// SPDX-License-Identifier: MIT
#include "common.h"

extern s16 D_80033860[];

s32 _spu_note2pitch(s32 center_note, u16 center_note_frac, s32 offset_note,
                    u16 offset_note_frac) {
    s16 octave;
    s16 var_a1;
    s16 var_v1_2;
    u16 sample_rate;
    s32 pos;

    var_a1 = (offset_note_frac + center_note_frac) / 8;
    for (var_v1_2 = 0; var_a1 >= 16; var_v1_2++) {
        var_a1 -= 16;
    }
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    var_v1_2 += offset_note - (center_note - 60);
    pos = ((var_v1_2 % 12) * 16) + var_a1;
    sample_rate = D_80033860[pos];
    octave = (var_v1_2 / 12) - 5;
    if (octave > 0) {
        sample_rate <<= octave;
    } else if (octave < 0) {
        sample_rate >>= -octave;
    }
    return sample_rate;
}

s32 _spu_pitch2note(u16 arg0, u16 arg1, u16 arg2) {
    s32 temp_a0;
    s32 note_high;
    s32 lsb_mask;
    s32 temp_v1;
    s32 lsb;
    s32 note_low;
    s32 i;

    // Find least significant bit of arg2
    lsb = 0;
    for (i = 0; i < 16; i++) {
        if ((arg2 >> i) & 1) {
            lsb = i;
        }
    }

    // Equivalent to `lsb_mask = 1 << lsb;`
    lsb_mask = (1 << (lsb + 1)) - (1 << lsb);

    // Mask out lsb of arg2
    temp_a0 = arg2 - (1 << lsb);

    temp_v1 =
        arg1 +
        ((temp_a0 - (lsb_mask * ((temp_a0 * 12) / lsb_mask)) / 12) * 0x600) /
            lsb_mask;
    note_high = arg0 + ((lsb - 12) * 12) + (temp_a0 * 12) / lsb_mask;

    note_low = temp_v1 % 0x80;
    note_high += (temp_v1 < 0x80) ? 0 : 1;

    if (note_high < 0) {
        return -1;
    }
    if (note_high >= 0x80) {
        return -1;
    }

    return (note_high << 8) | note_low;
}
