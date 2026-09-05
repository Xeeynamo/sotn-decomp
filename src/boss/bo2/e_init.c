// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo2.h"

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
void func_us_801A3E04(Entity* self);
void func_us_801A269C(Entity* self);
void EntityMinotaurAttackHitbox(Entity* self);
void EntityMinotaurFireball(Entity* self);
void EntityMinotaurSpitLiquid(Entity* self);
void func_us_801B385C(Entity* self);
void EntityWerewolfAttackHitbox(Entity* self);
void func_us_801B503C(Entity* self);
void EntityWerewolfSpinAttackAfterImage(Entity* self);
void func_us_801B52FC(Entity* self);
void EntityWerewolfDeathFlames(Entity* self);
void EntityMinotaurDeathPuff(Entity* self);
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void EntityLifeUpSpawn(Entity* self);
void EntityCutsceneDialogue(Entity* self);
void func_us_801A6EF8(Entity* self);
void func_us_801A7340(Entity* self);
void func_us_801A460C(Entity* self);
void func_us_801A4BA4(Entity* self);

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
    func_us_801A3E04,
    func_us_801A269C,
    EntityMinotaurAttackHitbox,
    EntityMinotaurFireball,
    EntityMinotaurSpitLiquid,
    func_us_801B385C,
    EntityWerewolfAttackHitbox,
    func_us_801B503C,
    EntityWerewolfSpinAttackAfterImage,
    func_us_801B52FC,
    EntityWerewolfDeathFlames,
    EntityMinotaurDeathPuff,
    EntityBossTorch,
    EntityBossDoors,
    EntityLifeUpSpawn,
    EntityCutsceneDialogue,
    func_us_801A6EF8,
    func_us_801A7340,
    func_us_801A460C,
    func_us_801A4BA4,
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
EInit D_us_80180524 = {ANIMSET_OVL(1), 0, 0, 0, 0x005};
EInit g_EInitMinotaurus = {ANIMSET_OVL(2), 1, 72, 512, 0x0CB};
EInit g_EInitMinotaurAttackHitbox = {ANIMSET_OVL(2), 1, 72, 512, 0x0CC};
EInit g_EInitMinotaurFireball = {ANIMSET_DRA(2), 1, 0, 0, 0x002};
EInit g_EInitMinotaurSpitLiquid = {ANIMSET_DRA(2), 1, 0, 0, 0x0CD};
EInit g_EInitWerewolfARE = {ANIMSET_OVL(3), 1, 84, 528, 0x0CE};
EInit g_EInitWerewolfAttackHitbox = {ANIMSET_OVL(3), 0, 84, 528, 0x0CF};
EInit D_us_80180578 = {ANIMSET_OVL(3), 57, 84, 528, 0x0D0};
EInit D_us_80180584 = {ANIMSET_OVL(3), 0, 84, 528, 0x0D1};
// clang-format on
