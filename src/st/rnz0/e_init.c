// SPDX-License-Identifier: AGPL-3.0-or-later
// SPDX-License-Identifier: AGPL-3.0-or-later(Entity* self);
#include "rnz0.h"

void EntityBreakableNZ0(Entity* self);
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
void EntityPurpleBrickScrollingBackground(Entity* self);
void EntityLeftSecretRoomWall(Entity* self);
void EntityBottomSecretRoomFloor(Entity* self);
void EntitySecretWallDebris(Entity* self);
void EntityFloorTrap(Entity* self);
void EntityCtulhu(Entity* self);
void EntityCtulhuFireball(Entity* self);
void EntityCtulhuIceShockwave(Entity* self);
void EntityCtulhuDeath(Entity* self);
void EntityFireDemon(Entity* self);
void EntityUnkId20(Entity* self);
void EntityUnkId21(Entity* self);
void EntityUnkId22(Entity* self);
void EntityLesserDemon(Entity* self);
void func_us_801BCAB0(Entity* self);
void func_us_801BD7D0(Entity* self);
void func_us_801BF7B0(Entity* self);
void EntityTableWithGlobe(Entity* self);
void EntityLifeMaxTank(Entity* self);
void EntityBlueFlameTable(Entity* self);
void EntityRelicContainer(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityRedEyeBust(Entity* self);
void EntityCannonLever(Entity* self);
void EntityCannon(Entity* self);
void EntityCannonShot(Entity* self);
void EntityCannonWall(Entity* self);
void EntityUnk31(Entity* self);
void func_us_801C09E8(Entity* self);
void func_us_801C1668(Entity* self);
void func_us_801C1758(Entity* self);
void func_us_801C1CC0(Entity* self);
void func_us_801C1E14(Entity* self);
void EntitySalemWitch(Entity* self);
void EntitySalemWitchGlow(Entity* self);
void EntitySalemWitchCurse(Entity* self);
void EntitySalemWitchTriboltLaunch(Entity* self);
void EntitySalemWitchTriboltProjectile(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakableNZ0,
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
    EntityPurpleBrickScrollingBackground,
    EntityLeftSecretRoomWall,
    EntityBottomSecretRoomFloor,
    EntitySecretWallDebris,
    EntityFloorTrap,
    EntityCtulhu,
    EntityCtulhuFireball,
    EntityCtulhuIceShockwave,
    EntityCtulhuDeath,
    EntityFireDemon,   // 1F
    EntityUnkId20,     // 20
    EntityUnkId21,     // 21
    EntityUnkId22,     // 22
    EntityLesserDemon, // 23
    func_us_801BCAB0,
    func_us_801BD7D0,
    func_us_801BF7B0,
    EntityTableWithGlobe,
    EntityLifeMaxTank,
    EntityBlueFlameTable,
    EntityRelicContainer,
    EntitySealedDoor,
    EntityRedEyeBust,
    EntityCannonLever,
    EntityCannon,
    EntityCannonShot,
    EntityCannonWall,
    EntityUnk31,
    func_us_801C09E8,
    func_us_801C1668,
    func_us_801C1758,
    func_us_801C1CC0,
    func_us_801C1E14,
    EntitySalemWitch,
    EntitySalemWitchGlow,
    EntitySalemWitchCurse,
    EntitySalemWitchTriboltLaunch,
    EntitySalemWitchTriboltProjectile,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0, PAL_NULL, 0x000};
#include "../e_init_common.h"
EInit g_EInitFloorTrap = {ANIMSET_OVL(3), 0, 75, 0x200, 0x005};
EInit g_EInitCtulhu = {ANIMSET_OVL(4), 0, 72, 0x209, 0x0E9};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(4), 0, 72, 0x209, 0x0EA};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(4), 44, 72, 0x209, 0x0EB};
EInit D_us_80180A20 = {ANIMSET_OVL(5), 1, 79, 0x21D, 0x04F};
EInit D_us_80180A2C = {ANIMSET_DRA(2), 1, 0, PAL_NULL, 0x050};
EInit D_us_80180A38 = {ANIMSET_OVL(6), 1, 76, 0x22D, 0x017};
EInit D_us_80180A44 = {ANIMSET_OVL(6), 25, 76, 0x22D, 0x019};
EInit D_us_80180A50 = {ANIMSET_DRA(9), 1, 0, 0x81B0, 0x01A};
EInit D_us_80180A5C = {ANIMSET_DRA(0), 0, 0, PAL_NULL, 0x018};
EInit D_us_80180A68 = {ANIMSET_OVL(1), 0, 0, PAL_NULL, 0x003};
EInit g_EInitEnemy3 = {ANIMSET_OVL(2), 0, 0, PAL_NULL, 0x003};
EInit g_EInitTableWithGlobe = {ANIMSET_OVL(7), 0, 75, 0x236, 0x005};
EInit g_EInitLifeMaxTank = {ANIMSET_OVL(8), 0, 79, 0x23A, 0x005};
EInit g_EInitPrizeContainer = {ANIMSET_OVL(9), 0, 83, 0x23E, 0x005};
EInit D_us_80180AA4 = {ANIMSET_OVL(10), 1, 72, 0x247, 0x0B6};
EInit D_us_80180AB0 = {ANIMSET_OVL(11), 1, 95, 0x260, 0x11C};
EInit D_us_80180ABC = {ANIMSET_OVL(11), 1, 95, 0x260, 0x002};
EInit D_us_80180AC8 = {ANIMSET_OVL(12), 0, 94, 0x270, 0x0E1};
EInit D_us_80180AD4 = {ANIMSET_OVL(12), 0, 94, 0x270, 0x005};
EInit D_us_80180AE0 = {ANIMSET_OVL(12), 0, 94, 0x270, 0x0E2};
EInit D_us_80180AEC = {ANIMSET_OVL(13), 1, 80, 0x24C, 0x0DD};
EInit D_us_80180AF8 = {ANIMSET_OVL(13), 0, 80, 0x24C, 0x0DE};
EInit D_us_80180B04 = {ANIMSET_OVL(14), 0, 92, 0x2EB, 0x0DF};
