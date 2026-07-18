// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_57);
extern s32 E_ID(ID_31);
extern s32 E_ID(ID_30);
extern s32 E_ID(ID_2F);
#endif

void func_us_801BFA34(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority += 8;
        self->palette = PAL_FLAG(PAL_UNK_19E);
        self->animSet = 2;
        self->animCurFrame = 9;
        self->blendMode = BLEND_TRANSP;
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = 64;
        self->scaleY = 64;
        self->rotate = ROT(-90);
        self->velocityX = FIX(-1.25);
    } else {
        self->scaleX += 4;
        self->scaleY += 14;
        self->posX.val += self->velocityX;

        self->poseTimer++;
        if ((self->poseTimer % 2) == 0) {
            self->animCurFrame++;
        }

        if (self->poseTimer > 23) {
            DestroyEntity(self);
        }
    }
}

static SVECTOR v0_0 = {-8, -8, -8};
static SVECTOR v0_1 = {8, -8, -8};
static SVECTOR v0_2 = {-8, 8, -8};
static SVECTOR v0_3 = {8, 8, -8};
static SVECTOR v0_4 = {-8, -8, 8};
static SVECTOR v0_5 = {8, -8, 8};
static SVECTOR v0_6 = {-8, 8, 8};
static SVECTOR v0_7 = {8, 8, 8};

static SVECTOR v1_0 = {-16, -8, -8};
static SVECTOR v1_1 = {16, -8, -8};
static SVECTOR v1_2 = {-16, 8, -8};
static SVECTOR v1_3 = {16, 8, -8};
static SVECTOR v1_4 = {-16, -8, 8};
static SVECTOR v1_5 = {16, -8, 8};
static SVECTOR v1_6 = {-16, 8, 8};
static SVECTOR v1_7 = {16, 8, 8};

static SVEC4 vertices0[] = {
    {&v0_0, &v0_1, &v0_2, &v0_3}, {&v0_1, &v0_5, &v0_3, &v0_7},
    {&v0_4, &v0_5, &v0_0, &v0_1}, {&v0_4, &v0_0, &v0_6, &v0_2},
    {&v0_2, &v0_3, &v0_6, &v0_7}, {&v0_5, &v0_4, &v0_7, &v0_6},
};

static SVEC4 vertices1[] = {
    {&v1_0, &v1_1, &v1_2, &v1_3}, {&v1_1, &v1_5, &v1_3, &v1_7},
    {&v1_4, &v1_5, &v1_0, &v1_1}, {&v1_4, &v1_0, &v1_6, &v1_2},
    {&v1_2, &v1_3, &v1_6, &v1_7}, {&v1_5, &v1_4, &v1_7, &v1_6},
};

static SVECTOR u0 = {FLT(0), FLT(0), FLT(1)};
static SVECTOR u1 = {FLT(-1), FLT(0), FLT(0)};
static SVECTOR u2 = {FLT(0), FLT(1), FLT(0)};
static SVECTOR u3 = {FLT(1), FLT(0), FLT(0)};
static SVECTOR u4 = {FLT(0), FLT(-1), FLT(0)};
static SVECTOR u5 = {FLT(0), FLT(0), FLT(-1)};

// 1.0 / sqrt(3)
#define iSqrt3 0.5773502691896258

static SVECTOR n0 = {FLT(iSqrt3), FLT(iSqrt3), FLT(iSqrt3)};
static SVECTOR n1 = {FLT(iSqrt3), FLT(iSqrt3), FLT(-iSqrt3)};
static SVECTOR n2 = {FLT(iSqrt3), FLT(-iSqrt3), FLT(iSqrt3)};
static SVECTOR n3 = {FLT(iSqrt3), FLT(-iSqrt3), FLT(-iSqrt3)};
static SVECTOR n4 = {FLT(-iSqrt3), FLT(iSqrt3), FLT(iSqrt3)};
static SVECTOR n5 = {FLT(-iSqrt3), FLT(iSqrt3), FLT(-iSqrt3)};
static SVECTOR n6 = {FLT(-iSqrt3), FLT(-iSqrt3), FLT(iSqrt3)};
static SVECTOR n7 = {FLT(-iSqrt3), FLT(-iSqrt3), FLT(-iSqrt3)};

static SVECTOR* unused[] = {&u0, &u1, &u2, &u3, &u4, &u5};

static SVEC4 normals[] = {
    {&n0, &n4, &n2, &n6}, {&n4, &n5, &n6, &n7}, {&n1, &n5, &n0, &n4},
    {&n1, &n0, &n3, &n2}, {&n2, &n6, &n3, &n7}, {&n5, &n1, &n7, &n3},
};

static MATRIX colorMatrix = {{
    {FLT(1.0 / 2), FLT(1.0 / 3), FLT(1.0 / 2)},
    {FLT(1.0 / 2), FLT(1.0 / 3), FLT(1.0 / 2)},
    {FLT(1.0 / 2), FLT(1.0 / 3), FLT(1.0 / 2)},
}};

STATIC_PAD_DATA(8);

void func_us_801BFB40(Entity* self) {
    long p, flag, otz;
    Collider collider;
    SVECTOR rot;
    VECTOR trans;
    MATRIX m;
    u8 pad[16];
    MATRIX lightMatrix;
    CVECTOR color;
    u8 pad2[2];
    Primitive* prim;
    Entity* tempEntity;
    SVEC4* vertPtr;
    SVEC4* normPtr;
    s32 primIndex;
    s16 posX, posY;
    s32 i;
    s32 opz;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 6);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BFB40.unk7C = prim;
            while (prim != NULL) {
                prim->tpage = 0xE;
                prim->clut = PAL_NULL;
                prim->u0 = 0xE9;
                prim->u1 = prim->u0 + 0xE;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0x31;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0xE;
                prim->v3 = prim->v2;
                prim->r0 = prim->b0 = prim->g0 = 0x80;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                if (self->params) {
                    prim->priority = 0xC0;
                } else {
                    prim->priority = 0xA0;
                }
                prim->drawMode = DRAW_UNK02;
                prim = prim->next;
            }
            break;
        }
        DestroyEntity(self);
        return;

    case 1:
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(1.0 / 16);
            self->velocityY = 0;
            self->step_s++;
            if (self->params) {
                self->velocityX = -(Random() & 7) * FIX(0.125);
                self->velocityY = FIX(-2.25) - (Random() & 3) * FIX(0.25);
            }
            break;

        case 1:
            if (!self->params) {
                self->ext.et_801BFB40.unk80.vx += 0x40;
                self->ext.et_801BFB40.unk80.vy -= 0x10;
                self->ext.et_801BFB40.unk80.vz -= 0x10;
            } else {
                self->ext.et_801BFB40.unk80.vx += 0x40;
                self->ext.et_801BFB40.unk80.vy += 0x80;
                self->ext.et_801BFB40.unk80.vz -= 0x20;
            }
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!self->params) {
                if (self->velocityX > FIX(-1.5)) {
                    self->velocityX -= FIX(0.25 / 16);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            if (!self->params) {
                posY += 8;
            } else {
                posY += 4;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (!self->params && (self->velocityX > FIX(-1.0)) &&
                (collider.effects & EFFECT_SOLID)) {
                if ((g_Timer & 7) == 0) {
                    self->posY.i.hi += collider.unk18;
                }
                self->velocityY = 0;
                self->ext.et_801BFB40.unk80.vx = 0;
                self->ext.et_801BFB40.unk80.vy = 0;
                self->ext.et_801BFB40.unk80.vz = 0;
            } else if (collider.effects & EFFECT_SOLID) {
                g_api.PlaySfx(SFX_STOMP_HARD_B);
                self->posY.i.hi += collider.unk18;
                self->velocityY = -self->velocityY / 2;
                if (self->params) {
                    if (self->velocityY > FIX(-0.25)) {
                        tempEntity =
                            AllocEntity(&g_Entities[64], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->params = 0x10;
                        }
                        DestroyEntity(self);
                        return;
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        tempEntity =
                            AllocEntity(&g_Entities[64], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_ID(ID_2F), self, tempEntity);
                            tempEntity->params = i;
                        }
                    }
                    if (self->velocityY > FIX(-1.25)) {
                        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
                        for (i = 0; i < 3; i++) {
                            tempEntity =
                                AllocEntity(&g_Entities[64], &g_Entities[256]);
                            if (tempEntity != NULL) {
                                CreateEntityFromEntity(
                                    E_ID(ID_31), self, tempEntity);
                                tempEntity->params = i + 1;
                            }
                        }
                        DestroyEntity(self);
                        return;
                    }
                }
            }
            break;
        }
        prim = self->ext.et_801BFB40.unk7C;
        SetGeomScreen(0x400);
        rot.vx = self->ext.et_801BFB40.unk80.vx;
        rot.vy = self->ext.et_801BFB40.unk80.vy;
        rot.vz = self->ext.et_801BFB40.unk80.vz;
        RotMatrix(&rot, &m);
        trans.vx = 0;
        trans.vy = 0;
        trans.vz = 0x408;
        if (self->params) {
            trans.vz = 0x800;
        }
        TransMatrix(&m, &trans);
        SetRotMatrix(&m);
        SetTransMatrix(&m);
        if (!self->params) {
            color.r = 0xA0;
            color.g = 0xA0;
            color.b = 0xA0;
            color.cd = prim->type;
        } else {
            color.r = 0x90;
            color.g = 0x90;
            color.b = 0x90;
            color.cd = prim->type;
        }
        RotMatrix(&rot, &lightMatrix);
        SetBackColor(0x40, 0x40, 0x40);
        SetLightMatrix(&lightMatrix);
        SetColorMatrix(&colorMatrix);
        SetFarColor(0x60, 0x60, 0x60);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        if (!self->params) {
            vertPtr = vertices1;
        } else {
            vertPtr = vertices0;
        }
        normPtr = normals;
        prim = self->ext.et_801BFB40.unk7C;
        for (i = 0; i < 6; i++) {
            opz = RotAverageNclip4(
                vertPtr->v0, vertPtr->v1, vertPtr->v2, vertPtr->v3,
                (long*)(&prim->x0), (long*)(&prim->x1), (long*)(&prim->x2),
                (long*)(&prim->x3), &p, &otz, &flag);
            if (opz <= 0) {
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
                NormalColorCol(normPtr->v0, &color, (CVECTOR*)(&prim->r0));
                NormalColorCol(normPtr->v1, &color, (CVECTOR*)(&prim->r1));
                NormalColorCol(normPtr->v2, &color, (CVECTOR*)(&prim->r2));
                NormalColorCol(normPtr->v3, &color, (CVECTOR*)(&prim->r3));
            }
            vertPtr++;
            normPtr++;
            prim = prim->next;
        }
        break;
    }
}

static s32 D_us_80181948[][2] = {
    {FIX(0.0), FIX(-3.0)},
    {FIX(-0.125), FIX(-2.25)},
    {FIX(-0.25), FIX(-4)},
    {FIX(-0.75), FIX(-3.5)},
};

static s16 D_us_80181968[] = {8, 12, 4, 6};

static s16 D_us_80181970[] = {0x180, 0x100, 0x200, 0x1C0};

static u8 D_us_80181978[] = {3, 1, 3, 2, 3, 3, 3, 4, 3, 5, 3, 6, -1, 0};

void func_us_801C01F0(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    Primitive* prim;
    s32 primIndex;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 8;
        self->animCurFrame = 0;
        self->palette = PAL_FLAG(4);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.et_801BFB40.unk7C = prim;
            UnkPolyFunc2(prim);
            prim->tpage = 0xE;
            prim->clut = 2;
            prim->u0 = 0x70;
            prim->u1 = 0x78;
            prim->u2 = prim->u0;
            prim->u3 = prim->u1;
            prim->v0 = 0xF6;
            prim->v1 = prim->v0;
            prim->v2 = 0xFD;
            prim->v3 = prim->v2;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_UNK02;
            prim->next->x1 = self->posX.i.hi;
            prim->next->y0 = self->posY.i.hi;
            if (!self->params) {
                LOH(prim->next->r2) = 4;
            } else {
                LOH(prim->next->r2) = D_us_80181968[self->params];
            }
            LOH(prim->next->b2) = LOH(prim->next->r2);
            prim->next->b3 = 0x80;
        } else {
            DestroyEntity(self);
            return;
        }
        if (!self->params) {
            self->velocityX = 0;
            self->velocityY = 0;
        } else {
            self->velocityX = D_us_80181948[self->params][0];
            self->velocityY = D_us_80181948[self->params][1];
        }
        self->step++;
        break;

    case 2:
        if (self->params && !AnimateEntity(D_us_80181978, self)) {
            self->animCurFrame = 0;
        }
        MoveEntity();
        self->velocityY += FIX(0.125);
        prim = self->ext.et_801BFB40.unk7C;
        if (!self->params) {
            LOH(prim->next->tpage) -= 0x200;
        } else {
            LOH(prim->next->tpage) -= D_us_80181970[self->params];
        }
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        UnkPrimHelper(prim);
        if (self->velocityY >= 0) {
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            posY += LOH(prim->next->r2) / 2 - 2;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->posY.i.hi += collider.unk18;
                if (self->velocityX > FIX(-1.0)) {
                    self->velocityX -= FIX(1.0 / 16);
                }
                self->velocityY = -self->velocityY / 2;
                if (self->velocityY > FIX(-0.25)) {
                    if (LOH(prim->next->r2) > 6) {
                        tempEntity =
                            AllocEntity(&g_Entities[64], &g_Entities[256]);
                        if (tempEntity != NULL) {
                            CreateEntityFromEntity(
                                E_INTENSE_EXPLOSION, self, tempEntity);
                            tempEntity->params = 0x10;
                        }
                    }
                    DestroyEntity(self);
                    return;
                }
            }
        }
        break;
    }
}

static s16 D_us_80181988[] = {
    0x528, 0x529, 0x52A, 0x52B, 0x4B2, 0x4B8, 0x4BE, 0x4D5,
};

static u8 D_us_80181998[] = {32, 92, 48, 93, 48, 94, 48, 95, 48, 96, -1, 0};

void func_us_801C05DC(Entity* self) {
    Entity* tempEntity;
    s32 tilePos;
    s32 i;
    u8 animRet;

    u8 max = 0;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A10);
        if (g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            max = 4;
            self->animCurFrame = 0;
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            self->zPriority -= 8;
            self->step++;
            tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID(ID_30), self, tempEntity);
            }
            tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID(ID_30), self, tempEntity);
                tempEntity->posY.i.hi -= 0x40;
            }
        }
        break;

    case 2:
        animRet = AnimateEntity(D_us_80181998, self);
        if (!animRet) {
            self->animCurFrame = 0;
            max = 4;
            self->step++;
            break;
        }
        max = self->pose - 2;
        if (max > 0x80) {
            max = 0;
        }
        if (self->poseTimer == 0 && self->pose > 1) {
            tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID(ID_30), self, tempEntity);
                tempEntity->posY.i.hi -= 0x30 - (max * 16);
            }
            tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_ID(ID_31), self, tempEntity);
                tempEntity->posX.i.hi += 7;
                tempEntity->posY.i.hi -= 0x38 - (max * 16);
            }
        }
        switch (self->step_s) {
        case 0:
            self->step_s++;
            break;

        case 1:
            if ((g_Timer % 8) == 0) {
                tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_ID(ID_2F), self, tempEntity);
                    tempEntity->posY.i.hi -= 0x3D;
                    tempEntity->posX.i.hi -= (Random() & 3) * 8 - 4;
                }
            }
            if (g_Timer % 24 == 0) {
                tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, tempEntity);
                    tempEntity->posX.i.hi -= 4;
                    tempEntity->params = 0x10;
                }
            }
            if (g_Timer % 32 == 0) {
                tempEntity = AllocEntity(&g_Entities[64], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->params = 0x11;
                }
            }
            break;
        }
        break;

    case 3:
        if (g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            max = 4;
        } else {
            max = 0;
        }
        break;
    }

    for (tilePos = 0x6F, i = 0; i < 4; tilePos += 16, i++) {
        g_Tilemap.fg[tilePos] = D_us_80181988[i];
    }
    for (tilePos = 0x6F, i = 0; i < max; tilePos += 16, i++) {
        g_Tilemap.fg[tilePos] = D_us_80181988[i + 4];
    }
}

static u16 D_us_801819A4[] = {
    0x02B, 0x02C, 0x023, 0x1BC, 0x001, 0x002, 0x023, 0x01C,
    0x003, 0x004, 0x023, 0x024, 0x029, 0x02A, 0x023, 0x01C,
    0x02B, 0x02C, 0x023, 0x024, 0x001, 0x002, 0x023, 0x0A2,
};

static u16 D_us_801819D4[] = {
    0x02B, 0x02C, 0x0FA, 0x1BC, 0x1D8, 0x1D9, 0x1DA, 0x1DB,
    0x1DC, 0x1DD, 0x1DE, 0x1DF, 0x1E7, 0x1E8, 0x1E9, 0x1EA,
    0x1EB, 0x1EC, 0x1ED, 0x1EE, 0x001, 0x002, 0x09E, 0x0A2,
};

void func_us_801C0A40(Entity* self) {
    s32 i, j;
    u8 index;
    s32 tilePos;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A10);
        self->animCurFrame = 0;
        if (!g_CastleFlags[NO1_UNKNOWN_FLAG]) {
            self->step = 2;
            break;
        }
        /* fallthrough */
    case 1:
        tilePos = 0x15F0;
        for (index = 0, i = 0; i < 6; i++) {
            for (j = 0; j < 4; j++) {
                g_Tilemap.fg[tilePos + j] = D_us_801819D4[index];
                index++;
            }
            tilePos += 0x30;
        }
        self->step = 3;
        break;
    case 2:
        tilePos = 0x15F0;
        for (index = 0, i = 0; i < 6; i++) {
            for (j = 0; j < 4; j++) {
                g_Tilemap.fg[tilePos + j] = D_us_801819A4[index];
                index++;
            }
            tilePos += 0x30;
        }
        self->step = 3;
    }
}

static u8 D_us_80181A04[] = {1, 114, 1, 115, 1, 116, -1, 0};

static u16 D_us_80181A0C[][2] = {
    {0x3A1, 0x3A2}, {0x3CA, 0x3BC}, {0x40E, 0x3FC}, {0x438, 0x410},
    {0x5AE, 0x5AF}, {0x5B0, 0x5B1}, {0x5B2, 0x5B3}, {0x5B4, 0x5B5},
};

// in the doppleganger room, maybe rotating door
void func_us_801C0B9C(Entity* self) {
    Entity* nextEntity;
    s32 i;
    s32 params;
    s32 fgIndex;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801809C8);
        self->animCurFrame = 0;
        self->ext.et_801C0B9C.unk84 = 0;
        if (!self->params) {
            nextEntity = self + 1;
            for (i = 1; i < 4; i++, nextEntity++) {
                CreateEntityFromCurrentEntity(E_ID(ID_57), nextEntity);
                nextEntity->params = i;
            }

            for (i = 0; i < 4; i++, nextEntity++) {
                CreateEntityFromCurrentEntity(E_ID(ID_57), nextEntity);
                nextEntity->params = i + 0x100;
            }
        }
        self->posY.i.hi = 0x68 - g_Tilemap.scrollY.i.hi;
        if (self->params & 0x100) {
            self->posX.i.hi = 0x1F0 - g_Tilemap.scrollX.i.hi;
        } else {
            self->posX.i.hi = 0x10 - g_Tilemap.scrollX.i.hi;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_80181A04, self)) {
            self->velocityY = FIX(4);
            self->step++;
        }
        break;
    case 3:
        MoveEntity();
        self->velocityY += FIX(0.125);

        params = self->params & 0xFF;
        posY = (((3 - params) * 0x10) + 0x60) + g_Tilemap.scrollY.i.hi;
        if (posY < self->posY.i.hi) {
            if (params != 4) {
                nextEntity = self + 1;
                nextEntity->ext.et_801C0B9C.unk84 = 1;
            }
            self->posY.i.hi = posY;
            fgIndex = 0xC0;
            if (self->params & 0x100) {
                g_api.PlaySfx(SFX_EXPLODE_FAST_A);
                fgIndex = 0xDE;
            }
            fgIndex += ((3 - params) << 5);
            (&g_Tilemap.fg[fgIndex])[0] = D_us_80181A0C[7 - params][0];
            (&g_Tilemap.fg[fgIndex])[1] = D_us_80181A0C[7 - params][1];
            self->velocityY = 0;
            self->step++;
        }
        break;
    case 4:
        if (g_pads[0].pressed & PAD_UP) {
            self->step++;
        }
        break;
    case 5:
        fgIndex = 0xC0;
        params = self->params & 0xFF;
        if (self->params & 0x100) {
            fgIndex = 0xDE;
        }

        fgIndex += ((3 - params) << 5);
        (&g_Tilemap.fg[fgIndex])[0] = D_us_80181A0C[3 - params][0];
        (&g_Tilemap.fg[fgIndex])[1] = D_us_80181A0C[3 - params][1];
        self->step++;
    case 7:
        break;
    case 6:
        if (self->params & 0x100) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        MoveEntity();
        posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
        if (posX < -0x20 || posX > 0x220) {
            self->step++;
        }
        break;
    }
}
