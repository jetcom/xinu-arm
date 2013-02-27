#ifndef __GPIO_H
#define __GPIO_H

#include "bcm2835.h"

//GPIO registers (see pg90 of the BCM2835 datasheet) (some are verified)
#define GPIO_BASE_ADDR 0x20200000
//GPIO function select
#define GPFSEL_BASE_ADDR (GPIO_BASE_ADDR+0x00)
#define GPFSEL0   __IO(GPFSEL_BASE_ADDR+0x00)
#define FSEL9 27
#define FSEL8 24
#define FSEL7 21
#define FSEL6 18
#define FSEL5 15
#define FSEL4 12
#define FSEL3 9
#define FSEL2 6
#define FSEL1 3
#define FSEL0 0
#define GPFSEL1   __IO(GPFSEL_BASE_ADDR+0x04)
#define FSEL19 FSEL9
#define FSEL18 FSEL8
#define FSEL17 FSEL7
#define FSEL16 FSEL6
#define FSEL15 FSEL5
#define FSEL14 FSEL4
#define FSEL13 FSEL3
#define FSEL12 FSEL2
#define FSEL11 FSEL1
#define FSEL10 FSEL0
#define GPFSEL2   __IO(GPFSEL_BASE_ADDR+0x08)
#define FSEL29 FSEL9
#define FSEL28 FSEL8
#define FSEL27 FSEL7
#define FSEL26 FSEL6
#define FSEL25 FSEL5
#define FSEL24 FSEL4
#define FSEL23 FSEL3
#define FSEL22 FSEL2
#define FSEL21 FSEL1
#define FSEL20 FSEL0
#define GPFSEL3   __IO(GPFSEL_BASE_ADDR+0x0C)
#define FSEL39 FSEL9
#define FSEL38 FSEL8
#define FSEL37 FSEL7
#define FSEL36 FSEL6
#define FSEL35 FSEL5
#define FSEL34 FSEL4
#define FSEL33 FSEL3
#define FSEL32 FSEL2
#define FSEL31 FSEL1
#define FSEL30 FSEL0
#define GPFSEL4   __IO(GPFSEL_BASE_ADDR+0x10)
#define FSEL49 FSEL9
#define FSEL48 FSEL8
#define FSEL47 FSEL7
#define FSEL46 FSEL6
#define FSEL45 FSEL5
#define FSEL44 FSEL4
#define FSEL43 FSEL3
#define FSEL42 FSEL2
#define FSEL41 FSEL1
#define FSEL40 FSEL0
#define GPFSEL5   __IO(GPFSEL_BASE_ADDR+0x14)
#define FSEL53 FSEL3
#define FSEL52 FSEL2
#define FSEL51 FSEL1
#define FSEL50 FSEL0
#define FSEL_MASK   0b111
#define FSEL_INPUT  0b000 //see pg102 of the datasheet for what the alternate functions do
#define FSEL_OUTPUT 0b001
#define FSEL_AF0    0b100
#define FSEL_AF1    0b101
#define FSEL_AF2    0b110
#define FSEL_AF3    0b111
#define FSEL_AF4    0b011
#define FSEL_AF5    0b010
//GPIO output set
#define GPSET_ADDR (GPIO_BASE_ADDR+0x1C)
#define GPSET0    __IO(GPSET_ADDR+0x00)
#define GPSET1    __IO(GPSET_ADDR+0x04)
//GPIO output clear
#define GPCLR_ADDR (GPIO_BASE_ADDR+0x28)
#define GPCLR0    __IO(GPCLR_ADDR+0x00)
#define GPCLR1    __IO(GPCLR_ADDR+0x04)
//GPIO pin level
#define GPLEV_ADDR (GPIO_BASE_ADDR+0x34)
#define GPLEV0    __IO(GPLEV_ADDR+0x00)
#define GPLEV1    __IO(GPLEV_ADDR+0x04)
//GPIO event detect enable
#define GPEDS_ADDR (GPIO_BASE_ADDR+0x40)
#define GPEDS0    __IO(GPEDS_ADDR+0x00)
#define GPEDS1    __IO(GPEDS_ADDR+0x04)
//GPIO rising edge detect enable
#define GPREN_ADDR (GPIO_BASE_ADDR+0x4C)
#define GPREN0    __IO(GPREN_ADDR+0x00)
#define GPREN1    __IO(GPREN_ADDR+0x04)
//GPIO falling edge detect enable
#define GPFEN_ADDR (GPIO_BASE_ADDR+0x58)
#define GPFEN0    __IO(GPFEN_ADDR+0x00)
#define GPFEN1    __IO(GPFEN_ADDR+0x04)
//GPIO high detect enable
#define GPHEN_ADDR (GPIO_BASE_ADDR+0x64)
#define GPHEN0    __IO(GPHEN_ADDR+0x00)
#define GPHEN1    __IO(GPHEN_ADDR+0x04)
//GPIO low detect enable
#define GPLEN_ADDR (GPIO_BASE_ADDR+0x70)
#define GPLEN0    __IO(GPLEN_ADDR+0x00)
#define GPLEN1    __IO(GPLEN_ADDR+0x04)
//GPIO asynchronous rising edge detect enable
#define GPAREN_ADDR (GPIO_BASE_ADDR+0x7C)
#define GPAREN0   __IO(GPAREN_ADDR+0x00)
#define GPAREN1   __IO(GPAREN_ADDR+0x04)
//GPIO asynchronous falling edge detect enable
#define GPAFEN_ADDR (GPIO_BASE_ADDR+0x88)
#define GPAFEN0   __IO(GPAFEN_ADDR+0x00)
#define GPAFEN1   __IO(GPAFEN_ADDR+0x04)
//GPIO pull-up/pull-down
#define GPPUD     __IO8(GPIO_BASE_ADDR+0x94)
#define PUDUP 1
#define PUDDN 0
//GPIO pull-up/pull-down clock
#define GPPUDCLK_ADDR (GPIO_BASE_ADDR+0x98)
#define GPPUDCLK0 __IO(GPPUDCLK_ADDR+0x00)
#define GPPUDCLK1 __IO(GPPUDCLK_ADDR+0x04)
/*******************************************************************************
 * Internal macros
 ******************************************************************************/
//on register x, function select y, write alternate function mode z
#define __GPFSEL(x, y, z) (x) &= ~(FSEL_MASK<<(y)); (x) |= ((z)<<(y))
//clear a bit for GPIO pin y, use base address x
#define __GPCB(x, y)      __IO((x)+(((y)/32)*4)) &= ~(1<<((y)%32))
//set a bit for GPIO pin y, use base address x
#define __GPSB(x, y)      __IO((x)+(((y)/32)*4)) |= (1<<((y)%32))
//reads bit from GPIO pin y, use base address x
#define __GPRB(x, y)      (__IO((x)+(((y)/32)*4)) >> ((y)%32))&1
/*******************************************************************************
 * Macros for users
 ******************************************************************************/
//like __GPFSEL, but takes a GPIO pin number x and alternate function mode y
//    ex: GPIOMODE(LED_PIN, FSEL_OUTPUT);
#define GPIOMODE(x, y) __GPFSEL((__IO(GPFSEL_BASE_ADDR+(((x)/10)*4))), (((x)%10)*3), (y))
//set GPIO pin x high
#define GPIOSET(x)     __GPSB(GPSET_ADDR, (x))
//set GPIO pin x low
#define GPIOCLR(x)     __GPSB(GPCLR_ADDR, (x))
//read the level of GPIO pin x
#define GPIOREAD(x)    __GPRB(GPLEV_ADDR, (x))
//turn on a pull-up on GPIO pin x (see pg101 of the BCM2835 datasheet) (not completely verified)
//requires a local "i" int
#define GPIOPULLUP(x) GPPUD |= (1<<PUDUP); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      __GPSB(GPPUDCLK_ADDR, (x)); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      GPPUD = 0; \
                      __GPCB(GPPUDCLK_ADDR, (x))
//turn on a pull-down on GPIO pin x (see pg101 of the BCM2835 datasheet) (not completely verified)
//requires a local "i" int
#define GPIOPULLDN(x) GPPUD |= (1<<PUDDN); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      __GPSB(GPPUDCLK_ADDR, (x)); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      GPPUD = 0; \
                      __GPCB(GPPUDCLK_ADDR, (x))
//turn off a pull-up/pull-down on GPIO pin x (see pg101 of the BCM2835 datasheet) (not completely verified)
//requires a local "i" int
#define GPIOPULLOF(x) GPPUD &= ~((1<<PUDUP) | (1<<PUDDN)); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      __GPCB(GPPUDCLK_ADDR, (x)); \
                      for(i=0; i<150; i++){__asm__("nop");} \
                      GPPUD = 0; \
                      __GPCB(GPPUDCLK_ADDR, (x))

#endif /* __GPIO_H */

/*
Copyright (c) 2012 David Welch dwelch@dwelch.com, 2013 David DiPaola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
