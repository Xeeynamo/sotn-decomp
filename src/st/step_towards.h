// SPDX-License-Identifier: AGPL-3.0-or-later
#include <types.h>

// EntitySpectralSword primarily uses this as a method to smoothly rotate, but
// also to retract it's outer ring after an attack by decreasing the radius.
static bool StepTowards(s16* val, s32 target, s32 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }

    if (*val > target) {
        *val -= step;
    }

    if (*val < target) {
        *val += step;
    }

    return false;
}
