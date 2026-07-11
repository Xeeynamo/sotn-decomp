// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

void OVL_EXPORT(EntityBreakable)(Entity* self);
void EntityExplosion(Entity* self);
void EntityPrizeDrop(Entity* self);
void OVL_EXPORT(EntityDamageDisplay)(Entity* self);
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
void OVL_EXPORT(EntityDummy)(Entity* self);
void OVL_EXPORT(EntityDummy)(Entity* self);
void OVL_EXPORT(EntityBackgroundBlock)(Entity* self);
void OVL_EXPORT(EntityLockCamera)(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void func_us_801CC8F8_from_no0(Entity* self);
void func_us_801CC750_from_no0(Entity* self);
void func_us_801CC9B4_from_no0(Entity* self);
void EntityClockRoomController(Entity* self);
void EntityClockHands(Entity* self);
void EntityBirdcageDoor(Entity* self);
void EntityStatue(Entity* self);
void EntityStatueGear(Entity* self);
void EntityStoneDoor(Entity* self);
void OVL_EXPORT(Unused801C2338)(Entity* self);
void OVL_EXPORT(EntityDummy)(Entity* self);
void EntityArmorLord(Entity* self);
void func_us_801D348C_from_are(Entity* self);
void EntityArmorLordFireWave(Entity* self);
void func_us_801D3700_from_are(Entity* self);
void OVL_EXPORT(Unused801C2C50)(Entity* self);
void EntityFloorTrap(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void func_us_801C7F24(Entity* self);
void EntityJackOBones(Entity* self);
void EntityJackOBonesDeathParts(Entity* self);
void EntityJackOBonesJack(Entity* self);
void EntityNovaSkeleton(Entity* self);
void EntityNovaLaser(Entity* self);
void EntityNovaLaserPulse(Entity* self);
void EntityBladeSoldierDeathParts(Entity* self);
void EntityHammer(Entity* self);
void EntityGurkhaBodyParts(Entity* self);
void EntityHammerWeapon(Entity* self);
void EntityGurkha(Entity* self);
void EntityGurkhaWeapon(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeWeapon(Entity* self);
void EntitySubWeaponContainer(Entity* self);
void EntitySubWpnContGlass(Entity* self);
void func_801C7654(Entity* self);
void func_801C77B8(Entity* self);
void func_801C7884(Entity* self);
void func_us_801CFEA0(Entity* self);
void func_us_801D068C(Entity* self);
void func_us_801D0CFC(Entity* self);
void func_us_801D136C(Entity* self);
void func_us_801D15C0(Entity* self);
void func_us_801D2038(Entity* self);
void func_us_801D1BF0(Entity* self);
void func_us_801D2264(Entity* self);
void func_us_801D21C8(Entity* self);
void func_us_801C2184_from_no0(Entity* self);
void EntityUnkId1B(Entity* self);
void func_us_801C2A34_from_no0(Entity* self);
void func_us_801C2B24_from_no0(Entity* self);
void func_us_801B7104(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void EntitySealedDoor(Entity* self);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
    EntityExplosion,
    EntityPrizeDrop,
    OVL_EXPORT(EntityDamageDisplay),
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
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityDummy),
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801CC8F8_from_no0,
    func_us_801CC750_from_no0,
    func_us_801CC9B4_from_no0,
    EntityClockRoomController,
    EntityClockHands,
    EntityBirdcageDoor,
    EntityStatue,
    EntityStatueGear,
    EntityStoneDoor,
    OVL_EXPORT(Unused801C2338),
    OVL_EXPORT(EntityDummy),
    EntityArmorLord,
    func_us_801D348C_from_are,
    EntityArmorLordFireWave,
    func_us_801D3700_from_are,
    OVL_EXPORT(Unused801C2C50),
    EntityFloorTrap,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    func_us_801C7F24,
    EntityJackOBones,
    EntityJackOBonesDeathParts,
    EntityJackOBonesJack,
    EntityNovaSkeleton,
    EntityNovaLaser,
    EntityNovaLaserPulse,
    EntityBladeSoldierDeathParts,
    EntityHammer,
    EntityGurkhaBodyParts,
    EntityHammerWeapon,
    EntityGurkha,
    EntityGurkhaWeapon,
    EntityBlade,
    EntityBladeWeapon,
    EntitySubWeaponContainer,
    EntitySubWpnContGlass,
    func_801C7654,
    func_801C77B8,
    func_801C7884,
    func_us_801CFEA0,
    func_us_801D068C,
    func_us_801D0CFC,
    func_us_801D136C,
    func_us_801D15C0,
    func_us_801D2038,
    func_us_801D1BF0,
    func_us_801D2264,
    func_us_801D21C8,
    func_us_801C2184_from_no0,
    EntityUnkId1B,
    func_us_801C2A34_from_no0,
    func_us_801C2B24_from_no0,
    func_us_801B7104,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
    EntitySealedDoor,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit OVL_EXPORT(EInitObtainable) = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit OVL_EXPORT(EInitParticle) = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit OVL_EXPORT(EInitSpawner) = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit OVL_EXPORT(EInitInteractable) = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit OVL_EXPORT(EInitUnkId13) = {ANIMSET_OVL(5), 0, 36, 0, 0x003};
EInit OVL_EXPORT(EInitLockCamera) = {ANIMSET_DRA(2), 0, 72, 0, 0x05B};
EInit Unused_ShouldBeCommon = {ANIMSET_DRA(3), 0, 72, 0, 0x05C};
EInit OVL_EXPORT(EInitDamageNum) = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit D_us_80180AA4 = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit OVL_EXPORT(EInitCommon) = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit D_us_80180ABC = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitGuardian = {ANIMSET_OVL(3), 1, 82, 518, 0x18C};
EInit D_us_80180AD4 = {ANIMSET_OVL(3), 0, 82, 518, 0x18D};
EInit D_us_80180AE0 = {ANIMSET_OVL(0), 0, 0, 0, 0x18E};
EInit D_us_80180AEC = {ANIMSET_OVL(4), 0, 75, 578, 0x005};
EInit g_EInitThornweed = {ANIMSET_OVL(5), 0, 80, 537, 0x09D};
EInit g_EInitCorpseweedUnused = {ANIMSET_OVL(5), 0, 80, 537, 0x09E};
EInit g_EInitCorpseweed = {ANIMSET_OVL(5), 0, 80, 537, 0x09F};
EInit D_us_80180B1C = {ANIMSET_OVL(5), 0, 80, 537, 0x0A0};
EInit g_EInitStoneSkull = {ANIMSET_OVL(6), 0, 86, 527, 0x180};
EInit g_EInitJackOBones = {ANIMSET_OVL(7), 1, 74, 528, 0x074};
EInit D_us_80180B40 = {ANIMSET_OVL(7), 0, 74, 528, 0x002};
EInit D_us_80180B4C = {ANIMSET_OVL(7), 21, 74, 528, 0x075};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(8), 1, 72, 532, 0x07E};
EInit D_us_80180B64 = {ANIMSET_OVL(8), 0, 72, 532, 0x07F};
EInit g_EInitHammer = {ANIMSET_OVL(9), 2, 87, 547, 0x0BA};
EInit D_us_80180B7C = {ANIMSET_OVL(9), 18, 87, 547, 0x0BB};
EInit g_EInitGurkha = {ANIMSET_OVL(9), 2, 87, 544, 0x0BC};
EInit D_us_80180B94 = {ANIMSET_OVL(9), 20, 87, 544, 0x0BD};
EInit g_EInitBlade = {ANIMSET_OVL(9), 2, 87, 541, 0x0BE};
EInit D_us_80180BAC = {ANIMSET_OVL(9), 19, 87, 541, 0x0BF};
EInit D_us_80180BB8 = {ANIMSET_OVL(10), 0, 76, 550, 0x005};
EInit D_us_80180BC4 = {ANIMSET_OVL(10), 0, 76, 550, 0x002};
EInit g_EInitGorgon = {ANIMSET_OVL(11), 0, 76, 560, 0x01F};
EInit D_us_80180BDC = {ANIMSET_OVL(11), 0, 76, 560, 0x020};
EInit D_us_80180BE8 = {ANIMSET_DRA(0), 0, 0, 0, 0x021};
EInit D_us_80180BF4 = {ANIMSET_OVL(12), 1, 72, 576, 0x005};
EInit g_EInitMedusaHead1 = {ANIMSET_OVL(13), 0, 95, 592, 0x12F};
EInit g_EInitMedusaHead2 = {ANIMSET_OVL(13), 0, 95, 593, 0x130};
// clang-format on
