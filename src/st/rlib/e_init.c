// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

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
void func_us_801AF280_from_lib(Entity* self);
void func_us_801AF538_from_lib(Entity* self);
void func_us_801AF7B8_from_lib(Entity* self);
void func_us_801AFA80_from_lib(Entity* self);
void func_us_801AE8E8_from_lib(Entity* self);
void func_us_801AE7AC_from_lib(Entity* self);
void func_us_801ADBE8(Entity* self);
void EntityHarpyKick(Entity* self);
void func_us_801AE414(Entity* self);
void func_us_801AE534(Entity* self);
void func_us_801AED4C(Entity* self);
void func_us_801D8D44_from_no4(Entity* self);
void func_us_801AEFE0(Entity* self);
void func_us_801AF11C(Entity* self);
void func_us_801AF448(Entity* self);
void func_us_801AF9E8(Entity* self);
void EntityExplosionPuffOpaque(Entity* self);
void func_us_801AFC88(Entity* self);
void EntityBreakableDebris(Entity* self);
void func_us_801BAF60_from_lib(Entity* self);

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
    func_us_801AF280_from_lib,
    func_us_801AF538_from_lib,
    func_us_801AF7B8_from_lib,
    func_us_801AFA80_from_lib,
    func_us_801AE8E8_from_lib,
    func_us_801AE7AC_from_lib,
    func_us_801ADBE8,
    EntityHarpyKick,
    func_us_801AE414,
    func_us_801AE534,
    func_us_801AED4C,
    func_us_801D8D44_from_no4,
    func_us_801AEFE0,
    func_us_801AF11C,
    func_us_801AF448,
    func_us_801AF9E8,
    EntityExplosionPuffOpaque,
    func_us_801AFC88,
    EntityBreakableDebris,
    func_us_801BAF60_from_lib,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitLion = {ANIMSET_OVL(3), 0x01, 0x50, PAL_LION, ENEMY_LION};
EInit D_us_8018064C = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_LION_UNK_107};
EInit D_us_80180658 = {ANIMSET_OVL(3), 0x00, 0x50, PAL_LION, ENEMY_PARTICLE};
EInit g_EInitTinman = {ANIMSET_OVL(4), 0x01, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN};
EInit D_us_80180670 = {ANIMSET_OVL(4), 0x05, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN_UNK_109};
EInit D_us_8018067C = {ANIMSET_OVL(4), 0x00, 0x53, PAL_TIN_MAN, ENEMY_TIN_MAN_UNK_10A};
EInit D_us_80180688 = {ANIMSET_OVL(4), 0x00, 0x53, PAL_TIN_MAN, ENEMY_PARTICLE};
EInit g_EInitScarecrow = {ANIMSET_OVL(5), 0x00, 0x54, PAL_SCARECROW, ENEMY_SCARECROW};
EInit D_us_801806A0 = {ANIMSET_OVL(5), 0x00, 0x54, PAL_SCARECROW, ENEMY_INTERACTABLE};
EInit g_EInitSchmoo = {ANIMSET_OVL(5), 0x08, 0x54, PAL_SCHMOO, ENEMY_SCHMOO};
EInit D_us_801806B8 = {ANIMSET_OVL(6), 0x00, 0x50, PAL_UNK_20F, ENEMY_INTERACTABLE};
// clang-format on
