/**
 * Functions to interface the VIC with XINU's interrupt
 *  functions.
 *
 * @author John Kloosterman for CS320 at Calvin College
 * @date April 2, 2012
 */

#include "interrupt.h"
#include "vic.h"

/**
 * Initialize interrupts and allow them
 *  to fire.
 *
 * @return
 *  New irq mask.
 */
irqmask enable( void )
{
    vic_enable_interrupts();

    return vic_get_irqmask();
}

/**
 * Disable interrupts, return old state.
 *
 * @return
 *  state of interrupts before they were disabled
 */
irqmask disable( void )
{
    irqmask im_pre = vic_get_irqmask();

    vic_disable_interrupts();

    return im_pre;
}

/**
 * Restore interrupts to state in im.
 *
 * @param
 *  im irqmask of interrupt state to restore
 * @return
 *  state of interrupts when called
 */
irqmask restore( irqmask im )
{
    irqmask im_pre = vic_get_irqmask();

    vic_set_irqmask( im );

    return im_pre;
}

irqmask enable_irq( int irq )
{
    irqmask im_pre = vic_get_irqmask();

    vic_enable_irq( irq );

    return im_pre;
}

irqmask disable_irq( int irq )
{
    irqmask im_pre = vic_get_irqmask();

    vic_disable_irq( irq );

    return im_pre;
}

void register_irq( int irq, irq_handler handler )
{
    vic_register_irq( irq, handler );
}

/**
 * Example of how to correctly define an IRQ handler,
 *  from the  firmware.
 */
void an_interrupt_handler( void )
{

}
