/**
 * @file platform-local.h
 *
 */

#ifndef _ARM_QEMU_PLATFORM_LOCAL_H
#define _ARM_QEMU_PLATFORM_LOCAL_H

/*
 * The fluke-arm platform has so little memory that the global default
 * of 64k for INITSTK is too big. Try something more conservativer.
 */
#define INITSTK (1337)

#endif /* _ARM_QEMU_PLATFORM_LOCAL_H */
