// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

void EntityUnkBreakable(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void EntityDamageDisplay(Entity* self);
void DAI_EntityRedDoor(Entity* self);
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
void DAI_EntityBackgroundBlock(Entity* self);
void DAI_EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801C0BA4(Entity* self);
void func_us_801D97D0(Entity* self);
void func_us_801D9F5C(Entity* self);
void func_us_801C0F8C(Entity* self);
void func_us_801C1184(Entity* self);
void func_us_801C1298(Entity* self);
void func_us_801C1EE4(Entity* self);
void func_us_801C2068(Entity* self);
void func_us_801C220C(Entity* self);
void EntityClouds(Entity* self);
void func_us_801C34FC(Entity* self);
void func_us_801C23A4(Entity* self);
void func_us_801C3164(Entity* self);
void func_us_801C2534(Entity* self);
void func_us_801C2CD4(Entity* self);
void func_us_801C2FF0(Entity* self);
void func_us_801C1E18(Entity* self);
void func_us_801D1204(Entity* self);
void func_us_801D1C24(Entity* self);
void func_us_801D1D00(Entity* self);
void func_us_801D2908(Entity* self);
void func_us_801D2CFC(Entity* self);
void func_us_801D2444(Entity* self);
void func_us_801C3644(Entity* self);
void func_us_801C3D44(Entity* self);
void func_us_801C3850(Entity* self);
void func_us_801C379C(Entity* self);
void func_us_801C3ED8(Entity* self);
void func_us_801D2FA4(Entity* self);
void func_us_801D36EC(Entity* self);
void EntitySkeletonPieces(Entity* self);
void func_us_801D37C4(Entity* self);
void func_us_801D3A40(Entity* self);
void EntityBat(Entity* self);
void func_us_801D3FD8(Entity* self);
void func_us_801D43BC(Entity* self);
void EntitySkelerang(Entity* self);
void EntitySkelerangBoomerang(Entity* self);
void EntitySkelerangUnknown(Entity* self);
void func_us_801D56F4(Entity* self);
void func_us_801D636C(Entity* self);
void func_us_801D64A0(Entity* self);
void func_us_801D6FC8(Entity* self);
void func_us_801D70A0(Entity* self);
void func_us_801D3BD4(Entity* self);
void EntityMagicallySealedDoor(Entity* self);
void func_801A8328(Entity* self);
void DAI_EntityCutscene(Entity* self);
void func_us_801C5920(Entity* self);
void func_us_801C5B88(Entity* self);
void EntityMistDoor(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    /* 0x00 */ EntityUnkBreakable,
    /* 0x04 */ EntityExplosion,
    /* 0x08 */ EntityPrizeDrop,
    /* 0x0C */ EntityDamageDisplay,
    /* 0x10 */ DAI_EntityRedDoor,
    /* 0x14 */ EntityIntenseExplosion,
    /* 0x18 */ EntitySoulStealOrb,
    /* 0x1C */ EntityRoomForeground,
    /* 0x20 */ EntityStageNamePopup,
    /* 0x24 */ EntityEquipItemDrop,
    /* 0x28 */ EntityRelicOrb,
    /* 0x2C */ EntityHeartDrop,
    /* 0x30 */ EntityEnemyBlood,
    /* 0x34 */ EntityMessageBox,
    /* 0x38 */ EntityDummy,
    /* 0x3C */ EntityDummy,
    /* 0x40 */ DAI_EntityBackgroundBlock,
    /* 0x44 */ DAI_EntityLockCamera,
    /* 0x48 */ EntityUnkId13,
    /* 0x4C */ EntityExplosionVariants,
    /* 0x50 */ EntityGreyPuff,
    /* 0x54 */ func_us_801C0BA4,
    /* 0x58 */ func_us_801D97D0,
    /* 0x5C */ func_us_801D9F5C,
    /* 0x60 */ func_us_801C0F8C,
    /* 0x64 */ func_us_801C1184,
    /* 0x68 */ func_us_801C1298,
    /* 0x6C */ func_us_801C1EE4,
    /* 0x70 */ func_us_801C2068,
    /* 0x74 */ func_us_801C220C,
    /* 0x78 */ EntityClouds,
    /* 0x7C */ func_us_801C34FC,
    /* 0x80 */ func_us_801C23A4,
    /* 0x84 */ func_us_801C3164,
    /* 0x88 */ func_us_801C2534,
    /* 0x8C */ func_us_801C2CD4,
    /* 0x90 */ func_us_801C2FF0,
    /* 0x94 */ func_us_801C1E18,
    /* 0x98 */ func_us_801D1204,
    /* 0x9C */ func_us_801D1C24,
    /* 0xA0 */ func_us_801D1D00,
    /* 0xA4 */ func_us_801D2908,
    /* 0xA8 */ func_us_801D2CFC,
    /* 0xAC */ func_us_801D2444,
    /* 0xB0 */ func_us_801C3644,
    /* 0xB4 */ func_us_801C3D44,
    /* 0xB8 */ func_us_801C3850,
    /* 0xBC */ func_us_801C379C,
    /* 0xC0 */ func_us_801C3ED8,
    /* 0xC4 */ func_us_801D2FA4,
    /* 0xC8 */ func_us_801D36EC,
    /* 0xCC */ EntitySkeletonPieces,
    /* 0xD0 */ func_us_801D37C4,
    /* 0xD4 */ func_us_801D3A40,
    /* 0xD8 */ EntityBat,
    /* 0xDC */ func_us_801D3FD8,
    /* 0xE0 */ func_us_801D43BC,
    /* 0xE4 */ EntitySkelerang,
    /* 0xE8 */ EntitySkelerangBoomerang,
    /* 0xEC */ EntitySkelerangUnknown,
    /* 0xF0 */ func_us_801D56F4,
    /* 0xF4 */ func_us_801D636C,
    /* 0xF8 */ func_us_801D64A0,
    /* 0xFC */ func_us_801D6FC8,
    /* 0x100 */ func_us_801D70A0,
    /* 0x104 */ func_us_801D3BD4,
    /* 0x108 */ EntityMagicallySealedDoor,
    /* 0x10C */ func_801A8328,
    /* 0x110 */ DAI_EntityCutscene,
    /* 0x114 */ func_us_801C5920,
    /* 0x118 */ func_us_801C5B88,
    /* 0x11C */ EntityMistDoor,
};
