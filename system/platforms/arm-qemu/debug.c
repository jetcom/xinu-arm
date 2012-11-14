/**
 * Functions to help debug XINU on the Fluke before getting device
 *  drivers working.
 *
 * @author
 *  John Kloosterman for CS320 at Calvin College
 * @date
 *  March 12, 2012
 */

#include "debug.h"

/*
 * Code and definitions ripped rudely from Fluke firmware code
 */

#define IODIR          (*((volatile unsigned long *) 0xE0028008))
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))
#define S_RST       (1 << 12)
#define MCLK        (1 << 4)
#define MDIN        (1 << 6)
#define LED         (1 << 17)
#define D2A_CS      (1 << 21)
#define A2D_CS      (1 << 22)
#define MCS         (1 << 23)
#define IROUT1      (1 << 13)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)
#define B_TXD       (1 << 8)
#define B_RTS       (1 << 10)

/**
 * Set up the LPC2106 I/O pins. This must be called before
 *  any LED or other I/O function.
 */
void setup_pins()
{
         IODIR = (S_RST  | MCLK   | MDIN  | D2A_CS | A2D_CS | MCS |
         IROUT1 | IROUT2 | IROUT3 | B_TXD | B_RTS);

       //This is not needed to set up pins that turn brad on
       IOSET = (D2A_CS | A2D_CS | MCS | B_TXD);
}

/*
 * LED functions
 */

/**
 * Turn the on-board LED on.
 */
void led_on( void )
{
    IOSET = LED;
}

/**
 * Turn the on-board LED off.
 */
void led_off( void )
{
    IOCLR = LED;
}

/**
 * Blink the LED on and off forever.
 */
void die( void )
{
    int i;

    for( ;; )
    {
	led_on();
	for( i = 0; i < 1000000; i++ );

	led_off();
	for( i = 0; i < 1000000; i++ );
    }
}
