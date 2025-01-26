// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

extern u16 D_us_80180938[];
extern u8* D_us_80180DD8[];
extern u8 D_us_80180E00[];
extern u8 D_us_80180E0C[];
extern u16 D_us_80180E18[];
extern u16 D_us_80180E2C[];
extern u16 D_us_80180E40[];
extern u8 D_us_80180E54[];
extern u16 D_us_80180E60[];
extern s16 D_us_80180E78[];
extern s32 D_psp_0929A590;

void func_us_801B5E20(Entity* self) {
    Entity* tempEntity;
    s32 i;
    s16 posY;
    s32 count;
    s16* ptr;
    u16 params;

    params = self->params >> 0xC;
    if (!self->step) {
        InitializeEntity(D_us_80180938);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->drawMode = D_us_80180E54[params];
        self->hitboxHeight = D_us_80180E00[params];
        self->animSet = D_us_80180E2C[params];
        self->unk5A = D_us_80180E40[params];
        self->palette = D_us_80180E18[params];
        self->hitboxOffY = D_us_80180E60[params];
    }
    AnimateEntity(D_us_80180DD8[params], self);
    if (self->hitParams) {
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
            tempEntity->params = D_us_80180E0C[params];
        }
        switch (params) {
        case 2:
        case 3:
            self->facingLeft = GetSideToPlayer() & 1;
            posY = self->posY.i.hi - 0x28;
            if (params == 2) {
                count = 4;
            } else {
                count = 3;
            }
            ptr = D_us_80180E78;
            if (params == 3) {
                ptr += 5;
            }
            for (i = 0; i < count; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
#ifdef VERSION_PSP
                    CreateEntityFromEntity(D_psp_0929A590, self, tempEntity);
#else
                    CreateEntityFromEntity(E_ID_5C, self, tempEntity);
#endif
                    tempEntity->posY.i.hi = posY;
                    tempEntity->params = *(ptr + i);
                    tempEntity->facingLeft = self->facingLeft;
                }
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
                    tempEntity->posY.i.hi = posY;
                    tempEntity->params = 0;
                }
                posY += 0x10;
            }
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;

        case 9:
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
#ifdef VERSION_PSP
                CreateEntityFromCurrentEntity(D_psp_0929A590, tempEntity);
#else
                CreateEntityFromCurrentEntity(E_ID_5C, tempEntity);
#endif
                tempEntity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, tempEntity);
                tempEntity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, tempEntity);
                tempEntity->params = 3;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}

INCLUDE_ASM("st/no1/nonmatchings/unk_35E20", func_us_801B6198);

typedef struct {
    s32 animSet;
    AnimationFrame* anim;
    s32 count;
    CVECTOR color;
} AnimParam;

extern u16 D_us_8018095C[];
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
        InitializeEntity(D_us_8018095C);
        D_us_80180EEC = g_CastleFlags[NO1_WEATHER] & 0x7F;
        g_CastleFlags[NO1_WEATHER] |= 0x80;
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

extern u16 D_us_8018095C[];
extern s16 D_us_80180E8C[];
extern s16 D_us_80180E9C[];
extern s16 D_us_80180ED4[];
extern s32 D_us_80180EEC;
extern s16 D_us_801D6328[];
extern s16 D_us_801D6334[];

#define PrimLine(x) ((PrimLineG2*)(x))

void func_us_801B7188(Entity* self) {
    s32 blink;
    s16 yLenUnscaled, xLenUnscaled;
    s32 yVelUnscaled, xVelUnscaled;
    s16 lenScale;
    s16 speed;
    s16 t;
    s16 xMin, xMax;
    s32 xVel, yVel;
    s16 xLen, yLen;
    s16 x0, x1;
    s16 y0, y1;
    s16 angle;
    s16 posX, posY;
    s32 i;
    Primitive* prim;

    if (D_us_80180EEC != 1) {
        x0 = D_us_80180ED4[self->params * 2 + 0] - g_Tilemap.scrollX.i.hi;
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
        if (self->params == 2 && g_Tilemap.scrollY.i.hi > 0x1B0) {
            x0 -= 0x210;
            x1 = 0x7000;
        }
        if (x0 < 0) {
            x0 = 0;
        }
        xMax = 0xFF;
        if ((x1 + 0x20) > 0 && x1 < 0x100) {
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
        t = rsin((s16)g_Status.timerMinutes * 0x42) >> 10;
        t += 4;
        angle = D_us_80180E8C[t];
        xLenUnscaled = rcos(angle) >> 8;
        yLenUnscaled = -(rsin(angle) >> 8);
        xVelUnscaled = rcos(angle) * 16;
        yVelUnscaled = -(rsin(angle) * 16);
        lenScale = D_us_80180E9C[t];
        speed = 0x30;
        if (self->step == 0) {
            InitializeEntity(D_us_8018095C);
            if (D_us_80180EEC == 0) {
                g_api.PlaySfx(SFX_UNK_7AF);
                self->primIndex = g_api.func_800EDB58(PRIM_LINE_G2_ALT, 0x80);
                if (self->primIndex == -1) {
                    DestroyEntity(self);
                    return;
                }
                xLen = (xLenUnscaled * lenScale) >> 4;
                yLen = (yLenUnscaled * lenScale) >> 4;
                xVel = xVelUnscaled * speed;
                yVel = yVelUnscaled * speed;
                prim = &g_PrimBuf[self->primIndex];
                i = 0;
                while (PrimLine(prim) != NULL) {
                    PrimLine(prim)->r0 = PrimLine(prim)->g0 = 8;
                    PrimLine(prim)->b0 = 0x4F;
                    PrimLine(prim)->r1 = PrimLine(prim)->g1 =
                        PrimLine(prim)->b1 = 0x4F;
                    PrimLine(prim)->x0 =
                        (rand() & 0xFF) + (rand() & 0x3F) + 0x10;
                    PrimLine(prim)->y0 = rand() & 0xFF;
                    PrimLine(prim)->xLength = xLen;
                    PrimLine(prim)->yLength = yLen;
                    PrimLine(prim)->preciseX.i.hi = PrimLine(prim)->x1 =
                        PrimLine(prim)->xLength + PrimLine(prim)->x0;
                    PrimLine(prim)->preciseY.i.hi = PrimLine(prim)->y1 =
                        PrimLine(prim)->yLength + PrimLine(prim)->y0;
                    PrimLine(prim)->velocityX.val = xVel;
                    PrimLine(prim)->velocityY.val = yVel;
                    PrimLine(prim)->priority = 0x48;
                    PrimLine(prim)->drawMode = DRAW_DEFAULT;

                    i++;

                    if (PrimLine(prim)->next == NULL) {
                        self->ext.et_801B7188.unk80 = prim;
                    }
                    PrimLine(prim) = PrimLine(prim)->next;
                }
            }
            if (D_us_80180EEC == 2) {
                self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x24);
                if (self->primIndex == -1) {
                    DestroyEntity(self);
                    return;
                }
                D_us_801D6334[3] = D_us_801D6328[0] = 0x1000;
                D_us_801D6334[4] = D_us_801D6328[1] = 0xCCC;
                D_us_801D6334[0] = D_us_801D6328[2] = 0x999;
                D_us_801D6334[1] = D_us_801D6328[3] = 0x666;
                D_us_801D6334[2] = D_us_801D6328[4] = 0x333;
                i = 0;
                posX = -(g_Tilemap.scrollX.i.hi * 5) / 4;
                while (posX < -0x90) {
                    posX += 0x90;
                }

                posY = -(g_Tilemap.scrollY.i.hi * 5) / 4;
                while (posY < -0x14A) {
                    posY += 0x14A;
                }

                prim = &g_PrimBuf[self->primIndex];

                while (prim != NULL) {
                    x0 = (rsin(D_us_801D6328[((i >> 2) + 0) % 5]) >> 9) - 8 +
                         posX;
                    x1 = (rsin(D_us_801D6328[((i >> 2) + 1) % 5]) >> 9) - 8 +
                         posX;
                    y0 = (rcos(D_us_801D6334[((i >> 2) + 0) % 5]) >> 10) - 8 +
                         posY;
                    y1 = (rcos(D_us_801D6334[((i >> 2) + 1) % 5]) >> 10) - 8 +
                         posY;
                    prim->x0 = ((i & 3) * 0x90) + x0;
                    prim->x2 = ((i & 3) * 0x90) + x1;
                    prim->x1 = prim->x0 + 0x90;
                    prim->x3 = prim->x2 + 0x90;
                    prim->y1 = prim->y0 = ((i >> 2) * 0x42) + y0;
                    prim->y3 = prim->y2 = ((i >> 2) * 0x42 + 0x42) + y1;
                    prim->u0 = prim->u2 = 2;
                    prim->v0 = prim->v1 = 0x39;
                    prim->u1 = prim->u3 = 0x7E;
                    prim->v2 = prim->v3 = 0x78;
                    prim->tpage = 0xF;
                    prim->clut = 0x40;
                    prim->priority = 0xE0;
                    prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
                    i++;
                    prim = prim->next;
                }
            }
            self->flags |= FLAG_HAS_PRIMS;
        }
        if (D_us_80180EEC == 0) {
            i = 0;
            blink = g_GameTimer & 3;
            xLen = (xLenUnscaled * lenScale) >> 4;
            yLen = (yLenUnscaled * lenScale) >> 4;
            xVel = xVelUnscaled * speed;
            yVel = yVelUnscaled * speed;

            prim = &g_PrimBuf[self->primIndex];
            while (PrimLine(prim) != NULL) {
                if ((i &= 3) != blink) {
                    PrimLine(prim)->drawMode = DRAW_HIDE;
                } else {
                    PrimLine(prim)->drawMode = DRAW_COLORS;
                    PrimLine(prim)->preciseX.i.hi = PrimLine(prim)->x0;
                    PrimLine(prim)->preciseY.i.hi = PrimLine(prim)->y0;
                    PrimLine(prim)->preciseX.val +=
                        PrimLine(prim)->velocityX.val;
                    PrimLine(prim)->preciseY.val +=
                        PrimLine(prim)->velocityY.val;
                    PrimLine(prim)->x0 = PrimLine(prim)->preciseX.i.hi;
                    PrimLine(prim)->y0 = PrimLine(prim)->preciseY.i.hi;
                    PrimLine(prim)->drawMode = DRAW_COLORS;
                    if (PrimLine(prim)->x0 < xMin) {
                        PrimLine(prim)->drawMode = DRAW_HIDE;
                    }
                    if (PrimLine(prim)->x1 > xMax) {
                        PrimLine(prim)->drawMode = DRAW_HIDE;
                    }
                    if (PrimLine(prim)->y0 > 0x100) {
                        PrimLine(prim)->drawMode = DRAW_HIDE;
                        PrimLine(prim)->x0 =
                            (rand() & 0xFF) + (rand() & 0x3F) + 0x10;
                        PrimLine(prim)->y0 -= 0x120;
                        PrimLine(prim)->xLength = xLen;
                        PrimLine(prim)->yLength = yLen;
                        PrimLine(prim)->velocityX.val = xVel;
                        PrimLine(prim)->velocityY.val = yVel;
                    }
                    PrimLine(prim)->preciseX.i.hi = PrimLine(prim)->x1 =
                        PrimLine(prim)->xLength + PrimLine(prim)->x0;
                    PrimLine(prim)->preciseY.i.hi = PrimLine(prim)->y1 =
                        PrimLine(prim)->yLength + PrimLine(prim)->y0;
                }
                i++;
                PrimLine(prim) = PrimLine(prim)->next;
            }
            prim = self->ext.et_801B7188.unk80;
            prim->drawMode = DRAW_DEFAULT;
            prim->x0 = prim->y0 = prim->x1 = prim->y1 = 0;
        }
        if (D_us_80180EEC == 2) {
            for (i = 0; i < 5; i++) {
                D_us_801D6328[i] += 16;
                D_us_801D6334[i] += 16;
            }
            posX = -(g_Tilemap.scrollX.i.hi * 5) / 4;
            while (posX < -0x90) {
                posX += 0x90;
            }
            posY = -(g_Tilemap.scrollY.i.hi * 5) / 4;
            while (posY < -0x14A) {
                posY += 0x14A;
            }
            i = 0;
            prim = &g_PrimBuf[self->primIndex];
            while (prim != NULL) {
                angle = ((i >> 2) + 0) % 5;
                x0 = (rsin(D_us_801D6328[angle]) >> 9) - 8 + posX;
                y0 = (rcos(D_us_801D6334[angle]) >> 10) - 8 + posY;
                angle = ((i >> 2) + 1) % 5;
                x1 = (rsin(D_us_801D6328[angle]) >> 9) - 8 + posX;
                y1 = (rcos(D_us_801D6334[angle]) >> 10) - 8 + posY;
                prim->x0 = ((i & 3) * 0x90) + x0;
                prim->x2 = ((i & 3) * 0x90) + x1;
                prim->x1 = prim->x0 + 0x90;
                prim->x3 = prim->x2 + 0x90;
                prim->y1 = prim->y0 = ((i >> 2) * 0x42) + y0;
                prim->y3 = prim->y2 = ((i >> 2) * 0x42 + 0x42) + y1;
                i++;
                prim = prim->next;
            }
        }
    }
}

void func_us_801B7CC4(Entity* self) {
    if (self->step == 0) {
        g_api.PlaySfx(SET_RELEASE_RATE_HIGH_20_21);
        self->step++;
    }
    DestroyEntity(self);
}

void func_us_801B7D24(void) {}

void func_us_801B7D2C(void) {}

// called after collecting max life up
extern AnimationFrame D_us_80180F48[];
extern AnimationFrame D_us_80180F6C[];
extern AnimationFrame D_us_80180F7C[];
extern s32 D_us_80180F84[];

void func_us_801B7D34(Entity* self) {
    s16 offsetX;
    s16 offsetY;

    offsetX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = -0x7FFF;
        self->zPriority = PLAYER.zPriority - 0x10;
        self->facingLeft = true;
        self->animFrameIdx = 0;
        self->animFrameDuration = 0;
        self->anim = D_us_80180F48;
        break;

    case 1:
        if (self->animFrameDuration < 0) {
            self->animFrameDuration = 0;
            self->animFrameIdx = 0;
            self->anim = D_us_80180F6C;
            self->velocityX = D_us_80180F84[self->facingLeft];
            // n.b.! this is one higher than INT16_MAX making
            //       it actually INT16_MIN. the first decrement
            //       below rolls the value back to positive before
            //       any comparison which is only against zero.
            self->ext.et_801B7D34.timer = (INT16_MAX + 1);
            self->step++;
        }
        break;

    case 2:
        if (--self->ext.et_801B7D34.timer == 0) {
            if (!self->facingLeft) {
                if (offsetX < 0x1e0 && offsetX > 0x1a0) {
                    self->step = 3;
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                    self->anim = D_us_80180F7C;
                    self->ext.et_801B7D34.unk7E = 3;
                    self->velocityY = FIX(-2.75);
                    break;
                }
            }

            self->step = 1;
            self->animFrameIdx = 3;
            self->animFrameDuration = 0;
            self->anim = D_us_80180F48;

        } else {
            self->posX.val += self->velocityX;
            if ((self->facingLeft == false && offsetX < 0x198) ||
                (self->facingLeft == true && offsetX > 0x208)) {
                self->facingLeft ^= true;
                self->velocityX = D_us_80180F84[self->facingLeft];
                if (!(rand() & 3)) {
                    self->ext.et_801B7D34.timer = (rand() & 0xF) + 0x18;
                } else {
                    self->ext.et_801B7D34.timer = (INT16_MAX + 1);
                }
            }
        }
        break;

    case 3:
        self->velocityY += FIX(7.0 / 32.0);
        self->posY.val += self->velocityY;
        if (self->velocityY > 0) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi - 0x8DD;
            if (offsetY >= 0) {
                self->posY.i.hi -= offsetY;
                self->posY.i.lo = 0;
                if (--self->ext.et_801B7D34.unk7E) {
                    self->velocityY = FIX(-2.75);
                    self->animFrameIdx = 0;
                    self->animFrameDuration = 0;
                } else {
                    self->step = 1;
                    self->animFrameIdx = 3;
                    self->animFrameDuration = 0;
                    self->anim = D_us_80180F48;
                }
            }
        }
        break;
    }

    g_api.UpdateAnim(NULL, NULL);
}
