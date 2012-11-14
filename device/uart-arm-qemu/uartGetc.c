/**
 * @file uartGetc.c
 * @provides uartGetc.
 *
 * $Id: uartGetc.c 2077 2009-09-24 23:58:54Z mschul $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <stddef.h>
#include <uart.h>
#include <device.h>
#include "qemu-uart.h"
#include "qemu.h"
/**
 * Read a single character from UART.
 * @param pdev pointer to UART device
 */

#define ULSR_RDR (1 << 0) 

void uart1_set_rts(void)
{
  //UART1_MCR |= UMCR_RTS;
  IOCLR = B_RTS;
}

void uart1_clear_rts(void)
{
  //UART1_MCR &= ~UMCR_RTS;
  IOSET = B_RTS;
}


devcall uartGetc(device *devptr)
{
  /*    uchar ch = 0;
    struct uart_csreg *regptr;
    regptr = (struct uart_csreg *)uarttab[devptr->minor].csr;

    if (regptr->lsr & ULSR_RDR)                 // check if character is available
      return regptr->buffer;//UART_RBR;                       // return character

    return SYSERR;
  */

  uart1_set_rts();

  // check if character is available
  if (UART1_LSR & ULSR_RDR)
    {
      uart1_clear_rts();
      // return character
      return UART1_RBR;   
    }
  
  
  uart1_clear_rts();  
  return -1;

}
