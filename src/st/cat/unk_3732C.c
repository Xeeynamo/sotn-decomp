// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B732C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B7A94);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B7AFC);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B7B64);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B7F2C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B7FE0);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B82A0);

void func_us_801B8474(u32 arg0) {
    Entity* temp_v0;
    s16 temp_s2;
    s16 temp_s1;

    temp_s2 = (((arg0 % 48) * 16) + 8) - g_Tilemap.scrollX.i.hi;
    temp_s1 = (((arg0 / 48) * 16) + 8) - g_Tilemap.scrollY.i.hi;
    (&g_CurrentEntity[1])->posX.i.hi = temp_s2;
    (&g_CurrentEntity[1])->posY.i.hi = temp_s1;

    temp_v0 = AllocEntity(&g_CurrentEntity[1], &g_CurrentEntity[4]);
    if (temp_v0 != NULL) {
        CreateEntityFromCurrentEntity(32, temp_v0);
        temp_v0->posX.i.hi = temp_s2;
        temp_v0->posY.i.hi = temp_s1;
    }
}

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B852C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B86B0);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B872C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B87E8);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B8AD0);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B8D2C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B907C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B951C);

INCLUDE_RODATA("st/cat/nonmatchings/unk_3732C", D_us_801B673C);

INCLUDE_RODATA("st/cat/nonmatchings/unk_3732C", D_us_801B674C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B972C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B9A74);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801B9D1C);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801BA164);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801BA388);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801BA7FC);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801BACF4);

INCLUDE_ASM("st/cat/nonmatchings/unk_3732C", func_us_801BB4CC);
