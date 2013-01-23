/**
 * Timer control structure.
 *
 * See 
 *
 * @author Travis Brown
 * @date April , 2012
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <stddef.h>
#include <stdint.h>

void timer_reset_interrupt(); 

struct spc804_timer
{
    //see 3-2 (page 34) of the ARM Dual-Timer Module (SP804) Technical Reference Manual
    uint32_t  load;     //the initial value, writing to this also sets value
    uint32_t  value;    //the current value
    uint32_t  ctrl;     //controls operation mode (be sure to disable the timer first before changing!!!)
                        //  bits, default value first:
                        //    bit 7: disable (0), enable (1)
                        //    bit 6: free-running (0), periodic (1)
                        //    bit 5: interrupt enabled (1), disabled (0)
                        //    bits 3-2: divide by 1 (0), divide by 16 (1), divide by 256 (2)
                        //    bit 1: 16bit counter (0), 32bit counter (1)
                        //    bit 0: wrapping counter (0), oneshot (1)
    uint32_t  int_clr;  //clears interrupt output when written to
    uint32_t  ris;      //Raw Interrupt Status (should be 1 or 0)
    uint32_t  mis;      //ris & (bit 5 of ctrl)
    uint32_t  bgload;   //like load above, but doesn't restart the timer
};

struct spc804_timer_version
{
    uint32_t  peripheralID[4];
    uint32_t  cellID[4];
};

#define TIMER_ENABLE    (1 << 7)
#define TIMER_MODE_MSK  (1 << 6)
#define TIMER_MODE_FR   (0 << 6)
#define TIMER_MODE_PD   (1 << 6)

#define TIMER_INT_EN    (1 << 5)
#define TIMER_PRS_MSK   (3 << 2)
#define TIMER_PRS_8S    (1 << 3)
#define TIMER_SIZE_MSK  (1 << 2)
#define TIMER_ONE_SHT   (1 << 0)


#endif /* _TIMER_H */
