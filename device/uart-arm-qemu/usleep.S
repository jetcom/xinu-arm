/******************************************************************************
 *
 * usleep (when clock is set to 60 Mhz)
 *	
 * Parameters:	
 *  R0 - sleep time in microseconds
 * 
 * 
 * keith.ohara@gatech.edu
 * April 2008
 * IPRE Fluke Firmware
 *
 ******************************************************************************/

.file "usleep.s"
.arm
.align
.globl usleep
.type usleep, %function
/* .section .data,"ax",%progbits */
usleep:
	STMFD SP!, {R0-R12, LR}
usleep_delay:
	LDR R5, =14
usleep_delay_inner:
	SUBS R5, R5, #1	
	BNE usleep_delay_inner
	
	SUBS R0, R0, #1	
	BNE usleep_delay

	/* return */
	LDMFD SP!, {R0-R12, PC}
