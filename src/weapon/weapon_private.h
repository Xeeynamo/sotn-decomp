// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#include <weapon.h>

#if !defined(WEAPON0) && !defined(WEAPON1)
#define WEAPON0 // forces WEAPON0 for the time being
#endif

// macros for including assets dynamically based
// on HAND_ID.
//
// PSP keeps a separate copy of the generated animsets per hand.
// clang-format off
#define inner_path(hand, n) CPP_STR(PATH_JOIN(gen/w##hand, n))
// clang-format on
#define path(hand, n) inner_path(hand, n)

// Used in weapon/w_046, weapon/w_053, weapon/w_056
typedef struct {
    /* 0x0 */ s16 uFlag; // flipX
    /* 0x2 */ s16 vFlag; // flipY
    /* 0x4 */ s16 clutFlag;
    /* 0x6 */ s16 lifetime;
    /* 0x8 */ s16 rotate;
    /* 0xA */ u8 r;
    /* 0xB */ u8 g;
    /* 0xC */ u8 b;
    /* 0xD */ u8 unused;
} WeaponParams;

#if defined(WEAPON0)
#define HAND_ID 0
#elif defined(WEAPON1)
#define HAND_ID 1
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID 0
#endif

extern s32 g_HandId;

// Weapon Factories all encode `g_HandId` at the top of the params
#define WFACTORY(id, param) (((g_HandId + 1) << 12) + FACTORY(id, param))

// This is the same as `WFACTORY`, except the order of operations
// is changed to add `id` to the `g_HandId` bits and then add then
// the shifted params. `WFACTORY` groups the `id` and `param`
// addition operation and is required for all other instances.
#define WFACTORY2(id, param) FACTORY(((g_HandId + 1) << 12) + (id), (param))

// PSP builds one overlay per weapon per hand, so each w*_*.c declares its own
// entry points and overlay table rather than sharing the ones below.
#ifndef VERSION_PSP
#ifndef NO_HEADER
// exported
void EntityWeaponAttack(Entity* self);
void LoadWeaponPalette(s32 clutIndex);
#ifndef FUNC_04_VOID
s32 func_ptr_80170004(Entity* self);
#else
void func_ptr_80170004(Entity* self);
#endif
void func_ptr_80170008(Entity* self);
#ifdef FUNC_0C_S32
s32 func_ptr_8017000C(Entity* self);
#else
void func_ptr_8017000C(Entity* self);
#endif
s32 func_ptr_80170010(Entity* self);
s32 func_ptr_80170014(Entity* self);
int GetWeaponId(void);
#ifdef SHIELDSPELL_S32
s32 EntityWeaponShieldSpell(Entity* self);
#else
void EntityWeaponShieldSpell(Entity* self);
#endif
void func_ptr_80170024(Entity* self);
void func_ptr_80170028(Entity* self);
void WeaponUnused2C(void);
void WeaponUnused30(void);
void WeaponUnused34(void);
void WeaponUnused38(void);
void WeaponUnused3C(void);

static Weapon WeaponOverlay = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008,
    func_ptr_8017000C,  func_ptr_80170010, func_ptr_80170014,
    GetWeaponId,        LoadWeaponPalette, EntityWeaponShieldSpell,
    func_ptr_80170024,  func_ptr_80170028, WeaponUnused2C,
    WeaponUnused30,     WeaponUnused34,    WeaponUnused38,
    WeaponUnused3C,
};
#endif // !NO_HEADER
#endif // !VERSION_PSP

#ifdef VERSION_PC
#include <psyz/module.h>
#include <string.h>

void Psyz_ModuleStart(void* param) {
    Weapon* o = param;
    memcpy(o, &WeaponOverlay, sizeof(Weapon));
}

void Psyz_ModuleStop(void) {}
#endif

#endif
