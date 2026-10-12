// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_OVERLAY_H
#define PC_OVERLAY_H

#include <game.h>
#include <servant.h>
#include <weapon.h>

bool LoadStageOverlay(const char* name, Overlay* o);
bool LoadServantOverlay(const char* name, ServantDesc* o);
bool LoadWeaponOverlay(const char* name, unsigned handId, Weapon* o);

#endif
