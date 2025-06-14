// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

void EntityBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityClockRoomController(Entity* self);
void EntityClockHands(Entity* self);
void EntityBirdcageDoor(Entity* self);
void EntityStatue(Entity* self);
void EntityStatueGear(Entity* self);
void EntityStoneDoor(Entity* self);
void EntityClockRoomUnused(Entity* self);
void EntityDummy(Entity* self);
void OVL_EXPORT(EntityCutscene)(Entity* self);
void func_us_8018C90C(Entity* self);
void func_us_8018CA94(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
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
    EntityClockRoomController,
    EntityClockHands,
    EntityBirdcageDoor,
    EntityStatue,
    EntityStatueGear,
    EntityStoneDoor,
    EntityClockRoomUnused,
    EntityDummy,
    OVL_EXPORT(EntityCutscene),
    func_us_8018C90C,
    func_us_8018CA94,
};

EInit OVL_EXPORT(EInitBreakable) = {0x0003, 0x0000, 0x0000, 0x0000, 0x0000};
u16 g_EInitObtainable[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitParticle[] = {0x0003, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitSpawner[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0004};
u16 g_EInitInteractable[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0005};
u16 g_EInitUnkId13[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0002};
u16 g_EInitLockCamera[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
u16 g_EInitCommon[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
u16 g_EInitDamageNum[] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};

static u16 unused[][6] = {
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0133, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0134, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0135, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0136, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0137, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0138, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0139, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013A, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013B, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013C, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013D, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013E, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x013F, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0140, 0x0000},
    {0x0000, 0x0000, 0x0000, 0x0000, 0x0141, 0x0000},
};
