// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_WEAPON_PRIVATE_H
#define SATURN_WEAPON_PRIVATE_H

#include "sattypes.h"
#include <saturn_sprite.h>
#include <saturn_weapon.h>

#ifdef SATZ
#define WEAPON_HEADER
#else
#define WEAPON_HEADER __attribute__((section(".rodata")))
#endif

typedef struct {
    /* 0x00 */ u16** frames;
    /* 0x04 */ s8* frameProps;
    /* 0x08 */ u16 palette;
    /* 0x0A */ u16 soundId;
    /* 0x0C */ u8 frameStart;
    /* 0x0D */ u8 soundFrame;
    /* 0x0E */ s16 unused;
} WeaponAnimation; // size = 0x10

typedef struct {
    u8 duration;
    u8 pose;
} WeaponPose;

#endif
