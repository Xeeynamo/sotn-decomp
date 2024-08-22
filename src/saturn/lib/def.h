// SPDX-License-Identifier: AGPL-3.0-only

#ifndef DEF_H
#define DEF_H

#include "xpt.h"

#define RGB16_COLOR(r, g, b) (Rgb16)(((b) << 10) + ((g) << 5) + (r) + 0x8000)

#define RGB32_COLOR(r, g, b)                                                   \
    (Rgb32)(((b) << 16) + ((g) << 8) + (r) + 0x80000000)

typedef Uint16 Rgb16;
typedef Uint32 Rgb32;

typedef struct XyInt {
    Sint16 x;
    Sint16 y;
} XyInt;

#endif
