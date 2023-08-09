#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80115DA0(void) {
    PLAYER.velocityY = 0;
    PLAYER.velocityX = 0;
    g_Player.D_80072EF4 = 0;
    g_Player.D_80072EFC = 4;

    switch (PLAYER.step_s) {
    case 0:
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            func_8011AAFC(g_CurrentEntity, 0x79, 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 2:
        func_80115C50();
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            func_8011AAFC(g_CurrentEntity, 0x20079, 0) == NULL) {
            PLAYER.animFrameDuration = 2;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010E570(0);
        }
        break;

    case 4:
        func_80115C50();
        if (PLAYER.animFrameIdx == 8 && PLAYER.animFrameDuration == 1 &&
            func_8011AAFC(g_CurrentEntity, 0x40079, 0) == NULL) {
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
        if (g_Player.unk1C != 0) {
            func_8010E570(0);
        }
        break;
    }
}
