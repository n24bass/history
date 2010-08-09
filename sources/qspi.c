// *** qspi.c *********************************************************
// this file performs qspi i/o transfers.

#include "main.h"

#define QSPI_BAUD_FAST  800000  // zigbee
#define QSPI_BAUD_SLOW  200000  // default

static bool csiv;

// perform both output and input qspi i/o
void
qspi_transfer(byte *buffer, int length)
{
#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    int i;
    int x;
    int request;

    x = splx(7);
    
    // while there is data remaining...
    while (length) {
        // process up to 16 bytes at a time
        request = MIN(length, 16);

        // for all bytes...
        for (i = 0; i < request; i++) {
            // set up the command
            MCF_QSPI_QAR = MCF_QSPI_QAR_CMD+i;
            MCF_QSPI_QDR = MCF_QSPI_QDR_CONT|(csiv?0:MCF_QSPI_QDR_QSPI_CS0);

            // copy tx data to qspi ram
            MCF_QSPI_QAR = MCF_QSPI_QAR_TRANS+i;
            MCF_QSPI_QDR = buffer[i];
        }

        // set the queue pointers
        assert(request);
        MCF_QSPI_QWR = (csiv?0:MCF_QSPI_QWR_CSIV)|MCF_QSPI_QWR_ENDQP(request-1)|MCF_QSPI_QWR_NEWQP(0);

        // start the transfer
        MCF_QSPI_QDLYR = MCF_QSPI_QDLYR_SPE;

        // wait for transfer complete
        assert(! (MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF));
        while (! (MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)) {
        }
        MCF_QSPI_QIR = MCF_QSPI_QIR_SPIF;

        assert((MCF_QSPI_QWR & 0xf0) >> 4 == request-1);
        assert(! (MCF_QSPI_QDLYR & MCF_QSPI_QDLYR_SPE));

        // for all bytes...
        for (i = 0; i < request; i++) {
            // copy rx data from qspi ram
            MCF_QSPI_QAR = MCF_QSPI_QAR_RECV+i;
            buffer[i] = MCF_QSPI_QDR;
        }

        buffer += request;
        length -= request;
    }

    // transfer complete
    MCF_QSPI_QWR = csiv?MCF_QSPI_QWR_CSIV:0;
    
    splx(x);
#elif MCF51JM128 || MCF51QE128 || MC9S08QE128 || MC9S12DT256 || MC9S12DP512
#if MCF51JM128
    // cs active
    if (csiv) {
        PTED &= ~PTEDD_PTEDD7_MASK;
    } else {
        PTED |= PTEDD_PTEDD7_MASK;
    }
#elif MCF51QE128 || MC9S08QE128
    // cs active
    if (csiv) {
        PTBD &= ~PTBDD_PTBDD5_MASK;
    } else {
        PTBD |= PTBDD_PTBDD5_MASK;
    }
#elif MC9S12DT256 || MC9S12DP512
    // cs active
    if (csiv) {
        PTM &= ~0x08;
    } else {
        PTM |= 0x08;
    }
#else
#error
#endif
    
    while (length) {
        // N.B. spi needs us to read the status register even for release code!
        ASSERT(SPI1SX & SPI1S_SPTEF_MASK);
        ASSERT(! (SPI1SX & SPI1S_SPRF_MASK));
        
        SPI1DL = *buffer;
        
        while (! (SPI1SX & SPI1S_SPTEF_MASK)) {
            // NULL
        }
        
        while (! (SPI1SX & SPI1S_SPRF_MASK)) {
            // NULL
        }
        
        *buffer = SPI1DL;
        
        buffer++;
        length--;
    }

#if MCF51JM128
    // cs inactive
    if (csiv) {
        PTED |= PTEDD_PTEDD7_MASK;
    } else {
        PTED &= ~PTEDD_PTEDD7_MASK;
    }
#elif MCF51QE128 || MC9S08QE128
    // cs inactive
    if (csiv) {
        PTBD |= PTBDD_PTBDD5_MASK;
    } else {
        PTBD &= ~PTBDD_PTBDD5_MASK;
    }
#elif MC9S12DT256 || MC9S12DP512
    // cs inactive
    if (csiv) {
        PTM |= 0x08;
    } else {
        PTM &= ~0x08;
    }
#else
#error
#endif
#elif PIC32
    // cs active
    if (csiv) {
        LATGCLR = 1<<8;
    } else {
        LATGSET = 1<<8;
    }
    
    while (length) {
        assert(! (SPI1STATbits.SPIBUSY));
        assert(! (SPI1STATbits.SPIRBF));
        assert(SPI1STATbits.SPITBE);
        SPI1BUF = *buffer;
        
        while (! SPI1STATbits.SPIRBF) {
            // NULL
        }
        
        assert(! (SPI1STATbits.SPIBUSY));
        assert(SPI1STATbits.SPIRBF);
        assert(SPI1STATbits.SPITBE);
        *buffer = SPI1BUF;
        
        buffer++;
        length--;
    }

    // cs inactive
    if (csiv) {
        LATGSET = 1<<8;
    } else {
        LATGCLR = 1<<8;
    }
#endif
}

extern void
qspi_inactive(bool csiv_in)
{
    csiv = csiv_in;
#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    MCF_QSPI_QWR = csiv?MCF_QSPI_QWR_CSIV:0;
#elif MCF51JM128
    if (csiv) {
        PTED |= PTEDD_PTEDD7_MASK;
    } else {
        PTED &= ~PTEDD_PTEDD7_MASK;
    }
#elif MCF51QE128 || MC9S08QE128
    if (csiv) {
        PTBD |= PTBDD_PTBDD5_MASK;
    } else {
        PTBD &= ~PTBDD_PTBDD5_MASK;
    }
#elif MC9S12DT256 || MC9S12DP512
    if (csiv) {
        PTM |= 0x08;
    } else {
        PTM &= ~0x08;
    }
#elif PIC32
    if (csiv) {
        LATGSET = 1<<8;
    } else {
        LATGCLR = 1<<8;
    }
#else
#error
#endif
}

extern void
qspi_baud_fast(void)
{
#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    // initialize qspi master at 800k baud
    assert(bus_frequency/QSPI_BAUD_FAST < 256);
    MCF_QSPI_QMR = MCF_QSPI_QMR_MSTR|/*MCF_QSPI_QMR_CPOL|MCF_QSPI_QMR_CPHA|*/bus_frequency/QSPI_BAUD_FAST;
#elif MCF51JM128 || MCF51QE128 || MC9S08QE128 || MC9S12DT256 || MC9S12DP512
    int log2;
    int divisor;
    
    // initialize qspi master at 800k baud
    log2 = 0;
    divisor = bus_frequency/QSPI_BAUD_FAST/2;
    while (divisor > 8) {
        divisor /= 2;
        log2++;
    }
    assert(log2 < 8 && (divisor-1) < 8);
    SPI1BRX_SPR = log2;
    SPI1BRX_SPPR = divisor-1;
#elif PIC32
    // initialize qspi master at 800k baud
    SPI1CON = 0;

    assert(bus_frequency/QSPI_BAUD_FAST/2 - 1 < 512);
    SPI1BRG = bus_frequency/QSPI_BAUD_FAST/2 - 1;
    
    SPI1CON = _SPI1CON_ON_MASK|_SPI2CON_CKE_MASK|_SPI2CON_MSTEN_MASK;
#endif
}

extern void
qspi_initialize(void)
{
#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    // QS is primary
    MCF_GPIO_PQSPAR = 0x0055;

    // initialize qspi master at 200k baud
    assert(bus_frequency/QSPI_BAUD_SLOW < 256);
    MCF_QSPI_QMR = MCF_QSPI_QMR_MSTR|/*MCF_QSPI_QMR_CPOL|MCF_QSPI_QMR_CPHA|*/bus_frequency/QSPI_BAUD_SLOW;
#elif MCF51JM128 || MCF51QE128 || MC9S08QE128 || MC9S12DT256 || MC9S12DP512
    int log2;
    int divisor;
    
#if MCF51JM128
    // E7 is gpio output
    PTEDD |= PTEDD_PTEDD7_MASK;
#elif MCF51QE128 || MC9S08QE128
    // B5 is gpio output
    PTBDD |= PTBDD_PTBDD5_MASK;
#elif MC9S12DT256 || MC9S12DP512
    // M3 is gpio output
    DDRM |= 0x08;
    
    // route spi0 to m2,3,4,5
    MODRR |= 0x10;
#else
#error
#endif
    
    SPI1C1X = SPI1C1_SPE_MASK|SPI1C1_MSTR_MASK;
    SPI1C2X = 0;
    
    // initialize qspi master at 200k baud
    log2 = 0;
    divisor = bus_frequency/QSPI_BAUD_SLOW/2;
    while (divisor > 8) {
        divisor /= 2;
        log2++;
    }
    assert(log2 < 8 && (divisor-1) < 8);
    SPI1BRX_SPR = log2;
    SPI1BRX_SPPR = divisor-1;
#elif PIC32
    // G8 is gpio putpit
    TRISGCLR |= 1<<8;

    SPI1CON = 0;

    assert(bus_frequency/QSPI_BAUD_SLOW/2 - 1 < 512);
    SPI1BRG = bus_frequency/QSPI_BAUD_SLOW/2 - 1;
    
    SPI1CON = _SPI1CON_ON_MASK|_SPI2CON_CKE_MASK|_SPI2CON_MSTEN_MASK;
#endif

    // initialize qspi to active low chip select
    qspi_inactive(1);
}

