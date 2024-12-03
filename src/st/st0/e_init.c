// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

void func_801A805C(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void ST0_EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityDummy(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void func_801A7D64(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void ST0_EntityCutscene(Entity*);
void EntityCutscene(Entity*);
void EntityStageTitleCard(Entity*);
void EntityStageTitleFadeout(Entity*);
void EntityDracula(Entity*);
void EntityDraculaFireball(Entity*);
void EntityDraculaMeteorball(Entity*);
void EntityDraculaBody(Entity*);
void func_801AD838(Entity*);
void EntityDraculaGlass(Entity*);
void EntityDraculaFinalForm(Entity*);
void EntityDraculaMegaFireball(Entity*);
void EntityDraculaRainAttack(Entity*);
void func_801BD8F0(Entity*);
void EntityBackgroundVortex(Entity*);
void EntityClouds(Entity*);
void func_801A8328(Entity*);
void EntitySecretStairsCeiling(Entity*);
void EntitySecretButton(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void func_801AF774(Entity*);
void EntityCutscenePhotograph(Entity*);
void EntityCutscenePhotographFire(Entity*);
void func_801BC5C0(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    func_801A805C,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    ST0_EntityRedDoor,
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityDummy,
    EntityEquipItemDrop,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    func_801A7D64,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    ST0_EntityCutscene,
    EntityCutscene,
    EntityStageTitleCard,
    EntityStageTitleFadeout,
    EntityDracula,
    EntityDraculaFireball,
    EntityDraculaMeteorball,
    EntityDraculaBody,
    func_801AD838,
    EntityDraculaGlass,
    EntityDraculaFinalForm,
    EntityDraculaMegaFireball,
    EntityDraculaRainAttack,
    func_801BD8F0,
    EntityBackgroundVortex,
    EntityClouds,
    func_801A8328,
    EntitySecretStairsCeiling,
    EntitySecretButton,
    EntitySecretStairs,
    EntityClockTower3D,
    func_801AF774,
    EntityCutscenePhotograph,
    EntityCutscenePhotographFire,
    func_801BC5C0
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0x7C, 0x0100, 0};


