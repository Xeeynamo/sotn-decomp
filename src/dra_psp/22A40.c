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