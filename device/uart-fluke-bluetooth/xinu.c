#include <uart.h>
/*
devcall uartInit(device *d) { return 0; }

devcall uartRead(device *d, void *buffer, uint len) { 
    // spin and wait for input.
    int ch;

    while( ( ch = kgetc( d ) ) == SYSERR )
    {
	// block
    }


    *(char *)buffer = ch;
    return 1;
}
devcall uartWrite(device *d, void *buffer, uint len) 
{ 
    int i;
    char *cbuf = buffer;

    for( i = 0; i < len; i++ )
	kputc( d, cbuf[i] );
    return len;
}

devcall uartGetc(device *d) { 
    int ch;

    while( ( ch = kgetc( d ) ) == SYSERR )
    {
	// block
    }

    return ch;
} 

devcall uartPutc(device *d, char e) { 
    kputc( d, e );
    return e;
}

devcall uartControl(device *d, int e, long f, long g) { return 0; }
interrupt uartInterrupt(void) {  }
void uartStat(ushort d) {  }

*/
