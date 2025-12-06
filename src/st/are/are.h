// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef ARE_H
#define ARE_H

#include <stage.h>

#define OVL_EXPORT(x) ARE_##x
#define STAGE_IS_ARE

enum Palettes {
    PAL_NONE,
    PAL_ARMOR_LORD_UNK = 0x21A,
    PAL_HUNTING_GIRL = 0x21C,
    PAL_PLATE_LORD_UNK1 = 0x226,
    PAL_PLATE_LORD_UNK2 = 0x227,
    PAL_PLATE_LORD_UNK3 = 0x228,
};

enum Entities {
    E_NONE,
    E_BREAKABLE,                    // OVL_EXPORT(EntityBreakable)
    E_EXPLOSION,                    // EntityExplosion
    E_PRIZE_DROP,                   // EntityPrizeDrop
    E_DAMAGE_DISPLAY,               // EntityDamageDisplay
    E_RED_DOOR,                     // OVL_EXPORT(EntityRedDoor)
    E_INTENSE_EXPLOSION,            // EntityIntenseExplosion
    E_SOUL_STEAL_ORB,               // EntitySoulStealOrb
    E_ROOM_FOREGROUND,              // EntityRoomForeground
    E_STAGE_NAME_POPUP,             // EntityStageNamePopup
    E_EQUIP_ITEM_DROP,              // EntityEquipItemDrop
    E_RELIC_ORB,                    // EntityRelicOrb
    E_HEART_DROP,                   // EntityHeartDrop
    E_ENEMY_BLOOD,                  // EntityEnemyBlood
    E_MESSAGE_BOX,                  // EntityMessageBox
    E_DUMMY_F,                      // EntityDummy
    E_DUMMY_10,                     // EntityDummy
    E_BACKGROUND_BLOCK,             // OVL_EXPORT(EntityBackgroundBlock)
    E_LOCK_CAMERA,                  // OVL_EXPORT(EntityLockCamera)
    E_UNK_ID13,                     // EntityUnkId13
    E_EXPLOSION_VARIANTS,           // EntityExplosionVariants
    E_GREY_PUFF,                    // EntityGreyPuff
    E_UNK_16,                       // func_us_801B628C
    E_UNK_17,                       // func_us_801B6420
    E_BRIDGE_BACKGROUND_PIECE,      // EntityBridgeBackgroundPiece
    E_UNK_19,                       // func_us_801B6DF0
    E_UNK_1A,                       // func_us_801B7184
    E_HEART_ROOM_SWITCH,            // EntityHeartRoomSwitch
    E_UNK_1C,                       // func_us_801B7998
    E_UNK_1D,                       // func_us_801B7C7C
    E_UNK_1E,                       // func_us_801B7E7C
    E_UNK_1F,                       // func_us_801B80C0
    E_EXPLOSION_PUFF_OPAQUE,        // EntityExplosionPuffOpaque
    E_BREAKABLE_DEBRIS,             // OVL_EXPORT(EntityBreakableDebris)
    E_BLADE_MASTER,                 // EntityBladeMaster
    E_BLADE_MASTER_ATTACK_HITBOX,   // EntityBladeMasterAttackHitbox
    E_BLADE_MASTER_DEATH_PARTS,     // EntityBladeMasterDeathParts
    E_BLADE_MASTER_DEATH_EXPLOSION, // EntityBladeMasterDeathExplosion
    E_BLADE_SOLDIER,                // EntityBladeSoldier
    E_BLADE_SOLDIER_ATTACK_HITBOX,  // EntityBladeSoldierAttackHitbox
    E_BLADE_SOLDIER_DEATH_PARTS,    // EntityBladeSoldierDeathParts
    E_BONE_MUSKET,                  // EntityBoneMusket
    E_BONE_MUSKET_UNK,              // func_us_801CF298
    E_OWL_KNIGHT,                   // EntityOwlKnight
    E_OWL,                          // EntityOwl
    E_OWL_KNIGHT_SWORD,             // EntityOwlKnightSword
    E_OWL_TARGET,                   // EntityOwlTarget
    E_VALHALLA_KNIGHT,              // EntityValhallaKnight
    E_VALHALLA_KNIGHT_UNK1,         // func_us_801C8954
    E_VALHALLA_KNIGHT_UNK2,         // func_us_801C8AAC
    E_AXE_KNIGHT_BLUE,              // EntityAxeKnightBlue
    E_AXE_KNIGHT_AXE,               // EntityAxeKnightThrowingAxe
    E_AXE_KNIGHT_AXE_2,             // func_us_801CBA30
    E_UNK_ENTITY,                   // InitializeUnkEntity
    E_ARMOR_LORD,                   // EntityArmorLord
    E_ARMOR_LORD_UNK1,              // func_us_801D348C
    E_ARMOR_LORD_FIRE_WAVE,         // EntityArmorLordFireWave
    E_ARMOR_LORD_UNK2,              // func_us_801D3700
    E_HUNTING_GIRL,                 // EntityHuntingGirl
    E_HUNTING_GIRL_ATTACK,          // EntityHuntingGirlAttack
    E_PARANTHROPUS,                 // EntityParanthropus
    E_PARANTHROPUS_BONE_HITBOX,     // EntityParanthropusBoneHitbox
    E_PARANTHROPUS_SKULL,           // EntityParanthropusSkull
    E_PARANTHROPUS_THROWN_BONE,     // EntityParanthropusThrownBone
    E_FLEA_ARMOR,                   // EntityFleaArmor
    E_FLEA_ARMOR_ATTACK_HITBOX,     // EntityFleaArmorAttackHitbox
    E_FLEA_MAN,                     // EntityFleaMan
    E_BONE_SCIMITAR,                // EntityBoneScimitar
    E_BONE_SCIMITAR_PARTS,          // EntityBoneScimitarParts
    E_PLATE_LORD,                   // EntityPlateLord
    E_PLATE_LORD_UNK1,              // func_us_801D2238
    E_PLATE_LORD_UNK2,              // func_us_801D23B4
    E_PLATE_LORD_UNK3,              // func_us_801D29B8
    E_PLATE_LORD_UNK4,              // func_us_801D3340
    E_PLATE_LORD_UNK5,              // func_us_801D2BC0
    E_GRAVE_KEEPER,                 // EntityGraveKeeper
    E_GRAVE_KEEPER_HITBOX,          // EntityGraveKeeperHitbox
    E_MIST_DOOR,                    // EntityMistDoor
    NUM_ENTITIES,
};

#endif // ARE_H
