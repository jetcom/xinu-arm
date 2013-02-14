/*
 * Platform specific definitons for the:
 *
 * ARM RealView Versatile Baseboard, using the ARM926EJ-S core.
 * 
 * defined in:
 * ARM document HBI-0118
 */

#ifndef _VERSATILE_ARM926EJS_H
#define _VERSATILE_ARM926EJS_H

/* Memory-mapped location for the vectored interrupt controller. */
#define VIC_BASE_ADDRESS 0x10140000

/* UART */
#define UART0_BASE_ADDRESS 0x101F1000
#define UART1_BASE_ADDRESS 0x101F2000
#define UART2_BASE_ADDRESS 0x101F3000

#define UART0_IRQ   12
#define UART1_IRQ   13
#define UART2_IRq   14

#endif /* _VERSATILE_ARM926EJS_H */
