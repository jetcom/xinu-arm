/**
 * @file kprintf.c
 * @provides kputc, kprintf.
 *
 * $Id: kprintf.c 2108 2009-10-29 05:07:39Z brylow $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <stdarg.h>
#include <device.h>
#include <stdio.h>
#include <uart.h>
#include "pl011.h"

/**
 * perform a synchronous character write to a serial port
 * @param *devptr pointer to device on which to write character
 * @param c character to write
 * @return c on success, SYSERR on failure
 */
syscall kputc(device *devptr, uchar c)
{
    int status, irmask;
    volatile struct uart_csreg *regptr;
    struct uart *uartptr;

    //get a pointer to the UART's registers
    regptr = (struct uart_csreg *)devptr->csr;
    //get the UART's device pointer
    uartptr = &uarttab[devptr->minor];

    irmask = regptr->imsc;      /* Save UART interrupt state.   */
    regptr->imsc = 0;           /* Disable UART interrupts.     */

    do                          /* Wait for transmitter to finish */
    {
        status = regptr->fr;
    }
    while ((status & PL011_FR_TXFF) != 0);

    /* Send character. */
    regptr->dr = c;
    uartptr->cout++;

    regptr->imsc = irmask;      /* Restore UART interrupts.     */
    return c;
}

/**
 * perform a synchronous kernel read from a serial device
 * @param *devptr pointer to device on which to write character
 * @return character read on success, SYSERR on failure
 */
syscall kgetc(device *devptr)
{
    int irmask;
    volatile struct uart_csreg *regptr;
    uchar c;

    //get a pointer to the UART's registers?
    regptr = (struct uart_csreg *)devptr->csr;

    irmask = regptr->imsc;      /* Save UART interrupt state.   */
    regptr->imsc = 0;           /* Disable UART interrupts.     */

    while (0 != (regptr->fr & PL011_FR_RXFE))
    {                           /* Do Nothing */
    }

    /* read character from Receive Holding Register */
    c = regptr->dr;

    regptr->imsc = irmask;      /* Restore UART interrupts.     */
    return c;
}

/**
 * kernel printf: formatted, unbuffered output to SERIAL0
 * @param *fmt pointer to string being printed
 * @return OK on success
 */
syscall kprintf(char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    _doprnt(fmt, ap, (int (*)(int, int))kputc, (int)&devtab[SERIAL0]);
    va_end(ap);
    return OK;
}
