// SPDX-License-Identifier: AGPL-3.0-or-later

#ifndef CAT_H
#define CAT_H

#define STAGE_IS_CAT

#include "stage.h"

#define OVL_EXPORT(x) CAT_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_UNK_BREAKABLE,         // EntityUnkBreakable
    E_EXPLOSION,             // EntityExplosion
    E_PRIZE_DROP,            // EntityPrizeDrop
    E_DAMAGE_DISPLAY,        // EntityDamageDisplay
    E_RED_DOOR,              // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,     // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,        // EntitySoulStealOrb
    E_ROOM_FOREGROUND,       // EntityRoomForeground
    E_STAGE_NAME_POPUP,      // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,       // EntityEquipItemDrop
    E_RELIC_ORB,             // EntityRelicOrb
    E_HEART_DROP,            // EntityHeartDrop
    E_ENEMY_BLOOD,           // EntityEnemyBlood
    E_MESSAGE_BOX,           // EntityMessageBox
    E_DUMMY_F,               // EntityDummy
    E_DUMMY_10,              // EntityDummy
    E_BACKGROUND_BLOCK,      // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,           // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,              // EntityUnkId13
    E_EXPLOSION_VARIANTS,    // EntityExplosionVariants
    E_GREY_PUFF,             // EntityGreyPuff
    E_UNK_16,                // func_us_801C4C7C
    E_UNK_17,                // func_us_801C589C
    E_UNK_18,                // func_us_801C5DF4
    E_UNK_19,                // func_us_801C56A0
    E_UNK_1A,                // func_us_801CA13C
    E_UNK_1B,                // func_us_801B732C
    E_UNK_1C,                // func_us_801B852C
    E_UNK_1D,                // func_us_801B7FE0
    E_UNK_1E,                // func_us_801B7F2C
    E_UNK_1F,                // func_us_801B7B64
    E_UNK_20,                // func_us_801B86B0
    E_UNK_21,                // func_us_801B8AD0
    E_UNK_22,                // func_us_801B87E8
    E_UNK_23,                // func_us_801BACF4
    E_UNK_24,                // func_us_801B972C
    E_UNK_25,                // func_us_801B9D1C
    E_UNK_26,                // func_us_801B9A74
    E_UNK_27,                // func_us_801B951C
    E_UNK_28,                // func_us_801B907C
    E_UNK_29,                // func_us_801BA388
    E_UNK_2A,                // func_us_801BA164
    E_UNK_2B,                // func_us_801B8D2C
    E_UNK_2C,                // func_us_801BA7FC
    E_BIG_RED_FIREBALL,      // EntityBigRedFireball
    E_DISCUS_LORD,           // EntityDiscusLord
    E_DISCUS,                // EntityDiscus
    E_DISCUS_TRAIL,          // EntityDiscusTrail
    E_DISCUS_CHAIN,          // EntityDiscusChain
    E_UNK_32,                // func_us_801CC2E4
    E_UNK_33,                // func_us_801CCEF0
    E_UNK_34,                // func_us_801CDB50
    E_UNK_35,                // func_us_801CD614
    E_UNK_36,                // func_us_801CE170
    E_UNK_37,                // func_us_801C839C
    E_UNK_38,                // func_us_801C8CE0
    E_UNK_39,                // func_us_801C7F84
    E_UNK_3A,                // func_us_801C7D98
    E_UNK_3B,                // func_us_801C774C
    E_UNK_3C,                // func_us_801C6360
    E_UNK_3D,                // func_us_801C7420
    E_LOSSOTH,               // EntityLossoth
    E_LOSSOTH_EFFECTS,       // EntityLossothEffects
    E_LOSSOTH_FIREBALL,      // EntityLossothFireball
    E_LOSSOTH_NAPALM,        // EntityLossothNapalmFlare
    E_LOSSOTH_FLAMES,        // EntityLossothFlames
    E_UNK_43,                // func_us_801BB4CC
    E_GRAVE_KEEPER,          // EntityGraveKeeper
    E_GRAVE_KEEPER_HITBOX,   // EntityGraveKeeperHitbox
    E_TOMBSTONE,             // EntityTombstone
    E_GREMLIN,               // EntityGremlin
    E_GREMLIN_EFFECT,        // EntityGremlinEffect
    E_GREMLIN_FIRE,          // EntityGremlinFire
    E_UNK_4A,                // EntityLargeSlime
    E_UNK_4B,                // func_us_801D3D08
    E_UNK_4C,                // EntitySlime
    E_UNK_4D,                // func_us_801D4744
    E_WERESKELETON,          // EntityWereskeleton
    E_ID_42,                 // func_us_801CE958
    E_ID_43,                 // func_us_801CEA2C
    E_THORNWEED,             // EntityThornweed
    E_CORPSEWEED,            // EntityCorpseweed
    E_CORPSEWEED_PROJECTILE, // EntityCorpseweedProjectile
    E_BLOOD_SKELETON,        // EntityBloodSkeleton
    NUM_ENTITIES,
};

extern EInit g_EInitDamageNum;
extern EInit g_EInitInteractable;
extern EInit g_EInitGremlin;
extern EInit g_EInitGremlinFire;
extern EInit g_EInitLockCamera;
extern EInit g_EInitObtainable;
extern EInit g_EInitWereskeleton;
extern EInit D_us_80180A88;

#endif
