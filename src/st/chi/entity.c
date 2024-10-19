#include "game.h"
#include "stage.h"

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
void EntityHeartDrop(Entity*);
void EntityEnemyBlood(Entity*);
void EntityMessageBox(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityTriggerVolume(Entity*);
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
    EntityHeartDrop,
    EntityEnemyBlood,
    EntityMessageBox,
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityTriggerVolume,
    EntityUnkId13,  // EntityFlameTrail
    EntityUnkId14,
    EntityUnkId15,  // EntityGreyPuff
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

//TODO: Used in EntityBreakable
//TODO: Used in func_8018DB18
// D_80180610
EntityInit EntityInit_80180610 = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 0,
};

//TODO: Used in func_801A2D84
//TODO: Used in func_801A3740
//TODO: Used in func_801A3FDC
//TODO: (More were unlisted)
// D_8018061C
EntityInit g_InitializeData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

//TODO: Used in func_801A3520
//TODO: Used in EntityOlroxDrool
//TODO: Used in func_801A5F54
//TODO: (More were unlisted)
// D_80180628
EntityInit g_InitializeEntityData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

//TODO: No match, no errors
// D_80180634
EntityInit EntityInit_80180634 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 4,
};

//TODO: Used in func_801A941C
//TODO: Used in func_801AD2BC
// EntityInit_80180640
EntityInit g_EInitGeneric = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

//TODO: Used in EntityUnkId13
// D_8018064C
EntityInit g_InitDataEnt13 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

//TODO: Used in EntityUnkId12
// D_80180658
EntityInit EntityInit_80180658 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

//TODO: Used in func_801A7C8C
//TODO: Used in EntityBackgroundBlock
//TODO: Used in EntityRedDoor
// D_80180664
EntityInit g_eInitGeneric2 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

//TODO: Used in EntityDamageDisplay
// D_80180670
EntityInit g_eDamageDisplayInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

//TODO: Used in EntityDemonSwitchWall
//TODO: Used in EntityBreakableWallDebris
// D_8018067C
EntityInit EntityInit_8018067C = {
    .animSet = ANIMSET_OVL(1),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

//TODO: Used in func_801A813C
//TODO: Used in func_801A8DE8
//TODO: (More were unlisted)
// D_80180688
EntityInit EntityInit_80180688 = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 1,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 221,
};

//TODO: Used in func_801A8EAC
// D_80180694
EntityInit EntityInit_80180694 = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 222,
};

//TODO: Used in func_801A9588
// D_801806A0
EntityInit EntityInit_801806A0 = {
    .animSet = ANIMSET_OVL(4),
    .animCurFrame = 0,
    .unk5A = 92,
    .palette = PAL_DRA(747),
    .enemyId = 223,
};

//TODO: Used in func_801A97C8
//TODO: Used in func_801A9D40
// D_801806AC
EntityInit EntityInit_801806AC = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 225,
};

//TODO: No match, no errors
// D_801806B8
EntityInit EntityInit_801806B8 = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 5,
};

//TODO: Used in func_801A9E94
// D_801806C4
EntityInit EntityInit_801806C4 = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 226,
};

//TODO: Used in func_801AA0F0
// D_801806D0
EntityInit EntityInit_801806D0 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 157,
};

//TODO: No match, no errors
// D_801806DC
EntityInit EntityInit_801806DC = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 158,
};

//TODO: Used in func_801AA404
// D_801806E8
EntityInit EntityInit_801806E8 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 159,
};

//TODO: Used in func_801AB0C0
// D_801806F4
EntityInit EntityInit_801806F4 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 160,
};

//TODO: Used in func_801AB844
// D_80180700
EntityInit EntityInit_80180700 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 161,
};

//TODO: Used in func_801AC124
//TODO: Used in func_801ACEF4
// D_8018070C
EntityInit EntityInit_8018070C = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 162,
};

//TODO: Used in func_801AC7A0
// D_80180718
EntityInit EntityInit_80180718 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 163,
};

//TODO: Used in func_801ACB6C
// D_80180724
EntityInit EntityInit_80180724 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 55,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 164,
};

// D_80180730
static u8 AnimFrames_80180730[] = {
    0x40, 0x01, 0xFF, 0x00,
};

// D_80180734
static u8 AnimFrames_80180734[] = {
    0x02, 0x25, 0x02, 0x26, 0x02, 0x27, 0x02, 0x26, 0x00, 0x00, 0x00, 0x00,
};

// Used in EntityBackgroundBlock
// D_80180740
ObjInit2 ObjInit2_80180740 = {
    .animSet = ANIMSET_DRA(6),
    .zPriority = 0x1FA,
    .unk4 = {.s = 0},
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_DEFAULT,
    .drawMode = DRAW_TPAGE,
    .unk10 = &AnimFrames_80180730,
};

// D_80180754
ObjInit2 ObjInit2_80180754 = {
    .animSet = ANIMSET_OVL(1),
    .zPriority = 0xC0,
    .unk4 = {.s = 0},
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_TRANSP | DRAW_UNK02,
    .drawMode = 0x30,
    .unkC = 0,
    .unk10 = AnimFrames_80180734,
};

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

// D_80180798
u8 D_80180798[] = {32, 32, 32, 32, 32, 32, 80, 32};
// D_801807A0
u8 D_801807A0[] = {0, 0, 0, 0, 0, 0, 0, 0};

// D_801807A8
u16 D_801807A8[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

// D_80180818
static u16 D_80180818[] = {
    0x0E03, 0x0F04, 0x1004, 0x1104, 0x1204, 0x1304, 0x1403, 0x0000,
};

// D_80180828
static u16 D_80180828[] = {
    0x1503, 0x1604, 0x1704, 0x1804, 0x1904, 0x1A04, 0x1B03, 0x0000,
};

// D_80180838
u16* D_80180838[] = {
    D_80180818, D_80180828, NULL, NULL, NULL, NULL, NULL, NULL,
};

// [height?]
// D_80180858
u8 D_80180858[] = {
    12, 20, 0, 0, 0, 0, 0, 0,
};

// [params?]
// D_80180860
u8 D_80180860[] = {
    3, 3, 0, 0, 0, 0, 0, 0,
};

// [animset?]
// D_80180868
u16 D_80180868[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0,
};

// [draw mode?]
// D_80180878
u8 D_80180878[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
};

// D_80180880
s16 D_80180880[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31,
};