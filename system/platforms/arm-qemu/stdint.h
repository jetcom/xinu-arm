/**
 * @file stdint.h
 *  Platform-specific types.
 *
 * Based on inttypes.h from IPRE Fluke Firmware:
 *   Ben Johnson <circuitben@gmail.com>, <keith.ohara@gatech.edu
 *   April 2008
 */

#ifndef _XINU_STDINT_H
#define _XINU_STDINT_H

typedef unsigned int intptr_t;

typedef unsigned char uint8_t;
typedef char int8_t;

typedef unsigned short uint16_t;
typedef short int16_t;

typedef unsigned int uint32_t;
typedef int int32_t;

#endif

