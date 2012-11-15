/* conf.c (GENERATED FILE; DO NOT EDIT) */

#include <conf.h>
#include <device.h>

#include <loopback.h>
#include <null.h>
#include <uart.h>
#include <tty.h>

extern devcall ioerr(void);
extern devcall ionull(void);

/* device independent I/O switch */

const device devtab[NDEVS] =
{
/**
 * Format of entries is:
 * dev-number, minor-number, dev-name,
 * init, open, close,
 * read, write, seek,
 * getc, putc, control,
 * dev-csr-address, intr-handler, irq
 */

/* SERIAL0 is uart */
	{ 0, 0, "SERIAL0",
	  (void *)uartInit, (void *)ionull, (void *)ionull,
	  (void *)uartRead, (void *)uartWrite, (void *)ioerr,
	  (void *)uartGetc, (void *)uartPutc, (void *)ionull,
	  (void *)0x101f1000, (void *)uartInterrupt, 6 },

/* SERIAL1 is uart */
	{ 1, 1, "SERIAL1",
	  (void *)uartInit, (void *)ionull, (void *)ionull,
	  (void *)uartRead, (void *)uartWrite, (void *)ioerr,
	  (void *)uartGetc, (void *)uartPutc, (void *)ionull,
	  (void *)0x101f2000, (void *)uartInterrupt, 7 },

/* DEVNULL is null */
	{ 2, 0, "DEVNULL",
	  (void *)ionull, (void *)ionull, (void *)ionull,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)0x0, (void *)ioerr, 0 },

/* LOOP is loopback */
	{ 3, 0, "LOOP",
	  (void *)loopbackInit, (void *)loopbackOpen, (void *)loopbackClose,
	  (void *)loopbackRead, (void *)loopbackWrite, (void *)ioerr,
	  (void *)loopbackGetc, (void *)loopbackPutc, (void *)loopbackControl,
	  (void *)0x0, (void *)ioerr, 0 },

/* TTYLOOP is tty */
	{ 4, 0, "TTYLOOP",
	  (void *)ttyInit, (void *)ttyOpen, (void *)ttyClose,
	  (void *)ttyRead, (void *)ttyWrite, (void *)ioerr,
	  (void *)ttyGetc, (void *)ttyPutc, (void *)ttyControl,
	  (void *)0x0, (void *)ioerr, 0 },

/* CONSOLE is tty */
	{ 5, 1, "CONSOLE",
	  (void *)ttyInit, (void *)ttyOpen, (void *)ttyClose,
	  (void *)ttyRead, (void *)ttyWrite, (void *)ioerr,
	  (void *)ttyGetc, (void *)ttyPutc, (void *)ttyControl,
	  (void *)0x0, (void *)ioerr, 0 }
};
