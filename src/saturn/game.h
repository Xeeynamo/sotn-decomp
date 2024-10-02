// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef GAME_H
#define GAME_H

#define DAMAGE_FLAG_NORMAL 0x0000
#define DAMAGE_FLAG_CRITICAL 0x4000
#define DAMAGE_FLAG_ABSORB 0x8000
#define DAMAGE_FLAG_IMMUNE 0xC000

extern EnemyDef g_EnemyDefs[];
extern s32 g_RoomCount;

// document g_Player.unk0C
#define PLAYER_STATUS_POISON 0x00004000

#endif
