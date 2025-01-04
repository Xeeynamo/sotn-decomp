// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

#define HUD_NUM_SPRITES 14

u8 g_HudSpriteX[HUD_NUM_SPRITES] = {
    90, 90, 90, 34, 2, 31, 3, 9, 15, 21, 59, 63, 67, 71,
};
u8 g_HudSpriteY[HUD_NUM_SPRITES] = {
    25, 25, 25, 22, 19, 26, 33, 33, 33, 33, 34, 34, 34, 34,
};
u8 g_HudSpriteU[HUD_NUM_SPRITES] = {
    0x00, 0x10, 0x68, 0x20, 0x00, 0x70, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
u8 g_HudSpriteV[HUD_NUM_SPRITES] = {
    0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x20,
    0x20, 0x20, 0x20, 0x18, 0x18, 0x18, 0x18,
};
u8 g_HudSpriteW[HUD_NUM_SPRITES] = {
    16, 16, 8, 72, 32, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};
u8 g_HudSpriteH[HUD_NUM_SPRITES] = {
    16, 16, 8, 24, 32, 56, 16, 16, 16, 16, 8, 8, 8, 8,
};
u16 g_HudSpriteClut[HUD_NUM_SPRITES] = {
    0x0173, 0x0175, 0x0170, 0x0172, 0x0171, 0x0174, 0x0171,
    0x0171, 0x0171, 0x0171, 0x0196, 0x0196, 0x0196, 0x0196,
};
u16 g_HudSpriteBlend[HUD_NUM_SPRITES] = {
    DRAW_HIDE, DRAW_HIDE, DRAW_HIDE, 0x2000, 0x2000, 0x2000, 0x2000,
    0x2000,    0x2000,    0x2000,    0x2000, 0x2000, 0x2000, 0x2000,
};

extern PlayerHud g_PlayerHud;
extern s32 g_HealingMailTimer[1]; // maybe part of g_PlayerHud

// Need these for now, they might be changed later.
extern Primitive* func_psp_090E4CD0(Primitive*);
extern Primitive* func_psp_090E4828(Primitive*);
void DrawRichterHudSubweapon(void) {
    s32 i;
    s32 temp_s4;
    s32 temp_a0;
    s32 temp_s2;
    Primitive* altPrim;
    Primitive* prim;

    if (D_8003C744 == 5) {
        prim = &g_PrimBuf[g_PlayerHud.primIndex1];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        prim = &g_PrimBuf[g_PlayerHud.primIndex2];
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        return;
    }
    if ((D_8003C744 == 1) && (g_PlayerHud.unk28 == 0)) {
        g_PlayerHud.unk10 = g_Entities[80].hitPoints;
        g_PlayerHud.unk0C = g_PlayerHud.unk10;
        // Not really sure what the point of this is.
        g_PlayerHud.unk1C = (g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10;
        g_PlayerHud.unk20 = 100;
        g_PlayerHud.unk28 = 1;
        D_80139008 = g_Status.hearts;
    }
    if ((D_8003C744 == 2) && (g_PlayerHud.unk28 == 1)) {
        g_PlayerHud.unk10 = g_Entities[85].hitPoints;
        g_PlayerHud.unk0C = g_PlayerHud.unk10;
        g_PlayerHud.unk28 = 2;
    }
    if (g_PlayerHud.unk28 != 100) {
        if (D_8003C744 == 1) {
            g_PlayerHud.unk0C = g_Entities[80].hitPoints;
        }
        if (D_8003C744 == 2 || D_8003C744 == 3) {
            g_PlayerHud.unk0C = g_Entities[85].hitPoints;
        }
        if (g_PlayerHud.unk0C < 0) {
            g_PlayerHud.unk0C = 0;
        }
    }
    if (g_PlayerHud.displayHP < g_Status.hp) {
        g_PlayerHud.displayHP++;
        D_801397FC = 1;
    }
    if (g_PlayerHud.displayHP > g_Status.hp) {
        g_PlayerHud.displayHP--;
    }
    if (D_8003C744 == 1) {
        if (g_PlayerHud.unk1C <
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk1C++;
        }
        if (g_PlayerHud.unk1C >
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk1C--;
        }
    }
    if (D_8003C744 == 2 || D_8003C744 == 3) {
        if (g_PlayerHud.unk1C != 0) {
            g_PlayerHud.unk1C -= 1;
        }
        if (g_PlayerHud.unk20 <
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk20++;
        }
        if (g_PlayerHud.unk20 >
            ((g_PlayerHud.unk0C * 100) / g_PlayerHud.unk10)) {
            g_PlayerHud.unk20--;
        }
    }
    if ((D_8003C744 != 0) && (g_PlayerHud.unk14 != 0)) {
        g_PlayerHud.unk14--;
    }
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xD8, 0x16, 0x20, 0x60);
    if ((D_8003C744 == 3) && (g_PlayerHud.unk20 == 0) &&
        ((g_PlayerHud.unk24 == 0) || (g_PlayerHud.unk24 >= 0x33U))) {
        prim->drawMode = DRAW_HIDE;
        // The i variable is not used, but is set up in the for-loop.
        for (altPrim = &g_PrimBuf[g_PlayerHud.primIndex2], i = 0;
             altPrim != NULL; i++, altPrim = altPrim->next) {
            if (altPrim->p2) {
                continue;
            }
            altPrim->drawMode = DRAW_ABSPOS | DRAW_COLORS;
            if (altPrim->p1) {
                altPrim->p1--;
                continue;
            }
            temp_a0 = rand() & 1;
            altPrim->y0 += temp_a0;
            altPrim->y1 += temp_a0;
            temp_a0 = (rand() & 3) + 1;
            altPrim->y2 += temp_a0;
            altPrim->y3 += temp_a0;
            altPrim->drawMode = DRAW_ABSPOS | DRAW_COLORS;
            if (altPrim->r2 >= 3) {
                temp_s2 = altPrim->r2 - 3;
                func_801071CC(altPrim, temp_s2, 2);
                func_801071CC(altPrim, temp_s2, 3);
            }
            if (altPrim->y2 >= 0x100) {
                altPrim->drawMode =
                    DRAW_ABSPOS | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                if (altPrim->r0) {
                    temp_s2 = altPrim->r0--;
                    func_801071CC(altPrim, temp_s2, 0);
                    func_801071CC(altPrim, temp_s2, 1);
                }
                if (altPrim->y2 >= 0x180) {
                    altPrim->drawMode =
                        DRAW_ABSPOS | DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE |
                        DRAW_COLORS | DRAW_TRANSP;
                }
            }
            if (altPrim->y2 >= 0x200) {
                altPrim->drawMode = DRAW_HIDE;
                altPrim->p2 = 1;
            }
        }
    }

    prim = prim->next;
    temp_s4 = (g_PlayerHud.displayHP * 0x5B) / g_Status.hpMax;
    prim->y0 = prim->y1 = prim->y2 - temp_s4;
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xE4, 0x70, 9, 3);
    temp_s4 = (g_PlayerHud.unk1C * 0x5B) / 100;
    if (temp_s4 < 0) {
        temp_s4 = 0;
    }
    prim->y0 = prim->y1 = prim->y2 - temp_s4;
    if (!(prim->p2--)) {
        prim->p1++;
        if (prim->p1 == 9) {
            prim->p1 = 0;
        }
        if (D_8003C744 == 2) {
            prim->p2 = 1;
        } else {
            prim->p2 = 4;
        }
        prim->clut = prim->p1 + 0x103;
    }
    temp_s2 = prim->clut;
    prim = prim->next;
    SetPrimRect(prim, g_PlayerHud.unk14 + 0xEC, 0x70, 9, 3);
    temp_s4 = (g_PlayerHud.unk20 * 0x5B) / 100;
    if (temp_s4 > 0x5B) {
        temp_s4 = 0x5B;
    }
    prim->y0 = prim->y1 = prim->y2 - temp_s4;
    prim->clut = temp_s2;
    prim = prim->next;

    prim->u0 = (g_Status.hearts / 10) * 8;
    prim->v0 = 0x60;
    prim->u1 = ((g_Status.hearts / 10) * 8) + 8;
    prim->v1 = 0x60;
    prim->u2 = (g_Status.hearts / 10) * 8;
    prim->v2 = 0x68;
    prim->u3 = ((g_Status.hearts / 10) * 8) + 8;
    prim->v3 = 0x68;
    // Perhaps flashes the heart numbers when you have enough for a crash
    if (g_Player.status & PLAYER_STATUS_UNK200000) {
        if (g_Timer & 2) {
            prim->clut = 0x103;
        } else {
            prim->clut = 0x100;
        }
    } else {
        prim->clut = 0x103;
    }
    altPrim = prim;
    prim = prim->next;
    prim->u0 = (g_Status.hearts % 10) * 8;
    prim->v0 = 0x60;
    prim->u1 = ((g_Status.hearts % 10) * 8) + 8;
    prim->v1 = 0x60;
    prim->u2 = (g_Status.hearts % 10) * 8;
    prim->v2 = 0x68;
    prim->u3 = ((g_Status.hearts % 10) * 8) + 8;
    prim->v3 = 0x68;

    prim->clut = altPrim->clut;
    prim->drawMode = altPrim->drawMode;
    prim = prim->next;

    if (g_PlayableCharacter == PLAYER_MARIA) {
        prim = func_psp_090E4CD0(prim);
    } else {
        prim = func_psp_090E4828(prim);
    }
    prim = prim->next;

    if (g_PlayerHud.unk24 == 0) {
        return;
    }
    // This acts like a switch, but does not appear to match if you try one.
    // Checking != 0 is redundant due to the prior if-block.
    if (g_PlayerHud.unk24 != 0 && g_PlayerHud.unk24 < 9) {
        prim->clut = g_PlayerHud.unk24 + 0x102;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 9) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0);
        prim->clut = 0x103;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 10) {
        SetTexturedPrimRect(prim, 0x21, 0x1C, 0x40, 8, 0x40, 0x10);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 11) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0x18);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 12) {
        SetTexturedPrimRect(prim, 0x21, 0x14, 0x40, 0x18, 0x40, 0x40);
        prim->clut = 0x112;
        g_PlayerHud.unk24++;
    } else if (13 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 20) {
        prim->clut = 0x112 - (g_PlayerHud.unk24 - 13);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 21) {
    } else if (51 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 58) {
        prim->clut = g_PlayerHud.unk24 + 0xD8;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 59) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0x18);
        prim->clut = 0x103;
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 60) {
        SetTexturedPrimRect(prim, 0x21, 0x1C, 0x40, 8, 0x40, 0x10);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 61) {
        SetTexturedPrimRect(prim, 0x21, 0x18, 0x40, 0x10, 0x40, 0);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 62) {
        SetTexturedPrimRect(prim, 0x21, 0x14, 0x40, 0x18, 0x40, 0x28);
        prim->clut = 0x10A;
        g_PlayerHud.unk24++;
    } else if (63 <= g_PlayerHud.unk24 && g_PlayerHud.unk24 <= 70) {
        prim->clut = 0x10A - (g_PlayerHud.unk24 - 63);
        g_PlayerHud.unk24++;
    } else if (g_PlayerHud.unk24 == 71) {
        g_PlayerHud.unk24 = 0;
    }
}

void DrawHud(void) {
    Primitive* prim;
    s32 i;

    D_8013B5E8 = 0;
    g_PlayerHud.displayHP = g_Status.hp;
    g_HealingMailTimer[0] = 0;

    if ((g_StageId == STAGE_ST0) || (g_PlayableCharacter != PLAYER_ALUCARD)) {
        DrawRichterHud();
        return;
    }

    g_PlayerHud.primIndex1 = func_800EDD9C(PRIM_GT4, HUD_NUM_SPRITES);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];

    for (i = 0; prim != NULL; i++, prim = prim->next) {
        SetTexturedPrimRect(
            prim, g_HudSpriteX[i], g_HudSpriteY[i], g_HudSpriteW[i],
            g_HudSpriteH[i], g_HudSpriteU[i], g_HudSpriteV[i]);
        prim->tpage = 0x1F;
        prim->clut = g_HudSpriteClut[i];
        prim->priority = 0x1F0;
        prim->drawMode = g_HudSpriteBlend[i];

        if (i == 5) {
            SetPrimRect(prim, g_HudSpriteX[i], g_HudSpriteY[i], g_HudSpriteH[i],
                        g_HudSpriteW[i]);
            prim->y0 = prim->y2;
            prim->x1 = prim->x0;
            prim->x2 = prim->x3;
            prim->y3 = prim->y1;
        }

        if (i == 1) {
            prim->p1 = 0;
            prim->p2 = (rand() & 0xFF) + 8;
            prim->p3 = (7 & rand()) + 1;
        }
    }
}

u16 g_HudSubwpnSpriteClut[HUD_NUM_SPRITES] = {
    0x0175, 0x0176, 0x0175, 0x0176, 0x0175, 0x0176, 0x0175,
    0x0176, 0x0176, 0x0175, 0x0176, 0x0175, 0x0176, 0x0175,
};
u8 g_HudSubwpnSpriteU[HUD_NUM_SPRITES] = {
    0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x20,
    0x20, 0x20, 0x20, 0x10, 0x10, 0x00, 0x00};
u8 g_HudSubwpnSpriteV[HUD_NUM_SPRITES] = {
    0x20, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40};

void DrawHudSubweapon() {
    SubweaponDef subwpn;
    RECT rect;
    Primitive* prim;

    s32 statXPos;
    s32 hpdiff;
    s32 mpFillSteps;
    s32 digitSpacing;
    u32 clut;
    u32 leading_zeros;

    if (g_StageId == STAGE_ST0 || g_PlayableCharacter != PLAYER_ALUCARD) {
        DrawRichterHudSubweapon();
        return;
    }
    func_800EB4F8(D_800C52F8[g_Status.subWeapon], 0, 0x3C0, 0x120);
    prim = &g_PrimBuf[g_PlayerHud.primIndex1];
    if (g_Status.subWeapon != 0) {
        prim->drawMode = DRAW_ABSPOS | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
        prim = prim->next;
        prim->p2--;
        if (!prim->p2) {
            prim->p1 += 1;
            if (prim->p1 == 0xF) {
                prim->p1 = 0;
                prim->p2 = (rand() & 0xFF) + 8;
                prim->p3--;
                if (prim->p3) {
                    prim->p1 = 1;
                    prim->p2 = 1;
                } else {
                    prim->p3 = (rand() & 7) + 1;
                }
            } else {
                prim->p2 = 1;
                prim->clut = g_HudSubwpnSpriteClut[prim->p1 - 1];
                prim->u0 = g_HudSubwpnSpriteU[prim->p1 - 1];
                prim->v0 = g_HudSubwpnSpriteV[prim->p1 - 1];
                prim->u1 = g_HudSubwpnSpriteU[prim->p1 - 1] + 16;
                prim->v1 = g_HudSubwpnSpriteV[prim->p1 - 1];
                prim->u2 = g_HudSubwpnSpriteU[prim->p1 - 1];
                prim->v2 = g_HudSubwpnSpriteV[prim->p1 - 1] + 16;
                prim->u3 = g_HudSubwpnSpriteU[prim->p1 - 1] + 16;
                prim->v3 = g_HudSubwpnSpriteV[prim->p1 - 1] + 16;
            }
        }
        if (prim->p1) {
            prim->drawMode = DRAW_ABSPOS;
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
        prim->drawMode = DRAW_ABSPOS;
    } else {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        prim->drawMode = DRAW_HIDE;
    }

    // Want to use prim = prim->next->next->next but that uses wrong register
    prim = prim->next;
    prim = prim->next;
    prim = prim->next;
    rect.x = 988;
    rect.y = 256;
    rect.w = 2;
    rect.h = 56;

    ClearImage(&rect, 0, 0, 0);
    if (!(g_Status.D_80097BF8 & 1)) {
        if (!(g_GameTimer & 0x3F)) {
            g_Status.mp++;
        }
        if ((CheckEquipmentItemCount(ITEM_MYSTIC_PENDANT, EQUIP_ACCESSORY) !=
             0) &&
            ((g_GameTimer & 0x3F) == 0x1F)) {
            g_Status.mp++;
        }
        if (g_Status.mp > g_Status.mpMax) {
            g_Status.mp = g_Status.mpMax;
        }
    }

    if ((CheckEquipmentItemCount(ITEM_HEALING_MAIL, EQUIP_ARMOR)) &&
        (g_Player.status & PLAYER_STATUS_UNK4000000) &&
        !(g_Player.status & PLAYER_STATUS_TRANSFORM)) {
        g_HealingMailTimer[0]++;
        if (g_HealingMailTimer[0] >= 128) {
            g_Player.unk56 = 2;
            g_Player.unk58 = 1;
            g_HealingMailTimer[0] = 0;
        }
    } else {
        g_HealingMailTimer[0] = 0;
    }

    // Why in the world would this call be in the HUD code? This codebase is
    // awful.
    DecrementStatBuffTimers();

    // Represents MP fill level in fraction of 50 (2% each)
    mpFillSteps = (g_Status.mp * 50) / g_Status.mpMax;
    LoadTPage(
        (u_long*)(D_800C52F8[10] + 4), 0, 0, 0x3DC, 0x100, 8, mpFillSteps);
    // Use one clut if MP is full, otherwise a different one
    if (mpFillSteps == 50) {
        prim->clut = 0x162;
    } else {
        prim->clut = 0x174;
    }

    if (D_8013B5E8 == 0) {
        hpdiff = g_Status.hp - g_PlayerHud.displayHP;
        if (hpdiff > 0) {
            if (hpdiff > 10) {
                g_PlayerHud.displayHP += (hpdiff) / 10;
            } else {
                g_PlayerHud.displayHP++;
            }
        }
        if (hpdiff < 0) {
            if (hpdiff < -10) {
                g_PlayerHud.displayHP += (hpdiff) / 10;
            } else {
                g_PlayerHud.displayHP--;
            }
        }
    } else {
        D_8013B5E8--;
    }
    if (g_PlayerHud.displayHP == g_Status.hpMax) {
        func_800EA5E4(2); // Likely related to HP showing bold when full
    } else if (g_PlayerHud.displayHP <= g_Status.hpMax >> 2) {
        func_800EA5E4(3); // Show yellow if under 1/4 health
    } else {
        func_800EA5E4(1); // Normal health display
    }

    if (g_PlayerHud.displayHP > 999) {
        leading_zeros = 0;
        digitSpacing = 6;
        statXPos = 3;
    } else if (g_PlayerHud.displayHP > 99) {
        leading_zeros = 1;
        digitSpacing = 6;
        statXPos = 6 - digitSpacing;
    } else {
        digitSpacing = 7;
        statXPos = 8 - digitSpacing * 2;
        if (g_PlayerHud.displayHP > 9) {
            leading_zeros = 2;
        } else {
            leading_zeros = 3;
        }
    }
    // Thousands digit of HP
    prim = prim->next;
    prim->u0 = ((g_PlayerHud.displayHP / 1000) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;

    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Hundreds digit of HP
    prim = prim->next;
    prim->u0 = (((g_PlayerHud.displayHP / 100) % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + digitSpacing;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Tens digit of HP
    prim = prim->next;
    prim->u0 = (((g_PlayerHud.displayHP / 10) % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + (digitSpacing * 2);
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;

    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Ones digit of HP
    prim = prim->next;
    prim->u0 = ((g_PlayerHud.displayHP % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + (digitSpacing * 3);
    prim->x1 = prim->x3 = prim->x0 + 8;

    if (g_Status.hearts > 999) {
        leading_zeros = 0;
        statXPos = 0x3B;
    } else if (g_Status.hearts > 99) {
        leading_zeros = 1;
        statXPos = 0x37;
    } else {
        statXPos = 0x33;
        if (g_Status.hearts > 9) {
            leading_zeros = 2;
        } else {
            leading_zeros = 3;
        }
    }

    if (func_800FE3C4(&subwpn, 0, false)) {
        // Enable flickering with g_Timer
        if (g_Timer & 2) {
            clut = 0x196;
        } else {
            clut = 0x193;
        }
    } else {
        clut = 0x196;
    }

    // Thousands digit of hearts
    prim = prim->next;
    prim->u0 = ((g_Status.hearts / 1000) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Hundreds digit of hearts
    prim = prim->next;
    prim->u0 = (((g_Status.hearts / 100) % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + 4;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Tens digit of hearts
    prim = prim->next;
    prim->u0 = (((g_Status.hearts / 10) % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + 8;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->drawMode = DRAW_ABSPOS;
    prim->clut = clut;
    if (leading_zeros != 0) {
        leading_zeros--;
        prim->drawMode = DRAW_HIDE;
    }
    // Ones digit of hearts
    prim = prim->next;
    prim->u0 = ((g_Status.hearts % 10) * 8) + 0x20;
    prim->u2 = prim->u0;
    prim->u1 = prim->u0 + 8;
    prim->u3 = prim->u1;
    prim->x0 = prim->x2 = statXPos + 12;
    prim->x1 = prim->x3 = prim->x0 + 8;
    prim->clut = clut;
}
