#include "libsnd_i.h"

s16 SsUtSetReverbType(s16 arg0) {
    s16 var_v1;
    s32 var_a1;
    SpuReverbAttr* new_var;
    s32 var_v0;
    var_a1 = 0;
    var_v1 = arg0;
    if (arg0 < 0) {
        var_a1 = 1;
        var_v1 = -arg0;
    }
    if (((u32)(((u16)var_v1) & 0xFFFF)) < 0xAU) {
        _svm_rattr.mask = 1;
        if (var_a1 != 0) {
            var_v0 = (var_v1 | 0x100) << 0x10;
        } else {
            var_v0 = var_v1 << 0x10;
        }
        new_var = &_svm_rattr;
        _svm_rattr.mode = var_v0 >> 0x10;
        if (var_v1 == 0) {
            SpuSetReverb(0);
        }
        SpuSetReverbModeParam(new_var);
        return var_v1;
    }
    return -1;
}

s16 SsUtGetReverbType(void) { return _svm_rattr.mode; }
