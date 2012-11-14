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
#include "uart.h"
#include "power.h"
#include "usleep.h"
#include "fluke-uart.h"

void led_on( void );
void led_off( void );

void kinitputc( void )
{
  /*    int i;

    usleep( 100000 );
    uart1Init(B460800, UART_8N1, UART_FIFO_8);

    for (i = 1; i < 512; i++)
    {
	uart1Putch(i);
    }

    set_bluetooth( 255 );

  */
}

/**
 * perform a synchronous character write to a serial port
 * @param *devptr pointer to device on which to write character
 * @param c character to write
 * @return c on success, SYSERR on failure
 */
syscall kputc(device *devptr, uchar c)
{
  //return putc(SERIAL1, c); // just print it to the serial bluetooth connection for now
  //return uart1PutchCTS( c );
  struct uart_csreg * regptr;
  regptr = (struct uart_csreg *)uarttab[devptr->minor].csr;
  while(!(regptr->lsr & UART_LSR_THRE)) 
    continue; // spin-wait until the transmit holding register is not empty

  regptr->thr = c;
  

}

/**
 * perform a synchronous kernel read from a serial device
 * @param *devptr pointer to device on which to write character
 * @return character read on success, SYSERR on failure
 */
syscall kgetc(device *devptr)
{
  int c;
  c = getc(SERIAL1);
  if( c == -1) 
    return SYSERR;
  else
    return c;
  /*  
  int c;

    c = uart1GetchRTS();

    if( c == -1 )
	return SYSERR;
    else
	return c;
  */
}

/**
 * Create a debug terminal for testing Bluetooth.
 */
void ksimpleterminal( void )
{
    
int c;

    led_on();

    for( ;; )
    {	
	c = kgetc( (void *)0 );

	if( c != SYSERR )
	    kputc( (void *)0, c );
	led_off();
	if( c == 'q' )
	  break;


    }
  
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
    _doprnt(fmt, ap, (int (*)(int, int))kputc, (int)&devtab[SERIAL1]);
    va_end(ap);
  
    return OK;
}
