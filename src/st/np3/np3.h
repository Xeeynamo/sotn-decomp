// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define OVL_EXPORT(x) NP3_##x
#define STAGE_IS_NP3

#define E_PUFF_OPAQUE_PALETTE_OFFSET 0xD0

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
    /* 0x19 */ E_CASTLE_DOOR,
    /* 0x1A */ E_ID_1A,
    /* 0x1B */ E_ID_1B,
    /* 0x1C */ E_ID_1C,
    /* 0x1D */ E_ID_1D,
    /* 0x1E */ E_CAVERN_DOOR_PLATFORM,
    /* 0x1F */ E_ID_1F,
    /* 0x20 */ E_ID_20,
    /* 0x21 */ E_ID_21,
    /* 0x22 */ E_ID_22,
    /* 0x23 */ E_ID_23,
    /* 0x24 */ E_ID_24,
    /* 0x25 */ E_ID_25,
    /* 0x26 */ E_ID_26,
    /* 0x27 */ E_FALLING_ROCK_2,
    /* 0x28 */ E_LIGHTNING_THUNDER,
    /* 0x29 */ E_LIGHTNING_CLOUD,
    /* 0x2A */ E_ID_2A,
    /* 0x2B */ E_ID_2B,
    /* 0x2C */ E_ID_2C,
    /* 0x2D */ E_SPLASH_WATER,
    /* 0x2E */ E_SURFACING_WATER,
    /* 0x2F */ E_SIDE_WATER_SPLASH,
    /* 0x30 */ E_SMALL_WATER_DROP,
    /* 0x31 */ E_WATER_DROP,
    /* 0x32 */ E_MERMAN2,
    /* 0x33 */ E_MERMAN_WATER_SPLASH,
    /* 0x34 */ E_MEDIUM_WATER_SPLASH,
    /* 0x35 */ E_HIGH_WATER_SPLASH,
    /* 0x36 */ E_MERMAN2_SPIT_FIRE,
    /* 0x37 */ E_MERMAN2_DYING,
    /* 0x38 */ E_MERMAN2_JUMP_AIR,
    /* 0x39 */ E_MERMAN,
    /* 0x3A */ E_MERMAN_SPIT_FIRE,
    /* 0x3B */ E_MERMAN_JUMP_AIR,
    /* 0x3C */ E_MERMAN_DYING,
    /* 0x3D */ E_ID_3D,
    /* 0x3E */ E_ID_3E,
    /* 0x3F */ E_BONE_SCIMITAR_PARTS,
    /* 0x40 */ E_BAT,
    /* 0x41 */ E_ID_41,
    /* 0x42 */ E_ZOMBIE,
    /* 0x43 */ E_ZOMBIE_SPAWNER,
    /* 0x44 */ E_OWL_KNIGHT,
    /* 0x45 */ E_OWL,
    /* 0x46 */ E_OWL_KNIGHT_SWORD,
    /* 0x47 */ E_OWL_TARGET,
    /* 0x48 */ E_BLOODY_ZOMBIE,
    /* 0x49 */ E_BLOOD_DRIPS,
    /* 0x4A */ E_BLOOD_SPLATTER,
    /* 0x4B */ E_STAIRWAY_PIECE,
    /* 0x4C */ E_FALLING_ROCK,
    /* 0x4D */ E_EXPLODE_PUFF_OPAQUE,
    /* 0x4E */ E_ID_4E,
    /* 0x4F */ E_SLOGRA_SPEAR,
    /* 0x50 */ E_SLOGRA_SPEAR_PROJECTILE,
    /* 0x51 */ E_GAIBON,
    /* 0x52 */ E_GAIBON_LEG,
    /* 0x53 */ E_GAIBON_SMALL_FIREBALL,
    /* 0x54 */ E_GAIBON_BIG_FIREBALL,
    /* 0x55 */ E_HAMMER, // the enemy named "Hammer", Gurkha's friend
    /* 0x56 */ E_GURKHA_BODY_PARTS,
    /* 0x57 */ E_HAMMER_WEAPON,
    /* 0x58 */ E_GURKHA,
    /* 0x59 */ E_GURKHA_WEAPON,
    /* 0x5A */ E_BLADE,
    /* 0x5B */ E_BLADE_WEAPON
} EntityIDs;

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

extern EInit OVL_EXPORT(EInitBreakable);
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit g_EInitSpawner;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
extern EInit g_EInitDamageNum;
extern EInit g_EInitStInteractable;
extern EInit g_EInitWaterObject;
extern EInit g_EInitWaterSplash;
extern EInit g_EInitMerman;
extern EInit g_EInitMermanFireball;
extern EInit g_EInitBoneScimitar;
extern EInit g_EInitScimitarParts;
extern EInit g_EInitBat;
extern EInit g_EInitZombie;
extern EInit g_EInitOwlKnight;
extern EInit g_EInitOwlKnightSword;
extern EInit g_EInitOwl;
extern EInit g_EInitBloodyZombie;
extern EInit g_EInitSlograNP3;
extern EInit g_EInitSlograSpearNP3;
extern EInit g_EInitSlograProjectileNP3;
extern EInit g_EInitGaibonNP3;
extern EInit g_EInitGaibonProjectileNP3;
extern EInit g_EInitGaibonLargeProjectileNP3;
extern EInit g_EInitGurkhaType0;
extern EInit g_EInitGurkhaHammer;
extern EInit g_EInitGurkha;
extern EInit g_EInitGurkhaWeapon;
extern EInit g_EInitBlade;
extern EInit g_EInitBladeWeapon;

extern void ReplaceBreakableWithItemDrop(Entity*);
extern Primitive* FindFirstUnkPrim(Primitive* poly);

extern void func_801BAFA0(s16);
extern void func_801BB044(s16);
extern void func_801BB140(s16);
extern void func_801BB2F8(s16);
extern void func_801BB3F4(s16);
extern s32 UnkCollisionFunc(s16* hitSensors, s16 sensorCount);
extern s32 GetPlayerCollisionWith(Entity* entity, u16 w, u16 h, u16 flags);
#ifdef VERSION_PC
extern s16 GetDistanceToPlayerX(void);
#endif
extern void EntityExplosionVariants(Entity* entity);
extern void func_801CD658();
extern void EntityPrizeDrop(Entity* entity);
extern void EntityEquipItemDrop(Entity* entity);
extern Primitive* func_801D2470(Primitive* poly);
void EntityGreyPuff(Entity* entity);
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
extern u16 D_80180AF0[];
extern u16 D_8018112C[];
extern u16 D_80181144[];
extern u16 D_8018115C[]; // this could be a struct
extern u16 D_80181168[];
extern u16 D_80181180[];
extern u16 D_801811AA[];
extern u16 D_801811E6[];

extern s16 g_WaterXTbl[]; // pos TBL

extern s16 D_80181A50[];
extern u16 D_80181D80[];
extern u16 D_80181DB0[];
extern u16 D_80181E74[];
extern s8 c_HeartPrizes[];
extern s32 D_80181E80[];
extern const u8* D_80181F2C[];
extern u8 D_80182008[];
extern u8 D_80182400[];
extern u8 D_80182414[];
extern s32 D_80182440[];
extern u8 D_80182454[];
extern u16 D_80182458[];
extern u8 D_80182594[];
extern u8 D_801825A8[];
extern u8 D_801825BC[];
extern u16 D_801825CC;

// *** EntityBloodyZombie properties START ***

extern s32 D_801825D4;
extern u16 D_801825E4[];
extern u8 D_801825EC[]; // Animation: Walking
extern u8 D_801825FC[]; // Animation: Bloody Zombie sword slash
extern u8 D_80182620[]; // Animation: Recoil from being hit
extern u8 D_80182634[]; // Animation: Dying
extern u8 D_8018267C[]; // Animation: Walking faster
// unk80 Walking direction timer
// unk84 BloodSplatter facing

// *** EntityBloodyZombie properties END ***

extern s32 D_8018268C;
extern s32 D_801826A4;
extern s32 D_801826C4;

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern SVECTOR g_CastleDoorVector;

// For EntityHammer
extern u16 D_80182978[];
extern s16 D_80182988[];
extern s16 D_80182A20[];
extern s16 D_80182A40[];
extern s16 D_80182A5C[];
extern s16 D_80182AB8[];
extern s16 D_80182AD0[];
extern s16 D_80182AE8[];
extern s16 D_80182B00[];
extern s16 D_80182B54[];
extern s16 D_80182BB4[];
extern s16 D_80182BEC[];
extern s16 D_80182C9C[];
extern s16 D_80182CC4[];
extern s16 D_80182CFC[];
extern s16 D_80182E38[];
extern s16 D_80182E48[];
extern s16 D_80182EDC[];

extern bool slograGaibonRetreat;
