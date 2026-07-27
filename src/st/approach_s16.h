// SPDX-License-Identifier: AGPL-3.0-or-later

bool func_801CDC80(s16* value, s16 target, s16 step) {
    if (abs(*value - target) < step) {
        *value = target;
        return true;
    }

    if (*value > target) {
        *value -= step;
    }

    if (*value < target) {
        *value += step;
    }

    return false;
}
