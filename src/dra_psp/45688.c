// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

// expanding circle effect when activating stopwatch
void EntityStopWatchExpandingCircle(Entity* self) {
    Primitive* prim;
    s16 angle;
    s32 sine;
    s32 cosine;
    s32 i;
    s16 selfPosX;
    s16 selfPosY;
    s16 minus20;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; prim = prim->next, i++) {
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->priority = self->zPriority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            angle = i << 8;
            prim->u0 = ((rsin(angle) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos(angle) << 5) >> 0xC) + 0xDF;
            angle = (i + 1 << 8);
            prim->u1 = ((rsin(angle) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos(angle) << 5) >> 0xC) + 0xDF;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->r0 = prim->r1 = prim->g0 = prim->g1 = prim->b0 = prim->b1 =
                0x40;
            prim->r2 = prim->r3 = prim->g2 = prim->g3 = 0;
            prim->b2 = prim->b3 = 0x20;
        }
        self->ext.et_stopwatchCircle.size = 0x20;
        self->step++;
        break;
    case 1:
        self->ext.et_stopwatchCircle.size += 0x18;
        self->ext.et_stopwatchCircle.timer++;
        if (self->ext.et_stopwatchCircle.timer > 30) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; prim = prim->next, i++) {
        sine = rsin(i << 8);
        cosine = rcos(i << 8);
        minus20 = self->ext.et_stopwatchCircle.size - 0x20;
        prim->x0 =
            selfPosX + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y0 =
            selfPosY - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x2 = selfPosX + ((sine * (minus20)) >> 0xC);
        prim->y2 = selfPosY - ((cosine * minus20) >> 0xC);
        sine = rsin((i + 1) << 8);
        cosine = rcos((i + 1) << 8);
        prim->x1 =
            selfPosX + ((sine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->y1 =
            selfPosY - ((cosine * self->ext.et_stopwatchCircle.size) >> 0xC);
        prim->x3 = selfPosX + ((sine * minus20) >> 0xC);
        prim->y3 = selfPosY - ((cosine * minus20) >> 0xC);
    }
}

// stopwatch subweapon effect. stops enemies (Dra Entity 0x2A)
void EntityStopWatch(Entity* self) {
    s32 var_s7;
    s32 c; //s6
    s32 d; //s5
    s16 offsetX, offsetY; //s4, s3
    s32 y; //s2
    s32 x; //s1
    Primitive* prim;

    if (g_unkGraphicsStruct.pauseEnemies) {
        g_unkGraphicsStruct.D_800973FC = 0;
        if (self->step && (self->step < 4)) {
            self->step = 4;
        }
    }

    switch (self->step) {
    case 0:
        if (g_unkGraphicsStruct.pauseEnemies) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->v0 = prim->v1 = 0xC0;
        prim->v2 = prim->v3 = 0xD8;
        if (self->facingLeft) {
            prim->u0 = prim->u2 = 0x98;
            prim->u1 = prim->u3 = 0xA8;
        } else {
            prim->u0 = prim->u2 = 0xA8;
            prim->u1 = prim->u3 = 0x98;
        }
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0x1A;
        prim->clut = 0x186;
        prim->priority = PLAYER.zPriority + 3;
        prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE | DRAW_UNK02;

        CreateEntFactoryFromEntity(self, FACTORY(75, 0), 0);
        PlaySfx(SFX_UI_ALERT_TINK);
        g_unkGraphicsStruct.D_800973FC = 1;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;

        self->ext.stopwatch.unk84.val += FIX(1.5);
        if (self->ext.stopwatch.unk84.val >= FIX(26)) {
            self->step++;
        }
        break;
    case 2:
        self->ext.stopwatch.unk84.val += FIX(-1);
        if (self->ext.stopwatch.unk84.val <= FIX(16)) {
            self->ext.stopwatch.t = 5;
            PlaySfx(SFX_CLOCK_TICK);
            self->step++;
        }
        break;
    case 3:
        self->ext.stopwatch.unk7E += 1;
        if (self->ext.stopwatch.unk7E > 80) {
            PlaySfx(SFX_CLOCK_TICK);
            self->ext.stopwatch.unk7E = 0;
            self->ext.stopwatch.unk8C = 1;
            self->ext.stopwatch.t -= 1;
            if (self->ext.stopwatch.t < 0) {
                self->step++;
                break;
            }
        }
        if (self->ext.stopwatch.t < 5) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            if (self->ext.stopwatch.t >= 10) {
                self->ext.stopwatch.unk8E = 1;
                x = (self->ext.stopwatch.t / 10) * 8;
                prim->u0 = prim->u2 = x + 0x18;
                prim->v0 = prim->v1 = 0x40;
                prim->u1 = prim->u3 = x + 0x1E;
                prim->v2 = prim->v3 = 0x49;
                prim->drawMode &= ~DRAW_HIDE;
                prim = prim->next;
            } else {
                self->ext.stopwatch.unk8E = 0;
            }
            x = (self->ext.stopwatch.t % 10) * 8;
            if (x == 0) {
                x = 0x50;
            }
            prim->u0 = prim->u2 = x + 0x18;
            prim->v0 = prim->v1 = 0x40;
            prim->u1 = prim->u3 = x + 0x1E;
            prim->v2 = prim->v3 = 0x49;
            prim->drawMode &= ~DRAW_HIDE;
        }
        break;
    case 4:
        self->flags &= ~FLAG_POS_PLAYER_LOCKED;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode &= ~DRAW_UNK_200;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;
        prim = prim->next;
        prim->drawMode |= DRAW_HIDE;

        self->posX.i.hi += self->facingLeft ? 6 : -6;
        self->posY.i.hi -= self->ext.stopwatch.unk84.val >> 0x10;
        self->ext.stopwatch.t = 0;
        self->step++;
        break;
    case 5:
        self->ext.stopwatch.t += 1;
        if (self->ext.stopwatch.t >= 4) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x15F;
            prim->drawMode |= DRAW_COLORS;
            PRED(prim) = 0x40;
            PGRN(prim) = 0x40;
            PBLU(prim) = 0x60;

            PlaySfx(SFX_UI_TINK);
            self->step++;
        }
        break;
    case 6:
        self->ext.stopwatch.t += 1;
        if (self->ext.stopwatch.t > 14) {
            CreateEntFactoryFromEntity(self, FACTORY(4, 14), 0);
            self->step++;
        }
        break;
    case 7:
        g_unkGraphicsStruct.D_800973FC = 0;
        DestroyEntity(self);
        return;
    }

    if (self->step) {
        prim = &g_PrimBuf[self->primIndex];
        if (self->step < 5) {
            x = PLAYER.posX.val + (PLAYER.facingLeft ? FIX(8) : FIX(-8));
            y = PLAYER.posY.val + FIX(-16);
            self->posX.val += (x - self->posX.val) / 12;
            self->posY.val += (y - self->posY.val) / 4;

            if (PLAYER.facingLeft != self->facingLeft) {
                if (abs(x - self->posX.val) < FIX(1)) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (!self->facingLeft && (self->posX.val > x)) {
                    self->facingLeft = PLAYER.facingLeft;
                } else if (self->facingLeft && (self->posX.val < x)) {
                    self->facingLeft = PLAYER.facingLeft;
                }
            }
            if (self->facingLeft) {
                prim->u0 = prim->u2 = 0x98;
                prim->u1 = prim->u3 = 0xA8;
            } else {
                prim->u0 = prim->u2 = 0xA8;
                prim->u1 = prim->u3 = 0x98;
            }
        }

        if (self->step < 3) {
            x = (self->facingLeft ? 6 : -6) + self->posX.i.hi;
            y = self->posY.i.hi - (self->ext.stopwatch.unk84.val >> 0x10);
            if (self->ext.stopwatch.unk82 < 100) {
                self->ext.stopwatch.unk82 += 4;
            }
            if (self->ext.stopwatch.unk80 < 0x1000) {
                self->ext.stopwatch.unk80 += 0x80;
            }

            offsetX = (self->ext.stopwatch.unk82 * 8) / 100;
            offsetY = (self->ext.stopwatch.unk82 * 12) / 100;
            c = rsin(self->ext.stopwatch.unk80);
            d = rcos(self->ext.stopwatch.unk80);
            prim->x0 = (x + (((d * -offsetX) - (c * -offsetY)) >> 0xC));
            prim->y0 = (y + (((c * -offsetX) + (d * -offsetY)) >> 0xC));
            prim->x1 = (x + (((d * offsetX) - (c * -offsetY)) >> 0xC));
            prim->y1 = (y + (((c * offsetX) + (d * -offsetY)) >> 0xC));
            prim->x2 = (x + (((d * -offsetX) - (c * offsetY)) >> 0xC));
            prim->y2 = (y + (((c * -offsetX) + (d * offsetY)) >> 0xC));
            prim->x3 = (x + (((d * offsetX) - (c * offsetY)) >> 0xC));
            prim->y3 = (y + (((c * offsetX) + (d * offsetY)) >> 0xC));
        } else if (self->step < 5) {
            if (self->ext.stopwatch.unk84.val <= FIX(16)) {
                if (self->ext.stopwatch.unk8C) {
                    self->ext.stopwatch.unk88.val =
                        ((rand() % 64) + 0x200) << 8;
                    self->ext.stopwatch.unk8C = 0;
                } else {
                    self->ext.stopwatch.unk88.val =
                        ((rand() % 128) + 0x100) << 8;
                }
                if (self->ext.stopwatch.unk80 >= 0) {
                    self->ext.stopwatch.unk80 = -((rand() % 64) + 0x40);
                } else {
                    self->ext.stopwatch.unk80 = (rand() % 64) + 0x40;
                }
            }
            self->ext.stopwatch.unk84.val += self->ext.stopwatch.unk88.val;
            self->ext.stopwatch.unk88.val -= FIX(0.25);

            x = (self->facingLeft ? 6 : -6) + self->posX.i.hi;
            y = self->posY.i.hi - (self->ext.stopwatch.unk84.val >> 0x10);

            c = rsin(self->ext.stopwatch.unk80);
            d = rcos(self->ext.stopwatch.unk80);
            prim->x0 = (x + (((d * -8) - (c * -0xC)) >> 0xC));
            prim->y0 = (y + (((c * -8) + (d * -0xC)) >> 0xC));
            prim->x1 = (x + (((d * 8) - (c * -0xC)) >> 0xC));
            prim->y1 = (y + (((c * 8) + (d * -0xC)) >> 0xC));
            prim->x2 = (x + (((d * -8) - (c * 0xC)) >> 0xC));
            prim->y2 = (y + (((c * -8) + (d * 0xC)) >> 0xC));
            prim->x3 = (x + (((d * 8) - (c * 0xC)) >> 0xC));
            prim->y3 = (y + (((c * 8) + (d * 0xC)) >> 0xC));
        } else {
            offsetX = 8 - self->ext.stopwatch.t;
            if (offsetX < 1) {
                offsetX = 1;
            }
            offsetY = (self->ext.stopwatch.t * 32) + 12;
            if (offsetY >= 0x80) {
                offsetY = 0x80;
            }

            prim->x0 = prim->x2 = self->posX.i.hi - offsetX;
            prim->x1 = prim->x3 = self->posX.i.hi + offsetX;
            prim->y0 = prim->y1 = self->posY.i.hi - offsetY;
            prim->y2 = prim->y3 = self->posY.i.hi + offsetY;
        }
        if (self->step < 4) {
            y = self->posY.i.hi - 14;
            if (self->ext.stopwatch.unk8E) {
                x = self->posX.i.hi - (self->facingLeft ? 10 : -4);

                prim = prim->next;
                if (self->ext.stopwatch.unk7E < 8) {
                    prim->x0 = prim->x2 = x - self->ext.stopwatch.unk7E / 2;
                    prim->x1 = prim->x3 = x + self->ext.stopwatch.unk7E / 2;
                    prim->y0 = prim->y1 =
                        (y - 8) - (7 - self->ext.stopwatch.unk7E);
                    prim->y2 = prim->y3 =
                        (y + 8) + (7 - self->ext.stopwatch.unk7E);
                } else if (self->ext.stopwatch.unk7E >= 0x44) {
                    offsetX = (0x50 - (self->ext.stopwatch.unk7E + 4)) / 2;
                    if (offsetX < 0) {
                        offsetX = 0;
                    }
                    offsetY = self->ext.stopwatch.unk7E - 0x44;
                    if (offsetY > 8) {
                        offsetY = 8;
                    }

                    prim->x0 = prim->x2 = x - offsetX;
                    prim->x1 = prim->x3 = x + offsetX;
                    prim->y0 = prim->y1 = (y - 8) - offsetY;
                    prim->y2 = prim->y3 = (y + 8) + offsetY;
                } else {
                    prim->x0 = prim->x2 = x - 4;
                    prim->x1 = prim->x3 = x + 4;
                    prim->y0 = prim->y1 = y - 8;
                    prim->y2 = prim->y3 = y + 8;
                }

                x = self->posX.i.hi - (self->facingLeft ? 4 : -10);
                prim = prim->next;
                if (self->ext.stopwatch.unk7E < 0xC) {
                    offsetX = (self->ext.stopwatch.unk7E - 4) / 2;
                    if (offsetX < 0) {
                        offsetX = 0;
                    }
                    offsetY = 7 - (self->ext.stopwatch.unk7E - 4);
                    if (offsetY < 0) {
                        offsetY = 0;
                    }

                    prim->x0 = prim->x2 = x - offsetX;
                    prim->x1 = prim->x3 = x + offsetX;
                    prim->y0 = prim->y1 = (y - 8) - offsetY;
                    prim->y2 = prim->y3 = (y + 8) + offsetY;
                    return;
                }
                if (self->ext.stopwatch.unk7E >= 0x48) {
                    prim->x0 = prim->x2 =
                        x - ((0x50 - self->ext.stopwatch.unk7E) / 2);
                    prim->x1 = prim->x3 =
                        x + ((0x50 - self->ext.stopwatch.unk7E) / 2);
                    prim->y0 = prim->y1 =
                        (y - 8) - (self->ext.stopwatch.unk7E - 0x48);
                    prim->y2 = prim->y3 =
                        (y + 8) + (self->ext.stopwatch.unk7E - 0x48);
                    return;
                }
                prim->x0 = prim->x2 = x - 4;
                prim->x1 = prim->x3 = x + 4;
                prim->y0 = prim->y1 = y - 8;
                prim->y2 = prim->y3 = y + 8;
                return;
            }

            x = self->posX.i.hi - (self->facingLeft ? 4 : -4);
            prim = prim->next;
            if (self->ext.stopwatch.unk7E < 8) {
                prim->x0 = prim->x2 = x - (self->ext.stopwatch.unk7E / 2);
                prim->x1 = prim->x3 = x + (self->ext.stopwatch.unk7E / 2);
                prim->y0 = prim->y1 = (y - 8) - (7 - self->ext.stopwatch.unk7E);
                prim->y2 = prim->y3 = (y + 8) + (7 - self->ext.stopwatch.unk7E);
                return;
            }
            if (self->ext.stopwatch.unk7E >= 0x48) {
                prim->x0 = prim->x2 =
                    x - ((0x50 - self->ext.stopwatch.unk7E) / 2);
                prim->x1 = prim->x3 =
                    x + ((0x50 - self->ext.stopwatch.unk7E) / 2);
                prim->y0 = prim->y1 =
                    (y - 8) - (self->ext.stopwatch.unk7E - 0x48);
                prim->y2 = prim->y3 =
                    (y + 8) + (self->ext.stopwatch.unk7E - 0x48);
                return;
            }
            prim->x0 = prim->x2 = x - 5;
            prim->x1 = prim->x3 = x + 5;
            prim->y0 = prim->y1 = y - 8;
            prim->y2 = prim->y3 = y + 8;
        }
    }
}

// DRA entity #44. Comes from blueprint 79.
// Identical to RIC
void EntitySubwpnBibleTrail(Entity* self) {
    Primitive* prim;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_UNK_20000 | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1C;
        prim->clut = 0x19D;
        prim->u0 = prim->u2 = 0x20;
        prim->v0 = prim->v1 = 0;
        prim->u1 = prim->u3 = 0x30;
        prim->v2 = prim->v3 = 0x10;
        prim->x0 = prim->x2 = self->posX.i.hi - 8;
        prim->x1 = prim->x3 = self->posX.i.hi + 8;
        prim->y0 = prim->y1 = self->posY.i.hi - 8;
        prim->y2 = prim->y3 = self->posY.i.hi + 8;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
        self->ext.et_BibleSubwpn.unk7E = 0x60;
        self->step++;
        break;
    case 1:
        self->ext.et_BibleSubwpn.unk7C++;
        if (self->ext.et_BibleSubwpn.unk7C > 5) {
            self->step++;
        }
        self->ext.et_BibleSubwpn.unk7E -= 8;
        break;
    case 2:
        DestroyEntity(self);
        return;
    }
    prim = &g_PrimBuf[self->primIndex];
    PCOL(prim) = self->ext.et_BibleSubwpn.unk7E;
}

// book rotates around player
void EntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3c;
    s16 selfX;
    s16 selfY;
    s32 var_s7;
    s32 var_s6;
    s32 var_s5;
    s32 var_s4 = 0;
    s32 var_s3;
    s32 sine;
    s32 cosine;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
        if (self->facingLeft) {
            sp44 = 32;
        } else {
            sp44 = -32;
        }
        self->ext.et_BibleSubwpn.unk84 = sp44;
        func_8011A290(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.et_BibleSubwpn.unk86++;
        g_Player.timers[10] = 4;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        self->ext.et_BibleSubwpn.unk7E++;
        if (self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        self->ext.et_BibleSubwpn.unk7C++;
        if (self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_KEEP_ALIVE_OFFCAMERA;
            if (self->facingLeft) {
                sp40 = FIX(-12);
            } else {
                sp40 = FIX(12);
            }
            self->velocityX = sp40;
            self->velocityY = FIX(-12);
            PlaySfx(SFX_BIBLE_SCRAPE);
            self->ext.et_BibleSubwpn.unk86++;
            self->step++;
        }
        break;
    }
    switch (self->ext.et_BibleSubwpn.unk86) {
    case 0:
        break;
    case 1:
        // All this logic is a mess, could use a cleanup
        sine = rsin(self->ext.et_BibleSubwpn.unk80);
        cosine = rcos(self->ext.et_BibleSubwpn.unk80);
        var_s5 = (sine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        var_s3 = (cosine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        var_s7 = cosine * var_s5 + sine * var_s3;
        sp48 = (cosine * var_s3 - sine * var_s5);
        var_s5 = var_s7 >> 0xC;
        var_s3 = sp48 >> 0xC;
        sine = rsin(self->ext.et_BibleSubwpn.unk82);
        cosine = rcos(self->ext.et_BibleSubwpn.unk82);
        var_s7 = ((cosine * var_s5) + (sine * var_s4)) >> 0xC;
        var_s4 = var_s6 = ((cosine * var_s4) - (sine * var_s5)) >> 0xC;
        if (self->facingLeft) {
            var_s6 = ((cosine * var_s4) + (sine * var_s3)) >> 0xC;
        } else {
            var_s6 = ((cosine * var_s4) - (sine * var_s3)) >> 0xC;
        }
        if (self->facingLeft) {
            sp3c = 0x80;
        } else {
            sp3c = -0x80;
        }
        self->ext.et_BibleSubwpn.unk80 += sp3c;
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (abs(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            self->ext.et_BibleSubwpn.unk84 *= -1;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + var_s7;
        self->posY.i.hi = PLAYER.posY.i.hi + var_s6;
        self->zPriority = PLAYER.zPriority + (var_s3 < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(-2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86) {
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = selfX - 8;
        prim->x1 = prim->x3 = selfX + 8;
        prim->y0 = prim->y1 = selfY - 12;
        prim->y2 = prim->y3 = selfY + 12;
        prim->priority = self->zPriority;
        CreateEntFactoryFromEntity(self, FACTORY(79, 0), 0);
        if (g_GameTimer % 10 == 0) {
            PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}