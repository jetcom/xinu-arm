/**
 * @file platform.h
 * @modified by Andrew Webster
 *
 * $Id: platform.h 2086 2009-10-06 22:24:27Z brylow $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stddef.h>
#include <platform-local.h>

#define PLT_STRMAX 18
/**
 * Various platform specific settings
 */
struct platform
{
    char name[PLT_STRMAX];
    char family[PLT_STRMAX];
    void *maxaddr;
    ulong clkfreq;
    uchar uart_dll;
    uchar uart_irqnum;
};

extern struct platform platform;

#endif                          /* _PLATFORM_H_ */
