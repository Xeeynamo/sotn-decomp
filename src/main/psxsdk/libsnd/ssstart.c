#include "common.h"
#include "libsnd_i.h"

struct Thing {
    u8 unk0;
};
extern struct Thing D_80032F00;

void _SsSeqCalledTbyT_1per2();
void _SsTrapIntrVSync();

void _SsStart(s32 arg0) {
    u16 rcnt_target;
    s32 wait;
    unsigned short var_v0_2;
    u32 rcnt_spec;
    u8 temp_a0;
    void (*callback_func)();
    s32 temp;
    s32 temp2;
    s32 temp3;
    wait = 999;
    do {
        wait -= 1;
    } while (wait >= 0);
    D_80032F00.unk0 = 0;
    D_80032F02 = 6;
    D_80032F01 = 0;
    D_80032EFC = 0;
    rcnt_spec = 0xF2000002;
    switch (_snd_seq_tick_env.unk0) {
    case 0:
        D_80032F02 = 0xFF;
        return;

    case 5:
        D_80032F02 = 0;
        if (arg0 == 0) {
            D_80032F00.unk0 = 1;
        } else {
            rcnt_spec = 0xF2000003;
            rcnt_target = 1;
        }
        break;

    case 3:
        rcnt_target = 0x89D0U;
        break;

    case 2:
        rcnt_target = 0x44E8;
        break;

    default:
        if (_snd_seq_tick_env.unk4 == 0) {
            if (_snd_seq_tick_env.unk0 < 0x46) {
                var_v0_2 = 0x204CC0 / _snd_seq_tick_env.unk0;
                _snd_seq_tick_env.unk17++;
                do {
                } while (0);
            } else {
                var_v0_2 = 0x409980 / _snd_seq_tick_env.unk0;
            }
            rcnt_target = var_v0_2;
        } else {
            return;
        }
        break;
    }

    temp2 = D_80032F00.unk0;
    if (temp2 != 0) {
        EnterCriticalSection();
        VSyncCallback(D_80032EF8);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcnt_spec);
        SetRCnt(rcnt_spec, rcnt_target & 0xFFFF, 0x1000);
        temp_a0 = D_80032F02;
        if (temp_a0 == 0) {
            temp3 = InterruptCallback(0U, 0);
            callback_func = _SsTrapIntrVSync;
            temp_a0 = D_80032F02;
            D_80032EFC = temp3;
        } else {
            callback_func = _SsSeqCalledTbyT_1per2;
            if (D_80032F01 == 0) {
                callback_func = D_80032EF8;
            }
        }
        InterruptCallback(temp_a0, callback_func);
    }
    ExitCriticalSection();
    return;
}

void SsStart(void) { _SsStart(1); }

void SsStart2(void) { _SsStart(0); }

void _SsTrapIntrVSync(void) {
    if (D_80032EFC != NULL) {
        D_80032EFC();
    }
    D_80032EF8();
}

void _SsSeqCalledTbyT_1per2(void) {
    if (D_80032F04 == 0) {
        D_80032F04 = 1;
        return;
    }
    D_80032F04 = 0;
    D_80032EF8();
}
