	.IMPORT     _MTH_Sin
	.IMPORT     _MTH_Cos
	.IMPORT     _MTH_Mul
	.IMPORT     unitMatrix
	.global		     _MTH_InitialMatrix
	.global		     _MTH_ClearMatrix
	.global		     _MTH_PushMatrix
	.global		     _MTH_PopMatrix
	.global		     _MTH_MoveMatrix
	.global		     _MTH_RotateMatrixX
	.global		     _MTH_RotateMatrixY
	.global		     _MTH_RotateMatrixZ
	.global		     _MTH_ReverseZ
	.global		     _MTH_MulMatrix
	.global		     _MTH_CoordTrans
	.global		     _MTH_NormalTrans
	.section	.text
	.align	4
_MTH_InitialMatrix:
	sts.l       pr,@-r15
	mov.w       r5,@r4
	mov.l       r6,@(8,r4)
	mov.l       r6,@(4,r4)
	bra	_MTH_ClearMatrix
	lds.l       @r15+,pr
_MTH_ClearMatrix:
	mov.l       cm_unitMatrix,r6
	mov.l       @(4,r4),r5
	MOV         #12,r0
cm_0:
	mov.l         @r6+,r1
	mov.l         r1,@r5
	DT          r0
	BF.s	cm_0
	ADD         #4,r5
	rts
	NOP
	.align	4
cm_unitMatrix:
	.long	unitMatrix
_MTH_PushMatrix:
	mov.l       @(4,r4),r6
	mov.l       @(4,r4),r5
	ADD         #48,r5
	MOV         r5,r2
	MOV         #12,r0
pm_0:
	mov.l         @r6+,r1
	mov.l		r1,@r5
	DT          r0
	BF.s	pm_0
	ADD         #4,r5
	rts
	mov.l       r2,@(4,r4)
_MTH_PopMatrix:
	mov.l       @(4,r4),r3
	ADD         #-48,r3
	rts
	mov.l       r3,@(4,r4)
_MTH_MoveMatrix:
	mov.l       @(4,r4),r3
	mov.l       r7,@-r15
	mov.l       r6,@-r15
	mov.l       r5,@-r15
	STS       mach,r6
	STS       macl,r7
	MOV         r15,r4
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	MOV         r3,r2
	mov.l       @r3+,r1
	ADD         r0,r1
	mov.l       r1,@r2
	MOV         r15,r4
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	MOV         r3,r2
	mov.l       @r3+,r1
	ADD         r0,r1
	mov.l       r1,@r2
	MOV         r15,r4
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       @r3,r1
	ADD         r0,r1
	ADD         #12,r15
	LDS       r6,mach
	LDS		r7,macl
	rts
	mov.l       r1,@r3
_MTH_RotateMatrixX:
	mov.l       r8,@-r15
	mov.l       r9,@-r15
	mov.l       r10,@-r15
	sts.l       pr,@-r15
	sts.l       macl,@-r15
	sts.l       mach,@-r15
	MOV         r4,r8
	MOV         r5,r9
	mov.l       rmx_MTH_Sin,r3
	JSR         @r3
	MOV         r9,r4
	MOV         r0,r10
	mov.l       rmx_MTH_Cos,r3
	JSR         @r3
	MOV         r9,r4
	mov.l       @(4,r8),r6
	mov.l       r0,@-r15
	NEG         r10,r1
	mov.l       r1,@-r15
	MOV         r15,r8
	mov.l       r10,@-r15
	mov.l       r0,@-r15
	MOV         r15,r7
	mov.l       @(8,r6),r0
	mov.l       r0,@-r15
	mov.l       @(4,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(4,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(8,r6)
	ADD         #8,r15
	mov.l       @(24,r6),r0
	mov.l       r0,@-r15
	mov.l       @(20,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(20,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(24,r6)
	ADD         #8,r15
	mov.l       @(40,r6),r0
	mov.l       r0,@-r15
	mov.l       @(36,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(36,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(40,r6)
	ADD         #24,r15
	lds.l       @r15+,mach
	lds.l       @r15+,macl
	lds.l       @r15+,pr
	mov.l       @r15+,r10
	mov.l       @r15+,r9
	rts
	mov.l       @r15+,r8
	.align	4
rmx_MTH_Sin:
	.long	_MTH_Sin
rmx_MTH_Cos:
	.long	_MTH_Cos
_MTH_RotateMatrixY:
	mov.l       r8,@-r15
	mov.l       r9,@-r15
	mov.l       r10,@-r15
	sts.l       pr,@-r15
	sts.l       macl,@-r15
	sts.l       mach,@-r15
	MOV         r4,r8
	MOV         r5,r9
	mov.l       rmy_MTH_Sin,r3
	JSR         @r3
	MOV         r9,r4
	MOV         r0,r10
	mov.l       rmy_MTH_Cos,r3
	JSR         @r3
	MOV         r9,r4
	mov.l       @(4,r8),r6
	mov.l       r0,@-r15
	mov.l       r10,@-r15
	MOV         r15,r8
	NEG         r10,r1
	mov.l       r1,@-r15
	mov.l       r0,@-r15
	MOV         r15,r7
	mov.l       @(8,r6),r0
	mov.l       r0,@-r15
	mov.l       @(0,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(0,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(8,r6)
	ADD         #8,r15
	mov.l       @(24,r6),r0
	mov.l       r0,@-r15
	mov.l       @(16,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(16,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(24,r6)
	ADD         #8,r15
	mov.l       @(40,r6),r0
	mov.l       r0,@-r15
	mov.l       @(32,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(32,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(40,r6)
	ADD         #24,r15
	lds.l       @r15+,mach
	lds.l       @r15+,macl
	lds.l       @r15+,pr
	mov.l       @r15+,r10
	mov.l       @r15+,r9
	rts
	mov.l       @r15+,r8
	.align	4
rmy_MTH_Sin:
	.long	_MTH_Sin
rmy_MTH_Cos:
	.long	_MTH_Cos
_MTH_RotateMatrixZ:
	mov.l       r8,@-r15
	mov.l       r9,@-r15
	mov.l       r10,@-r15
	sts.l       pr,@-r15
	sts.l       macl,@-r15
	sts.l       mach,@-r15
	MOV         r4,r8
	MOV         r5,r9
	mov.l       rmz_MTH_Sin,r3
	JSR         @r3
	MOV         r9,r4
	MOV         r0,r10
	mov.l       rmz_MTH_Cos,r3
	JSR         @r3
	MOV         r9,r4
	mov.l       @(4,r8),r6
	mov.l       r0,@-r15
	NEG         r10,r1
	mov.l       r1,@-r15
	MOV         r15,r8
	mov.l       r10,@-r15
	mov.l       r0,@-r15
	MOV         r15,r7
	mov.l       @(4,r6),r0
	mov.l       r0,@-r15
	mov.l       @(0,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(0,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(4,r6)
	ADD         #8,r15
	mov.l       @(20,r6),r0
	mov.l       r0,@-r15
	mov.l       @(16,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(16,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(20,r6)
	ADD         #8,r15
	mov.l       @(36,r6),r0
	mov.l       r0,@-r15
	mov.l       @(32,r6),r0
	mov.l       r0,@-r15
	MOV         r15,r9
	MOV         r7,r4
	MOV         r9,r3
	CLRMAC
	MAC.L       @r3+,@r4+
	MAC.L       @r3+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(32,r6)
	MOV         r8,r4
	CLRMAC
	MAC.L       @r9+,@r4+
	MAC.L       @r9+,@r4+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(36,r6)
	ADD         #24,r15
	lds.l       @r15+,mach
	lds.l       @r15+,macl
	lds.l       @r15+,pr
	mov.l       @r15+,r10
	mov.l       @r15+,r9
	rts
	mov.l       @r15+,r8
	.align	4
rmz_MTH_Sin:
	.long	_MTH_Sin
rmz_MTH_Cos:
	.long	_MTH_Cos
_MTH_ReverseZ:
	mov.l       @(4,r4),r6
	mov.l       @(8,r6),r0
	NEG         r0,r0
	mov.l       r0,@(8,r6)
	mov.l       @(24,r6),r0
	NEG         r0,r0
	mov.l       r0,@(24,r6)
	mov.l       @(40,r6),r0
	NEG         r0,r0
	rts
	mov.l       r0,@(40,r6)
_MTH_MulMatrix:
	sts.l       mach,@-r15
	sts.l       macl,@-r15
	mov.l       @(32,r5),r0
	mov.l       r0,@-r15
	mov.l       @(16,r5),r0
	mov.l       r0,@-r15
	mov.l       @(0,r5),r0
	mov.l       r0,@-r15
	MOV         r4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(0,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(16,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(32,r6)
	ADD         #12,r15
	mov.l       @(36,r5),r0
	mov.l       r0,@-r15
	mov.l       @(20,r5),r0
	mov.l       r0,@-r15
	mov.l       @(4,r5),r0
	mov.l       r0,@-r15
	MOV         r4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(4,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(20,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(36,r6)
	ADD         #12,r15
	mov.l       @(40,r5),r0
	mov.l       r0,@-r15
	mov.l       @(24,r5),r0
	mov.l       r0,@-r15
	mov.l       @(8,r5),r0
	mov.l       r0,@-r15
	MOV         r4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(8,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(24,r6)
	ADD         #4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(40,r6)
	ADD         #12,r15
	MOV         #1,r0
	SHLL16      r0
	mov.l       r0,@-r15
	mov.l       @(44,r5),r0
	mov.l       r0,@-r15
	mov.l       @(28,r5),r0
	mov.l       r0,@-r15
	mov.l       @(12,r5),r0
	mov.l       r0,@-r15
	MOV         r4,r2
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(12,r6)
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       r0,@(28,r6)
	MOV         r15,r3
	CLRMAC
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	MAC.L       @r2+,@r3+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	ADD         #16,r15
	lds.l       @r15+,macl
	lds.l       @r15+,mach
	rts
	mov.l       r0,@(44,r6)
_MTH_CoordTrans:
	STS		mach,r2
	STS		macl,r3
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       @r4+,r1
	ADD         r0,r1
	mov.l       r1,@(0,r6)
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       @r4+,r1
	ADD         r0,r1
	mov.l       r1,@(4,r6)
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	mov.l       @r4+,r1
	ADD         r0,r1
	LDS		r2,mach
	LDS		r3,macl
	rts
	mov.l       r1,@(8,r6)
_MTH_NormalTrans:
	STS		mach,r2
	STS       macl,r3
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	ADD         #4,r4
	mov.l       r0,@(0,r6)
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	ADD         #4,r4
	mov.l       r0,@(4,r6)
	MOV         r5,r7
	CLRMAC
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	MAC.L       @r4+,@r7+
	STS	      mach,r1
	STS	      macl,r0
	XTRCT	      r1,r0
	LDS       r2,mach
	LDS       r3,macl
	rts
	mov.l       r0,@(8,r6)
