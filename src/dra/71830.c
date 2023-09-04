#define INCLUDE_ASM_NEW
#include "common.h"
#include "dra.h"
#include "objects.h"

void func_80111830(void) {
    s32 var_v0;
    s32 i;

    for (i = 0; i < 16; i++) {
        switch (i) {
        case 0:
            var_v0 = func_801104D0();
            break;
        case 1:
            var_v0 = func_801106A4();
            break;
        case 2:
            var_v0 = func_8011081C();
            break;
        case 3:
            var_v0 = func_80110DF8();
            break;
        case 4:
            var_v0 = func_80111018();
            break;
        case 6:
            var_v0 = func_801112AC();
            break;
        case 9:
            var_v0 = func_8011151C();
            break;
        case 14:
            var_v0 = func_80110BC8();
            break;
        case 15:
            var_v0 = func_80110968();
            break;
        case 5:
        case 7:
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        default:
            var_v0 = 0;
            break;
        }
        if (var_v0 != 0) {
            return;
        }
    }
}

void func_80111928(void) { D_801396EA = 0; }

void func_80111938(void) {
    D_801396EA = 1;
    D_801396E4 = PLAYER.animCurFrame;
    D_801396E6.S16.unk0 = PLAYER.unk19;
    D_801396E8 = PLAYER.palette;
}

void func_8011197C(void) {
    D_801396EA = 0;
    PLAYER.unk44 = 0;
    PLAYER.animCurFrame = D_801396E4;
    PLAYER.unk19 = D_801396E6.S8.unk0;
    PLAYER.palette = D_801396E8;
}

bool func_801119C4(void) {
    if (D_801396EA == 0) {
        if (g_Player.padTapped & PAD_L2) {
            if (g_Player.D_80072EFC == 0) {
                func_80111938();
                return true;
            }
        }

        return false;
    }
    if ((g_Player.D_80072EFC != 0) || (g_Player.padTapped & PAD_L2)) {
        func_8011197C();
        return false;
    }
    if (g_Player.padPressed & PAD_CROSS) {
        if (g_Player.padPressed & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padPressed & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }

    } else {
        if (g_Player.padTapped & PAD_RIGHT) {
            g_Entities->posX.val += FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_LEFT) {
            g_Entities->posX.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_UP) {
            PLAYER.posY.val -= FIX(16.0f);
        }
        if (g_Player.padTapped & PAD_DOWN) {
            PLAYER.posY.val += FIX(16.0f);
        }
    }
#ifdef VERSION_US
    if (g_Player.padTapped & PAD_TRIANGLE) {
        if (!(D_80137FDC & 1)) {
            PLAYER.palette = 0x8100;
        } else {
            PLAYER.palette = 0x810D;
        }
        D_80137FDC++;
    }
#endif
    if (g_Player.padTapped & PAD_CIRCLE) {
        PLAYER.animCurFrame--;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        PLAYER.animCurFrame++;
    }
    if (PLAYER.animCurFrame <= 0) {
        PLAYER.animCurFrame = 1;
    }
    if (!(PLAYER.animCurFrame < 0xE1)) {
        PLAYER.animCurFrame = 0xE0;
    }
    FntPrint("charal:%02x\n", PLAYER.animCurFrame);
    return true;
}

void func_80111CC0(void) {
    if (g_Player.D_80072F02 != 0) {
        func_8011AAFC(g_CurrentEntity, 0x17002C, 0);
    }
    if (g_Player.D_80072F00 != 0) {
        func_8011AAFC(g_CurrentEntity, 0x16002C, 0);
    }
}

bool func_80111D24(void) {
    Collider collider;
    s32 speed = 0xC000;
    s16 posX = PLAYER.posX.i.hi;
    s16 posY = PLAYER.posY.i.hi;
    s32 hitboxLeftMargin;
    s32 hitboxRightMargin;

    CheckCollision(posX - 7, posY, &collider, 0);
    hitboxLeftMargin = collider.effects & EFFECT_MIST_ONLY;
    CheckCollision(posX + 7, posY, &collider, 0);
    hitboxRightMargin = collider.effects & EFFECT_MIST_ONLY;

    if (hitboxRightMargin & hitboxLeftMargin) {
        SetSpeedX(speed);
        return true;
    } else if (hitboxRightMargin != 0) {
        PLAYER.velocityX = -speed;
        return true;
    } else if (hitboxLeftMargin != 0) {
        PLAYER.velocityX = speed;
        return true;
    }
    return false;
}

INCLUDE_ASM("dra/nonmatchings/71830", func_80111DE8);

bool func_8011203C(void) {
    s32 collision = func_80111D24();

    if (g_Entities[E_WEAPON].step == 5) {
        if (collision == false) {
            DestroyEntity(&g_Entities[E_WEAPON]);
            return true;
        }
        return false;
    } else if (g_Entities[E_WEAPON].step <= 2) {
        if (g_Entities[E_WEAPON].step != 0) {
            g_Player.unk46 = 0;
            g_Entities[E_WEAPON].step = 3;
        }
    }
    return false;
}

INCLUDE_ASM("dra/nonmatchings/71830", func_801120B4);

void func_80112B64(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        SetSpeedX(0x18000);
        if (func_8010E27C() == 0) {
            func_8010E570(0);
        }
    }
}
