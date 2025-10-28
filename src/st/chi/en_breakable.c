// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_breakable.c
 * Overlay: CHI
 * Description: ENTITY - Breakable Object breaks into debris when struck
 */

#include "chi.h"

#define CANDLE_HIT_SFX SFX_FIRE_SHOT
#define BREAKABLE_ZPRIORITY 112

// D_80180818: u8 anim_unk_314415
// D_80180828: anim_unk_321422
// D_80180838: animations
// D_80180858: hitbox_heights
// D_80180860: explosion_types
// D_80180868: anim_sets
// D_80180878: u8 draw_modes
// D_80180880: debris_offsets
// func_8019B698: [E_BREAKABLE] EntityBreakableWithDebris
// func_8019B914: [E_BREAKABLE_DEBRIS] EntityBreakableDebris
#include "../e_breakable_with_lighting.h"
