// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

void EntityBreakable(Entity* self);
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
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_us_801B3D8C(Entity* self);
void func_us_801B3F30(Entity* self);
void EntityFrozenShadeCrystal(Entity* self);
void func_us_801B41A4(Entity* self);
void func_us_801B4210(Entity* self);
void Entity3DBackgroundHouse(Entity* self);
void Entity3DHouseSpawner(Entity* self);
void func_us_801B4DA4(Entity* self);
void func_us_801B5750(Entity* self);
void func_us_801B5368(Entity* self);
void func_us_801B52B4(Entity* self);
void func_us_801B5FB8(Entity* self);
void func_us_801B68EC(Entity* self);
void func_us_801B65A4(Entity* self);
void EntityBigRedFireball(Entity* self);
void func_us_801B6E34(Entity* self);
void EntityOwlKnight(Entity* self);
void EntityOwl(Entity* self);
void EntityOwlKnightSword(Entity* self);
void EntityOwlTarget(Entity* self);
void EntityBloodyZombie(Entity* self);
void EntityBloodDrips(Entity* self);
void EntityBloodSplatter(Entity* self);
void func_us_801B72E8(Entity* self);
void func_us_801B5948(Entity* self);
void func_us_801B7580(Entity* self);
void EntitySealedDoor(Entity* self);
void EntityValhallaKnight(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void EntityHammer(Entity* self);
void EntityGurkhaBodyParts(Entity* self);
void EntityHammerWeapon(Entity* self);
void EntityGurkha(Entity* self);
void EntityGurkhaSword(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeSword(Entity* self);
void func_us_801CDDF4(Entity* self);
void func_us_801CEB08(Entity* self);
void func_us_801CEBDC(Entity* self);
void EntityBreakableDebris(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
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
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    func_us_801B3D8C,
    func_us_801B3F30,
    EntityFrozenShadeCrystal,
    func_us_801B41A4,
    func_us_801B4210,
    Entity3DBackgroundHouse,
    Entity3DHouseSpawner,
    func_us_801B4DA4,
    func_us_801B5750,
    func_us_801B5368,
    func_us_801B52B4,
    func_us_801B5FB8,
    func_us_801B68EC,
    func_us_801B65A4,
    EntityBigRedFireball,
    func_us_801B6E34,
    EntityOwlKnight,
    EntityOwl,
    EntityOwlKnightSword,
    EntityOwlTarget,
    EntityBloodyZombie,
    EntityBloodDrips,
    EntityBloodSplatter,
    func_us_801B72E8,
    func_us_801B5948,
    func_us_801B7580,
    EntitySealedDoor,
    EntityValhallaKnight,
    func_us_801C8954,
    func_us_801C8AAC,
    EntityHammer,
    EntityGurkhaBodyParts,
    EntityHammerWeapon,
    EntityGurkha,
    EntityGurkhaSword,
    EntityBlade,
    EntityBladeSword,
    func_us_801CDDF4,
    func_us_801CEB08,
    func_us_801CEBDC,
    EntityBreakableDebris,
};

EInit g_EInitBreakable = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, PAL_NONE, 0x002};
EInit D_us_80180844 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, PAL_NONE, 0x003};
EInit g_EInitSkelerang = {ANIMSET_OVL(0x01), 0x01, 0x48, PAL_SKELERANG, 0x00B};
EInit g_EInitSkelerangBoomerang = {
    ANIMSET_OVL(0x01), 0x2B, 0x48, PAL_SKELERANG, 0x00C};
EInit D_us_801808A4 = {ANIMSET_OVL(0x02), 0x0B, 0x00, PAL_NONE, 0x003};
EInit D_us_801808B0 = {ANIMSET_OVL(0x03), 0x01, 0x49, PAL_UNK_203, 0x003};
EInit g_EInitOwlKnight = {ANIMSET_OVL(0x08), 0x10, 0x49, PAL_OWL_KNIGHT, 0x014};
EInit g_EInitOwlKnightSword = {
    ANIMSET_OVL(0x08), 0x00, 0x49, PAL_OWL_KNIGHT_SWORD, 0x015};
EInit g_EInitOwl = {ANIMSET_OVL(0x08), 0x01, 0x49, PAL_OWL_KNIGHT, 0x016};
EInit g_EInitBloodyZombie = {
    ANIMSET_OVL(0x09), 0x01, 0x4A, PAL_BLOODY_ZOMBIE, 0x00D};
EInit D_us_801808EC = {ANIMSET_OVL(0x02), 0x0E, 0x00, PAL_NONE, 0x005};
EInit g_EInitValhallaKnight = {
    ANIMSET_OVL(0x05), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, 0x085};
EInit D_us_80180904 = {
    ANIMSET_OVL(0x05), 0x01, 0x4C, PAL_VALHALLA_KNIGHT, 0x003};
EInit D_us_80180910 = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, 0x086};
EInit D_us_8018091C = {ANIMSET_OVL(0x00), 0x00, 0x00, PAL_NONE, 0x087};
EInit D_us_80180928 = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_23E, 0x0BA};
EInit D_us_80180934 = {ANIMSET_OVL(0x06), 0x12, 0x4C, PAL_UNK_23E, 0x0BB};
EInit D_us_80180940 = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_23B, 0x0BC};
EInit D_us_8018094C = {ANIMSET_OVL(0x06), 0x14, 0x4C, PAL_UNK_23B, 0x0BD};
EInit g_EInitBlade = {ANIMSET_OVL(0x06), 0x02, 0x4C, PAL_UNK_238, 0x0BE};
EInit g_EInitBladeSword = {ANIMSET_OVL(0x06), 0x13, 0x4C, PAL_UNK_238, 0x0BF};
EInit D_us_80180970 = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x081};
EInit D_us_8018097C = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x002};
EInit D_us_80180988 = {ANIMSET_OVL(0x04), 0x00, 0x50, PAL_UNK_241, 0x082};
