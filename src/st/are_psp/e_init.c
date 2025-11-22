// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
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
void func_pspeu_09237A60(Entity* self);
void func_pspeu_09239C40(Entity* self);
void func_pspeu_0923AA20(Entity* self);
void func_pspeu_0923AE60(Entity* self);
void func_pspeu_09238AA0(Entity* self);
void EntityHeartRoomSwitch(Entity* self);
void func_pspeu_09239558(Entity* self);
void func_pspeu_09238820(Entity* self);
void func_pspeu_0923B2C0(Entity* self);
void func_pspeu_092385C8(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void func_pspeu_0925E2B0(Entity* self);
void func_pspeu_0925F050(Entity* self);
void func_pspeu_0925F1C8(Entity* self);
void func_pspeu_0925F568(Entity* self);
void func_pspeu_09260700(Entity* self);
void func_pspeu_09261060(Entity* self);
void EntityBoneHalberdParts(Entity* self);
void func_pspeu_0925F620(Entity* self);
void func_pspeu_092600D8(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void func_pspeu_0923D440(Entity* self);
void func_pspeu_0923E5B0(Entity* self);
void func_pspeu_0923E7B8(Entity* self);
void func_pspeu_09253D80(Entity* self);
void func_pspeu_092461A8(Entity* self);
void func_pspeu_09246BF8(Entity* self);
void func_pspeu_092449E8(Entity* self);
void func_pspeu_09246F88(Entity* self);
void EntityHuntingGirl(Entity* self);
void EntityHuntingGirlAttack(Entity* self);
void func_pspeu_0923E970(Entity* self);
void func_pspeu_0923FEF0(Entity* self);
void func_pspeu_09240078(Entity* self);
void func_pspeu_0923FDF8(Entity* self);
void EntityFleaArmor(Entity* self);
void EntityFleaArmorAttackHitbox(Entity* self);
void EntityFleaMan(Entity* self);
void EntityBoneScimitar(Entity* self);
void EntityBoneScimitarParts(Entity* self);
void func_pspeu_092479D0(Entity* self);
void func_pspeu_0924A2C0(Entity* self);
void func_pspeu_0924A4D0(Entity* self);
void func_pspeu_0924ADC0(Entity* self);
void func_pspeu_0924BD30(Entity* self);
void func_pspeu_0924B178(Entity* self);
void EntityGraveKeeper(Entity* self);
void EntityGraveKeeperHitbox(Entity* self);
void EntityMistDoor(Entity* self);
void 0x00000000(Entity* self);

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
    func_pspeu_09237A60,
    func_pspeu_09239C40,
    func_pspeu_0923AA20,
    func_pspeu_0923AE60,
    func_pspeu_09238AA0,
    EntityHeartRoomSwitch,
    func_pspeu_09239558,
    func_pspeu_09238820,
    func_pspeu_0923B2C0,
    func_pspeu_092385C8,
    EntityExplosionPuffOpaque,
    OVL_EXPORT(EntityBreakableDebris),
    func_pspeu_0925E2B0,
    func_pspeu_0925F050,
    func_pspeu_0925F1C8,
    func_pspeu_0925F568,
    func_pspeu_09260700,
    func_pspeu_09261060,
    EntityBoneHalberdParts,
    func_pspeu_0925F620,
    func_pspeu_092600D8,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityValhallaKnight,
    func_us_801C8954,
    func_us_801C8AAC,
    func_pspeu_0923D440,
    func_pspeu_0923E5B0,
    func_pspeu_0923E7B8,
    func_pspeu_09253D80,
    func_pspeu_092461A8,
    func_pspeu_09246BF8,
    func_pspeu_092449E8,
    func_pspeu_09246F88,
    EntityHuntingGirl,
    EntityHuntingGirlAttack,
    func_pspeu_0923E970,
    func_pspeu_0923FEF0,
    func_pspeu_09240078,
    func_pspeu_0923FDF8,
    EntityFleaArmor,
    EntityFleaArmorAttackHitbox,
    EntityFleaMan,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    func_pspeu_092479D0,
    func_pspeu_0924A2C0,
    func_pspeu_0924A4D0,
    func_pspeu_0924ADC0,
    func_pspeu_0924BD30,
    func_pspeu_0924B178,
    EntityGraveKeeper,
    EntityGraveKeeperHitbox,
    EntityMistDoor,
    0x00000000,
};
