// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
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
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
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
void EntityRichterFightTrigger(Entity*);
void EntityCutscene(Entity*);
void func_us_801AD11C(Entity*);
void func_us_801AD320(Entity*);
void func_us_801AD400(Entity*);
void EntityBreakableDebris(Entity*);
void EntityAxeKnightBlue(Entity*);
void EntityAxeKnightThrowingAxe(Entity*);
void func_us_801CBA30(Entity*);
void InitializeUnkEntity(Entity*);

#ifdef VERSION_PSP
void func_pspeu_09249898(Entity*);
void func_pspeu_092496C8(Entity*);
void func_pspeu_092497B0(Entity*);
#endif

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
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
    EntityBackgroundBlock,
    EntityLockCamera,
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
    EntityRichterFightTrigger,
    EntityCutscene,
    func_us_801AD11C,
    func_us_801AD320,
    func_us_801AD400,
    EntityBreakableDebris,
    EntityAxeKnightBlue,
    EntityAxeKnightThrowingAxe,
    func_us_801CBA30,
    InitializeUnkEntity,
#ifdef VERSION_PSP
    func_pspeu_09249898,
    func_pspeu_092496C8,
    func_pspeu_092497B0
#endif
};

EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0x0, 0};

#include "../e_init_common.h"

EInit g_EInitTOPCommon = {ANIMSET_OVL(1), 0, 0, 0, 5};
EInit g_EInitFleaRider = {ANIMSET_OVL(3), 0, 0x4B, 0x206, 0x30};
EInit g_EInitAxeKnight = {ANIMSET_OVL(7), 1, 0x50, 0x0240, 6};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(7), 0x2F, 0x50, 0x240, 7};
