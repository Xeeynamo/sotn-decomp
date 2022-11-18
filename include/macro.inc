.macro glabel label
    .global \label
    \label:
.endm

.macro .def #
.endm

.macro li reg, num
.if \num < 0x8000 && \num > 0
  ori \reg, $0, \num & 0xFFFF
.elseif \num > 0xFFFF
  lui \reg, %hi(\num)
.elseif \num > 0
  ori \reg, $0, \num & 0xFFFF
.elseif \num == -0x8000
  addiu \reg, $0, \num & 0xFFFF
.elseif \num > -0x8000
  addiu \reg, $0, \num
.else
  lui \reg, %hi(\num)
.endif
.endm

.macro move a, b
    addu \a, \b, $zero
.endm
