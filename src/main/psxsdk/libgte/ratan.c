#include "common.h"

extern const s16 g_AtanTable[0x400];

long ratan2(long dx, long dy) {
    long ret;
    bool flag0;
    bool flag1;
    s32 lookup;

    flag0 = false;
    flag1 = false;
    if (dy < 0) {
        flag0 = true;
        dy = -dy;
    }
    if (dx < 0) {
        flag1 = true;
        dx = -dx;
    }
    if ((dy == 0) && (dx == 0)) {
        return 0;
    }
    if (dx < dy) {
        if (dx & 0x7FE00000) {
            lookup = (dx / (dy >> 10));
        } else {
            lookup = ((dx << 10) / dy);
        }
        ret = g_AtanTable[lookup];
    } else {
        if (dy & 0x7FE00000) {
            lookup = (dy / (dx >> 10));
        } else {
            lookup = ((dy << 10) / dx);
        }
        ret = 0x400 - g_AtanTable[lookup];
    }
    if (flag0)
        ret = 0x800 - ret;
    if (flag1)
        ret = -ret;
    return ret;
}
