// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include "game.h"
#include "zero/overlay.h"

void InitStatsAndGear(void);

SaturnGameApi g_ApiInit = {
    g_EquipDefs,   ModeGame,      func_8011A9D8, LoadSubDisplayFiles,
    func_0606B760, func_0606BB4C, func_0606BEE4, func_0606C064,
    func_06074470, func_0606C774, func_0606C594, InitStatsAndGear,
};
