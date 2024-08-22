// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #44. Used by weapons:
// Heart Refresh
#include "weapon_private.h"
#include "w_044_1.h"
#include "w_044_2.h"
#define g_Animset w_044_1
#define g_Animset2 w_044_2

static u16 D_138000_8017A040[] = {
    COLOR16(0, 0, 0, 0),    COLOR16(31, 0, 0, 1),   COLOR16(24, 16, 4, 1),
    COLOR16(31, 24, 4, 1),  COLOR16(13, 9, 3, 1),   COLOR16(20, 13, 7, 1),
    COLOR16(24, 18, 12, 1), COLOR16(25, 23, 20, 1), COLOR16(4, 5, 21, 1),
    COLOR16(7, 9, 31, 1),   COLOR16(4, 6, 4, 1),    COLOR16(8, 9, 8, 1),
    COLOR16(13, 13, 12, 1), COLOR16(16, 18, 18, 1), COLOR16(21, 22, 22, 1),
    COLOR16(24, 27, 30, 1), COLOR16(0, 0, 0, 0),    COLOR16(2, 0, 0, 1),
    COLOR16(3, 0, 0, 1),    COLOR16(5, 0, 0, 1),    COLOR16(7, 1, 0, 1),
    COLOR16(8, 1, 0, 1),    COLOR16(10, 1, 1, 1),   COLOR16(12, 2, 1, 1),
    COLOR16(14, 2, 1, 1),   COLOR16(15, 2, 1, 1),   COLOR16(17, 3, 1, 1),
    COLOR16(19, 3, 2, 1),   COLOR16(20, 3, 2, 1),   COLOR16(22, 4, 2, 1),
    COLOR16(24, 4, 2, 1),   COLOR16(26, 5, 3, 1),   COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
    COLOR16(0, 0, 0, 1),    COLOR16(0, 0, 0, 1),
};

static s32 D_138000_8017A260[] = {
    0x000, 0x100, 0x200, 0x300, 0x400, 0x500, 0x600, 0x700,
    0x800, 0x900, 0xA00, 0xB00, 0xC00, 0xD00, 0xE00, 0xF00};

static u16* g_WeaponCluts[] = {D_138000_8017A040};
static s32 g_HandId = HAND_ID;

#include "shared.h"

INCLUDE_ASM("weapon/nonmatchings/w_044", EntityWeaponAttack);

s32 func_ptr_80170004(Entity* self) {}

static void func_ptr_80170008(Entity* self) {}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 44; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
