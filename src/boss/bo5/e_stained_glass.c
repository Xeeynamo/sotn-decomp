// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

#include "../../st/e_stained_glass_blend.h"

extern s16 indices[];

#include "../../st/e_stained_glass_recurse.h"

INCLUDE_ASM("boss/bo5/nonmatchings/e_stained_glass", EntityStainedGlass);

INCLUDE_ASM("boss/bo5/nonmatchings/e_stained_glass", EntityStainedGlassBackground);
