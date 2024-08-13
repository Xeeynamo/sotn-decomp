#include "common.h"
#include "game.h"

u32 D_80173B64;
u32 D_80173B68[1280];
u32 D_80174F68;
u32 D_80174F6C;
u32 D_80174F70;
u32 D_80174F74;
u32 D_80174F78;
static u32 g_DebugWaitInfoTimer;
u32 D_80174F80[11];
u8 D_80174FAC[4];
u8 D_80174FB0[4];
u8 D_80174FB4[4];
u8 D_80174FB8[4];
u16 D_80174FBC;
u16 D_80174FBE[31];
u16 D_80174FFC;
u16 D_80174FFE;
u16 D_80175000;
u16 D_80175002[63];
u32 D_80175080;
u32 D_80175084;
u32 D_80175088[512];
u32 D_80175888;
u32 D_8017588C;
u32 D_80175890;
Point16 g_BiblePos[6];
u32 D_801758AC;
#ifdef VERSION_PC
// D_801758CC is used in other places so unclear if this is a bug
// or data import error
u32 g_AguneaParams[8];
#else
u32 g_AguneaParams[7];
#endif
u32 D_801758CC;
u32 D_801758D0[4];
ButtonComboState g_bladeDashButtons;
ButtonComboState D_801758E4;
u16 D_801758E6[52];
u16 D_80175950;
u16 D_80175952;
u16 D_80175954;
u16 D_80175956;
u32 D_80175958[32];
u32 D_801759D8[32];
