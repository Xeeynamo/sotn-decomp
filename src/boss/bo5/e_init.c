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
void EntityCameraBounds(Entity* self);
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
void EntityHippogryph(Entity* self);
void EntityHippogryphHitbox(Entity* self);
void EntityFireDamageHitbox(Entity* self);
void EntityHippogryphEgg(Entity* self);
void func_us_801A3E78(Entity* self);
void EntityFireBreath(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityPlayBossMusic(Entity* self);
void EntityCutscene(Entity* self);
void EntityCutsceneStage(Entity* self);
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
    EntityCameraBounds,
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
    EntityHippogryph,
    EntityHippogryphHitbox,
    EntityFireDamageHitbox,
    EntityHippogryphEgg,
    func_us_801A3E78,
    EntityFireBreath,
    EntityLifeUpSpawn,
    EntityPlayBossMusic,
    EntityCutscene,
    EntityCutsceneStage,
    func_us_801A62B4,
    func_801B1D68,
    BO5_RicSetDeadPrologue,
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
EInit g_EInitUnused801804C0 = {ANIMSET_OVL(1), 0x2B, 0x48, PAL_HIPPOGRYPH, ENEMY_COMMON};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitHippogryph = {ANIMSET_OVL(3), 0x00, 0x48, PAL_HIPPOGRYPH, ENEMY_HIPPOGRYPH};
EInit g_EInitHippogryphEgg = {ANIMSET_OVL(3), 0x68, 0x48, PAL_HIPPOGRYPH, ENEMY_HIPPOGRYPH_UNK_12D};
EInit g_EInitFireBreath = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_HIPPOGRYPH_FIRE_DAMAGE_HITBOX};
// clang-format on
