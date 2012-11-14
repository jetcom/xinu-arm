/*
 * Commands for turning the Bluetooth power on.
 *
 * Ripped from the Fluke firmware.
 */

#include "power.h"
#include "usleep.h"

#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))
#define MCLK        (1 << 4)
#define MDIN        (1 << 6)
#define D2A_CS      (1 << 21)

void d2a_wait( void )
{
    usleep(100);
}

void set_d2a(int power, int channel)
{
    int i, data;

    data = (power & 0xFF) | channel;

    IOCLR=D2A_CS; d2a_wait();
    for (i = 11; i >= 0; i--)
    {
	IOCLR=MCLK; d2a_wait();
	if (data & (1 << i))
        {
	    IOSET = MDIN;
        }
	else
        {
	    IOCLR = MDIN;
        }
	d2a_wait();
	IOSET=MCLK; d2a_wait();
    }

    IOCLR = MCLK; d2a_wait();
    IOSET = D2A_CS;  d2a_wait();
}

#define D2A_CHAN_BT    0x0800
void set_bluetooth(int power)
{
    set_d2a(power, D2A_CHAN_BT);
}

