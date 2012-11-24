#ifndef _VIC_H_
#define _VIC_H_

#include <interrupt.h>
#include <stdint.h>

volatile static struct vic *lpc_vic = (struct vic *) 0x10140000;

// VIC interrupt sources for the LPC210(4-6)
typedef enum
{
    VIC_WDT         = 0,
    VIC_SW          = 1,
    VIC_DEBUG_RX    = 2,
    VIC_DEBUG_TX    = 3,
    VIC_TIMER0      = 4,
    VIC_TIMER1      = 5,
    VIC_GPIO0       = 6,
    VIC_GPIO1       = 7,
    VIC_GPIO2       = 8,
    VIC_GPIO3       = 9,
    VIC_RTC         = 10,
    VIC_SSP         = 11, // Synchronous Serial Port
    VIC_UART0       = 12,
    VIC_UART1       = 13,
    VIC_UART2       = 14,
    VIC_SCI         = 15, // Smart Card Interface
#if 0
    VIC_CLCD        = 16, // CLCD controller
    VIC_DMA         = 17,
    VIC_PWRFAIL     = 18, // Power failure
    VIC_MBX         = 19, // Graphics processor
    VIC_GND         = 20, // reserved
    // External Interrupt signals from logic tiles or secondary controller 

    VIC_SRC21       = 21, // Disk on chip
    VIC_SRC22       = 22, // MCI0A
    VIC_SRC23       = 23, // MCI1A
    VIC_SRC24       = 24, // AACI
    VIC_SRC25       = 25, // Ethernet
    VIC_SRC26       = 26, // USB
    VIC_SRC27       = 27, // PCI 0
    VIC_SRC28       = 28, // PCI 1
    VIC_SRC29       = 29, // PCI 2
    VIC_SRC30       = 30, // PCI 3
    VIC_SRC31       = 31, // SIC source


    // 11 is reserved
    VIC_EINT1       = 15,
    VIC_EINT2       = 16
#endif
} vic_source_t;

struct vic
{
    uint32_t irq_status;            // 0x000
    uint32_t fiq_status;            // 0x004
    uint32_t raw_intr;              // 0x008
    uint32_t int_select;            // 0x00C
    uint32_t int_enable;            // 0x010
    uint32_t int_en_clear;          // 0x014
    uint32_t soft_int;              // 0x018
    uint32_t soft_int_clear;        // 0x01C
    uint32_t protection;            // 0x020
    uint32_t reserved_0[0x3];       // 0x3 = 0xC / 4 bytes per word
    uint32_t pl190_vect_addr;       // 0x030
    uint32_t pl190_def_vect_addr;   // 0x034

    uint32_t reserved_1[0x32];      // 0x32 = 0xC8 / 4 bytes per word

    void *   vect_addrs[32];        // 0x100
    uint32_t reserved_2[0x20];      

    uint32_t vect_cntls[32];        // 0x200 
    uint32_t reserved_3[0x20];      

    uint32_t vect_itcr;             // 0x300
    uint32_t vect_itip1;            // 0x304
    uint32_t vect_itip2;            // 0x308
    uint32_t vect_itop1;            // 0x30C
    uint32_t vect_itop2;            // 0x310

    uint32_t reserved_4[0x2FB];     // 0x2FB = 0xBEC / 4 bytes per word
    uint32_t pl192_def_vect_addr;   // 0xF00

    uint32_t reserved_5[0x37];      // 0x37 = 0xDC / 4 bytes per word

    uint32_t peripheralID[4];       // 0xFE0
    uint32_t primeCellID[4];        // 0xFF0
};

/* Configures the VIC and enables interrupts. */
void vic_init(void);
irqmask vic_get_irqmask( void );
void vic_set_irqmask( irqmask im );
void vic_enable_irq( int irq );
void vic_disable_irq( int irq );
void vic_register_irq( vic_source_t irq, irq_handler handler );
void vic_interrupt_handled( void );
int vic_in_interrupt( void );

/**
 * Encodes whether interupts are enabled or not into
 *  an irq mask.
 *
 * Bits 0-31: the actual interrupt mask
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

    if ( interrupts_enabled )
    {
        return true_mask | IRQMASK_ENABLED_BIT;
    }
    else
    {
        return true_mask;
    }
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


    // Check if interrupts are already enabled. If so, return 0

    asm("mrs r0, cpsr;"
        "and %[ret], r0, #0x80;"
        "bic r0, r0, #0x80;"
        "msr cpsr_c, r0" 
         : [ret]"=r" (ret) : : "r0");

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
/*    lpc_vic->int_select = 0;
    lpc_vic->int_enable = 0;
    lpc_vic->int_en_clear = ~0;
    lpc_vic->vect_itcr = 0;
    lpc_vic->soft_int_clear = ~0;*/
    int ret;
    asm("mrs r0, cpsr; "
        "and %[ret], r0, #0x80;"
        "orr r0, r0, #0x80;" 
        "msr cpsr_c, r0" 
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

    asm("mrs r0, cpsr;"
        "and %[ret], r0, #0x80;" 
	: [ret]"=r" (ret) 
	: 
	: "r0");

    return !ret;
}

#endif /* _VIC_H_ */
