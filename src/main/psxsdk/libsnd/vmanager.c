#define INCLUDE_ASM_NEW
#include "common.h"
#include "libsnd_internal.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmAlloc);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOnNow);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmDoAllocate);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", vmNoiseOn);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", vmNoiseOn2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", note2pitch);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", note2pitch2);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SePitchBend);

void SsUtVibrateOn(void) {}

void SsUtVibrateOff(void) {}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SeAutoVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SeAutoPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SetAutoPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmInit);

void SpuVmNoiseOnWithAdsr(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v0;

    D_800978D7 = 0x7F;
    temp_v0 = SpuVmAlloc(0xFF) & 0xFF;
    D_800978E2 = temp_v0;
    if (temp_v0 < (s32)spuVmMaxVoice) {
        vmNoiseOn2((u8)D_800978E2, arg0, arg1, arg2, arg3);
    }
}

void SpuVmNoiseOff(void) {
    s16 var_a0;
    for (var_a0 = 0; var_a0 < spuVmMaxVoice; var_a0++) {
        if (_svm_voice[var_a0].unk1b == 2) {
            _svm_voice[var_a0 & 0xff].unk1b = 0;
            _svm_voice[var_a0 & 0xff].unk04 = 0;
            // pointer to 0x1F801C00
            D_80032F10[0x194 / 2] = 0;
            D_80032F10[0x196 / 2] = 0;
        }
    }
}

void SpuVmNoiseOn(s32 arg0, s32 arg1) {
    D_800978D7 = 0x7F;
    D_800978E2 = SpuVmAlloc(0xFF);
    if (D_800978E2 < spuVmMaxVoice) {
        vmNoiseOn2(D_800978E2, arg0, arg1, 0x80FF, 0x5FC8);
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmPBVoice);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmPitchBend);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmFlush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOn);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmKeyOff);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSeKeyOn);

void SpuVmSeKeyOff(s16 arg0, s16 arg1, u16 arg2) {
    SpuVmKeyOff(0x21, arg0, arg1, arg2);
}

void KeyOnCheck(void) {}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetSeqVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmGetSeqVol);

extern s16 D_800978DE;

s16 SpuVmGetSeqLVol(s16 arg0) {
    struct SeqStruct* new_var;
    new_var = _ss_score[arg0 & 0xFF];
    do {
    } while (0);
    D_800978DE = arg0;
    return new_var[((s32)(arg0 & 0xFF00)) >> 8].unk74;
}

s16 SpuVmGetSeqRVol(s16 arg0) {
    struct SeqStruct* new_var;
    new_var = _ss_score[arg0 & 0xFF];
    do {
    } while (0);
    D_800978DE = arg0;
    return new_var[((s32)(arg0 & 0xFF00)) >> 8].unk76;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSeqKeyOff);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetProgVol);

s32 SpuVmGetProgVol(s16 arg0, s16 arg1) {
    if (!(SpuVmVSetUp(arg0, arg1))) {
        return D_8006C3B4[arg1].mvol;
    } else {
        return -1;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetProgPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmGetProgPan);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOn);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOff);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOnV);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtKeyOffV);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtPitchBend);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtChangePitch);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtChangeADSR);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtGetDetVVol);

s32 SsUtSetDetVVol(s16 arg0, s16 arg1, s16 arg2) {
    s32 temp[2];
    if (arg0 >= 0 && arg0 < 24) {
        _svm_sreg_buf[arg0].field_0_vol_left = arg1;
        _svm_sreg_buf[arg0].field_2_vol_right = arg2;
        _svm_sreg_dirty[arg0] = _svm_sreg_dirty[arg0] | 3;
        return 0;
    }

    return -1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtGetVVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtSetVVol);

s16 SsUtAutoVol(s16 vc, s16 start_vol, s16 end_vol, s16 delta_time) {
    if (!(vc >= 0x18U)) {
        SeAutoVol(vc, start_vol, end_vol, delta_time);
        return 0;
    }
    return -1;
}

s16 SsUtAutoPan(s16 vc, s16 start_pan, s16 end_pan, s16 delta_time) {
    if (!(vc >= 0x18U)) {
        SeAutoPan(vc, start_pan, end_pan, delta_time);
        return 0;
    }
    return -1;
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtAllKeyOff);
