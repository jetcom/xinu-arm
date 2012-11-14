/**
 * The LPC2106 Vectored Interrupt Controller driver.
 *
 * @author John Kloosterman for CS320 at Calvin College,
 *   based on Fluke firmware code.
 * @date April 17, 2012
 */

#include <stddef.h>
#include <led.h>
#include "vic.h"

/*
 * See LPC2016 manual page 62
 */
struct vic
{
    uint irq_status;
    uint fiq_status;
    uint raw_intr;
    uint int_select;
    uint int_enable;
    uint int_en_clear;
    uint soft_int;
    uint soft_int_clear;
    uint protection;  // 0xFFFF F020

    uint reserved_0[0x3];

    void *vect_addr;// 0xFFFF F030
    void *def_vect_addr; // 0xFFFF F034 

    uint reserved_1[0x32]; // 0x33 = 0xCC / 4 bytes per word

    void *vect_addrs[16]; // 0xFFFF F100

    uint reserved_2[0x30];

    uint vect_cntls[16]; // 0xFFFF F200 
};


/**
 * The VIC device
 */
static struct vic *lpc_vic = (struct vic *) 0xFFFFF000;
// int vic_next_slot = 0;

/**
 * This ISR is called when a device fires an interrupt
 *  but no handler was registered in the VIC.
 *
 * It flashes the front LED to tell the developer that
 *  something went wrong, since the interrupt will just keep
 *  firing.
 */
void vic_default( void ) __attribute__ ((interrupt("IRQ")));
void vic_default( void )
{
    int i;

    write( FRONTLED, 0, 0 );
    for( i = 0; i < 1000; i++ );
    write( FRONTLED, 0, 1 );
    for( i = 0; i < 1000; i++ );

    // This is unreachable, but good form.
    lpc_vic->vect_addr = 0;
}

/**
 * Initialize the VIC and enable interrupts.
 */
void vic_init( void )
{
/*
    kprintf( "vect_addr: %x, vect_addrs: %x, vect_cntls: %x\r\n",
	     &(lpc_vic->vect_addr),
	     &(lpc_vic->vect_addrs[0]),
	     &(lpc_vic->vect_cntls[0]) );
*/

    // Set the default interrupt handler to do nothing
    lpc_vic->def_vect_addr = vic_default;

    // Allow the LPC2106's interrupts to contribute to IRQ.
    // There are 16 LPC2106 interrupts, so allow the first 16
    // interrupts to fire.
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

    lpc_vic->int_enable = im;
    lpc_vic->int_en_clear = ~im;
}

void vic_enable_irq( int irq )
{
    // We don't have to worry about ORing, because
    //  only 1-bits have effect.
    lpc_vic->int_enable = 1 << irq;
}

void vic_disable_irq( int irq )
{
    // We don't have to worry about ORing, because
    //  only 1-bits have effect. Setting a bit to 1 in this
    //  register clears the interrupt.
    lpc_vic->int_en_clear = 1 << irq;
}

// There are 16 slots for 16 interrupts.
void vic_register_irq( vic_source_t irq, irq_handler handler )
{
    lpc_vic->vect_addrs[irq] = handler;

    // Bit 5 needs to be set to 1 to enable the interrupt. (Hex 0x20)
    // Bits 0-4 are the priority. The VIC doesn't like having 2 with the
    //  same priority, so we use the slot number.
    lpc_vic->vect_cntls[irq] = irq | 0x20;
}

irq_handler get_irq(int irq)
{
    return lpc_vic->vect_addrs[irq];
}

void vic_interrupt_handled( void )
{
    lpc_vic->vect_addr = 0;
}
