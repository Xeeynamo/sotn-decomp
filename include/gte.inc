# GTE macros

.macro RTPS
		.word	0x4A180001
.endm

.macro RTPT
		.word	0x4A280030
.endm

.macro DPCL
		.word	0x4A680029
.endm

.macro DPCS
		.word	0x4A780010
.endm

.macro DPCT
		.word	0x4AF8002A
.endm

.macro INTPL
		.word	0x4A980011
.endm

.macro NCS
		.word	0x4AC8041E
.endm

.macro NCT
		.word	0x4AD80420
.endm

.macro NCDS
		.word	0x4AE80413
.endm

.macro NCDT
		.word	0x4AF80416
.endm

.macro NCCS
		.word	0x4B08041B
.endm

.macro NCCT
		.word	0x4B18043F
.endm

.macro CDP
		.word	0x4B280414
.endm

.macro CC
		.word	0x4B38041C
.endm

.macro NCLIP
		.word	0x4B400006
.endm

.macro AVSZ3
		.word	0x4B58002D
.endm

.macro AVSZ4
		.word	0x4B68002E
.endm

.macro MVMVA sf, mx, v, cv, lm
		.word	0x4A400012|\sf<<19|\mx<<17|\v<<15|\cv<<13|\lm<<10
.endm

.macro SQR sf
		.word	0x4AA00428|\sf<<19
.endm

.macro OP sf
		.word	0x4B70000C|\sf<<19
.endm

.macro GPF sf
		.word	0x4B90003D|\sf<<19
.endm

.macro GPL sf
		.word	0x4BA0003E|\sf<<19
.endm
