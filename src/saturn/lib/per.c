// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"

// SEGA_PER.A

//_JudgeOreg
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CC0C, func_0602CC0C);

//_MoveBdryData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CC48, func_0602CC48);

//_SetPerData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CCC0, func_0602CCC0);

//_InitIntBackPer
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CD44, func_0602CD44);

//_GoIntBack
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CE04, func_0602CE04);

//_AnyInitPerData
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CE90, func_0602CE90);

//_SetPerId
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF10, func_0602CF10);

//_SetPerSize
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF4C, func_0602CF4C);

//_MoveOldToNew
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602CF8C, func_0602CF8C);

INCLUDE_ASM("asm/saturn/zero/data", d602D008, d_0602D008);
