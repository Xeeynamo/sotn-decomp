// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO4
#define OVL_EXPORT(x) NO4_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
    // /* 0x00 */ E_NONE,
    // /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
    // /* 0x04 */ E_NUMERIC_DAMAGE,
    // /* 0x05 */ E_RED_DOOR,
    // /* 0x06 */ E_INTENSE_EXPLOSION = 0x06,
    // /* 0x07 */ E_SOUL_STEAL_ORB,
    // /* 0x08 */ E_ROOM_FOREGROUND,
    // /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    // /* 0x0B */ E_RELIC_ORB,
    // /* 0x0C */ E_HEART_DROP,
    // /* 0x0D */ E_ENEMY_BLOOD,
    // /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11 = 0x11,
    // /* 0x12 */ E_ID_12,
    // /* 0x13 */ E_ID_13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    // /* 0x16 */ E_ID_16,
    /* 0x17 */ E_SPLASH_WATER = 0x17,
    /* 0x18 */ E_SURFACING_WATER,
    /* 0x19 */ E_SIDE_WATER_SPLASH,
    // /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_WATER_DROP = 0x1B,
} EntityIDs;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);

// extern EInit D_us_80180B8C;
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
// extern EInit D_us_80180BD4;
extern EInit g_EInitCommon;
// extern EInit g_EInitDamageNum;
// extern EInit D_us_80180BF8;
// extern EInit D_us_80180C04;
// extern EInit D_us_80180C10;
// extern EInit D_us_80180C1C;
// extern EInit D_us_80180C28;
extern EInit g_EInitUnkId3F;
// extern EInit D_us_80180C40;
// extern EInit D_us_80180C4C;
// extern EInit D_us_80180C58;
// extern EInit D_us_80180C64;
// extern EInit D_us_80180C70;
// extern EInit D_us_80180C7C;
// extern EInit D_us_80180C88;
// extern EInit D_us_80180C94;
// extern EInit D_us_80180CA0;
// extern EInit D_us_80180CAC;
// extern EInit D_us_80180CB8;
// extern EInit D_us_80180CC4;
// extern EInit D_us_80180CD0;
// extern EInit D_us_80180CDC;
// extern EInit D_us_80180CE8;

extern s16 D_us_801DF788;
extern s16 D_us_801DF78A;
extern s8 D_us_801DF78E;
extern s8 D_us_801DF78F;
