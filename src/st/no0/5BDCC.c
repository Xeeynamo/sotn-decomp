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

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", SkeletonAttackCheck);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DCB48);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DD018);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", EntitySkeletonThrownBone);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_801C6678);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", func_us_801DD2B0);

INCLUDE_ASM("st/no0/nonmatchings/5BDCC", EntityMagicallySealedDoor);
