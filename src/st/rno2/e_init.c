// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno2.h"

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
void EntityDeepBackgroundArch(Entity* self);
void EntityFountainWater(Entity* self);
void EntityRampart(Entity* self);
void EntityNightSky(Entity* self);
void EntityStoneBrazier(Entity* self);
void Entity3DBackgroundHouse(Entity* self);
void Entity3DHouseSpawner(Entity* self);
void EntityHouseShader(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityStoneBridgeSecret(Entity* self);
void EntityBreakableWallBackside(Entity* self);
void EntityPrisoner(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityCtulhu(Entity* self);
void EntityCtulhuFireball(Entity* self);
void EntityCtulhuIceShockwave(Entity* self);
void EntityCtulhuDeath(Entity* self);
void EntityMalachi(Entity* self);
void EnittyMalachiShooter(Entity* self);
void EntityMalachiBall(Entity* self);
void EntityMalachiBallWisp(Entity* self);
void EntityKarasuman(Entity* self);
void EntityKarasumanFeatherAttack(Entity* self);
void EntityKarasumanOrbAttack(Entity* self);
void EntityKarasumanRavenAttack(Entity* self);
void EntityKarasumanFeather(Entity* self);
void EntityKarasumanRavenAbsorb(Entity* self);
void EntityFlyingZombie2(Entity* self);
void EntityFlyingZombie1(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void EntityAzaghal(Entity* self);
void EntityAzaghalSwordHitbox(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityGhostDancer(Entity* self);
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
    EntityDeepBackgroundArch,
    EntityFountainWater,
    EntityRampart,
    EntityNightSky,
    EntityStoneBrazier,
    Entity3DBackgroundHouse,
    Entity3DHouseSpawner,
    EntityHouseShader,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    EntityBreakableWall,
    EntityStoneBridgeSecret,
    EntityBreakableWallBackside,
    EntityPrisoner,
    EntitySealedDoor,
    EntityCtulhu,
    EntityCtulhuFireball,
    EntityCtulhuIceShockwave,
    EntityCtulhuDeath,
    EntityMalachi,
    EnittyMalachiShooter,
    EntityMalachiBall,
    EntityMalachiBallWisp,
    EntityKarasuman,
    EntityKarasumanFeatherAttack,
    EntityKarasumanOrbAttack,
    EntityKarasumanRavenAttack,
    EntityKarasumanFeather,
    EntityKarasumanRavenAbsorb,
    EntityFlyingZombie2,
    EntityFlyingZombie1,
    EntityBloodDrips,
    EntityBloodSplatter,
    EntityAzaghal,
    EntityAzaghalSwordHitbox,
    EntityBreakableDebris,
    EntityGhostDancer,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
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
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0x0B, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitPrisoner = {ANIMSET_OVL(3), 0x01, 0x49, PAL_PRISONER, ENEMY_COMMON};

EInit g_EInitCtulhu = {ANIMSET_OVL(4), 0x00, 0x48, PAL_CTULHU, ENEMY_CTULHU};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(4), 0x00, 0x48, PAL_CTULHU, ENEMY_CTULHU_FIREBALL};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(4), 0x2C, 0x48, PAL_CTULHU, ENEMY_CTULHU_ICE_SHOCKWAVE};

EInit g_EInitMalachi = {ANIMSET_OVL(5), 0x00, 0x50, PAL_MALACHI, ENEMY_MALACHI};
EInit D_us_80180904 = {ANIMSET_OVL(5), 0x00, 0x50, PAL_MALACHI, ENEMY_MALACHI_SHOOTER};
EInit D_us_80180910 = {ANIMSET_OVL(5), 0x00, 0x50, PAL_MALACHI, ENEMY_MALACHI_BALL};
EInit g_EInitKarasuman = {ANIMSET_OVL(6), 0x00, 0x48, PAL_KARASUMAN, ENEMY_KARASUMAN};
EInit g_EInitKarasumanFeatherAttack = {ANIMSET_OVL(6), 0x3B, 0x48, PAL_KARASUMAN, ENEMY_KARASUMAN_FEATHER_ATTACK};
EInit g_EInitKarasumanOrbAttack = {ANIMSET_OVL(6), 0x00, 0x48, PAL_KARASUMAN, ENEMY_KARASUMAN_ORB_ATTACK};
EInit g_EInitKarasumanRavenAttack = {ANIMSET_OVL(6), 0x00, 0x48, PAL_KARASUMAN, ENEMY_KARASUMAN_RAVEN_ATTACK};
EInit g_EInitKarasumanFeather = {ANIMSET_OVL(6), 0x3F, 0x48, PAL_KARASUMAN, ENEMY_PARTICLE};
EInit g_EInitFlyingZombie2 = {ANIMSET_OVL(7), 0x01, 0x4B, PAL_FLYING_ZOMBIE, ENEMY_FLYING_ZOMBIE_2};
EInit g_EInitFlyingZombie1 = {ANIMSET_OVL(7), 0x00, 0x4B, PAL_FLYING_ZOMBIE, ENEMY_FLYING_ZOMBIE_1};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, ENEMY_BLOODY_ZOMBIE};
EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_AZAGHAL};
EInit g_EInitGhostDancer = {ANIMSET_OVL(10), 0x00, 0x4C, PAL_GHOST_DANCER, ENEMY_GHOST_DANCER};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(13), 0x00, 0x5F, PAL_MEDUSA_HEAD_BLUE, ENEMY_MEDUSA_HEAD_BLUE};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(13), 0x00, 0x5F, PAL_MEDUSA_HEAD_YELLOW, ENEMY_MEDUSA_HEAD_YELLOW};
// clang-format on
