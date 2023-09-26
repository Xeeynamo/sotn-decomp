.macro jlabel label
    glabel \label
.endm

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
  .if \num & 0xFFFF
    ori \reg, \reg, \num & 0xFFFF
  .endif
.elseif \num > 0
  ori \reg, $0, \num & 0xFFFF
.elseif \num == -0x8000
  addiu \reg, $0, \num & 0xFFFF
.elseif \num > -0x8000
  addiu \reg, $0, \num
.else
  lui \reg, (\num>>16) & 0xFFFF
  .if \num & 0xFFFF
    ori \reg, \reg, \num & 0xFFFF
  .endif
.endif
.endm

.macro move a, b
    addu \a, \b, $zero
.endm

.include "gte.inc"
