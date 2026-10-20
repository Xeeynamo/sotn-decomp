// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

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
void EntityBackgroundBookcase(Entity* self);
void EntityBackgroundFurniture(Entity* self);
void EntityBackgroundShadow(Entity* self);
void EntityDistantBookshelves(Entity* self);
void EntityThickBookcase(Entity* self);
void func_us_801AE7AC_from_lib(Entity* self);
void EntityLion(Entity* self);
void EntityLionAttack(Entity* self);
void EntityLionDeathParts(Entity* self);
void EntityTinMan(Entity* self);
void EntityTinManArm(Entity* self);
void EntityTinManProjectile(Entity* self);
void EntityTinManSmoke(Entity* self);
void EntityTinManDeathParts(Entity* self);
void EntityScarecrow(Entity* self);
void EntityScarecrowLimb(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void EntitySchmoo(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityCandleTable(Entity* self);

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
    EntityBackgroundBookcase,
    EntityBackgroundFurniture,
    EntityBackgroundShadow,
    EntityDistantBookshelves,
    EntityThickBookcase,
    func_us_801AE7AC_from_lib,
    EntityLion,
    EntityLionAttack,
    EntityLionDeathParts,
    EntityTinMan,
    EntityTinManArm,
    EntityTinManProjectile,
    EntityTinManSmoke,
    EntityTinManDeathParts,
    EntityScarecrow,
    EntityScarecrowLimb,
    EntityExplosionPuffOpaque,
    EntitySchmoo,
    EntityBreakableDebris,
    EntityCandleTable,
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
EInit g_EInitLion = {ANIMSET_OVL(3), 0x01, 0x50, PAL_LION, ENEMY_LION};
EInit g_EInitLionAttack = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_LION_UNK_107};
EInit g_EInitLionDeathParts = {ANIMSET_OVL(3), 0x00, 0x50, PAL_LION, ENEMY_PARTICLE};
EInit g_EInitTinman = {ANIMSET_OVL(4), 0x01, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN};
EInit g_EInitTinManArm = {ANIMSET_OVL(4), 0x05, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN_ARM};
EInit g_EInitTinManProjectile = {ANIMSET_OVL(4), 0x00, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN_PROJECTILE};
EInit g_EInitTinManDecoration = {ANIMSET_OVL(4), 0x00, 0x53, PAL_TIN_MAN, ENEMY_PARTICLE};
EInit g_EInitScarecrow = {ANIMSET_OVL(5), 0x00, 0x54, PAL_SCARECROW, ENEMY_SCARECROW};
EInit D_us_801806A0 = {ANIMSET_OVL(5), 0x00, 0x54, PAL_SCARECROW, ENEMY_INTERACTABLE};
EInit g_EInitSchmoo = {ANIMSET_OVL(5), 0x08, 0x54, PAL_SCHMOO, ENEMY_SCHMOO};
EInit g_EInitCandleTable = {ANIMSET_OVL(6), 0x00, 0x50, PAL_CANDLE_TABLE, ENEMY_INTERACTABLE};
// clang-format on
