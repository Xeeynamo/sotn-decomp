#include "common.h"
#include "libspu_internal.h"

struct SpuRevAttr {
    s32 unk0;
    s32 unk18;
    s16 unk1c;
    s16 unk1e;
    s32 unk20;
    s32 unk24;
};

extern s32 _spu_fd;
extern s32 _spu_trans_mode;
extern s32 _spu_rev_flag;
extern s32 _spu_rev_reserve_wa;
extern s32 _spu_rev_offsetaddr;
extern struct SpuRevAttr _spu_rev_attr;
extern u16 _spu_voice_centerNote[];
extern s32 _spu_EVdma;
extern s32 _spu_keystat;
extern s32 _spu_rev_startaddr[];

void SpuStart(void);

void _SpuInit(s32 arg0) {
    s32 i;
    ResetCallback();
    _spu_init(arg0);
    if (arg0 == 0) {
        for (i = 0; i < 0x18; i++) {
            _spu_voice_centerNote[i] = 0xC000;
        }
    }
    SpuStart();
    _spu_rev_flag = 0;
    _spu_rev_reserve_wa = 0;
    _spu_rev_attr.unk18 = 0;
    _spu_rev_attr.unk1c = 0;
    _spu_rev_attr.unk1e = 0;
    _spu_rev_attr.unk20 = 0;
    _spu_rev_attr.unk24 = 0;
    _spu_rev_offsetaddr = _spu_rev_startaddr[0];
    _spu_FsetRXX(0xD1, _spu_rev_startaddr[0], 0);
    _spu_trans_mode = 0;
    _spu_transMode = 0;
    _spu_keystat = 0;
}

void SpuStart(void) {
    s32 temp_v0;

    if (_spu_isCalled == 0) {
        _spu_isCalled = 1;
        EnterCriticalSection();
        D_80033098 = 0;
        _SpuDataCallback(_spu_FiDMA);
        temp_v0 = OpenEvent(0xF0000009U, 0x20, 0x2000, NULL);
        _spu_EVdma = temp_v0;
        EnableEvent(temp_v0);
        ExitCriticalSection();
    }
}
