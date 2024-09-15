// SPDX-License-Identifier: AGPL-3.0-or-later
u16 GetNormalizedAngle(u16 arg0, u16 arg1, u16 arg2) {
    u16 temp_a2 = arg2 - arg1;
    u16 ret;

    if (temp_a2 & 0x800) {
#if STAGE == STAGE_ST0
        ret = temp_a2 & 0x7FF;
#else
        ret = (0x800 - temp_a2) & 0x7FF;
#endif
    } else {
        ret = temp_a2;
    }

    if (ret > arg0) {
        if (temp_a2 & 0x800) {
            ret = arg1 - arg0;
        } else {
            ret = arg1 + arg0;
        }

        return ret;
    }
    return arg2;
}
