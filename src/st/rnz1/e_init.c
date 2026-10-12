// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

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
void EntityExplosionPuffOpaque(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundGears(Entity* self);
void EntityGearSidewaysLarge(Entity* self);
void EntityGearHorizontal(Entity* self);
void EntityGearVertical(Entity* self);
void EntityGearSidewaysSmall(Entity* self);
void EntityWallGear(Entity* self);
void EntityBreakableWall(Entity* self);
void EntitySecretWallDebris(Entity* self);
void EntityRoomExit(Entity* self);
void EntityBreakableWallPartial(Entity* self);
void EntitySecretAreaDoor(Entity* self);
void EntityWaterForeground(Entity* self);
void EntityAlucardWaterEffect(Entity* self);
void EntitySplashWater(Entity* self);
void EntitySurfacingWater(Entity* self);
void EntitySideWaterSplash(Entity* self);
void EntitySmallWaterDrop(Entity* self);
void EntityWaterDrop(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityDarkwingBat(Entity* self);
void EntityDarkwingBatPerch(Entity* self);
void EntityDarkwingBatWings(Entity* self);
void EntityDarkwingWindDust(Entity* self);
void EntityFadingFireball(Entity* self);
void EntityBossFightManager(Entity* self);
void EntityBossDoors(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCloakedKnight(Entity* self);
void EntityCloakedKnightCloak(Entity* self);
void EntityCloakedKnightSword(Entity* self);
void EntityCloakedKnightAura(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void EntityBombKnight(Entity* self);
void EntityThrownBomb(Entity* self);
void EntityKnightDeathParts(Entity* self);
void EntityBombFuseSparks(Entity* self);
void EntityThrownRock(Entity* self);
void EntityRockPiece(Entity* self);
void EntityBombKnightArm(Entity* self);
void EntityCrusherHead(Entity* self);
void EntityCrusherSpinningTeeth(Entity* self);
void EntityCrusher(Entity* self);

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
    EntityExplosionPuffOpaque,
    EntityClouds,
    EntityBackgroundGears,
    EntityGearSidewaysLarge,
    EntityGearHorizontal,
    EntityGearVertical,
    EntityGearSidewaysSmall,
    EntityWallGear,
    EntityBreakableWall,
    EntitySecretWallDebris,
    EntityRoomExit,
    EntityBreakableWallPartial,
    EntitySecretAreaDoor,
    EntityWaterForeground,
    EntityAlucardWaterEffect,
    EntitySplashWater,
    EntitySurfacingWater,
    EntitySideWaterSplash,
    EntitySmallWaterDrop,
    EntityWaterDrop,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    EntityDarkwingBat,
    EntityDarkwingBatPerch,
    EntityDarkwingBatWings,
    EntityDarkwingWindDust,
    EntityFadingFireball,
    EntityBossFightManager,
    EntityBossDoors,
    EntityLifeUpSpawn,
    EntityCloakedKnight,
    EntityCloakedKnightCloak,
    EntityCloakedKnightSword,
    EntityCloakedKnightAura,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
    EntityBreakableDebris,
    EntityValhallaKnight,
    func_us_801C8954,
    func_us_801C8AAC,
    EntityBombKnight,
    EntityThrownBomb,
    EntityKnightDeathParts,
    EntityBombFuseSparks,
    EntityThrownRock,
    EntityRockPiece,
    EntityBombKnightArm,
    EntityCrusherHead,
    EntityCrusherSpinningTeeth,
    EntityCrusher,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitUnused80180B7C = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitPlateLord = {ANIMSET_OVL(11), 0x01, 0x48, PAL_PLATE_LORD, ENEMY_PLATE_LORD};
EInit g_EInitUnused80180B94 = {ANIMSET_OVL(11), 0x16, 0x48, PAL_PLATE_LORD, ENEMY_PLATE_LORD_UNK_62};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnused80180BAC = {ANIMSET_OVL(3), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitDarkwingBat = {ANIMSET_OVL(5), 0x01, 0x48, PAL_DARKWING_BAT, ENEMY_DARKWING_BAT};
EInit g_EInitDarkwingBat2 = {ANIMSET_OVL(5), 0x00, 0x48, PAL_DARKWING_BAT, ENEMY_INTERACTABLE};
EInit g_EInitCloakedKnight = {ANIMSET_OVL(6), 0x01, 0x48, PAL_CLOAKED_KNIGHT, ENEMY_CLOAKED_KNIGHT};
EInit g_EInitCloakedKnightAura = {ANIMSET_OVL(6), 0x01, 0x48, PAL_CLOAKED_KNIGHT, ENEMY_PARTICLE};
EInit g_EInitCloakedKnightSword = {ANIMSET_OVL(6), 0x01, 0x48, PAL_CLOAKED_KNIGHT, ENEMY_CLOAKED_KNIGHT_SWORD};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(7), 0x00, 0x49, PAL_MEDUSA_HEAD_BLUE, ENEMY_MEDUSA_HEAD_BLUE};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(7), 0x00, 0x49, PAL_MEDUSA_HEAD_YELLOW, ENEMY_MEDUSA_HEAD_YELLOW};
EInit g_EInitValhallaKnight = {ANIMSET_OVL(8), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, ENEMY_VALHALLA_KNIGHT};
EInit g_EInitValhallaKnightUnk1 = {ANIMSET_OVL(8), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, ENEMY_COMMON};
EInit g_EInitValhallaKnightUnk2 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK2};
EInit g_EInitValhallaKnightUnk3 = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_VALHALLA_KNIGHT_UNK3};
EInit g_EInitBombKnight = {ANIMSET_OVL(11), 0x01, 0x48, PAL_BOMB_KNIGHT_ROCK_KNIGHT, ENEMY_BOMB_KNIGHT};
EInit g_EInitBomb = {ANIMSET_OVL(11), 0x24, 0x48, PAL_BOMB_KNIGHT_ROCK_KNIGHT, ENEMY_BOMB};
EInit g_EInitKnightDebris = {ANIMSET_OVL(11), 0x00, 0x48, PAL_BOMB_KNIGHT_ROCK_KNIGHT, ENEMY_PARTICLE};
EInit g_EInitRock = {ANIMSET_OVL(11), 0x41, 0x48, PAL_BOMB_KNIGHT_ROCK_KNIGHT, ENEMY_ROCK};
EInit g_EInitRockKnight = {ANIMSET_OVL(11), 0x01, 0x48, PAL_BOMB_KNIGHT_ROCK_KNIGHT, ENEMY_ROCK_KNIGHT};
EInit g_EInitCrusher = {ANIMSET_OVL(13), 0x01, 0x51, PAL_CRUSHER, ENEMY_INTERACTABLE};
// clang-format on
