// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A071C);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A07CC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A09DC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A0A80);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1120);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A16E4);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801C5518_from_no4);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801B5004_from_rbo5);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1BE8);

extern s16 g_splashAspects[];
extern s32 g_SplashYMovement[];

#include "../../st/entity_splash_water.h"

#include "../../st/entity_water_drop.h"
