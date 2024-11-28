// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO0

#define OVL_EXPORT(x) NO0_##x

void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

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
    /* 0x0E */ E_SAVE_GAME_POPUP,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x14 */ E_ID_14 = 0x14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x1D */ E_CLOCK_ROOM_SHADOW = 0x20,
    /* 0x2E */ E_SKELERANG = 0x2E,
    /* 0x2F */ E_SKELERANG_BOOMERANG,
    /* 0x30 */ E_SKELERANG_UNK,
    /* 0x31 */ E_PLATE_LORD,
    /* 0x32 */ E_ID_32,
    /* 0x33 */ E_ID_33,
    /* 0x34 */ E_ID_34,
    /* 0x35 */ E_ID_35,
    /* 0x36 */ E_ID_36,
    /* 0x37 */ E_GHOST_ENEMY,
    /* 0x3B */ E_SLINGER_THROWN_BONE = 0x3B,
    /* 0x3C */ E_SLINGER_PIECES,
    /* 0x3D */ E_ID_3D,
    /* 0x41 */ E_STONEROSE_SEED = 0x41,
    /* 0x44 */ E_CTULHU_FIREBALL = 0x44,
    /* 0x45 */ E_CTULHU_ICE_SHOCKWAVE,
    /* 0x46 */ E_CTULHU_DEATH,
    /* 0x48 */ E_AXE_KNIGHT_AXE = 0x48,
    /* 0x49 */ E_WARG_EXP_OPAQUE,
    /* 0x4A */ E_OUIJA_TABLE = 0x4A,
    /* 0x4B */ E_OUIJA_TABLE_COMPONENT,
    /* 0x4D */ E_SKELETON = 0x4D,
    /* 0x4E */ E_SKELETON_THROWN_BONE,
    /* 0x4F */ E_SKELETON_PIECES,
} EntityIDs;

extern Primitive* FindFirstUnkPrim(Primitive* poly);

#define E_PUFF_OPAQUE_PALETTE_OFFSET 0x2C0

extern s16 g_SineTable[];
extern u16 g_EInitCommon[];
extern u16 g_EInitParticle[];
extern u16 g_EInitInteractable[];

// Axe knight
extern EInit g_EInitAxeKnightAxe;

// Skeleton
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;

// Ouija Table
extern EInit g_EInitOuijaTable;
extern EInit g_EInitOuijaTableComponent;

// Flea Man
extern EInit g_EInitFleaMan;

// Slinger
extern EInit g_EInitSlinger;
extern EInit g_EInitSlingerPieces;
extern EInit g_EInitSlingerRib;

// Ghost (enemy)
extern EInit g_EInitGhostEnemy;

// Skelerang
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;

// Ctulhu
extern EInit g_EInitCtulhu;
extern EInit g_EInitCtulhuFireball;
extern EInit g_EInitCtulhuIceShockwave;

// Diplocephalus
extern EInit g_EInitDiplocephalusFoot;

// Clock room
extern EInit g_Statues;

// Seems shared between a number of entities - ghost spawner,
// func_us_801C2B24 (clocks?), func_us_801CC750
extern EInit D_us_80180A88;
