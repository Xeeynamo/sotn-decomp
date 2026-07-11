// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RWRP_H
#define RWRP_H

#define STAGE_IS_RWRP
#define OVL_EXPORT(x) RWRP_##x
#include <stage.h>

typedef enum EntityIDs {
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
    E_MESSAGE_BOX,
    E_DUMMY_0F,
    E_DUMMY_10,
    E_UNK_11,
    E_UNK_12,
    E_UNK_13,
    E_EXPLOSION_VARIANTS,
    E_GREY_PUFF,
    E_WARP,
    E_SMALL_ROCKS,
} EntityIDs;

extern EInit OVL_EXPORT(EInitObtainable);
extern EInit OVL_EXPORT(EInitParticle);
extern EInit OVL_EXPORT(EInitInteractable);
extern EInit OVL_EXPORT(EInitCommon);
extern EInit OVL_EXPORT(EInitLockCamera);
extern EInit g_EInitSmallRocks;

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

#endif
