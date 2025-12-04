// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_LIB
#define OVL_EXPORT(x) LIB_##x

enum Palettes {
    PAL_NONE = 0,
    PAL_BREAKABLE = 0x26C,
};

typedef enum EntityIDs {
    /* 0x00 */ E_NONE,
    /* 0x01 */ E_BREAKABLE,
    /* 0x02 */ E_EXPLOSION = 0x02,
    /* 0x03 */ E_PRIZE_DROP,
    // /* 0x04 */ E_NUMERIC_DAMAGE,
    // /* 0x05 */ E_RED_DOOR,
    /* 0x06 */ E_INTENSE_EXPLOSION = 0x06,
    /* 0x07 */ E_SOUL_STEAL_ORB,
    // /* 0x08 */ E_ROOM_FOREGROUND,
    // /* 0x09 */ E_STAGE_NAME_POPUP,
    /* 0x0A */ E_EQUIP_ITEM_DROP = 0x0A,
    /* 0x0B */ E_RELIC_ORB,
    /* 0x0C */ E_HEART_DROP,
    // /* 0x0D */ E_ENEMY_BLOOD,
    /* 0x0E */ E_MESSAGE_BOX = 0x0E,
    // /* 0x0F */ E_DUMMY_0F,
    // /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x12 */ E_ID_12,
    /* 0x13 */ E_ID_13,
    /* 0x14 */ E_EXPLOSION_VARIANTS,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x16 */ E_ID_16,
    /* 0x17 */ E_ID_17,
    /* 0x18 */ E_ID_18,
    /* 0x19 */ E_ID_19,
    /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_ID_1B,
    /* 0x1C */ E_ID_1C,
    /* 0x1D */ E_BLOOD_DRIPS,
    /* 0x1E */ E_BLOOD_SPLATTER,
    /* 0x1F */ E_ID_1F,
    /* 0x20 */ E_ID_20,
    /* 0x21 */ E_ID_21,
    /* 0x22 */ E_ID_22,
    /* 0x23 */ E_ID_23,
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
    /* 0x3A */ E_THORNWEED,
    /* 0x3B */ E_CORPSEWEED,
    /* 0x3C */ E_CORPSEWEED_PROJECTILE,
    /* 0x3D */ E_CANDLE_TABLE,
    /* 0x3E */ E_ID_3E,
    /* 0x3F */ E_ID_3F,
    /* 0x40 */ E_ID_40,
    /* 0x41 */ E_ID_41,
    /* 0x42 */ E_ID_42,
    /* 0x43 */ E_SKELETON,
    /* 0x44 */ E_SKELETON_THROWN_BONE,
    /* 0x45 */ E_SKELETON_PIECES,
    /* 0x46 */ E_ID_46,
    /* 0x47 */ E_BREAKABLE_DEBRIS,
    /* 0x48 */ E_ID_48,
    /* 0x49 */ E_ID_49,
    /* 0x4A */ E_FLEA_ARMOR,
    /* 0x4B */ E_FLEA_ARMOR_ATTACK_HITBOX,
    /* 0x4C */ E_FLEA_MAN,
    /* 0x4D */ E_MUDMAN,
    /* 0x4E */ E_ID_4E,
    /* 0x4F */ E_ID_4F,
} EntityIDs;

extern void EntityBloodDrips(Entity*);
extern void EntityExplosionVariants(Entity* entity);
extern void EntityGreyPuff(Entity* entity);
extern Primitive* FindFirstUnkPrim(Primitive* prim);
extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit D_us_80180824;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
extern EInit g_EInitDamageNum;
extern EInit g_EInitBloodyZombie;
extern EInit g_EInitFlyingZombie2;
extern EInit g_EInitFlyingZombie1;
// extern EInit D_us_80180890;
extern EInit g_EInitDhuron;
extern EInit D_us_801808A8;
extern EInit D_us_801808B4;
extern EInit g_EInitEctoplasm;
extern EInit g_EInitThornweed;
// extern EInit D_us_801808D8;
extern EInit g_EInitCorpseweed;
extern EInit g_EInitCorpseweedProjectile;
extern EInit D_us_801808FC;
extern EInit D_us_80180908;
extern EInit g_EInitSpellbook;
extern EInit D_us_80180920;
// extern EInit D_us_8018092C;
extern EInit D_us_80180938;
extern EInit g_EInitMagicTome;
extern EInit D_us_80180950;
extern EInit D_us_8018095C;
extern EInit g_EInitLesserDemon;
extern EInit g_EInitLesserDemonSpit;
extern EInit D_us_80180980;
extern EInit D_us_8018098C;
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;
extern EInit g_EInitMudman;
extern EInit D_us_801809EC;
