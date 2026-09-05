// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo1.h"

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
void EntityBossDoor(Entity* self);
void func_us_801BA164_from_cat(Entity* self);
void EntityGranfaloon(Entity* self);
void EntityGranfaloonTentacle(Entity* self);
void EntityTentacleHead(Entity* self);
void EntityTentacleLaser(Entity* self);
void EntityBodyPartShell(Entity* self);
void EntityBodyPartDeadPiece(Entity* self);
void func_us_801A2CC4(Entity* self);
void func_us_801A2D90(Entity* self);
void EntityZombieFalling(Entity* self);
void EntityZombieEnemy(Entity* self);
void EntityExplosionFlame(Entity* self);
void func_us_801A493C(Entity* self);
void EntityHomingLaser(Entity* self);
void EntityLifeUpSpawn(Entity* self);

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
    EntityBossDoor,
    func_us_801BA164_from_cat,
    EntityGranfaloon,
    EntityGranfaloonTentacle,
    EntityTentacleHead,
    EntityTentacleLaser,
    EntityBodyPartShell,
    EntityBodyPartDeadPiece,
    func_us_801A2CC4,
    func_us_801A2D90,
    EntityZombieFalling,
    EntityZombieEnemy,
    EntityExplosionFlame,
    func_us_801A493C,
    EntityHomingLaser,
    EntityLifeUpSpawn,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitBossDoor = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180B04 = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitGranfaloonCore = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x127};
EInit g_EInitTentacle = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x005};
EInit g_EInitHomingLaser = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x12A};
EInit D_us_80180B34 = {ANIMSET_DRA(0), 0, 0, 0, 0x12A};
EInit g_EInitGranfaloonShell = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x128};
EInit g_EInitShellDeadPiece = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x005};
EInit g_EInitGrafaloonZombie = {ANIMSET_OVL(3), 0, 72, PAL_BASE, 0x129};
// clang-format on
