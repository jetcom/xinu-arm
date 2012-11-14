#ifndef _VIC_H_
#define _VIC_H_

#include <interrupt.h>

// VIC interrupt sources for the LPC210(4-6)
typedef enum
{
    VIC_WDT         = 0,
    VIC_SW          = 1,
    VIC_DEBUG_RX    = 2,
    VIC_DEBUG_TX    = 3,
    VIC_TIMER0      = 4,
    VIC_TIMER1      = 5,
    VIC_UART0       = 6,
    VIC_UART1       = 7,
    VIC_PWM0        = 8,
    VIC_I2C         = 9,
    VIC_SPI         = 10,
    // 11 is reserved
    VIC_PLL         = 12,
    VIC_RTC         = 13,
    VIC_EINT0       = 14,
    VIC_EINT1       = 15,
    VIC_EINT2       = 16
} vic_source_t;

/* Configures the VIC and enables interrupts. */
void vic_init(void);
irqmask vic_get_irqmask( void );
void vic_set_irqmask( irqmask im );
void vic_enable_irq( int irq );
void vic_disable_irq( int irq );
void vic_register_irq( vic_source_t irq, irq_handler handler );
void vic_interrupt_handled( void );

/**
 * Encodes whether interupts are enabled or not into
 *  an irq mask.
 *
 * Bits 0-15: the actual interrupt mask
 * Bit 16: whether interrupts are enabled or not.
 *
 * @param interrupts_enabled
 *   nonzero if interrupts are enabled, zero otherwise
 * @param irqmask
 *   An irq mask.
 */
#define INTERRUPTS_ENABLED 1
#define INTERRUPTS_DISABLED 0
#define IRQMASK_ENABLED_BIT (0x10000)
static inline irqmask irqmask_pack( int interrupts_enabled, irqmask mask )
{
    irqmask true_mask = mask & 0xffff;

    if( interrupts_enabled )
	return true_mask | IRQMASK_ENABLED_BIT;
    else
	return true_mask;
}

/**
 * Return TRUE if the given irqmask specifies that interrupts
 *  were enabled.
 */
static inline int irqmask_interrupts_enabled( irqmask mask )
{
    return mask & IRQMASK_ENABLED_BIT;
}

/**
 * Enables interrupts by unsetting the I_BIT.
 *
 * @return nonzero if interrupts were disabled, 
 *   zero if interrupts were enabled.
 */
static inline int vic_enable_interrupts( void )
{
    int ret;
    asm("mrs r0, cpsr; and %[ret], r0, #0x80; bic r0, r0, #0x80; msr cpsr, r0"
	: [ret]"=r" (ret) 
	: 
	: "r0");

    return ret;
}

/**
 * Disabled interrupts by setting I_BIT.
 *
 * @return nonzero if interrupts were disabled, 
 *    zero if interrupts were enabled.
 */
static inline int vic_disable_interrupts( void )
{
    int ret;
    asm("mrs r0, cpsr; and %[ret], r0, #0x80; orr r0, r0, #0x80; msr cpsr, r0" 
	: [ret]"=r" (ret) 
	: 
	: "r0");

    return ret;
}

/**
 * Enquire whether interrupts are enabled or not.
 *
 * @return zero if interrupts were disabled, 
 *    nonzero if interrupts were enabled.
 */
static inline int vic_interrupts_enabled( void )
{
    int ret;

    asm("mrs r0, cpsr; and %[ret], r0, #0x80;" 
	: [ret]"=r" (ret) 
	: 
	: "r0");

    return !ret;
}

#endif /* _VIC_H_ */
