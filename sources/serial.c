// *** serial.c *******************************************************
// This file implements an interrupt driven serial console.

#include "main.h"

#if PIC32 || MCF51CN128
#define UART  1
#else
#define UART  0
#endif

#define BAUDRATE  9600

#define BUFFERSIZE  64

static byte rxbuffer[BUFFERSIZE];
static int rxlength;  // number of rx bytes in buffer

static bool waiting;  // we have sent Ctrl-S at end of command
static bool suspend;  // set this to send Ctrl-S in next send() loop
static bool resume;  // set this to send Ctrl-Q in next send() loop
static bool busy;  // we're in the middle of a send() loop

#define CTRLS  ('S'-'@')  // suspend
#define CTRLQ  ('Q'-'@')  // resume

bool serial_active;

#if SODEBUG
volatile bool serial_in_isr;
volatile int32 serial_in_ticks;
volatile int32 serial_out_ticks;
volatile int32 serial_max_ticks;
#endif

// this function disables the serial isr when BASIC takes over control
void
serial_disable(void)
{
#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    // disable uart0 receive interrupts
    MCF_UART0_UIMR = 0;
#elif MCF51JM128 || MCF51QE128 || MC9S08QE128 || MC9S12DT256 || MC9S12DP512
    // disable uart1 receive interrupts
    SCI1C2X &= ~SCI1C2_RIE_MASK;
#elif MCF51CN128
    // disable uart2 receive interrupts
    SCI2C2X &= ~SCI2C2_RIE_MASK;
#elif PIC32
    // Unconfigure UART2 RX Interrupt
    ConfigIntUART2(0);
#endif
    // don't allow the rx ball to start rolling
    waiting = false;
}


// this function acknowledges receipt of a serial command from upper
// level code.
void
serial_command_ack(void)
{
    int x;
    bool boo;
    
    ASSERT(gpl() == 0);

    x = splx(7);
    
    // if we held off the serial rx...
    if (waiting) {
        // receive new characters
        if (rxlength) {    
            // accumulate new commands
            boo = terminal_receive(rxbuffer, rxlength);
            rxlength = 0;
            
            // if a full command was accumulated...
            if (! boo) {
                // wait for another terminal_command_ack();
                goto XXX_SKIP_XXX;
            }
        }
        
        // start the rx ball rolling
        waiting = false;
        
        // if the tx is ready...
        if (pin_uart_tx_ready(UART)) {
            // stuff a resume
            pin_uart_tx(UART, CTRLQ);
        } else {
            // record we need a resume
            suspend = false;
            resume = true;
            assert(busy);
        }
    }
    
XXX_SKIP_XXX:
    splx(x);
}

INTERRUPT
void
#if PIC32
__ISR(32, ipl2) // REVISIT -- ipl?
#endif
serial_isr(void)
{
    char c;
    bool boo;
    
    assert(! serial_in_isr);
    assert((serial_in_isr = true) ? true : true);
    assert((serial_in_ticks = ticks) ? true : true);

#if ! MC9S08QE128 && ! MC9S12DT256 && ! MC9S12DP512
    (void)splx(7);
#endif

#if PIC32
    // Clear the RX interrupt Flag
    mU2RXClearIntFlag();
#endif

    do {
        // process the receive fifo
        while (pin_uart_rx_ready(UART)) {
            c = pin_uart_rx(UART);
            if (c && c != CTRLS && c != CTRLQ) {
                if (c == '\r') {
                    serial_active = true;
                }
                rxbuffer[rxlength++] = c;
                assert(rxlength < sizeof(rxbuffer));
            }
        }
        
        
        // receive characters
        if (rxlength && ! waiting) {    
            // accumulate commands
            boo = terminal_receive(rxbuffer, rxlength);
            rxlength = 0;
            
            // if a full command was accumulated...
            if (! boo) {
                // if the tx is ready...
                if (pin_uart_tx_ready(UART)) {
                    // stuff a suspend
                    pin_uart_tx(UART, CTRLS);
                } else {
                    // record we need a suspend
                    suspend = true;
                    resume = false;
                    assert(busy);
                }
                
                // drop the ball
                waiting = true;
            }
        }
    } while (pin_uart_rx_ready(UART));
    
    assert(serial_in_isr);
    assert((serial_in_isr = false) ? true : true);
    assert((serial_out_ticks = ticks) ? true : true);
    assert((serial_max_ticks = MAX(serial_max_ticks, serial_out_ticks-serial_in_ticks)) ? true : true);
}

void
serial_send(const byte *buffer, int length)
{
    ASSERT(gpl() == 0);

    assert(! busy);
    busy = true;
    
    while (! pin_uart_tx_ready(UART)) {
        // revisit -- poll?
    }
    
    // send the characters synchronously
    for (;;) {
        // if we have a suspend or resume to send, they take precedence
        if (suspend) {
            pin_uart_tx(UART, CTRLS);
            suspend = false;
            assert(! resume);
        } else if (resume) {
            pin_uart_tx(UART, CTRLQ);
            resume = false;
            assert(! suspend);
        } else {
            if (! length) {
                break;
            }
            
            pin_uart_tx(UART, *buffer);
            buffer++;
            length--;
        }
        
        while (! pin_uart_tx_ready(UART)) {
            // revisit -- poll?
        }
    }
    
    assert(busy);
    busy = false;
}

void
serial_initialize(void)
{
    // configure the first uart for serial terminal by default
    pin_uart_configure(UART, BAUDRATE, 8, 2, false);
    
    // start us out with a CTRLQ
    pin_uart_tx(UART, CTRLQ);

#if MCF52221 || MCF52233 || MCF52259 || MCF5211
    // UART 0
    // PORT UA (4 pins)
    // UCTS0#, URTS0#, URXD0, and UTXD0 are "primary" functions of their pin group.
    // Set to primary function (0x01).
    MCF_GPIO_PUAPAR = 0x55;
    
    // enable uart0 interrupt.
    MCF_INTC0_ICR13 = MCF_INTC_ICR_IL(SPL_SERIAL)|MCF_INTC_ICR_IP(SPL_SERIAL-2);
    MCF_INTC0_IMRL &= ~MCF_INTC_IMRL_MASKALL;
    MCF_INTC0_IMRL &= ~MCF_INTC_IMRL_INT_MASK13;  // uart0
    
    // configure uart0 receive interrupts
    MCF_UART0_UIMR = MCF_UART_UIMR_FFULL_RXRDY;
#elif MCF51JM128 || MCF51QE128 || MC9S08QE128 || MC9S12DT256 || MC9S12DP512
    SCI1C2X = SCI1C2_TE_MASK|SCI1C2_RE_MASK;
    
    // configure uart1 receive interrupts
    SCI1C2X |= SCI1C2_RIE_MASK;
#elif MCF51CN128
    SCI2C2X = SCI2C2_TE_MASK|SCI2C2_RE_MASK;
    
    // configure uart2 receive interrupts
    SCI2C2X |= SCI2C2_RIE_MASK;
    
    PTDPF2 = 0xa0;
#elif PIC32
    U2MODE |= _U2MODE_UARTEN_MASK;

    // Configure UART1 RX Interrupt
    ConfigIntUART2(UART_INT_PR2 | UART_RX_INT_EN);
#else
#error
#endif
}
