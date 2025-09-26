// SPDX-License-Identifier: MIT
#include "common.h"

extern s16 rsin_tbl[];

int rcos(int a) {
    if (a < 0) {
        a = -a;
    }
    a &= 0xFFF;

    if (a <= 0x800) {
        if (a <= 0x400) {
            return rsin_tbl[0x400 - a];
        } else {
            return -rsin_tbl[a - 0x400];
        }
    } else {
        if (a <= 0xC00) {
            return -rsin_tbl[0xC00 - a];
        } else {
            return rsin_tbl[a - 0xC00];
        }
    }
}
