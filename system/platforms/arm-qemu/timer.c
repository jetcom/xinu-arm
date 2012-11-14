/**
 * Driver for the LPC2106 clock.
 *
 * @author John Kloosterman for CS320 at Calvin College
 * @date April 26, 2012
 */

#include <stddef.h>
#include "timer.h"
#include "interrupt.h"
#include "vic.h"
#include <led.h>

// XINU interrupt handler in clkhandler.c
void clkhandler( void ) __attribute__((interrupt("IRQ")));

static volatile struct lpc_timer *timer0 = (struct lpc_timer *) 0xE0004000;
// static volatile struct lpc_timer *timer1 = (struct lpc_timer *) 0xE0008000;

/**
 * Interrupt handler that flashes the LED once a second.
 */
int ms_counter = 0;
int ledon = 0;
void timer_interrupt( void ) __attribute__((interrupt("IRQ")));
void timer_interrupt( void )
{
    ms_counter++;
    if( ms_counter >= 1000 )
    {
	if( ledon )
	    write( FRONTLED, 0, 1 );
	else
	    write( FRONTLED, 0, 0 );

	ledon = !ledon;

	ms_counter = 0;
    }

    // Handle the timer interrupt.
    timer0->interrupt = MR0_INTERRUPT;
    
    // Handle the VIC interrupt.
    irq_handled();
}

void timer_init( void )
{
    /* Double-check the struct.
    kprintf( "IR: %x, MCR: %x, CCR: %x, EMR: %x",
	     &(timer0->interrupt),
	     &(timer0->match_control),
	     &(timer0->capture_control),
	     &(timer0->external_match) );
    */

    /*
     * These values are from __ pg. 81.
     * They purport to make the timer interrupt fire every 1ms.
     */

    // This is the "VPB Divider". It isn't clear exactly what that is.
    // LPC2106 manual pg. 38
    //
    // It is necessary to set in order to know how many ticks per second
    //  the pclk does.

//    volatile uint *vpb_div = (uint *) 0xE01FC100;

    // Set pclk to 30MHz.
//    *vpb_div = 0x2;

    // This is about right, eyeballing it before we get vpb_div working.
    timer0->prescale = 1000;

    // Set the match register so that an interrupt is fired every
    //  millisecond.
    timer0->match_0 = 1;

    // Enable the interrupt on match, and reset the time counter.
    timer0->match_control = MATCH_INTERRUPT_ON_MR0 | MATCH_RESET_ON_MR0;

    // Enable timer.
    timer0->timer_control = COUNTER_ENABLE;

    // Add interrupt handler for the timer.
    register_irq( VIC_TIMER0, timer_interrupt );
    enable_irq( VIC_TIMER0 );
}

