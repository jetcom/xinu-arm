/******************************************************************************
 *
 * Main Fluke Header File - most fluke functionality exposed through
 * this interface
 * 
 * The LPC2106 data sheet is necessary for understanding this code.
 * 
 * keith.ohara@gatech.edu
 * April 2008
 * IPRE Fluke Firmware
 *
 ******************************************************************************/
 
#ifndef  __YJLIB__
#define  __YJLIB__

#include "lpc210x.h"
#include <stdint.h>


#define VERSION "fluke:2.9.1"
#define VERSION_OF_BOARD 6

// when the battery value is lower than this blink the LED
#define BATTERY_TOO_LOW  129 

/* These macros are useful for quickly switching between the UARTs
 *  UART0 - serial port connecting to scribbler
 *  UART1 - connected to bluetooth chip
 *
 *  UART1 can use flow control - CTS and RTS class are used for that
 *
 * Don't mix uart1_tx_write with uart1Putch, because that would interfere with
 * transmit queue operation.
 */

//#define putch(x) uart0Putch(x)
//#define dbg_putch(x) uart1PutchCTS(x)
//#define getch(x) uart0Getch(x)
//#define getchblock(x) uart0GetchBlock(x)

//#define putch(x) uart1Putch(x)
//#define dbg_putch(x) uart1Putch(x)
//#define getch(x) uart1Getch(x)
//#define getchblock(x) uart1GetchBlock(x)

#define putch(x) uart1_queue_write(x)
#define dbg_putch(x) uart1_queue_write(x)

#define getch(x) uart1GetchRTS(x)
#define getchblock(x) uart1GetchBlockRTS(x)

/*
 * Grab 2 bytes from the UART
 */
int getchblock2b( void );

/*
 * Push 2 bytes on the UART
 */
void putch2b(int);

void write_word(uint32_t word);


/*
 * Setup the directionality of the pins
 */
void setup_pins( void );

/*
 * Setup the PLL (clock)
 */
void setup_pll( void );

// base clock frequency - 20 MHz
#define FOSC            20000000
#define PLL_M		3
#define MSEL		(PLL_M-1)
#define PSEL 		0x01          
#define PLLE		0
#define PLLC		1

#define PLOCK		10

#define PLL_FEED1	0xAA
#define PLL_FEED2	0x55

#define VPBDIV_VAL	1


/*
 * Setup the MAM (the instruction prefetch)
 */
void setup_mam( void );
/*
 * MAM Setup
 */ 

// Interrupt vectors are re-mapped to Boot Block. 
#define MEMMAP_BOOT_LOADER_MODE   0      
 
// Interrupt vectors are not re-mapped and reside in Flash.
#define MEMMAP_USER_FLASH_MODE    (1<<0)  

// Interrupt vectors are re-mapped to Static RAM.
#define MEMMAP_USER_RAM_MODE      (1<<1)  


/*
 * A microsecond sleep call tuned with the scope 
 * (only valid for PLL setting of 60Mhz)
 */
__attribute__ ((section (".data"), long_call))  
void usleep(int microseconds);

#define msleep(x) usleep(x*1000)


/*
 * SPI Routines - used for reading A2D
 */

inline void spi_wait( void );
inline void spi_init( void );
inline void spi_fini( void );

/*
 * A2D - Battery and External Pin on hacker port
 * to convert battery value to volts: value / 20.9813
 */

#define A2D_CHAN_BAT    0x00
#define A2D_CHAN_EXT    0x01

int read_a2d(int channel);

/*
 * D2A - bright back LED, bluetooh external power, and IR power
 */

#define D2A_CHAN_BT    0x0800
#define D2A_CHAN_LED   0x0400
#define D2A_CHAN_IR    0x0A00

void set_d2a(int power, int channel);

void set_bluetooth(int power);
void set_led(int power);
void set_ir(int power);

/*
 * User LED on front of fluke
 */
void led_on( void );
void led_off( void );

/*
 * Turn on/off IR emitters When turned on the emitters pulse at 40 Khz
 * (our IR receiver responds to 40Khz IR)
 * 
 * emitters is a 3 bit value saying which emitters you want turned on
 * 0x01 = Right  (first bit)
 * 0x02 = Left   (second bit)
 * 0x04 = Center (third bit)
 *
 */ 
void emit_on(uint8_t emitters);
void emit_off(uint8_t emitters);

int check_ir_bounce(uint8_t emitters);

/* 
 * Simple printing utilties rather than full-on stdio.h 
 * 
 * they use the putch() so will use UART as described in top of the
 * file dbg_ use the dbg uart in the macros in the top of this file
 *
 * printdec will print an integer in base ten ascii format (>= 0)
 * printbin will print an integer in base two ascii format (>= 0)
 * printstr prints an arbitrary string
 */
void printdec(int sum);
void printbin(int sum);
void putstr(char* buf);
void putstrn(char* buf, int size);

void dbg_printdec(int sum);
void dbg_printbin(int sum);
void dbg_putstr(char* buf);
void dbg_putstrn(char* buf, int size);

/*
 * The images sometimes have Y/U/V swapped due to the way we sync up
 * with the camera clock. This routing takes multiple images and votes
 * on whether to take another to get more reliable images. It takes
 * the average of a few of the Y/U/V pixels and makes sure subsequent
 * frames don't differ by a bunch (which we assume indicates a swap).
 * This slows grabbing a frame. 
 *
 * Times is the number of attempts before giving up to get images that
 * agree on an average of some of the pixels.
 */
void grab_image_vote(int times, unsigned char* img, int delay);

#define IMG_VOTES 2

/*
 * Routines for reading the 1MBit serial memory.  The memory is
 * organized in 512 pages. Each page is 264 bytes large. Thus a byte
 * of memory is addressed by page and offset. These routines do not
 * sanity check the address or size you give it. It will wrap if you
 * aren't careful. 
 * 
 * There is a temporary memory buffer you write to before committing
 * to the actual serial memory.  
 *
 */

__attribute__ ((section (".data"), long_call)) 
void read_mem(int page, int offset, unsigned char* buf, int size);
void write_mem(int page, int offset, unsigned char* buf, int size);
void erase_mem(int page);
void write_mem_buffer(int offset, unsigned char* buf, int size);
void read_mem_buffer(int offset, unsigned char* buf, int size);
void mem_buffer_to_mem(int page);

#define MEM_DELAY 1
#define MAIN_MEMORY_PAGE_TO_BUFFER   0x53
#define MEM_BUF_WRITE                0x84
#define MEM_BUF_MEM                  0x83
#define MEM_READ_STATUS              0xD7
#define MEM_PAGE_READ                0xD2
#define MEM_PAGE_ERASE               0x81
#define MEM_BUF_READ                 0xD4


/*
 * Fluke Pinout
 *  (version 3 of the board was slightly different)
 *
 */


#if (VERSION_OF_BOARD == 3)

#define S_TXD       (1 << 0)
#define S_RXD       (1 << 1)
#define EXT_I2C_SC  (1 << 2)
#define EXT_I2C_SD  (1 << 3)
#define MCLK        (1 << 4)
#define MDOUT       (1 << 5)
#define MDIN        (1 << 6)
#define CAM_SC      (1 << 7)
#define B_TXD       (1 << 8)
#define B_RXD       (1 << 9)
#define B_RTS       (1 << 10)
#define B_CTS       (1 << 11)
#define S_RST       (1 << 12)
#define IROUT1      (1 << 13)
#define BOOT        (1 << 14)
#define CAM_VSYNC   (1 << 15)

#define CAM_PCLK    (1 << 16)
#define LED         (1 << 17)
#define IRIN        (1 << 18)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)
#define D2A_CS      (1 << 21)
#define A2D_CS      (1 << 22)
#define MCS         (1 << 23)
#define CAM_D0      (1 << 24)
#define CAM_D1      (1 << 25)
#define CAM_D2      (1 << 26)
#define CAM_D3      (1 << 27)
#define CAM_D4      (1 << 28)
#define CAM_D5      (1 << 29)
#define CAM_D6      (1 << 30)
#define CAM_D7      (1 << 31)

#else

#if (VERSION_OF_BOARD >= 4)

#define S_TXD       (1 << 0)
#define S_RXD       (1 << 1)
#define EXT_I2C_SC  (1 << 2)
#define EXT_I2C_SD  (1 << 3)
#define MCLK        (1 << 4)
#define MDOUT       (1 << 5)
#define MDIN        (1 << 6)
#define CAM_SC      (1 << 7)
#define B_TXD       (1 << 8)
#define B_RXD       (1 << 9)
#define IRIN        (1 << 10)
#define B_CTS       (1 << 11)
#define S_RST       (1 << 12)
#define IROUT1      (1 << 13)
#define BOOT        (1 << 14)
#define CAM_VSYNC   (1 << 15)
#define CAM_PCLK    (1 << 16)
#define LED         (1 << 17)
#define B_RTS       (1 << 18)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)
#define D2A_CS      (1 << 21)
#define A2D_CS      (1 << 22)
#define MCS         (1 << 23)
#define CAM_D0      (1 << 24)
#define CAM_D1      (1 << 25)
#define CAM_D2      (1 << 26)
#define CAM_D3      (1 << 27)
#define CAM_D4      (1 << 28)
#define CAM_D5      (1 << 29)
#define CAM_D6      (1 << 30)
#define CAM_D7      (1 << 31)
#endif
#endif

#endif /*  __YJLIB__ */
