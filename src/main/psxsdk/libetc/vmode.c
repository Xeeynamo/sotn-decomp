#include "common.h"
#include <libetc.h>

extern long D_8002D3A4;

long SetVideoMode(long mode) {
    long prev;

    prev = D_8002D3A4;
    D_8002D3A4 = mode;
    return prev;
}

long GetVideoMode(void) { return D_8002D3A4; }
