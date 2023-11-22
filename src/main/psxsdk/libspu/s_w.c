#include "common.h"

void _spu_write(u32, u32);
extern s32 _spu_inTransfer;
extern s32 _spu_transferCallback;

unsigned long SpuWrite(unsigned char* addr, unsigned long size) {
    u32 var_s0;

    var_s0 = size;
    if (var_s0 > 0x7F000U) {
        var_s0 = 0x7F000;
    }
    _spu_write(addr, var_s0);
    if (_spu_transferCallback == 0) {
        _spu_inTransfer = 0;
    }
    return var_s0;
}
