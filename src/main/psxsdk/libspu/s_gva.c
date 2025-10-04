// SPDX-License-Identifier: MIT
#include "common.h"
#include "libspu_internal.h"

static inline void SpuNGetVoiceAttr(s32 vNum, SpuVoiceAttr* arg) {
    s16 var_a0;
    s16 var_a1;
    s32 temp_s2;
    s32 note;
    u16 adsr0;
    u16 adsr1;
    u16 voll;
    u16 volr;
    s32 temp_t0;

    var_a1 = 0;

    voll = _spu_RXX->raw[vNum * 8 + 0];
    volr = _spu_RXX->raw[vNum * 8 + 1];
    temp_s2 = vNum * 8;
    temp_t0 = vNum * 2;

    if (voll & 0x8000) {
        switch (voll & 0xF000) {
        case 0x8000:
            var_a1 = 1;
            break;
        case 0x9000:
            var_a1 = 2;
            break;
        case 0xA000:
            var_a1 = 3;
            break;
        case 0xB000:
            var_a1 = 4;
            break;
        case 0xC000:
            var_a1 = 5;
            break;
        case 0xD000:
            var_a1 = 6;
            break;
        case 0xE000:
            var_a1 = 7;
            break;
        case 0xF000:
            var_a1 = 7;
            break;
        }
        voll &= 0xFFF;
    }

    var_a0 = 0;
    if (volr & 0x8000) {
        switch (volr & 0xF000) {
        case 0x8000:
            var_a0 = 1;
            break;
        case 0x9000:
            var_a0 = 2;
            break;
        case 0xA000:
            var_a0 = 3;
            break;
        case 0xB000:
            var_a0 = 4;
            break;
        case 0xC000:
            var_a0 = 5;
            break;
        case 0xD000:
            var_a0 = 6;
            break;
        case 0xE000:
            var_a0 = 7;
            break;
        case 0xF000:
            var_a0 = 7;
            break;
        }
        volr &= 0xFFF;
    }

    {
        u32 x = 0x8000;
        u32 y = voll;
        arg->volume.left = (voll < 0x4000) ? voll : (y - x);
    }
    {
        u32 x = 0x8000;
        u32 y = volr;
        arg->volume.right = (volr < 0x4000) ? volr : (y - x);
    }

    arg->volmode.right = var_a0;
    arg->volmode.left = var_a1;

    arg->volumex.left = _spu_RXX->raw[temp_t0 + 0x100];
    arg->volumex.right = _spu_RXX->raw[temp_t0 + 0x101];

    arg->pitch = _spu_RXX->raw[temp_s2 + 2];

    note = _spu_pitch2note(_spu_voice_centerNote[vNum] >> 8,
                           _spu_voice_centerNote[vNum] & 0xFF, arg->pitch);

    if (note >= 0) {
        arg->note = note;
    } else {
        arg->note = 0;
    }

    arg->sample_note = _spu_voice_centerNote[vNum];
    arg->envx = _spu_RXX->raw[temp_s2 + 6];
    arg->addr = _spu_RXX->raw[temp_s2 + 3] << _spu_mem_mode_plus;
    arg->loop_addr = _spu_RXX->raw[temp_s2 + 7] << _spu_mem_mode_plus;
    adsr0 = _spu_RXX->raw[temp_s2 + 4];
    adsr1 = _spu_RXX->raw[temp_s2 + 5];

    if (adsr0 & 0x80) {
        arg->a_mode = 5;
    } else {
        arg->a_mode = 1;
    }

    if (adsr1 & 0x300) {
        arg->s_mode = 7;
    } else if (adsr1 & 0x200) {
        arg->s_mode = 5;
    } else if (adsr1 & 0x100) {
        arg->s_mode = 3;
    } else {
        arg->s_mode = 1;
    }

    if (adsr1 & 0x20) {
        arg->r_mode = 7;
    } else {
        arg->r_mode = 3;
    }

    arg->ar = adsr0 >> 8;
    arg->dr = (adsr0 & 0xF0) >> 4;
    arg->sr = (adsr1 >> 6) & ~0x300;
    arg->rr = adsr1 & 0x1F;
    arg->sl = adsr0 & 0xF;
    arg->adsr1 = adsr0;
    arg->adsr2 = adsr1;
}

void SpuGetVoiceAttr(SpuVoiceAttr* arg) {
    s32 voice;
    s32 i;

    voice = -1;
    for (i = 0; i < NUM_SPU_CHANNELS; i++) {
        if (arg->voice & (1 << i)) {
            voice = i;
            break;
        }
    }

    if (voice != -1) {
        SpuNGetVoiceAttr(voice, arg);
    }
}
