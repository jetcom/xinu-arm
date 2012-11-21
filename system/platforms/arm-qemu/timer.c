/**
 * Driver for the SP804 clock.
 *
 * @author Travis Brown
 * @date November 16, 2012
 * References:
 * http://infocenter.arm.com/help/topic/com.arm.doc.ddi0271d/DDI0271.pdf
 * http://infocenter.arm.com/help/topic/com.arm.doc.ddi0287b/DDI0287B_arm926ejs_dev_chip_technical_reference_manual.pdf
 * http://lxr.free-electrons.com/source/arch/arm/common/timer-sp.c?v=3.3#L90
 */

#include <stddef.h>
#include "timer.h"
#include "interrupt.h"
#include "vic.h"

// XINU interrupt handler in clkhandler.c
void clkhandler( void ) __attribute__((interrupt("IRQ")));

static volatile struct spc804_timer *timer0 = (struct spc804_timer *) 0x101E2000;
static volatile struct spc804_timer_version *timer_version = (struct
        spc804_timer_version *) 0x101E2FE0;

/**
 * Interrupt handler that flashes the LED once a second.
 */
void timer_interrupt( void ) __attribute__((interrupt("IRQ")));

int timerInterrupts = 0;
void timer_interrupt( void )
{
    /* TEB: This causes us to crash after the 2nd interrupt. Why?! */
    static int ms_counter = 0;
    if ( ms_counter++ >= 100  )
    {
        ms_counter = 0;
    } 
    // Handle the VIC interrupt.
    timer0->int_clr = 1;
    irq_handled();
}

void timer_init( void )
{
    int i ;
    /* Double-check the struct.*/
    /*kprintf( "load: %x, value: %x, ctrl: %x\n",
	     &(timer0->load),
	     &(timer0->value),
	     &(timer0->ctrl));*/

    /*
    for ( i = 0; i < 4; i++ )
    {
        kprintf("peripheralID[%d]: %02x\n", i, timer_version->peripheralID[i]
                % 0xff);
    }*/
    disable_irq( VIC_TIMER0 );
    timer0->ctrl &= ~TIMER_ENABLE;

    // Need to set pclk
    timer0->load = 60000;

    timer0->ctrl = ( TIMER_SIZE_MSK | TIMER_INT_EN | TIMER_MODE_PD );
    //timer0->ctrl |= TIMER_PRS_MSK & (3 << 3);

    register_irq( VIC_TIMER0, clkhandler );
    timer0->ctrl |= ( TIMER_ENABLE );
    enable_irq( VIC_TIMER0 );
}
