// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo6/rbo6.h"

#include <scratchpad.h>

extern EInit g_EInitInteractable;

#define offsetof(st, m) (size_t)((size_t) & (((st*)0)->m))

#if TARGET == TARGET_PSP
extern s32 E_ID(UNK_30);
extern s32 E_ID(UNK_31);
#endif

extern s32 g_CutsceneFlags;
extern s32 g_BossFlag;
static s32 D_us_80181484 = 0;
static s32 D_us_80181488 = 0;
static SVECTOR D_us_8018148C[] = {
    {256, 512, 768, -64},
    {0, 0, 0, -4608},
    {0, 0, 1024, -17920},
    {512, 256, -512, -26880},
};
static SVECTOR D_us_801814AC = {102, -54, -33};
static SVECTOR D_us_801814B4 = {63, 54, -87};
static SVECTOR D_us_801814BC = {0, -54, -108};
static SVECTOR D_us_801814C4 = {0, -120, 0};
static SVECTOR D_us_801814CC = {63, -54, 87};
static SVECTOR D_us_801814D4 = {102, 54, 33};
static SVECTOR D_us_801814DC = {0, 120, 0};
static SVECTOR D_us_801814E4 = {0, 54, 108};
static SVECTOR D_us_801814EC = {-102, -54, -33};
static SVECTOR D_us_801814F4 = {-63, 54, -87};
static SVECTOR D_us_801814FC = {-63, -54, 87};
static SVECTOR D_us_80181504 = {-102, 54, 33};
static SVECTOR* D_us_8018150C[] = {
    &D_us_801814AC, &D_us_801814BC, &D_us_801814C4, &D_us_801814EC,
    &D_us_801814C4, &D_us_801814BC, &D_us_801814EC, &D_us_801814BC,
    &D_us_801814F4, &D_us_801814EC, &D_us_801814FC, &D_us_801814C4,
    &D_us_801814AC, &D_us_801814C4, &D_us_801814CC, &D_us_801814AC,
    &D_us_801814B4, &D_us_801814BC, &D_us_801814CC, &D_us_801814D4,
    &D_us_801814AC, &D_us_801814FC, &D_us_801814EC, &D_us_80181504,
    &D_us_801814B4, &D_us_801814AC, &D_us_801814D4, &D_us_801814C4,
    &D_us_801814FC, &D_us_801814CC, &D_us_801814BC, &D_us_801814B4,
    &D_us_801814F4, &D_us_801814F4, &D_us_80181504, &D_us_801814EC,
    &D_us_80181504, &D_us_801814F4, &D_us_801814DC, &D_us_801814D4,
    &D_us_801814CC, &D_us_801814E4, &D_us_80181504, &D_us_801814E4,
    &D_us_801814FC, &D_us_801814D4, &D_us_801814DC, &D_us_801814B4,
    &D_us_801814E4, &D_us_801814CC, &D_us_801814FC, &D_us_801814DC,
    &D_us_801814F4, &D_us_801814B4, &D_us_801814D4, &D_us_801814E4,
    &D_us_801814DC, &D_us_80181504, &D_us_801814DC, &D_us_801814E4,
    &D_us_801814FC, &D_us_801814E4, &D_us_801814E4, &D_us_801814B4,
    &D_us_801814DC, &D_us_801814DC, &D_us_801814DC, &D_us_801814E4,
    &D_us_801814E4, &D_us_801814E4, &D_us_801814DC, &D_us_801814DC,
};
static s16 D_us_8018162C[][3] = {
    {64, 9, 0x800}, {12, 100, 0x2AB}, {116, 100, -0x2AB}};
static SVECTOR D_us_80181640 = {0, 0, 0};

#if TARGET == TARGET_PSP
static SVECTOR D_us_801B3F34;
static s16 D_us_801B3F3C;
static s16 D_us_801B3F40;
static s16 D_us_801B3F44;
static s32 D_us_801B3F48;
#else
extern SVECTOR D_us_801B3F34;
extern s16 D_us_801B3F3C;
extern s16 D_us_801B3F40;
extern s16 D_us_801B3F44;
extern s32 D_us_801B3F48;
#endif

#if TARGET == TARGET_PSP

#define SHARD_TPAGE 0x110
#define SHARD_U 0x10
#define VORTEX_DRAW_X 0
#define VORTEX_DRAW_W 0x100
#define VORTEX_DRAW_H 0x100
#else
#define SHARD_TPAGE 0x114
#define SHARD_U 0x90
#define VORTEX_DRAW_X 0x180
#define VORTEX_DRAW_W 0x7F
#define VORTEX_DRAW_H 0x80
#endif

void func_us_801B1738(Entity* self) {
    s16 var_s7;
    s16 var_s6;
    u8* var_s5;
    MATRIX* m;
    s32* var_s3;
    u8 var_s2;
    s32 j;
    Primitive* prim;

    s32 primIndex;
    s32 i;
    s32 sp54;
    s32 priority;
    s32 sumX;
    s32 sumY;
    s32 sp64;
    s16* ptr_sp60;
    s32* ptr_sp5c;
    SVECTOR* ptr_sp58;
    CVECTOR* cVector;
    SVECTOR* sp4c;
    SVECTOR** vectors;
    SVECTOR* vec;
    VECTOR sp38;
    RECT clipRect;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    s16* pos;
    Entity* entity;

    FntPrint("d_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        self->zPriority = 0x80;
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers[0].flags &= 0xFFFE;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x2E);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->step = 0;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (prim == NULL) {
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
            self->step = 0;
            return;
        }
        prim->type = PRIM_ENV;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.et_801B1738.prim = prim;
        for (i = 0; i < 20; i++) {
            prim->type = PRIM_GT3;
#if TARGET == TARGET_PSP
            prim->clut = PAL_UNK_194;
            prim->tpage = SHARD_TPAGE;
#else
            prim->tpage = SHARD_TPAGE;
            prim->clut = PAL_UNK_194;
#endif
            prim->u0 = SHARD_U + 0x30;
            prim->v0 = 0x0D;
            prim->u1 = SHARD_U;
            prim->v1 = 0x60;
            prim->u2 = SHARD_U + 0x60;
            prim->v2 = 0x60;
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_801B1738.prim2 = prim;
        while (prim != NULL) {
            prim->priority = 0x80;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        ptr_sp60 = &self->ext.et_801B1738.unk84[0];
        ptr_sp58 = &D_us_8018148C[0];
        for (i = 0; i < 4; i++, ptr_sp60++, ptr_sp58++) {
            *ptr_sp60 = ptr_sp58->pad;
        }
        self->scaleX = 0x100;
        D_us_801B3F3C = 0x100;
        D_us_801B3F40 = 0x200;
        D_us_801B3F44 = 0x700;
        D_us_801B3F48 = 0;
        self->ext.et_801B1738.unkA4 = 4;
        self->ext.et_801B1738.unkA6 = 8;
        self->rotate = 2;
        self->ext.et_801B1738.unkA8 = 0;
        break;

    case 1:
        if (g_CutsceneFlags & 0x20) {
            D_us_80181484 = 1;
            D_us_801B3F48 = 0x10;
            self->step++;
        }
        break;

    case 2:
        D_us_801B3F48++;
        if (D_us_801B3F48 > 0x80) {
            D_us_801B3F48 = 0x80;
            self->step++;
        }
        break;

    case 3:
        if (g_BossFlag & 2) {
            self->step++;
        }
        break;

    case 4:
        if (self->ext.et_801B1738.unkA4 < 0x18) {
            self->ext.et_801B1738.unkA4 += 2;
        }
        if (self->ext.et_801B1738.unkA6 < 0x18) {
            self->ext.et_801B1738.unkA6 += 2;
        }
        if (self->rotate < ROT(45)) {
            self->rotate += 2;
        }
        self->ext.et_801B1738.unkA8 += 0x50;
        if (self->ext.et_801B1738.unkA8 > 0x1200) {
            D_us_80181488 = 1;
            self->ext.et_801B1738.timer = 0x40;
            entity = &g_Entities[159];
            CreateEntityFromCurrentEntity(E_ID(UNK_31), entity);
            self->step++;
        }
        break;

    case 5:
        if (D_us_801B3F48 < 0xA0) {
            D_us_801B3F48 += 2;
        }
        if (self->ext.et_801B1738.unkA4 > 0x10) {
            self->ext.et_801B1738.unkA4 -= 6;
        }
        if (self->ext.et_801B1738.unkA6 > 0x10) {
            self->ext.et_801B1738.unkA6 -= 6;
        }
        if (self->rotate > ROT(1.40625)) {
            self->rotate -= ROT(1.0546875);
        }
        if (!--self->ext.et_801B1738.timer) {
            self->step++;
        }
        break;

    case 6:
        D_us_801B3F48 -= 0xA;
        if (D_us_801B3F48 < 0x10) {
            D_us_801B3F48 = 0;
            self->ext.et_801B1738.timer = 0x60;
            self->step++;
        }
        break;

    case 7:
        prim = self->ext.et_801B1738.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if (!--self->ext.et_801B1738.timer) {
            DestroyEntity(self);
        }
        return;
    }

    prim = &g_PrimBuf[self->primIndex];
    drawEnv = g_CurrentBuffer->draw;
    drawEnv.isbg = 1;
    drawEnv.r0 = 0;
    drawEnv.g0 = 0;
    drawEnv.b0 = 0;
    clipRect.x = VORTEX_DRAW_X;
    clipRect.y = 0x100;
    clipRect.w = VORTEX_DRAW_W;
    clipRect.h = VORTEX_DRAW_H;
    drawEnv.clip = clipRect;
    drawEnv.ofs[0] = VORTEX_DRAW_X;
    drawEnv.ofs[1] = 0x100;
    dr_env = *(DR_ENV**)&prim->r1;
    SetDrawEnv(dr_env, &drawEnv);
    prim->priority = 0x27;
    prim->drawMode = DRAW_DEFAULT;
    prim = prim->next;
    prim->priority = 0x29;
    prim->drawMode = DRAW_UNK_800;

    i = g_Timer & 3;
    if (i < 3 && (rand() & 3)) {
        pos = D_us_8018162C[i];
        entity = AllocEntity(&g_Entities[192], &g_Entities[219]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(UNK_30), entity);
            entity->zPriority = 0x28;
            entity->rotate = pos[2];
            if (D_us_80181488) {
                entity->rotate += Random() * 2 - ROT(22.5);
            } else {
                entity->rotate += Random() - ROT(11.25);
            }
            entity->posX.i.hi = pos[0];
            entity->posY.i.hi = pos[1];
        }
    }

    D_us_801B3F34.vx += self->ext.et_801B1738.unkA4;
    D_us_801B3F34.vy += self->ext.et_801B1738.unkA6;
    D_us_801B3F34.vz += self->rotate;
    D_us_801B3F3C += 2;
    D_us_801B3F40 += 4;
    D_us_801B3F44 += 3;
    if (self->ext.et_801B1738.unkA8) {
        D_us_801B3F3C += 8;
        D_us_801B3F40 += 0x10;
        D_us_801B3F44 += 0xC;
    }

    m = (MATRIX*)SP(offsetof(RBO6_SCRATCHPAD, mat));
    vec = (SVECTOR*)SP(offsetof(RBO6_SCRATCHPAD, rot));
    ptr_sp5c = (s32*)SP(offsetof(RBO6_SCRATCHPAD, otz));
    cVector = (CVECTOR*)SP(offsetof(RBO6_SCRATCHPAD, color));
    cVector->r = cVector->g = cVector->b = 0x80;
    cVector->r =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rcos(D_us_801B3F3C)) >> 12);
    cVector->g =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rsin(D_us_801B3F40)) >> 12);
    cVector->b =
        D_us_801B3F48 + (((D_us_801B3F48 / 2) * rcos(D_us_801B3F44)) >> 12);
    cVector->cd = 5;
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    SetFarColor(0, 0, 0);
    SetFogNear(0x200, 0x600);
    *vec = D_us_801B3F34;
    RotMatrix(vec, m);
    SetRotMatrix(m);
    sp38.vx = 0;
    sp38.vy = 0;
    sp38.vz = -0x18;
    sp38.vz += self->ext.et_801B1738.unkA8;
#if TARGET == TARGET_PSP
    sp38.vz = 0x400;
#endif
    sp64 = sp38.vz >> 2;
    gte_ldtr(0, 0, sp38.vz);
    prim = self->ext.et_801B1738.prim;
    vectors = &D_us_8018150C[0];
    for (i = 0; i < 20; i++) {
        gte_ldv3(vectors[0], vectors[1], vectors[2]);
        gte_rtpt();
        gte_stsxy3_gt3(prim);
        *(CVECTOR*)&prim->r0 = *cVector;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        prim->drawMode = DRAW_COLORS | DRAW_UNK02;
        gte_nclip();
        gte_stopz((long*)ptr_sp5c);
        if (!self->ext.et_801B1738.unkA8 && *ptr_sp5c > 0) {
            prim->drawMode = DRAW_HIDE;
        }
        sumX = (prim->x0 & 0x100) + (prim->x1 & 0x100) + (prim->x2 & 0x100);
        sumY = (prim->y0 & 0x100) + (prim->y1 & 0x100) + (prim->y2 & 0x100);
        if (sumX > 0x300 || sumY > 0x300) {
            prim->drawMode = DRAW_HIDE;
        }
        gte_avsz3();
        gte_stszotz((long*)ptr_sp5c);
        prim->type = PRIM_GT3;
        priority = 0x80 - ((*ptr_sp5c - sp64) >> 2);
        if (!self->ext.et_801B1738.unkA8) {
            priority -= 2;
        }
        if (priority > 0x1F8) {
            priority = 0x1F8;
        }
        if (priority < 4) {
            priority = 4;
        }
        prim->priority = priority;
        vectors += 3;
        prim = prim->next;
    }

    if (!D_us_80181484 || (g_BossFlag & 1)) {
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;
    }

    ptr_sp60 = &self->ext.et_801B1738.unk84[0];
    for (i = 0; i < 4; i++, ptr_sp60++) {
        *ptr_sp60 += 0x38;
        if (*ptr_sp60 > 0 && *ptr_sp60 <= 0x38) {
            g_api.PlaySfx(SFX_ELECTRICITY);
        }
        if (*ptr_sp60 > 0x2000) {
            *ptr_sp60 = -(*ptr_sp60 & 0xFFF);
        }
    }
    prim = self->ext.et_801B1738.prim2;
    ptr_sp60 = &self->ext.et_801B1738.unk84[0];
    ptr_sp58 = &D_us_8018148C[0];
    m = (MATRIX*)SP(offsetof(RBO6_SCRATCHPAD, mat));
    vec = (SVECTOR*)SP(offsetof(RBO6_SCRATCHPAD, rot));
    sp4c = (SVECTOR*)SP(offsetof(RBO6_SCRATCHPAD, segEnds));
    var_s5 = (u8*)SP(offsetof(RBO6_SCRATCHPAD, shade));
    ptr_sp5c = (s32*)SP(offsetof(RBO6_SCRATCHPAD, otz));
    SetGeomScreen(0x600);
    SetGeomOffset(0x80, 0x80);
    gte_ldtr(0, 0, 0x600);

    sp4c[0].vx = 0;
    sp4c[0].vy = -0xC;
    sp4c[1].vx = 0;
    sp4c[1].vy = 0xC;
    sp54 = 0;
    for (i = 0; i < 4; i++, ptr_sp60++, ptr_sp58++) {
        var_s7 = *ptr_sp60;
        if (var_s7 >= 0) {
            vec->vx += ptr_sp58->vx;
            vec->vy += ptr_sp58->vy;
            vec->vz += ptr_sp58->vz;
            RotMatrix(vec, &m[1]);
            gte_SetColorMatrix(&m[1]);
            var_s2 = 0;
            var_s3 = (s32*)SP(offsetof(RBO6_SCRATCHPAD, sxy));
            for (j = 0; j < 7; j++) {
                var_s6 = 0x90 - ((var_s7 * 0x78) / 0x1800);
                if (var_s6 < 0x18) {
                    var_s6 = 0x18;
                }
                sp4c[0].vz = -var_s6;
                sp4c[1].vz = -var_s6;
#if TARGET == TARGET_PSP
                RotMatrix(&D_us_80181640, m);
                RotMatrixY(var_s7, m);
                RotMatrixX(vec->vx, m);
                RotMatrixY(vec->vy, m);
                RotMatrixZ(vec->vz, m);
#else
                LOW(m->m[0][0]) = 0;
                LOW(m->m[0][2]) = 0;
                LOW(m->m[1][1]) = 0;
                LOW(m->m[2][0]) = 0;
                LOW(m->m[2][2]) = 0;
                m->m[0][0] = 0x1000;
                m->m[1][1] = 0x1000;
                m->m[2][2] = 0x1000;

                RotMatrixY(var_s7, m);

                gte_ldclmv(m);
                gte_lcir();
                gte_stclmv(m);

                gte_ldclmv(&m->m[0][1]);
                gte_lcir();
                gte_stclmv(&m->m[0][1]);

                gte_ldclmv(&m->m[0][2]);
                gte_lcir();
                gte_stclmv(&m->m[0][2]);
#endif
                gte_SetRotMatrix(m);
                gte_ldv01c(sp4c);
                gte_rtpt();
                gte_stsxy01c(&var_s3[j * 2]);
                gte_stszotz((long*)&ptr_sp5c[j]);

                if (var_s7 < 0) {
                    var_s2++;
                    if (var_s2 > 4) {
                        var_s2 = 4;
                    }
                    var_s5[j] = 0x80 - (var_s2 * 0x20);
                } else {
                    var_s2 = 0;
                    var_s5[j] = 0x80;
                }
                var_s7 -= ratan2(0x10, var_s6);
                if (var_s7 > 0x1800) {
                    var_s5[j] = 0x60;
                    sp54 = 1;
                } else {
                    sp54 = 0;
                }
#if TARGET != TARGET_PSP
                if (var_s7 > 0x1800) {
                    var_s5[j] = 0;
                }
#endif
            }
            var_s3 = (s32*)SP(offsetof(RBO6_SCRATCHPAD, sxy));
            for (j = 0; j < 6; j++) {
                prim->tpage = 0x1A;
                prim->clut = PAL_UNK_194;
                prim->u0 = prim->u2 = j * 0x10 + 0x90;
                prim->u1 = prim->u3 = prim->u0 + 0xF;
                if (g_Timer & 2) {
                    prim->v0 = prim->v1 = 0xC0;
                    prim->v2 = prim->v3 = 0xD0;
                } else {
                    prim->v0 = prim->v1 = 0xD0;
                    prim->v2 = prim->v3 = 0xC0;
                }
                LOW(prim->x0) = var_s3[0];
                LOW(prim->x1) = var_s3[2];
                LOW(prim->x2) = var_s3[1];
                LOW(prim->x3) = var_s3[3];
                prim->priority = ptr_sp5c[j] - 0x100;
                prim->drawMode = DRAW_UNK02;
                var_s2 = (var_s5 + j)[1];
                if (var_s2 != 0x80) {
                    prim->r0 = prim->g0 = prim->b0 = var_s5[j];
                    LOW(prim->r2) = LOW(prim->r0);
                    prim->r1 = prim->g1 = prim->b1 = (var_s5 + j)[1];
                    LOW(prim->r3) = LOW(prim->r1);
                    prim->drawMode |=
                        DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                }
                prim = prim->next;
                var_s3 += 2;
            }
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

static u8 D_us_80181648[] = {2, 1, 2, 2, 2, 3,  2, 4,  2, 5,  2, 6,  2,    7,
                             2, 8, 2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 0xFF, 0};

void func_us_801B2864(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->flags |= FLAG_UNK_10000;
        self->palette = PAL_UNK_19E;
        self->palette = 0x2E2;
        self->palette = 0x2E5;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->drawFlags = ENTITY_ROTATE;
        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->facingLeft = Random() & 1;
        angle = self->rotate;
        if (self->facingLeft) {
            self->rotate = -(s16)angle;
        }
        self->velocityX = rsin((s32)(s16)angle) * 0x28;
        self->velocityY = rcos((s32)(s16)angle) * -0x28;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0xE0;
        self->scaleY = 0x140;
        if (D_us_80181488 != 0) {
            self->scaleX = 0x120;
            self->scaleY = 0x120;
        }
        /* fall through */
    case 1:
        MoveEntity();
        if (AnimateEntity(D_us_80181648, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}
