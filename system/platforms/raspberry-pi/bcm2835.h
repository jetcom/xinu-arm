#ifndef __BCM2835_H
#define __BCM2835_H

#include <stdint.h> //for uint32_t, etc

/**
 * @file bcm2835.h
 *
 * Constants and declarations associated with the Broadcom 2835
 *  System On A Chip.
 *
 */

/*******************************************************************************
 * Macros that make I/O device registers look like global volatile ints
 *
 * Addresses that the ARM can use directly are in 0x20nnnnnn (see IO_PHY_ADDR)
 * Addresses that the DMA engine can use are in 0x7Ennnnnn (see IO_BUS_ADDR)
 ******************************************************************************/
//for I/O devices when using the physical address space (0x20000000 - 0x20FFFFFF)
#define IO_PHY_ADDR(x) (((x)&0x00FFFFFF) | 0x20000000)
//for I/O devices when using the bus address space (0x7E000000 - 0x7EFFFFFF)
#define IO_BUS_ADDR(x) (((x)&0x00FFFFFF) | 0x7E000000)

//for using I/O devices just like a global variable
#define __IO32(x) (*((volatile uint32_t*)(IO_PHY_ADDR(x))))
#define __IO16(x) (*((volatile uint16_t*)(IO_PHY_ADDR(x)))) //requires little-endian mode
#define __IO8(x)  (*((volatile uint8_t*)(IO_PHY_ADDR(x)))) //requires little-endian mode
#define __IO(x)   __IO32(x)



/*******************************************************************************
 * Macros for the System Timer.
 *
 * See page the "System Timer" section of the BCM2835 ARM Peripherals datasheet.
 ******************************************************************************/
#define TIMER_CS_ADDR  0x20003000
#define TIMER_CLO_ADDR 0x20003004
#define TIMER_C0_ADDR  0x2000300C
#define TIMER_C1_ADDR  0x20003010
#define TIMER_C2_ADDR  0x20003014
#define TIMER_C3_ADDR  0x20003018
#define TIMER_CS  __IO(TIMER_CS_ADDR)
#define TIMER_CS_M3 3
#define TIMER_CS_M2 2
#define TIMER_CS_M1 1
#define TIMER_CS_M0 0
#define TIMER_CLO __IO(TIMER_CLO_ADDR)
#define TIMER_C0  __IO(TIMER_C0_ADDR) //the GPU may be using this one, steer clear
#define TIMER_C1  __IO(TIMER_C1_ADDR)
#define TIMER_C2  __IO(TIMER_C2_ADDR) //the GPU may be using this one, steer clear
#define TIMER_C3  __IO(TIMER_C3_ADDR)



/*******************************************************************************
 * Macros for the Interrupt Controller.
 *
 * See page the "Interrupt Controller" section of the BCM2835 ARM Peripherals
 * datasheet.
 ******************************************************************************/
#define INTERRUPT_BASE_ADDR 0x2000B000
#define INTERRUPT_BASICPEND_ADDR       (INTERRUPT_BASE_ADDR+0x200)
#define INTERRUPT_IRQPEND1_ADDR        (INTERRUPT_BASE_ADDR+0x204)
#define INTERRUPT_IRQPEND2_ADDR        (INTERRUPT_BASE_ADDR+0x208)
#define INTERRUPT_FIQCONTROL_ADDR      (INTERRUPT_BASE_ADDR+0x20C)
#define INTERRUPT_ENABLEIRQ1_ADDR      (INTERRUPT_BASE_ADDR+0x210)
#define INTERRUPT_ENABLEIRQ2_ADDR      (INTERRUPT_BASE_ADDR+0x214)
#define INTERRUPT_ENABLEBASICIRQ_ADDR  (INTERRUPT_BASE_ADDR+0x218)
#define INTERRUPT_DISABLEIRQ1_ADDR     (INTERRUPT_BASE_ADDR+0x21C)
#define INTERRUPT_DISABLEIRQ2_ADDR     (INTERRUPT_BASE_ADDR+0x220)
#define INTERRUPT_DISABLEBASICIRQ_ADDR (INTERRUPT_BASE_ADDR+0x224)
#define INTERRUPT_BASICPEND       __IO(INTERRUPT_BASICPEND_ADDR)
#define INTERRUPT_IRQPEND1        __IO(INTERRUPT_IRQPEND1_ADDR)
#define INTERRUPT_IRQPEND2        __IO(INTERRUPT_IRQPEND2_ADDR)
#define INTERRUPT_FIQCONTROL      __IO(INTERRUPT_FIQCONTROL_ADDR)
#define INTERRUPT_ENABLEIRQ1      __IO(INTERRUPT_ENABLEIRQ1_ADDR)
#define INTERRUPT_ENABLEIRQ2      __IO(INTERRUPT_ENABLEIRQ2_ADDR)
#define INTERRUPT_ENABLEBASICIRQ  __IO(INTERRUPT_ENABLEBASICIRQ_ADDR)
#define INTERRUPT_DISABLEIRQ1     __IO(INTERRUPT_DISABLEIRQ1_ADDR)
#define INTERRUPT_DISABLEIRQ2     __IO(INTERRUPT_DISABLEIRQ2_ADDR)
#define INTERRUPT_DISABLEBASICIRQ __IO(INTERRUPT_DISABLEBASICIRQ_ADDR)



#endif /* __BCM2835_H */

/*
Copyright (c) 2012 David Welch dwelch@dwelch.com, 2013 David DiPaola

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
