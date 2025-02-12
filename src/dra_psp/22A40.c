// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF3C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF480);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF548);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF608);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", DemoUpdate);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FFAB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", EntityBatEcho);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", TimeAttackController);

bool CalcPlayerDamage(DamageParam* damage) {
    if (damage->damageKind != DAMAGEKIND_5) {
        if (damage->damageKind >= DAMAGEKIND_16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if ((damage->damageTaken * 20) > g_Status.hpMax) {
            damage->damageKind = DAMAGEKIND_2;
        } else {
            damage->damageKind = DAMAGEKIND_3;
        }
    }
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        return true;
    }
    g_Status.hp -= damage->damageTaken;
    return false;
}

s32 AdjustForInvertedCastle(s32 arg0) {
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        arg0 *= 2;
    }
    return arg0;
}

// Unused. Exactly the same as CalcPlayerDamage. Pulled into g_Api.
bool CalcPlayerDamageAgain(DamageParam* damage) {
    if (damage->damageKind != DAMAGEKIND_5) {
        if (damage->damageKind >= DAMAGEKIND_16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if ((damage->damageTaken * 20) > g_Status.hpMax) {
            damage->damageKind = DAMAGEKIND_2;
        } else {
            damage->damageKind = DAMAGEKIND_3;
        }
    }
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        return true;
    }
    g_Status.hp -= damage->damageTaken;
    return false;
}
// What the heck? Repeating again? Never referenced but not dead-stripped?
s32 func_psp_091007E0(s32 arg0) {
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG) {
        arg0 *= 2;
    }
    return arg0;
}

ItemCategory GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}

s32 CountEquipItems(s32 equipTypeFilter) {
    s32 itemCount;
    s32 equipType;
    s32 i;

    switch (equipTypeFilter) {
    case EQUIP_HAND:
        return NUM_HAND_ITEMS;
    case EQUIP_HEAD:
        equipType = EQUIP_HEAD - 1;
        break;
    case EQUIP_ARMOR:
        equipType = EQUIP_ARMOR - 1;
        break;
    case EQUIP_CAPE:
        equipType = EQUIP_CAPE - 1;
        break;
    case EQUIP_ACCESSORY:
        equipType = EQUIP_ACCESSORY - 1;
        break;
    }

    for (itemCount = 0, i = 0; i < NUM_BODY_ITEMS; i++) {
        if (g_AccessoryDefs[i].equipType == equipType) {
            itemCount++;
        }
    }
    return itemCount;
}
