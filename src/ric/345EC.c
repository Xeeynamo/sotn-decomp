#include "ric.h"

void func_801705EC(Entity* entity) {
    u16 temp;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_04000000;
        entity->ext.generic.unk7E.modeU16 = 0;
        entity->step++;

    case 1:
    case 3:
    case 5:
    case 7:
        temp = entity->ext.generic.unk7E.modeU16 + 1;
        entity->ext.generic.unk7E.modeU16 = temp;
        func_801606BC(entity, (temp << 0x10) | 0x3F, 0);
        entity->ext.generic.unk7C.s = 0;
        entity->step++;
        break;

    case 2:
    case 4:
    case 6:
        entity->ext.generic.unk7C.s++;
        if (entity->ext.generic.unk7C.s >= 16) {
            entity->step++;
        }
        break;

    case 8:
        func_80156C60(entity);
        break;
    }
}

const u32 rodataPadding_80156BEC = 0;

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_801706C0);

void func_80170874(s32 bufSize, s32* buf) {
    s32 i, idx, swapTemp;

    for (i = bufSize - 1; i > 0; i--) {
        // Pick random index
        idx = rand() % bufSize;

        // Hold swap value temporarily
        swapTemp = buf[i];
        buf[i] = buf[idx];
        buf[idx] = swapTemp;
    }
}

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_8017091C);

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_80170F64);

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_8017161C);

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_801719A4);

void func_80172AE8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = g_api.AllocPrimitives(4, 1);
        entity->firstPolygonIndex = ret;
        if (entity->firstPolygonIndex != -1) {
            entity->flags = 0x20000 | FLAG_UNK_04000000 | FLAG_FREE_POLYGONS;
            poly = &g_PrimBuf[entity->firstPolygonIndex];
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
            entity->ext.generic.unk7E.modeU16 = 0x60U;
            entity->step++;
        } else {
            func_80156C60(entity);
            return;
        }
        break;

    case 1:
        if (++entity->ext.generic.unk7C.s > 5) {
            entity->step++;
        }
        entity->ext.generic.unk7E.modeU16 -= 8;
        break;

    case 2:
        func_80156C60(entity);
        return;

    default:
        break;
    }
    poly = &g_PrimBuf[entity->firstPolygonIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->ext.generic.unk7E.modeU8.unk0;
}

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_80172D00);

INCLUDE_ASM("asm/us/ric/nonmatchings/345EC", func_8017328C);