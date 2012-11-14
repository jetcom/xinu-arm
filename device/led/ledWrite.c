/**
 * @file     ledWrite.c
 * @provides ledWrite
 * @authors Andrew Webster, Brad Haan, Avery Martin
 * A simple, high-level interface to write .
 *
 * $Id: ledWrite.c 2077 2009-09-24 23:58:54Z mschul $
 */

/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

#include <stddef.h>
#include <device.h>
#include <led.h>
#include "fluke-led.h"

extern void usleep(int);

/**
 * Provides a simple driver for turning a LED on or off
 * @param *devptr pointer to the LED device
 * @param buf      not used: pass in 0 or NULL.
 * @param power    boolean value that will set the LED to on (1) or
 *  off(0), or for dimmable LED, to its intensity.
 * @return OK on success, SYSERR on failure
 */
devcall ledWrite(device *devptr, void *buf, uint power)
{
    struct led *ledptr;
    volatile struct led_csreg *regptr;

    ledptr = &ledtab[devptr->minor];
    regptr = (struct led_csreg *)ledptr->csr;
    if (regptr == NULL) {
        return SYSERR;
    }

    if (devptr->num == FRONTLED) {
        if (power != 0) {
            regptr->ioset = FRONT_LED_PIN;
        } else {
            regptr->ioclr = FRONT_LED_PIN;
        }
        return OK;
    }

    if (devptr->num == BACKLED) {	// dimmable led
        // Magic code from scribbler code.
        // calls to usleep() were calls to d2a_sleep().
        int i, data;

        /* TODO: check if power is a legal value */
        data = (power & 0xFF) | D2A_CHAN_LED;

        regptr->ioclr = D2A_CS;
        usleep(100);
        for (i = 11; i >= 0; i--) {
            regptr->ioclr = MCLK;
            usleep(100);

            if (data & (1 << i)) {
                regptr->ioset = MDIN;
            } else {
                regptr->ioclr = MDIN;
            }
            usleep(100);
            regptr->ioset = MCLK;
            usleep(100);
        }
    
        regptr->ioclr = MCLK;
        usleep(100);
        regptr->ioset = D2A_CS;
        usleep(100);
    }
    

#if 0    
    if((ledNum == 0) && power)
        IOSET = FRONT_LED_PIN;
    else if ((ledNum == 0) && !power)
        IOCLR = FRONT_LED_PIN;
    else if (ledNum == 1) { // if it is the dimmer-led, run this LED magic! from Fluke firmware
    
        int i, data;
    
        data = (power & 0xFF) | D2A_CHAN_LED;
    
        IOCLR=D2A_CS; usleep(100);
        for (i = 11; i >= 0; i--)
            {
                IOCLR=MCLK;
                usleep(100); // usleeps were d2a_sleeps
                if (data & (1 << i))
                    {
                        IOSET = MDIN;
                    }
                else
                    {
                        IOCLR = MDIN;
                    }
                usleep(100);
                IOSET=MCLK; usleep(100);
            }
    
        IOCLR = MCLK; usleep(100);
        IOSET = D2A_CS;  usleep(100);
    }
#endif
    else {  //Assume any other led is the IR tx set.  -- tew3, mlk9, ame6

    
        int i, data;
    
        data = (power & 0xFF) | D2A_CHAN_IR;
    
        IOCLR=D2A_CS; usleep(100);
        for (i = 11; i >= 0; i--)
            {
                IOCLR=MCLK;
                usleep(100); // usleeps were d2a_sleeps
                if (data & (1 << i))
                    {
                        IOSET = MDIN;
                    }
                else
                    {
                        IOCLR = MDIN;
                    }
                usleep(100);
                IOSET=MCLK; usleep(100);
            }
    
        IOCLR = MCLK; usleep(100);
        IOSET = D2A_CS;  usleep(100);

        //    serve_send_ir_message();

    }

    return OK;
}




