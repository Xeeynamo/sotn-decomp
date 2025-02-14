// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_LIB
#define OVL_EXPORT(x) LIB_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

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
    /* 0x0B */ E_RELIC_ORB,
    // /* 0x0C */ E_HEART_DROP,
    // /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    // /* 0x11 */ E_ID_11,
    // /* 0x13 */ E_UNK_ID_13,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x1C */ E_ID_1C = 0x1C,
    /* 0x1D */ E_BLOOD_DRIPS,
    /* 0x1E */ E_BLOOD_SPLATTER,
    /* 0x20 */ E_ID_20 = 0x20,
    /* 0x21 */ E_ID_21,
    /* 0x22 */ E_ID_22,
    /* 0x27 */ E_ID_27 = 0x27,
    /* 0x28 */ E_ID_28,
    /* 0x29 */ E_ID_29,
    /* 0x2A */ E_ID_2A,
    /* 0x2D */ E_ID_2D = 0x2D,
    /* 0x2E */ E_ID_2E,
    /* 0x2F */ E_ID_2F,
    /* 0x31 */ E_ID_31 = 0x31,
    /* 0x33 */ E_ID_33 = 0x33,
    /* 0x34 */ E_ID_34,
    /* 0x35 */ E_ID_35,
    /* 0x36 */ E_ID_36,
    /* 0x3A */ E_THORNWEED = 0x3A,
    /* 0x3B */ E_CORPSEWEED,
    /* 0x3C */ E_CORPSEWEED_PROJECTILE,
    /* 0x3E */ E_ID_3E = 0x3E,
    /* 0x43 */ E_SKELETON = 0x43,
    /* 0x44 */ E_SKELETON_THROWN_BONE,
    /* 0x45 */ E_SKELETON_PIECES,
    /* 0x48 */ E_ID_48 = 0x48,
    /* 0x4D */ E_ID_4D = 0x4D,
    /* 0x4E */ E_ID_4E,
} EntityIDs;

extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);
extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

typedef struct {
    /* 0x0 */ u16 category;
    /* 0x2 */ u16 itemId;
    /* 0x4 */ u32 price;
} AvailableInventoryItem;

extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitCommon;
extern EInit g_EInitInteractable;

// Skeleton
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;

extern EInit g_EInitFleaMan;

extern EInit D_us_80180878;

extern EInit D_us_8018089C;
extern EInit D_us_801808A8;
extern EInit D_us_801808B4;
