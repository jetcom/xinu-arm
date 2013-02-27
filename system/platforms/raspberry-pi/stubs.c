#include "interrupt.h"
#include <conf.h>
#include <device.h>
#include <stdio.h>
#include <uart.h>

extern void *memheap;	/* declared in initialize.c */
extern void *_bss_end;   /* declared by the loader */

void _startup( void )
{
    nulluser();
}
