#include "common.h"
#include "libspu_internal.h"

s32 SpuSetReverb(s32 on_off) {
    unsigned int new_var;
    u16 var_v1;
    switch (on_off) {
    case 0:
        D_800330A0 = 0;
        var_v1 = _spu_RXX->rxx.spucnt;
        var_v1 = var_v1 & 0xFF7F;
        _spu_RXX->rxx.spucnt = var_v1;
        break;

    case 1:
        if ((D_800330A4 != on_off) &&
            (_SpuIsInAllocateArea_(D_800330A8) != 0)) {
            D_800330A0 = 0;
            var_v1 = _spu_RXX->rxx.spucnt;
            var_v1 = var_v1 & 0xFF7F;
            new_var = var_v1;
            _spu_RXX->rxx.spucnt = new_var;
        } else {
            D_800330A0 = on_off;
            var_v1 = (new_var = _spu_RXX->rxx.spucnt) | 0x80;
            _spu_RXX->rxx.spucnt = var_v1;
        }
        break;
    }

    return D_800330A0;
}
