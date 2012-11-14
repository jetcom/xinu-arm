#include "interrupt.h"
#include "debug.h"
#include <conf.h>
#include <device.h>
#include <lpc210x.h>
#include <stdio.h>
#include <uart.h>
#include "../../../device/uart-fluke-bluetooth/fluke-uart.h"
#include "../../../device/uart-fluke-bluetooth/power.h"
#include "../../../device/uart-fluke-bluetooth/uart.h"

/* Prototypes for debug Bluetooth functions, defined in
   device/uart-fluke-bluetooth/kprintf.c
*/
void kinitputc( void );
void ksimpleterminal( void );
extern void usleep(int microseconds);

extern void *memheap;	/* declared in initialize.c */
extern void *_bss_end;   /* declared by the loader */
void _startup( void )
{
  int i;
#if NDEVS && SERIAL1
    struct uart_csreg *uart1_regptr;
#endif

    /*
     * We need to cheat here and run some code to ensure that
     * kprintf() can work before calling nulluser().
     */
    setup_pins();

    /* SERIAL1 is the bluetooth device our kprintf() uses. */
#if NDEVS && SERIAL1
    /*
     * Platform initialization of bluetooth for our kprintf() over
     * bluetooth to work (over bluetooth).
     */

    /* setup Pin Function Select Register (Pin Connect Block) make
     * sure old values of Bits 0-4 are masked out and set them
     * according to UART1-Pin-Selection.
     */
    PINSEL0 = (PINSEL0 & ~UART1_PINMASK) | UART1_PINSEL;
    /* turn on CTS */
    PINSEL0 = (PINSEL0 & ~UART1_CTS_PINMASK) | UART1_CTS_PINSEL;

    /* Actually configure the UART1's registers */
    uart1_regptr = devtab[SERIAL1].csr;
    fluke_uart_reg_init(uart1_regptr, 38400);

    /*
     * kprintf() needs to be informed of the CSR, it uses uarttab
     * instead of devtab to get it for unknown reason.
     */
    uarttab[devtab[SERIAL1].minor].csr = uart1_regptr;

    /* magic required to get the bluetooth to work */
    usleep(100000);
    for(i = 0; i< 512; i++)
        kputc((device *)&devtab[SERIAL1], i);

   usleep(100000);
   set_bluetooth(255);

   usleep(1000);
#endif /* NDEVS && SERIAL1 */

    nulluser();
}

void halt(void) {}
