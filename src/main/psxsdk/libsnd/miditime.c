#include "common.h"
#include "libsnd_internal.h"

s32 _SsReadDeltaValue(s16 arg0, s16 arg1) {
    s32 temp_v0;
    s32 var_v0;
    u8 temp_v1_2;
    u32 var_a0;
    u8* temp_v1;
    struct SeqStruct* temp_a1 = &_ss_score[arg0][arg1];
    var_a0 = *temp_a1->read_pos++;
    if (var_a0 == 0) {
        return 0;
    }

    // variable length quantity decoding (midi)
    if (var_a0 & 0x80) {
        var_a0 &= 0x7F;
        do {
            temp_v1_2 = *temp_a1->read_pos++;
            var_a0 = (var_a0 << 7) + (temp_v1_2 & 0x7F);
        } while (temp_v1_2 & 0x80);
    }

    temp_v0 = ((var_a0 << 2) + var_a0) * 2;
    temp_a1->unk80 += temp_v0;
    return temp_v0;
}
