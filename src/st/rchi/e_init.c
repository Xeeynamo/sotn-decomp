// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

void EntityBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void EntityRedDoor(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityPersistentItemDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntitySlogra(Entity* self);
void EntitySlograSpear(Entity* self);
void EntitySlograSpearProjectile(Entity* self);
void EntityGaibon(Entity* self);
void EntityGaibonLeg(Entity* self);
void EntitySmallGaibonProjectile(Entity* self);
void EntityLargeGaibonProjectile(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityDemonSwitchWall(Entity* self);
void EntityDemonSwitch(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityBat(Entity* self);

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
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntitySlogra,
    EntitySlograSpear,
    EntitySlograSpearProjectile,
    EntityGaibon,
    EntityGaibonLeg,
    EntitySmallGaibonProjectile,
    EntityLargeGaibonProjectile,
    EntityBreakableDebris,
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityBat,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitSlogra = {ANIMSET_OVL(3), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA};
EInit g_EInitSlograSpear = {ANIMSET_OVL(3), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_SPEAR};
EInit g_EInitSlograProjectile = {ANIMSET_OVL(3), 0x00, 0x48, PAL_SLOGRA, ENEMY_SLOGRA_PROJECTILE};
EInit g_EInitGaibon = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_GAIBON, ENEMY_GAIBON};
EInit g_EInitGaibonProjectile = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_PROJECTILE};
EInit g_EInitGaibonLargeProjectile = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GAIBON_LARGE_PROJECTILE};
EInit g_EInitBreakableWalL = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitBreakableWallDebris = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitThornweed = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};
EInit g_EInitCorpseweedUnused = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};
EInit g_EInitCorpseweed = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit D_us_80180678 = {ANIMSET_OVL(5), 0x00, 0x4C, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};
EInit g_EInitBat = {ANIMSET_OVL(9), 0x00, 0x5F, PAL_BAT, ENEMY_BAT};
// clang-format on
