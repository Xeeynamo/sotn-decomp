// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

void OVL_EXPORT(EntityBreakable)(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801A9CB8(Entity*);
void EntityStairSwitch(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void EntityClouds(Entity*);
void EntityBreakableWall(Entity*);
void EntityTriangleElevator(Entity*);
void EntityLionLamp(Entity*);
void func_us_801AB45C(Entity*);
void EntityTriggerBeforeCastleWarp(Entity*);
void func_us_801AABA4(Entity*);
void EntityFleaRider(Entity*);
void func_us_801A9250(Entity*);
void OVL_EXPORT(EntityCutscene)(Entity*);
void func_us_801AD11C(Entity*);
void func_us_801AD320(Entity*);
void func_us_801AD400(Entity*);
void OVL_EXPORT(EntityBreakableDebris)(Entity*);
void EntityAxeKnightBlue(Entity*);
void EntityAxeKnightThrowingAxe(Entity*);
void func_us_801CBA30(Entity*);
void InitializeUnkEntity(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801A9CB8,
    EntityStairSwitch,
    EntitySecretStairs,
    EntityClockTower3D,
    EntityClouds,
    EntityBreakableWall,
    EntityTriangleElevator,
    EntityLionLamp,
    func_us_801AB45C,
    EntityTriggerBeforeCastleWarp,
    func_us_801AABA4,
    EntityFleaRider,
    func_us_801A9250,
    OVL_EXPORT(EntityCutscene),
    func_us_801AD11C,
    func_us_801AD320,
    func_us_801AD400,
    OVL_EXPORT(EntityBreakableDebris),
    EntityAxeKnightBlue,
    EntityAxeKnightThrowingAxe,
    func_us_801CBA30,
    InitializeUnkEntity,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0x0, 0};

#include "../e_init_common.h"

EInit g_EInitTOPCommon = {ANIMSET_OVL(1), 0, 0, 0, 5};
EInit g_EInitFleaRider = {ANIMSET_OVL(3), 0, 0x4B, 0x206, 0x30};
EInit g_EInitAxeKnight = {ANIMSET_OVL(7), 1, 0x50, 0x0240, 6};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(7), 0x2F, 0x50, 0x240, 7};
