// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo4.h"

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
void EntityUnkId16(Entity*);
void EntityUnkId17(Entity*);
void EntityUnkId18(Entity*);
void EntityUnkId19(Entity*);
void EntityUnkId1A(Entity*);
void EntityUnkId1B(Entity*);
void EntityUnkId1C(Entity*);
void EntityLifeUpSpawn(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,     EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay, EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,  EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop, EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,    EntityMessageBox,        EntityDummy,
    EntityDummy,         EntityBackgroundBlock,   EntityLockCamera,
    EntityUnkId13,       EntityExplosionVariants, EntityGreyPuff,
    EntityUnkId16,       EntityUnkId17,           EntityUnkId18,
    EntityUnkId19,       EntityUnkId1A,           EntityUnkId1B,
    EntityUnkId1C,       EntityLifeUpSpawn,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};

#include "../../st/e_init_common.h"

EInit g_EInitDoppleganger10 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_DOPPLEGANGER10};
EInit EInitReboundStone = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_DOPPLEGANGER10_REBOUND_STONE};
EInit EInitSubwpnKnife = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_DOPPLEGANGER_SUBWPN_KNIFE};
EInit D_us_80180434 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_DOPPLEGANGER10_UNK_102};
EInit D_us_80180440 = {ANIMSET_OVL(3), 0x00, 0x44, PAL_UNK_211, ENEMY_DOPPLEGANGER10_UNARMED_ATTACK_1};
EInit D_us_8018044C = {ANIMSET_OVL(4), 0x00, 0x45, PAL_UNK_210, ENEMY_DOPPLEGANGER10_UNARMED_ATTACK_2};
EInit EInitUnk17 = {ANIMSET_OVL(15), 0x4B, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
