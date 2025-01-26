// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: dt_entity.c
 * Overlay: CHI
 * Description: DATA - Entities
 */

#include "chi.h"

void EntityBreakableWithDebris(Entity*);
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
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void EntityUnkId13(Entity*);
void EntityExplosionVariants(Entity*);
void EntityGreyPuff(Entity*);
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
PfnEntityUpdate OVL_EXPORT(EntityUpdates)[] = {
    EntityBreakableWithDebris,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    OVL_EXPORT(EntityRedDoor),
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
    EntityExplosionVariants,
    EntityGreyPuff,
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
EInit OVL_EXPORT(EInitBreakable) = {ANIMSET_OVL(1), 0, 0x00, 0x000, 0};

// NOTE: BEGIN ../e_init_common.h
//       I would include ../e_init_common.h here, but the last entry in there
//       has a different .enemyId value than is needed here
//  D_8018061C
EInit g_EInitObtainable = {ANIMSET_DRA(3), 0, 0x00, 0x000, 1};
// D_80180628
EInit g_EInitParticle = {ANIMSET_DRA(3), 0, 0x00, 0x000, 2};
// D_80180634
EInit g_EInitMaria = {ANIMSET_DRA(0), 0, 0x00, 0x000, 4};
// D_80180640
EInit g_EInitInteractable = {ANIMSET_DRA(0), 0, 0x00, 0x000, 5};
// D_8018064C
EInit g_EInitUnkId13 = {ANIMSET_DRA(0), 0, 0x00, 0x000, 2};
// D_80180658
EInit g_EInitUnkId12 = {ANIMSET_DRA(0), 0, 0x00, 0x000, 1};
// D_80180664
EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0x00, 0x000, 3};
// D_80180670
EInit g_EInitDamageNum = {ANIMSET_DRA(0), 0, 0x00, 0x000, 3};
// D_8018067C
EInit g_EInitSecret = {ANIMSET_OVL(1), 0, 0, PAL_DRA(0),
                       5}; // ../e_init_common.h has 3 for the last value
// NOTE: END ../e_init_common.h

// D_80180688
EInit g_EInitSalemWitch = {ANIMSET_OVL(3), 1, 72, PAL_DRA(516), 221};

// D_80180694
EInit g_EInitSalemWitchCurse = {ANIMSET_OVL(3), 0, 72, PAL_DRA(516), 222};

// D_801806A0
EInit g_EInitSalemWitchTribolt = {ANIMSET_OVL(4), 0, 92, PAL_DRA(747), 223};

// D_801806AC
EInit g_EInitGremlin = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 225};

// Unused
// D_801806B8
EInit g_EInit801806B8 = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 5};

// D_801806C4
EInit g_EInitGremlinFire = {ANIMSET_OVL(2), 0, 72, PAL_DRA(512), 226};

// D_801806D0
EInit g_EInitThornweed = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 157};

// Unused (Alternate Corpseweed)
// D_801806DC
EInit g_EInit801806DC = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 158};

// D_801806E8
EInit g_EInitCorpseweed = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 159};

// D_801806F4
EInit g_EInitCorpseweedProjectile = {ANIMSET_OVL(7), 0, 76, PAL_DRA(518), 160};

// D_80180700
EInit g_EInitVenusWeedRoot = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 161};

// D_8018070C
EInit g_EInitVenusWeedFlower = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 162};

// D_80180718
EInit g_EInitVenusWeedTendril = {ANIMSET_OVL(8), 0, 80, PAL_DRA(522), 163};

// D_80180724
EInit g_EInitVenusWeedDart = {ANIMSET_OVL(8), 55, 80, PAL_DRA(522), 164};

// D_80180730
static u8 AnimFrames_80180730[] = {0x40, 0x01, 0xFF, 0x00};

// D_80180734
static u8 AnimFrames_80180734[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00,
};

// Background Block
// D_80180740
ObjInit OVL_EXPORT(BackgroundBlockInit)[] = {
    {
        .animSet = ANIMSET_DRA(6),
        .zPriority = 0x1FA,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = DRAW_DEFAULT,
        .drawMode = DRAW_TPAGE,
        .animFrames = &AnimFrames_80180730,
    },
    {
        .animSet = ANIMSET_OVL(1),
        .zPriority = 0xC0,
        .unk5A = 0,
        .palette = PAL_DRA(0),
        .drawFlags = DRAW_TRANSP | DRAW_UNK02,
        .drawMode = DRAW_TPAGE2 | DRAW_TPAGE,
        .unkC = 0,
        .animFrames = AnimFrames_80180734,
    }};

// D_80180768
u16 OVL_EXPORT(RedDoorTiles)[][8] = {
    {0x039C, 0x039B, 0x039C, 0x039B, 0x010D, 0x010B, 0x010D, 0x010B},
    {0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x02F4, 0x0309, 0x0305, 0x0307},
    {0x03A3, 0x03A7, 0x03A8, 0x03A3, 0x02F4, 0x030F, 0x0310, 0x02F4},
};
