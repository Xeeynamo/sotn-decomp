.include "main.inc"

syscalldef exit             0xb0 0x38
syscalldef puts             0xb0 0x3f
syscalldef setjmp           0xa0 0x13
syscalldef strcat           0xa0 0x15
syscalldef strcpy           0xa0 0x19
syscalldef strlen           0xa0 0x1b
syscalldef memcpy           0xa0 0x2a
syscalldef memset           0xa0 0x2b
syscalldef rand             0xa0 0x2f
syscalldef srand            0xa0 0x30
syscalldef malloc           0xa0 0x33
syscalldef free             0xa0 0x34
syscalldef printf           0xa0 0x3f
