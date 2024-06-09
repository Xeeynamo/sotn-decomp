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

// *** Group here all the Entity Init ***
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
// ******

static u32 D_801804D0[] = {0x00FF0140};
static u32 D_801804D4[] = {0x26022502, 0x26022702, 0x00000000};
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
