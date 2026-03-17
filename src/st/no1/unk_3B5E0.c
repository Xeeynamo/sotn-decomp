// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_2A);
#endif

extern Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index);

static s16 D_us_80181508[][3] = {
    {0x1845, 0x1875, 0x18A5},
    {0x1245, 0x1275, 0x12A5},
    {0x0945, 0x0975, 0x09A5},
};

static s16 D_us_8018151C[][3] = {
    {0x554, 0x555, 0x554}, {0x554, 0x555, 0x554}, {0x552, 0x553, 0x552},
    {0x09A, 0x094, 0x09A}, {0x09A, 0x094, 0x09A}, {0x05B, 0x060, 0x05B},
};

// Called by elevator doors
static void func_us_801BB5E0(void) {
    Primitive* prim;
    s16 yMin, yMax;

    prim = g_CurrentEntity->ext.et_801BBD90.unk7C;
    yMax = g_CurrentEntity->posY.i.hi + 10;
    prim->y0 = g_CurrentEntity->posY.i.hi - 24;
    if (prim->y2 >= yMax) {
        if (g_CurrentEntity->ext.et_801BBD90.unk95) {
            g_CurrentEntity->ext.et_801BBD90.unk95 = 0;
        }
        prim->y2 = yMax;
    } else {
        if (!g_CurrentEntity->ext.et_801BBD90.unk95) {
            g_CurrentEntity->ext.et_801BBD90.unk95 = 1;
            PlaySfxPositional(SFX_ELEVATOR_DOOR);
        }
        prim->y2++;
    }
    prim->v0 = prim->v2 - (prim->y2 - prim->y0);
    yMax = g_CurrentEntity->posY.i.hi - 4;
    prim->y1 = g_CurrentEntity->posY.i.hi - 24;
    if (prim->y3 >= yMax) {
        prim->y3 = yMax;
    } else {
        prim->y3++;
    }
    prim->v1 = prim->v3 - (prim->y3 - prim->y1);

    prim = prim->next;
    yMin = g_CurrentEntity->posY.i.hi + 10;
    prim->y2 = g_CurrentEntity->posY.i.hi + 24;
    if (prim->y0 <= yMin) {
        prim->y0 = yMin;
    } else {
        prim->y0--;
    }
    prim->v2 = prim->v0 + (prim->y2 - prim->y0);
    yMin = g_CurrentEntity->posY.i.hi - 4;
    prim->y3 = g_CurrentEntity->posY.i.hi + 24;
    if (prim->y1 <= yMin) {
        prim->y1 = yMin;
    } else {
        prim->y1--;
    }
    prim->v3 = prim->v1 + (prim->y3 - prim->y1);
}

// Called by elevator doors
static void func_us_801BB7B8(void) {
    Primitive* prim;
    s16 yMin, yMax;

    prim = g_CurrentEntity->ext.et_801BBD90.unk7C;
    yMin = g_CurrentEntity->posY.i.hi - 10;
    prim->y0 = g_CurrentEntity->posY.i.hi - 24;
    if (prim->y2 <= yMin) {
        if (g_CurrentEntity->ext.et_801BBD90.unk95) {
            g_CurrentEntity->ext.et_801BBD90.unk95 = 0;
        }
        prim->y2 = yMin;
    } else {
        if (!g_CurrentEntity->ext.et_801BBD90.unk95) {
            g_CurrentEntity->ext.et_801BBD90.unk95 = 1;
            PlaySfxPositional(SFX_ELEVATOR_DOOR);
        }
        prim->y2--;
    }
    prim->v0 = prim->v2 - (prim->y2 - prim->y0);
    yMin = g_CurrentEntity->posY.i.hi - 24;
    prim->y1 = g_CurrentEntity->posY.i.hi - 24;
    if (prim->y3 <= yMin) {
        prim->y3 = yMin;
    } else {
        prim->y3--;
    }
    prim->v1 = prim->v3 - (prim->y3 - prim->y1);

    prim = prim->next;
    yMax = g_CurrentEntity->posY.i.hi + 24;
    prim->y2 = g_CurrentEntity->posY.i.hi + 24;
    if (prim->y0 >= yMax) {
        prim->y0 = yMax;
    } else {
        prim->y0++;
    }
    prim->v2 = prim->v0 + (prim->y2 - prim->y0);
    yMax = g_CurrentEntity->posY.i.hi + 10;
    prim->y3 = g_CurrentEntity->posY.i.hi + 24;
    if (prim->y1 >= yMax) {
        prim->y1 = yMax;
    } else {
        prim->y1++;
    }
    prim->v3 = prim->v1 + (prim->y3 - prim->y1);
}

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
        if (g_CastleFlags[NO1_ELEVATOR_ACTIVATED]) {
            if (tempEntity->ext.et_801BBD90.unk84 == params &&
                tempEntity->ext.et_801BBD90.unk85 == params) {
                SetStep(2);
            }
            tempEntity = &PLAYER;
            dx = self->posX.i.hi - tempEntity->posX.i.hi;
            if (dx < 0) {
                self->ext.et_801BBD90.unk88 = 0x20;
            } else if (dx < 0x20 && GetDistanceToPlayerY() < 0x10) {
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
    const RECT unused = {0xF0, 0xC0, 0x10, 0x10};
    u8 padding[4];

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
            D_psp_08C62AA4 = true;
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
                    dx = FLT_TO_I(-(magnitude * rsin(angle)));
                    dy = FLT_TO_I(-(magnitude * rcos(angle)));
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
                        if (dAngle > ROT(180)) {
                            dAngle = ROT(360) - dAngle;
                        }
                        if (dAngle < ROT(-180)) {
                            dAngle = dAngle + ROT(360);
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

// Mask for all of the statuses where the UP or DOWN button will
// be ignored when in elevator
//
// Value: 0xC5CFFEDF
#define PLAYER_STATUS_ELEVATOR_READY_MASK                                      \
    ~(PLAYER_STATUS_UNK20000000 | PLAYER_STATUS_UNK10000000 |                  \
      PLAYER_STATUS_ABSORB_BLOOD | NO_AFTERIMAGE | PLAYER_STATUS_UNK200000 |   \
      PLAYER_STATUS_UNK100000 | PLAYER_STATUS_UNK100 | PLAYER_STATUS_CROUCH)

static u8 D_us_80181540[] = {
    0x02, 0xC0, 0x00, 0x0F, 0x0F, 0x02, 0x70, 0x20,
    0x0F, 0x0F, 0x02, 0x80, 0x20, 0xF1, 0x0F, 0x00,
};

static u8 D_us_80181550[] = {32, 64, 8, 65, 8, 66, 16, 67, -1, 0};

static u8 D_us_8018155C[] = {32, 67, 8, 66, 8, 65, 16, 64, -1, 0};

static s16 D_us_80181568[] = {0x82C, 0x62C, 0x32C, 0x000};

static void func_us_801BC598(Primitive* prim) {
    Primitive* otherPrim;
    u8 tempVar;

    switch (prim->next->u2) {
    case 0:
        prim->tpage = 0x1A;
        prim->clut = PAL_UNK_1B0;
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
        if ((g_Timer % tempVar) == 0) {
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

static void func_us_801BC9A8(Primitive* prim) {
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
        if (g_CurrentEntity->velocityY) {
            if (g_Timer % 2) {
                prim->drawMode =
                    DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_HIDE;
            }
        }
        posY = g_Tilemap.scrollY.i.hi + prim->y2;
        if (posY > 0x810) {
            prim->drawMode = DRAW_HIDE;
        }
        if (posY > 0x610 && posY < 0x650) {
            prim->drawMode = DRAW_HIDE;
        }
        break;
    }
}

void func_us_801BCB34(Entity* self) {
    Collider collider;
    Primitive* prim;
    s16 posX, posY;
    s32 primIndex;
#ifdef VERSION_PSP
    s8 dPad;
#else
    u8 dPad;
#endif
    Entity* player;
    Entity* tempEntity;
    s32 i;

    s16 unusedA = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
    s16 unusedB = g_Tilemap.scrollY.i.hi + self->posY.i.hi;

    player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809F8);
        self->ext.et_801BBD90.unk84 = self->params;
        self->ext.et_801BBD90.unk85 = self->ext.et_801BBD90.unk84;
        self->ext.et_801BBD90.unk86 = 0;
        self->ext.et_801BBD90.unk87 = 0;
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 0x10;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x28);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BBD90.unk90 = prim;
            UnkPolyFunc2(prim);
            prim->next->u2 = 0;
            prim = prim->next;
            prim = prim->next;
            self->ext.et_801BBD90.unk7C = prim;
        } else {
            self->ext.et_801BBD90.unk90 = NULL;
            self->ext.et_801BBD90.unk7C = NULL;
        }
        tempEntity = self + 1;
        CreateEntityFromEntity(E_ID(ID_2A), self, tempEntity);
        tempEntity->posY.i.hi -= 0x22;
        tempEntity->ext.et_801BBD90.unk8C = 0;
        break;
    case 1:
        self->step++;
        break;
    case 2:
        self->velocityY = 0;
        if (GetDistanceToPlayerX() < 6 && GetDistanceToPlayerY() < 16) {
            i = g_Player.status;
            if (i & PLAYER_STATUS_ELEVATOR_READY_MASK) {
                break;
            }
            dPad = 0;
            if (g_pads[0].pressed & PAD_UP) {
                dPad = 1;
            }
            if (g_pads[0].pressed & PAD_DOWN) {
                dPad = -1;
            }
            if (dPad) {
                dPad += self->ext.et_801BBD90.unk84;
#ifdef VERSION_PSP
                if (dPad == -1U || dPad > 2) {
                    break;
                }
#else
                if (dPad == 0xFF || dPad > 2) {
                    break;
                }
                g_Player.demo_timer = 2;
                g_Player.padSim = 0;
                PLAYER.velocityX = 0;
                PLAYER.velocityY = 0;
#endif
                g_api.func_8010DFF0(0, 1);
                g_api.func_8010E168(1, 0x20);
                self->ext.et_801BBD90.unk85 = dPad;
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s = 0;
                self->step++;
#ifdef VERSION_PSP
                PLAYER.posX.val = self->posX.val;
                PLAYER.velocityX = 0;
#endif
            }
        }
        if (self->ext.et_801BBD90.unk94) {
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s = 1;
            self->step = 3;
        }
        break;
    case 3:
        if (!self->ext.et_801BBD90.unk94) {
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = 0;
            g_Player.demo_timer = 64;
        }
        if (AnimateEntity(D_us_80181550, self) == 0) {
            PlaySfxPositional(SFX_ELEVATOR_START);
            if (!self->ext.et_801BBD90.unk94) {
                g_unkGraphicsStruct.unk1C |= 1;
            }
            self->ext.et_801BBD90.unk88 = 0x18;
            self->step_s = 0;
            self->pose = 0;
            self->poseTimer = 0;
            if (self->ext.et_801BBD90.unk85 > self->ext.et_801BBD90.unk84) {
                self->step = 4;
            } else {
                self->step = 5;
                if (!self->ext.et_801BBD90.unk94) {
                    g_api.PlaySfx(SFX_VO_ALU_YELL);
                }
            }
        }
        break;
    case 4:
        if (!self->ext.et_801BBD90.unk94) {
            if (!self->ext.et_801BBD90.unk88) {
                MoveEntity();
                player->posY.i.hi = self->posY.i.hi - 4;
            } else {
                player->posY.i.hi = self->posY.i.hi - 4;
                MoveEntity();
                self->ext.et_801BBD90.unk88 -= 1;
            }
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = PAD_DOWN;
            g_Player.demo_timer = 2;
            g_Player.vram_flag |= VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        } else {
            MoveEntity();
        }
        posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        switch (self->step_s) {
        case 0:
            self->velocityY -= FIX(0.125);
            if (self->ext.et_801BBD90.unk7C != NULL) {
                if ((Random() % 10) == 0) {
                    prim = self->ext.et_801BBD90.unk7C;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->next->x1 = self->posX.i.hi + 0x10;
                        prim->next->y0 = self->posY.i.hi + 0x2C;
                        prim->next->r3 = self->ext.et_801BBD90.unk86;
                    }
                    self->ext.et_801BBD90.unk86 ^= 1;
                }
            }
            if (posY < D_us_80181568[self->ext.et_801BBD90.unk85]) {
                if (self->ext.et_801BBD90.unk85 == 2) {
                    g_api.PlaySfx(SFX_ELEVATOR_SLAM);
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi - 0x18;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk20;
                    self->velocityY = -self->velocityY;
                    self->step_s = 2;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi -= 0x18;
                            tempEntity->drawFlags |= ENTITY_ROTATE;
                            tempEntity->rotate = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                    self->ext.et_801BBD90.unk87 = 1;
                    self->velocityY /= 2;
                    self->step_s++;
                }
            }
            break;

        case 1:
            self->velocityY += FIX(1.0);
            if (posY > D_us_80181568[self->ext.et_801BBD90.unk85] + 8) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 2:
            self->velocityY -= FIX(2.0);
            if (self->velocityY < 0) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 3:
            self->ext.et_801BBD90.unk87 = 0;
            if (posY == D_us_80181568[self->ext.et_801BBD90.unk85]) {
                self->step_s = 0;
                self->step = 6;
            } else {
                if (posY > D_us_80181568[self->ext.et_801BBD90.unk85]) {
                    F(self->velocityY).i.hi = -1;
                } else {
                    F(self->velocityY).i.hi = 1;
                }
            }
            break;
        }
        break;

    case 5:
        if (!self->ext.et_801BBD90.unk94) {
            if (!self->ext.et_801BBD90.unk88) {
                MoveEntity();
                player->posY.i.hi = self->posY.i.hi - 4;
            } else {
                player->posY.i.hi = self->posY.i.hi - 4;
                MoveEntity();
                self->ext.et_801BBD90.unk88 -= 1;
            }
            g_api.func_8010DFF0(0, 1);
            g_api.func_8010E168(1, 0x20);
            g_Player.padSim = PAD_DOWN;
            g_Player.demo_timer = 2;
        } else {
            MoveEntity();
        }
        posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
        switch (self->step_s) {
        case 0:
            self->velocityY += FIX(0.25);
            if (self->ext.et_801BBD90.unk7C != NULL) {
                if (Random() % 10 == 0) {
                    prim = self->ext.et_801BBD90.unk7C;
                    prim = FindFirstUnkPrim2(prim, 2);
                    if (prim != NULL) {
                        UnkPolyFunc2(prim);
                        prim->next->x1 = self->posX.i.hi + 0x10;
                        prim->next->y0 = self->posY.i.hi + 0x2C;
                        prim->next->r3 = self->ext.et_801BBD90.unk86;
                        prim->next->r3 |= 0x10;
                    }
                    self->ext.et_801BBD90.unk86 ^= 1;
                }
            }
            if (posY > D_us_80181568[self->ext.et_801BBD90.unk85]) {
                self->ext.et_801BBD90.unk87 = 1;
                if (!self->ext.et_801BBD90.unk85) {
                    g_api.PlaySfx(SFX_ELEVATOR_SLAM);
                    self->velocityY = -self->velocityY / 2;
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi + 0x24;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk18;
                    self->step_s = 2;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi += 0x24;
                            tempEntity->drawFlags |= ENTITY_ROTATE;
                            tempEntity->rotate = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                } else {
                    g_api.PlaySfx(SFX_LEVER_METAL_BANG);
                    self->velocityY /= 2;
                    self->step_s = 1;
                }
            }
            break;

        case 1:
            self->velocityY -= FIX(1.5);
            if (posY < D_us_80181568[self->ext.et_801BBD90.unk85]) {
                self->velocityY = 0;
                self->step_s = 3;
            }
            break;

        case 2:
            self->velocityY += FIX(1.0);
            if (self->velocityY > 0) {
                self->velocityY -= FIX(0.75);
                if (posY > D_us_80181568[self->ext.et_801BBD90.unk85]) {
                    posX = self->posX.i.hi;
                    posY = self->posY.i.hi + 0x24;
                    g_api.CheckCollision(posX, posY, &collider, 0);
                    self->posY.i.hi += collider.unk18;
                    self->velocityY = 0;
                    self->step_s = 3;
                    for (i = 0; i < 3; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[224], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->posX.i.hi += (i * 8) - 8;
                            tempEntity->posY.i.hi += 0x24;
                            tempEntity->drawFlags |= ENTITY_ROTATE;
                            tempEntity->rotate = 0x400 - (i << 0xA);
                            tempEntity->params = 0x10;
                        }
                    }
                }
            }
            break;

        case 3:
            self->ext.et_801BBD90.unk87 = 0;
            if (posY == D_us_80181568[self->ext.et_801BBD90.unk85]) {
                self->step_s = 0;
                self->step = 6;
            } else {
                if (posY > D_us_80181568[self->ext.et_801BBD90.unk85]) {
                    F(self->velocityY).i.hi = -1;
                } else {
                    F(self->velocityY).i.hi = 1;
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            if (!self->ext.et_801BBD90.unk94) {
                player->posY.i.hi = self->posY.i.hi - 8;
            }
            g_unkGraphicsStruct.unk1C &= ~1;
            self->velocityY = 0;
            self->step_s++;
            break;

        case 1:
            if (!self->ext.et_801BBD90.unk94) {
                g_api.func_8010DFF0(0, 1);
                g_api.func_8010E168(1, 0x20);
                g_Player.padSim = 0;
                g_Player.demo_timer = 2;
            }
            if (AnimateEntity(D_us_8018155C, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case 2:
            self->ext.et_801BBD90.unk84 = self->ext.et_801BBD90.unk85;
            self->ext.et_801BBD90.unk94 = 0;
            self->step_s = 0;
            self->step = 2;
            break;
        }
        break;
    }
    prim = self->ext.et_801BBD90.unk90;
    if (prim != NULL) {
        func_us_801BC9A8(prim);
    }
    prim = self->ext.et_801BBD90.unk7C;
    while (prim != NULL) {
        if (prim->p3 & 8) {
            func_us_801BC598(prim);
        }
        prim = prim->next;
    }
}
