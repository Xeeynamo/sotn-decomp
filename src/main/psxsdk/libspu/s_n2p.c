// SPDX-License-Identifier: MIT
#include "common.h"

extern s16 D_80033860[];

s32 _spu_note2pitch(s32 center_note, u16 center_note_frac, s32 offset_note,
                    u16 offset_note_frac) {
    s16 octave;
    s32 temp_v0_3;
    s16 var_a1;
    s32 var_v0;
    s16 var_v1_2;
    u16 sample_rate;
    s32 pos;
    var_v0 = offset_note_frac + center_note_frac;
    if (var_v0 < 0) {
        var_v0 += 7;
    }
    var_a1 = var_v0 >> 3;
    var_v1_2 = 0;
    while (var_a1 >= 16) {
        var_a1 = var_a1 - 16;
        var_v1_2 += 1;
    }
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    temp_v0_3 = offset_note - (center_note - 60);
    var_v1_2 = var_v1_2 + temp_v0_3;
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/s_n2p", _spu_pitch2note);
