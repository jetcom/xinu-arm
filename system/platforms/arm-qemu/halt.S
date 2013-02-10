/*
 * A low power halt routine.
 */

/* When the I bit is high, interrupts are disabled. */
.set PSR_I_BIT, 0x80

/* When the F bit is high, fast interrupts are disabled. */
.set PSR_F_BIT, 0x40

.text
.align 4
.global halt
.type halt, %function

halt:
	msr cpsr, #(PSR_I_BIT | PSR_F_BIT)	@ Diable interrupts
	wfi
	b halt
