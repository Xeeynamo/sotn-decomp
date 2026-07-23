	.global		 _MTH_Mul
	.global		 _MTH_Div
	.global			_MTH_IntToFixed
	.global			_MTH_FixedToInt
	.global			_MTH_Product
	.section	.text
	.align	4
	.align	4
_MTH_Mul:
	STS	mach,r1
	STS	macl,r2
	DMULS.L r4,r5
	STS	mach,r3
	STS	macl,r0
	LDS	r1,mach
	LDS	r2,macl
	rts
	XTRCT	r3,r0
	.align	4
_MTH_Div:
	mov.l	A_DIV,r0
	SWAP.W	r4,r2
	mov.l	r5,@r0
	EXTS.W	r2,r2
	mov.l	r2,@(16,r0)
	SHLL16	r4
	mov.l	r4,@(20,r0)
	rts
	mov.l	@(20,r0),r0
	.align	4
_MTH_IntToFixed:
	MOV  	r4,r0
	rts
	SHLL16	r0
	.align	4
_MTH_FixedToInt:
	MOV  	r4,r0
	SHLr16	r0
	rts
	EXTS.W	r0,r0
	.align	4
_MTH_Product:
	STS	mach,r1
	STS	macl,r2
	MOV	#0,r0
	LDS	r0,mach
	LDS	r0,macl
	MAC.L   @r4+,@r5+
	MAC.L   @r4+,@r5+
	MAC.L   @r4+,@r5+
	STS	mach,r3
	STS	macl,r0
	LDS	r1,mach
	LDS	r2,macl
	rts
	XTRCT	r3,r0
	.align	4
__divls:
	mov.l	r3,@-r15
	MOV	#240,r3
	stc.l	sr,@-r15
	EXTU.B	r3,r3
	LDC	r3,sr
	mov.l	A_DIV,r3
	mov.l	r0,@r3
	NOP
	mov.l	r1,@(4,r3)
	NOP
	mov.l	@(20,r3),r0
	NOP
	ldc.l	@r15+,sr
	mov.l	@r15+,r3
	rts
	MOV	r0,r1
	.align	4
A_DIV:	.long	-256
