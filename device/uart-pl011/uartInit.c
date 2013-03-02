/**
 * @file uartInit.c
 * @provides uartInit.
 *
 * $Id: uartInit.c 2102 2009-10-26 20:36:13Z brylow $
 */
/* Embedded Xinu, Copyright (C) 2009.  All rights reserved. */

#include <uart.h>
#include "pl011.h"
#include <stddef.h>
#include <platform.h>
#include <interrupt.h>
#include <device.h>
#include <stdlib.h>

struct uart uarttab[NUART];

/**
 * Initialize UART control and status registers and buffers.
 * @param devptr pointer to a uart device
 */
devcall uartInit(device *devptr)
{
    //a pointer to the uart
    struct uart *uartptr;
    //a pointer to the uart's registers
    struct uart_csreg *regptr;

    /* Initialize structure pointers */
    uartptr = &uarttab[devptr->minor]; //get a pointer to the uarttab entry for this UART
    uartptr->dev = devptr; //set its device pointer to the one supplied as an argument
    uartptr->csr = devptr->csr; //copy over the register pointer from the device supplied as an argument
    regptr = (struct uart_csreg *)uartptr->csr; //for convenience, get our own register pointer

    /* Initialize statistical counts */
    uartptr->cout = 0;
    uartptr->cin = 0;
    uartptr->lserr = 0;
    uartptr->ovrrn = 0;
    uartptr->iirq = 0;
    uartptr->oirq = 0;

    /* Initialize input buffer */
    uartptr->isema = semcreate(0);
    uartptr->iflags = 0;
    uartptr->istart = 0;
    uartptr->icount = 0;

    /* Initialize output buffer */
    uartptr->osema = semcreate(UART_OBLEN);
    uartptr->oflags = 0;
    uartptr->ostart = 0;
    uartptr->ocount = 0;
    uartptr->oidle = 1;

    /* Wait for the UART to stop transmitting or receiving */
    while(regptr->fr & PL011_FR_BUSY){}

    /* Disable the UART before configuring it */
    regptr->cr = 0;

    /* Flush the transmit FIFO */
    regptr->lcrh &= ~(PL011_LCRH_FEN);

    /* Clear pending interrupts */
    regptr->icr = (PL011_ICR_OEIC |
                   PL011_ICR_BEIC |
                   PL011_ICR_PEIC |
                   PL011_ICR_FEIC |
                   PL011_ICR_RTIC |
                   PL011_ICR_TXIC |
                   PL011_ICR_RXIC |
                   PL011_ICR_DSRMIC |
                   PL011_ICR_DCDMIC |
                   PL011_ICR_CTSMIC |
                   PL011_ICR_RIMIC);

    /* Set baud rate */
    regptr->ibrd = PL011_BAUD_INT(115200);
    regptr->fbrd = PL011_BAUD_FRAC(115200);

    /* 8 bit, No Parity, 1 Stop, Disable FIFOs*/
    regptr->lcrh = (PL011_LCRH_WLEN_8BIT);

    /* Enable interrupts */
    regptr->imsc = (PL011_IMSC_TXIM | PL011_IMSC_RXIM);

    /* Now that we're done configureing, enable UART */
    regptr->cr = ((PL011_CR_RXE) | (PL011_CR_TXE) | (PL011_CR_UARTEN));

    /* Enable processor handling of UART interrupt requests */
    register_irq( devptr->irq, devptr->intr );
    enable_irq(devptr->irq);

    return OK;
}
