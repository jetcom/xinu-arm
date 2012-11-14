/* conf.c (GENERATED FILE; DO NOT EDIT) */

#include <conf.h>
#include <device.h>

#include <uart.h>
#include <led.h>

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
	  (void *)0xe000c000, (void *)uartInterrupt, 6 },

/* SERIAL1 is uart */
	{ 1, 1, "SERIAL1",
	  (void *)uartInit, (void *)ionull, (void *)ionull,
	  (void *)uartRead, (void *)uartWrite, (void *)ioerr,
	  (void *)uartGetc, (void *)uartPutc, (void *)ionull,
	  (void *)0x101f1000, (void *)uartInterrupt, 7 },

/* FRONTLED is led */
	{ 2, 0, "FRONTLED",
	  (void *)ledInit, (void *)ionull, (void *)ionull,
	  (void *)ionull, (void *)ledWrite, (void *)ioerr,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)0xe0028004, (void *)ioerr, 0 },

/* BACKLED is led */
	{ 3, 1, "BACKLED",
	  (void *)ledInit, (void *)ionull, (void *)ionull,
	  (void *)ionull, (void *)ledWrite, (void *)ioerr,
	  (void *)ionull, (void *)ionull, (void *)ioerr,
	  (void *)0xe0028004, (void *)ioerr, 0 }
};
