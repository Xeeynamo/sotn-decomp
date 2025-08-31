// SPDX-License-Identifier: MIT
#include "common.h"
#include "libsnd_i.h"

struct SndSeqTickEnv _snd_seq_tick_env = {
    .unk0 = 60,
    .unk4 = 1,
    .unk8 = SsSeqCalledTbyT,
    .unk12 = NULL,
    .unk16 = 0,
    .unk17 = 0,
    .unk18 = -1,
    .unk19 = 0,
    .unk20 = 0,
};

static inline void _SsTrapIntrVSync(void) {
    if (_snd_seq_tick_env.unk12 != NULL) {
        _snd_seq_tick_env.unk12();
    }
    _snd_seq_tick_env.unk8();
}

static inline s32 get20() { return _snd_seq_tick_env.unk20; }

static inline void _SsSeqCalledTbyT_1per2(void) {
    if (get20() == 0) {
        _snd_seq_tick_env.unk20 = 1;
    } else {
        _snd_seq_tick_env.unk20 = 0;
        _snd_seq_tick_env.unk8();
    }
}

static void _SsStart(s32 arg0) {
    u16 rcnt_target;
    u32 rcnt_spec;

    s32 wait = 1000;
    while (--wait >= 0) {
    }

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
        rcnt_target = 0x89D0;
        break;

    case 2:
        rcnt_target = 0x44E8;
        break;

    default:
        if (_snd_seq_tick_env.unk4 == 0) {
            if (_snd_seq_tick_env.unk0 < 0x46) {
                rcnt_target = 0x204CC0 / _snd_seq_tick_env.unk0;
                _snd_seq_tick_env.unk17++;
            } else {
                rcnt_target = 0x409980 / _snd_seq_tick_env.unk0;
            }
        } else {
            return;
        }
        break;
    }

    if (_snd_seq_tick_env.unk16 != 0) {
        EnterCriticalSection();
        VSyncCallback(_snd_seq_tick_env.unk8);
    } else {
        EnterCriticalSection();
        ResetRCnt(rcnt_spec);
        SetRCnt(rcnt_spec, rcnt_target, 0x1000);
        if (_snd_seq_tick_env.unk18 == 0) {
            _snd_seq_tick_env.unk12 =
                InterruptCallback(_snd_seq_tick_env.unk18, NULL);
            InterruptCallback(_snd_seq_tick_env.unk18, _SsTrapIntrVSync);
        } else if (_snd_seq_tick_env.unk17 == 0) {
            InterruptCallback(_snd_seq_tick_env.unk18, _snd_seq_tick_env.unk8);
        } else {
            InterruptCallback(_snd_seq_tick_env.unk18, _SsSeqCalledTbyT_1per2);
        }
    }
    ExitCriticalSection();
}

void SsStart(void) { _SsStart(1); }

void SsStart2(void) { _SsStart(0); }
