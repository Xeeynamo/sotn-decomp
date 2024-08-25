#include "dra.h"
#include "dra_bss.h"
#include "sfx.h"

// expanding circle effect when activating stopwatch
void EntityStopWatchExpandingCircle(Entity* self) {
    Primitive* prim;
    s32 sine;
    s32 cosine;
    s32 i;
    u16 selfPosX;
    u16 selfPosY;
    s16 minus20;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 16);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++, prim = prim->next) {
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            self->zPriority = 0xC2;
            prim->priority = 0xC2;
            prim->drawMode = DRAW_UNK_400 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->u0 = ((rsin((s16)(i << 8)) << 5) >> 0xC) + 0x20;
            prim->v0 = -((rcos((s16)(i << 8)) << 5) >> 0xC) - 0x21;
            prim->u1 = ((rsin((s16)(i + 1 << 8)) << 5) >> 0xC) + 0x20;
            prim->v1 = -((rcos((s16)(i + 1 << 8)) << 5) >> 0xC) - 0x21;
            prim->v2 = prim->v3 = 0xE0;
            prim->u2 = prim->u3 = 0x20;
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
        if (++self->ext.et_stopwatchCircle.timer >= 0x1F) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfPosX = self->posX.i.hi;
    selfPosY = self->posY.i.hi;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++, prim = prim->next) {
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
    Primitive* prim;
    s16 a;
    s16 b;
    s32 x;
    s32 c;
    s32 y;
    s32 d;
    s16 offsetX, offsetY;

    if (g_unkGraphicsStruct.unk0) {
        g_unkGraphicsStruct.D_800973FC = 0;
        if (self->step && (self->step < 4)) {
            self->step = 4;
        }
    }

    switch (self->step) {
    case 0:
        if (g_unkGraphicsStruct.unk0) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = AllocPrimitives(PRIM_GT4, 3);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS |
                      FLAG_UNK_40000 | FLAG_UNK_20000;
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

        CreateEntFactoryFromEntity(self, 0x4B, 0);
        PlaySfx(SFX_UNK_6AD);
        g_unkGraphicsStruct.D_800973FC = 1;
        goto label;
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
            PlaySfx(NA_SE_EV_CLOCK_TICK);
            self->step++;
        }
        break;
    case 3:
        self->ext.stopwatch.unk7E += 1;
        if (self->ext.stopwatch.unk7E > 80) {
            PlaySfx(NA_SE_EV_CLOCK_TICK);
            self->ext.stopwatch.unk7E = 0;
            self->ext.stopwatch.unk8C = 1;
            self->ext.stopwatch.t -= 1;
            if (self->ext.stopwatch.t < 0) {
                self->step++;
                break;
            }
        }
        if (self->ext.stopwatch.t < 5) {
            prim = g_PrimBuf[self->primIndex].next;
            if (self->ext.stopwatch.t >= 10) {
                self->ext.stopwatch.unk8E = 1;
                x = (self->ext.stopwatch.t / 10) * 8;
                prim->u0 = prim->u2 = x + 0x18;
                prim->v0 = prim->v1 = 0x40;
                prim->u1 = prim->u3 = x + 0x1E;
                prim->v2 = prim->v3 = 0x49;
                prim->drawMode &= 0xFFF7;
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
            prim->drawMode &= 0xFFF7;
        }
        break;
    case 4:
        self->flags &= ~FLAG_UNK_40000;
        prim = &g_PrimBuf[self->primIndex];
        prim->priority = 0xC2;
        prim->drawMode &= 0xFDFF;
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
        if (self->ext.stopwatch.t > 3) {
            prim = &g_PrimBuf[self->primIndex];
            prim->clut = 0x15F;
            prim->drawMode |= DRAW_COLORS;
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x40;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x40;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x60;

            PlaySfx(REBOUND_STONE_BOUNCE);
            self->step++;
        }
        break;
    case 6:
        self->ext.stopwatch.t += 1;
        if (self->ext.stopwatch.t > 14) {
            CreateEntFactoryFromEntity(self, FACTORY(0xE00, 4), 0);
        label:
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

            a = (self->ext.stopwatch.unk82 * 8) / 100;
            b = (self->ext.stopwatch.unk82 * 12) / 100;
            c = rsin(self->ext.stopwatch.unk80);
            d = rcos(self->ext.stopwatch.unk80);
            prim->x0 = (x + (((d * -a) - (c * -b)) >> 0xC));
            prim->y0 = (y + (((c * -a) + (d * -b)) >> 0xC));
            prim->x1 = (x + (((d * a) - (c * -b)) >> 0xC));
            prim->y1 = (y + (((c * a) + (d * -b)) >> 0xC));
            prim->x2 = (x + (((d * -a) - (c * b)) >> 0xC));
            prim->y2 = (y + (((c * -a) + (d * b)) >> 0xC));
            prim->x3 = (x + (((d * a) - (c * b)) >> 0xC));
            prim->y3 = (y + (((c * a) + (d * b)) >> 0xC));
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
                x = (self->facingLeft ? -10 : 4) + self->posX.i.hi;

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

                x = (self->facingLeft ? -4 : 10) + self->posX.i.hi;
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

            x = (self->facingLeft ? -4 : 4) + self->posX.i.hi;
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

void func_8012B78C(Entity* entity) {
    Primitive* prim;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = AllocPrimitives(PRIM_GT4, 1);
        entity->primIndex = ret;
        if (entity->primIndex != -1) {
            entity->flags = FLAG_UNK_20000 | FLAG_UNK_04000000 | FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[entity->primIndex];
            prim->tpage = 0x1C;
            prim->clut = 0x19D;
            prim->u0 = prim->u2 = 32;
            prim->u1 = prim->u3 = 48;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 16;
            prim->x0 = prim->x2 = entity->posX.i.hi - 8;
            prim->x1 = prim->x3 = entity->posX.i.hi + 8;
            prim->y0 = prim->y1 = entity->posY.i.hi - 8;
            prim->y2 = prim->y3 = entity->posY.i.hi + 8;
            prim->priority = entity->zPriority;
            prim->drawMode =
                DRAW_UNK_100 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            entity->ext.generic.unk7E.modeU16 = 96;
            entity->step++;
        } else {
            DestroyEntity(entity);
            return;
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s > 5) {
            entity->step++;
        }
        entity->ext.generic.unk7E.modeU16 -= 8;
        break;

    case 2:
        DestroyEntity(entity);
        return;

    default:
        break;
    }
    prim = &g_PrimBuf[entity->primIndex];
    prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 = prim->g2 =
        prim->g3 = prim->b0 = prim->b1 = prim->b2 = prim->b3 =
            entity->ext.generic.unk7E.modeU8.unk0;
}

// book rotates around player
void EntitySubwpnBible(Entity* self) {
    Primitive* prim;
    s16 left;
    s16 top;
    s16 bottom;
    s16 right;

    s32 sine;
    s32 cosine;
    s32 cos_s2;
    s32 sin_s3;
    s32 cos_s3;
    s32 sin_s2;

    s32 temp_a3;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_a1;

    s32 temp_v0;

    s32 var_s4;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_UNK_04000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        prim->tpage = 0x1E;
        prim->clut = 0x17F;
        prim->u0 = prim->u2 = 0x98;
        prim->v0 = prim->v1 = 0xD8;
        prim->u1 = prim->u3 = 0xA8;
        prim->v2 = prim->v3 = 0xF0;
        prim->priority = PLAYER.zPriority + 1;
        prim->drawMode = DRAW_UNK_100 | DRAW_HIDE;
        self->ext.et_BibleSubwpn.unk84 = self->facingLeft ? 0x20 : -0x20;
        func_8011A290(self);
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->step++;
        break;
    case 1:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode &= ~DRAW_HIDE;
        self->ext.et_BibleSubwpn.unk86++;
        g_Player.D_80072F00[10] = 4;
        self->step++;
    case 2:
        self->ext.et_BibleSubwpn.unk7C++;
        if (++self->ext.et_BibleSubwpn.unk7E >= 0x30) {
            self->step++;
        }
        break;
    case 3:
        if (++self->ext.et_BibleSubwpn.unk7C >= 0x12C) {
            self->flags &= ~FLAG_UNK_04000000;
            self->velocityX = self->facingLeft ? FIX(-12) : FIX(12);
            self->velocityY = FIX(-12);
            PlaySfx(SFX_UNK_6B2);
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
        temp_s2 = (sine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        temp_s3 = (cosine * self->ext.et_BibleSubwpn.unk7E) >> 0xC;
        cos_s2 = cosine * temp_s2;
        sin_s3 = sine * temp_s3;
        cos_s3 = cosine * temp_s3;
        temp_a1 = cos_s2 + sin_s3;
        sin_s2 = sine * temp_s2;
        temp_s2 = temp_a1 >> 0xC;
        temp_s3 = (cos_s3 - sin_s2) >> 0xC;
        sine = rsin(self->ext.et_BibleSubwpn.unk82);
        cosine = rcos(self->ext.et_BibleSubwpn.unk82);
        temp_a1 = ((cosine * temp_s2) + (sine * var_s4)) >> 0xC;
        temp_a3 = ((cosine * var_s4) - (sine * temp_s2)) >> 0xC;
        if (self->facingLeft != 0) {
            temp_a3 = ((cosine * temp_a3) + (sine * temp_s3)) >> 0xC;
        } else {
            temp_a3 = ((cosine * temp_a3) - (sine * temp_s3)) >> 0xC;
        }

        self->ext.et_BibleSubwpn.unk80 += (self->facingLeft ? 0x80 : -0x80);
        self->ext.et_BibleSubwpn.unk80 &= 0xFFF;
        self->ext.et_BibleSubwpn.unk82 += self->ext.et_BibleSubwpn.unk84;
        if (abs(self->ext.et_BibleSubwpn.unk82) >= 0x200) {
            // temp_v0 needed because otherwise unk84 gets loaded with lhu
            // instead of lh
            temp_v0 = -self->ext.et_BibleSubwpn.unk84;
            self->ext.et_BibleSubwpn.unk84 = temp_v0;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + temp_a1;
        self->posY.i.hi = PLAYER.posY.i.hi + temp_a3;
        self->zPriority = PLAYER.zPriority + (temp_s3 < 0 ? 2 : -2);
        break;
    case 2:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityY += FIX(-2);
        break;
    }
    if (self->ext.et_BibleSubwpn.unk86 != 0) {
        prim = &g_PrimBuf[self->primIndex];
        left = self->posX.i.hi - 8;
        right = self->posX.i.hi + 8;
        top = self->posY.i.hi - 12;
        bottom = self->posY.i.hi + 12;
        prim->x0 = prim->x2 = left;
        prim->x1 = prim->x3 = right;
        prim->y0 = prim->y1 = top;
        prim->y2 = prim->y3 = bottom;
        prim->priority = self->zPriority;
        CreateEntFactoryFromEntity(self, FACTORY(0, 79), 0);
        if (g_GameTimer % 10 == 0) {
            PlaySfx(BIBLE_SUBWPN_SWOOSH);
        }
    }
}

// echo of bat effect
void EntityBatEcho(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    Primitive* prim;
    Primitive* temp;
    Unkstruct_8012BEF8* unkstruct;
    s32 i;
    s16 temp_unk7E;
    s32 var_s5;
    s32 var_s6;
    s32 temp_s7;
    s32 posX, posY;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if ((self->ext.batEcho.unk8A % 384) == 0) {
        PlaySfx(SFX_BAT_ECHO_B);
    }
    self->ext.batEcho.unk8A += 1;
    if (self->ext.batEcho.unk88) {
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        self->primIndex = g_api.AllocPrimitives(PRIM_G4, 0x31);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000;
        prim = (Primitive*)&g_PrimBuf[self->primIndex];
        self->ext.batEcho.unk84 = prim;
        for (i = 0; i < 0x11; i++) {
            prim->type = 1;
            prim->drawMode = DRAW_HIDE;
            prim->y2 = D_800B0884[i];
            prim->x2 = (i * 3) + 1;
            prim->y3 = D_800B08A8[i];
            prim->x3 = (i << 0xA) & 0xFFF;
            prim->x1 = (i << 7) & 0xFFF;
            prim = prim->next;
        }
        for (i = 0; i < 0x20; i++) {
            prim->drawMode = DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_TRANSP;
            prim->priority = PLAYER.zPriority - 2;
            prim = prim->next;
        }
        self->ext.batEcho.unk80 = 0xA0;
        if (IsRelicActive(RELIC_FORCE_OF_ECHO)) {
            self->ext.batEcho.unk80 = 0x100;
            self->hitboxOffX = 0x40;
            self->hitboxOffY = -4;
            self->hitboxWidth = 0x28;
            self->hitboxHeight = 0xC;
            func_8011A328(self, 0xA);
        }
        self->step += 1;
        break;
    case 1:
        self->ext.batEcho.unk7E += 0xA;
        if (self->ext.batEcho.unk7E > self->ext.batEcho.unk80) {
            self->ext.batEcho.unk7E = self->ext.batEcho.unk80;
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 2:
        self->ext.batEcho.unk7E -= 0xA;
        if (self->ext.batEcho.unk7E < 0) {
            self->ext.batEcho.unk7E = 0;
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        prim = self->ext.batEcho.unk84;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.batEcho.unk88) {
            DestroyEntity(self);
        }
        return;
    }

    prim = self->ext.batEcho.unk84;
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));
    for (i = 0; i < 0x11; i++, unkstruct++) {
        prim->x3 += 0x100;
        unkstruct->unk4 = prim->x3;
        prim->x1 -= 0x40;
        unkstruct->unk6 = prim->x1;
        unkstruct->unk8 = prim->x2;
        unkstruct->unkA = prim->y2;
        unkstruct->unkC = prim->y3;
        unkstruct->unk10 = rcos(unkstruct->unk6) >> 6;
        unkstruct->unk14 = rcos(unkstruct->unk6 + 0x100) >> 6;
        unkstruct->unk18 = rsin(unkstruct->unk4) >> 4;
        prim = prim->next;
    }

    temp = (Primitive*)SP(0);
    posX = PLAYER.posX.i.hi;
    posY = PLAYER.posY.i.hi;
    if (self->facingLeft) {
        var_s5 = posX - 16;
    } else {
        var_s5 = posX + 16;
    }

    temp_s7 = (((rsin(PLAYER.rotZ) >> 4) * 0xA) >> 8) - 6;
    temp_s7 = posY + temp_s7;
    temp_unk7E = self->ext.batEcho.unk7E;
    unkstruct = (Unkstruct_8012BEF8*)SP(sizeof(Primitive));

    temp->x3 = temp->x1 = var_s5;
    temp->y1 = temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
    temp->y3 = temp->y1 - unkstruct->unk8;

    temp->r1 =
        (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->g1 =
        (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
    temp->b1 =
        (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

    var_s6 = temp->y1 + unkstruct->unk8;
    unkstruct++;
    for (i = 0; i < 0x10; i++, unkstruct++) {
        if (self->facingLeft) {
            var_s5 -= 8;
        } else {
            var_s5 += 8;
        }
        *(s32*)&prim->x0 = *(s32*)&temp->x0 = *(s32*)&temp->x1;
        *(s32*)&prim->x2 = *(s32*)&temp->x2 = *(s32*)&temp->x3;
        prim->x3 = prim->x1 = temp->x3 = temp->x1 = var_s5;
        prim->y1 = temp->y1 =
            temp_s7 + ((unkstruct->unk18 * unkstruct->unkA) >> 9);
        prim->y3 = temp->y3 = temp->y1 - unkstruct->unk8;

        *(s32*)&prim->r0 = *(s32*)&temp->r0 = *(s32*)&temp->r1;

        prim->r1 = temp->r1 =
            (unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->g1 = temp->g1 =
            (unkstruct->unk14 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);
        prim->b1 = temp->b1 =
            (-unkstruct->unk10 + 0x41) * unkstruct->unkC * temp_unk7E / FIX(1);

        prim->type = 3;
        prim = prim->next;
        *(s32*)&prim->x0 = *(s32*)&temp->x0;
        *(s32*)&prim->x1 = *(s32*)&temp->x1;
        *(s32*)&prim->x2 = *(s32*)&temp->x2;
        *(s32*)&prim->x3 = *(s32*)&temp->x3;
        *(s32*)&prim->r0 = *(s32*)&temp->r0;
        *(s32*)&prim->r1 = *(s32*)&temp->r1;
        prim->y2 = var_s6;
        var_s6 = temp->y1 + unkstruct->unk8;
        prim->y3 = var_s6;
        prim->type = 3;
        prim = prim->next;
    }
}

void func_8012C600(void) {
    s32 x, y;
    s32 i;
    s32 t0 = PLAYER.posX.i.hi;
    s32 t1 = PLAYER.posY.i.hi;

    x = g_Entities[20].posX.i.hi + 8;
    for (i = 0; i < 9; i++) {
        if (x <= g_Entities[i + 21].posX.i.hi + 4) {
            x = g_Entities[i + 21].posX.i.hi + 4;
        }
    }
    D_8013AEBC[0] = x - t0;

    x = g_Entities[20].posX.i.hi - 8;
    for (i = 0; i < 9; i++) {
        if (x >= g_Entities[i + 21].posX.i.hi - 4) {
            x = g_Entities[i + 21].posX.i.hi - 4;
        }
    }
    D_8013AEBC[2] = x - t0;

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y >= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y - 4;
    if (y >= g_Entities[30].posY.i.hi - 12) {
        y = g_Entities[30].posY.i.hi - 12;
    }
    if (y >= g_Entities[20].posY.i.hi - 8) {
        y = g_Entities[20].posY.i.hi - 8;
    }
    D_8013AEBC[3] = y - t1;
    if (D_8013AEBC[3] < -24) {
        D_8013AEBC[3] = -24;
    }

    y = g_Entities[21].posY.i.hi;
    for (i = 0; i < 9; i++) {
        if (y <= g_Entities[i + 21].posY.i.hi) {
            y = g_Entities[i + 21].posY.i.hi;
        }
    }
    y = y + 4;

    if (y <= PLAYER.posY.i.hi + 28) {
        y = PLAYER.posY.i.hi + 28;
    }
    if (y <= g_Entities[17].posY.i.hi + 28) {
        y = g_Entities[17].posY.i.hi + 28;
    }
    D_8013AEBC[1] = y - t1;
    if (D_8013AEBC[1] > 0x27) {
        D_8013AEBC[1] = 0x27;
    }

    if (!PLAYER.facingLeft) {
        if (D_8013AEBC[2] < -0x2C) {
            D_8013AEBC[2] = -0x2C;
        }
        if (D_8013AEBC[0] > 0x14) {
            D_8013AEBC[0] = 0x14;
        }
    } else {
        if (D_8013AEBC[2] < -0x14) {
            D_8013AEBC[2] = -0x14;
        }
        if (D_8013AEBC[0] > 0x2C) {
            D_8013AEBC[0] = 0x2C;
        }
    }
}

bool WolfFormFinished(void) {
    if (PLAYER.step_s == 0) {
        return false;
    }
    if (PLAYER.step_s == 8) {
        return false;
    }
    if (D_80097448[1] != 0 && !IsRelicActive(RELIC_HOLY_SYMBOL) ||
        g_Player.padTapped & PAD_R2 ||
        HandleTransformationMP(FORM_WOLF, REDUCE) < 0) {
        SetPlayerStep(Player_UnmorphWolf);
        SetPlayerAnim(0xCA);
        D_800AFDA4[1] = 1;
        PLAYER.palette = 0x810D;
        g_Player.unk66 = 0;
        g_Player.unk68 = 0;
        // Create factory for EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x2400, 44), 0);
        PLAYER.velocityY >>= 1;
        return true;
    }
    return false;
}

void func_8012C97C(void) {
    if (g_Entities[PLAYER_CHARACTER].step_s == 0) {
        return;
    }
    if (g_Entities[PLAYER_CHARACTER].step_s >= 8 &&
        g_Entities[PLAYER_CHARACTER].step_s < 10) {
        return;
    }
    if (D_80097448[1] < 13) {
        return;
    }
    if (!IsRelicActive(RELIC_HOLY_SYMBOL)) {
        return;
    }
    if (!IsRelicActive(RELIC_SKILL_OF_WOLF)) {
        return;
    }
    if (g_Player.pl_vram_flag & 1) {
        return;
    }
    if (!(g_Player.padPressed & PAD_TRIANGLE)) {
        return;
    }
    if (D_80138440 != 0) {
        return;
    }

    PLAYER.step_s = 9;
    D_800B0914 = 0;
    SetPlayerAnim(0xEC);
    PLAYER.velocityY = 0;
}

void func_8012CA64(void) {
    u8 anim;

    PLAYER.step_s = 1;
    D_800B0914 = 0;

    anim = 0xDE;
    if (g_Player.pl_vram_flag & 0x20) {
        anim = 0xDF;
    }
    SetPlayerAnim(anim);

    PLAYER.velocityY = 0;
    PLAYER.velocityX /= 2;

    D_800B0918 = 0x200;
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012CB0C(void) {
    PLAYER.ext.player.anim = 0xDE;
    PLAYER.velocityY = 0;
    D_800B0914 = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.animFrameDuration = 0;
    PLAYER.step_s = 7;
}

void func_8012CB4C(void) {
    PLAYER.step_s = 2;
    if ((PLAYER.facingLeft != 0 && g_Player.padPressed & PAD_RIGHT) ||
        (PLAYER.facingLeft == 0 && g_Player.padPressed & PAD_LEFT)) {
        SetPlayerAnim(0xE1);
        D_800B0914 = 0;
        D_8013842C = 0;
        return;
    } else if (D_8013842C != 0) {
        SetPlayerAnim(0xE2);
        D_800B0914 = 2;
        SetSpeedX(0x20000);
        return;
    } else {
        SetPlayerAnim(0xE0);
        D_800B0914 = 1;
        D_8013842C = 0xC;
    }
}

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if (g_ButtonCombo[COMBO_QCF].buttonsCorrect == COMBO_COMPLETE &&
            IsRelicActive(RELIC_SKILL_OF_WOLF) &&
            CastSpell(SPELL_WOLF_CHARGE)) {
            CheckMoveDirection();
            PLAYER.step_s = 2;
            D_800B0914 = 4;
            SetSpeedX(0x50000);
            g_CurrentEntity->velocityY = 0;
            SetPlayerAnim(0xED);
            LearnSpell(4);
        }
    } else {
        D_80138444 = 1;
    }
}

void func_8012CCE4(void) {
    PLAYER.velocityY = FIX(-3.5);
    if ((PLAYER.step_s == 2) & (D_800B0914 == 2)) {
        SetPlayerAnim(0xE7);
        // Might be possible to rewrite this block to reduce duplication with
        // some clever && and ||
        if (PLAYER.facingLeft) {
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        } else {
            if ((g_Player.pl_vram_flag & 0xF000) == 0x8000) {
                PLAYER.velocityY = -(abs(PLAYER.velocityX) + FIX(3.5));
            }
            if ((g_Player.pl_vram_flag & 0xF000) == 0xC000) {
                PLAYER.velocityY = FIX(-0.5);
            }
        }
        D_800B0914 = 2;
    } else if (
        (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) &&
        ((PLAYER.step_s != 2) || (D_800B0914 != 0)) && (PLAYER.step_s != 9)) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    } else {
        SetPlayerAnim(0xE6);
        D_800B0914 = 0;
        if (g_Player.padPressed & PAD_UP) {
            PLAYER.velocityY = FIX(-4.875);
        }
    }
    PLAYER.step_s = 4;
    D_80138430 += 0x80;
}

void func_8012CED4(void) {
    if (PLAYER.step_s == 2 && D_800B0914 == PLAYER.step_s) {
        SetPlayerAnim(0xE7);
        D_800B0914 = 1;
    } else {
        SetPlayerAnim(0xE8);
        SetSpeedX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animFrameIdx = 4;
            PLAYER.velocityX = 0;
            PLAYER.animFrameDuration = 1;
        }
    }
    PLAYER.step_s = 5;
    g_Player.D_80072F00[5] = 8;
    PLAYER.velocityY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    SetPlayerAnim(0xEA);
    PLAYER.step_s = 6;
    D_800B0914 = 0;
    PLAYER.velocityX = 0;
    g_Player.D_80072F00[5] = 8;
}

void func_8012CFF0(void) {
    PLAYER.step_s = 3;
    SetPlayerAnim(0xE3);
    D_800B0914 = 0;
}

void func_8012D024(void) {
    DecelerateX(0x2000);
    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
        return;
    }
    if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CED4();
        return;
    }
    if (g_Player.padTapped & PAD_SQUARE) {
        func_8012CC30(0);
        return;
    }
    if (g_Player.padPressed & (PAD_RIGHT | PAD_LEFT)) {
        func_8012CB4C();
        return;
    }
    if (g_Player.padPressed & PAD_DOWN) {
        func_8012CFF0();
        return;
    }
    if (D_800B0914 != 0) {
        return;
    }
    if (abs(PLAYER.posY.i.hi - g_Entities[17].posY.i.hi) < 4 &&
        --D_800B0918 == 0) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
        return;
    }
    if (g_Player.pl_vram_flag & 0x40) {
        D_800B0914 = 1;
        SetPlayerAnim(0xE9);
    }
}

void func_8012D178(void) {
    s32 var_v0;

    if (g_Player.padTapped & PAD_CROSS) {
        func_8012CCE4();
    } else if (!(g_Player.pl_vram_flag & 1)) {
        func_8012CFA8();
    } else {
#if defined(VERSION_US)
        if (PLAYER.facingLeft != 0) {
            var_v0 = g_Player.padPressed & PAD_LEFT;
        } else {
            var_v0 = g_Player.padPressed & PAD_RIGHT;
        }
#elif defined(VERSION_HD)
        var_v0 = g_Player.padPressed & (PAD_LEFT | PAD_RIGHT);
#endif
        if (var_v0 != 0) {
            func_8012CB4C();
        } else if (g_Player.unk04 & 0x40) {
            func_8012CA64();
        } else if (g_GameTimer % 6 == 0) {
            CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x100, 69), 0);
        }
    }
}

void func_8012D28C(bool exitEarly) {
    bool bitNotFound;
    s32 i;

    func_80102CD8(2);
    PlaySfx(SFX_WALL_DEBRIS_B);
    PLAYER.velocityX = 0;
    g_Player.D_80072EFC = 0x20;
    g_Player.padSim = 0;
    // Odd logic, if we exit early, we force an R2-tap. Strange!
    if (exitEarly) {
        g_Player.padTapped = PAD_R2;
        WolfFormFinished();
        return;
    }
    // Start a routine where we look through this array for a value.
    bitNotFound = 0;
    for (i = 3; i < 7; i++) {
        if (g_Player.colliders3[i].effects & EFFECT_UNK_0002) {
            break;
        }
    }
    // If we made it through that loop without finding one, skip i=7,8,9
    // and keep searching.
    if (i == 7) {
        for (i = 10; i < 14; i++) {
            if (g_Player.colliders3[i].effects & EFFECT_UNK_0002) {
                break;
            }
        }
    }
    // If we even made it through that one, then conclude the bit was not found.
    if (i == 14) {
        bitNotFound++;
    }

    SetSpeedX(FIX(1));
    CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(0x900, 4), 0);
    D_800B0914 = 0;
    // Finally make use of that bit to control if X is positive or negative.
    if (bitNotFound) {
        func_8012CED4();
        SetSpeedX(FIX(1));
    } else {
        func_8012CFA8();
        SetSpeedX(FIX(-1));
    }
    PLAYER.velocityY = FIX(-3.5);
}
