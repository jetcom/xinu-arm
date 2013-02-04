/**
 * @file     ctxsw.S
 * @provides ctxsw.
 *
 */

/* the size of the context record in bytes */
#define CONTEXT_SIZE 64

.file __FILE__

.text
    .align 4
    .global    ctxsw

/*------------------------------------------------------------------------
 *  ctxsw  -  Switch from one thread context to another.
 *------------------------------------------------------------------------
 */
    .type ctxsw, %function
ctxsw:
	/*
	 * Preconditions:
	 *     - Processor must be in system mode.
	 *
	 *     Really, it doesn't matter what mode we're in, but all calls to
	 *     ctxsw() must be done in the same ARM processor mode so that we
	 *     can rely on having the same banked registers (sp and lr).  We've
	 *     decided that system mode is the mode that this must always be
	 *     called in.
	 */

	/* Store all registers. */
	/* We save lr twice because new processes can branch two ways:
	 * - proceed to their first instruction, via pc.
	 * - return via lr, which points to INTIRET. This puts kill() at the
	 *   bottom of the call stack, so that we can reap a process when it's
	 *   terminated.
	 * All of this is set-up for us in create(), which builds the context
	 * for new processes.
	 *
	 * Existing processes don't get a choice, they have to return to where
	 * lr tells them to. We push lr twice for existing process so that it's
	 * balanced with the pops, lower down in this function.
	 */
	push	{lr}
	push	{lr}
	push	{r0-ip}
	/* Notice, we don't push sp, that's handled by resched(). */

	/* Save sp to location given in argument 1, but only if the address is
	 * non-null. */
	cmp	r0, #0			@ Null address?
	strne	sp, [r0, #0]		@ Nope, store it!

	/* Restore all of the registers, for the new thread. */
	cmp	r1, #0
	/* TODO: If there is no new stack pointer, we should consider panicking
	 * here.  For now, if the new stack isn't valid, we'll just not change
	 * stacks. */
	ldrne	sp, [r1, #0]

	/* Restore all of the registers. */
	pop	{r0-ip}
	pop	{lr}
	pop	{pc}
    .end ctxsw
