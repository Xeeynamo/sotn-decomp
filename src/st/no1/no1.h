// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO1

#define OVL_EXPORT(x) NO1_##x
#define CASTLE_FLAG_BANK 0x13

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

typedef enum EntityIDs {
    // /* 0x00 */ E_NONE,
    // /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP = 0x03,
    // /* 0x04 */ E_NUMERIC_DAMAGE,
    // /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION = 0x06,
    // /* 0x07 */ E_SOUL_STEAL_ORB,
    // /* 0x08 */ E_ROOM_FOREGROUND,
    // /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    // /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP = 0x0C,
    // /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11 = 0x11,
    // /* 0x13 */ E_UNK_ID_13 = 0x13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    // /* 0x1B */ E_CHAIR = 0x1B,
    // /* 0x20 */ E_AXE_KNIGHT_BLUE = 0x20,
    /* 0x21 */ E_AXE_KNIGHT_AXE = 0x21,
    /* 0x22 */ E_AXE_KNIGHT_AXE_2, // func_us_801CBA30
    /* 0x23 */ E_UNK_ENTITY,       // InitializeUnkEntity
    /* 0x25 */ E_ID_25 = 0x25,
    /* 0x26 */ E_ID_26,
    /* 0x27 */ E_ID_27,
    /* 0x2A */ E_ID_2A = 0x2A,
    /* 0x2F */ E_ID_2F = 0x2F,
    /* 0x30 */ E_ID_30,
    /* 0x31 */ E_ID_31,
    /* 0x33 */ E_ID_33 = 0x33,
    /* 0x36 */ E_ID_36 = 0x36,
    /* 0x38 */ E_ID_38 = 0x38,
    /* 0x39 */ E_ID_39,
    /* 0x3E */ E_SKELETON = 0x3E,
    /* 0x3F */ E_SKELETON_THROWN_BONE,
    /* 0x40 */ E_SKELETON_PIECES,
    /* 0x41 */ E_WERESKELETON,
    /* 0x42 */ E_ID_42,
    /* 0x43 */ E_ID_43,
    /* 0x44 */ E_BONE_ARCHER,
    /* 0x45 */ E_BONE_ARCHER_ARROW,
    /* 0x46 */ E_BONE_MUSKET,
    /* 0x47 */ E_ID_47,
    /* 0x48 */ E_SWORD_LORD,
    /* 0x49 */ E_ID_49,
    // /* 0x4A */ E_ARMOR_LORD = 0x4A,
    /* 0x4B */ E_ID_4B = 0x4B,
    /* 0x4C */ E_ARMOR_LORD_FIRE_WAVE,
    /* 0x4D */ E_ID_4D,
    // /* 0x4E */ E_SPEAR_GUARD = 0x4E,
    /* 0x50 */ E_ID_50 = 0x50,
    /* 0x52 */ E_ID_52 = 0x52,
    /* 0x53 */ E_SKELETON_APE,
    /* 0x54 */ E_ID_54,
    /* 0x55 */ E_SKELETON_APE_BARREL,
    /* 0x56 */ E_ID_56,
    /* 0x58 */ E_ID_58 = 0x58,
    // /* 0x59 */ E_MEDUSA_HEAD_SPAWNER = 0x59,
    /* 0x5A */ E_MEDUSA_HEAD_BLUE = 0x5A,
    /* 0x5B */ E_MEDUSA_HEAD_YELLOW,
    /* 0x5C */ E_ID_5C,
    // /* 0x5D */ E_MIST_DOOR = 0x5D,
    /* 0x5E */ E_ID_5E = 0x5E,
} EntityIDs;

extern EInit D_us_80180938;
// extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit D_us_8018095C;
extern EInit g_EInitInteractable;
// extern EInit D_us_80180974;
// extern EInit D_us_80180980;
// extern EInit D_us_8018098C;
// extern EInit g_EInitUnkId13;
// extern EInit g_EInitUnkId12;
extern EInit g_EInitCommon;
// extern EInit g_EInitDamageNum;
extern EInit D_us_801809C8;
extern EInit D_us_801809D4;
extern EInit g_EInitAxeKnight;
extern EInit g_EInitAxeKnightAxe;
extern EInit D_us_801809F8;
// extern EInit D_us_80180A04;
extern EInit D_us_80180A10;
extern EInit D_us_80180A1C;
// extern EInit D_us_80180A28;
// extern EInit D_us_80180A34;
extern EInit D_us_80180A40;
extern EInit D_us_80180A4C;
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;
extern EInit g_EInitWereskeleton;
extern EInit D_us_80180A88;
extern EInit g_EInitBoneMusket;
extern EInit D_us_80180AA0;
extern EInit g_EInitSwordLord;
extern EInit D_us_80180AB8;
extern EInit g_EInitBoneArcher;
extern EInit g_EInitBoneArcherArrow;
extern EInit g_EInitArmorLord;
// extern EInit D_us_80180AE8;
// extern EInit D_us_80180AF4;
extern EInit g_EInitSpearGuard;
extern EInit D_us_80180B0C;
extern EInit D_us_80180B18;
extern EInit g_EInitSkeletonApe;
extern EInit D_us_80180B30;
extern EInit D_us_80180B3C;
extern EInit g_EInitMedusaHeadBlue;
extern EInit g_EInitMedusaHeadYellow;
