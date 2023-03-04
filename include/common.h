#ifndef COMMON_H
#define COMMON_H

#include "include_asm.h"
#include "macros.h"
#include "types.h"

#define LOH(x) (*(s16*)&(x))

int sprintf(char* dst, const char* fmt, ...);

#endif
