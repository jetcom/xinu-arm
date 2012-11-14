

#define D2A_CS      (1 << 21)
#define A2D_CS      (1 << 22)
#define MCS         (1 << 23)
#define MCLK        (1 << 4)
#define MDIN        (1 << 6)
#define B_TXD       (1 << 8)
#define B_RTS       (1 << 10)
#define S_RST       (1 << 12)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)
#define IROUT1      (1 << 13)
#define LED         (1 << 17)

/* General Purpose Input/Output (GPIO) */
#define IOPIN          (*((volatile unsigned long *) 0xE0028000))
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IODIR          (*((volatile unsigned long *) 0xE0028008))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))

