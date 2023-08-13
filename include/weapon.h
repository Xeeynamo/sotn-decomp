#ifndef WEAPON_H
#define WEAPON_H

#include <game.h>

typedef struct {
    /* 0x00 */ void (*DoWeaponAttack)(Entity* self);
    /* 0x04 */ void* func_ptr_80170004;
    /* 0x08 */ void* func_ptr_80170008;
    /* 0x0C */ void* func_ptr_8017000C;
    /* 0x10 */ void* func_ptr_80170010;
    /* 0x14 */ void* func_ptr_80170014;
    /* 0x18 */ void* func_ptr_80170018; // int (*f)(void) ?
    /* 0x1C */ void (*LoadWeaponPalette)(s32 clutIndex);
    /* 0x20 */ void* func_ptr_80170020;
    /* 0x24 */ void* func_ptr_80170024;
    /* 0x28 */ void* func_ptr_80170028;
    /* 0x2C */ void* func_ptr_8017002C;
    /* 0x30 */ void* func_ptr_80170030;
    /* 0x34 */ void* func_ptr_80170034;
    /* 0x38 */ void* func_ptr_80170038;
    /* 0x3C */ void* func_ptr_8017003C;
} Weapon /* 0x40 */;

#endif
