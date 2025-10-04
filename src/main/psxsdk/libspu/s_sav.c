// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

s32 SpuSetAnyVoice(s32 on_off, u32 bits, s32 addr1, s32 addr2) {
    s32 var_t0;

    var_t0 = ((_spu_RXX->raw[addr2] & 0xFF) << 0x10) | _spu_RXX->raw[addr1];
    switch (on_off) {
    case 1:
        var_t0 |= bits & 0xFFFFFF;
        _spu_RXX->raw[addr1] |= bits;
        _spu_RXX->raw[addr2] |= ((bits >> 0x10) & 0xFF);
        break;

    case 0:
        var_t0 &= ~(bits & 0xFFFFFF);
        _spu_RXX->raw[addr1] &= ~bits;
        _spu_RXX->raw[addr2] &= ~((bits >> 0x10) & 0xFF);
        break;
    }
    return var_t0 & 0xFFFFFF;
}
