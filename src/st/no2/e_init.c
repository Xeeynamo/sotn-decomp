// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

void func_us_801B3754(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void func_us_801BAEF4(Entity* self);
void EntityIntenseExplosion(Entity* self);
void func_us_801C7508(Entity* self);
void func_us_801C7D4C(Entity* self);
void func_us_801C1EB8(Entity* self);
void EntityEquipItemDrop(Entity* self);
void EntityRelicOr(Entity* self);
void EntityHeartDrop(Entity* self);
void func_us_801C789C(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void func_us_801B34D0(Entity* self);
void func_us_801B3598(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_us_801B3D8C(Entity* self);
void func_us_801B3F30(Entity* self);
void func_us_801B4148(Entity* self);
void func_us_801B41A4(Entity* self);
void func_us_801B4210(Entity* self);
void func_us_801B4A50(Entity* self);
void func_us_801B4960(Entity* self);
void func_us_801B4DA4(Entity* self);
void func_us_801B5750(Entity* self);
void func_us_801B5368(Entity* self);
void func_us_801B52B4(Entity* self);
void func_us_801B5FB8(Entity* self);
void func_us_801B68EC(Entity* self);
void func_us_801B65A4(Entity* self);
void EntityBigRedFireball(Entity* self);
void func_us_801B6E34(Entity* self);
void func_us_801C58DC(Entity* self);
void func_us_801C4614(Entity* self);
void func_us_801C6B3C(Entity* self);
void func_us_801C6C1C(Entity* self);
void func_us_801C3C50(Entity* self);
void func_us_801C4408(Entity* self);
void func_us_801C3594(Entity* self);
void func_us_801B72E8(Entity* self);
void func_us_801B5948(Entity* self);
void func_us_801B7580(Entity* self);
void func_us_801B7980(Entity* self);
void func_us_801C8168(Entity* self);
void func_us_801C8954(Entity* self);
void func_us_801C8AAC(Entity* self);
void func_us_801C9CBC(Entity* self);
void func_us_801CA874(Entity* self);
void func_us_801CABD8(Entity* self);
void func_us_801CAF6C(Entity* self);
void func_us_801CBD50(Entity* self);
void func_us_801CC360(Entity* self);
void func_us_801CD1D8(Entity* self);
void func_us_801CDDF4(Entity* self);
void func_us_801CEB08(Entity* self);
void func_us_801CEBDC(Entity* self);
void func_us_801B3A94(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    /* 0x00 */ func_us_801B3754,
    /* 0x01 */ EntityExplosion,
    /* 0x02 */ EntityPrizeDrop,
    /* 0x03 */ EntityDamageDisplay,
    /* 0x04 */ func_us_801BAEF4,
    /* 0x05 */ EntityIntenseExplosion,
    /* 0x06 */ func_us_801C7508,
    /* 0x07 */ func_us_801C7D4C,
    /* 0x08 */ func_us_801C1EB8,
    /* 0x09 */ EntityEquipItemDrop,
    /* 0x0A */ EntityRelicOrb,
    /* 0x0B */ EntityHeartDrop,
    /* 0x0C */ func_us_801C789C,
    /* 0x0D */ EntityMessageBox,
    /* 0x0E */ EntityDummy,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ func_us_801B34D0,
    /* 0x11 */ func_us_801B3598,
    /* 0x12 */ EntityUnkId13,
    /* 0x13 */ EntityExplosionVariants,
    /* 0x14 */ EntityGreyPuff,
    /* 0x15 */ EntitySkelerang,
    /* 0x16 */ EntitySkelerangBoomerang,
    /* 0x17 */ EntitySkelerangUnknown,
    /* 0x18 */ func_us_801B3D8C,
    /* 0x19 */ func_us_801B3F30,
    /* 0x1A */ func_us_801B4148,
    /* 0x1B */ func_us_801B41A4,
    /* 0x1C */ func_us_801B4210,
    /* 0x1D */ func_us_801B4A50,
    /* 0x1E */ func_us_801B4960,
    /* 0x1F */ func_us_801B4DA4,
    /* 0x20 */ func_us_801B5750,
    /* 0x21 */ func_us_801B5368,
    /* 0x22 */ func_us_801B52B4,
    /* 0x23 */ func_us_801B5FB8,
    /* 0x24 */ func_us_801B68EC,
    /* 0x25 */ func_us_801B65A4,
    /* 0x26 */ EntityBigRedFireball,
    /* 0x27 */ func_us_801B6E34,
    /* 0x28 */ func_us_801C58DC,
    /* 0x29 */ func_us_801C4614,
    /* 0x2A */ func_us_801C6B3C,
    /* 0x2B */ func_us_801C6C1C,
    /* 0x2C */ func_us_801C3C50,
    /* 0x2D */ func_us_801C4408,
    /* 0x2E */ func_us_801C3594,
    /* 0x2F */ func_us_801B72E8,
    /* 0x30 */ func_us_801B5948,
    /* 0x31 */ func_us_801B7580,
    /* 0x32 */ func_us_801B7980,
    /* 0x33 */ func_us_801C8168,
    /* 0x34 */ func_us_801C8954,
    /* 0x35 */ func_us_801C8AAC,
    /* 0x36 */ func_us_801C9CBC,
    /* 0x37 */ func_us_801CA874,
    /* 0x38 */ func_us_801CABD8,
    /* 0x39 */ func_us_801CAF6C,
    /* 0x3A */ func_us_801CBD50,
    /* 0x3B */ func_us_801CC360,
    /* 0x3C */ func_us_801CD1D8,
    /* 0x3D */ func_us_801CDDF4,
    /* 0x3E */ func_us_801CEB08,
    /* 0x3F */ func_us_801CEBDC,
    /* 0x40 */ func_us_801B3A94,
};

EInit D_us_80180820 = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180844 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180868 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
EInit D_us_80180874 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitSkelerang = {ANIMSET_OVL(0x01), 0x01, 0x48, 0x200, 0x00B};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(0x01), 0x2B, 0x48, 0x200, 0x00C};
EInit D_us_801808A4 = {ANIMSET_OVL(0x02), 0x0B, 0x00, 0x000, 0x003};
EInit D_us_801808B0 = {ANIMSET_OVL(0x03), 0x01, 0x49, 0x203, 0x003};
EInit D_us_801808BC = {ANIMSET_OVL(0x08), 0x10, 0x49, 0x21C, 0x014};
EInit D_us_801808C8 = {ANIMSET_OVL(0x08), 0x00, 0x49, 0x2CB, 0x015};
EInit D_us_801808D4 = {ANIMSET_OVL(0x08), 0x01, 0x49, 0x21C, 0x016};
EInit g_EInitBloodyZombie = {ANIMSET_OVL(0x09), 0x01, 0x4A, 0x223, 0x00D};
EInit D_us_801808EC = {ANIMSET_OVL(0x02), 0x0E, 0x00, 0x000, 0x005};
EInit D_us_801808F8 = {ANIMSET_OVL(0x05), 0x01, 0x4C, 0x207, 0x085};
EInit D_us_80180904 = {ANIMSET_OVL(0x05), 0x01, 0x4C, 0x207, 0x003};
EInit D_us_80180910 = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x000, 0x086};
EInit D_us_8018091C = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x000, 0x087};
EInit D_us_80180928 = {ANIMSET_OVL(0x06), 0x02, 0x4C, 0x23E, 0x0BA};
EInit D_us_80180934 = {ANIMSET_OVL(0x06), 0x12, 0x4C, 0x23E, 0x0BB};
EInit D_us_80180940 = {ANIMSET_OVL(0x06), 0x02, 0x4C, 0x23B, 0x0BC};
EInit D_us_8018094C = {ANIMSET_OVL(0x06), 0x14, 0x4C, 0x23B, 0x0BD};
EInit D_us_80180958 = {ANIMSET_OVL(0x06), 0x02, 0x4C, 0x238, 0x0BE};
EInit D_us_80180964 = {ANIMSET_OVL(0x06), 0x13, 0x4C, 0x238, 0x0BF};
EInit D_us_80180970 = {ANIMSET_OVL(0x04), 0x00, 0x50, 0x241, 0x081};
EInit D_us_8018097C = {ANIMSET_OVL(0x04), 0x00, 0x50, 0x241, 0x002};
EInit D_us_80180988 = {ANIMSET_OVL(0x04), 0x00, 0x50, 0x241, 0x082};
