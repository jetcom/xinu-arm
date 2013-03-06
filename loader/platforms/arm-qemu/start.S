/******************************************************************************
 *
 * startup code
 * 
 * 
 * keith.ohara@gatech.edu
 * April 2008
 * IPRE Fluke Firmware
 * http://www.raspberrypi.org/phpBB3/viewtopic.php?t=23149&p=217231
 *
 ******************************************************************************/

#include <platform-local.h>
/* Vectored Interrupt Controller */
#include <pl190.h>

#define S_FRAME_SIZE 72
#define S_PC    60

/* Stack Sizes */
.set  UND_STACK_SIZE, 0x00000004		/* stack for "undefined instruction" interrupts is 4 bytes  */
.set  ABT_STACK_SIZE, 0x00000004		/* stack for "abort" interrupts is 4 bytes                  */
.set  FIQ_STACK_SIZE, 0x00000004		/* stack for "FIQ" interrupts  is 4 bytes         	    */
.set  IRQ_STACK_SIZE, 0X00000200		/* stack for "IRQ" normal interrupts is 4 bytes    	    */
.set  SVC_STACK_SIZE, 0x00000004		/* stack for "SVC" supervisor mode is 4 bytes  		    */
.set  SYS_STACK_SIZE, 0x00002000                /* stack for "SYS" (user) mode is 8192 bytes (nulluser task/thread) */


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
.global IRQ_STACK_START
.global _start
.func   _start

_start:

# Exception Vectors

_vectors:       
                b       Reset_Addr         
                ldr     PC, Undef_Addr
                ldr     PC, SWI_Addr
                ldr     PC, PAbt_Addr
                ldr     PC, DAbt_Addr
                ldr     PC, unused_handler
                LDR     PC, IRQ_Addr

                ldr     PC, FIQ_Addr

Reset_Addr:     .word   Reset_Handler		/* defined in this module below  */
Undef_Addr:     .word   UNDEF_Routine		/* defined in main.c  */
SWI_Addr:       .word   SWI_Routine		/* defined in main.c  */
PAbt_Addr:      .word   PAbt_Routine		/* defined in main.c  */
DAbt_Addr:      .word   DAbt_Routine		/* defined in main.c  */
FIQ_Addr:       .word   FIQ_Routine		/* defined in main.c  */
IRQ_Addr:       .word   IRQ_Routine
unused_handler: .word   UNDEF_Routine
                .word   0			/* rounds the vectors and ISR addresses to 64 bytes total  */

		/*.=.+0x1C0			*//* skip past Philips ISP ram usage (all the way to 0x40000200) */

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

/* TEB TODO: This will need to be revisted when we get a real memory map */
		/* Copy .data section (Copy from ROM to RAM) */
                /*ldr     R1, =_etext
                ldr     R2, =_data
                ldr     R3, =_edata
1:        	cmp     R2, R3
                ldrlo   R0, [R1], #4
                strlo   R0, [R2], #4
                blo     1b
*/


/* relocate exception vectors */
/* http://www.redacom.ch/software/arm_keil/docs_infopage/documents/arm_information/rvct_developer_guide.pdf */
                MOV        r8, #0
                ADR        r9, _vectors
                LDMIA      r9!,{r0-r7}           /* Copy the vectors (8 words) */
                STMIA      r8!,{r0-r7}
                LDMIA      r9!,{r0-r7}           /* Copy the DCD'ed addresses*/
                STMIA      r8!,{r0-r7}           /* (8 words again) */


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

.type panic_no_isr, %function
/*
 * Panic, since the the ISR that the VIC has given us is null.
 */
panic_no_isr:
	ldr	r1, [r0, #VIC_IRQ_STATUS]
	ldr	r0, panic_no_isr_str_ptr
	mov	r2, #0
	bl	kprintf
	b	halt
.section	.rodata
panic_no_isr_str:
	.asciz "Panic: Null interrupt handler! VIC_IRQ_STATUS: 0x%x\n"
.text
panic_no_isr_str_ptr:	.word	panic_no_isr_str


IRQ_Routine:
	/*
	 * With pipelining on ARM, the PC is 2 instructions (8 bytes) ahead of
	 * where we're currently executing. Usually the 'bl' instruction will
	 * subtract 4 from the PC before storing it in LR, but since we came in
	 * here via an exception we must do it ourselves.
	 */
	sub	lr, lr, #4

	/* Store lr_irq and the SPSR on the user stack */
	push	{r0}
	sub	sp, sp, #4
	stmia	sp, {sp}^		@ Grab sp_usr
	ldmfd	sp, {r0}		@ And load it into r0
	add	sp, sp, #4

	sub	r0, r0, #4
	stmia	r0, {lr}		@ Store lr_irq
	mrs	lr, spsr
	sub	r0, r0, #4
	stmia	r0, {lr}		@ Store the spsr
	pop	{r0}

	msr	cpsr, #MODE_SYS|I_BIT	@ Switch to sysmode, keep irq disabled

	/*
	 * When we saved the lr_irq and the SPSR earlier, we weren't able to
	 * modify the user mode stack pointer. Now we can adjust sp_usr to
	 * account for what is effectively a 'push {spsr,lr_irq}'.
	 */
	sub	sp, sp, #8		@ Make room for lr_irq and SPSR
	push	{r0-r3,r12,r14}		@ Push APCS registers

       /* Call the ISR */
       LDR    r0, =VIC_BASE_ADDRESS
       LDR    r1, [r0, #VIC_VEC_ADDR] /* Discover source of interrupt */
       cmp    r1, #0
       beq    panic_no_isr
       blx    r1

       /* This is the responsibility of the C IRQ-Handler */
#if 0
       LDR r1, =(VIC_BASE_ADDRESS + VIC_VEC_ADDR)
       STR r0, [r1]             /* Acknowledge Vectored IRQ has been serviced */
#endif

	pop	{r0-r3,r12,r14}		@ Push APCS registers

	/*
	 * Prematurely 'pop' here, since we can't modify sp_usr in IRQ mode when we
	 * really do restore lr_irq and SPSR.
	 */
	add	sp, sp, #8

	/* Switch back to IRQ mode to use sp_irq again; keep interrupts disabled. */
	msr	cpsr, #MODE_IRQ|I_BIT

	/* Load lr_irq from the user stack */
	push	{r0}
	sub	sp, sp, #4
	stmia	sp, {sp}^		@ Grab sp_usr
	ldmfd	sp, {r0}		@ And load it into r0
	add	sp, sp, #4

	sub	r0, r0, #8		@ Undo the premature add from earlier
	ldmfd	r0, {lr}
	msr	spsr_cxsf, lr		@ Restore spsr
	add	r0, r0, #4
	ldmfd	r0, {lr}		@ Restore lr_isr
	add	r0, r0, #4		@ nop
	pop	{r0}

	/* Restore cpsr and return. */
	subs	pc, lr, #0		@ Special ISR return instruction

.endfunc
.end
