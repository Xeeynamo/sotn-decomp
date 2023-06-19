#include "ric.h"

void func_8016E324(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = 0x20000 | FLAG_UNK_04000000;
        entity->ext.generic.unk7C.s = 0x14;
        entity->step++;

    case 1:
        entity->ext.generic.unk7C.s--;
        if ((entity->ext.generic.unk7C.s) == 0) {
        case 3:
        case 5:
            func_801606BC(entity, 0x39, 0);
            entity->step++;
        case 2:
        case 4:
        case 6:
            entity->ext.generic.unk7C.s++;
            if (entity->ext.generic.unk7C.s >= 11) {
                entity->ext.generic.unk7C.s = 0;
                entity->posX.val = 0x800000;
                entity->posY.val = 0;
                func_801606BC(entity, 0x10004, 0);
                entity->step++;
            }
        }
        break;

    case 7:
        entity->ext.generic.unk7C.s++;
        if (entity->ext.generic.unk7C.s >= 16) {
            func_80156C60(entity);
            g_Player.unk4E = 1;
            func_801606BC(entity, 0x3A, 0);
        }
        break;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016E46C);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016E9E4);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016F198);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8016F6F0);

void func_80170548(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unkB0 = 0x1E;
        func_8015FAB8(entity);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s >= 5) {
            func_80156C60(entity);
        }
        break;
    }
}
