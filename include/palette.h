#ifndef PALETTE_H
#define PALETTE_H

#include "common.h"

#define COLORS_PER_PAL (16)
#define COLOR_BPP (16)
#define COLOR_LEN ((COLOR_BPP) / 8)
#define PALETTE_LEN ((COLORS_PER_PAL) * ((COLOR_BPP) / 8))
#define COLOR16(r, g, b, a) (r) + ((g) << 5) + ((b) << 10) + ((a) << 15)

#define PAL_OVL_FLAG 0x8000
#define PAL_DRA(x) (x)
#define PAL_OVL(x) ((x) | PAL_OVL_FLAG)

#define MAKE_PAL_OP(kind, freq) ((kind) | ((freq) << 0x10))
#define GET_PAL_OP_KIND(x) (LOH(x))
#define GET_PAL_OP_FREQ(x) (HIH(x))

#define PAL_COPY 1
#define PAL_COPY_INFO() MAKE_PAL_OP(PAL_COPY, 0)
#define PAL_COPY_DATA(dst, data) (dst), (u_long*)LEN(data), (u_long*)(data)
#define PAL_COPY_DATA_(dst, data, len) (dst), (u_long*)(len), (u_long*)(data)

#define PAL_UNK_OP2 2
#define PAL_UNK_OP2_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP2_DATA(data) (u_long*)(data)

#define PAL_UNK_OP3 3
#define PAL_UNK_OP3_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_UNK_OP3_DATA(data) (u_long*)(data)

#define PAL_GLOW_ANIM 4
#define PAL_GLOW_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_GLOW_DATA(data) (u_long*)(data)

#define PAL_BULK_COPY 5
#define PAL_BULK_COPY_INFO(dst, n) (u_long*)(dst), (u_long*)(n)
#define PAL_BULK(dst, data) (u_long*)(dst), (u_long*)LEN(data), (u_long*)(data)

#define PAL_TERMINATE() ((u_long*)-1)

#endif // PALETTE_H
