// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_OVERLAY_H
#define PC_OVERLAY_H

#include <game.h>
#include <servant.h>
#include <weapon.h>

#if defined(_WIN32)
#define OVL_API __declspec(dllexport)
#else
#define OVL_API
#endif

// public signature for the overlay entrypoint
typedef void (*PfnInitStage)(Overlay* o);
typedef void (*PfnInitServant)(ServantDesc* o);
typedef void (*PfnInitWeapon)(Weapon* o);

bool LoadStageOverlay(const char* name, Overlay* o);
bool LoadServantOverlay(const char* name, ServantDesc* o);
bool LoadWeaponOverlay(const char* name, unsigned handId, Weapon* o);

#endif
