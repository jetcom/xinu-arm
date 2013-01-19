/**
 * switch to different tests  -- modularization
 *    So people can put in tests, while not interfering with others
 * 
 * Mike Koster
 * april 11, 2012
 */

#include <semaphore.h>
#include <stdio.h>
#include <device.h>
#include <interrupt.h>
#include "vic.h"

extern void usleep( int );
extern void ksimpleterminal( void );
extern void findMemory( void );
extern ulong clkticks;
extern ulong clktime;

/* Timer 0 */
#define TIMER0_IR      (*((volatile unsigned long *) 0xE0004000))
#define TIMER0_TCR     (*((volatile unsigned long *) 0xE0004004))
#define TIMER0_TC      (*((volatile unsigned long *) 0xE0004008))
#define TIMER0_PR      (*((volatile unsigned long *) 0xE000400C))
#define TIMER0_PC      (*((volatile unsigned long *) 0xE0004010))
#define TIMER0_MCR     (*((volatile unsigned long *) 0xE0004014))
#define TIMER0_MR0     (*((volatile unsigned long *) 0xE0004018))
#define TIMER0_MR1     (*((volatile unsigned long *) 0xE000401C))
#define TIMER0_MR2     (*((volatile unsigned long *) 0xE0004020))
#define TIMER0_MR3     (*((volatile unsigned long *) 0xE0004024))
#define TIMER0_CCR     (*((volatile unsigned long *) 0xE0004028))
#define TIMER0_CR0     (*((volatile unsigned long *) 0xE000402C))
#define TIMER0_CR1     (*((volatile unsigned long *) 0xE0004030))
#define TIMER0_CR2     (*((volatile unsigned long *) 0xE0004034))
#define TIMER0_CR3     (*((volatile unsigned long *) 0xE0004038))
#define TIMER0_EMR     (*((volatile unsigned long *) 0xE000403C))

/**
 * A sample thread.
 */
static int thr(void)
{
    int i;
    for (i = 0; i < 15; i++)
    {
        kprintf("thr() - %d\r\n", i);
        yield();
    }
    return 0;
}

/**
 * Yet another sample thread (YAST!)
 */
static void thr3(int a, int b, int c, int d, int e, int f, int g, int h, int j, int z)
{
    yield();
    kprintf("thr3! %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n", a++, b--, c*=5, d/=2, e--, f+=5, --g, ++h, --j, ++z);
    yield();
    kprintf("thr3. %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n", a, b, c, d, e, f, g, h, j, z);
}

/**
 * Another sample thread.
 */
static int thr2(int a, int b, int c, int d, int e, int f, int g, int h, int j, int z)
{
    int i;
    kprintf("thr2(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\r\n", a, b, c, d, e, f, g, h, j, z);
    thr3(a, b, c, d, e, f, g, h, j, z);
    for (i = 0; i < 10; i++)
    {
        kprintf("thr2!!!!!!!!!!!!!() - %d\r\n", i);
        yield();
    }
    thr3(a, b, c, d, e, f, g, h, j, z);
    kprintf("thr2(%d, %d, %d, %d, %d, %d, %d, %d, %d, %d)\r\n", a, b, c, d, e, f, g, h, j, z);
    return 0;
}

/**
 * Test context switching.
 */
static void threadTest(void)
{
    tid_typ thr_tid;

    ready(create((void *)thr2, 800, INITPRIO, "thr2", 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9), RESCHED_NO);
    kprintf("Creating thr\r\n");
    thr_tid = create((void *)thr, 800, INITPRIO, "thr", 0);
    kprintf("thr_tid is %x\r\n", thr_tid);
    ready(thr_tid, RESCHED_YES);
    kprintf("Control returned to main thread. YES!\r\n");
}

/**
 * A sample timeslice testing thread. This should hog the CPU and not call yield().
 */
static int tsThr1(const char* id)
{
    int i=0, j;
    while (TRUE)
    {
        for (j = 0; j < 1000000; j++)
            ;
        i++;
        kprintf("%s-i = %d\r\n", id, i);
    }
    return 0;
}

/**
 * Timeslice testing.
 */
static void timesliceThreadTest(void)
{
    ready(create((void *)tsThr1, 800, INITPRIO, "tsThr1-a", 1, "a"), RESCHED_NO);
    kprintf("Created tsThr1-a\r\n");
    ready(create((void *)tsThr1, 800, INITPRIO, "tsThr1-b", 1, "b"), RESCHED_YES);
    kprintf("Created tsThr1-b\r\n");
}

/**
 * A high priority thread waiting on a semaphore owned by a lower
 * priority process.
 */
static int semtest_high(semaphore sem)
{
    kprintf("high: wait()ing…\r\n");
    wait(sem);
    kprintf("high: awoken!\r\n");
    return 0;
}

/**
 * A low priority thread releasing a semaphore.
 */
static int semtest_low(semaphore sem)
{
    kprintf("low: signal()ing…\r\n");
    signal(sem);
    kprintf("low: awoken!\r\n");
    return 0;
}

/**
 * Test low/high priorities and semaphores as assigned by Victor
 * Norman.
 */
static int semtest(void)
{
    semaphore sem;

    sem = semcreate(0);
    kprintf("semtest: creating and switching to high thread…\r\n");
    ready(create((void *)semtest_high, 800, 4, "semtest_high", sem), RESCHED_YES);
    kprintf("semtest: high thread now waiting on semaphore…\r\n");
    kprintf("semtest: creating and switching to low thread…\r\n");
    ready(create((void *)semtest_low, 800, 2, "semtest_low", sem), RESCHED_YES);
    kprintf("semtest: low thread created, done.\r\n");

    return 0;
}

static int uartThread( void )
{
    printf( "Hello, world." );
    return 0;
}

static void uartTest( void )
{
    ready( create( (void *) uartThread, 800, INITPRIO, "uartThread", 0 ), RESCHED_YES );
}

/*
 * Interrupt testing.
 */
int numGPIO0Interrupts = 0;
void uart0_interrupt_handler( void ) __attribute__ ((interrupt("IRQ")));
void uart0_interrupt_handler( void )
{
    disable();
    int id;

    numGPIO0Interrupts++;

    // Handle the interrupt. Apparently reading this value is enough.
    // Tell the VIC we've handled the interrupt.
    irq_handled();
    enable();
}

static void interruptTest( void )
{
    int i;
    irqmask irqm;

    // Test interrupts
    irqm = enable();
    kprintf("Interrupt mask: %x\r\n", irqm );
    irqm = disable();

    kprintf("Disabled. Interrupt mask saved: %x, actual: %x\r\n", irqm,
	    vic_get_irqmask() );

    // UART 1 interrupt
    //restore( irqm );

    register_irq( VIC_UART0, uart0_interrupt_handler );
    enable_irq( VIC_GPIO0 );
    //kprintf("Enabled UART0 interrupt. Interrupt mask: %x\r\n", vic_get_irqmask() );

    
    for( i =0; i < 10; i++)
    {
        // busy-wait
        int j = 0;
        for( j = 0; j < 100000000; j++ );

        kprintf( "GPIO0 interrupts: %d\r\n", numGPIO0Interrupts );
    }
}

/****************/

#define IROUT1      (1 << 13)
#define IROUT2      (1 << 19)
#define IROUT3      (1 << 20)
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))

static void irTest( void ){
#if 0
    //while(1){
        IOSET = IROUT1 | IROUT2 | IROUT3;
        int i;
        for(i=0; i <= 255; i++) {
            write(3, 0, i);
            usleep(10000);
            if(i%10 == 5) kprintf("Current Value is %d.\r\n",i);
        }
        write(3, 0, 0);
        usleep(1000);
        IOCLR = IROUT1 | IROUT2 | IROUT3;
    //}
    kprintf("Complete!!!!");
    
#endif
}

void clockTest( void )
{
    kprintf("clkticks: %d\n", clkticks );
    kprintf("clktime: %d\n", clktime );
    sleep(2);
    kprintf("clkticks: %d\n", clkticks );
    kprintf("clktime: %d\n", clktime );
}

void timerTest( void )
{
#if 0
  TIMER0_PR = 0x39;
  TIMER0_TCR = 1;
  int diff = TIMER0_TC;
  usleep(1000);
  diff = TIMER0_TC - diff;
  kprintf("Timer difference usleep(1000) is %d.\r\n", diff);
#endif
}

bool runSelectedProgram(char c)
{
  //    int i = 0;
    switch (c) {
    case 'c':
        clockTest();
        break;
    case 'a':
        /* A simple echo program: sends back the character (q to quit)
           that you type. */
        //ksimpleterminal();
        return TRUE;
    case 'b':
      /* binki */
      semtest();
      break;
    case 'g':
        // Nathan Gelderloos
        //threadTest();
        timesliceThreadTest();
        break;
    case 'i':
        // ledInit(3);  init done from sysinit().
        irTest();
        break;
    case 'j':
	uartTest();
	break;
    case 'k':
	interruptTest();
	break;
    case 'm':
        /* Print out stuff about memory layout in the stack. */
        findMemory();
        break;
    case 'l':
        /* turn on the led */
        // ledInit(FRONTLED);  all inits are done from sysinit()
        //write(FRONTLED, 0, 1);
        break;
    case 'o':
        /* turn off the led */
        //write(FRONTLED, 0, 0);
        break;
    case 'L':
        /* turn on the back led */
        // ledInit(BACKLED);   all inits are done from sysinit()
	 //   write(BACKLED, 0, 240);
        break;
    case 'O':
        /* turn off the back led */
        //write(BACKLED, 0, 0);
        break;
    case 'w':
      kprintf("hello!\n");
      break;
    case 't':
      timerTest();
      break;
    default:
        return FALSE;
    }
    return FALSE;
}

int programSwitch( void ) 
{
    int i = 0;
    char c = NULL;

    while (1) {
        if (i == 0) {
            kprintf("Press the key to start your program.\r\n");
        }
        i = (i + 1) % 100000;
	//	led_off();
	//	c = read(SERIAL1,1);
	c = getc(SERIAL0);

        if (runSelectedProgram(c)) {
            break;
        }
    }

    return OK;    
}

