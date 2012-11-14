/**
 * @file fluke-led.h
 *
 * $Id: fluke-led.h 2102 2009-10-26 20:36:13Z brylow $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _FLUKE_LED_H_
#define _FLUKE_LED_H_

#include <stddef.h>

/**
 * Control and status registers for the Fluke LEDs.  This structure is
 * mapped directly to the base address for the CSR.
 */
struct led_csreg
{
    volatile uint ioset;      /**< the IOSET register */
    volatile uint iodir;      /**< the IODIR register (?) */
    volatile uint ioclr;      /**< the IOCLR register */
};


#endif          /* _FLUKE_LED_H_ */

