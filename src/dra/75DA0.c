#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80115DA0(void) {
    /**
     * TODO:
     * symbol D_80073428 is PLAYER.animFrameIdx
     * but this function needs the type to be s32
     */
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    *D_80072EF4 = 0;
    D_80072EFC = 4;

    switch (PLAYER.step_s) {
    case 0:
        if ((D_80073428 == 0x10008) &&
            (func_8011AAFC(g_CurrentEntity, 0x79, 0) == NULL)) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 2:
        func_80115C50();
        if ((D_80073428 == 0x10008) &&
            (func_8011AAFC(g_CurrentEntity, 0x20079, 0) == NULL)) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 4:
        func_80115C50();
        if ((D_80073428 == 0x10008) &&
            (func_8011AAFC(g_CurrentEntity, 0x40079, 0) == NULL)) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 1:
    case 3:
    case 5:
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        if (D_80072F3C != 0) {
            func_8010E570(0);
        }
        break;
    }
}