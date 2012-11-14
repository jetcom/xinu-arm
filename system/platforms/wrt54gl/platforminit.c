/**
 * @file platforminit.c
 * @provides platforminit.
 *
 * $Id: platforminit.c 2087 2009-10-06 23:49:39Z zlund $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <kernel.h>
#include <mips.h>
#include <platform.h>
#include <uart.h>
#include <stddef.h>
#include <string.h>

extern ulong cpuid;             /* Processor id                    */

extern struct platform platform;        /* Platform specific configuration */

/**
 * Determines and stores all platform specific information.
 * @return OK if everything is determined successfully
 */
int platforminit(void)
{
    switch (cpuid & PRID_CPU)
    {
    case PRID_CPU_BCM3302:
        strncpy(platform.family, "Broadcom 3302", PLT_STRMAX);
        switch (cpuid & PRID_REV)
        {
        case PRID_REV_WRT54G:
            strncpy(platform.name, "Linksys WRT54G", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_WRT54G);
            platform.clkfreq = CLKFREQ_WRT54G;
            platform.uart_dll = UART_DLL_WRT54G;
            break;
        case PRID_REV_WRT54GL:
            strncpy(platform.name, "Linksys WRT54GL", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_WRT54GL);
            platform.clkfreq = CLKFREQ_WRT54GL;
            platform.uart_dll = UART_DLL_WRT54GL;
            break;
        case PRID_REV_WRT350N:
            strncpy(platform.name, "Linksys WRT350N", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_WRT350N);
            platform.clkfreq = CLKFREQ_WRT350N;
            platform.uart_dll = UART_DLL_WRT350N;
            break;
        default:
            strncpy(platform.name, "Unknown Platform", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_DEFAULT);
            platform.clkfreq = CLKFREQ_DEFAULT;
            platform.uart_dll = UART_DLL_DEFAULT;
            return SYSERR;
        }
        break;
    case PRID_CPU_24K:
        strncpy(platform.family, "MIPS 24K", PLT_STRMAX);
        switch (cpuid & PRID_REV)
        {
        case PRID_REV_WRT160NL:
            strncpy(platform.name, "Linksys WRT160NL", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_WRT160NL);
            platform.clkfreq = CLKFREQ_WRT160NL;
            platform.uart_dll = (CLKFREQ_WRT160NL / 16) / UART_BAUD;
            break;
        default:
            strncpy(platform.name, "Unknown Platform", PLT_STRMAX);
            platform.maxaddr = (void *)(KSEG0_BASE | MAXADDR_DEFAULT);
            platform.clkfreq = CLKFREQ_DEFAULT;
            platform.uart_dll = UART_DLL_DEFAULT;
            return SYSERR;
        }
        break;
    }
 
/* Output Xinu memory layout */
    kprintf("%10d bytes physical memory.\r\n",
            (ulong)platform.maxaddr & 0x7FFFFFFF);
#ifdef DETAIL
    kprintf("           [0x%08X to 0x%08X]\r\n",
            (ulong)KSEG0_BASE, (ulong)(platform.maxaddr - 1));
#endif
    kprintf("%10d bytes reserved system area.\r\n",
            (ulong)_start - KSEG0_BASE);
#ifdef DETAIL
    kprintf("           [0x%08X to 0x%08X]\r\n",
            (ulong)KSEG0_BASE, (ulong)_start - 1);
#endif

    kprintf("%10d bytes Xinu code.\r\n", (ulong)&_end - (ulong)_start);
#ifdef DETAIL
    kprintf("           [0x%08X to 0x%08X]\r\n",
            (ulong)_start, (ulong)&_end - 1);
#endif

    kprintf("%10d bytes stack space.\r\n", (ulong)memheap - (ulong)&_end);
#ifdef DETAIL
    kprintf("           [0x%08X to 0x%08X]\r\n",
            (ulong)&_end, (ulong)memheap - 1);
#endif

    kprintf("%10d bytes heap space.\r\n",
            (ulong)platform.maxaddr - (ulong)memheap);
#ifdef DETAIL
    kprintf("           [0x%08X to 0x%08X]\r\n\r\n",
            (ulong)memheap, (ulong)platform.maxaddr - 1);
#endif

    return OK;
}
