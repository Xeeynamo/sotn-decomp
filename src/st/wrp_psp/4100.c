#include "common.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", EntitySoulStealOrb);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", EntityEnemyBlood);

// psp unique?
u8 func_psp_0923C2F8(u8 arg0) {
    if (arg0 & 0x100) {
        return func_psp_0923C2F8(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_psp_0923C2F8((arg0 & 0x7F) + 3);
    }
    return (arg0 * 0x10);
}

extern s32 D_91ED5F8;
extern s32 D_psp_0924BC68;
extern s32 D_psp_0924BC70;
extern s32* D_psp_0924BC78;

// PSP unique?
void func_psp_0923C390(s32 arg0, s32 arg1) {
    D_psp_0924BC78 = &D_91ED5F8;
    D_psp_0924BC70 = arg0;
    D_psp_0924BC68 = arg1;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", BlitChar);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", func_8018CAB0);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", func_8018CB34);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/4100", CollectHeart);
