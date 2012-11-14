/**
 * @file uartPutc.c
 * @provides uartPutc.
 *
 * $Id: uartPutc.c 2077 2009-09-24 23:58:54Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <uart.h>
#include <device.h>
#include "fluke-uart.h"

/**
 * Write a single character to the UART
 * @param  devptr  pointer to UART device
 * @param  ch    character to write 
 */
devcall uartPutc(device *devptr, char ch)
{
  /*  struct uart_csreg * regptr;
  regptr = (struct uart_csreg *)uarttab[devptr->minor].csr;
  while(!(regptr->lsr & UART_LSR_THRE)) 
    continue; // spin-wait until the transmit holding register is not empty

  regptr->thr = ch;
  */
  write(SERIAL1, (void *) &ch, 1);
  return OK;
  //    return uartWrite(devptr, (void *)&ch, 1);
}
