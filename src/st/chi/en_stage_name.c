// SPDX-License-Identifier: AGPL-3.0-or-later
/*
 * File: en_stage_name.c
 * Overlay: CHI
 * Description: ENTITY - Stage name popup
 */

#include "chi.h"

#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

#ifdef VERSION_PSP
#define STAGE_NAME_LOAD_GFX
#define NUM_PRIMS 181
#define STAGE_NAME_BOX_LEFT_X 8
#define STAGE_NAME_BOX_RIGHT_X 248

extern u32 D_91CE570; // Defined in global address space

static SVECTOR points_left = {-112, 0, -20};
static SVECTOR points_right = {112, 0, -20};
static SVECTOR normals = {0, 0, FIX(1.0 / 16.0)};
static MATRIX color_matrix = {{{0, FIX(-1.0 / 32.0), FIX(1.0 / 32.0)},
                               {0, 0, FIX(1.0 / 16.0)},
                               {0, FIX(1.0 / 32.0), FIX(1.0 / 32.0)}},
                              {0, 0, 0}};

static u8 stage_name_en[] = {
#include "gen/stage_name_en.h"
};
static u8 stage_name_it[] = {
#include "gen/stage_name_it.h"
};
static u8 stage_name_sp[] = {
#include "gen/stage_name_sp.h"
};
static u8 stage_name_ge[] = {
#include "gen/stage_name_ge.h"
};
static u8 stage_name_fr[] = {
#include "gen/stage_name_fr.h"
};

enum StageNameSteps {
    STAGE_NAME_INIT = 0,
    STAGE_NAME_RENDER = 4,
};

enum StageNameSubSteps {
    STAGE_NAME_RENDER_INIT,
    STAGE_NAME_DRAW_BOX,
    STAGE_NAME_DRAW_TEXT_IN,
    STAGE_NAME_HOLD_TEXT,
    STAGE_NAME_SHRINK_TEXT,
    STAGE_NAME_SHRINK_BOX,
};

static u_long* gfxBank[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

static u8* stage_name_gfx[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it};

static void LoadStageNameGraphics(void) {
    gfxBank[3] = (u_long*)stage_name_gfx[g_UserLanguage - 1];
    func_91040A0(gfxBank);
}

// This is banner version with turning drum style text and shrinks the text out.
// prims 12-181 appear to be completely unused
void EntityStageNamePopup(Entity* self) {
    s32 p, flag;
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    MATRIX lightMtx;
    CVECTOR color;
    s32 leftSideX[5];
    s32 rightSideX[5];
    CVECTOR colors[5];
    s16 z[6];
    Primitive* prim;
    s32 i, j;
    u8 primsSet;
    s32 primIndex;
    s16 nextX1;
    s16 nextY0;
    s16 xStartVal;
    s16* rotSlicePtr;

    if (D_91CE570) {
        LoadStageNameGraphics();
    }

    switch (self->step) {
    case STAGE_NAME_INIT:
        if (g_CastleFlags[STAGE_FLAG]) {
            DestroyEntity(self);
            return;
        }

        g_CastleFlags[STAGE_FLAG]++; // Unusual way of setting the flag
        InitializeEntity(g_EInitInteractable);
        LoadStageNameGraphics();

        self->ext.stpopupj.unk8C = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, NUM_PRIMS);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.stpopupj.firstTextPrim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F; // Black to white gradient
            if (i != 0) {
                prim->clut = PAL_UNK_19D; // Light grey to black gradient
            }
            prim->x2 = prim->x0 = 16;
            prim->y1 = prim->y0 = 157;
            prim->x3 = prim->x1 = 240;
            prim->y3 = prim->y2 = 197;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = 39;
            prim->r0 = 120;
            prim->g0 = 120;
            prim->b0 = 168;
            if (i != 0) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = 192 - i;
            prim->drawMode = DRAW_COLORS;
            if (i != 0) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }
        self->ext.stpopupj.boxPrim = prim;
        prim->type = PRIM_G4;
        prim->tpage = 26;
        prim->clut = PAL_FILL_WHITE; // All white palette
        prim->u0 = 0;
        prim->u1 = 64;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 192;
        prim->v1 = prim->v0;
        prim->v2 = 255;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = STAGE_NAME_BOX_LEFT_X;
        prim->y1 = prim->y0 = 155;
        prim->x3 = prim->x1 = STAGE_NAME_BOX_RIGHT_X;
        prim->y3 = prim->y2 = 199;
        prim->r0 = 16;
        prim->g0 = 40;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 56;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 176;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
        prim = prim->next;
        self->ext.stpopupj.firstRollingTextPrim = prim;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                prim->tpage = 17;
                prim->clut = PAL_UNK_19F; // Black to white gradient
                prim->x2 = prim->x0 = 16;
                prim->x3 = prim->x1 = 240;
                prim->y1 = prim->y0 = (i * 10) + 157;
                prim->y3 = prim->y2 = prim->y0 + 10;
                prim->u2 = prim->u0 = 0;
                prim->u1 = prim->u3 = 128;
                prim->v0 = prim->v1 = (i * 8) + (j * 32);
                prim->v2 = prim->v3 = prim->v0 + 8;
                prim->r0 = 120;
                prim->g0 = 120;
                prim->b0 = 168;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 192;
                prim->drawMode = DRAW_HIDE | DRAW_COLORS;
                prim = prim->next;
            }
        }
        self->step = STAGE_NAME_RENDER;
    case STAGE_NAME_RENDER:
        switch (self->step_s) {
        case STAGE_NAME_RENDER_INIT:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode = DRAW_HIDE;
            prim = self->ext.stpopupj.firstRollingTextPrim;
            for (i = 0; i < 8; i++) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 177;
            prim->y2 = prim->y3 = 177;
            self->ext.stpopupj.depth = 1044;
            self->ext.stpopupj.rotationSlices[0] = ROT(-270);
            self->ext.stpopupj.rotationSlices[1] = ROT(-270);
            self->ext.stpopupj.rotationSlices[2] = ROT(-270);
            self->ext.stpopupj.rotationSlices[3] = ROT(-270);
            self->ext.stpopupj.rotationSlices[4] = ROT(-270);
            self->step_s++;
            break;
        case STAGE_NAME_DRAW_BOX:
            primsSet = 0;
            prim = self->ext.stpopupj.boxPrim;
            if (prim->y0 > 155) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                primsSet |= 1;
            }

            if (prim->x0 > STAGE_NAME_BOX_LEFT_X * 2) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                primsSet |= 1;
            }

            if (!primsSet) {
                self->step_s++;
                self->ext.stpopupj.timer = 0;
            }
            break;
        case STAGE_NAME_DRAW_TEXT_IN:
            if (self->ext.stpopupj.rotationSlices[4] < ROT(90)) {
                self->ext.stpopupj.rotationSlices[4] += 64; // ~5.62°
            } else {
                self->ext.stpopupj.rotationSlices[4] = ROT(90);
            }
            if (self->ext.stpopupj.rotationSlices[4] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[3] < 341) { // ~29.97°
                    self->ext.stpopupj.rotationSlices[3] += 62;   // ~5.45°
                } else {
                    self->ext.stpopupj.rotationSlices[3] = 341;
                }
            }
            if (self->ext.stpopupj.rotationSlices[3] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[2] < 0) {
                    self->ext.stpopupj.rotationSlices[2] += 60; // ~5.27°
                } else {
                    self->ext.stpopupj.rotationSlices[2] = 0;
                }
            }
            if (self->ext.stpopupj.rotationSlices[2] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[1] < -341) {
                    self->ext.stpopupj.rotationSlices[1] += 58; // ~5.1°
                } else {
                    self->ext.stpopupj.rotationSlices[1] = -341;
                }
            }
            if (self->ext.stpopupj.rotationSlices[1] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[0] < ROT(-90)) {
                    self->ext.stpopupj.rotationSlices[0] += 56; // ~4.92°
                } else {
                    self->ext.stpopupj.rotationSlices[0] = ROT(-90);
                    self->ext.stpopupj.timer = 64;
                    self->step_s++;
                }
            }
            break;
        case STAGE_NAME_HOLD_TEXT:
            prim = self->ext.stpopupj.firstRollingTextPrim;
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 4; i++) {
                    if (j == 0) {
                        prim->x2 = prim->x0 = 16;
                        prim->x1 = prim->x3 = 128;
                    } else {
                        prim->x0 = prim->x2 = 128;
                        prim->x3 = prim->x1 = 240;
                    }
                    prim->y0 = prim->y1 = (i * 10) + 157;
                    prim->y2 = prim->y3 = (i * 10) + 167;
                    prim = prim->next;
                }
            }

            if (!--self->ext.stpopupj.timer) {
                rotSlicePtr = &self->ext.stpopupj.rotationSlices[0];
                for (i = 0; i < 5; i++) {
                    *rotSlicePtr -= ROT(720); // Equivalent to FLT(2) and 0x2000
                    rotSlicePtr++;
                }
                self->step_s++;
            }
            return;
        case STAGE_NAME_SHRINK_TEXT:
            rotSlicePtr = &self->ext.stpopupj.rotationSlices[0];
            for (i = 0; i < 5; i++) {
                *rotSlicePtr += 80; // ~7.03°
                rotSlicePtr++;
            }
            self->ext.stpopupj.depth += 64;
            if (self->ext.stpopupj.rotationSlices[4] > 0) {
                prim = self->ext.stpopupj.firstRollingTextPrim;
                for (i = 0; i < 8; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                self->step_s++;
            }
            break;
        case STAGE_NAME_SHRINK_BOX:
            prim = self->ext.stpopupj.boxPrim;
            prim->y0 += 2;
            prim->y1 = prim->y0;
            prim->y2 -= 2;
            prim->y3 = prim->y2;
            prim->x0 = prim->x2 += 2;
            prim->x1 = prim->x3 -= 2;
            if (prim->y0 > prim->y2) {
                DestroyEntity(self);
                return;
            }
        }
        // Part of STAGE_NAME_RENDER, runs every frame except during
        // RENDER->HOLD_TEXT
        prim = self->ext.stpopupj.firstRollingTextPrim;
        rotSlicePtr = &self->ext.stpopupj.rotationSlices[0];
        SetGeomScreen(1024);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = self->ext.stpopupj.depth;
        TransMatrix(&mtx, &transVector);
        SetTransMatrix(&mtx);
        color.r = 120;
        color.g = 120;
        color.b = 168;
        color.cd = prim->type;
        SetColorMatrix(&color_matrix);
        SetBackColor(64, 64, 64);
        SetGeomOffset(128, 177);
        for (i = 0; i < 5; i++) {
            rotVector.vx = *rotSlicePtr;
            rotVector.vy = 0;
            rotVector.vz = 0;
            RotMatrix(&rotVector, &mtx);
            SetRotMatrix(&mtx);
            RotMatrix(&rotVector, &lightMtx);
            SetLightMatrix(&lightMtx);
            z[i] = RotTransPers(
                &points_left, (long*)&leftSideX[i], (long*)&p, (long*)&flag);
            z[i] = RotTransPers(
                &points_right, (long*)&rightSideX[i], (long*)&p, (long*)&flag);
            NormalColorCol(&normals, &color, &colors[i]);
            rotSlicePtr++;
        }
        prim = self->ext.stpopupj.firstRollingTextPrim;
        for (j = 0; j < 2; j++) {
            rotSlicePtr = &self->ext.stpopupj.rotationSlices[0];
            for (i = 0; i < 4; i++) {
                rotSlicePtr++;
                if (j == 0) {
                    LOW(prim->x0) = LOW(leftSideX[i]);
                    LOW(prim->x1) = LOW(rightSideX[i]);
                    LOW(prim->x2) = LOW(leftSideX[i + 1]);
                    LOW(prim->x3) = LOW(rightSideX[i + 1]);
                    prim->x1 = prim->x3 = 128;
                    if (*rotSlicePtr > 0) {
                        prim->x2 = prim->x0 = 16;
                    }
                } else {
                    LOW(prim->x0) = LOW(leftSideX[i]);
                    LOW(prim->x1) = LOW(rightSideX[i]);
                    LOW(prim->x2) = LOW(leftSideX[i + 1]);
                    LOW(prim->x3) = LOW(rightSideX[i + 1]);
                    prim->x0 = prim->x2 = 128;
                    if (*rotSlicePtr > 0) {
                        prim->x3 = prim->x1 = 240;
                    }
                }
                LOW(prim->r0) = LOW(colors[i].r);
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(colors[i + 1].r);
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;
            }
        }
    }
}
#else
// func_801AD0EC: StageNamePopupHelper
// func_801AD2BC: [E_STAGE_NAME_POPUP] EntityStageNamePopup
#include "../e_stage_name_us.h"
#endif
