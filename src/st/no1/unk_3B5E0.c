// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Called by elevator doors
INCLUDE_ASM("st/no1/nonmatchings/unk_3B5E0", func_us_801BB5E0);

// Called by elevator doors
INCLUDE_ASM("st/no1/nonmatchings/unk_3B5E0", func_us_801BB7B8);

extern s16 D_us_80181508[][3];
extern s16 D_us_8018151C[][3];
extern u8 D_us_80181540[];

extern s32 D_psp_08C62AA4;

// Elevator doors
void func_us_801BB984(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s16 dx;
    s32 i;
    Entity* tempEntity;
    u8 params;
    s32 tilePos;

    params = self->params;
    tempEntity = &g_Entities[152];

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A1C);
        self->animCurFrame = 0x1F;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BBD90.unk7C = prim;
            for (i = 0; prim != NULL; i++) {
                prim->tpage = 0x12;
                prim->clut = 0x209;
                prim->u0 = prim->u2 = 0x70;
                prim->u1 = prim->u3 = 0x7D;
                prim->x0 = prim->x2 = self->posX.i.hi - 0xC;
                prim->x1 = prim->x3 = prim->x0 + 0xD;
                if (i == 0) {
                    prim->v0 = prim->v1 = 0xCC;
                    prim->v2 = prim->v0 + 0x22;
                    prim->v3 = prim->v0 + 0x14;
                    prim->y0 = prim->y1 = self->posY.i.hi - 0x18;
                    prim->y2 = prim->y0 + 0x22;
                    prim->y3 = prim->y0 + 0x14;
                } else {
                    prim->v0 = 0xEE;
                    prim->v1 = 0xE0;
                    prim->v2 = prim->v3 = 0xFC;
                    prim->y2 = prim->y3 = self->posY.i.hi + 0x18;
                    prim->y0 = prim->y2 - 0xE;
                    prim->y1 = prim->y2 - 0x1C;
                }
                prim->priority = 0x69;
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            self->animSet = 0;
        } else {
            self->ext.et_801BBD90.unk7C = NULL;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_16]) {
            if (tempEntity->ext.et_801BBD90.unk84 == params &&
                tempEntity->ext.et_801BBD90.unk85 == params) {
                SetStep(2);
            }
            tempEntity = &PLAYER;
            dx = self->posX.i.hi - tempEntity->posX.i.hi;
            if (dx < 0) {
                self->ext.et_801BBD90.unk88 = 0x20;
            } else if ((dx < 0x20) && (GetDistanceToPlayerY() < 0x10)) {
                if (!--self->ext.et_801BBD90.unk88) {
                    self->step = 4;
                }
            } else {
                self->ext.et_801BBD90.unk88 = 0x20;
            }
        }
        break;

    case 2:
        self->animCurFrame = 0;
        if (tempEntity->ext.et_801BBD90.unk85 != params) {
            self->step_s = 0;
            self->step = 3;
        }
        break;

    case 3:
        self->animCurFrame = 0x1F;
        self->step_s = 0;
        self->step = 1;
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            tempEntity->ext.et_801BBD90.unk94 = 1;
            tempEntity->ext.et_801BBD90.unk85 = params;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (tempEntity->ext.et_801BBD90.unk84 == params) {
                self->step_s = 0;
                self->step = 2;
            }
            break;
        }
        break;
    }
    if (self->ext.et_801BBD90.unk7C != NULL) {
        if (self->animCurFrame) {
            func_us_801BB5E0();
        } else {
            func_us_801BB7B8();
        }
    }
    if (self->animCurFrame) {
        for (i = 0; i < 3; i++) {
            tilePos = D_us_80181508[params][i];
            g_Tilemap.fg[tilePos] = D_us_8018151C[params][i];
        }
    } else {
        for (i = 0; i < 3; i++) {
            tilePos = D_us_80181508[params][i];
            g_Tilemap.fg[tilePos] = D_us_8018151C[params + 3][i];
        }
    }
}

void func_us_801BBD90(Entity* self) {
    s16 dx, dy;
    s16 var9a;
    s32 primIndex;
    s32 dx2;
    Entity* tempEntity;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    s16 dAngle;
    s16 posX, posY;
    s16 angle;
    s32 i;
    s16 magnitude;
    s16 temp;
    Primitive* prim;
    s32 dy2;
    RECT unused;
    u8 padding[4];

    unused = (RECT){.x = 0xf0, .y = 0xc0, .w = 0x10, .h = 0x10};
    tempEntity = self - 1;
    self->posX.i.hi = tempEntity->posX.i.hi;
    self->posY.i.hi = tempEntity->posY.i.hi - 0x22;
    magnitude = 8;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809F8);
        self->animCurFrame = 0;
        break;

    case 1:
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x20);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            drawEnv = g_CurrentBuffer->draw;
            drawEnv.isbg = 1;
            drawEnv.r0 = 0;
            drawEnv.g0 = 0;
            drawEnv.b0 = 0;
            drawEnv.clip.x = 0;
            drawEnv.clip.w = 0x20;
            drawEnv.clip.y = 0x100;
            drawEnv.clip.h = 0x100;
            drawEnv.ofs[0] = 0;
            drawEnv.ofs[1] = 0x100;
            SetDrawEnv(dr_env, &drawEnv);
            prim->priority = 0x11F;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env == NULL) {
                DestroyEntity(self);
                return;
            }
            prim->type = PRIM_ENV;
            prim->priority = 0x121;
            prim->drawMode = DRAW_UNK_800 | DRAW_HIDE;
            prim = prim->next;

            self->ext.et_801BBD90.unk7C = prim;
#ifdef VERSION_PSP
            prim->tpage = 0x8010;
#else
            prim->tpage = 0x10;
#endif
            prim->clut = 0x2F;
            prim->u0 = 0;
            prim->u1 = prim->u0 + 0x10;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0;
            prim->v1 = prim->v0;
            prim->v2 = 0xFF;
            prim->v3 = prim->v2;
            prim->priority = 0x69;
            prim = prim->next;

            while (prim != NULL) {
                prim->tpage = 0x10E;
                prim->clut = 0x2F;
                prim->u0 = 0x3E;
                prim->u1 = prim->u0 + 2;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0xC0;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0x10;
                prim->v3 = prim->v2;
                prim->priority = 0x120;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        self->step++;
        break;

    case 2:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        prim = self->ext.et_801BBD90.unk7C;
        prim = prim->next;
        posX = 0;
        posY = 0;
        while (prim != NULL) {
            prim->tpage = 0x10E;
            prim->x0 = prim->x2 = posX;
            prim->y0 = prim->y1 = posY;
            prim->x1 = prim->x3 = prim->x2 + 2;
            posY = prim->y2 = prim->y3 = prim->y0 + 0x10;
            prim = prim->next;
        }
        self->step_s = 0;
        self->step++;
        break;

    case 3:
        if (!self->step_s) {
            prim = &g_PrimBuf[self->primIndex];
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim = self->ext.et_801BBD90.unk7C;
            prim = prim->next;
            while (prim != NULL) {
                prim->v0 = prim->v1 = 0xC0;
                prim->v2 = prim->v3 = 0xC8;
                prim = prim->next;
            }
            self->step_s++;
#ifdef VERSION_PSP
            D_psp_08C62AA4 = 1;
#endif
        }
        if ((self->posX.i.hi & 0x100) || (self->posY.i.hi < 0)) {
            prim = self->ext.et_801BBD90.unk7C;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            i = 0;
            dAngle = 0;
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            posX -= 4;
            if (posY > 0xF0) {
                posY = (self->posY.i.hi & 0xF) + 0xF0;
            }
            tempEntity = self - 1;
            if (tempEntity->ext.et_801BBD90.unk87) {
                if (tempEntity->velocityY < 0) {
                    self->ext.et_801BBD90.unk8C += 0x60;
                } else {
                    if (self->ext.et_801BBD90.unk8C > 0) {
                        self->ext.et_801BBD90.unk8C -= 0x30;
                    } else {
                        self->ext.et_801BBD90.unk8C += 0x30;
                    }
                }
            } else if (self->ext.et_801BBD90.unk8C) {
                if (self->ext.et_801BBD90.unk8C > 0) {
                    self->ext.et_801BBD90.unk8C -= 0x30;
                } else {
                    self->ext.et_801BBD90.unk8C += 0x30;
                }
            }
            prim = self->ext.et_801BBD90.unk7C;
            if (!self->ext.et_801BBD90.unk8C) {
                prim->drawMode = DRAW_UNK02;
                prim->priority = 0x69;
                prim->x0 = prim->x2 = posX;
                prim->y2 = prim->y3 = posY;
                prim->x1 = prim->x0 + 0x10;
                prim->x3 = prim->x2 + 0x10;
                prim->y0 = prim->y1 = prim->y2 - 0xF0;
                prim->v2 = prim->v3 = 0xFF;
                temp = g_Tilemap.scrollY.i.hi + prim->y0;
                if (temp < 0x300) {
                    prim->y0 = 0x300 - g_Tilemap.scrollY.i.hi;
                    prim->y1 = prim->y0;
                }
                prim->v0 = prim->v1 = prim->v2 - (prim->y2 - prim->y0);
                prim = prim->next;
                while (prim != NULL) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
            } else {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
                angle = self->ext.et_801BBD90.unk8C;
                angle &= 0xFFF;
                while (prim != NULL) {
#ifdef VERSION_PSP
                    prim->tpage = 0x10;
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 4;
                    prim->v0 = prim->v1 = 0;
                    prim->v2 = prim->v3 = 0x10;
#else
                    prim->tpage = 0xE;
                    prim->u0 = -6;
                    prim->u3 = prim->u1 = -2;
                    prim->u2 = -6;
#endif
                    prim->priority = 0x69;
                    prim->x2 = posX;
                    prim->y2 = posY;
                    dx = -(magnitude * rsin(angle)) >> 0xC;
                    dy = -(magnitude * rcos(angle)) >> 0xC;
                    prim->x0 = posX + dx;
                    prim->y0 = posY + dy;
                    prim->x1 = prim->x0 + 4;
                    prim->x3 = prim->x2 + 4;
                    prim->y1 = prim->y0;
                    prim->y3 = prim->y2;
                    if (i == 0) {
                        i = 4;
                        dx2 = self->posX.i.hi - 4 - prim->x0;
                        dy2 = 0x10;
                        var9a = ratan2(-dx2, dy2);
                        dAngle = var9a - angle;
                        if (dAngle > 0x800) {
                            dAngle = 0x1000 - dAngle;
                        }
                        if (dAngle < -0x800) {
                            dAngle = dAngle + 0x1000;
                        }
                        dAngle /= 4;
                    }
                    angle += dAngle;
                    angle &= 0xFFF;
                    posX = prim->x0;
                    posY = prim->y0;
                    prim->drawMode = DRAW_UNK02;
                    if (prim->y2 < -0x10) {
                        break;
                    }
                    temp = g_Tilemap.scrollY.i.hi + prim->y0;
                    if (temp < 0x300) {
                        prim->y0 = 0x300 - g_Tilemap.scrollY.i.hi;
                        prim->y1 = prim->y0;
                        break;
                    }
                    i--;
                    prim = prim->next;
                }

                while (prim != NULL) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
            }
        }
        break;
    }
}

STATIC_PAD_RODATA(4);

void func_us_801BC598(Primitive* prim) {
    Primitive* otherPrim;
    u8 tempVar;

    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x1A;
        prim->clut = 0x1B0;
        prim->u0 = 0x70;
        prim->u1 = 0x7F;
        prim->u2 = prim->u1;
        prim->u3 = prim->u2;
        prim->v0 = 0x20;
        prim->v1 = prim->v0;
        prim->v2 = 0x2F;
        prim->v3 = prim->v2;
        prim->next->b3 = 0x80;
        if (prim->next->r3 & 0x10) {
            if (prim->next->r3 & 1) {
                LOH(prim->next->tpage) = 0xA00;
            } else {
                LOH(prim->next->tpage) = 0x600;
            }
        } else {
            if (prim->next->r3 & 1) {
                LOH(prim->next->tpage) = -0x100;
            } else {
                LOH(prim->next->tpage) = 0x100;
            }
        }
        LOH(prim->next->r2) = 0xE;
        LOH(prim->next->b2) = 0x10;
        prim->priority = 0xF0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim->next->x3 = 0x10;
        prim->next->u2 = 1;
        /* fallthrough */
    case 1:
        if (prim->next->r3 & 1) {
            prim->next->x1 = g_CurrentEntity->posX.i.hi - 0xC;
        } else {
            prim->next->x1 = g_CurrentEntity->posX.i.hi + 0xC;
        }
        if (prim->next->r3 & 0x10) {
            prim->next->y0 = g_CurrentEntity->posY.i.hi - 0x25;
        } else {
            prim->next->y0 = g_CurrentEntity->posY.i.hi + 0x23;
        }
        UpdateAnimation(D_us_80181540, prim);
        UnkPrimHelper(prim);
        if (Random() % 8 == 0) {
            otherPrim = g_CurrentEntity->ext.et_801BBD90.unk7C;
            otherPrim = FindFirstUnkPrim2(otherPrim, 2);
            if (otherPrim != NULL) {
                UnkPolyFunc2(otherPrim);
                otherPrim->x0 = prim->next->x1;
                otherPrim->y0 = prim->next->y0;
                otherPrim->g1 = (Random() & 1) + 1;
                otherPrim->g2 = (Random() & 3) + 1;
                otherPrim->next->u2 = 4;
                otherPrim->next->r3 = prim->next->r3;
            }
        }
        prim->next->x3--;
        if (!prim->next->x3) {
            prim->next->u2 = 0;
            prim->p1 = 0;
            prim->p2 = 0;
            UnkPolyFunc0(prim);
        }
        break;

    case 4:
        prim->type = PRIM_TILE;
        prim->u0 = 1;
        prim->v0 = 1;
        prim->b0 = 0xC0;
        prim->r0 = 0x40;
        prim->g0 = 0x40;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim->next->x3 = 0x20;
        prim->next->u2 = 5;
        /* fallthrough */
    case 5:
        if (prim->next->r3 & 0x10) {
            prim->y0 -= prim->g1;
        } else {
            prim->y0 += prim->g1;
        }
        tempVar = prim->g2;
        if (g_Timer % tempVar == 0) {
            if (prim->next->r3 & 1) {
                prim->x0++;
            } else {
                prim->x0--;
            }
        }
        prim->next->x3--;
        if (!prim->next->x3) {
            prim->type = PRIM_GT4;
            prim->next->u2 = 0;
            UnkPolyFunc0(prim);
        }
        break;
    }
}

void func_us_801BC9A8(Primitive* prim) {
    s16 posY;

    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0xE;
        prim->clut = 0x4A;
        prim->u0 = 0xD0;
        prim->u1 = prim->u0 + 0x1F;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0xC0;
        prim->v1 = prim->v0;
        prim->v2 = prim->v0 + 0xF;
        prim->v3 = prim->v2;
        prim->priority = 0x70;
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        LOH(prim->next->r2) = 0x20;
        LOH(prim->next->b2) = 0x10;
        prim->next->b3 = 0x30;
        prim->next->u2 = 1;
        /* fallthrough */
    case 1:
        prim->next->x1 = g_CurrentEntity->posX.i.hi;
        prim->next->y0 = g_CurrentEntity->posY.i.hi + 0x24;
        UnkPrimHelper(prim);
        prim->drawMode = DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if (!g_CurrentEntity->velocityY || g_Timer % 2) {
            prim->drawMode =
                DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        posY = g_Tilemap.scrollY.i.hi + prim->y2;
        if (posY > 0x810) {
            prim->drawMode = DRAW_HIDE;
        }
        if (posY > 0x610 && posY < 0x650) {
            prim->drawMode = DRAW_HIDE;
        }
    }
}
