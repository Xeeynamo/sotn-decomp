#ifndef WEAPON_H
#define WEAPON_H

#define WEAPON
#include <game.h>
#include <sfx.h>

typedef struct {
    /* 0x00 */ void (*EntityWeaponAttack)(Entity* self);
    /* 0x04 */ void (*func_ptr_80170004)(Entity* self);
    /* 0x08 */ void (*func_ptr_80170008)(Entity* self);
    /* 0x0C */ void (*func_ptr_8017000C)(Entity* self);
    /* 0x10 */ void (*func_ptr_80170010)(void);
    /* 0x14 */ void (*func_ptr_80170014)(Entity* self);
    /* 0x18 */ int (*GetWeaponId)(void);
    /* 0x1C */ void (*LoadWeaponPalette)(s32 clutIndex);
    /* 0x20 */ void (*EntityWeaponShieldSpell)(Entity* self);
    /* 0x24 */ void (*func_ptr_80170024)(Entity* self);
    /* 0x28 */ void (*func_ptr_80170028)(Entity* self);
    /* 0x2C */ void (*WeaponUnused2C)(void);
    /* 0x30 */ void (*WeaponUnused30)(void);
    /* 0x34 */ void (*WeaponUnused34)(void);
    /* 0x38 */ void (*WeaponUnused38)(void);
    /* 0x3C */ void (*WeaponUnused3C)(void);
} Weapon /* 0x40 */;

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

#define N_WEAPON_PAL 12
extern u16 D_8006EDCC[2][N_WEAPON_PAL * PALETTE_LEN];
#endif

#ifdef VERSION_PC
// LoadWeaponPalette reads a predetermined amount of bytes from the weapon
// palette, often going out of the array boundaries. This is not a problem on
// PSX, but on any other platform we need to force each weapon palette to be
// `N_ARRAY_PAL` long to account for the extra data read.
#define N_ARRAY_PAL LEN(*D_8006EDCC)
#else
#define N_ARRAY_PAL
#endif
