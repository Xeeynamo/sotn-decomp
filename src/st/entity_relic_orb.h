// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

const char* g_RelicOrbTexts[] = {
#if !defined(VERSION_US) || STAGE == STAGE_ST0
    "を入手した"
#else
    "Obtained ",
#endif
};
u16 g_RelicOrbTextBg1EY[] = {16, 12, 8, 4, 0, -4, -8, -12};
u16 g_RelicOrbTextBg1SY[] = {-32, -26, -20, -13, -7, -1, 5, 12};
u16 g_RelicOrbTextBg2SY[] = {-16, -12, -8, -4, 0, 4, 8, 12};
u16 g_RelicOrbTextBg2EY[] = {32, 26, 20, 13, 7, 1, -5, -12};
#if STAGE != STAGE_ST0
u16 g_RelicOrbSparkleX[] = {-8, 4, -2, 8, 0, 4, -4, 2};
u16 g_RelicOrbSparkleY[] = {-2, 2, 4, -3, 0, 2, -4, 3};
#endif

extern u16 g_InitializeData0[];
extern u16 msgBoxTpage[0x600];

void BlinkItem(Entity* entity, u16 blinkFlag);
void EntityRelicOrb(Entity* self) {
#if STAGE == STAGE_ST0
    const int PrimCount = 3;
#else
    const int PrimCount = 7;
#endif
    // prim 0: green rectangle for Obtained text bg
    // prim 1: blue rectangle for Obtained text bg

#if defined(VERSION_BETA) || STAGE == STAGE_ST0
    const int MaxItemSlots = LEN(g_ItemIconSlots);
#else
    const int MaxItemSlots = LEN(g_ItemIconSlots) - 1;
#endif
    u16 relicId;
#if defined(VERSION_PSP) || STAGE == STAGE_ST0
    u16 temp;
#else
    bool temp;
#endif
    RECT rect;
    Primitive* prim;
    const char* msg;
    s32 primIndex;
    s16 iconSlot;
    s32 i;
    u8* chPix;
    u16 var_s8;
    u16 msgLen;

    // unnamed variables
    u8* var_v0_5;
    u16 var_s2;
#if defined(VERSION_PSP)
    const char sp34[0x100];
#endif

#if defined(VERSION_BETA) || STAGE == STAGE_ST0
    u16 vramX;
    u16* chPixSrc;
    u16* chPixDst;
    u16 ch;
    s16 left, top, right, bottom;
#endif

    relicId = self->params & 0x7FFF;
    if (self->step && self->step < 5 && self->hitFlags) {
        self->step = 5;
    }

    switch (self->step) {
    case 0:
#if STAGE != STAGE_ST0
        // If the relic was previously obtained, do not spawn it.
        if (g_Status.relics[relicId] & RELIC_FLAG_FOUND) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_InitializeData0);
        for (iconSlot = 0; iconSlot < MaxItemSlots; iconSlot++) {
            if (!g_ItemIconSlots[iconSlot]) {
                break;
            }
        }

        if (iconSlot >= MaxItemSlots) {
            self->step = 0;
            return;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, PrimCount);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
#if STAGE == STAGE_ST0
        g_api.LoadEquipIcon(g_api.equipDefs[relicId].icon,
                            g_api.equipDefs[relicId].iconPalette, iconSlot);
#else
        self->ext.relicOrb.iconSlot = iconSlot;
#if !defined(VERSION_BETA)
        g_ItemIconSlots[iconSlot] = 0x10;
#endif
        g_api.LoadEquipIcon(g_api.relicDefs[relicId].icon,
                            g_api.relicDefs[relicId].iconPalette, iconSlot);
#endif
        prim = &g_PrimBuf[primIndex];
        for (i = 0; prim != NULL; i++) {
            if (i != 0) {
#if STAGE == STAGE_ST0
                prim->type = PRIM_G4;
#endif
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->tpage = 0x1A;
                prim->clut = iconSlot + 0x1D0;
                // Pulls iconSlot & 0b00111
                prim->u0 = prim->u2 = ((iconSlot & 7) << 4) + 1;
                prim->u1 = prim->u3 = prim->u0 + 14;
                // Pulls iconSlot & 0b11000
                prim->v0 = prim->v1 = ((iconSlot & 24) << 1) + 0x81;
                prim->v2 = prim->v3 = prim->v0 + 14;
#if STAGE != STAGE_ST0
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
#else
                prim->drawMode = DRAW_UNK02;
#endif
            }
#if STAGE == STAGE_ST0
            prim->priority = 0xC0;
#else
            prim->priority = 0x7E;
#endif
            prim = prim->next;
        }
#if STAGE != STAGE_ST0
        self->posY.i.lo = 0x8000;
        self->velocityY = FIX(0.25);
        self->ext.relicOrb.floatTimer = 64;
        self->ext.relicOrb.yFloatSpeed = -FIX(0.0078125);
#endif
        break;
#if STAGE != STAGE_ST0
    case 1:
        // The relic floats in the air
        self->velocityY += self->ext.relicOrb.yFloatSpeed;
        if (!--self->ext.relicOrb.floatTimer) {
            self->ext.relicOrb.floatTimer = 64;
            self->ext.relicOrb.yFloatSpeed = -self->ext.relicOrb.yFloatSpeed;
        }
        MoveEntity();
        iconSlot = self->ext.relicOrb.iconSlot;
        g_ItemIconSlots[iconSlot] = 0x10;
        break;
#endif
    case 5:
#if STAGE != STAGE_ST0
        g_api.func_800FE044(relicId, 0x2000);
#if !defined(VERSION_BETA)
        msg = g_api.relicDefs[relicId].name;
        if (relicId >= RELIC_SWORD_CARD && relicId < RELIC_FAERIE_CARD) {
            g_Status.relics[relicId] ^= RELIC_FLAG_ACTIVE;
        }
#endif
        self->flags |= FLAG_UNK_10000;
#else
        g_api.PlaySfx(SFX_UNK_618);

        g_Status.relics[relicId] = 3;
#endif

        // Reserve space in the VRAM to store the pre-render texture with the
        // "obtained" relic message
        rect.x = 0;
        rect.y = 256;
        rect.w = 64;
        rect.h = 16;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 3; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = 0x10;
                prim->y0 = 0xA0;
                prim->u0 = 0;
                prim->v0 = 0;
                prim->u1 = 0xF0;
                prim->v1 = 0x10;
#if STAGE == STAGE_ST0
                prim->clut = 0x1F8;
#else
                prim->clut = 0x1A1;
#endif
                prim->priority = 0x1FE;
                prim->drawMode = DRAW_HIDE;
            } else {
#if STAGE != STAGE_ST0
                prim->type = PRIM_G4;
#endif
                prim->x0 = prim->x1 = prim->x2 = prim->x3 = 0x80;
                prim->y0 = prim->y1 = prim->y2 = prim->y3 = 0xA7;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;

                if (i == 1) {
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }

        self->step++;
        break;

    case 6:
        // This case creates the texture "Obtained RELIC_NAME" and stores it
        // in the VRAM
#if defined(VERSION_PSP)
        msgLen = 0;
        var_s2 = 0;
        temp = false;
        msg = g_api.relicDefs[relicId].name;
        switch (D_PSP_8B42058) {
        case 1:
        default:
            D_psp_0924BC60 = &D_psp_09246640;
            break;
        case 2:
            D_psp_0924BC60 = &D_psp_09246650;
            break;
        case 3:
            D_psp_0924BC60 = &D_psp_09246660;
            break;
        case 4:
            D_psp_0924BC60 = &D_psp_09246668;
            break;
        case 5:
            D_psp_0924BC60 = &D_psp_09246678;
            break;
        }

        if (D_PSP_8B42058 != 4) {
            func_890C6FC(&sp34, &D_psp_09246688, D_psp_0924BC60, msg);
        } else {
            func_890C6FC(&sp34, &D_psp_09246688, msg, D_psp_0924BC60);
        }
        // Presumably this is a strlen call?
        msgLen = func_890CAE0(sp34);
        BlitChar(&sp34[0], 0, 12, 0x100);
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#elif defined(VERSION_BETA) || STAGE == STAGE_ST0
        msgLen = 0;
        temp = false;
        vramX = 0;
        msg = g_api.relicDefs[relicId].name;
        while (true) {
            ch = *msg++;
            if (ch == 0) {
                if (temp) {
                    break;
                }
                temp = true;
                msg = g_RelicOrbTexts[0];
            } else {
                ch = (ch << 8) | *msg++;
                chPixSrc = g_api.func_80106A28(ch, 1);
                if (chPixSrc != NULL) {
                    chPixDst = &msgBoxTpage[msgLen * 0x30];
                    for (i = 0; i < 0x30; i++) {
                        *chPixDst++ = *chPixSrc++;
                    }
                    LoadTPage(&msgBoxTpage[msgLen * 0x30], 0, 0, vramX, 0x100,
                              0xC, 0x10);
                    vramX += 3;
                    msgLen++;
                }
            }
        }
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#else
        msgLen = 0;
        temp = false;
        msg = g_RelicOrbTexts[0];
        chPix = g_Pix[0];
        var_v0_5 = (u8*)chPix;
        for (i = 0; i < 0xC00; i++) {
            *var_v0_5++ = 0;
        }

        msgLen = 0;
        while (true) {
            if (*msg == 0) {
                if (temp) {
                    break;
                }
                msg = g_api.relicDefs[relicId].name;
                temp = true;
            } else {
                msg = BlitChar(msg, &msgLen, chPix, 0xC0);
            }
        }

        LoadTPage(chPix, 0, 0, 0, 0x100, 0x180, 0x10);
        self->ext.relicOrb.unk7C = 0;
        self->ext.relicOrb.unk7E = msgLen;
#endif
        self->step++;
        break;
    case 7:
        // Animates the blue/green rectangle for the Obtain text bg
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 2; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->x2 -= 3;
                prim->x3 += 3;
                prim->y0 = prim->y1 -= 4;
                prim->y2 = prim->y3 += 2;
            } else {
                prim->x0 -= 3;
                prim->x1 += 3;
                prim->y0 = prim->y1 -= 2;
                prim->y2 = prim->y3 += 4;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->ext.relicOrb.unk7C = 0;
            self->step++;
        }
        break;

    case 8:
        var_s2 = self->ext.relicOrb.unk7C;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; i < 3; i++) {
            if (i == 0) {
                prim->x1 = 0x80 - (var_s2 + 1) * 0xC;
                prim->x0 = 0x80 + (var_s2 + 1) * 0xC;
                prim->x2 = 0x68 + (var_s2 * 0x78) / 7;
                prim->x3 = 0x98 - (var_s2 * 0x78) / 7;
                prim->y0 = prim->y1 = g_RelicOrbTextBg1SY[var_s2] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg1EY[var_s2] + 0xA7;
                prim->b2 = prim->b3 -= 0x10;
            } else {
                prim->x0 = 0x68 + (var_s2 * 0x78) / 7;
                prim->x1 = 0x98 - (var_s2 * 0x78) / 7;
                prim->x3 = 0x80 - (var_s2 + 1) * 0xC;
                prim->x2 = 0x80 + (var_s2 + 1) * 0xC;
                prim->y0 = prim->y1 = g_RelicOrbTextBg2SY[var_s2] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg2EY[var_s2] + 0xA7;
                prim->g0 = prim->g1 -= 0x10;
            }
            prim = prim->next;
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->step++;
            self->ext.relicOrb.unk7C = 0;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
#if defined(VERSION_US) && !defined(VERSION_PSP)
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E;
#else
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E * 6;
#endif
        prim->drawMode = DRAW_DEFAULT;
        self->ext.relicOrb.unk7C++;
        if (self->ext.relicOrb.unk7C > 0x60) {
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->step < 2) {
#if defined(VERSION_BETA)
        // This is just the function BlinkItem inlined
        prim = &g_PrimBuf[self->primIndex];

        left = self->posX.i.hi - 7;
        right = self->posX.i.hi + 7;
        prim->x2 = left;
        prim->x0 = left;
        prim->x3 = right;
        prim->x1 = right;

        top = self->posY.i.hi - 7;
        bottom = self->posY.i.hi + 7;
        prim->y1 = top;
        prim->y0 = top;
        prim->y3 = bottom;
        prim->y2 = bottom;

        if (g_Timer & RENDERFLAGS_NOSHADOW) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 255;
        } else {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = 128;
        }
#else
        BlinkItem(self, g_Timer);
        prim = &g_PrimBuf[self->primIndex];
#endif

        // Animates the four sparkles while the relic is floating
        for (i = 0; i < 3; i++) { // Skip the first three primitives
            prim = prim->next;
        }

        if (!self->ext.relicOrb.sparkleCycle) {
            for (i = 0; i < 4; i++) {
                if (prim->drawMode == DRAW_HIDE) {
                    prim->tpage = 0x1A;
                    prim->clut = 0x1B1;
                    prim->u0 = prim->u2 = 0;
                    prim->u1 = prim->u3 = 0x10;
                    prim->v0 = prim->v1 = 0x50;
                    prim->v2 = prim->v3 = 0x60;

                    var_s8 = self->ext.relicOrb.sparkleAnim & 7;
                    iconSlot = self->posX.i.hi;
                    iconSlot += g_RelicOrbSparkleX[var_s8];
                    prim->x0 = prim->x2 = iconSlot - 6;
                    prim->x1 = prim->x3 = iconSlot + 6;

                    iconSlot = self->posY.i.hi;
                    iconSlot += g_RelicOrbSparkleY[var_s8];
                    prim->y0 = prim->y1 = iconSlot - 6;
                    prim->y2 = prim->y3 = iconSlot + 6;

                    prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                    prim->p1 = 0;
                    prim->priority = 0x7F;
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    break;
                }
                prim = prim->next;
            }

            self->ext.relicOrb.sparkleCycle = 4;
            self->ext.relicOrb.sparkleAnim++;
        } else {
            self->ext.relicOrb.sparkleCycle--;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 3; i++) {
        prim = prim->next;
    }

    for (; prim != NULL; prim = prim->next) {
        if (prim->drawMode != DRAW_HIDE) {
            if (prim->p1 & 3) {
                prim->y0 = prim->y1--;
                prim->y2 = prim->y3--;
            } else {
                prim->y2 = prim->y3 -= 2;
                prim->x0 = prim->x2++;
                prim->x1 = prim->x3--;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3 -= 6;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 -= 6;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 -= 6;
            prim->p1++;
            if (prim->p1 > 0x10) {
                prim->drawMode = DRAW_HIDE;
            }
        }
    }
}
