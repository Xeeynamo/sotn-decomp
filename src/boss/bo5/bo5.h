// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef BO5_H
#define BO5_H

#include <stage.h>

#define STAGE_IS_BO5

enum Palettes {
    PAL_NONE = 0,
    PAL_STAINED_GLASS = 0xE,
    PAL_STAINED_GLASS_BG = 0xF,
    PAL_CASTLE_WALL_1 = 0x74,
    PAL_BELL = 0x75,
    PAL_BELL_ROPE = 0x76,
    PAL_CLOUDS = 0xC0,
    PAL_BACKGROUND_SKY_LAND = 0xC5,
    PAL_CASTLE_WALL_2 = 0xC8,
    PAL_HIPPOGRYPH = 0x200,
    PAL_STAINED_GLASS_LIGHT = 0x204,
    PAL_STAINED_GLASS_BG_LIGHT = 0x205,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,                // EntityBreakable
    E_EXPLOSION,                // EntityExplosion
    E_PRIZE_DROP,               // EntityPrizeDrop
    E_DAMAGE_DISPLAY,           // EntityDamageDisplay
    E_RED_DOOR,                 // EntityRedDoor
    E_INTENSE_EXPLOSION,        // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,           // EntitySoulStealOrb
    E_ROOM_FOREGROUND,          // EntityRoomForeground
    E_STAGE_NAME_POPUP,         // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,          // EntityEquipItemDrop
    E_RELIC_ORB,                // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP,     // EntityPersistentItemDrop
    E_ENEMY_BLOOD,              // EntityEnemyBlood
    E_MESSAGE_BOX,              // EntityMessageBox
    E_DUMMY_F,                  // EntityDummy
    E_DUMMY_10,                 // EntityDummy
    E_BACKGROUND_BLOCK,         // EntityBackgroundBlock
    E_LOCK_CAMERA,              // EntityLockCamera
    E_UNK_ID13,                 // EntityUnkId13
    E_EXPLOSION_VARIANTS,       // EntityExplosionVariants
    E_GREY_PUFF,                // EntityGreyPuff
    E_CAMERA_BOUNDS,            // EntityCameraBounds
    E_STAINED_GLASS,            // EntityStainedGlass
    E_STAINED_GLASS_BACKGROUND, // EntityStainedGlassBackground
    E_BLOCK,                    // EntityBlock
    E_STATUE,                   // EntityStatue
    E_BELL,                     // EntityBell
    E_CASTLE_WALL1,             // EntityCastleWall1
    E_CASTLE_WALL2,             // EntityCastleWall2
    E_STAIRCASE,                // EntityStaircase
    E_CLOUDS,                   // EntityClouds
    E_BACKGROUND_SKY_LAND,      // EntityBackgroundSkyLand
    E_RBO3DOOR,                 // EntityRbo3Door
    E_UNK_22,                   // func_us_801A1C14
    E_UNK_23,                   // EntityHippogryphHitbox
    E_UNK_24,                   // EntityFireDamageHitbox
    E_UNK_25,                   // func_us_801A3FD4
    E_UNK_26,                   // func_us_801A3E78
    E_UNK_27,                   // func_us_801A3B88
    E_LIFE_UP_SPAWN,            // EntityLifeUpSpawn
    E_PLAY_DEATH_BALLAD,        // EntityPlayDeathBallad
    E_CUTSCENE,                 // EntityCutscene
    E_CUTSCENE_STAGE,           // EntityCutsceneStage
    E_UNK_2C,                   // func_us_801A62B4
    E_UNK_2D,                   // func_801B1D68
    E_UNK_2E,                   // RicSetDeadPrologue
    NUM_ENTITIES,
};

#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(CAMERA_BOUNDS);
extern s32 E_ID(STAINED_GLASS);
extern s32 E_ID(STAINED_GLASS_BACKGROUND);
extern s32 E_ID(BLOCK);
extern s32 E_ID(STATUE);
extern s32 E_ID(BELL);
extern s32 E_ID(CASTLE_WALL1);
extern s32 E_ID(CASTLE_WALL2);
extern s32 E_ID(STAIRCASE);
extern s32 E_ID(CLOUDS);
extern s32 E_ID(BACKGROUND_SKY_LAND);
extern s32 E_ID(RBO3DOOR);
extern s32 E_ID(UNK_22);
extern s32 E_ID(UNK_23);
extern s32 E_ID(UNK_24);
extern s32 E_ID(UNK_25);
extern s32 E_ID(UNK_26);
extern s32 E_ID(UNK_27);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(PLAY_DEATH_BALLAD);
extern s32 E_ID(CUTSCENE);
extern s32 E_ID(CUTSCENE_STAGE);
extern s32 E_ID(UNK_2C);
extern s32 E_ID(UNK_2D);
extern s32 E_ID(UNK_2E);
#endif

extern s32 D_us_801806DC;

#endif // BO5_H
