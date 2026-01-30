// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include <scratchpad.h>

static SVECTOR D_80182690 = {-8, -8, 0};
static SVECTOR D_80182698 = {8, -8, 0};
static SVECTOR D_801826A0 = {-8, 8, 0};
static SVECTOR D_801826A8 = {8, 8, 0};
static SVECTOR unused = {0, 0, 0};
extern unkstr_801C06B0 D_801C06B0;

void func_801BD8F0(Entity* self) {
    DRAWENV drawEnv;
    RECT cliprect;
    DR_ENV* dr_env;
    s16 angle;
    s32 xVar;
    s32 yVar;
    s32 i;
    s32 j;
    s32 var_s5;
    s32 var_s7;
    s32 var_s8;
    Primitive* prim;
    unkstr_801C06B0* unkStr;
    u32 primIndex;
    Entity* entity;
    SVECTOR* sp40;
    VECTOR* vec;
    MATRIX* m;
    SVECTOR* sp34;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInit3DObject);
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0;
        // fallthrough
    case 1:
        self->step++;
        break;
    case 2:
        primIndex = g_api.func_800EDB58(PRIM_GT4, 15 * 15);
        if (primIndex == -1) {
            SetStep(7);
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->step++;
        // fallthrough
    case 3:
#ifdef VERSION_PSP
        func_psp_0891B0DC(0x300, 0);
#else
        prim = self->ext.prim;
        drawEnv = g_CurrentBuffer->draw;
        if (drawEnv.ofs[0] == 0) {
            prim->tpage = 0x100;
        } else {
            prim->tpage = 0x104;
        }
        prim->type = PRIM_GT4;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0xEF;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 0xFF;
        prim->y0 = prim->y1 = 0;
        prim->y2 = prim->y3 = 0xEF;
        prim->priority = 0x69;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(7);
            return;
        }
        prim->type = PRIM_ENV;
        drawEnv.isbg = 1;
        drawEnv.r0 = 0;
        drawEnv.g0 = 0;
        drawEnv.b0 = 0;
        drawEnv.dtd = 0;
        cliprect.x = 0x300;
        cliprect.y = 0;
        cliprect.w = 0x100;
        cliprect.h = 0x100;
        drawEnv.clip = cliprect;
        drawEnv.ofs[0] = 0x300;
        drawEnv.ofs[1] = 0;
        SetDrawEnv(dr_env, &drawEnv);
        prim->priority = 0x68;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
        if (dr_env == NULL) {
            SetStep(7);
            break;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK_800;
#endif
        self->step++;
        break;
    case 4:
        prim = self->ext.prim;
#ifndef VERSION_PSP
        prim = prim->next;
        for (i = 0; i < 2; i++) {
            dr_env = LOW(prim->r1);
            dr_env->tag = 0;
            prim->type = PRIM_GT4;
            prim = prim->next;
        }
        prim = self->ext.prim;
#endif
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                xVar = j * 17;
                yVar = i * 16;
#ifdef VERSION_PSP
                prim->tpage = ((yVar & 0x100) >> 4 | 0x100 |
                               ((xVar + 0x300) & 0x3FF) >> 6) |
                              ((yVar & 0x200) << 2);
                var_s5 = xVar % 0x40;
                prim->u0 = prim->u2 = var_s5;
                prim->u1 = prim->u3 = var_s5 + 17;
#else
                prim->tpage = 0x10C;
                prim->u0 = prim->u2 = xVar;
                prim->u1 = prim->u3 = xVar + 17;
#endif
                prim->v0 = prim->v1 = yVar;
                prim->v2 = prim->v3 = yVar + 16;
                prim->x0 = prim->x2 = xVar;
                prim->x1 = prim->x3 = xVar + 17;
                prim->y0 = prim->y1 = yVar;
                prim->y2 = prim->y3 = yVar + 16;
                prim->r0 = 0x40;
                prim->g0 = prim->b0 = 0x30;

                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 0x6C;
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
        }
        self->step++;
        break;
    case 5:
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers[0].flags &= 0xFFFE;
        prim = self->ext.prim;
        unkStr = &D_801C06B0;
        for (i = 0; i < 15 * 15; i++, unkStr++) {
            xVar = prim->x0 + 8;
            yVar = prim->y0 + 8;
            xVar -= 0x80;
            yVar -= 0x80;
            unkStr->unkA = xVar;
            unkStr->unkE = yVar;
            unkStr->unk10 = 0x80;
            angle = ratan2(yVar, xVar);
            var_s7 = (xVar * xVar) + (yVar * yVar);
            xVar = rsin(angle) * 0x24;
            yVar = rcos(angle) * 0x24;
            var_s7 = SquareRoot0(var_s7);
            var_s8 = 0xC0 - var_s7;
            xVar = xVar * var_s8 / 0xC0;
            yVar = yVar * var_s8 / 0xC0;
            xVar >>= 0xC;
            yVar >>= 0xC;
            unkStr->unk0.x = xVar;
            unkStr->unk0.y = yVar;
            unkStr->unk14 = ((var_s7 * 3) / 2) - (Random() & 0x1F);
            if (unkStr->unk14 < 0) {
                unkStr->unk14 = 0;
            }
            unkStr->unk4 = 0;
            unkStr->unk6 = 0;
            prim = prim->next;
        }
        self->ext.GS_Props.pickupFlag = 1;
        self->step++;
        break;
    case 6:
        SetGeomScreen(0x80);
        SetGeomOffset(0x80, 0x80);
#ifndef VERSION_PC
        m = (MATRIX*)SPAD(0);
        sp40 = (SVECTOR*)SPAD(8);
        vec = (VECTOR*)SPAD(10);
        sp34 = (SVECTOR*)SPAD(14);
#else
        MATRIX sp38_;
        SVECTOR sp40_;
        VECTOR sp3c_;
        SVECTOR sp34_;
        m = &sp38_;
        sp40 = &sp40_;
        vec = &sp3c_;
        sp34 = &sp34_;
#endif
        sp34[0] = D_80182690;
        sp34[1] = D_80182698;
        sp34[2] = D_801826A0;
        sp34[3] = D_801826A8;
        unkStr = &D_801C06B0;
        prim = self->ext.prim;
        for (i = 0; i < 15 * 15; i++, unkStr++) {
            if ((unkStr->unk14) || (unkStr->unk10 > 0x180)) {
                prim = prim->next;
                continue;
            }
            sp40->vx = unkStr->unk4;
            sp40->vy = unkStr->unk6;
            sp40->vz = 0;
            RotMatrixYXZ(sp40, m);
#ifdef VERSION_PSP
            SetRotMatrix(m);
#else
            gte_SetRotMatrix(m);
#endif
            vec->vx = unkStr->unkA;
            vec->vy = unkStr->unkE;
            vec->vz = unkStr->unk10;
            gte_SetTransVector(vec);
            gte_ldv3c(sp34);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(&sp34[3]);
            gte_rtps();
            gte_stsxy((long*)&prim->x3);
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        unkStr = &D_801C06B0;
        prim = self->ext.prim;
        var_s8 = 0;
        for (i = 0; i < 15 * 15; i++, unkStr++) {
            if (unkStr->unk14) {
                unkStr->unk14--;
                prim = prim->next;
                continue;
            }
            unkStr->unk4 += unkStr->unk0.x;
            unkStr->unk6 += unkStr->unk0.y;
            unkStr->unk10 += 3;
            if (unkStr->unk10 > 0x180) {
                var_s8 += 1;
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        if (self->ext.GS_Props.pickupFlag) {
            if (var_s8 > 14) {
                self->ext.GS_Props.pickupFlag = 0;
                entity = self + 1;
                CreateEntityFromCurrentEntity(E_ID_24, entity);
            }
        }
        if (var_s8 == 15 * 15) {
            DestroyEntity(self);
        }
        break;
    case 7:
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID_24, entity);
        DestroyEntity(self);
        break;
    }
}
