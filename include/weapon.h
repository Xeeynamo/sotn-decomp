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

#define N_WEAPON_PAL 12
extern u16 D_8006EDCC[2][N_WEAPON_PAL * PALETTE_LEN];
#endif
