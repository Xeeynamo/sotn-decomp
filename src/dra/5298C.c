#include "dra.h"

#define CH(x) ((x)-0x20)

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F298C);

bool func_800F483C(void) {
    s32 buf[BUTTON_COUNT];
    s32 i;
    s32 var_a1;
    s32* buttonConfig;

    for (i = 0; i < 8; i++) {
        buf[i] = 0;
    }

    for (i = 0; i < 7; i++) {
        buf[g_Settings.buttonConfig[i]] = 1;
    }

    for (i = 0; i < 8; i++) {
        if (buf[i] == 0) {
            g_Settings.buttonConfig[7] = i;
            break;
        }
    }

    for (i = 0; i < 8; i++) {
        g_Settings.buttonMask[i] = D_800A0160[g_Settings.buttonConfig[i]];
    }

    var_a1 = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        var_a1 |= 1 << *buttonConfig++;
    }

    return var_a1 == 0xFF;
}

bool IsAlucart(void) {
    if (CheckEquipmentItemCount(0xA8, 0) && CheckEquipmentItemCount(0xA7, 0) &&
        CheckEquipmentItemCount(0x59, 2))
        return true;
    return false;
}

void func_800F4994(void) {
    s32 correctStonesEquipped;
    s32 j;
    s32 i;
    s32* statsPtr;
    u32 statBonus;
    u32 hourOfDay;

    statsPtr = &g_Status.statsEquip;
    for (i = 0; i < 4; i++, statsPtr++) {
        *statsPtr = 0;
    }
    // Iterate through each Accessory
    for (i = 0; i < 5; i++) {
        // Iterate through the 4 stats (STR, CON, INT, LCK)
        for (j = 0; j < 4; j++) {
            statBonus = D_800A7718[g_Status.equipment[2 + i]].statsBonus[j];
            if ((s32)statBonus >= 0x81) {
                statBonus -= 0x100;
            }
            g_Status.statsEquip[j] += statBonus;
        }
    }
    hourOfDay = g_Status.timerHours % 24;
    // Hours of sunstone effectiveness
    if (6 <= hourOfDay && hourOfDay < 18) {
        // Sunstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3BU, 4U);
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped = CheckEquipmentItemCount(0x3AU, 4U);
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    }
    if (D_80139830[2] != 0) {
        g_Status.statsEquip[STAT_STR] += 20;
    }
    if (D_80139830[1] != 0) {
        g_Status.statsEquip[STAT_INT] += 20;
    }
    if (D_80139830[0] != 0) {
        g_Status.statsEquip[STAT_LCK] += 20;
    }
    if (g_Status.relics[27] & 2) {
        g_Status.statsEquip[STAT_CON] += 10;
    }
    if (g_Status.relics[29] & 2) {
        g_Status.statsEquip[STAT_LCK] += 10;
    }
    if (g_Status.relics[26] & 2) {
        g_Status.statsEquip[STAT_STR] += 10;
    }
    if (g_Status.relics[28] & 2) {
        g_Status.statsEquip[STAT_INT] += 10;
    }
    if (IsAlucart() != false) {
        g_Status.statsEquip[STAT_LCK] += 30;
    }
    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] >= 100) {
            g_Status.statsEquip[i] = 99;
        }
        g_Status.statsTotal[i] = g_Status.statsBase[i] + g_Status.statsEquip[i];
    }

    g_Status.statsTotal[1] =
        (g_Status.statsEquip[1] * 8) + g_Status.statsBase[1];
    g_Status.statsTotal[2] =
        (g_Status.statsEquip[2] * 4) + g_Status.statsBase[2];
    for (i = 0; i < 4; i++) {
        if (g_Status.statsTotal[i] < 0) {
            g_Status.statsTotal[i] = 0;
        }
    }
}

s32 CalcAttack(s32 equipId, s32 otherEquipId) {
    s32 i;
    u16 equipmentAttackBonus;
    s16 totalAttack;
    s16 strengthStat;

    if (D_800A4B04[equipId].itemCategory == ITEM_FOOD ||
        D_800A4B04[equipId].itemCategory == ITEM_MEDICINE ||
        (D_800A4B04[equipId].itemCategory == ITEM_SHIELD &&
         D_800A4B04[equipId].attack == 1)) {
        return 0;
    }
    if (equipId == 0x10) {
        return 0;
    }
    equipmentAttackBonus = 0;
    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            (u16)D_800A7718[g_Status.equipment[2 + i]].attBonus;
    }

    totalAttack = D_800A4B04[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (strengthStat >= totalAttack) {
        totalAttack += strengthStat;
    } else {
        totalAttack += strengthStat / 2;
    }

    totalAttack += equipmentAttackBonus;

    if (equipId == 0x7D) { // Badelaire sword
        totalAttack += g_Status.timerHours;
    }
    if (equipId == 0x8D) { // Muramasa sword
        totalAttack += SquareRoot0(g_Status.D_80097C40);
    }
    if (equipId == 4 && D_800A4B04[otherEquipId].itemCategory == ITEM_SHIELD) {
        totalAttack += 5;
    }
    if (equipId == 0x7E) {                  // Equippable Sword Familiar
        totalAttack += g_Status.D_80097C74; // Level of sword familiar
    }
    if (D_8013982C != 0) {
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
    g_Status.defenseElement = 0;
    g_Status.D_80097C2A = 0;
    g_Status.D_80097C2C = 0;
    g_Status.D_80097C2E = 0;

    // Iterate over player's hands, hand 0 and hand 1.
    for (i = 0; i < 2; i++) {
        thisHandItem = g_Status.equipment[i];
        totalDefense += D_800A4B04[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if ((thisHandItem == 4) &&
            D_800A4B04[g_Status.equipment[1 - i]].itemCategory == 9) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &D_800A7718[g_Status.equipment[i + 2]];
        totalDefense += acc->defBonus;
        g_Status.defenseElement |= acc->unk10;
        g_Status.D_80097C2A |= acc->unk12;
        g_Status.D_80097C2C |= acc->unk14;
        g_Status.D_80097C2E |= acc->unk16;
    }
    // Mirror cuirass
    if (CheckEquipmentItemCount(0xD, 0U) != 0) {
        g_Status.D_80097C2C |= 0x200;
    }
    // Alucard Mail
    if (CheckEquipmentItemCount(0xF, 0U) != 0) {
        g_Status.D_80097C2C |= 0x8000;
    }
    if (g_Status.relics[25] & 2) {
        g_Status.D_80097C2C |= 0x100;
    }
    if (D_8013983C != 0) {
        g_Status.D_80097C2A |= 0x8000;
    }
    if (D_80139840 != 0) {
        g_Status.D_80097C2A |= 0x2000;
    }
    if (D_80139844 != 0) {
        g_Status.D_80097C2A |= 0x4000;
    }
    if (D_80139848 != 0) {
        g_Status.D_80097C2A |= 0x100;
    }
    if (D_8013984C != 0) {
        g_Status.D_80097C2A |= 0x1000;
    }
    if (D_80139850 != 0) {
        g_Status.D_80097C2C |= 0x200;
    }
    if (D_80139854 != 0) {
        g_Status.D_80097C2A |= 0x800;
    }

    totalDefense += (SquareRoot0(g_Status.statsTotal[STAT_CON]) - 2);
    // Walk armor
    if (CheckEquipmentItemCount(0x13, 2) != 0) {
        totalDefense += g_roomCount / 60;
    }

    if (*D_80139828 != 0) {
        totalDefense += 0x14;
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
    u32* ot = g_CurrentBuffer->ot;
    DR_MODE* drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];

    if (D_80137614 != 0) {
        SetDrawMode(drawMode, 0, 0, tpage, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

u8 func_800F548C(u8 arg0) {
    u16 temp = arg0;

    if (arg0 & 0x80) {
        arg0 &= 0x7F;
        return func_800F548C(arg0 + 3);
    }
    return temp << 4;
}

bool IsOutsideDrawArea(s32 x0, s32 x1, s32 y0, s32 y1, MenuContext* context) {
    if (!(x1 > context->unk1.x)) {
        return true;
    }
    if (!(context->unk1.y < y1)) {
        return true;
    }
    if (x0 < (context->unk1.x + context->unk1.w)) {
        return (y0 < (context->unk1.y + context->unk1.h)) ^ 1;
    }
    return true;
}

bool ScissorPolyG4(POLY_G4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;
    s32 diff;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
    }

    return false;
}

bool ScissorPolyGT4(POLY_GT4* poly, MenuContext* context) {
    s32 scissorX;
    s32 scissorY;

    if (IsOutsideDrawArea(poly->x0, poly->x1, poly->y0, poly->y2, context))
        return true;

    if (poly->x0 < context->unk1.x) {
        s32 diff = context->unk1.x - poly->x0;
        poly->x0 += diff;
        poly->x2 += diff;
        poly->u0 += diff;
        poly->u2 += diff;
    }

    if (poly->y0 < context->unk1.y) {
        s32 diff = context->unk1.y - poly->y0;
        poly->y0 += diff;
        poly->y1 += diff;
        poly->v0 += diff;
        poly->v1 += diff;
    }

    scissorX = context->unk1.x + context->unk1.w;
    if (scissorX < poly->x1) {
        s32 diff = poly->x1 - scissorX;
        poly->x1 -= diff;
        poly->x3 -= diff;
        poly->u1 -= diff;
        poly->u3 -= diff;
    }

    scissorY = context->unk1.y + context->unk1.h;
    if (scissorY < poly->y2) {
        s32 diff = poly->y2 - scissorY;
        poly->y2 -= diff;
        poly->y3 -= diff;
        poly->v2 -= diff;
        poly->v3 -= diff;
    }

    return false;
}

bool ScissorSprite(SPRT* sprite, MenuContext* context) {
    s32 scissorY;
    s32 scissorX;
    s32 spriteX;
    s32 spriteY;

    if (IsOutsideDrawArea(sprite->x0, sprite->x0 + sprite->w, sprite->y0,
                          sprite->y0 + sprite->h, context))
        return true;

    if (sprite->x0 < context->unk1.x) {
        scissorX = context->unk1.x - sprite->x0;
        sprite->x0 += scissorX;
        sprite->u0 = sprite->u0 + scissorX;
        sprite->w = sprite->w - scissorX;
    }

    if (sprite->y0 < context->unk1.y) {
        scissorY = context->unk1.y - sprite->y0;
        sprite->y0 = sprite->y0 + scissorY;
        sprite->v0 = sprite->v0 + scissorY;
        sprite->h = sprite->h - scissorY;
    }

    scissorX = context->unk1.x + context->unk1.w;
    spriteX = sprite->x0 + sprite->w;
    if (scissorX < spriteX) {
        scissorY = spriteX - scissorX;
        sprite->w = sprite->w - scissorY;
    }

    scissorY = context->unk1.y + context->unk1.h;
    spriteY = sprite->y0 + sprite->h;
    if (scissorY < spriteY) {
        scissorX = spriteY - scissorY;
        sprite->h = sprite->h - scissorX;
    }

    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F5904);

void func_800F5A90(void) {
    func_800F5904(NULL, 96, 96, 64, 64, 0, 0, 0, 0x114, 1, 0);
}

void func_800F5AE4(MenuContext* context) {
    s32 i, x;

    for (i = 0, x = 72; i < 3; i++, x += 128)
        func_800F5904(context, x, 201, 128, 16, (i & 1) << 7,
                      func_800F548C(2) & 0xFF, 0x1A1, (i / 2) + 6, 1, 0);
}
void DrawMenuSprite(
    MenuContext* context, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 arg9, s32 colorIntensity, s32 argB) {
    u32* ot = g_CurrentBuffer->ot;
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    s32 otIdx = context->unk18 + 2;
    u32 polyColorIntensity;
    s32 temp_polyx0;

    if (context == &g_MenuData.menus[1]) {
        otIdx--;
    }

    poly->code &= 0xFD;

    if (arg9 != 0) {
        poly->code |= 1;
    } else {
        poly->code &= 0xFC;
    }

    func_80107360(poly, x, y, width, height, u, v);

    if (ScissorPolyGT4(poly, context) == false) {
        poly->tpage = tpage;
        poly->clut = D_8003C104[clut];
        func_80107250(poly, colorIntensity);
        if (argB == 1) {
            polyColorIntensity = (poly->y2 - poly->y0) * 4;
            func_801071CC(poly, polyColorIntensity, 0);
            func_801071CC(poly, polyColorIntensity, 1);
        }
        if (argB == 2) {
            temp_polyx0 = poly->x0;
            poly->x0 = poly->x2 = poly->x1;
            poly->x1 = poly->x3 = temp_polyx0;
        }
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.gt4++;
        func_800F53D4(tpage, otIdx);
    }
}

// NOTE: used to draw the menu cursor
void DrawMenuRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b) {
    u32* ot = g_CurrentBuffer->ot;
    POLY_G4* poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4];
    s32 otIdx = context->unk18 + 1;
    u32 temp;

    poly->x0 = posX;
    poly->y0 = posY;

    temp = (poly->x1 = posX + width);
    poly->y1 = posY;
    poly->x2 = posX;
    poly->x3 = temp;

    temp = (poly->y2 = posY + height);
    poly->y3 = temp;

    poly->code &= 0xFC;
    if (!ScissorPolyG4(poly, context)) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = r;
        poly->g0 = poly->g1 = poly->g2 = poly->g3 = g;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = b;
        AddPrim(&ot[otIdx], poly);
        g_GpuUsage.g4++;
        func_800F53D4(0, otIdx);
    }
}

void func_800F5E68(MenuContext* context, s32 cursorIdx, s32 x, s32 y, s32 w,
                   s32 h, s32 yGap, s32 bColorMode) {
    s32 r;

    if (bColorMode) {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            r = 0x7F - (g_blinkTimer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    DrawMenuRect(context, x, y + (cursorIdx * (h + yGap)), w, h, r, 0, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", DrawRelicsMenu);

void DrawMenuAlucardPortrait(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    DrawMenuSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

// Equivalent of floor(number * .75)
// Cloak color components are 5 bit.
// Examples: 31->23, 15->11
s32 DarkenCloakColor(s32 color) { return color * 3 / 4; }

// Creates light and dark versions of cloak colors in BGR555 format
void ApplyJosephsCloakPalette(void) {
    g_JosephsCloak.liningDark =
        DarkenCloakColor(g_Settings.cloakColors[3]) +
        ((DarkenCloakColor(g_Settings.cloakColors[4]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[5]) << 0xA);
    g_JosephsCloak.liningLight =
        (g_Settings.cloakColors[3] +
         ((g_Settings.cloakColors[4] << 5) - 0x8000)) +
        ((u32)g_Settings.cloakColors[5] << 0xA);
    g_JosephsCloak.exteriorDark =
        DarkenCloakColor(g_Settings.cloakColors[0]) +
        ((DarkenCloakColor(g_Settings.cloakColors[1]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[2]) << 0xA);
    g_JosephsCloak.exteriorLight =
        g_Settings.cloakColors[0] +
        ((g_Settings.cloakColors[1] << 5) - 0x8000) +
        ((u32)g_Settings.cloakColors[2] << 0xA);
}

void DrawMenuAlucardCloakPreview(MenuContext* ctx) {
    DrawMenuSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    DrawMenuSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_800F6508(MenuContext* context, s32 x, s32 y) {
    s32 yellow;

    if (g_blinkTimer & 0x10) {
        yellow = ((g_blinkTimer & 0xF) * 2) + 0x60;
    } else {
        yellow = 0x7F - (g_blinkTimer & 0xF);
    }
    DrawMenuRect(context, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* context) {
    s32 height;
    s32 r;

    height = context->cursorH / 5;
    if (g_blinkTimer & 0x20) {
        r = (g_blinkTimer & 0x1F) + 0x40;
    } else {
        r = 0x5F - (g_blinkTimer & 0x1F);
    }
    DrawMenuRect(context, context->cursorX,
                 context->cursorY + (height * g_MenuNavigation.cursorMain),
                 context->cursorW, height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuContextIndex, s32 bColorMode) {
    s32 r;
    MenuContext* context = &g_MenuData.menus[menuContextIndex];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_blinkTimer & 0x20) {
            r = (g_blinkTimer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_blinkTimer & 0x1F);
        }
    }
    DrawMenuRect(context, 0x70, g_MenuNavigation.cursorEquip * 13 + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

void func_800F66BC(
    const char* str, s32 x, s32 y, MenuContext* context, bool disableTexShade) {
    u16 temp;
    const int ChWidth = 12;
    const int ChHeight = 16;
    u8 ch;
    s32 unk;
loop_1:
    ch = *(str++);

    if (ch == 0xFF) {
        return;
    }
    unk = (u16)(ch & 0x10);
    unk = unk != 0;
    temp = ch;
    temp = temp >> 5;
    func_800F5904(context, x, y, ChWidth, ChHeight, (ch & 0xF) * ChWidth,
                  temp * ChHeight, 0x1A1, unk + 6, disableTexShade, 0x40);
    x += ChWidth;
    goto loop_1;
}

void DrawMenuChar(u8 ch, int x, int y, MenuContext* context) {
    func_800F5904(context, x, y, 8, 8, (ch & 0xF) * 8, (u32)(ch & 0xF0) >> 1,
                  0x196, 0x1E, 1, 0);
}

void DrawMenuStr(const u8* str, s32 x, s32 y, MenuContext* context) {
    const int ChWidth = 8;
    const int ChHeight = 8;
    u8 ch;
    s32 xcopy;
    s32 ycopy;

    s32 s4 = D_8013784C;

    D_80137614 = 0;
    while (1) {
        xcopy = x;
        ycopy = y;
        ch = *str++;
        if (*str == 0xC0 && *(str + 1) == 0xD2) {
            D_8013784C = 2;
            str += 2;
        } else
            D_8013784C = s4;

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
        DrawMenuChar(ch, xcopy, ycopy, context);
        x += ChWidth;
    }
    D_80137614 = 1;
    func_800F53D4(0x1E, context->unk18 + 2);
}

void DrawMenuInt(s32 digit, s32 x, s32 y, MenuContext* context) {
    do {
        DrawMenuChar((digit % 10) + 16, x, y, context);
        digit /= 10;
        x += -8;
    } while (digit != 0);
}

// Draw a number with a limit of N digits
void DrawMenuTime(s32 number, s32 x, s32 y, MenuContext* context, s32 digits) {
    do {
        DrawMenuChar(((number % 10) + 0x10), x, y, context);
        number /= 10;
        x -= 8;
        digits -= 1;
    } while (digits != 0);
}

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F6A70);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F6BEC);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F6CC0);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F6DC8);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", DrawSettingsButton);
#else
extern u8 c_chPlaystationButtons[];
extern u8 c_chShoulderButtons[];

void DrawSettingsButton(MenuContext* ctx) {
    s32 cursorX;
    s32 i;
    s32 x;
    s32 y;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;

    cursorX = 0x98;
    i = 0;
    x = 0xC0;
    y = 0x30;
    for (; i < 7; i++) {
        DrawMenuStr(c_strButtonRightHand[i], cursorX, y, ctx);
        buttonId = g_Settings.buttonConfig[i];
        btn1_x = (buttonId * 12) + 0x30;
        DrawMenuChar(c_chPlaystationButtons[buttonId], x + btn1_x, y, ctx);
        if (buttonId >= 4) {
            btn2_x = btn1_x + 8;
            DrawMenuChar(c_chShoulderButtons[buttonId], x + btn2_x, y, ctx);
        }
        y += 16;
    }

    func_800F5E68(
        ctx, g_MenuNavigation.cursorButtons, cursorX - 2, 46, 84, 12, 4, 1);
}
#endif

void DrawSettingsReverseCloak(MenuContext* context) {
    DrawMenuStr(c_strNormal, 176, 48, context);
    DrawMenuStr(c_strReversal, 176, 64, context);
    func_800F5E68(
        context, g_Settings.isCloakLiningReversed, 174, 46, 64, 12, 4, 1);
}

void DrawSettingsSound(MenuContext* context) {
    s16 cursorX = context->cursorX;
    s16 cursorY = context->cursorY;
    s32 subMenuX = cursorX + 4;
    DrawMenuStr(c_strStereo, subMenuX, cursorY + 4, context);
    DrawMenuStr(c_strMono, subMenuX, cursorY + 0x14, context);
    func_800F5E68(context, g_Settings.isSoundMono, cursorX + 2, cursorY + 2, 53,
                  12, 4, 1);
}

u8 statChangeArrow(u16 arg0, u16 arg1) {
    if (arg0 == arg1) {
        return 0xE4; // Right arrow
    }
    if (arg0 < arg1) {
        return 0xE3; // Right-Up arrow

    } else {
        return 0xE5; // Right-Down arrow
    }
}

void func_800F7244(void) {
    s32 i;

    g_NewAttackRightHand = g_Status.attackHands[0];
    g_NewAttackLeftHand = g_Status.attackHands[1];
    g_NewDefenseEquip = g_Status.defenseEquip;

    for (i = 0; i < 4; i++) {
        g_NewPlayerStatsTotal[i] =
            g_Status.statsBase[i] + g_Status.statsEquip[i];
    }
}

extern s32 D_80137948;

void DrawStatChanges(void) {
    s32 xcoord;
    s32 ycoord;
    s32 i;
    MenuContext* ctx;
    s32 arrow;

    if ((g_MenuData.D_80137692 != 0) || (D_80137948 == 0)) {
        return;
    }
    ctx = &g_MenuData.menus[2];
    // Print the destination value for the square attack item
    DrawMenuInt(g_NewAttackRightHand, 0x154, 0x50, ctx);
    // Show arrow icon for increasing, decreasing, or staying the same
    arrow = statChangeArrow(g_Status.attackHands[0], g_NewAttackRightHand);
    DrawMenuChar(arrow, 0x13C, 0x50, ctx);

    // Same but for the circle attack item
    DrawMenuInt(g_NewAttackLeftHand, 0x154, 0x5A, ctx);
    arrow = statChangeArrow(g_Status.attackHands[1], g_NewAttackLeftHand);
    DrawMenuChar(arrow, 0x13C, 0x5A, ctx);
    // And repeat for defense.
    DrawMenuInt(g_NewDefenseEquip, 0x154, 0x6A, ctx);
    arrow = statChangeArrow(g_Status.defenseEquip, g_NewDefenseEquip);
    DrawMenuChar(arrow, 0x13C, 0x6A, ctx);

    // Iterate through the 4 stats (STR CON INT LCK) doing the same.
    xcoord = 0x108;
    for (i = 0; i < 4; i++) {
        ycoord = 0x22 + i * 10;
        // Name of the stat
        DrawMenuStr((&c_strSTR)[i], xcoord, ycoord, ctx);
        // Current value for the stat
        DrawMenuInt(g_Status.statsBase[i] + g_Status.statsEquip[i],
                    xcoord + 0x2C, ycoord, ctx);
        // Indication of change
        arrow =
            statChangeArrow((g_Status.statsBase[i] + g_Status.statsEquip[i]),
                            g_NewPlayerStatsTotal[i]);
        DrawMenuChar(arrow, xcoord + 0x34, ycoord, ctx);
        // Final value for the stat
        DrawMenuInt(g_NewPlayerStatsTotal[i], xcoord + 0x4C, ycoord, ctx);
    }
}

void DrawPauseMenu(s32 arg0) {
    MenuContext* ctx;
    s32 temp_s1;
    s32 temp_var;
    s32 x;
    s32 y;
    s32 i;
    s32 temp_y;
    s32 phi_a0_5;

    ctx = &g_MenuData.menus[arg0];
    func_800F53A4();
    if (arg0 == 1) {
        DrawMenuAlucardPortrait(ctx);
        DrawMenuStr(IsAlucart() ? c_strALUCART : c_strALUCARD, 128, 40, ctx);
        DrawMenuStr(c_strHP, 96, 56, ctx);
        DrawMenuInt(g_Status.hp, 168, 56, ctx);
        DrawMenuChar(CH('/'), 176, 56, ctx);
        DrawMenuInt(g_Status.hpMax, 208, 56, ctx);
        DrawMenuStr(c_strMP, 96, 68, ctx);
        DrawMenuInt(g_Status.mp, 168, 68, ctx);
        DrawMenuChar(CH('/'), 176, 68, ctx);
        DrawMenuInt(g_Status.mpMax, 208, 68, ctx);
        DrawMenuStr(c_strHEART, 96, 80, ctx);
        DrawMenuInt(g_Status.hearts, 168, 80, ctx);
        DrawMenuChar(CH('/'), 176, 80, ctx);
        DrawMenuInt(g_Status.heartsMax, 208, 80, ctx);
        DrawMenuStr(c_strEXP, 32, 176, ctx);
        DrawMenuInt(g_Status.exp, 144, 176, ctx);
        DrawMenuStr(c_strNEXT, 32, 188, ctx);
        DrawMenuInt(g_Status.level != 99
                        ? c_arrExpNext[g_Status.level] - g_Status.exp
                        : 0,
                    144, 188, ctx);
        DrawMenuStr(c_strGOLD[0], 32, 200, ctx);
        DrawMenuInt(g_Status.gold, 144, 200, ctx);
        DrawMenuStr(c_strLEVEL, 248, 40, ctx);
        DrawMenuInt(g_Status.level, 304, 40, ctx);
        DrawMenuStr(c_strSTATUS, 248, 56, ctx);
        i = 37;
        if (g_Player.unk0C & PLAYER_STATUS_CURSE) {
            i = 40;
        }
        if (g_Player.unk0C & PLAYER_STATUS_POISON) {
            i = 38;
        }
        if (g_Player.unk0C & PLAYER_STATUS_STONE) {
            i = 39;
        }
        if (IsAlucart()) {
            i = 45;
        }
        DrawMenuStr(c_strGOLD[i - 7], 260, 68, ctx);
        DrawMenuStr(c_strROOMS, 240, 150, ctx);
        DrawMenuInt(g_roomCount, 328, 150, ctx);
        DrawMenuStr(c_strKILLS, 240, 164, ctx);
        DrawMenuInt(g_Status.killCount, 328, 164, ctx);
        DrawMenuStr(c_strTIME, 208, 192, ctx);
        DrawMenuInt(g_Status.timerHours, 264, 192, ctx);
        DrawMenuChar(CH(':'), 272, 192, ctx);
        DrawMenuTime(g_Status.timerMinutes, 288, 192, ctx, 2);
        DrawMenuChar(CH(':'), 296, 192, ctx);
        DrawMenuTime(g_Status.timerSeconds, 312, 192, ctx, 2);
    }

    if (ctx == &g_MenuData.menus[1]) {
        x = 248;
        y = 88;
    } else {
        x = 232;
        y = 80;
    }
    func_800F66BC(D_800A2D68, x, y, ctx, 1);

    temp_var = g_Settings.buttonConfig[0];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 44, y, ctx);
    } else {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 40, y, ctx);
        DrawMenuChar(c_chShoulderButtons[temp_s1], x + 48, y, ctx);
    }
    DrawMenuInt(g_Status.attackHands[0], x + 76, y, ctx);

    temp_var = g_Settings.buttonConfig[1];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 44, y + 10, ctx);
    } else {
        DrawMenuChar(c_chPlaystationButtons[temp_s1], x + 40, y + 10, ctx);
        DrawMenuChar(c_chShoulderButtons[temp_s1], x + 48, y + 10, ctx);
    }

    DrawMenuInt(g_Status.attackHands[1], x + 76, y + 10, ctx);
    func_800F66BC(D_800A2D6C, x, y + 20, ctx, 1);
    DrawMenuInt(g_Status.defenseEquip, x + 76, y + 26, ctx);
    if (ctx == (&g_MenuData.menus[1])) {
        x = 32;
        y = 120;
    } else {
        DrawMenuStr(D_800A83AC[g_MenuNavigation.cursorEquip], 8, 40, ctx);
        x = 12;
        y = 70;
    }

    for (i = 0, temp_y = y; i < 4; temp_y += 12, i++) {
        s32* statsBase = &g_Status.statsBase[i];
        DrawMenuStr((&c_strSTR)[i], x, temp_y, ctx);
        DrawMenuInt(*statsBase, x + 44, temp_y, ctx);
        if (g_Status.statsEquip[i] != 0) {
            if (g_Status.statsEquip[i] > 0) {
                DrawMenuChar(CH('+'), x + 52, temp_y, ctx);
                phi_a0_5 = g_Status.statsEquip[i];
            } else {
                DrawMenuChar(CH('-'), x + 52, temp_y, ctx);
                phi_a0_5 = -g_Status.statsEquip[i];
            }
            DrawMenuInt(phi_a0_5, x + 68, temp_y, ctx);
        }
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", DrawSpellMenu);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F7F64);

void func_800F82F4(void) {
    RECT dstRect;

    dstRect.x = 448;
    dstRect.y = 176;
    dstRect.w = g_imgUnk8013C200->width >> 2;
    dstRect.h = g_imgUnk8013C200->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C200->data);

    dstRect.x = 480;
    dstRect.w = g_imgUnk8013C270->width >> 2;
    dstRect.h = g_imgUnk8013C270->height;
    LoadImage(&dstRect, (u_long*)g_imgUnk8013C270->data);
}

void DrawSystemMenu(MenuContext* ctx) {
    const char** new_var;
    s32 strIdx;
    s8** menuOptions;

    func_800F5E68(ctx, g_MenuNavigation.cursorSettings, 30, 46, 128, 12, 4,
                  D_800978F8 == 0x101);

    new_var = &c_strButton;
    DrawMenuStr(*new_var, 0x20, 0x30, ctx);

    strIdx = g_IsCloakLiningUnlocked ? 0x11 : 0x13;
    menuOptions = (&c_strButton) - 0x10;
    DrawMenuStr(menuOptions[strIdx], 32, 64, ctx);

    strIdx = g_IsCloakColorUnlocked ? 0x12 : 0x13;
    DrawMenuStr(menuOptions[strIdx], 32, 80, ctx);
    DrawMenuStr(c_strWindow, 32, 96, ctx);
    DrawMenuStr(c_strSound, 32, 112, ctx);

    strIdx = g_IsTimeAttackUnlocked ? 0x24 : 0x13;
    DrawMenuStr(menuOptions[strIdx], 32, 128, ctx);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F84CC);

void func_800F86E4(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        FreePrimitives(D_801377FC[i]);
    }

    FreePrimitives(D_8013783C);
    FreePrimitives(D_80137840);
}

void func_800F8754(MenuContext* context, s32 x, s32 y) {
    s32 curX;
    s32 phi_a1;

    if (D_801375DC == 0) {
        D_8013784C = 1;
    }

    DrawMenuStr(c_strSpells, x + 14, y + 20, context);
    if (D_801375FC == 0) {
        D_8013784C = 1;
    } else {
        D_8013784C = 0;
    }

    phi_a1 = x + 2;
    DrawMenuStr(c_strFamiliars, phi_a1, y + 68, context);
    D_8013784C = 0;
    DrawMenuStr(c_strEquip, x + 18, y + 4, context);
    curX = x + 14;
    DrawMenuStr(c_strRelics, curX, y + 36, context);
    DrawMenuStr(c_strSystem, curX, y + 52, context);
}

void func_800F8858(MenuContext* context) {
    s32 i = 0;
    const char** pStrEquipTypes = &c_strSSword;
    s32 y = 8;

    for (; i < ITEM_END; i++) {
        DrawMenuStr(pStrEquipTypes[g_Settings.equipOrderTypes[i]],
                    context->cursorX + 4, context->cursorY + y, context);
        y += 16;
    }

    func_800F5E68(context, D_80137618, context->cursorX + 2,
                  context->cursorY + 4, 72, 16, 0, 1);
}

void func_800F892C(s32 index, s32 x, s32 y, MenuContext* context) {
    func_800F5904(context, x, y, 16, 16, (index & 7) * 16,
                  ((index & 0xF8) * 2) | 0x80, index + 0x1D0, 0x1A, 1, 0);
}

void func_800F8990(MenuContext* ctx, s32 x, s32 y) {
    const s32 Cols = 2;
    const s32 Width = 168;
    const s32 Height = 12;

    u8* sp20;
    s32 itemsPerPage;
    s32* new_var;
    s32 totalItemCount;
    s32 curX;
    s32 curY;
    s32 myX;
    s32 myY;
    s32 itemIndex;
    s32 i;
    s8* strEquipName;
    u16 icon;
    u16 palette;
    u8 equipId;
    u8* equipsAmount;
    s32 idx;

    new_var = &D_801375CC.equipTypeFilter;
    sp20 = GetEquipOrder(*new_var);
    equipsAmount = GetEquipCount(*new_var);
    totalItemCount = func_800FD6C4(*new_var);
    curX = 0;
    curY = 0;
    itemsPerPage = Cols + ctx->cursorH / Height * Cols;
    for (i = 0; i < itemsPerPage; i++) {
        itemIndex = i + -ctx->h / Height * Cols;
        if (itemIndex >= totalItemCount) {
            break;
        }

        myX = 40 + x + (itemIndex & 1) * Width;
        myY = 4 + y + itemIndex / 2 * Height;
        if (g_IsSelectingEquipment && itemIndex == g_EquipmentCursor) {
            curX = myX + 1;
            curY = myY - 2;
        }

        equipId = sp20[D_801375D8[itemIndex]];
        if (equipsAmount[equipId] == 0)
            continue;

        strEquipName = GetEquipmentName(*new_var, equipId);
        if (D_801375CC.equipTypeFilter == 0) {
            icon = D_800A4B04[equipId].icon;
            palette = D_800A4B04[equipId].palette;
        } else {
            icon = D_800A7718[equipId].icon;
            palette = D_800A7718[equipId].palette;
        }

        LoadEquipIcon(icon, palette, i);
        func_800F892C(i, myX - 16, myY - 4, ctx);
        DrawMenuStr(strEquipName, myX, myY, ctx);

        if (D_801375CC.equipTypeFilter == 0 && equipId != 0 ||
            D_801375CC.equipTypeFilter != 0 && equipId != 0x1A &&
                equipId != 0 && equipId != 0x30 && equipId != 0x39) {
            DrawMenuInt(equipsAmount[equipId], myX + 128, myY, ctx);
        }
    }

    if (g_IsSelectingEquipment) {
        func_800F6508(ctx, curX, curY);
    }
}

void BlinkMenuCursor(s32 left, s32 top, s32 right, s32 bottom, s32 arg4) {

    s32 var_s2;
    u8 blink_value;

    u32* temp_s3 = g_CurrentBuffer->ot;
    LINE_G2* temp_s0 = &g_CurrentBuffer->lineG2[g_GpuUsage.line];

    if (arg4 != 0) {
        var_s2 = g_MenuData.menus[arg4 - 1].unk18 + 4;
    } else {
        var_s2 = 0x80;
    }
    SetSemiTrans(temp_s0, 0);
    SetShadeTex(temp_s0, 1);
    if (g_blinkTimer & 0x20) {
        blink_value = g_blinkTimer & 0x1F;
    } else {
        blink_value = 0x1F - (g_blinkTimer & 0x1F);
    }
    blink_value *= 4;
    blink_value -= 0x80;

    if (arg4 != 0) {
        blink_value = 0xFF;
    }

    temp_s0->r0 = blink_value;
    temp_s0->g0 = blink_value;
    temp_s0->b0 = blink_value;
    temp_s0->r1 = blink_value;
    temp_s0->g1 = blink_value;
    temp_s0->b1 = blink_value;
    temp_s0->x0 = left;
    temp_s0->y0 = top;
    temp_s0->x1 = right;
    temp_s0->y1 = bottom;
    AddPrim(&temp_s3[var_s2], temp_s0);
    g_GpuUsage.line++;
}

void DrawConsumableCount(s32 itemId, s32 hand, MenuContext* ctx) {
    u8 outstring[16];
    u8* str_idx;
    s32 displayCount;
    u8 equipCount;

    if (D_800A4B04[itemId].isConsumable != 0) {
        // This holds one less than how many you have.
        equipCount = g_Status.equipHandCount[itemId];
        str_idx = &outstring;
        // First character in the string is the (
        *str_idx++ = MENUCHAR('(');
        // This is now how many you have.
        displayCount = equipCount + 1;
        if (displayCount < 10) {
            // Get the character code for the count.
            *str_idx++ = equipCount + 1 + MENUCHAR('0');
        } else {
            if (displayCount == 100) {
                *str_idx++ = MENUCHAR('1');
                // Neat trick, set this to 0 so following two steps draw 00
                displayCount = 0;
            }
            *str_idx++ = (displayCount / 10) + MENUCHAR('0');
            *str_idx++ = (displayCount % 10) + MENUCHAR('0');
        }
        // Finish off with a ) and string terminator
        *str_idx++ = MENUCHAR(')');
        *str_idx++ = 0xFF;
        *str_idx++ = 0;
        // Draw it after the item name. X=224, Y = 30 + 13*hand
        DrawMenuStr(&outstring, 224, (hand * 13) + 30, ctx);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F8F28);

void func_800F9690(void) {
    POLY_GT4* poly = &g_PrimBuf[D_8013783C];

    if (D_80137608 != 0) {
        poly->pad3 = 0x80;
    } else {
        poly->pad3 = 0x8;
    }
    if (D_801376B0 != 0) {
        poly->pad3 = 0x8;
    }
}

void func_800F96F4(void) { // !Fake:
    s32 new_var2;
    POLY_GT4* poly;
    s32 temp_a2;
    s32* temp;
    s32* new_var;

    new_var = D_80137848;
    poly = &g_PrimBuf[D_80137840];
    temp_a2 = g_MenuData.D_80137692 == 0;
    temp = D_80137844;

    if ((D_80137844[0] != 0) && (temp_a2 != 0)) {
        (&g_PrimBuf[D_80137840])->blendMode = 0x80;
        if (D_80137844[0] == 1) {
            (&g_PrimBuf[D_80137840])->clut = 0x188;
        } else {
            D_80137844[0] -= 1;
            (&g_PrimBuf[D_80137840])->clut = 0x181;
        }
    } else {
        poly->pad3 = 0x8;
    }

    poly = (POLY_GT4*)poly->tag;
    temp = new_var;

    if (((*temp) != 0) && (temp_a2 != 0)) {
        poly->pad3 = 0x80;
        new_var2 = *temp;
        if (new_var2 == 1) {
            do {
                poly->clut = 0x188;
            } while (0);
            return;
        }
        *temp -= 1;
        poly->clut = 0x181;
        return;
    }
    poly->pad3 = 8;
}

void func_800F97DC(void) {
    D_8013794C = &D_8007EFE4;
    D_80137950 = 0x180;
    D_80137954 = 0;
}

void func_800F9808(u32 arg0) {
    s32 temp_s0;
    s32 i;
    PixPattern* oldPos;

    temp_s0 = (arg0 == 2) ? 32 : 0;
    arg0 = func_800F548C(arg0);
    oldPos = (PixPattern*)D_8013794C;

    for (i = 0; i < ((temp_s0 + 0x100) * 8); i++) {
        *D_8013794C++ = 0;
    }

    LoadTPage(oldPos, 0, 0, 0x180, arg0, temp_s0 + 256, 16);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F98AC);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F99B8);

void func_800F9D40(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }

    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F98AC(arg0, arg1);
}

void func_800F9D88(s32 arg0, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = &D_80082FE4;
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(arg0, arg1, 0);
}

void func_800F9DD0(u8* arg0, u8* arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*arg0 == 0)
            break;
        *arg1++ = *arg0++;
        *arg1++ = *arg0++;
    }
}

// DECOMP_ME_WIP func_800F9E18 https://decomp.me/scratch/VmuNt 99.46%
INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F9E18);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800F9F40);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FA034);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FA3C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FA60C);

// If you use both attack buttons at once, see if something special happens.
// Applies to Shield Rod + Shield, or dual Heaven Swords
void CheckWeaponCombo(void) {
    s32 weapon0;
    s32 weapon1;
    s32 combo1;
    s32 combo2;
    s32 comboBits;
    s32 i;
    s32 oddComboCheck;

    weapon0 = g_Status.equipment[0];
    weapon1 = g_Status.equipment[1];

    combo1 = D_800A4B04[weapon0].comboSub & D_800A4B04[weapon1].comboMain;
    oddComboCheck = 0x80000000;
    oddComboCheck &= -(combo1 == 0);

    combo2 = D_800A4B04[weapon0].comboMain & D_800A4B04[weapon1].comboSub;
    comboBits = combo1 | combo2;

    if (comboBits != 0) {
        for (i = 0xAA; i < 0xD9; i++) {
            if (comboBits & D_800A4B04[i].comboSub) {
                D_8013AEE4 = oddComboCheck + i;
                return;
            }
        }
    }
    D_8013AEE4 = 0;
}

bool LoadWeaponPrg(s32 equipIndex) {
    s32 equipId;
    s32 weaponId;

    equipId = g_Status.equipment[equipIndex];
    if (g_Status.equipment[3] == 0x19) {
        equipId = 0xD8;
    }
    weaponId = D_800A4B04[equipId].weaponId;
    if (weaponId == D_8003C90C[equipIndex] || weaponId == 0xFF) {
        return 1;
    }
    if (g_UseDisk) {
        if (g_IsUsingCd) {
            return 0;
        }
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_Weapon0 + equipIndex;
    } else {
        if (LoadFileSim(weaponId, SimFileType_Weapon0Prg + equipIndex) < 0 ||
            LoadFileSim(weaponId, SimFileType_Weapon0Chr + equipIndex) < 0) {
            return 0;
        }
    }
    D_8003C90C[equipIndex] = weaponId;
    return 1;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FA9DC);

void func_800FAB1C(void) {
    const int START = 4;
    Entity* entity;
    s32 i;

    for (entity = g_Entities + START, i = START; i < 64; i++) {
        if (entity->entityId >= 208 && entity->entityId < 224) {
            DestroyEntity(entity);
        }
        entity++;
    }
}

Unkstruct_80137638 D_80137638[];

void func_800FAB8C(s32 arg0) {
    D_80137638[arg0].unk0 = 1;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABBC(s32 arg0) {
    D_80137638[arg0].unk0 = 3;
    D_80137638[arg0].unk1 = 0;
}

void func_800FABEC(s32 context) { D_80137638[context].unk0 = 0; }

void func_800FAC0C(s32 context) { D_80137638[context].unk0 = 2; }

void func_800FAC30(void) {
    D_80137844[0] = 0;
    D_80137848[0] = 0;
}

void func_800FAC48(void) {
    ClearImage(&g_Vram.D_800ACD90, 0, 0, 0);
    ClearImage(&g_Vram.D_800ACDC8, 0, 0, 0);
}

void func_800FAC98(void) { func_800F9808(2); }

bool func_800FACB8(void) {
    if (g_pads[0].tapped & 2) {
        g_MenuNavigation.cursorEquip++;
        if (g_MenuNavigation.cursorEquip == 7) {
            g_MenuNavigation.cursorEquip = 0;
        }
        return true;
    }
    if (g_pads[0].tapped & 1) {
        g_MenuNavigation.cursorEquip--;
        if (g_MenuNavigation.cursorEquip == -1) {
            g_MenuNavigation.cursorEquip = 6;
        }
        return true;
    }
    return false;
}

void func_800FAD34(s32 arg0, u8 arg1, u16 equipIcon, u16 palette) {
    D_80137608 = 0;
    func_800F9808(2);

    if (arg1) {
        D_80137608 = 1;
        func_800F99B8(arg0, 2, 0);
        LoadEquipIcon(equipIcon, palette, 0x1F);
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FADC0);

void func_800FAE98(void) {
    func_800FADC0();
    D_800978F8 = 0x40;
}

void func_800FAEC4(u16 pad, u16 arg1, s32 arg2, s16 arg3, u16 arg4) {
    g_IsSelectingEquipment = 0;
    func_800FAC98();
    func_800FAD34(arg2, arg1, arg3, arg4);
    D_800978F8 += 1;
}

void func_800FAF44(s32 arg0) {
    s32 var_a0;
    s32 i;
    s32 j;
    s32* var_a1;

    D_801375D8 = &D_80084FE4;
    var_a1 = &D_80084FE4;

    if (arg0 == 0) {
        for (i = 0; i < 169; i++) {
            *var_a1 = i;
            var_a1++;
        }

        g_MenuData.D_80137688 = g_MenuData.D_8013768C =
            g_MenuNavigation.scrollEquipHand;
        return;
    }
    g_MenuData.D_80137688 = g_MenuData.D_8013768C =
        ((s32*)g_MenuNavigation.scrollEquipAccessories)[D_801375D4];

    for (i = 0; i < 90; i++) {
        if (D_800A7734[i].unk00 == D_801375D4) {
            *var_a1 = i;
            var_a1++;
        }
    }
}

void func_800FB004(void) {
    s32 temp_a1 = func_800FD6C4(D_801375CC.equipTypeFilter);
    s32 temp_v0;

    if (((-g_MenuData.D_80137688) / 12) != 0) {
        if (*D_80137844 == 0) {
            *D_80137844 = 1;
        }
    } else {
        *D_80137844 = 0;
    }

    temp_v0 = -g_MenuData.D_80137688 + g_MenuData.D_80137678[2];

    if ((temp_v0 / 12) < (temp_a1 / 2)) {
        if (D_80137848[0] == 0) {
            D_80137848[0] = 1;
        }
    } else {
        D_80137848[0] = 0;
    }
}

void func_800FB0FC(void) {
    Unkstruct_800A2D98* temp = &D_800A2D98[g_MenuNavigation.cursorEquip];
    s32 temp_a1 = temp->unk4;
    s32 new_var2 = temp->unk8;

    D_801375CC.equipTypeFilter = temp->equipTypeFilter;
    D_801375CC.unk8 = temp_a1;
    func_800FAF44(new_var2);
    func_800FB004();
}

void func_800FB160(s32 arg0, s32 arg1, s32 equipType) {
    u8 swap;
    u8* equipOrder;

    equipOrder = GetEquipOrder(equipType);
    swap = equipOrder[D_801375D8[arg0]];
    equipOrder[D_801375D8[arg0]] = equipOrder[D_801375D8[arg1]];
    equipOrder[D_801375D8[arg1]] = swap;
}

bool func_800FB1EC(s32 arg0) {
    if (D_801375CC.equipTypeFilter == 0) {
        if (arg0 == 0) {
            return true;
        }
    } else if (
        (arg0 == 0x1A) || (arg0 == 0) || (arg0 == 0x30) || (arg0 == 0x39)) {
        return true;
    }

    return false;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FB23C);

void func_800FB9BC(void) {
    s32 i;

    MenuContext* context = &g_MenuData.menus[0];

    for (i = 0; i < 0x10; i++, context++) {
        context->cursorX = context->unk1.x = MenuContextData[i].cursorX;
        context->cursorY = context->unk1.y = MenuContextData[i].cursorY;
        context->cursorW = context->unk1.w = MenuContextData[i].cursorW;
        context->cursorH = context->unk1.h = MenuContextData[i].cursorH;
        context->unk14 = 0;
        context->w = 0;
        context->unk16 = 0;
        context->h = 0;
        context->unk18 = MenuContextData[i].unk08;
        context->unk1C = 2;
    }
    D_801376C4 = D_801376C8 = -((g_MenuNavigation.cursorRelic / 2) * 120) / 14;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FBAC4);

INCLUDE_ASM("asm/us/dra/nonmatchings/5298C", func_800FBC24);

void func_800FD39C(s32 x, s32 y, s32 w, s32 h, s32 u, s32 v, s32 pal, s32 _,
                   s32 blend, s32 color) {
    GpuBuffer* gpuBuffer;
    SPRT* sprt;

    sprt = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
    gpuBuffer = g_CurrentBuffer;
    SetSemiTrans(sprt, 0);
    SetShadeTex(sprt, blend);
    sprt->x0 = x;
    sprt->y0 = y;
    sprt->w = w;
    sprt->h = h;
    sprt->u0 = u;
    sprt->v0 = v;
    sprt->b0 = sprt->g0 = sprt->r0 = color;
    sprt->clut = D_8003C104[pal];
    AddPrim(&gpuBuffer->ot[0x1FF], sprt);
    g_GpuUsage.sp++;
}

s32 func_800FD4C0(s32 bossId, s32 action) {
    s32 temp_v0;
    s32 temp_v1;
    s32 seconds;
    s32 timer;

    switch (action) {
    // get the time attack for a specific defeated boss. this is also
    // responsible to check if the player should teleport into a boss room
    case 0:
        return g_Settings.timeAttackRecords[bossId];

    // set new time attack record if the boss was not previously defeated
    case 1:
        timer = g_Settings.timeAttackRecords[bossId];
        if (timer = timer != 0) {
            return g_Settings.timeAttackRecords[bossId];
        }

        seconds = g_Status.timerSeconds;
        g_Settings.timeAttackRecords[bossId] = seconds;
        temp_v1 = (g_Status.timerMinutes * 100) + seconds;
        g_Settings.timeAttackRecords[bossId] = temp_v1;
        temp_v0 = (g_Status.timerHours * 10000) + temp_v1;
        g_Settings.timeAttackRecords[bossId] = temp_v0;
        return temp_v0;

    // set boss visited
    // not exactly sure yet why this flag is needed
    case 2:
        g_Settings.D_8003CB00 |= 1 << bossId;
    }
}

bool func_800FD5BC(Unkstruct_800FD5BC* arg0) {
    s32 temp;

    if (arg0->unk4 != 5) {
        if (((u32)arg0->unk4) >= 0x10U) {
            temp = g_Status.hpMax;
            if (g_Status.hpMax < 0) {
                temp += 7;
            }
            arg0->unk8 = temp >> 3;
        } else if (g_Status.hpMax >= (arg0->unk8 * 0x14)) {
            arg0->unk4 = 3;
        } else {
            arg0->unk4 = 2;
        }
    }
    if (g_Status.hp <= arg0->unk8) {
        g_Status.hp = 0;
        return true;
    } else {
        g_Status.hp -= arg0->unk8;
        return false;
    }
}

s32 func_800FD664(s32 arg0) { return g_StageId & 0x20 ? arg0 << 1 : arg0; }

u8 GetEquipItemCategory(s32 equipId) {
    return D_800A4B04[g_Status.equipment[equipId]].itemCategory;
}
