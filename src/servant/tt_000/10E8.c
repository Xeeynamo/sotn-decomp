#include "common.h"
#include "game.h"

void func_801710E8(Entity* entity, s32* arg1) {
    if (entity->unk4C != arg1) {
        entity->unk4C = arg1;
        entity->animationFrameIndex = 0;
        entity->animationFrameDuration = 0;
    }
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_8017110C);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801713C8);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80171434);

void func_80171560(void) {}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80171568);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_8017160C);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_8017170C);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801718A0);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801719E0);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80171ED4);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80172120);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80172C30);

void func_8017339C(void) {}

void func_801733A4(void) {}

void func_801733AC(void) {}

void func_801733B4(void) {}

void func_801733BC(void) {}

void func_801733C4(void) {}

void func_801733CC(void) {}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801733D4);

void func_80173C0C(void) {}

void func_80173C14(void) {}

void func_80173C1C(void) {}

void func_80173C24(void) {}

extern s32 D_80174D3C;

void func_80173C2C(Entity* entity) {
    if (entity->subId == 0xF) {
        D_80174D3C = 1;
    }
    func_80173E0C(entity);
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173C64);

void func_80173E0C(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_api.FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173E78);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173EB0);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173F30);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173F74);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80173FE8);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80174038);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80174210);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801745E4);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801746A0);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_801747B8);

INCLUDE_ASM("config/../asm/servant/tt_000/nonmatchings/10E8", func_80174864);
