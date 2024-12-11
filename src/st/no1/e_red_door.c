// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", EntityIsNearPlayer);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", NO1_EntityRedDoor);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", EntityUnkId12);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B5E20);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B6198);

typedef struct {
    s32 animSet;
    AnimationFrame* anim;
    s32 count;
    CVECTOR color;
} AnimParam;

extern u16 D_us_8018095C;
extern s16 D_us_80180ED4[];
extern s32 D_us_80180EEC;
extern AnimParam D_us_80180EF8[];
extern s16 D_us_80180F28[];
extern s16 D_us_801D6340[];
extern s16 D_us_801D635C[];

void func_us_801B6490(Entity* self) {
    Primitive* prim;
    AnimParam* animParams;
    s16 x0, x1;
    s16 xOffset;
    s16 xMin, xMax;
    s32 i, j;
    s16 temp;

    x0 = D_us_80180ED4[self->params * 2] - g_Tilemap.scrollX.i.hi;
    x1 = D_us_80180ED4[self->params * 2 + 1] - g_Tilemap.scrollX.i.hi;
    if (self->params == 4) {
        if (g_Tilemap.scrollY.i.hi < 0x260) {
            x0 += 0x50;
        }
        if (g_Tilemap.scrollY.i.hi < 0x80) {
            x0 += 0x10;
        }
        if (g_Tilemap.scrollY.i.hi > 0x190) {
            x1 = 0x7000;
        }
    }
    if (self->params == 2) {
        if (g_Tilemap.scrollY.i.hi > 0x1B0) {
            x0 -= 0x210;
            x1 = 0x7000;
        }
    }

    if (x0 < 0) {
        x0 = 0;
    }
    xMax = 0xFF;
    if ((x1 + 0x20 > 0) && (x1 < 0x100)) {
        if (x1 < 0) {
            x1 = 0;
        }
        if (x0 >= 0x100 && x1 < 0xE0) {
            xMax = x1 + 0x20;
        }
    } else {
        x1 = 0x7000;
    }

    if (x0 > x1) {
        xMin = x1;
    } else {
        xMin = x0;
    }
    animParams = &D_us_80180EF8[D_us_80180EEC];
    if (self->step == 0) {
        InitializeEntity(&D_us_8018095C);
        D_us_80180EEC = g_CastleFlags[0x13] & 0x7F;
        g_CastleFlags[0x13] |= 0x80;
        animParams = &D_us_80180EF8[D_us_80180EEC];
        g_api.func_800EA5E4(animParams->animSet);
        self->anim = animParams->anim;
        for (i = 0; i < 0xE; i++) {
            D_us_801D6340[i] = (i << 0xC) / 7;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, animParams->count);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0, j = 0; i < animParams->count; i++) {
            switch (i) {
            case 0:
                if (D_us_80180EEC == 1) {
                    prim->y0 = 0x14;
                    prim->y2 = 0x4F;
                    prim->clut = 0x45;
                    prim->u0 = prim->u2 = 0xF1;
                    prim->u3 = prim->u1 = 0xF6;
                    prim->v0 = 0xCA;
                    prim->v2 = 0xFC;
                } else {
                    prim->y0 = 0x8E;
                    prim->y2 = 0xB4;
                    prim->clut = 0x46;
                    prim->u2 = prim->u0 = 0xF9;
                    prim->u3 = prim->u1 = 0xFD;
                    prim->v0 = 0xD9;
                    prim->v2 = 0xFE;
                }
                prim->priority = 0x40;
                prim->tpage = 0xE;
                break;
            case 1:
                PRED(prim) = 0x30;
                PGRN(prim) = 8;
                PBLU(prim) = 0x88;
                prim->y0 = 0xB4;
                prim->y2 = 0xBC;
                prim->type = PRIM_G4;
                prim->priority = 0x40;
                break;
            case 2:
            case 3:
                prim->y0 = 0xB5;
                prim->y2 = 0xE3;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x2F;
                prim->tpage = 0xF;
                prim->priority = 0x42;
                break;
            case 4:
                prim->y0 = 0x14;
                prim->y2 = 0x74;
                prim->v0 = 0;
                prim->v2 = 0x5F;
                prim->tpage = 0xF;
                prim->clut = 0x3A;
                prim->priority = 0x44;
                PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
                break;
            default:
                if (D_us_80180EEC == 0) {
                    temp = 0;
                    prim->clut = 0xFE;
                }
                if (D_us_80180EEC == 1) {
                    temp = 0x50;
                    prim->clut = 0x3B;
                }

                prim->y0 = j % 13 * 8 + temp;
                prim->y2 = prim->y0 + 8;
                prim->v0 = j % 13 * 8 + 0x98;
                prim->v2 = prim->v0 + 7;
                prim->tpage = 0xF;
                prim->priority = 0x46;
                j++;
                break;
            }
            prim->y1 = prim->y0;
            prim->y3 = prim->y2;
            prim->v1 = prim->v0;
            prim->v3 = prim->v2;
            prim = prim->next;
        }
    }
    g_api.UpdateAnim(NULL, NULL);

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < animParams->count; i++) {
        if (i == 2 || i == 3) {
            prim->clut = self->animCurFrame & 0xFF;
        }
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
    prim = &g_PrimBuf[self->primIndex];
    if (xMin < 0x100) {
        prim->x0 = prim->x2 = xMin;
        prim->x1 = prim->x3 = xMax;
        prim->drawMode = DRAW_DEFAULT;
        prim = prim->next;
        if (D_us_80180EEC != 1) {
            prim->x0 = prim->x2 = xMin;
            prim->x1 = prim->x3 = xMax;
            prim->drawMode = DRAW_COLORS;
        }
        prim = prim->next;
    } else {
        prim = prim->next;
        prim = prim->next;
    }
    if (xMin < 0x80) {
        prim->drawMode = DRAW_DEFAULT;
        prim->x0 = prim->x2 = xMin;
        prim->u0 = prim->u2 = xMin & 0x7F;
        if (xMax < 0x80) {
            prim->x1 = prim->x3 = xMax;
            prim->u1 = prim->u3 = xMax & 0x7F;
            prim = prim->next;
            prim = prim->next;
        } else {
            prim->x1 = prim->x3 = 0x80;
            prim->u1 = prim->u3 = 0x7F;
            prim = prim->next;
            prim->x0 = prim->x2 = 0x80;
            prim->u0 = prim->u2 = 0;
            prim->x1 = prim->x3 = xMax;
            prim->u1 = prim->u3 = xMax & 0x7F;
            prim->drawMode = DRAW_DEFAULT;
            prim = prim->next;
        }
    } else {
        if (xMin < 0x100) {
            prim->x0 = prim->x2 = xMin;
            prim->x1 = prim->x3 = xMax;
            prim->u0 = prim->u2 = xMin & 0x7F;
            prim->u1 = prim->u3 = xMax & 0x7F;
            prim->drawMode = DRAW_DEFAULT;
        }
        prim = prim->next;
        prim = prim->next;
    }
    if (D_us_80180EEC == 1) {
        x0 = xMin;
        if ((g_Tilemap.scrollX.i.hi > 0xC0) &&
            (x0 = D_us_80180ED4[self->params * 2] - g_Tilemap.scrollX.i.hi,
             (self->params == 4))) {
            if (g_Tilemap.scrollY.i.hi < 0x260) {
                x0 += 0x50;
            }
            if (g_Tilemap.scrollY.i.hi < 0x80) {
                x0 += 0x10;
            }
        }
        if (xMax > 0xA0) {
            if (x0 < 0xF9) {
                if (x0 > 0xA0) {
                    prim->x0 = x0;
                    prim->u0 = x0 + 7;
                } else {
                    prim->x0 = 0xA0;
                    prim->u0 = 0xA7;
                }
                if (xMax > 0xF8) {
                    prim->x1 = 0xF8;
                    prim->u1 = 0xFF;
                } else {
                    prim->x1 = xMax;
                    prim->u1 = xMax + 7;
                }
                prim->x3 = prim->x1;
                prim->u3 = prim->u1;
                prim->x2 = prim->x0;
                prim->u2 = prim->u0;
                prim->drawMode = DRAW_COLORS;
                PGREY(prim, 0) = PGREY(prim, 1) =
                    ((g_GameTimer & 1) << 4) + 0x30;
            }
        }
    }
    prim = prim->next;
    if (D_us_80180EEC != 2) {
        for (i = 0; i < 0xE; i++) {
            D_us_801D6340[i] += 0x10;
            x0 = rsin(D_us_801D6340[i]) >> 10;
            x0 *= D_us_80180F28[i];
            D_us_801D635C[i] = x0 >> 3;
        }
        for (i = 0; i < 0x27; i++) {
            if (i < 0xD) {
                xOffset = -0x10;
            } else if (i < 0x1A) {
                xOffset = 0x6F;
            } else {
                xOffset = 0xEE;
            }
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0xFF;
            prim->x0 = D_us_801D635C[i % 13] + xOffset;
            prim->x2 = D_us_801D635C[i % 13 + 1] + xOffset;
            prim->x1 = prim->x0 + 0x80;
            prim->x3 = prim->x2 + 0x80;
            if (i < 0xD) {
                if (xMin < 0x70) {
                    prim->drawMode = DRAW_DEFAULT;
                    if (xMin >= (prim->x1 - 0x80)) {
                        prim->x0 = xMin;
                        prim->u0 = 0xFF - (prim->x1 - prim->x0);
                        if (prim->u0 < 0x80) {
                            prim->u0 = 0x80;
                        }
                    }
                    if (prim->x1 > xMax) {
                        prim->u1 = 0xFF - (prim->x1 - xMax);
                        if (prim->u1 < 0x80) {
                            prim->u1 = 0x80;
                        }
                        prim->x1 = xMax;
                    }
                    if (xMin >= (prim->x3 - 0x80)) {
                        prim->x2 = xMin;
                        prim->u2 = 0xFF - (prim->x3 - prim->x2);
                        if (prim->u0 < 0x80) {
                            prim->u0 = 0x80;
                        }
                    }
                    if (prim->x3 > xMax) {
                        prim->u3 = 0xFF - (prim->x3 - xMax);
                        if (prim->u3 < 0x80) {
                            prim->u3 = 0x80;
                        }
                        prim->x3 = xMax;
                    }
                }
            } else if (i < 0x1A) {
                if (xMax < 0x70) {
                    break;
                }
                if (xMin < 0xF0) {
                    prim->drawMode = DRAW_DEFAULT;
                    if (xMin >= prim->x1 - 0x80) {
                        prim->x0 = xMin;
                        prim->u0 = 0xFF - (prim->x1 - prim->x0);
                        if (prim->u0 < 0x80) {
                            prim->u0 = 0x80;
                        }
                    }
                    if (prim->x1 > xMax) {
                        prim->u1 = 0xFF - (prim->x1 - xMax);
                        if (prim->u1 < 0x80) {
                            prim->u1 = 0x80;
                        }
                        prim->x1 = xMax;
                    }
                    if (xMin >= prim->x3 - 0x80) {
                        prim->x2 = xMin;
                        prim->u2 = 0xFF - (prim->x3 - prim->x2);
                        if (prim->u2 < 0x80) {
                            prim->u2 = 0x80;
                        }
                    }
                    if (prim->x3 > xMax) {
                        prim->u3 = 0xFF - (prim->x3 - xMax);
                        if (prim->u3 < 0x80) {
                            prim->u3 = 0x80;
                        }
                        prim->x3 = xMax;
                    }
                }
            } else {
                if (xMin < 0x100) {
                    if (xMax < 0xF0) {
                        break;
                    }
                    prim->drawMode = DRAW_DEFAULT;
                    if (xMin >= prim->x1 - 0x80) {
                        prim->x0 = xMin;
                        prim->u0 = 0xFF - (prim->x1 - prim->x0);
                        if (prim->u0 < 0x80) {
                            prim->u0 = 0x80;
                        }
                    }
                    if (xMin >= prim->x3 - 0x80) {
                        prim->x2 = xMin;
                        prim->u2 = 0xFF - (prim->x3 - prim->x2);
                        if (prim->u0 < 0x80) {
                            prim->u0 = 0x80;
                        }
                    }
                }
            }
            prim = prim->next;
        }
    }
    g_GpuBuffers[0].draw.r0 = animParams->color.r;
    g_GpuBuffers[0].draw.g0 = animParams->color.g;
    g_GpuBuffers[0].draw.b0 = animParams->color.b;
    g_GpuBuffers[1].draw.r0 = animParams->color.r;
    g_GpuBuffers[1].draw.g0 = animParams->color.g;
    g_GpuBuffers[1].draw.b0 = animParams->color.b;
}

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B7188);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B7CC4);

void func_us_801B7D24(void) {}

void func_us_801B7D2C(void) {}

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B7D34);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8008);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8068);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B81E8);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B832C);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B83CC);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8430);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B84E4);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8B00);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8D30);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B8F50);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B9028);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B9184);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B9304);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801B9BE4);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BA034);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BA290);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BB4C0);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BB5E0);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BB7B8);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BB984);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BBD90);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BC598);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BC9A8);

INCLUDE_RODATA("st/no1/nonmatchings/e_red_door", D_us_801B47B0);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BCB34);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BD8AC);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BDA0C);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BDF9C);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BE2C8);

INCLUDE_RODATA("st/no1/nonmatchings/e_red_door", D_us_801B4808);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BE880);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BEB54);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BEE00);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BF074);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BF3F4);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BFA34);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801BFB40);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C01F0);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C05DC);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C0A40);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C0B9C);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C0E98);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C1090);

INCLUDE_ASM("st/no1/nonmatchings/e_red_door", func_us_801C10F4);
