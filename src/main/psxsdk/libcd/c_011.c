#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", StCdInterrupt);

void mem2mem(s32* arg0, s32* arg1, u32 arg2) {
    s32 temp_v0;
    s32* var_a0;
    s32* var_a1;
    u32 var_v1;

    var_a0 = arg0;
    var_a1 = arg1;

    for (var_v1 = 0; var_v1 < arg2; var_v1++) {
        temp_v0 = *var_a1++;
        *var_a0++ = temp_v0;
    }
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libcd/c_011", dma_execute);
