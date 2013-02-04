#include <device.h>
#include "interrupt.h"
#include "vic.h"

//based on code by David Welch (dwelch@dwelch.com), original license:
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//these might work
#define uint32_t unsigned int
#define int32_t int

//for I/O devices when using the physical address space (0x20000000 - 0x20FFFFFF)
#define IO_PHY_ADDR(x) (((x)&0x00FFFFFF) | 0x20000000)
//for I/O devices when using the bus address space (0x7E000000 - 0x7EFFFFFF)
#define IO_BUS_ADDR(x) (((x)&0x00FFFFFF) | 0x7E000000)

//for using I/O devices just like a global variable
#define __IO(x) (*((volatile uint32_t*)(IO_PHY_ADDR(x))))

//mini uart registers
#define AUX_ENABLES     __IO(0x20215004)
#define AUX_MU_IO_REG   __IO(0x20215040)
#define AUX_MU_IER_REG  __IO(0x20215044)
#define AUX_MU_IIR_REG  __IO(0x20215048)
#define AUX_MU_LCR_REG  __IO(0x2021504C)
#define AUX_MU_MCR_REG  __IO(0x20215050)
#define AUX_MU_LSR_REG  __IO(0x20215054)
#define AUX_MU_MSR_REG  __IO(0x20215058)
#define AUX_MU_SCRATCH  __IO(0x2021505C)
#define AUX_MU_CNTL_REG __IO(0x20215060)
#define AUX_MU_STAT_REG __IO(0x20215064)
#define AUX_MU_BAUD_REG __IO(0x20215068)

//GPIO registers
#define GPFSEL1 __IO(0x20200004)
#define GPSET0  __IO(0x2020001C)
#define GPCLR0  __IO(0x20200028)

//peripheral clock registers
#define GPPUD     __IO(0x20200094)
#define GPPUDCLK0 __IO(0x20200098)


void muart_putc(char c){
  //wait for transmission to finish
  while((AUX_MU_LSR_REG & 0x20) == 0){}
  //send char
  AUX_MU_IO_REG = c;
}

char muart_getc(void){
  char result;

  //wait for a character to come in
  while((AUX_MU_LSR_REG & 0x01) == 0){}
  //get char
  result = (AUX_MU_IO_REG & 0xFF);

  return result;
}


void uart_interrupt( void ) __attribute__((interrupt("IRQ")));

void uart_interrupt( void )
{
    irq_handled();
}


devcall uartInit (device *devptr)
{
  int i;

  //initialize UART
  AUX_ENABLES = 1;
  AUX_MU_IER_REG = 0;    //No interrupts (ERBFI, ETBEI, ELSI, EDSSI)
  AUX_MU_CNTL_REG = 0;   //pg16
  AUX_MU_LCR_REG = 3;    //not using the divisor, no break, no stick parity, even parity, no parity bit, 8 bits, 1 stop bit
  AUX_MU_MCR_REG = 0;    //diagnostics off, OUT2 off, OUT1 off, RTS off, DTR off
  AUX_MU_IER_REG = 0;    //disable interrupts again?
  AUX_MU_IIR_REG = 0xC6; 
  AUX_MU_BAUD_REG = 270; //115200 baud

  //initialize GPIO to let the UART TX through
  GPFSEL1 &= ~(7<<12);
  GPFSEL1 |= (2<<12);

  //initialize GPIO to let the UART RX through
  GPFSEL1 &= ~(7<<15);
  GPFSEL1 |= (2<<15);

  //initialize the peripheral clock
  GPPUD = 0;
  for(i=0; i<150; i++){}
  GPPUDCLK0 = (1<<14);
  for(i=0; i<150; i++){}
  GPPUDCLK0 = 0;

  //final UART initialization
  AUX_MU_CNTL_REG = 3; //3 for TX/RX, 2 for just TX

  return OK;
}

devcall uartRead( device *devptr, void *buf, uint len )
{
    int i;
    uchar *buffer = buf;
    for( i = 0; i < len; i++ )
    {
        buffer[i] = muart_getc ();
    }
    return OK;
}

devcall uartWrite( device *devptr, void *buf, uint len )
{
    int i;
    uchar *buffer = buf;
    for( i = 0; i < len; i++ )
    {
        muart_putc (*buffer);
    }
    return OK;
}

devcall uartGetc( device *devptr )
{
    uchar ch = 0;
    ch = muart_getc ();
    return ch;

}

devcall uartPutc( device *devptr, char ch )
{
    muart_putc(ch);
    return OK;
}

void uartInterrupt( void )
{
}

void serial_putc (const char c)
{
	if (c == '\n')
		muart_putc ('\r');

	muart_putc (c);
}

void serial_puts (const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

int serial_getc (void)
{
	return muart_getc();
}

int serial_tstc (void)
{
	return OK;
}

void serial_setbrg (void)
{
}
