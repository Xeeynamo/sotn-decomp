// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ARE_H
#define ARE_H

#include <stage.h>

#define OVL_EXPORT(x) ARE_##x
#define STAGE_IS_ARE


enum OVL_EXPORT(Palettes) {
    PAL_NONE,
};

enum OVL_EXPORT(Entities) {
    E_NONE,
    E_BREAKABLE,                // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                // EntityExplosion
    E_PRIZE_DROP,               // EntityPrizeDrop
    E_DAMAGE_DISPLAY,           // EntityDamageDisplay
    E_RED_DOOR,                 // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,        // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,           // EntitySoulStealOrb
    E_ROOM_FOREGROUND,          // EntityRoomForeground
    E_STAGE_NAME_POPUP,         // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,          // EntityEquipItemDrop
    E_RELIC_ORB,                // EntityRelicOrb
    E_HEART_DROP,               // EntityHeartDrop
    E_ENEMY_BLOOD,              // EntityEnemyBlood
    E_MESSAGE_BOX,              // EntityMessageBox
    E_DUMMY_F,                  // EntityDummy
    E_DUMMY_10,                 // EntityDummy
    E_BACKGROUND_BLOCK,         // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,              // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                 // EntityUnkId13
    E_EXPLOSION_VARIANTS,       // EntityExplosionVariants
    E_GREY_PUFF,                // EntityGreyPuff
    E_UNK_16,                   // func_pspeu_09237A60
    E_UNK_17,                   // func_pspeu_09239C40
    E_UNK_18,                   // func_pspeu_0923AA20
    E_UNK_19,                   // func_pspeu_0923AE60
    E_UNK_1A,                   // func_pspeu_09238AA0
    E_HEART_ROOM_SWITCH,        // EntityHeartRoomSwitch
    E_UNK_1C,                   // func_pspeu_09239558
    E_UNK_1D,                   // func_pspeu_09238820
    E_UNK_1E,                   // func_pspeu_0923B2C0
    E_UNK_1F,                   // func_pspeu_092385C8
    E_EXPLOSION_PUFF_OPAQUE,    // EntityExplosionPuffOpaque
    E_BREAKABLE_DEBRIS,         // OVL_EXPORT(EntityBreakableDebris)
    E_UNK_22,                   // func_pspeu_0925E2B0
    E_UNK_23,                   // func_pspeu_0925F050
    E_UNK_24,                   // func_pspeu_0925F1C8
    E_UNK_25,                   // func_pspeu_0925F568
    E_UNK_26,                   // func_pspeu_09260700
    E_UNK_27,                   // func_pspeu_09261060
    E_BONE_HALBERD_PARTS,       // EntityBoneHalberdParts
    E_UNK_29,                   // func_pspeu_0925F620
    E_UNK_2A,                   // func_pspeu_092600D8
    E_OWL_KNIGHT,               // EntityOwlKnight
    E_OWL,                      // EntityOwl
    E_OWL_KNIGHT_SWORD,         // EntityOwlKnightSword
    E_OWL_TARGET,               // EntityOwlTarget
    E_VALHALLA_KNIGHT,          // EntityValhallaKnight
    E_UNK_30,                   // func_us_801C8954
    E_UNK_31,                   // func_us_801C8AAC
    E_UNK_32,                   // func_pspeu_0923D440
    E_UNK_33,                   // func_pspeu_0923E5B0
    E_UNK_34,                   // func_pspeu_0923E7B8
    E_UNK_35,                   // func_pspeu_09253D80
    E_UNK_36,                   // func_pspeu_092461A8
    E_UNK_37,                   // func_pspeu_09246BF8
    E_UNK_38,                   // func_pspeu_092449E8
    E_UNK_39,                   // func_pspeu_09246F88
    E_HUNTING_GIRL,             // EntityHuntingGirl
    E_HUNTING_GIRL_ATTACK,      // EntityHuntingGirlAttack
    E_UNK_3C,                   // func_pspeu_0923E970
    E_UNK_3D,                   // func_pspeu_0923FEF0
    E_UNK_3E,                   // func_pspeu_09240078
    E_UNK_3F,                   // func_pspeu_0923FDF8
    E_FLEA_ARMOR,               // EntityFleaArmor
    E_FLEA_ARMOR_ATTACK_HITBOX, // EntityFleaArmorAttackHitbox
    E_FLEA_MAN,                 // EntityFleaMan
    E_BONE_SCIMITAR,            // EntityBoneScimitar
    E_BONE_SCIMITAR_PARTS,      // EntityBoneScimitarParts
    E_UNK_45,                   // func_pspeu_092479D0
    E_UNK_46,                   // func_pspeu_0924A2C0
    E_UNK_47,                   // func_pspeu_0924A4D0
    E_UNK_48,                   // func_pspeu_0924ADC0
    E_UNK_49,                   // func_pspeu_0924BD30
    E_UNK_4A,                   // func_pspeu_0924B178
    E_GRAVE_KEEPER,             // EntityGraveKeeper
    E_GRAVE_KEEPER_HITBOX,      // EntityGraveKeeperHitbox
    E_MIST_DOOR,                // EntityMistDoor
    E_UNK_4E,                   // 0x00000000
    NUM_ENTITIES,
};

#endif // ARE_H