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

static s32 func_pspeu_092A9920(s32 arg0) {
    arg0 %= 0x1000;
    if (arg0 < 0) {
        arg0 += 0x1000;
    }
    return arg0;
}

extern s32 D_pspeu_092E5D18[0x80];
extern s32 D_pspeu_092E5F18;
static Entity* func_pspeu_092A9978(Entity* self) {
    Entity* e;
    s32 i;
    s32 var_s2;
    s32 found;

    found = 0;
    e = &g_Entities[STAGE_ENTITY_START];
    for (i = 0; i < LEN(D_pspeu_092E5D18); i++, e++) {
        D_pspeu_092E5D18[i] = 0;
        if (!e->entityId) {
            continue;
        }
        if (e->hitboxState == 0) {
            continue;
        }
        if (e->flags & FLAG_UNK_00200000) {
            continue;
        }
        if (e->posX.i.hi < -0x10 || e->posX.i.hi > 0x110) {
            continue;
        }
        if (e->posY.i.hi > 0xF0 || e->posY.i.hi < 0) {
            continue;
        }
        if (e->hitboxState & 8) {
            continue;
        }
        if (self->facingLeft && self->posX.i.hi < e->posX.i.hi) {
            continue;
        }
        if (!self->facingLeft && self->posX.i.hi > e->posX.i.hi) {
            continue;
        }
        if (e->hitPoints >= 0x7000) {
            continue;
        }
        if (e->flags & FLAG_UNK_80000) {
            found++;
            D_pspeu_092E5D18[i] = 1;
        } else {
            e->flags |= FLAG_UNK_80000;
            return e;
        }
    }
    if (found) {
        var_s2 = D_pspeu_092E5F18 % LEN(D_pspeu_092E5D18);
        for (i = 0; i < LEN(D_pspeu_092E5D18); i++) {
            if (D_pspeu_092E5D18[var_s2]) {
                e = &g_Entities[var_s2 + 0x40];
                D_pspeu_092E5F18 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
                return e;
            }
            var_s2 = (var_s2 + 1) % LEN(D_pspeu_092E5D18);
        }
    }
    return NULL;
}

static int func_pspeu_092A9C28(Entity* entity) {
    if (entity == NULL) {
        return 0;
    }
    if (entity->hitboxState == 0) {
        return 0;
    }
    if (entity->posX.i.hi < -0x10) {
        return 0;
    }
    if (entity->posX.i.hi > 0x110) {
        return 0;
    }
    if (entity->posY.i.hi > 0xF0) {
        return 0;
    }
    if (entity->posY.i.hi < 0) {
        return 0;
    }
    if (entity->hitPoints >= 0x7000) {
        return 0;
    }
    if (entity->hitPoints <= 0) {
        return 0;
    }
    return 1;
}

static void func_pspeu_092A9D48(Entity* entity, s32 x, s32 y) {
    entity->ext.maria092A9E88.pos1.x = x;
    entity->ext.maria092A9E88.pos1.y = y;
    entity->ext.maria092A9E88.pos2.x = x;
    entity->ext.maria092A9E88.pos2.y = y;
    entity->ext.maria092A9E88.pos3.x = x;
    entity->ext.maria092A9E88.pos3.y = y;
    entity->ext.maria092A9E88.pos4.x = x;
    entity->ext.maria092A9E88.pos4.y = y;
}

static void func_pspeu_092A9DE8(Entity* entity, s32 x, s32 y) {
    entity->ext.maria092A9E88.pos4.x = entity->ext.maria092A9E88.pos3.x;
    entity->ext.maria092A9E88.pos4.y = entity->ext.maria092A9E88.pos3.y;
    entity->ext.maria092A9E88.pos3.x = entity->ext.maria092A9E88.pos2.x;
    entity->ext.maria092A9E88.pos3.y = entity->ext.maria092A9E88.pos2.y;
    entity->ext.maria092A9E88.pos2.x = entity->ext.maria092A9E88.pos1.x;
    entity->ext.maria092A9E88.pos2.y = entity->ext.maria092A9E88.pos1.y;
    entity->ext.maria092A9E88.pos1.x = x;
    entity->ext.maria092A9E88.pos1.y = y;
}

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
