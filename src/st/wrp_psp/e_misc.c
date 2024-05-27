#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityRelicOrb);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityHeartDrop);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityMessageBox);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", func_8018F510);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", func_8018F838);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityUnkId15);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/e_misc", EntityIntenseExplosion);

void func_801916C4(s16 sfxId) {
    s32 posX;
    s32 posY;
    s16 arg2;
    s16 arg1;

    posX = g_CurrentEntity->posX.i.hi - 128;
    arg2 = (abs(posX) - 32) >> 5;
    if (arg2 > 8) {
        arg2 = 8;
    } else if (arg2 < 0) {
        arg2 = 0;
    }
    if (posX < 0) {
        arg2 = -arg2;
    }
    arg1 = abs(posX) - 96;
    posY = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (posY > 0) {
        arg1 += posY;
    }
    if (arg1 < 0) {
        arg1 = 0;
    }
    arg1 = 127 - (arg1 >> 1);
    if (arg1 > 0) {
        g_api.func_80134714(sfxId, arg1, arg2);
    }
}
