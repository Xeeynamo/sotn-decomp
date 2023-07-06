
#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80102D70(void) {
    switch (D_801379AC.start) {
    case 2:
        func_80102D08();
        g_backbufferX = D_801379AC.unk8;
        break;
    case 1:
    case 3:
    case 4:
    case 6:
        func_80102D08();
        g_backbufferY = D_801379AC.unk8;
    case 0:
    case 5:
    default:
        break;
    }
}

void func_80102DEC(s32 context) {
    D_80137E64 = 0;
    D_80137E68 = context;
}

s32 func_80102E04(void) {
    u32 new_var2 = D_80137E68;
    s32 temp_s0 = D_80137E64;

    switch (temp_s0) {
    case 0:
        func_800E92E4();
        D_80137E50 = 4;
        D_80137E64++;
        break;

    case 1:
        if (func_800E9B18(new_var2, 0) != temp_s0) {
            D_80137E50 = D_80137E50 - 1;
            if (D_80137E50 == -1) {
                temp_s0 = -1;
                return temp_s0;
            }
        } else {
            return 1;
        }
        break;
    }

    return 0;
}

void func_80102EB8(void) {
    POLY_GT4 *poly1, *poly2, *poly3;
    s32 i;

    D_80137E58 = AllocPrimitives(PRIM_GT4, 3);
    poly1 = &g_PrimBuf[D_80137E58];

    D_80137E5C = AllocPrimitives(PRIM_G4, 3);
    poly2 = &g_PrimBuf[D_80137E5C];

    D_80137E60 = AllocPrimitives(PRIM_LINE_G2, 12);
    poly3 = &g_PrimBuf[D_80137E60];

    for (i = 0; i < 3; i++) {
        func_80107360(poly1, 98, 79, 96, 0, 0, 0);
        func_801072DC(poly1);
        poly1->tpage = 0x10;
        poly1->clut = 0x1A1;
        poly1->pad2 = g_zEntityCenter.S16.unk0 + 32;
        poly1->pad3 = 8;
        poly1->p1 = 0;
        SetPolyRect(poly2, 80, 79, 96, 0);
        func_801072DC(poly2);
        func_801071CC(poly2, 96, 0);
        func_801071CC(poly2, 96, 1);
        poly2->g0 = poly2->g1 = poly2->g2 = poly2->g3 = poly2->r0 = poly2->r1 =
            poly2->r2 = poly2->r3 = 0;
        poly2->tpage = 0x1F;
        poly2->pad2 = g_zEntityCenter.S16.unk0 + 31;
        poly2->pad3 = 8;
        poly1 = (POLY_GT4*)poly1->tag;
        poly2 = (POLY_GT4*)poly2->tag;
    }

    for (i = 0; i < 12; i++) {
        func_80107250(poly3, 255);
        poly3->pad2 = g_zEntityCenter.S16.unk0 + 32;
        poly3->pad3 = 8;
        poly3 = (POLY_GT4*)poly3->tag;
    }
}

void func_801030B4(s32 arg0, POLY_GT4* poly, s32 arg2) {
    s32 var_v1;

    if (arg2 == arg0) {
        if (g_blinkTimer & 0x20) {
            var_v1 = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            var_v1 = 0x7F - (g_blinkTimer & 0x1F);
        }

        poly->r0 = poly->r1 = var_v1 - 16;
        poly->r2 = poly->r3 = var_v1 + 16;
        poly->b0 = poly->b1 = poly->b2 = poly->b3 = 0;
        poly->pad3 = 0x404;
    } else {
        poly->b1 = 96;
        poly->b0 = 96;
        poly->b3 = 128;
        poly->b2 = 128;
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = 0;
        poly->pad3 = 0x415;
    }
}

POLY_GT4* func_80103148(POLY_GT4* poly1, POLY_GT4* arg1) {
    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y0 - 1;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x0 - 1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x0 - 1;
    poly1->y0 = arg1->y2;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    poly1 = (POLY_GT4*)poly1->tag;

    poly1->x0 = arg1->x1;
    poly1->y0 = arg1->y0 - 1;
    poly1->x1 = arg1->x1;
    poly1->y1 = arg1->y2;
    poly1->pad3 = 0;
    return (POLY_GT4*)poly1->tag;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80103238);

void func_80103EAC(void) {
    D_80137E4C = 0;
    func_800E92F4();
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80103ED4);

void func_8010427C(void) {
    FreePrimitives(D_80137E40);
    FreePrimitives(D_80137E44);
    FreePrimitives(D_80137E48);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801042C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80104790);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80105078);

void func_80105408(void) {
    g_Player.D_80072EF4 = 0x1000;
    g_Player.D_80072EFC = 1;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80105428);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_HAS_PRIMS) {
        FreePrimitives(entity->primIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = NULL;
}

void func_801065F4(s16 startIndex) {
    Entity* pItem;

    for (pItem = &g_Entities[startIndex];
         pItem < &g_Entities[TOTAL_ENTITY_COUNT]; pItem++)
        DestroyEntity(pItem);
}

void DrawEntitiesHitbox(s32 blendMode) {
    DR_MODE* drawMode;
    s32 polyCount;
    s32* ot;
    Entity* entity;
    TILE* tile;
    u32 otIdx;
    u16 x;
    u16 y;

    ot = g_CurrentBuffer->ot;
    tile = &g_CurrentBuffer->tiles[g_GpuUsage.tile];
    drawMode = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes];
    otIdx = 0x1F0;
    for (polyCount = 0, entity = g_Entities; polyCount < 0x40; polyCount++,
        entity++) {
        if (entity->hitboxState == 0)
            continue;
        if (g_GpuUsage.tile >= GPU_MAX_TILE_COUNT) {
            break;
        }

        y = (u16)entity->posY.i.hi + (u16)g_backbufferY;
        x = (u16)entity->posX.i.hi + (u16)g_backbufferX;
        if (entity->facing) {
            x -= entity->hitboxOffX;
        } else {
            x += entity->hitboxOffX;
        }
        y += entity->hitboxOffY;

        tile->r0 = 0xFF;
        tile->g0 = 0xFF;
        tile->b0 = 0xFF;
        if (entity->hitboxState == 2) {
            tile->r0 = 0;
            tile->g0 = 0xFF;
            tile->b0 = 0;
        }
        tile->x0 = x - entity->hitboxWidth;
        tile->y0 = y - entity->hitboxHeight;
        tile->w = entity->hitboxWidth * 2;
        tile->h = entity->hitboxHeight * 2;
        SetSemiTrans(tile, 1);
        AddPrim(&ot[otIdx], tile);
        tile++;
        g_GpuUsage.tile++;
    }

    for (; polyCount < GPU_MAX_TILE_COUNT; polyCount++, entity++) {
        if (entity->hitboxState == 0)
            continue;
        if (g_GpuUsage.tile >= GPU_MAX_TILE_COUNT) {
            break;
        }

        y = (u16)entity->posY.i.hi + (u16)g_backbufferY;
        x = (u16)entity->posX.i.hi + (u16)g_backbufferX;
        if (entity->facing) {
            x -= entity->hitboxOffX;
        } else {
            x += entity->hitboxOffX;
        }
        y += entity->hitboxOffY;

        tile->r0 = 0xFF;
        tile->g0 = 0xFF;
        tile->b0 = 0xFF;
        if (entity->hitboxState == 1) {
            tile->r0 = 0xFF;
            tile->g0 = 0;
            tile->b0 = 0;
        }
        if (entity->hitboxState == 2) {
            tile->r0 = 0;
            tile->g0 = 0;
            tile->b0 = 0xFF;
        }
        if (entity->hitboxState == 3) {
            tile->r0 = 0xFF;
            tile->g0 = 0;
            tile->b0 = 0xFF;
        }
        tile->x0 = x - entity->hitboxWidth;
        tile->y0 = y - entity->hitboxHeight;
        tile->w = entity->hitboxWidth * 2;
        tile->h = entity->hitboxHeight * 2;
        SetSemiTrans(tile, 1);
        AddPrim(&ot[otIdx], tile);
        tile++;
        g_GpuUsage.tile++;
    }

    if (g_GpuUsage.drawModes < 0x400) {
        SetDrawMode(drawMode, 0, 0, (blendMode - 1) << 5, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80106A28);

bool func_8010715C(s32 mapTilesetId) {
    if (g_IsUsingCd)
        return false;

    if (!g_UseDisk) {
        if (func_800E81FC(mapTilesetId, SimFileType_Monster) < 0) {
            return false;
        }
    } else {
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_28;
        g_mapTilesetId = mapTilesetId;
    }
    return true;
}

void func_801071CC(POLY_GT4* poly, u32 colorIntensity, s32 vertexIndex) {
    switch (vertexIndex) {
    case 0:
        poly->b0 = colorIntensity;
        poly->g0 = colorIntensity;
        poly->r0 = colorIntensity;
        break;
    case 1:
        poly->b1 = colorIntensity;
        poly->g1 = colorIntensity;
        poly->r1 = colorIntensity;
        break;
    case 2:
        poly->b2 = colorIntensity;
        poly->g2 = colorIntensity;
        poly->r2 = colorIntensity;
        break;
    case 3:
        poly->b3 = colorIntensity;
        poly->g3 = colorIntensity;
        poly->r3 = colorIntensity;
        break;
    }
}

void func_80107250(POLY_GT4* poly, s32 colorIntensity) {
    func_801071CC(poly, (u8)colorIntensity, 0);
    func_801071CC(poly, (u8)colorIntensity, 1);
    func_801071CC(poly, (u8)colorIntensity, 2);
    func_801071CC(poly, (u8)colorIntensity, 3);
}

void func_801072BC(POLY_GT4* poly) { func_80107250(poly, 0); }

void func_801072DC(POLY_GT4* poly) { func_80107250(poly, 0x80); }

void func_801072FC(POLY_G4* poly) {
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
}

void SetPolyRect(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void func_80107360(
    POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->y2 = y + height;
    poly->x3 = x + width;
    poly->y3 = y + height;
    poly->v0 = v;
    poly->v1 = v;
    poly->u0 = u;
    poly->u1 = u + width;
    poly->u2 = u;
    poly->v2 = v + height;
    poly->u3 = u + width;
    poly->v3 = v + height;
}
