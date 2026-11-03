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
#define HAND_ID LEFT_HAND
#elif defined(WEAPON1)
#define HAND_ID RIGHT_HAND
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID LEFT_HAND
#endif

extern s32 g_HandId;

// Weapon Factories all encode `g_HandId` at the top of the params
#define WFACTORY(id, param) (((g_HandId + 1) << 12) + FACTORY(id, param))

// This is the same as `WFACTORY`, except the order of operations
// is changed to add `id` to the `g_HandId` bits and then add then
// the shifted params. `WFACTORY` groups the `id` and `param`
// addition operation and is required for all other instances.
#define WFACTORY2(id, param) FACTORY(((g_HandId + 1) << 12) + (id), (param))

#endif
