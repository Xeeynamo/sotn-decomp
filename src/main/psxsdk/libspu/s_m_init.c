#include "common.h"

extern s32 D_8003355C;
extern s32 D_80033560;
extern s8* D_80033564;
extern s32 _spu_mem_mode_plus;

typedef struct tagSpuMalloc {
    u32 addr;
    u32 size;
} SPU_MALLOC;

s32 SpuInitMalloc(s32 num, s8* top) {
    SPU_MALLOC* temp = top;
    if (num > 0) {
        temp->addr = 0x40001010;
        D_80033564 = temp;
        D_80033560 = 0;
        D_8003355C = num;
        temp->size = (s32)((0x10000 << _spu_mem_mode_plus) - 0x1010);
        return num;
    }
    return 0;
}
