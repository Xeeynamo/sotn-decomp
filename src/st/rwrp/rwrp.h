// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RWRP_H
#define RWRP_H

#include "common.h"
#include "stage.h"

#define OVL_EXPORT(x) RWRP_##x

#define CASTLE_FLAG_BANK 0x1E0

typedef enum {
    E_NONE,
    E_BREAKABLE,
    E_EXPLOSION,
    E_PRIZE_DROP,
    E_NUMERIC_DAMAGE,
    E_RED_DOOR,
    E_INTENSE_EXPLOSION,
    E_SOUL_STEAL_ORB,
    E_ROOM_FOREGROUND,
    E_STAGE_NAME_POPUP,
    E_EQUIP_ITEM_DROP,
    E_RELIC_ORB,
    E_HEART_DROP,
    E_ENEMY_BLOOD,
    E_SAVE_GAME_POPUP,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_ID_14,
    E_GREY_PUFF,
    E_WARP,
    E_SMALL_ROCKS,
} EntityIDs;

typedef struct {
    s16 x, y;
} WarpCoord;

extern s32 D_8003C8B8;

extern u16 g_EInitObtainable[];
extern u16 g_EInitParticle[];
extern u16 g_EInitInteractable[];
extern u16 g_EInitCommon[];
extern u16 g_EInitSmallRocks[];

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

#endif
