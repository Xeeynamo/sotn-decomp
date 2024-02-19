#include "common.h"
#include "libspu_internal.h"

s32 SpuSetAnyVoice(s32 on_off, u32 bits, s32 addr1, s32 addr2) {
    s32 var_t0;
    u16 var_v1;
    u16* temp_a2;
    u16* temp_a3;
    u16 temp;

    temp_a3 = &_spu_RXX->raw[addr2];
    temp_a2 = &_spu_RXX->raw[addr1];
    var_t0 = *temp_a2 | ((_spu_RXX->raw[addr2] & 0xff) << 0x10);
    if (on_off != 0) {
        if (on_off == 1) {
            var_t0 |= bits & 0xFFFFFF;
            *temp_a2 |= bits;
            var_v1 = *temp_a3 | ((bits >> 0x10) & 0xFF);
            *temp_a3 = var_v1;
        }
    } else {
        var_t0 &= ~(bits & 0xFFFFFF);
        *temp_a2 &= ~bits;
        var_v1 = *temp_a3 & ~((bits >> 0x10) & 0xFF);
        *temp_a3 = var_v1;
    }
    return var_t0 & 0xFFFFFF;
}
