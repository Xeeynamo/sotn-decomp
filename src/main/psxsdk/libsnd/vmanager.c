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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmNoiseOnWithAdsr);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmNoiseOff);

void SpuVmNoiseOn(s32 arg0, s32 arg1) {
    s16 temp_v0;

    D_800978D7 = 0x7F;
    temp_v0 = SpuVmAlloc(0xFF);
    D_800978E2 = temp_v0;
    if (temp_v0 < spuVmMaxVoice) {
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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmGetSeqLVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmGetSeqRVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSeqKeyOff);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmSetProgVol);

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SpuVmGetProgVol);

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

INCLUDE_ASM("main/nonmatchings/psxsdk/libsnd/vmanager", SsUtSetDetVVol);

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
