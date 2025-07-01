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
void func_us_801C2B3C(Entity* self);
void func_us_801C32C4(Entity* self);
void func_us_801C3538(Entity* self);
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
    func_us_801B3754,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    func_us_801BAEF4,
    EntityIntenseExplosion,
    func_us_801C7508,
    func_us_801C7D4C,
    func_us_801C1EB8,
    EntityEquipItemDrop,
    EntityRelicOrb,
    EntityHeartDrop,
    func_us_801C789C,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    func_us_801B34D0,
    func_us_801B3598,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801C2B3C,
    func_us_801C32C4,
    func_us_801C3538,
    func_us_801B3D8C,
    func_us_801B3F30,
    func_us_801B4148,
    func_us_801B41A4,
    func_us_801B4210,
    func_us_801B4A50,
    func_us_801B4960,
    func_us_801B4DA4,
    func_us_801B5750,
    func_us_801B5368,
    func_us_801B52B4,
    func_us_801B5FB8,
    func_us_801B68EC,
    func_us_801B65A4,
    EntityBigRedFireball,
    func_us_801B6E34,
    func_us_801C58DC,
    func_us_801C4614,
    func_us_801C6B3C,
    func_us_801C6C1C,
    func_us_801C3C50,
    func_us_801C4408,
    func_us_801C3594,
    func_us_801B72E8,
    func_us_801B5948,
    func_us_801B7580,
    func_us_801B7980,
    func_us_801C8168,
    func_us_801C8954,
    func_us_801C8AAC,
    func_us_801C9CBC,
    func_us_801CA874,
    func_us_801CABD8,
    func_us_801CAF6C,
    func_us_801CBD50,
    func_us_801CC360,
    func_us_801CD1D8,
    func_us_801CDDF4,
    func_us_801CEB08,
    func_us_801CEBDC,
    func_us_801B3A94,
};

EInit D_us_80180820 = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180844 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit D_us_80180850 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180868 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
EInit D_us_80180874 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit D_us_8018088C = {ANIMSET_OVL(0x01), 0x01, 0x48, 0x200, 0x00B};
EInit D_us_80180898 = {ANIMSET_OVL(0x01), 0x2B, 0x48, 0x200, 0x00C};
EInit D_us_801808A4 = {ANIMSET_OVL(0x02), 0x0B, 0x00, 0x000, 0x003};
EInit D_us_801808B0 = {ANIMSET_OVL(0x03), 0x01, 0x49, 0x203, 0x003};
EInit D_us_801808BC = {ANIMSET_OVL(0x08), 0x10, 0x49, 0x21C, 0x014};
EInit D_us_801808C8 = {ANIMSET_OVL(0x08), 0x00, 0x49, 0x2CB, 0x015};
EInit D_us_801808D4 = {ANIMSET_OVL(0x08), 0x01, 0x49, 0x21C, 0x016};
EInit D_us_801808E0 = {ANIMSET_OVL(0x09), 0x01, 0x4A, 0x223, 0x00D};
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