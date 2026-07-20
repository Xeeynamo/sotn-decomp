// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

char* g_LuckCode = "X-X!V''Q";
char* g_AxeArmorCode = "AXEARMOR";
char* g_GTIClubCode = "GTI-CLUB";

__asm__(".text\n.align 2\n.data");

typedef struct {
    u16 frameOffset;
    u16 paletteOffset;
} StatusHudSpriteOffset;

StatusHudSpriteOffset g_StatusHudSpriteOffsets[9] = {
    {5, 1}, {6, 2}, {26, 5}, {26, 5}, {26, 5}, {7, 0}, {7, 0}, {7, 0}, {0, 0},
};

u16 g_StatusHudPrimitiveLayout[29] = {
    0x0002, 0x0018, 0x0110, 0x0016, 0x0004, 0x0074, 0x011F, 0x0072,
    0x0129, 0x0072, 0x0012, 0x001D, 0x001B, 0x001D, 0x0014, 0x0029,
    0x0028, 0x0016, 0x1429, 0x142D, 0x1224, 0x1425, 0x1128, 0x1425,
    0x1425, 0x192E, 0x132A, 0x1125, 0x1429,
};

StatusHudSpriteOffset g_AlternateStatusHudSpriteOffsets[8] = {
    {5, 1}, {17, 0}, {17, 10}, {6, 0}, {6, 0}, {6, 0}, {6, 0}, {0, 0},
};

u16 g_AlternateStatusHudPrimitiveLayout[33] = {
    0x0002, 0x0018, 0x0004, 0x0074, 0x0019, 0x0074, 0x0010, 0x001D, 0x0018,
    0x001D, 0x0020, 0x001D, 0x0014, 0x0029, 0x002D, 0x0015, 0x0000, 0x1429,
    0x142D, 0x1224, 0x1425, 0x1128, 0x1425, 0x1425, 0x192E, 0x132A, 0x1125,
    0x1429, 0x0000, 0x0000, 0x0064, 0x0000, 0x0064,
};

s32 g_StatusWindowColorRed = 0;
s32 g_StatusWindowColorGreen = 0;
s32 g_StatusWindowColorBlue = 8;

u16 g_StatusPortraitPalette[16] = {
    0xC0A8, 0x8421, 0x84AB, 0x8D2F, 0x91D6, 0x929B, 0x994A, 0xA5CE,
    0x8421, 0x9CE7, 0xFFE0, 0x98A5, 0xA94A, 0xBE2E, 0xC2F7, 0xF39C,
};

SaturnSpriteImage g_StatusPortraitImages[17] = {
    {32, 48, 0x0000}, {20, 8, 0x0300},  {20, 8, 0x0328},  {12, 8, 0x0350},
    {12, 8, 0x0368},  {24, 28, 0x0380}, {20, 28, 0x0428}, {12, 28, 0x04B4},
    {20, 16, 0x0508}, {16, 16, 0x0558}, {12, 16, 0x0598}, {20, 16, 0x05C8},
    {16, 20, 0x0618}, {16, 16, 0x0668}, {16, 16, 0x06A8}, {16, 16, 0x06E8},
    {0, 0, 0x0728},
};

extern const char g_StatusMenuFamiliarList[];
extern const char g_StatusMenuFamiliar[];
extern const char g_StatusMenuOther[];
extern const char g_StatusMenuCape[];
extern const char g_StatusMenuArmor[];
extern const char g_StatusMenuHelm[];
extern const char g_StatusMenuHolder[];
extern const char g_StatusMenuLeftHandWeapon[];
extern const char g_StatusMenuRightHandWeapon[];
extern const char g_StatusMenuMedicine[];
extern const char g_StatusMenuShield[];
extern const char g_StatusMenuProjectile[];
extern const char g_StatusMenuBomb[];
extern const char g_StatusMenuFood[];
extern const char g_StatusMenuTwoHandedSword[];
extern const char g_StatusMenuClub[];
extern const char g_StatusMenuFist[];
extern const char g_StatusMenuThrowingSword[];
extern const char g_StatusMenuSword[];
extern const char g_StatusMenuDagger[];
extern const char g_StatusMenuSystem[];
extern const char g_StatusMenuRelics[];
extern const char g_StatusMenuSpecialMoves[];
extern const char g_StatusMenuEquipment[];
extern const char g_StatusMenuSpecialMoveList[];
extern const char g_StatusMenuDefense[];
extern const char g_StatusMenuAttack[];
extern const char g_StatusMenuElapsedTime[];
extern const char g_StatusMenuWindowColor[];
extern const char g_StatusMenuCustomColor[];
extern const char g_StatusMenuReversibleCloak[];
extern const char g_StatusMenuButtonAssignment[];
extern const char g_StatusMenuUnknown[];

const char* g_StatusMenuLabelPointers[] = {
    g_StatusMenuAttack,
    g_StatusMenuDefense,
    g_StatusMenuSpecialMoveList,
    g_StatusMenuEquipment,
    g_StatusMenuSpecialMoves,
    g_StatusMenuRelics,
    g_StatusMenuSystem,
    g_StatusMenuDagger,
    g_StatusMenuSword,
    g_StatusMenuThrowingSword,
    g_StatusMenuFist,
    g_StatusMenuClub,
    g_StatusMenuTwoHandedSword,
    g_StatusMenuFood,
    g_StatusMenuBomb,
    g_StatusMenuProjectile,
    g_StatusMenuShield,
    g_StatusMenuMedicine,
    g_StatusMenuRightHandWeapon,
    g_StatusMenuLeftHandWeapon,
    g_StatusMenuHolder,
    g_StatusMenuHelm,
    g_StatusMenuArmor,
    g_StatusMenuCape,
    g_StatusMenuOther,
    g_StatusMenuOther,
    g_StatusMenuFamiliar,
    g_StatusMenuFamiliarList,
    g_StatusMenuUnknown,
    g_StatusMenuButtonAssignment,
    g_StatusMenuReversibleCloak,
    g_StatusMenuCustomColor,
    g_StatusMenuWindowColor,
    g_StatusMenuElapsedTime,
};

typedef struct {
    u8 widthCode;
    u8 height;
    u16 coordinateOffset;
} StatusFaceImageLayout;

StatusFaceImageLayout g_StatusFaceImageLayouts[9] = {
    {0, 0, 0},  {0, 10, 15}, {0, 11, 16}, {0, 9, 14}, {0, 13, 18},
    {0, 7, 12}, {0, 8, 13},  {0, 12, 17}, {0, 0, 0},
};

void func_0607AC40(Entity* self);

PfnEntityUpdate g_FallingPrimitiveUpdate = func_0607AC40;
u32 g_FallingPrimitiveInitData = 0;
s16 g_FallingPrimitiveCollisionSensors[] = {0, 0, 0xFF};
