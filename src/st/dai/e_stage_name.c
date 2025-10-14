// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
// Defined before vram address space
extern s32 g_UserLanguage;
extern u32 D_91CE570;

// data
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

static u_long* stage_name[] = {
    (u_long*)GFX_BANK_COMPRESSED,
    GFX_ENTRY(256, 64, 128, 128, stage_name_en),
    GFX_TERMINATE(),
};

// sp and it are swapped in relation to maria in order to match the order in
// GetLang
static u8* get_lang[] = {
    stage_name_en, stage_name_fr, stage_name_sp, stage_name_ge, stage_name_it};
static void LoadStageNameGraphics(void) {
    stage_name[3] = (u_long*)get_lang[g_UserLanguage - 1];
    func_91040A0(stage_name);
}

void EntityStageNamePopup(Entity* self) {
    Primitive* prim;
    s32 i;
    u8 primsSet;
    s32 primIndex;
    s16 nextX1;
    s16 nextY0;
    s16 xStartVal;

    if (D_91CE570) {
        LoadStageNameGraphics();
    }

    switch (self->step) {
    case 0:
        if (g_CastleFlags[DAI_STAGE_FLAG]) {
            DestroyEntity(self);
            return;
        }
        LoadStageNameGraphics();
        InitializeEntity(g_EInitInteractable);
        self->ext.stpopupj.unk8C = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 183);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        self->ext.stpopupj.prim = prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[primIndex];
        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = PAL_STAGE_NAME_19F;
            if (i) {
                prim->clut = PAL_STAGE_NAME_19D;
            }
            prim->x2 = prim->x0 = 0;
            prim->y1 = prim->y0 = 157;
            prim->x3 = prim->x1 = 128;
            prim->y3 = prim->y2 = 173;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = 32;
            prim->r0 = 120;
            prim->g0 = 120;
            prim->b0 = 168;
            if (i) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = 192 - i;
            prim->drawMode = DRAW_COLORS;
            if (i) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }

        for (i = 0; i < 2; i++) {
            prim->tpage = 17;
            prim->clut = PAL_STAGE_NAME_19F;
            if (i) {
                prim->clut = PAL_STAGE_NAME_19D;
            }
            prim->x2 = prim->x0 = 128;
            prim->y1 = prim->y0 = 173;
            prim->x3 = prim->x1 = 256;
            prim->y3 = prim->y2 = 189;
            prim->u2 = prim->u0 = 0;
            prim->v0 = prim->v1 = 0;
            prim->u1 = prim->u3 = 128;
            prim->v2 = prim->v3 = 32;
            prim->r0 = 120;
            prim->g0 = 120;
            prim->b0 = 168;
            if (i) {
                prim->r0 = prim->b0 = prim->g0 = 0;
            }
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);

            prim->priority = 192 - i;
            prim->drawMode = DRAW_COLORS;
            if (i) {
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS | DRAW_HIDE;
            }
            prim = prim->next;
        }

        self->ext.stpopupj.unk88 = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 26;
        prim->clut = PAL_STAGE_NAME_19E;
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

        self->ext.stpopupj.unk84 = prim;
        prim->type = PRIM_G4;
        prim->tpage = 26;
        prim->clut = PAL_COLOR_GRADIENT;
        prim->u0 = 0;
        prim->u1 = 64;
        prim->u2 = prim->u0;
        prim->u3 = prim->u1;
        prim->v0 = 192;
        prim->v1 = prim->v0;
        prim->v2 = 255;
        prim->v3 = prim->v2;
        prim->x2 = prim->x0 = 8;
        prim->x3 = prim->x1 = 248;
        prim->y1 = prim->y0 = 155;
        prim->y3 = prim->y2 = 191;
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
        self->step = 1;
    case 1:
        switch (self->step_s) {
        case 0:
            prim = self->ext.stpopupj.prim;
            for (i = 0; i < 2; i++) {
                prim->u0 = prim->u2 = 128;
                prim->v0 = prim->v1 = 16;
                prim->v2 = prim->v3 = prim->v0 + 2;
                prim->x3 = prim->x1 = i * 3 + 128;
                prim->x0 = prim->x2 = i * 3 + 128;
                prim->y1 = prim->y0 = i * 2 + 173;
                prim->y3 = prim->y2 = prim->y0 + 2;
                prim = prim->next;
            }

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

            prim = self->ext.stpopupj.unk84;
            prim->x0 = prim->x2 = 128;
            prim->x1 = prim->x3 = 128;
            prim->y0 = prim->y1 = 173;
            prim->y2 = prim->y3 = 173;
            self->step_s++;
        case 1:
            primsSet = 0;
            prim = self->ext.stpopupj.unk84;
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
                self->step_s++;
                self->ext.stpopupj.unk80 = 0;
                prim = self->ext.stpopupj.prim;
                prim = prim->next;
                prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
                prim = prim->next;
                prim = prim->next;
                prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_COLORS;
                prim = self->ext.stpopupj.unk88;
                prim->drawMode =
                    DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2 | DRAW_COLORS;
            }
            break;
        case 2:
            prim = self->ext.stpopupj.prim;
            self->ext.stpopupj.unk80 += 8;
            for (i = 0; i < 2; i++) {
                if (self->ext.stpopupj.unk80 > 64) {
                    prim->u0 -= 16;
                    prim->u2 = prim->u0;
                    prim->x0 -= 16;
                    prim->x2 = prim->x0;
                }
                nextX1 = prim->x0;
                nextY0 = prim->y0;
                prim = prim->next;
            }

            for (i = 0; i < 2; i++) {
                if (self->ext.stpopupj.unk80 < 65) {
                    prim->u0 -= 16;
                    prim->u2 = prim->u0;
                    prim->x0 -= 16;
                    prim->x2 = prim->x0;
                }
                nextX1 = prim->x0;
                nextY0 = prim->y0;
                prim = prim->next;
            }

            prim = self->ext.stpopupj.unk88;
            prim->next->x1 = nextX1;
            prim->next->y0 = nextY0;
            LOH(prim->next->tpage) -= 128;
            UnkPrimHelper(prim);
            prim = self->ext.stpopupj.prim;
            if (!prim->u0) {
                self->step_s = 3;
            }
            break;
        case 3:
            PrimDecreaseBrightness(self->ext.stpopupj.unk88, 4);
            if (!(g_Timer % 2)) {
                prim = self->ext.stpopupj.prim;
                for (i = 0; i < 2; i++) {
                    if (prim->y0 > i * 2 + 157) {
                        prim->v0--;
                        prim->v1 = prim->v0;
                        prim->y0--;
                        prim->y1 = prim->y0;
                    } else {
                        self->step_s = 4;
                    }
                    if (prim->y2 < i * 2 + 189) {

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
                        self->step_s = 4;
                    }

                    if (prim->y2 < i * 2 + 189) {
                        prim->v2++;
                        prim->v3 = prim->v2;
                        prim->y2++;
                        prim->y3 = prim->y2;
                    }
                    prim = prim->next;
                }
            }
            break;
        case 4:
            self->step = 32;
            self->ext.stpopupj.unk80 = 32;
            break;
        }
        break;
    case 18:
        if (self->step_s != 0) {
            (void)1;
            return;
        }

        prim = self->ext.stpopupj.unk84;
        prim->x1 -= 4;
        xStartVal = prim->x3 = prim->x1;
        prim = self->ext.stpopupj.prim;
        self->ext.stpopupj.unk80 += 4;
        for (i = 0; i < 2; i++) {
            if (self->ext.stpopupj.unk80 > 128 && prim->x1 > xStartVal) {
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
            prim = prim->next;
        }

        for (i = 0; i < 2; i++) {
            if (self->ext.stpopupj.unk80 < 129) {
                if (prim->x1 > xStartVal) {
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
            prim = prim->next;
        }

        prim = self->ext.stpopupj.unk84;
        if (prim->x0 > prim->x1) {
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
        if (!--self->ext.stpopupj.unk80) {
            g_CastleFlags[DAI_STAGE_FLAG] = 1;
            self->step_s = 0;
            self->step = 18;
        }
        break;
    }
}
#else
#include "../e_stage_name.h"
#endif
