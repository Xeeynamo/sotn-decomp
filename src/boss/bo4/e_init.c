// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

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
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void OVL_EXPORT(EntityLockCamera)(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityUnkId16(Entity*);
void EntityUnkId17(Entity*);
void EntityUnkId18(Entity*);
void EntityUnkId19(Entity*);
void EntityUnkId1A(Entity*);
void EntityUnkId1B(Entity*);
void EntityUnkId1C(Entity*);
void EntityLifeUpSpawn(Entity*);

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
    OVL_EXPORT(EntityBackgroundBlock),
    OVL_EXPORT(EntityLockCamera),
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityUnkId16,
    EntityUnkId17,
    EntityUnkId18,
    EntityUnkId19,
    EntityUnkId1A,
    EntityUnkId1B,
    EntityUnkId1C,
    EntityLifeUpSpawn,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0x00, 0x000, 0};

#include "../../st/e_init_common.h"

EInit EInitUnk16 = {ANIMSET_DRA(0), 0, 0, 0, 0xFD};
EInit EInitReboundStone = {ANIMSET_DRA(0), 0, 0, 0, 0x101};
EInit EInitSubwpnKnife = {ANIMSET_DRA(0), 0, 0, 0, 0x12B};
EInit D_us_80180434 = {ANIMSET_DRA(0), 0, 0, 0, 0x102};
EInit D_us_80180440 = {ANIMSET_OVL(3), 0, 0x44, 0x211, 0x103};
EInit D_us_8018044C = {ANIMSET_OVL(4), 0, 0x45, 0x210, 0x104};
EInit EInitUnk17 = {ANIMSET_OVL(15), 0x4B, 0, 0, 5};
