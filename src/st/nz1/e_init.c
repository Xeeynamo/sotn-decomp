// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void OVL_EXPORT(EntityRedDoor)(Entity* self);
void EntityIntenseExplosion(Entity* self);
void EntitySoulStealOrb(Entity* self);
void EntityRoomForeground(Entity* self);
void EntityStageNamePopup(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOrb(Entity* self);
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
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
void EntitySkullLordFlames(Entity* self);
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
void EntitySwordLordAttackHitbox(Entity* self);
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
void OVL_EXPORT(EntityBreakableDebris)(Entity* self);
void EntityBossDoorTrigger(Entity* self);
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

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityStageNamePopup,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
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
    EntitySkullLordFlames,
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
    EntitySwordLordAttackHitbox,
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
    OVL_EXPORT(EntityBreakableDebris),
    EntityBossDoorTrigger,
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
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0, PAL_NONE, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, PAL_NONE, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x003};
EInit g_EInitEnvironment = {ANIMSET_OVL(1), 0, 0, PAL_NONE, 0x005};
EInit D_us_80180BA0 = {ANIMSET_OVL(3), 1, 76, PAL_UNK_200, 0x105};
EInit D_us_80180BAC = {ANIMSET_OVL(3), 1, 76, PAL_UNK_200, 0x005};
EInit g_EInitHarpy = {ANIMSET_OVL(4), 0, 76, PAL_UNK_206, 0x0EF};
EInit D_us_80180BC4 = {ANIMSET_OVL(4), 18, 76, PAL_UNK_206, 0x0F1};
EInit g_EInitHarpyFlame = {ANIMSET_OVL(4), 19, 76, PAL_UNK_206, 0x0F2};
EInit D_us_80180BDC = {ANIMSET_OVL(4), 0, 76, PAL_UNK_206, 0x0F0};
EInit D_us_80180BE8 = {ANIMSET_OVL(4), 24, 76, PAL_UNK_206, 0x002};
EInit g_EInitCloakedKnight = {ANIMSET_OVL(5), 1, 72, PAL_UNK_20A, 0x10F};
EInit g_EInitCloakedKnightAura = {ANIMSET_OVL(5), 1, 72, PAL_UNK_20A, 0x002};
EInit g_EInitCloakedKnightSword = {ANIMSET_OVL(5), 1, 72, PAL_UNK_20A, 0x110};
EInit D_us_80180C18 = {ANIMSET_OVL(6), 1, 80, PAL_UNK_20F, 0x009};
EInit D_us_80180C24 = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x00A};
EInit D_us_80180C30 = {ANIMSET_OVL(6), 40, 80, PAL_UNK_20F, 0x0E4};
EInit D_us_80180C3C = {ANIMSET_OVL(6), 40, 80, PAL_UNK_20F, 0x002};
EInit g_EInitPhantomSkull = {ANIMSET_OVL(7), 18, 74, PAL_UNK_220, 0x043};
EInit g_EInitPhantomSkullTrail = {ANIMSET_OVL(7), 18, 74, PAL_UNK_220, 0x002};
EInit D_us_80180C60 = {ANIMSET_OVL(7), 1, 74, PAL_UNK_220, 0x044};
EInit D_us_80180C6C = {ANIMSET_OVL(7), 17, 74, PAL_UNK_220, 0x045};
EInit g_EInitFleaArmor = {ANIMSET_OVL(8), 1, 72, PAL_UNK_223, 0x029};
EInit g_EInitFleaArmorAttackHitbox = {ANIMSET_DRA(0), 0, 0, PAL_NONE, 0x02A};
EInit g_EInitFleaMan = {ANIMSET_OVL(8), 0, 72, PAL_UNK_223, 0x028};
EInit g_EInitKarasuman = {ANIMSET_OVL(11), 0, 72, PAL_UNK_232, 0x118};
EInit g_EInitKarasumanFeatherAttack = {ANIMSET_OVL(11), 59, 72, PAL_UNK_232, 0x119};
EInit g_EInitKarasumanOrbAttack = {ANIMSET_OVL(11), 0, 72, PAL_UNK_232, 0x11A};
EInit g_EInitKarasumanRavenAttack = {ANIMSET_OVL(11), 0, 72, PAL_UNK_232, 0x11B};
EInit g_EInitKarasumanFeather = {ANIMSET_OVL(11), 63, 72, PAL_UNK_232, 0x002};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(12), 0, 86, PAL_UNK_238, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(12), 0, 86, PAL_UNK_239, 0x130};
// clang-format on
