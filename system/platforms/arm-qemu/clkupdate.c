#include "stddef.h"
#include "timer.h"
#include "interrupt.h"
#include "vic.h"
#include "conf.h"

static volatile struct spc804_timer *timer0 = (struct spc804_timer *) 0x101E2000;
static volatile struct spc804_timer_version *timer_version = (struct
        spc804_timer_version *) 0x101E2FE0;

void clkupdate( ulong cycles )
{
   static bool initialized = FALSE;
   if ( !initialized ) 
   {
       initialized = TRUE;
   }
   else
   {
       return;
   }


   //disable our out interrupt vector while we work on the registers
   disable_irq( IRQ_TIMER );

   //disable the timer
   timer0->ctrl &= ~TIMER_ENABLE;

   // Need to set pclk
   //timer0->load = 20000;

   //set up the counter
   timer0->load = cycles;

   //divide clock source by 16, enable interrupts, periodic mode
   timer0->ctrl = ( TIMER_SIZE_MSK | TIMER_INT_EN | TIMER_MODE_PD );

   //enable the timer
   timer0->ctrl |= ( TIMER_ENABLE );

   // Registration should have already happened in clkinit, just enable our interrupt vector
   enable_irq( IRQ_TIMER );

   //timer0->ctrl |= TIMER_PRS_MSK & (3 << 3);
   //register_irq( VIC_TIMER0, clkhandler );
   //    register_irq( VIC_TIMER0, timer_interrupt );
   //enable_irq( VIC_TIMER0 );
}

