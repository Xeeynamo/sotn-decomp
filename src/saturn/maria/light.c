// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "maria.h"

u16 g_MariaLightningPalettes[] = {0x194, 0x199};

s32 g_MariaLightningColorWhite[] = {0xFF, 0xFF, 0xFF};
s32 g_MariaLightningColorYellow[] = {0x7F, 0x7F, 0x3F};
s32 g_MariaLightningColorMagenta[] = {0x7F, 0x3F, 0x7F};

AnimationFrame* g_MariaAnimationGroups[] = {
    g_MariaAnim_060C2E64, ric_anim_land_from_air_run,
    ric_anim_stand,       ric_anim_stand_alt,
    g_MariaAnim_060C2E20, g_MariaAnim_060C31E8,
    g_MariaAnim_060C3438, g_MariaAnim_060C34D4,
    g_MariaAnim_060C34F8, g_MariaAnim_060C32F8,
    g_MariaAnim_060C3390, g_MariaAnim_060C33B0,
    g_MariaAnim_060C3284, ric_anim_walk,
};
