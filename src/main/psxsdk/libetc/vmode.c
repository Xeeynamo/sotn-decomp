// SPDX-License-Identifier: MIT
#include "common.h"
#include <libetc.h>

static long video_mode = 0;

long SetVideoMode(long mode) {
    long prev;

    prev = video_mode;
    video_mode = mode;
    return prev;
}

long GetVideoMode() { return video_mode; }
