// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO1

#define OVL_EXPORT(x) NO1_##x

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

enum OVL_EXPORT(Palette) {
    PAL_NONE = 0,
    PAL_ARMOR_LORD_UNK = 0x220,
    PAL_BREAKABLE = 0x22D,
    PAL_BREAKABLE_DEBRIS = 0x231,
};

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION,
    /* 0x03 */ E_PRIZE_DROP,
    /* 0x04 */ E_NUMERIC_DAMAGE,
    /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    /* 0x08 */ E_ROOM_FOREGROUND,
    /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_ID_11,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_ID_16,
    /* 0x17 */ E_ID_17,
    /* 0x18 */ E_ID_18,
    /* 0x19 */ E_ID_19,
    /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_CHAIR,
    /* 0x1C */ E_ID_1C,
    /* 0x1D */ E_ID_1D,
    /* 0x1E */ E_ID_1E,
    /* 0x1F */ E_ID_1F,
    /* 0x20 */ E_AXE_KNIGHT_BLUE,
    /* 0x21 */ E_AXE_KNIGHT_AXE,
    /* 0x22 */ E_AXE_KNIGHT_AXE_2,
    /* 0x23 */ E_UNK_ENTITY,
    /* 0x24 */ E_ID_24,
    /* 0x25 */ E_ID_25,
    /* 0x26 */ E_ID_26,
    /* 0x27 */ E_ID_27,
    /* 0x28 */ E_ID_28,
    /* 0x29 */ E_ID_29,
    /* 0x2A */ E_ID_2A,
    /* 0x2B */ E_ID_2B,
    /* 0x2C */ E_ID_2C,
    /* 0x2D */ E_ID_2D,
    /* 0x2E */ E_ID_2E,
    /* 0x2F */ E_ID_2F,
    /* 0x30 */ E_ID_30,
    /* 0x31 */ E_ID_31,
    /* 0x32 */ E_ID_32,
    /* 0x33 */ E_ID_33,
    /* 0x34 */ E_ID_34,
    /* 0x35 */ E_ID_35,
    /* 0x36 */ E_ID_36,
    /* 0x37 */ E_ID_37,
    /* 0x38 */ E_ID_38,
    /* 0x39 */ E_ID_39,
    /* 0x3A */ E_ID_3A,
    /* 0x3B */ E_ID_3B,
    /* 0x3C */ E_ID_3C,
    /* 0x3D */ E_ID_3D,
    /* 0x3E */ E_SKELETON,
    /* 0x3F */ E_SKELETON_THROWN_BONE,
    /* 0x40 */ E_SKELETON_PIECES,
    /* 0x41 */ E_WERESKELETON,
    /* 0x42 */ E_ID_42,
    /* 0x43 */ E_ID_43,
    /* 0x44 */ E_BONE_ARCHER,
    /* 0x45 */ E_BONE_ARCHER_ARROW,
    /* 0x46 */ E_BONE_MUSKET,
    /* 0x47 */ E_BONE_MUSKET_UNK,
    /* 0x48 */ E_SWORD_LORD,
    /* 0x49 */ E_SWORD_LORD_ATTACK,
    /* 0x4A */ E_ARMOR_LORD,
    /* 0x4B */ E_ARMOR_LORD_UNK1,
    /* 0x4C */ E_ARMOR_LORD_FIRE_WAVE,
    /* 0x4D */ E_ARMOR_LORD_UNK2,
    /* 0x4E */ E_ID_4E,
    /* 0x4F */ E_SPEAR_GUARD,
    /* 0x50 */ E_SPEAR_GUARD_BLOCK,
    /* 0x51 */ E_ID_51,
    /* 0x52 */ E_ID_52,
    /* 0x53 */ E_SKELETON_APE,
    /* 0x54 */ E_SKELETON_APE_PUNCH,
    /* 0x55 */ E_SKELETON_APE_BARREL,
    /* 0x56 */ E_THROWN_BARREL,
    /* 0x57 */ E_ID_57,
    /* 0x58 */ E_THROWN_SPEAR,
    /* 0x59 */ E_MEDUSA_HEAD_SPAWNER,
    /* 0x5A */ E_MEDUSA_HEAD_BLUE,
    /* 0x5B */ E_MEDUSA_HEAD_YELLOW,
    /* 0x5C */ E_BREAKABLE_DEBRIS,
    /* 0x5D */ E_MIST_DOOR,
    /* 0x5E */ E_ID_5E,
} EntityIDs;

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit D_us_80180974;
extern EInit D_us_80180980;
extern EInit D_us_8018098C;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
extern EInit g_EInitDamageNum;
extern EInit D_us_801809C8;
extern EInit D_us_801809D4;
extern EInit g_EInitAxeKnight;
extern EInit g_EInitAxeKnightAxe;
extern EInit D_us_801809F8;
extern EInit D_us_80180A04;
extern EInit D_us_80180A10;
extern EInit D_us_80180A1C;
extern EInit D_us_80180A28;
extern EInit D_us_80180A34;
extern EInit D_us_80180A40;
extern EInit D_us_80180A4C;
extern EInit g_EInitWereskeleton;
extern EInit D_us_80180A88;
extern EInit g_EInitSwordLord;
extern EInit g_EInitSwordLordAttack;
extern EInit g_EInitBoneArcher;
extern EInit g_EInitBoneArcherArrow;
extern EInit g_EInitSpearGuard;
extern EInit g_EInitThrownSpear;
extern EInit D_us_80180B18;
extern EInit g_EInitSkeletonApe;
extern EInit g_EInitSkeletonApeBarrel;
extern EInit g_EInitSkeletonApePunch;
