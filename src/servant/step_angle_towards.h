// SPDX-License-Identifier: AGPL-3.0-or-later

// This is a variant on a clamp function that adjusts
// the target by either the difference in current and target
// or by the maximum value.
s16 StepAngleTowards(s16 current, s16 target, s16 step) {
    s16 maxStep = abs(target - current);
    if (step > maxStep) {
        step = maxStep;
    }

    if (target < current) {
        if (maxStep < 0x800) {
            target += step;
        } else {
            target -= step;
        }
    } else {
        if (maxStep < 0x800) {
            target -= step;
        } else {
            target += step;
        }
    }
    return target & 0xFFF;
}
