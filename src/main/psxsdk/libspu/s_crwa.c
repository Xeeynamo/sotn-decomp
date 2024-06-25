#include "common.h"
#include "libspu_internal.h"

void WaitEvent(s32);
s32 _SpuIsInAllocateArea_(u32);
extern s32 D_800330F8[];
extern s32 _spu_rev_startaddr[];
extern s32 _spu_EVdma;
extern s32 _spu_mem_mode_plus;
extern s32 _spu_transMode;

s32 SpuClearReverbWorkArea(s32 rev_mode) {
    volatile s32 callback;
    s32 oldTransmode;
    s32 var_s2;
    s32 var_s3;
    s32 transmodeCleared;
    u32 var_s0;
    u32 var_s1;

    callback = 0;
    transmodeCleared = 0;
    if ((rev_mode >= 0xAU) ||
        (_SpuIsInAllocateArea_(_spu_rev_startaddr[rev_mode]) != 0)) {
        return -1;
    }
    if (rev_mode == 0) {
        var_s1 = 0x10 << _spu_mem_mode_plus;
        var_s2 = 0xFFF0 << _spu_mem_mode_plus;
    } else {
        var_s1 = (0x10000 - _spu_rev_startaddr[rev_mode]) << _spu_mem_mode_plus;
        var_s2 = _spu_rev_startaddr[rev_mode] << _spu_mem_mode_plus;
    }
    oldTransmode = _spu_transMode;
    if (_spu_transMode == 1) {
        _spu_transMode = 0;
        transmodeCleared = 1;
    }
    var_s3 = 1;
    if (_spu_transferCallback != 0) {
        callback = _spu_transferCallback;
        _spu_transferCallback = 0;
    }
    do {
        var_s0 = var_s1;
        if (!(var_s1 < 0x401U)) {
            var_s0 = 0x400;
        } else {
            var_s3 = 0;
        }

        _spu_t(2, var_s2);
        _spu_t(1);
        _spu_t(3, &D_800330F8[0], var_s0);
        WaitEvent(_spu_EVdma);
        var_s1 -= 0x400;
        var_s2 += 0x400;
    } while (var_s3 != 0);
    if (transmodeCleared != 0) {
        _spu_transMode = oldTransmode;
    }
    if (callback != 0) {
        _spu_transferCallback = callback;
    }
    return 0;
}
