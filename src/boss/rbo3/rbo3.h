// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO3_H
#define RBO3_H

#include <game.h>
#include <stage.h>

#define STAGE_IS_RBO3

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x07 */ E_SOUL_STEAL_ORB = 0x7,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0xA,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0D */ E_ENEMY_BLOOD = 13,
    /* 0x11 */ E_BACKGROUND_BLOCK = 0x11,
    /* 0x12 */ E_LOCK_CAMERA,
    /* 0x13 */ E_UNK_ID13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_UNK_22,
    /* 0x17 */ E_MEDUSA,
    /* 0x18 */ E_UNK_24,
    /* 0x19 */ E_UNK_25,
    /* 0x1A */ E_UNK_26,
    /* 0x1B */ E_UNK_27,
    /* 0x1C */ E_UNK_28,
    /* 0x1D */ E_UNK_29,
    /* 0x1E */ E_LIFE_UP_SPAWN,
    /* 0x1F */ E_CLOUDS,
    /* 0x20 */ E_UNK_32,
} EntityID;

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;

#endif // RBO3_H
