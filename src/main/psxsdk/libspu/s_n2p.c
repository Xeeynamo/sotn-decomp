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
    s32 temp_a1_2;
    s32 temp_v1;
    u32 var_a3;
    s32 note_low;
    s32 var_v1;

    var_a3 = 0;
    for (var_v1 = 0; var_v1 < 16; var_v1++) {
        if ((arg2 >> var_v1) & 1) {
            var_a3 = var_v1;
        }        
    }
    
    temp_a1_2 = (1 << (var_a3 + 1)) - (1 << var_a3);
    temp_a0 = arg2 - (1 << var_a3);
    temp_v1 = arg1 + ((temp_a0 - (temp_a1_2 * ((temp_a0 * 12) / temp_a1_2)) / 12) * 0x600) / temp_a1_2;
    note_high = arg0 + ((var_a3 - 12) * 12) + (temp_a0 * 12) / temp_a1_2;
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

