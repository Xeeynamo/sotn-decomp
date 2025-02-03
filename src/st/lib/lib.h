// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_LIB
#define OVL_EXPORT(x) LIB_##x
#define CASTLE_FLAG_BANK 0x6F

typedef enum EntityIDs {
    // /* 0x00 */ E_NONE,
    // /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
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
    // /* 0x0E */ E_MESSAGE_BOX,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11,
    // /* 0x13 */ E_UNK_ID_13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x1D */ E_BLOOD_DRIPS = 0x1D,
    /* 0x1E */ E_BLOOD_SPLATTER,
    /* 0x20 */ E_ID_20 = 0x20,
    /* 0x21 */ E_ID_21,
    /* 0x22 */ E_ID_22,
    /* 0x3A */ E_THORNWEED = 0x3A,
    /* 0x3B */ E_CORPSEWEED,
    /* 0x3C */ E_CORPSEWEED_PROJECTILE,
    /* 0x43 */ E_SKELETON = 0x43,
    /* 0x44 */ E_SKELETON_THROWN_BONE,
    /* 0x45 */ E_SKELETON_PIECES,
} EntityIDs;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);
extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

extern EInit g_EInitParticle;
extern EInit g_EInitObtainable;

// Skeleton
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;
