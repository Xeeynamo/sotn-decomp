// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

void EntityBreakable(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityStageNamePopup(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityRelicOrb(Entity*);
void EntityPersistentItemDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801CC8F8(Entity*);
void func_us_801CC750(Entity*);
void func_us_801CC9B4(Entity*);
void EntityClockRoomController(Entity*);
void EntityClockHands(Entity*);
void EntityBirdcageDoor(Entity*);
void EntityStatue(Entity*);
void EntityStatueGear(Entity*);
void EntityStoneDoor(Entity*);
void EntityClockRoomUnused(Entity*);
void EntityDummy(Entity*);
void EntityDiplocephalus(Entity*);
void EntityDiplocephalusFoot(Entity*);
void EntityDiplocephalusLeg(Entity*);
void EntityDiplocephalusTail(Entity*);
void EntityDiplocephalusFireball(Entity*);
void EntityDiplocephalusTorso(Entity*);
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
void EntityMarionette(Entity*);
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
void EntitySealedDoor(Entity*);

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
    func_us_801CC8F8,
    func_us_801CC750,
    func_us_801CC9B4,
    EntityClockRoomController,
    EntityClockHands,
    EntityBirdcageDoor,
    EntityStatue,
    EntityStatueGear,
    EntityStoneDoor,
    EntityClockRoomUnused,
    EntityDummy,
    EntityDiplocephalus,
    EntityDiplocephalusFoot,
    EntityDiplocephalusLeg,
    EntityDiplocephalusTail,
    EntityDiplocephalusFireball,
    EntityDiplocephalusTorso,
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
    EntityMarionette,
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
    EntitySealedDoor,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit D_us_80180A88 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit D_us_80180AA0 = {ANIMSET_DRA(2), 0x00, 0x00, PAL_NONE, ENEMY_WHITE_DRAGON_FLAME_BREATH}; // unused
EInit D_us_80180AAC = {ANIMSET_OVL(5), 0x00, 0x24, PAL_NONE, ENEMY_COMMON}; // unused
EInit D_us_80180AB8 = {ANIMSET_DRA(2), 0x00, 0x48, PAL_NONE, ENEMY_LOCK_CAMERA_VARIANT}; // unused
EInit D_us_80180AC4 = {ANIMSET_DRA(3), 0x00, 0x48, PAL_NONE, ENEMY_UNK_5C}; // unused
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitStoneRose = {ANIMSET_OVL(12), 0x00, 0x4A, PAL_STONE_ROSE, ENEMY_STONE_ROSE};
EInit D_us_80180B00 = {ANIMSET_OVL(12), 0x00, 0x4A, PAL_STONE_ROSE, ENEMY_STONE_ROSE_SEED_1};
EInit D_us_80180B0C = {ANIMSET_OVL(12), 0x00, 0x4A, PAL_STONE_ROSE, ENEMY_STONE_ROSE_SEED_2};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDiplocephalus = {ANIMSET_OVL(9), 0x01, 0x4B, PAL_DIPLOCEPHALUS, ENEMY_DIPLOCEPHALUS};
EInit g_EInitDiplocephalusFoot = {ANIMSET_OVL(9), 0x0C, 0x4B, PAL_DIPLOCEPHALUS, ENEMY_DIPLOCEPHALUS_FOOT};
EInit D_us_80180B3C = {ANIMSET_OVL(9), 0x08, 0x4B, PAL_DIPLOCEPHALUS, ENEMY_INTERACTABLE};
EInit g_EInitDiplocephalusTail = {ANIMSET_OVL(9), 0x16, 0x4B, PAL_DIPLOCEPHALUS, ENEMY_DIPLOCEPHALUS_TAIL};
EInit g_EInitDiplocephalusFireball = {ANIMSET_OVL(13), 0x00, 0x4E, PAL_PUFF_OPAQUE_OFFSET, ENEMY_DIPLOCEPHALUS_FIREBALL};
EInit g_EInitElevator = {ANIMSET_OVL(11), 0x01, 0x48, PAL_ELEVATOR, ENEMY_INTERACTABLE};
EInit g_EInitSkelerang = {ANIMSET_OVL(4), 0x01, 0x48, PAL_SKELERANG, ENEMY_SKELERANG};
EInit g_EInitSkelerangBoomerang = {ANIMSET_OVL(4), 0x2B, 0x48, PAL_SKELERANG, ENEMY_SKELERANG_BOOMERANG};
EInit g_EInitPlateLord = {ANIMSET_OVL(5), 0x01, 0x4C, PAL_PLATE_LORD_UNK1, ENEMY_PLATE_LORD};
EInit D_us_80180B90 = {ANIMSET_OVL(5), 0x16, 0x4C, PAL_PLATE_LORD_UNK1, ENEMY_PLATE_LORD_UNK_62};
EInit g_EInitGhostEnemy = {ANIMSET_OVL(6), 0x01, 0x4A, PAL_GHOST, ENEMY_GHOST};
EInit g_EInitMarionette = {ANIMSET_OVL(8), 0x00, 0x48, PAL_MARIONETTE, ENEMY_MARIONETTE};
EInit g_EInitSlinger = {ANIMSET_OVL(10), 0x01, 0x49, PAL_SLINGER, ENEMY_SLINGER};
EInit g_EInitSlingerPieces = {ANIMSET_OVL(10), 0x00, 0x49, PAL_SLINGER, ENEMY_PARTICLE};
EInit g_EInitSlingerRib = {ANIMSET_OVL(10), 0x16, 0x49, PAL_SLINGER, ENEMY_SLINGER_RIB};
EInit g_EInitCtulhu = {ANIMSET_OVL(14), 0x00, 0x50, PAL_CTULHU, ENEMY_CTULHU};
EInit g_EInitCtulhuFireball = {ANIMSET_OVL(14), 0x00, 0x50, PAL_CTULHU, ENEMY_CTULHU_FIREBALL};
EInit g_EInitCtulhuIceShockwave = {ANIMSET_OVL(14), 0x2C, 0x50, PAL_CTULHU, ENEMY_CTULHU_ICE_SHOCKWAVE};
EInit g_EInitAxeKnight = {ANIMSET_OVL(7), 0x01, 0x48, PAL_AXE_KNIGHT, ENEMY_BLUE_AXE_KNIGHT};
EInit g_EInitAxeKnightAxe = {ANIMSET_OVL(7), 0x2F, 0x48, PAL_AXE_KNIGHT_AXE, ENEMY_BLUE_AXE_KNIGHT_AXE};
EInit g_EInitOuijaTable = {ANIMSET_OVL(2), 0x00, 0x4B, PAL_OUIJA_TABLE, ENEMY_OUIJA_TABLE};
EInit g_EInitOuijaTableComponent = {ANIMSET_OVL(2), 0x00, 0x4B, PAL_OUIJA_TABLE, ENEMY_OUIJA_TABLE_COMPONENT};
EInit g_EInitFleaMan = {ANIMSET_OVL(15), 0x00, 0x53, PAL_FLEA_MAN, ENEMY_FLEA_MAN};
EInit g_EInitSkeleton = {ANIMSET_OVL(24), 0x01, 0x50, PAL_SKELETON, ENEMY_SKELETON};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(24), 0x00, 0x50, PAL_SKELETON, ENEMY_PARTICLE};
EInit g_EInitSkeletonBone = {ANIMSET_OVL(24), 0x15, 0x50, PAL_SKELETON, ENEMY_SKELETON_BONE};
