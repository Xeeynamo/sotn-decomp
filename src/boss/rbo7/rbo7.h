// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO7_H
#define RBO7_H

#include <stage.h>

#define STAGE_IS_RBO7

enum Palettes {
    PAL_NONE,
    PAL_AKMODAN_II = 0x23A,
};

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,            // EntityBreakable
    E_EXPLOSION,            // EntityExplosion
    E_PRIZE_DROP,           // EntityPrizeDrop
    E_DAMAGE_DISPLAY,       // EntityDamageDisplay
    E_RED_DOOR,             // EntityRedDoor
    E_INTENSE_EXPLOSION,    // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,       // EntitySoulStealOrb
    E_ROOM_FOREGROUND,      // EntityRoomForeground
    E_STAGE_NAME_POPUP,     // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,      // EntityEquipItemDrop
    E_RELIC_ORB,            // EntityRelicOrb
    E_PERSISTENT_ITEM_DROP, // EntityPersistentItemDrop
    E_ENEMY_BLOOD,          // EntityEnemyBlood
    E_MESSAGE_BOX,          // EntityMessageBox
    E_DUMMY_F,              // EntityDummy
    E_DUMMY_10,             // EntityDummy
    E_BACKGROUND_BLOCK,     // EntityBackgroundBlock
    E_LOCK_CAMERA,          // EntityLockCamera
    E_UNK_ID13,             // EntityUnkId13
    E_EXPLOSION_VARIANTS,   // EntityExplosionVariants
    E_GREY_PUFF,            // EntityGreyPuff
    E_BOSS_DOORS,           // EntityBossDoors
    E_BOSS_FIGHT_MANAGER,   // EntityBossFightManager
    E_LIFE_UP_SPAWN,        // EntityLifeUpSpawn
    E_AKMODAN_II,           // EntityAkmodanII
    E_UNK_1A,               // func_us_801957C0
    E_HARPY_KICK,           // EntityHarpyKick
    E_UNK_1C,               // func_us_80195A8C
    E_UNK_1D,               // func_us_80195D04
    E_CTULHU_DEATH,         // EntityCtulhuDeath
    NUM_ENTITIES,
};

#ifdef VERSION_PSP
extern s32 E_ID(BACKGROUND_BLOCK);
extern s32 E_ID(LOCK_CAMERA);
extern s32 E_ID(UNK_ID13);
extern s32 E_ID(EXPLOSION_VARIANTS);
extern s32 E_ID(GREY_PUFF);
extern s32 E_ID(BOSS_DOORS);
extern s32 E_ID(BOSS_FIGHT_MANAGER);
extern s32 E_ID(LIFE_UP_SPAWN);
extern s32 E_ID(AKMODAN_II);
extern s32 E_ID(UNK_1A);
extern s32 E_ID(HARPY_KICK);
extern s32 E_ID(UNK_1C);
extern s32 E_ID(UNK_1D);
extern s32 E_ID(CTULHU_DEATH);
#endif


enum BossMgrState {
    BOSS_MGR_IDLE = 0,       // initial state, fight not yet engaged
    BOSS_MGR_FIGHT_ON = 1,   // boss battle started
    BOSS_MGR_DEFEAT = 2,     // triggered as soon as the boss is defeated
    BOSS_MGR_TERMINATED = 4, // boss is dead, entity got destroyed
};

#endif // RBO7_H
