#include "common.h"
#include "registers.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", StCdInterrupt);

void mem2mem(s32* dst, s32* src, u32 num) {
    u32 i;
    for (i = 0; i < num; i++) {
        *dst++ = *src++;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", dma_execute);
