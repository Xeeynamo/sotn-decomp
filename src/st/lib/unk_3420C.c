// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

void func_us_801B245C(Primitive* arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4,
                      s32 arg5, s32 arg6);
void func_us_801B0FBC(u8* ptr, u16 x, u16 y);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B420C);

extern u8* D_us_80181528[];
extern u8** D_psp_092A5FC8;
extern u16 D_us_80181530;
extern u8 D_us_80181650[];
extern u8 D_us_80181658[];
extern u8 D_us_80181660[];
extern u8* D_psp_092A5F50;
extern s32 g_CutsceneFlags;
extern s32 D_91ED5F8;

void func_us_801B4830(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 j;
    s32 count;
    u16* var_s4;
    u8* tempPtr;
    Entity* tempEntity;
    s32* unused;

    tempEntity = self - 1;
    switch (self->step) {
    case 0:
#ifdef VERSION_PSP
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x84);
#else
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x53);
#endif
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            count = 0x49;
            j = 0;
            while (prim != NULL) {
                if (i < 6) {
                    prim->type = PRIM_LINE_G2;
                    prim->r0 = prim->r1 = 0x80;
                    prim->g0 = prim->g1 = 0x80;
                    prim->b0 = prim->b1 = 0x80;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 8) {
                    prim->type = PRIM_G4;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0xBA;
                    prim->y0 = prim->y1 = 0x76;
                    prim->y2 = prim->y3 = 0xCA;
                    prim->priority = 0xBF;
                    prim->drawMode = DRAW_HIDE;
                } else if (i < 10) {
                    prim->type = PRIM_GT4;
#ifdef VERSION_PSP
                    prim->tpage = 0x110;
#else
                    prim->tpage = 0x114;
#endif
                    prim->u0 = prim->u2 = (i - 9) * 0x3A + 0xBA;
                    prim->u1 = prim->u3 = prim->u0 + 0x3A;
                    prim->v0 = prim->v1 = 0x7E;
                    prim->v2 = prim->v3 = prim->v0 + 0x44;
                    prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0xBA;
                    prim->y0 = prim->y1 = 0x7E;
                    prim->y2 = prim->y3 = 0xC2;
                    prim->priority = 0xC0;
                    prim->drawMode = DRAW_HIDE;
                } else if (i == 10) {
#ifdef VERSION_PSP
                    func_us_801B11A0(0x50, 0x100, 0x24, 0x20);
#else
                    func_us_801B11A0(0x60, 0x100, 0x24, 0x20);
#endif
                    prim->clut = 0x1A1;
                    prim->tpage = 0x10;
#ifdef VERSION_PSP
                    prim->u0 = 0x50;
#else
                    prim->u0 = 0x60;
#endif
                    prim->v0 = 0;
                    prim->u1 = 0x24;
                    prim->v1 = 0x20;
                    prim->x0 = 0x80;
                    prim->y0 = 0x7E;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                    var_s4 = &D_us_80181530;
                } else if (i < 15) {
                    if (i == 11) {
#ifdef VERSION_PSP
                        D_psp_092A5F50[0] =
                            D_us_80181650[g_Settings.buttonConfig[0]];
                        D_psp_092A5F50[1] =
                            D_us_80181658[g_Settings.buttonConfig[0]];
                        D_psp_092A5F50[2] =
                            D_us_80181650[g_Settings.buttonConfig[1]];
                        D_psp_092A5F50[3] =
                            D_us_80181658[g_Settings.buttonConfig[1]];
                        func_us_801B3FB4(prim, D_psp_092A5F50, 8, 0);
#else
                        D_us_80181660[0] =
                            D_us_80181650[g_Settings.buttonConfig[0]];
                        D_us_80181660[1] =
                            D_us_80181658[g_Settings.buttonConfig[0]];
                        D_us_80181660[2] =
                            D_us_80181650[g_Settings.buttonConfig[1]];
                        D_us_80181660[3] =
                            D_us_80181658[g_Settings.buttonConfig[1]];
                        func_us_801B3FB4(prim, D_us_80181660, 8, 0);
#endif
                    }
                    prim->x0 = *var_s4++ + 0xBA;
                    prim->y0 = *var_s4++ + 0xA0;
                    j++;
                    if (g_Settings.buttonConfig[(i - 11) / 2] < 4) {
                        if ((i - 11) & 1) {
                            prim->x0 -= 4;
                        }
                    }
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = 8;
                    prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                } else {
                    prim->x0 = *var_s4++ + 0xBA;
                    prim->y0 = *var_s4++ + 0xA0;
                    j++;
                    prim->clut = 0x196;
                    prim->tpage = 0x1E;
                    prim->u1 = 8;
                    prim->v1 = 8;
                    prim->priority = 0x11;
                    prim->drawMode = DRAW_HIDE;
                }
                prim = prim->next;
                i++;
#ifdef VERSION_PSP
                if (j >= count) {
                    break;
                }
#endif
            }
#ifdef VERSION_PSP
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
#endif
        }
        break;

    case 1:
        if (!self->step_s) {
            unused = &D_91ED5F8;
            for (i = 0; i < 2; i++) {
#ifdef VERSION_PSP
                tempPtr = D_psp_092A5FC8[i];
                func_us_801B0FBC(tempPtr, 0x17, 0x104 + i * 16);
#else
                tempPtr = D_us_80181528[i];
                func_us_801B0FBC(tempPtr, 0x1A, 0x104 + i * 16);
#endif
            }
            self->step_s++;
        } else if (g_CutsceneFlags & 0x400) {
            SetStep(2);
            self->ext.et_801B6F30.unk7C = 0x10;
        }
        break;

    case 2:
        if (!--self->ext.et_801B6F30.unk7C) {
            prim = &g_PrimBuf[self->primIndex];
            func_us_801B420C(prim, tempEntity);
            for (i = 0; i < 10; i++) {
                prim = prim->next;
            }
            for (i = 0; i < 7; i++) {
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
            SetStep(3);
            self->ext.et_801B6F30.unk7C = 0;
            self->ext.et_801B6F30.unk7E = 0;
        }
        break;

    case 3:
        self->ext.et_801B6F30.unk7C++;
        self->ext.et_801B6F30.unk7E += 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x42, 0x18, 0x32, 1);
        if (self->ext.et_801B6F30.unk7C == 0x10) {
            SetStep(4);
        }
        break;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B420C(prim, tempEntity);
        if ((g_CutsceneFlags & 0x400) == 0) {
            self->ext.et_801B6F30.unk7E = 0x400;
            self->ext.et_801B6F30.unk7C = 0x10;
            SetStep(8);
        }
        break;

    case 8:
        self->ext.et_801B6F30.unk7C--;
        self->ext.et_801B6F30.unk7E -= 0x40;
        prim = &g_PrimBuf[self->primIndex];
        func_us_801B245C(prim, self->ext.et_801B6F30.unk7E,
                         self->ext.et_801B6F30.unk7C * 2, 0x42, 0x18, 0x32, 1);
        if (!self->ext.et_801B6F30.unk7C) {
            for (i = 0; i < 10; i++) {
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
        DestroyEntity(self);
        break;
    }
}

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801ACF88);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801ACFA4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801ACFC4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801ACFE0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD000);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD024);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B4ED4);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B5068);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD088);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD098);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0A8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0B8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0C8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0D8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0E8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD0F4);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B56E4);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B5F18);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B5F84);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B60C8);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B6124);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD134);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD144);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD14C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD150);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD15C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD16C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD178);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD188);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD198);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1A8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1B0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1C4);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1D0);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1D8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1EC);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD1F8);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD204);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD210);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD21C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD22C);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD234);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD248);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD254);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD264);

INCLUDE_RODATA("st/lib/nonmatchings/unk_3420C", D_us_801AD26C);
