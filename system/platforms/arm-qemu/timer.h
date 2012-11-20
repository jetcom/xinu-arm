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

struct spc804_timer
{
    uint32_t  load;
    uint32_t  value;
    uint32_t  ctrl;
    uint32_t  int_clr;
    uint32_t  ris;
    uint32_t  mis;
    uint32_t  bgload;
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
