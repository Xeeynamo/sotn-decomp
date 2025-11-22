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
void func_us_801B628C(Entity* self);
void func_us_801B6420(Entity* self);
void EntityBridgeBackgroundPiece(Entity* self);
void func_us_801B6DF0(Entity* self);
void func_us_801B7184(Entity* self);
void EntityHeartRoomSwitch(Entity* self);
void func_us_801B7998(Entity* self);
void func_us_801B7C7C(Entity* self);
void func_us_801B7E7C(Entity* self);
void func_us_801B80C0(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void func_us_801C3844(Entity* self);
void func_us_801C41EC(Entity* self);
void func_us_801C4300(Entity* self);
void func_us_801C45B0(Entity* self);
void func_us_801C47E4(Entity* self);
void func_us_801C4EDC(Entity* self);
void EntityBoneHalberdParts(Entity* self);
void EntityBoneMusket(Entity* self);
void func_us_801C5744(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C886C(Entity* self);
void func_us_801C89C4(Entity* self);
void EntityAxeKnightBlue(Entity* self);
void EntityAxeKnightThrowingAxe(Entity* self);
void func_us_801CA2AC(Entity* self);
void InitializeUnkEntity(Entity* self);
void EntityArmorLord(Entity* self);
void func_us_801CC660(Entity* self);
void EntityArmorLordFireWave(Entity* self);
void func_us_801CC8D4(Entity* self);
void EntityHuntingGirl(Entity* self);
void EntityHuntingGirlAttack(Entity* self);
void func_us_801CDCF4(Entity* self);
void func_us_801CEBC8(Entity* self);
void func_us_801CECAC(Entity* self);
void func_us_801CEB00(Entity* self);
void EntityFleaArmor(Entity* self);
void EntityFleaArmorAttackHitbox(Entity* self);
void EntityFleaMan(Entity* self);
void EntityBoneScimitar(Entity* self);
void EntityBoneScimitarParts(Entity* self);
void EntityPlateLord(Entity* self);
void func_us_801D2238(Entity* self);
void func_us_801D23B4(Entity* self);
void func_us_801D29B8(Entity* self);
void func_us_801D3340(Entity* self);
void func_us_801D2BC0(Entity* self);
void EntityGraveKeeper(Entity* self);
void EntityGraveKeeperHitbox(Entity* self);
void EntityMistDoor(Entity* self);

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
    func_us_801B628C,
    func_us_801B6420,
    EntityBridgeBackgroundPiece,
    func_us_801B6DF0,
    func_us_801B7184,
    EntityHeartRoomSwitch,
    func_us_801B7998,
    func_us_801B7C7C,
    func_us_801B7E7C,
    func_us_801B80C0,
    EntityExplosionPuffOpaque,
    OVL_EXPORT(EntityBreakableDebris),
    func_us_801C3844,
    func_us_801C41EC,
    func_us_801C4300,
    func_us_801C45B0,
    func_us_801C47E4,
    func_us_801C4EDC,
    EntityBoneHalberdParts,
    EntityBoneMusket,
    func_us_801C5744,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityValhallaKnight,
    func_us_801C886C,
    func_us_801C89C4,
    EntityAxeKnightBlue,
    EntityAxeKnightThrowingAxe,
    func_us_801CA2AC,
    InitializeUnkEntity,
    EntityArmorLord,
    func_us_801CC660,
    EntityArmorLordFireWave,
    func_us_801CC8D4,
    EntityHuntingGirl,
    EntityHuntingGirlAttack,
    func_us_801CDCF4,
    func_us_801CEBC8,
    func_us_801CECAC,
    func_us_801CEB00,
    EntityFleaArmor,
    EntityFleaArmorAttackHitbox,
    EntityFleaMan,
    EntityBoneScimitar,
    EntityBoneScimitarParts,
    EntityPlateLord,
    func_us_801D2238,
    func_us_801D23B4,
    func_us_801D29B8,
    func_us_801D3340,
    func_us_801D2BC0,
    EntityGraveKeeper,
    EntityGraveKeeperHitbox,
    EntityMistDoor,
};
