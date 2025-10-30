// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_entity.c
 * Overlay: CHI
 * Description: DATA - Entities
 */

#include "chi.h"

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
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityDemonSwitchWall(Entity*);
void EntityDemonSwitch(Entity*);
void EntityBreakableWall(Entity*);
void EntityBreakableWallDebris(Entity*);
void OVL_EXPORT(EntityBreakableDebris)(Entity*);
void EntityFallingStairs(Entity*);
void EntityCerberusGateDebug(Entity*);
void EntityFallingStep(Entity*);
void EntityGremlin(Entity*);
void EntityGremlinEffect(Entity*);
void EntityGremlinFire(Entity*);
void EntitySalemWitch(Entity*);
void EntitySalemWitchGlow(Entity*);
void EntitySalemWitchCurse(Entity*);
void EntitySalemWitchTriboltLaunch(Entity*);
void EntitySalemWitchTriboltProjectile(Entity*);
void EntityThornweed(Entity*);
void EntityCorpseweed(Entity*);
void EntityCorpseweedProjectile(Entity*);
void EntityVenusWeed(Entity*);
void EntityVenusWeedFlower(Entity*);
void EntityVenusWeedTendril(Entity*);
void EntityVenusWeedDart(Entity*);
void EntityVenusWeedSpike(Entity*);

// D_8018055C
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
    OVL_EXPORT(EntityLockCamera), // EntityCameraLock
    EntityUnkId13,                // EntityParticleTrail
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    OVL_EXPORT(EntityBreakableDebris),
    EntityCerberusGateDebug,
    EntityFallingStairs,
    EntityFallingStep,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    EntitySalemWitch,
    EntitySalemWitchGlow,
    EntitySalemWitchCurse,
    EntitySalemWitchTriboltLaunch,
    EntitySalemWitchTriboltProjectile,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityVenusWeed,
    EntityVenusWeedFlower,
    EntityVenusWeedTendril,
    EntityVenusWeedDart,
    EntityVenusWeedSpike,
};

// D_80180610
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};

#include "../e_init_common.h"

EInit g_EInitSecret = {ANIMSET_OVL(1), 0, 0, PAL_UNK_000, 5};

// D_80180688
EInit g_EInitSalemWitch = {ANIMSET_OVL(3), 1, 72, PAL_DRA(516), 221};

// D_80180694
EInit g_EInitSalemWitchCurse = {ANIMSET_OVL(3), 0, 72, PAL_DRA(516), 222};

// D_801806A0
EInit g_EInitSalemWitchTribolt = {ANIMSET_OVL(4), 0, 92, PAL_DRA(747), 223};

// D_801806AC
EInit g_EInitGremlin = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 225};

// Unused
// D_801806B8
EInit g_EInit801806B8 = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 5};

// D_801806C4
EInit g_EInitGremlinFire = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 226};

// D_801806D0
EInit g_EInitThornweed = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 157};

// Unused (Alternate Corpseweed)
// D_801806DC
EInit g_EInit801806DC = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 158};

// D_801806E8
EInit g_EInitCorpseweed = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 159};

// D_801806F4
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 160};

// D_80180700
EInit g_EInitVenusWeedRoot = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 161};

// D_8018070C
EInit g_EInitVenusWeedFlower = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 162};

// D_80180718
EInit g_EInitVenusWeedTendril = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 163};

// D_80180724
EInit g_EInitVenusWeedDart = {ANIMSET_OVL(8), 55, 80, PAL_DRA(522), 164};
