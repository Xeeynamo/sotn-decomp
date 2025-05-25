// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6280);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6740);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6958);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6A08);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A6E50);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A7560);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A7950);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A7B80);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A7F20);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A7F78);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A81C0);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A82E0);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A8AE8);

static int func_pspeu_092A9250() {
    switch (PLAYER.step) {
    case PL_S_CROUCH:
        return -20;
    default:
        return -36;
    }
}

AnimationFrame D_pspeu_092C09F8[];
void func_pspeu_092A9288(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x11;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = 0x811A;
        self->animSet = ANIMSET_OVL(0x14);
        MarSetAnimation(D_pspeu_092C09F8);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->hitboxWidth = 48;
        self->hitboxHeight = 40;
        self->hitboxOffX = 0;
        self->hitboxOffY = -20;
        self->ext.maria092A9288.unkB0 = 0;
        MarSetWeaponParams(self, 0x20, 0x9000, 2, 0x20, 0x10, 1, 0);
        g_api.PlaySfx(SFX_FIREBALL_SHOT_B);
        g_Player.unk7A = 1;
        self->ext.maria092A9288.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->hitboxOffY = -20;
        self->rotX += 16;
        self->rotY += 16;
        if (self->rotX == 256) {
            self->step++;
        }
        break;
    case 2:
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 0x18 + func_pspeu_092A9250();
        self->hitboxOffY = -20;
        self->drawFlags = FLAG_DRAW_DEFAULT;
        self->ext.maria092A9288.timer++;
        if (self->ext.maria092A9288.timer >= 60) {
            self->step++;
        }
        break;
    case 3:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
    if (PLAYER.step != PL_S_SUBWPN_28) {
        self->step = 3;
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A95A8);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9920);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9978);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9C28);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9D48);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9DE8);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092A9E88);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092AAA38);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092AAC80);

INCLUDE_ASM("maria_psp/nonmatchings/80", func_pspeu_092AB1C0);
