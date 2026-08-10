// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno0.h"

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
void EntityHeartDrop(Entity* self);
void EntityEnemyBlood(Entity* self);
void EntityMessageBox(Entity* self);
void EntityDummy(Entity* self);
void EntityDummy(Entity* self);
void EntityBackgroundBlock(Entity* self);
void EntityLockCamera(Entity* self);
void EntityUnkId13(Entity* self);
void EntityExplosionVariants(Entity* self);
void EntityGreyPuff(Entity* self);
void EntityBackgroundPillar(Entity* self);
void EntityCorridorDecorator(Entity* self);
void EntityLongCorridorEye(Entity* self);
void EntityClockRoomController(Entity* self);
void EntityClockHands(Entity* self);
void EntityBirdcageDoor(Entity* self);
void EntityStatue(Entity* self);
void EntityStatueGear(Entity* self);
void EntityStoneDoor(Entity* self);
void EntityClockRoomUnused(Entity* self);
void EntityDummy(Entity* self);
void EntityGuardian(Entity* self);
void func_us_801D348C_from_are(Entity* self);
void EntityGuardianFireWave(Entity* self);
void EntityArmorLordUnk2(Entity* self);
void EntityArmorLordUnused(Entity* self);
void EntityFloorTrap(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityStoneSkull(Entity* self);
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
void EntityGorgon(Entity* self);
void func_us_801D068C(Entity* self);
void func_us_801D0CFC(Entity* self);
void func_us_801D136C(Entity* self);
void func_us_801D15C0(Entity* self);
void func_us_801D2038(Entity* self);
void func_us_801D1BF0(Entity* self);
void func_us_801D2264(Entity* self);
void func_us_801D21C8(Entity* self);
void EntityElevator(Entity* self);
void EntityElevatorPart(Entity* self);
void EntityPendulum(Entity* self);
void EntityClockTickSound(Entity* self);
void EntityPinkCavernsBlock(Entity* self);
void EntityMedusaHeadSpawner(Entity* self);
void EntityMedusaHeadBlue(Entity* self);
void EntityMedusaHeadYellow(Entity* self);
void EntitySealedDoor(Entity* self);

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
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityBackgroundPillar,
    EntityCorridorDecorator,
    EntityLongCorridorEye,
    EntityClockRoomController,
    EntityClockHands,
    EntityBirdcageDoor,
    EntityStatue,
    EntityStatueGear,
    EntityStoneDoor,
    EntityClockRoomUnused,
    EntityDummy,
    EntityGuardian,
    func_us_801D348C_from_are,
    EntityGuardianFireWave,
    EntityArmorLordUnk2,
    EntityArmorLordUnused,
    EntityFloorTrap,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityStoneSkull,
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
    EntityGorgon,
    func_us_801D068C,
    func_us_801D0CFC,
    func_us_801D136C,
    func_us_801D15C0,
    func_us_801D2038,
    func_us_801D1BF0,
    func_us_801D2264,
    func_us_801D21C8,
    EntityElevator,
    EntityElevatorPart,
    EntityPendulum,
    EntityClockTickSound,
    EntityPinkCavernsBlock,
    EntityMedusaHeadSpawner,
    EntityMedusaHeadBlue,
    EntityMedusaHeadYellow,
    EntitySealedDoor,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkIdVariant = {ANIMSET_OVL(5), 0, 36, 0, 0x003};
EInit g_EInitLockCameraVariant = {ANIMSET_DRA(2), 0, 72, 0, 0x05B};
EInit Unused_ShouldBeCommon = {ANIMSET_DRA(3), 0, 72, 0, 0x05C};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
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
EInit g_EInitElevator = {ANIMSET_OVL(12), 1, 72, 576, 0x005};
EInit g_EInitMedusaHead1 = {ANIMSET_OVL(13), 0, 95, 592, 0x12F};
EInit g_EInitMedusaHead2 = {ANIMSET_OVL(13), 0, 95, 593, 0x130};
// clang-format on
