#include "common.h"
#include <libetc.h>

static int PadIdentifier;
static int pad_buf = 0;

void PadInit(int mode) {
    PadIdentifier = mode;
    pad_buf = -1;
    ResetCallback();
    PAD_init(0x20000001, &pad_buf);
    ChangeClearPAD(0);
}

u_long PadRead(int id) {
    PAD_dr();
    return ~pad_buf;
}

void PadStop(void) { StopPAD(); }
