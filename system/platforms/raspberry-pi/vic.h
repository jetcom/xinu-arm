#ifndef __VIC_H
#define __VIC_H

/*
    See vic.c for important notes.
    See the table page 113 of the BCM2835 Arm Peripherals datasheet for vector numbers
*/

#include "interrupt.h"


void vic_init(void);

static inline int vic_interrupts_disabled( void )
{
    int ret;

    // Check if interrupts are already enabled. If so, return 0
    __asm__("mrs r0, cpsr;"
            "and %[ret], r0, #0x80;"
            : [ret]"=r" (ret)
            :
            : "r0");

    return ret;
}

static inline int vic_enable_interrupts( void )
{
    int ret;

    ret = vic_interrupts_disabled();

    __asm__("mrs r0,cpsr;"
            "bic r0,r0,#0x80;"
            "msr cpsr_c,r0");

    return ret;
}

static inline int vic_disable_interrupts(void)
{
    int ret;

    ret = vic_interrupts_disabled();

    __asm__("mrs r0, cpsr; "
            "orr r0, r0, #0x80;"
            "msr cpsr_c, r0");

    return ret;
}

irqmask vic_get_irqmask(void);

void vic_set_irqmask(irqmask im);

void vic_enable_irq(int vect_num);

void vic_disable_irq(int vect_num);

void vic_register_irq(int vect_num, irq_handler handler);

void vic_deregister_irq(int vect_num);

void vic_irq_handler(void);

#endif //__VIC_H
