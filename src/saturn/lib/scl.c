#include "sattypes.h"
#include "inc_asm.h"

// SEGA_SCL.A

// _SCL_Open
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024444, func_06024444);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024474, func_06024474);

// _SCL_MoveTo
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024494, func_06024494);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602465C, func_0602465C);

// _SCL_CopyReg
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024848, func_06024848);

// _SCL_ScrollShow
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024A48, func_06024A48);

// _SCL_Memcpyw
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024B20, func_06024B20);

// _SCL_SetColRamMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024B84, func_06024B84);

// _SCL_PriIntProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024C20, func_06024C20);

// _SCL_SetFrameInterval
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024DB4, func_06024DB4);

// _SCL_DisplayFrame
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024EC0, func_06024EC0);

// _SCL_VblInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024F08, func_06024F08);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6024F64, func_06024F64);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025074, func_06025074);

// _SCL_PriorityInit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025174, func_06025174);

// _SCL_GetColRamMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025214, func_06025214);

// _SCL_AbortAutoVe
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025244, func_06025244);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602525C, func_0602525C);

// _SCL_AutoExec
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6025AE4, func_06025AE4);

// _SCL_IncColOffset
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60263E0, func_060263E0);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026534, func_06026534);

// _SCL_InitSclSpPriNum
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026C30, func_06026C30);

// _SCL_InitSclBgPriNum
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026D3C, func_06026D3C);

// _SCL_InitSclSpColMix
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026DF0, func_06026DF0);

// _SCL_InitSclBgColMix
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026EEC, func_06026EEC);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6026FC4, func_06026FC4);

// _SCL_SetShadowBit
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60271F0, func_060271F0);

// _SCL_SetDisplayMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60274C0, func_060274C0);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60277D8, func_060277D8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6027B74, func_06027B74);

// _SCL_SetVramConfig
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6027BD8, func_06027BD8);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028548, func_06028548);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028614, func_06028614);

// _SCL_SetColMixMode
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028978, func_06028978);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028A00, func_06028A00);

// _SCL_EnableLineCol
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028BE4, func_06028BE4);

INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028C0C, func_06028C0C);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028C34, func_06028C34);

// _SCL_InitConfigTb
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6028D10, func_06028D10);

// _SCL_SetConfig = 0x06028ddc splitter bug

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/f_nonmat", f602915A, func_0602915A);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A654, func_0602A654);

// _SCL_FreeColRam
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A6DC, func_0602A6DC);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A778, func_0602A778);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602A964, func_0602A964);

// _Fcos
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f602AA84, func_0602AA84);

INCLUDE_ASM("asm/saturn/zero/data", d602AB9C, d_0602AB9C);
