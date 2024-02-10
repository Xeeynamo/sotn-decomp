#include "common.h"
#include "libspu_internal.h"

extern s32 _spu_keystat;

void SpuSetKey(long on_off, unsigned long voice_bit) {
    u32 temp_a1;
    unsigned short new_var;
    u32 temp_a3;
    temp_a1 = voice_bit & 0xFFFFFF;
    temp_a3 = temp_a1 >> 0x10;
    new_var = temp_a1;
    if (on_off != 0) {
        if (on_off != 1) {
            return;
        }
        _spu_RXX->rxx.key_on[0] = new_var;
        _spu_RXX->rxx.key_on[1] = temp_a3;
        _spu_keystat = temp_a1 | _spu_keystat;
    } else {
        _spu_RXX->rxx.key_off[0] = temp_a1;
        _spu_RXX->rxx.key_off[1] = temp_a3;
        _spu_keystat = (~temp_a1) & _spu_keystat;
    }
}
