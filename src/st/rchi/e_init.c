// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

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
void EntitySlogra(Entity* self);
void EntitySlograSpear(Entity* self);
void EntitySlograSpearProjectile(Entity* self);
void EntityGaibon(Entity* self);
void EntityGaibonLeg(Entity* self);
void EntitySmallGaibonProjectile(Entity* self);
void EntityLargeGaibonProjectile(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityDemonSwitchWall(Entity* self);
void EntityDemonSwitch(Entity* self);
void EntityBreakableWall(Entity* self);
void EntityBreakableWallDebris(Entity* self);
void EntityThornweed(Entity* self);
void EntityCorpseweed(Entity* self);
void EntityCorpseweedProjectile(Entity* self);
void EntityBat(Entity* self);

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
    EntitySlogra,
    EntitySlograSpear,
    EntitySlograSpearProjectile,
    EntityGaibon,
    EntityGaibonLeg,
    EntitySmallGaibonProjectile,
    EntityLargeGaibonProjectile,
    EntityBreakableDebris,
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityBat,
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
EInit g_EInitSlogra = {ANIMSET_OVL(3), 0, 72, 512, 0x0F3};
EInit D_us_80180600 = {ANIMSET_OVL(3), 0, 72, 512, 0x0F4};
EInit D_us_8018060C = {ANIMSET_OVL(3), 0, 72, 512, 0x0F5};
EInit g_EInitGaibon = {ANIMSET_OVL(4), 0, 76, 515, 0x0FE};
EInit D_us_80180624 = {ANIMSET_DRA(0), 0, 0, 0, 0x0FF};
EInit D_us_80180630 = {ANIMSET_DRA(0), 0, 0, 0, 0x100};
EInit D_us_8018063C = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit D_us_80180648 = {ANIMSET_OVL(2), 0, 0, 0, 0x005};
EInit g_EInitThornweed = {ANIMSET_OVL(5), 0, 76, 523, 0x09D};
EInit g_EInitCorpseweedUnused = {ANIMSET_OVL(5), 0, 76, 523, 0x09E};
EInit g_EInitCorpseweed = {ANIMSET_OVL(5), 0, 76, 523, 0x09F};
EInit D_us_80180678 = {ANIMSET_OVL(5), 0, 76, 523, 0x0A0};
EInit g_EInitBat = {ANIMSET_OVL(9), 0, 95, 576, 0x040};
// clang-format on
