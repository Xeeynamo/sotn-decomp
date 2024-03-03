#include "common.h"

s32 rsin(s32 arg0) {
    if (arg0 < 0) {
        return -sin_1(-arg0 & 0xFFF);
    }
    return sin_1(arg0 & 0xFFF);
}

extern s16 rsin_tbl[];
s32 sin_1(s32 arg0) {
    if (arg0 < 0x801) {
        if (arg0 < 0x401) {
            return rsin_tbl[arg0];
        } else {
            return rsin_tbl[0x800 - arg0];
        }
    } else {
        if (arg0 < 0xC01) {
            return -1 * rsin_tbl[arg0 - 0x800];
        } else {
            return -1 * rsin_tbl[0x1000 - arg0];
        }
    }
}
