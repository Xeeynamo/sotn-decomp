// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: e_init.c
 * Overlay: CHI
 * Description: DATA - Entities
 */

#include "chi.h"

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
void EntityPersistentItemDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityDemonSwitchWall(Entity*);
void EntityDemonSwitch(Entity*);
void EntityBreakableWall(Entity*);
void EntityBreakableWallDebris(Entity*);
void EntityBreakableDebris(Entity*);
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
    EntityPersistentItemDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera, // EntityCameraLock
    EntityUnkId13,    // EntityParticleTrail
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityBreakableDebris,
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
// clang-format off
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};

#include "../e_init_common.h"

EInit g_EInitSecret = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};

// D_80180688
EInit g_EInitSalemWitch = {ANIMSET_OVL(3), 0x01, 0x48, PAL_SALEM_WITCH, ENEMY_SALEM_WITCH};

// D_80180694
EInit g_EInitSalemWitchCurse = {ANIMSET_OVL(3), 0x00, 0x48, PAL_SALEM_WITCH, ENEMY_SALEM_WITCH_CURSE};

// D_801806A0
EInit g_EInitSalemWitchTribolt = {ANIMSET_OVL(4), 0x00, 0x5C, PAL_SALEM_WITCH_TRIBOLT, ENEMY_SALEM_WITCH_TRIBOLT};

// D_801806AC
EInit g_EInitGremlin = {ANIMSET_OVL(2), 0x00, 0x48, PAL_GREMLIN, ENEMY_GREMLIN};

// Unused
// D_801806B8
EInit g_EInit801806B8 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_GREMLIN, ENEMY_INTERACTABLE};

// D_801806C4
EInit g_EInitGremlinFire = {ANIMSET_OVL(2), 0x00, 0x48, PAL_GREMLIN, ENEMY_GREMLIN_FIRE};

// D_801806D0
EInit g_EInitThornweed = {ANIMSET_OVL(7), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};

// Unused (Alternate Corpseweed)
// D_801806DC
EInit g_EInit801806DC = {ANIMSET_OVL(7), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};

// D_801806E8
EInit g_EInitCorpseweed = {ANIMSET_OVL(7), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};

// D_801806F4
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(7), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};

// D_80180700
EInit g_EInitVenusWeedRoot = {ANIMSET_OVL(8), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_ROOT};

// D_8018070C
EInit g_EInitVenusWeedFlower = {ANIMSET_OVL(8), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_FLOWER};

// D_80180718
EInit g_EInitVenusWeedTendril = {ANIMSET_OVL(8), 0x00, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_TENDRIL};

// D_80180724
EInit g_EInitVenusWeedDart = {ANIMSET_OVL(8), 0x37, 0x50, PAL_VENUS_WEED, ENEMY_VENUS_WEED_DART};
