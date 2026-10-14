// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A071C);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A07CC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A09DC);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A0A80);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1120);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A16E4);

extern EInit g_EInitInteractable;
extern s16 water_slow_zones[];

#include "../../st/water_slow_zone.h"

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801B5004);

INCLUDE_ASM("boss/bo3/nonmatchings/water_effects", func_us_801A1BE8);

extern s16 g_splashAspects[];
extern s32 g_SplashYMovement[];

#include "../../st/entity_splash_water.h"

#include "../../st/entity_water_drop.h"
