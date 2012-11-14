/**
 * @file     ledInit.c
 * @provides ledInit
 * @author Andrew Webster, Brad Haan, Avery Martin
 * @author Victor Norman
 * LED initialization.  This should be called during general device
 * initialization.
 *
 */
#include <stddef.h>
#include <led.h>
#include <device.h>
#include "fluke-led.h"

struct led ledtab[NLED];

void server_set_ir_emittors( void );


/*
 * Initialize LED control and status registers.
 * @param devptr pointer to a led device
 * @return OK on success, SYSERR on failure
 */
devcall ledInit(device *devptr)
{
    struct led *ledptr;
    struct led_csreg *regptr;

    /* Initialize structure pointers */
    ledptr = &ledtab[devptr->minor];
    ledptr->dev = devptr;
    ledptr->csr = devptr->csr;
    regptr = (struct led_csreg *)ledptr->csr;

    if (devptr->num == FRONTLED) {
        /* Front LED */
        regptr->iodir |= FRONT_LED_PIN;
        // IODIR = IODIR | FRONT_LED_PIN;
    } else if (devptr->num == BACKLED) {
        /* Back (dimmable) LED */
        regptr->iodir |= MDIN;
        // IODIR = IODIR | MDIN;
    } else if (devptr->num == 3) {  /* NOT RIGHT ! */
        server_set_ir_emittors();
    } else {
        return SYSERR;
    }

    return OK;  
}

/*
 * Set IR emitters used for transmission
 */
uint32_t use_emitters = IROUT1 | IROUT2 | IROUT3;

void server_set_ir_emittors( void )
{
    uint32_t e;   // vtn2: this is wrong.  I changed from uint8_t to fix compiling.
  e = 0xE0010000;
  
  // right
  if (e & 0x1)
    {
      use_emitters |= IROUT1;
    }
  else
    {
      use_emitters &= ~IROUT1;
    }
  
  //middle
  if (e & 0x2)
    {
      use_emitters |= IROUT3;
    }
  else
    {
      use_emitters &= ~IROUT3;
    }

  //left
  if (e & 0x4)
    {
      use_emitters |= IROUT2;
    }
  else
    {
      use_emitters &= ~IROUT2;
    }
}


void clear_rts( void ){
    IOSET = (1 << 18);
}


void set_rts( void ){
    IOCLR = (1 << 18);
}

int getchBlockRTS(){
    set_rts();
    while(!(UART1_LSR & USLR_RDR));

    clear_rts();
    return UART1_RBR;
}

