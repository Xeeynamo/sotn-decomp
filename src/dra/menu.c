#include "dra.h"
#include "dra_bss.h"
#include "menu.h"
#include "sfx.h"

typedef struct EquipMenuHelper {
    s32 equipTypeFilter;
    s32 index;
    s32 isAccessory;
} EquipMenuHelper;

// Struct for table of values to intitialize MenuContext structs
typedef struct {
    /* 0x00 */ s16 cursorX;
    /* 0x02 */ s16 cursorY;
    /* 0x04 */ s16 cursorW;
    /* 0x06 */ s16 cursorH;
    /* 0x08 */ s16 otIdx;
    /* 0x0A */ s16 padding;
} MenuContextInit; // size = 0x1C

#define CH(x) ((x) - 0x20)

#if defined(VERSION_US)
#define ShowText(str, id) func_800F99B8(str, id, 0);
#elif defined(VERSION_HD)
#define ShowText(str, id) func_800F98AC(str, id);
#endif

const char* D_800A2D48[] = {
#if defined(VERSION_US)
    "？？？？？",
    "Button set−up",
    "Select front／back of reversible cloak",
    "Custom cloak settings",
    "Window color settings",
    "Sound settings",
    "Time from game start",
#elif defined(VERSION_HD)
    "？？？？？",
    "ボタン割当変更",
    "リバーシブルマントの表\裏の選択",
    "オーダーメイドのカラーの設定",
    "ウィンドウカラーの設定",
    "サウンドの設定",
    "ゲームスタートからの経過時間",
#endif
};

#ifndef SOTN_STR
// Similar to `_S`, a second lookup table is used for some menus based on BIOS
// fonts in a custom table. This is only relevant to the strings below.
// e.g. "\x02\x03\x04\xFF" -> _S2("ＤＥＦ")
#define _S2(x) (x)

// Like `_S2`, but uses a lookup table unique to the HD version of the game
#define _S2_HD(x) (x)
#endif

#if defined(VERSION_US)
static const char* D_800A2D64[] = {
    "ＡＴＤＥＦ",
};

static const char* D_800A2D68[] = {
#if !defined(VERSION_PC)
    _S2("ＡＴＴ"),
    _S2("ＤＥＦ"),
#else // TODO cheap fix as func_800F66BC does not support unicode
    "\x00\x01\x01\xFF",
    "\x02\x03\x04\xFF",
#endif
};
#elif defined(VERSION_HD)
static const char* D_800A2D10[] = {
    "装備技システム短剣必殺使攻撃力防",
};

static const char* D_800A2D14[] = {
    "御魔導器拳こ一覧棒両手食物爆弾盾",
};

static const char* D_800A2D18[] = {
    "投射薬ん右左武兜鎧マントその他い",
};

static const char* D_800A2D68[] = {
    _S2_HD("攻撃力"),     //
    _S2_HD("防御力"),     // D_800A83AC
    _S2_HD("必殺技一覧"), // D_800A2D24
    _S2_HD("装備"),       // g_MenuStr[93]
    _S2_HD("必殺技"),     // g_MenuStr[96]
    _S2_HD("魔導器"),     // g_MenuStr[92]
    _S2_HD("システム"),   // g_MenuStr[94]
    _S2_HD("短剣"),       // g_MenuStr[99]
    _S2_HD("剣"),         //
    _S2_HD("投剣"),       //
    _S2_HD("拳"),         //
    _S2_HD("こん棒"),     //
    _S2_HD("両手剣"),     //
    _S2_HD("食物"),       //
    _S2_HD("爆弾"),       //
    _S2_HD("投射"),       //
    _S2_HD("盾"),         //
    _S2_HD("薬"),         //
    _S2_HD("右手武器"),   //
    _S2_HD("左手武器"),   //
    _S2_HD("兜"),         //
    _S2_HD("鎧"),         //
    _S2_HD("マント"),     //
    _S2_HD("その他"),     //
    _S2_HD("その他"),     //
    _S2_HD("使い魔"),     // g_MenuStr[95]
    _S2_HD("使い魔一覧"), // D_800A2D84
};
#endif

u8 g_ChButtons[] = {0xEA, 0xE8, 0xE9, 0xEB, 0x32, 0x2C,
                    0x32, 0x2C, 0x12, 0x11, 0x11, 0x12};
u8 g_ChRgb[] = {MENUCHAR('R'), MENUCHAR('G'), MENUCHAR('B')};
u8 D_800A2D80[] = {0x00, 0x20, 0x30, 0x40, 0x50, 0x60, 0x69, 0x70,
                   0x75, 0x78, 0x7A, 0x7C, 0x7D, 0x7E, 0x7F, 0x80};

#if defined(VERSION_US)
RECT D_800A2D90 = {0x180, 0x30, 0x80, 0x80};
#endif

EquipMenuHelper g_EquipMenuHelper[] = {
    {EQUIP_HAND, 0, false},     // LEFT_HAND_SLOT
    {EQUIP_HAND, 0, false},     // RIGHT_HAND_SLOT
    {EQUIP_HEAD, 0, true},      // HEAD_SLOT
    {EQUIP_ARMOR, 1, true},     // ARMOR_SLOT
    {EQUIP_CAPE, 2, true},      // CAPE_SLOT
    {EQUIP_ACCESSORY, 3, true}, // ACCESSORY_1_SLOT
    {EQUIP_ACCESSORY, 3, true}, // ACCESSORY_2_SLOT
};

s32 D_800A2DEC[] = {
    0x1A, 0x00, 0x30, 0x39, 0x39,
};

MenuContextInit g_MenuInit[NUM_MENU] = {
#if defined(VERSION_US)
    {158, 100, 76, 80, 0x40},  // MENU_DG_MAIN
    {0, 24, 360, 200, 0x10},   // MENU_DG_BG
    {0, 24, 360, 97, 0x20},    // MENU_DG_EQUIP_OVERVIEW
    {0, 120, 360, 74, 0x20},   // MENU_DG_EQUIP_SELECTOR
    {0, 193, 360, 31, 0x40},   // MENU_DG_INFO_BAR
    {0, 24, 360, 170, 0x20},   // MENU_DG_RELICS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SPELLS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SETTINGS
    {168, 120, 144, 64, 0x30}, // MENU_DG_CLOAK_COLOR
    {148, 44, 200, 112, 0x30}, // MENU_DG_CFG_BUTTONS
    {172, 44, 65, 32, 0x30},   // MENU_DG_CLOAK_LINING
    {172, 112, 57, 32, 0x30},  // MENU_DG_CFG_SOUND
    {172, 76, 124, 40, 0x30},  // MENU_DG_WINDOW_COLORS
    {12, 32, 340, 153, 0x30},  // MENU_DG_TIME_ATTACK
    {276, 32, 77, 183, 0x50},  // MENU_DG_EQUIP_SORT
    {0, 24, 360, 200, 0x18},   // MENU_DG_FAMILIARS
#elif defined(VERSION_HD)
    {172, 100, 48, 80, 0x40},  // MENU_DG_MAIN
    {0, 24, 360, 200, 0x10},   // MENU_DG_BG
    {0, 24, 360, 97, 0x20},    // MENU_DG_EQUIP_OVERVIEW
    {0, 120, 360, 74, 0x20},   // MENU_DG_EQUIP_SELECTOR
    {0, 193, 360, 31, 0x40},   // MENU_DG_INFO_BAR
    {0, 24, 360, 170, 0x20},   // MENU_DG_RELICS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SPELLS
    {0, 24, 360, 170, 0x20},   // MENU_DG_SETTINGS
    {168, 120, 144, 64, 0x30}, // MENU_DG_CLOAK_COLOR
    {124, 44, 160, 112, 0x30}, // MENU_DG_CFG_BUTTONS
    {124, 44, 44, 32, 0x30},   // MENU_DG_CLOAK_LINING
    {124, 112, 41, 32, 0x30},  // MENU_DG_CFG_SOUND
    {124, 76, 124, 40, 0x30},  // MENU_DG_WINDOW_COLORS
    {112, 32, 240, 153, 0x30}, // MENU_DG_TIME_ATTACK
    {296, 32, 45, 183, 0x50},  // MENU_DG_EQUIP_SORT
    {0, 24, 360, 200, 0x18},   // MENU_DG_FAMILIARS
#endif
};

// BSS
extern EquipKind D_801375CC;
extern s32 D_801375D0;
extern s32 D_801375D4;
extern s32* D_801375D8;
extern s32 D_801375DC;
extern s32 D_801375E0[NUM_FAMILIARS + 1];
extern s32 g_IsCloakLiningUnlocked;
extern s32 g_IsCloakColorUnlocked;
extern s32 D_80137608;
extern s32 g_IsSelectingEquipment;
extern s32 g_EquipmentCursor;
extern s32 D_80137614;
extern s32 g_EquipOrderType;
extern MenuData g_MenuData;
extern s32 D_801377FC[NUM_MENU];
extern s32 D_8013783C;
extern s32 D_80137840;
extern s32 D_80137844[1];
extern s32 D_80137848[1];
#if defined(VERSION_US)
extern s32 D_8013784C;
#endif
extern s16 g_RelicMenuFadeTimer;
extern s32 g_TimeAttackEntryTimes[NUM_TIMEATTACK_EVENTS];
extern s32 c_strTimeAttackEntry[NUM_TIMEATTACK_EVENTS];
extern s32 g_NewAttackRightHand;
extern s32 g_NewAttackLeftHand;
extern s32 g_NewDefenseEquip;
extern s32 g_NewPlayerStatsTotal[];
extern s32 D_80137948;
extern s8* D_8013794C; // Pointer to texture pattern
extern s32 D_80137950;
extern s32 D_80137954;
extern s32 D_80137958;
extern s32 g_ServantPrevious;

u16* func_80106A28(u32 arg0, u16 kind);

bool CheckIfAllButtonsAreAssigned(void) {
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
        g_Settings.buttonMask[i] = g_ButtonMask[g_Settings.buttonConfig[i]];
    }

    var_a1 = 0;
    buttonConfig = g_Settings.buttonConfig;
    for (i = 0; i < 8; i++) {
        var_a1 |= 1 << *buttonConfig++;
    }

    return var_a1 == 0xFF;
}

bool IsAlucart(void) {
    if (CheckEquipmentItemCount(ITEM_ALUCART_SWORD, EQUIP_HAND) &&
        CheckEquipmentItemCount(ITEM_ALUCART_SHIELD, EQUIP_HAND) &&
        CheckEquipmentItemCount(ITEM_ALUCART_MAIL, EQUIP_ARMOR))
        return true;
    return false;
}

void func_800F4994(void) {
    s32* statsPtr = &g_Status.statsEquip;
    s32 correctStonesEquipped;
    s32 statBonus;
    u32 hourOfDay;
    s32 i, j;

    for (i = 0; i < 4; i++, statsPtr++) {
        *statsPtr = 0;
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
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    } else {
        // Moonstone check
        correctStonesEquipped =
            CheckEquipmentItemCount(ITEM_MOONSTONE, EQUIP_ACCESSORY);
        statsPtr = &g_Status.statsEquip;
        for (i = 0; i < 4; i++, statsPtr++) {
            *statsPtr += correctStonesEquipped * 5;
        }
    }

    if (D_80139828[4]) {
        g_Status.statsEquip[STAT_STR] += 20;
    }
    if (D_80139828[3]) {
        g_Status.statsEquip[STAT_INT] += 20;
    }
    if (D_80139828[2]) {
        g_Status.statsEquip[STAT_LCK] += 20;
    }
    if (g_Status.relics[RELIC_RIB_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_CON] += 10;
    }
    if (g_Status.relics[RELIC_EYE_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_LCK] += 10;
    }
    if (g_Status.relics[RELIC_TOOTH_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_STR] += 10;
    }
    if (g_Status.relics[RELIC_RING_OF_VLAD] & 2) {
        g_Status.statsEquip[STAT_INT] += 10;
    }
    if (IsAlucart() != false) {
        g_Status.statsEquip[STAT_LCK] += 30;
    }

    for (i = 0; i < 4; i++) {
        if (g_Status.statsEquip[i] > 99) {
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

    if (g_EquipDefs[equipId].itemCategory == ITEM_FOOD ||
        g_EquipDefs[equipId].itemCategory == ITEM_MEDICINE ||
        (g_EquipDefs[equipId].itemCategory == ITEM_SHIELD &&
         g_EquipDefs[equipId].attack == 1)) {
        return 0;
    }

    if (equipId == ITEM_ALUCARD_SHIELD) {
        return 0;
    }

    equipmentAttackBonus = 0;

    for (i = 0; i < 5; i++) {
        equipmentAttackBonus +=
            (u16)g_AccessoryDefs[g_Status.equipment[2 + i]].attBonus;
    }

    totalAttack = g_EquipDefs[equipId].attack;
    strengthStat = g_Status.statsTotal[0];

    if (strengthStat >= totalAttack) {
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
    if (equipId == 4 && g_EquipDefs[otherEquipId].itemCategory == ITEM_SHIELD) {
        totalAttack += 5;
    }
    if (equipId == ITEM_SWORD_FAMILIAR) {
        totalAttack += g_Status.statsFamiliars[FAM_STATS_SWORD].level;
    }
    if (D_80139828[1]) {
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
        totalDefense += g_EquipDefs[thisHandItem].defense;
        // If this hand is shield rod and other hand is a shield, defense bonus
        // of 2.
        if ((thisHandItem == 4) &&
            g_EquipDefs[g_Status.equipment[1 - i]].itemCategory == 9) {
            totalDefense += 2;
        }
    }
    // Iterate over accessories worn by player
    for (i = 0; i < 5; i++) {
        acc = &g_AccessoryDefs[g_Status.equipment[i + 2]];
        totalDefense += acc->defBonus;
        g_Status.defenseElement |= acc->unk10;
        g_Status.D_80097C2A |= acc->unk12;
        g_Status.D_80097C2C |= acc->unk14;
        g_Status.D_80097C2E |= acc->unk16;
    }

    if (CheckEquipmentItemCount(ITEM_MIRROR_CUIRASS, EQUIP_HAND) != 0) {
        g_Status.D_80097C2C |= 0x200;
    }
    if (CheckEquipmentItemCount(ITEM_ALUCARD_MAIL, EQUIP_HAND) != 0) {
        g_Status.D_80097C2C |= 0x8000;
    }
    if (g_Status.relics[RELIC_HEART_OF_VLAD] & 2) {
        g_Status.D_80097C2C |= 0x100;
    }
    if (D_80139828[5]) {
        g_Status.D_80097C2A |= 0x8000;
    }
    if (D_80139828[6]) {
        g_Status.D_80097C2A |= 0x2000;
    }
    if (D_80139828[7]) {
        g_Status.D_80097C2A |= 0x4000;
    }
    if (D_80139828[8]) {
        g_Status.D_80097C2A |= 0x100;
    }
    if (D_80139828[9]) {
        g_Status.D_80097C2A |= 0x1000;
    }
    if (D_80139828[10]) {
#if defined(VERSION_US)
        g_Status.D_80097C2C |= 0x200;
#elif defined(VERSION_HD)
        g_Status.D_80097C2A |= 0x200;
#endif
    }
    if (D_80139828[11]) {
        g_Status.D_80097C2A |= 0x800;
    }

    totalDefense += (SquareRoot0(g_Status.statsTotal[STAT_CON]) - 2);

    if (CheckEquipmentItemCount(ITEM_WALK_ARMOR, EQUIP_ARMOR) != 0) {
        totalDefense += g_RoomCount / 60;
    }

    if (D_80139828[0]) {
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

void MenuDrawImg(MenuContext* menu, s32 x, s32 y, s32 w, u32 h, s32 u, s32 v,
                 s32 clut, s32 tpage, bool disableTexShade, s32 c) {
    SPRT* sp;
    s32 otIdx;
    OT_TYPE* ot;

    ot = g_CurrentBuffer->ot;
    sp = &g_CurrentBuffer->sprite[g_GpuUsage.sp];
#if defined(VERSION_US)
    if (D_8013784C == 1) {
        clut = 0x15E;
    }
    if (D_8013784C == 2) {
        clut = 0x15D;
    }
#endif
    if (menu == NULL) {
        otIdx = 0x1FF;
    } else {
        otIdx = menu->otIdx + 2;
    }
    SetSemiTrans(sp, 0);
    SetShadeTex(sp, disableTexShade);
    sp->x0 = x;
    sp->y0 = y;
    sp->w = w;
    sp->h = h;
    sp->u0 = u;
    sp->v0 = v;
    if (menu == NULL || ScissorSprite(sp, menu) == false) {
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

void func_800F5AE4(MenuContext* menu) {
    s32 i, x;

    for (i = 0, x = 72; i < 3; i++, x += 128)
        MenuDrawImg(menu, x, 201, 128, 16, (i & 1) << 7,
                    func_800F548C(2) & 0xFF, 0x1A1, (i / 2) + 6, 1, 0);
}
void MenuDrawSprite(
    MenuContext* context, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v,
    s32 clut, s32 tpage, s32 isAlpha, s32 colorIntensity, s32 fade) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    POLY_GT4* poly = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4];
    s32 otIdx = context->otIdx + 2;
    u32 polyColorIntensity;
    s32 temp_polyx0;

    if (context == &g_MenuData.menus[MENU_DG_BG]) {
        otIdx--;
    }

    poly->code &= 0xFD;

    if (isAlpha) {
        poly->code |= 1;
    } else {
        poly->code &= 0xFC;
    }

    SetTexturedPrimRect(poly, x, y, width, height, u, v);

    if (ScissorPolyGT4(poly, context) == false) {
        poly->tpage = tpage;
        poly->clut = g_ClutIds[clut];
        func_80107250(poly, colorIntensity);
        if (fade == 1) {
            polyColorIntensity = (poly->y2 - poly->y0) * 4;
            func_801071CC(poly, polyColorIntensity, 0);
            func_801071CC(poly, polyColorIntensity, 1);
        }
        if (fade == 2) {
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
void MenuDrawRect(MenuContext* context, s32 posX, s32 posY, s32 width,
                  s32 height, s32 r, s32 g, s32 b) {
    OT_TYPE* ot = g_CurrentBuffer->ot;
    POLY_G4* poly = &g_CurrentBuffer->polyG4[g_GpuUsage.g4];
    s32 otIdx = context->otIdx + 1;
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
        if (g_Timer & 0x20) {
            r = (g_Timer & 0x1F) + 0x60;
        } else {
            r = 0x7F - (g_Timer & 0x1F);
        }
    } else {
        r = 0x80;
    }
    MenuDrawRect(context, x, y + (cursorIdx * (h + yGap)), w, h, r, 0, 0);
}

void DrawRelicsMenu(MenuContext* ctx) {
    s32 ctx_h;
    s32 switchFadeLevel;
    s32 spriteY;
    s32 spriteX;
    s32 var_a0;
    s32 i;
    s32 offsetY;
    s32 baseY;
    s32 var_s3;
    s32 u_OnOff;
    u8* relic;

    ctx_h = ctx->h;
    relic = &g_Status.relics[RELIC_SOUL_OF_BAT];
#if defined(VERSION_US)
    for (i = 0, var_s3 = 0; i < 30; i++, var_s3++, relic++) {
        // This if-statement only exists in US. This is to skip over
        // rendering the JP-exclusive familiars (sprite and nosedevil)
        if (i == 23) {
            i = 25;
            relic += 2;
        }

// Declare this as the var to use for the two comparisons later
#define INDEXER var_s3
#else
    for (i = 0; i < 30; i++, relic++) {
#define INDEXER i
#endif
        offsetY = (INDEXER / 2) * 0x13;
        baseY = ctx_h + 0x22;
        spriteY = offsetY + baseY;
        spriteX = (i & 1) * 0xB0;
        if (*relic & RELIC_FLAG_FOUND) {
            if (spriteY < 0) {
                continue;
            }
            if (spriteY >= 193) {
                continue;
            }
            if (!(i & 2)) {
                if (i < 0) {
                    var_a0 = i + 3;
                } else {
                    var_a0 = i;
                }
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C((var_a0 >> 2) - 0x80), 0x1A1, 6, 1, 0, 0);
            } else {
                if (i < 0) {
                    var_a0 = i + 3;
                } else {
                    var_a0 = i;
                }
                MenuDrawSprite(
                    ctx, spriteX + 0x38, spriteY, 0x78, 0x10, (i & 1) * 0x78,
                    func_800F548C((var_a0 >> 2) + 3), 0x1A1, 7, 1, 0, 0);
            }
        }
        switchFadeLevel = 0;
        // Determine the U value for the texture to use for the switch
        u_OnOff = -(!(*relic & RELIC_FLAG_ACTIVE)) & 0x30;
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
        MenuDrawSprite(ctx, spriteX | 8, spriteY, 0x2F, 0xF, u_OnOff, 0x70,
                       switchFadeLevel + 0x1C8, 0x1F,
                       INDEXER == g_MenuNavigation.cursorRelic, 0x40, 0);
    }
    spriteY = ctx_h + ((g_MenuNavigation.cursorRelic / 2) * 0x13);
    MenuDrawRect(ctx, ((g_MenuNavigation.cursorRelic & 1) * 0xB0) | 8,
                 spriteY + 0x21, 0xA8, 0x12, 0x60, 0, 0);
#undef INDEXER
}

void MenuDrawAlucardPortrait(MenuContext* ctx) {
    MenuDrawSprite(ctx, 0x10, 0x24, 0x40, 0x40, 0, 0x80, 0x150, 0x9C, 1, 0, 0);
    MenuDrawSprite(ctx, 0x10, 0x64, 0x40, 0x20, 0, 0xC0, 0x150, 0x9C, 0, 0, 1);
}

// Equivalent of floor(number * .75)
// Cloak color components are 5 bit.
// Examples: 31->23, 15->11
s32 DarkenCloakColor(s32 color) { return color * 3 / 4; }

// Creates light and dark versions of cloak colors in BGR555 format
void ApplyJosephsCloakPalette(void) {
    const int LiningDark = 0;
    const int LiningLight = 1;
    const int ExteriorDark = 2;
    const int ExteriorLight = 3;

    g_JosephsCloakColors[LiningDark] =
        DarkenCloakColor(g_Settings.cloakColors[3]) +
        ((DarkenCloakColor(g_Settings.cloakColors[4]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[5]) << 0xA);
    g_JosephsCloakColors[LiningLight] =
        (g_Settings.cloakColors[3] +
         ((g_Settings.cloakColors[4] << 5) - 0x8000)) +
        ((u32)g_Settings.cloakColors[5] << 0xA);
    g_JosephsCloakColors[ExteriorDark] =
        DarkenCloakColor(g_Settings.cloakColors[0]) +
        ((DarkenCloakColor(g_Settings.cloakColors[1]) << 5) - 0x8000) +
        (DarkenCloakColor(g_Settings.cloakColors[2]) << 0xA);
    g_JosephsCloakColors[ExteriorLight] =
        g_Settings.cloakColors[0] +
        ((g_Settings.cloakColors[1] << 5) - 0x8000) +
        ((u32)g_Settings.cloakColors[2] << 0xA);
}

void MenuDrawAlucardCloakPreview(MenuContext* ctx) {
    MenuDrawSprite(ctx, 0xC0, 0x80, 0x20, 0x40, 0, 0xB0, 0x100, 7, 1, 0, 2);
    MenuDrawSprite(ctx, 0x100, 0x80, 0x40, 0x40, 0x80, 0xB0, 0x100, 7, 1, 0, 0);
}

void func_800F6508(MenuContext* context, s32 x, s32 y) {
    s32 yellow;

    if (g_Timer & 0x10) {
        yellow = ((g_Timer & 0xF) * 2) + 0x60;
    } else {
        yellow = 0x7F - (g_Timer & 0xF);
    }
    MenuDrawRect(context, x, y, 0x70, 0xB, yellow, yellow, 0);
}

// Draw main menu cursor
void func_800F6568(MenuContext* context) {
    s32 height;
    s32 r;

    height = context->cursorH / 5;
    if (g_Timer & 0x20) {
        r = (g_Timer & 0x1F) + 0x40;
    } else {
        r = 0x5F - (g_Timer & 0x1F);
    }
    MenuDrawRect(context, context->cursorX,
                 context->cursorY + (height * g_MenuNavigation.cursorMain),
                 context->cursorW, height, r, 0, 0);
}

// Draw equip menu cursor
void func_800F6618(s32 menuDialogue, s32 bColorMode) {
    s32 r;
    MenuContext* context = &g_MenuData.menus[menuDialogue];

    if (bColorMode != 0) {
        r = 0x80;
    } else {
        if (g_Timer & 0x20) {
            r = (g_Timer & 0x1F) + 0x40;
        } else {
            r = 0x5F - (g_Timer & 0x1F);
        }
    }
    MenuDrawRect(context, 0x70, g_MenuNavigation.cursorEquip * 13 + 0x1C, 0x71,
                 0xB, r, 0, 0);
}

void func_800F66BC(
    const char* str, s32 x, s32 y, MenuContext* menu, bool disableTexShade) {
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
    MenuDrawImg(menu, x, y, ChWidth, ChHeight, (ch & 0xF) * ChWidth,
                temp * ChHeight, 0x1A1, unk + 6, disableTexShade, 0x40);
    x += ChWidth;
    goto loop_1;
}

void MenuDrawChar(u8 ch, int x, int y, MenuContext* menu) {
    MenuDrawImg(menu, x, y, 8, 8, (ch & 0xF) * 8, (u32)(ch & 0xF0) >> 1, 0x196,
                0x1E, 1, 0);
}

void MenuDrawStr(const u8* str, s32 x, s32 y, MenuContext* context) {
    const int ChWidth = 8;
    const int ChHeight = 8;
    u8 ch;
    s32 xcopy;
    s32 ycopy;

#if defined(VERSION_US)
    s32 s4 = D_8013784C; // FAKE? not used in HD
#endif

    D_80137614 = 0;
    while (1) {
        xcopy = x;
        ycopy = y;
        ch = *str++;
#if defined(VERSION_US)
        if (*str == 0xC0 && *(str + 1) == 0xD2) {
            D_8013784C = 2;
            str += 2;
        } else {
            D_8013784C = s4;
        }
#endif

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
        MenuDrawChar(ch, xcopy, ycopy, context);
        x += ChWidth;
    }
    D_80137614 = 1;
    func_800F53D4(0x1E, context->otIdx + 2);
}

void MenuDrawInt(s32 digit, s32 x, s32 y, MenuContext* context) {
    do {
        MenuDrawChar((digit % 10) + 16, x, y, context);
        digit /= 10;
        x += -8;
    } while (digit != 0);
}

// Draw a number with a limit of N digits
void MenuDrawTime(s32 number, s32 x, s32 y, MenuContext* context, s32 digits) {
    do {
        MenuDrawChar(((number % 10) + 0x10), x, y, context);
        number /= 10;
        x -= 8;
        digits -= 1;
    } while (digits != 0);
}

void func_800F6A48(void) {
    func_800EA538(6);
    func_800EA5E4(0x411);
}

void MenuJosephsCloakDraw(MenuContext* context) {
    s32 row1Ypos;
    s32 row2Ypos;
    s32 i;
    u8* chsRgb;
    s32 x_RGB;
    const char** exteriorInterior;

    MenuContext* ctx = &g_MenuData.menus[7];
#if defined(VERSION_US)
    s32 x_Start = 0xB0;
    s32 number_spacing = 0x28;
    const s32 xRGBVal = 0xF8;
#elif defined(VERSION_HD)
    s32 x_Start = 0x80;
    const s32 number_spacing = 0;
    const s32 xRGBVal = 0xA0;
#endif
    i = 0;
    exteriorInterior = &g_MenuStr[20];
    x_RGB = xRGBVal;
    chsRgb = g_ChRgb;
    row2Ypos = 0x4C;
    row1Ypos = 0x28;
    // 3 iterations, each iteration does Exterior and Lining for one letter
    for (; i < 3; row1Ypos += 0xC, chsRgb++, row2Ypos += 0xC, i++) {
        // Write "Exterior"
        MenuDrawStr(exteriorInterior[0], x_Start, row1Ypos, ctx);
        // Write R, G, or B
        MenuDrawChar(*chsRgb, x_RGB, row1Ypos, ctx);
        // Write "Lining"
        MenuDrawStr(exteriorInterior[1], x_Start, row2Ypos, ctx);
        // Write R, G, or B
        MenuDrawChar(*chsRgb, x_RGB, row2Ypos, ctx);
    }
    for (i = 0; i < 6; i++) {
        MenuDrawInt(g_Settings.cloakColors[i], x_Start + number_spacing + 0x48,
                    0x28 + 0xC * i, ctx);
    }
    func_800F5E68(ctx, g_MenuNavigation.cursorCloak, x_Start - 2, 0x26,
                  number_spacing + 0x58, 0xC, 0, 1);
    ApplyJosephsCloakPalette();
    func_800F6A48();
}

void MenuWindowColorsDraw(MenuContext* context) {
#if defined(VERSION_HD)
    s32 x = 128;
#else
    s32 x = 176;
#endif
    s32 y;
    s32 i;

    for (i = 0; i < LEN(g_ChRgb); i++) {
        MenuDrawChar(g_ChRgb[i], x + 32, (i * 12) + 80, context);
        MenuDrawInt(g_Settings.windowColors[i], x + 72, 80 + i * 12, context);
    }
    func_800F5E68(
        context, g_MenuNavigation.cursorWindowColors, x - 2, 78, 120, 12, 0, 1);
}

void SortTimeAttackEntries(void) {
    s32 i;
    s32 isLooping;
    s32 swapTime;
    s32 swapName;

    // All the uninitialised time attack timers needs to be set to a large
    // value, so their record can be beat.
    for (i = 0; i < NUM_TIMEATTACK_EVENTS; i++) {
        g_TimeAttackEntryTimes[i] =
            TimeAttackController(i, TIMEATTACK_GET_RECORD);
        if (g_TimeAttackEntryTimes[i] == 0) {
            g_TimeAttackEntryTimes[i] = 1000000;
        }
        c_strTimeAttackEntry[i] = i;
    }

    // Ensure the time attacks are sequentially ordered by their timer
    do {
        isLooping = false;
        for (i = 0; i < NUM_TIMEATTACK_EVENTS - 1; i++) {
            swapTime = g_TimeAttackEntryTimes[i];
            if (g_TimeAttackEntryTimes[i + 1] < g_TimeAttackEntryTimes[i]) {
                g_TimeAttackEntryTimes[i] = g_TimeAttackEntryTimes[i + 1];
                g_TimeAttackEntryTimes[i + 1] = swapTime;
                swapName = c_strTimeAttackEntry[i];
                c_strTimeAttackEntry[i] = c_strTimeAttackEntry[i + 1];
                c_strTimeAttackEntry[i + 1] = swapName;
                isLooping++;
            }
        }
    } while (isLooping);
}

void MenuTimeAttackDraw(MenuContext* ctx) {
    s16 padX;
    s16 cursorX;
    s32 cursorY;
    s32 entryIdx;
    s32 offsetY;
    s32 i;
    s32 hours;
    s32 seconds;

    for (i = 0, offsetY = 8; i < 12; i++, offsetY += 12) {
        cursorX = ctx->cursorX;
        entryIdx = i + g_MenuNavigation.cursorTimeAttack;
        cursorY = ctx->cursorY + offsetY;
        MenuDrawInt(entryIdx + 1, cursorX + 16, cursorY, ctx);
        seconds = g_TimeAttackEntryTimes[entryIdx];
        if (seconds == 1000000) {
            MenuDrawStr(g_MenuStr[41], cursorX + 29, cursorY, ctx);
        } else {
            MenuDrawStr(g_MenuStr[53 + c_strTimeAttackEntry[entryIdx]],
                        cursorX + 29, cursorY, ctx);
            hours = seconds / 10000;
#if defined(VERSION_HD)
            padX = -100;
#elif defined(VERSION_US)
            padX = 0;
#endif
            MenuDrawInt(hours, cursorX + 276 + padX, cursorY, ctx);
            MenuDrawChar(0x1A, cursorX + 284 + padX, cursorY, ctx);
            MenuDrawTime((seconds / 100) - (hours * 100), cursorX + 300 + padX,
                         cursorY, ctx, 2);
            MenuDrawChar(0x1A, cursorX + 308 + padX, cursorY, ctx);
            MenuDrawTime(seconds % 100, cursorX + 324 + padX, cursorY, ctx, 2);
        }
    }
}

void MenuButtonConfigDraw(MenuContext* ctx) {
    s32 i;
    s32 x;
    s32 buttonId;
    s32 btn1_x;
    s32 btn2_x;
#if defined(VERSION_HD)
    const s32 InitCursorX = 0x80;
    const s32 W = 0x28;
#define XVAR cursorX
#elif defined(VERSION_US)
    const s32 InitCursorX = 0x98;
    const s32 W = 0x54;
#define XVAR x
#endif
    s32 cursorX = InitCursorX;

    for (i = 0, x = 0xC0; i < 7; i++) {
        MenuDrawStr(g_MenuStr[22 + i], cursorX, 0x30 + (i * 0x10), ctx);
        buttonId = g_Settings.buttonConfig[i];
        btn1_x = (buttonId * 12) + 0x30;
        MenuDrawChar(
            g_ChButtons[buttonId], XVAR + btn1_x, 0x30 + (i * 0x10), ctx);
        if (buttonId >= 4) {
            btn2_x = btn1_x + 8;
            MenuDrawChar(g_ChButtons[4 + buttonId], XVAR + btn2_x,
                         0x30 + (i * 0x10), ctx);
        }
    }

    func_800F5E68(
        ctx, g_MenuNavigation.cursorButtons, cursorX - 2, 46, W, 12, 4, 1);
#undef XVAR
}

void MenuReverseCloakDraw(MenuContext* context) {
#if defined(VERSION_US)
    const int StrX = 176;
    const int ImgW = 64;
#elif defined(VERSION_HD)
    const int StrX = 128;
    const int ImgW = 40;
#endif

    MenuDrawStr(g_MenuStr[30], StrX, 48, context);
    MenuDrawStr(g_MenuStr[31], StrX, 64, context);
    func_800F5E68(context, g_Settings.isCloakLiningReversed, StrX - 2, 46, ImgW,
                  12, 4, 1);
}

void MenuSoundConfigDraw(MenuContext* context) {
#if defined(VERSION_US)
    const int ImgW = 53;
#elif defined(VERSION_HD)
    const int ImgW = 37;
#endif

    s16 cursorX = context->cursorX;
    s16 cursorY = context->cursorY;
    s32 subMenuX = cursorX + 4;
    MenuDrawStr(g_MenuStr[33], subMenuX, cursorY + 4, context);
    MenuDrawStr(g_MenuStr[34], subMenuX, cursorY + 0x14, context);
    func_800F5E68(context, g_Settings.isSoundMono, cursorX + 2, cursorY + 2,
                  ImgW, 12, 4, 1);
}

u8 StatChangeArrow(u16 arg0, u16 arg1) {
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

void MenuStatChangesDraw(void) {
    s32 xcoord;
    s32 ycoord;
    s32 i;
    MenuContext* ctx;
    s32 arrow;

    if ((g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk1C != 0) ||
        (D_80137948 == 0)) {
        return;
    }
    ctx = &g_MenuData.menus[MENU_DG_EQUIP_OVERVIEW];
    // Print the destination value for the square attack item
    MenuDrawInt(g_NewAttackRightHand, 0x154, 0x50, ctx);
    // Show arrow icon for increasing, decreasing, or staying the same
    arrow = StatChangeArrow(g_Status.attackHands[0], g_NewAttackRightHand);
    MenuDrawChar(arrow, 0x13C, 0x50, ctx);

    // Same but for the circle attack item
    MenuDrawInt(g_NewAttackLeftHand, 0x154, 0x5A, ctx);
    arrow = StatChangeArrow(g_Status.attackHands[1], g_NewAttackLeftHand);
    MenuDrawChar(arrow, 0x13C, 0x5A, ctx);
    // And repeat for defense.
    MenuDrawInt(g_NewDefenseEquip, 0x154, 0x6A, ctx);
    arrow = StatChangeArrow(g_Status.defenseEquip, g_NewDefenseEquip);
    MenuDrawChar(arrow, 0x13C, 0x6A, ctx);

    // Iterate through the 4 stats (STR CON INT LCK) doing the same.
    xcoord = 0x108;
    for (i = 0; i < 4; i++) {
        ycoord = 0x22 + i * 10;
        // Name of the stat
        MenuDrawStr(g_MenuStr[1 + i], xcoord, ycoord, ctx);
        // Current value for the stat
        MenuDrawInt(g_Status.statsBase[i] + g_Status.statsEquip[i],
                    xcoord + 0x2C, ycoord, ctx);
        // Indication of change
        arrow =
            StatChangeArrow((g_Status.statsBase[i] + g_Status.statsEquip[i]),
                            g_NewPlayerStatsTotal[i]);
        MenuDrawChar(arrow, xcoord + 0x34, ycoord, ctx);
        // Final value for the stat
        MenuDrawInt(g_NewPlayerStatsTotal[i], xcoord + 0x4C, ycoord, ctx);
    }
}

void MenuDrawStats(s32 menuDialogue) {
    MenuContext* ctx;
    s32 temp_s1;
    s32 temp_var;
    s32 x;
    s32 y;
    s32 i;
    s32 temp_y;
    s32 phi_a0_5;

    ctx = &g_MenuData.menus[menuDialogue];
    func_800F53A4();
    if (menuDialogue == MENU_DG_BG) {
        MenuDrawAlucardPortrait(ctx);
        MenuDrawStr(IsAlucart() ? g_MenuStr[42] : g_MenuStr[0], 128, 40, ctx);
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
        MenuDrawStr(g_MenuStr[i], 260, 68, ctx);
        MenuDrawStr(g_MenuStr[10], 240, 150, ctx);
        MenuDrawInt(g_RoomCount, 328, 150, ctx);
        MenuDrawStr(g_MenuStr[11], 240, 164, ctx);
        MenuDrawInt(g_Status.killCount, 328, 164, ctx);
        MenuDrawStr(g_MenuStr[9], 208, 192, ctx);
        MenuDrawInt(g_Status.timerHours, 264, 192, ctx);
        MenuDrawChar(CH(':'), 272, 192, ctx);
        MenuDrawTime(g_Status.timerMinutes, 288, 192, ctx, 2);
        MenuDrawChar(CH(':'), 296, 192, ctx);
        MenuDrawTime(g_Status.timerSeconds, 312, 192, ctx, 2);
    }

    if (ctx == &g_MenuData.menus[MENU_DG_BG]) {
        x = 248;
        y = 88;
    } else {
        x = 232;
        y = 80;
    }
    func_800F66BC(D_800A2D68[0], x, y, ctx, 1);

    temp_var = g_Settings.buttonConfig[0];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        MenuDrawChar(g_ChButtons[temp_s1], x + 44, y, ctx);
    } else {
        MenuDrawChar(g_ChButtons[temp_s1], x + 40, y, ctx);
        MenuDrawChar(g_ChButtons[4 + temp_s1], x + 48, y, ctx);
    }
    MenuDrawInt(g_Status.attackHands[0], x + 76, y, ctx);

    temp_var = g_Settings.buttonConfig[1];
    temp_s1 = temp_var;
    if (temp_s1 < 4) {
        MenuDrawChar(g_ChButtons[temp_s1], x + 44, y + 10, ctx);
    } else {
        MenuDrawChar(g_ChButtons[temp_s1], x + 40, y + 10, ctx);
        MenuDrawChar(g_ChButtons[4 + temp_s1], x + 48, y + 10, ctx);
    }

    MenuDrawInt(g_Status.attackHands[1], x + 76, y + 10, ctx);
#if defined(VERSION_US)
    func_800F66BC(D_800A2D68[1], x, y + 20, ctx, 1);
#elif defined(VERSION_HD)
    func_800F66BC(D_800A2D68[1], x, y + 20, ctx, 1);
#endif
    MenuDrawInt(g_Status.defenseEquip, x + 76, y + 26, ctx);
    if (ctx == (&g_MenuData.menus[MENU_DG_BG])) {
        x = 32;
        y = 120;
    } else {
#if defined(VERSION_US)
        MenuDrawStr(g_MenuStr[85 + g_MenuNavigation.cursorEquip], 8, 40, ctx);
#elif defined(VERSION_HD)
        func_800F66BC(
            D_800A2D68[g_MenuNavigation.cursorEquip + 0x12], 24, 40, ctx, true);
#endif
        x = 12;
        y = 70;
    }

    for (i = 0, temp_y = y; i < 4; temp_y += 12, i++) {
        s32* statsBase = &g_Status.statsBase[i];
        MenuDrawStr(g_MenuStr[1 + i], x, temp_y, ctx);
        MenuDrawInt(*statsBase, x + 44, temp_y, ctx);
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
    const u8* comboPointer;
#if defined(VERSION_US)
    s32 startXCoord = 176;
    MenuDrawStr(g_MenuStr[98], 104, 40, ctx);
#elif defined(VERSION_HD)
    const s32 startXCoord = 172;
    func_800F66BC(D_800A2D68[2], 136, 36, ctx, 1);
#endif
    for (i = 0; i < NUM_SPELLS; i++) {
        spell = g_Status.spells[i];
        if (!(spell & 0x80)) {
            continue;
        }
        spell ^= 0x80;
        comboPointer = g_SpellDefs[spell].combo;
        charNum = 0;
        yCoord = 64 + i * 16;
        // Count up how many characters are in the combo
        while (*comboPointer != 0) {
            comboPointer++;
            charNum++;
        }
        charNum--;
#if defined(VERSION_US)
        // These spells start with an up-arrow colored red.
        if ((spell == SPELL_TETRA_SPIRIT) || (spell == SPELL_SWORD_BROTHERS)) {
            charNum -= 2;
        }
#endif
        if (spell != SPELL_WING_SMASH) {
            MenuDrawStr(g_SpellDefs[spell].combo, startXCoord, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + (charNum * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[0];
            charNum++;
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
                charNum++;
                MenuDrawChar(g_ChButtons[4 + buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            }
            // This writes the word "or", because spells say '{Square} or
            // {Circle}'
            charNum++;
            MenuDrawChar(CH('o'), startXCoord + (charNum * 8), yCoord, ctx);
            charNum++;
            MenuDrawChar(CH('r'), startXCoord + (charNum * 8), yCoord, ctx);
            buttonCFG = g_Settings.buttonConfig[1];
            charNum++;
            if (buttonCFG < 4) {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            } else {
                MenuDrawChar(g_ChButtons[buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
                charNum++;
                MenuDrawChar(g_ChButtons[4 + buttonCFG],
                             startXCoord + (charNum * 8), yCoord, ctx);
            }
        } else {
            MenuDrawChar(CH('?'), startXCoord, yCoord, ctx);
            MenuDrawChar(CH('+'), startXCoord + 8, yCoord, ctx);
            MenuDrawStr(g_SpellDefs[6].combo, startXCoord + 16, yCoord, ctx);
            MenuDrawChar(
                CH('+'), startXCoord + 16 + (charNum * 8), yCoord, ctx);
            MenuDrawChar(
                CH('?'), startXCoord + 24 + (charNum * 8), yCoord, ctx);
        }
        MenuDrawStr(g_MenuStr[13], 292, yCoord, ctx);
        MenuDrawInt(g_SpellDefs[spell].mpUsage, 316, yCoord, ctx);
    }
    for (i = 0; i < 8; i++) {
        if (g_Status.spells[i] & 0x80) {
            MenuDrawImg(ctx, 0x1C, 0x3C + 0x10 * i, 0xF0, 0x10U, 0,
                        func_800F548C(-0x80 + i) & 0xFF, 0x1A1, 6, true, 0);
        }
    }
#if defined(VERSION_US)
    // The highlighted spell glows yellow, increasing and decreasing.
    if (g_Timer & 0x20) {
        colorIntensity = (g_Timer & 0x1F) + 0x60;
    } else {
        colorIntensity = 0x7F - (g_Timer & 0x1F);
    }
    // The colorIntensity gets passed to the MenuRect's R and G values, making
    // it a brighter or dimmer yellow.
    MenuDrawRect(ctx, 26, (g_MenuNavigation.cursorSpells * 0x10) + 0x3B, 300,
                 17, colorIntensity, colorIntensity, 0);
#elif defined(VERSION_HD)
    func_800F5E68(
        ctx, (g_MenuNavigation.cursorSpells), 0x1A, 0x3B, 0x12C, 0x11, -1, 1);
#endif
}

void MenuFamiliarsDraw(MenuContext* menu) {
    s32 i;
    s32 baseX;
    s32 x;
    s32 y;
    s32 strId;
    s32 new_var;

#if defined(VERSION_US)
    MenuDrawStr(g_MenuStr[97], 120, 40, menu);
#elif defined(VERSION_HD)
    func_800F66BC(D_800A2D68[26], 136, 36, menu, 1);
#endif
    for (i = 0; i < NUM_FAMILIARS; i++) {
        if (D_801375E0[i] == 0) {
            continue;
        }
        baseX = (i & 1) * 172;
        y = new_var = (i / 2) * 40;
        new_var = y + 68;
        x = baseX + 48;
        if (i == FAM_STATS_NOSE_DEMON) {
            x = baseX + 220;
        }
        strId = i + 46;
        MenuDrawStr(g_MenuStr[strId], x, y + 68, menu);
        strId = 43;
        if (i < FAM_STATS_YOUSEI) {
            if (1) {
                strId = 8;
            }
        }
        MenuDrawStr(g_MenuStr[strId], x + 56, y + 68, menu);
        MenuDrawInt(g_Status.statsFamiliars[i].level, x + 112, y + 68, menu);
        strId = 44;
        if (i < FAM_STATS_YOUSEI) {
            strId = 5;
        }
        MenuDrawStr(g_MenuStr[strId], x + 56, y + 84, menu);
        MenuDrawInt(
            g_Status.statsFamiliars[i].exp % 100, x + 112, y + 84, menu);
        switch (i) {
        case FAM_STATS_BAT:
            MenuDrawImg(menu, 16, 64, 24, 30, 104, 129, 0x1D2, 0x1E, 1, 0);
            break;
        case FAM_STATS_GHOST:
            MenuDrawImg(menu, 176, 64, 40, 30, 32, 161, 0x1D1, 0x1E, 1, 0);
            break;
        case FAM_STATS_FAERIE:
            MenuDrawImg(menu, 12, 104, 32, 30, 72, 129, 0x1D4, 0x1E, 1, 0);
            break;
        case FAM_STATS_DEMON:
            MenuDrawImg(menu, 180, 104, 32, 30, 0, 225, 0x1D6, 0x1E, 1, 0);
            break;
        case FAM_STATS_SWORD:
            MenuDrawImg(menu, 12, 144, 32, 54, 0, 129, 0x1D0, 0x1E, 1, 0);
            break;
        case FAM_STATS_YOUSEI:
            MenuDrawImg(menu, 176, 144, 40, 30, 32, 129, 0x1D3, 0x1E, 1, 0);
            break;
        case FAM_STATS_NOSE_DEMON:
            MenuDrawImg(menu, 180, 184, 32, 38, 0, 185, 0x1D5, 0x1E, 1, 0);
            break;
        }
    }
}

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

void MenuSystemDraw(MenuContext* ctx) {
#if defined(VERSION_US)
    const int Width = 128;
#else
    const int Width = 80;
#endif

    s32 strIdx;
    func_800F5E68(ctx, g_MenuNavigation.cursorSettings, 30, 46, Width, 12, 4,
                  g_MenuStep == 0x101);

    MenuDrawStr(g_MenuStr[16], 0x20, 0x30, ctx);

    strIdx = g_IsCloakLiningUnlocked ? 0x11 : 0x13;
    MenuDrawStr(g_MenuStr[strIdx], 32, 64, ctx);

    strIdx = g_IsCloakColorUnlocked ? 0x12 : 0x13;
    MenuDrawStr(g_MenuStr[strIdx], 32, 80, ctx);
    MenuDrawStr(g_MenuStr[35], 32, 96, ctx);
    MenuDrawStr(g_MenuStr[32], 32, 112, ctx);

    strIdx = g_IsTimeAttackUnlocked ? 0x24 : 0x13;
    MenuDrawStr(g_MenuStr[strIdx], 32, 128, ctx);
}

void func_800F84CC(void) {
    Primitive* prim;
    s32 i;
    s32 primIndex;

    for (i = 0; i < NUM_MENU; i++) {
        D_801377FC[i] = func_800EDD9C(PRIM_G4, 1);
        prim = &g_PrimBuf[D_801377FC[i]];
        prim->drawMode = DRAW_HIDE;
    }

    D_8013783C = func_800EDD9C(PRIM_GT4, 1);
    prim = &g_PrimBuf[D_8013783C];
    SetPrimRect(prim, 20, 195, 42, 28);
    prim->u0 = 113;
    prim->v0 = 177;
    prim->u1 = 127;
    prim->v1 = 177;
    prim->u2 = 113;
    prim->v2 = 191;
    prim->u3 = 127;
    prim->v3 = 191;
    prim->tpage = 0x1A;
    prim->clut = 0x1EF;
    prim->priority = 0x40;
    prim->drawMode = DRAW_MENU | DRAW_HIDE;

    D_80137840 = func_800EDD9C(PRIM_GT4, 2);
    prim = &g_PrimBuf[D_80137840];
    for (i = 0; prim; i++) {
        prim->x0 = prim->x2 = 7;
        prim->x1 = prim->x3 = 23;
        prim->v0 = prim->v1 = 48;
        prim->v2 = prim->v3 = 64;
        if (i == 0) {
            prim->y0 = prim->y1 = 124;
            prim->u0 = prim->u2 = 80;
        } else {
            prim->y0 = prim->y1 = 174;
            prim->u0 = prim->u2 = 96;
        }
        prim->y2 = prim->y3 = prim->y0 + 0x10;
        prim->u1 = prim->u3 = prim->u0 + 0x10;
        func_80107250(prim, 64);
        prim->tpage = 0x1A;
        prim->priority = 0x40;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }
}

void func_800F86E4(void) {
    s32 i;

    for (i = 0; i < NUM_MENU; i++) {
        FreePrimitives(D_801377FC[i]);
    }

    FreePrimitives(D_8013783C);
    FreePrimitives(D_80137840);
}

#if defined(VERSION_US)
void func_800F8754(MenuContext* menu, s32 x, s32 y) {
    if (D_801375DC == 0) {
        D_8013784C = 1;
    }

    MenuDrawStr(g_MenuStr[93], x + 14, y + 20, menu);
    if (D_801375E0[NUM_FAMILIARS] == 0) {
        D_8013784C = 1;
    } else {
        D_8013784C = 0;
    }

    MenuDrawStr(g_MenuStr[96], x + 2, y + 68, menu);
    D_8013784C = 0;
    MenuDrawStr(g_MenuStr[92], x + 18, y + 4, menu);
    MenuDrawStr(g_MenuStr[94], x + 14, y + 36, menu);
    MenuDrawStr(g_MenuStr[95], x + 14, y + 52, menu);
}
#elif defined(VERSION_HD)
void func_800F8754(MenuContext* menu, s32 x, s32 y) {
    func_800F66BC(D_800A2D68[3], x + 0xC, y, menu, true);
    func_800F66BC(D_800A2D68[4], x + 6, y + 0x10, menu, D_801375DC != 0);
    func_800F66BC(D_800A2D68[5], x + 6, y + 0x20, menu, true);
    func_800F66BC(D_800A2D68[6], x, y + 0x30, menu, true);
    func_800F66BC(
        D_800A2D68[25], x + 6, y + 0x40, menu, D_801375E0[NUM_FAMILIARS] != 0);
}
#endif

void MenuEquipSortDraw(MenuContext* context) {
#if defined(VERSION_US)
    const int TextY = 8;
    const int UnkX = 72;
#elif defined(VERSION_HD)
    const int TextY = 4;
    const int UnkX = 40;
#endif
    s32 i = 0;
#if defined(VERSION_US)
    const char** pStrEquipTypes = &g_MenuStr[99];
#elif defined(VERSION_HD)
    const char** pStrEquipTypes = &D_800A2D68[7];
#endif
    s32 y = TextY;

    for (; i < ITEM_END; i++) {
#if defined(VERSION_US)
        MenuDrawStr(pStrEquipTypes[g_Settings.equipOrderTypes[i]],
                    context->cursorX + 4, context->cursorY + y, context);
#elif defined(VERSION_HD)
        func_800F66BC(
            pStrEquipTypes[g_Settings.equipOrderTypes[i]], context->cursorX + 4,
            context->cursorY + y, context, true);
#endif
        y += 16;
    }
    func_800F5E68(context, g_EquipOrderType, context->cursorX + 2,
                  context->cursorY + 4, UnkX, 16, 0, true);
}

void func_800F892C(s32 index, s32 x, s32 y, MenuContext* menu) {
    MenuDrawImg(menu, x, y, 16, 16, (index & 7) * 16,
                ((index & 0xF8) * 2) | 0x80, index + 0x1D0, 0x1A, 1, 0);
}

void func_800F8990(MenuContext* ctx, s32 x, s32 y) {
    const s32 Cols = 2;
    const s32 Width = 168;
    const s32 Height = 12;

    u8* sp20;
    s32 itemsPerPage;
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

    sp20 = GetEquipOrder(D_801375CC);
    equipsAmount = GetEquipCount(D_801375CC);
    totalItemCount = func_800FD6C4(D_801375CC);
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

        strEquipName = GetEquipmentName(D_801375CC, equipId);
        if (D_801375CC == 0) {
            icon = g_EquipDefs[equipId].icon;
            palette = g_EquipDefs[equipId].iconPalette;
        } else {
            icon = g_AccessoryDefs[equipId].icon;
            palette = g_AccessoryDefs[equipId].iconPalette;
        }

        LoadEquipIcon(icon, palette, i);
        func_800F892C(i, myX - 16, myY - 4, ctx);
        MenuDrawStr(strEquipName, myX, myY, ctx);

        if (D_801375CC == 0 && equipId != 0 ||
            D_801375CC != 0 && equipId != 0x1A && equipId != 0 &&
                equipId != 0x30 && equipId != 0x39) {
            MenuDrawInt(equipsAmount[equipId], myX + 128, myY, ctx);
        }
    }

    if (g_IsSelectingEquipment) {
        func_800F6508(ctx, curX, curY);
    }
}

void MenuDrawLine(s32 x0, s32 y0, s32 x1, s32 y1, s32 isColorStatic) {
    s32 z;
    u8 color;

    OT_TYPE* ot = g_CurrentBuffer->ot;
    LINE_G2* line = &g_CurrentBuffer->lineG2[g_GpuUsage.line];

    if (isColorStatic) {
        z = g_MenuData.menus[isColorStatic - 1].otIdx + 4;
    } else {
        z = 0x80;
    }

    SetSemiTrans(line, 0);
    SetShadeTex(line, 1);

    if (g_Timer & 0x20) {
        color = g_Timer & 0x1F;
    } else {
        color = 0x1F - (g_Timer & 0x1F);
    }
    color *= 4;
    color -= 0x80;

    if (isColorStatic) {
        color = 0xFF;
    }

    line->r0 = color;
    line->g0 = color;
    line->b0 = color;
    line->r1 = color;
    line->g1 = color;
    line->b1 = color;
    line->x0 = x0;
    line->y0 = y0;
    line->x1 = x1;
    line->y1 = y1;
    AddPrim(&ot[z], line);
    g_GpuUsage.line++;
}

void DrawConsumableCount(s32 itemId, s32 hand, MenuContext* ctx) {
    u8 outstring[16];
    u8* str_idx;
    s32 displayCount;
    u8 equipCount;

    if (g_EquipDefs[itemId].isConsumable != 0) {
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
                // Neat trick, set this to 0 so following two steps draw
                // 00
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
        MenuDrawStr(&outstring, 224, (hand * 13) + 30, ctx);
    }
}

void MenuDraw(void) {
    u8 padding[32];
    s32 x;
    s32 y;
    Accessory* acc;
    Equipment* equip;
    MenuContext* menu;
    Primitive* prim;
    s16 swap;
    s32 ch;
    s32 cy;
    s32 cx;
    s32 cw;
    s16 r0;
    s16 g0;
    s16 b0;
    s16 r1;
    s16 g1;
    s16 b1;
    s32 var_a1;
    s32 cursorXMovement;
    s32 equipIndex;
    s32 flag;
    s32 i;
    s32 j;
    s32 new_var2;
    s32 stuff;
    s32 stuffed;

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
        new_var2 = -1;
        if (var_a1 == new_var2) {
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
            j = menu->unk1D; // FAKE?
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
            j = menu->unk1D; // FAKE?
            if (menu->unk1D == 16) {
                menu->unk1C = 0;
            } else {
                cursorXMovement =
                    cw / 2 * (128 - D_800A2D80[menu->unk1D]) / 128;
                cx += cursorXMovement;
                cw -= cursorXMovement * 2;
                j = 16 - menu->unk1D; // FAKE?
                var_a1 = ch / 16 * j;
                ch -= var_a1;
            }
        }
        menu->unk1.x = cx;
        menu->unk1.y = cy;
        menu->unk1.w = cw;
        menu->unk1.h = ch;
        SetPrimRect(prim, cx, cy, cw, ch);

        r0 = g_Settings.windowColors[0] * 8 - 0x20;
        if (r0 < 0) {
            r0 = 0;
        }
        g0 = g_Settings.windowColors[1] * 8 - 0x20;
        if (g0 < 0) {
            g0 = 0;
        }
        b0 = g_Settings.windowColors[2] * 8 - 0x20;
        if (b0 < 0) {
            b0 = 0;
        }
        r1 = g_Settings.windowColors[0] * 8 + 0x20;
        if (r1 >= 0x100) {
            r1 = 0xFF;
        }
        g1 = g_Settings.windowColors[1] * 8 + 0x20;
        if (g1 >= 0x100) {
            g1 = 0xFF;
        }
        b1 = g_Settings.windowColors[2] * 8 + 0x20;
        if (b1 >= 0x100) {
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
            equipIndex = g_Status.equipment[0];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 30, menu);
            DrawConsumableCount(equipIndex, 0, menu);
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x10);

            equipIndex = g_Status.equipment[1];
            equip = &g_EquipDefs[equipIndex];
            MenuDrawStr(equip->name, 112, 43, menu);
            DrawConsumableCount(equipIndex, 1, menu);
            flag = equip->itemCategory == 5;
            LoadEquipIcon(equip->icon, equip->iconPalette, 0x11);

            for (j = 0; j < 5; j++) {
                acc = &g_AccessoryDefs[g_Status.equipment[j + 2]];
                MenuDrawStr(acc->name, 112, 56 + j * 13, menu);
                LoadEquipIcon(acc->icon, acc->iconPalette, j + 0x12);
            }

            for (j = 0; j < 7; j++) {
                if (j >= 0 && j < 2 && flag) {
                    if (j == 0) {
                        func_800F892C(0x10, 0x5E, 0x20, menu);
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
        }
    }
}

void func_800F9690(void) {
    Primitive* prim = &g_PrimBuf[D_8013783C];

    if (D_80137608 != 0) {
        prim->drawMode = DRAW_MENU;
    } else {
        prim->drawMode = DRAW_HIDE;
    }
    if (g_MenuData.menus[4].unk1C != 0) {
        prim->drawMode = DRAW_HIDE;
    }
}

void func_800F96F4(void) { // !Fake:
    s32 new_var2;
    Primitive* prim;
    s32 temp_a2;
    s32* temp;
    s32* new_var;

    new_var = D_80137848;
    prim = &g_PrimBuf[D_80137840];
    temp_a2 = g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk1C == 0;
    temp = D_80137844;

    if ((D_80137844[0] != 0) && (temp_a2 != 0)) {
        (&g_PrimBuf[D_80137840])->drawMode = DRAW_MENU;
        if (D_80137844[0] == 1) {
            (&g_PrimBuf[D_80137840])->clut = 0x188;
        } else {
            D_80137844[0] -= 1;
            (&g_PrimBuf[D_80137840])->clut = 0x181;
        }
    } else {
        prim->drawMode = DRAW_HIDE;
    }

    prim = prim->next;
    temp = new_var;

    if (((*temp) != 0) && (temp_a2 != 0)) {
        prim->drawMode = DRAW_MENU;
        new_var2 = *temp;
        if (new_var2 == 1) {
            do {
                prim->clut = 0x188;
            } while (0);
            return;
        }
        *temp -= 1;
        prim->clut = 0x181;
        return;
    }
    prim->drawMode = DRAW_HIDE;
}

void func_800F97DC(void) {
    D_8013794C = g_Pix[0];
    D_80137950 = 0x180;
    D_80137954 = 0;
}

void func_800F9808(u32 arg0) {
    s32 temp_s0;
    s32 i;
    u8* oldPos;

    temp_s0 = (arg0 == 2) ? 32 : 0;
    arg0 = func_800F548C(arg0);
    oldPos = D_8013794C;

    for (i = 0; i < ((temp_s0 + 0x100) * 8); i++) {
        *D_8013794C++ = 0;
    }

    LoadTPage(oldPos, 0, 0, 0x180, arg0, temp_s0 + 256, 16);
}

void func_800F98AC(const char* str, u32 arg1) {
    u32 temp_s2;
    s32 i;
    u8* data_ptr;
    s32 var_s1;
    u8* var_a1;
    u32 loaded_data;

    temp_s2 = arg1;
    var_s1 = (temp_s2 >> 2) & 0x40;
    temp_s2 = func_800F548C(temp_s2);

#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif

    for (data_ptr = str; *data_ptr != 0;) {
        // Loads a big-endian u16 from data_ptr.
        // This is connected to shift-jis.
        loaded_data = *data_ptr++ << 8;
        loaded_data += *data_ptr++;
        var_a1 = func_80106A28(loaded_data, 0);
        for (i = 0; i < 0x60; i++) {
            D_8013794C[i] = *var_a1++;
        }
        LoadTPage((PixPattern*)D_8013794C, 0, 0, var_s1 + D_80137950,
                  temp_s2 + D_80137954, 0xC, 0x10);
        D_8013794C += 0x60;
        var_s1 += 3;
    }
}

#if defined(VERSION_US)
void func_800F99B8(const char* str, s32 arg1, s32 arg2) {
    // See src/st/blit_char.h
    const u16 MINSCODE = 0x8140;
    const u16 RIGHT_DOUBLE_QUOTATION_MARK = 0x8168;

    const int FontWidth = 12;
    const int FontHeight = 16;
    const int FontStride = FontWidth / 2;

    s32 var_a0;
    u8* var_a2;
    s32 var_a3;
    u8 var_s0;
    u8* var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 i;
    s32 j;
    u8* dest_addr;

    var_s1 = str;
    var_s5 = arg1;
    if (arg2 == 0) {
        var_s4 = 0x90;
    } else {
        var_s4 = 0x3C;
    }
    for (i = 0; i < var_s4 * FontHeight; i++) {
        D_8013794C[i] = 0;
    }
    var_s6 = ((u32)var_s5 >> 2) & 0x40;
    var_s3 = 0;
    if (var_s5 & 0x200) {
        var_s6 += 0x20;
        var_s5 &= ~0x200;
    }
    var_s5 = func_800F548C(var_s5 & 0xFF) & 0xFF;
#ifdef VERSION_PC
    NOT_IMPLEMENTED;
    return;
#endif
    while (*var_s1 != 0) {
        var_s2 = 0;
        var_s0 = *var_s1++;
        if ('a' <= var_s0 && var_s0 <= 'z') {
            var_a0 = var_s0 + 0x8220;
        } else if ('A' <= var_s0 && var_s0 <= 'Z') {
            var_a0 = var_s0 + 0x821F;
        } else if (var_s0 == ' ') {
            var_a0 = MINSCODE;
            var_s2 = 2;
        } else {
            // load var_a0 as a big-endian value corresponding with shift-jis
            var_a0 = (var_s0 << 8);
            var_a0 += *var_s1++;
            if (var_a0 == RIGHT_DOUBLE_QUOTATION_MARK) {
                var_s1 += 2;
            }
            if (var_a0 == MINSCODE) {
                var_s0 = ' ';
                var_s2 = 2;
            }
        }
        var_a2 = func_80106A28(var_a0, 0);
        while (1) {
            if (var_s0 == ' ') {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                // probably fake, i think var_a2 is a 2d array like [6][??]
                if (var_a2[i * FontStride] != 0) {
                    break;
                }
            }
            if (i != FontHeight) {
                break;
            }
            for (i = 0; i < FontHeight; i++) {
                dest_addr = &var_a2[i * FontStride];
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
            for (j = 0; j < FontStride; j++) {
                // similar to above comment, this could be var_a2[i][j]
                if ((var_a2[i * FontStride + j] != 0) && (var_a3 < j)) {
                    var_a3 = j;
                }
            }
        }
        for (i = 0; i < FontHeight; i++) {
            if (var_a2[i * FontStride + var_a3] & 0xF0) {
                break;
            }
        }
        if (i != FontHeight) {
            var_a3 += 1;
        }
        if (var_a3 < FontStride) {
            var_a3 += 1;
        }
        for (i = 0; i < FontHeight; i++) {
            dest_addr = &D_8013794C[var_s3 + var_s4 * i];
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
            *dest_addr++ = *var_a2++;
        }
        var_s3 += var_a3 + var_s2;
        if (var_s3 >= var_s4) {
            break;
        }
    }

    LoadTPage((PixPattern*)D_8013794C, 0, 0, var_s6 + D_80137950,
              var_s5 + D_80137954, var_s4 * 2, 0x10);
    D_8013794C += var_s4 * 0x10;
}
#endif

void func_800F9D40(const char* str, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = g_Pix[2];
    }

    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F98AC(str, arg1);
}

#if defined(VERSION_US)
void func_800F9D88(const char* str, s32 arg1, s32 arg2) {
    if (arg2 != 0) {
        D_8013794C = g_Pix[2];
    }
    D_80137950 = 0;
    D_80137954 = 0x100;
    func_800F99B8(str, arg1, 0);
}
#endif

void func_800F9DD0(u8* arg0, u8* arg1) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (*arg0 == 0)
            break;
        *arg1++ = *arg0++;
        *arg1++ = *arg0++;
    }
}

const char D_800DC6EC[] = {
    "　　　　　　　　　　　　　　　　　　　　　",
};

#if defined(VERSION_US)
void func_800F9E18(s32 arg0) {
    const int ItemsPerRow = 2;
    char buffer[38];
    s32 nHalfScreenSize = arg0 * 5;
    s32 i = (arg0 * 5) + 5;
    s32 nItems = i;

    if (arg0 == 0) {
        ClearImage(&D_800A2D90, 0, 0, 0);
        DrawSync(0);
    }

    for (i = nHalfScreenSize; i < nItems; i++, nHalfScreenSize++) {
        strcpy(buffer, g_RelicDefs[i * ItemsPerRow + 0].name);
        if ((nHalfScreenSize % ItemsPerRow) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 128, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 259, 1);
        }

        strcpy(buffer, g_RelicDefs[i * ItemsPerRow + 1].name);
        if ((nHalfScreenSize % ItemsPerRow) == 0) {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 640, 1);
        } else {
            func_800F99B8(buffer, (nHalfScreenSize / ItemsPerRow) + 771, 1);
        }
    }
}
#elif defined(VERSION_HD)
void func_800F9E18(s32 arg0) {
    const int ItemsPerRow = 2;
    char buffer[2][0x14];
    s32 nItems = (arg0 * 5) + 5;
    s32 i;

    for (i = arg0 * 5; i < nItems; i++) {
        STRCPY(buffer, D_800DC6EC);
        func_800F9DD0(g_RelicDefs[i * ItemsPerRow + 0].name, buffer[0]);
        func_800F9DD0(g_RelicDefs[i * ItemsPerRow + 1].name, buffer[1]);
        if ((i % ItemsPerRow) == 0) {
            func_800F98AC(buffer, i / ItemsPerRow + 0x80);
        } else {
            func_800F98AC(buffer, i / ItemsPerRow + 0x103);
        }
    }
}
#endif

void func_800F9F40(void) {
    char buffer[38];
    u8 spellId;
    s32 i;

    for (i = 0; i < NUM_SPELLS; i++) {
        spellId = D_80097902[0x80 + i];
        if (spellId & 0x80) {
            spellId ^= 0x80;
            STRCPY(buffer, D_800DC6EC);
            func_800F9DD0(g_SpellDefs[spellId].name, buffer);
            ShowText(buffer, 0x80 + i);
        }
    }
}

void MenuHandleCursorInput(s32* nav, u8 nOptions, u32 arg2) {
    const int ItemsPerPage = 12;
    const int Unk16 = 72;
    s32 limit;
    u8 prevCursor;

    prevCursor = *nav;
    switch (arg2) {
    case 3:
        if (g_pads[0].repeat & PAD_UP) {
            if (*nav) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 0:
        if (g_pads[0].repeat & PAD_UP) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 4:
        if (g_pads[0].repeat & PAD_LEFT) {
            if (*nav != 0) {
                *nav -= 1;
            }
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            if (*nav != nOptions - 1) {
                *nav += 1;
            }
        }
        break;
    case 5:
        if (g_pads[0].repeat & PAD_LEFT) {
            *nav -= 1;
            if (*nav == -1) {
                *nav = nOptions - 1;
            }
        }
        if (g_pads[0].repeat & PAD_RIGHT) {
            *nav += 1;
            if (*nav == nOptions) {
                *nav = 0;
            }
        }
        break;
    case 1:
    case 2:
        if (g_pads[0].repeat & PAD_UP) {
            if (*nav >= 2) {
                *nav -= 2;
            }
        }
        if (g_pads[0].repeat & PAD_DOWN) {
            if (*nav == nOptions - 2) {
                if (*nav & 1) {
                    *nav = nOptions - 1;
                }
            }
            if (*nav < nOptions - 2) {
                *nav += 2;
            }
        }
        if (g_pads[0].repeat & (PAD_RIGHT | PAD_LEFT)) {
            *nav ^= 1;
            if (*nav == nOptions) {
                *nav ^= 1;
            }
        }
        if (arg2 == 2) {
            if (g_pads[0].repeat & PAD_L1) {
                if (*nav >= ItemsPerPage) {
                    *nav -= ItemsPerPage;
                    g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 += Unk16;
                    if (g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 > 0) {
                        g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 = 0;
                    }
                } else {
                    *nav = 0;
                    g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 = 0;
                }
            }
            if (g_pads[0].repeat & PAD_R1) {
                if (*nav < nOptions - ItemsPerPage) {
                    *nav += ItemsPerPage;
                    limit = ((nOptions - 1) / 2 - 5) * -ItemsPerPage;
                    g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 -= Unk16;
                    if (g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 <
                        limit) {
                        g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 = limit;
                    }
                } else {
                    *nav = nOptions - 1;
                    if (nOptions >= 13) {
                        g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 =
                            (*nav / 2 - 5) * -ItemsPerPage;
                    }
                }
            }
        }
        break;
    }

    if (prevCursor != *nav) {
        PlaySfx(SE_UI_SELECT);
    }
}

void func_800FA3C4(s32 cursorIndex, s32 arg1, s32 arg2) {
    s32 limit;
    s32 top_offset;
    s32 arg0_lowbit;
    s32 left;
    s32 top;
    s32 half_arg0;
    MenuContext* menu = &g_MenuData.menus[MENU_DG_EQUIP_SELECTOR];

    if (menu->unk1C != 0) {
        return;
    }
    arg0_lowbit = cursorIndex & 1;
    half_arg0 = (cursorIndex / 2);

    left = (arg0_lowbit * 0xA8) + 0x28;
    limit = -(menu->unk16 / 12);

    // Below some limit
    if (half_arg0 < limit) {
        menu->unk16 += 12;
        top = menu->cursorY + 1;
        // Beyond that limit, on the other side
    } else if (half_arg0 >= (limit + menu->cursorH / 12)) {
        menu->unk16 -= 12;
        top_offset = (menu->cursorH / 12 - 1) * 12 + 1;
        top = menu->cursorY + top_offset;
        // Somewhere in between
    } else {
        top = ((half_arg0 - limit) * 12) + menu->cursorY + 1;
    }

    if (D_801375CC == 0) {
        g_MenuNavigation.scrollEquipType[EQUIP_HAND] = menu->unk16;
    } else {
        g_MenuNavigation.scrollEquipType[EQUIP_HEAD + D_801375D4] = menu->unk16;
    }
    if (arg2 != 0) {
        if (arg1 == 0) {
            MenuDrawLine(left, top, left + 0x70, top, 0);
            MenuDrawLine(left, top, left, top + 0xB, 0);
            MenuDrawLine(left + 0x70, top, left + 0x70, top + 0xB, 0);
            MenuDrawLine(left, top + 0xB, left + 0x70, top + 0xB, 0);
        } else {
            MenuDrawLine(left, top, left + 0x70, top + 0xB, 0);
            MenuDrawLine(left, top + 0xB, left + 0x70, top, 0);
        }
    }
}

void MenuEquipHandlePageScroll(s32 arg0) {
    const int ItemsPerPage = 12;
    const int Unk16 = 72;
    s32 nItems;
    s32 limit;
    s32* cursorIndex;
    MenuContext* menu = &g_MenuData.menus[MENU_DG_EQUIP_SELECTOR];

    if (D_801375CC == 0) {
        cursorIndex = &g_MenuNavigation.cursorEquipType[EQUIP_HAND];
    } else {
        cursorIndex =
            &g_MenuNavigation.cursorEquipType[EQUIP_HEAD + D_801375D4];
    }

    nItems = func_800FD6C4(D_801375CC);
    if (arg0 != 0) {
        if (g_pads[0].repeat & PAD_L1) {
            if (*cursorIndex >= ItemsPerPage) {
                *cursorIndex -= ItemsPerPage;
                menu->unk16 += Unk16;
                if (menu->unk16 > 0) {
                    menu->unk16 = 0;
                }
                if (*D_80137844 != 0) {
                    *D_80137844 = 5;
                }
            } else {
                *cursorIndex = 0;
                menu->unk16 = 0;
            }
        }
        if (g_pads[0].repeat & PAD_R1) {
            if (*cursorIndex < nItems - ItemsPerPage) {
                *cursorIndex += ItemsPerPage;
                limit = -(((nItems - 1) / 2 - 5) * ItemsPerPage);
                menu->unk16 -= Unk16;
                if (menu->unk16 < limit) {
                    menu->unk16 = limit;
                }
                if (*D_80137848 != 0) {
                    *D_80137848 = 5;
                }
            } else {
                *cursorIndex = nItems - 1;
                if (nItems > ItemsPerPage) {
                    menu->unk16 = -((*cursorIndex / 2 - 5) * ItemsPerPage);
                }
            }
        }
    }
    func_800FA3C4(*cursorIndex, 0, 0);
}

// If you use both attack buttons at once, see if something special
// happens. Applies to Shield Rod + Shield, or dual Heaven Swords
void CheckWeaponCombo(void) {
    s32 weapon0;
    s32 weapon1;
    s32 combo1;
    s32 combo2;
    s32 comboBits;
    s32 i;
    s32 oddComboCheck;

    weapon0 = g_Status.equipment[LEFT_HAND_SLOT];
    weapon1 = g_Status.equipment[RIGHT_HAND_SLOT];

    combo1 = g_EquipDefs[weapon0].comboSub & g_EquipDefs[weapon1].comboMain;
    oddComboCheck = 0x80000000;
    oddComboCheck &= -(combo1 == 0);

    combo2 = g_EquipDefs[weapon0].comboMain & g_EquipDefs[weapon1].comboSub;
    comboBits = combo1 | combo2;

    if (comboBits != 0) {
        for (i = 0xAA; i < 0xD9; i++) {
            if (comboBits & g_EquipDefs[i].comboSub) {
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
    if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
        equipId = 0xD8;
    }

    weaponId = g_EquipDefs[equipId].weaponId;
    if (weaponId == g_EquippedWeaponIds[equipIndex] || weaponId == 0xFF) {
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
    g_EquippedWeaponIds[equipIndex] = weaponId;
    return 1;
}

void InitWeapon(s32 itemSlot) {
    // Called twice every time the in-game menu is closed.
    // It will be called twice, with LEFT_HAND_SLOT and then RIGHT_HAND_SLOT

    void (*loadWeaponPalette)(u8 clutIndex);
    s32 equipId;
    Entity* entity;
    u16 entityId;
    s32 i;

    equipId = g_Status.equipment[itemSlot];

    // Having the Axe Lord Armor equipped will not load any normal weapon
    if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
        equipId = 0xD8;
    }

    // Do not re-load the same weapon
    if (equipId == g_PrevEquippedWeapons[itemSlot]) {
        return;
    }

    // Assign the right palette to the weapon graphics
    if (itemSlot == LEFT_HAND_SLOT) {
        loadWeaponPalette = D_8017A000.LoadWeaponPalette;
    } else {
        loadWeaponPalette = D_8017D000.LoadWeaponPalette;
    }
    loadWeaponPalette(g_EquipDefs[equipId].palette);

    // Destroy any entity spawned by the previously equipped weapon.
    // 0xE0-0xEF: weapon0 (left hand) entities
    // 0xF0-0xFF: weapon1 (right hand) entities
    entity = g_Entities;
    for (i = 0; i < STAGE_ENTITY_START; i++) {
        entityId = entity->entityId;
        if (entityId >= itemSlot * 0x10 + WEAPON_0_START &&
            entityId <= itemSlot * 0x10 + WEAPON_0_END) {
            DestroyEntity(entity);
        }
        if (entityId >= WEAPON_0_START + 8 && entityId < WEAPON_0_START + 14) {
            DestroyEntity(entity);
        }
        if (entityId >= WEAPON_1_START + 8 && entityId < WEAPON_1_START + 14) {
            DestroyEntity(entity);
        }
        entity++;
    }
}

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

void MenuHide(s32 menuDialogue) {
    g_MenuData.menus[menuDialogue].unk1C = 1;
    g_MenuData.menus[menuDialogue].unk1D = 0;
}

void MenuShow(s32 menuDialogue) {
    g_MenuData.menus[menuDialogue].unk1C = 3;
    g_MenuData.menus[menuDialogue].unk1D = 0;
}

void func_800FABEC(s32 menuDialogue) {
    g_MenuData.menus[menuDialogue].unk1C = 0;
}

void func_800FAC0C(s32 menuDialogue) {
    g_MenuData.menus[menuDialogue].unk1C = 2;
}

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
    if (g_pads[0].tapped & PAD_R2) {
        g_MenuNavigation.cursorEquip++;
        if (g_MenuNavigation.cursorEquip == 7) {
            g_MenuNavigation.cursorEquip = 0;
        }
        return true;
    }
    if (g_pads[0].tapped & PAD_L2) {
        g_MenuNavigation.cursorEquip--;
        if (g_MenuNavigation.cursorEquip == -1) {
            g_MenuNavigation.cursorEquip = 6;
        }
        return true;
    }
    return false;
}

void func_800FAD34(const char* str, u8 count, u16 equipIcon, u16 palette) {
    D_80137608 = 0;
    func_800F9808(2);

    if (count > 0) {
        D_80137608 = 1;
        ShowText(str, 2);
        LoadEquipIcon(equipIcon, palette, 0x1F);
    }
}

void func_800FADC0(void) {
    const char* description;
    s32 cursorEquip;
    u16 equipIcon;
    u16 palette;

    if (g_MenuNavigation.cursorEquip < 2) {
        cursorEquip = g_Status.equipment[g_MenuNavigation.cursorEquip];
        description = g_EquipDefs[cursorEquip].description;
        equipIcon = g_EquipDefs[cursorEquip].icon;
        palette = g_EquipDefs[cursorEquip].iconPalette;
    } else {
        cursorEquip = g_Status.equipment[g_MenuNavigation.cursorEquip];
        description = g_AccessoryDefs[cursorEquip].description;
        equipIcon = g_AccessoryDefs[cursorEquip].icon;
        palette = g_AccessoryDefs[cursorEquip].iconPalette;
    }
    func_800FAD34(description, 0x1, equipIcon, palette);
}

void func_800FAE98(void) {
    func_800FADC0();
    g_MenuStep = MENU_STEP_EQUIP;
}

void func_800FAEC4(s32 cursor, u16 count, const char* str, u16 icon, u16 pal) {
    g_IsSelectingEquipment = 0;
    func_800FAC98();
    func_800FAD34(str, count, icon, pal);
    g_MenuStep++;
}

void func_800FAF44(s32 isAccessory) {
    s32 var_a0;
    s32 i;
    s32 j;
    s32* var_a1;

    D_801375D8 = g_Pix[3];
    var_a1 = g_Pix[3];

    if (isAccessory == 0) {
        for (i = 0; i < 169; i++) {
            *var_a1 = i;
            var_a1++;
        }

        g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].h =
            g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 =
                g_MenuNavigation.scrollEquipType[EQUIP_HAND];
    } else {
        g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].h =
            g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].unk16 =
                g_MenuNavigation.scrollEquipType[EQUIP_HEAD + D_801375D4];
        for (i = 0; i < 90; i++) {
            if (g_AccessoryDefs[i].equipType == D_801375D4) {
                *var_a1 = i;
                var_a1++;
            }
        }
    }
}

void func_800FB004(void) {
    s32 temp_a1 = func_800FD6C4(D_801375CC);
    s32 temp_v0;

    if (((-g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].h) / 12) != 0) {
        if (*D_80137844 == 0) {
            *D_80137844 = 1;
        }
    } else {
        *D_80137844 = 0;
    }

    temp_v0 = -g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].h +
              g_MenuData.menus[MENU_DG_EQUIP_SELECTOR].cursorH;

    if ((temp_v0 / 12) < (temp_a1 / 2)) {
        if (D_80137848[0] == 0) {
            D_80137848[0] = 1;
        }
    } else {
        D_80137848[0] = 0;
    }
}

void func_800FB0FC(void) {
    EquipMenuHelper* helper = &g_EquipMenuHelper[g_MenuNavigation.cursorEquip];
    s32 index = helper->index;
    s32 isAccessory = helper->isAccessory;

    D_801375CC = helper->equipTypeFilter;
    D_801375D4 = index;
    func_800FAF44(isAccessory);
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
    if (D_801375CC == EQUIP_HAND) {
        if (arg0 == 0) {
            return true;
        }
    } else if (arg0 == 0x1A || arg0 == 0 || arg0 == 0x30 || arg0 == 0x39) {
        return true;
    }

    return false;
}

#if defined(VERSION_US)
#define PAD_MENU_SELECT_ALT (PAD_CROSS)
#define PAD_MENU_SELECT (PAD_MENU_SELECT_ALT)
#define PAD_MENU_BACK (PAD_TRIANGLE)
#define PAD_MENU_SORT (PAD_SQUARE)
#elif defined(VERSION_HD)
#define PAD_MENU_SELECT_ALT (PAD_CIRCLE)
#define PAD_MENU_SELECT (PAD_MENU_SELECT_ALT | PAD_SQUARE)
#define PAD_MENU_BACK (PAD_CROSS)
#define PAD_MENU_SORT (PAD_TRIANGLE)
#endif
#define PAD_MENU_BACK_ALT (PAD_MENU_SELECT | PAD_MENU_BACK)

s32 func_800FB23C(MenuNavigation* nav, u8* order, u8* count, u32* selected) {
    s32 prevCursor;
    s32 nItems;
    s32 ret;
    u16 itemId;
    s32 var_s4;
    s32 var_s6;
    u16 otherItemId;
    u16 yetAnotherId;

    s32 temp_psp_a1;
    s32 temp_psp_a2;

    nItems = func_800FD6C4(D_801375CC);
    prevCursor = nav->cursorMain;
    MenuHandleCursorInput(nav, nItems, 2);
    itemId = order[D_801375D8[nav->cursorMain]];
    otherItemId = *selected;
    ret = 0;
    if (count[itemId] != 0) {
        *selected = itemId;
    } else {
        *selected = 0;
    }

    if (D_801375CC == EQUIP_HAND) {
        yetAnotherId = g_Status.equipment[1 - D_801375D0];
        if (count[itemId] > 0) {
            if (g_EquipDefs[otherItemId].itemCategory == 5) {
                g_Status.equipment[1 - D_801375D0] = 0;
            }
            if (g_EquipDefs[itemId].itemCategory == 5) {
                g_Status.equipment[1 - D_801375D0] = itemId;
            }
        } else if (g_EquipDefs[otherItemId].itemCategory == 5) {
            g_Status.equipment[1 - D_801375D0] = 0;
        }
    }
    var_s6 = 0;
    func_800F53A4();

    if ((g_Player.unk0C & 0x17) | (PLAYER.step == Player_UnmorphWolf) |
        (PLAYER.step == Player_BossGrab) | (g_Player.unk60)) {
        if (itemId == ITEM_AXE_LORD_ARMOR) {
            if (D_801375CC == EQUIP_ARMOR) {
                if (count[ITEM_AXE_LORD_ARMOR] != 0) {
                    var_s6 = 1;
                }
            }
        }
    }

    temp_psp_a2 = 0;
    if (D_801375CC == EQUIP_HAND && count[itemId] > 0) {
        if (itemId == ITEM_LIFE_APPLE || itemId == ITEM_HAMMER) {
            temp_psp_a1 = 1;
        } else {
            temp_psp_a1 = 0;
        }
        if (temp_psp_a1) {
            temp_psp_a2 = 1;
        }
    }
    var_s6 |= temp_psp_a2;
    D_80137948 = 0;
    if (var_s6 == 0) {
        D_80137948 = 1;
        func_800F7244();
    }
    *selected = otherItemId;
    if (D_801375CC == EQUIP_HAND) {
        g_Status.equipment[1 - D_801375D0] = yetAnotherId;
    }
    func_800F53A4();
    if (g_pads[0].tapped & PAD_MENU_SORT) {
        if (g_IsSelectingEquipment == 0) {
            if (func_800FB1EC(itemId) == false) {
                g_EquipmentCursor = nav->cursorMain;
                g_IsSelectingEquipment++;
                PlaySfx(SFX_UI_CONFIRM);
            } else {
                PlaySfx(SE_UI_ERROR);
            }
        } else if (func_800FB1EC(itemId) != false) {
            PlaySfx(SE_UI_ERROR);
        } else {
            goto block_36;
        }
    } else if (g_pads[0].tapped & PAD_MENU_SELECT) {
        if (g_IsSelectingEquipment != 0) {
            do {
                if (func_800FB1EC(itemId) == false) {
                block_36:
                    func_800FB160(
                        g_EquipmentCursor, nav->cursorMain, D_801375CC);
                    ret = 2;
                    g_IsSelectingEquipment = 0;
                    PlaySfx(SFX_UI_CONFIRM);
                } else {
                    PlaySfx(SE_UI_ERROR);
                }
            } while (0);
        } else if (var_s6 != 0) {
            PlaySfx(SE_UI_ERROR);
        } else {
            PlaySfx(SFX_UI_CONFIRM);
            if (count[itemId] > 0) {
                var_s4 = 1;
                *selected = itemId;
                if (func_800FB1EC(itemId) == false) {
                    count[itemId]--;
                }
                if (D_801375CC == EQUIP_HAND && itemId == ITEM_SWORD_FAMILIAR &&
                    (LOW(g_Status.relics[RELIC_FAERIE_CARD]) & 0x30000) ==
                        0x30000) {
                    g_Status.relics[RELIC_SWORD_CARD] = 1;
                    g_Servant = 0;
                }
            } else {
                var_s4 = 0;
                if (D_801375CC == EQUIP_HAND) {
                    ret = 2;
                    if (*selected != 0) {
                        *selected = 0;
                    } else {
                        goto block_5b0;
                    }
                } else {
                    *selected = D_800A2DEC[D_801375D4];
                }
            }
            AddToInventory(otherItemId, D_801375CC);
            if (D_801375CC == EQUIP_HAND) {
                if (g_EquipDefs[otherItemId].itemCategory == 5) {
                    g_Status.equipment[1 - D_801375D0] = 0;
                }
                if (g_EquipDefs[itemId].itemCategory == 5 && var_s4 != 0) {
                    if (g_EquipDefs[yetAnotherId].itemCategory !=
                        g_EquipDefs[itemId].itemCategory) {
                        AddToInventory(yetAnotherId, D_801375CC);
                    }
                    g_Status.equipment[1 - D_801375D0] = itemId;
                }
            }
            ret = 2;
        }
    }
block_5b0:
    func_800FA3C4(nav->cursorMain, var_s6, 1);
    if ((-g_MenuData.menus[3].h) / 12) {
        if (g_pads[0].repeat & PAD_L1) {
            *D_80137844 = 5;
        } else if (*D_80137844 == 0) {
            *D_80137844 = 1;
        }
    } else {
        *D_80137844 = 0;
    }
    if ((-g_MenuData.menus[3].h + g_MenuData.menus[3].cursorH) / 12 <
        (nItems + 1) / 2) {
        if (g_pads[0].repeat & PAD_R1) {
            *D_80137848 = 5;
        } else if (*D_80137848 == 0) {
            *D_80137848 = 1;
        }
    } else {
        *D_80137848 = 0;
    }

    if (func_800FACB8()) {
        return 1;
    }

    if (g_pads[0].tapped & PAD_MENU_BACK) {
        if (g_IsSelectingEquipment == 0) {
            func_800FAE98();
            return 0;
        } else {
            g_IsSelectingEquipment = 0;
        }
    }
    if (prevCursor != nav->cursorMain) {
        return 2;
    }

    return ret;
}

void func_800FB9BC(void) {
    const int ItemsPerRow = 2;
#if defined(VERSION_US)
    const int VertScrollWindow = 120;
    const int YScrollPerElement = 14;
#elif defined(VERSION_HD)
    const int VertScrollWindow = 140;
    const int YScrollPerElement = 15;
#endif

    s32 i;
    MenuContext* context;

    context = &g_MenuData.menus[0];
    for (i = 0; i < NUM_MENU; i++, context++) {
        context->cursorX = context->unk1.x = g_MenuInit[i].cursorX;
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
    g_MenuData.menus[5].h = g_MenuData.menus[5].unk16 =
        -((g_MenuNavigation.cursorRelic / ItemsPerRow) * VertScrollWindow) /
        YScrollPerElement;
}

void func_800FBAC4(void) {
    s32 i;
    s32 j;
    s32* var_a1;
    s32 importantcategory;

    for (i = g_EquipOrderType; i > 0; i--) {
        // j is used as a temp to swap these two variables.
        j = g_Settings.equipOrderTypes[i];
        g_Settings.equipOrderTypes[i] = g_Settings.equipOrderTypes[i - 1];
        g_Settings.equipOrderTypes[i - 1] = j;
    }

    g_EquipOrderType = 0;
    var_a1 = D_801375D8;
    *var_a1++ = 0;
    for (i = 0; i < ITEM_END; i++) {
        importantcategory = g_Settings.equipOrderTypes[i];
        for (j = 0; j < NUM_HAND_ITEMS; j++) {
            if (g_Status.equipHandCount[g_Status.equipHandOrder[j]] != 0 &&
                g_Status.equipHandOrder[j] != 0 &&
                g_EquipDefs[g_Status.equipHandOrder[j]].itemCategory ==
                    importantcategory) {
                *var_a1++ = g_Status.equipHandOrder[j];
            }
        }
    }

    for (j = 0; j < NUM_HAND_ITEMS; j++) {
        if (g_Status.equipHandCount[g_Status.equipHandOrder[j]] == 0) {
            *var_a1++ = g_Status.equipHandOrder[j];
        }
    }

    var_a1 = D_801375D8;
    for (i = 0; i < NUM_HAND_ITEMS; i++) {
        g_Status.equipHandOrder[i] = *var_a1++;
    }
}

void MenuHandle(void) {
    s32 temp_s1;
    s32 var_a0;
    s32 id;
    s32 var_s1;
    s32 i;
    u8 equipId;
    s32 isSecondAccessory;

#if defined(VERSION_US)
    D_8013784C = 0;
#endif
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
        PlaySfx(SET_UNK_10);
        func_800EA5E4(0);
        func_800FAC30();
        func_800FB9BC();
        g_PrevEquippedWeapons[0] = g_Status.equipment[0];
        g_PrevEquippedWeapons[1] = g_Status.equipment[1];
        if (g_Status.equipment[ARMOR_SLOT] == ITEM_AXE_LORD_ARMOR) {
            *g_PrevEquippedWeapons = 0xD8;
            g_PrevEquippedWeapons[1] = 0xD8;
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
        func_800E346C();
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
#if defined(VERSION_US)
            func_800F98AC(*D_800A2D64, 0);
#elif defined(VERSION_HD)
            func_800F98AC(*D_800A2D10, 0);
            func_800F98AC(*D_800A2D14, 0x100);
            func_800F98AC(*D_800A2D18, 1);
#endif
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
        if (LoadWeaponPrg(LEFT_HAND_SLOT) == false) {
            break;
        }
        if (g_UseDisk) {
            g_MenuStep++;
            break;
        }
        InitWeapon(LEFT_HAND_SLOT);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_7:
        if (!g_UseDisk) {
            g_MenuStep++;
            break;
        }
        if (g_IsUsingCd) {
            break;
        }
        InitWeapon(LEFT_HAND_SLOT);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_8:
        if (LoadWeaponPrg(RIGHT_HAND_SLOT) == false) {
            break;
        }
        if (g_UseDisk) {
            g_MenuStep++;
            break;
        }
        InitWeapon(RIGHT_HAND_SLOT);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_9:
        if (!g_UseDisk) {
            g_MenuStep++;
            break;
        }
        if (g_IsUsingCd) {
            break;
        }
        InitWeapon(RIGHT_HAND_SLOT);
        g_MenuStep++;
        break;
    case MENU_STEP_EXIT_10:
        if (g_Servant == FAM_ACTIVE_NONE || g_Servant != g_ServantPrevious) {
            func_800FAB1C();
        }
        if (g_Servant == FAM_ACTIVE_NONE) {
            g_MenuStep += 2;
        } else if (g_Servant == g_ServantLoaded) {
            if (g_Servant != g_ServantPrevious) {
                if (g_Status.statsFamiliars[g_Servant - 1].unk8 < 9999) {
                    g_Status.statsFamiliars[g_Servant - 1].unk8++;
                }
                func_800E6218(1);
            } else {
                func_800E6218(3);
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
        if (!g_UseDisk || !g_IsUsingCd) {
            if (!g_UseDisk) {
                func_800E6250();
                func_800E6218(1);
            } else if (!g_IsUsingCd) {
                func_800E6218(1);
            }
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
        if (D_80097928 == 0) {
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
        MenuHandleCursorInput(&g_MenuNavigation.cursorMain, 5, 0);
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
            }
            if (g_MenuStep == MENU_STEP_OPENED) {
                PlaySfx(SE_UI_ERROR);
                break;
            }
            MenuHide(MENU_DG_MAIN);
            MenuHide(MENU_DG_BG);
            PlaySfx(SFX_UI_CONFIRM);
        }
        break;
    case MENU_STEP_FAMILIAR_INIT:
        func_800EA5E4(0x21);
        func_800EAEA4();
        MenuShow(MENU_DG_FAMILIARS);
        g_MenuStep++;
        break;
    case MENU_STEP_FAMILIAR:
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
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
        MenuHandleCursorInput(&g_MenuNavigation.cursorSettings, 6, 0);
        func_800F9808(2);
        i = g_MenuNavigation.cursorSettings + 1;
        if (i == 2 && g_IsCloakLiningUnlocked == false) {
            i = 0;
        }
        if (i == 3 && g_IsCloakColorUnlocked == false) {
            i = 0;
        }
        if (i == 6 && g_IsTimeAttackUnlocked == false) {
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
                MenuShow(MENU_DG_CFG_SOUND);
                g_MenuStep = MENU_STEP_SYSTEM_SOUND;
                break;
            case 5:
                if (g_IsTimeAttackUnlocked) {
                    SortTimeAttackEntries();
                    MenuShow(MENU_DG_TIME_ATTACK);
                    g_MenuStep = MENU_STEP_SYSTEM_TIME_ATTACK;
                }
                break;
            }
            if (g_MenuStep == MENU_STEP_SYSTEM) {
                PlaySfx(SE_UI_ERROR);
            } else {
                PlaySfx(SFX_UI_CONFIRM);
            }
        }
        break;
    case MENU_STEP_SYSTEM_BUTTONS:
        MenuHandleCursorInput(&g_MenuNavigation.cursorButtons, 7, 0);
        MenuHandleCursorInput(
            &g_Settings.buttonConfig[g_MenuNavigation.cursorButtons], 8, 5);
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            if (CheckIfAllButtonsAreAssigned()) {
                PlaySfx(SFX_UI_CONFIRM);
                MenuHide(MENU_DG_CFG_BUTTONS);
                g_MenuStep = MENU_STEP_SYSTEM;
            } else {
            block_117:
                func_800F9808(2);
#if defined(VERSION_US)
                ShowText("Assign the function to each button．", 2);
#elif defined(VERSION_HD)
                ShowText("すべてのボタンを割り当ててください。", 2);
#endif
                PlaySfx(SE_UI_ERROR);
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
#if defined(VERSION_US)
        if (id >= RELIC_JP_0) {
            id += 2; // Skip the two exclusive Japanese relics
        }
#endif
        if (g_Status.relics[id] & RELIC_FLAG_FOUND) {
            ShowText(g_RelicDefs[id].desc, 2);
        }
        func_800F9E18(2);
        g_MenuStep++;
        break;
    case MENU_STEP_RELIC:
#if defined(VERSION_US)
        g_MenuData.menus[5].unk16 =
            (-((g_MenuNavigation.cursorRelic / 2) * 0x78)) / 14;
#elif defined(VERSION_HD)
        g_MenuData.menus[5].unk16 =
            (-((g_MenuNavigation.cursorRelic / 2) * 0x8C)) / 15;
#endif
        var_s1 = g_MenuNavigation.cursorRelic;
#if defined(VERSION_US)
        if (var_s1 >= RELIC_JP_0) {
            var_s1 += 2; // Skip the two exclusive Japanese relics
        }
#endif
        MenuHandleCursorInput(
            &g_MenuNavigation.cursorRelic, NUM_AVAIL_RELICS, 1);
        id = g_MenuNavigation.cursorRelic;
#if defined(VERSION_US)
        if (id >= RELIC_JP_0) {
            id += 2; // Skip the two exclusive Japanese relics
        }
#endif
        if (g_pads[0].tapped & PAD_MENU_SELECT &&
            g_Status.relics[id] & RELIC_FLAG_FOUND) {
            PlaySfx(SFX_UI_CONFIRM);
            g_Status.relics[id] = g_Status.relics[id] ^ 2;
            if (g_RelicDefs[id].unk0C > 0) {
                for (var_a0 = 0; var_a0 < NUM_RELICS; var_a0++) {
                    if (var_a0 == id) {
                        continue;
                    }
                    if (g_RelicDefs[var_a0].unk0C <= 0) {
                        continue;
                    }
                    g_Status.relics[var_a0] &= ~RELIC_FLAG_ACTIVE;
                }

                if (g_Status.relics[id] & RELIC_FLAG_ACTIVE) {
                    var_a0 = ITEM_SWORD_FAMILIAR;
                    g_Servant = g_RelicDefs[id].unk0C;
                    if (g_Servant == FAM_ACTIVE_SWORD) {
                        if (g_Status.equipment[LEFT_HAND_SLOT] == var_a0) {
                            g_Status.equipment[LEFT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(var_a0, 0);
                        }
                        if (g_Status.equipment[RIGHT_HAND_SLOT] == var_a0) {
                            g_Status.equipment[RIGHT_HAND_SLOT] =
                                ITEM_EMPTY_HAND;
                            AddToInventory(var_a0, 0);
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
#if defined(VERSION_US)
        func_800F9808(2);
        id = g_Status.spells[g_MenuNavigation.cursorSpells];
        id ^= SPELL_FLAG_KNOWN;
        ShowText(g_SpellDefs[id].description, 2);
#endif
        g_MenuStep++;
        break;
    case MENU_STEP_SPELL:
        temp_s1 = g_MenuNavigation.cursorSpells;
        MenuHandleCursorInput(&g_MenuNavigation.cursorSpells, D_801375DC, 3);
#if defined(VERSION_US)
        if (temp_s1 != g_MenuNavigation.cursorSpells) {
#elif defined(VERSION_HD)
        if (1) {
#endif
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
        if (g_pads[0].tapped & PAD_MENU_BACK_ALT) {
            func_801073C0();
            g_CdStep = CdStep_None;
            func_800E346C();
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
        func_800F98AC(g_SpellDefs[id].description, 2);
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
            &g_MenuNavigation.cursorEquipType[1 + D_801375D4],
            g_Status.equipBodyCount[equipId],
            g_AccessoryDefs[equipId].description, g_AccessoryDefs[equipId].icon,
            g_AccessoryDefs[equipId].iconPalette);
        func_800FAF44(1);
    case MENU_STEP_EQUIP_ACC:
        isSecondAccessory = g_MenuNavigation.cursorEquip == ACCESSORY_2_SLOT;
        i = func_800FB23C(
            &g_MenuNavigation.cursorEquipType[1 + D_801375D4],
            g_Status.equipBodyOrder, g_Status.equipBodyCount,
            &g_Status.equipment[isSecondAccessory + D_801375D4 + 2]);
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
    if (g_MenuStep >= MENU_STEP_OPENED ||
        g_MenuStep >= MENU_STEP_EXIT_BEGIN && g_MenuStep < MENU_STEP_EXIT_5) {
        MenuDraw();
        func_800F9690();
        func_800F96F4();
    }
}

#if defined(VERSION_US)
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
    sprt->clut = g_ClutIds[pal];
    AddPrim(&gpuBuffer->ot[0x1FF], sprt);
    g_GpuUsage.sp++;
}
#endif

s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action) {
    s32 temp_v0;
    s32 temp_v1;
    s32 seconds;
    s32 timer;

    switch (action) {
    case TIMEATTACK_GET_RECORD:
        // get the time attack for a specific defeated boss. this is
        // also responsible to check if the player should teleport into
        // a boss room
        return g_Settings.timeAttackRecords[eventId];

    case TIMEATTACK_SET_RECORD:
        // set new time attack record if the boss was not previously
        // defeated
        timer = g_Settings.timeAttackRecords[eventId];
        if (timer = timer != 0) {
            return g_Settings.timeAttackRecords[eventId];
        }

        seconds = g_Status.timerSeconds;
        g_Settings.timeAttackRecords[eventId] = seconds;
        temp_v1 = (g_Status.timerMinutes * 100) + seconds;
        g_Settings.timeAttackRecords[eventId] = temp_v1;
        temp_v0 = (g_Status.timerHours * 10000) + temp_v1;
        g_Settings.timeAttackRecords[eventId] = temp_v0;
        return temp_v0;

    case TIMEATTACK_SET_VISITED:
        // not exactly sure yet why this flag is needed
        g_Settings.D_8003CB00 |= 1 << eventId;
    }
}
