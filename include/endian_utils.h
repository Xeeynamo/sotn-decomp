// SPDX-License-Identifier: AGPL-3.0-or-later
#ifndef SOTN_ENDIAN_UTILS_H
#define SOTN_ENDIAN_UTILS_H

#include "types.h"

static inline u8 SotnNumericLowU8(u32 value) { return (u8)value; }

static inline u16 SotnNumericLowU16(u32 value) { return (u16)value; }

static inline s16 SotnNumericLowS16(s32 value) { return (s16)(u16)value; }

static inline u16 SotnNumericHighU16(u32 value) { return (u16)(value >> 16); }

static inline s16 SotnNumericHighS16(s32 value) {
    return (s16)(u16)((u32)value >> 16);
}

static inline s16 SotnFixedInteger(s32 value) {
    return SotnNumericHighS16(value);
}

#endif
