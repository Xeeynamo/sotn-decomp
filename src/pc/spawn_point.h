// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_SPAWN_POINT_H
#define PC_SPAWN_POINT_H

#include <game.h>
#include "pc.h"

int SpawnPoint_StageForName(const char* name);
void SpawnPoint_Init(const struct InitGameParams* params);
void SpawnPoint_OnFrame(void);
void SpawnPoint_HookOverlay(Overlay* o);

#endif
