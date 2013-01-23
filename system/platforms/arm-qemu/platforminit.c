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
#include "interrupt.h"
#include "vic.h"
#include <led.h>
#include "timer.h"

extern ulong cpuid;             /* Processor id                    */

extern struct platform platform;        /* Platform specific configuration */

void setup_pins( void );
void kinitputc( void );

/**
 * Determines and stores all platform specific information.
 * @return OK if everything is determined successfully
 */
int platforminit( void )
{
    unsigned char c;
    int i;
    
    //    setup_pins();

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
    	c = getc(SERIAL0);
        if (c == '@') {
            break;
        }
    }        

    strncpy(platform.name, "ARM Qemu", PLT_STRMAX);
    platform.maxaddr = (void *)(0x8000000/*RAM*/) /** \todo dynamically determine? */;
    platform.clkfreq = 64000 /** \todo dynamically determine? */;
    //    platform.uart_dll = 1337 /** \todo fixme */;


    return OK;
}
