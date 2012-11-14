/**
 * Prints out the memory location  -- mapping
 *    
 * @author
 *  Victor Norman & Mike Koster
 * @date
 *  april 11, 2012
 */
#include <stdio.h>

int partC(int m) {
    unsigned int *mem;
    int o = 200;
    char p = 'a', q = 'A';

    kprintf("In c, called from b, called from a\r\n");
    kprintf("address of param m is 0x%x\r\n", (unsigned int) &m);
    kprintf("address of vars mem, o, p, q are 0x%x, 0x%x, 0x%x, 0x%x\r\n",
            (unsigned int) &mem,  (unsigned int) &o,
            (unsigned int) &p,  (unsigned int) &q);


    kprintf("Enter a memory location to start at.  Will print values in next 32 words.\r\n");
    int i;
    for (i = 0; i < 32; i++) {
        kprintf("At 0x%x, we see value 0x%08x\r\n", mem + i, (unsigned int) *(i + mem));
    }

    return 0;
}


int partB(int k)
{
    int l = 101;
    kprintf("In b, local var l is at 0x%x\r\n",  (unsigned int) &l);
    kprintf("In b, param k is at 0x%x\r\n", (unsigned int) &k);
    return partC(l);
}


int partA(int i)
{
    int j = 99;
    kprintf("In a, local var j is at 0x%x\r\n", (unsigned int) &j);
    kprintf("In a, param i is at 0x%x\r\n", (unsigned int) &i);
    return partB(j);
}


void findMemory( void )
{
    int i = 77;
    kprintf("\r\nMemory locations:\r\n");
    kprintf("In main, local var i is at 0x%x\r\n", (unsigned int) &i);
    kprintf("Address of functions a, b, c are 0x%x, 0x%x, 0x%x\r\n",
           (unsigned int) partA, (unsigned int) partB, (unsigned int) partC);
    (void) partA(i);
}
