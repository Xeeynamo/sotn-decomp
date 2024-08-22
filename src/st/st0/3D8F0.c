#include "st0.h"

typedef struct {
    Point16 unk0;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s16 unk14;
} unkstr_801C06B0;

extern SVECTOR D_80182690;
extern SVECTOR D_80182698;
extern SVECTOR D_801826A0;
extern SVECTOR D_801826A8;
extern unkstr_801C06B0 D_801C06B0;

void func_801BD8F0(Entity* self) {
    DRAWENV drawEnv;
    RECT cliprect;
    DR_ENV* dr_env;

    Primitive* prim;
    s32 var_s8;
    s32 var_s7;
    s32 i;
    s32 yVar;
    s32 var_s5;
    s32 j;
    s32 xVar;
    unkstr_801C06B0* var_s3;
    s16 angle;
    s32 sp48;
    Entity* sp44;
    SVECTOR* sp40;
    VECTOR* sp3c;
    MATRIX* sp38;
    SVECTOR* sp34;

    switch (self->step) {
    case 0:
        InitializeEntity(D_801805D4);
        g_GpuBuffers[0].draw.r0 = 0;
        g_GpuBuffers[0].draw.g0 = 0;
        g_GpuBuffers[0].draw.b0 = 0;
        g_GpuBuffers[1].draw.r0 = 0;
        g_GpuBuffers[1].draw.g0 = 0;
        g_GpuBuffers[1].draw.b0 = 0;
        /* fallthrough */
    case 1:
        self->step++;
        return;
    case 2:
        sp48 = g_api.func_800EDB58(4, 15 * 15);
        if (sp48 == -1) {
            SetStep(7);
            return;
        }
        self->flags |= FLAG_UNK_800000;
        self->primIndex = sp48;
        prim = &g_PrimBuf[sp48];
        self->ext.prim = prim;
        for (; prim != NULL; prim = prim->next) {
            prim->drawMode = DRAW_HIDE;
        }
        self->step += 1;
    case 3:
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
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x6A;
        prim->drawMode = DRAW_UNK_800;
        self->step++;
        return;
    case 4:
        prim = self->ext.prim;
        prim = prim->next;
        for (i = 0; i < 2; i++) {
            dr_env = LOW(prim->r1);
            dr_env->tag = 0;
            prim->type = PRIM_GT4;
            prim = prim->next;
        }
        prim = self->ext.prim;
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 15; j++) {
                xVar = j * 17;
                yVar = i * 16;
                prim->tpage = 0x10C;
                prim->u0 = prim->u2 = xVar;
                prim->u1 = prim->u3 = xVar + 17;
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
        return;
    case 5:
        var_s3 = &D_801C06B0;
        g_Tilemap.flags &= 0xFFFE;
        g_BgLayers[0].flags &= 0xFFFE;
        prim = self->ext.prim;
        for (i = 0; i < 15 * 15; i++, var_s3++) {
            xVar = prim->x0 + 8;
            yVar = prim->y0 + 8;
            xVar -= 0x80;
            yVar -= 0x80;
            var_s3->unkA = xVar;
            var_s3->unkE = yVar;
            var_s3->unk10 = 0x80;
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
            var_s3->unk0.x = xVar;
            var_s3->unk0.y = yVar;
            var_s3->unk14 = ((var_s7 * 3) / 2) - (Random() & 0x1F);
            if (var_s3->unk14 < 0) {
                var_s3->unk14 = 0;
            }
            var_s3->unk4 = 0;
            var_s3->unk6 = 0;
            prim = prim->next;
        }
        self->ext.GS_Props.pickupFlag = 1;
        self->step++;
        return;
    case 6:
        SetGeomScreen(0x80);
        SetGeomOffset(0x80, 0x80);
#ifndef VERSION_PC
        sp38 = (MATRIX*)SPAD(0);
        sp40 = (SVECTOR*)SPAD(8);
        sp3c = (VECTOR*)SPAD(10);
        sp34 = (SVECTOR*)SPAD(14);
#else
        MATRIX sp38_;
        SVECTOR sp40_;
        VECTOR sp3c_;
        SVECTOR sp34_;
        sp38 = &sp38_;
        sp40 = &sp40_;
        sp3c = &sp3c_;
        sp34 = &sp34_;
#endif
        sp34[0] = D_80182690;
        sp34[1] = D_80182698;
        sp34[2] = D_801826A0;
        sp34[3] = D_801826A8;
        var_s3 = &D_801C06B0;
        prim = self->ext.prim;
        for (i = 0; i < 15 * 15; i++, var_s3++) {
            if ((var_s3->unk14) || (var_s3->unk10 > 0x180)) {
                prim = prim->next;
                continue;
            }
            sp40->vx = var_s3->unk4;
            sp40->vy = var_s3->unk6;
            sp40->vz = 0;
            RotMatrixYXZ(sp40, sp38);
            gte_SetRotMatrix(sp38);
            sp3c->vx = var_s3->unkA;
            sp3c->vy = var_s3->unkE;
            sp3c->vz = var_s3->unk10;
            gte_SetTransVector(sp3c);
            gte_ldv3c(sp34);
            gte_rtpt();
            gte_stsxy3_gt3(prim);
            gte_ldv0(&sp34[3]);
            gte_rtps();
            gte_stsxy(&prim->x3);
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        var_s3 = &D_801C06B0;
        prim = self->ext.prim;
        var_s8 = 0;
        for (i = 0; i < 15 * 15; i++, var_s3++) {
            if (var_s3->unk14) {
                var_s3->unk14--;
                prim = prim->next;
                continue;
            }
            var_s3->unk4 += var_s3->unk0.x;
            var_s3->unk6 += var_s3->unk0.y;
            var_s3->unk10 += 3;
            if (var_s3->unk10 > 0x180) {
                var_s8 += 1;
                prim->drawMode = DRAW_HIDE;
            }
            prim = prim->next;
        }
        if (self->ext.GS_Props.pickupFlag) {
            if (var_s8 > 14) {
                self->ext.GS_Props.pickupFlag = 0;
                sp44 = self + 1;
                CreateEntityFromCurrentEntity(0x24, sp44);
            }
        }
        if (var_s8 == 15 * 15) {
            DestroyEntity(self);
        }
        break;
    case 7:
        sp44 = self + 1;
        CreateEntityFromCurrentEntity(0x24, sp44);
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/st0/nonmatchings/3D8F0", EntityBackgroundVortex);
