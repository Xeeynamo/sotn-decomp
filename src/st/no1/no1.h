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
    // /* 0x0C */ E_HEART_DROP,
    // /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11 = 0x11,
    // /* 0x13 */ E_UNK_ID_13 = 0x13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x21 */ E_AXE_KNIGHT_AXE = 0x21,
    /* 0x22 */ E_AXE_KNIGHT_AXE_2, // func_us_801CBA30
    /* 0x23 */ E_UNK_ENTITY,       // InitializeUnkEntity
    /* 0x2A */ E_ID_2A = 0x2A,
    /* 0x3E */ E_SKELETON = 0x3E,
    /* 0x3F */ E_SKELETON_THROWN_BONE,
    /* 0x40 */ E_SKELETON_PIECES,
    /* 0x41 */ E_ID_41,
    /* 0x42 */ E_ID_42,
    /* 0x43 */ E_ID_43,
    /* 0x44 */ E_ID_44,
    /* 0x45 */ E_ID_45,
    /* 0x46 */ E_ID_46,
    /* 0x47 */ E_ID_47,
    /* 0x48 */ E_ID_48,
    /* 0x49 */ E_ID_49,
    /* 0x50 */ E_ID_50 = 0x50,
    /* 0x53 */ E_ID_53 = 0x53,
    /* 0x56 */ E_ID_56 = 0x56,
    /* 0x58 */ E_ID_58 = 0x58,
    /* 0x5A */ E_ID_5A = 0x5A,
    /* 0x5B */ E_ID_5B,
} EntityIDs;

// Skeleton
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;
