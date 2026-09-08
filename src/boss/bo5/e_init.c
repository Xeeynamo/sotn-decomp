// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

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
void func_801A8620(Entity* self);
void EntityStainedGlass(Entity* self);
void EntityStainedGlassBackground(Entity* self);
void EntityBlock(Entity* self);
void EntityStatue(Entity* self);
void EntityBell(Entity* self);
void EntityCastleWall1(Entity* self);
void EntityCastleWall2(Entity* self);
void EntityStaircase(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundSkyLand(Entity* self);
void EntityRbo3Door(Entity* self);
void func_us_801A1C14(Entity* self);
void func_us_801A425C(Entity* self);
void func_us_801A4430(Entity* self);
void func_us_801A3FD4(Entity* self);
void func_us_801A3E78(Entity* self);
void func_us_801A3B88(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void func_us_801A4494(Entity* self);
void EntityCutscene(Entity* self);
void func_us_801A5F88(Entity* self);
void func_us_801A62B4(Entity* self);
void func_801B1D68(Entity* self);
void BO5_RicSetDeadPrologue(Entity* self);

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
    func_801A8620,
    EntityStainedGlass,
    EntityStainedGlassBackground,
    EntityBlock,
    EntityStatue,
    EntityBell,
    EntityCastleWall1,
    EntityCastleWall2,
    EntityStaircase,
    EntityClouds,
    EntityBackgroundSkyLand,
    EntityRbo3Door,
    func_us_801A1C14,
    func_us_801A425C,
    func_us_801A4430,
    func_us_801A3FD4,
    func_us_801A3E78,
    func_us_801A3B88,
    EntityLifeUpSpawn,
    func_us_801A4494,
    EntityCutscene,
    func_us_801A5F88,
    func_us_801A62B4,
    func_801B1D68,
    BO5_RicSetDeadPrologue,
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
EInit g_EInitUnused801804C0 = {ANIMSET_OVL(1), 43, 72, 512, 0x003};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitHippogryph = {ANIMSET_OVL(3), 0, 72, 512, 0x12C};
EInit D_us_801804E4 = {ANIMSET_OVL(3), 104, 72, 512, 0x12D};
EInit D_us_801804F0 = {ANIMSET_DRA(0), 0, 0, 0, 0x12E};
// clang-format on
