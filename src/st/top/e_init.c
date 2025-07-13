// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void TOP_EntityRedDoor(Entity*);
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
void TOP_EntityBackgroundBlock(Entity*);
void TOP_EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801A9CB8(Entity*);
void func_us_801A99EC(Entity*);
void func_us_801A9F0C(Entity*);
void EntityClockTower3D(Entity*);
void func_us_801BABF8(Entity*);
void func_us_801AA354(Entity*);
void func_us_801AA624(Entity*);
void func_us_801AB308(Entity*);
void func_us_801AB45C(Entity*);
void func_us_801AB67C(Entity*);
void func_us_801AABA4(Entity*);
void EntityFleaRider(Entity*);
void func_us_801A9250(Entity*);
void TOP_EntityCutscene(Entity*);
void func_us_801AD11C(Entity*);
void func_us_801AD320(Entity*);
void func_us_801AD400(Entity*);
void func_801A8328(Entity*);
void EntityAxeKnightBlue(Entity*);
void EntityAxeKnightThrowingAxe(Entity*);
void func_us_801CBA30(Entity*);
void InitializeUnkEntity(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    TOP_EntityRedDoor,
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
    TOP_EntityBackgroundBlock,
    TOP_EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801A9CB8,
    func_us_801A99EC,
    func_us_801A9F0C,
    EntityClockTower3D,
    func_us_801BABF8,
    func_us_801AA354,
    func_us_801AA624,
    func_us_801AB308,
    func_us_801AB45C,
    func_us_801AB67C,
    func_us_801AABA4,
    EntityFleaRider,
    func_us_801A9250,
    TOP_EntityCutscene,
    func_us_801AD11C,
    func_us_801AD320,
    func_us_801AD400,
    func_801A8328,
    EntityAxeKnightBlue,
    EntityAxeKnightThrowingAxe,
    func_us_801CBA30,
    InitializeUnkEntity,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0x0, 0};

#include "../e_init_common.h"

EInit D_us_80180A00 = {ANIMSET_OVL(1), 0, 0, 0, 5};
EInit g_EInitFleaRider = {ANIMSET_OVL(3), 0, 0x4B, 0x206, 0x30};
EInit g_EInitAxeKnight = {ANIMSET_OVL(7), 1, 0x50, 0x0240, 6};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(7), 0x2F, 0x50, 0x240, 7};
