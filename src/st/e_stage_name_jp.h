// SPDX-License-Identifier: AGPL-3.0-or-later

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

#ifdef VERSION_HD
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
extern s32 g_UserLanguage;
extern u32 D_91CE570; // dra bss

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
    func_91040A0(gfxBank);
}
#endif

// This is the banner version which "shutter opens" and wipes away to the left.
// psp prims 8-183 and hd prims 6-181 seem to be completely unused
void EntityStageNamePopup(Entity* self) {
#ifdef VERSION_HD
    u8 padding[0xD8];
#endif
    Primitive* prim;
    s32 i;
    u8 primsSet;
    s32 primIndex;
    s16 starRightX;
    s16 starTopY;
    s16 boxRightX;

#ifdef STAGE_NAME_LOAD_GFX
    if (D_91CE570) {
        LoadStageNameGraphics();
    }
#endif

    switch (self->step) {
    case STAGE_NAME_INIT:
        if (g_CastleFlags[STAGE_FLAG]) {
            DestroyEntity(self);
            return;
        }
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
#if !defined(VERSION_HD)
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
#endif
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = 0x19F; // Black to white gradient
            if (i != 0) {
                prim->clut = 0x19D; // Light grey to black gradient
            }
            prim->x2 = prim->x0 = PRIM_LEFT_SIDE_X;
            prim->y1 = prim->y0 = 157;
// This splits the two loops in the middle because that is what is happening
// functionally.  The two prims for psp together have the same left and right
// sides (conceptually) as the single prim for hd.
#if !defined(VERSION_HD)
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
            prim->clut = 0x19F; // Black to white gradient
            if (i != 0) {
                prim->clut = 0x19D; // Light grey to black gradient
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
        prim->clut = 0x19E; // Black to light grey gradient
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
        prim->clut = 0x15F; // All white palette
        prim->u0 = 0;
        prim->u1 = 64;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 192;
        prim->v1 = prim->v0;
        prim->v2 = 255;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = STAGE_NAME_BOX_LEFT_X;
#ifdef VERSION_HD
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

#if !defined(VERSION_HD)
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
#if !defined(VERSION_HD)
                self->ext.stpopupj.timer = 0;
#endif
                prim = self->ext.stpopupj.firstTextPrim;
#if !defined(VERSION_HD)
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
#ifdef VERSION_HD
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
#if !defined(VERSION_HD)
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
    case STAGE_NAME_WIPE_AWAY:
        if (self->step_s != 0) {
            (void)1;
            return;
        }

        prim = self->ext.stpopupj.boxPrim;
        prim->x1 -= 4; // Aligns right side of box with right side of text
        boxRightX = prim->x3 = prim->x1;
        prim = self->ext.stpopupj.firstTextPrim;
#ifdef VERSION_HD
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
#ifdef VERSION_HD
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
            g_CastleFlags[STAGE_FLAG] = true;
            self->step_s = 0;
            self->step = STAGE_NAME_WIPE_AWAY;
        }
        break;
    }
}
