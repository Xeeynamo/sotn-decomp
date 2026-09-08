// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

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
void func_us_801B7D24(Entity* self);
void func_us_801B6490(Entity* self);
void func_us_801B7188(Entity* self);
void func_us_801B7D2C(Entity* self);
void EntityMouse(Entity* self);
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
void EntitySwordLordAttack(Entity* self);
void EntityArmorLord(Entity* self);
void EntityArmorLordSwordShadow(Entity* self);
void EntityArmorLordFireWave(Entity* self);
void EntityArmorLordUnk2(Entity* self);
void EntityArmorLordUnused(Entity* self);
void EntitySpearGuard(Entity* self);
void EntitySpearGuardBlock(Entity* self);
void func_us_801D4558(Entity* self);
void func_us_801D4950(Entity* self);
void EntitySkeletonApe(Entity* self);
void EntitySkeletonApePunch(Entity* self);
void EntitySkeletonApeBarrel(Entity* self);
void EntityThrownBarrel(Entity* self);
void func_us_801C0B9C(Entity* self);
void EntityThrownSpear(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityMistDoor(Entity* self);
#ifndef VERSION_PSP
void func_us_801C10F4(Entity* self);
#endif

PfnEntityUpdate EntityUpdates[] = {
    /* 0x01 */ EntityBreakable,
    /* 0x02 */ EntityExplosion,
    /* 0x03 */ EntityPrizeDrop,
    /* 0x04 */ EntityDamageDisplay,
    /* 0x05 */ EntityRedDoor,
    /* 0x06 */ EntityIntenseExplosion,
    /* 0x07 */ EntitySoulStealOrb,
    /* 0x08 */ EntityRoomForeground,
    /* 0x09 */ EntityStageNamePopup,
    /* 0x0A */ EntityEquipItemDrop,
    /* 0x0B */ EntityRelicOrb,
    /* 0x0C */ EntityPersistentItemDrop,
    /* 0x0D */ EntityEnemyBlood,
    /* 0x0E */ EntityMessageBox,
    /* 0x0F */ EntityDummy,
    /* 0x10 */ EntityDummy,
    /* 0x11 */ EntityBackgroundBlock,
    /* 0x12 */ EntityLockCamera,
    /* 0x13 */ EntityUnkId13,
    /* 0x14 */ EntityExplosionVariants,
    /* 0x15 */ EntityGreyPuff,
    /* 0x16 */ func_us_801B7D24,
    /* 0x17 */ func_us_801B6490,
    /* 0x18 */ func_us_801B7188,
    /* 0x19 */ func_us_801B7D2C,
    /* 0x1A */ EntityMouse,
    /* 0x1B */ EntityChair,
    /* 0x1C */ func_us_801B81E8,
    /* 0x1D */ func_us_801B8430,
    /* 0x1E */ func_us_801B84E4,
    /* 0x1F */ func_us_801B8B00,
    /* 0x20 */ EntityAxeKnightBlue,
    /* 0x21 */ EntityAxeKnightThrowingAxe,
    /* 0x22 */ func_us_801CBA30,
    /* 0x23 */ InitializeUnkEntity,
    /* 0x24 */ func_us_801BE880,
    /* 0x25 */ func_us_801BEB54,
    /* 0x26 */ func_us_801BEE00,
    /* 0x27 */ func_us_801BF074,
    /* 0x28 */ func_us_801BA290,
    /* 0x29 */ func_us_801BCB34,
    /* 0x2A */ func_us_801BBD90,
    /* 0x2B */ func_us_801BB984,
    /* 0x2C */ func_us_801BA034,
    /* 0x2D */ func_us_801C05DC,
    /* 0x2E */ func_us_801C0A40,
    /* 0x2F */ func_us_801C01F0,
    /* 0x30 */ func_us_801BFA34,
    /* 0x31 */ func_us_801BFB40,
    /* 0x32 */ func_us_801B8F50,
    /* 0x33 */ func_us_801B9BE4,
    /* 0x34 */ func_us_801BB4C0,
    /* 0x35 */ func_us_801BF3F4,
    /* 0x36 */ func_us_801BDA0C,
    /* 0x37 */ func_us_801BD8AC,
    /* 0x38 */ func_us_801BDF9C,
    /* 0x39 */ func_us_801BE2C8,
    /* 0x3A */ func_us_801B8D30,
    /* 0x3B */ func_us_801B9028,
    /* 0x3C */ func_us_801B9304,
    /* 0x3D */ func_us_801B7CC4,
    /* 0x3E */ EntitySkeleton,
    /* 0x3F */ EntitySkeletonThrownBone,
    /* 0x40 */ EntitySkeletonPieces,
    /* 0x41 */ EntityWereskeleton,
    /* 0x42 */ func_us_801CEA2C,
    /* 0x43 */ func_us_801CE958,
    /* 0x44 */ EntityBoneArcher,
    /* 0x45 */ EntityBoneArcherArrow,
    /* 0x46 */ EntityBoneMusket,
    /* 0x47 */ func_us_801CF298,
    /* 0x48 */ EntitySwordLord,
    /* 0x49 */ EntitySwordLordAttack,
    /* 0x4A */ EntityArmorLord,
    /* 0x4B */ EntityArmorLordSwordShadow,
    /* 0x4C */ EntityArmorLordFireWave,
    /* 0x4D */ EntityArmorLordUnk2,
    /* 0x4E */ EntityArmorLordUnused,
    /* 0x4F */ EntitySpearGuard,
    /* 0x50 */ EntitySpearGuardBlock,
    /* 0x51 */ func_us_801D4558,
    /* 0x52 */ func_us_801D4950,
    /* 0x53 */ EntitySkeletonApe,
    /* 0x54 */ EntitySkeletonApePunch,
    /* 0x55 */ EntitySkeletonApeBarrel,
    /* 0x56 */ EntityThrownBarrel,
    /* 0x57 */ func_us_801C0B9C,
    /* 0x58 */ EntityThrownSpear,
    /* 0x59 */ EntityMedusaHeadSpawner,
    /* 0x5A */ EntityMedusaHeadBlue,
    /* 0x5B */ EntityMedusaHeadYellow,
    /* 0x5C */ EntityBreakableDebris,
    /* 0x5D */ EntityMistDoor,
#ifndef VERSION_PSP
    /* 0x5E */ func_us_801C10F4,
#endif
};

EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit D_us_80180974 = {ANIMSET_OVL(0x05), 0x00, 0x24, 0x000, 0x003}; // unused
EInit D_us_80180980 = {ANIMSET_DRA(0x02), 0x00, 0x48, 0x000, 0x05B}; // unused
EInit D_us_8018098C = {ANIMSET_DRA(3), 0x00, 0x48, 0x000, 0x05C};    // unused
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x001};
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
EInit D_us_80180A28 = {ANIMSET_OVL(0x01), 0x4A, 0x00, 0x000, 0x002}; // unused
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
EInit g_EInitSwordLordAttack = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x00A};
EInit g_EInitBoneArcher = {ANIMSET_OVL(0x07), 0x01, 0x4B, 0x215, 0x06C};
EInit g_EInitBoneArcherArrow = {ANIMSET_OVL(0x07), 0x00, 0x4B, 0x215, 0x06D};
EInit g_EInitArmorLord = {ANIMSET_OVL(0x0B), 0x01, 0x52, 0x21C, 0x022};
EInit g_EInitArmorLordSwordShadow = {
    ANIMSET_OVL(0x0B), 0x00, 0x52, 0x21C, 0x023};
EInit g_EInitArmorLordTemp = {ANIMSET_OVL(0x00), 0x00, 0x00, 0x000, 0x024};
EInit g_EInitSpearGuard = {ANIMSET_OVL(0x0C), 0x01, 0x53, 0x222, 0x05D};
EInit g_EInitThrownSpear = {ANIMSET_OVL(0x0C), 0x00, 0x53, 0x222, 0x060};
EInit D_us_80180B18 = {ANIMSET_OVL(0x0D), 0x01, 0x50, 0x228, 0x0B1};
EInit g_EInitSkeletonApe = {ANIMSET_OVL(0x0E), 0x01, 0x4F, 0x225, 0x053};
EInit g_EInitSkeletonApeBarrel = {ANIMSET_OVL(0x0E), 0x28, 0x4F, 0x225, 0x054};
EInit g_EInitSkeletonApePunch = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x181};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22B, 0x12F};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(0x0F), 0x00, 0x56, 0x22C, 0x130};
