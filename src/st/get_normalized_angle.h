// SPDX-License-Identifier: AGPL-3.0-only
u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2) {
    u16 temp_a2;
    u16 var_v0;

    temp_a2 = (s16)(arg2 - arg1);
    if (temp_a2 & 0x800) {
        var_v0 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    } else {
        return arg2;
    }
}
