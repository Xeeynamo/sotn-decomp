#include "ric.h"

void func_8016E324(Entity* entity) {
    switch (entity->step) {
    case 0:
        entity->flags = 0x20000 | FLAG_UNK_04000000;
        entity->unk7C.s = 0x14;
        entity->step++;

    case 1:
        entity->unk7C.s--;
        if ((entity->unk7C.s) == 0) {
        case 3:
        case 5:
            func_801606BC(entity, 0x39, 0);
            entity->step++;
        case 2:
        case 4:
        case 6:
            entity->unk7C.s++;
            if (entity->unk7C.s >= 11) {
                entity->unk7C.s = 0;
                entity->posX.val = 0x800000;
                entity->posY.val = 0;
                func_801606BC(entity, 0x10004, 0);
                entity->step++;
            }
        }
        break;

    case 7:
        entity->unk7C.s++;
        if (entity->unk7C.s >= 16) {
            func_80156C60(entity);
            D_80072F6E = 1;
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
        entity->unkB0 = 0x1E;
        func_8015FAB8(entity);
        entity->hitboxWidth = 8;
        entity->hitboxHeight = 8;
        entity->step++;
        break;

    case 1:
        if (++entity->unk7C.s >= 5) {
            func_80156C60(entity);
        }
        break;
    }
}

/**
 * TODO:
 * Aspatch jumps to the wrong instruction
 * This function matches with GCC 2.6.0 + ASPSX 2.3.4,
 * It also has a jumptable which makes it impossible for it
 * to be included in a NON_MATCHING state.
 */
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_801705EC);
#else
void func_80156C60(Entity* entity);

void func_801705EC(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->unk7E.modeU16 = 0;
        entity->step++;

    case 1:
    case 3:
    case 5:
    case 7:
        temp = entity->unk7E.modeU16 + 1;
        entity->unk7E.modeU16 = temp;
        func_801606BC(entity, (temp << 0x10) | 0x3F, 0);
        entity->unk7C.s = 0;
        entity->step++;
        break;

    case 2:
    case 4:
    case 6:
        entity->unk7C.s++;
        if (entity->unk7C.s >= 16) {
            entity->step++;
        }
        break;

    case 8:
        func_80156C60(entity);
        break;
    }
}
#endif

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_801706C0);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_80170874);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8017091C);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_80170F64);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8017161C);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_801719A4);

void func_80172AE8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = g_api.AllocPolygons(4, 1);
        entity->firstPolygonIndex = ret;
        if (entity->firstPolygonIndex != -1) {
            entity->flags = 0x20000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->tpage = 0x1C;
            poly->clut = 0x19D;
            poly->u2 = 0x20;
            poly->u0 = 0x20;
            poly->u3 = 0x30;
            poly->u1 = 0x30;
            poly->v1 = 0;
            poly->v0 = 0;
            poly->v3 = 0x10;
            poly->v2 = 0x10;
            poly->x0 = poly->x2 = entity->posX.i.hi - 8;
            poly->x1 = poly->x3 = entity->posX.i.hi + 8;
            poly->y0 = poly->y1 = entity->posY.i.hi - 8;
            poly->y2 = poly->y3 = entity->posY.i.hi + 8;
            poly->pad2 = entity->zPriority;
            poly->pad3 = 0x115;
            entity->unk7E.modeU16 = 0x60U;
            entity->step++;
        } else {
            func_80156C60(entity);
            return;
        }
        break;

    case 1:
        if (++entity->unk7C.s > 5) {
            entity->step++;
        }
        entity->unk7E.modeU16 -= 8;
        break;

    case 2:
        func_80156C60(entity);
        return;

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->unk7E.modeU8.unk0;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_80172D00);

INCLUDE_ASM("asm/us/ric/nonmatchings/32324", func_8017328C);