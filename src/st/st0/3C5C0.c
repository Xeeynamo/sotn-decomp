// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"

static SVECTOR D_801824E8[] = {
    {256, 512, 768, -64},
    {0, 0, 0, -768},
    {0, 0, 1024, -1536},
    {512, 256, -512, -2304},
};
static SVECTOR D_80182508 = {34, -18, -11};
static SVECTOR D_80182510 = {21, 18, -29};
static SVECTOR D_80182518 = {0, -18, -36};
static SVECTOR D_80182520 = {0, -40, 0};
static SVECTOR D_80182528 = {21, -18, 29};
static SVECTOR D_80182530 = {34, 18, 11};
static SVECTOR D_80182538 = {0, 40, 0};
static SVECTOR D_80182540 = {0, 18, 36};
static SVECTOR D_80182548 = {-34, -18, -11};
static SVECTOR D_80182550 = {-21, 18, -29};
static SVECTOR D_80182558 = {-21, -18, 29};
static SVECTOR D_80182560 = {-34, 18, 11};
static SVECTOR* D_80182568[] = {
    &D_80182508, &D_80182518, &D_80182520, &D_80182548, &D_80182520,
    &D_80182518, &D_80182548, &D_80182518, &D_80182550, &D_80182548,
    &D_80182558, &D_80182520, &D_80182508, &D_80182520, &D_80182528,
    &D_80182508, &D_80182510, &D_80182518, &D_80182528, &D_80182530,
    &D_80182508, &D_80182558, &D_80182548, &D_80182560, &D_80182510,
    &D_80182508, &D_80182530, &D_80182520, &D_80182558, &D_80182528,
    &D_80182518, &D_80182510, &D_80182550, &D_80182550, &D_80182560,
    &D_80182548, &D_80182560, &D_80182550, &D_80182538, &D_80182530,
    &D_80182528, &D_80182540, &D_80182560, &D_80182540, &D_80182558,
    &D_80182530, &D_80182538, &D_80182510, &D_80182540, &D_80182528,
    &D_80182558, &D_80182538, &D_80182550, &D_80182510, &D_80182530,
    &D_80182540, &D_80182538, &D_80182560, &D_80182538, &D_80182540,
    &D_80182558, &D_80182540, &D_80182540, &D_80182510, &D_80182538,
    &D_80182538, &D_80182538, &D_80182540, &D_80182540, &D_80182540,
    &D_80182538, &D_80182538,
#ifndef VERSION_PSP
    NULL,        NULL,
#endif
};

#ifdef VERSION_PSP
extern SVECTOR D_pspeu_09279DC0; // bss
#endif

// Defines for the locations of scratchpad values
#define offsetof(st, m) (size_t)((size_t) & (((st*)0)->m)) // __builtin_offsetof

void func_801BC5C0(Entity* self) {
#ifdef VERSION_PC
    u8 sp[sizeof(ST0_SCRATCHPAD)];
#endif
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
    s32 sp64;
    s16* ptr_sp60;
    s32* ptr_sp5c;
    SVECTOR* ptr_sp58;
    s32 sp54;
    CVECTOR* cVector;
    SVECTOR* sp4c;
    SVECTOR** vectors;
    SVECTOR* vec;
    VECTOR sp38;

    FntPrint("d_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInit3DObject);
        self->zPriority = 0xC0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x34);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.et_801BC5C0.prim1 = prim;
        for (i = 0; i < 20; i++) {
            prim->type = PRIM_GT3;
            prim->tpage = 0x1A;
            prim->clut = PAL_UNK_194;
            prim->u0 = 0x30;
            prim->v0 = 0x40;
            prim->u1 = 0x48;
            prim->v1 = 0x40;
            prim->u2 = 0x3C;
            prim->v2 = 0x58;
            prim->x3 = 0;
            prim->y3 = 0;
            prim->u3 = 0;
            prim->priority = 0xC0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.et_801BC5C0.unk80 = prim;
        while (prim != NULL) {
            prim->priority = 0xC0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        ptr_sp60 = &self->ext.et_801BC5C0.unk84[0];
        ptr_sp58 = &D_801824E8[0];
        for (i = 0; i < 4; i++, ptr_sp60++, ptr_sp58++) {
            *ptr_sp60 = ptr_sp58->pad;
        }
        self->scaleX = 0x400;
        self->velocityX = 0;
        self->velocityY = 0;
        self->ext.et_801BC5C0.unkA0 = 0;
        self->ext.et_801BC5C0.unk9C = 0x40;
        self->step = 1;
        break;

    case 3:
        self->posX.val += self->velocityX;
        self->velocityX += self->ext.et_801BC5C0.unkA0;
        if (self->facingLeft) {
            self->ext.et_801BC5C0.unkA0 += 0x60;
        } else {
            self->ext.et_801BC5C0.unkA0 -= 0x60;
        }
        if (self->posX.i.hi > 0x180 || self->posX.i.hi < -0x80) {
            DestroyEntity(self);
            break;
        }
        // Fallthrough!
    case 2:
        self->rotate += 8;
        self->ext.et_801BC5C0.unkA4 += 0x18;
        self->ext.et_801BC5C0.unkA6 += 0x50;
        m = (MATRIX*)SP(offsetof(ST0_SCRATCHPAD, m));
        vec = (SVECTOR*)SP(offsetof(ST0_SCRATCHPAD, vec));
        ptr_sp5c = (s32*)SP(offsetof(ST0_SCRATCHPAD, sp5c));
        cVector = (CVECTOR*)SP(offsetof(ST0_SCRATCHPAD, sp50));

        cVector->r = cVector->g = cVector->b = 0x80;
        cVector->cd = 5;
        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        SetFarColor(0x60, 0, 0);
        SetFogNear(0x180, 0x100);
        vec->vx = self->ext.et_801BC5C0.unkA4;
        vec->vy = self->ext.et_801BC5C0.unkA6;
        vec->vz = self->rotate;
        RotMatrix(vec, m);
        SetRotMatrix(m);
        sp38.vx = 0;
        sp38.vy = 0;
        sp38.vz = self->scaleX + 0x100;

        sp64 = sp38.vz >> 2;
        gte_ldtr(0, 0, sp38.vz);
        prim = self->ext.prim;

        vectors = &D_80182568[0];
        for (i = 0; i < 20; i++) {
            if (prim->u3) {
                prim->y3 += 12;
                prim->x3 += 6;
                gte_ldtr(prim->x3, 0, sp38.vz + prim->y3);
            } else {
                gte_ldtr(0, 0, sp38.vz);
            }
            gte_ldv3(vectors[0], vectors[1], vectors[2]);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldrgb(cVector);
            gte_dpcs();
            gte_strgb(&prim->r0);
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            gte_avsz3();
            gte_stszotz((long*)ptr_sp5c);
            if (self->step > 2) {
                if (prim->x0 > (self->posX.i.hi + 0x10)) {
                    prim->u3 = 1;
                }
            }
            prim->type = PRIM_GT3;
            prim->priority = 0xC0 - ((*ptr_sp5c - sp64) >> 2);
            if (prim->priority > 0x1F8) {
                prim->priority = 0x1F8;
            }
            vectors += 3;
            prim = prim->next;
        }

        self->scaleX -= 8;
        if (self->scaleX < 0x80) {
            self->scaleX = 0x80;
            if (self->ext.et_801BC5C0.unk9E) {
                if (!--self->ext.et_801BC5C0.unk9E) {
                    SetStep(3);
                }
            }
        }
        // Fallthrough!
    case 1:
        ptr_sp60 = &self->ext.et_801BC5C0.unk84[0];
        for (i = 0; i < 4; i++, ptr_sp60++) {
            *ptr_sp60 += 0x38;
        }
        prim = self->ext.et_801BC5C0.unk80;
        ptr_sp60 = &self->ext.et_801BC5C0.unk84[0];

        ptr_sp58 = &D_801824E8[0];
        m = (MATRIX*)SP(offsetof(ST0_SCRATCHPAD, m));
        vec = (SVECTOR*)SP(offsetof(ST0_SCRATCHPAD, vec));
        sp4c = (SVECTOR*)SP(offsetof(ST0_SCRATCHPAD, sp4c));
        var_s5 = (u8*)SP(offsetof(ST0_SCRATCHPAD, var_s5));
        ptr_sp5c = (s32*)SP(offsetof(ST0_SCRATCHPAD, sp5c));
        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        gte_ldtr(0, 0, 0x100);

        sp4c[0].vx = 0;
        sp4c[0].vy = -0xC;
        sp4c[1].vx = 0;
        sp4c[1].vy = 0xC;
        sp54 = 0;
        for (i = 0; i < 4; i++, ptr_sp60++, ptr_sp58++) {
            var_s7 = *ptr_sp60;
            if (var_s7 >= 0) {
                vec->vx = ptr_sp58->vx;
                vec->vy = ptr_sp58->vy;
                vec->vz = ptr_sp58->vz;
                RotMatrix(vec, &m[1]);
                gte_SetColorMatrix(&m[1]);
                var_s2 = 0;
                var_s3 = (s32*)SP(offsetof(ST0_SCRATCHPAD, var_s3));
                for (j = 0; j < 9; j++) {
                    var_s6 = 0x70 - ((var_s7 * 0x5E) / 0x1800);
                    if (var_s6 < 0x12) {
                        var_s6 = 0x12;
                    }
                    sp4c[0].vz = -var_s6;
                    sp4c[1].vz = -var_s6;
#ifdef VERSION_PSP
                    RotMatrix(&D_pspeu_09279DC0, m);
                    RotMatrixY(var_s7, m);
                    RotMatrixX(vec->vx, m);
                    RotMatrixY(vec->vy, m);
                    RotMatrixZ(vec->vz, m);
                    SetRotMatrix(m);
#else
                    // This seems to be creating an identity matrix?
                    // First we zero it out, then we write the proper diagonal
                    // elements. But how to zero it out? This works I guess.
                    LOW(m->m[0][0]) = 0;
                    LOW(m->m[0][2]) = 0;
                    LOW(m->m[1][1]) = 0;
                    LOW(m->m[2][0]) = 0;
                    LOW(m->m[2][2]) = 0;
                    // Now make the diagonal stuffs
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

                    gte_SetRotMatrix(m);
#endif
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
                }
                var_s3 = (s32*)SP(offsetof(ST0_SCRATCHPAD, var_s3));
                for (j = 0; j < 8; j++) {
                    prim->tpage = 0x1A;
                    prim->clut = PAL_UNK_19F;

                    prim->u0 = prim->u2 = j * 0x10 + 0x7F;
                    prim->u1 = prim->u3 = prim->u0 + 0xF;
                    prim->v0 = prim->v1 = 0xE7;
                    prim->v2 = prim->v3 = 0xFF;
                    LOW(prim->x0) = var_s3[0];
                    LOW(prim->x1) = var_s3[2];
                    LOW(prim->x2) = var_s3[1];
                    LOW(prim->x3) = var_s3[3];
                    prim->priority = (ptr_sp5c[j] + 0x80);
                    prim->drawMode = DRAW_UNK02;
                    var_s2 = (var_s5 + j)[1];
                    if (var_s2 != 0x80) {
                        prim->r0 = prim->g0 = prim->b0 = var_s5[j];
                        LOW(prim->r2) = LOW(prim->r0);
                        prim->r1 = prim->g1 = prim->b1 = (var_s5 + j)[1];
                        LOW(prim->r3) = LOW(prim->r1);
                        prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE |
                                          DRAW_COLORS | DRAW_TRANSP;
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
        if (self->ext.et_801BC5C0.unk9C) {
            if (!--self->ext.et_801BC5C0.unk9C) {
                SetStep(2);
                self->ext.et_801BC5C0.unk9E = 0x40;
            }
        }
    }
}
