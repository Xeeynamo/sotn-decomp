.macro glabel label
    .global \label
    \label:
.endm

.macro .def #
.endm

.macro move a, b
    addu \a, \b, $zero
.endm
