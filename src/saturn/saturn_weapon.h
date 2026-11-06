// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SATURN_WEAPON_H
#define SATURN_WEAPON_H

typedef struct {
    /* 0x00 */ void (*entries[16])();
    /* 0x40 */ void* data;
} SaturnWeaponOvl;

#define WEAPON_SLOTS 64
#define WEAPON_SLOT_SIZE 0x3000
#define WEAPON_CHR_SLOT_SIZE 0x4000

#endif
