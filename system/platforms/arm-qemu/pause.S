/**
 * @file     pause.S
 * @provides pause.
 * Platform-dependent code for idling the processor
 */

.text
	.align 4	
	.global pause

/**
 * @fn void pause(void)
 * 
 * Enter some kind of powerdown state (if it exists) that suspends
 * execution until an interrupt is detected.
 */
	.type pause, %function
pause:
	wfi /* wait for interrupt */
	mov	pc, lr
	.end pause

