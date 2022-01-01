.include "macro.inc"
.set noat
.set noreorder
.align 4
.section .text

.macro syscalldef label Sect Func
    .global \label
    \label:
	addiu	$t2, $zero, \Sect
	jr	$t2
	addiu	$t1, $zero, \Func
	nop
.endm

.macro exceptiondef label Func
    .global \label
    \label:
	addiu	$a0, $zero, \Func
	syscall	
	jr	$ra
	nop
.endm
