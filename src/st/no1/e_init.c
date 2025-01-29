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
void EntityEnvTile(Entity* self);
void EntityUnkId12(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void NO1Unused_801B7D24(Entity* self);
void func_us_801B6490(Entity* self);
void func_us_801B7188(Entity* self);
void NO1Unused_801B7D2C(Entity* self);
void func_us_801B7D34(Entity* self);
void EntityChair(Entity* self);
void func_us_801B81E8(Entity* self);
void func_us_801B8430(Entity* self);
void func_us_801B84E4(Entity* self);
void func_us_801B8B00(Entity* self);
void EntityAxeKnightBlue(Entity* self);
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
void EntityWereskeleton(Entity* self);
void func_us_801CEA2C(Entity* self);
void func_us_801CE958(Entity* self);
void EntityBoneArcher(Entity* self);
void EntityBoneArcherArrow(Entity* self);
void EntityBoneMusket(Entity* self);
void func_us_801CF298(Entity* self);
void EntitySwordLord(Entity* self);
void func_us_801D04B8(Entity* self);
void EntityArmorLord(Entity* self);
void func_us_801D348C(Entity* self);
void EntityArmorLordFireWave(Entity* self);
void func_us_801D3700(Entity* self);
void func_us_801D1A94(Entity* self);
void EntitySpearGuard(Entity* self);
void func_us_801D42EC(Entity* self);
void func_us_801D4558(Entity* self);
void func_us_801D4950(Entity* self);
void EntitySkeletonApe(Entity* self);
void func_us_801D4F18(Entity* self);
void EntitySkeletonApeBarrel(Entity* self);
void func_us_801D544C(Entity* self);
void func_us_801C0B9C(Entity* self);
void func_us_801D4400(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void func_us_801B6198(Entity* self);
void EntityMistDoor(Entity* self);
void func_us_801C10F4(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    /* 0x00 */ func_us_801B5E20,
    /* 0x01 */ EntityExplosion,
    /* 0x02 */ EntityPrizeDrop,
    /* 0x03 */ EntityDamageDisplay,
    /* 0x04 */ OVL_EXPORT(EntityRedDoor),
    /* 0x05 */ EntityIntenseExplosion,
    /* 0x06 */ EntitySoulStealOrb,
    /* 0x07 */ EntityRoomForeground,
    /* 0x08 */ EntityStageNamePopup,
    /* 0x09 */ EntityEquipItemDrop,
    /* 0x0A */ EntityRelicOrb,
    /* 0x0B */ EntityHeartDrop,
    /* 0x0C */ EntityEnemyBlood,
    /* 0x0D */ EntityMessageBox,
    /* 0x0E */ EntityDummy,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityEnvTile,
    /* 0x11 */ EntityUnkId12,
    /* 0x12 */ EntityUnkId13,
    /* 0x13 */ EntityExplosionVariants,
    /* 0x14 */ EntityGreyPuff,
    /* 0x15 */ NO1Unused_801B7D24,
    /* 0x16 */ func_us_801B6490,
    /* 0x17 */ func_us_801B7188,
    /* 0x18 */ NO1Unused_801B7D2C,
    /* 0x19 */ func_us_801B7D34,
    /* 0x1A */ EntityChair,
    /* 0x1B */ func_us_801B81E8,
    /* 0x1C */ func_us_801B8430,
    /* 0x1D */ func_us_801B84E4,
    /* 0x1E */ func_us_801B8B00,
    /* 0x1F */ EntityAxeKnightBlue,
    /* 0x20 */ EntityAxeKnightThrowingAxe,
    /* 0x21 */ func_us_801CBA30,
    /* 0x22 */ InitializeUnkEntity,
    /* 0x23 */ func_us_801BE880,
    /* 0x24 */ func_us_801BEB54,
    /* 0x25 */ func_us_801BEE00,
    /* 0x26 */ func_us_801BF074,
    /* 0x27 */ func_us_801BA290,
    /* 0x28 */ func_us_801BCB34,
    /* 0x29 */ func_us_801BBD90,
    /* 0x2A */ func_us_801BB984,
    /* 0x2B */ func_us_801BA034,
    /* 0x2C */ func_us_801C05DC,
    /* 0x2D */ func_us_801C0A40,
    /* 0x2E */ func_us_801C01F0,
    /* 0x2F */ func_us_801BFA34,
    /* 0x30 */ func_us_801BFB40,
    /* 0x31 */ func_us_801B8F50,
    /* 0x32 */ func_us_801B9BE4,
    /* 0x33 */ func_us_801BB4C0,
    /* 0x34 */ func_us_801BF3F4,
    /* 0x35 */ func_us_801BDA0C,
    /* 0x36 */ func_us_801BD8AC,
    /* 0x37 */ func_us_801BDF9C,
    /* 0x38 */ func_us_801BE2C8,
    /* 0x39 */ func_us_801B8D30,
    /* 0x3A */ func_us_801B9028,
    /* 0x3B */ func_us_801B9304,
    /* 0x3C */ func_us_801B7CC4,
    /* 0x3D */ EntitySkeleton,
    /* 0x3E */ EntitySkeletonThrownBone,
    /* 0x3F */ EntitySkeletonPieces,
    /* 0x40 */ EntityWereskeleton,
    /* 0x41 */ func_us_801CEA2C,
    /* 0x42 */ func_us_801CE958,
    /* 0x43 */ EntityBoneArcher,
    /* 0x44 */ EntityBoneArcherArrow,
    /* 0x45 */ EntityBoneMusket,
    /* 0x46 */ func_us_801CF298,
    /* 0x47 */ EntitySwordLord,
    /* 0x48 */ func_us_801D04B8,
    /* 0x49 */ EntityArmorLord,
    /* 0x4A */ func_us_801D348C,
    /* 0x4B */ EntityArmorLordFireWave,
    /* 0x4C */ func_us_801D3700,
    /* 0x4D */ func_us_801D1A94,
    /* 0x4E */ EntitySpearGuard,
    /* 0x4F */ func_us_801D42EC,
    /* 0x50 */ func_us_801D4558,
    /* 0x51 */ func_us_801D4950,
    /* 0x52 */ EntitySkeletonApe,
    /* 0x53 */ func_us_801D4F18,
    /* 0x54 */ EntitySkeletonApeBarrel,
    /* 0x55 */ func_us_801D544C,
    /* 0x56 */ func_us_801C0B9C,
    /* 0x57 */ func_us_801D4400,
    /* 0x58 */ EntityMedusaHeadSpawner,
    /* 0x59 */ EntityMedusaHeadBlue,
    /* 0x5A */ EntityMedusaHeadYellow,
    /* 0x5B */ func_us_801B6198,
    /* 0x5C */ EntityMistDoor,
    /* 0x5D */ func_us_801C10F4};

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
EInit g_EInitWereskeleton = {ANIMSET_OVL(0x06), 0x01, 0x4E, 0x213, 0x03D};
EInit D_us_80180A88 = {ANIMSET_OVL(0x06), 0x00, 0x4E, 0x213, 0x03E};
EInit g_EInitBoneMusket = {ANIMSET_OVL(0x09), 0x00, 0x4C, 0x216, 0x066};
EInit D_us_80180AA0 = {ANIMSET_OVL(0x09), 0x00, 0x4C, 0x216, 0x067};
EInit g_EInitSwordLord = {ANIMSET_OVL(0x0A), 0x01, 0x50, 0x21A, 0x009};
EInit D_us_80180AB8 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x00A};
EInit g_EInitBoneArcher = {ANIMSET_OVL(0x07), 0x01, 0x4B, 0x215, 0x06C};
EInit D_us_80180AD0 = {ANIMSET_OVL(0x07), 0x00, 0x4B, 0x215, 0x06D};
EInit g_EInitArmorLord = {ANIMSET_OVL(0x0B), 0x01, 0x52, 0x21C, 0x022};
EInit D_us_80180AE8 = {ANIMSET_OVL(0x0B), 0x00, 0x52, 0x21C, 0x023};
EInit D_us_80180AF4 = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x000, 0x024};
EInit g_EInitSpearGuard = {ANIMSET_OVL(0x0C), 0x01, 0x53, 0x222, 0x05D};
EInit D_us_80180B0C = {ANIMSET_OVL(0x0C), 0x00, 0x53, 0x222, 0x060};
EInit D_us_80180B18 = {ANIMSET_OVL(0x0D), 0x01, 0x50, 0x228, 0x0B1};
EInit g_EInitSkeletonApe = {ANIMSET_OVL(0x0E), 0x01, 0x4F, 0x225, 0x053};
EInit D_us_80180B30 = {ANIMSET_OVL(0x0E), 0x28, 0x4F, 0x225, 0x054};
EInit D_us_80180B3C = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x181};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22B, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22C, 0x130};
