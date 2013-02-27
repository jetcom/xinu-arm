/**
 * @file interrupt.h
 * 
 * Constants and declarations associated with interrupt and exception
 * processing.
 *
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "stdint.h"
#include "bcm2835.h"

#define INTERRUPT_BASE_ADDR 0x2000B000
#define INTERRUPT_BASICPEND_ADDR       (INTERRUPT_BASE_ADDR+0x200)
#define INTERRUPT_IRQPEND1_ADDR        (INTERRUPT_BASE_ADDR+0x204)
#define INTERRUPT_IRQPEND2_ADDR        (INTERRUPT_BASE_ADDR+0x208)
#define INTERRUPT_FIQCONTROL_ADDR      (INTERRUPT_BASE_ADDR+0x20C)
#define INTERRUPT_ENABLEIRQ1_ADDR      (INTERRUPT_BASE_ADDR+0x210)
#define INTERRUPT_ENABLEIRQ2_ADDR      (INTERRUPT_BASE_ADDR+0x214)
#define INTERRUPT_ENABLEBASICIRQ_ADDR  (INTERRUPT_BASE_ADDR+0x218)
#define INTERRUPT_DISABLEIRQ1_ADDR     (INTERRUPT_BASE_ADDR+0x21C)
#define INTERRUPT_DISABLEIRQ2_ADDR     (INTERRUPT_BASE_ADDR+0x220)
#define INTERRUPT_DISABLEBASICIRQ_ADDR (INTERRUPT_BASE_ADDR+0x224)
#define INTERRUPT_BASICPEND       __IO(INTERRUPT_BASICPEND_ADDR)
#define INTERRUPT_IRQPEND         __IO64(INTERRUPT_IRQPEND1_ADDR)
   #define IRQSYSTIMERC1 1
   #define IRQSYSTIMERC3 3
   #define IRQAUX        29
   #define IRQUART       57
#define INTERRUPT_IRQPEND1        __IO(INTERRUPT_IRQPEND1_ADDR)
#define INTERRUPT_IRQPEND2        __IO(INTERRUPT_IRQPEND2_ADDR)
#define INTERRUPT_FIQCONTROL      __IO(INTERRUPT_FIQCONTROL_ADDR)
#define INTERRUPT_ENABLEIRQ       __IO64(INTERRUPT_ENABLEIRQ1_ADDR)
#define INTERRUPT_ENABLEIRQ1      __IO(INTERRUPT_ENABLEIRQ1_ADDR)
#define INTERRUPT_ENABLEIRQ2      __IO(INTERRUPT_ENABLEIRQ2_ADDR)
#define INTERRUPT_ENABLEBASICIRQ  __IO(INTERRUPT_ENABLEBASICIRQ_ADDR)
#define INTERRUPT_DISABLEIRQ1     __IO(INTERRUPT_DISABLEIRQ1_ADDR)
#define INTERRUPT_DISABLEIRQ2     __IO(INTERRUPT_DISABLEIRQ2_ADDR)
#define INTERRUPT_DISABLEBASICIRQ __IO(INTERRUPT_DISABLEBASICIRQ_ADDR)

typedef void (__attribute__((interrupt("IRQ"))) *irq_handler)( void );

/*
 * See Comer, "OS Design: The XINU approach, Linksys edition," pg. 40.
 */
typedef struct {
    uint32_t lower; //IRQ bank 1 status, 1 means enabled, 0 disabled
    uint32_t upper; //IRQ bank 2 status
    uint32_t irqen; //ARM CPU status, 0 means enabled, !=0 disabled
} irqmask;

/* Interrupt enabling function prototypes */
irqmask disable(void);
irqmask restore(irqmask);
irqmask enable(void);
irqmask enable_irq( int irq );
irqmask disable_irq( int irq );
void register_irq( int irq, irq_handler handler );
irq_handler get_irq(int irq);
void irq_handled( void );
int in_interrupt( void );

#endif                          /* _INTERRUPT_H_ */
