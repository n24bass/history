// *** timer.c ********************************************************
// this file implements the core interval timer used internally.

#include "main.h"

bool timer_in_isr;

volatile int ticks;  // incremented by pit0 isr every millisecond
volatile int seconds;  // incremented by pit0 isr every second

// called by pit0 every millisecond
INTERRUPT
void
timer_isr(void)
{
    assert(! timer_in_isr);
    timer_in_isr = true;
    
    (void)splx(-SPL_PIT0);

#if ! MCF51JM128
    MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIF;
#else
    RTCSC |= RTCSC_RTIF_MASK;
#endif
    ticks++;

    // poll the adc every millisecond
    adc_timer_poll();

    if (ticks%125 == 0) {
        if (ticks%1000 == 0) {
            seconds++;
        }
        
        // poll the LEDs 8 times a second
        led_timer_poll();
        
#if PICTOCRYPT
        // poll for panics 8 times a second
        main_timer_poll();
#endif
    }

#if MCF52233
    // 200 Hz cticks
    if (ticks%5 == 0) {
        extern volatile unsigned long cticks;
    
        cticks++;
    }
#endif

#if STICKOS
    // profile
    code_timer_poll();
#endif

#if BADGE_BOARD
    // manage LED matrix
    jm_timer_poll();
#endif

    assert(timer_in_isr);
    timer_in_isr = false;
}

// this function initializes the timer module.
void
timer_initialize(void)
{
#if ! MCF51JM128
    // enable pit0 timer interrupt
    MCF_INTC0_ICR55 = MCF_INTC_ICR_IL(SPL_PIT0)|MCF_INTC_ICR_IP(SPL_PIT0);
    MCF_INTC0_IMRH &= ~MCF_INTC_IMRH_INT_MASK55;  // pit0
    MCF_INTC0_IMRL &= ~MCF_INTC_IMRL_MASKALL;

    // configure pit0 to interrupt every 1 ms
    MCF_PIT0_PCSR = 0;
    MCF_PIT0_PMR = bus_frequency/1000;  // 1 ms
    MCF_PIT0_PCSR = MCF_PIT_PCSR_PRE(0)|MCF_PIT_PCSR_DOZE|MCF_PIT_PCSR_OVW|MCF_PIT_PCSR_PIE|MCF_PIT_PCSR_RLD|MCF_PIT_PCSR_EN;
#else  // ! MCF51JM128
    // remap rtc to level 6
    INTC_PL6P7 = 27;
    
    // enable rtc interrupt
    RTCSC = RTCSC_RTCLKS0_MASK|RTCSC_RTIE_MASK|1;
    RTCMOD = 11;  // 1ms at 12MHz
#endif
}

