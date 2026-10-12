// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

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
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void func_us_801A0BF4(Entity*);
void EntityStairSwitch(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void EntityClouds(Entity*);
void EntityBreakableWall(Entity*);
void EntityBreakableDebris(Entity*);
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
void EntitySkullLordEye(Entity*);
void EntitySkullLordPieces(Entity*);

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
    func_us_801A0BF4,
    EntityStairSwitch,
    EntitySecretStairs,
    EntityClockTower3D,
    EntityClouds,
    EntityBreakableWall,
    EntityBreakableDebris,
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
    EntitySkullLordEye,
    EntitySkullLordPieces,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};

#include "../e_init_common.h"

static EInit __unused__ = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitRTOPCommon = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitTombstone = {ANIMSET_OVL(5), 0x15, 0x4D, PAL_TOMBSTONE, ENEMY_TOMBSTONE};
EInit g_EInitYorick = {ANIMSET_OVL(6), 0x01, 0x56, PAL_YORICK, ENEMY_YORICK};
EInit g_EInitYorickSkull = {ANIMSET_OVL(6), 0x1E, 0x56, PAL_YORICK, ENEMY_YORICK_SKULL};
EInit g_EInitSkullLord = {ANIMSET_OVL(7), 0x01, 0x48, PAL_SKULL_LORD, ENEMY_SKULL_LORD};
EInit g_EInitSkullLordEffects = {ANIMSET_OVL(7), 0x01, 0x48, PAL_SKULL_LORD, ENEMY_INTERACTABLE};
