// SPDX-License-Identifier: AGPL-3.0-or-later(Entity* self);
#include "rnz0.h"

void D_us_8018324C(Entity* self);
void EntityBreakableNZ0(Entity* self);
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
void EntityPurpleBrickScrollingBackground(Entity* self);
void EntityLeftSecretRoomWall(Entity* self);
void EntityBottomSecretRoomFloor(Entity* self);
void EntitySecretWallDebris(Entity* self);
void func_us_801B7C8C(Entity* self);
void func_us_801B8238(Entity* self);
void func_us_801B9430(Entity* self);
void func_us_801B965C(Entity* self);
void func_us_801B9D78(Entity* self);
void func_us_801BB5D8(Entity* self);
void func_us_801BB000(Entity* self);
void func_us_801BA21C(Entity* self);
void func_us_801B9E64(Entity* self);
void func_us_801BE600(Entity* self);
void func_us_801BCAB0(Entity* self);
void func_us_801BD7D0(Entity* self);
void func_us_801BF7B0(Entity* self);
void EntityTableWithGlobe(Entity* self);
void EntityLifeMaxTank(Entity* self);
void EntityBlueFlameTable(Entity* self);
void EntityRelicContainer(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityRedEyeBust(Entity* self);
void EntityCannonLever(Entity* self);
void func_us_801AC758(Entity* self);
void EntityCannonShot(Entity* self);
void func_us_801ACAD0(Entity* self);
void func_us_801C060C(Entity* self);
void func_us_801C09E8(Entity* self);
void func_us_801C1668(Entity* self);
void func_us_801C1758(Entity* self);
void func_us_801C1CC0(Entity* self);
void func_us_801C1E14(Entity* self);
void EntitySalemWitch(Entity* self);
void EntitySalemWitchGlow(Entity* self);
void EntitySalemWitchCurse(Entity* self);
void EntitySalemWitchTriboltLaunch(Entity* self);
void EntitySalemWitchTriboltProjectile(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    D_us_8018324C,
    EntityBreakableNZ0,
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
    EntityPurpleBrickScrollingBackground,
    EntityLeftSecretRoomWall,
    EntityBottomSecretRoomFloor,
    EntitySecretWallDebris,
    func_us_801B7C8C,
    func_us_801B8238,
    func_us_801B9430,
    func_us_801B965C,
    func_us_801B9D78,
    func_us_801BB5D8,
    func_us_801BB000,
    func_us_801BA21C,
    func_us_801B9E64,
    func_us_801BE600,
    func_us_801BCAB0,
    func_us_801BD7D0,
    func_us_801BF7B0,
    EntityTableWithGlobe,
    EntityLifeMaxTank,
    EntityBlueFlameTable,
    EntityRelicContainer,
    EntitySealedDoor,
    EntityRedEyeBust,
    EntityCannonLever,
    func_us_801AC758,
    EntityCannonShot,
    func_us_801ACAD0,
    func_us_801C060C,
    func_us_801C09E8,
    func_us_801C1668,
    func_us_801C1758,
    func_us_801C1CC0,
    func_us_801C1E14,
    EntitySalemWitch,
    EntitySalemWitchGlow,
    EntitySalemWitchCurse,
    EntitySalemWitchTriboltLaunch,
    EntitySalemWitchTriboltProjectile
};