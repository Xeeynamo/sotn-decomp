// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

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
void EntityBridgeBreakTrigger(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void EntityClouds(Entity* self);
void EntityBackgroundGears(Entity* self);
void EntityGearSidewaysLarge(Entity* self);
void EntityGearHorizontal(Entity* self);
void EntityGearVertical(Entity* self);
void EntityGearSidewaysSmall(Entity* self);
void EntityWallGear(Entity* self);
void EntityPendulumAnchor(Entity* self);
void EntityPendulumBoneChain(Entity* self);
void EntityPendulumWeight(Entity* self);
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
void EntitySkullLord(Entity* self);
void EntitySkullLordOutline(Entity* self);
void EntitySkullLordEye(Entity* self);
void EntitySkullLordPieces(Entity* self);
void EntityHarpy(Entity* self);
void EntityHarpyDagger(Entity* self);
void EntityHarpyFlame(Entity* self);
void EntityHarpyKick(Entity* self);
void EntityHarpyFeather(Entity* self);
void EntityCloakedKnight(Entity* self);
void EntityCloakedKnightCloak(Entity* self);
void EntityCloakedKnightSword(Entity* self);
void EntityCloakedKnightAura(Entity* self);
void EntitySwordLord(Entity* self);
void EntitySwordLordAttack(Entity* self);
void EntityVandalSword(Entity* self);
void EntityVandalSwordDeath(Entity* self);
void EntityVandalSwordHitbox(Entity* self);
void EntityPhantomSkull(Entity* self);
void EntityPhantomSkullTrail(Entity* self);
void EntityFlailGuard(Entity* self);
void EntityFlailGuardFlail(Entity* self);
void EntityBridgeBackgroundPiece(Entity* self);
void EntityFleaArmor(Entity* self);
void EntityFleaArmorAttackHitbox(Entity* self);
void EntityFleaMan(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityBossFightManager(Entity* self);
void EntityBossDoors(Entity* self);
void EntityKarasuman(Entity* self);
void EntityKarasumanFeatherAttack(Entity* self);
void EntityKarasumanOrbAttack(Entity* self);
void EntityKarasumanRavenAttack(Entity* self);
void EntityKarasumanFeather(Entity* self);
void EntityKarasumanRavenAbsorb(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);

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
    EntityBridgeBreakTrigger,
    EntityExplosionPuffOpaque,
    EntityClouds,
    EntityBackgroundGears,
    EntityGearSidewaysLarge,
    EntityGearHorizontal,
    EntityGearVertical,
    EntityGearSidewaysSmall,
    EntityWallGear,
    EntityPendulumAnchor,
    EntityPendulumBoneChain,
    EntityPendulumWeight,
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
    EntitySkullLord,
    EntitySkullLordOutline,
    EntitySkullLordEye,
    EntitySkullLordPieces,
    EntityHarpy,
    EntityHarpyDagger,
    EntityHarpyFlame,
    EntityHarpyKick,
    EntityHarpyFeather,
    EntityCloakedKnight,
    EntityCloakedKnightCloak,
    EntityCloakedKnightSword,
    EntityCloakedKnightAura,
    EntitySwordLord,
    EntitySwordLordAttack,
    EntityVandalSword,
    EntityVandalSwordDeath,
    EntityVandalSwordHitbox,
    EntityPhantomSkull,
    EntityPhantomSkullTrail,
    EntityFlailGuard,
    EntityFlailGuardFlail,
    EntityBridgeBackgroundPiece,
    EntityFleaArmor,
    EntityFleaArmorAttackHitbox,
    EntityFleaMan,
    EntityBreakableDebris,
    EntityBossFightManager,
    EntityBossDoors,
    EntityKarasuman,
    EntityKarasumanFeatherAttack,
    EntityKarasumanOrbAttack,
    EntityKarasumanRavenAttack,
    EntityKarasumanFeather,
    EntityKarasumanRavenAbsorb,
    EntityLifeUpSpawn,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
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
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitSkullLord = {ANIMSET_OVL(3), 0x01, 0x4C, PAL_UNK_200, ENEMY_SKULL_LORD};
EInit g_EInitSkullLordEffects = {ANIMSET_OVL(3), 0x01, 0x4C, PAL_UNK_200, ENEMY_INTERACTABLE};
EInit g_EInitHarpy = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_UNK_206, ENEMY_HARPY};
EInit g_EInitHarpyDagger = {ANIMSET_OVL(4), 0x12, 0x4C, PAL_UNK_206, ENEMY_HARPY_DAGGER};
EInit g_EInitHarpyFlame = {ANIMSET_OVL(4), 0x13, 0x4C, PAL_UNK_206, ENEMY_HARPY_FLAME};
EInit g_EInitHarpyKick = {ANIMSET_OVL(4), 0x00, 0x4C, PAL_UNK_206, ENEMY_HARPY_KICK};
EInit g_EInitHarpyFeather = {ANIMSET_OVL(4), 0x18, 0x4C, PAL_UNK_206, ENEMY_PARTICLE};
EInit g_EInitCloakedKnight = {ANIMSET_OVL(5), 0x01, 0x48, PAL_UNK_20A, ENEMY_CLOAKED_KNIGHT};
EInit g_EInitCloakedKnightAura = {ANIMSET_OVL(5), 0x01, 0x48, PAL_UNK_20A, ENEMY_PARTICLE};
EInit g_EInitCloakedKnightSword = {ANIMSET_OVL(5), 0x01, 0x48, PAL_UNK_20A, ENEMY_CLOAKED_KNIGHT_SWORD};
EInit g_EInitSwordLord = {ANIMSET_OVL(6), 0x01, 0x50, PAL_UNK_20F, ENEMY_SWORD_LORD};
EInit g_EInitSwordLordAttack = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SWORD_LORD_ATTACK};
EInit g_EInitVandalSword = {ANIMSET_OVL(6), 0x28, 0x50, PAL_UNK_20F, ENEMY_VANDAL_SWORD};
EInit g_EInitVandSwordDeath = {ANIMSET_OVL(6), 0x28, 0x50, PAL_UNK_20F, ENEMY_PARTICLE};
EInit g_EInitPhantomSkull = {ANIMSET_OVL(7), 0x12, 0x4A, PAL_UNK_220, ENEMY_PHANTOM_SKULL};
EInit g_EInitPhantomSkullTrail = {ANIMSET_OVL(7), 0x12, 0x4A, PAL_UNK_220, ENEMY_PARTICLE};
EInit g_EInitFlailGuard = {ANIMSET_OVL(7), 0x01, 0x4A, PAL_UNK_220, ENEMY_FLAIL_GUARD};
EInit g_EInitFlailGuardFlail = {ANIMSET_OVL(7), 0x11, 0x4A, PAL_UNK_220, ENEMY_FLAIL_GUARD_FLAIL};
EInit g_EInitFleaArmor = {ANIMSET_OVL(8), 0x01, 0x48, PAL_UNK_223, ENEMY_FLEA_ARMOR};
EInit g_EInitFleaArmorAttackHitbox = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_FLEA_ARMOR_ATTACK_HITBOX};
EInit g_EInitFleaMan = {ANIMSET_OVL(8), 0x00, 0x48, PAL_UNK_223, ENEMY_FLEA_MAN};
EInit g_EInitKarasuman = {ANIMSET_OVL(11), 0x00, 0x48, PAL_UNK_232, ENEMY_KARASUMAN};
EInit g_EInitKarasumanFeatherAttack = {ANIMSET_OVL(11), 0x3B, 0x48, PAL_UNK_232, ENEMY_KARASUMAN_FEATHER_ATTACK};
EInit g_EInitKarasumanOrbAttack = {ANIMSET_OVL(11), 0x00, 0x48, PAL_UNK_232, ENEMY_KARASUMAN_ORB_ATTACK};
EInit g_EInitKarasumanRavenAttack = {ANIMSET_OVL(11), 0x00, 0x48, PAL_UNK_232, ENEMY_KARASUMAN_RAVEN_ATTACK};
EInit g_EInitKarasumanFeather = {ANIMSET_OVL(11), 0x3F, 0x48, PAL_UNK_232, ENEMY_PARTICLE};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(12), 0x00, 0x56, PAL_UNK_238, ENEMY_MEDUSA_HEAD_BLUE};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(12), 0x00, 0x56, PAL_UNK_239, ENEMY_MEDUSA_HEAD_YELLOW};
// clang-format on
