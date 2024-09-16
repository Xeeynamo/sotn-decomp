// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018AFC4);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B018);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B1DC);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B238);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B2F0);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B474);

struct UnkStruct8018B4A0 {
    s16 active;
    u16 index;
    u8* data;
};
extern struct UnkStruct8018B4A0 D_us_8019AEB0;
extern u32 D_us_8019AF20;
extern PfnEntityUpdate PfnEntityUpdates[];
void func_us_8018B4A0(void) {
    Entity* entity;
    u16 nEntities;

    D_us_8019AEB0.index++;
    if (D_us_8019AEB0.index >= 0xFFFF) {
        D_us_8019AEB0.active = 0;
        return;
    }
    while (true) {
        nEntities = *D_us_8019AEB0.data++ << 8;
        nEntities |= *D_us_8019AEB0.data++;
        if (D_us_8019AEB0.index < nEntities) {
            D_us_8019AEB0.data -= 2;
            return;
        }
        switch (*D_us_8019AEB0.data++) {
        case 0:
            entity = &g_Entities[*D_us_8019AEB0.data++ & 0xFF] + 64;
            DestroyEntity(entity);
            entity->entityId = *D_us_8019AEB0.data++;
            entity->pfnUpdate = PfnEntityUpdates[entity->entityId - 1];
            entity->posX.i.hi = *D_us_8019AEB0.data++ * 0x10;
            entity->posX.i.hi |= *D_us_8019AEB0.data++;
            entity->posY.i.hi = *D_us_8019AEB0.data++ * 0x10;
            entity->posY.i.hi |= *D_us_8019AEB0.data++;
            break;
        case 1:
            entity = &g_Entities[*D_us_8019AEB0.data++ & 0xFF] + 64;
            DestroyEntity(entity);
            break;
        case 2:
            if (!((D_us_8019AF20 >> *D_us_8019AEB0.data) & 1)) {
                D_us_8019AEB0.data--;
                return;
            }
            D_us_8019AF20 &= ~(1 << *D_us_8019AEB0.data++);
            break;
        case 3:
            D_us_8019AF20 |= 1 << *D_us_8019AEB0.data++;
            break;
        }
    }
}

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B74C);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", EntityMariaCutscene);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018C90C);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018CA94);
