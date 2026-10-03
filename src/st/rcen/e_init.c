// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcen.h"

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
void EntityShaft(Entity* self);
void EntityShaftMeridianRings(Entity* self);
void EntityShaftCrystalBall(Entity* self);
void EntityCutsceneShaft(Entity* self);
void EntityShaftAttackOrb(Entity* self);
void EntityShaftFlameTrail(Entity* self);
void EntityShaftFlamePillar(Entity* self);
void EntityShaftLightning(Entity* self);
void EntityShaftLightningHitbox(Entity* self);
void EntityShaftOrbitOrb(Entity* self);
void EntityShaftDeathFlames(Entity* self);
void EntityCutscene(Entity* self);
void func_us_8019F148(Entity* self);
void func_us_8019F5F0(Entity* self);
void EntityElevatorStationary(Entity* self);
void EntityUnkId1B(Entity* self);
void func_us_8019F9C0(Entity* self);
void func_us_801B4148_from_bo0(Entity* self);
void func_us_801C123C_from_no4(Entity* self);

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
    EntityShaft,
    EntityShaftMeridianRings,
    EntityShaftCrystalBall,
    EntityCutsceneShaft,
    EntityShaftAttackOrb,
    EntityShaftFlameTrail,
    EntityShaftFlamePillar,
    EntityShaftLightning,
    EntityShaftLightningHitbox,
    EntityShaftOrbitOrb,
    EntityShaftDeathFlames,
    EntityCutscene,
    func_us_8019F148,
    func_us_8019F5F0,
    EntityElevatorStationary,
    EntityUnkId1B,
    func_us_8019F9C0,
    func_us_801B4148_from_bo0,
    func_us_801C123C_from_no4,
};

// clang-format off
// animSet, animCurFrame, unk5A, palette, enemyID
EInit g_EInitBreakable = {ANIMSET_OVL(1), 0, 0, 0, 0x000};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0, 0, 0x001};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0, 0, 0x002};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0, 0, 0, 0x004};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0, 0, 0x005};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0, 0, 0x002};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0, 0, 0, 0x001};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 0x003};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0, 0, 0x003};

// All Shaft related entities
EInit g_EInitShaft = {ANIMSET_OVL(3), 0, 72, 0x200, 0x15F};
EInit g_EInitShaftCrystalBall = {ANIMSET_OVL(3), 0, 72, 0x200, 0x005};
EInit g_EInitShaftOrb = {ANIMSET_OVL(3), 0, 72, 0x200, 0x160};
EInit g_EInitShaftFlame = {ANIMSET_DRA(14), 0, 121, 0x2E0, 0x161};
EInit g_EInitShaftLightningHitbox = {ANIMSET_DRA(0), 0, 0, 0, 0x162};

EInit g_EInitElevator = {ANIMSET_OVL(12), 1, 72, 0x240, 0x005};
// clang-format on
