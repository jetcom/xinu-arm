/**
 * 
 * ARM PrimeCell™ Vectored Interrupt Controller (PL190/PL192)

 * PL190: http://infocenter.arm.com/help/topic/com.arm.doc.ddi0181e/DDI0181.pdf
 * PL192: http://infocenter.arm.com/help/topic/com.arm.doc.ddi0273a/DDI0273.pdf

 * Also useful: * http://lxr.free-electrons.com/source/arch/arm/mach-versatile/include/mach/platform.h#L207
 *
 * @author Travis Brown
 * @date November 16, 2012
 */

#include <stddef.h>
#include <led.h>
#include "vic.h"


/**
 * The VIC device
 */
// int vic_next_slot = 0;

/**
 * This ISR is called when a device fires an interrupt
 *  but no handler was registered in the VIC.
 *
 * It flashes the front LED to tell the developer that
 *  something went wrong, since the interrupt will just keep
 *  firing.
 */
void vic_default( void )
{
}

/**
 * Initialize the VIC and enable interrupts.
 */
void vic_init( void )
{
    /*
    uint32_t cellid = 0;
    for ( i = 0; i < 4; i++ )
    {
        cellid |= (( lpc_vic->peripheralID[i] & 0xff ) << (8*i));
    }
       uint vendor = (cellid >> 12 ) & 0xff;
       kprintf("cellid: %x\n", cellid );
    kprintf("vendor: %x\n", vendor );*/

    
    /*
    kprintf( "vect_addr: %x,  vect_addrs: %x, vect_cntls: %x\r\n",
             &(lpc_vic->pl190_vect_addr),
	     &(lpc_vic->vect_addrs[0]),
	     &(lpc_vic->vect_cntls[0]) );*/



    // Set the default interrupt handler to do nothing
    lpc_vic->pl190_def_vect_addr = vic_default;
}

/**
 * Returns the current interrupt mask.
 *
 * Optimize this as inline?
 */
irqmask vic_get_irqmask( void )
{
    return irqmask_pack( vic_interrupts_enabled(), lpc_vic->int_enable );
}

void vic_set_irqmask( irqmask im )
{
    if( irqmask_interrupts_enabled( im ) )
	vic_enable_interrupts();
    else
	vic_disable_interrupts();

    im &= 0xffff;

    lpc_vic->int_enable = im;
    lpc_vic->int_en_clear = ~im;
}

void vic_enable_irq( int irq )
{
    // We don't have to worry about ORing, because
    //  only 1-bits have effect.
    lpc_vic->int_enable = 1 << irq;     // Enable our interrupt
    //lpc_vic->int_select = 1 << irq;     // Select FIQ
}

void vic_disable_irq( int irq )
{
    // We don't have to worry about ORing, because
    //  only 1-bits have effect. Setting a bit to 1 in this
    //  register clears the interrupt.
    lpc_vic->int_en_clear = 1 << irq;
}

// There are 32 slots for 32 interrupts.
void vic_register_irq( vic_source_t irq, irq_handler handler )
{
    lpc_vic->int_en_clear = 1 << irq;       // Disable the interrupt
    lpc_vic->vect_addrs[irq] = handler;     // Set vector address
    lpc_vic->vect_cntls[irq] = irq | 0x20;  // Enable interrupt source
    kprintf("lpc_vic->vect_ctrls[irq]: 0x%x\n",  lpc_vic->vect_cntls[irq] );


    // Bit 5 needs to be set to 1 to enable the interrupt. (Hex 0x20)
    // Bits 0-4 are the source. The VIC doesn't like having 2 with the
    //  same priority, so we use the slot number.
    //lpc_vic->vect_cntls[irq] = irq | 0x20;
}

irq_handler get_irq(int irq)
{
    return lpc_vic->vect_addrs[irq];
}

void vic_interrupt_handled( void )
{
    lpc_vic->pl190_vect_addr = 0xffffffff;
}

int vic_in_interrupt()
{
    return lpc_vic->pl190_vect_addr != 0;
}
