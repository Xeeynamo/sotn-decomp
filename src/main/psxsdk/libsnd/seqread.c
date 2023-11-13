#define INCLUDE_ASM_NEW
#include "common.h"
#include "libsnd_internal.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsSeqPlay);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsGetSeqData);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsNoteOn);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsSetProgramChange);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsSetControlChange);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContModulation);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContPortaTime);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContPortamento);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContResetAll);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContNrpn1);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContNrpn2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContRpn1);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContRpn2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsContDataEntry);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsSndSetVabAttr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsSetPitchBend);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/seqread", _SsGetMetaEvent);

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

    temp_v0 = var_a0 * 10;
    temp_a1->unk80 += temp_v0;
    return temp_v0;
}
