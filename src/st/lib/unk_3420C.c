// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

void func_us_801B0FBC(u8* ptr, u16 x, u16 y);
Primitive* func_us_801B1064(
    Primitive* arg0, u16 arg1, s16 arg2, const char* arg3, u16 arg4);
void func_us_801B245C(Primitive* arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4,
                      s32 arg5, s32 arg6);

INCLUDE_ASM("st/lib/nonmatchings/unk_3420C", func_us_801B420C);

extern char* D_us_80181528[];
extern char** D_psp_092A5FC8;
extern u16 D_us_80181530;
extern u8 D_us_80181650[];
extern u8 D_us_80181658[];
extern u8 D_us_80181660[];
extern u8* D_psp_092A5F50;
extern s32 D_91ED5F8;

void func_us_801B4830(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 i;
    s32 j;
    s32 count;
    u16* var_s4;
    char* name;
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
                name = D_psp_092A5FC8[i];
                func_us_801B0FBC(name, 0x17, 0x104 + i * 16);
#else
                name = D_us_80181528[i];
                func_us_801B0FBC(name, 0x1A, 0x104 + i * 16);
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

const RECT D_us_801AD0F4 = {.x = 0x100, .y = 0x100, .w = 0x100, .h = 0x100};

extern AvailableInventoryItem D_us_801814D8[];
extern char D_us_801816A4[];
extern char* D_us_801816AC[];
extern char* D_us_801816B0[];
extern u32 D_us_801D415C[];
extern s32 D_us_801D425C[];
extern AvailableInventoryItem D_us_801D4364[];

extern char** D_psp_092A5FA8;
extern char** D_psp_092A5FB0;
extern char* D_psp_092A5FB8;

void func_us_801B56E4(Entity* self) {
    Entity* tempEntity;
    s32 primIndex;
    s32 i, j;
    AvailableInventoryItem* inventoryItem;
    DRAWENV drawEnv;
    DR_ENV* dr_env;
    RECT clipRect;
    const char* name;
    Primitive* prim;
    Primitive* prim2;
    s16 posX, posY;
    s16 itemId;
    s16 index;
    s32 count;
    u32 price;

    clipRect = D_us_801AD0F4;
    tempEntity = self - 3;
    switch (self->step) {
    case 0:
        primIndex = g_api.AllocPrimitives(PRIM_SPRT, 0x13A);
        if (primIndex != -1) {
            InitializeEntity(g_EInitCommon);
            i = 0;
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
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
                return;
            }
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x12;
                prim->drawMode = DRAW_UNK_800;
            } else {
                self->step = 0;
                return;
            }
            prim = prim->next;
            while (prim != NULL) {
                prim->clut = 0x196;
                prim->tpage = 0x1E;
                prim->u1 = prim->v1 = 8;
                prim->priority = 0x11;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        }
        break;

    case 1:
        if (g_CutsceneFlags & 0x400) {
            if (tempEntity->params) {
                SetStep(4);
            } else {
                SetStep(2);
            }
        }
        break;

    case 2:
        posY = tempEntity->ext.et_801B56E4.unk84 + 16;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        index = tempEntity->ext.et_801B56E4.unk82;
        posY = 16;
        for (i = 0; i < 8; i++) {
            if (i == 7 && !tempEntity->ext.et_801B56E4.unk84) {
                break;
            }
            if (tempEntity->params) {
                inventoryItem = &D_us_801814D8[index];
            } else {
                inventoryItem = &D_us_801D4364[index];
            }
            itemId = inventoryItem->itemId;
            switch (inventoryItem->category) {
            case 0:
                name = g_api.equipDefs[itemId].name;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                name = g_api.accessoryDefs[itemId].name;
                break;
            case 5:
#ifdef VERSION_PSP
                name = D_psp_092A5FB0[itemId];
#else
                name = D_us_801816AC[itemId];
#endif
                break;
            case 6:
#ifdef VERSION_PSP
                name = D_psp_092A5FA8[itemId];
#else
                name = D_us_801816B0[itemId];
#endif
                break;
            default:
#ifdef VERSION_PSP
                name = *D_psp_092A5FC8;
#else
                name = *D_us_80181528;
#endif
                break;
            }
            prim = func_us_801B1064(prim, 8, posY, name, 0x196);
            if (D_us_801D415C[index] != 0) {
                posX = 0x7E;
                prim->clut = 0x196;
                prim->u0 = 0x40;
                prim->v0 = 0x28;
                prim->drawMode = DRAW_DEFAULT;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
                prim2 = prim;
                for (j = 0; j < 2; j++) {
                    prim->clut = 0x196;
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
                func_us_801B3EC8(prim2, D_us_801D415C[index], 2);
                posX += 10;
                prim2 = prim;
                price = inventoryItem->price * D_us_801D415C[index];
                for (j = 0; j < 8; j++) {
                    if (g_Status.gold < price) {
                        prim->clut = 0x191;
                    } else {
                        prim->clut = 0x196;
                    }
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
                func_us_801B3EC8(prim2, price, 8);
            } else {
#ifdef VERSION_PSP
                posX = 0x80;
                count = 16;
                prim2 = prim;
                for (j = 0; j < count; j++) {
#else
                posX = 0x96;
                prim2 = prim;
                for (j = 0; j < 8; j++) {
#endif
                    prim->clut = 0x196;
                    prim->x0 = posX;
                    prim->y0 = posY;
                    prim = prim->next;
                    posX += 8;
                }
#ifdef VERSION_PSP
                func_us_801B3FB4(prim2, D_psp_092A5FB8, count, 1);
#else
                func_us_801B3FB4(prim2, D_us_801816A4, 8, 1);
#endif
            }
            posY += 12;
            index++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if ((g_CutsceneFlags & 0x400) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(3);
        }
        break;

    case 3:
        DestroyEntity(self);
        return;

    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        prim = prim->next;
        index = tempEntity->ext.et_801B56E4.unk82;
        posY = 0x10;
        for (i = 0; i < 7; i++) {
            inventoryItem = &D_us_801814D8[index];
            name = g_api.accessoryDefs[inventoryItem->itemId].name;
            if (D_us_801D425C[index] != 0) {
                itemId = 0x196;
            } else {
                itemId = 0x191;
            }
            prim = func_us_801B1064(prim, 8, posY, name, itemId);
            posX = 0x7E;
            prim->clut = itemId;
            prim->u0 = 0x40;
            prim->v0 = 0x28;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = posX;
            prim->y0 = posY;
            prim = prim->next;
            posX += 8;
            prim2 = prim;
            for (j = 0; j < 2; j++) {
                prim->clut = itemId;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
            }
            func_us_801B3EC8(prim2, D_us_801D415C[index], 2);
            posX += 10;
            prim2 = prim;
            price = inventoryItem->price * D_us_801D415C[index];
            for (j = 0; j < 8; j++) {
                prim->clut = itemId;
                prim->x0 = posX;
                prim->y0 = posY;
                prim = prim->next;
                posX += 8;
            }
            func_us_801B3EC8(prim2, price, 8);
            posY += 12;
            index++;
        }
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        if ((g_CutsceneFlags & 0x400) == 0) {
            prim = &g_PrimBuf[self->primIndex];
            prim = prim->next;
            prim = prim->next;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            SetStep(3);
        }
        break;
    }
}

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
