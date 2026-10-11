// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

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
void EntityMinotaur(Entity* self);
void EntityMinotaurAttackHitbox(Entity* self);
void EntityMinotaurFireball(Entity* self);
void EntityMinotaurSpitLiquid(Entity* self);
void EntityWerewolf(Entity* self);
void EntityWerewolfAttackHitbox(Entity* self);
void EntityWerewolfEnergyWave(Entity* self);
void EntityWerewolfSpinAttackAfterImage(Entity* self);
void EntityWerewolfDeathFlames(Entity* self);
void EntityMinotaurDeathPuff(Entity* self);
void EntityAzaghal(Entity* self);
void EntityAzaghalSwordHitbox(Entity* self);
void EntityBreakableFloorSecret(Entity* self);
void EntityBreakableDebris(Entity* self);
void EntityBackgroundDoorRubble(Entity* self);
void EntityFountainWater(Entity* self);
void EntityBossTorch(Entity* self);
void EntityBossDoors(Entity* self);
void EntityWhiteDragon(Entity* self);
void EntityWhiteDragonFlameBreath(Entity* self);
void EntityStoneSkull(Entity* self);

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
    EntityMinotaur,
    EntityMinotaurAttackHitbox,
    EntityMinotaurFireball,
    EntityMinotaurSpitLiquid,
    EntityWerewolf,
    EntityWerewolfAttackHitbox,
    EntityWerewolfEnergyWave,
    EntityWerewolfSpinAttackAfterImage,
    EntityWerewolfDeathFlames,
    EntityMinotaurDeathPuff,
    EntityAzaghal,
    EntityAzaghalSwordHitbox,
    EntityBreakableFloorSecret,
    EntityBreakableDebris,
    EntityBackgroundDoorRubble,
    EntityFountainWater,
    EntityBossTorch,
    EntityBossDoors,
    EntityWhiteDragon,
    EntityWhiteDragonFlameBreath,
    EntityStoneSkull,
};

// animSet, animCurFrame, unk5A, palette, enemyID
// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitSpawner = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};

EInit g_EInitEnvironmentBreakable = {ANIMSET_OVL(1), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitEnvironment = {ANIMSET_OVL(2), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};

EInit g_EInitMinotaur = {ANIMSET_OVL(3), 0x01, 0x48, PAL_MINOTAUR, ENEMY_MINOTAUR};
EInit g_EInitMinotaurAttackHitbox = {ANIMSET_OVL(3), 0x00, 0x48, PAL_MINOTAUR, ENEMY_MINOTAUR_ATTACK_HITBOX};
EInit g_EInitMinotaurFireball = {ANIMSET_DRA(2), 0x01, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitMinotaurSpitLiquid = {ANIMSET_DRA(2), 0x01, 0x00, PAL_NONE, ENEMY_MINOTAUR_SPIT_LIQUID};

EInit g_EInitWerewolf = {ANIMSET_OVL(4), 0x01, 0x50, PAL_WEREWOLF, ENEMY_WEREWOLF_RARE};
EInit g_EInitWerewolfAttackHitbox = {ANIMSET_OVL(4), 0x00, 0x50, PAL_WEREWOLF, ENEMY_WEREWOLF_RARE_ATTACK_HITBOX};
EInit g_EInitWerewolfEnergyWave = {ANIMSET_OVL(4), 0x36, 0x50, PAL_WEREWOLF, ENEMY_WEREWOLF_RARE_ENERGY_WAVE};

EInit g_EInitAzaghal = {ANIMSET_OVL(0), 0x00, 0x00, PAL_NONE, ENEMY_AZAGHAL};

// nb. Main White Dragon entity uses a g_EInitSpawner to initialise
EInit g_EInitWhiteDragonFlameBreath = {ANIMSET_DRA(14), 0x00, 0x79, PAL_WHITE_DRAGON_FLAME_BREATH, ENEMY_WHITE_DRAGON_FLAME_BREATH};

EInit g_EInitStoneSkull = {ANIMSET_OVL(7), 0x00, 0x49, PAL_STONE_SKULL, ENEMY_STONE_SKULL};
