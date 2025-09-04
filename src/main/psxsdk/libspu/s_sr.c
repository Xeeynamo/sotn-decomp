// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 SpuSetReverb(s32 on_off) {
    u16 var_v1;
    switch (on_off) {
    case 0:
        _spu_rev_flag = 0;
#ifdef VERSION_PC
        var_v1 = read_16(0x1F801DAA, __FILE__, __LINE__); // spucnt
        var_v1 &= ~0x80;
        write_16(0x1F801DAA, var_v1, __FILE__, __LINE__); // spucnt
#else
        var_v1 = _spu_RXX->rxx.spucnt;
        var_v1 &= ~0x80;
        _spu_RXX->rxx.spucnt = var_v1;
#endif
        break;

    case 1:
        if ((_spu_rev_reserve_wa != on_off) &&
            _SpuIsInAllocateArea_(_spu_rev_offsetaddr)) {
            _spu_rev_flag = 0;
#ifdef VERSION_PC
            var_v1 = read_16(0x1F801DAA, __FILE__, __LINE__);
            var_v1 &= ~0x80;
            write_16(0x1F801DAA, var_v1, __FILE__, __LINE__);
#else
            var_v1 = _spu_RXX->rxx.spucnt;
            var_v1 &= ~0x80;
            _spu_RXX->rxx.spucnt = var_v1;
#endif
        } else {
            _spu_rev_flag = on_off;
#ifdef VERSION_PC
            var_v1 = read_16(0x1F801DAA, __FILE__, __LINE__);
            var_v1 |= 0x80;
            write_16(0x1F801DAA, var_v1, __FILE__, __LINE__);
#else
            var_v1 = _spu_RXX->rxx.spucnt;
            var_v1 |= 0x80;
            _spu_RXX->rxx.spucnt = var_v1;
#endif
        }
        break;
    }

    return _spu_rev_flag;
}
