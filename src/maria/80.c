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

extern AnimationFrame D_pspeu_092C0A50[];
void func_pspeu_092AAA38(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_UNK_100000;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 8;
        self->palette = 0x8116;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A50);
        self->facingLeft = PLAYER.facingLeft;
        self->velocityX = 0;
        self->ext.maria092AAA38.x = 0;
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.maria092AAA38.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->hitboxWidth = 24;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->attack = 255;
        self->attackElement = 0;
        self->hitboxState = 4;
        self->nFramesInvincibility = 6;
        self->stunFrames = 0;
        self->hitEffect = 1;
        self->entityRoomIndex = 1;
        g_Player.unk7A = 1;
        self->ext.maria092AAA38.timer = 0;
        self->step++;
        break;
    case 1:
        self->posX.i.hi = PLAYER.posX.i.hi + self->ext.maria092AAA38.x;
        self->posY.i.hi = PLAYER.posY.i.hi + 24;
        self->ext.maria092AAA38.timer++;
        if (self->ext.maria092AAA38.timer >= 180) {
            self->step++;
        }
        break;
    case 2:
        g_Player.unk7A = 0;
        DestroyEntity(self);
        break;
    }
}

extern AnimationFrame D_pspeu_092C0A60[];
void func_pspeu_092AAC80(Entity* self) {
    s32 x;

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 6;
        self->palette = 0x8116;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A60);
        self->facingLeft = PLAYER.facingLeft;
        if (PLAYER.facingLeft) {
            x = -74;
        } else {
            x = 74;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + x;
        self->posY.i.hi = PLAYER.posY.i.hi - 16;
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        g_Player.unk28 = NULL;
#if defined(VERSION_PC)
        g_Player.unk20 = (signed long long)self;
#else
        g_Player.unk20 = (s32)self;
#endif
        g_Player.unk24 = 0;
        self->ext.maria092AAC80.timer = 0;
        self->ext.maria092AAC80.timer2 = 0;
        g_Player.unk2C = -1;
        self->step = 1;
        func_pspeu_092BF8B8(3);
        func_pspeu_092BEA38(self, 0);
        return;
    case 1:
        if (g_Player.unk5C == 1) {
            g_api.PlaySfx(SFX_VO_MAR_8F1);
            MarCreateEntFactoryFromEntity(self, 0xE, 0);
            self->step = 3;
        }
        break;
    case 3:
        self->ext.maria092AAC80.timer2 += 16;
        if (self->ext.maria092AAC80.timer2 >= 128) {
            func_pspeu_092BEA38(self, 0x80);
            self->step = 2;
            return;
        }
        func_pspeu_092BEA38(self, self->ext.maria092AAC80.timer2);
        break;
    case 2:
        if (self->rotX < 256) {
            self->rotX += 16;
            self->rotY += 16;
        } else {
            self->drawFlags &= ~(FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
        }
        if ((self->ext.maria092AAC80.timer % 60) == 0) {
            g_api_PlaySfx(SFX_MAGIC_NOISE_SWEEP);
        }
        self->ext.maria092AAC80.timer++;
        if (self->ext.maria092AAC80.timer >= 0xFF) {
            self->step = 5;
        }
        break;
    case 5:
        if (self->rotX > 0x80) {
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
            self->rotX -= 0x20;
            self->rotY -= 0x20;
            self->rotZ += 0xF78;
            return;
        }
        self->ext.maria092AAC80.timer2 = 0x80;
        self->step = 4;
        break;
    case 4:
        self->ext.maria092AAC80.timer2 -= 0x10;
        if (self->ext.maria092AAC80.timer2 <= 0) {
            func_pspeu_092BEA38(self, 0);
            self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->step = 6;
            func_pspeu_092BFEB0(g_Player.unk20);
            g_Player.unk2C = 0xB4;
            return;
        }
        func_pspeu_092BEA38(self, self->ext.maria092AAC80.timer2);
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;
        break;
    case 6:
        if (g_Player.unk28 == NULL) {
            self->step = 7;
            self->ext.maria092AAC80.timer3 = 0;
            return;
        }
        if (g_Player.unk2C == 0) {
            g_api_PlaySfx(SFX_HEALTH_PICKUP);
            g_Player.unk56 = 1;
            g_Player.unk58 = g_Player.unk24;
            self->step = 7;
            self->ext.maria092AAC80.timer3 = 0;
            return;
        }
        g_Player.unk2C--;
        break;
    case 7:
        self->ext.maria092AAC80.timer3++;
        if (self->ext.maria092AAC80.timer3 > 60) {
            g_Player.unk28 = NULL;
            g_Player.unk20 = 0;
            g_Player.unk5C = 0;
            DestroyEntity(self);
        }
        break;
    }
}

AnimationFrame D_pspeu_092C0A58[];
void func_pspeu_092AB1C0(Entity* self) {
    Entity* entity;
    s32 x;

    entity = *(Entity**)&g_Player.unk20;
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x10;
        self->zPriority = PLAYER.zPriority - 7;
        self->palette = 0x8116;
        self->animSet = ANIMSET_OVL(18);
        MarSetAnimation(D_pspeu_092C0A58);
        self->facingLeft = 0;
        self->velocityX = 0;
        self->ext.maria092AB1C0.rotation = 0xF0;
        if (entity == NULL) {
            if (PLAYER.facingLeft) {
                x = -74;
            } else {
                x = 74;
            }
            self->posX.i.hi = PLAYER.posX.i.hi + x;
            self->posY.i.hi = PLAYER.posY.i.hi - 0x10;
        } else {
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
        }
        self->rotX = 0;
        self->rotY = 0;
        self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        self->drawMode |= DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
        self->rotZ = 0;
        self->unk6C = 0x80;
        self->hitboxWidth = 48;
        self->hitboxHeight = 48;
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->ext.maria092AB1C0.unkB0 = 0;
        MarSetWeaponParams(self, 5, 0x1400, 2, 0x20, 0, 2, 0);
        self->ext.maria092AB1C0.hitboxState = self->hitboxState;
        self->hitboxState = 0;
        self->ext.maria092AB1C0.timer = 0;
        self->step = 1;
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 1:
        if (self->rotX < 256) {
            self->rotX += 16;
            self->rotY += 16;
        } else {
            self->hitboxState = self->ext.maria092AB1C0.hitboxState;
            self->drawFlags &= ~(FLAG_DRAW_ROTX | FLAG_DRAW_ROTY);
        }
        self->ext.maria092AB1C0.timer++;
        if (self->ext.maria092AB1C0.timer >= 240) {
            self->hitboxState = 0;
            self->step = 2;
        }
        if (self->ext.maria092AB1C0.timer % 8 == 0) {
            self->ext.maria092AB1C0.rotation -= 5;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 2:
        if (self->ext.maria092AB1C0.rotation >= 65) {
            self->ext.maria092AB1C0.rotation -= 5;
        } else {
            self->step = 3;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 3:
        if (self->rotX > 0) {
            self->rotX -= 8;
            self->rotY -= 8;
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
        } else {
            self->step = 4;
        }
        self->rotZ += 0x1000 - (0x1000 / self->ext.maria092AB1C0.rotation);
        return;
    case 4:
        DestroyEntity(self);
        return;
    }
}
