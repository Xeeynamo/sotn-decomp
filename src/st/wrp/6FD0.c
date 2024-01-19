/*
 * File: 6FD0.c
 * Overlay: WRP
 * Description: All warp rooms.
 */

#include "wrp.h"

typedef struct {
    s16 x, y;
} WarpCoord;

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
LayoutEntity* g_pStObjLayout[] = {
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
LayoutEntity* D_80180310[] = {
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
void func_8018F510(Entity*);
void func_8018F838(Entity*);
void EntityUnkId15(Entity*);
void EntityWarpRoom(Entity*);
void EntityWarpSmallRocks(Entity*);
void EntityPrizeDrop(Entity*);
PfnEntityUpdate PfnEntityUpdates[] = {
    /* 3E4 */ (PfnEntityUpdate)EntityBreakable,
    /* 3E8 */ (PfnEntityUpdate)EntityExplosion,
    /* 3EC */ (PfnEntityUpdate)EntityPrizeDrop,
    /* 3F0 */ (PfnEntityUpdate)EntityNumericDamage,
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
    /* 42C */ (PfnEntityUpdate)func_8018F510,
    /* 430 */ (PfnEntityUpdate)func_8018F838,
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
u16 D_80180458[] = {
    0x0003, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000,
};
u16 g_EInitGeneric[] = {
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
// *** entity definition end ***

// *** entity declaration start ***
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
u16 D_80180608[] = {
    /* 608 */ 0x0000, 0x0000,
    /* 60C */ 0x0200, 0x0000,
    /* 610 */ 0x0400, 0x0000,
    /* 614 */ 0x0600, 0x0000,
    /* 618 */ 0x0800, 0x0000,
    /* 61C */ 0x0A00, 0x0000,
    /* 620 */ 0x0C00, 0x0000,
    /* 624 */ 0x0E00, 0x0000,
    /* 628 */ 0x1000, 0x0000,
    /* 62C */ 0x1200, 0x0000,
    /* 630 */ 0x1400, 0x0000,
    /* 634 */ 0x1600, 0x0000,
    /* 638 */ 0x1800, 0x0000,
    /* 63C */ 0x1A00, 0x0000,
    /* 640 */ 0x1C00, 0x0000,
    /* 644 */ 0x1E00, 0x0000,
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

u8* D_80180E58[] = {
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
extern u16 D_80180F1C[];
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

// *** rodata section start ***
const char D_80186E30[] = "step %x\n";
const char D_80186E3C[] = "move_room%x\n";
const char D_80186E4C[] = "for_x:%x y%x\n";
// gives some padding to align it to the next section
const char D_80186E5C[] = "move_x:%x y%x\n\0\0\0\0\0";
// TODO import missing RODATA
// *** rodata section end ***

// *** bss? section start ***
extern LayoutEntity* D_80193AB0;
extern u16* D_80193AB4;
extern u8 D_80193AB8;
extern u8 D_80193ABC;
extern u16 g_ItemIconSlots[];
// *** bss? section end ***

void func_80186FD0(Entity* arg0) {
    ObjInit2* objInit = &D_801804E0[arg0->params];
    if (arg0->step == 0) {
        InitializeEntity(D_80180494);
        arg0->animSet = objInit->animSet;
        arg0->zPriority = objInit->zPriority;
        arg0->unk5A = objInit->unk4.s;
        arg0->palette = objInit->palette;
        arg0->drawFlags = objInit->drawFlags;
        arg0->blendMode = objInit->blendMode;

        if (objInit->unkC != 0) {
            arg0->flags = objInit->unkC;
        }

        if (arg0->params == 1) {
            arg0->rotX = arg0->rotY = 0x0200;
        }
    }

    AnimateEntity(objInit->unk10, arg0);
}

void func_801870B0(Entity* entity) {
    s32 ret;
    u16* temp_v0_2;
    u16 temp_s1 = entity->params;
    u16 phi_v1;
    u16 unk;
    entity->unk6D[0] = 0;

    if (entity->step != 0) {
        switch (temp_s1) {
        case 4:
        case 5:
            if (g_Tilemap.x != 0) {
                return;
            }
            break;

        case 6:
            if (g_pads->pressed & PAD_TRIANGLE) {
                g_Tilemap.x = 0;
                g_Tilemap.width = 1280;
                entity->step++;
                return;
            }
            break;
        }

        if (entity->unk44 != 0) {
            ret = GetSideToPlayer();
            phi_v1 = entity->ext.generic.unk7C.s;
            if (phi_v1 != 0) {
                phi_v1 = (ret & 2) * 2;
            } else {
                phi_v1 = (ret & 1) * 4;
            }
            unk = 8;
            temp_s1 = (temp_s1 * unk) + phi_v1;
            temp_v0_2 = &D_80180538[temp_s1];
            g_Tilemap.x = *(temp_v0_2++);
            g_Tilemap.y = *(temp_v0_2++);
            g_Tilemap.width = *(temp_v0_2++);
            g_Tilemap.height = *(temp_v0_2++);
        }
    } else {
        InitializeEntity(D_80180488);
        entity->ext.generic.unk7C.s = D_80180530[temp_s1];
        if (entity->ext.generic.unk7C.s != 0) {
            entity->hitboxWidth = D_80180528[temp_s1];
            entity->hitboxHeight = 16;
        } else {
            entity->hitboxWidth = 16;
            entity->hitboxHeight = D_80180528[temp_s1];
        }
    }
}

void CreateEntityFromCurrentEntity(u16 entityId, Entity* entity);
void ReplaceBreakableWithItemDrop(Entity*);
void EntityBreakable(Entity* entity) {
    u16 breakableType = entity->params >> 0xC;
    if (entity->step) {
        AnimateEntity(g_eBreakableAnimations[breakableType], entity);
        if (entity->unk44) { // If the candle is destroyed
            Entity* entityDropItem;
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            entityDropItem = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entityDropItem != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, entityDropItem);
                entityDropItem->params =
                    g_eBreakableExplosionTypes[breakableType];
            }
            ReplaceBreakableWithItemDrop(entity);
        }
    } else {
        InitializeEntity(g_eBreakableInit);
        entity->zPriority = g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 0x14;
        entity->blendMode = g_eBreakableBlendModes[breakableType];
        entity->hitboxHeight = g_eBreakableHitboxes[breakableType];
        entity->animSet = g_eBreakableanimSets[breakableType];
    }
}
