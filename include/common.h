#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "macros.h"
#include "settings.h"
#include "types.h"

#if defined(_internal_version_us)
#define VERSION_US
#define VERSION "us"
#elif defined(_internal_version_hd)
#define VERSION_HD
#define VERSION "hd"
#elif defined(_internal_version_pspeu)
#define VERSION_PSP
#define VERSION "psp"
#elif defined(_internal_version_beta)
#define VERSION_BETA
#define VERSION "beta"
#else
#warning "Version not specified. Falling back to the US version."
#define VERSION_US
#define VERSION "us"
#endif

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))
#define LENU(x) ((u32)(sizeof(x) / sizeof(*(x))))
#define OFF(type, field) ((size_t)(&((type*)0)->field))
#define STRCPY(dst, src) __builtin_memcpy(dst, src, sizeof(src))

#ifdef _MSC_VER
#define __builtin_memcpy memcpy
#endif

#define LOH(x) (*(s16*)&(x))
#define HIH(x) (((s16*)&(x))[1])
#define LOHU(x) (*(u16*)&(x))
#define LOW(x) (*(s32*)&(x))
#define LOWU(x) (*(u32*)&(x))

#if defined(HACKS) && !defined(PERMUTER)
#define ALIGNED4 __attribute__((aligned(4)))
#else
#define ALIGNED4
#endif

#ifndef __clang__
int sprintf(char* dst, const char* fmt, ...);
#endif

#define FIX(x) ((s32)((x) * 65536.0))
#define FIX_TO_I(x) ((s32)((x) >> 16))

// The second argument to CreateEntFactoryFromEntity has weird bit packing,
// this takes the 2 relevant inputs and packs them up.
// A0 should be a value like 0x##00 where ## is two hexadecimal digits.
// BLUEPRINTNUM is which blueprint gets loaded from g_FactoryBlueprints.
#define FACTORY(A0, BLUEPRINTNUM) (A0 << 8 | BLUEPRINTNUM)
// Tests multiple bits of x being set, based on the bitmask defined in y.
#define TEST_BITS(x, y) ((x & y) == y)

// PSX SDK libraries do not use float. Instead they use a fix-point number
// where 4096 is equal to 1.0.
#define FLT(x) ((s32)((x) * 4096.0))

#endif
