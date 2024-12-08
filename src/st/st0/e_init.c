// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

void func_801A805C(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void OVL_EXPORT(EntityRedDoor)(Entity*);
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
void OVL_EXPORT(EntityBackgroundBlock)(Entity*);
void EntityLockCamera(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
void OVL_EXPORT(EntityCutscene)(Entity*);
void EntityCutscene(Entity*);
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
void func_801BD8F0(Entity*);
void EntityBackgroundVortex(Entity*);
void EntityClouds(Entity*);
void func_801A8328(Entity*);
void EntitySecretStairsCeiling(Entity*);
void EntitySecretButton(Entity*);
void EntitySecretStairs(Entity*);
void EntityClockTower3D(Entity*);
void func_801AF774(Entity*);
void EntityCutscenePhotograph(Entity*);
void EntityCutscenePhotographFire(Entity*);
void func_801BC5C0(Entity*);

PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    func_801A805C,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
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
    OVL_EXPORT(EntityBackgroundBlock),
    EntityLockCamera,
    EntityUnkId13,
    EntityExplosionVariants,
    EntityGreyPuff,
    OVL_EXPORT(EntityCutscene),
    EntityCutscene,
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
    func_801BD8F0,
    EntityBackgroundVortex,
    EntityClouds,
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

EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_DRA(3), 0, 0x7C, 0x0100, 0};
EInit g_EInitObtainable = {0x8003, 0x0000, 0x007C, 0x0100, 0x0001};
EInit g_EInitParticle = {0x0003, 0x0000, 0x0000, 0x0000, 0x0002};
EInit g_EInitCutscene = {0x0000, 0x0000, 0x0000, 0x0000, 0x0004};
EInit g_EInitUnkId13 = {0x0000, 0x0000, 0x0000, 0x0000, 0x0002};
EInit g_EInitLockCamera = {0x0000, 0x0000, 0x0000, 0x0000, 0x0001};
EInit g_EInitCommon = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
EInit g_EInitDamageNum = {0x0000, 0x0000, 0x0000, 0x0000, 0x0003};
EInit g_EInit3DObject = {0x0000, 0x0000, 0x0000, 0x0000, 0x0005};
EInit g_EInitDracula = {0x8001, 0x0000, 0x0048, 0x0200, 0x00A9};
EInit g_EInitDraculaFireball = {0x8001, 0x0000, 0x0048, 0x0200, 0x00AA};
EInit g_EInitDraculaMeteorball = {0x8001, 0x0000, 0x0048, 0x0200, 0x00AB};
EInit g_EInitDraculaFinalForm = {0x8002, 0x0000, 0x0050, 0x0202, 0x00AC};
EInit g_EInitDraculaMegaFireball = {0x8002, 0x0000, 0x0050, 0x0202, 0x00AD};
EInit g_EInitDraculaRainAttack = {0x8002, 0x0000, 0x0050, 0x0202, 0x00AE};
EInit g_EInitSecretStairs = {0x8006, 0x0000, 0x004C, 0x0228, 0x0005};

static u8 D_80180634[] = {0x40, 0x01, 0xFF, 0x00};
ObjInit OVL_EXPORT(BackgroundBlockInit)[] = {
    {.animSet = ANIMSET_DRA(6),
     .zPriority = 0x01FA,
     .unk5A = 0x0000,
     .palette = PAL_DRA(0),
     .drawFlags = FLAG_DRAW_DEFAULT,
     .drawMode = DRAW_TPAGE,
     .unkC = 0x00000000,
     D_80180634},
};

u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x001, 0x001, 0x001, 0x001, 0x000, 0x000, 0x000, 0x000},
};
