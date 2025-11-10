// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO3_H
#define RBO3_H

#include <game.h>
#include <stage.h>

#define STAGE_IS_RBO3
#define OVL_EXPORT(x) RBO3_##x

typedef enum {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x07 */ E_SOUL_STEAL_ORB = 0x7,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0xA,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x11 */ E_MEDUSA,
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x18 */ UNK_ENTITY_24 = 24,
    /* 0x19 */ UNK_ENTITY_25,
    /* 0x1A */ UNK_ENTITY_26,
    /* 0x1B */ UNK_ENTITY_27,
    /* 0x1C */ UNK_ENTITY_28,
    /* 0x1D */ UNK_ENTITY_29,
    /* 0x1E */ UNK_ENTITY_30,
} EntityIDs;

extern EInit g_EInitInteractable;
extern EInit g_EInitCommon;
extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;

extern s8 c_HeartPrizes[];

#endif // RBO3_H
