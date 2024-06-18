#include "np3.h"

u16 func_801C4144(s16 arg0, s16 arg1, s16 arg2, s16* arg3) {
    s16 temp;
    s16* ptr;

    ptr = &D_80181230[arg0 * 8];
    arg1 -= *ptr++;
    if (arg1 < 0) {
        return 0;
    }
    *arg3++ = arg1;

    temp = *ptr++ - arg1;
    if (temp <= 0) {
        return 0;
    }
    *arg3++ = temp;

    temp = D_80182168[*ptr++];
    if (temp) {
        temp = arg1 / temp;
    } else {
        temp = 0;
    }

    temp = *ptr++ - temp;
    if ((temp <= arg2) && (arg2 < *ptr++)) {
        return (arg2 - 0x8000) - temp;
    }
    return 0;
}

// ID 0x2C
INCLUDE_ASM("st/np3/nonmatchings/44144", func_801C424C);
