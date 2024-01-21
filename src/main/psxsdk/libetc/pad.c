#include "common.h"
#include <libetc.h>

extern int PadIdentifier;
extern int pad_buf;

void PadInit(int mode) {
    PadIdentifier = mode;
    pad_buf = -1;
    ResetCallback();
    PAD_init(0x20000001, &pad_buf);
    ChangeClearPAD(0);
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/pad", PadRead);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/pad", PadStop);
