#include "common.h"

extern s16 rsin_tbl[];

int rcos(int a) {
    if (a < 0) {
        a = -a;
    }
    a &= 0xFFF;

    if (a < 0x801) {
        if (a < 0x401) {
            return rsin_tbl[0x400 - a];
        }
        return -rsin_tbl[a - 0x400];
    } else {
        if (a < 0xC01) {
            return -rsin_tbl[0xC00 - a];
        }
        return rsin_tbl[a - 0xC00];
    }
}
