#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CC750);

extern s32 D_80097408[];

void func_us_801CC8F8(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = -0x7FFF;
        self->animCurFrame = 3;
        self->zPriority = (u16)(D_80097408[0] - 0x54);
        self->unk68 = 0xC0;
        self->flags &= ~FLAG_UNK_20000000;
        return;
    }

    if (self->posX.i.hi < -0x40) {
        self->posX.i.hi += 0x180;
    }

    if (self->posX.i.hi >= 0x141) {
        self->posX.i.hi -= 0x180;
    }
}

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CC9B4);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCAAC);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCBE4);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCC2C);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CCC74);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CD750);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CD864);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CDAD4);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CDB20);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CDE48);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE058);

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE0F8);

void func_us_801CE2D8(void) {
}

INCLUDE_ASM("st/no0/nonmatchings/4C750", func_us_801CE2E0);
