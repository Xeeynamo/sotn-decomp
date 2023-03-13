
#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80102D08();
extern s16 D_801379B4;

void func_80102D70(void) {
    switch (*D_801379AC) {
    case 2:
        func_80102D08();
        g_backbufferX = (s32)D_801379B4;
        return;
    case 1:
    case 3:
    case 4:
    case 6:
        func_80102D08();
        g_backbufferY = (s32)D_801379B4;
        /* fallthrough */
    case 0:
    case 5:
    default:
        return;
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

    D_80137E58 = AllocPolygons(4, 3);
    poly1 = &D_80086FEC[D_80137E58];

    D_80137E5C = AllocPolygons(3, 3);
    poly2 = &D_80086FEC[D_80137E5C];

    D_80137E60 = AllocPolygons(2, 12);
    poly3 = &D_80086FEC[D_80137E60];

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
    FreePolygons(D_80137E40);
    FreePolygons(D_80137E44);
    FreePolygons(D_80137E48);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801042C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80104790);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80105078);

void func_80105408(void) {
    *D_80072EF4 = 0x1000;
    D_80072EFC = 1;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80105428);

void DestroyEntity(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->flags & FLAG_FREE_POLYGONS) {
        FreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = NULL;
}

void func_801065F4(s16 startIndex) {
    Entity* pItem;

    for (pItem = &g_EntityArray[startIndex];
         pItem < &g_EntityArray[TOTAL_ENTITY_COUNT]; pItem++)
        DestroyEntity(pItem);
}

// Print debug hitboxes
void func_80106670(s32 blendMode);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80106670);
#else
extern u32 D_80097944; // tile count?

// https://decomp.me/scratch/iTgjO
void func_80106670(s32 blendMode) {
    const int MaxPolyCount = 0x100;
    int new_var2 = 4;
    DR_MODE* sp20;
    GpuBuffer* temp_a0;
    s32 absX;
    s32 absX_2;
    s32 absY;
    s32 absY_2;
    s32 polyCount;
    s8* temp_s7;
    Entity* entity;
    TILE* tile;
    u32* tileCount;
    u32 var_s8 = 0x1F0;
    s32 temp_var;
    polyCount = 0;
    temp_a0 = D_8006C37C;
    entity = g_EntityArray;
    temp_s7 = temp_a0->_unk_0474;
    tile = &temp_a0->tiles[D_80097944];
    sp20 = &temp_a0->drawModes[g_GpuUsage.drawModes];
    while (polyCount < 0x40) {
        if (entity->unk3C != 0) {
            s32 var_a0_2;
            if (D_80097944 >= MaxPolyCount) {
                break;
            }
            absY = (u16)entity->posY.i.hi + (u16)g_backbufferY;
            absX = (u16)entity->posX.i.hi + (u16)g_backbufferX;
            if (entity->facing != 0) {
                var_a0_2 = absX - (u16)entity->unk10;
            } else {
                var_a0_2 = (u16)entity->unk10 + absX;
            }
            temp_var = absY + (u16)entity->unk12;
            tile->r0 = 0xFF;
            tile->g0 = 0xFF;
            tile->b0 = 0xFF;
            if (entity->unk3C == 2) {
                tile->r0 = 0;
                tile->g0 = 0xFF;
                tile->b0 = 0;
            }
            tile->x0 = var_a0_2 - entity->hitboxWidth;
            tile->y0 = temp_var - entity->hitboxHeight;
            tile->w = 2;
            tile->w = entity->hitboxWidth * tile->w;
            tile->h = entity->hitboxHeight * 2;
            SetSemiTrans(tile, 1);
            AddPrim(temp_s7 + var_s8 * 4, tile);
            tile++;
            D_80097944++;
        }
        polyCount++;
        entity++;
    }

    if (polyCount < MaxPolyCount) {
        while (polyCount < MaxPolyCount) {
            if (entity->unk3C != 0) {
                s32 var_a0_2;
                if (D_80097944 >= MaxPolyCount) {
                    break;
                }
                absY_2 = (u16)entity->posY.i.hi + (u16)g_backbufferY;
                absX_2 = (u16)entity->posX.i.hi + (u16)g_backbufferX;
                if (entity->facing != 0) {
                    var_a0_2 = absX_2 - (u16)entity->unk10;
                } else {
                    var_a0_2 = (u16)entity->unk10 + absX_2;
                }
                temp_var = absY_2 + (u16)entity->unk12;
                tile->r0 = 0xFF;
                tile->g0 = 0xFF;
                tile->b0 = 0xFF;
                if (entity->unk3C == 1) {
                    tile->r0 = 0xFF;
                    tile->g0 = 0;
                    tile->b0 = 0;
                }
                if (entity->unk3C == 2) {
                    tile->r0 = 0;
                    tile->g0 = 0;
                    tile->b0 = 0xFF;
                }
                if (entity->unk3C == 3) {
                    tile->r0 = 0xFF;
                    tile->g0 = 0;
                    tile->b0 = 0xFF;
                }
                tile->x0 = var_a0_2 - entity->hitboxWidth;
                tile->y0 = temp_var - entity->hitboxHeight;
                tile->w = entity->hitboxWidth * 2;
                tile->h = entity->hitboxHeight * 2;
                SetSemiTrans(tile, 1);
                AddPrim(temp_s7 + (var_s8 * (new_var2 = 4)), tile);
                tile++;
                D_80097944++;
            }
            polyCount++;
            entity++;
        }
    }

    if (g_GpuUsage.drawModes < 0x400U) {
        SetDrawMode(sp20, 0, 0, (blendMode - 1) << 5, &D_800ACD80);
        AddPrim(temp_s7 + var_s8 * 4, sp20);
        g_GpuUsage.drawModes++;
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80106A28);

bool func_8010715C(s32 mapTilesetId) {
    if (D_8006C3B0 != 0)
        return false;

    if (D_800978AC == 0) {
        if (func_800E81FC(mapTilesetId, 0xD) < 0) {
            return false;
        }
    } else {
        D_8006C398 = 1;
        D_8006BAFC = 0x1C;
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

void func_80107360(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
                   s32 v) {
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

void func_801073C0(void) {
    CdReadyCallback(NULL);
    CdDataCallback(NULL);
}

s32 func_801073E8(void) {
    u8 sp10;

    if (CdSync(1, &sp10) == 0) {
        D_80137F9C = 0;
        return D_80137F9C;
    } else {
        if (((u32)(func_80019444() - 0x10) < 2) || (!(sp10 & 0x10))) {
            CdControlF(1, 0);
            D_80137F9C = 0;
            return D_80137F9C;
        }
        D_80137F9C = 1;
        return D_80137F9C;
    }
}

void func_80107460(void) {
    D_80137F7C = &D_801EC000[D_80137F6C << 0x9];
    CdGetSector(D_80137F7C, 0x200);
    D_80137F6C = (D_80137F6C + 1) & 7;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", CopyMapOverlayCallback);
// https://decomp.me/scratch/1AWN1

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107614);
// https://decomp.me/scratch/U0IGY

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107750);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801078C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107B04);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107C6C);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107DB4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80107EF0);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801080DC);

void func_8010838C(s32 arg0) {
    func_801073C0();
    D_8006C398 = arg0;
}

void func_801083BC(void) {
    D_8006C398 = 1;
    D_8006BAFC = 25;
    D_8013AE9C = 10;
    D_800ACC64[0] = 0;
}

bool func_801083F0(void) {
    D_8006C398 = 1;
    D_8006BAFC = 0x19;

    if (D_8013AE9C == 0) {
        return false;
    } else {
        D_8013AE9C--;
        D_800ACC64[0] += 4;
    }

    return true;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80108448);

// https://decomp.me/scratch/QZk8K
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801092E8);

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.unk1E;

    D_80072F20.unk66 = 0;
    if ((*player_unk1E == 0x800) && (PLAYER.step == 8)) {
        PLAYER.unk1E = 0;
        PLAYER.animCurFrame = 0x9D;
        PLAYER.facing = (PLAYER.facing + 1) & 1;
    }

    if (D_80072F16[0] != 0) {
        D_80072F16[0] = 0;
        func_801092E8(0);
    }
    PLAYER.blendMode = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801093C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80109594);

void func_80109990(void) {
    if (D_80137FB4 == 0) {
        if ((D_80097BA0.mp == D_80097BA0.mpMax) && !(D_80072F2C & 0x100000)) {
            func_8011AAFC(g_CurrentEntity, 0x28, 0);
            PlaySfx(NA_SE_PL_MP_GAUGE);
            D_80137FB4++;
        }
    } else if (D_80097BA0.mp != D_80097BA0.mpMax) {
        D_80137FB4 = 0;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80109A44);

// regalloc
// https://decomp.me/scratch/rdeqb
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010A234);
#else
void func_8010A234(s32 arg0) {
    s32 temp;
    g_CurrentEntity = g_EntityArray;
    temp = D_8017A018();

    do { // !FAKE
        if ((temp == 0x2D) && (CheckEquipmentItemCount(0x19, 2) != 0)) {
            if (!(*(s32*)&D_80072F2C & 0x01000000)) {
                PlaySfx(NA_SE_VO_AL_WHAT);
                *D_80072EF4 = 0;
                D_80072EFC = 0x20;
                func_8010FAF4();
                D_8017A000();
                *(s32*)&D_80072F2C |= 0x01000000;
                func_8010DFF0(1, 10);
                func_80109328();
                if (arg0 != 0) {
                    func_8010DBFC(&D_800B0130, &D_800B01B8);
                }
            }
        } else if (*(s32*)&D_80072F2C & 0x01000000) {
            g_EntityArray[PLAYER_CHARACTER].palette = 0x8100;
            g_EntityArray[PLAYER_CHARACTER].animSet = 1;
            g_EntityArray[PLAYER_CHARACTER].unk5A = 0;
            g_EntityArray[PLAYER_CHARACTER].unk1E = 0;
            g_EntityArray[PLAYER_CHARACTER].unk19 &= 0xF3;
            func_8010FAF4();
            g_EntityArray[PLAYER_CHARACTER].unk22 = 0;
            g_EntityArray[PLAYER_CHARACTER].unk20 = 0;
            if (D_80072F20.pl_vram_flag & 1) {
                func_8010E570(0);
            } else {
                func_8010E7AC();
            }
            *(s32*)&D_80072F2C &= 0xFEFF0000 | 0xFFFF;
            func_80111CC0();
            if (arg0 != 0) {
                func_8010DBFC(&D_800B0130, &D_800B01B8);
            }
        }
    } while (0);
}
#endif

// Matching in gcc 2.6.0 + aspsx 2.3.4
// Matching in gcc 2.7.2 + aspsx (the one in decomp.me)
// https://decomp.me/scratch/oKHMJ
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010A3F0);
#else
void func_8010A3F0(void) {
    s32 temp = 0x38;

    if ((D_8017A018() == temp) && (D_8017D018() == temp)) {
        if (D_80072F16[0] == 0) {
            func_801092E8(1);
        }
        D_80072F16[0] = 0x20;
        temp = D_80072F30 != 0;
        if (temp && (D_80097C40[0] < -1)) {
            D_80097C40[0]++;
        }
    }
    D_80072F30 = 0;
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010A4A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", UpdateEntityAlucard);

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
        arg0->unk14 = D_800ACEC6.unk1A - ((D_80072F2C / 2) & 2);
        arg0->unk1C = D_800ACEC6.unk1C + ((D_80072F2C / 2) & 2);
        arg0->unk18 = D_800ACEC6.unk10 - 1;
        arg0->unk20 = D_800ACEC6.unk0 + 1;
    } else {
        D_8013C00C();
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010BFFC);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010C36C);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010C9F4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010D010);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010D2C8);

void func_8010D584(s16 step) {
    PLAYER.step = step;
    PLAYER.unk2E = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010D59C);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010D800);

void func_8010DA2C(s32* arg0) {
    g_CurrentEntity->unk4C = arg0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

void func_8010DA48(u32 arg0) {
    g_CurrentEntity->unkAC = arg0;
    g_CurrentEntity->animFrameDuration = 0;
    g_CurrentEntity->animFrameIdx = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010DA70);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010DB38);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010DBFC);

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", UpdateAnim);
#else
void UpdateAnim(FrameProperty* frameProps, s32* arg1) {
    AnimationFrame* animFrame;
    s8* frameProp;
    if (g_CurrentEntity->animFrameDuration == -1) {
    } else if (g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameDuration =
            g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
    } else if (--g_CurrentEntity->animFrameDuration == 0) {
        g_CurrentEntity->animFrameIdx++;
        animFrame = &g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx];
        switch ((u32)animFrame->duration) {
        case 0:
            g_CurrentEntity->animFrameIdx = animFrame->unk2;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].duration;
            break;

        case 0xFFFF:
            g_CurrentEntity->animFrameIdx =
                g_CurrentEntity->animFrameIdx + 1 + animFrame->duration;
            g_CurrentEntity->animFrameDuration = -1;
            break;

        case 0xFFFE:
            g_CurrentEntity->unk4C = (s32*)arg1[animFrame->unk2];
            g_CurrentEntity->animFrameIdx = 0;
            g_CurrentEntity->animFrameDuration =
                g_CurrentEntity->unk4C[0].duration;
            break;

        default:
            g_CurrentEntity->animFrameDuration = animFrame->duration;
            break;
        }
    }
    if (frameProps != 0) {
        frameProp =
            frameProps +
            (g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].unk2 >> 9);
        g_CurrentEntity->unk10 = *(frameProp++);
        g_CurrentEntity->unk12 = *(frameProp++);
        g_CurrentEntity->hitboxWidth = frameProp[0];
        g_CurrentEntity->hitboxHeight = frameProp[1];
    }
    g_CurrentEntity->animCurFrame =
        g_CurrentEntity->unk4C[g_CurrentEntity->animFrameIdx].unk2 & 0x1FF;
}
#endif

void func_8010DF70(void) {
    g_CurrentEntity = &PLAYER;

    switch (PLAYER.unkAC) {
    case 0xBA:
    case 0xBB:
    case 0xBE:
    case 0xF0:
    case 0xF1:
        func_8010DBFC(D_800B0130, D_800B01B8);
    }
}

void func_8010DFF0(s32 arg0, s32 arg1) {
    POLY_GT4* poly;
    s32 i;

    if (arg0 != 0) {
        g_EntityArray[UNK_ENTITY_1].unk7C.U8.unk1 = 1;
        g_EntityArray[UNK_ENTITY_3].animCurFrame = 0;
        g_EntityArray[UNK_ENTITY_2].animCurFrame = 0;
        g_EntityArray[UNK_ENTITY_1].animCurFrame = 0;
        poly = &D_80086FEC[g_EntityArray[UNK_ENTITY_1].firstPolygonIndex];

        for (i = 0; i < 6; i++) {
            poly->x1 = 0;
            poly = (POLY_GT4*)poly->tag;
        }
    }

    g_EntityArray[UNK_ENTITY_1].unk7C.U8.unk0 = 1;
    g_EntityArray[UNK_ENTITY_1].unk7E.modeU8.unk0 = 10;

    if (arg1 != 0) {
        if (arg1 < 4) {
            D_80072F1E = 4;
        } else {
            D_80072F1E = arg1;
        }
    }
}

void func_8010E0A8(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7E.modeU8.unk0 = 0;
}

void func_8010E0B8(void) {
    Entity* entity = &g_EntityArray[UNK_ENTITY_1];

    entity->unk7C.U8.unk1 = 0;
    entity->unk7C.U8.unk0 = 0;
}

void func_8010E0D0(s32 arg0) {
    Entity* entity;

    if (arg0 == 1) {
        entity = func_8011AAFC(g_EntityArray, 0x47002C, 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }

        entity = func_8011AAFC(g_EntityArray, 0x40002C, 0);

        if (entity != NULL) {
            entity->flags |= FLAG_UNK_10000;
        }
    }
    func_8010DFF0(1, 1);
}

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        func_8011AAFC(g_CurrentEntity, 0x15002C, 0);
        if (arg1 >= D_80072F1A[0]) {
            D_80072F1A[0] = arg1;
        }
    } else if (D_80072F1C[0] <= arg1) {
        D_80072F1C[0] = arg1;
    }
}

void func_8010E1EC(s32 speed) {
    if (g_CurrentEntity->accelerationX < 0) {
        g_CurrentEntity->accelerationX += speed;
        if (g_CurrentEntity->accelerationX > 0) {
            g_CurrentEntity->accelerationX = 0;
        }
    } else {
        g_CurrentEntity->accelerationX -= speed;
        if (g_CurrentEntity->accelerationX < 0)
            g_CurrentEntity->accelerationX = 0;
    }
}

void func_8010E234(s32 speed) {
    if (g_CurrentEntity->accelerationY < 0) {
        g_CurrentEntity->accelerationY += speed;
        if (g_CurrentEntity->accelerationY > 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    } else {
        g_CurrentEntity->accelerationY -= speed;
        if (g_CurrentEntity->accelerationY < 0) {
            g_CurrentEntity->accelerationY = 0;
        }
    }
}

s32 func_8010E27C(void) {
    u16* facing;

    if (D_80072F20.unk44 & 2) {
        return 0;
    }

    facing = &PLAYER.facing;
    if (*facing == 1) {
        if (D_80072EE8 & 0x2000) {
            *facing = 0;
            D_80072F6C = 1;
            return -1;
        } else if (D_80072EE8 & 0x8000) {
            return 1;
        }
    } else {
        if (!(D_80072EE8 & 0x2000)) {
            if (D_80072EE8 & 0x8000) {
                *facing = 1;
                D_80072F6C = 1;
                return -1;
            }
            return 0;
        }
        return 1;
    }
    return 0;
}

// https://decomp.me/scratch/YvoMU
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010E334);

/*
 * Updates the Entity acceleration in the X Axis
 */
void AccelerateX(s32 accelerationX) {
    if (g_CurrentEntity->facing == 1) {
        accelerationX = -accelerationX;
    }
    g_CurrentEntity->accelerationX = accelerationX;
}

/*
 * Updates the Player acceleration in the X Axis
 */
void func_8010E3B8(s32 accelerationX) {
    if (PLAYER.objectRoomIndex == 1) {
        accelerationX = -accelerationX;
    }
    PLAYER.accelerationX = accelerationX;
}

void func_8010E3E0(void) {
    if (D_80072F20.unk48 != 0) {
        DestroyEntity(&g_EntityArray[16]);
        D_80072F20.unk48 = 0;
    }
}

void func_8010E42C(u16 arg0) {
    PLAYER.unk2E = arg0;
    PLAYER.step = 18;

    if (!(arg0 & 1)) {
        func_8010DA48(0xF4);
    } else {
        func_8010DA48(0xF5);
    }
}

void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.accelerationX = arg1;
    PLAYER.accelerationY = 0;
    PLAYER.step = 2;
    PLAYER.unk2E = D_800ACF4C[arg0 * 2 + 0];
    func_8010DA48(D_800ACF4C[arg0 * 2 + 1]);
}

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = 0x8100;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;

    if ((u32)(D_80072F20.unk72 - 1) < 2U) {
        func_8010DA48(0xC7);
        PLAYER.accelerationY = 0;
        PLAYER.accelerationX = 0;
        func_8010D584(6);
        func_80111CC0();
        PlaySfx(NA_SE_VO_AL_WHAT);
        return;
    }
    func_80111CC0();
    func_8010E470(0, 0);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010E570);
void func_8010E570(/*?*/ s32);

void func_8010E6AC(s32 arg0) {
    bool condition = false;

    condition = ((D_80072F20.pl_vram_flag & 0x20) != condition);
    AccelerateX(0x18000);
    PLAYER.accelerationY = 0;
    func_8010D584(1);

    if (arg0 != 0) {
        if (PLAYER.unkAC != 0xD) {
            func_8010DA48(0xD);
        }
    } else {
        func_8010DA48(7);
        func_8011AAFC(g_CurrentEntity, 0x50001, 0);
    }

    if (D_80072F20.unk4C != 0) {
        PLAYER.unkAC = 9;
    }

    if ((PLAYER.unkAC == 7) && (condition)) {
        PLAYER.animFrameIdx = 1;
    }

    if (D_80072F20.unk50 == 2) {
        PLAYER.animFrameIdx = 4;
    }
}

void func_8010E7AC(void) {
    func_8010D584(3);

    if (D_80072F20.unk50 != 1) {
        func_8010DA48(0x1C);
    }

    PLAYER.accelerationY = 0x20000;
    PLAYER.accelerationX = 0;
    D_80072F0C = 8;

    if (D_80072F20.unk04 & 1) {
        D_80072F0A[0] = 8;
    } else {
        D_80072F0A[0] = 0;
    }

    D_80072F20.unk44 = 0x10;
}

void func_8010E83C(s32 arg0) {
    if (D_80072F92 != 0) {
        func_8010E7AC();
        return;
    } else if (func_8010E27C() != 0) {
        func_8010DA48(0x1A);
        AccelerateX(0x18000);
        D_80072F20.unk44 = 0;
    } else {
        func_8010DA48(0x16);
        PLAYER.accelerationX = 0;
        D_80072F20.unk44 = 4;
    }

    PLAYER.accelerationY = 0xFFFB0000 | 0x2000;
    func_8010D584(4);

    if (D_80072F70 == 1) {
        D_80072F64 |= 0x10;
    }

    if (arg0 != 0) {
        D_80072F64 &= ~1;
    } else {
        D_80072F64 |= 1;
    }
}

void func_8010E940(void) {
    D_80072F20.unk44 |= 0x21;
    func_8010DA48(0x20);
    PLAYER.unk2E = 0;
    PLAYER.accelerationY = -0x44000;
    if (D_80072F20.unk72 != 0) {
        PLAYER.accelerationY = 0;
    }
}

void func_8010E9A4(void) {
    if (func_8010E27C() != 0) {
        AccelerateX(0x30000);
    } else {
        PLAYER.accelerationX = 0;
    }

    if (PLAYER.step == 4) {
        D_80072F20.unk44 |= 1;
    } else {
        D_80072F20.unk44 = 0;
    }

    func_8011AAFC(g_CurrentEntity, 2, 0);
    func_8010D584(8);
    PLAYER.accelerationY = -0xC0000;
    func_8010DA48(0x21);
    D_80072F20.unk4A = 0;
}

// https://decomp.me/scratch/9jKqU
// matching in decomp.me, probably aspsx
// TODO: aspatch div macro
// https://discord.com/channels/710646040331681844/815529862604390411/1051628313073958992
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010EA54);
#else
void func_8010EA54(s32 arg0) {
    s16 temp_hi;

    if (arg0 != 0) {
        temp_hi = rand() % arg0;

        if (temp_hi < 4) {
            PlaySfx(D_800ACF60[temp_hi]);
        }
    }
}
#endif

s32 func_8010EADC(s16 arg0, s16 arg1) {
    Entity* entity = &g_EntityArray[0x20];
    s32 i;
    s32 var_a2;
    s32 ret;

    for (i = 0, var_a2 = 0, ret = 0; i < 16; i++) {
        if (entity->objectId == 0) {
            ret++;
        }

        if (entity->unkB0 != 0) {
            if (entity->unkB0 == arg0) {
                var_a2++;
            }
        }

        if (var_a2 >= arg1) {
            return -1;
        }
        entity++;
    }

    return (ret == 0) ? -1 : 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010EB5C);

// https://decomp.me/scratch/N8Srk
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010EC8C);

void func_8010ED54(u8 arg0) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0xF);
    func_8010DA48(arg0);
    func_8011AAFC(g_CurrentEntity, 0x14003D, 0);
    D_80072F68 = 0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010EDB8);

void func_8010FAF4(void) {
    DestroyEntity(&g_EntityArray[UNK_ENTITY_10]);
    D_80072F66 = 0;
}

void func_8010FB24(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x22);
    func_8010E168(1, 0x10);
    func_8010E3E0();
}

void func_8010FB68(void) { // Related to Dark Methamorphosis
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x20);
    func_8010E3E0();
    func_8010DA48(0xBA);
    PlaySfx(NA_SE_VO_AL_DARK_METAMORPHOSIS);
    PlaySfx(NA_SE_PL_MP_GAUGE);
    D_80072F16[0] = func_800FDB18(3, 0x400);
    func_801092E8(1);
    func_8011AAFC(g_CurrentEntity, 0x110028, 0);
    func_80118C28(0xB);
}

void func_8010FBF4(void) { // Related to Soul Steal spell
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x25);
    func_8010E3E0();
    func_8010DA48(0xDA);
    PlaySfx(NA_SE_VO_AL_SOUL_STEAL);
    func_80118C28(0xC);
    D_80072F18 = 4;
}

void func_8010FC50(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x21);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x75, 0);
    func_8010DA48(0xF0);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    D_80072F18 = 4;
}

void func_8010FCB8(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x23);
    func_8010E3E0();
    func_8011AAFC(g_CurrentEntity, 0x10075, 0);
    func_8010DA48(0xF1);
    PlaySfx(NA_SE_VO_AL_PUNCH);
    D_80072F18 = 4;
}

void func_8010FD24(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0x27);
    func_8010E3E0();
    func_8010DA48(0xF1);
    func_8011AAFC(g_CurrentEntity, 0x170028, 0);
    D_80072F18 = 4;
}

void func_8010FD88(void) {
    PLAYER.step = 0;
    PLAYER.unk2E = 3;
    AccelerateX(0xFFFC8000);
    g_CurrentEntity->accelerationY = 0;
    func_8010DA48(0xDB);
    func_8011AAFC(g_CurrentEntity, 0, 0);
    D_80072F66 = 0;
    PlaySfx(NA_SE_AL_BACKSLIDE);
}

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8010FDF8);
s32 func_8010FDF8(/*?*/ s32);

// https://decomp.me/scratch/Akstc 94.80%
INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80110394);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801104D0);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801106A4);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8011081C);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80110968);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80110BC8);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80110DF8);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_80111018);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_801112AC);

INCLUDE_ASM("asm/us/dra/nonmatchings/62D70", func_8011151C);