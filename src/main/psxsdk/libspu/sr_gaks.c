#include "common.h"
#include "libspu_internal.h"

extern s32 _spu_keystat;

s32 SpuRGetAllKeysStatus(s32 min, s32 max, s8* status) {
    s32 last_voice;
    s32 var_a1;
    s32 voice;
    s32 var_v0;
    s8* var_a2;
    u16 volume;
    if (min < 0) {
        min = 0;
    }
    if (min < NUM_SPU_CHANNELS) {
        if (max >= NUM_SPU_CHANNELS) {
            max = NUM_SPU_CHANNELS - 1;
        }
    } else {
        return -3;
    }
    if ((max < 0) || (max < min)) {
        return -3;
    }
    voice = min;
    last_voice = max + 1;

    for (voice = min; voice < last_voice; voice++) {
        volume = _spu_RXX->raw[(8 * voice) + 6];
        if ((1 << voice) & _spu_keystat) {
            if (volume != 0) {
                status[voice] = 1;
            } else {
                status[voice] = 3;
            }
        } else if (volume != 0) {
            status[voice] = 2;
        } else {
            status[voice] = 0;
        }
    }

    return 0;
}

void SpuGetAllKeysStatus(s8* status) {
    s32 voice;
    u16* new_var;
    u16 volumex;
    s32 max;
    max = NUM_SPU_CHANNELS;
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
