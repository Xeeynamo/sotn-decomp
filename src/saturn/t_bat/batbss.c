// SPDX-License-Identifier: AGPL-3.0-or-later
#include "batbss.h"

#define BSS __attribute__((section(".bss")))

u32 g_CurrentServant BSS = 0;
s32 g_CurrentRoomX BSS = 0;
s32 g_CurrentRoomY BSS = 0;
s16 g_BatFollowDeltaX BSS = 0;
s16 g_BatFollowDeltaY BSS = 0;
u8 g_BatRuntimePadding[0xDC] BSS = {0};
FamiliarStats s_BatStats BSS = {0};
u32 g_BatStatsPadding BSS = 0;
Point16 s_BatPathingPoints[4][16] BSS = {0};
u8 g_BatOverlayReserved[0x36C0] BSS = {0};
