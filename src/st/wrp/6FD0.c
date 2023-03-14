/*
 * File: 6FD0.c
 * Overlay: WRP
 * Description: All warp rooms.
 */

#include "stage.h"

typedef struct {
    s16 x, y;
} WarpCoord;

// *** Overlay exports start ***
void Update(void);
void TestCollisions(void);
void func_80189FB4(LayoutObject*);
void func_8018A520(s16);
void func_8018A7AC(void);
void func_8018CAB0(void);
void InitRoomEntities(s32 objLayoutId);
void func_801916C4(u16);
void func_80192F40(u8*, u8);

RoomHeader g_Rooms[];
s16** g_SpriteBanks[];
void* g_Cluts[];
RoomDef g_TileLayers[];
void* g_EntityGfxs[];
void func_80188514(void);

Overlay g_StageOverlay = {
    /* 0x00 */ Update,
    /* 0x04 */ TestCollisions,
    /* 0x08 */ func_8018A7AC,
    /* 0x0C */ InitRoomEntities,
    /* 0x10 */ g_Rooms,
    /* 0x14 */ g_SpriteBanks,
    /* 0x18 */ g_Cluts,
    /* 0x1C */ NULL,
    /* 0x20 */ g_TileLayers,
    /* 0x24 */ g_EntityGfxs,
    /* 0x28 */ func_80188514,
    /* 0x2C */ 0x00000000,
    /* 0x30 */ 0x00000000,
    /* 0x34 */ 0x00000000,
    /* 0x38 */ 0x00000000,
    /* 0x3C */ 0x00000000,
};

// *** Sprites and layout definition start ***
u32 D_80181D08[];
TileDefinition D_80182D68[];
TileDefinition D_80186D78;
SpriteParts* D_80186D88[];

s16** g_SpriteBanks[] = {
    /* 0x040 */ 0x00000000,
    /* 0x044 */ D_80186D88,
    /* 0x048 */ 0x00000000,
    /* 0x04C */ 0x00000000,
    /* 0x050 */ 0x00000000,
    /* 0x054 */ 0x00000000,
    /* 0x058 */ 0x00000000,
    /* 0x05C */ 0x00000000,
    /* 0x060 */ 0x00000000,
    /* 0x064 */ 0x00000000,
    /* 0x068 */ 0x00000000,
    /* 0x06C */ 0x00000000,
    /* 0x070 */ 0x00000000,
    /* 0x074 */ 0x00000000,
    /* 0x078 */ 0x00000000,
    /* 0x07C */ 0x00000000,
    /* 0x080 */ 0x00000000,
    /* 0x084 */ 0x00000000,
    /* 0x088 */ 0x00000000,
    /* 0x08C */ 0x00000000,
    /* 0x090 */ 0x00000000,
    /* 0x094 */ 0x00000000,
    /* 0x098 */ 0x00000000,
    /* 0x09C */ 0x00000000,
};
void* D_801800A0[] = {
    /* 0x0A0 */ (void*)0x00000005,
    /* 0x0A4 */ (void*)0x00002000,
    /* 0x0A8 */ (void*)0x00000010,
    /* 0x0AC */ (void*)D_80181D08,
    /* 0x0B0 */ (void*)0xFFFFFFFF,
};
void* g_Cluts[] = {
    /* 0x0B4 */ D_801800A0,
};

u16 D_80181D68[];
u16 D_80181F68[];
u16 D_80182168[];
u16 D_80182368[];
u16 D_80182568[];
u16 D_80182768[];
LayerDef D_801800B8 = {0, 0, 0, 0, 0, 0};
LayerDef D_801800C8 = {D_80181D68, &D_80186D78, 0x01328328, 0x60, 3, 0};
LayerDef D_801800D8 = {D_80181F68, &D_80186D78, 0x01565565, 0x60, 3, 0};
LayerDef D_801800E8 = {D_80182168, &D_80186D78, 0x0147B47B, 0x60, 3, 0};
LayerDef D_801800F8 = {D_80182368, &D_80186D78, 0x0198F98F, 0x60, 3, 0};
LayerDef D_80180108 = {D_80182568, &D_80186D78, 0x01B23B23, 0x60, 3, 0};
LayerDef D_80180118 = {D_80182768, &D_80182D68, 0x40B22B22, 0x20, 3, 2};
LayerDef D_80180128 = {D_80182768, &D_80182D68, 0x41990990, 0x1F, 3, 2};
LayerDef D_80180138 = {D_80182768, &D_80182D68, 0x40564564, 0x1E, 3, 2};
LayerDef D_80180148 = {D_80182768, &D_80182D68, 0x4147C47C, 0x1D, 3, 2};
LayerDef D_80180158 = {D_80182768, &D_80182D68, 0x40327327, 0x1C, 3, 2};
RoomDef g_TileLayers[] = {
    /* 0x168 */ {&D_801800C8, &D_801800B8},
    /* 0x170 */ {&D_801800D8, &D_801800B8},
    /* 0x178 */ {&D_801800E8, &D_801800B8},
    /* 0x180 */ {&D_801800F8, &D_801800B8},
    /* 0x188 */ {&D_80180108, &D_801800B8},
    /* 0x190 */ {&D_80180118, &D_801800B8},
    /* 0x198 */ {&D_80180128, &D_801800B8},
    /* 0x1A0 */ {&D_80180138, &D_801800B8},
    /* 0x1A8 */ {&D_80180148, &D_801800B8},
    /* 0x1B0 */ {&D_80180158, &D_801800B8},
};

u32 D_80181420[];
u32 D_80181764[];
void* D_801801B8[] = {
    /* 0x1B8 */ (void*)0x00000000,
    /* 0x1BC */ (void*)0x00000000,
    /* 0x1C0 */ (void*)0x00000000,
    /* 0x1C4 */ (void*)0x00000000,
    /* 0x1C8 */ (void*)0xFFFFFFFF,
};
void* D_801801CC[] = {
    /* 0x1CC */ (void*)0x00000004,
    /* 0x1D0 */ (void*)0x00400100,
    /* 0x1D4 */ (void*)0x00800080,
    /* 0x1D8 */ (void*)D_80181420,
    /* 0x1DC */ (void*)0x00600100,
    /* 0x1E0 */ (void*)0x00800080,
    /* 0x1E4 */ (void*)D_80181764,
    /* 0x1E8 */ (void*)0xFFFFFFFF,
};
void* g_EntityGfxs[] = {
    /* 0x1EC */ D_801801B8,
    /* 0x1F0 */ D_801801B8,
    /* 0x1F4 */ D_801801B8,
    /* 0x1F8 */ D_801801B8,
    /* 0x1FC */ D_801801B8,
    /* 0x200 */ D_801801CC,
    /* 0x204 */ D_801801B8,
    /* 0x208 */ D_801801B8,
    /* 0x20C */ D_801801B8,
    /* 0x210 */ D_801801B8,
    /* 0x214 */ D_801801B8,
    /* 0x218 */ D_801801B8,
    /* 0x21C */ D_801801B8,
    /* 0x220 */ D_801801B8,
    /* 0x224 */ D_801801B8,
    /* 0x228 */ D_801801B8,
    /* 0x22C */ D_801801B8,
    /* 0x230 */ D_801801B8,
    /* 0x234 */ D_801801B8,
    /* 0x238 */ D_801801B8,
};
// *** Layout definition end ***

// *** Layout object definition start ***
LayoutObject D_80181228[];
LayoutObject D_80181250[];
LayoutObject D_801812A0[];
LayoutObject D_801812C8[];
LayoutObject D_80181278[];
LayoutObject D_801812F0[];
LayoutObject D_80181304[];
LayoutObject* g_pStObjLayout[] = {
    /* 0x23C */ D_801812F0,
    /* 0x240 */ D_80181228,
    /* 0x244 */ D_80181250,
    /* 0x248 */ D_801812A0,
    /* 0x24C */ D_801812C8,
    /* 0x250 */ D_80181278,
    /* 0x254 */ D_801812F0,
    /* 0x258 */ D_801812F0,
    /* 0x25C */ D_801812F0,
    /* 0x260 */ D_801812F0,
    /* 0x264 */ D_801812F0,
    /* 0x268 */ D_801812F0,
    /* 0x26C */ D_801812F0,
    /* 0x270 */ D_801812F0,
    /* 0x274 */ D_801812F0,
    /* 0x278 */ D_801812F0,
    /* 0x27C */ D_801812F0,
    /* 0x280 */ D_801812F0,
    /* 0x284 */ D_801812F0,
    /* 0x288 */ D_801812F0,
    /* 0x28C */ D_801812F0,
    /* 0x290 */ D_801812F0,
    /* 0x294 */ D_801812F0,
    /* 0x298 */ D_801812F0,
    /* 0x29C */ D_801812F0,
    /* 0x2A0 */ D_801812F0,
    /* 0x2A4 */ D_801812F0,
    /* 0x2A8 */ D_801812F0,
    /* 0x2AC */ D_801812F0,
    /* 0x2B0 */ D_801812F0,
    /* 0x2B4 */ D_801812F0,
    /* 0x2B8 */ D_801812F0,
    /* 0x2BC */ D_801812F0,
    /* 0x2C0 */ D_801812F0,
    /* 0x2C4 */ D_801812F0,
    /* 0x2C8 */ D_801812F0,
    /* 0x2CC */ D_801812F0,
    /* 0x2D0 */ D_801812F0,
    /* 0x2D4 */ D_801812F0,
    /* 0x2D8 */ D_801812F0,
    /* 0x2DC */ D_801812F0,
    /* 0x2E0 */ D_801812F0,
    /* 0x2E4 */ D_801812F0,
    /* 0x2E8 */ D_801812F0,
    /* 0x2EC */ D_801812F0,
    /* 0x2F0 */ D_801812F0,
    /* 0x2F4 */ D_801812F0,
    /* 0x2F8 */ D_801812F0,
    /* 0x2FC */ D_80181304,
    /* 0x300 */ D_80181304,
    /* 0x304 */ D_80181304,
    /* 0x308 */ D_80181304,
    /* 0x30C */ D_80181304,
};

LayoutObject D_80181324[];
LayoutObject D_8018134C[];
LayoutObject D_80181374[];
LayoutObject D_8018139C[];
LayoutObject D_801813C4[];
LayoutObject D_801813EC[];
LayoutObject D_80181400[];
LayoutObject* D_80180310[] = {
    /* 310 */ D_801813EC,
    /* 314 */ D_80181324,
    /* 318 */ D_8018134C,
    /* 31C */ D_8018139C,
    /* 320 */ D_801813C4,
    /* 324 */ D_80181374,
    /* 328 */ D_801813EC,
    /* 32C */ D_801813EC,
    /* 330 */ D_801813EC,
    /* 334 */ D_801813EC,
    /* 338 */ D_801813EC,
    /* 33C */ D_801813EC,
    /* 340 */ D_801813EC,
    /* 344 */ D_801813EC,
    /* 348 */ D_801813EC,
    /* 34C */ D_801813EC,
    /* 350 */ D_801813EC,
    /* 354 */ D_801813EC,
    /* 358 */ D_801813EC,
    /* 35C */ D_801813EC,
    /* 360 */ D_801813EC,
    /* 364 */ D_801813EC,
    /* 368 */ D_801813EC,
    /* 36C */ D_801813EC,
    /* 370 */ D_801813EC,
    /* 374 */ D_801813EC,
    /* 378 */ D_801813EC,
    /* 37C */ D_801813EC,
    /* 380 */ D_801813EC,
    /* 384 */ D_801813EC,
    /* 388 */ D_801813EC,
    /* 38C */ D_801813EC,
    /* 390 */ D_801813EC,
    /* 394 */ D_801813EC,
    /* 398 */ D_801813EC,
    /* 39C */ D_801813EC,
    /* 3A0 */ D_801813EC,
    /* 3A4 */ D_801813EC,
    /* 3A8 */ D_801813EC,
    /* 3AC */ D_801813EC,
    /* 3B0 */ D_801813EC,
    /* 3B4 */ D_801813EC,
    /* 3B8 */ D_801813EC,
    /* 3BC */ D_801813EC,
    /* 3C0 */ D_801813EC,
    /* 3C4 */ D_801813EC,
    /* 3C8 */ D_801813EC,
    /* 3CC */ D_801813EC,
    /* 3D0 */ D_80181400,
    /* 3D4 */ D_80181400,
    /* 3D8 */ D_80181400,
    /* 3DC */ D_80181400,
};
// *** Layout object definition end ***

// *** Object definition start ***
void func_80186FD0(Entity*);
void func_801870B0(Entity*);
void func_8018F510(Entity*);
void func_8018F838(Entity*);
void func_8018F928(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
PfnEntityUpdate PfnEntityUpdates[] = {
    /* 3E0 */ (PfnEntityUpdate)D_80181400,
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)EntityExplosion,
    /* 3EC */ (PfnEntityUpdate)EntityPriceDrop,
    /* 3F0 */ (PfnEntityUpdate)EntityNumericDamage,
    /* 3F4 */ (PfnEntityUpdate)EntityRedDoor,
    /* 3F8 */ (PfnEntityUpdate)EntityIntenseExplosion,
    /* 3FC */ (PfnEntityUpdate)EntityAbsorbOrb,
    /* 400 */ (PfnEntityUpdate)EntityRoomForeground,
    /* 404 */ (PfnEntityUpdate)EntityStageNamePopup,
    /* 408 */ (PfnEntityUpdate)EntityInventoryDrop,
    /* 40C */ (PfnEntityUpdate)EntityRelicOrb,
    /* 410 */ (PfnEntityUpdate)EntityHeartDrop,
    /* 414 */ (PfnEntityUpdate)EntityEnemyBlood,
    /* 418 */ (PfnEntityUpdate)EntityUnkId0E,
    /* 41C */ (PfnEntityUpdate)EntityDummy,
    /* 420 */ (PfnEntityUpdate)EntityDummy,
    /* 424 */ (PfnEntityUpdate)func_80186FD0, // unused
    /* 428 */ (PfnEntityUpdate)func_801870B0, // unused? looks debugging stuff
    /* 42C */ (PfnEntityUpdate)func_8018F510,
    /* 430 */ (PfnEntityUpdate)func_8018F838,
    /* 434 */ (PfnEntityUpdate)func_8018F928,
    /* 438 */ (PfnEntityUpdate)EntityWarpRoom,
    /* 43C */ (PfnEntityUpdate)EntityWarpSmallRocks,
};

u16 g_eBreakableInit[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u16 D_8018044C[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 D_80180458[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 D_80180470[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 D_8018047C[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 D_80180488[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 D_80180494[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 D_801804A0[] = {
    /**/ 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
    /**/ 0x8001, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
    /**/ 0x800B, 0x0001, 0x0048, 0x021A, 0x0061, 0x0000,
};
u16 D_801804C4[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
// *** Object definition end ***

// *** Object declaration start ***
// owned by func_80186FD0
u32 D_801804D0[] = {0x00FF0140};
u32 D_801804D4[] = {0x26022502, 0x26022702, 0x00000000};
ObjInit2 D_801804E0[] = {
    {0x0006, 0x01FA, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0x00000000,
     D_801804D0},
    {0x8001, 0x00C0, 0x0000, 0x0000, 0x03, 0x00, 0x30, 0x00, 0x00000000,
     D_801804D4},
};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 D_80180508[] = {
    /* 508 */ 0x001D, 0x0025, 0x0075, 0x007D,
    /* 510 */ 0x00C6, 0x00C7, 0x00C8, 0x00C9,
    /* 518 */ 0x001F, 0x0027, 0x0077, 0x007F,
    /* 520 */ 0x00CA, 0x00CB, 0x00CC, 0x00CD,
};

// owned by func_801870B0
u8 D_80180528[] = {
    /* 528 */ 0x20,
    /* 529 */ 0x20,
    /* 52A */ 0x20,
    /* 52B */ 0x20,
    /* 52C */ 0x20,
    /* 52D */ 0x20,
    /* 52E */ 0x50,
    /* 52F */ 0x20,
};
u8 D_80180530[] = {
    /* 530 */ 0x00,
    /* 531 */ 0x00,
    /* 532 */ 0x00,
    /* 533 */ 0x00,
    /* 534 */ 0x00,
    /* 535 */ 0x00,
    /* 536 */ 0x00,
    /* 537 */ 0x00,
};
u16 D_80180538[] = {
    /* 538 */ 0x0000,
    /* 53A */ 0x0000,
    /* 53C */ 0x0600,
    /* 53E */ 0x0100,
    /* 540 */ 0x0000,
    /* 542 */ 0x0000,
    /* 544 */ 0x0600,
    /* 546 */ 0x01FC,
    /* 548 */ 0x0000,
    /* 54A */ 0x00FC,
    /* 54C */ 0x0600,
    /* 54E */ 0x01FC,
    /* 550 */ 0x0000,
    /* 552 */ 0x0000,
    /* 554 */ 0x0600,
    /* 556 */ 0x01FC,
    /* 558 */ 0x0000,
    /* 55A */ 0x00FC,
    /* 55C */ 0x0600,
    /* 55E */ 0x0300,
    /* 560 */ 0x0000,
    /* 562 */ 0x00FC,
    /* 564 */ 0x0600,
    /* 566 */ 0x01FC,
    /* 568 */ 0x0000,
    /* 56A */ 0x00FC,
    /* 56C */ 0x0600,
    /* 56E */ 0x0300,
    /* 570 */ 0x0000,
    /* 572 */ 0x0200,
    /* 574 */ 0x0600,
    /* 576 */ 0x0300,
    /* 578 */ 0x0000,
    /* 57A */ 0x01FC,
    /* 57C */ 0x0500,
    /* 57E */ 0x02FC,
    /* 580 */ 0x0000,
    /* 582 */ 0x0000,
    /* 584 */ 0x0500,
    /* 586 */ 0x0400,
    /* 588 */ 0x0000,
    /* 58A */ 0x0000,
    /* 58C */ 0x0500,
    /* 58E */ 0x0400,
    /* 590 */ 0x0000,
    /* 592 */ 0x01FC,
    /* 594 */ 0x0500,
    /* 596 */ 0x02FC,
    /* 598 */ 0x00F0,
    /* 59A */ 0x01FC,
    /* 59C */ 0x0310,
    /* 59E */ 0x02FC,
    /* 5A0 */ 0x00F0,
    /* 5A2 */ 0x01FC,
    /* 5A4 */ 0x0310,
    /* 5A6 */ 0x02FC,
};

// owned by EntityBreakable
u8 D_801805A8[] = {4, 1, 4, 2, 0, 0, 0, 0};
u8 D_801805B0[] = {4, 0, 4, 0, 0, 0, 0, 0};
u8* g_eBreakableAnimations[] = {
    /* 5B8 */ D_801805A8,
    /* 5BC */ D_801805B0,
    /* 5C0 */ 0,
    /* 5C4 */ 0,
    /* 5C8 */ 0,
    /* 5CC */ 0,
    /* 5D0 */ 0,
    /* 5D4 */ 0,
};
u8 g_eBreakableHitboxes[] = {
    /* 5D8 */ 8,
    /* 5D9 */ 8,
    /* 5DA */ 0,
    /* 5DB */ 0,
    /* 5DC */ 0,
    /* 5DD */ 0,
    /* 5DE */ 0,
    /* 5DF */ 0,
};
u8 g_eBreakableExplosionTypes[] = {
    /* 5E0 */ 0,
    /* 5E1 */ 0,
    /* 5E2 */ 0,
    /* 5E3 */ 0,
    /* 5E4 */ 0,
    /* 5E5 */ 0,
    /* 5E6 */ 0,
    /* 5E7 */ 0,
};
u16 g_eBreakableanimSets[] = {
    /* 5E8 */ 3,
    /* 5EA */ 3,
    /* 5EC */ 0,
    /* 5EE */ 0,
    /* 5F0 */ 0,
    /* 5F2 */ 0,
    /* 5F4 */ 0,
    /* 5F6 */ 0,
};
u8 g_eBreakableBlendModes[] = {
    /* 5F8 */ 0x70,
    /* 5F9 */ 0x30,
    /* 5FA */ 0x00,
    /* 5FB */ 0x00,
    /* 5FC */ 0x00,
    /* 5FD */ 0x00,
    /* 5FE */ 0x00,
    /* 5FF */ 0x00,
    /* 600 */ 0x00,
    /* 601 */ 0x00,
    /* 602 */ 0x00,
    /* 603 */ 0x00,
    /* 604 */ 0x00,
    /* 605 */ 0x00,
    /* 606 */ 0x00,
    /* 607 */ 0x00,
};

// owned by func_1873A0
u32 D_80180608[] = {
    /* 608 */ 0x00000000,
    /* 60C */ 0x00000200,
    /* 610 */ 0x00000400,
    /* 614 */ 0x00000600,
    /* 618 */ 0x00000800,
    /* 61C */ 0x00000A00,
    /* 620 */ 0x00000C00,
    /* 624 */ 0x00000E00,
    /* 628 */ 0x00001000,
    /* 62C */ 0x00001200,
    /* 630 */ 0x00001400,
    /* 634 */ 0x00001600,
    /* 638 */ 0x00001800,
    /* 63C */ 0x00001A00,
    /* 640 */ 0x00001C00,
    /* 644 */ 0x00001E00,
};

// owned by EntityWarpRoom
u32 D_80180648[] = {
    /* 648 */ 0x00000000,
    /* 64C */ 0x00040000,
    /* 650 */ 0x00040000,
    /* 654 */ 0xFFFC0004,
    /* 658 */ 0x0000FFF8,
};
WarpCoord D_8018065C[] = {
    /* 65C */ {0x000F, 0x0026},
    /* 660 */ {0x0023, 0x002C},
    /* 664 */ {0x003B, 0x0011},
    /* 668 */ {0x0028, 0x000C},
    /* 66C */ {0x0025, 0x0015},
    /* 670 */ {0x0000, 0x0000},
    /* 674 */ {0x0000, 0x0000},
    /* 678 */ {0x0001, 0x0000},
    /* 67C */ {0x0001, 0x0000},
    /* 680 */ {0x0001, 0x0001},
    /* 684 */ {0x0001, 0x0001},
    /* 688 */ {0x0001, 0x0001},
    /* 68C */ {0x0001, 0x0101},
};
// *** Object declaration end ***

// *** Unknown stuff start ***
u16 D_80180690[] = {
    /* 690 */ 0x8163,
    /* 692 */ 0x8164,
    /* 694 */ 0x8166,
    /* 696 */ 0x8164,
    /* 698 */ 0x8160,
    /* 69A */ 0x8166,
    /* 69C */ 0x8162,
    /* 69E */ 0x8164,
    /* 6A0 */ 0x8167,
    /* 6A2 */ 0x8164,
    /* 6A4 */ 0x8167,
    /* 6A6 */ 0x8168,
    /* 6A8 */ 0x8168,
    /* 6AA */ 0x8164,
    /* 6AC */ 0x8161,
    /* 6AE */ 0x8164,
    /* 6B0 */ 0x8165,
    /* 6B2 */ 0x8165,
    /* 6B4 */ 0x8163,
    /* 6B6 */ 0x8163,
    /* 6B8 */ 0x8165,
    /* 6BA */ 0x8165,
};

u16 D_801806BC[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x001E, 0x0000, 0x0000,
    0x002B, 0x0000, 0x0010, 0x0000, 0x000D, 0x0068, 0x0068, 0x0016, 0x0000,
    0x0000, 0x0000, 0x003E, 0x0000, 0x0023, 0x0050, 0x0000, 0x0000, 0x0000,
    0x0006, 0x0000, 0x000A, 0x0000, 0x007D, 0x0000, 0x0000, 0x002D, 0x0000,
    0x0000, 0x006D, 0x007B, 0x0000, 0x0017, 0x0041, 0x0000, 0x0073, 0x0000,
    0x004C, 0x0000, 0x0000, 0x0038, 0x0014, 0x005C, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0046, 0x0000,
    0x0000, 0x0003, 0x0058, 0x0044, 0x0024, 0x0037, 0x0000, 0x0002, 0x0059,
    0x0000, 0x0000, 0x0000, 0x0007, 0x0000, 0x0056, 0x0000, 0x007C, 0x0000,
    0x000B, 0x0000, 0x0026, 0x0000, 0x001D, 0x0000, 0x0000, 0x002A, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0027, 0x0000, 0x0000, 0x0000, 0x001C, 0x0000,
    0x0031, 0x0000, 0x0000, 0x001A, 0x0000, 0x008D, 0x0009, 0x002C, 0x0030,
    0x0020, 0x0000, 0x0005, 0x0047, 0x0000, 0x005E, 0x0035, 0x0034, 0x006A,
    0x0000, 0x003A, 0x0000, 0x0066, 0x0000, 0x0045, 0x0000, 0x0019, 0x0000,
    0x0071, 0x0000, 0x0029, 0x0039, 0x0000, 0x0051, 0x0000, 0x004D, 0x0000,
    0x0000, 0x003F, 0x0000, 0x0077, 0x0000, 0x0000, 0x0072, 0x0000, 0x0000,
    0x006F, 0x0000, 0x002F, 0x0000, 0x0074, 0x0000, 0x0000, 0x0079, 0x0000,
    0x007A, 0x0000, 0x0000, 0x0013, 0x0011, 0x0036, 0x0036, 0x0000, 0x005F,
    0x005F, 0x0000, 0x0000, 0x0067, 0x0000, 0x0075, 0x0000, 0x0001, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0008, 0x0000, 0x0000, 0x000E, 0x0000,
    0x002E, 0x0000, 0x0069, 0x0021, 0x0000, 0x0000, 0x0055, 0x0000, 0x0054,
    0x0000, 0x0053, 0x0000, 0x0000, 0x000F, 0x0000, 0x0076, 0x0000, 0x0000,
    0x008E, 0x0000, 0x0000, 0x0000, 0x0000, 0x004A, 0x0000, 0x0000, 0x004B,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0043, 0x0000, 0x0000, 0x003D, 0x0000,
    0x0078, 0x008A, 0x0000, 0x0000, 0x0000, 0x0052, 0x0000, 0x0000, 0x0089,
    0x0048, 0x0000, 0x003C, 0x0040, 0x008B, 0x0000, 0x0000, 0x0000, 0x001F,
    0x0000, 0x0000, 0x007E, 0x0000, 0x0000, 0x0049, 0x0000, 0x0000, 0x0000,
    0x0015, 0x0000, 0x0000, 0x000C, 0x0028, 0x0000, 0x0000, 0x0000, 0x0032,
    0x0000, 0x0022, 0x0012, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0033, 0x0060, 0x0000, 0x0064, 0x0000, 0x0000, 0x007F, 0x0000, 0x0000,
    0x0000, 0x004E, 0x0000, 0x006E, 0x0000, 0x0000, 0x0000, 0x004F, 0x0000,
    0x0000, 0x0057, 0x0000, 0x0000, 0x0000, 0x0086, 0x0065, 0x0000, 0x003B,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0025, 0x0062, 0x0062,
    0x0000, 0x0000, 0x0000, 0x0042, 0x0000, 0x0000, 0x0018, 0x001B, 0x006B,
    0x0000, 0x008C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0061, 0x0063,
    0x0088, 0x0000, 0x0000, 0x0000, 0x0085, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0084, 0x0000, 0x0000, 0x0087, 0x0000, 0x0000, 0x0000, 0x0000,
    0x005D, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x005B,
    0x0091, 0x0000, 0x0000, 0x0000, 0x0000, 0x0090, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x005A, 0x0000, 0x0000, 0x0082, 0x0000, 0x0000,
    0x0000, 0x0083, 0x0000, 0x0081, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0092, 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0070,
    0x0000, 0x0000, 0x006C, 0x0000, 0x0000, 0x0080, 0x0080, 0x0000, 0x0000,
    0x008F, 0x0000, 0x0000, 0x0000,
};

u8 D_801809DC[] = {
    /* 9DC */ 0x00,
    /* 9DD */ 0x40,
    /* 9DE */ 0x20,
    /* 9DF */ 0x10,
};

u8 D_801809E0[] = {
    /* 9E0 */ 0x80,
    /* 9E1 */ 0x80,
    /* 9E2 */ 0xA0,
    /* 9E3 */ 0xA0,
    /* 9E4 */ 0xC0,
    /* 9E5 */ 0xC0,
    /* 9E6 */ 0x00,
    /* 9E7 */ 0x00,
};

u8 D_801809E8[] = {
    /* 9E8 */ 0x60,
    /* 9E9 */ 0x60,
    /* 9EA */ 0x60,
    /* 9EB */ 0x60,
    /* 9EC */ 0x60,
    /* 9ED */ 0x60,
    /* 9EE */ 0x00,
    /* 9EF */ 0x00,
};

u16 D_801809F0[] = {
    /* 9F0 */ 0x8000,
    /* 9F2 */ 0x4000,
    /* 9F4 */ 0x2000,
    /* 9F6 */ 0x1000,
    /* 9F8 */ 0x0800,
    /* 9FA */ 0x0200,
    /* 9FC */ 0x0100,
    /* 9FE */ 0x0080,
    /* A00 */ 0x0400,
    /* A02 */ 0x0040,
};

u8 D_80180A04[] = {
    /* A04 */ 0x02,
    /* A05 */ 0x04,
    /* A06 */ 0x03,
    /* A07 */ 0x05,
    /* A08 */ 0x06,
    /* A09 */ 0x07,
    /* A0A */ 0x08,
    /* A0B */ 0x0A,
    /* A0C */ 0x02,
    /* A0D */ 0x01,
    /* A0E */ 0x00,
    /* A0F */ 0x00,
};

u16 D_80180A10[] = {
    /* A10 */ 0x0003,
    /* A12 */ 0x0000,
    /* A14 */ 0x0002,
    /* A16 */ 0x0003,
    /* A18 */ 0x0003,
    /* A1A */ 0x0003,
    /* A1C */ 0x0003,
    /* A1E */ 0x0003,
    /* A20 */ 0x0003,
    /* A22 */ 0x0004,
    /* A24 */ 0x0004,
    /* A26 */ 0x0004,
    /* A28 */ 0x0004,
    /* A2A */ 0x0005,
    /* A2C */ 0x0005,
    /* A2E */ 0x0000,
    /* A30 */ 0x0000,
    /* A32 */ 0x0000,
    /* A34 */ 0x0000,
    /* A36 */ 0x0000,
    /* A38 */ 0x0000,
    /* A3A */ 0x0000,
    /* A3C */ 0x0000,
    /* A3E */ 0x0000,
    /* A40 */ 0x0000,
    /* A42 */ 0x0000,
    /* A44 */ 0x0001,
    /* A46 */ 0x0001,
    /* A48 */ 0x0002,
    /* A4A */ 0x0006,
    /* A4C */ 0x0007,
    /* A4E */ 0x00C6,
};

u16 D_80180A50[] = {
    /* A50 */ 0x0C00,
    /* A52 */ 0x0168,
    /* A54 */ 0x0F00,
    /* A56 */ 0x0169,
    /* A58 */ 0x0FD0,
    /* A5A */ 0x016A,
    /* A5C */ 0x0FF0,
    /* A5E */ 0x016B,
    /* A60 */ 0x0FF8,
    /* A62 */ 0x016C,
    /* A64 */ 0x0FFD,
    /* A66 */ 0x016D,
    /* A68 */ 0x0FFF,
    /* A6A */ 0x016E,
};

u16 D_80180A6C[] = {
    /* A6C */ 0x01B2,
    /* A6E */ 0x01B3,
    /* A70 */ 0x01B6,
    /* A72 */ 0x01B7,
    /* A74 */ 0x01B4,
    /* A76 */ 0x01B5,
    /* A78 */ 0x01B0,
    /* A7A */ 0x01B1,
};

u8 D_80180A7C[] = {
    /* A7C */ 0xB1,
    /* A7D */ 0xB7,
    /* A7E */ 0xB1,
    /* A7F */ 0xB7,
    /* A80 */ 0x21,
    /* A81 */ 0x21,
    /* A82 */ 0x5F,
    /* A83 */ 0x5F,
    /* A84 */ 0x88,
    /* A85 */ 0xA8,
    /* A86 */ 0x88,
    /* A87 */ 0xA8,
    /* A88 */ 0x21,
    /* A89 */ 0x21,
    /* A8A */ 0x5F,
    /* A8B */ 0x5F,
    /* A8C */ 0xA8,
    /* A8D */ 0x88,
    /* A8E */ 0xA8,
    /* A8F */ 0x88,
    /* A90 */ 0x21,
    /* A91 */ 0x21,
    /* A92 */ 0x5F,
    /* A93 */ 0x5F,
};

s16 D_80180A94[] = {
    0x0000, 0x0065, 0x00C9, 0x012D, 0x0191, 0x01F5, 0x0259, 0x02BC, 0x031F,
    0x0381, 0x03E3, 0x0444, 0x04A5, 0x0505, 0x0564, 0x05C2, 0x061F, 0x067C,
    0x06D7, 0x0732, 0x078B, 0x07E3, 0x083A, 0x088F, 0x08E4, 0x0937, 0x0988,
    0x09D8, 0x0A26, 0x0A73, 0x0ABF, 0x0B08, 0x0B50, 0x0B97, 0x0BDB, 0x0C1E,
    0x0C5E, 0x0C9D, 0x0CDA, 0x0D15, 0x0D4E, 0x0D85, 0x0DB9, 0x0DEC, 0x0E1C,
    0x0E4B, 0x0E77, 0x0EA1, 0x0EC8, 0x0EEE, 0x0F11, 0x0F31, 0x0F50, 0x0F6C,
    0x0F85, 0x0F9C, 0x0FB1, 0x0FC4, 0x0FD4, 0x0FE1, 0x0FEC, 0x0FF5, 0x0FFB,
    0x0FFF, 0x1000, 0x0FFF, 0x0FFB, 0x0FF5, 0x0FEC, 0x0FE1, 0x0FD4, 0x0FC4,
    0x0FB1, 0x0F9C, 0x0F85, 0x0F6C, 0x0F50, 0x0F31, 0x0F11, 0x0EEE, 0x0EC8,
    0x0EA1, 0x0E77, 0x0E4B, 0x0E1C, 0x0DEC, 0x0DB9, 0x0D85, 0x0D4E, 0x0D15,
    0x0CDA, 0x0C9D, 0x0C5E, 0x0C1E, 0x0BDB, 0x0B97, 0x0B50, 0x0B08, 0x0ABF,
    0x0A73, 0x0A26, 0x09D8, 0x0988, 0x0937, 0x08E4, 0x088F, 0x083A, 0x07E3,
    0x078B, 0x0732, 0x06D7, 0x067C, 0x061F, 0x05C2, 0x0564, 0x0505, 0x04A5,
    0x0444, 0x03E3, 0x0381, 0x031F, 0x02BC, 0x0259, 0x01F5, 0x0191, 0x012D,
    0x00C9, 0x0065, 0x0000, 0xFF9B, 0xFF37, 0xFED3, 0xFE6F, 0xFE0B, 0xFDA7,
    0xFD44, 0xFCE1, 0xFC7F, 0xFC1D, 0xFBBC, 0xFB5B, 0xFAFB, 0xFA9C, 0xFA3E,
    0xF9E1, 0xF984, 0xF929, 0xF8CE, 0xF875, 0xF81D, 0xF7C6, 0xF771, 0xF71C,
    0xF6C9, 0xF678, 0xF628, 0xF5DA, 0xF58D, 0xF541, 0xF4F8, 0xF4B0, 0xF469,
    0xF425, 0xF3E2, 0xF3A2, 0xF363, 0xF326, 0xF2EB, 0xF2B2, 0xF27B, 0xF247,
    0xF214, 0xF1E4, 0xF1B5, 0xF189, 0xF15F, 0xF138, 0xF112, 0xF0EF, 0xF0CF,
    0xF0B0, 0xF094, 0xF07B, 0xF064, 0xF04F, 0xF03C, 0xF02C, 0xF01F, 0xF014,
    0xF00B, 0xF005, 0xF001, 0xF000, 0xF001, 0xF005, 0xF00B, 0xF014, 0xF01F,
    0xF02C, 0xF03C, 0xF04F, 0xF064, 0xF07B, 0xF094, 0xF0B0, 0xF0CF, 0xF0EF,
    0xF112, 0xF138, 0xF15F, 0xF189, 0xF1B5, 0xF1E4, 0xF214, 0xF247, 0xF27B,
    0xF2B2, 0xF2EB, 0xF326, 0xF363, 0xF3A2, 0xF3E2, 0xF425, 0xF469, 0xF4B0,
    0xF4F8, 0xF541, 0xF58D, 0xF5DA, 0xF628, 0xF678, 0xF6C9, 0xF71C, 0xF771,
    0xF7C6, 0xF81D, 0xF875, 0xF8CE, 0xF929, 0xF984, 0xF9E1, 0xFA3E, 0xFA9C,
    0xFAFB, 0xFB5B, 0xFBBC, 0xFC1D, 0xFC7F, 0xFCE1, 0xFD44, 0xFDA7, 0xFE0B,
    0xFE6F, 0xFED3, 0xFF37, 0xFF9B,
};
s16 D_80180C94[] = {
    /* C94 */ 0x0E01,
    /* C96 */ 0x0000,
};
s16 D_80180C98[] = {
    /* C98 */ 0x0302,
    /* C9A */ 0x0406,
    /* C9C */ 0x0505,
    /* C9E */ 0x0605,
    /* CA0 */ 0x0704,
    /* CA2 */ 0x0803,
    /* CA4 */ 0x0904,
    /* CA6 */ 0x0A05,
    /* CA8 */ 0x0B05,
    /* CAA */ 0x0C06,
    /* CAC */ 0x0307,
    /* CAE */ 0x0406,
    /* CB0 */ 0x0505,
    /* CB2 */ 0x0605,
    /* CB4 */ 0x0704,
    /* CB6 */ 0x0803,
    /* CB8 */ 0x0904,
    /* CBA */ 0x0A05,
    /* CBC */ 0x0B05,
    /* CBE */ 0x0C06,
    /* CC0 */ 0x0D02,
    /* CC2 */ 0x0000,
};
s16 D_80180CC4[] = {
    /* CC4 */ 0x1404,
    /* CC6 */ 0x1507,
    /* CC8 */ 0x1606,
    /* CCA */ 0x1703,
    /* CCC */ 0x1803,
    /* CCE */ 0x1906,
    /* CD0 */ 0x1502,
    /* CD2 */ 0x0000,
};
s16 D_80180CD4[] = {
    /* CD4 */ 0x1A01,
    /* CD6 */ 0x0000,
};
s16 D_80180CD8[] = {
    /* CD8 */ 0x1B01,
    /* CDA */ 0x0000,
};
s16 D_80180CDC[] = {
    /* CDC */ 0x1C01,
    /* CDE */ 0x0000,
};
s16 D_80180CE0[] = {
    /* CE0 */ 0x1D01,
    /* CE2 */ 0x0000,
};
s16 D_80180CE4[] = {
    /* CE4 */ 0x1E01,
    /* CE6 */ 0x0000,
};
s16 D_80180CE8[] = {
    /* CE8 */ 0x1F01,
    /* CEA */ 0x0000,
};
s16 D_80180CEC[] = {
    /* CEC */ 0x2001,
    /* CEE */ 0x0000,
};
s16 D_80180CF0[] = {
    /* CF0 */ 0x2101,
    /* CF2 */ 0x0000,
};
s16 D_80180CF4[] = {
    /* CF4 */ 0x2202,
    /* CF6 */ 0x2302,
    /* CF8 */ 0x2402,
    /* CFA */ 0x2502,
    /* CFC */ 0x2602,
    /* CFE */ 0x2702,
    /* D00 */ 0x2802,
    /* D02 */ 0x2902,
    /* D04 */ 0x0000,
    /* D06 */ 0x0000,
};
s16 D_80180D08[] = {
    /* D08 */ 0x0F1A,
    /* D0A */ 0x1006,
    /* D0C */ 0x1104,
    /* D0E */ 0x1202,
    /* D10 */ 0x1104,
    /* D12 */ 0x1006,
    /* D14 */ 0x0000,
    /* D16 */ 0x0000,
};
s16 D_80180D18[] = {
    /* D18 */ 0x1301,
    /* D1A */ 0x0000,
};
s16 D_80180D1C[] = {
    /* D1C */ 0x2A05,
    /* D1E */ 0x2B05,
    /* D20 */ 0x2C05,
    /* D22 */ 0x2D05,
    /* D24 */ 0x2E05,
    /* D26 */ 0x2F05,
    /* D28 */ 0x3005,
    /* D2A */ 0x3105,
    /* D2C */ 0x0000,
    /* D2E */ 0x0000,
};
s16 D_80180D30[] = {
    /* D30 */ 0x3205,
    /* D32 */ 0x3305,
    /* D34 */ 0x3405,
    /* D36 */ 0x3505,
    /* D38 */ 0x3605,
    /* D3A */ 0x3705,
    /* D3C */ 0x3805,
    /* D3E */ 0x3905,
    /* D40 */ 0x0000,
    /* D42 */ 0x0000,
};
s16 D_80180D44[] = {
    /* D44 */ 0x3A05,
    /* D46 */ 0x3B05,
    /* D48 */ 0x3C05,
    /* D4A */ 0x3D05,
    /* D4C */ 0x3E05,
    /* D4E */ 0x3F05,
    /* D50 */ 0x4005,
    /* D52 */ 0x4105,
    /* D54 */ 0x0000,
    /* D56 */ 0x0000,
};
s16 D_80180D58[] = {
    /* D58 */ 0x4205,
    /* D5A */ 0x4305,
    /* D5C */ 0x4405,
    /* D5E */ 0x4505,
    /* D60 */ 0x4605,
    /* D62 */ 0x4705,
    /* D64 */ 0x4805,
    /* D66 */ 0x4905,
    /* D68 */ 0x0000,
    /* D6A */ 0x0000,
};
s16 D_80180D6C[] = {
    /* D6C */ 0x4A05,
    /* D6E */ 0x4B05,
    /* D70 */ 0x4C05,
    /* D72 */ 0x4D05,
    /* D74 */ 0x4E05,
    /* D76 */ 0x4F05,
    /* D78 */ 0x5005,
    /* D7A */ 0x5105,
    /* D7C */ 0x0000,
    /* D7E */ 0x0000,
};
s16 D_80180D80[] = {
    /* D80 */ 0x5205,
    /* D82 */ 0x5305,
    /* D84 */ 0x5405,
    /* D86 */ 0x5505,
    /* D88 */ 0x5605,
    /* D8A */ 0x5705,
    /* D8C */ 0x5805,
    /* D8E */ 0x5905,
    /* D90 */ 0x0000,
    /* D92 */ 0x0000,
};
s16 D_80180D94[] = {
    /* D94 */ 0x5A05,
    /* D96 */ 0x5B05,
    /* D98 */ 0x5C05,
    /* D9A */ 0x5D05,
    /* D9C */ 0x5E05,
    /* D9E */ 0x5F05,
    /* DA0 */ 0x6005,
    /* DA2 */ 0x6105,
    /* DA4 */ 0x0000,
    /* DA6 */ 0x0000,
};
s16 D_80180DA8[] = {
    /* DA8 */ 0x6205,
    /* DAA */ 0x6305,
    /* DAC */ 0x6405,
    /* DAE */ 0x6505,
    /* DB0 */ 0x6605,
    /* DB2 */ 0x6705,
    /* DB4 */ 0x6805,
    /* DB6 */ 0x6905,
    /* DB8 */ 0x0000,
    /* DBA */ 0x0000,
};
s16 D_80180DBC[] = {
    /* DBC */ 0x6A05,
    /* DBE */ 0x6B05,
    /* DC0 */ 0x6C05,
    /* DC2 */ 0x6D05,
};

u16 D_80180DC4[] = {
    /* DC4 */ 0x6E05,
    /* DC6 */ 0x6F05,
    /* DC8 */ 0x7005,
    /* DCA */ 0x7105,
    /* DCC */ 0x0000,
    /* DCE */ 0x0000,
};
s16 D_80180DD0[] = {
    /* DD0 */ 0x8F01,
    /* DD2 */ 0x0000,
    /* DD4 */ 0xFCFC,
    /* DD6 */ 0xFC04,
    /* DD8 */ 0x04FC,
    /* DDA */ 0x0404,
    /* DDC */ 0x0080,
    /* DDE */ 0x0000,
    /* DE0 */ 0x0001,
    /* DE2 */ 0x0002,
    /* DE4 */ 0x0004,
    /* DE6 */ 0x0003,
    /* DE8 */ 0x0006,
    /* DEA */ 0x0005,
    /* DEC */ 0x0007,
    /* DEE */ 0x0008,
    /* DF0 */ 0x0009,
    /* DF2 */ 0x0000,
};

u16 D_80180DF4[] = {
    /* DF4 */ 0x0000,
    /* DF6 */ 0x000E,
    /* DF8 */ 0x000F,
    /* DFA */ 0x0011,
    /* DFC */ 0x0010,
    /* DFE */ 0x0013,
    /* E00 */ 0x0012,
    /* E02 */ 0x0014,
    /* E04 */ 0x0015,
    /* E06 */ 0x0016,
};

extern u8 D_80186EC0[];
extern u8 D_80186EC8[];
extern u8 D_80186ED0[];
extern u8 D_80186ED8[];
extern u8 D_80186EE0[];
extern u8 D_80186EE8[];
extern u8 D_80186EF0[];
extern u8 D_80186EF8[];
extern u8 D_80186F00[];
extern u8 D_80186F08[];
u8* D_80180E08[] = {
    // u8 is an assumption
    /* E08 */ D_80186F08,
    /* E0C */ D_80186F00,
    /* E10 */ D_80186EF8,
    /* E14 */ D_80186EF0,
    /* E18 */ D_80186EE8,
    /* E1C */ D_80186EE0,
    /* E20 */ D_80186ED8,
    /* E24 */ D_80186ED0,
    /* E28 */ D_80186EC8,
    /* E2C */ D_80186EC0,
};

s32 c_GoldPrizes[] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

s16* D_80180E58[] = {
    /* E58 */ D_80180C94,
    /* E5C */ D_80180C98,
    /* E60 */ D_80180CC4,
    /* E64 */ D_80180CD4,
    /* E68 */ D_80180CD8,
    /* E6C */ D_80180CDC,
    /* E70 */ D_80180CE0,
    /* E74 */ D_80180CE4,
    /* E78 */ D_80180CE8,
    /* E7C */ D_80180CEC,
    /* E80 */ D_80180CF0,
    /* E84 */ D_80180CF4,
    /* E88 */ D_80180D08,
    /* E8C */ D_80180D18,
    /* E90 */ D_80180D58,
    /* E94 */ D_80180D44,
    /* E98 */ D_80180D1C,
    /* E9C */ D_80180D30,
    /* EA0 */ D_80180D6C,
    /* EA4 */ D_80180D80,
    /* EA8 */ D_80180D94,
    /* EAC */ D_80180DA8,
    /* EB0 */ D_80180DBC,
    /* EB4 */ D_80180DD0,
};

u16 D_80180EB8[] = {
    0xFFFA,
    0x0004,
    0x0000,
    0xFFF8,
};

s8 c_HeartPrizes[] = {1, 5};

s32 D_80180EC4[] = {
    /* EC4 */ 0xFFFF0000,
    /* EC8 */ 0xFFFE8000,
    /* ECC */ 0xFFFE8000,
    /* ED0 */ 0xFFFE8000,
    /* ED4 */ 0xFFFD0000,
};

u8 D_80180ED8[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05,
    0x02, 0x06, 0x02, 0x07, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00,
};
u8 D_80180EEC[] = {
    0x01, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D,
    0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x02, 0x11, 0x02, 0x12,
    0x03, 0x13, 0x04, 0x14, 0x00, 0x00, 0x00, 0x00,
};
u8 D_80180F08[] = {
    0x02, 0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x18, 0x02, 0x19, 0x02, 0x1A,
    0x02, 0x1B, 0x02, 0x1C, 0x02, 0x1D, 0x02, 0x1E, 0x02, 0x1F, 0x02, 0x20,
    0x02, 0x21, 0x02, 0x22, 0x02, 0x23, 0x02, 0x24, 0x02, 0x25, 0x02, 0x26,
    0x02, 0x27, 0x02, 0x28, 0x02, 0x29, 0x02, 0x2A, 0x00, 0x00, 0x00, 0x00,
};
u8 D_80180F38[] = {
    0x02, 0x2B, 0x02, 0x2C, 0x02, 0x2D, 0x02, 0x2E, 0x02, 0x2F, 0x02,
    0x30, 0x02, 0x31, 0x02, 0x32, 0x02, 0x33, 0x02, 0x34, 0x02, 0x35,
    0x02, 0x36, 0x02, 0x37, 0x02, 0x38, 0x02, 0x39, 0x02, 0x3A, 0x02,
    0x3B, 0x02, 0x3C, 0x02, 0x3D, 0x02, 0x3E, 0x02, 0x3F, 0x02, 0x40,
    0x02, 0x41, 0x02, 0x42, 0x00, 0x00, 0x00, 0x00,
};
u8 D_80180F6C[] = {0x01, 0x43, 0x00, 0x00};

u8* D_80180F70[] = {
    D_80180ED8, D_80180EEC, D_80180F08, D_80180F38, D_80180F6C,
};

extern char D_80186F48[];
char* D_80180F84[] = {
    D_80186F48,
};

s16 D_80180F88[] = {16, 12, 8, 4, 0, -4, -8, -12};
s16 D_80180F98[] = {-32, -26, -20, -13, -7, -1, 5, 12};
s16 D_80180FA8[] = {-16, -12, -8, -4, 0, 4, 8, 12};
s16 D_80180FB8[] = {32, 26, 20, 13, 7, 1, -5, -12};
s16 D_80180FC8[] = {-8, 4, -2, 8, 0, 4, -4, 2};
s16 D_80180FD8[] = {-2, 2, 4, -3, 0, 2, -4, 3};

u16 D_80180FE8[] = {
    /* FE8 */ 0x0010,
    /* FEA */ 0x0020,
    /* FEC */ 0x0030,
    /* FEE */ 0x0040,
    /* FF0 */ 0x0050,
    /* FF2 */ 0x0060,
    /* FF4 */ 0x0070,
    /* FF6 */ 0x0000,
};

u16 D_80180FF8[] = {
    /* FF8 */ 0x0030,
    /* FFA */ 0x0050,
    /* FFC */ 0x0080,
    /* FFE */ 0x00B0,
    /* 1000 */ 0x00D0,
    /* 1002 */ 0x0100,
    /* 1004 */ 0x0100,
    /* 1006 */ 0x0000,
};

s32 D_80181008[] = {
    /* 1008 */ 0x00000400,
    /* 100C */ 0x00002400,
    /* 1010 */ 0x00003C00,
    /* 1014 */ 0x00006000,
    /* 1018 */ 0x00007800,
    /* 101C */ 0x0000C000,
};

s32 D_80181020[] = {
    /* 1020 */ 0x00000800,
    /* 1024 */ 0x00002800,
    /* 1028 */ 0x00004800,
    /* 102C */ 0x00007000,
    /* 1030 */ 0x0000E000,
    /* 1034 */ 0x00012000,
};

u8 D_80181038[] = {
    /* 1038 */ 0x01,
    /* 1039 */ 0x09,
    /* 103A */ 0x15,
    /* 103B */ 0x2B,
};

u16 D_8018103C[] = {
    /* 103C */ 0x0010,
    /* 103E */ 0x0018,
    /* 1040 */ 0x002A,
    /* 1042 */ 0x002F,
};

u32 D_80181044[] = {
    /* 1044 */ 0x00000000,
    /* 1048 */ 0x000000FF,
};

u8 D_8018104C[] = {
    2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1,
};
u16 D_8018105C[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8};
u16 D_8018107C[] = {0, 1, 3, 4, 1, 2, 4, 5, 3, 4, 6, 7, 4, 5, 7, 8, 0, 0};

u16 D_801810A0[] = {
    /* 10A0 */ 0x0820,
    /* 10A2 */ 0x0840,
    /* 10A4 */ 0x0860,
    /* 10A6 */ 0x0880,
    /* 10A8 */ 0x08C0,
    /* 10AA */ 0x0900,
    /* 10AC */ 0x0940,
    /* 10AE */ 0x0A00,
};

u16 D_801810B0[] = {
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00D0, 0x0068, 0x00D8, 0x0070,
    0xFFFD, 0xFFFD, 0x0008, 0x0008, 0x00C8, 0x0068, 0x00D0, 0x0070,
    0xFFF9, 0xFFF9, 0x0010, 0x000F, 0x00C8, 0x0070, 0x00D8, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0080, 0x0068, 0x0098, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x0098, 0x0068, 0x00B0, 0x007F,
    0xFFF5, 0xFFF5, 0x0018, 0x0017, 0x00B0, 0x0068, 0x00C8, 0x007F,
};

u32 D_80181110[] = {
    /* 1110 */ 0x03030204,
    /* 1114 */ 0x05030403,
    /* 1118 */ 0x03030603,
    /* 111C */ 0x00000000,
};
u8 D_80181120[] = {0x40, 0x01, 0xFF, 0x00};
u8 D_80181124[] = {0x40, 0x02, 0xFF, 0x00};
u8 D_80181128[] = {0x40, 0x02, 0xFF, 0x00};
u8 D_8018112C[] = {0x40, 0x01, 0xFF, 0x00};
u8 D_80181130[] = {0x40, 0x03, 0xFF, 0x00};

ObjInit2 D_80181134[] = {
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_80181120},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_80181128},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_8018112C},
    {0x0006, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_80181124},
    {0x000C, 0x01EC, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_80181130},
    {0x000C, 0x0080, 0x0000, 0x0000, 0x00, 0x00, 0x10, 0x00, 0, D_8018112C},
};
// *** Unknown stuff end ***

// *** rodata section start ***
const char D_80186E30[] = "step %x\n";
const char D_80186E3C[] = "move_room%x\n";
const char D_80186E4C[] = "for_x:%x y%x\n";
// gives some padding to align it to the next section
const char D_80186E5C[] = "move_x:%x y%x\n\0\0\0\0\0";
// TODO import missing RODATA
// *** rodata section end ***

// *** bss? section start ***
extern LayoutObject* D_80193AB0;
extern u16* D_80193AB4;
extern s8 D_80193AB8;
extern u8 D_80193ABC;
extern u16 D_80194728[];
// *** bss? section end ***

void func_80186FD0(Entity* arg0) {
    ObjInit2* objInit = &D_801804E0[arg0->subId];
    if (arg0->step == 0) {
        InitializeEntity(D_80180494);
        arg0->animSet = objInit->animSet;
        arg0->zPriority = objInit->zPriority;
        arg0->unk5A = objInit->unk4.s;
        arg0->palette = objInit->palette;
        arg0->unk19 = objInit->unk8;
        arg0->blendMode = objInit->blendMode;

        if (objInit->unkC != 0) {
            arg0->flags = objInit->unkC;
        }

        if (arg0->subId == 1) {
            arg0->unk1C = 0x0200;
            arg0->unk1A = 0x0200;
        }
    }

    AnimateEntity(objInit->unk10, arg0);
}

void func_801870B0(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->subId;
    u16 phi_v1;
    u16 unk;
    entity->unk6D = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_CurrentRoom.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_CurrentRoom.x = 0;
                g_CurrentRoom.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = func_8018B970();
            phi_v1 = entity->unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180538[temp_s1];
            g_CurrentRoom.x = *(temp_v0_2++);
            g_CurrentRoom.y = *(temp_v0_2++);
            g_CurrentRoom.width = *(temp_v0_2++);
            g_CurrentRoom.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180488);
        entity->unk7C.s = D_80180530[temp_s1];
        if (entity->unk7C.s != 0) {
            entity->hitboxWidth = D_80180528[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180528[temp_s1];
        }
    }
}

void func_801870B0(Entity* entity);
void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity);
void ReplaceBreakableWithItemDrop(Entity*);
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->subId >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(ENTITY_EXPLOSION, entityDropItem);
                entityDropItem->subId =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_zEntityCenter.S16.unk0 - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityWarpRoom);
#else
extern u8 D_8003BEBC;
extern void (*D_8003C7E8)(u16 arg0, u8 arg1, u8 arg2, u8 arg3);
extern s32 D_8003C8B8;
extern s32 D_80072EFC;
extern s32 D_80193AA0; // rename into move_room
extern s32 D_80193AA4;
extern s32 D_80193AA8;
extern s32 D_80193AAC;

// Handles everything about the warp room.
// It is responsible to spawn the colourful background, the stones on the
// ground and it always listen to the UP button. When the UP
// button is pressed, it brights the screen and teleport the player.
void EntityWarpRoom(Entity* entity) {
    POLY_GT4* poly;
    s16 temp_s4;
    s16 temp_s5;
    s32 move_y;
    s32 move_x;
    s16 temp_s6;
    s16 temp_s7;
    s16 firstPolyIndex;
    s32 temp_s1_2;
    POLY_GT4* temp_s2_4;
    s32 temp_v1_6;
    u16 move_room;
    s32 var_s0;
    s32 i;
    s32 i3;
    s32 var_s1;
    s32 var_v0_10;
    s32 bgColorG1;
    s32 var_v0_12;
    s32 bgColorB1;
    s32 var_v0_15;
    s32 var_v0_2;
    s32 bgColorR0;
    s32 var_v0_4;
    s32 bgColorG0;
    s32 var_v0_6;
    s32 bgColorB0;
    s32 var_v0_8;
    s32 bgColorR1;
    s32 fadeIn;
    s32 temp_s4_3;
    s32 temp_s5_3;
    u32* temp_v1_8;
    POLY_GT4* temp_s2;
    u32 temp_v0_5;
    u8 tintColor;
    WarpCoord* warpCoord;
    POLY_GT4* temp_s2_5;
    POLY_GT4* var_s2_3;
    s32 tmpa;
    s32 tmpb;

    FntPrint("step %x\n", entity->step);
    switch (entity->step) {
    case 0:
        // Initialize all the objects in the warp room
        InitializeEntity(D_80180470);
        firstPolyIndex = g_api.AllocPolygons(4, 24);
        if (firstPolyIndex == -1) {
            entity->step = 0;
            return;
        }
        poly = &D_80086FEC[firstPolyIndex];
        temp_s5 = entity->posY.i.hi; // must not be lhu but lh
        temp_s4 = entity->posX.i.hi; // must not be lhu but lh
        entity->firstPolygonIndex = firstPolyIndex;
        *(u32*)&entity->unk7C.s = poly;
        temp_s7 = temp_s4;
        temp_s6 = temp_s5;
        entity->flags |= FLAG_FREE_POLYGONS;
        var_s0 = 0;

        while (var_s0 < 0x10) {
            var_s1 = var_s0 << 8;
            var_s0++;
            poly->x0 = temp_s4 + ((rcos(var_s1) * 4) >> 8);
            poly->y0 = temp_s5 - ((rsin(var_s1) * 4) >> 8);
            poly->u0 = (((rcos(var_s1) >> 4) * 30) >> 8) + 0x20;
            poly->v0 = (-0x20) - (((rsin(var_s1) >> 4) * 30) >> 8);
            poly->x1 = temp_s4 + ((rcos(var_s0 << 8) * 4) >> 8);
            poly->y1 = temp_s5 - ((rsin(var_s0 << 8) * 4) >> 8);
            poly->u1 = (((rcos(var_s0 << 8) >> 4) * 30) >> 8) + 0x20;
            poly->v1 = (-0x20) - (((rsin(var_s0 << 8) >> 4) * 30) >> 8);
            poly->u3 = 0x20;
            poly->u2 = 0x20;
            poly->v3 = 0xE0;
            poly->v2 = 0xE0;
            poly->tpage = 0x1A;
            poly->clut = 0x15F;
            poly->pad2 = 0x40;
            poly->pad3 = 0x406;
            poly->y3 = temp_s6;
            poly->y2 = temp_s6;
            poly->x3 = temp_s7;
            poly->x2 = temp_s7;
            poly = (POLY_GT4*)poly->tag;
            var_s1 = var_s0 << 8;
        }

        entity->unk84.unk = poly; // store next polygon?
        setcode(poly, 1);
        poly->u0 = 0x40;
        poly->v0 = 0x50;
        poly->x0 = 0x60;
        poly->y0 = 0x70;
        poly->r0 = poly->g0 = poly->b0 = 0;
        poly->pad2 = 0x60;
        poly->pad3 = 0xA;
        poly = (POLY_GT4*)poly->tag;
        poly->code = 3;
        poly->r0 = poly->g0 = poly->b0 = 0;
        poly->x1 = poly->x3 = 256;
        poly->y0 = poly->y1 = 16;
        poly->y2 = poly->y3 = 240;
        poly->pad2 = 0x1F0;
        poly->pad3 = 8;
        poly->x0 = poly->x2 = 0;
        *((s32*)(&poly->r1)) = *((s32*)(&poly->r0));
        *((s32*)(&poly->r2)) = *((s32*)(&poly->r0));
        *((s32*)(&poly->r3)) = *((s32*)(&poly->r0));
        D_80193AA4 = 0x100;
        for (i = 0; i < 32; i++) {
            Entity* newEntity = AllocEntity(D_8007A958, &D_8007A958[96]);
            if (newEntity) {
                CreateEntityFromCurrentEntity(0x17, newEntity);
                newEntity->posY.i.hi = 0xCC - g_Camera.posY.i.hi;
                newEntity->posX.i.hi = (Random() & 0x7F) + 0x40;
            }
        }

        entity->unk3C = 1;
        entity->hitboxWidth = 2;
        entity->hitboxHeight = 16;
        *((u32*)D_80180648) = 0;
        entity->unk12 += 0x10;
        D_8003BEBC |= 1 | (1 << entity->subId);
        if (((u32)((PLAYER.posX.i.hi + ((s16)g_Camera.posX.i.hi)) - 0x61)) <
            0x3F) {
            D_80072EFC = 0x10;
            *D_80072EF4 = 0;
            D_8003C8B8 = 0;
            entity->step = 5;
            *((u32*)D_80180648) = 1;
        }

    case 1:
        // Wait for player to press the UP button
        if (((entity->unk48 != 0) && (g_pads->pressed & 0x1000)) &&
            (!(D_80072F2C & 0xC5CF3EF7))) {
            D_8003C8B8 = (*D_80072EF4 = 0);
            D_80072EFC = 0x80;
            PLAYER.accelerationX = 0;
            PLAYER.accelerationY = 0;
            entity->step++;
        }
        break;

    case 2:
        // Move Alucard in the background and fade him to white
        D_80072EFC = 0x80;
        PLAYER.zPriority = 0x5C;
        *D_80072EF4 = 0;
        g_zEntityCenter.unk = 0x5C;
        poly = (POLY_GT4*)(*&entity->unk84.unk);
        D_8003C8B8 = 0;
        poly->g0 = poly->b0 = poly->r0 = poly->r0 + 2;
        poly->pad3 = 0x31;
        if (poly->r0 >= 97) {
            *((u32*)D_80180648) = 1;
            g_api.PlaySfx(0x636);
            entity->step++;
        }
        break;

    case 3:
        // Fade the entire room into white
        D_80072EFC = 0x80;
        PLAYER.zPriority = 0x5C;
        *D_80072EF4 = 0;
        g_zEntityCenter.unk = 0x5C;
        poly = (POLY_GT4*)(*&entity->unk84.unk);
        D_8003C8B8 = 0;
        poly->pad3 = 0x31;
        if (poly->r0 < 0xF0) {
            poly->g0 = poly->b0 = poly->r0 += 2;
        }
        var_s2_3 = poly->tag;
        var_s2_3->pad3 = 0x31;
        if (var_s2_3->r0 < 0xF8) {
            var_s2_3->g0 = var_s2_3->b0 = var_s2_3->r0 += 2;
        } else {
            entity->step++;
        }
        *((s32*)(&var_s2_3->r1)) = *((s32*)(&var_s2_3->r0));
        *((s32*)(&var_s2_3->r2)) = *((s32*)(&var_s2_3->r0));
        *((s32*)(&var_s2_3->r3)) = *((s32*)(&var_s2_3->r0));
        break;

    case 4:
        // .rodata+0x1c
        // Perform the actual warp
        move_room = entity->subId + 1;
        for (i = 0; i < 5; i++) {
            if (move_room >= 5) {
                move_room = 0;
            }
            if ((D_8003BEBC >> move_room) & 1)
                break;
            move_room++;
        }

        warpCoord = &D_8018065C[move_room];
        D_80193AA0 = move_room;
        move_x = warpCoord->x - g_CurrentRoom.left;
        move_y = warpCoord->y - g_CurrentRoom.top;
        FntPrint(D_80186E3C, move_room);
        FntPrint(D_80186E4C, warpCoord->x, warpCoord->y);
        FntPrint(D_80186E5C, move_x, move_y);
        D_80097C98 = 2;
        PLAYER.posX.i.hi += move_x << 8;
        PLAYER.posY.i.hi += move_y << 8;
        entity->step = 128;
        break;

    case 5:
        // .rodata+0x20
        *D_80072EF4 = 0;
        D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        temp_s2_4 = (POLY_GT4*)entity->unk84.unk;
        temp_s2_4->pad3 = 8;
        temp_s2_4->r0 = 0;
        temp_s2_4->b0 = 0;
        temp_s2_4->r0 = 0;
        temp_s2_5 = temp_s2_4->tag;
        temp_s2_5->b0 = 0xF8;
        temp_s2_5->r0 = 0xF8;
        temp_s2_5->r0 = 0xF8;
        temp_s2_5->pad3 = 0x31;
        *((s32*)(&temp_s2_5->r1)) = *((s32*)(&temp_s2_5->r0));
        *((s32*)(&temp_s2_5->r2)) = *((s32*)(&temp_s2_5->r0));
        *((s32*)(&temp_s2_5->r3)) = *((s32*)(&temp_s2_5->r0));
        D_8003C7E8(0, 0, 0, 0);
        entity->step++;
        /* fallthrough */

    case 6:
        // Finalize warp by fading in from white
        // .rodata+0x24
        *D_80072EF4 = 0;
        D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        var_s2_3 = ((POLY_GT4*)(*&entity->unk84.unk))->tag;
        fadeIn = var_s2_3->r0 - 4;
        var_v0_15 = fadeIn < 0x28;
        if (fadeIn < 0) {
            // Fade-in complete
            fadeIn = 0;
            var_s2_3->pad3 = 8;
            D_8003C8B8 = 1;
            entity->step = 1;
            var_v0_15 = 0 < 0x28;
        }
        if (var_v0_15 != 0) {
            *((u32*)D_80180648) = 0;
        }
        var_s2_3->g0 = var_s2_3->b0 = var_s2_3->r0 = fadeIn;
        *((s32*)(&var_s2_3->r1)) = *((s32*)(&var_s2_3->r0));
        *((s32*)(&var_s2_3->r2)) = *((s32*)(&var_s2_3->r0));
        *((s32*)(&var_s2_3->r3)) = *((s32*)(&var_s2_3->r0));
        break;

    default:
        warpCoord = &D_8018065C[D_80193AA0];
        bgColorR1 = warpCoord->x - g_CurrentRoom.left;
        temp_s4_3 = bgColorR1;
        temp_s5_3 = warpCoord->y - g_CurrentRoom.top;
        FntPrint(D_80186E3C, D_80193AA0);
        FntPrint(D_80186E4C, warpCoord->x, warpCoord->y);
        FntPrint(D_80186E5C, temp_s4_3, temp_s5_3);
        break;
    }

    D_80193AA8 += 0x10;
    D_80193AAC = (rsin(D_80193AA8) >> 8) + 0xD0;
    if (D_80193AAC < 0) {
        D_80193AAC = 0;
    }
    if (D_80193AAC >= 0x100) {
        D_80193AAC = 0xFF;
    }
    poly = (POLY_GT4*)&entity->unk7C.s;
    D_80193AA4 = (rcos(D_80193AA8) >> 8) + 0xD0;
    for (i3 = 0; i3 <= 0x10; i3++) {
        var_v0_2 = i3;
        if (i3 < 0) {
            var_v0_2 = i3 + 15;
        }
        bgColorR0 =
            ((rsin(D_80180608[i3 - ((var_v0_2 >> 4) * 0x10)]) + 0x1000) >> 6) *
            D_80193AA4;
        if (bgColorR0 < 0) {
            bgColorR0 += 255;
        }
        poly->r0 = bgColorR0 >> 8;
        temp_v1_6 = i3 + 5;
        var_v0_4 = temp_v1_6;
        if (var_v0_4 < 0) {
            var_v0_4 = i3 + 20;
        }
        bgColorG0 = ((rsin(D_80180608[temp_v1_6 - ((var_v0_4 >> 4) * 0x10)]) +
                      0x1000) >>
                     6) *
                    D_80193AA4;
        if (bgColorG0 < 0) {
            bgColorG0 += 255;
        }
        poly->g0 = bgColorG0 >> 8;
        temp_v1_6 = i3 + 10;
        var_v0_6 = temp_v1_6;
        if (var_v0_6 < 0) {
            var_v0_6 = i3 + 25;
        }
        bgColorB0 = ((rsin(D_80180608[temp_v1_6 - ((var_v0_6 >> 4) * 0x10)]) +
                      0x1000) >>
                     6) *
                    D_80193AA4;
        if (bgColorB0 < 0) {
            bgColorB0 += 255;
        }
        poly->b0 = bgColorB0 >> 8;
        temp_s1_2 = i3 + 1;
        var_v0_8 = temp_s1_2;
        if (var_v0_8 < 0) {
            var_v0_8 = i3 + 16;
        }
        bgColorR1 = ((rsin(D_80180608[temp_s1_2 - ((var_v0_8 >> 4) * 0x10)]) +
                      0x1000) >>
                     6) *
                    D_80193AA4;
        if (bgColorR1 < 0) {
            bgColorR1 += 255;
        }
        poly->r1 = bgColorR1 >> 8;
        temp_v1_6 = i3 + 6;
        var_v0_10 = temp_v1_6;
        if (var_v0_10 < 0) {
            var_v0_10 = i3 + 0x15;
        }
        bgColorG1 = ((rsin(D_80180608[temp_v1_6 - ((var_v0_10 >> 4) * 0x10)]) +
                      0x1000) >>
                     6) *
                    D_80193AA4;
        if (bgColorG1 < 0) {
            bgColorG1 += 255;
        }
        poly->g1 = bgColorG1 >> 8;
        temp_v1_6 = i3 + 11;
        var_v0_12 = temp_v1_6;
        if (temp_v1_6 < 0) {
            var_v0_12 = i3 + 26;
        }
        bgColorB1 = ((rsin(D_80180608[temp_v1_6 - ((var_v0_12 >> 4) * 0x10)]) +
                      0x1000) >>
                     6) *
                    D_80193AA4;
        if (bgColorB1 < 0) {
            bgColorB1 += 255;
        }
        poly->b1 = bgColorB1 >> 8;
        poly->r2 = poly->g2 = poly->b2 = poly->r3 = poly->g3 = poly->b3 =
            D_80193AAC;
        D_80180608[i3] += 0x20;
        poly = (POLY_GT4*)poly->tag;
    }
}
#endif

// TODO this is matching, but EntityWarpRoom needs to match first due to the
// jump table.
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityWarpSmallRocks);
#else

void EntityWarpSmallRocks(Entity* entity) {
    s32 x;
    s32 y;
    s16* y_unk;
    s32 distance;
    s16 radians;
    u32* unk;

    switch (entity->step) {
    case 0:
        unk = D_80180648;
        InitializeEntity(D_801804C4);
        entity->unk19 = 4;
        entity->unk1E = Random() * 0x10;
        entity->animCurFrame = (Random() % 5) + 1;
        if (*unk != 0) {
            entity->posY.i.hi = (Random() & 0x1F) + 0x90;
            entity->step = 4;
        }
        break;

    case 1:
        if (*D_80180648 != 0) {
            *(u32*)(&entity->unk88) = Random() & 0x3F;
            entity->accelerationY = -0x40000;
            entity->step++;
        }
        break;

    case 2:
        if (*(u32*)&entity->unk88 != 0) {
            *(u32*)&entity->unk88 = *(u32*)&entity->unk88 - 1;
        } else {
            MoveEntity();
            entity->accelerationY += 0x4000;
            if (entity->accelerationY > ((s32)0xFFFF0000)) {
                entity->unk19 = 3;
                entity->unk1C = 0x100;
                distance = 0x100;
                entity->unk1A = distance;
                entity->step++;
            }
        }
        break;

    case 3:
        x = 0x80 - entity->posX.i.hi;
        y = 0x80 - entity->posY.i.hi;
        radians = ratan2(y, x);
        entity->accelerationX = rcos(radians) << 5;
        entity->accelerationY = rsin(radians) << 5;
        MoveEntity();
        distance = SquareRoot0(x * x + y * y) * 2;
        if (distance >= 0x101) {
            distance = 0x100;
        }
        entity->unk1A = entity->unk1C = distance;
        if (distance < 8) {
            DestroyEntity(entity);
        }
        break;

    case 4:
        unk = D_80180648;
        entity->unk1E += 0x20;
        entity->accelerationY = rsin(entity->unk1E) * 4;
        if (*unk == 0) {
            *(u32*)&entity->unk88 = 0x10;
            entity->step++;
        }
        break;

    case 5:
        y_unk = &g_Camera.posY.i.hi;
        *(u32*)&entity->unk88 = *(u32*)&entity->unk88 - 1;
        if (*(u32*)&entity->unk88 == 0) {
            func_801916C4(0x644);
        }
        MoveEntity();
        entity->accelerationY += 0x3000;
        y = entity->posY.i.hi + *y_unk + 5;
        if (y >= 209) {
            entity->posY.i.hi = 203 - (*y_unk);
            entity->step = 1;
        }
        break;
    }
}
#endif

s32 Random(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

void Update(void) {
    s16 i;
    Entity* entity;
    s32* unk;

    for (i = 0; i < 0x20; i++) {
        if (D_80194728[i]) {
            D_80194728[i]--;
        }
    }

    unk = &D_80097410;
    if (*unk) {
        if (!--*unk) {
            g_api.FreePolygons(D_80097414);
        }
    }

    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            s32 unk34 = entity->flags;
            if (unk34 & FLAG_DESTROY_IF_OUT_OF_CAMERA) {
                s16 posX = i = entity->posX.i.hi;
                s16 posY = entity->posY.i.hi;
                if (unk34 & FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA) {
                    if ((u16)(posX + 64) > 384 || (u16)(posY + 64) > 352) {
                        DestroyEntity(entity);
                        continue;
                    }
                } else {
                    if ((u16)(posX + 128) > 512 || (u16)(posY + 128) > 480) {
                        DestroyEntity(entity);
                        continue;
                    }
                }
            }

            if ((unk34 & 0x02000000)) {
                s16 posY = entity->posY.i.hi + g_Camera.posY.i.hi;
                s16 test = (g_CurrentRoom.vSize * 256) + 128;
                if (posY > test) {
                    DestroyEntity(entity);
                    continue;
                }
            }

            if (unk34 & 0xF) {
                entity->palette =
                    D_80180690[(entity->unk49 << 1) | (unk34 & 1)];
                entity->flags--;
                if ((entity->flags & 0xF) == 0) {
                    entity->palette = entity->unk6A;
                    entity->unk6A = 0;
                }
            }

            if (!(unk34 & 0x20000000) || (unk34 & 0x10000000) ||
                ((u16)(entity->posX.i.hi + 64) <= 384) &&
                    ((u16)(entity->posY.i.hi + 64) <= 352)) {
                if (!entity->unk58 || (entity->unk58--, unk34 & 0x100000)) {
                    if (!D_800973FC || unk34 & 0x2100 ||
                        (unk34 & 0x200 && !(D_8003C8C4 & 3))) {
                        g_CurrentEntity = entity;
                        entity->pfnUpdate(entity);
                        entity->unk44 = 0;
                        entity->unk48 = 0;
                    }
                }
            }
        } else {
            g_CurrentEntity = entity;
            entity->pfnUpdate(entity);
            entity->unk44 = 0;
            entity->unk48 = 0;
        }
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80188514);
#else
void func_80188514(void) {
    Entity* entity;
    for (entity = D_800762D8; entity < &D_8007EFD8; entity++) {
        if (!entity->pfnUpdate)
            continue;

        if (entity->step) {
            if (entity->flags & FLAG_UNK_10000) {
                if (entity->flags & 0xF) {
                    entity->palette =
                        D_80180690[entity->unk49 << 1 | entity->flags & 1];
                    entity->flags--;
                    if ((entity->flags & 0xF) == 0) {
                        entity->palette = entity->unk6A;
                        entity->unk6A = 0;
                    }
                }
            } else
                continue;
        }

        g_CurrentEntity = entity;
        entity->pfnUpdate(entity);
        entity->unk44 = 0;
        entity->unk48 = 0;
    }
}

#endif

// https://decomp.me/scratch/Nq66t
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", TestCollisions);

// https://decomp.me/scratch/m0PKE
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityNumericDamage);

void CreateEntityFromLayout(Entity* entity, LayoutObject* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->objectId & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.i.hi = initDesc->posX - g_Camera.posX.i.hi;
    entity->posY.i.hi = initDesc->posY - g_Camera.posY.i.hi;
    entity->subId = initDesc->subId;
    entity->objectRoomIndex = initDesc->objectRoomIndex >> 8;
    entity->unk68 = (initDesc->objectId >> 0xA) & 7;
}

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80189E9C);
#else
void func_80189E9C(LayoutObject* layoutObj) {
    s16 temp_v0, posY;
    u16 initFlags;

    temp_v0 = g_Camera.posY.i.hi - 0x40;
    if (temp_v0 < 0) {
        temp_v0 = 0;
    }

    if ((s16)layoutObj->posY < temp_v0)
        return;
    if (((s16)(g_Camera.posY.i.hi + 0x120) < layoutObj->posY))
        return;

    initFlags = layoutObj->objectId & 0xE000;
    if (initFlags != 0x8000) {
        Entity* entity;
        switch (initFlags) {
        case 0x0:
            entity = &D_800762D8[layoutObj->objectRoomIndex];
            if (entity->objectId == 0) {
                CreateEntityFromLayout(entity, layoutObj);
            }
            break;
        case 0xA000:
            entity = &D_800762D8[layoutObj->objectRoomIndex];
            CreateEntityFromLayout(entity, layoutObj);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80189FB4);

void func_8018A0CC(s16 arg0) {
    do {
    loop_1:
        if (D_80193AB0->posX == 0xFFFE || D_80193AB0->posX < (s32)arg0) {
            D_80193AB0++;
            goto loop_1;
        }
    } while (0);
}

void func_8018A118(s32 arg0) {
    s32 a2, a3;
    a3 = 0xFFFF;
    arg0 = (s16)arg0;
    a2 = 0xFFFE;
loop_1:
    if ((D_80193AB0->posX == a3) ||
        (((s32)arg0 < D_80193AB0->posX) && (D_80193AB0->posX != a2))) {
        D_80193AB0--;
        goto loop_1;
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018A170);
void func_8018A170(s16);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018A26C);
void func_8018A26C(s16);

void func_8018A380(s16 arg0) {
    u16 a1 = -2;
    s32 tmp = arg0;
    arg0 = (s16)arg0;
loop_1:
    if (D_80193AB4[1] == (s32)a1 || D_80193AB4[1] < tmp) {
        D_80193AB4 += sizeof(LayoutObject) / sizeof(u16);
        goto loop_1;
    }
}

void func_8018A3CC(s16 arg0) {
    while (true) {
        if (D_80193AB4[1] == 0xFFFF) {
            D_80193AB4 -= sizeof(LayoutObject) / sizeof(u16);
        } else if ((s32)arg0 >= (s32)D_80193AB4[1] || D_80193AB4[1] == 0xFFFE) {
            break;
        } else {
            D_80193AB4 -= sizeof(LayoutObject) / sizeof(u16);
        }
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018A424);
void func_8018A424(s16 arg0);
#else
void func_8018A424(s16 arg0) {
    if (D_80193ABC) {
        func_8018A380(arg0 - D_8009790C);
        D_80193ABC = 0;
    }

    while (true) {
        if (D_80193AB4[1] != -1 && arg0 >= D_80193AB4[1]) {
            u8 flag = (D_80193AB4[3] >> 8) + 0xFF;
            if (flag == 0xFF ||
                (1 << (flag & 0x1F) & g_entityDestroyed[flag >> 5]) == 0) {
                func_80189FB4(D_80193AB4);
            }
            D_80193AB4 += sizeof(LayoutObject) / sizeof(u16);
        } else
            break;
    }
}
#endif

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018A520);
void func_8018A424(s16 arg0);
#else
void func_8018A520(s16 arg0) {
    s32 var_v0;
    u32 new_var;
    u8 flag;
    if (arg0 < 0) {
        arg0 = 0;
    }
    var_v0 = arg0 << 0x10;
    if (D_80193ABC == 0) {
        func_8018A3CC(arg0 - D_8009790C);
        D_80193ABC = 1;
    }
loop_5:
    if ((D_80193AB4[1] != 0xFFFE) && ((var_v0 >> 0x10) <= D_80193AB4[1])) {
        flag = (D_80193AB4[3] >> 8) + 0xFF;
        new_var = g_entityDestroyed[flag >> 5];
        if ((flag == 0xFF) || (((1 << (flag & 0x1F)) & new_var) == 0)) {
            func_80189FB4(D_80193AB4);
        }
        D_80193AB4 -= 0xA;
        goto loop_5;
    }
}
#endif

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", InitRoomEntities);
#else
void InitRoomEntities(s32 objLayoutId) {
    s16 temp_s0;
    s16 var_a1_2;
    u16* pObjLayoutStart;
    s16* layout;
    s32 arg0;
    s16 var_a1;
    u16* temp_v1;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    layout = &g_CurrentRoomTileLayout;
    D_80193AB0 = pObjLayoutStart;
    D_80193AB4 = D_80180310[objLayoutId];

    if (*pObjLayoutStart != 0xFFFE) {
        D_80193AB0 = pObjLayoutStart + 1;
        arg0 = Random() & 0xFF;
        for (var_a1 = 0;; var_a1++) {
            s32 temp_v0;
            temp_v1 = D_80193AB0;
            D_80193AB0 = ((u16*)D_80193AB0) + 1;
            temp_v0 = arg0 - temp_v1[0];
            arg0 = temp_v0;
            if (((s16)temp_v0) < 0) {
                break;
            }
            D_80193AB0 = temp_v1 + 3;
        }

        D_80193AB0 = (temp_v1[2] << 0x10) + temp_v1[1];
        D_80193AB4 += var_a1 * 2 + 2;
        D_80193AB4 = (D_80193AB4[1] << 0x10) + D_80193AB4[0];
    }

    var_a1_2 = layout[5] - 0x40;
    temp_s0 = layout[5] + 0x140;
    if (var_a1_2 < 0) {
        var_a1_2 = 0;
    }

    D_80193AB8 = 0;
    D_80193ABC = 0;
    func_8018A0CC(var_a1_2);
    func_8018A170(temp_s0);
    func_8018A380(layout[7] + 0x120);
}
#endif

void func_8018A7AC(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = g_Camera.posX.i.hi;
        if (D_80097908 > 0)
            func_8018A170(tmp + 0x140);
        else
            func_8018A26C(tmp - 0x40);
    }

    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0)
            func_8018A424(currentRoomTileLayout->unkE + 0x120);
        else
            func_8018A520(tmp - 0x40);
    }
}

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = g_CurrentEntity->posX.i.hi;
    entity->posY.i.hi = g_CurrentEntity->posY.i.hi;
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
}

s32 func_8018A950(Entity* e) {
    s16 diff;

    diff = PLAYER.posX.i.hi - e->posX.i.hi;
    diff = ABS(diff);

    if (diff >= 17) {
        diff = 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = ABS(diff);
        diff = diff < 33;
    }

    return diff;
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityRedDoor);

void DestroyEntity(Entity* item) {
    s32 i;
    s32 length;
    u32* ptr;

    if (item->flags & FLAG_FREE_POLYGONS) {
        g_api.FreePolygons(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void DestroyEntityFromIndex(s16 index) {
    Entity* entity = &g_EntityArray[index];

    while (entity < &D_8007EF1C) {
        DestroyEntity(entity);
        entity++;
    }
}

void PreventEntityFromRespawning(Entity* entity) {
    if (entity->objectRoomIndex) {
        u32 value = (entity->objectRoomIndex - 1);
        u16 index = value / 32;
        u16 bit = value % 32;
        g_entityDestroyed[index] |= 1 << bit;
    }
}

#include "st/AnimateEntity.h"

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018B7E8);

/*
 * Returns the absolute distance from g_CurrentEntity to player in the X Axis
 */
s16 func_8018B900(void) {
    s16 xDistance = g_CurrentEntity->posX.i.hi - PLAYER.posX.i.hi;

    if (xDistance < 0) {
        xDistance = -xDistance;
    }
    return xDistance;
}

/*
 * Returns the absolute distance from g_CurrentEntity to player in the Y Axis
 */
s32 func_8018B93C(void) {
    s32 yDistance = g_CurrentEntity->posY.i.hi - PLAYER.posY.i.hi;

    if (yDistance < 0) {
        yDistance = -yDistance;
    }
    return yDistance;
}

s32 func_8018B970(void) {
    s16 arg0 = g_CurrentEntity->posX.i.hi > PLAYER.posX.i.hi;

    if (g_CurrentEntity->posY.i.hi > PLAYER.posY.i.hi) {
        arg0 |= 2;
    }
    return arg0;
}

void MoveEntity(void) {
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;
}

void FallEntity(void) {
    if (g_CurrentEntity->accelerationY < FALL_TERMINAL_VELOCITY) {
        g_CurrentEntity->accelerationY += FALL_GRAVITY;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018BA10);
#else
s32 func_8018BA10(u16* arg0) {
    s16 new_var;
    s32 new_var4;
    Collider res;
    Collider resBack;
    s16 i;
    s16 x;
    s16 y;
    s32 var_v0;

    MoveEntity();
    FallEntity();
    if (g_CurrentEntity->accelerationY >= 0) {
        x = g_CurrentEntity->posX.i.hi;
        y = g_CurrentEntity->posY.i.hi;
        for (i = 0; i < 4; i++) {
            x += *(arg0++);
            y += *(arg0++);
            g_api.CheckCollision(x, y, &res, 0);
            new_var4 = res.unk0;
            if (new_var4 & 0x8000) {
                var_v0 = new_var4 & 5;
                if (i == 1) {
                    if (new_var4 & 1) {
                        g_api.CheckCollision(x, y - 8, &resBack, 0);
                        if (!(resBack.unk0 & 1)) {
                            new_var = LOH(res.unk18);
                            g_CurrentEntity->accelerationX = 0;
                            g_CurrentEntity->accelerationY = 0;
                            g_CurrentEntity->posY.i.hi =
                                (((u16)g_CurrentEntity->posY.i.hi) + 4) +
                                new_var;
                            g_CurrentEntity->flags &= 0xEFFFFFFF;
                            return 1;
                        }
                    }
                    continue;
                }
            } else {
                var_v0 = new_var4 & 5;
            }
            if (new_var4 & 5) {
                if (i != 1) {
                    if (new_var4 & 4) {
                        g_CurrentEntity->flags &= 0xEFFFFFFF;
                        return 4;
                    }
                    g_api.CheckCollision(x, y - 8, &resBack, 0);
                    if (!(resBack.unk0 & 1)) {
                        x = ((u16)g_CurrentEntity->posY.i.hi) + LOH(res.unk18);
                        new_var = x;
                        g_CurrentEntity->accelerationX = 0;
                        g_CurrentEntity->accelerationY = 0;
                        g_CurrentEntity->posY.i.hi = new_var;
                        g_CurrentEntity->flags &= 0xEFFFFFFF;
                        return 1;
                    }
                }
            }
        }
    }
    g_CurrentEntity->flags |= 0x10000000;
    return 0;
}
#endif

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018BC88);

Entity* AllocEntity(Entity* start, Entity* end) {
    Entity* current = start;
    while (current < end) {
        if (current->objectId == 0) {
            DestroyEntity(current);
            return current;
        }

        current++;
    }
    return NULL;
}

s32 func_8018BED0(u8 arg0, s16 arg1) { return D_80180A94[arg0] * arg1; }

s16 func_8018BEFC(u8 arg0) { return D_80180A94[arg0]; }

void func_8018BF18(s32 arg0, s16 arg1) {
    g_CurrentEntity->accelerationX = func_8018BED0(arg0, arg1);
    g_CurrentEntity->accelerationY = func_8018BED0(arg0 - 0x40, arg1);
}

u8 func_8018BF84(s16 x, s16 y) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8018BFBC(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.i.hi - (u16)a->posX.i.hi;
    s32 diffY = (u16)b->posY.i.hi - (u16)a->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C004(s32 x, s32 y) {
    s32 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s32 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return func_8018BF84(diffX, diffY);
}

u8 func_8018C04C(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_8018C0A4(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = g_CurrentEntity;
    if (moveX < 0) {
        moveX += 15;
    }
    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = g_CurrentEntity;
    if (moveY < 0) {
        moveY += 15;
    }
    entity->accelerationY = moveY >> 4;
}

u16 func_8018C130(s16 x, s16 y) { return ratan2(y, x); }

u16 func_8018C160(Entity* a, Entity* b) {
    s32 diffX = b->posX.i.hi - a->posX.i.hi;
    s32 diffY = b->posY.i.hi - a->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C198(s32 x, s32 y) {
    s16 diffX = x - (u16)g_CurrentEntity->posX.i.hi;
    s16 diffY = y - (u16)g_CurrentEntity->posY.i.hi;
    return ratan2(diffY, diffX);
}

u16 func_8018C1E0(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_8018C240(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_8018C260(u8 arg0) {
    g_CurrentEntity->unk2E = arg0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

void func_8018C27C(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801916C4(arg1);
    }
    if (arg0 == 0xFF) {
        DestroyEntity(g_CurrentEntity);
        return;
    }

    entity = g_CurrentEntity;
    entity->unk19 = 0;
    entity->objectId = ENTITY_EXPLOSION;
    entity->pfnUpdate = (PfnEntityUpdate)EntityExplosion;
    entity->subId = arg0;
    entity->animCurFrame = 0;
    g_CurrentEntity->step = 0;
    g_CurrentEntity->unk2E = 0;
}

void InitializeEntity(u16 arg0[]) {
    u16 enemyId;
    EnemyDef* enemyDef;

    g_CurrentEntity->animSet = *arg0++;
    g_CurrentEntity->animCurFrame = *arg0++;
    g_CurrentEntity->unk5A = *arg0++;
    g_CurrentEntity->palette = *arg0++;

    enemyId = *arg0++;
    g_CurrentEntity->enemyId = enemyId;
    enemyDef = &g_api.enemyDefs[enemyId];
    g_CurrentEntity->hitPoints = enemyDef->hitPoints;
    g_CurrentEntity->attack = enemyDef->attack;
    g_CurrentEntity->attackElement = enemyDef->attackElement;
    g_CurrentEntity->unk3C = enemyDef->unkC;
    g_CurrentEntity->hitboxWidth = enemyDef->hitboxWidth;
    g_CurrentEntity->hitboxHeight = enemyDef->hitboxHeight;
    g_CurrentEntity->flags = enemyDef->unk24;
    g_CurrentEntity->unk10 = 0;
    g_CurrentEntity->unk12 = 0;
    g_CurrentEntity->unk2E = 0;
    g_CurrentEntity->step++;
    if (g_CurrentEntity->zPriority == 0) {
        g_CurrentEntity->zPriority = g_zEntityCenter.S16.unk0 - 0xC;
    }
}

void EntityDummy(Entity* arg0) {
    if (arg0->step == 0) {
        arg0->step++;
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018C434);

void func_8018C55C(u16* arg0, s16 arg1);
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018C55C);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018C6B4);

void ReplaceBreakableWithItemDrop(Entity* entity) {
    u16 subId;

    PreventEntityFromRespawning(entity);

    if (!(D_8009796E & 2)) {
        DestroyEntity(entity);
        return;
    }

    subId = entity->subId &= 0xFFF;

    if (subId < 0x80) {
        entity->objectId = ENTITY_PRICE_DROP;
        entity->pfnUpdate = EntityPriceDrop;
        entity->animFrameDuration = 0;
        entity->animFrameIdx = 0;
    } else {
        subId -= 0x80;
        entity->objectId = ENTITY_INVENTORY_DROP;
        entity->pfnUpdate = (PfnEntityUpdate)EntityInventoryDrop;
    }

    entity->subId = subId;
    entity->unk6D = 0x10;
    entity->step = 0;
}

void func_8018CAB0(void) {
    s32 temp_v1;
    Entity* entity;

    entity = g_CurrentEntity;
    if (entity->accelerationY >= 0) {
        temp_v1 = *(s16*)&entity->unk88 + entity->unk84.unk;
        entity->unk84.unk = temp_v1;
        entity->accelerationX = temp_v1;
        if (temp_v1 == 0x10000 || temp_v1 == -0x10000) {
            *(s16*)&entity->unk88 = -*(s16*)&entity->unk88;
        }
        entity = g_CurrentEntity;
    }
    NOP;

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}

void func_8018CB34(u16 arg0) {
    Collider res;

    if (g_CurrentEntity->accelerationX < 0) {
        g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                             g_CurrentEntity->posY.i.hi - 7, &res, 0);
        if (res.unk0 & 5) {
            g_CurrentEntity->accelerationY = 0;
        }
    }

    g_api.CheckCollision(g_CurrentEntity->posX.i.hi,
                         g_CurrentEntity->posY.i.hi + 7, &res, 0);

    if (arg0) {
        if (!(res.unk0 & 5)) {
            MoveEntity();
            FallEntity();
            return;
        }

        g_CurrentEntity->accelerationX = 0;
        g_CurrentEntity->accelerationY = 0;

        if (res.unk0 & 4) {
            g_CurrentEntity->posY.val += 0x2000;
            return;
        }

        g_CurrentEntity->posY.i.hi += LOH(res.unk18);
        return;
    }

    if (!(res.unk0 & 5)) {
        MoveEntity();
        func_8018CAB0();
    }
}

void CollectHeart(u16 heartSize) {
    s32* hearts;

    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    hearts = &D_80097BA0.hearts;
    *hearts += c_HeartPrizes[heartSize];

    if (D_80097BA0.heartsMax < *hearts) {
        *hearts = D_80097BA0.heartsMax;
    }

    DestroyEntity(g_CurrentEntity);
}

void CollectGold(u16 goldSize) {
    s32 *gold, *unk;
    u16 goldSizeIndex;

    g_api.PlaySfx(NA_SE_PL_COLLECT_GOLD);
    gold = &g_playerGold;
    goldSizeIndex = goldSize - 2;
    *gold += c_GoldPrizes[goldSizeIndex];
    if (*gold > MAX_GOLD) {
        *gold = MAX_GOLD;
    }

    unk = &D_80097410;
    if (*unk) {
        g_api.FreePolygons(D_80097414);
        *unk = 0;
    }

    func_80192F40(D_80180E08[goldSizeIndex], 1);
    DestroyEntity(g_CurrentEntity);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018CDEC);
#else
void func_8018CDEC(u16 arg0) {
    u16 temp_v0;
    u16 var_a0;
    Entity* player;

    g_api.PlaySfx(NA_SE_PL_IT_PICKUP);
    player = &PLAYER;
    temp_v0 = D_80180DC4[arg0];
    // player_equip_left_hand = temp_v0;
    if (player_equip_left_hand == temp_v0) {
        var_a0 = 1;
        g_CurrentEntity->unk6D = 0x10;
    } else {
        var_a0 = D_80180DF4[player_equip_left_hand];
        g_CurrentEntity->unk6D = 0x60;
    }
    if (var_a0 != 0) {
        g_CurrentEntity->subId = var_a0;
        g_CurrentEntity->posY.i.hi = player->posY.i.hi + 0xC;
        func_8018C240(7);
        g_CurrentEntity->accelerationY = -0x28000;
        g_CurrentEntity->animCurFrame = 0;
        g_CurrentEntity->unk8A = 5;
        if (player->facing != 1) {
            g_CurrentEntity->accelerationX = -0x20000;
        } else {
            g_CurrentEntity->accelerationX = 0x20000;
        }
    } else {
        DestroyEntity(g_CurrentEntity);
    }
}
#endif

void CollectHeartVessel(void) {
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        D_80097BA0.hearts += HEART_VESSEL_RICHTER;

        if (D_80097BA0.heartsMax < D_80097BA0.hearts) {
            D_80097BA0.hearts = D_80097BA0.heartsMax;
        }
    } else {
        g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
        g_api.func_800FE044(HEART_VESSEL_INCREASE, 0x4000);
    }
    DestroyEntity(g_CurrentEntity);
}

void CollectLifeVessel(void) {
    g_api.PlaySfx(NA_SE_PL_COLLECT_HEART);
    g_api.func_800FE044(LIFE_VESSEL_INCREASE, 0x8000);
    DestroyEntity(g_CurrentEntity);
}

void DestroyCurrentEntity(void) { DestroyEntity(g_CurrentEntity); }

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityPriceDrop);

void EntityExplosion(Entity* entity) {
    u16 zPriority;

    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->animSet = 2;
        entity->animFrameIdx = 0;
        entity->animFrameDuration = 0;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority) {
            entity->zPriority = zPriority >> 8;
        }
        entity->subId &= 15;
        entity->accelerationY = D_80180EC4[entity->subId];
    } else {
        entity->posY.val += entity->accelerationY;
        if (!AnimateEntity(D_80180F70[entity->subId], entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_8018D990(Entity* arg0, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &D_80086FEC[arg0->firstPolygonIndex];

    left = arg0->posX.i.hi - 7;
    right = arg0->posX.i.hi + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = arg0->posY.i.hi - 7;
    bottom = arg0->posY.i.hi + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityInventoryDrop);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018E01C);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityRelicOrb);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityHeartDrop);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityUnkId0E);

u8 func_8018F420(s16* arg0, u8 facing) {
    u8 ret = 0;
    Collider res;
    s16 posX, posY;

    while (*arg0 != 0xFF) {
        ret <<= 1;

        posX = facing ? (g_CurrentEntity->posX.i.hi + *arg0++)
                      : (g_CurrentEntity->posX.i.hi - *arg0++);
        posY = g_CurrentEntity->posY.i.hi + *arg0++;

        g_api.CheckCollision(posX, posY, &res, 0);

        if (res.unk0 & 1) {
            ret |= 1;
        }
    }

    return ret;
}

void func_8018F510(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_8018047C);
        entity->unk8C.modeU16.unk0 = entity->unk80.entityPtr->objectId;
    case 1:
        if (entity->unk7C.U8.unk0++ >= 5) {
            Entity* newEntity =
                AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(ENTITY_EXPLOSION, entity, newEntity);
                newEntity->objectId = ENTITY_EXPLOSION;
                newEntity->pfnUpdate = EntityExplosion;
                newEntity->subId = entity->subId;
            }
            entity->unk7C.U8.unk0 = 0;
        }
        entity->posX.i.hi = entity->unk80.entityPtr->posX.i.hi;
        entity->posY.i.hi = entity->unk80.entityPtr->posY.i.hi;
        if (entity->unk80.entityPtr->objectId != entity->unk8C.modeU16.unk0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018F620);

// https://decomp.me/scratch/peM5t by stuckpixel
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018F750);
#else
extern void func_8018F928(Entity*);
void func_8018F750(Entity* source, s8 count, u16 xOffset, u16 yOffset,
                   s16 xDistance) {
    Entity* entity;
    s32 x, y;
    u8 i;

    x = (u16)source->posX.i.hi + xOffset;
    y = (u16)source->posY.i.hi + yOffset;

    for (i = 0; i < count; i++) {
        entity = AllocEntity(D_8007A958, &D_8007A958[MaxEntityCount]);
        if (entity != NULL) {
            entity->objectId = 21;
            entity->pfnUpdate = func_8018F928;
            entity->posX.i.hi = x;
            entity->posY.i.hi = y;
            entity->subId = i;
            entity->zPriority = source->zPriority + 1;
        }
        x += xDistance;
    }
}
#endif

void func_8018F838(Entity* entity) {
    if (entity->step == 0) {
        entity->accelerationY = D_80181020[entity->unk94];
        entity->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        entity->palette = 0x8195;
        entity->animSet = 2;
        entity->animCurFrame = D_80181038[entity->subId];
        entity->blendMode = 0x10;
        entity->step++;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= entity->accelerationY;

        if (!(entity->animFrameDuration & 1)) {
            entity->animCurFrame++;
        }

        if (D_8018103C[entity->subId] < (s32)entity->animFrameDuration) {
            DestroyEntity(entity);
        }
    }
}

void func_8018F928(Entity* arg0) {
    u16 temp_v0;

    if (arg0->step == 0) {
        arg0->flags = 0x2000 | FLAG_UNK_04000000 | FLAG_UNK_08000000;
        arg0->palette = 0x8195;
        arg0->animSet = 5;
        arg0->animCurFrame = 1U;
        arg0->blendMode = 0x10;
        arg0->unk19 = 3;
        temp_v0 = D_80180FF8[arg0->subId];
        arg0->unk1A = temp_v0;
        arg0->unk1C = temp_v0;
        arg0->accelerationY = D_80181008[arg0->subId];
        arg0->step++;
    } else {
        arg0->animFrameDuration++;
        arg0->posY.val -= arg0->accelerationY;
        if (!(arg0->animFrameDuration & 1)) {
            arg0->animCurFrame++;
        }
        if (arg0->animFrameDuration >= 37) {
            DestroyEntity(arg0);
        }
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018FA1C);

bool func_8018FC4C(Unkstruct6* unk) {
    Collider res;

    FallEntity();
    g_CurrentEntity->posX.val += g_CurrentEntity->accelerationX;
    g_CurrentEntity->posY.val += g_CurrentEntity->accelerationY;

    if (g_CurrentEntity->accelerationY >= 0) {
        s16 posX = g_CurrentEntity->posX.i.hi;
        s16 posY = g_CurrentEntity->posY.i.hi;
        posX += unk->x;
        posY += unk->y;
        g_api.CheckCollision(posX, posY, &res, 0);
        if (res.unk0 & 1) {
            g_CurrentEntity->posY.i.hi += LOH(res.unk18);
            g_CurrentEntity->accelerationY =
                -g_CurrentEntity->accelerationY / 2;
            if (g_CurrentEntity->accelerationY > -0x10000) {
                return true;
            }
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_8018FD48);

void EntityIntenseExplosion(Entity* entity) {
    u32 zPriority;
    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->palette = 0x8170;
        entity->animSet = 5;
        entity->animCurFrame = 1;
        entity->blendMode = 0x30;
        if (entity->subId & 0xF0) {
            entity->palette = 0x8195;
            entity->blendMode = 0x10;
        }

        zPriority = entity->subId & 0xFF00;
        if (zPriority != 0) {
            entity->zPriority = zPriority >> 8;
        }
        entity->zPriority += 8;
    } else {
        entity->animFrameDuration++;
        entity->posY.val -= 0x4000;

        if ((entity->animFrameDuration & 1) == 0) {
            entity->animCurFrame++;
        }

        if (entity->animFrameDuration >= 37) {
            DestroyEntity(entity);
        }
    }
}

void func_801903C8(Entity* entity) {
    if (entity->step == 0) {
        InitializeEntity(D_80180458);
        entity->unk6C = 0xF0;
        entity->unk1A = 0x01A0;
        entity->unk1C = 0x01A0;
        entity->animSet = 8;
        entity->animCurFrame = 1;
        entity->zPriority += 16;

        if (entity->subId) {
            entity->palette = entity->subId;
        } else {
            entity->palette = 0x8160;
        }

        entity->step++;
    } else {
        MoveEntity();
        if (!AnimateEntity(D_8018104C, entity)) {
            DestroyEntity(entity);
        }
    }
}

void func_80190494(u16 objectId, Entity* source, Entity* entity) {
    u16 palette;

    DestroyEntity(entity);
    entity->objectId = objectId;
    entity->pfnUpdate = PfnEntityUpdates[objectId];
    entity->posX.i.hi = source->posX.i.hi;
    entity->posY.i.hi = source->posY.i.hi;
    entity->unk5A = source->unk5A;
    entity->zPriority = source->zPriority;
    entity->animSet = source->animSet;
    entity->flags = 0x1002000 | FLAG_UNK_04000000 | FLAG_UNK_08000000 |
                    FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                    FLAG_DESTROY_IF_OUT_OF_CAMERA;

    palette = source->palette;
    entity->palette = palette & 0x8000 ? source->unk6A : palette;
}

void func_8019055C(void) {
    s32 temp_s3;
    s8 temp_s4;
    Entity* entity;
    s32 i;

    temp_s4 = Random() & 3;
    temp_s3 = ((Random() & 0xF) << 8) - 0x800;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(ENTITY_EXPLOSION, g_CurrentEntity, entity);
            entity->unk84.U8.unk1 = 6 - i;
            entity->unk80.modeS16.unk0 = temp_s3;
            entity->unk84.U8.unk0 = temp_s4;
        }
    }
}

void func_80190614(Entity* self) {
    s32 accelerationX;
    s32 accelerationY;
    s32 temp;

    if (self->step == 0) {
        InitializeEntity(D_80180458);
        self->animSet = 2;
        self->palette = 0x81B6;
        self->unk6C = 0x70;
        self->zPriority = 192;
        self->unk19 |= 0xC;
        self->blendMode |= 0x30;

        switch (self->unk84.U8.unk0) {
        case 1:
            if (self->unk84.U8.unk1 >= 4) {
                self->unk84.U8.unk1 += 253;
                self->unk80.modeS16.unk0 -= 0x800;
            }
            break;

        case 2:
            self->unk80.modeS16.unk0 += self->unk84.U8.unk1 * 192;
            break;
        }

        self->unk1E = self->unk80.modeS16.unk0 &= 0xFFF;
        temp = (self->unk84.U8.unk1 * 320) / 24;
        self->accelerationX = temp * rsin(self->unk80.modeS16.unk0);
        self->accelerationY = -(temp * rcos(self->unk80.modeS16.unk0));
    }

    if (self->animFrameIdx >= 13) {
        accelerationX = self->accelerationX;
        if (accelerationX < 0) {
            accelerationX += 3;
        }

        accelerationY = self->accelerationY;
        self->accelerationX = (accelerationX >> 2) * 3;
        if (accelerationY < 0) {
            accelerationY += 3;
        }
        self->accelerationY = (accelerationY >> 2) * 3;
    }

    MoveEntity();

    if (AnimateEntity(D_80180EEC, self) == 0) {
        DestroyEntity(self);
    }
}

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_801907EC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80190DCC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_801914CC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_801916C4);

s32 func_80193A3C(u8* arg0, u8 value);
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_801917BC);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityStageNamePopup);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityAbsorbOrb);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", EntityEnemyBlood);

void EntityRoomForeground(Entity* entity) {
    ObjInit2* objInit = &D_80181134[entity->subId];
    if (entity->step == 0) {
        InitializeEntity(D_80180494);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk4.s;
        entity->palette = objInit->palette;
        entity->unk19 = objInit->unk8;
        entity->blendMode = objInit->blendMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 |= 4;
        }
    }
    AnimateEntity(objInit->unk10, entity);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80192F40);
#else
void func_80192F40(u8* arg0, u8 arg1) {
    u8 sp10[0x40];
    POLY_GT4* poly;
    s16 temp_t2;
    s16 temp_t3;
    s32 firstPolyIndex;
    s16 temp_v0_2;
    s16 var_t5_2;
    s16 var_t5_3;
    short temp_v1;
    s32 var_s0;
    u16 polyCount;
    s32 i;
    u8 temp_v1_2;
    u8 var_v1;
    u8* var_a1;
    u8* var_a1_2;
    u8* var_a1_3;
    var_a1 = &sp10;
    var_s0 = 0;
    polyCount = 0;
    for (i = sizeof(sp10) - 1; i >= 0; i--) {
        *(var_a1++) = 0;
    }

    var_a1_2 = &sp10;
    while (1) {
        var_v1 = *arg0++;
        if (var_v1 == 0xFF) {
            var_v1 = *arg0++;
            if (var_v1 == 0) {
                break;
            }
        }
        *(var_a1_2++) = var_v1;
        if (var_v1 != 0) {
            polyCount++;
            var_s0 = var_s0 + 8;
        } else {
            var_s0 += 4;
        }
    }

    firstPolyIndex = g_api.AllocPolygons(6, polyCount + 4);
    D_80097414 = firstPolyIndex;
    if (firstPolyIndex == (-1)) {
        return;
    }
    poly = &D_80086FEC[firstPolyIndex];
    setcode(poly, 3);
    poly->r3 = 0;
    poly->r2 = 0;
    poly->r1 = 0;
    poly->r0 = 0;
    poly->g3 = 0;
    poly->g2 = 0;
    poly->g1 = 0;
    poly->g0 = 0;
    poly->b3 = 0;
    poly->b2 = 0;
    poly->b1 = 0;
    poly->b0 = 0;
    if (arg1) {
        poly->b1 = 0xAF;
        poly->b0 = 0xAF;
    } else {
        poly->g1 = 0x5F;
        poly->g0 = 0x5F;
    }
    var_t5_2 = 7;
    if (arg1) {
        var_s0 += 4;
    } else {
        var_t5_2 = 0xD4 - var_s0;
    }
    temp_v1 = var_t5_2 + var_s0;
    temp_v0_2 = temp_v1 + 0x20;
    temp_t2 = var_t5_2 + 0xA;
    temp_t3 = temp_v1 + 0x18;
    poly->x3 = temp_v0_2;
    poly->x1 = temp_v0_2;
    poly->y1 = 0xD0;
    poly->y0 = 0xD0;
    poly->y3 = 0xDF ^ 0;
    poly->y2 = 0xDF;
    poly->pad2 = 0x1EE;
    poly->pad3 = 0x11;
    poly->x2 = var_t5_2;
    poly->x0 = var_t5_2;
    var_t5_3 = var_t5_2 + 0x10;
    poly = poly->tag;
    poly->tpage = 0x1F;
    poly->clut = 0x197;
    poly->x0 = var_t5_2 - 6;
    poly->y0 = 0xCB;
    poly->u0 = 0x80;
    poly->v0 = 0;
    poly->u1 = 0x10;
    poly->v1 = 0x18;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    poly->tpage = 0x1F;
    poly->clut = 0x197;
    poly->x0 = temp_v1 + 0x16;
    poly->y0 = 0xCB;
    poly->u0 = 0xA8;
    poly->v0 = 0;
    poly = poly;
    poly->u1 = 0x10;
    poly->v1 = 0x18;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    setcode(poly, 4);
    poly->y1 = 0xCD;
    poly->y0 = 0xCD;
    poly->y3 = 0xE1;
    poly->y2 = 0xE1;
    do {
        poly->u2 = 0x98;
        poly->u0 = 0x98;
        poly->u3 = 0x9C;
        poly->u1 = 0x9C;
        poly->v1 = 2;
        poly->v0 = 2;
        poly->tpage = 0x1F;
        poly->clut = 0x197;
        poly->x2 = temp_t2;
        poly->x0 = temp_t2;
        poly->x3 = temp_t3;
        poly->x1 = temp_t3;
        poly->v3 = 0x16;
    } while (0);
    poly->v2 = 0x16;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0;
    poly = poly->tag;
    var_a1_3 = &sp10;
    while (poly != 0) {
        var_v1 = *var_a1_3++;
        temp_v1_2 = var_v1;
        if (temp_v1_2 != 0) {
            poly->x0 = var_t5_3;
            poly->u0 = (temp_v1_2 & 0xF) * 8;
            poly->tpage = 0x1E;
            poly->clut = 0x196;
            poly->v0 = (temp_v1_2 & 0xF0) / 2;
            poly->v1 = 8;
            poly->u1 = 8;
            poly->pad2 = 0x1F0;
            poly->pad3 = 0;
            poly->y0 = 0xD4;
            poly = poly->tag;
            var_t5_3 += 8;
        } else {
            var_t5_3 += 4;
        }
    }

    D_80097410 = 0x130;
}
#endif

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80193270);

INCLUDE_ASM("asm/us/st/wrp/nonmatchings/6FD0", func_80193658);

POLY_GT4* func_801937A8(POLY_GT4* poly) {
    while (poly) {
        if (poly->p3 == 0)
            return poly;
        poly = (POLY_GT4*)poly->tag;
    }
    return NULL;
}

POLY_GT4* func_801937D8(POLY_GT4* poly, u8 index) {
    if (poly) {
        s32 index_ = index;
    loop_2:
        if (poly->p3 == 0) {
            POLY_GT4* var_v0 = NULL;
            POLY_GT4* firstPoly = poly;
            s32 i = 1;
            if (i < index_) {
                do {
                    poly = (POLY_GT4*)poly->tag;
                    if (!poly)
                        return NULL;
                } while (poly->p3 == 0 && ++i < index);
            }
            var_v0 = firstPoly;
            if (i == index_)
                return var_v0;
        }
        poly = (POLY_GT4*)poly->tag;
        if (poly) {
            goto loop_2;
        }
    }
    return NULL;
}

POLY_GT4* func_80193854(POLY_GT4* startPoly, s32 count) {
    POLY_GT4* poly;
    s8 unk;
    s32 i;

    if (startPoly->p3) {
        startPoly->p3 = 0;
    } else {
        startPoly->p3 = 1;
    }

    poly = startPoly;
    for (i = 0; i < count; i++) {
        if (poly->p3) {
            poly->pad3 &= ~8;
            unk = 0;
        } else {
            poly->pad3 |= 8;
            unk = 1;
        }

        poly = (POLY_GT4*)poly->tag;
        if (poly == 0)
            return 0;
        poly->p3 = unk;
    }

    return poly;
}

void func_801938DC(POLY_GT4* arg0) {
    arg0->p1 = 0;
    arg0->p2 = 0;
    arg0->p3 = 0;
    ((POLY_GT4*)arg0->tag)->x1 = 0;
    ((POLY_GT4*)arg0->tag)->y1 = 0;
    ((POLY_GT4*)arg0->tag)->y0 = 0;
    ((POLY_GT4*)arg0->tag)->x0 = 0;
    ((POLY_GT4*)arg0->tag)->clut = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u0 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r1 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->u1 = 0;
    ((POLY_GT4*)arg0->tag)->tpage = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->r2 = 0;
    *(u16*)&((POLY_GT4*)arg0->tag)->b2 = 0;
    ((POLY_GT4*)arg0->tag)->u2 = 0;
    ((POLY_GT4*)arg0->tag)->v2 = 0;
    ((POLY_GT4*)arg0->tag)->r3 = 0;
    ((POLY_GT4*)arg0->tag)->b3 = 0;
    ((POLY_GT4*)arg0->tag)->x2 = 0;
    ((POLY_GT4*)arg0->tag)->y2 = 0;
}

void func_801939BC(POLY_GT4* poly) {
    func_801938DC(poly);
    poly->p3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 1;
    ((POLY_GT4*)poly->tag)->code = 2;
    ((POLY_GT4*)poly->tag)->pad3 = 0xA;
}

void func_80193A10(POLY_GT4* poly) {
    poly->p3 = 0;
    poly->pad3 = 8;
    ((POLY_GT4*)poly->tag)->p3 = 0;
    ((POLY_GT4*)poly->tag)->code = 4;
    ((POLY_GT4*)poly->tag)->pad3 = 8;
}

s32 func_80193A3C(u8* arg0, u8 value) {
    s32 ret = 0;
    u8* phi_a0 = arg0 + 4;
    s32 i;

    for (i = 0; i < 4; i++) {
        u8* ptrCur = phi_a0;
        s32 ptrEnd = (s32)phi_a0 + 3;
        do {
            s32 phi_v0 = *ptrCur - value;
            if (phi_v0 < 0) {
                phi_v0 = 0;
            } else {
                ret |= 1;
            }

            *ptrCur++ = phi_v0;
        } while ((s32)ptrCur < ptrEnd);

        phi_a0 += 0xC;
    }

    return ret;
}
