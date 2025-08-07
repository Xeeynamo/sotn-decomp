// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

void EntityUnkBreakable(Entity* self);
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
void func_us_801C4C7C(Entity* self);
void func_us_801C589C(Entity* self);
void func_us_801C5DF4(Entity* self);
void func_us_801C56A0(Entity* self);
void func_us_801CA13C(Entity* self);
void func_us_801B732C(Entity* self);
void func_us_801B852C(Entity* self);
void func_us_801B7FE0(Entity* self);
void func_us_801B7F2C(Entity* self);
void func_us_801B7B64(Entity* self);
void func_us_801B86B0(Entity* self);
void func_us_801B8AD0(Entity* self);
void func_us_801B87E8(Entity* self);
void func_us_801BACF4(Entity* self);
void func_us_801B972C(Entity* self);
void func_us_801B9D1C(Entity* self);
void func_us_801B9A74(Entity* self);
void func_us_801B951C(Entity* self);
void func_us_801B907C(Entity* self);
void func_us_801BA388(Entity* self);
void func_us_801BA164(Entity* self);
void func_us_801B8D2C(Entity* self);
void func_us_801BA7FC(Entity* self);
void EntityBigRedFireball(Entity* self);
void func_us_801CA2A4(Entity* self);
void func_us_801CAF68(Entity* self);
void func_us_801CBB24(Entity* self);
void func_us_801CBC10(Entity* self);
void func_us_801CC2E4(Entity* self);
void func_us_801CCEF0(Entity* self);
void func_us_801CDB50(Entity* self);
void func_us_801CD614(Entity* self);
void func_us_801CE170(Entity* self);
void func_us_801C839C(Entity* self);
void func_us_801C8CE0(Entity* self);
void func_us_801C7F84(Entity* self);
void func_us_801C7D98(Entity* self);
void func_us_801C774C(Entity* self);
void func_us_801C6360(Entity* self);
void func_us_801C7420(Entity* self);
void func_us_801CFAE8(Entity* self);
void func_us_801D033C(Entity* self);
void func_us_801D08A8(Entity* self);
void func_us_801D0B38(Entity* self);
void func_us_801D0F10(Entity* self);
void func_us_801BB4CC(Entity* self);
void func_us_801D1474(Entity* self);
void func_us_801D1F68(Entity* self);
void func_us_801D2060(Entity* self);
void EntityGremlin(Entity* self);
void EntityGremlinEffect(Entity* self);
void EntityGremlinFire(Entity* self);
void func_us_801D2B3C(Entity* self);
void func_us_801D3D08(Entity* self);
void func_us_801D4088(Entity* self);
void func_us_801D4744(Entity* self);
void EntityWereskeleton(Entity* self);
void func_us_801CE958(Entity* self);
void func_us_801CEA2C(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityBloodSkeleton(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityUnkBreakable,
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
    func_us_801C4C7C,
    func_us_801C589C,
    func_us_801C5DF4,
    func_us_801C56A0,
    func_us_801CA13C,
    func_us_801B732C,
    func_us_801B852C,
    func_us_801B7FE0,
    func_us_801B7F2C,
    func_us_801B7B64,
    func_us_801B86B0,
    func_us_801B8AD0,
    func_us_801B87E8,
    func_us_801BACF4,
    func_us_801B972C,
    func_us_801B9D1C,
    func_us_801B9A74,
    func_us_801B951C,
    func_us_801B907C,
    func_us_801BA388,
    func_us_801BA164,
    func_us_801B8D2C,
    func_us_801BA7FC,
    EntityBigRedFireball,
    func_us_801CA2A4,
    func_us_801CAF68,
    func_us_801CBB24,
    func_us_801CBC10,
    func_us_801CC2E4,
    func_us_801CCEF0,
    func_us_801CDB50,
    func_us_801CD614,
    func_us_801CE170,
    func_us_801C839C,
    func_us_801C8CE0,
    func_us_801C7F84,
    func_us_801C7D98,
    func_us_801C774C,
    func_us_801C6360,
    func_us_801C7420,
    func_us_801CFAE8,
    func_us_801D033C,
    func_us_801D08A8,
    func_us_801D0B38,
    func_us_801D0F10,
    func_us_801BB4CC,
    func_us_801D1474,
    func_us_801D1F68,
    func_us_801D2060,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    func_us_801D2B3C,
    func_us_801D3D08,
    func_us_801D4088,
    func_us_801D4744,
    EntityWereskeleton,
    func_us_801CE958,
    func_us_801CEA2C,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityBloodSkeleton,
};
