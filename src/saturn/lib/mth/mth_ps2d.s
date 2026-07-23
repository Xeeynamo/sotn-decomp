	.global		 _MTH_Pers2D
	.global		 _MTH_ComputeBright
	.section	.text
	.align	4
	.align	4
_MTH_Pers2D:
	sts.l	mach,@-r15
	sts.l	macl,@-r15
	mov.l	A_DIV,r0
	mov.l   @(8,r4),r1
	mov.l	r1,@r0
	mov.l	IMM_LABEL0,r1
	mov.l	r1,@(16,r0)
	mov.l	IMM_LABEL1,r1
	mov.l	r1,@(20,r0)
	mov.l   @r4+,r1
	mov.l   @r5+,r2
	DMULS.L r1,r2
	STS	mach,r1
	STS	macl,r2
	XTRCT	r1,r2
	mov.l   @r4+,r3
	mov.l   @r5+,r4
	DMULS.L r3,r4
	STS	mach,r3
	STS	macl,r4
	XTRCT	r3,r4
	mov.l	@(20,r0),r1
	DMULS.L r1,r2
	STS	mach,r2
	STS	macl,r3
	XTRCT	r2,r0
	SHLr16	r0
	mov.w	r0,@r6
	DMULS.L r1,r4
	STS	mach,r2
	STS	macl,r3
	XTRCT	r2,r0
	lds.l	@r15+,macl
	lds.l	@r15+,mach
	SHLr16	r0
	rts
	mov.w	r0,@(2,r6)
	.align	4
IMM_LABEL0:
	.long	1
IMM_LABEL1:
	.long	0

	.align	4
A_DIV:	.long	-256
	.align	4
_MTH_ComputeBright:
	STS	mach,r1
	STS	macl,r2
	CLRMAC
	MAC.L   @r4+,@r5+
	MAC.L   @r4+,@r5+
	MAC.L   @r4+,@r5+
	STS	mach,r3
	STS	macl,r0
	ADD	#1,r3
	XTRCT	r3,r0
	MOV	#16,r3
	DMULS.L r3,r0
	STS	mach,r3
	STS	macl,r0
	SHLr16	r0
	LDS	r1,mach
	LDS	r2,macl
	rts
	AND	#31,r0
	NOP
