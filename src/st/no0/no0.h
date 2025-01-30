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
    /* 0x0E */ E_MESSAGE_BOX,
    /* 0x0F */ E_DUMMY_0F,
    /* 0x10 */ E_DUMMY_10,
    /* 0x11 */ E_ID_11 = 0x11,
    /* 0x13 */ E_UNK_ID_13 = 0x13,
    /* 0x14 */ E_ID_14,
    /* 0x15 */ E_GREY_PUFF,
    /* 0x19 */ E_CLOCK_ROOM_CONTROLLER = 0x19,
    /* 0x1A */ E_CLOCK_HANDS,
    /* 0x1B */ E_BIRDCAGE_DOOR,
    /* 0x1C */ E_STATUE,
    /* 0x1D */ E_STATUE_GEAR,
    /* 0x1E */ E_STONE_DOOR,
    /* 0x1F */ E_CLOCK_ROOM_UNUSED,
    /* 0x20 */ E_CLOCK_ROOM_SHADOW,
    /* 0x21 */ E_DIPLOCEPHALUS,
    /* 0x22 */ E_ID_22,
    /* 0x23 */ E_ID_23,
    /* 0x24 */ E_DIPLOCEPHALUS_TAIL,
    /* 0x25 */ E_DIPLOCEPHALUS_FIREBALL,
    /* 0x26 */ E_DIPLOCEPHALUS_TORSO,
    /* 0x27 */ E_OLROX_DROOL,
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

// extern EInit OVL_EXPORT(EInitBreakable);
// extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit D_us_80180A88;
extern EInit g_EInitInteractable;
// extern EInit D_us_80180AA0;
extern EInit D_us_80180AAC;
// extern EInit D_us_80180AB8;
// extern EInit D_us_80180AC4;
// extern EInit g_EInitUnkId13;
extern EInit D_us_80180ADC;
extern EInit g_EInitCommon;
extern EInit g_EInitStoneRose;
extern EInit D_us_80180B00;
extern EInit D_us_80180B0C;
// extern EInit g_EInitDamageNum;
extern EInit g_EInitDiplocephalus;
extern EInit g_EInitDiplocephalusFoot;
extern EInit D_us_80180B3C;
extern EInit g_EInitDiplocephalusTail;
extern EInit g_EInitDiplocephalusFireball;
extern EInit g_EInitElevator;
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;
extern EInit g_EInitPlateLord;
extern EInit D_us_80180B90;
extern EInit g_EInitGhostEnemy;
extern EInit g_EInitMarionette;
extern EInit g_EInitSlinger;
extern EInit g_EInitSlingerPieces;
extern EInit g_EInitSlingerRib;
extern EInit g_EInitCtulhu;
extern EInit g_EInitCtulhuFireball;
extern EInit g_EInitCtulhuIceShockwave;
extern EInit g_EInitAxeKnight;
extern EInit g_EInitAxeKnightAxe;
extern EInit g_EInitOuijaTable;
extern EInit g_EInitOuijaTableComponent;
extern EInit g_EInitFleaMan;
extern EInit g_EInitSkeleton;
extern EInit g_EInitSkeletonPieces;
extern EInit g_EInitSkeletonBone;

// Clock room
extern u16 g_Statues[];
