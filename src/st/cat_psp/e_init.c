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
void func_pspeu_0925BE88(Entity* self);
void func_pspeu_0925B118(Entity* self);
void func_pspeu_0925B7B8(Entity* self);
void func_pspeu_0925CA38(Entity* self);
void func_pspeu_09253988(Entity* self);
void func_pspeu_09260D58(Entity* self);
void func_us_801C3D44(Entity* self);
void func_us_801C3850(Entity* self);
void func_us_801C379C(Entity* self);
void func_pspeu_09261BB8(Entity* self);
void func_us_801C3ED8(Entity* self);
void func_pspeu_09261748(Entity* self);
void func_pspeu_0925F410(Entity* self);
void func_pspeu_0925EA40(Entity* self);
void func_pspeu_0925D418(Entity* self);
void func_pspeu_0925DC38(Entity* self);
void func_pspeu_0925D8C8(Entity* self);
void func_pspeu_0925D168(Entity* self);
void func_pspeu_0925CC60(Entity* self);
void func_pspeu_09260768(Entity* self);
void func_pspeu_092604A0(Entity* self);
void func_pspeu_09262B58(Entity* self);
void func_pspeu_0925F7B0(Entity* self);
void EntityBigRedFireball(Entity* self);
void func_pspeu_092395A8(Entity* self);
void func_pspeu_0923A8B8(Entity* self);
void func_pspeu_0923BA88(Entity* self);
void func_pspeu_0923BBC8(Entity* self);
void func_pspeu_09255558(Entity* self);
void func_pspeu_092566B8(Entity* self);
void func_pspeu_09257850(Entity* self);
void func_pspeu_09257148(Entity* self);
void func_pspeu_09257FD0(Entity* self);
void func_pspeu_09243078(Entity* self);
void func_pspeu_09243F28(Entity* self);
void func_pspeu_09242AC8(Entity* self);
void func_pspeu_092427C8(Entity* self);
void func_pspeu_09241E58(Entity* self);
void func_pspeu_09240480(Entity* self);
void func_pspeu_09241A88(Entity* self);
void func_pspeu_09250068(Entity* self);
void func_pspeu_09250C88(Entity* self);
void func_pspeu_092513C8(Entity* self);
void func_pspeu_09251718(Entity* self);
void func_pspeu_09251C28(Entity* self);
void func_pspeu_09260290(Entity* self);
void func_pspeu_0923DA30(Entity* self);
void func_pspeu_0923EA58(Entity* self);
void func_pspeu_0923EBC0(Entity* self);
void EntityGremlin(Entity* self);
void EntityGremlinEffect(Entity* self);
void EntityGremlinFire(Entity* self);
void func_pspeu_0924CF78(Entity* self);
void func_pspeu_0924E938(Entity* self);
void func_pspeu_0924EE40(Entity* self);
void func_pspeu_0924F8C8(Entity* self);
void EntityWereskeleton(Entity* self);
void func_us_801CE958(Entity* self);
void func_us_801CEA2C(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void func_pspeu_0924CA30(Entity* self);

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
    func_pspeu_0925BE88,
    func_pspeu_0925B118,
    func_pspeu_0925B7B8,
    func_pspeu_0925CA38,
    func_pspeu_09253988,
    func_pspeu_09260D58,
    func_us_801C3D44,
    func_us_801C3850,
    func_us_801C379C,
    func_pspeu_09261BB8,
    func_us_801C3ED8,
    func_pspeu_09261748,
    func_pspeu_0925F410,
    func_pspeu_0925EA40,
    func_pspeu_0925D418,
    func_pspeu_0925DC38,
    func_pspeu_0925D8C8,
    func_pspeu_0925D168,
    func_pspeu_0925CC60,
    func_pspeu_09260768,
    func_pspeu_092604A0,
    func_pspeu_09262B58,
    func_pspeu_0925F7B0,
    EntityBigRedFireball,
    func_pspeu_092395A8,
    func_pspeu_0923A8B8,
    func_pspeu_0923BA88,
    func_pspeu_0923BBC8,
    func_pspeu_09255558,
    func_pspeu_092566B8,
    func_pspeu_09257850,
    func_pspeu_09257148,
    func_pspeu_09257FD0,
    func_pspeu_09243078,
    func_pspeu_09243F28,
    func_pspeu_09242AC8,
    func_pspeu_092427C8,
    func_pspeu_09241E58,
    func_pspeu_09240480,
    func_pspeu_09241A88,
    func_pspeu_09250068,
    func_pspeu_09250C88,
    func_pspeu_092513C8,
    func_pspeu_09251718,
    func_pspeu_09251C28,
    func_pspeu_09260290,
    func_pspeu_0923DA30,
    func_pspeu_0923EA58,
    func_pspeu_0923EBC0,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    func_pspeu_0924CF78,
    func_pspeu_0924E938,
    func_pspeu_0924EE40,
    func_pspeu_0924F8C8,
    EntityWereskeleton,
    func_us_801CE958,
    func_us_801CEA2C,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    func_pspeu_0924CA30,
};
