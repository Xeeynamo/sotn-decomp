// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_OVERLAY_H
#define PC_OVERLAY_H

#include <game.h>
#include <servant.h>

#if defined(_WIN32)
#define OVL_API __declspec(dllexport)
#else
#define OVL_API
#endif

// public signature for the overlay entrypoint
typedef void (*PfnInitStage)(Overlay* o);
typedef void (*PfnInitServant)(ServantDesc* o);

// DLL/shared library name to load, writes public to struct
bool LoadStageOverlay(const char* name, Overlay* o);

// DLL/shared library name to load, writes public to struct
bool LoadServantOverlay(const char* name, ServantDesc* o);

#endif
