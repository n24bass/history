// *** init.c *********************************************************
// this file contains non-page0 initialization, which runs after we
// have completed compatible upgrade.  this file subsequently calls
// main(), wasting a word of stack.

#include "main.h"

#if ! PIC32 && ! MC9S08QE128 && ! MC9S12DT256 && ! MC9S12DP512
extern unsigned char far __BSS_START[], __BSS_END[];
extern unsigned char far __DATA_RAM[], __DATA_ROM[], __DATA_END[];
#endif

#if COMPAT
uint32 incompat;
#endif

bool disable_autorun;
uint16 flash_checksum;
bool usb_host_mode;

#if ! PIC32 && ! MC9S08QE128 && ! MC9S12DT256 && ! MC9S12DP512

#if BADGE_BOARD || DEMO_KIT
extern void pre_main(void);
#endif
extern int main();

// N.B. this is outside of page0
void
init(void)
{
    byte *p;
    uint32 n;
    uint8 *dp, *sp;
    
#if COMPAT
    if (__DATA_ROM != __DATA_RAM) {
        dp = (uint8 *)__DATA_RAM;
        sp = (uint8 *)__DATA_ROM;
        n = __DATA_END - __DATA_RAM;
        while (n--) {
            *dp++ = *sp++;
        }
    }
#endif

#if MCF51JM128
    PTGPE = 0x01;
#elif MCF51QE128
    PTAPE = 0x04;
#endif

    // move initialized data from ROM to RAM.
    // N.B. we do this here since these variables will likely change,
    // and we don't want that to result in an incompatible upgrade!
    if (__DATA_ROM != __DATA_RAM) {
        dp = (uint8 *)__DATA_RAM;
        sp = (uint8 *)__DATA_ROM;
        n = __DATA_END - __DATA_RAM;
        while (n--) {
            *dp++ = *sp++;
        }
    }

    // flash beyond this point is available for runtime data
    end_of_static = __DATA_ROM + (__DATA_END - __DATA_RAM);

    // compute flash checksum
    for (p = (byte *)0; p < end_of_static; p++) {
        flash_checksum += *p;
    }

#if BADGE_BOARD || DEMO_KIT
    pre_main();
#endif

#if ! FLASHER && ! PICTOCRYPT
    // initialize pins
    pin_initialize();
#endif

    // finally, call main()
    main();
}
#endif

