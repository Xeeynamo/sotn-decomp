// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO5_H
#define RBO5_H

#include <stage.h>

#define OVL_EXPORT(x) RBO5_##x

#include "../doppleganger.h"

extern EInit OVL_EXPORT(EInitParticle);
extern EInit g_EInitLockCamera;

#endif // RBO5_H
