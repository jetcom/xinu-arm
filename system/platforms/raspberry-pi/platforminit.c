/**
 * @file platforminit.c
 * @provides platforminit.
 */

#include <kernel.h>
#include <platform.h>
#include <uart.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "vic.h"
#include "gpio.h"

extern ulong cpuid;                     /* Processor id                    */
extern struct platform platform;        /* Platform specific configuration */

//NOTE on the Raspberry Pi, we rely on the GPU to have initialized the PL011
//properly so that we can do kprintf since we don't actually initialize it
//until the latter part of sysinit()

/**
 * Determines and stores all platform specific information.
 * @return OK if everything is determined successfully
 */
int platforminit( void )
{
    unsigned char c;
    int i;

    //set GPIO pin 14 to PL011 UART TX mode
    GPIOMODE(14, FSEL_AF0);
    //set GPIO pin 15 to PL011 UART RX mode
    GPIOMODE(15, FSEL_AF0);
    //turn off pull-up/pull-down resistors on the TX and RX pins
    GPIOPULLOF(14);
    GPIOPULLOF(15);

    //initialize the VIC
    vic_init();

    /*
     * Go into an infinite loop waiting for user to type the @ sign.
     * This will get Xinu going and produce output, like "Welcome
     * to Xinu."
     */

    i = 0;
    while (1) {
        if (i==0) {
            kprintf("Press @ to begin.\r\n");
        }
        i = (i+1)%100000;
        c = kgetc(&devtab[SERIAL0]);
        if (c == '@') {
            break;
        }
    }

    //fill in the platform information struct (from include/platform.h)
    strncpy(platform.name, "Raspberry Pi", PLT_STRMAX);
    strncpy(platform.family, "ARM", PLT_STRMAX);
    platform.maxaddr = (void *)(0x8000000/*128MB of RAM*/) /** \todo dynamically determine? */;
    platform.clkfreq = 1000000 /*we have a 1Mhz input clock to the system timer*/ /** \todo dynamically determine? */;
    //platform.uart_dll = 1337 /*Divisor Latch Low Byte, not useful?*/ /** \todo fixme */;
    //platform.uart_irqnum = 0; /*UART IRQ number? Not read anywhere.*/


    return OK;
}
