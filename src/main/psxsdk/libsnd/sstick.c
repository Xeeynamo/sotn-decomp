#include "libsnd_i.h"

void SsSetTickMode(long tick_mode) {
    s32 videoMode;
    s32 var_v0;

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
            VBLANK_MINUS = 0x32;
            if (videoMode != 1) {
                _snd_seq_tick_env.unk0 = 0x32;
                return;
            }
            _snd_seq_tick_env.unk0 = 5;
            return;
        case 1:
            var_v0 = 0x3C;
            VBLANK_MINUS = 0x3C;
            if (videoMode == 0) {
                var_v0 = 5;
            }
            _snd_seq_tick_env.unk0 = var_v0;
            return;
        case 3:
            VBLANK_MINUS = 0x78;
            return;
        case 2:
            VBLANK_MINUS = 0xF0;
            return;
        case 5:
            switch (videoMode) {
            case 1:
                VBLANK_MINUS = 0x32;
                return;
            default:
            case 0:
                VBLANK_MINUS = 0x3C;
                return;
            }
            break;
        case 0:
            if (videoMode != 0) {
                if (videoMode == 1) {
                    VBLANK_MINUS = 0x32;
                    return;
                }
            }
            VBLANK_MINUS = 0x3C;
            return;
        default:
            VBLANK_MINUS = 0x3C;
            return;
        }
    } else {
        VBLANK_MINUS = _snd_seq_tick_env.unk0;
    }
}
