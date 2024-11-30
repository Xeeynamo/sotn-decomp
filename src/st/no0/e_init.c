// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void func_us_801C1854(Entity*);
void func_801B0AA4(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801CC8F8(Entity*);
void func_us_801CC750(Entity*);
void func_us_801CC9B4(Entity*);
void func_us_801CCC74(Entity*);
void EntityClockHands(Entity*);
void EntityBirdcageDoor(Entity*);
void EntityStatue(Entity*);
void EntityStatueGear(Entity*);
void EntityStoneDoor(Entity*);
void EntityClockRoomUnused(Entity*);
void EntityDummy(Entity*);
void func_us_801CFBE8(Entity*);
void func_us_801CF4A8(Entity*);
void func_us_801CF910(Entity*);
void EntityDiplocephalusTail(Entity*);
void EntityDiplocephalusFireball(Entity*);
void func_us_801D0718(Entity*);
void EntityOlroxDrool(Entity*);
void func_us_801C2184(Entity*);
void func_us_801C26B8(Entity*);
void func_us_801C27A4(Entity*);
void func_us_801C2A34(Entity*);
void func_us_801C2CD8(Entity*);
void func_us_801C2E7C(Entity*);
void EntitySkelerang(Entity*);
void EntitySkelerangBoomerang(Entity*);
void EntitySkelerangUnknown(Entity*);
void EntityPlateLord(Entity*);
void func_us_801D4324(Entity*);
void func_us_801D44A0(Entity*);
void func_us_801D4AA4(Entity*);
void func_us_801D542C(Entity*);
void func_us_801D4CAC(Entity*);
void EntityGhostEnemy(Entity*);
void EntityGhostEnemySpawner(Entity*);
void func_us_801D66F8(Entity*);
void EntitySlinger(Entity*);
void EntitySlingerRib(Entity*);
void EntitySlingerPieces(Entity*);
void func_us_801D8150(Entity*);
void func_us_801D8DF0(Entity*);
void func_us_801D8FFC(Entity*);
void func_us_801D91C4(Entity*);
void func_us_801D7DAC(Entity*);
void func_us_801C2B24(Entity*);
void EntityCtulhu(Entity*);
void EntityCtulhuFireball(Entity*);
void EntityCtulhuIceShockwave(Entity*);
void EntityCtulhuDeath(Entity*);
void EntityAxeKnight(Entity*);
void EntityAxeKnightThrowingAxe(Entity*);
void EntityExplosionPuffOpaque(Entity*);
void EntityOuijaTable(Entity*);
void EntityOuijaTableComponent(Entity*);
void EntityFleaMan(Entity*);
void EntitySkeleton(Entity*);
void EntitySkeletonThrownBone(Entity*);
void EntitySkeletonPieces(Entity*);
void EntityDummy(Entity*);
void EntityMagicallySealedDoor(Entity*);

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
    func_us_801C1854,
    func_801B0AA4,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801CC8F8,
    func_us_801CC750,
    func_us_801CC9B4,
    func_us_801CCC74,
    EntityClockHands,
    EntityBirdcageDoor,
    EntityStatue,
    EntityStatueGear,
    EntityStoneDoor,
    EntityClockRoomUnused,
    EntityDummy,
    func_us_801CFBE8,
    func_us_801CF4A8,
    func_us_801CF910,
    EntityDiplocephalusTail,
    EntityDiplocephalusFireball,
    func_us_801D0718,
    EntityOlroxDrool,
    func_us_801C2184,
    func_us_801C26B8,
    func_us_801C27A4,
    func_us_801C2A34,
    func_us_801C2CD8,
    func_us_801C2E7C,
    EntitySkelerang,
    EntitySkelerangBoomerang,
    EntitySkelerangUnknown,
    EntityPlateLord,
    func_us_801D4324,
    func_us_801D44A0,
    func_us_801D4AA4,
    func_us_801D542C,
    func_us_801D4CAC,
    EntityGhostEnemy,
    EntityGhostEnemySpawner,
    func_us_801D66F8,
    EntitySlinger,
    EntitySlingerRib,
    EntitySlingerPieces,
    func_us_801D8150,
    func_us_801D8DF0,
    func_us_801D8FFC,
    func_us_801D91C4,
    func_us_801D7DAC,
    func_us_801C2B24,
    EntityCtulhu,
    EntityCtulhuFireball,
    EntityCtulhuIceShockwave,
    EntityCtulhuDeath,
    EntityAxeKnight,
    EntityAxeKnightThrowingAxe,
    EntityExplosionPuffOpaque,
    EntityOuijaTable,
    EntityOuijaTableComponent,
    EntityFleaMan,
    EntitySkeleton,
    EntitySkeletonThrownBone,
    EntitySkeletonPieces,
    EntityDummy,
    EntityMagicallySealedDoor};

EInit OVL_EXPORT(
    EInitBreakable) = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(0x03), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180A88 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x005};
EInit D_us_80180AA0 = {ANIMSET_DRA(0x02), 0x00, 0x00, 0x000, 0x02C};
EInit D_us_80180AAC = {ANIMSET_OVL(0x05), 0x00, 0x24, 0x000, 0x003};
EInit D_us_80180AB8 = {ANIMSET_DRA(0x02), 0x00, 0x48, 0x000, 0x05B};
EInit D_us_80180AC4 = {ANIMSET_DRA(0x03), 0x00, 0x48, 0x000, 0x05C};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x002};
EInit D_us_80180ADC = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit g_EInitCommon = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit D_us_80180AF4 = {ANIMSET_OVL(0x0C), 0x00, 0x4A, 0x22E, 0x055};
EInit D_us_80180B00 = {ANIMSET_OVL(0x0C), 0x00, 0x4A, 0x22E, 0x056};
EInit D_us_80180B0C = {ANIMSET_OVL(0x0C), 0x00, 0x4A, 0x22E, 0x057};
EInit g_EInitDamageNum = {ANIMSET_DRA(0x00), 0x00, 0x00, 0x000, 0x003};
EInit D_us_80180B24 = {ANIMSET_OVL(0x09), 0x01, 0x4B, 0x20E, 0x010};
EInit g_EInitDiplocephalusFoot = {ANIMSET_OVL(0x09), 0x0C, 0x4B, 0x20E, 0x011};
EInit D_us_80180B3C = {ANIMSET_OVL(0x09), 0x08, 0x4B, 0x20E, 0x005};
EInit g_EInitDiplocephalusTail = {ANIMSET_OVL(0x09), 0x16, 0x4B, 0x20E, 0x012};
EInit g_EInitDiplocephalusFireball = {
    ANIMSET_OVL(0x0D), 0x00, 0x4E, 0x2C0, 0x013};
EInit g_EInitElevator = {ANIMSET_OVL(0x0B), 0x01, 0x48, 0x223, 0x005};
EInit g_EInitSkelerang = {ANIMSET_OVL(0x04), 0x01, 0x48, 0x228, 0x00B};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(0x04), 0x2B, 0x48, 0x228, 0x00C};
EInit g_EInitPlateLord = {ANIMSET_OVL(0x05), 0x01, 0x4C, 0x22B, 0x061};
EInit D_us_80180B90 = {ANIMSET_OVL(0x05), 0x16, 0x4C, 0x22B, 0x062};
EInit g_EInitGhostEnemy = {ANIMSET_OVL(0x06), 0x01, 0x4A, 0x200, 0x09C};
EInit D_us_80180BA8 = {ANIMSET_OVL(0x08), 0x00, 0x48, 0x201, 0x031};
EInit g_EInitSlinger = {ANIMSET_OVL(0x0A), 0x01, 0x49, 0x203, 0x0B2};
EInit g_EInitSlingerPieces = {ANIMSET_OVL(0x0A), 0x00, 0x49, 0x203, 0x002};
EInit g_EInitSlingerRib = {ANIMSET_OVL(0x0A), 0x16, 0x49, 0x203, 0x0B3};
EInit g_EInitCtulhu = {ANIMSET_OVL(0x0E), 0x00, 0x50, 0x238, 0x0E9};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(0x0E), 0x00, 0x50, 0x238, 0x0EA};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(0x0E), 0x2C, 0x50, 0x238, 0x0EB};
EInit g_EInitAxeKnight = {ANIMSET_OVL(0x07), 0x01, 0x48, 0x23F, 0x0F6};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(0x07), 0x2F, 0x48, 0x23D, 0x18F};
EInit g_EInitOuijaTable = {ANIMSET_OVL(0x02), 0x00, 0x4B, 0x241, 0x0C1};
EInit g_EInitOuijaTableComponent = {ANIMSET_OVL(0x02), 0x0, 0x4B, 0x241, 0x0C2};
EInit g_EInitFleaMan = {ANIMSET_OVL(0x0F), 0x00, 0x53, 0x204, 0x028};
EInit g_EInitSkeleton = {ANIMSET_OVL(0x18), 0x01, 0x50, 0x207, 0x04B};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(0x18), 0x00, 0x50, 0x207, 0x002};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(0x18), 0x15, 0x50, 0x207, 0x04C};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    0x0597, 0x0597, 0x0597, 0x0597, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0597, 0x0597, 0x06F3, 0x06F4, 0x0000, 0x0000, 0x031B, 0x031C,
    0x06F5, 0x06F6, 0x06F7, 0x06F8, 0x06F2, 0x045E, 0x047B, 0x047E,
};
