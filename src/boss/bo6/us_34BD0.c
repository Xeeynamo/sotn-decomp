// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo6.h"

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4BD0);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4EAC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B4FA4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B502C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B50BC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B5A14);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", RichterThinking);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6998);

extern EInit D_us_80180400; //
extern s32 D_us_801CF3E0;
extern u32 D_us_801CF3E4;

void func_us_801B6AC4(Entity* self) {
    Entity* entity;
    s32 i;

    g_Ric.unk6A = RIC.hitPoints;
    if (self->step == 0) {
        InitializeEntity(D_us_80180400);
        func_us_801B4BD0();
        entity = &g_Entities[STAGE_ENTITY_START + 4];
        for (i = STAGE_ENTITY_START + 4; i < 144; i++, entity++) {
            DestroyEntity(entity);
        }
        g_Ric.unk6E = g_Ric.unk6A = g_Ric.unk6C = RIC.hitPoints;
        D_us_801CF3E4 = g_Ric.unk6E / 2;
        D_us_801CF3E0 = 0;
        g_Ric.unk70 = RIC.hitboxState;
        func_us_801B5A14(18);
        func_us_801B9B78(1, 48);
    } else {
        RichterThinking();
        func_us_801B50BC();
        func_us_801BBBD0();
        func_us_801B6998();
    }
    g_Ric.unk6C = g_Ric.unk6A;
}

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6BD8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6E3C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6EA8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B6F88);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7444);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B74DC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B779C);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B77D8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7818);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B7E80);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8540);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B85DC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8684);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B86B8);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B86EC);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B87B4);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8A88);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8D50);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8E80);

INCLUDE_ASM("boss/bo6/nonmatchings/us_34BD0", func_us_801B8F78);
