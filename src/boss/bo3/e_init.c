// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

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
void EntityDummy(Entity* self);
void EntitySplashWater(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityWaterDrop(Entity* self);
void func_us_801C12B0(Entity* self);
void func_us_801C15F8(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void func_us_801A07CC(Entity* self);
void func_us_801A0A80(Entity* self);
void func_us_801A1120(Entity* self);
void func_us_801A16E4(Entity* self);
void EntityScylla(Entity* self);
void EntityScyllaTentacles(Entity* self);
void EntityScyllaWolfHead(Entity* self);
void EntityScyllaWaterBlade(Entity* self);
void func_us_801A42A8(Entity* self);
void EntityScyllaBubbleSkull(Entity* self);
void EntityScyllaWaterOrb(Entity* self);
void EntityScyllaFallingRock(Entity* self);
void EntityScyllaDroplet(Entity* self);
void EntityWyrm(Entity* self);
void EntityWyrmBodyPart(Entity* self);
void EntityWyrmHead(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void func_us_801A1BE8(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void func_us_801A6370(Entity* self);
void func_us_801A6568(Entity* self);
void EntityBreakableStatueBroken(Entity* self);

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
    EntityDummy,
    EntitySplashWater,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityWaterDrop,
    func_us_801C12B0,
    func_us_801C15F8,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    func_us_801A07CC,
    func_us_801A0A80,
    func_us_801A1120,
    func_us_801A16E4,
    EntityScylla,
    EntityScyllaTentacles,
    EntityScyllaWolfHead,
    EntityScyllaWaterBlade,
    func_us_801A42A8,
    EntityScyllaBubbleSkull,
    EntityScyllaWaterOrb,
    EntityScyllaFallingRock,
    EntityScyllaDroplet,
    EntityWyrm,
    EntityWyrmBodyPart,
    EntityWyrmHead,
    EntityExplosionPuffOpaque,
    func_us_801A1BE8,
    EntityBreakableWallDebris,
    EntityLifeUpSpawn,
    func_us_801A6370,
    func_us_801A6568,
    EntityBreakableStatueBroken,
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
EInit g_EInitScylla = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA};
EInit D_us_801805AC = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_UNK_120};
EInit D_us_801805B8 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_INTERACTABLE};
EInit D_us_801805C4 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_UNK_121};
EInit D_us_801805D0 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_UNK_122};
EInit D_us_801805DC = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_UNK_124};
EInit D_us_801805E8 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_UNK_125};
EInit D_us_801805F4 = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_PARTICLE};
EInit g_EInitWyrm = {ANIMSET_OVL(2), 0x00, 0x48, PAL_SCYLLA, ENEMY_SCYLLA_WYRM};
// clang-format on
