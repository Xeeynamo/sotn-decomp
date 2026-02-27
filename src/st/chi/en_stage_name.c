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
#define STAGE_NAME_BOX_RIGHT_X 0xF8

extern u32 D_91CE570; // Defined in global address space

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

static SVECTOR points_left = {-112, 0, -20};
static SVECTOR points_right = {112, 0, -20};
static SVECTOR normal = {FLT(0.0), FLT(0.0), FLT(1.0)};
static MATRIX color_matrix = {{{FLT(0.0), FLT(-0.5), FLT(0.5)},
                               {FLT(0.0), FLT(0.0), FLT(1.0)},
                               {FLT(0.0), FLT(0.5), FLT(0.5)}}};

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
    s16 z[5];
    Primitive* prim;
    s32 i, j;
    u8 primsSet;
    s32 primIndex;
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
            prim->tpage = 0x11;
            prim->clut = PAL_UNK_19F;
            if (i != 0) {
                prim->clut = PAL_UNK_19D;
            }
            prim->x2 = prim->x0 = 0x10;
            prim->y1 = prim->y0 = 0x9D;
            prim->x3 = prim->x1 = 0xF0;
            prim->y3 = prim->y2 = 0xC5;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 0x80;
            prim->v2 = prim->v3 = 0x27;
            prim->r0 = 120;
            prim->g0 = 120;
            prim->b0 = 168;
            if (i != 0) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xC0 - i;
            prim->drawMode = DRAW_COLORS;
            if (i != 0) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }
        self->ext.stpopupj.boxPrim = prim;
        prim->type = PRIM_G4;
        prim->tpage = 0x1A;
        prim->clut = PAL_FILL_WHITE;
        prim->u0 = 0;
        prim->u1 = 0x40;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 0xC0;
        prim->v1 = prim->v0;
        prim->v2 = 0xFF;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = STAGE_NAME_BOX_LEFT_X;
        prim->y1 = prim->y0 = 0x9B;
        prim->x3 = prim->x1 = STAGE_NAME_BOX_RIGHT_X;
        prim->y3 = prim->y2 = 0xC7;
        prim->r0 = 16;
        prim->g0 = 40;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 56;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 0xB0;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
        prim = prim->next;
        self->ext.stpopupj.firstRollingTextPrim = prim;
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 4; i++) {
                prim->tpage = 0x11;
                prim->clut = PAL_UNK_19F; // Black to white gradient
                prim->x2 = prim->x0 = 0x10;
                prim->x3 = prim->x1 = 0xF0;
                prim->y1 = prim->y0 = (i * 10) + 0x9D;
                prim->y3 = prim->y2 = prim->y0 + 10;
                prim->u2 = prim->u0 = 0;
                prim->u1 = prim->u3 = 0x80;
                prim->v0 = prim->v1 = (i * 8) + (j * 0x20);
                prim->v2 = prim->v3 = prim->v0 + 8;
                prim->r0 = 120;
                prim->g0 = 120;
                prim->b0 = 168;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->priority = 0xC0;
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
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 0x80;
            prim->x1 = prim->x3 = 0x80;
            prim->y0 = prim->y1 = 0xB1;
            prim->y2 = prim->y3 = 0xB1;
            self->ext.stpopupj.depth = 0x414;
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
                    self->ext.stpopupj.timer = 0x40;
                    self->step_s++;
                }
            }
            break;

        case STAGE_NAME_HOLD_TEXT:
            prim = self->ext.stpopupj.firstRollingTextPrim;
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 4; i++) {
                    if (j == 0) {
                        prim->x2 = prim->x0 = 0x10;
                        prim->x1 = prim->x3 = 0x80;
                    } else {
                        prim->x0 = prim->x2 = 0x80;
                        prim->x3 = prim->x1 = 0xF0;
                    }
                    prim->y0 = prim->y1 = (i * 10) + 0x9D;
                    prim->y2 = prim->y3 = (i * 10) + 0xA7;
                    prim = prim->next;
                }
            }
            if (!--self->ext.stpopupj.timer) {
                rotSlicePtr = self->ext.stpopupj.rotationSlices;
                for (i = 0; i < 5; i++) {
                    *rotSlicePtr -= ROT(720); // Equivalent to FLT(2) and 0x2000
                    rotSlicePtr++;
                }
                self->step_s++;
            }
            return;

        case STAGE_NAME_SHRINK_TEXT:
            rotSlicePtr = self->ext.stpopupj.rotationSlices;
            for (i = 0; i < 5; i++) {
                *rotSlicePtr += 80; // ~7.03°
                rotSlicePtr++;
            }
            self->ext.stpopupj.depth += 0x40;
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
            break;
        }
        // Part of STAGE_NAME_RENDER, runs every frame except during
        // RENDER->HOLD_TEXT
        prim = self->ext.stpopupj.firstRollingTextPrim;
        rotSlicePtr = self->ext.stpopupj.rotationSlices;
        SetGeomScreen(0x400);
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
        SetBackColor(0x40, 0x40, 0x40);
        SetGeomOffset(0x80, 0xB1);
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
            NormalColorCol(&normal, &color, &colors[i]);
            rotSlicePtr++;
        }
        prim = self->ext.stpopupj.firstRollingTextPrim;
        for (j = 0; j < 2; j++) {
            rotSlicePtr = self->ext.stpopupj.rotationSlices;
            for (i = 0; i < 4; i++) {
                rotSlicePtr++;
                if (j == 0) {
                    LOW(prim->x0) = leftSideX[i];
                    LOW(prim->x1) = rightSideX[i];
                    LOW(prim->x2) = leftSideX[i + 1];
                    LOW(prim->x3) = rightSideX[i + 1];
                    prim->x1 = prim->x3 = 0x80;
                    if (*rotSlicePtr > 0) {
                        prim->x2 = prim->x0 = 0x10;
                    }
                } else {
                    LOW(prim->x0) = leftSideX[i];
                    LOW(prim->x1) = rightSideX[i];
                    LOW(prim->x2) = leftSideX[i + 1];
                    LOW(prim->x3) = rightSideX[i + 1];
                    prim->x0 = prim->x2 = 0x80;
                    if (*rotSlicePtr > 0) {
                        prim->x3 = prim->x1 = 0xF0;
                    }
                }
                LOW(prim->r0) = LOW(colors[i]);
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(colors[i + 1]);
                LOW(prim->r3) = LOW(prim->r2);
                prim = prim->next;
            }
        }
        break;
    }
}
#else
// func_801AD0EC: StageNamePopupHelper
// func_801AD2BC: [E_STAGE_NAME_POPUP] EntityStageNamePopup
#include "../e_stage_name_us.h"
#endif
