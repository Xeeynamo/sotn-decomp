#include "common.h"
#include "libsnd_i.h"

static void _SsSeqCalledTbyT_1per2();
static void _SsTrapIntrVSync();

static void _SsStart(s32 arg0) {
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
    _snd_seq_tick_env.unk16 = 0;
    _snd_seq_tick_env.unk18 = 6;
    _snd_seq_tick_env.unk17 = 0;
    _snd_seq_tick_env.unk12 = 0;
    rcnt_spec = 0xF2000002;
    switch (_snd_seq_tick_env.unk0) {
    case 0:
        _snd_seq_tick_env.unk18 = 0xFF;
        return;

    case 5:
        _snd_seq_tick_env.unk18 = 0;
        if (arg0 == 0) {
            _snd_seq_tick_env.unk16 = 1;
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
            } else {
                var_v0_2 = 0x409980 / _snd_seq_tick_env.unk0;
            }
            rcnt_target = var_v0_2;
        } else {
            return;
        }
        break;
    }

    temp2 = _snd_seq_tick_env.unk16;
    if (temp2 != 0) {
        EnterCriticalSection();
        VSyncCallback(_snd_seq_tick_env.unk8);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcnt_spec);
        SetRCnt(rcnt_spec, rcnt_target & 0xFFFF, 0x1000);
        temp_a0 = _snd_seq_tick_env.unk18;
        if (temp_a0 == 0) {
            temp3 = InterruptCallback(0U, 0);
            callback_func = _SsTrapIntrVSync;
            temp_a0 = _snd_seq_tick_env.unk18;
            _snd_seq_tick_env.unk12 = temp3;
        } else {
            callback_func = _SsSeqCalledTbyT_1per2;
            if (_snd_seq_tick_env.unk17 == 0) {
                callback_func = _snd_seq_tick_env.unk8;
            }
        }
        InterruptCallback(temp_a0, callback_func);
    }
    ExitCriticalSection();
}

void SsStart(void) { _SsStart(1); }

void SsStart2(void) { _SsStart(0); }

static void _SsTrapIntrVSync(void) {
    if (_snd_seq_tick_env.unk12 != NULL) {
        _snd_seq_tick_env.unk12();
    }
    _snd_seq_tick_env.unk8();
}

static inline s32 get20() { return _snd_seq_tick_env.unk20; }

static void _SsSeqCalledTbyT_1per2(void) {
    if (get20() == 0) {
        _snd_seq_tick_env.unk20 = 1;
        return;
    }
    _snd_seq_tick_env.unk20 = 0;
    _snd_seq_tick_env.unk8();
}
