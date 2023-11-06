#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libetc/pad", PadInit);
// void PadInit(s32 arg0) {
//     D_80073080 = arg0;
//     D_8003925C = -1;
//     ResetCallback();
//     PAD_init(0x20000001, &D_8003925C);
//     ChangeClearPAD(0);
// }

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libetc/pad", PadRead);

INCLUDE_ASM("asm/us/main/nonmatchings/psxsdk/libetc/pad", PadStop);
