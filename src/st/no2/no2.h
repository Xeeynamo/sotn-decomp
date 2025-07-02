// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO2

#define OVL_EXPORT(x) NO2_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

typedef enum EntityIDs {
    /* 0x00 */ // E_NONE,
    /* 0x01 */ // E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ // E_NUMERIC_DAMAGE,
    /* 0x05 */ // E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION = 0x06,
    /* 0x07 */ // E_SOUL_STEAL_ORB,
    /* 0x08 */ // E_ROOM_FOREGROUND,
    /* 0x09 */ // E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    /* 0x0B */ // E_RELIC_ORB,
    /* 0x0C */ // E_HEART_DROP,
    /* 0x0D */ // E_ENEMY_BLOOD,
    /* 0x0E */ // E_MESSAGE_BOX,
    /* 0x0F */ // E_DUMMY_0F,
    /* 0x10 */ // E_DUMMY_10,
    /* 0x11 */ // E_BACKGROUND_BLOCK,
    /* 0x12 */ // E_LOCK_CAMERA,
    /* 0x13 */ // E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_SKELERANG,
    /* 0x17 */ E_SKELERANG_BOOMERANG,
    /* 0x18 */ E_SKELERANG_UNKNOWN,
    /* 0x19 */ // E_ID_19,
    /* 0x1A */ // E_ID_1A,
    /* 0x1B */ // E_ID_1B,
    /* 0x1C */ // E_ID_1C,
    /* 0x1D */ // E_ID_1D,
    /* 0x1E */ // E_ID_1E,
    /* 0x1F */ // E_ID_1F,
    /* 0x20 */ // E_ID_20,
    /* 0x21 */ // E_ID_21,
    /* 0x22 */ // E_ID_22,
    /* 0x23 */ // E_ID_23,
    /* 0x24 */ // E_ID_24,
    /* 0x25 */ // E_ID_25,
    /* 0x26 */ // E_ID_26,
    /* 0x27 */ E_ID_27 = 0x27,
    /* 0x28 */ // E_ID_28,
    /* 0x29 */ E_OWL_KNIGHT = 0x29,
    /* 0x2A */ E_OWL,
    /* 0x2B */ E_OWL_KNIGHT_SWORD,
    /* 0x2C */ E_OWL_TARGET,
    /* 0x2D */ // E_ID_2D,
    /* 0x2E */ E_BLOOD_DRIPS = 0x2E,
    /* 0x2F */ E_BLOOD_SPLATTER,
} EntityIDs;

// extern EInit D_us_80180820;
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
// extern EInit D_us_80180844;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
extern EInit g_EInitDamageNum;
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;
// extern EInit D_us_801808A4;
// extern EInit D_us_801808B0;
extern EInit g_EInitOwlKnight;
extern EInit D_us_801808C8;
extern EInit g_EInitOwl;
extern EInit g_EInitBloodyZombie;
// extern EInit D_us_801808EC;
// extern EInit D_us_801808F8;
// extern EInit D_us_80180904;
// extern EInit D_us_80180910;
// extern EInit D_us_8018091C;
// extern EInit D_us_80180928;
// extern EInit D_us_80180934;
// extern EInit D_us_80180940;
// extern EInit D_us_8018094C;
// extern EInit D_us_80180958;
// extern EInit D_us_80180964;
// extern EInit D_us_80180970;
// extern EInit D_us_8018097C;
// extern EInit D_us_80180988;
