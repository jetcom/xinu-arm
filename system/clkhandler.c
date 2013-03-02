/**
 * @file     clkhandler.c
 * @provides clkhandler.
 *
 * $Id: clkhandler.c 2020 2009-08-13 17:50:08Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <queue.h>
#include <clock.h>
#include <thread.h>
#include <platform.h>
#ifdef FLUKE_ARM
#include "timer.h"
#endif
#include "conf.h"

//DEBUG
#include "platforms/raspberry-pi/gpio.h"

void wakeup(void);
syscall resched(void);

/**
 * Clock handler updates timer registers and system time.
 * Wakes sleeping threads if necessary.
 */
#ifdef FLUKE_ARM
static volatile struct spc804_timer *timer0 = (struct spc804_timer *) 0x101E2000;
#endif
interrupt clkhandler( void );

interrupt clkhandler(void)
{
    /* Reset the timer to fire again */
    clkupdate(platform.clkfreq / CLKTICKS_PER_SEC);

    /* Another clock tick passes. */
    clkticks++;

    /* Update global second counter. */
    if (clkticks >= CLKTICKS_PER_SEC)
    {
        clktime++;
        clkticks = 0;
    }

    /* If sleepq is not empty, decrement first key.   */
    /* If key reaches zero, call wakeup.              */
    if (nonempty(sleepq) && (--firstkey(sleepq) <= 0))
    {
        wakeup(); // This no longer does a resched() call since we need to
                  // clear our interrupts before doing a resched()
    }

    #ifdef FLUKE_ARM
    /* Acknowledge and clear the interrupt */
    timer0->int_clr = 1;
    irq_handled();
    #endif

    resched();
}

