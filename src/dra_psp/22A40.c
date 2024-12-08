// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF3C0);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF480);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF548);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FF608);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", DemoUpdate);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FFAB8);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_090FFB28);

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", TimeAttackController);

bool CalcPlayerDamage(DamageParam* damage) {
    if (damage->damageKind != 5) {
        if (damage->damageKind >= 16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if ((damage->damageTaken * 20) > g_Status.hpMax) {
            damage->damageKind = 2;
        } else {
            damage->damageKind = 3;
        }
    }
    if (g_Status.hp <= damage->damageTaken) {
        g_Status.hp = 0;
        return true;
    }
    g_Status.hp -= damage->damageTaken;
    return false;
}

s32 func_800FD664(s32 arg0) {
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG){
        arg0 *= 2;
    }
    return arg0;
}

// Unused. Exactly the same as CalcPlayerDamage. Pulled into g_Api.
bool CalcPlayerDamageAgain(DamageParam* damage) {
    if (damage->damageKind != 5) {
        if (damage->damageKind >= 16) {
            damage->damageTaken = g_Status.hpMax / 8;
        } else if ((damage->damageTaken * 20) > g_Status.hpMax) {
            damage->damageKind = 2;
        } else {
            damage->damageKind = 3;
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
    if (g_StageId & STAGE_INVERTEDCASTLE_FLAG){
        arg0 *= 2;
    }
    return arg0;
}

ItemCategory GetEquipItemCategory(s32 equipId) {
    return g_EquipDefs[g_Status.equipment[equipId]].itemCategory;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/22A40", func_psp_09100870);
