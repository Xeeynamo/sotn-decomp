// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_T_BAT_BSS_H
#define SATURN_T_BAT_BSS_H

#include "sattypes.h"

extern u32 g_CurrentServant;
extern s32 g_CurrentRoomX;
extern s32 g_CurrentRoomY;
extern s16 g_BatFollowDeltaX;
extern s16 g_BatFollowDeltaY;
extern Primitive* prim;
extern bool isAlive[16];
extern Point16 positions[16];
extern s16 facingLeft[16];
extern s16 offsets[16];
extern u8 fade[16];
extern s32 idx;
extern FamiliarStats s_BatStats;
extern Point16 s_BatPathingPoints[4][16];

#endif
