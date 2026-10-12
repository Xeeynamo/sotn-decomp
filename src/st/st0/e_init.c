// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

void func_801A805C(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void EntityIntenseExplosion(Entity*);
void EntitySoulStealOrb(Entity*);
void EntityRoomForeground(Entity*);
void EntityDummy(Entity*);
void EntityEquipItemDrop(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void EntityCutscene(Entity*);
void EntityCutsceneSupport(Entity*);
void EntityStageTitleCard(Entity*);
void EntityStageTitleFadeout(Entity*);
void EntityDracula(Entity*);
void EntityDraculaFireball(Entity*);
void EntityDraculaMeteorball(Entity*);
void EntityDraculaBody(Entity*);
void func_801AD838(Entity*);
void EntityDraculaGlass(Entity*);
void EntityDraculaFinalForm(Entity*);
void EntityDraculaMegaFireball(Entity*);
void EntityDraculaRainAttack(Entity*);
void EntityDematerializeStageBg(Entity*);
void EntityBackgroundVortex(Entity*);
void EntityBackgroundClouds(Entity*);
void func_801A8328(Entity*);
void EntitySecretStairsCeiling(Entity*);
void EntitySecretButton(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void func_801AF774(Entity*);
void EntityCutscenePhotograph(Entity*);
void EntityCutscenePhotographFire(Entity*);
void func_801BC5C0(Entity*);

PfnEntityUpdate EntityUpdates[] = {
    func_801A805C,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
    EntityIntenseExplosion,
    EntitySoulStealOrb,
    EntityRoomForeground,
    EntityDummy,
    EntityEquipItemDrop,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    EntityCutscene,
    EntityCutsceneSupport,
    EntityStageTitleCard,
    EntityStageTitleFadeout,
    EntityDracula,
    EntityDraculaFireball,
    EntityDraculaMeteorball,
    EntityDraculaBody,
    func_801AD838,
    EntityDraculaGlass,
    EntityDraculaFinalForm,
    EntityDraculaMegaFireball,
    EntityDraculaRainAttack,
    EntityDematerializeStageBg,
    EntityBackgroundVortex,
    EntityBackgroundClouds,
    func_801A8328,
    EntitySecretStairsCeiling,
    EntitySecretButton,
    EntitySecretStairs,
    EntityClockTower3D,
    func_801AF774,
    EntityCutscenePhotograph,
    EntityCutscenePhotographFire,
    func_801BC5C0,
};

// clang-format off
EInit g_EInitBreakable = {ANIMSET_DRA(3), 0x00, 0x7C, PAL_UNK_100, ENEMY_BREAKABLE};
EInit g_EInitObtainable = {ANIMSET_OVL(3), 0x00, 0x7C, PAL_UNK_100, ENEMY_OBTAINABLE};
EInit g_EInitParticle = {ANIMSET_DRA(3), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitCutscene = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_SPAWNER};
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_PARTICLE};
EInit g_EInitLockCamera = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_OBTAINABLE};
EInit g_EInitCommon = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_COMMON};
EInit g_EInit3DObject = {ANIMSET_DRA(0), 0x00, 0x00, PAL_NONE, ENEMY_INTERACTABLE};
EInit g_EInitDracula = {ANIMSET_OVL(1), 0x00, 0x48, PAL_DRACULA, ENEMY_DRACULA};
EInit g_EInitDraculaFireball = {ANIMSET_OVL(1), 0x00, 0x48, PAL_DRACULA, ENEMY_DRACULA_FIREBALL};
EInit g_EInitDraculaMeteorball = {ANIMSET_OVL(1), 0x00, 0x48, PAL_DRACULA, ENEMY_DRACULA_METEORBALL};
EInit g_EInitDraculaFinalForm = {ANIMSET_OVL(2), 0x00, 0x50, PAL_GREATER_DEMON, ENEMY_GREATER_DEMON};
EInit g_EInitDraculaMegaFireball = {ANIMSET_OVL(2), 0x00, 0x50, PAL_GREATER_DEMON, ENEMY_GREATER_DEMON_MEGA_FIREBALL};
EInit g_EInitDraculaRainAttack = {ANIMSET_OVL(2), 0x00, 0x50, PAL_GREATER_DEMON, ENEMY_GREATER_DEMON_RAIN_ATTACK};
EInit g_EInitSecretStairs = {ANIMSET_OVL(6), 0x00, 0x4C, PAL_SECRET_STAIRS, ENEMY_INTERACTABLE};
