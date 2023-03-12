#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

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

INCLUDE_ASM("asm/us/dra/nonmatchings/71830", func_801119C4);

void func_80111CC0(void) {
    if (D_80072F00[1] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x17002C, 0);
    }
    if (D_80072F00[0] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x16002C, 0);
    }
}

bool func_80111D24(void) {
    Collider res;
    s32 speed = 0xC000;
    s16 posX = PLAYER.posX.i.hi;
    s16 posY = PLAYER.posY.i.hi;
    s32 hitboxLeftMargin;
    s32 hitboxRightMargin;

    CheckCollision(posX - 7, posY, &res, 0);
    hitboxLeftMargin = res.unk0 & 0x10;
    CheckCollision(posX + 7, posY, &res, 0);
    hitboxRightMargin = res.unk0 & 0x10;

    if (hitboxRightMargin & hitboxLeftMargin) {
        AccelerateX(speed);
        return true;
    } else if (hitboxRightMargin != 0) {
        PLAYER.accelerationX = -speed;
        return true;
    } else if (hitboxLeftMargin != 0) {
        PLAYER.accelerationX = speed;
        return true;
    }
    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/71830", func_80111DE8);

bool func_8011203C(void) {
    s32 collision = func_80111D24();

    if (g_EntityArray[UNK_ENTITY_10].step == 5) {
        if (collision == false) {
            DestroyEntity(&g_EntityArray[UNK_ENTITY_10]);
            return true;
        }
        return false;
    } else if (g_EntityArray[UNK_ENTITY_10].step <= 2) {
        if (g_EntityArray[UNK_ENTITY_10].step != 0) {
            D_80072F66 = 0;
            g_EntityArray[UNK_ENTITY_10].step = 3;
        }
    }
    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/71830", func_801120B4);

void func_80112B64(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        AccelerateX(0x18000);
        if (func_8010E27C() == 0) {
            func_8010E570(0);
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/71830", func_80112BB0);

void func_80113148(void) {
    if ((D_80072F0A[0] != 0) && (D_80072EEC & 0x40)) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        func_8010E1EC(0x1000);
        if (func_8010E27C() != 0) {
            AccelerateX(0xC000);
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/71830", func_801131C4);

void func_801139CC(s32 arg0) {
    s32 move = PLAYER.facing != 0 ? -3 : 3;

    PLAYER.posY.i.hi -= 22;
    PLAYER.posX.i.hi = move + PLAYER.posX.i.hi;
    func_8011AAFC(g_CurrentEntity, 0x10004, 0);
    PLAYER.posY.i.hi = PLAYER.posY.i.hi + 22;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - move;

    if (arg0 & 1) {
        func_80102CD8(3);
        PlaySfx(NA_SE_SECRET_STAIRS);
    }
    if (arg0 & 2) {
        PLAYER.accelerationX = 0;
        PLAYER.accelerationY = 0;
    }
}
