// SPDX-License-Identifier: MIT
#include "common.h"

extern s16 rsin_tbl[];

int rsin(int a) {
    if (a < 0) {
        return -sin_1(-a & 0xFFF);
    } else {
        return sin_1(a & 0xFFF);
    }
}

int sin_1(int a) {
    if (a <= 0x800) {
        if (a <= 0x400) {
            return rsin_tbl[a];
        } else {
            return rsin_tbl[0x800 - a];
        }
    } else {
        if (a <= 0xC00) {
            return -rsin_tbl[a - 0x800];
        } else {
            return -rsin_tbl[0x1000 - a];
        }
    }
}
