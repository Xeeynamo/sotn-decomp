#include "common.h"

s32 GetVideoMode();
extern s32 D_80032EF4;
extern s32 VBLANK_MINUS;
extern s32 snd_seq_tick_env;

void SsSetTickMode(s32 tick_mode) {
    s32 videoMode;
    s32 var_v0;

    videoMode = GetVideoMode();
    if (tick_mode & 0x1000) {
        D_80032EF4 = 1;
        snd_seq_tick_env = tick_mode & 0xFFF;
    } else {
        D_80032EF4 = 0;
        snd_seq_tick_env = tick_mode;
    }
    if (snd_seq_tick_env < 6) {
        switch (snd_seq_tick_env) {
        case 4:
            VBLANK_MINUS = 0x32;
            if (videoMode != 1) {
                snd_seq_tick_env = 0x32;
                return;
            }
            snd_seq_tick_env = 5;
            return;
        case 1:
            var_v0 = 0x3C;
            VBLANK_MINUS = 0x3C;
            if (videoMode == 0) {
                var_v0 = 5;
            }
            snd_seq_tick_env = var_v0;
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
        VBLANK_MINUS = snd_seq_tick_env;
    }
}
