#include "game.h"
#include "stage.h"

void EntityUnkId01(Entity*);
void EntityExplosion(Entity*);
void EntityPrizeDrop(Entity*);
void EntityDamageDisplay(Entity*);
void EntityRedDoor(Entity*);
void func_801A5F54(Entity*);
void func_801A7448(Entity*);
void func_801A7C8C(Entity*);
void func_801AD2BC(Entity*);
void EntityEquipItemDrop(Entity*);
void func_801A3F58(Entity*);
void func_801A4A28(Entity*);
void func_801A77DC(Entity*);
void func_801A4B50(Entity*);
void EntityDummy(Entity*);
void EntityBackgroundBlock(Entity*);
void EntityUnkId12(Entity*);
void func_801A519C(Entity*);
void func_801A54C4(Entity*);
void func_801A55B4(Entity*);
void EntityDemonSwitchWall(Entity*);
void EntityDemonSwitch(Entity*);
void EntityBreakableWall(Entity*);
void EntityBreakableWallDebris(Entity*);
void func_8019B914(Entity*);
void EntityFallingStairs(Entity*);
void func_8019CBA8(Entity*);
void EntityFallingStep(Entity*);
void func_801A97C8(Entity*);
void func_801A9D40(Entity*);
void func_801A9E94(Entity*);
void func_801A813C(Entity*);
void func_801A8DE8(Entity*);
void func_801A8EAC(Entity*);
void func_801A93D4(Entity*);
void func_801A9588(Entity*);
void func_801AA020(Entity*);
void func_801AA390(Entity*);
void func_801AB0C0(Entity*);
void func_801AB7CC(Entity*);
void func_801AC074(Entity*);
void func_801AC730(Entity*);
void func_801ACB6C(Entity*);
void func_801ACEF4(Entity*);

PfnEntityUpdate PfnEntityUpdates[] = {
    EntityUnkId01,
    EntityExplosion,
    EntityPrizeDrop,
    EntityDamageDisplay,
    EntityRedDoor,
    func_801A5F54,  // EntityIntenseExplosion
    func_801A7448,  // EntitySoulStealOrb
    func_801A7C8C,  // EntityRoomForeground
    func_801AD2BC,  // EntityStageNamePopup
    EntityEquipItemDrop,
    func_801A3F58,  // EntityRelicOrb
    func_801A4A28,  // EntityHeartDrop
    func_801A77DC,  // EntityEnemyBlood
    func_801A4B50,  // EntityMessageBox
    EntityDummy,
    EntityDummy,
    EntityBackgroundBlock,
    EntityUnkId12,
    func_801A519C,  // EntityUnkId13
    func_801A54C4,  // EntityUnkId14
    func_801A55B4,  // EntityUnkId15
    EntityDemonSwitchWall,
    EntityDemonSwitch,
    EntityBreakableWall,
    EntityBreakableWallDebris,
    func_8019B914,  // E_ID_1A - CEN.func_8018DB18
    func_8019CBA8,  // E_ID_1B
    EntityFallingStairs,
    EntityFallingStep,
    func_801A97C8,  // E_ID_1E
    func_801A9D40,  // E_ID_1F
    func_801A9E94,  // E_ID_20
    func_801A813C,  // E_ID_21
    func_801A8DE8,  // E_ID_22
    func_801A8EAC,  // E_ID_23
    func_801A93D4,  // E_ID_24
    func_801A9588,  // E_ID_25
    func_801AA020,  // E_ID_26
    func_801AA390,  // E_ID_27
    func_801AB0C0,  // E_ID_28
    func_801AB7CC,  // E_ID_29
    func_801AC074,  // E_ID_2A
    func_801AC730,  // E_ID_2B
    func_801ACB6C,  // E_ID_2C
    func_801ACEF4,  // E_ID_2D
};

//TODO: Used in EntityUnkId01
//TODO: Used in func_8018DB18
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
EntityInit g_InitializeData0 = {
    .animSet = ANIMSET_DRA(3),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 1,
};

//TODO: Used in func_801A3520
//TODO: Used in func_801A56A8
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
EntityInit EntityInit_80180634 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 4,
};

//TODO: Used in func_801A941C
//TODO: Used in func_801AD2BC
EntityInit EntityInit_80180640 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 5,
};

//TODO: Used in func_801A519C
EntityInit EntityInit_8018064C = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 2,
};

//TODO: Used in EntityUnkId12
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
EntityInit g_eInitGeneric2 = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

//TODO: Used in EntityDamageDisplay
EntityInit g_eDamageDisplayInit = {
    .animSet = ANIMSET_DRA(0),
    .animCurFrame = 0,
    .unk5A = 0,
    .palette = PAL_DRA(0),
    .enemyId = 3,
};

//TODO: Used in EntityDemonSwitchWall
//TODO: Used in EntityBreakableWallDebris
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
EntityInit EntityInit_80180688 = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 1,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 221,
};

//TODO: Used in func_801A8EAC
EntityInit EntityInit_80180694 = {
    .animSet = ANIMSET_OVL(3),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(516),
    .enemyId = 222,
};

//TODO: Used in func_801A9588
EntityInit EntityInit_801806A0 = {
    .animSet = ANIMSET_OVL(4),
    .animCurFrame = 0,
    .unk5A = 92,
    .palette = PAL_DRA(747),
    .enemyId = 223,
};

//TODO: Used in func_801A97C8
//TODO: Used in func_801A9D40
EntityInit EntityInit_801806AC = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 225,
};

//TODO: No match, no errors
EntityInit EntityInit_801806B8 = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 5,
};

//TODO: Used in func_801A9E94
EntityInit EntityInit_801806C4 = {
    .animSet = ANIMSET_OVL(2),
    .animCurFrame = 0,
    .unk5A = 72,
    .palette = PAL_DRA(512),
    .enemyId = 226,
};

//TODO: Used in func_801AA0F0
EntityInit EntityInit_801806D0 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 157,
};

//TODO: No match, no errors
EntityInit EntityInit_801806DC = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 158,
};

//TODO: Used in func_801AA404
EntityInit EntityInit_801806E8 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 159,
};

//TODO: Used in func_801AB0C0
EntityInit EntityInit_801806F4 = {
    .animSet = ANIMSET_OVL(7),
    .animCurFrame = 0,
    .unk5A = 76,
    .palette = PAL_DRA(518),
    .enemyId = 160,
};

//TODO: Used in func_801AB844
EntityInit EntityInit_80180700 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 161,
};

//TODO: Used in func_801AC124
//TODO: Used in func_801ACEF4
EntityInit EntityInit_8018070C = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 162,
};

//TODO: Used in func_801AC7A0
EntityInit EntityInit_80180718 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 0,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 163,
};

//TODO: Used in func_801ACB6C
EntityInit EntityInit_80180724 = {
    .animSet = ANIMSET_OVL(8),
    .animCurFrame = 55,
    .unk5A = 80,
    .palette = PAL_DRA(522),
    .enemyId = 164,
};

static u16 D_80180730[] = {
    0x0140, 0x00FF,
};

static u16 D_80180734[] = {
    0x2502, 0x2602, 0x2702, 0x2602, 0x0000, 0x0000,
};

u16 D_80180740[] = {
    0x0006, 0x01FA, 0x0000, 0x0000, 0x0000, 0x0010, 0x0000, 0x0000,
};

u16* D_80180750[] = {
    D_80180730,
};

ObjInit2 ObjInit2_80180754 = {
    .animSet = ANIMSET_OVL(1),
    .zPriority = 0xC0,
    .unk4 = {.s = 0},
    .palette = PAL_DRA(0),
    .drawFlags = DRAW_TRANSP | DRAW_UNK02,
    .drawMode = 0x30,
    .unkC = 0,
    .unk10 = D_80180734,
};

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

u8 D_80180798[] = {32, 32, 32, 32, 32, 32, 80, 32};
u8 D_801807A0[] = {0, 0, 0, 0, 0, 0, 0, 0};

u16 D_801807A8[] = {
    0x0000, 0x0000, 0x0600, 0x0100, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x01FC, 0x0000, 0x0000, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x00FC, 0x0600, 0x01FC,
    0x0000, 0x00FC, 0x0600, 0x0300, 0x0000, 0x0200, 0x0600, 0x0300,
    0x0000, 0x01FC, 0x0500, 0x02FC, 0x0000, 0x0000, 0x0500, 0x0400,
    0x0000, 0x0000, 0x0500, 0x0400, 0x0000, 0x01FC, 0x0500, 0x02FC,
    0x00F0, 0x01FC, 0x0310, 0x02FC, 0x00F0, 0x01FC, 0x0310, 0x02FC,
};

static u16 D_80180818[] = {
    0x0E03, 0x0F04, 0x1004, 0x1104, 0x1204, 0x1304, 0x1403, 0x0000,
};

static u16 D_80180828[] = {
    0x1503, 0x1604, 0x1704, 0x1804, 0x1904, 0x1A04, 0x1B03, 0x0000,
};

u16* D_80180838[] = {
    D_80180818, D_80180828, NULL, NULL, NULL, NULL, NULL, NULL,
};

// height?
u8 D_80180858[] = {
    12, 20, 0, 0, 0, 0, 0, 0,
};

// params?
u8 D_80180860[] = {
    3, 3, 0, 0, 0, 0, 0, 0,
};

// animset?
u16 D_80180868[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0,
};

// draw mode?
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

s16 D_80180880[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31,
};