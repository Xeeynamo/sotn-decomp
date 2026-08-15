// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

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
void func_us_801A68AC(Entity* self);
void func_us_801A700C(Entity* self);
void func_us_801B7CC4_from_no1(Entity* self);
void EntityParanthropus(Entity* self);
void EntityParanthropusBoneHitbox(Entity* self);
void EntityParanthropusSkull(Entity* self);
void EntityParanthropusThrownBone(Entity* self);
void func_us_801C7F24_from_rno0(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesDeathParts(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityBladeSoldierDeathParts(Entity* self);
void func_us_801B8F50_from_no1(Entity* self);
void func_us_801BE880_from_no1(Entity* self);
void func_us_801BEB54_from_no1(Entity* self);
void func_us_801BEE00_from_no1(Entity* self);
void func_us_801BF074_from_no1(Entity* self);
void func_us_801A86A8(Entity* self);
void EntityBreakableDebris(Entity* self);
void func_us_801A9BEC(Entity* self);
void func_us_801B9028_from_no1(Entity* self);
void func_us_80198A18_from_rbo4(Entity* self);
void func_us_801A9A8C(Entity* self);

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
    func_us_801A68AC,
    func_us_801A700C,
    func_us_801B7CC4_from_no1,
    EntityParanthropus,
    EntityParanthropusBoneHitbox,
    EntityParanthropusSkull,
    EntityParanthropusThrownBone,
    func_us_801C7F24_from_rno0,
    EntityJackOBones,
    EntityJackOBonesDeathParts,
    EntityJackOBonesJack,
    EntityNovaSkeleton,
    EntityNovaLaser,
    EntityNovaLaserPulse,
    EntityBladeSoldierDeathParts,
    func_us_801B8F50_from_no1,
    func_us_801BE880_from_no1,
    func_us_801BEB54_from_no1,
    func_us_801BEE00_from_no1,
    func_us_801BF074_from_no1,
    func_us_801A86A8,
    EntityBreakableDebris,
    func_us_801A9BEC,
    func_us_801B9028_from_no1,
    func_us_80198A18_from_rbo4,
    func_us_801A9A8C,
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
EInit g_EInitParanthropus = {ANIMSET_OVL(3), 1, 76, 512, 0x0D3};
EInit g_EInitParanthropusBoneHitbox = {ANIMSET_OVL(0), 0, 0, 0, 0x0D4};
EInit g_EInitParanthropusThrownBone = {ANIMSET_OVL(3), 54, 76, 512, 0x0D5};
EInit g_EInitStoneSkull = {ANIMSET_OVL(4), 0, 78, 515, 0x180};
EInit g_EInitJackOBones = {ANIMSET_OVL(5), 1, 74, 524, 0x074};
EInit D_us_8018070C = {ANIMSET_OVL(5), 0, 74, 524, 0x002};
EInit D_us_80180718 = {ANIMSET_OVL(5), 21, 74, 524, 0x075};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(6), 1, 72, 532, 0x07E};
EInit D_us_80180730 = {ANIMSET_OVL(6), 0, 72, 532, 0x07F};
EInit D_us_8018073C = {ANIMSET_OVL(8), 1, 79, 537, 0x005};
EInit D_us_80180748 = {ANIMSET_OVL(2), 75, 0, 0, 0x005};
EInit D_us_80180754 = {ANIMSET_DRA(0), 0, 0, 0, 0x000};
EInit D_us_80180760 = {ANIMSET_OVL(2), 102, 0, 0, 0x005};
EInit D_us_8018076C = {ANIMSET_OVL(11), 0, 72, 564, 0x003};
EInit D_us_80180778 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitUnused80180784 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit D_us_80180790 = {ANIMSET_OVL(2), 92, 0, 0, 0x005};
// clang-format on
