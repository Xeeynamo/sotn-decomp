// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"
#include "../dra/menu.h"
#include "servant.h" // for InitializeMode enum

typedef struct EquipMenuHelper {
    s32 equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ u16 cursorW;
    /* 0x06 */ u16 cursorH;
    /* 0x08 */ s32 otIdx;
} MenuContextInit; // size = 0x0C

void MenuDrawStr(const char* str, s32 x, s32 y, MenuContext* ctx);
extern s32 D_80137614;
extern u8* D_8013794C;
extern s32 D_80137950;
extern s32 D_80137954;
extern s32 D_801377FC[NUM_MENU];
extern s16 g_RelicMenuFadeTimer;
extern s32 g_StatBuffTimers[16];
extern MenuData g_MenuData;
extern char* g_ChRgb;
extern u8 D_psp_0914A0D0[];
extern u8 D_psp_09149E90[];
extern u8 D_psp_0914A248[];
extern u8 D_psp_09149FB0[];
extern u_long* D_psp_0914A388[];
extern s32 D_801375CC;
extern s32 D_801375D4;
extern s32 D_psp_091CE1E0;
extern s32 D_psp_091CDE30[];
extern s32 D_psp_091CDDC0[];

extern char** D_800A2D48;
extern char** D_800A2D68;
extern char* D_psp_09147FD8[];
extern char* D_psp_09148200[];
extern char* D_psp_091483F8[];
extern char* D_psp_09148600[];
extern char* D_psp_091487C0[];
extern char* D_psp_091488D0[];
extern char* D_psp_091489A0[];
extern char* D_psp_09148A70[];
extern char* D_psp_09148B48[];
extern char* D_psp_09148BF8[];

#include "../get_lang.h"

void func_psp_090EAFA8(void) {
    D_800A2D68 = GetLang(D_psp_09147FD8, D_psp_09148600, D_psp_09148200,
                         D_psp_091487C0, D_psp_091483F8);
    D_800A2D48 = GetLang(D_psp_091488D0, D_psp_09148B48, D_psp_091489A0,
                         D_psp_09148BF8, D_psp_09148A70);
}

bool CheckIfAllButtonsAreAssigned(void) {
    s32 buf[8];
    s32 i;
    s32 bitMask_Assigned;
    s32* miscPtr;

    for (i = 1; i < 8; i++) {
        buf[i] = 0;
    }

    for (i = 0; i < 7; i++) {
        buf[g_Settings.buttonConfig[i] + 1] = 1;
    }

    // What is the purpose of this loop?
    for (i = 0, miscPtr = &buf[1]; i < 7; miscPtr++, i++) {
        if (*miscPtr == 0) {
            break;
        }
    }

    for (i = 0; i < 7; i++) {
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    bitMask_Assigned = 0;
    miscPtr = g_Settings.buttonConfig;
    for (i = 1; i < 8; i++) {
        bitMask_Assigned |= 1 << *miscPtr++;
    }

    return bitMask_Assigned == 0x7F;
}

bool IsAlucart(void) {
    if (CheckEquipmentItemCount(ITEM_ALUCART_SWORD, EQUIP_HAND) &&
        CheckEquipmentItemCount(ITEM_ALUCART_SHIELD, EQUIP_HAND) &&
        CheckEquipmentItemCount(ITEM_ALUCART_MAIL, EQUIP_ARMOR))
        return true;
    return false;
}

void func_800F4994(void) {
    s32* statsPtr;
    s32 correctStonesEquipped;
    s32 hourOfDay;
    s32 i, j;
    s32 statBonus;

    statsPtr = g_Status.statsEquip;
    for (i = 0; i < 4; i++) {
        *statsPtr++ = 0;
    }

    // Iterate through each Item Slot
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus = g_AccessoryDefs[g_Status.equipment[HEAD_SLOT + i]]
                            .statsBonus[j];
            if (statBonus > 128) {
                statBonus -= 256;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }
    hourOfDay = g_Status.timerHours % 24;

    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_SUNSTONE, EQUIP_ACCESSORY);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_MOONSTONE, EQUIP_ACCESSORY);
        statsPtr = g_Status.statsEquip;
        for (i = 0; i < 4; i++) {
            *statsPtr++ += correctStonesEquipped * 5;
        }
    }

    if (g_StatBuffTimers[4]) {
        g_Status.statsEquip[STAT_STR] += 20;
    }
    if (g_StatBuffTimers[3]) {
        g_Status.statsEquip[STAT_INT] += 20;
    }
    if (g_StatBuffTimers[2]) {
        g_Status.statsEquip[STAT_LCK] += 20;
    }
    if (g_Status.relics[RELIC_RIB_OF_VLAD] & RELIC_FLAG_ACTIVE) {
        g_Status.statsEquip[STAT_CON] += 10;
    }
    if (g_Status.relics[RELIC_EYE_OF_VLAD] & RELIC_FLAG_ACTIVE) {
        g_Status.statsEquip[STAT_LCK] += 10;
    }
    if (g_Status.relics[RELIC_TOOTH_OF_VLAD] & RELIC_FLAG_ACTIVE) {
        g_Status.statsEquip[STAT_STR] += 10;
    }
    if (g_Status.relics[RELIC_RING_OF_VLAD] & RELIC_FLAG_ACTIVE) {
        g_Status.statsEquip[STAT_INT] += 10;
    }
    if (IsAlucart()) {
        g_Status.statsEquip[STAT_LCK] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] = g_Status.statsBase[1] + g_Status.statsEquip[1] * 8;
    g_Status.statsTotal[2] = g_Status.statsBase[2] + g_Status.statsEquip[2] * 4;
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

s32 CalcAttack(u32 equipId, u32 otherEquipId) {
    s32 i;
    s16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (g_EquipDefs[equipId].itemCategory == ITEM_FOOD ||
        g_EquipDefs[equipId].itemCategory == ITEM_MEDICINE) {
        return 0;
    }
    if (g_EquipDefs[equipId].itemCategory == ITEM_SHIELD &&
        g_EquipDefs[equipId].attack == 1) {
        return 0;
    }

    if (equipId == ITEM_ALUCARD_SHIELD) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            g_AccessoryDefs[g_Status.equipment[2 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (totalAttack <= strengthStat) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    if (equipId == ITEM_BADELAIRE) {
        totalAttack += g_Status.timerHours;
    }
    if (equipId == ITEM_MURAMASA) {
        totalAttack += SquareRoot0(g_Status.D_80097C40);
    }
    if (equipId == ITEM_SHIELD_ROD &&
        g_EquipDefs[otherEquipId].itemCategory == ITEM_SHIELD) {
        totalAttack += 5;
    }
    if (equipId == ITEM_SWORD_FAMILIAR) {
        totalAttack += g_Status.statsFamiliars[FAM_STATS_SWORD].level;
    }
    if (g_StatBuffTimers[1]) {
        totalAttack += 20;
    }
    if (totalAttack < 0) {
        totalAttack = 0;
    }
    if (totalAttack > 999) {
        totalAttack = 999;
    }
    return totalAttack;
}

void func_800F4F48(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        g_Status.attackHands[i] =
            CalcAttack(g_Status.equipment[i], g_Status.equipment[1 - i]);
    }
}

void CalcDefense(void) {
    Accessory* acc;
    s32 thisHandItem;
    s32 i;
    s16 totalDefense;

    totalDefense = 0;
    g_Status.elementsWeakTo = 0;
    g_Status.elementsResist = 0;
    g_Status.elementsImmune = 0;
    g_Status.elementsAbsorb = 0;

    // Iterate over player's hands, hand 0 and hand 1.
    for (i = 0; i < 2; i++) {
        thisHandItem = g_Status.equipment[i];
        totalDefense += g_EquipDefs[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if ((thisHandItem == ITEM_SHIELD_ROD) &&
            g_EquipDefs[g_Status.equipment[1 - i]].itemCategory ==
                ITEM_SHIELD) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &g_AccessoryDefs[g_Status.equipment[i + 2]];
        totalDefense += acc->defBonus;
        g_Status.elementsWeakTo |= acc->weakToElements;
        g_Status.elementsResist |= acc->resistElements;
        g_Status.elementsImmune |= acc->immuneElements;
        g_Status.elementsAbsorb |= acc->absorbElements;
    }

    if (CheckEquipmentItemCount(ITEM_MEDUSA_SHIELD, EQUIP_HAND) != 0) {
        g_Status.elementsImmune |= ELEMENT_STONE;
    }
    if (CheckEquipmentItemCount(ITEM_FIRE_SHIELD, EQUIP_HAND) != 0) {
        g_Status.elementsImmune |= ELEMENT_FIRE;
    }
    if (g_Status.relics[RELIC_HEART_OF_VLAD] & RELIC_FLAG_ACTIVE) {
        g_Status.elementsImmune |= ELEMENT_CURSE;
    }
    if (g_StatBuffTimers[SBT_RESISTFIRE]) {
        g_Status.elementsResist |= ELEMENT_FIRE;
    }
    if (g_StatBuffTimers[SBT_RESISTICE]) {
        g_Status.elementsResist |= ELEMENT_ICE;
    }
    if (g_StatBuffTimers[SBT_RESISTTHUNDER]) {
        g_Status.elementsResist |= ELEMENT_THUNDER;
    }
    if (g_StatBuffTimers[SBT_RESISTCURSE]) {
        g_Status.elementsResist |= ELEMENT_CURSE;
    }
    if (g_StatBuffTimers[SBT_RESISTHOLY]) {
        g_Status.elementsResist |= ELEMENT_HOLY;
    }
    if (g_StatBuffTimers[SBT_RESISTSTONE]) {
        g_Status.elementsResist |= ELEMENT_STONE;
    }
    if (g_StatBuffTimers[SBT_RESISTDARK]) {
        g_Status.elementsResist |= ELEMENT_DARK;
    }

    totalDefense += (SquareRoot0(g_Status.statsTotal[STAT_CON]) - 2);

    if (CheckEquipmentItemCount(ITEM_WALK_ARMOR, EQUIP_ARMOR) != 0) {
        totalDefense += g_RoomCount / 60;
    }

    if (g_StatBuffTimers[SBT_DEF]) {
        totalDefense += 20;
    }
    if (totalDefense < 0) {
        totalDefense = 0;
    }
    if (totalDefense > 999) {
        totalDefense = 999;
    }
    g_Status.defenseEquip = totalDefense;
}

void func_800F53A4(void) {
    func_800F4994();
    func_800F4F48();
    CalcDefense();
}

void func_800F53D4(s32 tpage, s32 otIdx) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];

    if (D_80137614 != 0) {
        SetDrawMode(drawMode, 0, 0, tpage, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

u8 func_800F548C(u8 arg0) {
    if (arg0 & 0x100) {
        return func_800F548C(arg0 & 0xFF);
    }
    if (arg0 & 0x80) {
        return func_800F548C((arg0 & 0x7F) + 3);
    }
    return arg0 << 4;
}

static u32 IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* ctx) {
    if (ctx->unk1.x >= x1) {
        return true;
    }
    if (ctx->unk1.y >= y1) {
        return true;
    }
    if (ctx->unk1.x + ctx->unk1.w <= x0) {
        return true;
    }
    if (ctx->unk1.y + ctx->unk1.h <= y0) {
        return true;
    }
    return false;
}

bool ScissorPolyG4(POLY_G4* poly, MenuContext* ctx) {
    s32 scissorX;
    s32 scissorY;
    s32 diff;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, ctx))
        return true;

    if (ctx->unk1.x > poly->x0) {
        diff = ctx->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
    }

    if (ctx->unk1.y > poly->y0) {
        diff = ctx->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
    }

    scissorX = ctx->unk1.x + ctx->unk1.w;
    if (scissorX < poly->x1) {
        diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
    }

    scissorY = ctx->unk1.y + ctx->unk1.h;
    if (scissorY < poly->y2) {
        diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
    }

    return false;
}

bool ScissorPolyGT4(POLY_GT4* poly, MenuContext* ctx) {
    s32 scissorX;
    s32 scissorY;
    s32 diff;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, ctx))
        return true;

    if (ctx->unk1.x > poly->x0) {
        diff = ctx->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
        poly->u0 += diff;
        poly->u2 += diff;
    }

    if (ctx->unk1.y > poly->y0) {
        diff = ctx->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
        poly->v0 += diff;
        poly->v1 += diff;
    }

    scissorX = ctx->unk1.x + ctx->unk1.w;
    if (scissorX < poly->x1) {
        diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
        poly->u1 -= diff;
        poly->u3 -= diff;
    }

    scissorY = ctx->unk1.y + ctx->unk1.h;
    if (scissorY < poly->y2) {
        diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
        poly->v2 -= diff;
        poly->v3 -= diff;
    }

    return false;
}

bool ScissorSprite(SPRT* sprite, MenuContext* ctx) {
    s32 scissorY;
    s32 scissorX;
    s32 spriteX;
    s32 spriteY;
    s32 diff;

    if (IsOutsideDrawArea(sprite->x0, sprite->x0 + sprite->w, sprite->y0,
                          sprite->y0 + sprite->h, ctx))
        return true;

    if (ctx->unk1.x > sprite->x0) {
        diff = ctx->unk1.x - sprite->x0;
        sprite->x0 += diff;
        sprite->u0 += diff;
        sprite->w -= diff;
    }

    if (ctx->unk1.y > sprite->y0) {
        diff = ctx->unk1.y - sprite->y0;
        sprite->y0 += diff;
        sprite->v0 += diff;
        sprite->h -= diff;
    }

    spriteX = sprite->x0 + sprite->w;
    scissorX = ctx->unk1.x + ctx->unk1.w;
    if (spriteX > scissorX) {
        diff = spriteX - scissorX;
        sprite->w -= diff;
    }

    spriteY = sprite->y0 + sprite->h;
    scissorY = ctx->unk1.y + ctx->unk1.h;
    if (spriteY > scissorY) {
        diff = spriteY - scissorY;
        sprite->h -= diff;
    }

    return false;
}

void MenuDrawImg(MenuContext* ctx, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v,
                 s32 clut, s32 tpage, bool disableTexShade, s32 c) {
    s32 otIdx;
    SPRT* sp;
    OT_TYPE* ot;

    ot = g_CurrentBuffer->ot;
    sp = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    if (D_psp_091CE1E0 == 1) {
        clut = 0x15E;
    }
    if (D_psp_091CE1E0 == 2) {
        clut = 0x15D;
    }
    if (ctx) {
        otIdx = ctx->otIdx + 2;
    } else {
        otIdx = 0x1FF;
    }
    SetSemiTrans(sp, 0);
    SetShadeTex(sp, disableTexShade);
    sp->x0 = x;
    sp->y0 = y;
    sp->w = w;
    sp->h = h;
    sp->u0 = u;
    sp->v0 = v;
    if (ctx == NULL || !ScissorSprite(sp, ctx)) {
        sp->r0 = c;
        sp->g0 = c;
        sp->b0 = c;
        sp->clut = g_ClutIds[clut];
        AddPrim(&ot[otIdx], sp);
        g_GpuUsage.sp++;
        func_800F53D4(tpage, otIdx);
    }
}

void func_800F5A90(void) {
    MenuDrawImg(NULL, 96, 96, 64, 64, 0, 0, 0, 0x114, 1, 0);
}

void func_800F5AE4(MenuContext* ctx) {
    s32 i, x;

    for (i = 0, x = 72; i < 3; i++, x += 128)
        MenuDrawImg(ctx, x, 201, 128, 16, (i & 1) << 7, func_800F548C(2), 0x1A1,
                    (i / 2) + 6, 1, 0);
}

void MenuDrawSprite(
    MenuContext* ctx, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 isAlpha, s32 colorIntensity, s32 fade) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    s32 otIdx = ctx->otIdx + 2;
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    u32 polyColorIntensity;
    s32 temp;

    if (ctx == &g_MenuData.menus[MENU_DG_BG]) {
        otIdx--;
    }

    setSemiTrans(poly, 0);
    setShadeTex(poly, isAlpha);
    SetTexturedPrimRect((Primitive*)poly, x, y, width, height, u, v);

    if (!ScissorPolyGT4(poly, ctx)) {
        poly->tpage = tpage;
        poly->clut = g_ClutIds[clut];
        func_80107250(poly, colorIntensity);
        if (fade == 1) {
            polyColorIntensity = (poly->y2 - poly->y0) * 4;
            func_801071CC(poly, polyColorIntensity, 0);
            func_801071CC(poly, polyColorIntensity, 1);
        }
        if (fade == 2) {
            temp = poly->x0;
            poly->x0 = poly->x2 = poly->x1;
            poly->x1 = poly->x3 = temp;
        }
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.gt4++;
        func_800F53D4(tpage, otIdx);
    }
}

// NOTE: used to draw the menu cursor
void MenuDrawRect(MenuContext* ctx, s32 posX, s32 posY, s32 width, s32 height,
                  s32 r, s32 g, s32 b) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    POLY_G4* poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4];
    s32 otIdx = ctx->otIdx + 1;

    setSemiTrans(poly, 0);
    setShadeTex(poly, 0);

    poly->x0 = posX;
    poly->y0 = posY;
    poly->x1 = posX + width;
    poly->y1 = posY;
    poly->x2 = posX;
    poly->y2 = posY + height;
    poly->x3 = posX + width;
    poly->y3 = posY + height;

    if (!ScissorPolyG4(poly, ctx)) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = r;
        poly->g0 = poly->g1 = poly->g2 = poly->g3 = g;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = b;
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.g4++;
        func_800F53D4(0, otIdx);
    }
}

void func_800F5E68(MenuContext* ctx, s32 cursorIdx, s32 x, s32 y, s32 w, s32 h,
                   s32 yGap, s32 bColorMode) {
    s32 r;

    if (bColorMode) {
        if (g_Timer & 0x20) {
            r = 0x60 + (g_Timer & 0x1F);
        } else {
            r = 0x7F - (g_Timer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    MenuDrawRect(ctx, x, y + (cursorIdx * (h + yGap)), w, h, r, 0, 0);
}

void DrawRelicsMenu(MenuContext* ctx) {
    s32 ctx_h;
    s32 switchFadeLevel;
    s32 i;
    s32 spriteX;
    s32 spriteY;
    s32 var_s3;
    s32 u_OnOff;
    u8* relic;

    ctx_h = ctx->h;
    relic = g_Status.relics;

    for (i = 0; i < 30; i++, relic++) {
#define INDEXER i
        spriteX = (i & 1) * 0xB0;
        spriteY = (INDEXER / 2) * 0x13 + 0x22 + ctx_h;
        if (*relic & RELIC_FLAG_FOUND) {
            if (spriteY < 0) {
                continue;
            }
            if (spriteY >= 193) {
                continue;
            }
            if ((i & 2) == 0) {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i / 4 + 0x80), 0x1A1, 6, 1, 0, 0);
            } else {
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C(i / 4 + 0x103), 0x1A1, 7, 1, 0, 0);
            }
        }
        // Determine the U value for the texture to use for the switch
        if (*relic & RELIC_FLAG_ACTIVE) {
            u_OnOff = 0;
        } else {
            u_OnOff = 0x30;
        }
        switchFadeLevel = 0;
        if (INDEXER == g_MenuNavigation.cursorRelic) {
            // This routine handles the fade in/fade out of the ON/OFF switch
            // when hovering
            if (++g_RelicMenuFadeTimer >= 0x48) {
                g_RelicMenuFadeTimer = 0;
            }
            if (g_RelicMenuFadeTimer < 0x24) {
                // Fade up
                switchFadeLevel = g_RelicMenuFadeTimer / 6;
            } else {
                // Fade down
                switchFadeLevel = 6 - ((g_RelicMenuFadeTimer - 0x24) / 6);
            }
        }
        MenuDrawSprite(ctx, spriteX + 8, spriteY, 0x2F, 0xF, u_OnOff, 0x70,
                       switchFadeLevel + 0x1C8, 0x1F,
                       INDEXER == g_MenuNavigation.cursorRelic, 0x40, 0);
    }
    spriteY = (g_MenuNavigation.cursorRelic / 2) * 0x13 + 0x22 + ctx_h;
    MenuDrawRect(ctx, ((g_MenuNavigation.cursorRelic & 1) * 0xB0) + 8,
                 spriteY - 1, 0xA8, 0x12, 0x60, 0, 0);
#undef INDEXER
}

void MenuDrawAlucardPortrait(MenuContext* ctx) {
    MenuDrawSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    MenuDrawSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

// Equivalent of floor(number * .75)
// Cloak color components are 5 bit.
// Examples: 31->23, 15->11
static s32 DarkenCloakColor(s32 color) { return color * 3 / 4; }

// Creates light and dark versions of cloak colors in BGR555 format
void ApplyJosephsCloakPalette(void) {
    const int LiningDark = 0;
    const int LiningLight = 1;
    const int ExteriorDark = 2;
    const int ExteriorLight = 3;

    g_JosephsCloakColors[LiningDark] =
        0x8000 + DarkenCloakColor(g_Settings.cloakColors[3]) +
        (DarkenCloakColor(g_Settings.cloakColors[4]) << 5) +
        (DarkenCloakColor(g_Settings.cloakColors[5]) << 10);
    g_JosephsCloakColors[LiningLight] =
        0x8000 + g_Settings.cloakColors[3] + (g_Settings.cloakColors[4] << 5) +
        (g_Settings.cloakColors[5] << 10);
    g_JosephsCloakColors[ExteriorDark] =
        0x8000 + DarkenCloakColor(g_Settings.cloakColors[0]) +
        (DarkenCloakColor(g_Settings.cloakColors[1]) << 5) +
        (DarkenCloakColor(g_Settings.cloakColors[2]) << 10);
    g_JosephsCloakColors[ExteriorLight] =
        0x8000 + g_Settings.cloakColors[0] + (g_Settings.cloakColors[1] << 5) +
        (g_Settings.cloakColors[2] << 10);
}

void MenuDrawAlucardCloakPreview(MenuContext* ctx) {
    MenuDrawSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    MenuDrawSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_psp_090ECF20(MenuContext* ctx, s32 x, s32 y) {
    s32 yellow;

    if (g_Timer & 0x10) {
        yellow = 0x60 + (g_Timer & 0xF) * 2;
    } else {
        yellow = 0x7F - (g_Timer & 0xF);
    }
    MenuDrawRect(ctx, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* ctx) {
    s32 height;
    s32 r;

    height = ctx->cursorH / 7;
    if (g_Timer & 0x20) {
        r = 0x40 + (g_Timer & 0x1F);
    } else {
        r = 0x5F - (g_Timer & 0x1F);
    }
    MenuDrawRect(ctx, ctx->cursorX,
                 ctx->cursorY + (g_MenuNavigation.cursorMain * height),
                 ctx->cursorW, height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuDialogue, s32 bColorMode) {
    s32 r;
    MenuContext* context = &g_MenuData.menus[menuDialogue];

    if (bColorMode) {
        r = 0x80;
    } else {
        if (g_Timer & 0x20) {
            r = 0x40 + (g_Timer & 0x1F);
        } else {
            r = 0x5F - (g_Timer & 0x1F);
        }
    }
    MenuDrawRect(context, 0x70, g_MenuNavigation.cursorEquip * 13 + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

void func_800F66BC(
    const char* str, s32 x, s32 y, MenuContext* ctx, bool disableTexShade) {
    MenuDrawStr(str, x, y, ctx);
}

void MenuDrawChar(char ch, s32 x, s32 y, MenuContext* ctx) {
    MenuDrawImg(
        ctx, x, y, 8, 8, (ch & 0xF) * 8, (ch & 0xF0) >> 1, 0x196, 0x1E, 1, 0);
}

void MenuDrawStr(const char* str, s32 x, s32 y, MenuContext* ctx) {
    const s32 ChWidth = 8;
    const s32 ChHeight = 8;
    s32 temp;
    s32 xcopy;
    s32 ycopy;
    char ch;

    temp = D_psp_091CE1E0;
    D_80137614 = 0;
    while (true) {
        ch = *str++;
        xcopy = x;
        ycopy = y;
        if (str[0] == 0xC0 && str[1] == 0xD2) {
            D_psp_091CE1E0 = 2;
            str += 2;
        } else {
            D_psp_091CE1E0 = temp;
        }
        if (ch == 0xFF) {
            ch = *str++;
            if (ch == 0) {
                break;
            }
            if (ch != 0xFF) {
                xcopy -= ChWidth;
                ycopy -= ChHeight;
                x -= ChWidth;
            }
        }
        MenuDrawChar(ch, xcopy, ycopy, ctx);
        x += ChWidth;
    }
    D_80137614 = 1;
    func_800F53D4(0x1E, ctx->otIdx + 2);
}

void MenuDrawInt(s32 number, s32 x, s32 y, MenuContext* ctx) {
    const s32 ChWidth = 8;
    do {
        MenuDrawChar((number % 10) + CH('0'), x, y, ctx);
        number /= 10;
        x -= ChWidth;
    } while (number != 0);
}

// Draw a number with a limit of N digits
void MenuDrawTime(s32 number, s32 x, s32 y, MenuContext* ctx, s32 digits) {
    const s32 ChWidth = 8;
    do {
        MenuDrawChar((number % 10) + CH('0'), x, y, ctx);
        number /= 10;
        x -= ChWidth;
        digits--;
    } while (digits != 0);
}

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

u8 g_ChButtons[] = {SQUARE,  CIRCLE,  CROSS,   TRIANGLE,
                    CH('L'), CH('R'), CH('L'), CH(' ')};
u8 g_ChButtons2[] = {CH(' '), CH(' '), CH('+'), CH(' '),
                     CH(' '), CH(' '), CH(' '), CH(' ')};
u8 g_ChButtons3[] = {CH(' '), CH(' '), CH('R'), CH(' '),
                     CH(' '), CH(' '), CH(' '), CH(' ')};

char rgb_en[] = {CH('R'), CH('G'), CH('B')};
char rgb_it[] = {CH('R'), CH('V'), CH('B')};
char rgb_sp[] = {CH('R'), CH('V'), CH('A')};
char rgb_fr[] = {CH('R'), CH('V'), CH('B')};
char rgb_ge[] = {CH('R'), CH('G'), CH('B')};

void MenuJosephsCloakDraw(MenuContext* ctx) {
    s32 i;
    MenuContext* menu;
    s32 row1Ypos;
    s32 row2Ypos;

    menu = &g_MenuData.menus[MENU_DG_SETTINGS];
    g_ChRgb = GetLang(rgb_en, rgb_fr, rgb_sp, rgb_ge, rgb_it);
    for (i = 0, row1Ypos = 0x28; i < 3; i++) {
        MenuDrawStr(g_MenuStr[20], 0xB0, row1Ypos, menu);
        MenuDrawChar(g_ChRgb[i], 0xF8, row1Ypos, menu);
        MenuDrawStr(g_MenuStr[21], 0xB0, row1Ypos + 0x24, menu);
        MenuDrawChar(g_ChRgb[i], 0xF8, row1Ypos + 0x24, menu);
        row1Ypos += 0xC;
    }
    for (i = 0, row2Ypos = 0x28; i < 6; i++) {
        MenuDrawInt(g_Settings.cloakColors[i], 0x120, row2Ypos, menu);
        row2Ypos += 0xC;
    }
    func_800F5E68(
        menu, g_MenuNavigation.cursorCloak, 0xAE, 0x26, 0x80, 0xC, 0, 1);
    ApplyJosephsCloakPalette();
    func_800F6A48();
}

void MenuWindowColorsDraw(MenuContext* ctx) {
    s32 x = 188;
    s32 i;

    g_ChRgb = GetLang(rgb_en, rgb_fr, rgb_sp, rgb_ge, rgb_it);

    for (i = 0; i < 3; i++) {
        s32 y = 80 + i * 12;
        MenuDrawChar(g_ChRgb[i], x + 32, y, ctx);
        MenuDrawInt(g_Settings.windowColors[i], x + 72, y, ctx);
    }
    func_800F5E68(
        ctx, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}

void SortTimeAttackEntries(void) {
    s32 i;
    s32 isLooping;
    s32 swapTime;
    s32 swapName;

    // All the uninitialised time attack timers needs to be set to a large
    // value, so their record can be beat.
    for (i = 0; i < NUM_TIMEATTACK_EVENTS; i++) {
        D_psp_091CDE30[i] = TimeAttackController(i, TIMEATTACK_GET_RECORD);
        if (D_psp_091CDE30[i] == 0) {
            D_psp_091CDE30[i] = 1000000;
        }
        D_psp_091CDDC0[i] = i;
    }

    // Ensure the time attacks are sequentially ordered by their timer
    do {
        isLooping = false;
        for (i = 0; i < NUM_TIMEATTACK_EVENTS - 1; i++) {
            if (D_psp_091CDE30[i] > D_psp_091CDE30[i + 1]) {
                swapTime = D_psp_091CDE30[i];
                D_psp_091CDE30[i] = D_psp_091CDE30[i + 1];
                D_psp_091CDE30[i + 1] = swapTime;
                swapName = D_psp_091CDDC0[i];
                D_psp_091CDDC0[i] = D_psp_091CDDC0[i + 1];
                D_psp_091CDDC0[i + 1] = swapName;
                isLooping++;
            }
        }
    } while (isLooping);
}

void MenuTimeAttackDraw(MenuContext* ctx) {
    s32 i;
    s32 entryIdx;
    s32 seconds;
    s32 cursorX;
    s32 cursorY;

    for (i = 0; i < 12; i++) {
        entryIdx = g_MenuNavigation.cursorTimeAttack + i;
        cursorX = ctx->cursorX + 8;
        cursorY = ctx->cursorY + 8 + i * 12;
        MenuDrawInt(entryIdx + 1, cursorX + 8, cursorY, ctx);
        seconds = D_psp_091CDE30[entryIdx];
        if (seconds == 1000000) {
            MenuDrawStr(g_MenuStr[41], cursorX + 21, cursorY, ctx);
        } else {
            MenuDrawStr(g_MenuStr[53 + D_psp_091CDDC0[entryIdx]], cursorX + 21,
                        cursorY, ctx);
            MenuDrawInt(seconds / 10000, cursorX + 268, cursorY, ctx);
            MenuDrawChar(CH(':'), cursorX + 276, cursorY, ctx);
            MenuDrawTime((seconds / 100) % 100, cursorX + 292, cursorY, ctx, 2);
            MenuDrawChar(CH(':'), cursorX + 300, cursorY, ctx);
            MenuDrawTime(seconds % 100, cursorX + 316, cursorY, ctx, 2);
        }
    }
}

void MenuButtonConfigDraw(MenuContext* ctx) {
    s32 i;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;

    const s32 InitCursorX = 0xA4;
    const s32 W = 0x54;

    s32 cursorX = InitCursorX;

    for (i = 0; i < 7; i++) {
        MenuDrawStr(g_MenuStr[22 + i], cursorX, 0x30 + (i * 0x10), ctx);
        buttonId = g_Settings.buttonConfig[i];
        btn1_x = (buttonId * 12);
        MenuDrawChar(
            g_ChButtons[buttonId], 0xFC + btn1_x, 0x30 + (i * 0x10), ctx);
        if (buttonId >= 4) {
            MenuDrawChar(g_ChButtons2[buttonId - 4], 0x104 + btn1_x,
                         0x30 + (i * 0x10), ctx);
            btn2_x = btn1_x + 8;
            MenuDrawChar(g_ChButtons3[buttonId - 4], 0x104 + btn2_x,
                         0x30 + (i * 0x10), ctx);
        }
    }

    func_800F5E68(
        ctx, g_MenuNavigation.cursorButtons, cursorX - 2, 46, W, 12, 4, 1);
}

void MenuReverseCloakDraw(MenuContext* ctx) {
    const int StrX = 188;
    const int ImgW = 88;

    MenuDrawStr(g_MenuStr[30], StrX, 48, ctx);
    MenuDrawStr(g_MenuStr[31], StrX, 64, ctx);
    func_800F5E68(
        ctx, g_Settings.isCloakLiningReversed, StrX - 2, 46, ImgW, 12, 4, 1);
}

void MenuSoundConfigDraw(MenuContext* ctx) {}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090ED9E0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090EDA78);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090EDB70);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090EDBA0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuStatChangesDraw);

void MenuDrawStats(s32 menuDialogue) {
    MenuContext* ctx;
    s32 buttonCFG;
    s32 x, y;
    s32 i;
    s32 temp_y;
    s32 phi_a0_5;

    ctx = &g_MenuData.menus[menuDialogue];
    func_800F53A4();
    if (menuDialogue == MENU_DG_BG) {
        MenuDrawAlucardPortrait(ctx);
        if (IsAlucart()) {
            MenuDrawStr(g_MenuStr[42], 128, 40, ctx);
        } else {
            MenuDrawStr(g_MenuStr[0], 128, 40, ctx);
        }
        MenuDrawStr(g_MenuStr[12], 96, 56, ctx);
        MenuDrawInt(g_Status.hp, 168, 56, ctx);
        MenuDrawChar(CH('/'), 176, 56, ctx);
        MenuDrawInt(g_Status.hpMax, 208, 56, ctx);
        MenuDrawStr(g_MenuStr[13], 96, 68, ctx);
        MenuDrawInt(g_Status.mp, 168, 68, ctx);
        MenuDrawChar(CH('/'), 176, 68, ctx);
        MenuDrawInt(g_Status.mpMax, 208, 68, ctx);
        MenuDrawStr(g_MenuStr[14], 96, 80, ctx);
        MenuDrawInt(g_Status.hearts, 168, 80, ctx);
        MenuDrawChar(CH('/'), 176, 80, ctx);
        MenuDrawInt(g_Status.heartsMax, 208, 80, ctx);
        MenuDrawStr(g_MenuStr[5], 32, 176, ctx);
        MenuDrawInt(g_Status.exp, 144, 176, ctx);
        MenuDrawStr(g_MenuStr[6], 32, 188, ctx);
        MenuDrawInt(g_Status.level != 99
                        ? g_ExpNext[g_Status.level + 1] - g_Status.exp
                        : 0,
                    144, 188, ctx);
        MenuDrawStr(g_MenuStr[7], 32, 200, ctx);
        MenuDrawInt(g_Status.gold, 144, 200, ctx);
        MenuDrawStr(g_MenuStr[8], 248, 40, ctx);
        MenuDrawInt(g_Status.level, 304, 40, ctx);
        MenuDrawStr(g_MenuStr[15], 248, 56, ctx);
        i = 37;
        if (g_Player.status & PLAYER_STATUS_CURSE) {
            i = 40;
        }
        if (g_Player.status & PLAYER_STATUS_POISON) {
            i = 38;
        }
        if (g_Player.status & PLAYER_STATUS_STONE) {
            i = 39;
        }
        if (IsAlucart()) {
            i = 45;
        }
        MenuDrawStr(g_MenuStr[i], 260, 68, ctx);
        MenuDrawStr(g_MenuStr[10], 252, 150, ctx);
        MenuDrawInt(g_RoomCount, 340, 150, ctx);
        MenuDrawStr(g_MenuStr[11], 252, 164, ctx);
        MenuDrawInt(g_Status.killCount, 340, 164, ctx);
        MenuDrawStr(g_MenuStr[9], 244, 192, ctx);
        MenuDrawInt(g_Status.timerHours, 300, 192, ctx);
        MenuDrawChar(CH(':'), 308, 192, ctx);
        MenuDrawTime(g_Status.timerMinutes, 324, 192, ctx, 2);
        MenuDrawChar(CH(':'), 332, 192, ctx);
        MenuDrawTime(g_Status.timerSeconds, 348, 192, ctx, 2);
    }

    if (ctx == &g_MenuData.menus[MENU_DG_BG]) {
        x = 248;
        y = 88;
    } else {
        x = 232;
        y = 80;
    }
    func_800F66BC(D_800A2D68[0], x, y, ctx, 1);

    buttonCFG = g_Settings.buttonConfig[0];
    if (buttonCFG < 4) {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 44, y, ctx);
    } else if (buttonCFG == 7) {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 40, y, ctx);
        MenuDrawChar(g_ChButtons2[buttonCFG - 4], x + 48, y, ctx);
        MenuDrawChar(g_ChButtons3[buttonCFG - 4], x + 56, y, ctx);
    } else {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 44, y, ctx);
    }
    MenuDrawInt(g_Status.attackHands[0], x + 76, y, ctx);

    buttonCFG = g_Settings.buttonConfig[1];
    if (buttonCFG < 4) {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 44, y + 10, ctx);
    } else if (buttonCFG == 7) {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 40, y + 10, ctx);
        MenuDrawChar(g_ChButtons2[buttonCFG - 4], x + 48, y + 10, ctx);
        MenuDrawChar(g_ChButtons3[buttonCFG - 4], x + 56, y + 10, ctx);
    } else {
        MenuDrawChar(g_ChButtons[buttonCFG], x + 44, y + 10, ctx);
    }

    MenuDrawInt(g_Status.attackHands[1], x + 76, y + 10, ctx);
    func_800F66BC(D_800A2D68[1], x, y + 20, ctx, 1);
    MenuDrawInt(g_Status.defenseEquip, x + 76, y + 26, ctx);
    if (ctx == (&g_MenuData.menus[MENU_DG_BG])) {
        x = 32;
        y = 120;
    } else {
        func_800F66BC(
            D_800A2D68[g_MenuNavigation.cursorEquip + 0x12], 15, 40, ctx, true);
        x = 12;
        y = 70;
    }

    for (i = 0, temp_y = y; i < 4; temp_y += 12, i++) {
        s32* statsBase = g_Status.statsBase;
        MenuDrawStr(g_MenuStr[i + 1], x, temp_y, ctx);
        MenuDrawInt(statsBase[i], x + 44, temp_y, ctx);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                MenuDrawChar(CH('+'), x + 52, temp_y, ctx);
                phi_a0_5 = g_Status.statsEquip[i];
            } else {
                MenuDrawChar(CH('-'), x + 52, temp_y, ctx);
                phi_a0_5 = -g_Status.statsEquip[i];
            }
            MenuDrawInt(phi_a0_5, x + 68, temp_y, ctx);
        }
    }
}

void MenuSpellsDraw(MenuContext* ctx) {
    s32 buttonCFG;
    s32 spell;
    s32 charNum;
    s32 i;
    s32 colorIntensity;
    s32 yCoord;
    s32 v1;

    const s32 startXCoord = 180;
    func_800F66BC(D_800A2D68[2], 136, 36, ctx, 1);

    for (i = 0; i < NUM_SPELLS; i++) {
        spell = g_Status.spells[i];
        if (!(spell & 0x80)) {
            continue;
        }
        spell ^= 0x80;
        charNum = 0;
        yCoord = 64 + i * 16;
        // Count up how many characters are in the combo
        for (v1 = 0; (s8)g_SpellDefs[spell].combo[v1] != 0; v1++) {
            if (g_SpellDefs[spell].combo[v1] == 0xC0 &&
                g_SpellDefs[spell].combo[v1 + 1] == 0xD2) {
                charNum--;
            } else {
                charNum++;
            }
        }

        if (spell != SPELL_WING_SMASH) {
            MenuDrawStr(g_SpellDefs[spell].combo, startXCoord, yCoord, ctx);
            MenuDrawChar(
                CH('+'), startXCoord + ((charNum - 1) * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[0];
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
                if (buttonCFG == 7) {
                    MenuDrawChar(g_ChButtons2[buttonCFG - 4],
                                 startXCoord + (charNum * 8), yCoord, ctx);
                    MenuDrawChar(g_ChButtons3[buttonCFG - 4],
                                 startXCoord + 8 + (charNum * 8), yCoord, ctx);
                    charNum++;
                }
            }
            MenuDrawChar(15, startXCoord + ((charNum + 1) * 8), yCoord, ctx);

            buttonCFG = g_Settings.buttonConfig[1];
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + ((charNum + 2) * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                MenuDrawChar(g_ChButtons2[buttonCFG - 4],
                             startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                MenuDrawChar(
                    g_ChButtons3[buttonCFG - 4],
                    startXCoord + 8 + ((charNum + 2) * 8), yCoord, ctx);
                if (buttonCFG == 7) {
                    MenuDrawChar(
                        g_ChButtons2[buttonCFG - 4],
                        startXCoord + ((charNum + 2) * 8), yCoord, ctx);
                    MenuDrawChar(
                        g_ChButtons3[buttonCFG - 4],
                        startXCoord + 8 + ((charNum + 2) * 8), yCoord, ctx);
                }
            }
        } else {
            MenuDrawChar(CH('?'), startXCoord, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + 8, yCoord, ctx);
            MenuDrawStr(
                g_SpellDefs[spell].combo, startXCoord + 16, yCoord, ctx);
            MenuDrawChar(
                CH('+'), startXCoord + 16 + ((charNum - 1) * 8), yCoord, ctx);
            MenuDrawChar(
                CH('?'), startXCoord + 24 + ((charNum - 1) * 8), yCoord, ctx);
        }
        MenuDrawStr(g_MenuStr[13], 292, yCoord, ctx);
        MenuDrawInt(g_SpellDefs[spell].mpUsage, 316, yCoord, ctx);
    }
    for (i = 0; i < 8; i++) {
        if (g_Status.spells[i] & 0x80) {
            MenuDrawImg(ctx, 0x1C, 0x3C + 0x10 * i, 0xF0, 0x10U, 0,
                        func_800F548C(0x80 + i) & 0xFF, 0x1A1, 6, true, 0);
        }
    }
    // The highlighted spell glows yellow, increasing and decreasing.
    if (g_Timer & 0x20) {
        colorIntensity = 0x60 + (g_Timer & 0x1F);
    } else {
        colorIntensity = 0x7F - (g_Timer & 0x1F);
    }
    // The colorIntensity gets passed to the MenuRect's R and G values, making
    // it a brighter or dimmer yellow.
    MenuDrawRect(ctx, 26, (g_MenuNavigation.cursorSpells * 0x10) + 0x3B, 300,
                 17, colorIntensity, colorIntensity, 0);
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuFamiliarsDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F82F4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuSystemDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F84CC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F86E4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F8754);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuEquipSortDraw);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F892C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F8990);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuDrawLine);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", DrawConsumableCount);

u8 D_800A2D80[] = {0x00, 0x20, 0x30, 0x40, 0x50, 0x60, 0x69, 0x70,
                   0x75, 0x78, 0x7A, 0x7C, 0x7D, 0x7E, 0x7F, 0x80};

void MenuDraw(void) {
    u8 padding[32];
    s32 x, y;
    Primitive* prim;
    Accessory* acc;
    Equipment* equip;
    MenuContext* menu;
    s16 swap;
    s32 cy;
    s32 cx;
    s16 r0, g0, b0;
    s16 r1, g1, b1;
    s32 var_a1;
    s32 cursorXMovement;
    s32 equipIndex;
    s32 cw;
    s32 ch;
    s32 flag;
    s32 i, j;

    for (i = 0; i < NUM_MENU; i++) {
        prim = &g_PrimBuf[D_801377FC[i]];
        menu = &g_MenuData.menus[i];
        if (menu->unk1C == 2) {
            prim->drawMode = DRAW_HIDE;
            continue;
        }
        cx = menu->cursorX;
        cy = menu->cursorY;
        cw = menu->cursorW;
        ch = menu->cursorH;
        var_a1 = menu->unk14 - menu->w;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        if (var_a1 == -1) {
            var_a1 = -2;
        }
        menu->w += var_a1 / 2;

        var_a1 = menu->unk16 - menu->h;
        if (var_a1 == 1) {
            var_a1 = 2;
        }
        if (var_a1 == -1) {
            var_a1 = -2;
        }
        menu->h += var_a1 / 2;

        x = cx + menu->w;
        y = cy + menu->h;

        if (menu->unk1C == 1) {
            menu->unk1D++;
            if (menu->unk1D == 16) {
                menu->unk1C = 2;
                prim->drawMode = DRAW_HIDE;
                continue;
            }
            cy += ch / 16 * menu->unk1D;
            ch -= ch / 16 * menu->unk1D;
            j = 16 - menu->unk1D;

            cursorXMovement = cw / 2 * (128 - D_800A2D80[j]) / 128;
            cx += cursorXMovement;
            cw -= cursorXMovement * 2;
        }
        if (menu->unk1C == 3) {
            menu->unk1D++;
            if (menu->unk1D == 16) {
                menu->unk1C = 0;
            } else {
                cursorXMovement =
                    cw / 2 * (128 - D_800A2D80[menu->unk1D]) / 128;
                cx += cursorXMovement;
                cw -= cursorXMovement * 2;
                j = 16 - menu->unk1D;
                ch -= ch / 16 * j;
            }
        }
        menu->unk1.x = cx;
        menu->unk1.y = cy;
        menu->unk1.w = cw;
        menu->unk1.h = ch;
        SetPrimRect(prim, cx, cy, cw, ch);

        r0 = (s16)(g_Settings.windowColors[0] * 8) - 0x20;
        if (r0 < 0) {
            r0 = 0;
        }
        g0 = (s16)(g_Settings.windowColors[1] * 8) - 0x20;
        if (g0 < 0) {
            g0 = 0;
        }
        b0 = (s16)(g_Settings.windowColors[2] * 8) - 0x20;
        if (b0 < 0) {
            b0 = 0;
        }
        r1 = (s16)(g_Settings.windowColors[0] * 8) + 0x20;
        if (r1 > 0xFF) {
            r1 = 0xFF;
        }
        g1 = (s16)(g_Settings.windowColors[1] * 8) + 0x20;
        if (g1 > 0xFF) {
            g1 = 0xFF;
        }
        b1 = (s16)(g_Settings.windowColors[2] * 8) + 0x20;
        if (b1 > 0xFF) {
            b1 = 0xFF;
        }
        if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_MAD) {
            swap = r0;
            r0 = r1;
            r1 = swap;
            swap = g0;
            g0 = g1;
            g1 = swap;
            swap = b0;
            b0 = b1;
            b1 = swap;
        }
        prim->r0 = r0;
        prim->g0 = g0;
        prim->b0 = b0;

        prim->r1 = r0;
        prim->g1 = g0;
        prim->b1 = b0;

        prim->r2 = r1;
        prim->g2 = g1;
        prim->b2 = b1;

        prim->r3 = r1;
        prim->g3 = g1;
        prim->b3 = b1;
        prim->priority = menu->otIdx;
        prim->drawMode = DRAW_UNK_400 | DRAW_MENU;

        // draw the white window border
        MenuDrawLine(cx, cy, cx, cy + ch - 1, i + 1);
        MenuDrawLine(cx, cy, cx + cw - 1, cy, i + 1);
        MenuDrawLine(cx + cw - 1, cy, cx + cw - 1, cy + ch - 1, i + 1);
        MenuDrawLine(cx, cy + ch - 1, cx + cw - 1, cy + ch - 1, i + 1);

        switch (i) {
        case MENU_DG_MAIN:
            func_800F6568(menu);
            func_800F8754(menu, x, y);
            break;
        case MENU_DG_BG:
            MenuDrawStats(1);
            break;
        case MENU_DG_EQUIP_OVERVIEW:
            MenuDrawStats(2);
            equipIndex = g_Status.equipment[LEFT_HAND_SLOT];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 30, menu);
            DrawConsumableCount(equipIndex, LEFT_HAND_SLOT, menu);
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x10);

            equipIndex = g_Status.equipment[RIGHT_HAND_SLOT];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 43, menu);
            DrawConsumableCount(equipIndex, RIGHT_HAND_SLOT, menu);
            flag = equip->itemCategory == 5;
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x11);

            for (j = 0; j < 5; j++) {
                acc = &g_AccessoryDefs[g_Status.equipment[j + 2]];
                MenuDrawStr(acc->name, 112, 56 + j * 13, menu);
                LoadEquipIcon(acc->icon, acc->iconPalette, j + 0x12);
            }

            for (j = 0; j < 7; j++) {
                // Equivalent (but not matching) with (j==0 || j==1) && flag
                if (!(j != 0 && j != 1) && flag) {
                    if (j == 0) {
                        func_800F892C(j + 0x10, 0x5E, 0x20 + j * 13, menu);
                    }
                } else {
                    func_800F892C(j + 0x10, 0x5E, 0x1a + j * 13, menu);
                }
            }
            func_800F6618(i, g_MenuStep != 0x40);
            break;
        case MENU_DG_EQUIP_SELECTOR:
            func_800F8990(menu, x, y);
            MenuStatChangesDraw();
            break;
        case MENU_DG_INFO_BAR:
            func_800F5AE4(menu);
            break;
        case MENU_DG_RELICS:
            DrawRelicsMenu(menu);
            break;
        case MENU_DG_SPELLS:
            MenuSpellsDraw(menu);
            break;
        case MENU_DG_SETTINGS:
            MenuSystemDraw(menu);
            break;
        case MENU_DG_CLOAK_COLOR:
            MenuDrawAlucardCloakPreview(menu);
            MenuJosephsCloakDraw(menu);
            break;
        case MENU_DG_CFG_BUTTONS:
            MenuButtonConfigDraw(menu);
            break;
        case MENU_DG_CLOAK_LINING:
            MenuReverseCloakDraw(menu);
            break;
        case MENU_DG_CFG_SOUND:
            MenuSoundConfigDraw(menu);
            break;
        case MENU_DG_WINDOW_COLORS:
            MenuWindowColorsDraw(menu);
            break;
        case MENU_DG_TIME_ATTACK:
            MenuTimeAttackDraw(menu);
            break;
        case MENU_DG_EQUIP_SORT:
            MenuEquipSortDraw(menu);
            break;
        case MENU_DG_FAMILIARS:
            MenuFamiliarsDraw(menu);
            break;
        case MENU_PSP_EXTRA_1:
        case MENU_PSP_EXTRA_3:
            func_psp_090ED9E0(menu);
            break;
        case MENU_PSP_EXTRA_2:
            func_psp_090EDA78(menu);
            break;
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F9690);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F96F4);

static void func_800F97DC(void) {
    D_8013794C = g_Pix[0];
    D_80137950 = 0x180;
    D_80137954 = 0;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F9808);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800F98AC);

void func_800F99B8(const char* str, s32 arg1, bool arg2) {
    // See src/st/blit_char.h
    const u16 DOUBLE_SPACE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    char sp5f;
    s32 sp54;
    s32 sp50;
    s32 sp4c;
    s32 sp48;
    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s2;
    s32 var_s1;
    s32 var_s0;
    s32 i;
    s32 j;
    u8* dest_addr;

    if (arg2) {
        var_s0 = 0x3C;
    } else {
        var_s0 = 0x90;
    }
    for (i = 0, sp4c = var_s0 * FontHeight; i < sp4c; i++) {
        D_8013794C[i] = 0;
    }
    var_s1 = 0;
    sp50 = 0;
    if (arg1 & 0x100) {
        sp50 = 0x40;
    }
    if (arg1 & 0x200) {
        sp50 += 0x20;
        arg1 &= ~0x200;
    }
    sp48 = func_800F548C(arg1 & 0xFF) & 0xFF;
    while (*str != 0) {
        sp54 = 0;
        var_a0 = func_psp_0913F960(str, &sp5f);
        var_s2 = *str++;
        if ('a' <= var_s2 && var_s2 <= 'z') {
            var_a0 = var_s2 + 0x8220;
        } else if ('A' <= var_s2 && var_s2 <= 'Z') {
            var_a0 = var_s2 + 0x821F;
        } else if (var_s2 == ' ') {
            var_a0 = DOUBLE_SPACE;
            sp54 = 2;
        } else {
            sp54 = sp5f;
            if (sp5f > 1) {
                str += (sp5f - 1);
            }
            if (var_a0 == DOUBLE_SPACE) {
                var_s2 = ' ';
            }
        }
        // var_a2 = (u8*)func_80106A28(var_a0, 0);
        var_a2 = (u8*)func_psp_0913FA28(var_a0, 0);
        while (1) {
            if (var_s2 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontWidth / 2] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontWidth / 2];
                // Effectively shift everything down an index
                for (j = 0; j < 5; j++) {
                    dest_addr[0] = dest_addr[1];
                    dest_addr += 1;
                }
                // Set last index to 0
                *dest_addr = 0;
            }
        }
        for (i = 0, var_a3 = 0; i < FontHeight; i++) {
            for (j = 0; j < FontWidth / 2; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontWidth / 2 + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (var_a2[i * FontWidth / 2 + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontWidth / 2) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_8013794C[(i * var_s0) + var_s1];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s1 += var_a3 + sp54;
        if (var_s1 >= var_s0) {
            break;
        }
    }

    LoadTPage((u_long*)D_8013794C, 0, 0, D_80137950 + sp50, D_80137954 + sp48,
              var_s0 * 2, 0x10);
    D_8013794C += sp4c;
}

void func_800F9D88(const char* str, s32 arg1, bool arg2) {
    if (arg2) {
        D_8013794C = g_Pix[2];
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(str, arg1, false);
}

void func_800F9DD0(const char* src, char* dst) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*src == 0)
            break;
        *dst++ = *src++;
        *dst++ = *src++;
    }
}

void func_800F9E18(s32 arg0) {
    char buffer[38];
    const int ItemsPerRow = 2;
    s32 i = arg0 * 5;
    s32 nHalfScreenSize;
    s32 nItems = i + 5;

    static RECT D_800A2D90 = {0x180, 0x30, 0x80, 0x80};

    if (arg0 == 0) {
        ClearImage(&D_800A2D90, 0, 0, 0);
        DrawSync(0);
    }

    D_psp_0914A388[3] = GetLang(
        NULL, D_psp_0914A0D0, D_psp_09149E90, D_psp_0914A248, D_psp_09149FB0);
    if (D_psp_0914A388[3] != NULL) {
        func_psp_091040A0(D_psp_0914A388);
    }

    for (nHalfScreenSize = i; i < nItems; i++, nHalfScreenSize++) {
        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 128, true);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 259, true);
        }

        STRCPY(buffer, g_RelicDefs[i * ItemsPerRow + 1].name);
        if ((nHalfScreenSize & 1) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 640, true);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 771, true);
        }
    }
}

#define ShowText(str, id) func_800F99B8(str, id, false);

void func_800F9F40(void) {
    char buffer[38];
    u8 spellId;
    s32 i;

    for (i = 0; i < NUM_SPELLS; i++) {
        spellId = g_Status.spells[i];
        if (spellId & 0x80) {
            spellId ^= 0x80;
            STRCPY(buffer, "　　　　　　　　　　　　　　　　　　　　　");
            func_800F9DD0(g_SpellDefs[spellId].name, buffer);
            ShowText(buffer, 0x80 + i);
        }
    }
}

void MenuHandleCursorInput(s32* nav, u8 nOptions, u32 arg2);
INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuHandleCursorInput);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F1418);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuEquipHandlePageScroll);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", CheckWeaponCombo);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F18B0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F1968);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", InitWeapon);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAB1C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuHide);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", MenuShow);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FABEC);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAC0C);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAC30);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAC48);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F1CE0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F1CE8);

void func_800FAD34(const char* str, u8 count, u16 equipIcon, u16 palette);
INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAD34);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FADC0);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F1EA0);

void func_800FAEC4(
    s32* cursor_unused, u16 count, const char* str, u16 icon, u16 pal);
INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAEC4);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FAF44);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FB004);

EquipMenuHelper g_EquipMenuHelper[] = {
    {EQUIP_HAND, 0, false},     // LEFT_HAND_SLOT
    {EQUIP_HAND, 0, false},     // RIGHT_HAND_SLOT
    {EQUIP_HEAD, 0, true},      // HEAD_SLOT
    {EQUIP_ARMOR, 1, true},     // ARMOR_SLOT
    {EQUIP_CAPE, 2, true},      // CAPE_SLOT
    {EQUIP_ACCESSORY, 3, true}, // ACCESSORY_1_SLOT
    {EQUIP_ACCESSORY, 3, true}, // ACCESSORY_2_SLOT
};

void func_800FB0FC(void) {
    EquipMenuHelper* helper = &g_EquipMenuHelper[g_MenuNavigation.cursorEquip];
    D_801375CC = helper->equipTypeFilter;
    D_801375D4 = helper->index;
    func_800FAF44(helper->isAccessory);
    func_800FB004();
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F2178);

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_psp_090F21F8);

s32 D_800A2DEC[] = {
    0x1A, 0x00, 0x30, 0x39, 0x39,
};

extern bool func_800FB1EC(u16 arg0);
extern u32 D_801375D0;
extern s32* D_801375D8;
extern s32 D_80137844[1];
extern s32 D_80137848[1];
extern s32 D_80137948;
extern s32 g_IsSelectingEquipment;
extern s32 g_EquipmentCursor;

extern u32 D_psp_08B42050; // psp cross button
extern u32 D_psp_08B42054; // psp triangle button

#define PAD_MENU_SELECT_ALT (D_psp_08B42050)
#define PAD_MENU_SELECT (PAD_MENU_SELECT_ALT | PAD_SQUARE)
#define PAD_MENU_BACK (D_psp_08B42054)
#define PAD_MENU_SORT (PAD_TRIANGLE)
#define PAD_MENU_BACK_ALT (PAD_MENU_BACK | PAD_MENU_SELECT)

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FB23C);

MenuContextInit g_MenuInit[NUM_MENU] = {
    {142, 100, 84, 112, 0x40}, // MENU_DG_MAIN
    {0, 24, 360, 200, 0x10},   // MENU_DG_BG
    {0, 24, 360, 97, 0x20},    // MENU_DG_EQUIP_OVERVIEW
    {0, 120, 360, 74, 0x20},   // MENU_DG_EQUIP_SELECTOR
    {0, 193, 360, 31, 0x40},   // MENU_DG_INFO_BAR
    {0, 24, 360, 170, 0x20},   // MENU_DG_RELICS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SPELLS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SETTINGS
    {168, 120, 144, 64, 0x30}, // MENU_DG_CLOAK_COLOR
    {148, 44, 200, 112, 0x30}, // MENU_DG_CFG_BUTTONS
    {172, 44, 89, 32, 0x30},   // MENU_DG_CLOAK_LINING 6db90
    {172, 112, 57, 32, 0x30},  // MENU_DG_CFG_SOUND
    {172, 76, 124, 40, 0x30},  // MENU_DG_WINDOW_COLORS
    {12, 32, 340, 153, 0x30},  // MENU_DG_TIME_ATTACK
    {276, 32, 77, 183, 0x50},  // MENU_DG_EQUIP_SORT
    {0, 24, 360, 200, 0x18},   // MENU_DG_FAMILIARS
    {240, 180, 65, 32, 0x50},  // MENU_PSP_EXTRA_1
    {128, 100, 88, 48, 0x1FB}, // MENU_PSP_EXTRA_2
    {176, 180, 65, 32, 0x1FB}, // MENU_PSP_EXTRA_3
};

void func_800FB9BC(void) {
    const int ItemsPerRow = 2;

    const int VertScrollWindow = 140;
    const int YScrollPerElement = 15;

    s32 i;
    MenuContext* context;

    context = g_MenuData.menus;
    for (i = 0; i < NUM_MENU; i++, context++) {
        context->cursorX = context->unk1.x = g_MenuInit[i].cursorX;
        context->cursorX += 12;
        context->cursorY = context->unk1.y = g_MenuInit[i].cursorY;
        context->cursorW = context->unk1.w = g_MenuInit[i].cursorW;
        context->cursorH = context->unk1.h = g_MenuInit[i].cursorH;
        context->unk14 = 0;
        context->w = 0;
        context->unk16 = 0;
        context->h = 0;
        context->otIdx = g_MenuInit[i].otIdx;
        context->unk1C = 2;
    }
    g_MenuData.menus[MENU_DG_RELICS].h =
        g_MenuData.menus[MENU_DG_RELICS].unk16 =
            ((g_MenuNavigation.cursorRelic / ItemsPerRow) * -VertScrollWindow) /
            YScrollPerElement;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", func_800FBAC4);

extern s32 D_80137614;
extern s32 g_ServantPrevious;
extern s32 D_801375DC;
extern s32 D_801375E0[NUM_FAMILIARS + 1];
extern s32 g_IsCloakLiningUnlocked;
extern s32 g_IsCloakColorUnlocked;
extern s32 D_80137958;
extern const char* D_800A2D64[];
extern s32 D_80137608;
extern s32 g_EquipOrderType;
extern bool D_psp_091CDD48;
extern s32 g_UserLanguage;
extern s32 D_psp_091CDD40;

extern s32 D_8013784C;

extern const char* D_800A2D10[];
extern const char* D_800A2D14[];
extern const char* D_800A2D18[];
extern const char* D_800A2D58[];

void MenuHandle(void) {
    s32 temp_s1;
    s32 i;
    s32 id;
    s32 var_s1;
    u8 equipId;
    s32 isSecondAccessory;
    char* buttonAssignStr;

    D_80137614 = 1;
    func_800F97DC();
    if (g_MenuStep >= MENU_STEP_OPENED && g_pads[0].tapped & PAD_START) {
        if (CheckIfAllButtonsAreAssigned()) {
            g_MenuStep = MENU_STEP_EXIT_BEGIN;
        } else {
            goto block_117;
        }
    }
block_4:
    switch (g_MenuStep) {
    case MENU_STEP_INIT:
        if (!CdSoundCommandQueueEmpty()) {
            break;
        }
        func_psp_090EAFA8();
        PlaySfx(SET_UNK_10);
        func_800EA5E4(0);
        func_800FAC30();
        func_800FB9BC();
        g_PrevEquippedWeapons[LEFT_HAND_SLOT] =
            g_Status.equipment[LEFT_HAND_SLOT];
        g_PrevEquippedWeapons[RIGHT_HAND_SLOT] =
            g_Status.equipment[RIGHT_HAND_SLOT];
        if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
            g_PrevEquippedWeapons[LEFT_HAND_SLOT] = 0xD8;
            g_PrevEquippedWeapons[RIGHT_HAND_SLOT] = 0xD8;
        }
        g_ServantPrevious = g_Servant;
        for (i = 0; i < NUM_SPELLS; i++) {
            if (!(g_Status.spells[i] & SPELL_FLAG_KNOWN)) {
                break;
            }
        }
        D_801375DC = i;
        for (i = 0; i < LEN(D_801375E0); i++) {
            D_801375E0[i] = 0;
        }
        for (i = 0; i < NUM_RELICS; i++) {
            if (!(g_Status.relics[i] & RELIC_FLAG_FOUND)) {
                continue;
            }
            if (g_RelicDefs[i].unk0C == 0) {
                continue;
            }
            D_801375E0[g_RelicDefs[i].unk0C - 1] = 1;
            D_801375E0[NUM_FAMILIARS] = 1;
        }
        g_IsCloakLiningUnlocked =
            g_Status.equipBodyCount[ITEM_REVERSE_CLOAK] |
            g_Status.equipment[CAPE_SLOT] == ITEM_REVERSE_CLOAK;
        g_IsCloakColorUnlocked =
            g_Status.equipBodyCount[ITEM_JOSEPHS_CLOAK] |
            g_Status.equipment[CAPE_SLOT] == ITEM_JOSEPHS_CLOAK;
        g_MenuStep++;
        break;
    case MENU_STEP_FADE_FROM_GAME:
        if (func_801025F4() == 0) {
            break;
        }
        SetGPUBuffRGBZero();
        func_80102628(0x180);
        SetMenuDisplayBuffer();
        func_800FAC48();
        D_800973EC = 1;
        g_MenuStep++;
        break;
    case MENU_STEP_OPENING:
        if (func_80133950()) {
            D_80137958 = D_80097910;
            D_80097910 = 0;
            func_800F6A48();
            func_800F84CC();
            func_801027C4(2);
            func_800F98AC(*D_800A2D10, 0);
            func_800F98AC(*D_800A2D14, 0x100);
            func_800F98AC(*D_800A2D18, 1);
            func_800F98AC(*D_800A2D58, 0x101);
            func_800FABEC(MENU_DG_MAIN);
            func_800FABEC(MENU_DG_BG);
            D_80137608 = 0;
            g_IsSelectingEquipment = 0;
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_EXIT_BEGIN:
        func_801027C4(1);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_4:
        if (func_801025F4()) {
            func_80102628(0x100);
            SetStageDisplayBuffer();
            func_800FAC48();
            func_800EB6B4();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_5:
        UpdateCapePalette();
        LoadGfxAsync(D_80097904);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_6:
        if (func_800EB720()) {
            break;
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_7:
        if (!func_psp_090F1968(LEFT_HAND_SLOT)) {
            break;
        }
        if (!g_UseDisk) {
            InitWeapon(LEFT_HAND_SLOT);
        }
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            InitWeapon(LEFT_HAND_SLOT);
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_8:
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_9:
        if (!func_psp_090F1968(RIGHT_HAND_SLOT)) {
            break;
        }
        if (!g_UseDisk) {
            InitWeapon(RIGHT_HAND_SLOT);
        }
        if (g_UseDisk) {
            if (g_IsUsingCd) {
                break;
            }
            InitWeapon(RIGHT_HAND_SLOT);
        }
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_10:
        if (g_Servant == FAM_ACTIVE_NONE || g_Servant != g_ServantPrevious) {
            func_800FAB1C();
        }
        if (g_Servant == FAM_ACTIVE_NONE || g_Servant == g_ServantLoaded) {
            if (g_Servant != FAM_ACTIVE_NONE) {
                if (g_Servant != g_ServantPrevious) {
                    if (g_Status.statsFamiliars[g_Servant - 1].unk8 < 9999) {
                        g_Status.statsFamiliars[g_Servant - 1].unk8++;
                    }
                    InitializeServant(MENU_SWITCH_SERVANT);
                } else {
                    InitializeServant(MENU_SAME_SERVANT);
                }
            }
            g_MenuStep += 2;
        } else {
            if (g_UseDisk) {
                g_CdStep = CdStep_LoadInit;
                g_LoadFile = CdFile_ServantChr;
                g_LoadOvlIdx = g_Servant - 1;
            }
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_11:
        if (func_8932EA4()) {
            if (g_UseDisk) {
                if (g_IsUsingCd) {
                    break;
                }
            } else {
                func_800E6250();
            }
            InitializeServant(MENU_SWITCH_SERVANT);
            g_ServantLoaded = g_Servant;
            if (g_Status.statsFamiliars[g_Servant - 1].unk8 < 9999) {
                g_Status.statsFamiliars[g_Servant - 1].unk8++;
            }
            g_MenuStep++;
        }
        break;
    case MENU_STEP_EXIT_12:
        if (g_IsUsingCd) {
            break;
        }
        if (CdSoundCommandQueueEmpty() == false) {
            break;
        }
        D_80097910 = D_80137958;
        if (D_psp_091CDD48 != 0) {
            PlaySfx(0xB);
        } else {
            PlaySfx(SET_UNK_11);
        }
        CheckWeaponCombo();
        func_800F53A4();
        D_800973EC = 0;
        func_800FAC30();
        func_800F86E4();
        func_8010A234(1);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_13:
        if (func_80133950() == false) {
            break;
        }
        func_801027C4(2);
        g_MenuStep++;
        if (D_psp_091CDD48) {
            D_psp_091CDD48 = 0;
            SetGameState(3);
            g_GameStep = 0x63;
        }
        break;
    case MENU_STEP_RETURN_TO_GAMEPLAY:
        if (func_801025F4() == 0) {
            break;
        }
        PlaySfx(SET_UNPAUSE_SFX_SCRIPTS);
        PlaySfx(SET_KEY_ON_20_21);
        PlaySfx(SET_KEY_ON_22_23);
        g_GameEngineStep = Engine_Normal;
        break;
    case MENU_STEP_OPENED:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            g_MenuStep = MENU_STEP_EXIT_BEGIN;
            goto block_4;
        }
        MenuHandleCursorInput(&g_MenuNavigation.cursorMain, 7, 0);
        if (g_pads[0].tapped & PAD_MENU_SELECT) {
            switch (g_MenuNavigation.cursorMain) {
            case 0:
                MenuShow(MENU_DG_EQUIP_OVERVIEW);
                func_800FB0FC();
                func_800FADC0();
                MenuShow(MENU_DG_EQUIP_SELECTOR);
                MenuShow(MENU_DG_INFO_BAR);
                g_MenuStep = MENU_STEP_EQUIP;
                break;
            case 1:
                if (D_801375DC) {
                    g_MenuStep = MENU_STEP_SPELL_INIT;
                }
                break;
            case 2:
                func_800F9E18(0);
                g_MenuStep = MENU_STEP_RELIC_INIT;
                break;
            case 3:
                g_MenuStep = MENU_STEP_SYSTEM_INIT;
                break;
            case 4:
                if (D_801375E0[NUM_FAMILIARS]) {
                    g_MenuStep = MENU_STEP_FAMILIAR_INIT;
                }
                break;
            case 5:
                if (D_8006C378 < 0) {
                    break;
                }
                MenuShow(0x10);
                D_psp_091CDD40 = 1;
                g_MenuStep = 0x80;
                break;
            case 6:
                MenuShow(0x10);
                D_psp_091CDD40 = 1;
                g_MenuStep = 0x90;
                break;
            }
            if (!(g_MenuStep == MENU_STEP_OPENED || g_MenuStep == 0x80 ||
                  g_MenuStep == 0x90)) {
                MenuHide(MENU_DG_MAIN);
                MenuHide(MENU_DG_BG);
                PlaySfx(SFX_UI_CONFIRM);
            } else {
                if (g_MenuStep == 0x80 || g_MenuStep == 0x90) {
                    PlaySfx(SFX_UI_CONFIRM);
                } else {
                    PlaySfx(SFX_UI_ERROR);
                }
            }
        }
        break;
    case 0x80:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            PlaySfx(SFX_UI_ERROR);
            MenuHide(0x10);
            g_MenuStep = 0x10;
            break;
        }
        MenuHandleCursorInput(&D_psp_091CDD40, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_SELECT)) {
            break;
        }
        if (D_psp_091CDD40 == 0) {
            PlaySfx(SFX_UI_CONFIRM);
            func_psp_090DFC80();
            MenuHide(0x10);
            D_psp_091CDD48 = 1;
            g_MenuStep = 3;
            goto block_4;
        }
        PlaySfx(SFX_UI_ERROR);
        MenuHide(0x10);
        g_MenuStep = 0x10;
        break;
    case 0x90:
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            PlaySfx(SFX_UI_ERROR);
            MenuHide(0x10);
            g_MenuStep = 0x10;
            break;
        }
        MenuHandleCursorInput(&D_psp_091CDD40, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_SELECT)) {
            break;
        }
        if (D_psp_091CDD40 == 0) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(0x10);
            D_psp_091CDD48 = 1;
            g_MenuStep = 3;
            goto block_4;
        }
        PlaySfx(SFX_UI_ERROR);
        MenuHide(0x10);
        g_MenuStep = 0x10;
        break;
    case MENU_STEP_FAMILIAR_INIT:
        func_800EA5E4(0x21);
        func_800EAEA4();
        MenuShow(MENU_DG_FAMILIARS);
        g_MenuStep++;
        break;
    case MENU_STEP_FAMILIAR:
        if (g_pads[0].tapped & (PAD_MENU_SELECT | PAD_MENU_BACK)) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            func_800EAEA4();
            MenuHide(MENU_DG_FAMILIARS);
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_SYSTEM_INIT:
        func_800F82F4();
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_SETTINGS);
        g_MenuStep++;
    case MENU_STEP_SYSTEM:
        MenuHandleCursorInput(&g_MenuNavigation.cursorSettings, 5, 0);
        DrawSync(0);
        func_800F9808(2);
        i = g_MenuNavigation.cursorSettings + 1;
        if (i == 2 && g_IsCloakLiningUnlocked == false) {
            i = 0;
        }
        if (i == 3 && g_IsCloakColorUnlocked == false) {
            i = 0;
        }
        if (i == 5 && g_IsTimeAttackUnlocked == false) {
            i = 0;
        }
        ShowText(D_800A2D48[i], 2);
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_SETTINGS);
            g_MenuStep = MENU_STEP_OPENED;
        } else if (g_pads[0].tapped & PAD_MENU_SELECT) {
            switch (g_MenuNavigation.cursorSettings) {
            case 0:
                MenuShow(MENU_DG_CFG_BUTTONS);
                g_MenuStep = MENU_STEP_SYSTEM_BUTTONS;
                break;
            case 1:
                if (g_IsCloakLiningUnlocked) {
                    MenuShow(MENU_DG_CLOAK_LINING);
                    g_MenuStep = MENU_STEP_SYSTEM_CLOAK_LINING;
                }
                break;
            case 2:
                if (g_IsCloakColorUnlocked) {
                    func_800FABEC(MENU_DG_CLOAK_COLOR);
                    g_MenuStep = MENU_STEP_SYSTEM_CLOAK_COLOR;
                }
                break;
            case 3:
                MenuShow(MENU_DG_WINDOW_COLORS);
                g_MenuStep = MENU_STEP_SYSTEM_WINDOW_COLOR;
                break;
            case 4:
                if (g_IsTimeAttackUnlocked) {
                    SortTimeAttackEntries();
                    MenuShow(MENU_DG_TIME_ATTACK);
                    g_MenuStep = MENU_STEP_SYSTEM_TIME_ATTACK;
                }
            }

            if (g_MenuStep != MENU_STEP_SYSTEM) {
                PlaySfx(SFX_UI_CONFIRM);
            } else {
                PlaySfx(SFX_UI_ERROR);
            }
        }
        break;
    case MENU_STEP_SYSTEM_BUTTONS:
        MenuHandleCursorInput(&g_MenuNavigation.cursorButtons, 6, 0);
        MenuHandleCursorInput(
            &g_Settings.buttonConfig[g_MenuNavigation.cursorButtons], 6, 5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            if (CheckIfAllButtonsAreAssigned()) {
                PlaySfx(SFX_UI_CONFIRM);
                MenuHide(MENU_DG_CFG_BUTTONS);
                g_MenuStep = MENU_STEP_SYSTEM;
            } else {
            block_117:
                func_800F9808(2);
                switch (g_UserLanguage) {
                default:
                case LANG_EN:
                    buttonAssignStr = "Allocate all button functions";
                    break;
                case LANG_FR:
                    buttonAssignStr = "Attr. toutes les fonctions des touches";
                    break;
                case LANG_SP:
                    buttonAssignStr = "Asigna las funciones de los botones";
                    break;
                case LANG_GE:
                    buttonAssignStr = "Standard-Tastenbelegung";
                    break;
                case LANG_IT:
                    buttonAssignStr = "Assegna tutte le funzioni tasto";
                    break;
                }
                ShowText(buttonAssignStr, 2);
                PlaySfx(SFX_UI_ERROR);
            }
        }
        break;
    case MENU_STEP_SYSTEM_CLOAK_LINING:
        MenuHandleCursorInput(&g_Settings.isCloakLiningReversed, 2, 0);
        if (!(g_pads[0].tapped & PAD_MENU_BACK_ALT)) {
            break;
        }
        PlaySfx(SFX_UI_CONFIRM);
        MenuHide(MENU_DG_CLOAK_LINING);
        g_MenuStep = MENU_STEP_SYSTEM;
        break;
    case MENU_STEP_SYSTEM_CLOAK_COLOR:
        MenuHandleCursorInput(&g_MenuNavigation.cursorCloak, 6, 0);
        MenuHandleCursorInput(
            &g_Settings.cloakColors[g_MenuNavigation.cursorCloak], 32, 5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            func_800FAC0C(MENU_DG_CLOAK_COLOR);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_WINDOW_COLOR:
        MenuHandleCursorInput(&g_MenuNavigation.cursorWindowColors, 3, 0);
        MenuHandleCursorInput(
            &g_Settings.windowColors[g_MenuNavigation.cursorWindowColors], 16,
            5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_WINDOW_COLORS);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_SOUND:
        MenuHandleCursorInput(&g_Settings.isSoundMono, 2, 0);
        func_800E493C();
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_CFG_SOUND);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_SYSTEM_TIME_ATTACK:
        MenuHandleCursorInput(&g_MenuNavigation.cursorTimeAttack, 0x10, 3);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuHide(MENU_DG_TIME_ATTACK);
            g_MenuStep = MENU_STEP_SYSTEM;
        }
        break;
    case MENU_STEP_RELIC_INIT:
        func_800F9E18(1);
        g_MenuStep++;
        break;
    case MENU_STEP_RELIC_INIT_2:
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_RELICS);
        func_800F9808(2);
        id = g_MenuNavigation.cursorRelic;
        if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
            ShowText(g_RelicDefs[id].desc, 2);
        }
        func_800F9E18(2);
        g_MenuStep++;
        break;
    case MENU_STEP_RELIC:
        g_MenuData.menus[5].unk16 =
            ((g_MenuNavigation.cursorRelic / 2) * -140) / 15;
        var_s1 = g_MenuNavigation.cursorRelic;
        MenuHandleCursorInput(
            &g_MenuNavigation.cursorRelic, NUM_AVAIL_RELICS, 1);
        id = g_MenuNavigation.cursorRelic;
        if (g_pads[0].tapped & PAD_MENU_SELECT &&
            g_Status.relics[id] & RELIC_FLAG_FOUND) {
            PlaySfx(SFX_UI_CONFIRM);
            g_Status.relics[id] = g_Status.relics[id] ^ 2;
            if (g_RelicDefs[id].unk0C > 0) {
                for (i = 0; i < NUM_RELICS; i++) {
                    if (i == id) {
                        continue;
                    }
                    if (g_RelicDefs[i].unk0C <= 0) {
                        continue;
                    }
                    g_Status.relics[i] &= ~RELIC_FLAG_ACTIVE;
                }

                if (g_Status.relics[id] & RELIC_FLAG_ACTIVE) {
                    i = ITEM_SWORD_FAMILIAR;
                    g_Servant = g_RelicDefs[id].unk0C;
                    func_8932E78(g_Servant - 1);
                    if (g_Servant == FAM_ACTIVE_SWORD) {
                        if (g_Status.equipment[LEFT_HAND_SLOT] == i) {
                            g_Status.equipment[LEFT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(i, 0);
                        }
                        if (g_Status.equipment[RIGHT_HAND_SLOT] == i) {
                            g_Status.equipment[RIGHT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(i, 0);
                        }
                    }
                } else {
                    g_Servant = FAM_ACTIVE_NONE;
                }
            }
        }
        if (var_s1 != id) {
            func_800F9808(2);
            if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
                ShowText(g_RelicDefs[id].desc, 2);
            }
        }

        D_80137608 = 0;
        if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
            D_80137608 = 1;
            LoadEquipIcon(g_RelicDefs[id].unk08, g_RelicDefs[id].unk0A, 0x1F);
        }
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_RELICS);
            D_80137608 = 0;
            g_MenuStep = MENU_STEP_OPENED;
        }

        break;
    case MENU_STEP_SPELL_INIT:
        MenuShow(MENU_DG_INFO_BAR);
        MenuShow(MENU_DG_SPELLS);
        func_800F9808(2);
        func_800F9F40();
        g_MenuStep++;
        break;
    case MENU_STEP_SPELL:
        temp_s1 = g_MenuNavigation.cursorSpells;
        MenuHandleCursorInput(&g_MenuNavigation.cursorSpells, D_801375DC, 3);
        if (1) {
            func_800F9808(2);
            id = g_Status.spells[g_MenuNavigation.cursorSpells];
            id ^= SPELL_FLAG_KNOWN;
            ShowText(g_SpellDefs[id].description, 2);
        }
        if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            MenuHide(MENU_DG_INFO_BAR);
            MenuHide(MENU_DG_SPELLS);
            g_MenuStep = MENU_STEP_OPENED;
        }
        break;
    case MENU_STEP_UNK_32:
        if (func_801025F4()) {
            func_80102628(0x100);
            SetStageDisplayBuffer();
            func_800FAC48();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_33:
        if (!g_IsUsingCd) {
            g_GpuBuffers[1].draw.isbg = 0;
            g_GpuBuffers[0].draw.isbg = 0;
            func_801083BC();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_34:
        func_800F5A90();
        g_MenuStep++;
        break;
    case MENU_STEP_UNK_35:
        func_800F5A90();
        if (g_pads[0].tapped & (PAD_MENU_SELECT | PAD_MENU_BACK)) {
            func_801073C0();
            g_CdStep = CdStep_None;
            SetGPUBuffRGBZero();
            func_80102628(0x180);
            SetMenuDisplayBuffer();
            func_800FAC48();
            g_MenuStep++;
        }
        break;
    case MENU_STEP_UNK_36:
        func_801027C4(2);
        func_800F9808(2);
        id = g_Status.spells[g_MenuNavigation.cursorSpells];
        id ^= SPELL_FLAG_KNOWN;
        ShowText(g_SpellDefs[id].description, 2);
        func_800F9F40();
        g_MenuStep++;
        break;
    case MENU_STEP_UNK_37:
        if (func_801025F4() == 0) {
            break;
        }
        g_MenuStep = MENU_STEP_SPELL;
        break;
    case MENU_STEP_EQUIP:
        D_80137948 = 0;
        func_800FB0FC();
        var_s1 = g_MenuNavigation.cursorEquip;
        MenuHandleCursorInput(&g_MenuNavigation.cursorEquip, NUM_ITEM_SLOTS, 0);
        MenuEquipHandlePageScroll(1);
        func_800FB0FC();
        if (var_s1 != g_MenuNavigation.cursorEquip) {
            func_800FADC0();
        }
        if (g_pads[0].tapped & PAD_MENU_SORT && D_801375CC == 0) {
            PlaySfx(SFX_UI_CONFIRM);
            MenuShow(MENU_DG_EQUIP_SORT);
            g_MenuStep = MENU_STEP_EQUIP_SORT;
            g_EquipOrderType = 0;
        } else if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuHide(MENU_DG_EQUIP_OVERVIEW);
            MenuHide(MENU_DG_EQUIP_SELECTOR);
            MenuHide(MENU_DG_INFO_BAR);
            MenuShow(MENU_DG_MAIN);
            MenuShow(MENU_DG_BG);
            *D_80137844 = 0;
            *D_80137848 = 0;
            D_80137608 = 0;
            g_MenuStep = MENU_STEP_OPENED;
        } else if (g_pads[0].tapped & PAD_MENU_SELECT) {
            PlaySfx(SFX_UI_CONFIRM);
        block_191:
            func_800FB0FC();
            if (g_MenuNavigation.cursorEquip < HEAD_SLOT) {
                g_MenuStep = MENU_STEP_EQUIP_HAND_INIT;
            } else {
                g_MenuStep = MENU_STEP_EQUIP_ACC_INIT;
            }
        }
        break;
    case MENU_STEP_EQUIP_SORT:
        func_800FB0FC();
        MenuHandleCursorInput(&g_EquipOrderType, 11, 0);
        MenuEquipHandlePageScroll(0);
        if (g_pads[0].tapped & PAD_MENU_SELECT_ALT) {
            PlaySfx(SFX_UI_CONFIRM);
            func_800FBAC4();
            g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 = 0;
            g_MenuNavigation.cursorEquipType[0] = 0;
            func_800FB0FC();
        } else if (g_pads[0].tapped & PAD_MENU_BACK) {
            MenuHide(MENU_DG_EQUIP_SORT);
            g_MenuStep = MENU_STEP_EQUIP;
        }
        break;
    case MENU_STEP_EQUIP_HAND_INIT:
        equipId = g_Status.equipHandOrder[g_MenuNavigation.cursorEquipType[0]];
        func_800FAEC4(
            &g_MenuNavigation.cursorEquipType[0],
            g_Status.equipHandCount[equipId], g_EquipDefs[equipId].description,
            g_EquipDefs[equipId].icon, g_EquipDefs[equipId].iconPalette);
        func_800FAF44(0);
    case MENU_STEP_EQUIP_HAND:
        if (g_MenuNavigation.cursorEquip == LEFT_HAND_SLOT) {
            D_801375D0 = LEFT_HAND_SLOT;
        } else {
            D_801375D0 = RIGHT_HAND_SLOT;
        }
        i = func_800FB23C(
            &g_MenuNavigation.cursorEquipType[0], g_Status.equipHandOrder,
            g_Status.equipHandCount, &g_Status.equipment[D_801375D0]);
        if (i == 2) {
            equipId =
                g_Status.equipHandOrder[g_MenuNavigation.cursorEquipType[0]];
            func_800FAD34(
                g_EquipDefs[equipId].description,
                g_Status.equipHandCount[equipId], g_EquipDefs[equipId].icon,
                g_EquipDefs[equipId].iconPalette);
        } else if (i == 1) {
            goto block_191;
        }
        break;
    case MENU_STEP_EQUIP_ACC_INIT:
        equipId =
            g_Status.equipBodyOrder
                [D_801375D8[g_MenuNavigation.cursorEquipType[1 + D_801375D4]]];
        func_800FAEC4(
            &g_MenuNavigation.cursorEquipType[D_801375D4] + 1,
            g_Status.equipBodyCount[equipId],
            g_AccessoryDefs[equipId].description, g_AccessoryDefs[equipId].icon,
            g_AccessoryDefs[equipId].iconPalette);
        func_800FAF44(1);
    case MENU_STEP_EQUIP_ACC:
        isSecondAccessory = g_MenuNavigation.cursorEquip;
        isSecondAccessory = (isSecondAccessory == ACCESSORY_2_SLOT);
        i = func_800FB23C(
            &g_MenuNavigation.cursorEquipType[D_801375D4] + 1,
            g_Status.equipBodyOrder, g_Status.equipBodyCount,
            &g_Status.wornEquipment[D_801375D4 + isSecondAccessory]);
        if (i == 2) {
            equipId = g_Status.equipBodyOrder
                          [D_801375D8[g_MenuNavigation
                                          .cursorEquipType[1 + D_801375D4]]];
            func_800FAD34(
                g_AccessoryDefs[equipId].description,
                g_Status.equipBodyCount[equipId], g_AccessoryDefs[equipId].icon,
                g_AccessoryDefs[equipId].iconPalette);
        } else if (i == 1) {
            goto block_191;
        }
        break;
    }
    if (g_MenuStep >= MENU_STEP_OPENED || g_MenuStep == MENU_STEP_EXIT_BEGIN ||
        g_MenuStep == MENU_STEP_EXIT_4) {
        MenuDraw();
        func_800F9690();
        func_800F96F4();
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/E588", DrawHudSubweapon2);
