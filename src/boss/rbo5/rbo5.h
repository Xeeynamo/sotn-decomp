// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef RBO5_H
#define RBO5_H

#include <stage.h>

#define STAGE_IS_RBO5

#include "../doppleganger.h"

extern EInit g_EInitParticle;
extern EInit g_EInitLockCamera;

enum Palettes {
    PAL_NONE,
    PAL_UNK_210 = 0x210,
    PAL_UNK_218 = 0x218,
};

#endif // RBO5_H
