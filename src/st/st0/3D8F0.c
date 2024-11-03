// SPDX-License-Identifier: AGPL-3.0-or-later
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
        InitializeEntity(g_EInit3DObject);
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
        sp48 = g_api.func_800EDB58(PRIM_GT4, 15 * 15);
        if (sp48 == -1) {
            SetStep(7);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
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
                CreateEntityFromCurrentEntity(E_ID_24, sp44);
            }
        }
        if (var_s8 == 15 * 15) {
            DestroyEntity(self);
        }
        break;
    case 7:
        sp44 = self + 1;
        CreateEntityFromCurrentEntity(E_ID_24, sp44);
        DestroyEntity(self);
    }
}

extern SVECTOR D_801C1BC8[];
extern u8 D_801C23C8[16];

void EntityBackgroundVortex(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    u8 brightness; // writes into an array, later that array is used for colors
    u8 leftV;
    u8 rightV;
    s32 primIndex;
    s32 scale;
    s32 xSize;
    s32 ySize;
    s32 zSize;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX m;
    DRAWENV draw_env;
    DR_ENV* dr_env;
    RECT tw_rect;
    CVECTOR unused_Cvector;

    s32 size;
    s16 angle;
    s32 vectorIndex1;
    s32 vectorIndex2;
    s32 j;
    CVECTOR* scratchColor;
    s32 var_s2;
    s32 i;
    Primitive* prim;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInit3DObject);
        self->posX.i.hi = 0x80;
        self->posY.i.hi = 0x1A0;
        primIndex = g_api.func_800EDB58(PRIM_GT4, 0x110);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.bgVortex.unk9C = 0x5F0;
        self->ext.bgVortex.unk9E = 0xB0;
        self->ext.bgVortex.unkA0 = 0;
        self->ext.bgVortex.unkAE = 0xD0;
        // Fallthrough
    case 1:
        size = 0x60;
        scale = 0;
        brightness = 0x10;
        var_s2 = 0;
        angle = 0;
        for (j = 0; j < 16; j++) {
            scale = SquareRoot0(j * 0x120) * 4;
            for (i = 0; i < 16; i++) {
                xSize = (size * rcos(angle + i * 0x100)) >> 0xC;
                ySize = (size * rsin(angle + i * 0x100)) >> 0xC;
                zSize = scale;
                D_801C1BC8[var_s2].vx = xSize;
                D_801C1BC8[var_s2].vy = ySize;
                D_801C1BC8[var_s2].vz = zSize;
                var_s2 += 1;
            }
            D_801C23C8[j] = brightness;
            angle += 0x80;
            size += 0x1C;
            brightness += 0x28;
            if (brightness > 0xA0) {
                brightness = 0xA0;
            }
        }
        self->step++;
        break;
    case 2:
        prim = self->ext.prim;
        while (prim != NULL) {
            prim->tpage = 0x16;
            prim->clut = 0x19E;
            prim->u0 = prim->u2 = 0x40;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x40;
            prim->priority = 0x80;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
        prim = self->ext.prim;
        draw_env = g_CurrentBuffer->draw;

        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        draw_env.isbg = 0;
        draw_env.r0 = 0;
        draw_env.g0 = 0;
        draw_env.b0 = 0;
        draw_env.dtd = 0;
        draw_env.clip.x = 0;
        draw_env.ofs[0] = 0;
        tw_rect.x = 0;
        tw_rect.y = 0;
        tw_rect.w = 0x40;
        tw_rect.h = 0x40;
        draw_env.tw = tw_rect;
        SetDrawEnv(dr_env, &draw_env);
        prim->priority = 2;
        prim->drawMode = DRAW_UNK_1000;
        prim = prim->next;
        dr_env = g_api.func_800EDB08(prim);
        if (dr_env == NULL) {
            DestroyEntity(self);
            return;
        }
        prim->type = PRIM_ENV;
        prim->priority = 0x59;
        prim->drawMode = DRAW_UNK_800;
        prim = prim->next;
        self->step++;
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(-0.75);
            if (self->posY.i.hi < 0xA0) {
                self->posY.i.hi = 0xA0;
                self->step_s++;
            }
            break;
        case 1:
            self->ext.bgVortex.unkA4 += 16;
            self->ext.bgVortex.unkA6 += 8;
            self->ext.bgVortex.unkA8 += 32;
            self->ext.bgVortex.unkAA += 2;
            self->ext.bgVortex.unk9C =
                ((rsin(self->ext.bgVortex.unkA4) << 6) >> 0xC) + 0x5F0;
            self->ext.bgVortex.unk9E =
                ((rsin(self->ext.bgVortex.unkA6) << 7) >> 0xC) + 0xB0;
            self->ext.bgVortex.unkA0 =
                ((rsin(self->ext.bgVortex.unkA8) << 4) >> 0xC);
            self->ext.bgVortex.unkAE =
                ((rsin(self->ext.bgVortex.unkAA) * 24) >> 0xC) + 0xD0;
            break;
        }
        prim = self->ext.prim;
        prim = prim->next;
        prim = prim->next;
        leftV = prim->v0;
        rightV = prim->v2;
        leftV += 2;
        rightV += 2;

        if (rightV < leftV) {
            leftV = rightV;
            rightV = leftV + 0x40;
        }
        while (prim != NULL) {
            prim->v0 = prim->v1 = leftV;
            prim->v2 = prim->v3 = rightV;
            prim = prim->next;
        }
        self->ext.bgVortex.unk80 -= 4;
        SetGeomScreen(0xC0);
        SetGeomOffset(self->posX.i.hi, self->posY.i.hi);
        SetFarColor(0, 0, 0);
        SetFogNear(0x128, 0xC0);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = self->ext.bgVortex.unk80;
        rotVector.vx += self->ext.bgVortex.unk9C;
        rotVector.vy += self->ext.bgVortex.unk9E;
        rotVector.vz += self->ext.bgVortex.unkA0;

        RotMatrix(&rotVector, &m);
        SetRotMatrix(&m);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = 0xC0;
        transVector.vz += self->ext.bgVortex.unkAE;
        TransMatrix(&m, &transVector);
        SetTransMatrix(&m);
        // scratchpad memory
        scratchColor = (CVECTOR*)SP(0);
        for (i = 0; i < 16; i++, scratchColor++) {
            var_s2 = ((i & 1) * 2) + 1;
            scratchColor->b = (D_801C23C8[i] / var_s2);
            scratchColor->r = scratchColor->g = (D_801C23C8[i] / 2) / var_s2;
            scratchColor->cd = 4;
        }
        prim = self->ext.prim;
        prim = prim->next;
        prim = prim->next;
        unused_Cvector.r = 0x80;
        unused_Cvector.g = 0x80;
        unused_Cvector.b = 0x80;
        unused_Cvector.cd = 4;
        scratchColor = (CVECTOR*)SP(0);
        for (i = 0; i < 15; i++) {
            for (j = 0; j < 16; j++) {
                var_s2 = i * 0x10;
                vectorIndex1 = var_s2 + j;
                vectorIndex2 = var_s2 + ((j + 1) & 0xF);
                gte_ldv0(&D_801C1BC8[vectorIndex1]);
                gte_rtps();
                gte_stsxy(&prim->x0);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                gte_strgb(&prim->r0);
                prim->type = PRIM_GT4;
                gte_ldv0(&D_801C1BC8[vectorIndex2]);
                gte_rtps();
                gte_stsxy(&prim->x1);
                gte_ldrgb(&scratchColor[i]);
                gte_dpcs();
                if ((prim->y0 >= 0) || (prim->y1 >= 0)) {
                    gte_strgb(&prim->r1);
                    gte_ldv0(&D_801C1BC8[vectorIndex1] + 0x10);
                    gte_rtps();
                    if (prim->y0 <= 0x100 || prim->y1 <= 0x100) {
                        gte_stsxy(&prim->x2);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        gte_strgb(&prim->r2);
                        gte_ldv0(&D_801C1BC8[vectorIndex2] + 0x10);
                        gte_rtps();
                        gte_stsxy(&prim->x3);
                        gte_ldrgb(&scratchColor[i] + 1);
                        gte_dpcs();
                        if (prim->x0 <= 0x100 || prim->x1 <= 0x100 ||
                            prim->x2 <= 0x100 || prim->x3 <= 0x100) {
                            gte_strgb(&prim->r3);
                            if (prim->x0 >= 0 || prim->x1 >= 0 ||
                                prim->x2 >= 0 || prim->x3 >= 0) {
                                gte_stszotz(&zSize);
                                if (zSize < 0x55) {
                                    prim->priority = 0x58 - zSize;
                                } else {
                                    prim->priority = 3;
                                }
                                prim->drawMode = DRAW_COLORS;
                                prim = prim->next;
                            }
                        }
                    }
                }
            }
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
    }
}
