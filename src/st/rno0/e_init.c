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
void EntityGuardianSwordShadow(Entity* self);
void EntityGuardianFireWave(Entity* self);
void EntityGuardianUnk2(Entity* self);
void EntityGuardianUnused(Entity* self);
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
void EntityNovaSkeletonDeathParts(Entity* self);
void EntityHammer(Entity* self);
void EntityGurkhaBodyParts(Entity* self);
void EntityHammerWeapon(Entity* self);
void EntityGurkha(Entity* self);
void EntityGurkhaWeapon(Entity* self);
void EntityBlade(Entity* self);
void EntityBladeWeapon(Entity* self);
void EntitySubWeaponContainer(Entity* self);
void EntitySubWpnContGlass(Entity* self);
void EntityFallingLiquid(Entity* self);
void EntityBubbles(Entity* self);
void EntitySubwpnInContainer(Entity* self);
void EntityGorgon(Entity* self);
void EntityGorgonFront(Entity* self);
void EntityGorgonRear(Entity* self);
void EntityGorgonFoot(Entity* self);
void EntityGorgonHead(Entity* self);
void EntityGorgonSaddle(Entity* self);
void EntityGorgonTail(Entity* self);
void EntityGorgonAttack(Entity* self);
void EntityGorgonSnort(Entity* self);
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
    EntityGuardianSwordShadow,
    EntityGuardianFireWave,
    EntityGuardianUnk2,
    EntityGuardianUnused,
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
    EntityNovaSkeletonDeathParts,
    EntityHammer,
    EntityGurkhaBodyParts,
    EntityHammerWeapon,
    EntityGurkha,
    EntityGurkhaWeapon,
    EntityBlade,
    EntityBladeWeapon,
    EntitySubWeaponContainer,
    EntitySubWpnContGlass,
    EntityFallingLiquid,
    EntityBubbles,
    EntitySubwpnInContainer,
    EntityGorgon,
    EntityGorgonFront,
    EntityGorgonRear,
    EntityGorgonFoot,
    EntityGorgonHead,
    EntityGorgonSaddle,
    EntityGorgonTail,
    EntityGorgonAttack,
    EntityGorgonSnort,
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
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkIdVariant = {ANIMSET_OVL(5), 0x00, 0x24, PAL_NONE, ENEMY_COMMON};
EInit g_EInitLockCameraVariant = {ANIMSET_DRA(2), 0x00, 0x48, PAL_NONE, ENEMY_LOCK_CAMERA_VARIANT};
EInit Unused_ShouldBeCommon = {ANIMSET_DRA(3), 0x00, 0x48, PAL_NONE, ENEMY_UNK_5C};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitGuardian = {ANIMSET_OVL(3), 0x01, 0x52, PAL_GUARDIAN, ENEMY_GUARDIAN};
EInit g_EInitGuardianSwordShadow = {ANIMSET_OVL(3), 0x00, 0x52, PAL_GUARDIAN, ENEMY_GUARDIAN_SWORD_SHADOW};
EInit g_EInitGuardianTemp = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_GUARDIAN_UNK_18E};
EInit g_EInitFloorTrap = {ANIMSET_OVL(4), 0x00, 0x4B, PAL_FLOOR_TRAP, ENEMY_INTERACTABLE};
EInit g_EInitThornweed = {ANIMSET_OVL(5), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_THORNWEED};
EInit g_EInitCorpseweedUnused = {ANIMSET_OVL(5), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_UNUSED};
EInit g_EInitCorpseweed = {ANIMSET_OVL(5), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED};
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(5), 0x00, 0x50, PAL_THORNWEED_CORPSEWEED, ENEMY_CORPSEWEED_PROJECTILE};
EInit g_EInitStoneSkull = {ANIMSET_OVL(6), 0x00, 0x56, PAL_STONE_SKULL, ENEMY_STONE_SKULL};
EInit g_EInitJackOBones = {ANIMSET_OVL(7), 0x01, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES};
EInit g_EInitJackOBones2 = {ANIMSET_OVL(7), 0x00, 0x4A, PAL_JACK_O_BONES, ENEMY_PARTICLE};
EInit g_EInitJackOBones3 = {ANIMSET_OVL(7), 0x15, 0x4A, PAL_JACK_O_BONES, ENEMY_JACK_O_BONES_3};
EInit g_EInitNovaSkeleton = {ANIMSET_OVL(8), 0x01, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON};
EInit g_EInitNovaSkeleton2 = {ANIMSET_OVL(8), 0x00, 0x48, PAL_NOVA_SKELETON, ENEMY_NOVA_SKELETON_LASER};
EInit g_EInitHammer = {ANIMSET_OVL(9), 0x02, 0x57, PAL_HAMMER, ENEMY_HAMMER};
EInit g_EInitHammerWeapon = {ANIMSET_OVL(9), 0x12, 0x57, PAL_HAMMER, ENEMY_HAMMER_WEAPON};
EInit g_EInitGurkha = {ANIMSET_OVL(9), 0x02, 0x57, PAL_GURKHA, ENEMY_GURKHA};
EInit g_EInitGurkhaWeapon = {ANIMSET_OVL(9), 0x14, 0x57, PAL_GURKHA, ENEMY_GURKHA_WEAPON};
EInit g_EInitBlade = {ANIMSET_OVL(9), 0x02, 0x57, PAL_BLADE, ENEMY_BLADE};
EInit g_EInitBladeWeapon = {ANIMSET_OVL(9), 0x13, 0x57, PAL_BLADE, ENEMY_BLADE_WEAPON};
EInit g_EInitSubwpnCloche = {ANIMSET_OVL(10), 0x00, 0x4C, PAL_SUBWPN_CLOCHE, ENEMY_INTERACTABLE};
EInit g_EInitSubwpnClochePieces = {ANIMSET_OVL(10), 0x00, 0x4C, PAL_SUBWPN_CLOCHE, ENEMY_PARTICLE};
EInit g_EInitGorgon = {ANIMSET_OVL(11), 0x00, 0x4C, PAL_GORGON, ENEMY_GORGON};
EInit g_EInitGorgonHead = {ANIMSET_OVL(11), 0x00, 0x4C, PAL_GORGON, ENEMY_GORGON_HEAD};
EInit g_EInitGorgonAttack = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_GORGON_ATTACK};
EInit g_EInitElevator = {ANIMSET_OVL(12), 0x01, 0x48, PAL_ELEVATOR, ENEMY_INTERACTABLE};
EInit g_EInitMedusaHeadBlue = {ANIMSET_OVL(13), 0x00, 0x5F, PAL_MEDUSA_HEAD_BLUE, ENEMY_MEDUSA_HEAD_BLUE};
EInit g_EInitMedusaHeadYellow = {ANIMSET_OVL(13), 0x00, 0x5F, PAL_MEDUSA_HEAD_YELLOW, ENEMY_MEDUSA_HEAD_YELLOW};
// clang-format on
