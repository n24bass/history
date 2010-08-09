#include "main.h"

// *** clone **************************************************************

#define MASTER_FSYS  48000000  // frequency of M52221DEMO board
#define SLAVE_FSYS    8000000  // frequency of target board

#define CLONE_PAGE_SIZE  256

#define WRITE_CONFIGURATION_REGISTER  0x01
#define PAGE_PROGRAM  0x02
#define READ_DATA  0x03
#define READ_STATUS_REGISTER  0x05
#define WRITE_ENABLE  0x06
#define BULK_ERASE  0xc7

#define WRITE_ERROR  0x40
#define WRITE_ENABLE_STATUS  0x02
#define WRITE_IN_PROGRESS  0x01


// perform both output and input qspi i/o
static
void
flash_qspi(byte *buffer, int length)
{
    int i;
    int request;

    while (length) {
        request = MIN(length, 16);

        for (i = 0; i < request; i++) {
            // set up the command
            MCF_QSPI_QAR = MCF_QSPI_QAR_CMD+i;
            MCF_QSPI_QDR = MCF_QSPI_QDR_CONT;

            // copy tx data to qspi ram
            MCF_QSPI_QAR = MCF_QSPI_QAR_TRANS+i;
            MCF_QSPI_QDR = buffer[i];
        }

        // set the queue pointers
        assert(request);
        MCF_QSPI_QWR = MCF_QSPI_QWR_ENDQP(request-1)|MCF_QSPI_QWR_NEWQP(0);

        // start the transfer
        MCF_QSPI_QDLYR = MCF_QSPI_QDLYR_SPE;

        // wait for transfer complete
        assert(! (MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF));
        while (! (MCF_QSPI_QIR & MCF_QSPI_QIR_SPIF)) {
        }
        MCF_QSPI_QIR = MCF_QSPI_QIR_SPIF;

        assert((MCF_QSPI_QWR & 0xf0) >> 4 == request-1);
        assert(! (MCF_QSPI_QDLYR & MCF_QSPI_QDLYR_SPE));

        for (i = 0; i < request; i++) {
            // copy rx data from qspi ram
            MCF_QSPI_QAR = MCF_QSPI_QAR_RECV+i;
            buffer[i] = MCF_QSPI_QDR;
        }

        buffer += request;
        length -= request;
    }

    MCF_QSPI_QWR = MCF_QSPI_QWR_CSIV;
}

static
int
flash_status(void)
{
    byte buffer[2];

    // read the status register
    buffer[0] = READ_STATUS_REGISTER;
    flash_qspi(buffer, 1+1);

    return buffer[1];
}

static
bool
flash_write(byte *buffer, int length)
{
    byte status;
    byte command;

    status = flash_status();
    if (status & (WRITE_ERROR|WRITE_IN_PROGRESS)) {
        return false;
    }

    // enable the write
    command = WRITE_ENABLE;
    flash_qspi(&command, 1);
    
    status = flash_status();
    if (! (status & WRITE_ENABLE_STATUS)) {
        return false;
    }

    // do the write
    flash_qspi(buffer, length);

    // wait for the write to complete
    do {
        status = flash_status();
        if (status & WRITE_ERROR) {
            return false;
        }
    } while (status & WRITE_IN_PROGRESS);
    
    return true;
}

void
clone(bool and_run)
{
    unsigned n;
    byte status;
    static byte buffer[4+CLONE_PAGE_SIZE];

    // AS is gpio output; bit 0 is slave rsti*
    MCF_GPIO_PASPAR = 0;
    MCF_GPIO_DDRAS = 0x3;

    // QS is primary
    MCF_GPIO_PQSPAR = 0x1555;

    // pulse slave rsti* low
    MCF_QSPI_QWR = 0;
    MCF_GPIO_CLRAS = ~1;
    delay(1);
    MCF_GPIO_SETAS = 1;
    delay(1);

    // initialize qspi master at 100k baud
    assert(MASTER_FSYS/2/100000 < 256);
    MCF_QSPI_QMR = MCF_QSPI_QMR_MSTR|/*MCF_QSPI_QMR_CPOL|MCF_QSPI_QMR_CPHA|*/MASTER_FSYS/2/100000;
    MCF_QSPI_QWR = MCF_QSPI_QWR_CSIV;

    status = flash_status();
    if (status & (WRITE_ERROR|WRITE_IN_PROGRESS)) {
    	printf("initialization failed\n");
    	return;
    }

    // write configuration register
    buffer[0] = WRITE_CONFIGURATION_REGISTER;
    if (SLAVE_FSYS > 25600000) {
        buffer[1] = MCF_CFM_CFMCLKD_PRDIV8|MCF_CFM_CFMCLKD_DIV((SLAVE_FSYS-1)/2/8/200000);
    } else {
        buffer[1] = MCF_CFM_CFMCLKD_DIV((SLAVE_FSYS-1)/2/200000);
    }
    if (! flash_write(buffer, 2+0)) {
    	printf("write configuration register failed\n");
    	return;
    }

    // bulk erase
    buffer[0] = BULK_ERASE;
    if (! flash_write(buffer, 1+0)) {
    	printf("bulk erase failed\n");
    	return;
    }

    for (n = 0; n < FLASH_BYTES; n += CLONE_PAGE_SIZE) {
        // get the reference data from our flash
        memcpy(buffer+4, (void *)n, CLONE_PAGE_SIZE);

        // program the data to the target device
        buffer[0] = PAGE_PROGRAM;
        buffer[1] = n/0x10000;
        buffer[2] = n/0x100;
        buffer[3] = n;
        if (! flash_write(buffer, 4+CLONE_PAGE_SIZE)) {
        	printf("\npage program failed\n");
        	return;
        }

        memset(buffer+4, 0x5a, CLONE_PAGE_SIZE);

        // read the data back from the target device
        buffer[0] = READ_DATA;
        buffer[1] = n/0x10000;
        buffer[2] = n/0x100;
        buffer[3] = n;
        flash_qspi(buffer, 4+CLONE_PAGE_SIZE);

        // verify the data
        if (memcmp(buffer+4, (void *)n, CLONE_PAGE_SIZE)) {
        	printf("\nverification failed at offset %d\n", n);
        	return;
        }
        
        printf(".");
    }
    
    if (and_run) {
	    // reset and run!
	    MCF_QSPI_QWR = MCF_QSPI_QWR_CSIV;

	    // pulse slave rsti* low
	    MCF_GPIO_CLRAS = ~1;
	    delay(1);
	    MCF_GPIO_SETAS = 1;
	    delay(1);
    }
    
    printf("\nclone done!\n");
}
