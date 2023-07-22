#include "sattypes.h"
#include "inc_asm.h"

// SEGA_SPR.A
// doesn't match as closely as SEGA_BUP, different version of lib?

// SPR_SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60218E8, func_060218E8);

// SPR_GetStatus
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021A58, func_06021A58);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6021AE8, func_06021AE8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022060, func_06022060);

// _SPR_SetEosMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022088, func_06022088);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220B4, func_060220B4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60220EC, func_060220EC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022138, func_06022138);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022148, func_06022148);

// _SPR_2Initial
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022164, func_06022164);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022194, func_06022194);

// SPR_2SetTvMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022514, func_06022514);

// SPR_2FrameChgIntr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022588, func_06022588);
// func_060225C4 is SPR_2FrameEraseData, splitter bug
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60225F4, func_060225F4);

// SPR_2SetGourTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602262C, func_0602262C);

// SPR_2SetLookupTbl
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022678, func_06022678);

// SPR_2ClrAllChar
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60226D0, func_060226D0);

// _SPR_2GourTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022768, func_06022768);

// SPR_2LookupTblNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227AC, func_060227AC);

// SPR_2CharNoToVram
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60227E4, func_060227E4);

// SPR_2GetAreaSizeInfo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602281C, func_0602281C);

// SPR_2OpenCommand
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602292C, func_0602292C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022A48, func_06022A48);

// _SPR_2FlushDrawPrty
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C7C, func_06022C7C);

// _SPR_2LocalCoord
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022C9C, func_06022C9C);

// _SPR_2SysClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D28, func_06022D28);

// SPR_2UserClip
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022D98, func_06022D98);

// _SPR_2Cmd
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E2C, func_06022E2C); // SPR_2Cmd

// _SPR_2FlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6022E8C, func_06022E8C);

// SlaveFlushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60230B8, func_060230B8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023108, func_06023108);

// SPR_RunSlaveSH
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023114, func_06023114);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023144, func_06023144);

// flushDrawPrtyBlock
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60231C0, func_060231C0);

INCLUDE_ASM("asm/saturn/zero/data", d6023394, d_06023394);
