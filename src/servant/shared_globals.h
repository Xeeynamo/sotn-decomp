// SPDX-License-Identifier: AGPL-3.0-or-later
static s32 g_PlaySfxStep = 99;
static s16 g_EntityRanges[] = {5, 7, 32, 63};
static ServantEvent* g_EventQueue = g_Events;
static u32 g_CurrentServant = 0;
static s32 g_CurrentRoomX = 0;
static s32 g_CurrentRoomY = 0;
