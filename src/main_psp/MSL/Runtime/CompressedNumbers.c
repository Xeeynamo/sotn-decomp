// SPDX-License-Identifier: AGPL-3.0-or-later

#include "CompressedNumbers.h"

char* __DecodeSignedNumber(char* p, long* pnum) {
    signed long x, y, z, w;

    x = *((signed char*)&p[0]);

    if ((x & 1) == 0) {
        *pnum = x >> 1;
        return p + 1;
    }

    y = p[1];

    if ((x & 2) == 0) {
        *pnum = ((x >> 2) << 8) | y;
        return p + 2;
    }

    z = p[2];

    if ((x & 4) == 0) {
        *pnum = ((x >> 3) << 16) | (y << 8) | z;
        return p + 3;
    }

    w = p[3];

    *pnum = ((x >> 3) << 24) | (y << 16) | (z << 8) | w;
    return p + 4;
}

char* __DecodeUnsignedNumber(char* p, unsigned long* pnum) {
    unsigned long x, y, z, w;

    x = p[0];

    if ((x & 1) == 0) {
        *pnum = x >> 1;
        return p + 1;
    }

    y = p[1];

    if ((x & 2) == 0) {
        *pnum = ((x >> 2) << 8) | y;
        return p + 2;
    }

    z = p[2];

    if ((x & 4) == 0) {
        *pnum = ((x >> 3) << 16) | (y << 8) | z;
        return p + 3;
    }

    w = p[3];

    *pnum = ((x >> 3) << 24) | (y << 16) | (z << 8) | w;
    return p + 4;
}
