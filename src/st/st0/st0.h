// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#undef STAGE
#define STAGE STAGE_ST0

#define STAGE_IS_ST0

#define OVL_EXPORT(x) ST0_##x

typedef enum EntityID {
    E_NONE,
    E_BREAKABLE,              // func_801A805C
    E_EXPLOSION,              // EntityExplosion
    E_PRIZE_DROP,             // EntityPrizeDrop
    E_NUMERIC_DAMAGE,         // EntityDamageDisplay
    E_RED_DOOR,               // EntityRedDoor
    E_INTENSE_EXPLOSION,      // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,         // EntitySoulStealOrb
    E_ROOM_FOREGROUND,        // EntityRoomForeground
    E_DUMMY_09,               // EntityDummy
    E_EQUIP_ITEM_DROP,        // EntityEquipItemDrop
    E_DUMMY_0B,               // EntityDummy
    E_DUMMY_0C,               // EntityDummy
    E_DUMMY_0D,               // EntityDummy
    E_DUMMY_0E,               // EntityDummy
    E_DUMMY_0F,               // EntityDummy
    E_DUMMY_10,               // EntityDummy
    E_BACKGROUND_BLOCK,       // EntityBackgroundBlock
    E_LOCK_CAMERA,            // EntityLockCamera
    E_ID_13,                  // EntityUnkId13
    E_EXPLOSION_VARIANTS,     // EntityExplosionVariants
    E_GREY_PUFF,              // EntityGreyPuff
    E_CUTSCENE,               // EntityCutscene
    E_CUTSCENE_SUPPORT,       // EntityCutsceneSupport
    E_STAGE_TITLE_CARD,       // EntityStageTitleCard
    E_STAGE_TITLE_FADEOUT,    // EntityStageTitleFadeout
    E_DRACULA,                // EntityDracula
    E_DRACULA_FIREBALL,       // EntityDraculaFireball
    E_DRACULA_METEORBALL,     // EntityDraculaMeteorball
    E_DRACULA_BODY,           // EntityDraculaBody
    E_ID_1E,                  // func_801AD838
    E_DRACULA_GLASS,          // EntityDraculaGlass
    E_DRACULA_FINAL_FORM,     // EntityDraculaFinalForm
    E_DRACULA_MEGA_FIREBALL,  // EntityDraculaMegaFireball
    E_DRACULA_RAIN_ATTACK,    // EntityDraculaRainAttack
    E_DEMATERIALIZE_STAGE_BG, // EntityDematerializeStageBg
    E_BACKGROUND_VORTEX,      // EntityBackgroundVortex
    E_BACKGROUND_CLOUDS,      // EntityBackgroundClouds
    E_ID_26,                  // func_801A8328
    E_SCRET_STAIRS_CEILING,   // EntitySecretStairsCeiling
    E_SECRET_BUTTON,          // EntitySecretButton
    E_SECRET_STAIRS,          // EntitySecretStairs
    E_CLOCK_TOWER_3D,         // EntityClockTower3D
    E_ID_2B,                  // func_801AF774
    E_PHOTOGRAPH,             // EntityCutscenePhotograph
    E_PHOTOGRAPH_FIRE,        // EntityCutscenePhotographFire
    E_ID_2E,                  // func_801BC5C0
} EntityID;

void MoveEntity();
void EntityExplosion(Entity*);
void EntityExplosionVariants(Entity* entity);
void EntityGreyPuff(Entity* entity);

extern EInit g_EInitBreakable;
extern EInit g_EInitParticle;
extern EInit g_EInitCutscene;
extern EInit g_EInitCommon;
extern EInit g_EInit3DObject;
extern EInit g_EInitDracula;
extern EInit g_EInitDraculaFireball;
extern EInit g_EInitDraculaFinalForm;
extern EInit g_EInitDraculaMegaFireball;
extern EInit g_EInitSecretStairs;
extern EInit g_EInitObtainable;
