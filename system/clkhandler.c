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

void wakeup(void);
syscall resched(void);

/**
 * Clock handler updates timer registers and system time.
 * Wakes sleeping threads if necessary.
 */
#ifdef FLUKE_ARM
interrupt clkhandler( void ) __attribute__( ( interrupt( "IRQ" ) ) );
#endif

interrupt clkhandler(void)
{
#ifndef FLUKE_ARM
    clkupdate(platform.clkfreq / CLKTICKS_PER_SEC);
#endif

    /* Another clock tick passes. */
    clkticks++;

    /* Update global second counter. */
    if (CLKTICKS_PER_SEC == clkticks)
    {
        clktime++;
        clkticks = 0;
    }

    /* If sleepq is not empty, decrement first key.   */
    /* If key reaches zero, call wakeup.              */
    if (nonempty(sleepq) && (--firstkey(sleepq) <= 0))
    {
        wakeup();
    }
    else
    {
        resched();
    }
}
