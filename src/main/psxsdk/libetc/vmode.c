#include "common.h"
#include <libetc.h>

static long videoMode = 0;

long SetVideoMode(long mode) {
    long prev;

    prev = videoMode;
    videoMode = mode;
    return prev;
}

long GetVideoMode() { return videoMode; }
