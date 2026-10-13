// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"

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
void EntityBossDoors(Entity* self);
void EntityBossFightManager(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityAkmodanII(Entity* self);
void func_us_801957C0(Entity* self);
void EntityHarpyKick(Entity* self);
void func_us_80195A8C(Entity* self);
void func_us_80195D04(Entity* self);
void EntityCtulhuDeath(Entity* self);

PfnEntityUpdate EntityUpdates[] = {
    /* 0x01 */ EntityBreakable,
    /* 0x02 */ EntityExplosion,
    /* 0x03 */ EntityPrizeDrop,
    /* 0x04 */ EntityDamageDisplay,
    /* 0x05 */ EntityRedDoor,
    /* 0x06 */ EntityIntenseExplosion,
    /* 0x07 */ EntitySoulStealOrb,
    /* 0x08 */ EntityRoomForeground,
    /* 0x09 */ EntityStageNamePopup,
    /* 0x0A */ EntityEquipItemDrop,
    /* 0x0B */ EntityRelicOrb,
    /* 0x0C */ EntityPersistentItemDrop,
    /* 0x0D */ EntityEnemyBlood,
    /* 0x0E */ EntityMessageBox,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityDummy,
    /* 0x11 */ EntityBackgroundBlock,
    /* 0x12 */ EntityLockCamera,
    /* 0x13 */ EntityUnkId13,
    /* 0x14 */ EntityExplosionVariants,
    /* 0x15 */ EntityGreyPuff,
    /* 0x16 */ EntityBossDoors,
    /* 0x17 */ EntityBossFightManager,
    /* 0x18 */ EntityLifeUpSpawn,
    /* 0x19 */ EntityAkmodanII,
    /* 0x1A */ func_us_801957C0,
    /* 0x1B */ EntityHarpyKick,
    /* 0x1C */ func_us_80195A8C,
    /* 0x1D */ func_us_80195D04,
    /* 0x1E */ EntityCtulhuDeath,
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
EInit g_EInitUnused80180420 = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitBossDoors = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitAkmodanII = {ANIMSET_OVL(8), 0x01, 0x48, PAL_AKMODAN_II, ENEMY_AKMODAN_II};
EInit D_us_80180444 = {ANIMSET_OVL(8), 0x00, 0x48, PAL_AKMODAN_II, ENEMY_AKMODAN_II_UNK_10C};
EInit D_us_80180450 = {ANIMSET_OVL(10), 0x01, 0x4E, PAL_CC_YELLOW_EFFECT, ENEMY_AKMODAN_II_UNK_10D};
// clang-format on
