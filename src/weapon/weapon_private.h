// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef WEAPON_PRIVATE_H
#define WEAPON_PRIVATE_H

#include <weapon.h>

#if !defined(WEAPON0) && !defined(WEAPON1)
#define WEAPON0 // forces WEAPON0 for the time being
#endif

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

// Used in weapon/w_051
typedef struct {
    s16 isFlipped;
    s16 timer;
    s16 rotation;
} AnimProperties;

// Used in weapon/w_029
typedef struct {
    f32 posX;
    f32 posY;
    s16 unk8;
    u16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 spawnDelay;
    s16 unk14;
    s16 state;
} FireShieldDragon;

#if defined(WEAPON0)
#define HAND_ID 0
#elif defined(WEAPON1)
#define HAND_ID 1
#else
#warning "WEAPON0 or WEAPON1 not specified. Falling back to WEAPON0."
#define HAND_ID 0
#endif

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
// exported
static void EntityWeaponAttack(Entity* self);
static void LoadWeaponPalette(s32 clutIndex);
#ifndef FUNC_04_VOID
static s32 func_ptr_80170004(Entity* self);
#else
static void func_ptr_80170004(Entity* self);
#endif
static void func_ptr_80170008(Entity* self);
#ifdef FUNC_0C_S32
static s32 func_ptr_8017000C(Entity* self);
#else
static void func_ptr_8017000C(Entity* self);
#endif
static s32 func_ptr_80170010(Entity* self);
static s32 func_ptr_80170014(Entity* self);
static int GetWeaponId(void);
#ifdef SHIELDSPELL_S32
static s32 EntityWeaponShieldSpell(Entity* self);
#else
static void EntityWeaponShieldSpell(Entity* self);
#endif
static void func_ptr_80170024(Entity* self);
static void func_ptr_80170028(Entity* self);
static void WeaponUnused2C(void);
static void WeaponUnused30(void);
static void WeaponUnused34(void);
static void WeaponUnused38(void);
static void WeaponUnused3C(void);

void DestroyEntity(Entity* entity);
static void SetSpriteBank1(SpriteParts* animset);
static void SetSpriteBank2(SpriteParts* animset);
static void DecelerateX(s32 amount);
static void DecelerateY(s32 amount);
static void SetSpeedX(s32 speed);

static Weapon header = {
    EntityWeaponAttack, func_ptr_80170004, func_ptr_80170008,
    func_ptr_8017000C,  func_ptr_80170010, func_ptr_80170014,
    GetWeaponId,        LoadWeaponPalette, EntityWeaponShieldSpell,
    func_ptr_80170024,  func_ptr_80170028, WeaponUnused2C,
    WeaponUnused30,     WeaponUnused34,    WeaponUnused38,
    WeaponUnused3C,
};

#endif // !VERSION_PSP

#ifdef VERSION_PC
#include "../pc/stages/overlay.h"
#include <string.h>

OVL_API void InitWeapon(Weapon* o) { memcpy(o, &header, sizeof(Weapon)); }
#endif

#endif
