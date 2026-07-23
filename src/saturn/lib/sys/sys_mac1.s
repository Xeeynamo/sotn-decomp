	.global		 _SYS_GetMac
	.global		 _SYS_SetMac
	.section	.text
	.align	4
_SYS_GetMac:
	ADD     #8,r4
	sts.l   macl,@-r4
	rts
	sts.l   mach,@-r4
_SYS_SetMac:
	lds.l   @r4+,mach
	rts
	lds.l   @r4+,macl
