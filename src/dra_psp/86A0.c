// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

#define HUD_NUM_SPRITES 14

extern PlayerHud g_PlayerHud;
extern s32 g_HealingMailTimer[1]; // maybe part of g_PlayerHud
extern s32 D_8013B5E8;

INCLUDE_ASM("dra_psp/psp/dra_psp/86A0", DrawRichterHudSubweapon);

INCLUDE_ASM("dra_psp/psp/dra_psp/86A0", func_psp_090E6058);

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
    LoadTPage((u_long*)(D_800C52F8[10] + 4), 0, 0, 0x3DC, 0x100, 8, mpFillSteps);
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

INCLUDE_ASM("dra_psp/psp/dra_psp/86A0", func_psp_090E7090);

INCLUDE_ASM("dra_psp/psp/dra_psp/86A0", func_psp_090E7150);
