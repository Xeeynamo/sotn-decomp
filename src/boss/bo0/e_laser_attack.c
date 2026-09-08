// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

Primitive* FindFirstUnkPrim(Primitive* prim);
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

static void func_us_801B8794(Primitive* prim) {
    switch (prim->p1) {
    case 0:
        prim->type = PRIM_LINE_G2;
        prim->x0 = prim->x1 = Random() & 0x3F;
        prim->y0 = 0x100;
        prim->y1 = (Random() & 0x1F) + 0x120;
        prim->y2 = (Random() & 0xF) + 0x10;
        prim->r0 = 0;
        prim->g0 = 0xFF;
        prim->b0 = 0xFF;
        prim->r1 = 0;
        prim->g1 = 0xFF;
        prim->b1 = 0xFF;
        prim->priority = 0xC8;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
        prim->p1++;
        // fallthrough

    case 1:
        prim->y0 -= prim->y2;
        prim->y1 -= prim->y2;
        if (prim->y1 < 0x40) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        break;
    }
}

static void func_us_801B888C(Primitive* prim) {
    switch (prim->p1) {
    case 0:
        prim->type = PRIM_GT4;
        prim->tpage = 0x1A;
        prim->clut = 0x194;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x20;
        prim->v0 = prim->v1 = 0x60;
        prim->v2 = prim->v3 = 0x80;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0x40;
        prim->y0 = prim->y1 = 0x100;
        prim->y2 = prim->y3 = 0x100;
        prim->priority = 0xC8;
        prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->p1++;
        // fallthrough

    case 1:
        prim->y0 = prim->y1 -= 16;
        if (prim->y0 == 64) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        return;
    }
}

static void func_us_801B8970(Primitive* prim) {
    switch (prim->next->u2) {
    case 0:
        prim->type = PRIM_G4;
        prim->priority = 0xCE;
        prim->drawMode = DRAW_UNK02;
        prim->p3 |= 0x30;
        LOW(prim->next->r1) = ((Random() & 0xF) * -0x2000) - 0x2000;
        prim->next->b3 = 0;
        LOH(prim->next->r2) = (Random() & 7) + 4;
        LOH(prim->next->b2) = (Random() & 7) + 4;
        prim->next->x2 = 0x1000;
        prim->next->y2 = 0x1000;
        prim->next->tpage = 0;
        prim->next->x3 = 0;
        prim->next->y3 = 0;
        prim->next->u2 = 1;
        break;

    case 1:
        prim->next->y3 += (((Random() & 3) + 2) << 6);
        prim->next->x3 += 0x40;
        LOH(prim->next->tpage) += 0x40;
        prim->next->x2 -= 0x20;
        prim->next->y2 = prim->next->x2;
        if (prim->next->x2 < 0xC00) {
            prim->next->b3 = (u8)((s32)(0xFFF - prim->next->x2) >> 4);
        }
        if (prim->next->x2 < 0x100) {
            UnkPolyFunc0(prim);
            return;
        }
        break;
    }

    UnkPrimHelper(prim);
    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
}

void func_us_801B8B64(Primitive* prim) {
    switch (prim->next->u2) {
    case 0:
        prim->type = PRIM_G4;
        prim->priority = 0xAE;
        prim->drawMode = DRAW_UNK02;
        prim->p3 |= 0x30;
        LOW(prim->next->r1) = (((Random() & 0xF) * -0x4000) - 0x2000);
        prim->next->b3 = 0;
        LOH(prim->next->r2) = (Random() & 7) + 6;
        LOH(prim->next->b2) = (Random() & 7) + 6;
        prim->next->x2 = 0x1000;
        prim->next->y2 = 0x1000;
        prim->next->tpage = 0;
        prim->next->x3 = 0;
        prim->next->y3 = 0;
        prim->next->u2 = 1;
        break;

    case 1:
        LOW(prim->next->r1) -= 0x4000;
        prim->next->y3 += ((Random() & 3) + 2) << 6;
        prim->next->x3 += 0x40;
        LOH(prim->next->tpage) += 0x40;
        prim->next->x2 -= 0x40;
        prim->next->y2 = prim->next->x2;

        prim->next->b3 = (prim->next->x2 >> 4) / 2;
        if (prim->next->x2 < 0x100) {
            UnkPolyFunc0(prim);
            return;
        }
        break;
    }

    UnkPrimHelper(prim);
    prim->r0 = prim->r1 = prim->r2 / 2;
    prim->g0 = prim->g1 = prim->g2 / 2;
    prim->b0 = prim->b1 = prim->b2 / 2;
}

extern EInit g_EInitLaserAttack;

void EntityLaserAttack(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* entity;
    Entity* child;
    s16 angle;
    s32 i;
    s16 x1;
    s16 x0;
    RECT rect;
    DRAWENV draw;
    DR_ENV* drEnv;
    s16 hitboxOffX;
    s16 hitboxOffY;
    s16 y0;
    s16 offsetX;
    s16 offsetY;

    entity = self->ext.olroxLaser.next;
    if (entity->flags & FLAG_DEAD) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitLaserAttack);
        self->hitboxHeight = 0x38;
        self->hitboxOffY = -0x38;
        primIndex = g_api.func_800EDB58(4, 0x30);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxLaser.prim1 = prim;
            prim->type = PRIM_GT3;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->u0 = 0x10;
            prim->u1 = 0x10;
            prim->u2 = 0x14;
            prim->v0 = 0x10;
            prim->v1 = 0x14;
            prim->v2 = 0x14;
            prim->r0 = 0x60;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            prim->r1 = 0x80;
            prim->g1 = 0x80;
            prim->b1 = 0x60;
            prim->r2 = 0;
            prim->g2 = 0;
            prim->b2 = 0;
            prim->priority = 0x9E;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;

            prim = prim->next;
            self->ext.olroxLaser.prim2 = prim;
            prim->type = PRIM_G4;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->u0 = prim->u2 = 0xE8;
            prim->u1 = prim->u3 = 0xF8;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0x86;
            prim->r0 = 0;
            prim->g0 = 0;
            prim->b0 = 0;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            prim->r2 = 0x80;
            prim->g2 = 0x80;
            prim->b2 = 0x30;
            LOW(prim->r3) = LOW(prim->r2);
            prim->priority = 0x9E;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            self->ext.olroxLaser.prim3 = prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
        }

        entity = self->ext.olroxLaser.next;
        angle = ROT(180) - (entity->rotate - ROT(22.5));
        if (self->facingLeft) {
            angle = ROT(180) - angle;
        }
        self->posX.i.hi += FLT_TO_I(rcos(angle) * 16);
        self->posY.i.hi += FLT_TO_I(rsin(angle) * -16);
        PlaySfxPositional(SFX_OLROX_LASER_ATTACK);
        break;

    case 1:
        entity = self->ext.olroxLaser.next;
        angle = ROT(180) - (entity->rotate - ROT(22.5));
        if (self->facingLeft) {
            angle = ROT(180) - angle;
        }
        self->velocityX = FLT_TO_FIX(rcos(angle) * 8);
        self->velocityY = FLT_TO_FIX(rsin(angle) * -8);
        prim = self->ext.olroxLaser.prim1;
        prim->x0 = prim->x1 = prim->x2 = self->posX.i.hi;
        prim->y0 = prim->y1 = prim->y2 = self->posY.i.hi;
        self->step++;
        break;

    case 2:
        MoveEntity();
        offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;

        if (self->facingLeft) {
            offsetX = 0x200 - offsetX;
        }
        if (offsetX < 0x30) {
            entity = self->ext.olroxLaser.next;
            entity->ext.olroxLaser.unkA9 = 0;
            DestroyEntity(self);
            return;
        }
        if (offsetY > 0x1D0) {
            self->posY.i.hi = 0x1D0 - g_Tilemap.scrollY.i.hi;
            self->ext.olroxLaser.timer9C = 0x20;
            self->step++;

            prim = self->ext.olroxLaser.prim2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->y2 = prim->y3 = self->posY.i.hi;
            prim->y0 = prim->y1 = prim->y3 - 8;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = prim->x0;
        }
        prim = self->ext.olroxLaser.prim1;
        prim->x1 = prim->x2 = self->posX.i.hi;
        prim->y1 = prim->y2 = self->posY.i.hi;
        prim->x2 += 2;
        break;
    case 3:
        if (!(g_Timer & 0xF)) {
            g_api.PlaySfx(SFX_BAT_ECHO_B);
        }
        prim = self->ext.olroxLaser.prim1;
        if (self->params ^ self->facingLeft) {
            prim->x1 += 2;
        } else {
            prim->x1 -= 2;
        }
        entity = self->ext.olroxLaser.next;
        prim->x0 = entity->posX.i.hi;
        prim->y0 = entity->posY.i.hi;
        angle = ROT(180) - (entity->rotate - ROT(22.5));
        if (self->facingLeft) {
            angle = ROT(180) - angle;
        }
        prim->x0 += FLT_TO_I(rcos(angle) * 16);
        prim->y0 += FLT_TO_I(rsin(angle) * -16);
        hitboxOffX = prim->x0 - prim->x1;
        hitboxOffY = prim->y0 - prim->y1;
        angle = -ratan2(-hitboxOffY, hitboxOffX);
        if (!self->facingLeft) {
            entity->rotate = angle + ROT(22.5);
        } else {
            entity->rotate = -angle - ROT(157.5);
        }
        if (self->ext.olroxLaser.timer9C < 16) {
            if (self->params ^ self->facingLeft) {
                prim->x2 += 2;
            } else {
                prim->x2 -= 2;
            }
        }

        hitboxOffX = prim->x1;
        prim = self->ext.olroxLaser.prim2;
        prim->x0 = prim->x2 = hitboxOffX;
        if (g_Timer & 1) {
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        } else {
            prim->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        }
        hitboxOffX = g_Tilemap.scrollX.i.hi + hitboxOffX;
        if (hitboxOffX < 0x30 || hitboxOffX > 0x1D0) {
            self->ext.olroxLaser.timer9C = 1;
        }

        if (!--self->ext.olroxLaser.timer9C) {
            prim = self->ext.olroxLaser.prim1;
            self->posX.i.hi = prim->x0;
            self->posY.i.hi = prim->y0;
            angle = ROT(180) - angle;
            self->velocityX = FLT_TO_FIX(rcos(angle) * 8);
            self->velocityY = FLT_TO_FIX(rsin(angle) * -8);
            self->step++;
        }
        break;

    case 4:
        prim = self->ext.olroxLaser.prim1;
        if (prim->x2 != prim->x1) {
            if (self->params ^ self->facingLeft) {
                prim->x2 += 2;
            } else {
                prim->x2 -= 2;
            }
        }
        MoveEntity();

        offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        if (offsetY > 0x1D0) {
            prim->drawMode = DRAW_HIDE;
            self->posY.i.hi = 0x1D0 - g_Tilemap.scrollY.i.hi;
            self->ext.olroxLaser.timer9C = 0x20;
            self->step++;
        }
        prim = self->ext.olroxLaser.prim1;
        prim->x0 = self->posX.i.hi;
        prim->y0 = self->posY.i.hi;
        break;

    case 5:
        prim = self->ext.olroxLaser.prim2;
        prim->y1 = prim->y0 += 1;
        if (prim->y0 >= prim->y2) {
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            g_api.func_800EA5AC(1U, 0xD0U, 0xC0U, 0xC0U);
            g_api.func_80102CD8(1);
            g_api.PlaySfx(SFX_FIREBALL_SHOT_A);
            self->step++;
        }
        break;
    case 6:
        prim = self->ext.olroxLaser.prim2;
        x1 = prim->x0;
        x0 = prim->x1;
        y0 = prim->y0;
        self->posX.i.hi = x1;
        self->ext.olroxLaser.hitboxOffX = x0 - x1;
        hitboxOffX = (x0 - x1) / 16;
        prim->drawMode = DRAW_HIDE;

        prim = self->ext.olroxLaser.prim1;
        prim->type = PRIM_GT4;
        prim->tpage = 0x110;
        if (self->params & 1) {
            prim->u0 = prim->u2 = 0x40;
            prim->u1 = prim->u3 = 0x7F;
        } else {
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x3F;
        }
        prim->v0 = prim->v1 = 0x40;
        prim->v2 = prim->v3 = 0xFF;
        prim->x0 = prim->x2 = x1;
        prim->x1 = prim->x3 = x0;
        prim->y0 = prim->y1 = y0 - 0xC0;
        prim->y2 = prim->y3 = y0;
        prim->priority = 0xCC;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;

        prim = prim->next;
        self->ext.olroxLaser.prim4 = prim;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (!drEnv) {
            DestroyEntity(self);
            return;
        }

        prim->type = PRIM_ENV;
        draw = g_CurrentBuffer->draw;
        draw.r0 = 0;
        draw.g0 = 0;
        draw.b0 = 0;
        draw.isbg = 1;
        if (self->params & 1) {
            rect.x = 0x40;
        } else {
            rect.x = 0;
        }
        rect.y = 0x100;
        rect.w = 0x40;
        rect.h = 0x100;
        draw.clip = rect;
        if (self->params & 1) {
            draw.ofs[0] = 0x40;
        } else {
            draw.ofs[0] = 0;
        }
        draw.ofs[1] = 0x100;
        SetDrawEnv(drEnv, &draw);
        prim->priority = 0xC7;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        drEnv = g_api.func_800EDB08((POLY_GT4*)prim);
        if (!drEnv) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0xC9;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        self->ext.olroxLaser.prim6 = prim;
        for (i = 0; i < 16; i++) {
            prim->type = PRIM_LINE_G2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.olroxLaser.prim5 = prim;
        for (i = 0; i < 8; i++) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        };
        self->ext.olroxLaser.prim3 = prim;
        self->ext.olroxLaser.timer9C = 1;
        self->ext.olroxLaser.timer9E = 1;
        self->ext.olroxLaser.timer = 0x40;
        self->hitboxState = 1;
        hitboxOffX = self->ext.olroxLaser.hitboxOffX / 2;
        if (!self->facingLeft) {
            self->hitboxOffX = hitboxOffX;
        } else {
            self->hitboxOffX = -hitboxOffX;
        }
        hitboxOffX = abs(hitboxOffX);
        if (hitboxOffX > 8) {
            self->hitboxWidth = hitboxOffX - 8;
        }
        entity = self->ext.olroxLaser.next;
        entity->ext.olroxLaser.unkA9 = 0;
        child = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (child != NULL) {
            CreateEntityFromEntity(E_ID(LASER_EXPLOSION), self, child);
            child->posX.i.hi += self->ext.olroxLaser.hitboxOffX / 2;
            child->posY.i.hi -= 0x10;
            child->params = 0;
        }
        self->step++;
        break;

    case 7:
        prim = self->ext.olroxLaser.prim6;
        prim = FindFirstUnkPrim(prim);
        if ((intptr_t)prim < (intptr_t)self->ext.olroxLaser.prim5) {
            prim->p3 = 4;
            prim->p1 = 0;
        }
        prim = self->ext.olroxLaser.prim6;
        for (i = 0; i < 16; i++) {
            if (prim->p3 & 4) {
                func_us_801B8794(prim);
            }
            prim = prim->next;
        }

        if (!--self->ext.olroxLaser.timer9C) {
            self->ext.olroxLaser.timer9C = 2;
            prim = self->ext.olroxLaser.prim5;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p3 = 4;
                prim->p1 = 0;
            }
        }
        prim = self->ext.olroxLaser.prim5;
        for (i = 0; i < 8; i++) {
            if (prim->p3 & 4) {
                func_us_801B888C(prim);
            }
            prim = prim->next;
        }

        if (!--self->ext.olroxLaser.timer9E) {
            self->ext.olroxLaser.timer9E = 12;
            x0 = self->posX.i.hi;
            x1 = x0 + self->ext.olroxLaser.hitboxOffX;
            hitboxOffX = (x0 - x1) / 16;

            prim = self->ext.olroxLaser.prim3;
            prim = FindFirstUnkPrim2(prim, 2);
            if (prim != NULL) {
                UnkPolyFunc2(prim);
                prim->next->x1 = (hitboxOffX * (Random() & 0xF)) + x1;
                prim->next->y0 = self->posY.i.hi;
            }
        }
        prim = self->ext.olroxLaser.prim3;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                func_us_801B8970(prim);
            }
            prim = prim->next;
        }

        if (!self->ext.olroxLaser.timer) {
            self->hitboxState = 0;
            prim = self->ext.olroxLaser.prim1;
            if (self->ext.olroxLaser.hitboxOffX > 0) {
                prim->x2 = prim->x0 += 2;
                prim->x3 = prim->x1 -= 2;
                if (prim->x0 >= prim->x1) {
                    self->step++;
                }
            } else {
                prim->x2 = prim->x0 -= 2;
                prim->x3 = prim->x1 += 2;
                if (prim->x0 <= prim->x1) {
                    self->step++;
                }
            }
        } else {
            self->ext.olroxLaser.timer--;
            if (!self->ext.olroxLaser.timer) {
                child = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (child != NULL) {
                    CreateEntityFromEntity(E_ID(LASER_EXPLOSION), self, child);
                    child->posX.i.hi += self->ext.olroxLaser.hitboxOffX / 2;
                    child->posY.i.hi -= 0x10;
                    child->params = 0x10;
                }
            }
        }
        break;
    case 8:
        prim = self->ext.olroxLaser.prim1;
        for (i = 0; i < 27; i++) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        // fallthrough

    case 9:
        prim = self->ext.olroxLaser.prim3;
        i = 0;
        while (prim != NULL) {
            if (prim->p3 & 8) {
                i++;
                func_us_801B8970(prim);
            }
            prim = prim->next;
        }
        if (i == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitFireballAttack;
extern s16 g_animFireballAttack1[];
extern s16 g_animFireballAttack2[];

void EntityFireballAttack(Entity* self) {
    Entity* entity;
    Entity* next;
    Primitive* prim;
    s32 primIndex;
    s16 angle;
    s16 offsetX;
    s16 offsetY;
    s16 scale;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFireballAttack);
        self->animSet = 9;
        self->animCurFrame = 1;
        self->hitboxWidth = 5;
        self->hitboxHeight = 5;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEX;
        self->scaleX = 0x140;
        next = self->ext.olroxLaser.next;
        self->rotate = next->rotate - ROT(22.5);
        if (self->facingLeft) {
            angle = self->rotate;
        } else {
            angle = ROT(180) - self->rotate;
        }
        self->posX.i.hi += FLT_TO_I(rcos(angle) * 0x10);
        self->posY.i.hi += FLT_TO_I(rsin(angle) * -0x10);
        scale = g_animFireballAttack2[self->ext.olroxLaser.scaleIndex];
        self->velocityX = scale * rcos(angle);
        self->velocityY = -scale * rsin(angle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.olroxLaser.prim1 = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x1A;
        prim->clut = 0x16D;
        prim->u0 = prim->u1 = 0xE0;
        prim->u2 = prim->u3 = 0xC0;
        prim->v0 = prim->v2 = 0x80;
        prim->v1 = prim->v3 = 0x90;
        LOH(prim->next->r2) = 0x34;
        LOH(prim->next->b2) = 0x16;
        LOH(prim->next->tpage) = -angle;
        prim->next->b3 = 0x60;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        prim->priority = self->zPriority + 1;
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        g_api.PlaySfx(SFX_EXPLODE_FAST_A);
        break;

    case 1:
        MoveEntity();
        AnimateEntity(g_animFireballAttack1, self);
        prim = self->ext.olroxLaser.prim1;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        if (self->facingLeft) {
            angle = self->rotate;
        } else {
            angle = ROT(180) - self->rotate;
        }
        prim->next->x1 -= FLT_TO_I(rcos(angle) * 24);
        prim->next->y0 -= FLT_TO_I(rsin(angle) * -24);
        UnkPrimHelper(prim);
        prim->v0 = prim->v2 += 1;
        prim->v1 = prim->v3 += 1;
        if (prim->v1 == 0xB0) {
            prim->v0 = prim->v2 = 0x80;
            prim->v1 = prim->v3 = 0x90;
        }
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->r2 = prim->g2 = prim->b2 = 0;
        offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        if (offsetX < 0x30 || offsetX > 0x1D0 || offsetY < 0x50 ||
            offsetY > 0x1D0) {
            self->flags |= FLAG_DEAD;
        }
        break;
    }
}
