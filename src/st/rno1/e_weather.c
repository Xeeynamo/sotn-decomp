// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

static s16 fogAngles[] = {
    0xBC0, 0xBB0, 0xBA0, 0xB90, 0xB80, 0xB70, 0xB60, 0xB50};
static s16 fogScales[] = {24, 28, 32, 40, 48, 56, 64, 72};
static AnimationFrame rain_anim[] = {
    4, 0x3C, 4, 0xF8, 4, 0xF9, 4, 0xF8, 0, 0x00};
static AnimationFrame clear_anim[] = {
    4, 0xFF, 4, 0xFA, 4, 0xFB, 4, 0xFA, 0, 0x00};
typedef enum {
    WEATHER_RAIN,
    WEATHER_CLEAR,
    WEATHER_FOG
} weatherModes;
static weatherModes weatherMode = 0; // doesn't make sense to init to rain
static u8 D_us_80180EF0[] = {0x60, 0x80, 0xC0, 0x80, 0x60};
static AnimParam animParams[] = {
    {ANIMSET_OVL(1), rain_anim, 44, {.r = 8, .g = 8, .b = 24}},
    {ANIMSET_OVL(2), clear_anim, 44, {.r = 16, .g = 8, .b = 72}},
    {ANIMSET_OVL(2), rain_anim, 5, {.r = 8, .g = 8, .b = 24}}};
static s16 fogMovement[] = {4, 5, 6, 7, 6, 6, 5, 5, 4, 4, 3, 3, 2, 2};
STATIC_PAD_DATA(1);

// bss
static s16 D_us_801D6328[6];
static s16 D_us_801D6334[6];
static s16 D_us_801D6340[14];
static s16 D_us_801D635C[14];
static s32 g_DebugWaitInfoTimer;

// Likely copied out of DRA, unused in RNO1
static void DebugShowWaitInfo(const char* msg) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint(msg);
    if (g_DebugWaitInfoTimer++ & 4) {
        FntPrint("\no\n");
    }
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}

static void DebugInputWait(const char* msg) {
    while (PadRead(0))
        DebugShowWaitInfo(msg);
    while (!PadRead(0))
        DebugShowWaitInfo(msg);
}

void EntityFog(Entity* self) {
    Primitive* prim;
    AnimParam* aP;
    s16 x0, x1;
    s16 xOffset;
    s16 xMin, xMax;
    s32 i, j;
    s16 temp;

    aP = &animParams[weatherMode];
    if (self->step == 0) {
        InitializeEntity(g_EInitSpawner);
        weatherMode = g_CastleFlags[NO1_WEATHER] & 0x7F;
        g_CastleFlags[NO1_WEATHER] |= 0x80;
        aP = &animParams[weatherMode];
        g_api.func_800EA5E4(aP->animSet);
        self->anim = aP->anim;
        for (i = 0; i < LEN(D_us_801D6340); i++) {
            D_us_801D6340[i] = (i << 0xC) / 7;
        }
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, aP->count);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0, j = 0; i < aP->count; i++) {
            switch (i) {
            case 0:
                if (weatherMode == WEATHER_CLEAR) {
                    prim->y0 = 0xE3;
                    prim->y2 = 0xA8;
                    prim->clut = 0x45;
                    prim->u0 = prim->u2 = 0xF1;
                    prim->u3 = prim->u1 = 0xF6;
                    prim->v0 = 0xCA;
                    prim->v2 = 0xFC;
                } else {
                    prim->y0 = 0x6C;
                    prim->y2 = 0x46;
                    prim->clut = 0x46;
                    prim->u2 = prim->u0 = 0xF9;
                    prim->u3 = prim->u1 = 0xFD;
                    prim->v0 = 0xD9;
                    prim->v2 = 0xFE;
                }
                prim->x0 = prim->x2 = 0;
                prim->x1 = prim->x3 = 0xFF;
                prim->priority = 0x40;
                prim->drawMode = DRAW_DEFAULT;
                prim->tpage = 0xE;
                break;
            case 1:
                PRED(prim) = 0x30;
                PGRN(prim) = 8;
                PBLU(prim) = 0x88;
                prim->y0 = 0x46;
                prim->y2 = 0x3E;
                prim->type = PRIM_G4;
                prim->priority = 0x40;
                prim->x0 = prim->x2 = 0;
                prim->x1 = prim->x3 = 0xFF;
                prim->drawMode = DRAW_COLORS;
                if (weatherMode == WEATHER_CLEAR) {
                    prim->drawMode = DRAW_HIDE;
                }
                break;
            case 2:
            case 3:
                prim->y2 = 0x14;
                prim->y0 = 0x42;
                prim->v0 = prim->v1 = 0;
                prim->v2 = prim->v3 = 0x2F;
                prim->tpage = 0xF;
                prim->priority = 0x42;
                prim->drawMode = DRAW_DEFAULT;
                prim->u0 = prim->u2 = 0;
                prim->u1 = prim->u3 = 0x7F;
                if (i == 2) {
                    prim->x0 = prim->x2 = 0;
                    prim->x1 = prim->x3 = 0x80;
                } else {
                    prim->x0 = prim->x2 = 0x80;
                    prim->x1 = prim->x3 = 0xFF;
                }
                break;
            case 4:
                prim->y0 = 0xE3;
                prim->y2 = 0x83;
                prim->v0 = 0;
                prim->v2 = 0x5F;
                prim->tpage = 0xF;
                prim->clut = 0x3A;
                prim->priority = 0x44;
                prim->drawMode = DRAW_COLORS;
                PGREY(prim, 2) = PGREY(prim, 3) = 0x80;
                prim->x3 = prim->x1 = 8;
                prim->x2 = prim->x0 = 0x60;
                prim->u3 = prim->u1 = 0xFF;
                prim->u2 = prim->u0 = 0xA8;
                if (weatherMode != WEATHER_CLEAR) {
                    prim->drawMode = DRAW_HIDE;
                }
                break;
            default:
                if (weatherMode == WEATHER_RAIN) {
                    temp = 0xF5;
                    prim->clut = 0xFE;
                }
                if (weatherMode == WEATHER_CLEAR) {
                    temp = 0xA5;
                    prim->clut = 0x3B;
                }

                prim->y0 = temp - j % 13 * 8;
                prim->y2 = prim->y0 - 8;
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
    for (i = 0; i < 5; i++) {
        if (i == 2 || i == 3) {
            prim->clut = self->animCurFrame & 0xFF;
        }
        if (i == 4) {
            PGREY(prim, 0) = PGREY(prim, 1) = ((g_GameTimer & 1) << 4) + 0x30;
        }
        prim = prim->next;
    }

    if (weatherMode != WEATHER_FOG) {
        for (i = 0; i < LEN(D_us_801D6340); i++) {
            D_us_801D6340[i] += 0x10;
            x0 = rsin(D_us_801D6340[i]) >> 10;
            x0 *= fogMovement[i];
            D_us_801D635C[i] = x0 >> 3;
        }
        for (i = 0; i < 0x27; i++) {
            if (i < 13) {
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
            prim = prim->next;
        }
    }
    g_GpuBuffers[0].draw.r0 = aP->color.r;
    g_GpuBuffers[0].draw.g0 = aP->color.g;
    g_GpuBuffers[0].draw.b0 = aP->color.b;
    g_GpuBuffers[1].draw.r0 = aP->color.r;
    g_GpuBuffers[1].draw.g0 = aP->color.g;
    g_GpuBuffers[1].draw.b0 = aP->color.b;
    FntPrint("scr_y:%02x\n", g_Tilemap.scrollY.i.hi);
    FntPrint("scr_x:%02x\n", g_Tilemap.scrollX.i.hi);
    // Tenki is Japanese for "weather"
    FntPrint("tenki_w:%02x\n", weatherMode);
    FntPrint("flags_tenki:%2x\n", g_CastleFlags[NO1_WEATHER]);
}

#define PrimLine(x) ((PrimLineG2*)(x))

void EntityRain(Entity* self) {
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

    if (weatherMode != WEATHER_CLEAR) {
        t = rsin((s16)g_Status.timerMinutes * 66) >> 10;
        t += 4;
        angle = fogAngles[t];
        xLenUnscaled = rcos(angle) >> 8;
        yLenUnscaled = -(rsin(angle) >> 8);
        xVelUnscaled = rcos(angle) * 16;
        yVelUnscaled = -(rsin(angle) * 16);
        lenScale = fogScales[t];
        speed = 0x30;
        if (self->step == 0) {
            InitializeEntity(g_EInitSpawner);
            if (weatherMode == WEATHER_RAIN) {
                g_api.PlaySfx(SFX_RAIN_LOOP);
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
                        (rand() & 0xFF) - (rand() & 0x3F) - 0x10;
                    PrimLine(prim)->y0 = rand() & 0xFF;
                    PrimLine(prim)->xLength = -xLen;
                    PrimLine(prim)->yLength = -yLen;
                    PrimLine(prim)->preciseX.i.hi = PrimLine(prim)->x1 =
                        PrimLine(prim)->xLength + PrimLine(prim)->x0;
                    PrimLine(prim)->preciseY.i.hi = PrimLine(prim)->y1 =
                        PrimLine(prim)->yLength + PrimLine(prim)->y0;
                    PrimLine(prim)->velocityX.val = -xVel;
                    PrimLine(prim)->velocityY.val = -yVel;
                    PrimLine(prim)->priority = 0x48;
                    PrimLine(prim)->drawMode = DRAW_DEFAULT;

                    i++;

                    if (PrimLine(prim)->next == NULL) {
                        self->ext.et_801B7188.unk80 = prim;
                    }
                    PrimLine(prim) = PrimLine(prim)->next;
                }
            }
            if (weatherMode == WEATHER_FOG) {
                self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x24);
                if (self->primIndex == -1) {
                    DestroyEntity(self);
                    return;
                }
                D_us_801D6334[3] = D_us_801D6328[0] = ROT(360);
                D_us_801D6334[4] = D_us_801D6328[1] = ROT(360 * 0.8);
                D_us_801D6334[0] = D_us_801D6328[2] = ROT(360 * 0.6);
                D_us_801D6334[1] = D_us_801D6328[3] = ROT(360 * 0.4);
                D_us_801D6334[2] = D_us_801D6328[4] = ROT(360 * 0.2);
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
                    prim->u0 = prim->u2 = 0x7E;
                    prim->v0 = prim->v1 = 0x78;
                    prim->u1 = prim->u3 = 2;
                    prim->v2 = prim->v3 = 0x39;
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
        if (weatherMode == WEATHER_RAIN) {
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
                    if (PrimLine(prim)->y0 < 0) {
                        PrimLine(prim)->drawMode = DRAW_HIDE;
                        PrimLine(prim)->x0 =
                            (rand() & 0xFF) - (rand() & 0x3F) - 0x10;
                        PrimLine(prim)->y0 += 0x120;
                        PrimLine(prim)->xLength = -xLen;
                        PrimLine(prim)->yLength = -yLen;
                        PrimLine(prim)->velocityX.val = -xVel;
                        PrimLine(prim)->velocityY.val = -yVel;
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
        if (weatherMode == WEATHER_FOG) {
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

// One of these exists in every room adjacent to the main room.
// Seems like this makes the rain sound fade out as you walk
// into the new room (out of the rainy room)?
// If it is not raining, this has no impact, but still runs.
void EntityFadeRainSound(Entity* self) {
    if (self->step == 0) {
        g_api.PlaySfx(SET_RELEASE_RATE_HIGH_20_21);
        self->step++;
    }
    DestroyEntity(self);
}
