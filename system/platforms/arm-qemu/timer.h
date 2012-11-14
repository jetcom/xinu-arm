/**
 * Timer control structure.
 *
 * See LPC2106 manual pg. 135.
 *
 * @author John Kloosterman for CS320 at Calvin College
 * @date April 23, 2012
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <stddef.h>

struct lpc_timer
{
    uint interrupt;        // IR
    uint timer_control;    // TCR
    uint timer_counter;    // TC
    uint prescale;         // PR
    uint prescale_counter; // PC
    uint match_control;    // MCR
    uint match_0;          // MR0
    uint match_1;          // MR1
    uint match_2;          // MR2
    uint match_3;          // MR3
    uint capture_control;  // CCR
    uint capture_0;        // CR0
    uint capture_1;        // CR1
    uint capture_2;        // CR2
    uint capture_3;        // CR3
    uint external_match;   // EMR
};

/* Bits in the interrupt register */
#define MR0_INTERRUPT          (1)
#define MR1_INTERRUPT          (1 << 1)
#define MR2_INTERRUPT          (1 << 2)
#define MR3_INTERRUPT          (1 << 3)
#define CR0_INTERRUPT          (1 << 4)
#define CR1_INTERRUPT          (1 << 5)
#define CR2_INTERRUPT          (1 << 6)
#define CR3_INTERRUPT          (1 << 7)

/* Bits in the timer control register */
#define COUNTER_ENABLE         (1)
#define COUNTER_RESET          (1 << 1)

/* Bits in the match control register */
#define MATCH_INTERRUPT_ON_MR0 (1)
#define MATCH_RESET_ON_MR0     (1 << 1)
#define MATCH_STOP_ON_MR0      (1 << 2)
#define MATCH_INTERRUPT_ON_MR1 (1 << 3)
#define MATCH_RESET_ON_MR1     (1 << 4)
#define MATCH_STOP_ON_MR1      (1 << 5)
#define MATCH_INTERRUPT_ON_MR2 (1 << 6)
#define MATCH_RESET_ON_MR2     (1 << 7)
#define MATCH_STOP_ON_MR2      (1 << 8)
#define MATCH_INTERRUPT_ON_MR3 (1 << 9)
#define MATCH_RESET_ON_MR3     (1 << 10)
#define MATCH_STOP_ON_MR3      (1 << 11)


#endif /* _TIMER_H */
