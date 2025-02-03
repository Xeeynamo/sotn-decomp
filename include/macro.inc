.ifndef .L_MACRO_INC
.L_MACRO_INC:

.macro jlabel label
    glabel \label
.endm

.macro glabel label
    .global \label
    \label:
.endm

.macro .def #
.endm


.include "gte.inc"

.endif
