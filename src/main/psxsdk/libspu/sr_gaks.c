#include "common.h"
#include "libspu_internal.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libspu/sr_gaks", SpuRGetAllKeysStatus);

extern s32 _spu_keystat;

void SpuGetAllKeysStatus(char* status) {
    s32 voice;
    u16* new_var;
    u16 volumex;
    s32 max;
    max = 24;
    for (voice = 0; voice < max; voice++) {
        new_var = &_spu_RXX->rxx.voice[voice].volumex;
        volumex = *new_var;
        if ((1 << voice) & _spu_keystat) {
            if (volumex != 0) {
                status[voice] = 1;
            } else {
                status[voice] = 3;
            }
        } else if (volumex != 0) {
            status[voice] = 2;
        } else {
            status[voice] = 0;
        }
    }
}
