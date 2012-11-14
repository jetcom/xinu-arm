
#include <uart.h>
#include "uart.h"  // defining pinsel stuff
#include "fluke-uart.h" 
#include <lpc210x.h> // constants
#include <stdint.h>

// stuff included stolen from uartInit.c in ns16550
#include <stddef.h>
#include <platform.h>
#include <interrupt.h>
#include <device.h>
#include <stdlib.h>

#define B_RTS (1 << 10) 
// from fluke.h

struct uart uarttab[NUART];   // = 2 for the fluke

/*    baudrate divisor - use UART_BAUD macro
 *    mode - see typical modes (uart.h)
 *    fmode - see typical fmodes (uart.h)
 *    NOTE: uart1Init(UART_BAUD(9600), UART_8N1, UART_FIFO_8); 
 */

devcall uartInit(device * devptr)
{
  //  uint8_t mode, fmode; // delete this eventually
  struct uart *uartptr;
  struct uart_csreg *regptr;

  register_irq(7/*IRQ_NUMBER*/, uartInterrupt);

  //UART1_IER = 0x00;             // disable all interrupts
  //UART1_IIR = 0x00;             // clear interrupt ID register
  //UART1_LSR = 0x00;             // clear line status register

  // set the baudrate - DLAB must be set to access DLL/DLM
  //  UART1_LCR = (1<<UART1_LCR_DLAB); // set divisor latches (DLAB)
  //  UART1_DLL = (uint8_t)baud;         // set for baud low byte
  //  UART1_DLM = (uint8_t)(baud >> 8);  // set for baud high byte
  
  // set the number of characters and other
  // user specified operating parameters
  // Databits, Parity, Stopbits - Settings in Line Control Register
  //UART1_LCR = (mode & ~(1<<UART1_LCR_DLAB)); // clear DLAB "on-the-fly"
  // setup FIFO Control Register (fifo-enabled + xx trig) 
  //UART1_FCR = fmode;

      /* Initialize structure pointers */
    uartptr = &uarttab[devptr->minor];
    uartptr->dev = devptr;
    uartptr->csr = devptr->csr;
    regptr = (struct uart_csreg *)uartptr->csr;

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

    /* OUT2 is used to control the board's interrupt tri-state        */
    /* buffer. It should be set high to generate interrupts properly. */
    //    regptr->mcr = UART_MCR_OUT2;        /* Turn on user-defined OUT2.   */

    
    /* Enable UART FIFOs, clear and set interrupt trigger level       */
    //    regptr->fcr = UART_FCR_EFIFO | UART_FCR_RRESET
    //   | UART_FCR_TRESET | UART_FCR_TRIG2;

    /*
     * Only initialize the device's registers if they have not already
     * been initialized. Bluetooth is a platform-level device,
     * initialized in fluke-specific _startup() because its
     * functioning is required by kprintf().
     */
    if (devtab[SERIAL1].csr != devptr->csr)
      fluke_uart_reg_init(devptr->csr, 38400);

    /* Enable processor handling of UART interrupt requests */
    // INTERRUPT STUFF here.. uncomment when that is working....
    //    register_irq(devptr->irq, devptr->intr);
    enable_irq(devptr->irq);

    return OK;  
}

void fluke_uart_reg_init(struct uart_csreg *uart_regptr, uint16_t baud)
{
    /*
     * Enable interrupts (but they're ignored until we enable() them).
     */
    uart_regptr->ier = 0x03;//UART_IER_ERBFI | UART_IER_ETBEI | UART_IER_ELSI;
    uart_regptr->iir = 0;
    uart_regptr->lsr = 0;

    /* Set baud rate */
    /// LCR IS MESSED UP
    uart_regptr->lcr = 0;//(1<<UART_LCR_DLAB);        /* Set Divisor Latch Access Bit */
    // DO WORK HERE!!! Make sure BAUD is set right
    uart_regptr->dll = baud;//platform.uart_dll;    /* Set Divisor Latch Low Byte   */
    uart_regptr->dlm = baud >> 8;//0x00;         /* Set Divisor Latch High Byte  */

    uart_regptr->lcr = UART_8N1 & ~UART_LCR_DLAB; /* 8 bit, No Parity, 1 Stop     */
    uart_regptr->fcr = UART_FIFO_8;//0x00;         /* Disable FIFO for now         */
}
