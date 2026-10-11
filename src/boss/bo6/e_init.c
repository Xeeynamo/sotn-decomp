// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

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
void EntityRichter(Entity*);
void func_us_801A7DC0(Entity*);
void func_us_801A9084(Entity*);
void func_us_801A95F4(Entity*);
void func_us_801A9208(Entity*);
void func_us_801A9944(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    EntityBreakable,     EntityExplosion,         EntityPrizeDrop,
    EntityDamageDisplay, EntityRedDoor,           EntityIntenseExplosion,
    EntitySoulStealOrb,  EntityRoomForeground,    EntityStageNamePopup,
    EntityEquipItemDrop, EntityRelicOrb,          EntityPersistentItemDrop,
    EntityEnemyBlood,    EntityMessageBox,        EntityDummy,
    EntityDummy,         EntityBackgroundBlock,   EntityLockCamera,
    EntityUnkId13,       EntityExplosionVariants, EntityGreyPuff,
    EntityRichter,       func_us_801A7DC0,        func_us_801A9084,
    func_us_801A95F4,    func_us_801A9208,        func_us_801A9944,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};

#include "../../st/e_init_common.h"

EInit D_us_80180400 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER};
EInit D_us_8018040C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_134};
EInit D_us_80180418 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_135};
EInit D_us_80180424 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_136};
EInit D_us_80180430 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_137};
EInit D_us_8018043C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_138};
EInit D_us_80180448 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_139};
EInit D_us_80180454 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_SUBWPN_CROSS};
EInit D_us_80180460 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_SUBWPN_HOLY_WATER};
EInit D_us_8018046C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_13C};
EInit D_us_80180478 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_13D};
EInit D_us_80180484 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_13E};
EInit D_us_80180490 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_CRASH_AXE};
EInit D_us_8018049C = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_140};
EInit D_us_801804A8 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_141};
EInit D_us_801804B4 = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_147};
EInit D_us_801804C0 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_15D};
EInit D_us_801804CC = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_RICHTER_UNK_15C};
