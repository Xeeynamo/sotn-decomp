// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitInteractable;

#ifdef STAGE_IS_TEK
void DpqColor(CVECTOR* v0, long p, CVECTOR* v1);
long VectorNormalS(VECTOR* v0, SVECTOR* v1);

#include "stage_name_dissolver.h"
#endif

#ifndef STAGE_FLAG
#define STAGE_FLAG NULL_STAGE_FLAG
#endif

#ifdef STAGE_NAME_BOX_MARGIN
#define STAGE_NAME_BOX_LEFT_X STAGE_NAME_BOX_MARGIN
#define STAGE_NAME_BOX_RIGHT_X 256 - STAGE_NAME_BOX_MARGIN
#else
#define STAGE_NAME_BOX_LEFT_X 8
#define STAGE_NAME_BOX_RIGHT_X 248
#endif

#if defined(VERSION_HD) || defined(VERSION_BETA)
#define NUM_PRIMS 181
#define TEXT_X 192
#define TEXT_Y 177
#define TEXT_V 20
#define BOX_BOTTOM_Y 198
#define BOX_INITIAL_Y 176
#define PRIM_LEFT_SIDE_X 64
#define PRIM_RIGHT_SIDE_X 192
#define PRIM_BOTTOM_Y 196
#define PRIM_BOTTOM_V 39
#else
#define NUM_PRIMS 183
#define TEXT_X 128
#define TEXT_Y 173
#define TEXT_V 16
#define BOX_BOTTOM_Y 191
#define BOX_INITIAL_Y 173
#define PRIM_LEFT_SIDE_X 0
#define PRIM_RIGHT_SIDE_X 256
#define PRIM_BOTTOM_Y 189
#define PRIM_BOTTOM_V 32
#endif

enum StageNameSteps {
    STAGE_NAME_INIT = 0,
    STAGE_NAME_RENDER = 1,
    STAGE_NAME_WAIT = 2,
    STAGE_NAME_WIPE_AWAY = 18,
    STAGE_NAME_SET_FLAG = 32,
#ifdef STAGE_IS_TEK
    STAGE_NAME_RENDER_COLORS = 2,
    STAGE_NAME_RENDER_ZOOM = 3,
    STAGE_NAME_RENDER_DRUM = 4,
    STAGE_NAME_FADE_AWAY = 16,
    STAGE_NAME_DISSOLVE = 17,
    STAGE_NAME_RENDER_CUBE = 33,
#endif
};

enum StageNameSubSteps {
    STAGE_NAME_RENDER_INIT,
    STAGE_NAME_DRAW_BOX,
    STAGE_NAME_DRAW_TEXT,
    STAGE_NAME_VERTICAL_REVEAL,
    STAGE_NAME_HOLD_TEXT,
};

// While all stages have EntityStageNamePopup, only stages that display the
// banner use these functions
#ifdef STAGE_NAME_LOAD_GFX
extern s32 D_psp_091CE570; // dra bss

static u_long* gfxBank[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

// sp and it are swapped in relation to maria in order to match the order in
// GetLang
static u8* stage_name_gfx[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it};

static void LoadStageNameGraphics(void) {
    gfxBank[3] = (u_long*)stage_name_gfx[g_UserLanguage - 1];
    func_psp_091040A0(gfxBank);
}
#endif

#ifdef STAGE_IS_TEK
static SVECTOR corner_top_left = {-64, -11, 0};
static SVECTOR corner_top_right = {64, -11, 0};
static SVECTOR corner_bottom_left = {-64, 28, 0};
static SVECTOR corner_bottom_right = {64, 28, 0};

static VECTOR cube_normals[] = {
    {FLT(1.0), FLT(1.0), FLT(0.0)},    {FLT(1.0), FLT(0.5), FLT(0.0)},
    {FLT(0.5), FLT(0.5), FLT(0.5)},    {FLT(0.5), FLT(0.25), FLT(0.5)},
    {FLT(0.0), FLT(0.25), FLT(1.0)},   {FLT(0.0), FLT(-0.25), FLT(1.0)},
    {FLT(-0.5), FLT(-0.25), FLT(0.5)}, {FLT(-0.5), FLT(-0.5), FLT(0.5)},
    {FLT(-1.0), FLT(-0.5), FLT(0.0)},  {FLT(-1.0), FLT(-1.0), FLT(0.0)},
};

static VECTOR* cube_face_normals[] = {
    &cube_normals[0], &cube_normals[2], &cube_normals[1], &cube_normals[3],
    &cube_normals[2], &cube_normals[4], &cube_normals[3], &cube_normals[5],
    &cube_normals[4], &cube_normals[6], &cube_normals[5], &cube_normals[7],
    &cube_normals[6], &cube_normals[8], &cube_normals[7], &cube_normals[9],
};

static MATRIX cube_color_matrix = {{{FLT(0.0), FLT(0.0), FLT(2.0)},
                                    {FLT(0.0), FLT(0.0), FLT(1.0)},
                                    {FLT(0.0), FLT(0.0), FLT(0.0)}}};

static SVECTOR points_left = {-64, 0, -20};
static SVECTOR points_right = {64, 0, -20};
static SVECTOR normal = {FLT(0.0), FLT(0.0), FLT(1.0)};
static MATRIX color_matrix = {{{FLT(0.0), FLT(-0.5), FLT(0.5)},
                               {FLT(0.0), FLT(0.0), FLT(1.0)},
                               {FLT(0.0), FLT(0.5), FLT(0.5)}}};
static SVECTOR no_rotation = {0, 0, 0};
#endif

// This is the banner version which "shutter opens" and wipes away to the left.
// psp prims 8-183 and hd prims 6-181 seem to be completely unused
void EntityStageNamePopup(Entity* self) {
#if defined(STAGE_IS_TEK)
    SVECTOR rotVector;
    VECTOR transVector;
    MATRIX mtx;
    VECTOR unusedVector; // never read, but the target keeps its stack slot
    MATRIX lightMtx;
    SVECTOR unusedSVector; // same as unusedVector
    CVECTOR color;
    SVECTOR normalVector;
    s32 leftSideX[5];
    s32 rightSideX[5];
    CVECTOR colors[5];
    s16 z[5];
    s32 p, flag;
#elif defined(VERSION_HD) || defined(VERSION_BETA)
    // the TEK locals above, unused once the other effects were removed
    u8 padding[0xD8];
#endif
    Primitive* prim;
    s32 i;
    u8 primsSet;
    s32 primIndex;
    s16 starRightX;
    s16 starTopY;
    s16 boxRightX;
#ifdef STAGE_IS_TEK
    s16* rotSlicePtr;
    VECTOR** normals;
#endif

#ifdef STAGE_NAME_LOAD_GFX
    if (D_psp_091CE570) {
        LoadStageNameGraphics();
    }
#endif

    switch (self->step) {
    case STAGE_NAME_INIT:
#ifndef STAGE_IS_TEK
        if (g_CastleFlags[STAGE_FLAG]) {
            DestroyEntity(self);
            return;
        }
#endif
#ifdef STAGE_NAME_LOAD_GFX
        LoadStageNameGraphics();
#endif
        InitializeEntity(g_EInitInteractable);
        // This is the only time stpopupj.unk8C is ever referenced
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
#if !defined(VERSION_HD) && !defined(VERSION_BETA)
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
#endif
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F; // Black to white gradient
            if (i != 0) {
                prim->clut = PAL_UNK_19D; // Light grey to black gradient
            }
            prim->x2 = prim->x0 = PRIM_LEFT_SIDE_X;
            prim->y1 = prim->y0 = 157;
// This splits the two loops in the middle because that is what is happening
// functionally.  The two prims for psp together have the same left and right
// sides (conceptually) as the single prim for hd.
#if !defined(VERSION_HD) && !defined(VERSION_BETA)
            prim->x3 = prim->x1 = 128;
            prim->y3 = prim->y2 = 173;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = 32;
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
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F; // Black to white gradient
            if (i != 0) {
                prim->clut = PAL_UNK_19D; // Light grey to black gradient
            }
            prim->x2 = prim->x0 = 128;
            prim->y1 = prim->y0 = 173;
#endif
            prim->x3 = prim->x1 = PRIM_RIGHT_SIDE_X;
            prim->y3 = prim->y2 = PRIM_BOTTOM_Y;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = PRIM_BOTTOM_V;
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

        self->ext.stpopupj.firstStarPrim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 26;
        prim->clut = PAL_UNK_19E; // Black to light grey gradient
        prim->u0 = 0;
        prim->u1 = 16;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 64;
        prim->v1 = prim->v0;
        prim->v2 = 80;
        prim->v3 = prim->v2;
        LOH(prim->next->r2) = 14;
        LOH(prim->next->b2) = 14;
        prim->next->b3 = 128;
        prim->priority = 192;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim = prim->next;
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
#if defined(VERSION_HD) || defined(VERSION_BETA)
        prim->y1 = prim->y0 = 155;
        prim->x3 = prim->x1 = STAGE_NAME_BOX_RIGHT_X;
#else
        prim->x3 = prim->x1 = STAGE_NAME_BOX_RIGHT_X;
        prim->y1 = prim->y0 = 155;
#endif
        prim->y3 = prim->y2 = BOX_BOTTOM_Y;
        // Top of box #102800
        prim->r0 = 16;
        prim->g0 = 40;
        prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        // Bottom of box #080038
        prim->r2 = 8;
        prim->g2 = 0;
        prim->b2 = 56;
        LOW(prim->r3) = LOW(prim->r2);
        prim->priority = 176;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
        prim = prim->next;
#ifdef STAGE_IS_TEK
        self->ext.stpopupj.firstRowPrim = prim;
        for (i = 0; i < 40; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F;
            prim->x2 = prim->x0 = 64;
            prim->y1 = prim->y0 = i + 157;
            prim->x3 = prim->x1 = 192;
            prim->y3 = prim->y2 = i + 158;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = i;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = i + 1;
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

        self->ext.stpopupj.firstColumnPrim = prim;
        for (i = 0; i < 4; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F;
            prim->x2 = prim->x0 = i * 32 + 64;
            prim->x3 = prim->x1 = prim->x0 + 32;
            prim->y1 = prim->y0 = 157;
            prim->y3 = prim->y2 = 196;
            prim->u2 = prim->u0 = i * 32;
            prim->u1 = prim->u3 = prim->u0 + 32;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 39;
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

        self->ext.stpopupj.firstRollingTextPrim = prim;
        for (i = 0; i < 4; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F;
            prim->x2 = prim->x0 = 64;
            prim->x3 = prim->x1 = 192;
            prim->y1 = prim->y0 = i * 10 + 157;
            prim->y3 = prim->y2 = prim->y0 + 10;
            prim->u2 = prim->u0 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v0 = prim->v1 = i * 10;
            prim->v2 = prim->v3 = i * 10 + 10;
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

        self->ext.stpopupj.firstPixelColumnPrim = prim;
        for (i = 0; i < 128; i++) {
            prim->tpage = 17;
            prim->clut = PAL_UNK_19F;
            prim->x2 = prim->x0 = i + 64;
            prim->x3 = prim->x1 = prim->x0 + 1;
            prim->y1 = prim->y0 = 157;
            prim->y3 = prim->y2 = 196;
            prim->u2 = prim->u0 = i;
            prim->u1 = prim->u3 = prim->u0 + 1;
            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 39;
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
#endif
        self->step = STAGE_NAME_RENDER;
    case STAGE_NAME_RENDER:
        switch (self->step_s) {
        case STAGE_NAME_RENDER_INIT:
            prim = self->ext.stpopupj.firstTextPrim;
            for (i = 0; i < 2; i++) {
                prim->u0 = prim->u2 = 128;
                prim->v0 = prim->v1 = TEXT_V;
                prim->v2 = prim->v3 = prim->v0 + 2;
                prim->x3 = prim->x1 = i * 3 + TEXT_X;
                prim->x0 = prim->x2 = i * 3 + TEXT_X;
                prim->y1 = prim->y0 = i * 2 + TEXT_Y;
                prim->y3 = prim->y2 = prim->y0 + 2;
                prim = prim->next;
            }

#if !defined(VERSION_HD) && !defined(VERSION_BETA)
            for (i = 0; i < 2; i++) {
                prim->u0 = prim->u2 = 128;
                prim->v0 = prim->v1 = 48;
                prim->v2 = prim->v3 = prim->v0 + 2;
                prim->x3 = prim->x1 = i * 3 + 256;
                prim->x0 = prim->x2 = i * 3 + 256;
                prim->y1 = prim->y0 = i * 2 + 173;
                prim->y3 = prim->y2 = prim->y0 + 2;
                prim = prim->next;
            }
#endif
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = BOX_INITIAL_Y;
            prim->y2 = prim->y3 = BOX_INITIAL_Y;
            self->step_s++;
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
#if !defined(VERSION_HD) && !defined(VERSION_BETA)
                self->ext.stpopupj.timer = 0;
#endif
                prim = self->ext.stpopupj.firstTextPrim;
#if !defined(VERSION_HD) && !defined(VERSION_BETA)
                prim = prim->next;
                prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
                prim = prim->next;
#endif
                prim = prim->next;
                prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
                prim = self->ext.stpopupj.firstStarPrim;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            }
            break;
        case STAGE_NAME_DRAW_TEXT:
            prim = self->ext.stpopupj.firstTextPrim;
#if defined(VERSION_HD) || defined(VERSION_BETA)
            for (i = 0; i < 2; i++) {
                prim->u0 -= 8;
                prim->u2 = prim->u0;
                prim->x0 -= 8;
                prim->x2 = prim->x0;
#else
            self->ext.stpopupj.timer += 8;
            for (i = 0; i < 2; i++) {
                if (self->ext.stpopupj.timer > 64) {
                    prim->u0 -= 16;
                    prim->u2 = prim->u0;
                    prim->x0 -= 16;
                    prim->x2 = prim->x0;
                }
                starRightX = prim->x0;
                starTopY = prim->y0;
                prim = prim->next;
            }

            for (i = 0; i < 2; i++) {
                if (self->ext.stpopupj.timer <= 64) {
                    prim->u0 -= 16;
                    prim->u2 = prim->u0;
                    prim->x0 -= 16;
                    prim->x2 = prim->x0;
                }
#endif
                starRightX = prim->x0;
                starTopY = prim->y0;
                prim = prim->next;
            }

            prim = self->ext.stpopupj.firstStarPrim;
            prim->next->x1 = starRightX;
            prim->next->y0 = starTopY;
            LOH(prim->next->tpage) -= 128;
            UnkPrimHelper(prim);
            prim = self->ext.stpopupj.firstTextPrim;
            if (!prim->u0) {
                self->step_s = STAGE_NAME_VERTICAL_REVEAL;
            }
            break;
        case STAGE_NAME_VERTICAL_REVEAL:
            prim = self->ext.stpopupj.firstStarPrim;
            PrimDecreaseBrightness(prim, 4);
            if (!(g_Timer % 2)) {
                prim = self->ext.stpopupj.firstTextPrim;
                for (i = 0; i < 2; i++) {
                    if (prim->y0 > i * 2 + 157) {
                        prim->v0--;
                        prim->v1 = prim->v0;
                        prim->y0--;
                        prim->y1 = prim->y0;
                    } else {
                        self->step_s = STAGE_NAME_HOLD_TEXT;
                    }
#if !defined(VERSION_HD) && !defined(VERSION_BETA)
                    if (prim->y2 < i * 2 + PRIM_BOTTOM_Y) {
                        prim->v2++;
                        prim->v3 = prim->v2;
                        prim->y2++;
                        prim->y3 = prim->y2;
                    }
                    prim = prim->next;
                }

                for (i = 0; i < 2; i++) {
                    if (prim->y0 > i * 2 + 157) {
                        prim->v0--;
                        prim->v1 = prim->v0;
                        prim->y0--;
                        prim->y1 = prim->y0;
                    } else {
                        self->step_s = STAGE_NAME_HOLD_TEXT;
                    }
#endif
                    if (prim->y2 < i * 2 + PRIM_BOTTOM_Y) {
                        prim->v2++;
                        prim->v3 = prim->v2;
                        prim->y2++;
                        prim->y3 = prim->y2;
                    }
                    prim = prim->next;
                }
            }
            break;
        case STAGE_NAME_HOLD_TEXT:
            self->step = STAGE_NAME_SET_FLAG;
            self->ext.stpopupj.timer = 32;
            break;
        }
        break;
#ifdef STAGE_IS_TEK
    case STAGE_NAME_RENDER_COLORS:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.firstTextPrim;
            for (i = 0; i < 2; i++) {
                prim->r0 = prim->b0 = prim->g0 = 0;
                prim->x3 = prim->x1 = i * 3 + 192;
                prim->x0 = prim->x2 = i * 3 + 192;
                prim->u0 = prim->u2 = 128;
                prim->v0 = prim->v1 = 39;
                prim->y3 = prim->y2 = prim->y1 = prim->y0 = i * 2 + 196;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim = prim->next;
            }
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 176;
            prim->y2 = prim->y3 = 176;
            self->step_s++;
            break;
        case 1:
            primsSet = 0;
            prim = self->ext.stpopupj.boxPrim;
            if (prim->y0 > 155) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                primsSet |= 1;
            }
            if (prim->x0 > 16) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                primsSet |= 1;
            }
            if (!primsSet) {
                self->ext.stpopupj.timer = 0;
                self->ext.stpopupj.unk8C = 1;
                self->step_s++;
                prim = self->ext.stpopupj.firstStarPrim;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->v1 += 0xFF;
            prim->u2 -= 2;
            if (prim->v1 > 240) {
                prim->v1 = 0;
                self->step_s++;
            }
            prim->v0 = prim->v1;
            break;
        case 3:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->u2 -= 2;
            prim->u0 -= 2;
            if (prim->u2 > 240) {
                prim->u2 = 0;
                self->step_s++;
            }
            break;
        case 4:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->u0 -= 2;
            if (prim->u0 > 240) {
                prim->u0 = 0;
                self->step_s++;
            }
            break;
        case 5:
            break;
        }
        prim = self->ext.stpopupj.firstTextPrim;
        prim->x0 = prim->x3 + (prim->u0 - prim->u3);
        prim->x1 = prim->x3 + (prim->u1 - prim->u3);
        prim->x2 = prim->x3 + (prim->u2 - prim->u3);
        prim->y0 = prim->y3 + (prim->v0 - prim->v3);
        prim->y1 = prim->y3 + (prim->v1 - prim->v3);
        prim->y2 = prim->y3 + (prim->v2 - prim->v3);
        if (self->ext.stpopupj.unk8C) {
            if (++self->ext.stpopupj.timer > 16) {
                self->ext.stpopupj.unk8C++;
                if (self->ext.stpopupj.unk8C > 4) {
                    self->ext.stpopupj.unk8C = 4;
                }
                self->ext.stpopupj.timer = 0;
            }
        }
        prim = self->ext.stpopupj.firstTextPrim;
        switch (self->ext.stpopupj.unk8C) {
        case 4:
            if (prim->g0 > 128) {
                if (prim->b0 > 128) {
                    if (prim->r0 > 128) {
                        self->step = STAGE_NAME_SET_FLAG;
                        self->ext.stpopupj.unk8C = 0;
                        self->ext.stpopupj.timer = 64;
                    } else {
                        prim->r0 += 4;
                    }
                } else {
                    prim->b0 += 4;
                }
            } else {
                prim->g0 += 4;
            }
        case 3:
            if (prim->b2 > 128) {
                if (prim->r2 > 128) {
                    if (prim->g2 <= 128) {
                        prim->g2 += 4;
                    }
                } else {
                    prim->r2 += 4;
                }
            } else {
                prim->b2 += 4;
            }
        case 2:
            if (prim->g1 > 128) {
                if (prim->r1 > 128) {
                    if (prim->b1 <= 128) {
                        prim->b1 += 4;
                    }
                } else {
                    prim->r1 += 4;
                }
            } else {
                prim->g1 += 4;
            }
        case 1:
            if (prim->r3 > 128) {
                if (prim->g3 > 128) {
                    if (prim->b3 <= 128) {
                        prim->b3 += 4;
                    }
                } else {
                    prim->g3 += 4;
                }
            } else {
                prim->r3 += 4;
            }
            break;
        case 0:
            break;
        }
        break;
    case STAGE_NAME_RENDER_ZOOM:
        switch (self->step_s) {
        case 0:
            self->ext.stpopupj.depth = 0x1400;
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode =
                DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 176;
            prim->y2 = prim->y3 = 176;
            self->step_s++;
            break;
        case 1:
            primsSet = 0;
            prim = self->ext.stpopupj.boxPrim;
            if (prim->y0 > 155) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                primsSet |= 1;
            }
            if (prim->x0 > 16) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                primsSet |= 1;
            }
            if (!primsSet) {
                self->ext.stpopupj.depth = 0x1400;
                self->ext.stpopupj.timer = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.stpopupj.depth != 0x400) {
                self->ext.stpopupj.depth -= 0x40;
            } else {
                self->step_s++;
            }
            break;
        case 3:
            self->step_s++;
            break;
        case 4:
            self->step = STAGE_NAME_SET_FLAG;
            self->ext.stpopupj.unk8C = 0;
            self->ext.stpopupj.timer = 64;
            break;
        }
        prim = self->ext.stpopupj.firstTextPrim;
        SetGeomScreen(0x400);
        rotVector.vx = 0;
        rotVector.vy = 0;
        rotVector.vz = 0;
        RotMatrix(&no_rotation, &mtx);
        transVector.vx = 0;
        transVector.vy = 0;
        transVector.vz = self->ext.stpopupj.depth;
        TransMatrix(&mtx, &transVector);
        SetRotMatrix(&mtx);
        SetTransMatrix(&mtx);
        color.r = 120;
        color.g = 120;
        color.b = 168;
        color.cd = prim->type;
        SetFarColor(0, 0, 0);
        SetFogNear(0x400, 0x400);
        SetGeomOffset(128, 176);
        RotTransPers4(
            &corner_top_left, &corner_top_right, &corner_bottom_left,
            &corner_bottom_right, (long*)&prim->x0, (long*)&prim->x1,
            (long*)&prim->x2, (long*)&prim->x3, (long*)&p, (long*)&flag);
        DpqColor(&color, p, (CVECTOR*)&prim->r0);
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        return;
    case STAGE_NAME_RENDER_DRUM:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode = DRAW_HIDE;
            prim = self->ext.stpopupj.firstRollingTextPrim;
            for (i = 0; i < 4; i++) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
                prim = prim->next;
            }
            prim = self->ext.stpopupj.boxPrim;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 176;
            prim->y2 = prim->y3 = 176;
            self->ext.stpopupj.depth = 0x414;
            self->ext.stpopupj.rotationSlices[0] = ROT(-270);
            self->ext.stpopupj.rotationSlices[1] = ROT(-270);
            self->ext.stpopupj.rotationSlices[2] = ROT(-270);
            self->ext.stpopupj.rotationSlices[3] = ROT(-270);
            self->ext.stpopupj.rotationSlices[4] = ROT(-270);
            self->step_s++;
            break;
        case 1:
            primsSet = 0;
            prim = self->ext.stpopupj.boxPrim;
            if (prim->y0 > 155) {
                prim->y0 -= 4;
                prim->y1 = prim->y0;
                prim->y2 += 4;
                prim->y3 = prim->y2;
                primsSet |= 1;
            }
            if (prim->x0 > 16) {
                prim->x0 -= 8;
                prim->x2 = prim->x0;
                prim->x1 += 8;
                prim->x3 = prim->x1;
                primsSet |= 1;
            }
            if (!primsSet) {
                self->ext.stpopupj.timer = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.stpopupj.rotationSlices[4] < ROT(90)) {
                self->ext.stpopupj.rotationSlices[4] += 64;
            } else {
                self->ext.stpopupj.rotationSlices[4] = ROT(90);
            }
            if (self->ext.stpopupj.rotationSlices[4] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[3] < 341) {
                    self->ext.stpopupj.rotationSlices[3] += 62;
                } else {
                    self->ext.stpopupj.rotationSlices[3] = 341;
                }
            }
            if (self->ext.stpopupj.rotationSlices[3] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[2] < 0) {
                    self->ext.stpopupj.rotationSlices[2] += 60;
                } else {
                    self->ext.stpopupj.rotationSlices[2] = 0;
                }
            }
            if (self->ext.stpopupj.rotationSlices[2] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[1] < -341) {
                    self->ext.stpopupj.rotationSlices[1] += 58;
                } else {
                    self->ext.stpopupj.rotationSlices[1] = -341;
                }
            }
            if (self->ext.stpopupj.rotationSlices[1] > ROT(-225)) {
                if (self->ext.stpopupj.rotationSlices[0] < ROT(-90)) {
                    self->ext.stpopupj.rotationSlices[0] += 56;
                } else {
                    self->ext.stpopupj.rotationSlices[0] = ROT(-90);
                    self->ext.stpopupj.timer = 64;
                    self->step_s++;
                }
            }
            break;
        case 3:
            if (!--self->ext.stpopupj.timer) {
                rotSlicePtr = self->ext.stpopupj.rotationSlices;
                for (i = 0; i < 5; i++) {
                    *rotSlicePtr -= ROT(720);
                    rotSlicePtr++;
                }
                self->step_s++;
            }
            break;
        case 4:
            rotSlicePtr = self->ext.stpopupj.rotationSlices;
            for (i = 0; i < 5; i++) {
                *rotSlicePtr += 48;
                rotSlicePtr++;
            }
            self->ext.stpopupj.depth += 32;
            if (self->ext.stpopupj.rotationSlices[4] > 0) {
                prim = self->ext.stpopupj.firstRollingTextPrim;
                for (i = 0; i < 4; i++) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                }
                self->step_s++;
            }
            break;
        case 5:
            prim = self->ext.stpopupj.boxPrim;
            prim->y1 = prim->y0 += 2;
            prim->y3 = prim->y2 -= 2;
            if (prim->y0 > prim->y2) {
                DestroyEntity(self);
                return;
            }
            break;
        }
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
        SetGeomOffset(128, 176);
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
        rotSlicePtr = self->ext.stpopupj.rotationSlices;
        for (i = 0; i < 4; i++) {
            LOW(prim->x0) = leftSideX[i];
            LOW(prim->x1) = rightSideX[i];
            LOW(prim->x2) = leftSideX[i + 1];
            LOW(prim->x3) = rightSideX[i + 1];
            rotSlicePtr++;
            if (*rotSlicePtr > 0) {
                prim->x2 = prim->x0 = 64;
                prim->x3 = prim->x1 = 192;
            }
            LOW(prim->r0) = LOW(colors[i]);
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(colors[i + 1]);
            LOW(prim->r3) = LOW(prim->r2);
            prim = prim->next;
        }
        return;
    case STAGE_NAME_FADE_AWAY:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode =
                DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            prim = prim->next;
            prim->drawMode =
                DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            self->step_s++;
            return;
        case 1:
            PrimDecreaseBrightness(self->ext.stpopupj.firstTextPrim, 3);
            primsSet = PrimDecreaseBrightness(self->ext.stpopupj.boxPrim, 6);
            if (!primsSet) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.boxPrim;
            prim->g0 = prim->b0 = prim->r0 += 1;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            primsSet =
                PrimDecreaseBrightness(self->ext.stpopupj.firstTextPrim, 3);
            if (!primsSet) {
                self->step_s++;
            }
            break;
        case 3:
            prim = self->ext.stpopupj.boxPrim;
            prim->y1 = prim->y0 += 2;
            prim->y3 = prim->y2 -= 2;
            if (prim->y0 > prim->y2) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    case STAGE_NAME_DISSOLVE:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode = DRAW_HIDE;
            prim = self->ext.stpopupj.firstRowPrim;
            for (i = 0; i < 20; i++) {
                prim->b0 = prim->g0 = prim->r0 = 128;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = i * 4;
                prim->p2 = Random() & 3;
                prim->p3 = 0;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
                prim = prim->next;
            }
            for (i = 0; i < 20; i++) {
                prim->b0 = prim->g0 = prim->r0 = 128;
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
                prim->p1 = -((20 - i) * 4);
                prim->p2 = Random() & 3;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
                prim->p3 = 0;
                prim = prim->next;
            }
            self->ext.stpopupj.timer = 112;
            self->step_s++;
            return;
        case 1:
            prim = self->ext.stpopupj.firstRowPrim;
            while (prim != NULL) {
                StageNamePopupDissolver(prim);
                prim = prim->next;
            }
            if (!--self->ext.stpopupj.timer) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.firstRowPrim;
            while (prim != NULL) {
                StageNamePopupDissolver(prim);
                prim = prim->next;
            }
            prim = self->ext.stpopupj.boxPrim;
            prim->y0 += 2;
            prim->y1 = prim->y0;
            prim->y2 -= 2;
            prim->y3 = prim->y2;
            prim->x0 -= 2;
            prim->x1 += 2;
            prim->x2 -= 2;
            prim->x3 += 2;
            if (prim->y2 < prim->y0) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
#endif
    case STAGE_NAME_WIPE_AWAY:
        if (self->step_s != 0) {
            (void)1;
            return;
        }

        prim = self->ext.stpopupj.boxPrim;
        prim->x1 -= 4; // Aligns right side of box with right side of text
        boxRightX = prim->x3 = prim->x1;
        prim = self->ext.stpopupj.firstTextPrim;
#if defined(VERSION_HD) || defined(VERSION_BETA)
        for (i = 0; i < 2; i++) {
            if (prim->x1 > boxRightX) {
                prim->x1 -= 4;
#else
        self->ext.stpopupj.timer += 4;
        for (i = 0; i < 2; i++) {
            if (self->ext.stpopupj.timer > 128 && prim->x1 > boxRightX) {
                prim->x1 -= 8;
#endif
                prim->x3 = prim->x1;
                if (prim->x1 < prim->x0) {
                    prim->drawMode = DRAW_HIDE;
                }
#if defined(VERSION_HD) || defined(VERSION_BETA)
                prim->u1 -= 4;
                prim->u3 = prim->u1;
            }
#else
                prim->u1 -= 8;
                prim->u3 = prim->u1;
                if (!prim->u1) {
                    prim->drawMode = DRAW_HIDE;
                }
            }
            prim = prim->next;
        }

        for (i = 0; i < 2; i++) {
            if (self->ext.stpopupj.timer < 129) {
                if (prim->x1 > boxRightX) {
                    prim->x1 -= 8;
                    prim->x3 = prim->x1;
                    if (prim->x1 < prim->x0) {
                        prim->drawMode = DRAW_HIDE;
                    }
                    prim->u1 -= 8;
                    prim->u3 = prim->u1;

                    if (!prim->u1) {
                        prim->drawMode = DRAW_HIDE;
                    }
                }
            } else {
                prim->drawMode = DRAW_HIDE;
            }
#endif
            prim = prim->next;
        }

        prim = self->ext.stpopupj.boxPrim;
        if (prim->x0 > prim->x1) {
            DestroyEntity(self);
            return;
        }
        break;
    case STAGE_NAME_SET_FLAG:
        if (!--self->ext.stpopupj.timer) {
#ifndef STAGE_IS_TEK
            g_CastleFlags[STAGE_FLAG] = true;
#endif
            self->step_s = 0;
            self->step = STAGE_NAME_WIPE_AWAY;
        }
        break;
#ifdef STAGE_IS_TEK
    case STAGE_NAME_RENDER_CUBE:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode = DRAW_HIDE;
            prim = self->ext.stpopupj.firstColumnPrim;
            for (i = 0; i < 4; i++) {
                prim->drawMode = DRAW_COLORS;
                prim = prim->next;
            }
            self->ext.stpopupj.rotation.vx = 0;
            self->ext.stpopupj.rotation.vy = ROT(-180);
            self->ext.stpopupj.rotation.vz = 0;
            self->step_s++;
            break;
        case 1:
            // the target really stores vx back unchanged
            self->ext.stpopupj.rotation.vx = self->ext.stpopupj.rotation.vx;
            if ((self->ext.stpopupj.rotation.vy += 32) == ROT(180)) {
                self->step_s++;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.firstTextPrim;
            prim->drawMode = DRAW_COLORS;
            prim = self->ext.stpopupj.firstColumnPrim;
            for (i = 0; i < 4; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            self->step_s = 0;
            self->step = STAGE_NAME_FADE_AWAY;
            break;
        }
        prim = self->ext.stpopupj.firstColumnPrim;
        SetGeomScreen(0x400);
        rotVector.vx = self->ext.stpopupj.rotation.vx;
        rotVector.vy = self->ext.stpopupj.rotation.vy;
        rotVector.vz = self->ext.stpopupj.rotation.vz;
        color.r = 160;
        color.g = 160;
        color.b = 176;
        color.cd = prim->type;
        RotMatrix(&no_rotation, &lightMtx);
        RotMatrixX(rotVector.vx, &lightMtx);
        RotMatrixY(rotVector.vy, &lightMtx);
        SetLightMatrix(&lightMtx);
        SetColorMatrix(&cube_color_matrix);
        SetBackColor(0x40, 0x40, 0x40);
        SetGeomOffset(128, 176);
        normals = cube_face_normals;
        for (i = 0; i < 4; i++) {
            VectorNormalS(normals[0], &normalVector);
            NormalColorCol(&normalVector, &color, (CVECTOR*)&prim->r0);
            VectorNormalS(normals[1], &normalVector);
            NormalColorCol(&normalVector, &color, (CVECTOR*)&prim->r1);
            VectorNormalS(normals[2], &normalVector);
            NormalColorCol(&normalVector, &color, (CVECTOR*)&prim->r2);
            VectorNormalS(normals[3], &normalVector);
            NormalColorCol(&normalVector, &color, (CVECTOR*)&prim->r3);
            normals += 4;
            prim = prim->next;
        }
        break;
#endif
    }
}
