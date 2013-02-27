#include "bcm2835.h"
#include "stddef.h"
#include "interrupt.h"
#include "vic.h"
#include "conf.h"

void clkupdate( ulong cycles )
{
   static bool initialized = FALSE;

   //disable our interrupt vector while we work on the registers
   disable_irq( IRQ_TIMER );

   //clear/ack the interrupt
   TIMER_CS |= (1<<TIMER_CS_M1);

   //if we've never done initialization before
   if( initialized == FALSE )
   {
       //initialize the timer compare
       TIMER_C1 = TIMER_CLO + cycles;
       //ok, we've done the initialization
       initialized = TRUE;
   }
   //if we have done initialization before
   else
   {
       //advance the timer comparison register to the next time we want an interrupt
       TIMER_C1 += cycles;
   }

   // Registration should have already happened in clkinit, just enable our interrupt vector
   enable_irq( IRQ_TIMER );
}

