#define INCLUDE_ASM_NEW
#include "common.h"

s16 _spu_FsetRXXa(s32, s32);
extern s16 _spu_tsa;

s32 SpuSetTransferStartAddr(s32 arg0) {
    _spu_tsa = _spu_FsetRXXa(-1, arg0);
    return arg0;
}
