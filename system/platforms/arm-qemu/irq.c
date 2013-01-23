#include "timer.h"
static volatile struct spc804_timer *timer0 = (struct spc804_timer *) 0x101E2000;

void idAndClearIRQ()
{
    // Hard coded for now
//    timer0->int_clr = 1;
}
