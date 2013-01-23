/**
 * @file interrupt.h
 * 
 * Constants and declarations associated with interrupt and exception
 * processing.
 *
 */

#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef void (__attribute__((interrupt("IRQ"))) *irq_handler)( void );

/*
 * irqmasks are laid out like the following:
 * 
 * bits 0-15: whether a given interrupt is enabled or not.
 * bit 16: whether interrupts are enabled (1) or disabled (0)
 *
 * The reason for this is that restore() is responsible
 *  for enabling/disabling interrupts as well as restoring
 *  the IRQ mask. 
 *
 * See Comer, "OS Design: The XINU approach, Linksys edition," pg. 40.
 */
typedef unsigned long irqmask;  /**< machine status for disable/restore  */

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
