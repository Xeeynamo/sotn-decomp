// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#define INVERTED_STAGE

enum Palettes {
    PAL_NONE,
    PAL_TORCH_A = 0x5A,
    PAL_TORCH_B = 0x5B,
    PAL_UNK_169 = 0x169,
    PAL_UNK_210 = 0x210,
    PAL_UNK_2E4 = 0x2E4,
    PAL_UNK_2E9 = 0x2E9,
    PAL_UNK_2EF = 0x2EF,
};

typedef enum EntityID {
    E_NONE,
    E_UNK_BREAKABLE,          // EntityUnkBreakable
    E_EXPLOSION,              // EntityExplosion
    E_PRIZE_DROP,             // EntityPrizeDrop
    E_DAMAGE_DISPLAY,         // EntityDamageDisplay
    E_RED_DOOR,               // EntityRedDoor
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb
    E_ROOM_FOREGROUND,        // EntityRoomForeground
    E_STAGE_NAME_POPUP,       // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop
    E_RELIC_ORB,              // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,   // EntityPersistentItemDrop
    E_ENEMY_BLOOD,            // EntityEnemyBlood
    E_MESSAGE_BOX,            // EntityMessageBox
    E_DUMMY_F,                // EntityDummy
    E_DUMMY_10,               // EntityDummy
    E_BACKGROUND_BLOCK,       // EntityBackgroundBlock
    E_LOCK_CAMERA,            // EntityLockCamera
    E_UNK_ID13,               // EntityUnkId13
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants
    E_GREY_PUFF,              // EntityGreyPuff
    E_BOSS_TORCH,             // EntityBossTorch
    E_BOSS_DOORS,             // EntityBossDoors
    E_LIFE_UP_SPAWN,          // EntityLifeUpSpawn
    E_COFFIN,                 // EntityCoffin
    E_BOSS_FIGHT_MANAGER,     // EntityBossFightManager
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

enum BossMgrState {
    BOSS_MGR_IDLE = 0,       // initial state, fight not yet engaged
    BOSS_MGR_FIGHT_ON = 1,   // boss battle started
    BOSS_MGR_INTRO_DONE = 2, // the fake party members become hittable
    BOSS_MGR_TERMINATED = 4, // bosses are dead
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
extern s32 E_ID(BOSS_FIGHT_MANAGER);
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
extern s32 g_BossMgrState;
extern s32 D_us_801806B4; // boss state flag (how many defeated?)

// the fake trio reads unk8C from their own coffin
struct EntityCoffin {
    ENTITY_SHARED;
    /* 0x7C */ struct Primitive* prim;
    /* 0x80 */ s16 timer;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s16 unk84;
    /* 0x86 */ s16 : 16;
    /* 0x88 */ s16 unk88;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ s32 unk8C;
};
SYNC_STRUCT(EntityCoffin);
