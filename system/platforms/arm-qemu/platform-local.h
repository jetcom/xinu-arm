/**
 * @file platform-local.h
 *
 */

#ifndef _ARM_QEMU_PLATFORM_LOCAL_H
#define _ARM_QEMU_PLATFORM_LOCAL_H

/* Memory-mapped location for the vectored interrupt controller. */
#define VIC_BASE_ADDRESS 0x10140000

/* In some versions of QEMU, the VIC has an off-by-one error and gives us a
 * null ISR. This was fixed in September, 2012, so not all systems have
 * upgraded to a version with the fix.
 */
#define QEMU_VIC_WORKAROUND 1

#endif /* _ARM_QEMU_PLATFORM_LOCAL_H */
