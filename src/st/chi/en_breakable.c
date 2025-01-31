// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_breakable.c
 * Overlay: CHI
 * Description: ENTITY - Breakable Object breaks into debris when struck
 */

#include "chi.h"

// D_80180818
static u8 anim_1[] = {3, 14, 4, 15, 4, 16, 4, 17, 4, 18, 4, 19, 3, 20, 0, 0};

// D_80180828
static u8 anim_2[] = {3, 21, 4, 22, 4, 23, 4, 24, 4, 25, 4, 26, 3, 27, 0, 0};

// D_80180838
static u8* g_eBreakableAnimations[] = {
    anim_1, anim_2, NULL, NULL, NULL, NULL, NULL, NULL};

// D_80180858
static u8 g_eBreakableHitboxes[] = {12, 20, 0, 0, 0, 0, 0, 0};

// D_80180860
#ifndef VERSION_PSP // on PSP this is in the BSS section, not data
static u8 g_eBreakableExplosionTypes[] = {3, 3, 0, 0, 0, 0, 0, 0};
#else
extern u8 g_eBreakableExplosionTypes[];
#endif

// D_80180868
static u16 g_eBreakableAnimSets[] = {
    ANIMSET_OVL(1), ANIMSET_OVL(1), 0, 0, 0, 0, 0, 0};

// D_80180878
static u8 g_eBreakableDrawModes[] = {
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT,
    DRAW_DEFAULT};

// D_80180880
#ifndef VERSION_PSP
// on PSP this might be either optimised out to BSS or completely removed
static u16 g_eBreakableDebrisOffsets[] = {
    -4, -4, 3, -6, 2, 9, -4, 12, 0, 2, 0, 15, 0, 31};
#endif

// func_8019B698: [E_BREAKABLE] EntityBreakableWithDebris
// func_8019B914: [E_BREAKABLE_DEBRIS] EntityBreakableDebris
#include "en_breakable.h"
