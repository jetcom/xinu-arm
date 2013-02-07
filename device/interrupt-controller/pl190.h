/*
 * Address offsets for the pl190 Vector Interrupt Controller.
 */

#ifndef _PL190_H
#define _PL190_H

/*
 * VIC registers, and their offsets from the VIC_BASE_ADDRESS.
 */

/* Read only */
#define VIC_IRQ_STATUS  0x0
#define VIC_FIQ_STATUS  0x4
#define VIC_RAW_INTR    0x8

/* Read-write */
#define VIC_INT_SELECT  0xC
#define VIC_INT_ENABLE  0x10

/* Write-only */
#define VIC_ENABLE_AND_CLEAR    0x14

/* Read-write */
#define VIC_SOFT_INT    0x18

/* Write-only */
#define VIC_SOFT_INT_CLEAR  0x1C

/* Read-write */
#define VIC_PROTECTION  0x20
#define VIC_VEC_ADDR    0x30
#define VIC_DEF_VEC_ADDR    0x34

/* Base address for the IRQs, zero indexed */
#define VIC_VECT_ADDR_BASE  0x100

/* Base address for the vector control registers, zero indexed */
#define VIC_VECT_CNTL_BASE  0x200

#endif /* _PL190_H */
