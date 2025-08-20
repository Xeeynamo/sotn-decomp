// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

void OVL_EXPORT(EntityBreakable)(Entity*);
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
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801A0BF4(Entity*);
void EntityStairSwitch(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void EntityClouds(Entity*);
void EntityBreakableWall(Entity*);
void OVL_EXPORT(EntityBreakableDebris)(Entity*);
void EntityTriangleElevator(Entity*);
void EntityLionLamp(Entity*);
void func_us_801A21F8(Entity*);
void EntityTriggerBeforeCastleWarp(Entity*);
void func_us_801A1940(Entity*);
void EntityYorick(Entity*);
void EntityYorickSkull(Entity*);
void EntitySkeletonPieces(Entity*);
void EntityTombstone(Entity*);
void EntitySkullLord(Entity*);
void EntitySkullLordOutline(Entity*);
void EntitySkullLordFlames(Entity*);
void EntitySkullLordPieces(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    OVL_EXPORT(EntityBreakable),
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
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    func_us_801A0BF4,
    EntityStairSwitch,
    EntitySecretStairs,
    EntityClockTower3D,
    EntityClouds,
    EntityBreakableWall,
    OVL_EXPORT(EntityBreakableDebris),
    EntityTriangleElevator,
    EntityLionLamp,
    func_us_801A21F8,
    EntityTriggerBeforeCastleWarp,
    func_us_801A1940,
    EntityYorick,
    EntityYorickSkull,
    EntitySkeletonPieces,
    EntityTombstone,
    EntitySkullLord,
    EntitySkullLordOutline,
    EntitySkullLordFlames,
    EntitySkullLordPieces,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0, 0x0, 0};

#include "../e_init_common.h"

static EInit __unused__ = {ANIMSET_OVL(1), 0, 0, 0x0, 3};
EInit g_EInitRTOPCommon = {ANIMSET_OVL(2), 0, 0, 0x0, 5};
EInit g_EInitTombstone = {ANIMSET_OVL(5), 21, 0x4D, 0x208, 0x71};
EInit g_EInitSkeletonPieces = {ANIMSET_OVL(6), 1, 0x56, 0x20A, 0x78};
EInit D_us_801805E4 = {ANIMSET_OVL(6), 0x1E, 0x56, 0x20A, 0x79};
EInit g_EInitSkullLord = {ANIMSET_OVL(7), 1, 0x48, 0x20B, 0x105};

EInit D_us_801805FC = {ANIMSET_OVL(7), 1, 0x48, 0x20B, 0x5};
