// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#define OVL_EXPORT(x) RBO0_##x
#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_TORCH_A = 0x5A,
    PAL_TORCH_B = 0x5B,
};

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_UNK_BREAKABLE,          // EntityUnkBreakable
    E_EXPLOSION,              // EntityExplosion
    E_PRIZE_DROP,             // EntityPrizeDrop
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay
    E_RED_DOOR,               // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb
    E_ROOM_FOREGROUND,        // EntityRoomForeground
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop
    E_RELIC_ORB,              // EntityRelicOrb
    E_HEART_DROP,             // EntityHeartDrop
    E_ENEMY_BLOOD,            // EntityEnemyBlood
    E_MESSAGE_BOX,            // EntityMessageBox
    E_DUMMY_F,                // EntityDummy
    E_DUMMY_10,               // EntityDummy
    E_BACKGROUND_BLOCK,       // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,            // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,               // EntityUnkId13
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants
    E_GREY_PUFF,              // EntityGreyPuff
    E_BOSS_TORCH,             // EntityBossTorch
    E_BOSS_DOORS,             // EntityBossDoors
    E_LIFE_UP_SPAWN,          // EntityLifeUpSpawn
    E_COFFIN,                 // EntityCoffin
    E_UNK_1A,                 // OVL_EXPORT(EntityBoss)
    E_FAKE_RALPH,             // EntityFakeRalph
    E_FAKE_GRANT,             // EntityFakeGrant
    E_FAKE_SYPHA,             // EntityFakeSypha
    E_BONE_CROSS,             // EntityBoneCross
    E_BONE_CROSS_AFTER_IMAGE, // EntityBoneCrossAfterImage
    E_GIANT_BONE_CROSS,       // EntityGiantBoneCross
    E_DAGGER,                 // EntityDagger
    E_HOLY_WATER_FLASK,       // EntityHolyWaterFlask
    E_HOLY_WATER_FLAME,       // EntityHolyWaterFlame
    E_VERTICAL_DAGGER,        // EntityVerticalDagger
    E_HORIZONTAL_DAGGER,      // EntityHorizontalDagger
    E_UNK_26,                 // func_us_80197764
    E_UNK_27,                 // func_us_80196768
    E_DEATH_FLAMES,           // EntityDeathFlames
    E_HOLY_FLAME,             // EntityFlameAttack
    E_PETRIFY_CLOUD,          // EntityPetrifyCloud
    E_HOLY_LIGHTNING,         // EntityHolyLightning
    E_RESURRECT,              // EntitySummonAttack
    NUM_ENTITIES,
};

#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(BOSS_TORCH);
extern s32 E_ID(BOSS_DOORS);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(COFFIN);
extern s32 E_ID(UNK_1A);
extern s32 E_ID(FAKE_RALPH);
extern s32 E_ID(FAKE_GRANT);
extern s32 E_ID(FAKE_SYPHA);
extern s32 E_ID(BONE_CROSS);
extern s32 E_ID(BONE_CROSS_AFTER_IMAGE);
extern s32 E_ID(GIANT_BONE_CROSS);
extern s32 E_ID(DAGGER);
extern s32 E_ID(HOLY_WATER_FLASK);
extern s32 E_ID(HOLY_WATER_FLAME);
extern s32 E_ID(VERTICAL_DAGGER);
extern s32 E_ID(HORIZONTAL_DAGGER);
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
extern s32 E_ID(DEATH_FLAMES);
extern s32 E_ID(HOLY_FLAME);
extern s32 E_ID(PETRIFY_CLOUD);
extern s32 E_ID(HOLY_LIGHTNING);
extern s32 E_ID(RESURRECT);

#endif

extern EInit g_EInitInteractable;
extern s32 D_us_801806B0;
extern s32 D_us_801806B4; // boss state flag (how many defeated?)
