// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "game.h"

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DBDCC);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC194);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC64C);

void func_us_801DC754(void) {
    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
}

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DC788);
