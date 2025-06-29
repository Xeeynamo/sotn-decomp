// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define OVL_EXPORT(x) NP3_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

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
    /* 0x46 */ E_801CD540,
    /* 0x47 */ E_801CD620,
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
    /* 0x52 */ E_GAIBON_IDLE,
    /* 0x53 */ E_GAIBON_SMALL_FIREBALL,
    /* 0x54 */ E_GAIBON_BIG_FIREBALL,
    /* 0x55 */ E_HAMMER, // the enemy named "Hammer", Gurkha's friend
    /* 0x56 */ E_GURKHA_BODY_PARTS,
    /* 0x57 */ E_HAMMER_WEAPON,
    /* 0x58 */ E_GURKHA,
    /* 0x59 */ E_GURKHA_SWORD,
    /* 0x5A */ E_BLADE,
    /* 0x5B */ E_BLADE_SWORD
} EntityIDs;

extern void ReplaceBreakableWithItemDrop(Entity*);
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
extern EInit OVL_EXPORT(EInitBreakable);
extern u8* g_eBreakableAnimations[8];
extern u8 g_eBreakableHitboxes[];
extern u8 g_eBreakableExplosionTypes[];
extern u16 g_eBreakableanimSets[];
extern u8 g_eBreakableDrawModes[];
extern u16 g_EInitObtainable[];
extern u16 g_EInitParticle[];
extern u16 g_EInitSpawner[];
extern u16 g_EInitInteractable[];
extern u16 g_EInitLockCamera[];
extern u16 g_EInitCommon[];
extern u16 g_EInitWaterObject[];
extern u16 g_EInitWaterSplash[];
extern u16 g_EInitMerman[];
extern u16 g_EInitMermanFireball[];
extern u16 D_80180AF0[];
extern u16 g_EInitBat[];
extern u16 g_EInitZombie[];
extern u16 D_80180B20[];
extern u16 g_EInitSlograSpearNP3[];
extern u16 g_EInitSlograProjectileNP3[];
extern u16 g_EInitGaibonNP3[];
extern u16 g_EInitGaibonProjectileNP3[];
extern u16 g_EInitGaibonLargeProjectileNP3[];
extern u16 g_EInitGurkhaHammer[];
extern u16 g_EInitGurkhaSword[];
extern u16 g_EInitGurkhaBlade[];
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
extern u8 D_8018258C[];
extern u8 D_80182594[];
extern u8 D_801825A8[];
extern u8 D_801825BC[];
extern u16 D_801825CC;

// *** EntityBloodyZombie properties START ***

extern u16 g_EInitBloodyZombie[]; // InitProps
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
extern u8 D_80182914[];
extern u8 D_80182935[];

// *** EntitySoulStealOrb properties START ***

extern u16 g_ESoulStealOrbAngles[];
extern s16 g_ESoulStealOrbSprt[];
extern u8 g_ESoulStealOrbAnim[];

// *** EntitySoulStealOrb properties END ***

extern SVECTOR g_CastleDoorVector;

// For EntityHammer
extern u16 g_EInitGurkhaType0[];
extern u16 D_80182978[];
extern s16 D_80182988[];
extern s16 D_80182A20;
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

// For EntityGurkhaBodyParts
extern u16 g_EInitGurkhaType2[];

// For EntityGurkha
extern u16 g_EInitGurkhaType1[];
extern u16 D_80182EF4[];
extern s16 D_80182F04[];
extern s16 D_80182F9C;
extern s16 D_80182FBC[];
extern s16 D_80182FD8[];
extern s16 D_80182FF4[];
extern s16 D_80183010[];
extern s16 D_8018302C[];
extern s16 D_80183044[];
extern s16 D_80183098[];
extern s16 D_801830F8[];
extern s16 D_80183130[];
extern s16 D_801831F8[];
extern s16 D_80183218[];
extern s16 D_80183258[];
extern s16 D_80183284[];
extern s16 D_80183360[];
extern s16 D_80183378[];
extern s16 D_801833A0[];
extern s16 D_801833CC[];

// For EntityOwl
extern u16 g_EInitOwl[];
extern u16 D_801826CC[];
extern u8 D_801826EC[];
extern u8 D_801826F8[];
extern u8 D_80182710[];
extern u8 D_80182720[];
extern u8 D_80182734[];
extern u8 D_80182740[];
extern u8 D_8018274C[];

// For EntityOwlKnight
extern u16 D_80180B14[];
extern u16 D_80182758[];
extern s16 D_80182768[];
extern u8 D_80182770[];
extern u8 D_80182778[];
extern u8 D_80182788[];
extern u8 D_80182794[];
extern u8 D_801827A8[];
extern u8 D_801827BC[];
extern u8 D_801827C8[];
extern u8 D_801827D8[];
extern u8 D_801827EC[];
extern u8 D_80182800[];
extern u8 D_80182820[];
extern u8 D_80182834[];
extern u8 D_8018284C[];
extern u8 D_80182860[];
extern u8 D_80182888[];
extern u8 D_801828A0[];
extern u8 D_801828AC[];
extern s8 D_801828B8[];
extern u8 D_801828C8[];
extern s16 D_8018290C[];

// For EntityBlade

extern u16 D_801833E4[];
extern s16 D_801833F4;
extern s16 D_80183494;
extern s16 D_801834B8[];
extern s16 D_801834D8[];
extern s16 D_801834F8[];
extern s16 D_80183514[];
extern s16 D_80183530[];
extern s16 D_80183548[];
extern s16 D_80183560[];
extern s16 D_80183570[];
extern s16 D_80183580[];
extern s16 D_801835A8[];
extern s16 D_80183600[];
extern s16 D_80183638[];
extern s16 D_80183700[];
extern s16 D_80183720[];
extern s16 D_80183760[];
extern s16 D_8018386C[];
extern s16 D_8018389C[];
extern s16 D_801838C4[];
extern s16 D_80183934[];
extern s16 D_80183990[];
extern s16 D_80183A24[];
extern s16 D_80183A4C[];

// for EntityBackgroundBushes

extern u16 g_EInitStInteractable[];

extern bool D_801812CC;
