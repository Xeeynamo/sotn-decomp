// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo0.h"

static void func_us_801BA030(s16 sfxId) {
    s32 yOffset;
    s16 vol;
    s16 pan;
    s32 xOffset;

    xOffset = g_CurrentEntity->posX.i.hi - 128;
    pan = (abs(xOffset) - 0x20) >> 5;
    if (pan > 8) {
        pan = 8;
    } else if (pan < 0) {
        pan = 0;
    }
    if (xOffset < 0) {
        pan = -pan;
    }
    vol = abs(xOffset) - 0x60;
    yOffset = abs(g_CurrentEntity->posY.i.hi - 128) - 112;
    if (yOffset > 0) {
        vol += yOffset;
    }
    if (vol < 0) {
        vol = 0;
    }
    vol = 0x58 - (vol >> 1);
    if (vol > 0) {
        g_api.PlaySfxVolPan(sfxId, vol, pan);
    }
}

extern EInit g_EInitParticle;

void EntityRealOlroxDrool(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s16 params;
    s16 rotate;
    s32 primIndex;
    s32 offsetX;
    s16 offsetY;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_LINE_G2, 1);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->hitboxState = 0;
            prim = &g_PrimBuf[primIndex];
            self->ext.olroxDrool.prim = prim;
            i = 0;
            while (prim != NULL) {
                prim->x0 = prim->x1 = self->posX.i.hi;
                prim->y0 = prim->y1 = self->posY.i.hi;
                prim->r0 = 0x60;
                prim->g0 = 0x80;
                prim->b0 = 0x60;
                prim->r1 = 0;
                prim->g1 = 0x20;
                prim->b1 = 0;
                prim->priority = 0xA0;
                prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                  DRAW_UNK02 | DRAW_TRANSP;
                i++;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;

    case 1:
        prim = self->ext.olroxDrool.prim;
        offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        if (offsetY > 0x1D0) {
            prim->y1 += 2;
            if (!self->step_s) {
                func_us_801BA030(SFX_AXE_KNIGHT_WEAPON_BREAK);
                EntityExplosionVariantsSpawner(self, 1, 2, 0, 0, 3, 0);
                self->step_s = 1;
            }
        } else {
            self->velocityY += FIX(0.0625);
            self->posY.val += self->velocityY;
            if ((prim->y0 - prim->y1) > 8) {
                prim->y0 = self->posY.i.hi;
                prim->y1 = prim->y0 - 9;
                entity = self->ext.olroxDrool.entity;
                offsetX = entity->posX.val;
                offsetX -= self->ext.olroxDrool.velocityX;
                self->posX.val += offsetX / 4;
            } else {
                entity = self->ext.olroxDrool.entity;
                self->posX.i.hi = entity->posX.i.hi;
                self->posY.i.hi = entity->posY.i.hi;
                params = self->params;
                rotate = entity->rotate - ROT(33.75);
                if (entity->facingLeft) {
                    self->posX.i.hi += FLT_TO_I(params * rcos(rotate));
                } else {
                    self->posX.i.hi -= FLT_TO_I(params * rcos(rotate));
                }
                self->posY.i.hi -= FLT_TO_I(params * rsin(rotate));
                offsetY = prim->y0 - prim->y1;
                offsetY += 1;
                prim->y1 = self->posY.i.hi;
                prim->y0 = prim->y1 + offsetY;
                if (offsetY > 8) {
                    self->posY.i.hi += 8;
                }
            }
        }
        prim->x0 = self->posX.i.hi;
        prim->x1 = self->posX.i.hi;
        entity = self->ext.olroxDrool.entity;
        self->ext.olroxDrool.velocityX = entity->posX.val;
        if (prim->y0 < prim->y1) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

Primitive* FindFirstUnkPrim(Primitive* prim);
Primitive* FindFirstUnkPrim2(Primitive* prim, int);

void func_us_801BA4AC(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x80);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.olroxDrool.prim = prim;
        while (prim != NULL) {
            prim->priority = 0xB0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        // fallthrough

    case 1:
        prim = self->ext.olroxDrool.prim;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->type = PRIM_LINE_G2;
            prim->r0 = 0x60;
            prim->g0 = 0x60;
            prim->b0 = 0x40;
            prim->r1 = 0;
            prim->g1 = 0;
            prim->b1 = 0;
            prim->x0 = prim->x1 = Random() & 0xFF;
            prim->y0 = 0xF0;
            prim->y1 = (Random() & 0x1F) + 0x120;
            prim->y2 = (Random() & 0xF) + 0xC;
            prim->p3 = 4;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        }
        if (!(g_Timer & 3)) {
            prim = self->ext.olroxDrool.prim;
            prim = FindFirstUnkPrim2(prim, 2);
            if (prim != NULL) {
                UnkPolyFunc2(prim);
                prim->next->x1 = Random() & 0xFF;
                prim->next->y0 = 0x1D0 - g_Tilemap.scrollY.i.hi;
            }
        }
    case 2:
        prim = self->ext.olroxDrool.prim;
        while (prim != NULL) {
            if (prim->p3 == 4) {
                prim->y0 -= prim->y2;
                prim->y1 -= prim->y2;
                if (prim->y1 < 0) {
                    prim->drawMode = DRAW_HIDE;
                    prim->p3 = 0;
                }
            }
            if (prim->p3 & 8) {
                func_us_801B8B64(prim);
            }
            prim = prim->next;
        }
        break;
    }
}

void func_us_801BA724(Entity* self) UNUSED {
    DRAWENV draw;
    s16 primIndex;
    Primitive* prim;
    s16 tpage;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.olroxDrool.prim = prim;
        // fallthrough
    case 1:
        draw = g_CurrentBuffer->draw;
        if (draw.ofs[0]) {
            tpage = 0x104;
        } else {
            tpage = 0x100;
        }

        // n.b.! if this doesn't enter with `self->step == 0`
        // `prim` will be uninitialized.
        prim->tpage = tpage;
        prim->u1 = prim->u3 = 0xFF;
        prim->u0 = prim->u2 = 0;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0xF0;

        break;
    }
}
