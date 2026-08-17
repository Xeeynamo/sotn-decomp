// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_WARP_H
#define PC_WARP_H

#include <game.h>
#include "pc.h"

#define PC_SPAWN_DEFAULT 0
#define PC_SPAWN_NP3_STAGE15 1
#define PC_SPAWN_RNO3_RSTAGE15 2
#define PC_SPAWN_NO0_STAGE16 3
#define PC_SPAWN_NO4_STAGE16 4
#define PC_SPAWN_RNO0_RSTAGE16 5
#define PC_SPAWN_RNO4_RSTAGE16 6
#define PC_SPAWN_COUNT 7

int Warp_StageForSpawnPoint(int spawnPoint);
void Warp_Init(const struct InitGameParams* params);
void Warp_OnFrame(void);
void Warp_HookOverlay(Overlay* o);

#endif
