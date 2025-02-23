// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

// warp.c
s32 DestinationWarpRoom;
s32 WarpBackgroundAmplitiude;
s32 WarpBackgroundPhase;
s32 WarpBackgroundBrightness;
s32 D_80180648;

// st_debug.c
u8 entityLockCameraData[8];

// e_misc.c
u8 WRP_PrizeDrops[8]; // different than the g_HeartDropArray in warp.c ???

// ????
u8 D_psp_0924BCD0[0x1000];

// e_breakable.c
u8 g_eBreakableExplosionTypes[8];

// st_init_wrp.c
s32 E_ID(ID_11);
s32 E_ID(ID_12);
s32 E_ID(ID_13);
s32 E_ID(ID_14);
s32 E_ID(ID_15);
s32 E_ID(ID_16);
s32 E_ID(SMALL_ROCKS);

// ????
LayerDef D_psp_0924BC80;

// blit_char.c
u8* D_psp_0924BC78;
u8* D_psp_0924BC70;
s32 D_psp_0924BC68;

// entity_relic_orb.c
s32 obtainedStr;

// st_update.c
// u16 g_ItemIconSlots[0x20];
