// SPDX-License-Identifier: MIT
#include "libsnd_i.h"

void SsSetTickMode(long tick_mode) {
    s32 videoMode;

    videoMode = GetVideoMode();
    if (tick_mode & 0x1000) {
        _snd_seq_tick_env.unk4 = 1;
        _snd_seq_tick_env.unk0 = tick_mode & 0xFFF;
    } else {
        _snd_seq_tick_env.unk4 = 0;
        _snd_seq_tick_env.unk0 = tick_mode;
    }
    if (_snd_seq_tick_env.unk0 < 6) {
        switch (_snd_seq_tick_env.unk0) {
        case 4:
            VBLANK_MINUS = 50;
            if (videoMode != 1) {
                _snd_seq_tick_env.unk0 = 50;
            } else {
                _snd_seq_tick_env.unk0 = 5;
            }
            return;
        case 1:
            VBLANK_MINUS = 60;
            if (videoMode == 0) {
                _snd_seq_tick_env.unk0 = 5;
            } else {
                _snd_seq_tick_env.unk0 = 60;
            }
            return;
        case 3:
            VBLANK_MINUS = 120;
            return;
        case 2:
            VBLANK_MINUS = 240;
            return;
        case 5:
            switch (videoMode) {
            case 1:
                VBLANK_MINUS = 50;
                return;
            default:
            case 0:
                VBLANK_MINUS = 60;
                return;
            }
            break;
        case 0:
            if (videoMode != 0) {
                if (videoMode == 1) {
                    VBLANK_MINUS = 50;
                    return;
                }
            }
            VBLANK_MINUS = 60;
            return;
        default:
            VBLANK_MINUS = 60;
            return;
        }
    } else {
        VBLANK_MINUS = _snd_seq_tick_env.unk0;
    }
}
