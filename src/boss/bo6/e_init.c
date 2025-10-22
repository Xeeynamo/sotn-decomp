// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

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
void EntityRichter(Entity*);
void func_us_801A7DC0(Entity*);
void func_us_801A9084(Entity*);
void func_us_801A95F4(Entity*);
void func_us_801A9208(Entity*);
void func_us_801A9944(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakable,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    BO6_EntityRedDoor,
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
    BO6_EntityBackgroundBlock,
    BO6_EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityRichter,
    func_us_801A7DC0,
    func_us_801A9084,
    func_us_801A95F4,
    func_us_801A9208,
    func_us_801A9944,
};

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0, 0x0, 0};

#include "../../st/e_init_common.h"

EInit D_us_80180400 = {ANIMSET_DRA(0), 0, 0, 0, 0x133};
EInit D_us_8018040C = {ANIMSET_DRA(0), 0, 0, 0, 0x134};
EInit D_us_80180418 = {ANIMSET_DRA(0), 0, 0, 0, 0x135};
EInit D_us_80180424 = {ANIMSET_DRA(0), 0, 0, 0, 0x136};
EInit D_us_80180430 = {ANIMSET_DRA(0), 0, 0, 0, 0x137};
EInit D_us_8018043C = {ANIMSET_DRA(0), 0, 0, 0, 0x138};
EInit D_us_80180448 = {ANIMSET_DRA(0), 0, 0, 0, 0x139};
EInit D_us_80180454 = {ANIMSET_DRA(0), 0, 0, 0, 0x13A};
EInit D_us_80180460 = {ANIMSET_DRA(0), 0, 0, 0, 0x13B};
EInit D_us_8018046C = {ANIMSET_DRA(0), 0, 0, 0, 0x13C};
EInit D_us_80180478 = {ANIMSET_DRA(0), 0, 0, 0, 0x13D};
EInit D_us_80180484 = {ANIMSET_DRA(0), 0, 0, 0, 0x13E};
EInit D_us_80180490 = {ANIMSET_DRA(0), 0, 0, 0, 0x13F};
EInit D_us_8018049C = {ANIMSET_DRA(0), 0, 0, 0, 0x140};
EInit D_us_801804A8 = {ANIMSET_DRA(0), 0, 0, 0, 0x141};
EInit D_us_801804B4 = {ANIMSET_DRA(3), 0, 0, 0, 0x147};
EInit D_us_801804C0 = {ANIMSET_DRA(0), 0, 0, 0, 0x15D};
EInit D_us_801804CC = {ANIMSET_DRA(0), 0, 0, 0, 0x15C};
