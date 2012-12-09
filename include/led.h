/**
 * @file led.h
 * This file provides various definitions and prototypes for the led
 * driver and all its affiliates
 *
 * @authors Andrew Webster, Brad Haan, Avery Martin
 */
/* Embedded XINU, Copyright (C) 2007.  All rights reserved. */

//#include <kernel.h>
#include <device.h>
#include <stdarg.h>
#include <stdint.h>

#ifndef _LED_H_
#define _LED_H_

/**
 * LED control block
 */
struct led
{
    /* Pointers to associated structures */
    void *csr;                  /**< Control & status registers         */
    device *dev;                /**< Dev structure                      */
};

extern struct led ledtab[];




#define IODIR          (*((volatile unsigned long *) 0xE0028008))
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))
#define FRONT_LED_PIN        (1 << 17)
#define MDIN                 (1 << 6)
#define MCLK                 (1 << 4)
#define D2A_CS               (1 << 21)
#define D2A_CHAN_LED         0x0400
#define D2A_CHAN_IR          0x0A00

#define UART1_LSR            (*((volatile unsigned char *)0xE0010014))
#define USLR_RDR             (1 << 0)
#define UART1_RBR            (*((volatile unsigned char *) 0xE0010000))

#define IROUT1      (1 << 13)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)


/* Prototypes for led function calls */

devcall ledInit(device *devptr);
devcall ledWrite(device *devptr, void *buf /* not used */, uint power);

int getchBlockRTS( void );
void set_trs( void );
void clear_trs( void );

void server_set_ir_emitters( void );


#endif                          /* _LED_H_ */
