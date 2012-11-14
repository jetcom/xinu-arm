/******************************************************************************
 *
 * startup code
 * 
 * 
 * keith.ohara@gatech.edu
 * April 2008
 * IPRE Fluke Firmware
 *
 ******************************************************************************/

/* Stack Sizes */
.set  UND_STACK_SIZE, 0x00000004		/* stack for "undefined instruction" interrupts is 4 bytes  */
.set  ABT_STACK_SIZE, 0x00000004		/* stack for "abort" interrupts is 4 bytes                  */
.set  FIQ_STACK_SIZE, 0x00000004		/* stack for "FIQ" interrupts  is 4 bytes         	    */
.set  IRQ_STACK_SIZE, 0X000000A0		/* stack for "IRQ" normal interrupts is 4 bytes    	    */
.set  SVC_STACK_SIZE, 0x00000004		/* stack for "SVC" supervisor mode is 4 bytes  		    */
.set  SYS_STACK_SIZE, 0x00002000        /* stack for "SYS" (user) mode is 8192 bytes (nulluser task/thread) */


/* Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs (program status registers) */
.set  MODE_USR, 0x10            		/* Normal User Mode 				    */
.set  MODE_FIQ, 0x11            		/* FIQ Processing Fast Interrupts Mode 		    */
.set  MODE_IRQ, 0x12            		/* IRQ Processing Standard Interrupts Mode 	    */
.set  MODE_SVC, 0x13            		/* Supervisor Processing Software Interrupts Mode   */
.set  MODE_ABT, 0x17            		/* Abort Processing memory Faults Mode 	            */
.set  MODE_UND, 0x1B            		/* Undefined Processing Undefined Instructions Mode 		*/
.set  MODE_SYS, 0x1F            		/* System Running Priviledged Operating System Tasks  Mode	*/

.set  I_BIT, 0x80               		/* when I bit is set, IRQ is disabled (program status registers) */
.set  F_BIT, 0x40               		/* when F bit is set, FIQ is disabled (program status registers) */


.text
.arm

.global Reset_Handler
.global _start
.func   _start

_start:

# Exception Vectors

_vectors:       ldr     PC, Reset_Addr         
                ldr     PC, Undef_Addr
                ldr     PC, SWI_Addr
                ldr     PC, PAbt_Addr
                ldr     PC, DAbt_Addr
                nop				/* Reserved Vector (holds Philips ISP checksum) */
                ldr     PC, [PC,#-0xFF0]	/* see page 71 of "Insiders Guide to the Philips ARM7-Based Microcontrollers" by Trevor Martin  */
                ldr     PC, FIQ_Addr

Reset_Addr:     .word   Reset_Handler		/* defined in this module below  */
Undef_Addr:     .word   UNDEF_Routine		/* defined in main.c  */
SWI_Addr:       .word   SWI_Routine		/* defined in main.c  */
PAbt_Addr:      .word   UNDEF_Routine		/* defined in main.c  */
DAbt_Addr:      .word   UNDEF_Routine		/* defined in main.c  */
FIQ_Addr:       .word   FIQ_Routine		/* defined in main.c  */
                .word   0			/* rounds the vectors and ISR addresses to 64 bytes total  */

		.=.+0x1C0			/* skip past Philips ISP ram usage (all the way to 0x40000200) */

# Reset Handler
Reset_Handler:  
		/* Setup a stack for each mode - note that this only sets up a usable stack
		for User mode.   Also each mode is setup with interrupts initially disabled. */
    			  
		ldr   r0, =_end
        add r0, r0, #UND_STACK_SIZE
   		msr   CPSR_c, #MODE_UND|I_BIT|F_BIT 	/* Undefined Instruction Mode  */
    		mov   sp, r0
    		add   r0, r0, #ABT_STACK_SIZE
    		msr   CPSR_c, #MODE_ABT|I_BIT|F_BIT 	/* Abort Mode */
    		mov   sp, r0
    		add   r0, r0, #FIQ_STACK_SIZE
    		msr   CPSR_c, #MODE_FIQ|I_BIT|F_BIT 	/* FIQ Mode */
    		mov   sp, r0	
   		add   r0, r0, #IRQ_STACK_SIZE
    		msr   CPSR_c, #MODE_IRQ|I_BIT|F_BIT 	/* IRQ Mode */
    		mov   sp, r0
    		add   r0, r0, #SVC_STACK_SIZE
    		msr   CPSR_c, #MODE_SVC|I_BIT|F_BIT 	/* Supervisor Mode */
    		mov   sp, r0
    		add   r0, r0, #SYS_STACK_SIZE
    		msr   CPSR_c, #MODE_SYS|I_BIT|F_BIT 	/* User Mode */
    		mov   sp, r0

		/* Copy .data section (Copy from ROM to RAM) */
                ldr     R1, =_etext
                ldr     R2, =_data
                ldr     R3, =_edata
1:        	cmp     R2, R3
                ldrlo   R0, [R1], #4
                strlo   R0, [R2], #4
                blo     1b

		/* Clear .bss section (Zero init)  */
                mov     R0, #0
                ldr     R1, =_bss
                ldr     R2, =_end
2:		cmp     R1, R2
                strlo   R0, [R1], #4
                blo     2b

        mov r0, sp
        add r0, r0, #8
        ldr r1, =memheap
        str r0, [r1]

		/* Enter the C code  */
                b       _startup

.endfunc
.end
