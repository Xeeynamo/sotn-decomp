// SPDX-License-Identifier: AGPL-3.0-or-later
#include "maria.h"

void func_pspeu_092BEA38(Entity* entity, s32 setUnk6C) {
    if (setUnk6C >= 0x80) {
        entity->drawMode = entity->drawFlags = FLAG_DRAW_DEFAULT;
        entity->unk6C = 0x80;
    } else {
        entity->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = setUnk6C;
    }
}

s32 func_pspeu_092BEAB0(s16 setUnk80) {
    Entity* entity = (Entity*)MarGetFreeEntity(0x38, 0x40);
    if (entity == NULL) {
        return -1;
    }
    DestroyEntity(entity);
    entity->entityId = E_UNK_16;
    entity->posX.val = g_Entities->posX.val;
    entity->posY.val = g_Entities->posY.val;
    entity->ext.maria092BEAB0.unk80 = setUnk80;
    entity->ext.maria092BEAB0.unk82 = 1;
    return 0;
}

void func_pspeu_092BEB40(Entity* self) {
    s32 timer;
    u16 value;
    s16 x2;
    s16 h;
    s16 x;
    s16 y;
    s16 w;
    u8 u;
    s32 i;
    Primitive* prim;

    timer = -1;
    switch (self->step) {
    case 0:
        value = self->ext.maria092BEB40.value;
        self->primIndex = func_90E0E30(PRIM_GT4, 20);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_10000 | FLAG_HAS_PRIMS | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->ext.maria092BEB40.width = 0;
        self->ext.maria092BEB40.height = 2;
        self->ext.maria092BEB40.timer = 8;
        self->ext.maria092BEB40.digits[0] = value % 10;
        value /= 10;
        if (value) {
            self->ext.maria092BEB40.digits[1] = value % 10;
            value /= 10;
            self->ext.maria092BEB40.nDigits++;
            if (value) {
                self->ext.maria092BEB40.digits[2] = value % 10;
                value /= 10;
                self->ext.maria092BEB40.nDigits++;
                if (value) {
                    self->ext.maria092BEB40.digits[3] = value % 10;
                    self->ext.maria092BEB40.nDigits++;
                }
            }
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 4; i++) {
            prim->clut = 0x1B2;
            if (self->ext.maria092BEB40.value == 0) {
                prim->clut = 0x1B4;
            }
            if (self->ext.maria092BEB40.kind == 1) {
                prim->clut = 0x1B8;
            }
            if (self->ext.maria092BEB40.kind == 2) {
                prim->clut = 0x1B6;
            }
            prim->tpage = 0x1A;
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_DEFAULT;
            u = self->ext.maria092BEB40.digits[i] * 8;
            if (self->ext.maria092BEB40.digits[i]) {
                u -= 8;
            } else {
                u += 0x48;
            }
            prim->u0 = u + 0x20;
            prim->v0 = 0x40;
            prim->u1 = u + 0x28;
            prim->v1 = 0x40;
            prim->u2 = u + 0x20;
            prim->v2 = 0x49;
            prim->u3 = u + 0x28;
            prim->v3 = 0x49;
            if (self->ext.maria092BEB40.nDigits < i) {
                prim->drawMode = 8;
            }
            prim = prim->next;
        }
        for (i = 0; i < 16; i++) {
            prim->type = PRIM_TILE;
            prim->r0 = 0xFF;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            if (self->ext.maria092BEB40.value == 0) {
                prim->r0 = 0x40;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            if (self->ext.maria092BEB40.kind == 1) {
                prim->r0 = 0x40;
                prim->g0 = 0xFF;
                prim->b0 = 0x40;
            }
            if (self->ext.maria092BEB40.kind == 2) {
                prim->r0 = 0xFF;
                prim->g0 = 0x40;
                prim->b0 = 0xFF;
            }
            prim->priority = 0x1B8;
            prim->drawMode = DRAW_UNK02 | DRAW_HIDE;
            prim->u0 = prim->v0 = 1;
            prim = prim->next;
        }
        self->step++;
        break;
    case 1:
        self->ext.maria092BEB40.width++;
        self->ext.maria092BEB40.height++;
        if (self->ext.maria092BEB40.kind != 2) {
            self->posY.i.hi -= 1;
        }
        if (--self->ext.maria092BEB40.timer == 0) {
            self->ext.maria092BEB40.timer = 8;
            self->step++;
        }
        break;
    case 2:
        self->ext.maria092BEB40.width--;
        self->ext.maria092BEB40.height--;
        if (self->ext.maria092BEB40.width == 4) {
            self->step++;
            self->ext.maria092BEB40.timer = 4;
        }
        break;
    case 3:
        self->ext.maria092BEB40.width++;
        self->ext.maria092BEB40.height++;
        if (self->ext.maria092BEB40.kind != 2) {
            self->posY.i.hi -= 1;
        }
        if (--self->ext.maria092BEB40.timer == 0) {
            self->ext.maria092BEB40.timer = 3;
            self->step++;
        }
        break;
    case 4:
        self->ext.maria092BEB40.width--;
        self->ext.maria092BEB40.height--;
        if (self->ext.maria092BEB40.width == 4) {
            self->ext.maria092BEB40.timer = 24;
            self->step++;
        }
        break;
    case 5:
        if (--self->ext.maria092BEB40.timer == 0) {
            x = self->posX.i.hi - 13;
            y = self->posY.i.hi - 70;
            self->ext.maria092BEB40.direction = ratan2(-y, x) & 0xFFF;
            self->ext.maria092BEB40.distance = SquareRoot0(x * x + y * y);
            self->ext.maria092BEB40.timer = 16;
            self->ext.maria092BEB40.angle = 0;
            self->step++;
        }
        break;
    case 6:
        if (self->ext.maria092BEB40.width != 2) {
            self->ext.maria092BEB40.width--;
            self->ext.maria092BEB40.height--;
        }
        self->ext.maria092BEB40.timer--;
        timer = self->ext.maria092BEB40.timer;
        y = self->ext.maria092BEB40.direction;
        x = self->ext.maria092BEB40.distance * self->ext.maria092BEB40.timer /
            16;
        self->posX.i.hi = ((x * (rcos(y) >> 4)) >> 8) + 0xD;
        self->posY.i.hi = 0x46 - ((x * (rsin(y) >> 4)) >> 8);
        self->ext.maria092BEB40.angle += 0x100;
        self->posX.i.hi += rcos(self->ext.maria092BEB40.angle) >> 9;
        self->posY.i.hi -= rsin(self->ext.maria092BEB40.angle) >> 9;
        if (self->ext.maria092BEB40.timer == 0) {
            if (self->ext.maria092BEB40.kind == 2) {
                DestroyEntity(self);
                return;
            }
            self->step++;
            break;
        }
        break;
    case 7:
    case 9:
        self->ext.maria092BEB40.width++;
        self->ext.maria092BEB40.height++;
        if (self->ext.maria092BEB40.width == 7) {
            self->step++;
            self->ext.maria092BEB40.timer = 24;
        }
        break;
    case 8:
        if (self->ext.maria092BEB40.width != 4) {
            self->ext.maria092BEB40.width--;
            self->ext.maria092BEB40.height--;
        } else {
            self->step++;
        }
        break;
    case 10:
        if (self->ext.maria092BEB40.width != 4) {
            self->ext.maria092BEB40.width--;
            self->ext.maria092BEB40.height--;
        }
        if (--self->ext.maria092BEB40.timer == 0) {
            self->step++;
        }
        break;
    case 11:
        self->ext.maria092BEB40.x += 2;
        self->posX.i.hi -= 2;
        if (!(--self->ext.maria092BEB40.timer & 2)) {
            self->ext.maria092BEB40.height--;
        }
        if (self->ext.maria092BEB40.height == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    w = self->ext.maria092BEB40.width;
    h = self->ext.maria092BEB40.height;
    if (self->step != 11) {
        self->ext.maria092BEB40.x = self->posX.i.hi;
    }
    x = self->posX.i.hi + w * self->ext.maria092BEB40.nDigits;
    x2 = self->ext.maria092BEB40.x + w * self->ext.maria092BEB40.nDigits;
    y = self->posY.i.hi - 16;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 4; i++) {
        prim->x0 = x - w;
        prim->y0 = y - h;
        prim->x1 = x + w;
        prim->y1 = y - h;
        prim->x2 = x2 - w;
        prim->y2 = y + h;
        prim->x3 = x2 + w;
        prim->y3 = y + h;
        x -= w * 2 - 3;
        x2 -= w * 2 - 3;
        prim = prim->next;
    }
    for (i = 0; i < 16; i++) {
        if (prim->r1) {
            if (--prim->g1 == 0) {
                prim->drawMode = DRAW_HIDE;
            }
            prim->y0++;
        } else if (timer == i) {
            prim->drawMode &= ~DRAW_HIDE;
            prim->x0 = self->posX.i.hi;
            prim->y0 = self->posY.i.hi;
            prim->r1++;
            prim->g1 = 12;
        }
        prim = prim->next;
    }
}

s32 func_pspeu_092BF8B8(s32 crashId) {
    Entity* entity;

    entity = (Entity*)MarGetFreeEntity(8, 16);
    if (entity == NULL) {
        g_Player.unk5C = 1;
        return -1;
    }
    DestroyEntity(entity);
    entity->entityId = E_UNK_6;
    entity->posX.val = PLAYER.posX.val;
    entity->posY.val = PLAYER.posY.val;
    entity->ext.mariaCrashSummon.crashId = crashId;
    return 0;
}

void func_pspeu_092BF950(Entity* self) {
    s32 x;
    s32 y;
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            g_Player.unk5C = 1;
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_KEEP_ALIVE_OFFCAMERA;
        self->unk5A = 0x1C;
        self->zPriority = 0x1C0;
        func_pspeu_092C0138(self->ext.mariaCrashSummon.crashId);
        MarSetInvincibilityFrames(0, 999);
        self->ext.mariaCrashSummon.timer = 0x200;
        self->step = 1;
        break;
    case 1:
        self->ext.mariaCrashSummon.timer -= 0x10;
        if (self->ext.mariaCrashSummon.timer > 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim->tpage = 7;
            prim->clut = 0x11E;
            prim->priority = 0x1C0;
            x = (self->ext.mariaCrashSummon.timer * 128) / 256;
            y = (self->ext.mariaCrashSummon.timer * 112) / 256;
            prim->x0 = self->posX.i.hi - x / 2;
            prim->y0 = self->posY.i.hi - y / 2;
            prim->x1 = x + (self->posX.i.hi - x / 2);
            prim->y1 = self->posY.i.hi - y / 2;
            prim->x2 = self->posX.i.hi - x / 2;
            prim->y2 = y + (self->posY.i.hi - y / 2);
            prim->x3 = x + (self->posX.i.hi - x / 2);
            prim->y3 = y + (self->posY.i.hi - y / 2);
            prim->u0 = 0;
            prim->v0 = 0;
            prim->u1 = 0x7F;
            prim->v1 = 0;
            prim->u2 = 0;
            prim->v2 = 0x70;
            prim->u3 = 0x7F;
            prim->v3 = 0x70;
            prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
            return;
        }
        self->step = 2;
        break;
    case 2:
        g_Player.timers[PL_T_INVINCIBLE_SCENE] = 0;
        g_Player.unk5C = 1;
        DestroyEntity(self);
        break;
    }
}

void func_pspeu_092BFD30(Entity* self) {
    if (PLAYER.step_s != 0x70) {
        DestroyEntity(self);
        return;
    }
    self->flags = FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED;
    self->facingLeft = PLAYER.facingLeft;
    self->posY.i.hi = PLAYER.posY.i.hi;
    self->posX.i.hi = PLAYER.posX.i.hi;
    g_Player.unk44 &= ~0x80;
    if (self->step == 0) {
        self->attack = 30;
        self->attackElement = ELEMENT_HIT;
        self->hitboxState = 2;
        self->nFramesInvincibility = 16;
        self->stunFrames = 16;
        self->hitEffect = 1;
        self->entityRoomIndex = 0;
        func_8015F9F0(self);
        self->hitboxOffX = 9;
        self->hitboxOffY = 21;
        self->hitboxWidth = 4;
        self->hitboxHeight = 5;
        self->step++;
        return;
    }
    if (self->hitFlags == 1) {
        g_Player.unk44 |= 0x80;
    }
}

INCLUDE_ASM("maria_psp/nonmatchings/18838", func_pspeu_092BFEB0);

void func_pspeu_092BFF78(Entity* self) {
    if (g_Player.unk28) {
        g_Player.unk28(self);
    }
}
