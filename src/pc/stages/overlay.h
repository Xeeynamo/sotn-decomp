// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef PC_OVERLAY_H
#define PC_OVERLAY_H

#include <game.h>

#if defined(_WIN32)
#define OVL_API __declspec(dllexport)
#else
#define OVL_API
#endif

// public function necessary to register a stage overlay
#define OVL_ENTRYPOINT_NAME "InitStage"

// public signature of OVL_ENTRYPOINT_NAME
typedef void (*PfnInitStage)(Overlay* o);

// DLL/shared library name to load, writes endpoints to *o
bool LoadStageOverlay(const char* name, Overlay* o);

#endif
