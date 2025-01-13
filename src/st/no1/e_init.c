// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

void func_us_801B5E20(Entity* self);
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
void func_us_801B4CC4(Entity* self);
void EntityUnkId12(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801B7D24(Entity* self);
void func_us_801B6490(Entity* self);
void func_us_801B7188(Entity* self);
void func_us_801B7D2C(Entity* self);
void func_us_801B7D34(Entity* self);
void func_us_801B8068(Entity* self);
void func_us_801B81E8(Entity* self);
void func_us_801B8430(Entity* self);
void func_us_801B84E4(Entity* self);
void func_us_801B8B00(Entity* self);
void func_us_801CAE04(Entity* self);
void EntityAxeKnightThrowingAxe(Entity* self);
void func_us_801CBA30(Entity* self);
void InitializeUnkEntity(Entity* self);
void func_us_801BE880(Entity* self);
void func_us_801BEB54(Entity* self);
void func_us_801BEE00(Entity* self);
void func_us_801BF074(Entity* self);
void func_us_801BA290(Entity* self);
void func_us_801BCB34(Entity* self);
void func_us_801BBD90(Entity* self);
void func_us_801BB984(Entity* self);
void func_us_801BA034(Entity* self);
void func_us_801C05DC(Entity* self);
void func_us_801C0A40(Entity* self);
void func_us_801C01F0(Entity* self);
void func_us_801BFA34(Entity* self);
void func_us_801BFB40(Entity* self);
void func_us_801B8F50(Entity* self);
void func_us_801B9BE4(Entity* self);
void func_us_801BB4C0(Entity* self);
void func_us_801BF3F4(Entity* self);
void func_us_801BDA0C(Entity* self);
void func_us_801BD8AC(Entity* self);
void func_us_801BDF9C(Entity* self);
void func_us_801BE2C8(Entity* self);
void func_us_801B8D30(Entity* self);
void func_us_801B9028(Entity* self);
void func_us_801B9304(Entity* self);
void func_us_801B7CC4(Entity* self);
void EntitySkeleton(Entity* self);
void EntitySkeletonThrownBone(Entity* self);
void EntitySkeletonPieces(Entity* self);
void func_us_801CDE20(Entity* self);
void func_us_801CEA2C(Entity* self);
void func_us_801CE958(Entity* self);
void EntityBoneArcher(Entity* self);
void EntityBoneArcherArrow(Entity* self);
void func_us_801CEB28(Entity* self);
void func_us_801CF298(Entity* self);
void func_us_801CF850(Entity* self);
void func_us_801D04B8(Entity* self);
void func_us_801D2D00(Entity* self);
void func_us_801D348C(Entity* self);
void func_us_801D18BC(Entity* self);
void func_us_801D3700(Entity* self);
void func_us_801D1A94(Entity* self);
void EntitySpearGuard(Entity* self);
void func_us_801D42EC(Entity* self);
void func_us_801D4558(Entity* self);
void func_us_801D4950(Entity* self);
void func_us_801D49E4(Entity* self);
void func_us_801D4F18(Entity* self);
void func_us_801D5040(Entity* self);
void func_us_801D544C(Entity* self);
void func_us_801C0B9C(Entity* self);
void func_us_801D4400(Entity* self);
void func_us_801D563C(Entity* self);
void func_us_801D582C(Entity* self);
void func_us_801D5808(Entity* self);
void func_us_801B6198(Entity* self);
void func_us_801D5A10(Entity* self);
void func_us_801C10F4(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    func_us_801B5E20,
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
    func_us_801B4CC4,
    EntityUnkId12,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801B7D24,
    func_us_801B6490,
    func_us_801B7188,
    func_us_801B7D2C,
    func_us_801B7D34,
    func_us_801B8068,
    func_us_801B81E8,
    func_us_801B8430,
    func_us_801B84E4,
    func_us_801B8B00,
    func_us_801CAE04,
    EntityAxeKnightThrowingAxe,
    func_us_801CBA30,
    InitializeUnkEntity,
    func_us_801BE880,
    func_us_801BEB54,
    func_us_801BEE00,
    func_us_801BF074,
    func_us_801BA290,
    func_us_801BCB34,
    func_us_801BBD90,
    func_us_801BB984,
    func_us_801BA034,
    func_us_801C05DC,
    func_us_801C0A40,
    func_us_801C01F0,
    func_us_801BFA34,
    func_us_801BFB40,
    func_us_801B8F50,
    func_us_801B9BE4,
    func_us_801BB4C0,
    func_us_801BF3F4,
    func_us_801BDA0C,
    func_us_801BD8AC,
    func_us_801BDF9C,
    func_us_801BE2C8,
    func_us_801B8D30,
    func_us_801B9028,
    func_us_801B9304,
    func_us_801B7CC4,
    EntitySkeleton,
    EntitySkeletonThrownBone,
    EntitySkeletonPieces,
    func_us_801CDE20,
    func_us_801CEA2C,
    func_us_801CE958,
    EntityBoneArcher,
    EntityBoneArcherArrow,
    func_us_801CEB28,
    func_us_801CF298,
    func_us_801CF850,
    func_us_801D04B8,
    func_us_801D2D00,
    func_us_801D348C,
    func_us_801D18BC,
    func_us_801D3700,
    func_us_801D1A94,
    EntitySpearGuard,
    func_us_801D42EC,
    func_us_801D4558,
    func_us_801D4950,
    func_us_801D49E4,
    func_us_801D4F18,
    func_us_801D5040,
    func_us_801D544C,
    func_us_801C0B9C,
    func_us_801D4400,
    func_us_801D563C,
    func_us_801D582C,
    func_us_801D5808,
    func_us_801B6198,
    func_us_801D5A10,
    func_us_801C10F4};

EInit D_us_80180938 = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit D_us_8018095C = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit D_us_80180974 = {ANIMSET_OVL(0x05), 0x00, 0x24, 0x000, 0x003};
EInit D_us_80180980 = {ANIMSET_DRA(0x02), 0x00, 0x48, 0x000, 0x05B};
EInit D_us_8018098C = {ANIMSET_DRA(0x03), 0x00, 0x48, 0x000, 0x05C};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitUnkId12 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit D_us_801809C8 = {ANIMSET_OVL(0x01), 0x4B, 0x00, 0x000, 0x005};
EInit D_us_801809D4 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitAxeKnight = {ANIMSET_OVL(0x03), 0x01, 0x48, 0x200, 0x006};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(0x03), 0x2F, 0x48, 0x200, 0x007};
EInit D_us_801809F8 = {ANIMSET_OVL(0x01), 0x40, 0x00, 0x000, 0x005};
EInit D_us_80180A04 = {ANIMSET_OVL(0x01), 0x4A, 0x00, 0x000, 0x005};
EInit D_us_80180A10 = {ANIMSET_OVL(0x01), 0x5C, 0x00, 0x000, 0x005};
EInit D_us_80180A1C = {ANIMSET_OVL(0x04), 0x01, 0x4A, 0x207, 0x005};
EInit D_us_80180A28 = {ANIMSET_OVL(0x01), 0x4A, 0x00, 0x000, 0x002};
EInit D_us_80180A34 = {ANIMSET_OVL(0x01), 0x67, 0x00, 0x000, 0x003};
EInit D_us_80180A40 = {ANIMSET_OVL(0x01), 0x66, 0x00, 0x000, 0x005};
EInit D_us_80180A4C = {ANIMSET_OVL(0x08), 0x00, 0x48, 0x20A, 0x003};
EInit g_EInitSkeleton = {ANIMSET_OVL(0x05), 0x01, 0x4D, 0x212, 0x04B};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(0x05), 0x00, 0x4D, 0x212, 0x002};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(0x05), 0x15, 0x4D, 0x212, 0x04C};
EInit D_us_80180A7C = {ANIMSET_OVL(0x06), 0x01, 0x4E, 0x213, 0x03D};
EInit D_us_80180A88 = {ANIMSET_OVL(0x06), 0x00, 0x4E, 0x213, 0x03E};
EInit D_us_80180A94 = {ANIMSET_OVL(0x09), 0x00, 0x4C, 0x216, 0x066};
EInit D_us_80180AA0 = {ANIMSET_OVL(0x09), 0x00, 0x4C, 0x216, 0x067};
EInit D_us_80180AAC = {ANIMSET_OVL(0x0A), 0x01, 0x50, 0x21A, 0x009};
EInit D_us_80180AB8 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x00A};
EInit D_us_80180AC4 = {ANIMSET_OVL(0x07), 0x01, 0x4B, 0x215, 0x06C};
EInit D_us_80180AD0 = {ANIMSET_OVL(0x07), 0x00, 0x4B, 0x215, 0x06D};
EInit D_us_80180ADC = {ANIMSET_OVL(0x0B), 0x01, 0x52, 0x21C, 0x022};
EInit D_us_80180AE8 = {ANIMSET_OVL(0x0B), 0x00, 0x52, 0x21C, 0x023};
EInit D_us_80180AF4 = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x000, 0x024};
EInit D_us_80180B00 = {ANIMSET_OVL(0x0C), 0x01, 0x53, 0x222, 0x05D};
EInit D_us_80180B0C = {ANIMSET_OVL(0x0C), 0x00, 0x53, 0x222, 0x060};
EInit D_us_80180B18 = {ANIMSET_OVL(0x0D), 0x01, 0x50, 0x228, 0x0B1};
EInit D_us_80180B24 = {ANIMSET_OVL(0x0E), 0x01, 0x4F, 0x225, 0x053};
EInit D_us_80180B30 = {ANIMSET_OVL(0x0E), 0x28, 0x4F, 0x225, 0x054};
EInit D_us_80180B3C = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x181};
EInit D_us_80180B48 = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22B, 0x12F};
EInit D_us_80180B54 = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22C, 0x130};
