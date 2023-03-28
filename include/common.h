#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "macros.h"
#include "types.h"

#define LEN(x) ((s32)(sizeof(x) / sizeof(*(x))))
#define LENU(x) ((u32)(sizeof(x) / sizeof(*(x))))
#define STRCPY(dst, src) __builtin_memcpy(dst, src, sizeof(src))

#define LOH(x) (*(s16*)&(x))
#define LOB(x) (*(s8*)&(x))
#define LOBU(x) (*(u8*)&(x))
#if defined(HACKS) && !defined(PERMUTER)
// The following hacks are required to get a matching decompilation. If removed
// they will still logically match the original function.
#define ALIGNED4 __attribute__((aligned(4)))
#define NOP asm volatile("nop")
#else
#define ALIGNED4
#define NOP
#endif

int sprintf(char* dst, const char* fmt, ...);

#endif
