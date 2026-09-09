// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz1.h"

s16 func_us_801BD0EC(Primitive* prim, s32 arg1, s32 arg2) {
    prim->drawMode = 2;    
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 0x70;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 0x60;
    if (arg1 < arg2) {
        arg1 = arg2 - arg1;
        prim->v0 = prim->v1 = arg1 + 0x10;
        prim->y0 = prim->y1 = arg2;
        arg1 = 0;
    } else {
        prim->v0 = prim->v1 = 0x10;
        prim->y0 = prim->y1 = arg1;
    }
    return arg1;
}


// NOTE: This function contains an ugly ifdef! It is seen in several other files
// including a few different e_secrets, and e_discus_lord. Search for:
// (prim->x0 << 0x10) + (u16)prim->x1; and you will find those others.
// This likely signals something we are doing wrongly! Maybe a weird union?
void func_us_801BD184(Primitive* prim) {
    u32 x;
    u32 y;
    s32 length;
    s16 angle;

    switch (prim->p1) {
    case 0:
        prim->r0 = 0x80;
        prim->g0 = 0x80;
        prim->b0 = 0xC0;
        prim->drawMode = 2;
        prim->x1 = 0;
        prim->y1 = 0;
        prim->y0 = g_CurrentEntity->posY.i.hi + 0xC;
        length = (Random() & 0x1F) + 0x20;
        angle = (Random() * 6) + 0x900;
        LOW(prim->x2) = length * rcos(angle);
        LOW(prim->x3) = length * rsin(angle);
        prim->p1 = 1;
        prim->r3 = 0x10;
        /* fallthrough */
    case 1:
#ifdef VERSION_US
    x = (prim->x0 << 0x10) + (u16)prim->x1;
#else
    x = (prim->x0 << 0x10) + prim->x1;
#endif
        x += LOW(prim->x2);
        prim->x0 = HIHU(x);
        prim->x1 = LOHU(x);
#ifdef VERSION_US
    y = (prim->y0 << 0x10) + (u16)prim->y1;
#else
    y = (prim->y0 << 0x10) + prim->y1;
#endif
        y += LOW(prim->x3);
        prim->y0 = HIH(y);
        prim->y1 = LOH(y);
        LOW(prim->x3) += 0x2000;
        prim->r0 -= 5;
        prim->g0 -= 5;
        prim->b0 -= 9;
        prim->r3 -= 1;
        if (!prim->r3) {
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
        }
    }
}


// Grindy crushy platform things.
// params 0 = one-wide, params 1 = three-wide
extern EInit D_us_80180C78;

void func_us_801BD324(Entity* self) {
    Entity* crusherHead;

    switch (self->step) {
        case 0:
        InitializeEntity(D_us_80180C78);
        self->hitboxState = 0;
        self->animCurFrame = 1;
        crusherHead = self + 1;
        CreateEntityFromEntity(0x48, self, crusherHead);
        crusherHead->posY.i.hi += 0x20;
        crusherHead->params = self->params;
    }
}

extern u16 D_us_80180C7E;
extern EInit D_us_80180C78;


void func_us_801BD398(Entity* self) {
    Collider sp3C;
    bool hitPlayer;
    s32 primIndex;
    s32 xVar;
    s32 playerY;
    s32 i;
    Entity* other;
    s32 yVar;
    Primitive* prim;

    if (!self->params) {
        xVar = 0x18;
    } else {
        xVar = 0x32;
    }
    hitPlayer = GetPlayerCollisionWith(self, xVar, 0x10, 4);
    switch (self->step) {                              /* irregular */
    case 0x0:
        InitializeEntity(D_us_80180C78);
        if (!self->params) {
            self->animCurFrame = 3;
            self->hitboxState = 1;
            self->hitboxWidth = 0x14;
            self->hitboxHeight = 4;
            self->hitboxOffY = 0x10;
            self->attackElement = 0x50;
            self->attack = 0xF;
        } else {
            self->animCurFrame = 6;
            self->hitboxOffY = 0x1A;
            other = self + 1;
            for(i = 0; i < 3; i++, other++) {
                CreateEntityFromEntity(0x49, self, other);
                other->params = i;
            }
        }
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->tpage = 0x14;
            prim->clut = 0x232;
            prim->u0 = prim->u2 = 0xE0;
            prim->u1 = prim->u3 = 0xF0;
            prim->priority = ((self->zPriority) - 1);
            prim->drawMode = 8;
            prim = prim->next;
        }
        break;
    case 0x1:
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[2] = 0x20;
            self->step_s++;
        }
        if (self->ext.ILLEGAL.s16[2] & 1) {
            self->posY.i.hi--;
        } else {
            self->posY.i.hi++;
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            SetStep(2);
        }
        break;
    case 0x2:
        if (!self->step_s) {
            self->velocityY = 0x8000;
            self->step_s++;
        }
        if (!(g_Timer & 7)) {
            PlaySfxPositional(0x6DC);
        }
        MoveEntity();
        if (self->params) {
            self->velocityY += 0x4000;
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        if (!self->params) {
            yVar += 0x10;
        } else {
            yVar += 0x1C;
        }
        g_api.CheckCollision(xVar, yVar, &sp3C, 0);
        if (sp3C.effects & 1) {
            PlaySfxPositional(0x63D);
            self->posY.i.hi += sp3C.unk18;
            SetStep(3);
            if (self->params) {
                g_api.func_80102CD8(1);
            }
        }
        break;
    case 0x3:
        if (!self->step_s) {
            if (!self->params) {
                self->ext.ILLEGAL.s16[2] = 0x20;
            } else {
                self->ext.ILLEGAL.s16[2] = 0x40;
            }
            self->step_s++;
        }
        self->ext.ILLEGAL.u8[0xC] = 1;
        if ((self->params) && !(self->ext.ILLEGAL.s16[2] & 3)) {
            PlaySfxPositional(0x652);
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->ext.ILLEGAL.u8[0xC] = 0;
            SetStep(4);
        }
        break;
    case 0x4:
        if (!self->step_s) {
            self->velocityY = -0x8000;
            self->step_s++;
        }
        other = self - 1;
        playerY = other->posY.i.hi + 0x20;
        if ((g_Timer % 12U) == 0) {
            PlaySfxPositional(0x6DB);
        }
        MoveEntity();
        if (self->posY.i.hi < playerY) {
            self->velocityY = 0;
            self->posY.i.hi = playerY;
            SetStep(1);
        }
        if ((hitPlayer) && (g_Player.vram_flag & 2)) {
            self->velocityY = 0;
            SetStep(2);
        }
        break;
    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
    if (hitPlayer) {
        other = &PLAYER;
        yVar = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        yVar -= self->ext.ILLEGAL.s16[4];
        other->posY.i.hi += yVar;
        g_api.func_8010DFF0(0, 1);
    }
    yVar = self->posY.i.hi - 0x10;
    prim = self->ext.prim;
    other = self - 1;
    playerY = other->posY.i.hi;
    while (prim != NULL) {
        yVar = func_us_801BD0EC(prim, yVar, playerY);
        prim = prim->next;
        if (yVar == 0) {
            break;
        }
    }
    
    while (prim != NULL) {
        prim->drawMode = 8;
        prim = prim->next;
    }
    
    self->ext.ILLEGAL.s16[4] = (self->posY.i.hi + g_Tilemap.scrollY.i.hi);
    if (!self->params) {
        if (self->hitFlags) {
            self->ext.ILLEGAL.s32[4] = 0x37;
        }
        if (self->ext.ILLEGAL.s32[4] != 0) {
            self->ext.ILLEGAL.s32[4]--;
        }
        self->palette = ((D_us_80180C7E) + (self->ext.ILLEGAL.s32[4] >> 3));
    }
}

extern AnimateEntityFrame D_us_801824B8[];
extern u16 D_us_80180C7E;
extern EInit D_us_80180C78;

void func_us_801BDA24(Entity* self) {
    Entity* other;
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180C78);
        self->hitboxState = 1;
        self->hitboxOffY = 7;
        self->hitboxWidth = 0xD;
        self->hitboxHeight = 5;
        self->attackElement = 0x50;
        self->attack = 0xF;
        primIndex = g_api.AllocPrimitives(PRIM_TILE_ALT, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= 0x800000;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        for(self->ext.prim = prim; prim != NULL; prim = prim->next) {
            prim->u0 = prim->v0 = 1;
            prim->r0 = 0x40;
            prim->g0 = 0x40;
            prim->b0 = 0x40;
            prim->priority = self->zPriority + 2;
            prim->drawMode = 8;
        }
    case 1:
        AnimateEntity(D_us_801824B8, self);
        other = self - self->params - 1;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi + 0x12;
        self->posX.i.hi += (((self->params) * 0x24) - 0x24);
        if (other->ext.ILLEGAL.u8[12]) {
            if (g_Timer & 1) {
                other = AllocEntity(&g_Entities[224], &g_Entities[240]);
                if (other != NULL) {
                    CreateEntityFromEntity(6, self, other);
                    other->params = 0x10;
                    other->zPriority = ((self->zPriority) + 1);
                    other->posY.i.hi += 12;
                    other->posX.i.hi += ((Random() & 0x1F) - 0x10);
                }
            }
            prim = self->ext.prim;
            prim = FindFirstUnkPrim(prim);
            if (prim != NULL) {
                prim->p1 = 0;
                prim->y0 = self->posY.i.hi + 12;
                prim->x0 = (self->posX.i.hi + (Random() & 0x1F)) - 0x10;
                prim->p3 = 2;
            }
        }
    }
    if (self->hitFlags) {
        self->ext.ILLEGAL.s32[4] = 0x37;
    }
    if (self->ext.ILLEGAL.s32[4] != 0) {
        self->ext.ILLEGAL.s32[4] -= 1;
    }
    self->palette = (D_us_80180C7E + (self->ext.ILLEGAL.s32[4] >> 3));
    for(prim = self->ext.prim; prim->next != NULL; prim = prim->next) {
        if (prim->p3 & 2) {
            func_us_801BD184(prim);
        }
    }
    prim->p3 = 2;
    prim->x0 = prim->y0 = -0x10;
    prim->priority = ((self->zPriority) + 2);
    prim->drawMode = 2;
}
