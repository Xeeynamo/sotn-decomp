// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

inline s32 SpuRGetAllKeysStatus(s32 min, s32 max, s8* status) {
    s32 last_voice;
    s32 voice;
    u16 volumex;

    if (min < 0) {
        min = 0;
    }
    if (min >= NUM_SPU_CHANNELS) {
        return -3;
    }
    if (max >= NUM_SPU_CHANNELS) {
        max = NUM_SPU_CHANNELS - 1;
    }
    if ((max < 0) || (max < min)) {
        return -3;
    }
    last_voice = max + 1;

    for (voice = min; voice < last_voice; voice++) {
        volumex = _spu_RXX->raw[(8 * voice) + 6];;
        if ((1 << voice) & _spu_keystat) {
            if (volumex != 0) {
                status[voice] = 1;
            } else {
                status[voice] = 3;
            }
        } else {
            if (volumex != 0) {
                status[voice] = 2;
            } else {
                status[voice] = 0;
            }
        }
    }

    return 0;
}

void SpuGetAllKeysStatus(s8* status) {
    SpuRGetAllKeysStatus(0, NUM_SPU_CHANNELS, status);
}
