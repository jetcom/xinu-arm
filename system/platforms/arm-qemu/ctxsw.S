/**
 * @file     ctxsw.S
 * @provides ctxsw.
 *
 */

/* the size of the context record in bytes */
#define CONTEXT_SIZE 64

.text
    .align 4
    .global    ctxsw

/*------------------------------------------------------------------------
 *  ctxsw  -  Switch from one thread context to another.
 *------------------------------------------------------------------------
 */
    .type ctxsw, %function
ctxsw:
    /* build context record on stack                               */
    stmfd sp!, {lr} /* Stores the return address */
    stmfd sp!, {lr} /* Stores the link register */
    sub sp, sp, #16 /* Skip over space where arguments would be stored */
    /* save callee-save ("non-volatile") registers                 */
    stmfd sp!, {v1, v2, v3, v4, v5, v6, v7, v8}
    /* save outgoing stack pointer                                 */
    str sp, [a1, #0]
    /* load incoming stack pointer                                 */
    ldr sp, [a2, #0]

    /* TEB: Re-enable interrupts and clear the timer interrupt */ 
    mrs r0, cpsr
    bic r0, r0, #0x80
    msr cpsr_c, r0

    ldr r1, =0x1014000C 
    mov r0, #1
    STR r0, [r1]

    /* restore callee-save ("non-volatile") registers              */
    ldmfd sp!, {v1, v2, v3, v4, v5, v6, v7, v8}
    /* restore address registers */
    ldmfd sp!, {a1, a2, a3, a4}
    /* restore link register (sometimes means passing INITRET) */
    ldmfd sp!, {lr}
    /* return (sometimes means calling procaddr()) */
    ldmfd sp!, {pc}
    .end ctxsw

