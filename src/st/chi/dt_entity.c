// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_entity.c
 * Overlay: CHI
 * Description: DATA - Entities
 */

#include "game.h"
#include "stage.h"

void EntityBreakableWithDebris(Entity*);
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
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityUnkId14(Entity*);
void EntityUnkId15(Entity*);
void EntityDemonSwitchWall(Entity*);
void EntityDemonSwitch(Entity*);
void EntityBreakableWall(Entity*);
void EntityBreakableWallDebris(Entity*);
void EntityBreakableDebris(Entity*);
void EntityFallingStairs(Entity*);
void EntityCerberusGateDebug(Entity*);
void EntityFallingStep(Entity*);
void EntityGremlin(Entity*);
void EntityGremlinEffect(Entity*);
void EntityGremlinFire(Entity*);
void EntitySalemWitch(Entity*);
void EntitySalemWitchGlow(Entity*);
void EntitySalemWitchCurse(Entity*);
void EntitySalemWitchTriboltLaunch(Entity*);
void EntitySalemWitchTriboltProjectile(Entity*);
void EntityThornweed(Entity*);
void EntityCorpseweed(Entity*);
void EntityCorpseweedProjectile(Entity*);
void EntityVenusWeed(Entity*);
void EntityVenusWeedFlower(Entity*);
void EntityVenusWeedTendril(Entity*);
void EntityVenusWeedDart(Entity*);
void EntityVenusWeedSpike(Entity*);

// D_8018055C
PfnEntityUpdate PfnEntityUpdates[] = {
    EntityBreakableWithDebris,
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
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityUnkId12, // EntityCameraLock
    EntityUnkId13, // EntityParticleTrail
    EntityUnkId14,
    EntityUnkId15, // EntityGreyPuff
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    EntityBreakableDebris,
    EntityCerberusGateDebug,
    EntityFallingStairs,
    EntityFallingStep,
    EntityGremlin,
    EntityGremlinEffect,
    EntityGremlinFire,
    EntitySalemWitch,
    EntitySalemWitchGlow,
    EntitySalemWitchCurse,
    EntitySalemWitchTriboltLaunch,
    EntitySalemWitchTriboltProjectile,
    EntityThornweed,
    EntityCorpseweed,
    EntityCorpseweedProjectile,
    EntityVenusWeed,
    EntityVenusWeedFlower,
    EntityVenusWeedTendril,
    EntityVenusWeedDart,
    EntityVenusWeedSpike,
};

// D_80180610
EntityInit g_eBreakableWithDebrisInit = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 0,
};

// D_8018061C
EntityInit g_InitializeData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

// D_80180628
EntityInit g_InitializeEntityData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

// Unused
// D_80180634
EntityInit g_EntityInit_80180634 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 4,
};

// D_80180640
EntityInit g_EInitGeneric = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

// D_8018064C
EntityInit g_InitDataEnt13 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

// Camera Lock
// D_80180658
EntityInit g_EntityUnkId12Init = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

// D_80180664
EntityInit g_eInitGeneric2 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

// D_80180670
EntityInit g_eDamageDisplayInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

// Graphics that are supposed to simulate the tilemap or similar
// (ie. the Demon Switch)
// D_8018067C
EntityInit g_InitTilemap = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

// D_80180688
EntityInit g_InitSalemWitch = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 1,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 221,
};

// D_80180694
EntityInit g_InitSalemWitchCurse = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 222,
};

// D_801806A0
EntityInit g_InitSalemWitchTribolt = {
    .animSet = ANIMSET_OVL(4),
    .animCurFrame = 0,
    .unk5A = 92,
    .palette = PAL_DRA(747),
    .enemyId = 223,
};

// D_801806AC
EntityInit g_InitGremlin = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 225,
};

// Unused (Same enemyId as g_InitTilemap)
// D_801806B8
EntityInit g_EntityInit_801806B8 = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 5,
};

// D_801806C4
EntityInit g_InitGremlinFire = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 226,
};

// D_801806D0
EntityInit g_InitThornweed = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 157,
};

// Unused (Alternate Corpseweed)
// D_801806DC
EntityInit g_EntityInit_801806DC = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 158,
};

// D_801806E8
EntityInit g_InitCorpseweed = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 159,
};

// D_801806F4
EntityInit g_InitCorpseweedProjectile = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 160,
};

// D_80180700
EntityInit g_InitVenusWeedRoot = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 161,
};

// D_8018070C
EntityInit g_InitVenusWeedFlower = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 162,
};

// D_80180718
EntityInit g_InitVenusWeedTendril = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 163,
};

// D_80180724
EntityInit g_InitVenusWeedDart = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 55,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 164,
};

// D_80180730
static u8 AnimFrames_80180730[] = {
    0x40,
    0x01,
    0xFF,
    0x00,
};

// D_80180734
static u8 AnimFrames_80180734[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00,
};

// Background Block
// D_80180740
ObjInit2 g_eBackgroundBlockInit[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .facingLeft = false,
        .palette = PAL_DRA(0),
        .drawFlags = DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .animFrames = &AnimFrames_80180730,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .facingLeft = false,
        .palette = PAL_DRA(0),
        .drawFlags = DRAW_TRANSP | DRAW_UNK02,
        .drawMode = 0x30,
        .unkC = 0,
        .animFrames = AnimFrames_80180734,
    }};

// D_80180768
u16 g_eRedDoorTiles[3][8] = {
    {
        0x039C,
        0x039B,
        0x039C,
        0x039B,
        0x010D,
        0x010B,
        0x010D,
        0x010B,
    },
    {
        0x03A3,
        0x03A4,
        0x03A5,
        0x03A6,
        0x02F4,
        0x0309,
        0x0305,
        0x0307,
    },
    {
        0x03A3,
        0x03A7,
        0x03A8,
        0x03A3,
        0x02F4,
        0x030F,
        0x0310,
        0x02F4,
    },
};
