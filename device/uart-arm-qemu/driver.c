#include "uart.h"
#include <lpc210x.h>
#include <inttypes.h>

#define B_RTS 1 << 10 // from fluke.h


/*    baudrate divisor - use UART_BAUD macro
 *    mode - see typical modes (uart.h)
 *    fmode - see typical fmodes (uart.h)
 *    NOTE: uart1Init(UART_BAUD(9600), UART_8N1, UART_FIFO_8); 
 */
void uart1Init(uint16_t baud, uint8_t mode, uint8_t fmode)
{
  // setup Pin Function Select Register (Pin Connect Block) 
  // make sure old values of Bits 0-4 are masked out and
  // set them according to UART1-Pin-Selection
  PINSEL0 = (PINSEL0 & ~UART1_PINMASK) | UART1_PINSEL;
  
  // turn on CTS
  PINSEL0 = (PINSEL0 & ~UART1_CTS_PINMASK) | UART1_CTS_PINSEL;
  
  UART1_IER = 0x03;             // enable interrupts
  UART1_IIR = 0x00;             // clear interrupt ID register
  UART1_LSR = 0x00;             // clear line status register

  // set the baudrate - DLAB must be set to access DLL/DLM
  UART1_LCR = (1<<UART1_LCR_DLAB); // set divisor latches (DLAB)
  UART1_DLL = (uint8_t)baud;         // set for baud low byte
  UART1_DLM = (uint8_t)(baud >> 8);  // set for baud high byte
  
  // set the number of characters and other
  // user specified operating parameters
  // Databits, Parity, Stopbits - Settings in Line Control Register
  UART1_LCR = (mode & ~(1<<UART1_LCR_DLAB)); // clear DLAB "on-the-fly"
  // setup FIFO Control Register (fifo-enabled + xx trig) 
  UART1_FCR = fmode;
}

int uart1Putch(int ch)
{
  while (!(UART1_LSR & ULSR_THRE))    // wait for TX buffer to empty
    continue;                         // also either WDOG() or swap()

  UART1_THR = (uint8_t)ch;  // put char to Transmit Holding Register
  return (uint8_t)ch;       // return char ("stdio-compatible"?)
}

int uart1PutchCTS(int ch)
{  

  while (!(UART1_MSR & UMSR_CTS) || !(UART1_LSR & ULSR_THRE))  // wait for CTS to change
    {
      ;
    }
  
  
  UART1_THR = (uint8_t)ch;  // put char to Transmit Holding Register
  
  return (uint8_t)ch;       // return char ("stdio-compatible"?)
}

int uart1TxEmpty(void)
{
  return (UART1_LSR & (ULSR_THRE | ULSR_TEMT)) == (ULSR_THRE | ULSR_TEMT);
}

void uart1TxFlush(void)
{
  UART1_FCR |= UFCR_TX_FIFO_RESET;          // clear the TX fifo
}

/* Returns: character on success, -1 if no character is available */
int uart1Getch(void)
{
  if (UART1_LSR & ULSR_RDR)                 // check if character is available
    return UART1_RBR;                       // return character

  return -1;
}

int uart1GetchRTS(void)
{
  uart1_set_rts();

  // check if character is available
  if (UART1_LSR & ULSR_RDR)
    {
      uart1_clear_rts();
      // return character
      return UART1_RBR;   
    }
  
  
  uart1_clear_rts();  
  return -1;
}

int uart1GetchBlock(void)
{
  while (!(UART1_LSR & ULSR_RDR));
  return UART1_RBR;
}

int uart1GetchBlockRTS(void)
{
  uart1_set_rts();
  while (!(UART1_LSR & ULSR_RDR));

  uart1_clear_rts();
  
  return UART1_RBR;
}

inline void uart1_set_rts()
{
  //UART1_MCR |= UMCR_RTS;
  IOCLR = B_RTS;
}

inline void uart1_clear_rts()
{
  //UART1_MCR &= ~UMCR_RTS;
  IOSET = B_RTS;
}

inline int uart1_cts()
{
  return (UART1_MSR & UMSR_CTS);
}
