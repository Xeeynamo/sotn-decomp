/*
 * File: 6FD0.c
 * Overlay: WRP
 * Description: All warp rooms.
 */

#include "wrp.h"
#include "../st_private.h"

// *** Overlay exports start ***
void CreateEntityWhenInHorizontalRange(LayoutEntity*);
void func_8018A520(s16);
void func_8018CAB0(void);
void func_801916C4(u16);
void BottomCornerText(u8*, u8);

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

// *** Layout entity definition start ***
LayoutEntity D_80181228[];
LayoutEntity D_80181250[];
LayoutEntity D_801812A0[];
LayoutEntity D_801812C8[];
LayoutEntity D_80181278[];
LayoutEntity D_801812F0[];
LayoutEntity D_80181304[];
LayoutEntity* g_pStObjLayoutHorizontal[] = {
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

LayoutEntity D_80181324[];
LayoutEntity D_8018134C[];
LayoutEntity D_80181374[];
LayoutEntity D_8018139C[];
LayoutEntity D_801813C4[];
LayoutEntity D_801813EC[];
LayoutEntity D_80181400[];
LayoutEntity* g_pStObjLayoutVertical[] = {
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
    /* 3E0 */ D_80181400,
};
// *** Layout entity definition end ***

// *** entity definition start ***
void func_80186FD0(Entity*);
void func_801870B0(Entity*);
void EntityUnkId13(Entity*);
void EntityUnkId14(Entity*);
void EntityUnkId15(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
PfnEntityUpdate PfnEntityUpdates[] = {
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)EntityExplosion,
    /* 3EC */ (PfnEntityUpdate)EntityPrizeDrop,
    /* 3F0 */ (PfnEntityUpdate)EntityDamageDisplay,
    /* 3F4 */ (PfnEntityUpdate)EntityRedDoor,
    /* 3F8 */ (PfnEntityUpdate)EntityIntenseExplosion,
    /* 3FC */ (PfnEntityUpdate)EntitySoulStealOrb,
    /* 400 */ (PfnEntityUpdate)EntityRoomForeground,
    /* 404 */ (PfnEntityUpdate)EntityStageNamePopup,
    /* 408 */ (PfnEntityUpdate)EntityEquipItemDrop,
    /* 40C */ (PfnEntityUpdate)EntityRelicOrb,
    /* 410 */ (PfnEntityUpdate)EntityHeartDrop,
    /* 414 */ (PfnEntityUpdate)EntityEnemyBlood,
    /* 418 */ (PfnEntityUpdate)EntityMessageBox,
    /* 41C */ (PfnEntityUpdate)EntityDummy,
    /* 420 */ (PfnEntityUpdate)EntityDummy,
    /* 424 */ (PfnEntityUpdate)func_80186FD0, // unused
    /* 428 */ (PfnEntityUpdate)func_801870B0, // unused? looks debugging stuff
    /* 42C */ (PfnEntityUpdate)EntityUnkId13,
    /* 430 */ (PfnEntityUpdate)EntityUnkId14,
    /* 434 */ (PfnEntityUpdate)EntityUnkId15,
    /* 438 */ (PfnEntityUpdate)EntityWarpRoom,
    /* 43C */ (PfnEntityUpdate)EntityWarpSmallRocks,
};

u16 g_eBreakableInit[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};
u16 g_InitializeData0[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_InitializeEntityData0[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 g_EInitGeneric[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
u16 g_InitDataEnt13[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
};
u16 D_80180488[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000,
};
u16 g_eInitGeneric2[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
};
u16 g_eDamageDisplayInit[] = {
    /**/ 0x0000, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
    /**/ 0x8001, 0x0000, 0x0000, 0x0000, 0x0003, 0x0000,
    /**/ 0x800B, 0x0001, 0x0048, 0x021A, 0x0061, 0x0000,
};
u16 D_801804C4[] = {
    0x8001, 0x0000, 0x0000, 0x0000, 0x0005, 0x0000,
};
// *** entity definition end ***

// *** entity declaration start ***
// owned by func_80186FD0
u32 D_801804D0[] = {0x00FF0140};
u32 D_801804D4[] = {0x26022502, 0x26022702, 0x00000000};
ObjInit2 D_801804E0[] = {
    {0x0006, 0x01FA, 0x0000, 0x0000, 0x00, 0x10, 0x00000000, D_801804D0},
    {0x8001, 0x00C0, 0x0000, 0x0000, 0x03, 0x30, 0x00000000, D_801804D4},
};

// Owned by EntityRedDoor to animate the tiles behind the door itself.
// There is a loop in EntityRedDoor that forces to write those tiles
// at every frame based on the door state to create the animation.
u16 g_eRedDoorTiles[2][8] = {
    {0x1D, 0x25, 0x75, 0x7D, 0xC6, 0xC7, 0xC8, 0xC9},
    {0x1F, 0x27, 0x77, 0x7F, 0xCA, 0xCB, 0xCC, 0xCD},
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
u8 g_eBreakableDrawModes[] = {
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

u32 D_80180608[] = {
    /* 608 */ 0x0000,
    /* 60C */ 0x0200,
    /* 610 */ 0x0400,
    /* 614 */ 0x0600,
    /* 618 */ 0x0800,
    /* 61C */ 0x0A00,
    /* 620 */ 0x0C00,
    /* 624 */ 0x0E00,
    /* 628 */ 0x1000,
    /* 62C */ 0x1200,
    /* 630 */ 0x1400,
    /* 634 */ 0x1600,
    /* 638 */ 0x1800,
    /* 63C */ 0x1A00,
    /* 640 */ 0x1C00,
    /* 644 */ 0x1E00,
};

// owned by EntityWarpRoom
u32 D_80180648 = 0;
u32 D_8018064C[] = {
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
// *** entity declaration end ***

// *** Unknown stuff start ***
u16 UNK_Invincibility0[] = {
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
