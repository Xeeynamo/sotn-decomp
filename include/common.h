#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "macros.h"
#include "types.h"

#define LOH(x) (*(s16*)&(x))
#ifdef HACKS
#define ALIGNED4 __attribute__((aligned(4)))
#define NOP asm volatile("nop")
#else
#define ALIGNED4
#define NOP
#endif

int sprintf(char* dst, const char* fmt, ...);

#endif
