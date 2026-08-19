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
void func_us_801B3D8C_from_bo0(Entity* self);
void func_us_801B3F30_from_bo0(Entity* self);
void func_us_801B4148_from_bo0(Entity* self);
void func_us_801B41A4_from_bo0(Entity* self);
void func_us_801B4210_from_bo0(Entity* self);
void Entity3DBackgroundHouse(Entity* self);
void Entity3DHouseSpawner(Entity* self);
void func_us_801B4DA4_from_bo0(Entity* self);
void EntitySpikes(Entity* self);
void EntitySpikesParts(Entity* self);
void EntitySpikesDust(Entity* self);
void EntitySpikesDamage(Entity* self);
void func_us_801B5FB8_from_no2(Entity* self);
void func_us_801B68EC_from_no2(Entity* self);
void func_us_801AC54C_from_bo0(Entity* self);
void EntityPrisoner(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityCtulhu(Entity* self);
void EntityCtulhuFireball(Entity* self);
void EntityCtulhuIceShockwave(Entity* self);
void EntityCtulhuDeath(Entity* self);
void func_us_801C39A4(Entity* self);
void func_us_801C4960(Entity* self);
void func_us_801C4C0C(Entity* self);
void func_us_801C4EA8(Entity* self);
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
void func_us_801CAB8C(Entity* self);
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
    func_us_801B3D8C_from_bo0,
    func_us_801B3F30_from_bo0,
    func_us_801B4148_from_bo0,
    func_us_801B41A4_from_bo0,
    func_us_801B4210_from_bo0,
    Entity3DBackgroundHouse,
    Entity3DHouseSpawner,
    func_us_801B4DA4_from_bo0,
    EntitySpikes,
    EntitySpikesParts,
    EntitySpikesDust,
    EntitySpikesDamage,
    func_us_801B5FB8_from_no2,
    func_us_801B68EC_from_no2,
    func_us_801AC54C_from_bo0,
    EntityPrisoner,
    EntitySealedDoor,
    EntityCtulhu,
    EntityCtulhuFireball,
    EntityCtulhuIceShockwave,
    EntityCtulhuDeath,
    func_us_801C39A4,
    func_us_801C4960,
    func_us_801C4C0C,
    func_us_801C4EA8,
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
    func_us_801CAB8C,
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
EInit D_us_801808BC = {ANIMSET_OVL(2), 11, 0, 0, 0x003};
EInit D_us_801808C8 = {ANIMSET_OVL(3), 1, 73, 513, 0x003};

EInit g_EInitCtulhu = {ANIMSET_OVL(4), 0, 72, 515, 0x0E9};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(4), 0, 72, 515, 0x0EA};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(4), 44, 72, 515, 0x0EB};

EInit g_EInitMalachi = {ANIMSET_OVL(5), 0, 80, 520, 0x0EC};
EInit D_us_80180904 = {ANIMSET_OVL(5), 0, 80, 520, 0x0ED};
EInit D_us_80180910 = {ANIMSET_OVL(5), 0, 80, 520, 0x0EE};
EInit g_EInitKarasuman = {ANIMSET_OVL(6), 0, 72, 536, 0x118};
EInit D_us_80180928 = {ANIMSET_OVL(6), 59, 72, 536, 0x119};
EInit D_us_80180934 = {ANIMSET_OVL(6), 0, 72, 536, 0x11A};
EInit D_us_80180940 = {ANIMSET_OVL(6), 0, 72, 536, 0x11B};
EInit D_us_8018094C = {ANIMSET_OVL(6), 63, 72, 536, 0x002};
EInit g_EInitFlyingZombieHalf2 = {ANIMSET_OVL(7), 1, 75, 542, 0x00F};
EInit g_EInitFlyingZombieHalf1 = {ANIMSET_OVL(7), 0, 75, 542, 0x00E};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(9), 1, 74, 726, 0x00D};
EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0, 0, 0, 0x0E0};
EInit g_EInitGhostDancer = {ANIMSET_OVL(10), 0, 76, 558, 0x0D8};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(13), 0, 95, 592, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(13), 0, 95, 593, 0x130};
// clang-format on
