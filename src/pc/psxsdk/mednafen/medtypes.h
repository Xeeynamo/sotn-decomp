#pragma once

#include <inttypes.h>

using uint16 = uint16_t;
using int16 = int16_t;
using uint32 = uint32_t;
using int32 = int32_t;
using uint8 = uint8_t;
using int8 = int8_t;
using int64 = int64_t;
using uint64 = uint64_t;

#define MDFN_FASTCALL
#define NO_INLINE
#define INLINE
#define MDFN_HIDE
#define NULL 0
#define MDFN_LIKELY(x) x
#define MDFN_UNLIKELY(x) x
#define MDFN_COLD

#define sign_x_to_s32(n, v) ((int32)((uint32)(v) << (32 - (n))) >> (32 - (n)))

#include "git.h"
