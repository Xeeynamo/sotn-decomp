#include "common.h"
#include "libsnd_i.h"

typedef void (*SndSsMarkCallbackProc)(short seq_no, short sep_no, short data);
extern SndSsMarkCallbackProc _SsMarkCallback[32][16];
extern short D_80032EC0[];
extern u16 D_80032ED0[];

void _SsInit(void) {
    u16* var_a2;
    int i, j;

    var_a2 = (u16*)0x1F801C00;
    for (i = 0; i < 24; i++) {
        for (j = 0; j < 8; j++) {
#ifdef VERSION_PC
            write_16(0x1F801C00 + (i * 8 + j) * 2, D_80032EC0[j], __FILE__,
                     __LINE__);
#else
            *var_a2++ = D_80032EC0[j];
#endif
        }
    }

    var_a2 = (u16*)0x1F801D80;
    for (i = 0; i < 16; i++) {
#ifdef VERSION_PC
        write_16(0x1F801D80 + i * 2, D_80032ED0[i], __FILE__, __LINE__);
#else
        *var_a2++ = D_80032ED0[i];
#endif
    }

    SpuVmInit(24);

    for (j = 0; j < 32; j++) {
        for (i = 0; i < 16; i++) {
            _SsMarkCallback[j][i] = 0;
        }
    }

    VBLANK_MINUS = 0x3C;
    _snd_openflag = 0;
    _snd_ev_flag = 0;
}
