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
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 11, 0, 0, 0x003};
EInit g_EInitPrisoner = {ANIMSET_OVL(3), 1, 73, 513, 0x003};

EInit g_EInitCtulhu = {ANIMSET_OVL(4), 0, 72, 515, 0x0E9};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(4), 0, 72, 515, 0x0EA};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(4), 44, 72, 515, 0x0EB};

EInit g_EInitMalachi = {ANIMSET_OVL(5), 0, 80, 520, 0x0EC};
EInit D_us_80180904 = {ANIMSET_OVL(5), 0, 80, 520, 0x0ED};
EInit D_us_80180910 = {ANIMSET_OVL(5), 0, 80, 520, 0x0EE};
EInit g_EInitKarasuman = {ANIMSET_OVL(6), 0, 72, 536, 0x118};
EInit g_EInitKarasumanFeatherAttack = {ANIMSET_OVL(6), 59, 72, 536, 0x119};
EInit g_EInitKarasumanOrbAttack = {ANIMSET_OVL(6), 0, 72, 536, 0x11A};
EInit g_EInitKarasumanRavenAttack = {ANIMSET_OVL(6), 0, 72, 536, 0x11B};
EInit g_EInitKarasumanFeather = {ANIMSET_OVL(6), 63, 72, 536, 0x002};
EInit g_EInitFlyingZombieHalf2 = {ANIMSET_OVL(7), 1, 75, 542, 0x00F};
EInit g_EInitFlyingZombieHalf1 = {ANIMSET_OVL(7), 0, 75, 542, 0x00E};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 1, 74, 726, 0x00D};
EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0, 0, 0, 0x0E0};
EInit g_EInitGhostDancer = {ANIMSET_OVL(10), 0, 76, 558, 0x0D8};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(13), 0, 95, 592, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(13), 0, 95, 593, 0x130};
// clang-format on
