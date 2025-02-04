// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

void func_us_801B245C(Primitive* arg0, u16 arg1, u16 arg2, s32 arg3, u16 arg4,
                      s32 arg5, s32 arg6);

extern RECT D_us_801AD0F4;
extern s32 g_CutsceneFlags;
extern s32 D_psp_08B42050;
extern s32 D_psp_08B42054;
extern s32 D_psp_092A5600;

#ifdef VERSION_PSP
#define unkVal 0x43
#else
#define unkVal 0x42
#endif

void func_us_801B6F30(Entity* self) {
    DRAWENV drawEnv;
    RECT clipRect;
    DR_ENV* dr_env;
    Primitive* prim;
    s32 primIndex;
    s16 enemyMask;
    s32 i;
    u16 pads;
    Entity* tempEntity;

    clipRect = D_us_801AD0F4;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x140);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            for (; prim != NULL; i++) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x16;
                    prim->y2 = prim->y3 = 0x7A;
                    prim->priority = 0x1FA;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
                    prim->u0 = prim->u2 = (i - 8) * 0x74 + 4;
#else
                    prim->tpage = 0x114;
                    prim->u0 = prim->u2 = (i - 8) * 0x74;
#endif
                    prim->u1 = prim->u3 = prim->u0 + 0x74;
                    prim->v0 = prim->v1 = 0xD;
                    prim->v2 = prim->v3 = 0x61;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                    prim->y0 = prim->y1 = 0x1E;
                    prim->y2 = prim->y3 = 0x72;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
                    prim->type = PRIM_G4;
                    prim->y0 = prim->y1 = 0x2B;
                    prim->y2 = prim->y3 = 0x37;
#ifdef VERSION_PSP
                    PRED(prim) = 0x40;
                    PGRN(prim) = 0x10;
                    PBLU(prim) = 0x10;
#else
                    PRED(prim) = 0;
                    PGRN(prim) = 0x20;
                    PBLU(prim) = 0x40;
#endif
                    prim->priority = 0x1FB;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 13) {
                    prim->type = PRIM_GT4;
                    prim->tpage = 0x1E;
                    prim->clut = 0x17F;
                    prim->u0 = prim->u2 = 0x58;
                    prim->u1 = prim->u3 = 0x60;
                    prim->v0 = prim->v1 = (i - 0xB) * 8 + 0x70;
                    prim->v2 = prim->v3 = 0x78 - (i - 0xB) * 8;
                    prim->x0 = prim->x2 = 0x7C;
                    prim->x1 = prim->x3 = prim->x0 + 8;
                    prim->y0 = prim->y1 = (i - 0xB) * 0x60 + 0x14;
                    prim->y2 = prim->y3 = prim->y0 + 8;
                    prim->priority = 0x1FC;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 13) {
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x10;
                        prim->drawMode = DRAW_DEFAULT;
                        drawEnv = g_CurrentBuffer->draw;
                        drawEnv.isbg = 1;
                        drawEnv.clip = clipRect;
#ifdef VERSION_PSP
                        drawEnv.ofs[0] = 0;
#else
                        drawEnv.ofs[0] = 0x100;
#endif
                        drawEnv.ofs[1] = 0x100;
                        SetDrawEnv(dr_env, &drawEnv);
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }
                    prim = prim->next;
                    dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
                    if (dr_env != NULL) {
                        prim->type = PRIM_ENV;
                        prim->priority = 0x13;
                        prim->drawMode = DRAW_UNK_800;
                    } else {
                        self->step = 0;
                        g_api.FreePrimitives(self->primIndex);
                        self->flags &= ~FLAG_HAS_PRIMS;
                        return;
                    }

                } else {
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
            }
            self->ext.et_801B6F30.unk80 = 0;
            self->ext.et_801B6F30.unk82 = 0;
            self->ext.et_801B6F30.unk84 = 0;
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
            g_CastleFlags[ENEMY_LIST_190] |= 1;
        }
        break;

    case 2:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x7C, 0x20, 7, 1);
        for (i = 0; i < 15; i++) {
            prim = prim->next;
        }
        func_us_801B6E20(prim, self);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(3);
        }
        break;

    case 3:
        pads = g_pads[0].repeat;
        if (pads & PAD_DOWN) {
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80++;
            } else if (self->ext.et_801B6F30.unk82 < unkVal) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82++;
            }
        } else if (pads & PAD_UP) {
            if (self->ext.et_801B6F30.unk80 > 0) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80--;
            } else if (self->ext.et_801B6F30.unk82) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82--;
            }
        }
#ifdef VERSION_PSP
        if (pads & 0x600) {
#else
        if (pads & (PAD_R1 + PAD_R2)) {
#endif
            if (self->ext.et_801B6F30.unk80 < 6) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk80 = 6;
            } else if (self->ext.et_801B6F30.unk82 < unkVal) {
                g_api.PlaySfx(SFX_UI_MOVE);
                self->ext.et_801B6F30.unk82 += 7;
                if (self->ext.et_801B6F30.unk82 > unkVal) {
                    self->ext.et_801B6F30.unk82 = unkVal;
                }
            }
        } else {
#ifdef VERSION_PSP
            if (pads & 0x102) {
#else
            if (pads & (PAD_L1 + PAD_L2)) {
#endif
                if (self->ext.et_801B6F30.unk80 > 0) {
                    g_api.PlaySfx(SFX_UI_MOVE);
                    self->ext.et_801B6F30.unk80 = 0;
                } else if (self->ext.et_801B6F30.unk82) {
                    g_api.PlaySfx(SFX_UI_MOVE);
                    if (self->ext.et_801B6F30.unk82 > 7) {
                        self->ext.et_801B6F30.unk82 -= 7;
                    } else {
                        self->ext.et_801B6F30.unk82 = 0;
                    }
                }
            }
        }
        if (pads & (PAD_LEFT | PAD_RIGHT)) {
            if (self->ext.et_801B6F30.unk84) {
                self->ext.et_801B6F30.unk84 = 0;
            } else {
                self->ext.et_801B6F30.unk84 = 1;
            }
            g_api.PlaySfx(SFX_UI_MOVE);
        }
        pads = g_pads[0].tapped;
#ifdef VERSION_PSP
        if (pads & D_psp_08B42050) {
#else
        if (pads & PAD_CROSS) {
#endif
            enemyMask =
                (self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80) *
                    2 +
                self->ext.et_801B6F30.unk84;
            if (g_CastleFlags[(enemyMask >> 3) + ENEMY_LIST_190] &
                (1 << (enemyMask & 7))) {
                g_api.PlaySfx(SFX_UI_CONFIRM);
                SetStep(4);
            } else {
                g_api.PlaySfx(SFX_UI_ERROR);
            }
#ifdef VERSION_PSP
        } else if (pads & D_psp_08B42054) {
#else
        } else if (pads & PAD_TRIANGLE) {
#endif
            SetStep(7);
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 10; i++) {
            prim = prim->next;
        }
        if (!self->ext.et_801B6F30.unk84) {
            prim->x0 = prim->x2 = 9;
            prim->x1 = prim->x3 = 0x80;
        } else {
            prim->x0 = prim->x2 = 0x80;
            prim->x1 = prim->x3 = 0xF7;
        }
        prim->y0 = prim->y1 = self->ext.et_801B6F30.unk80 * 0xC + 0x1F;
        prim->y2 = prim->y3 = prim->y0 + 0xC;
        prim->drawMode = DRAW_COLORS;
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        if (self->ext.et_801B6F30.unk82 < unkVal) {
            prim->drawMode = DRAW_DEFAULT;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim = prim->next;
        prim = prim->next;
        func_us_801B6E20(prim, self);
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (g_api.func_80131F68()) {
                g_api.PlaySfx(SET_STOP_MUSIC);
            }
            self->step_s++;
            break;

        case 1:
            if (!g_api.func_80131F68()) {
                if ((g_CutsceneFlags & 0x200) == 0) {
                    prim = &g_PrimBuf[self->primIndex];
                    for (i = 0; i < 10; i++) {
                        prim = prim->next;
                    }
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                    prim->drawMode = DRAW_HIDE;
                    self->ext.et_801B6F30.unk7E = 0x400;
                    self->ext.et_801B6F30.unk7C = 0x10;
                    SetStep(5);
                }
            }
            break;
        }
        break;

    case 5:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
#ifdef VERSION_PSP
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x7C, 0x20, 7, 1);
#else
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C, 0x74, 0x20, 7, 1);
#endif
        if (!self->ext.et_801B6F30.unk7C) {
            for (i = 0; i < 6; i++) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            for (i = 0; i < 9; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            tempEntity = self + 1;
#ifdef VERSION_PSP
            CreateEntityFromCurrentEntity(D_psp_092A5600, tempEntity);
#else
            CreateEntityFromCurrentEntity(E_ID_2F, tempEntity);
#endif
            tempEntity->params =
                (self->ext.et_801B6F30.unk82 + self->ext.et_801B6F30.unk80) *
                    2 +
                self->ext.et_801B6F30.unk84;
            g_CutsceneFlags &= ~0x400;
            SetStep(1);
        }
        break;

    case 7:
        if ((g_CutsceneFlags & 0x200) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
            prim->drawMode = DRAW_HIDE;
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            self->step++;
            g_CutsceneFlags |= 0x200;
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x74, 0x20, 7, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 15; i++) {
                prim = prim->next;
            }
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(9);
        }
        break;

    case 9:
        g_CutsceneFlags &= ~0x400;
        DestroyEntity(self);
        break;
    }
}

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B7C94);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B7D10);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B7DF8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD2C8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD2DC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD2F0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD304);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD314);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD324);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD330);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD33C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD348);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD350);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD35C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD360);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD36C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD374);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD37C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD384);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD38C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD394);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD39C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3A4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3AC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3B4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3B8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3C4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3CC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3D4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3DC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3E4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3EC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3F4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD3FC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD404);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD40C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD414);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD41C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD424);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD42C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD438);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD440);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD44C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD450);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD458);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD464);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD46C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD470);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD474);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD478);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD484);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B8234);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B8958);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD4CC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD4DC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD4F0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD500);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD510);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD524);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD538);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD548);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD55C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD570);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD584);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD598);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5AC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5B8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5C8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5D8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5E4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD5F8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD608);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD61C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD634);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD64C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD664);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD67C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD694);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6A4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6B4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6C4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6D8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6E0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD6F4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD708);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD714);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B8A00);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", CutsceneUnk1);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", SetCutsceneScript);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801B9804);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", CutsceneUnk4);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", DrawCutsceneActorName);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", SetCutsceneEnd);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", CutsceneRun);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_80194F14);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", ScaleCutsceneAvatar);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD760);

INCLUDE_RODATA("st/lib/nonmatchings/unk_36F30", D_us_801AD774);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", LIB_EntityCutscene);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801BAF60);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801BB200);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801BB53C);

INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801BB8DC);

u8 func_us_801BBAB4(void);
INCLUDE_ASM("st/lib/nonmatchings/unk_36F30", func_us_801BBAB4);
