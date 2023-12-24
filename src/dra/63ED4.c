#include "dra.h"
#include "objects.h"
#include "sfx.h"

// Note: Including this as part of the previous file (62D70.c) caused
// four 00 bytes to be added to the rodata at 0x3CDC0; this indicates
// that this function should be the start of this new file.
void func_80103ED4(void) {
    char saveFile[32];
    s32 memCardClose;
    s32 i;
    s32 case1_state;

    switch (D_80137E4C) {
    case 0:
        MemcardInit();
        g_MemCardRetryCount = 4;
        D_80137E4C++;
        return;
    case 1:
        // This really should be doable as a switch, but that doesn't match.
        case1_state = func_800E9880(D_80097924, 0);
        if (case1_state == 0) {
            return;
        }
        if (case1_state == -1) {
            if (--g_MemCardRetryCount == -1) {
                D_80137E4C = 7;
            }
            return;
        }
        if (case1_state == -3) {
            if (--g_MemCardRetryCount == -1) {
                D_80137E4C = 8;
            }
            return;
        }
        if (case1_state == -2) {
            D_80137E4C = 9;
            return;
        }
        MemcardInit();
        D_80137E4C++;
        return;
    case 2:
        if (MemcardParse(D_80097924, 0) >= 0) {
            g_MemCardRetryCount = 10;
            if (D_8006C378 >= 0) {
                i = 0;
                if (D_80137E54 == 2) {
                    for (i = 0; i < 15; i++) {
                        MakeMemcardPath(saveFile, i);
                        if (MemcardDetectSave(D_80097924, saveFile, 0) != 0) {
                            break;
                        }
                    }
                    if ((i == 15) &&
                        (GetMemcardFreeBlockCount(D_80097924) == 0)) {
                        D_80137E54 = 3;
                    }
                }
                D_80137E4C += 2;
                return;
            } else {
                D_80137E4C += 1;
                return;
            }
        }
        break;
    case 3:
        for (i = 0; i < 15; i++) {
            MakeMemcardPath(saveFile, i);
            if (MemcardDetectSave(D_80097924, saveFile, 0) == 0) {
                break;
            }
        }
        if (i != 15) {
            if (GetMemcardFreeBlockCount(D_80097924) == 0) {
                D_80137E4C = 10;
                return;
            }
            D_8006C378 = i;
            D_80137E4C++;
            return;
        }
        D_80137E4C = 10;
        return;
    case 4:
        MakeMemcardPath(saveFile, D_8006C378);
        // careful with i here, it's not an iterator.
        if (MemcardDetectSave(D_80097924, saveFile, 0) == 1) {
            i = 0;
        } else {
            i = 1;
            if (GetMemcardFreeBlockCount(D_80097924) == 0) {
                D_80137E4C = 10;
                return;
            }
        }
        // I believe the rand() call here selects the icon on the save
        // in the save-select screen.
        StoreSaveData(g_Pix, D_8006C378, rand() & 0xF);
        if (MemcardWriteFile(D_80097924, 0, saveFile, g_Pix, 1, i) != 0) {
            if (--g_MemCardRetryCount == -1) {
                D_80137E4C = 0;
                return;
            }
        } else {
            g_MemCardRetryCount = 10;
            D_80137E4C++;
            return;
        }
        break;
    case 5:
        memCardClose = MemcardClose(D_80097924);
        if (memCardClose == 0) {
            return;
        }
        if (memCardClose == -3) {
            if (--g_MemCardRetryCount != -1) {
                D_80137E4C--;
                return;
            }
            D_80137E4C = 0;
            return;
        }
        D_80137E4C = 6;
        return;
    case 6:
        return;
    }
}

void func_8010427C(void) {
    FreePrimitives(D_80137E40);
    FreePrimitives(D_80137E44);
    FreePrimitives(D_80137E48);
}

INCLUDE_ASM("dra/nonmatchings/63ED4", func_801042C4);

INCLUDE_ASM("dra/nonmatchings/63ED4", func_80104790);

void func_80105078(s32 arg0, s32 arg1) {
    VECTOR sp28;
    SVECTOR pad;
    SVECTOR sp40[3];
    SVECTOR sp58[3];
    u8 sp70[4];
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 sp88;
    SVECTOR** sp90;
    Primitive* prim;
    s32 temp_v0_4;
    s32 i;

    sp70[2] = sp70[1] = sp70[0] = 0x80;
    sp70[3] = 0;
    RotMatrix(&D_801379C8, &D_80137E00);
    RotMatrix(&D_801379C8, &D_80137E20);
    SetColorMatrix(&D_800A37B8);
    SetLightMatrix(&D_80137E20);
    SetBackColor(0xC0, 0xC0, 0xC0);

    sp90 = &D_800A34C0;
    prim = &g_PrimBuf[D_80137E44];

    for (sp88 = 0; sp88 < 18; sp88++, prim = prim->next, sp90 += 3) {
        if (arg0 == 0) {
            prim->blendMode = BLEND_VISIBLE;
            continue;
        }
        TransMatrix(&D_80137E00, &D_801379D0);
        SetRotMatrix(&D_80137E00);
        SetTransMatrix(&D_80137E00);
        sp7C = 0;
        for (i = 0; i < 3; i++) {
            sp28.vx = sp40[i].vx = (sp90[i]->vx * arg0) >> 8;
            sp28.vy = sp40[i].vy = (sp90[i]->vy * arg0) >> 8;
            sp28.vz = sp40[i].vz = (sp90[i]->vz * arg0) >> 8;
            func_80017008(&sp28, &sp58[i]);
        }
        temp_v0_4 = RotAverageNclip3(
            &sp40[0], &sp40[1], &sp40[2], (s32*)&prim->x0, (s32*)&prim->x1,
            (s32*)&prim->x2, &sp78, &sp7C, &sp80);
        if (temp_v0_4 < 0) {
            RotAverage3(&sp40[0], &sp40[2], &sp40[1], (s32*)&prim->x0,
                        (s32*)&prim->x2, (s32*)&prim->x1, &sp78, &sp80);
        }
        prim->type = 2;
        if (sp7C < 0xF0) {
            if (temp_v0_4 >= 0) {
                prim->priority =
                    g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 + 3;
            } else {
                prim->priority =
                    g_unkGraphicsStruct.g_zEntityCenter.S16.unk0 - 3;
            }
            if (arg1 != 0) {
                if (arg1 & 0x80) {
                    prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 =
                        prim->b1 = arg1 & 0x7F;
                } else if (arg1 < 0x11) {
                    prim->r0 = prim->g0 = prim->b0 = (0x10 - arg1) * 8;
                } else if (arg1 < 0x21) {
                    prim->r1 = prim->g1 = prim->b1 = (0x20 - arg1) * 8;
                } else {
                    prim->blendMode = BLEND_VISIBLE;
                    continue;
                }
            }
            prim->blendMode = 0x35;
        }
    }
}

void func_80105408(void) {
    g_Player.D_80072EF4 = 0x1000;
    g_Player.D_80072EFC = 1;
}

INCLUDE_ASM("dra/nonmatchings/63ED4", func_80105428);

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

void DestroyEntities(s16 startIndex) {
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
        if (entity->facingLeft) {
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
        if (entity->facingLeft) {
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

    if (g_GpuUsage.drawModes < MAX_DRAW_MODES) {
        SetDrawMode(drawMode, 0, 0, (blendMode - 1) << 5, &g_Vram.D_800ACD80);
        AddPrim(&ot[otIdx], drawMode);
        g_GpuUsage.drawModes++;
    }
}

INCLUDE_ASM("dra/nonmatchings/63ED4", func_80106A28);

bool LoadMonsterLibrarianPreview(s32 monsterId) {
    if (g_IsUsingCd)
        return false;

    if (!g_UseDisk) {
        if (LoadFileSim(monsterId, SimFileType_Monster) < 0) {
            return false;
        }
    } else {
        g_CdStep = CdStep_LoadInit;
        g_LoadFile = CdFile_Monster;
        g_LoadOvlIdx = monsterId;
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

void SetPrimRect(Primitive* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void SetTexturedPrimRect(
    Primitive* poly, s32 x, s32 y, s32 width, s32 height, s32 u, s32 v) {
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
