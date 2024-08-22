// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"

// SEGA_DMA.A

// _DMA_ScuInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60234F4, func_060234F4);

// _DMA_ScuMemCopy
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602354C, func_0602354C);

// _DMA_ScuResult - func_0602371C
// splitter bug
INCLUDE_ASM("asm/saturn/zero/data", d602371C, d_0602371C);

// _DMA_ScuStart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023950, func_06023950);

// _DMA_ScuGetStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023A60, func_06023A60);

// _DMA_ScuIntFunc0
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023AB0, func_06023AB0);

// _DMA_ScuIntFunc1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023B54, func_06023B54);

// _DMA_ScuIntFunc2 - splitter bug
INCLUDE_ASM("asm/saturn/zero/data", d6023C00, d_06023C00);

// _DMA_CpuSetPrm
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023DE0, func_06023DE0);

// _DMA_CpuStart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023F88, func_06023F88);

// _DMA_CpuStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023FC8, func_06023FC8);

// _DMA_CpuAllStop
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024008, func_06024008);

// _DMA_CpuGetComStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602402C, func_0602402C);

// _DMA_CpuGetStatus
INCLUDE_ASM("asm/saturn/zero/data", d6024058, d_6024058);
