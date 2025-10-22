// SPDX-License-Identifier: AGPL-3.0-or-later

#include "stage.h"

#define STAGE_IS_NO2

#define OVL_EXPORT(x) NO2_##x

enum OVL_EXPORT(Palette) {
    PAL_NONE = 0,
    PAL_SKELERANG = 0x200,
    PAL_UNK_203 = 0x203,
    PAL_VALHALLA_KNIGHT = 0x207,
    PAL_OWL_KNIGHT = 0x21C,
    PAL_BLOODY_ZOMBIE = 0x223,
    PAL_BLADE = 0x238,
    PAL_GURKHA = 0x23B,
    PAL_UNK_23E = 0x23E,
    PAL_SPECTRAL_SWORD = 0x241,
    PAL_UNK_242 = 0x242,
    PAL_BREAKABLE = 0x251,
    PAL_BREAKABLE_DEBRIS = 0x255,
    PAL_OWL_KNIGHT_SWORD = 0x2CB,
};

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_BREAKABLE,           // EntityBreakable
    E_EXPLOSION,           // EntityExplosion
    E_PRIZE_DROP,          // EntityPrizeDrop
    E_DAMAGE_DISPLAY,      // EntityDamageDisplay
    E_RED_DOOR,            // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,   // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,      // EntitySoulStealOrb
    E_ROOM_FOREGROUND,     // EntityRoomForeground
    E_STAGE_NAME_POPUP,    // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,     // EntityEquipItemDrop
    E_RELIC_ORB,           // EntityRelicOrb
    E_HEART_DROP,          // EntityHeartDrop
    E_ENEMY_BLOOD,         // EntityEnemyBlood
    E_MESSAGE_BOX,         // EntityMessageBox
    E_DUMMY_F,             // EntityDummy
    E_DUMMY_10,            // EntityDummy
    E_BACKGROUND_BLOCK,    // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,         // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,            // EntityUnkId13
    E_EXPLOSION_VARIANTS,  // EntityExplosionVariants
    E_GREY_PUFF,           // EntityGreyPuff
    E_SKELERANG,           // EntitySkelerang
    E_SKELERANG_BOOMERANG, // EntitySkelerangBoomerang
    E_SKELERANG_UNKNOWN,   // EntitySkelerangUnknown
    E_UNK_19,              // func_us_801B3D8C
    E_UNK_1A,              // func_us_801B3F30
    E_UNK_1B,              // func_us_801B4148
    E_UNK_1C,              // func_us_801B41A4
    E_UNK_1D,              // func_us_801B4210
    E_3D_BACKGROUND_HOUSE, // Entity3DBackgroundHouse
    E_3D_HOUSE_SPAWNER,    // Entity3DHouseSpawner
    E_UNK_20,              // func_us_801B4DA4
    E_UNK_21,              // func_us_801B5750
    E_ID_22,               // func_us_801B5368
    E_ID_23,               // func_us_801B52B4
    E_UNK_24,              // func_us_801B5FB8
    E_UNK_25,              // func_us_801B68EC
    E_UNK_26,              // func_us_801B65A4
    E_BIG_RED_FIREBALL,    // EntityBigRedFireball
    E_ID_28,               // func_us_801B6E34
    E_OWL_KNIGHT,          // EntityOwlKnight
    E_OWL,                 // EntityOwl
    E_OWL_KNIGHT_SWORD,    // EntityOwlKnightSword
    E_OWL_TARGET,          // EntityOwlTarget
    E_BLOODY_ZOMBIE,       // EntityBloodyZombie
    E_BLOOD_DRIPS,         // EntityBloodDrips
    E_BLOOD_SPLATTER,      // EntityBloodSplatter
    E_UNK_30,              // func_us_801B72E8
    E_ID_31,               // func_us_801B5948
    E_ID_32,               // func_us_801B7580
    E_UNK_33,              // func_us_801B7980
    E_VALHALLA_KNIGHT,     // EntityValhallaKnight
    E_UNK_35,              // func_us_801C8954
    E_UNK_36,              // func_us_801C8AAC
    E_HAMMER,              // EntityHammer
    E_GURKHA_BODY_PARTS,   // EntityGurkhaBodyParts
    E_HAMMER_WEAPON,       // EntityHammerWeapon
    E_GURKHA,              // EntityGurkha
    E_GURKHA_WEAPON,       // EntityGurkhaWeapon
    E_BLADE,               // EntityBlade
    E_BLADE_WEAPON,        // EntityBladeWeapon
    E_SPECTRAL_SWORD,      // EntitySpectralSword
    E_UNK_3F,              // func_us_801CEB08
    E_POLTERGEIST,         // EntityPoltergeist
    E_BREAKABLE_DEBRIS,    // EntityBreakableDebris
    NUM_ENTITIES,
};

extern Primitive* FindFirstUnkPrim(Primitive* prim);
extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

extern EInit g_EInitBreakable;
extern EInit g_EInitObtainable;
extern EInit g_EInitParticle;
extern EInit D_us_80180844;
extern EInit g_EInitInteractable;
extern EInit g_EInitUnkId13;
extern EInit g_EInitLockCamera;
extern EInit g_EInitCommon;
extern EInit g_EInitDamageNum;
extern EInit g_EInitSkelerang;
extern EInit g_EInitSkelerangBoomerang;
extern EInit D_us_801808A4;
extern EInit D_us_801808B0;
extern EInit g_EInitOwlKnight;
extern EInit g_EInitOwlKnightSword;
extern EInit g_EInitOwl;
extern EInit g_EInitBloodyZombie;
extern EInit D_us_801808EC;
extern EInit g_EInitValhallaKnight;
extern EInit D_us_80180904;
extern EInit D_us_80180910;
extern EInit D_us_8018091C;
extern EInit g_EInitHammer;
extern EInit g_EInitHammerWeapon;
extern EInit g_EInitGurkha;
extern EInit g_EInitGurkhaWeapon;
extern EInit g_EInitBlade;
extern EInit g_EInitBladeWeapon;
extern EInit g_EInitSpectralSword;
extern EInit D_us_8018097C;
extern EInit g_EInitPoltergeist;
