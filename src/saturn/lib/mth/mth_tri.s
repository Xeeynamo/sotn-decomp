	.global		     _MTH_Sin
	.global		     _MTH_Cos
	.global		     _MTH_Atan
	.global		     _fsin
	.global		     _fcos
	.section	.text
	.align	4
_MTH_Sin:
	mov.l       r14,@-r15
	sts.l       pr,@-r15
	cmp/pz	r4
	BT.s	sin_0
	MOV         #0,r14
	MOV         #1,r14
	NEG         r4,r4
sin_0:
	mov.l       sin_f180,r2
	cmp/ge	r2,r4
	BF          sin_1
	bra	sin_2
	MOV         #0,r4
sin_1:
	mov.l       sin_f90,r3
	cmp/gt	r3,r4
	BF          sin_2
	SUB         r4,r2
	MOV         r2,r4
sin_2:
	mov.l       fsin,r3
	JSR         @r3
	NOP
	TST         r14,r14
	BT          sin_3
	NEG         r0,r0
sin_3:
	lds.l       @r15+,pr
	rts
	mov.l       @r15+,r14
	.align	4
sin_f180:	.long	11796480
sin_f90:	.long	5898240
fsin:	.long	_fsin
_MTH_Cos:
	mov.l       r14,@-r15
	sts.l       pr,@-r15
	cmp/pz	r4
	BT          cos_0
	NEG         r4,r4
cos_0:
	mov.l       cos_f180,r2
	cmp/ge	r2,r4
	BF.s	cos_1
	MOV         #1,r14
	bra	cos_4
	MOV         #0,r4
cos_1:
	mov.l       cos_f90,r2
	cmp/gt	r2,r4
	BF          cos_2
	mov.l       cos_f180,r2
	SUB         r4,r2
	bra	cos_4
	MOV         r2,r4
cos_2:
	MOV         #0,r14
cos_4:
	mov.l       fcos,r3
	JSR         @r3
	NOP
	TST         r14,r14
	BT          cos_5
	NEG         r0,r0
cos_5:
	lds.l       @r15+,pr
	rts
	mov.l       @r15+,r14
	.align	4
cos_f180:	.long	11796480
cos_f90:	.long	5898240
fcos:	.long	_fcos
_fcos:
	mov.l	NINTY,r2
	NEG	r4,r4
	ADD	r2,r4
_fsin:
	MOVA	SINTBL,r0
	STS	macl,r3
	SWAP.W	r4,r1
	EXTU.W	r1,r1
	SHLL2	r1
	mov.w	@(r0,r1),r2
	ADD	#2,r0
	MULU	r4,r2
	mov.w	@(r0,r1),r0
	STS	macl,r2
	EXTU.W	r0,r0
	LDS	r3,macl
	SWAP.W	r2,r2
	EXTU.W	r2,r2
	rts
	ADD	r2,r0
	.align	4
NINTY:	.long	5898240
SINTBL:
	.short	1143,0
	.short	1144,1143
	.short	1142,2287
	.short	1142,3429
	.short	1140,4571
	.short	1139,5711
	.short	1136,6850
	.short	1134,7986
	.short	1132,9120
	.short	1128,10252
	.short	1124,11380
	.short	1121,12504
	.short	1117,13625
	.short	1112,14742
	.short	1107,15854
	.short	1103,16961
	.short	1096,18064
	.short	1091,19160
	.short	1085,20251
	.short	1078,21336
	.short	1072,22414
	.short	1064,23486
	.short	1056,24550
	.short	1049,25606
	.short	1041,26655
	.short	1033,27696
	.short	1023,28729
	.short	1015,29752
	.short	1005,30767
	.short	995,31772
	.short	986,32767
	.short	975,33753
	.short	965,34728
	.short	954,35693
	.short	942,36647
	.short	932,37589
	.short	919,38521
	.short	907,39440
	.short	896,40347
	.short	882,41243
	.short	870,42125
	.short	857,42995
	.short	843,43852
	.short	830,44695
	.short	815,45525
	.short	802,46340
	.short	787,47142
	.short	773,47929
	.short	758,48702
	.short	743,49460
	.short	728,50203
	.short	712,50931
	.short	696,51643
	.short	680,52339
	.short	664,53019
	.short	648,53683
	.short	632,54331
	.short	614,54963
	.short	598,55577
	.short	580,56175
	.short	564,56755
	.short	545,57319
	.short	529,57864
	.short	510,58393
	.short	492,58903
	.short	475,59395
	.short	456,59870
	.short	437,60326
	.short	420,60763
	.short	400,61183
	.short	382,61583
	.short	363,61965
	.short	344,62328
	.short	325,62672
	.short	305,62997
	.short	287,63302
	.short	267,63589
	.short	247,63856
	.short	228,64103
	.short	209,64331
	.short	189,64540
	.short	169,64729
	.short	149,64898
	.short	129,65047
	.short	110,65176
	.short	90,65286
	.short	70,65376
	.short	50,65446
	.short	30,65496
	.short	10,65526
	.short	0,65535
_MTH_Atan:
	mov.l       r14,@-r15
	mov.l       r13,@-r15
	mov.l       r12,@-r15
	mov.l       r11,@-r15
	mov.l       r10,@-r15
	mov.l       r9,@-r15
	sts.l	      mach,@-r15
	sts.l	      macl,@-r15
	MOV         r5,r10
	sts.l       pr,@-r15
	mov.l       rTanTbl,r11
	cmp/pz	r10
	BT.s	atan_0
	MOV         r4,r12
	NEG         r10,r5
atan_0:
	cmp/pz	r12
	BT          atan_2
	NEG         r12,r4
atan_2:
	MOV         #65,r2
	cmp/ge	r2,r5
	BT          atan_4
	mov.l       atan_fmax,r13
	bra	atan_5
	NOP
atan_4:
	mov.l	      A_DIV,r0
	SWAP.W      r4,r2
	mov.l	      r5,@r0
	EXTS.W      r2,r2
	mov.l	      r2,@(16,r0)
	SHLL16      r4
	mov.l	      r4,@(20,r0)
	mov.l	      @(20,r0),r13
atan_5:
	MOV         #0,r4
	MOV         #90,r5
atan_6:
	MOV         r4,r14
	ADD         r5,r14
	SHAR        r14
	MOV         r14,r0
	SHLL2       r0
	SHLL        r0
	mov.l       @(r0,r11),r2
	cmp/gt	r13,r2
	BT          atan_7
	MOV         r14,r4
	ADD         #1,r4
	MOV         r4,r0
	SHLL2       r0
	SHLL        r0
	mov.l       @(r0,r11),r3
	cmp/ge	r3,r13
	BT          atan_8
	bra	atan_9
	NOP
atan_7:
	MOV         r14,r5
atan_8:
	cmp/ge	r5,r4
	BF          atan_6
atan_9:
	MOV         r14,r0
	MOV         r13,r4
	SHLL2       r0
	SHLL        r0
	mov.l       @(r0,r11),r3
	SUB         r3,r4
	ADD         #4,r0
	mov.l       @(r0,r11),r5
	DMULS.L     r4,r5
	STS	      mach,r3
	STS	      macl,r4
	XTRCT	      r3,r4
	mov.l       atan_f1,r2
	cmp/gt	r2,r4
	BF          atan_10
	mov.l       atan_f1,r4
atan_10:
	MOV  	      r14,r0
	SHLL16      r0
	cmp/pz	r12
	BT.s	atan_11
	ADD         r0,r4
	NEG         r4,r4
atan_11:
	cmp/pz	r10
	BT          atan_14
	cmp/pz	r12
	BF          atan_12
	mov.l       atan_f180,r2
	bra	atan_13
	NOP
atan_12:
	mov.l       atan_fm180,r2
atan_13:
	SUB         r4,r2
	MOV         r2,r4
atan_14:
	MOV         r4,r0
	lds.l       @r15+,pr
	lds.l	      @r15+,macl
	lds.l	      @r15+,mach
	mov.l       @r15+,r9
	mov.l       @r15+,r10
	mov.l       @r15+,r11
	mov.l       @r15+,r12
	mov.l       @r15+,r13
	rts
	mov.l       @r15+,r14
	.align	4
A_DIV:
	.long	-256
rTanTbl:
	.long	tanTbl
atan_fmax:
	.long	2147418112
atan_f1:
	.long	65536
atan_f180:
	.long	11796480
atan_fm180:
	.long	-11796480
tanTbl:
	.long	0,3754554,1143,3752267,2288,3747696,3434,3740845,4582,3731724,5733,3720344,6888,3706719,8046,3690864,9210,3672800,10379,3652548,11555,3630133,12738,3605583,13930,3578927,15130,3550198,16339,3519431,17560,3486663,18792,3451934,20036,3415287,21293,3376766,22565,3336418,23853,3294292,25156,3250440,26478,3204915,27818,3157772,29178,3109069,30559,3058866,31964,3007223,33392,2954203,34846,2899871,36327,2844294,37837,2787538,39378,2729673,40951,2670770,42559,2610899,44204,2550136,45888,2488552,47614,2426223,49384,2363226,51202,2299637,53070,2235533,54991,2170993,56969,2106094,59008,2040917,61113,1975541,63287,1910045,65536,1844509,67864,1779013,70278,1713637,72785,1648460,75390,1583561,78102,1519021,80930,1454917,83882,1391328,86969,1328331,90202,1266002,93595,1204418,97161,1143654,100916,1083784,104879,1024881,109070,967016,113511,910260,118230,854683,123255,800351,128621,747331,134368,695688,140542,645485,147196,596782,154393,549639,162207,504114,170727,460262,180058,418136,190330,377788,201699,339267,214358,302620,228551,267891,244583,235123,262850,204356,283867,175627,308322,148971,337153,124421,371673,102006,413778,81754,466312,63690,533747,47835,623533,34210,749079,22829,937208,13709,1250501,6858,1876705,2287,3754554,261,2147483647,0
