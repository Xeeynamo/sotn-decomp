	.IMPORT     _SpMstDrawPrtyBlk
	.IMPORT     _SpDrawPrtyBlkMax
	.IMPORT     _SpMstCmdPos
	.IMPORT     _SpMstCmd
	.IMPORT     _SpSlvCmd
	.IMPORT     _SpCmdTblR
	.IMPORT     _SpCmdNo
	.global		     _SPR_2SetDrawPrty
	.global		     _flushDrawPrtyBlock
	.global		     _sprMemCpyL
	.global		     _sprMemCpyW


	.section	.text
	.align	4
_sprMemCpyL:
	cmp/pl	r6
	BF          MCL_99
MCL_00:
	mov.l       @r5+,r0
	mov.l       r0,@r4
	DT          r6
	BF.s	MCL_00
	ADD         #4,r4
MCL_99:
	rts
	NOP
_sprMemCpyW:
	cmp/pl	r6
	BF          MCW_99
MCW_00:
	mov.w       @r5+,r0
	mov.w       r0,@r4
	DT          r6
	BF.s	MCW_00
	ADD         #2,r4
MCW_99:
	rts
	NOP
_SPR_2SetDrawPrty:
	mov.l       SDP_SpDrawPrtyBlkMax,r1
	mov.l       @r1,r1
	cmp/ge	r1,r4
	BF          SDP_02
	mov	       r1,r4
	ADD         #-1,r4
SDP_02:
	mov.l       SDP_SpMstCmdPos,r5
	mov.l       SDP_SpMstDrawPrtyBlk,r6
	mov.l       @r6,r6
	SHLL2       r4
	ADD         r4,r6
	mov.w       @(0,r6),r0
	EXTS.W      r0,r0
	cmp/eq	#-1,r0
	BF          SDP_00
	mov.l       @r5,r0
	bra	SDP_01
	mov.w       r0,@(0,r6)
SDP_00:
	mov.w       @(2,r6),r0
	EXTU.W      r0,r0
	mov.l       SDP_SpMstCmd,r7
	mov.l       @r7,r7
	SHLL2       r0
	SHLL2       r0
	SHLL        r0
	ADD         r0,r7
	mov.l       @r5,r0
	mov.w       r0,@(2,r7)
SDP_01:
	rts
	mov.w       r0,@(2,r6)
	.align	4
SDP_SpMstDrawPrtyBlk:
	.long	_SpMstDrawPrtyBlk
SDP_SpDrawPrtyBlkMax:
	.long	_SpDrawPrtyBlkMax
SDP_SpMstCmdPos:
	.long	_SpMstCmdPos
SDP_SpMstCmd:
	.long	_SpMstCmd
_flushDrawPrtyBlock:
	mov.l       r14,@-r15
	mov.l       r13,@-r15
	mov.l       r12,@-r15
	mov.l       r11,@-r15
	mov.l       r10,@-r15
	mov.l       r9,@-r15
	mov.l       r8,@-r15
	ADD         #-8,r15
	mov.l       r4,@(0,r15)
	mov.l       r7,@(4,r15)
	MOV	      #-1,r2
	mov.l       FDP_SpMstCmd,r3
	mov.l       @r3,r3
	mov.l       FDP_SpSlvCmd,r4
	mov.l       @r4,r4
	MOV	      #0,r8
	MOV	      #0,r9
	mov.l       FDP_SpCmdNo,r0
	mov.l       @r0,r0
	SHLL2	      r0
	mov.l       FDP_SpCmdTblR,r10
	mov.w       @r10,r10
	EXTS.W      r10,r10
	ADD         r0,r10
	mov.l       FDP_SpMstCmdPos,r0
	mov.l       @r0,r0
	SHLL2	      r0
	mov	       r10,r11
	ADD         r0,r11
	MOV         r4,r0
	cmp/eq	#0,r0
	BF          FDP_20
	mov.l       @(0,r15),r0
FDP_100:
	cmp/eq	#0,r0
	BF          FDP_110
	bra	FDP_EXIT
	NOP
FDP_110:
	mov.w       @(0,r5),r0
	EXTS.W      r0,r7
	mov.w       @(2,r5),r0
	EXTS.W      r0,r14
	mov	       r2,r0
	mov.w       r0,@(0,r5)
	ADD         #4,r5
	cmp/eq	r2,r7
	BT	      FDP_199
	mov		      r7,r1
FDP_101:
	cmp/eq	r1,r14
	BT	      FDP_102
	SHLL2	      r1
	SHLL2	      r1
	SHLL	      r1
	ADD	      r3,r1
	mov		      r1,r12
	mov.w       @(2,r12),r0
	EXTS.W      r0,r0
	mov		      r0,r1
	SHLL2	      r0
	ADD	      r10,r0
	bra	FDP_101
	mov.w       r0,@(2,r12)
FDP_102:
	mov	       r8,r0
	cmp/eq	#0,r0
	BT 	      FDP_108
	mov		      r7,r0
	SHLL2	      r0
	ADD	      r10,r0
	mov.w       r0,@(2,r8)
FDP_108:
	mov	       r9,r0
	cmp/eq	#0,r0
	BF 	      FDP_109
	mov		      r7,r9
	SHLL2	      r9
	ADD	      r10,r9
FDP_109:
	mov		      r14,r8
	SHLL2	      r8
	SHLL2	      r8
	SHLL	      r8
	ADD	      r3,r8
FDP_199:
	mov.l       @(0,r15),r0
	ADD         #-1,r0
	bra	FDP_100
	mov.l       r0,@(0,r15)
FDP_20:
	mov.l       @(0,r15),r0
FDP_00:
	cmp/eq	#0,r0
	BT          FDP_EXIT
	mov.w       @(0,r5),r0
	EXTS.W      r0,r7
	mov.w       @(2,r5),r0
	EXTS.W      r0,r14
	mov	       r2,r0
	mov.w       r0,@(0,r5)
	ADD         #4,r5
	cmp/eq	r2,r7
	BT	      FDP_02
	mov		      r7,r1
FDP_01:
	cmp/eq	r1,r14
	BT	      FDP_02
	SHLL2	      r1
	SHLL2	      r1
	SHLL	      r1
	ADD	      r3,r1
	mov		      r1,r12
	mov.w       @(2,r12),r0
	EXTS.W      r0,r0
	mov		      r0,r1
	SHLL2	      r0
	ADD	      r10,r0
	bra	FDP_01
	mov.w       r0,@(2,r12)
FDP_02:
	mov.w       @(0,r6),r0
	EXTS.W      r0,r12
	mov.w       @(2,r6),r0
	EXTS.W      r0,r13
	mov	       r2,r0
	mov.w       r0,@(0,r6)
	ADD         #4,r6
	cmp/eq	r2,r12
	BT	      FDP_04
	mov		      r12,r1
FDP_03:
	cmp/eq	r1,r13
	BT	      FDP_04
	SHLL2	      r1
	SHLL2	      r1
	SHLL	      r1
	ADD	      r4,r1
	mov		      r1,r2
	mov.w       @(2,r2),r0
	EXTS.W      r0,r0
	mov		      r0,r1
	SHLL2	      r0
	ADD	      r11,r0
	bra	FDP_03
	mov.w       r0,@(2,r2)
FDP_04:
	MOV	      #-1,r2
	cmp/eq	r2,r7
	BT	      FDP_10
	cmp/eq	r2,r12
	BT	      FDP_07
	mov	       r8,r0
	cmp/eq	#0,r0
	BT 	      FDP_05
	mov		      r7,r0
	SHLL2	      r0
	ADD	      r10,r0
	mov.w       r0,@(2,r8)
FDP_05:
	mov		      r14,r1
	SHLL2	      r1
	SHLL2	      r1
	SHLL	      r1
	ADD	      r3,r1
	mov		      r12,r0
	SHLL2	      r0
	ADD	      r11,r0
	mov.w       r0,@(2,r1)
	mov	       r9,r0
	cmp/eq	#0,r0
	BF 	      FDP_06
	mov		      r7,r9
	SHLL2	      r9
	ADD	      r10,r9
FDP_06:
	mov		      r13,r8
	SHLL2	      r8
	SHLL2	      r8
	SHLL	      r8
	bra	FDP_99
	ADD	      r4,r8
FDP_07:
	mov	       r8,r0
	cmp/eq	#0,r0
	BT 	      FDP_08
	mov		      r7,r0
	SHLL2	      r0
	ADD	      r10,r0
	mov.w       r0,@(2,r8)
FDP_08:
	mov	       r9,r0
	cmp/eq	#0,r0
	BF 	      FDP_09
	mov		      r7,r9
	SHLL2	      r9
	ADD	      r10,r9
FDP_09:
	mov		      r14,r8
	SHLL2	      r8
	SHLL2	      r8
	SHLL	      r8
	bra	FDP_99
	ADD	      r3,r8
FDP_10:
	cmp/eq	r2,r12
	BT	      FDP_99
	mov	       r8,r0
	cmp/eq	#0,r0
	BT 	      FDP_11
	mov		      r12,r0
	SHLL2	      r0
	ADD	      r11,r0
	mov.w       r0,@(2,r8)
FDP_11:
	mov	       r9,r0
	cmp/eq	#0,r0
	BF 	      FDP_12
	mov		      r12,r9
	SHLL2	      r9
	ADD	      r11,r9
FDP_12:
	mov		      r13,r8
	SHLL2	      r8
	SHLL2	      r8
	SHLL	      r8
	ADD	      r4,r8
FDP_99:
	mov.l       @(0,r15),r0
	ADD         #-1,r0
	bra	FDP_00
	mov.l       r0,@(0,r15)
FDP_EXIT:
	mov.l	      @(4,r15),r7
	mov.l	      r8,@r7
	mov	       r9,r0
	ADD         #8,r15
	mov.l       @r15+,r8
	mov.l       @r15+,r9
	mov.l       @r15+,r10
	mov.l       @r15+,r11
	mov.l       @r15+,r12
	mov.l       @r15+,r13
	rts
	mov.l       @r15+,r14
	.align	4
FDP_SpMstCmd:
	.long	_SpMstCmd
FDP_SpSlvCmd:
	.long	_SpSlvCmd
FDP_SpCmdTblR:
	.long	_SpCmdTblR
FDP_SpCmdNo:
	.long	_SpCmdNo
FDP_SpMstCmdPos:
	.long	_SpMstCmdPos
