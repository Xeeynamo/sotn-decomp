// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

#define HEART_DROP_CASTLE_FLAG 0
extern EInit g_EInitObtainable;

#if defined(VERSION_PSP) && STAGE != STAGE_ST0
extern s32 g_UserLanguage;
extern char* obtainedStr; // BSS
#else
const char* g_RelicOrbTexts[] = {
#if !defined(VERSION_US) || STAGE == STAGE_ST0
    "を入手した"
#else
    "Obtained ",
#endif
};
#endif

s16 g_RelicOrbTextBg1EY[] = {16, 12, 8, 4, 0, -4, -8, -12};
s16 g_RelicOrbTextBg1SY[] = {-32, -26, -20, -13, -7, -1, 5, 12};
s16 g_RelicOrbTextBg2SY[] = {-16, -12, -8, -4, 0, 4, 8, 12};
s16 g_RelicOrbTextBg2EY[] = {32, 26, 20, 13, 7, 1, -5, -12};
#if STAGE != STAGE_ST0
s16 g_RelicOrbSparkleX[] = {-8, 4, -2, 8, 0, 4, -4, 2};
s16 g_RelicOrbSparkleY[] = {-2, 2, 4, -3, 0, 2, -4, 3};
#endif

extern u16 msgBoxTpage[0x600];

void BlinkItem(Entity* entity, u16 blinkFlag);

// same as e_collect
// INCLUDE_ASM("boss/bo6/nonmatchings/e_collect2", EntityRelicOrb);
// params: (& 0x7FFF) Relic ID
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
    u16 isObtainedTextStored;
#else
    bool isObtainedTextStored;
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
    char sp34[0x100];
#endif

// The unk7C variable matches different other variables
// in different versions. We use this as a hack to match everywhere.
#if STAGE == STAGE_ST0
#define orbUnk7C isObtainedTextStored
#else
#define orbUnk7C var_s2
#endif

#if !defined(VERSION_US) || STAGE == STAGE_ST0
    u16 vramX;
    u16* chPixSrc;
    u16* chPixDst;
    u16 ch;
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
        InitializeEntity(g_EInitObtainable);
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
#if defined(VERSION_PSP) && STAGE != STAGE_ST0
        msgLen = 0;
        var_s2 = 0;
        isObtainedTextStored = false;
        msg = g_api.relicDefs[relicId].name;
        switch (g_UserLanguage) {
        case LANG_EN:
        default:
            obtainedStr = "Obtained";
            break;
        case LANG_FR:
            obtainedStr = "Obtenu \xB1 ";
            break;
        case LANG_SP:
            obtainedStr = "Tienes";
            break;
        case LANG_GE:
            obtainedStr = "erhalten";
            break;
        case LANG_IT:
            obtainedStr = "Ottenuto";
            break;
        }

        if (g_UserLanguage != LANG_GE) {
            sprintf(&sp34, "%s %s", obtainedStr, msg);
        } else {
            sprintf(&sp34, "%s %s", msg, obtainedStr);
        }
        // Presumably this is a strlen call?
        msgLen = func_890CAE0(sp34);
        BlitChar(&sp34[0], 0, 12, 0x100);
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#elif !defined(VERSION_US) || STAGE == STAGE_ST0
        msgLen = 0;
        isObtainedTextStored = false;
        vramX = 0;
        msg = g_api.relicDefs[relicId].name;
        while (true) {
            ch = *msg++;
            if (ch == 0) {
                if (isObtainedTextStored) {
                    break;
                }
                isObtainedTextStored = true;
                msg = g_RelicOrbTexts[0];
            } else {
                ch = (ch << 8) | *msg++;
                chPixSrc = g_api.func_80106A28(ch, 1);
                if (chPixSrc != NULL) {
                    chPixDst = &msgBoxTpage[msgLen * 0x30];
                    for (i = 0; i < 0x30; i++) {
                        *chPixDst++ = *chPixSrc++;
                    }
                    LoadTPage((u_long*)&msgBoxTpage[msgLen * 0x30], 0, 0, vramX,
                              0x100, 0xC, 0x10);
                    vramX += 3;
                    msgLen++;
                }
            }
        }
        self->ext.relicOrb.unk7E = msgLen;
        self->ext.relicOrb.unk7C = 0;
#else
    msgLen = 0;
    isObtainedTextStored = false;
    msg = g_RelicOrbTexts[0];
    chPix = g_Pix[0];
    var_v0_5 = (u8*)chPix;
    for (i = 0; i < 0xC00; i++) {
        *var_v0_5++ = 0;
    }

    msgLen = 0;
    while (true) {
        if (*msg == 0) {
            if (isObtainedTextStored) {
                break;
            }
            msg = g_api.relicDefs[relicId].name;
            isObtainedTextStored = true;
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
        orbUnk7C = self->ext.relicOrb.unk7C;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
#if STAGE == STAGE_ST0
        for (i = 0; prim != NULL; prim = prim->next, i++) {
#else
        for (i = 0; i < 3; prim = prim->next, i++) {
#endif
            if (i == 0) {
                prim->x1 = 0x80 - (orbUnk7C + 1) * 0xC;
                prim->x0 = 0x80 + (orbUnk7C + 1) * 0xC;
                prim->x2 = 0x68 + (orbUnk7C * 0x78) / 7;
                prim->x3 = 0x98 - (orbUnk7C * 0x78) / 7;
                prim->y0 = prim->y1 = g_RelicOrbTextBg1SY[orbUnk7C] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg1EY[orbUnk7C] + 0xA7;
                prim->b2 = prim->b3 -= 0x10;
            } else {
                prim->x0 = 0x68 + (orbUnk7C * 0x78) / 7;
                prim->x1 = 0x98 - (orbUnk7C * 0x78) / 7;
                prim->x3 = 0x80 - (orbUnk7C + 1) * 0xC;
                prim->x2 = 0x80 + (orbUnk7C + 1) * 0xC;
                prim->y0 = prim->y1 = g_RelicOrbTextBg2SY[orbUnk7C] + 0xA7;
                prim->y2 = prim->y3 = g_RelicOrbTextBg2EY[orbUnk7C] + 0xA7;
                prim->g0 = prim->g1 -= 0x10;
            }
        }

        if (++self->ext.relicOrb.unk7C == 8) {
            self->step++;
            self->ext.relicOrb.unk7C = 0;
        }
        break;

    case 9:
        prim = &g_PrimBuf[self->primIndex];
#if defined(VERSION_US) && !defined(VERSION_PSP) && STAGE != STAGE_ST0
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E;
#else
        prim->x0 = 0x80 - self->ext.relicOrb.unk7E * 6;
#endif
        prim->drawMode = DRAW_DEFAULT;
        self->ext.relicOrb.unk7C++;
#if STAGE == STAGE_ST0
        if (self->ext.relicOrb.unk7C > 0x100) {
#else
        if (self->ext.relicOrb.unk7C > 0x60) {
#endif
            DestroyEntity(self);
            return;
        }
        break;
    }

    if (self->step < 2) {
#if STAGE == STAGE_ST0
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 14;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 14;
#elif defined(VERSION_BETA)
        // This is just the function BlinkItem inlined
        prim = &g_PrimBuf[self->primIndex];
        prim->x0 = prim->x2 = self->posX.i.hi - 7;
        prim->x1 = prim->x3 = prim->x0 + 14;
        prim->y0 = prim->y1 = self->posY.i.hi - 7;
        prim->y2 = prim->y3 = prim->y0 + 14;

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
#if STAGE != STAGE_ST0
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
#endif
    }
}

#if STAGE != STAGE_ST0
#if defined(VERSION_BETA)
static u16 OVL_EXPORT(PrizeDrops)[] = {
    0x000C, 0x0017, 0x00D8, 0x012F, 0x000C, 0x0085, 0x0017, 0x00E5,
    0x014A, 0x00EE, 0x013A, 0x0017, 0x000C, 0x00C9, 0x008B, 0x00C8,
    0x0098, 0x0099, 0x0142, 0x0161, 0x008F, 0x011A, 0x011F, 0x0099,
    0x00C9, 0x00F2, 0x0133, 0x0103, 0x0150, 0x013E, 0x000C, 0x0017,
    0x0103, 0x00D6, 0x00E6, 0x0017, 0x0017, 0x0089, 0x0139, 0x0000};
#else
// defined in d_prize_drops.c
extern u16 OVL_EXPORT(PrizeDrops)[];
#endif

// params: Local index of this drop
void EntityHeartDrop(Entity* self) {
    u16 index;
    u8 value;
    PfnEntityUpdate update;

    if (!self->step) {
        index = self->ext.heartDrop.unkB4 =
            self->params + HEART_DROP_CASTLE_FLAG;
        value = g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] >>
                (index & 7);
        if (value & 1) {
            DestroyEntity(self);
            return;
        }

        index -= HEART_DROP_CASTLE_FLAG;
        index = OVL_EXPORT(PrizeDrops)[index];
        if (index < 128) {
            self->unkB8 = (Entity*)EntityPrizeDrop;
        } else {
            self->unkB8 = (Entity*)EntityEquipItemDrop;
            index -= 128;
        }
        self->params = index + 0x8000;
    } else {
        index = self->ext.heartDrop.unkB4;
        if (self->step < 5) {
            if (self->hitFlags) {
                g_CastleFlags[(index >> 3) + CASTLE_COLLECTIBLES_100] |=
                    1 << (index & 7);
                self->step = 5;
            }
        }
    }
    update = (PfnEntityUpdate)self->unkB8;
    update(self);
}

// same as e_collect
// INCLUDE_ASM("boss/bo6/nonmatchings/e_collect2", EntityMessageBox);
#if !defined(VERSION_BETA)
// params: message box duration, in frames
// ext.messageBox.label: box size and text to render
void EntityMessageBox(Entity* self) {
    const u16 VramX = 0;
    const u16 VramY = 0x180;
    const int FontW = 12;
    const int FontH = 16;
    const int FontLen = FontW * FontH / 2 / sizeof(u16); // 4bpp

    Primitive* prim;
    s32 i;
    char* str;
    s32 primIndex;
    u16 xOffset;
    u8* chPix;
    u8* dstPix;
    u8 ch;
    RECT rect;

    u16 x;
    u16 y;
    u16 nCh;

    u16 chjp;
    u16* srcJpPix;
    u16* dstJpPix;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitObtainable);
        self->flags |= FLAG_UNK_10000;
        self->flags ^= FLAG_POS_CAMERA_LOCKED;
        if (!self->params) {
            self->params = 96; // default to 96 frames, or 1.5 seconds
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        str = self->ext.messageBox.label;
        self->ext.messageBox.width = *str++;
        self->ext.messageBox.height = *str++;
        self->ext.messageBox.label += 2;
        break;
    case 1:
        rect.x = 0;
        rect.y = 0x180;
        rect.w = 64;
        rect.h = self->ext.messageBox.height;
        ClearImage(&rect, 0, 0, 0);

        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->type = PRIM_SPRT;
                prim->tpage = 0x10;
                prim->x0 = self->posX.i.hi - self->ext.messageBox.width / 2;
                prim->y0 = self->posY.i.hi - self->ext.messageBox.height / 2;
                prim->u0 = 0;
                prim->v0 = 0x80;
                prim->u1 = self->ext.messageBox.width;
                prim->v1 = self->ext.messageBox.height;
                prim->clut = 0x1A1;
                prim->priority = 0x1FD;
                prim->drawMode = DRAW_HIDE;
            } else {
                prim->type = PRIM_G4;
                prim->x0 = prim->x2 =
                    self->posX.i.hi - self->ext.messageBox.width / 2 - 4;
                prim->x1 = prim->x3 =
                    self->posX.i.hi + self->ext.messageBox.width / 2 + 4;
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0;
                if (i == 1) {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi - self->ext.messageBox.height / 2 - 4;
                    prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                } else {
                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + self->ext.messageBox.height / 2 + 4;
                    prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                }
                prim->priority = 0x1FC;
                prim->drawMode = DRAW_TPAGE | DRAW_TRANSP;
            }
        }
        self->step++;
        break;
    case 2:
#if defined(VERSION_US)
        dstPix = g_Pix[0];
        chPix = dstPix;
        str = self->ext.messageBox.label;
        xOffset = 0;
        for (i = 0;
             i < self->ext.messageBox.width / 2 * self->ext.messageBox.height;
             i++) {
            *chPix++ = 0;
        }

        chPix = dstPix;
        while (true) {
            if (*str == 0) {
                break;
            }
            if (*str == 1) {
                str++;
                xOffset = 0;
                chPix = &dstPix[self->ext.messageBox.width * 8];
            } else {
                str = BlitChar(
                    str, &xOffset, chPix, (self->ext.messageBox.width >> 1));
            }
        }
        LoadTPage((u_long*)dstPix, 0, 0, VramX, VramY,
                  self->ext.messageBox.width, self->ext.messageBox.height);
#elif defined(VERSION_PSP)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        BlitChar(str, 0, 0, 0x180);
#elif defined(VERSION_HD)
        nCh = 0;
        x = VramX;
        y = VramY;
        str = self->ext.messageBox.label;
        while (true) {
            chjp = *str++;
            if (!chjp) {
                break;
            }
            if (chjp == 1) {
                y += FontH;
                x = 0;
            } else {
                chjp = (*str++ | (chjp << 8));
                srcJpPix = g_api.func_80106A28(chjp, 1);
                if (srcJpPix) {
                    dstJpPix = &msgBoxTpage[nCh * FontLen];
                    for (i = 0; i < FontLen; i++) {
                        *dstJpPix++ = *srcJpPix++;
                    }
                    LoadTPage(
                        &msgBoxTpage[nCh * FontLen], 0, 0, x, y, FontW, FontH);
                    x += 3;
                    nCh++;
                }
            }
        }
#endif
        self->ext.messageBox.duration = 0;
        self->step++;
        break;
    case 3:
        self->ext.messageBox.duration++;
        prim = &g_PrimBuf[self->primIndex];
        prim = prim->next;
        for (i = 0; prim != NULL; prim = prim->next, i++) {
            if (i == 0) {
                prim->y2 = prim->y3 =
                    prim->y0 + (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->b0 = prim->b1 -= 0x10;
            } else {
                prim->y0 = prim->y1 =
                    prim->y2 - (self->ext.messageBox.height + 8) *
                                   self->ext.messageBox.duration / 8;
                prim->g2 = prim->g3 -= 0x10;
            }
        }
        if (self->ext.messageBox.duration == 8) {
            self->ext.messageBox.duration = 0;
            self->step++;
        }
        break;
    case 4:
        prim = &g_PrimBuf[self->primIndex];
        prim->drawMode = DRAW_DEFAULT;
        self->ext.messageBox.duration++;
        if (self->ext.messageBox.duration > self->params) {
            DestroyEntity(self);
        }
        break;
    }
}

#endif

#endif
