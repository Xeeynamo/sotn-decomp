#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FD874);
#else
void func_800FD874(u16 context, s32 arg1) {
    u8* temp_a0_2;
    u8* temp_v0;
    u8 temp_a1;
    u8 temp_v1;
    u8* phi_a0;
    u8* phi_a0_2;
    u16 i;
    s32 phi_a1;
    s32 phi_a1_2;
    u8* cursorY = func_800FD744(arg1);
    u8* temp_a3 = func_800FD760(arg1);
    u16 temp_a2 = context & 0xFFFF;
    u8* temp_a0 = temp_a3 + temp_a2;
    if (*temp_a0 < 0x63) {
        temp_a1 = *temp_a0;
        *temp_a0 = temp_a1 + 1;
        if (*temp_a0 == 1) {
            *temp_a0 = temp_a1;
            if (arg1 != 0) {
                i = D_800A7734[temp_a2 << 5];
            }
            phi_a0 = cursorY;
            phi_a1 = 0;
            phi_a1_2 = 0;
            while (true) {
                if (*++phi_a0 == temp_a2)
                    break;
                phi_a1_2 += 1;
            }
            phi_a0_2 = cursorY;
        loop_8:
            temp_v1 = *phi_a0_2;
            if (*((s8*)temp_a3 + temp_v1) != 0) {
            block_12:
                phi_a0_2 += 1;
                phi_a1 += 1;
                goto loop_8;
            }
            if ((arg1 != 0) && (i != D_800A7734[temp_v1 << 5])) {
                goto block_12;
            }

            temp_v0 = temp_a3 + (context & 0xFFFF);
            *temp_v0 += 1;
            temp_a0_2 = &cursorY[phi_a1];
            if (phi_a1 < phi_a1_2) {
                cursorY[phi_a1_2] = *temp_a0_2;
                *temp_a0_2 = context;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FD9D4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FDB18);

bool func_800FDC94(s32 arg0) {
    u8 temp = D_800A841C[arg0 * 0x1C];

    if (g_playerMP.current < (s32)temp) {
        return false;
    } else {
        g_playerMP.current -= temp;
        return true;
    }
}

// https://decomp.me/scratch/5ufgy
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FDCE0);

bool func_800FDD44(s32 equipHeadIndex) {
    s32 equippedItem;
    u8 temp_s1;
    u8 temp_v0;

    equippedItem = g_playerEquip[equipHeadIndex];
    temp_s1 = D_800A4B1D[g_playerEquip[equipHeadIndex]].unk0;
    if (!CheckEquipmentItemCount(0x54, 4)) {
        if (temp_s1 != 0) {
            temp_v0 = D_8009798A[equippedItem];
            if (temp_v0 == 0) {
                g_playerEquip[equipHeadIndex] = 0;
                func_800F53A4();
                return true;
            }
            D_8009798A[equippedItem]--;
        }
    }
    return false;
}

void func_800FDE00(void) {
    D_80137960 = 0;
    D_80137964 = 0;
    D_80137968 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FDE20);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FE044);

bool func_800FE3A8(s32 arg0) {
    /*
     * also matches without the temp like this:
     * return (D_80097964[arg0] & ~0xfd) != 0;
     * if that array contains a bitmask, it would make
     * more sense that way.
     */
    s32 temp = 2;

    return (D_80097964[arg0] & temp) != 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FE3C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FE728);

bool HasEnoughMp(s32 mpCount, bool subtractMp) {
    if (g_playerMP.current >= mpCount) {
        if (subtractMp != 0) {
            g_playerMP.current -= mpCount;
        }
        return false;
    }
    return true;
}

void func_800FE8F0(void) {
    if (D_8013B5E8 == 0) {
        D_8013B5E8 = 0x40;
    }
}

void AddHearts(s32 value) {
    if (g_playerHeart->current < g_playerHeart->max) {
        g_playerHeart->current += value;
        if (g_playerHeart->max < g_playerHeart->current) {
            g_playerHeart->current = g_playerHeart->max;
        }
        func_8011AAFC(g_EntityArray, 99, 0);
        PlaySfx(NA_SE_PL_COLLECT_HEART);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FE97C);

// !FAKE: explicitly casting two pointers to s32
// before comparing them, that's weird
void func_800FEE6C(void) {
    s32* var_v1 = D_80139828;

    do {
        if (*var_v1 != 0) {
            *var_v1 -= 1;
        }
        var_v1++;
    } while ((s32)var_v1 < (s32)&D_80139828[0x10]);
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FEEA4);

s32 func_800FF064(s32 arg0) {
    s32 playerMP;

    playerMP = g_playerMP.current - 4;

    if (playerMP > 0) {
        if (arg0 != 0) {
            g_playerMP.current = playerMP;
        }
        return 0;
    }
    return -1;
}

void func_800FF0A0(s32 context) { D_80139828[context] = 0; }

void func_800FF0B8(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        func_800FF0A0(i);
    }
}

void func_800FF0F4(s32 arg0) { D_80139828[arg0] = 0x1000; }

s32 func_800FF110(s32 arg0) { return D_80139828[arg0]; }

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FF128);

s32 func_800FF460(s32 arg0) {
    if (arg0 == 0) {
        return 0;
    }
    return arg0 + ((arg0 * D_80097BE4) >> 7);
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FF494);

void func_800FF60C(void) {
    s32 var_a0_2;
    s32 i;

    func_800EA538(6);

    i = 0;
    while (1) {
        if (g_playerEquip[4] == D_800A2FBC[i]) {
            break;
        }

        if (D_800A2FBC[i] == -1) {
            break;
        }
        i += 2;
    }

    var_a0_2 = D_800A2FC0[i];
    if ((g_playerEquip[4] == 0x32) && (g_SettingsCloakMode != 0)) {
        var_a0_2++;
    }
    func_800EA5E4(var_a0_2);
    if (g_playerEquip[4] == 0x38) {
        func_800EA5E4(0x415);
    }
}

void func_800FF60C();

void func_800FF6C4(void) {
    if ((g_mapProgramId != 0x1F) &&
        (g_CurrentPlayableCharacter == PLAYER_ALUCARD)) {
        func_800FF60C();
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FF708);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_800FF7B8);

extern Unkstruct_80137990 D_80137990;

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", DrawHudRichter);
#else
void DrawHudRichter(void) {
    POLY_GT4* poly;

    D_80137978 = 0x190;
    D_8013797C = 0x190;
    D_801397FC = 0;
    D_80139008 = 0;
    D_80137994 = 0;
    D_8003C744 = NULL;
    D_80137980 = 50;
    D_80137984 = 0;
    D_80137990.unk0 = 0;
    D_8013798C = 0x9C40U / 400U;
    D_80137988 = 0x9C40U / 400U;
    D_80137970 = func_800EDD9C(4, 9);
    poly = &D_80086FEC[D_80137970];

    func_80107360(poly, 2, 22, 32, 96, 0, 0);
    poly->tpage = 0x1B;
    poly->clut = 0x101;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 216, 22, 32, 96, 32, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x100;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 4, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x105;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 228, 112, 9, 3, 64, 89);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly->p1 = 0;
    poly->p2 = 6;
    poly = poly->tag;

    func_80107360(poly, D_80137980 + 236, 112, 9, 3, 64, 89);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 14, 27, 8, 8, 0, 96);
    poly->tpage = 0x1BU;
    poly->clut = 0x103U;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 22, 27, 8, 8, 0, 96);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1F0;
    poly->pad3 = 0x2000;
    poly = poly->tag;

    func_80107360(poly, 18, 38, 8, 8, 0, 0);
    poly->tpage = 0x1BU;
    poly->clut = 0x102;
    poly->pad2 = 0x1F0U;
    poly->pad3 = 0x2000U;
    poly = poly->tag;

    func_80107360(poly, 33, 20, 64, 24, 64, 40);
    poly->tpage = 0x1B;
    poly->clut = 0x103;
    poly->pad2 = 0x1EF;
    poly->pad3 = 0x2000;

    D_80137974 = func_800EDD9C(4, 16);
    poly = &D_80086FEC[D_80137974];
    if (poly != 0) {
        s32 phi_s1 = 0x20;
        s32 phi_s0 = 0xD8;
        do {
            func_80107360(poly, phi_s0, 22, 2, 96, phi_s1, 0);
            func_801072DC(poly);
            poly->tpage = 0x1B;
            poly->clut = 0x100;
            poly->pad2 = 0x1EE;
            poly->pad3 = 8;
            poly->p1 = (rand() & 0x3F) + 1;
            poly->p2 = 0;
            poly = poly->tag;
            phi_s0 += 2;
            phi_s1 += 2;
        } while (poly != 0);
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80100B50);

extern Unkstruct_80137990 D_80137990;

bool func_8010183C(s32 arg0) {
    if (arg0 == 0) {
        if (D_80137990.unk0 == 0) {
            D_80137990.unk0 = 1;
            return true;
        }
        return false;
    } else if (arg0 == 1) {
        if (D_80137990.unk0 == 0x15) {
            D_80137990.unk0 = 0x33;
            return true;
        }
        return false;
    }
    return true;
}
void DrawHudRichter(void);

void func_8010189C(void) {
    POLY_GT4* poly;
    s32 i;
    u16* new_var;

    D_8013B5E8 = 0;
    D_80137998 = 0;
    D_8013796C = g_playerHp.current;

    if ((g_mapProgramId == PROGRAM_ST0) ||
        (g_CurrentPlayableCharacter != PLAYER_ALUCARD)) {
        DrawHudRichter();
        return;
    }

    D_80137970 = func_800EDD9C(4, 14);
    poly = &D_80086FEC[D_80137970];

    if (poly != NULL) {
        for (i = 0; poly != NULL; i++) {
            func_80107360(poly, D_800A2EE8[i], D_800A2EF8[i], D_800A2F28[i],
                          D_800A2F38[i], D_800A2F08[i], D_800A2F18[i]);
            poly->tpage = 0x1F;
            new_var = &D_800A2F48[i];
            poly->clut = *new_var;
            poly->pad2 = 0x1F0;
            poly->pad3 = D_800A2F64[i];

            if (i == 5) {
                SetPolyRect(poly, D_800A2EED, D_800A2EFD, D_800A2F3D,
                            D_800A2F2D);
                poly->y0 = poly->y2;
                poly->x1 = poly->x0;
                poly->x2 = poly->x3;
                poly->y3 = poly->y1;
            }

            if (i == 1) {
                poly->p1 = 0;
                poly->p2 = rand() + 8;
                poly->p3 = (7 & rand()) + 1;
            }

            poly = (POLY_GT4*)poly->tag;
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80101A80);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801024DC);

extern Unkstruct_80086FFA D_80086FFA[];

u16 func_801025F4(void) { return D_80086FFA[D_8013799C].unk0; }

void func_80102628(s32 arg0) {
    POLY_GT4* poly;
    s32 temp;
    s32 i = 0;

    poly = &D_80086FEC[D_8013799C];

    if (poly != NULL) {
        temp = arg0 / 2;
        while (poly != NULL) {
            poly->y0 = 0;
            poly->u0 = (u8)temp;
            poly->v0 = 0xF0;
            poly->b0 = 0;
            poly->g0 = 0;
            poly->r0 = 0;
            poly->pad2 = 0x1FD;
            poly->pad3 = 8;
            poly->x0 = temp * (i & 1);
            poly = (POLY_GT4*)poly->tag;
            i++;
        }
    }
}

void func_801026BC(s32 arg0) {
    POLY_GT4* poly = &D_80086FEC[D_801379A0];

    if (arg0 == 0) {
        poly->pad3 = 8;
        return;
    } else if (!(g_mapProgramId & 0x20)) {
        SetPolyRect(poly, 0, 1, 255, 255);
    } else {
        poly->x2 = 255;
        poly->x0 = 255;
        poly->y1 = 240;
        poly->y0 = 240;
        poly->x3 = 0;
        poly->x1 = 0;
        poly->y3 = -15;
        poly->y2 = -15;
    }

    func_80107250(poly, arg0 * 2);

    if (arg0 == 0x40) {
        poly->pad3 = 0;
    } else {
        poly->pad3 = 0x35;
    }
}

void func_801027A4(void) { func_801026BC(0); }

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801027C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801028AC);

// https://decomp.me/scratch/8D47k
// Matches in gcc 2.6.0, aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80102CD8);
#else
extern s32 D_800A3194[];
extern u16 D_801379AC[2];
extern s32 D_801379B0;

void func_80102CD8(s32 arg0) {
    D_801379AC[0] = arg0;
    D_801379AC[1] = 0;
    D_801379B0 = D_800A3194[arg0];
}
#endif

// https://decomp.me/scratch/NNXbc
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80102D08);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80102D70);

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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80102EB8);

void func_801030B4(s32 arg0, POLY_GT4* poly, s32 arg2) {
    s32 var_v1;

    if (arg2 == arg0) {
        if (g_blinkTimer & 0x20) {
            var_v1 = (g_blinkTimer & 0x1F) + 0x60;
        } else {
            var_v1 = 0x7F - (g_blinkTimer & 0x1F);
        }

        poly->r0 = poly->r1 = var_v1 - 0x10;
        poly->r2 = poly->r3 = var_v1 + 0x10;
        poly->b3 = 0;
        poly->b2 = 0;
        poly->b1 = 0;
        poly->b0 = 0;
        poly->pad3 = 0x404;
    } else {
        poly->b1 = 0x60;
        poly->b0 = 0x60;
        poly->b3 = 0x80;
        poly->b2 = 0x80;
        poly->r3 = 0;
        poly->r2 = 0;
        poly->r1 = 0;
        poly->r0 = 0;
        poly->pad3 = 0x415;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80103148);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80103238);

void func_80103EAC(void) {
    D_80137E4C = 0;
    func_800E92F4();
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80103ED4);

void func_8010427C(void) {
    FreePolygons(D_80137E40);
    FreePolygons(D_80137E44);
    FreePolygons(D_80137E48);
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801042C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80104790);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80105078);

void func_80105408(void) {
    D_80072EF4 = 0x1000;
    D_80072EFC = 1;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80105428);

void func_80106590(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
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
        func_80106590(pItem);
}

// Print debug hitboxes
void func_80106670(s32 blendMode);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80106670);
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
    sp20 = &temp_a0->drawModes[D_8009792C.unk0];
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

    if (D_8009792C.unk0 < 0x400U) {
        SetDrawMode(sp20, 0, 0, (blendMode - 1) << 5, &D_800ACD80);
        AddPrim(temp_s7 + var_s8 * 4, sp20);
        D_8009792C.unk0++;
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80106A28);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010715C);

void func_801071CC(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
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

void func_80107250(POLY_GT4* poly, s32 arg1) {
    func_801071CC(poly, arg1, 0);
    func_801071CC(poly, arg1, 1);
    func_801071CC(poly, arg1, 2);
    func_801071CC(poly, arg1, 3);
}

void func_801072BC(POLY_GT4* poly) { func_80107250(poly, 0); }

void func_801072DC(POLY_GT4* poly) { func_80107250(poly, 0x80); }

void func_801072FC(POLY_G4* poly) {
    poly->r0 = 0;
    poly->g0 = 0;
    poly->b0 = 0;

    poly->r1 = 0;
    poly->g1 = 0;
    poly->b1 = 0;

    poly->r2 = 0;
    poly->g2 = 0;
    poly->b2 = 0;

    poly->r3 = 0;
    poly->g3 = 0;
    poly->b3 = 0;
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
        if ((((u32)(func_80019444() - 0x10)) < 2) || (!(sp10 & 0x10))) {
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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", CopyMapOverlayCallback);
// https://decomp.me/scratch/1AWN1

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107614);
// https://decomp.me/scratch/U0IGY

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107750);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801078C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107B04);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107C6C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107DB4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80107EF0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801080DC);

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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80108448);

// https://decomp.me/scratch/QZk8K
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801092E8);

void func_80109328(void) {
    s16* player_unk1E = &PLAYER.unk1E;

    D_80072F86 = 0;
    if ((*player_unk1E == 0x800) && (PLAYER.step == 8)) {
        PLAYER.unk1E = 0;
        PLAYER.animationFrame = 0x9D;
        PLAYER.facing = (PLAYER.facing + 1) & 1;
    }

    if (D_80072F16[0] != 0) {
        D_80072F16[0] = 0;
        func_801092E8(0);
    }
    PLAYER.blendMode = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801093C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80109594);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80109990);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80109A44);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010A234);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010A3F0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010A4A4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", UpdateEntityAlucard);

void func_8010BF64(Unkstruct_8010BF64* arg0) {
    if (g_CurrentPlayableCharacter == PLAYER_ALUCARD) {
        arg0->unk14 = D_800ACEC6.unk1A - ((D_80072F2C >> 1) & 2);
        arg0->unk1C = D_800ACEC6.unk1C + ((D_80072F2C >> 1) & 2);
        arg0->unk18 = D_800ACEC6.unk10 - 1;
        arg0->unk20 = D_800ACEC6.unk0 + 1;
        return;
    }
    D_8013C00C();
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010BFFC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010C36C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010C9F4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010D010);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010D2C8);

void func_8010D584(s16 step) {
    PLAYER.step = step;
    PLAYER.unk2E = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010D59C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010D800);

void func_8010DA2C(s32* arg0) {
    g_CurrentEntity->unk4C = arg0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

void func_8010DA48(u32 arg0) {
    g_CurrentEntity->unkAC = arg0;
    g_CurrentEntity->animationFrameDuration = 0;
    g_CurrentEntity->animationFrameIndex = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010DA70);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010DB38);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010DBFC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010DDA0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010DF70);

void func_8010DFF0(s32 arg0, s32 arg1) {
    POLY_GT4* poly;
    s32 i;

    if (arg0 != 0) {
        g_EntityArray[UNK_ENTITY_1].unk7C.U8.unk1 = 1;
        g_EntityArray[UNK_ENTITY_3].animationFrame = 0;
        g_EntityArray[UNK_ENTITY_2].animationFrame = 0;
        g_EntityArray[UNK_ENTITY_1].animationFrame = 0;
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
            entity->unk34 = entity->unk34 | 0x10000;
        }

        entity = func_8011AAFC(g_EntityArray, 0x40002C, 0);

        if (entity != NULL) {
            entity->unk34 = entity->unk34 | 0x10000;
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

    if (D_80072F64 & 2) {
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
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010E334);

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
    // D_80072F68 is part of a struct, the temp isn't needed in that case
    u16* temp = &D_80072F68;
    if (*temp != 0) {
        func_80106590(&g_EntityArray[16]);
        *temp = 0;
    }
}

void func_8010E42C(u16 arg0) {
    PLAYER.unk2E = arg0;
    PLAYER.step = 0x12;

    if (!(arg0 & 1)) {
        func_8010DA48(0xF4);
    } else {
        func_8010DA48(0xF5);
    }
}

// https://decomp.me/scratch/wgVVw // nop in between array assignments
// aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010E470);
#else
void func_8010E470(s32 arg0, s32 arg1) {
    PLAYER.accelerationX = arg1;
    PLAYER.accelerationY = 0;
    PLAYER.step = 2;
    PLAYER.unk2E = D_800ACF4C[arg0 * 2 + 0];
    func_8010DA48(D_800ACF4C[arg0 * 2 + 1]);
}
#endif

// This may be the function that turns Alucard into stone
void func_8010E4D0(void) {
    func_80111CC0();

    PLAYER.palette = 0x8100;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;

    if ((u32)(D_80072F92 - 1) < 2U) {
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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010E570);
void func_8010E570(/*?*/ s32);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010E6AC);

void func_8010E7AC(void) {
    func_8010D584(3);

    if (D_80072F70 != 1) {
        func_8010DA48(0x1C);
    }

    PLAYER.accelerationY = 0x20000;
    PLAYER.accelerationX = 0;
    D_80072F0C = 8;

    if (D_80072F24 & 1) {
        D_80072F0A = 8;
    } else {
        D_80072F0A = 0;
    }

    D_80072F64 = 0x10;
}

void func_8010E83C(s32 arg0) {
    if (D_80072F92 != 0) {
        func_8010E7AC();
        return;
    } else if (func_8010E27C() != 0) {
        func_8010DA48(0x1A);
        AccelerateX(0x18000);
        D_80072F64 = 0;
    } else {
        func_8010DA48(0x16);
        PLAYER.accelerationX = 0;
        D_80072F64 = 4;
    }

    PLAYER.accelerationY = 0xFFFB0000 | 0x2000;
    func_8010D584(4);

    if (D_80072F70 == 1) {
        D_80072F64 |= 0x10;
    }

    if (arg0 != 0) {
        D_80072F64 = D_80072F64 & ~1;
    } else {
        D_80072F64 = D_80072F64 | 1;
    }
}

void func_8010E940(void) {
    u16* temp = &D_80072F64;

    *temp |= 0x21;
    func_8010DA48(0x20);
    PLAYER.unk2E = 0;
    PLAYER.accelerationY = -0x44000;
    if (D_80072F92 != 0) {
        PLAYER.accelerationY = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010E9A4);

// https://decomp.me/scratch/9jKqU
// matching in decomp.me, probably aspsx
// TODO: aspatch div macro
// https://discord.com/channels/710646040331681844/815529862604390411/1051628313073958992
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010EA54);
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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010EB5C);

// https://decomp.me/scratch/N8Srk
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010EC8C);

void func_8010ED54(u8 arg0) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    func_8010D584(0xF);
    func_8010DA48(arg0);
    func_8011AAFC(g_CurrentEntity, 0x14003D, 0);
    D_80072F68 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010EDB8);

void func_8010FAF4(void) {
    func_80106590(&g_EntityArray[16]);
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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010FDF8);
s32 func_8010FDF8(/*?*/ s32);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80110394);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801104D0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801106A4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011081C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80110968);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80110BC8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80110DF8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80111018);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801112AC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011151C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80111830);

void func_80111928(void) { D_801396EA = 0; }

void func_80111938(void) {
    D_801396EA = 1;
    D_801396E4 = PLAYER.animationFrame;
    D_801396E6.S16.unk0 = PLAYER.unk19;
    D_801396E8 = PLAYER.palette;
}

void func_8011197C(void) {
    D_801396EA = 0;
    PLAYER.unk44 = 0;
    PLAYER.animationFrame = D_801396E4;
    PLAYER.unk19 = D_801396E6.S8.unk0;
    PLAYER.palette = D_801396E8;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801119C4);

void func_80111CC0(void) {
    if (D_80072F00[1] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x17002C, 0);
    }
    if (D_80072F00[0] != 0) {
        func_8011AAFC(g_CurrentEntity, 0x16002C, 0);
    }
}

bool func_80111D24(void) {
    CollisionResult collisionResult;
    s32 speed = 0xC000;
    s16 posX = PLAYER.posX.i.hi;
    s16 posY = PLAYER.posY.i.hi;
    s32 hitboxLeftMargin;
    s32 hitboxRightMargin;

    CheckCollision(posX - 7, posY, &collisionResult, 0);
    hitboxLeftMargin = collisionResult.unk0 & 0x10;
    CheckCollision(posX + 7, posY, &collisionResult, 0);
    hitboxRightMargin = collisionResult.unk0 & 0x10;

    if (hitboxRightMargin & hitboxLeftMargin) {
        AccelerateX(speed);
        return true;
    } else if (hitboxRightMargin != 0) {
        PLAYER.accelerationX = -speed;
        return true;
    } else if (hitboxLeftMargin != 0) {
        PLAYER.accelerationX = speed;
        return true;
    }
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80111DE8);

bool func_8011203C(void) {
    s32 collision = func_80111D24();

    if (g_EntityArray[UNK_ENTITY_10].step == 5) {
        if (collision == false) {
            func_80106590(&g_EntityArray[UNK_ENTITY_10]);
            return true;
        }
        return false;
    } else if (g_EntityArray[UNK_ENTITY_10].step <= 2) {
        if (g_EntityArray[UNK_ENTITY_10].step != 0) {
            D_80072F66 = 0;
            g_EntityArray[UNK_ENTITY_10].step = 3;
        }
    }
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801120B4);

void func_80112B64(void) {
    if (func_8010FDF8(0x4301C) == 0) {
        AccelerateX(0x18000);
        if (func_8010E27C() == 0) {
            func_8010E570(0);
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80112BB0);

void func_80113148(void) {
    if ((D_80072F0A != 0) && (D_80072EEC & 0x40)) {
        func_8010E83C(1);
    } else if (func_8010FDF8(0x9029) == 0) {
        func_8010E1EC(0x1000);
        if (func_8010E27C() != 0) {
            AccelerateX(0xC000);
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801131C4);

void func_801139CC(s32 arg0) {
    s32 move = PLAYER.facing != 0 ? -3 : 3;

    PLAYER.posY.i.hi -= 22;
    PLAYER.posX.i.hi = move + PLAYER.posX.i.hi;
    func_8011AAFC(g_CurrentEntity, 0x10004, 0);
    PLAYER.posY.i.hi = PLAYER.posY.i.hi + 22;
    PLAYER.posX.i.hi = PLAYER.posX.i.hi - move;

    if (arg0 & 1) {
        func_80102CD8(3);
        PlaySfx(NA_SE_SECRET_STAIRS);
    }
    if (arg0 & 2) {
        PLAYER.accelerationX = 0;
        PLAYER.accelerationY = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80113AAC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80113D7C);

// !FAKE: too many temps
s16 func_80113E68(void) {
    s16 rnd = rand();
    s32 temp_v0;
    s32 var_a1;

    temp_v0 = rnd;
    PLAYER.unkAC = (rnd % 3) + 0x2E;
    var_a1 = rnd;
    if (rnd < 0) {
        var_a1 = rnd + 0xF;
    }
    return (temp_v0 - ((var_a1 >> 4) * 0x10));
}

void func_80113EE0(void) {
    PLAYER.animationSet = 1;
    PLAYER.unk19 &= 0xF3;
    PLAYER.animationFrameDuration = 0;
    PLAYER.animationFrameIndex = 0;
    PLAYER.objectId = 0;
    PLAYER.blendMode = 0;
    D_80072F64 = 0;
    D_80072F66 = 0;
    PLAYER.unk1E = 0;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;
    if (g_EntityArray[UNK_ENTITY_10].objectId == 0x22) {
        func_8010FAF4();
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80113F7C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011405C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80114DF4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80115394);

void func_80115BB0(void) {
    PLAYER.unk19 = 4;
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    PLAYER.animationFrameDuration = 4;

    if (D_80097420 == 0) {
        if (D_80072F20 & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        func_8011AAFC(g_CurrentEntity, 0x4A0000 | 0x2C, 0);
        D_80097D37 = 0;
    }
}

void func_80115C50(void) {
    s32 dist;

    if (g_mapProgramId == PROGRAM_TOP) {
        dist = (g_CurrentRoom.left << 8) + playerX;
        dist = ABS(dist);

        if ((dist - 0x1F40) > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left << 8) + playerX;
        dist = ABS(dist);

        if ((dist - 0x1F40) < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_mapProgramId == 0x2B) {
        dist = (g_CurrentRoom.left << 8) + playerX;
        dist = ABS(dist);

        if ((dist - 0x20C0) > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left << 8) + playerX;
        dist = ABS(dist);

        if ((dist - 0x20C0) < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80115DA0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80115F54);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80116208);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80116408);

void func_801166A4(void) {
    switch (PLAYER.unk2E) {
    case 0:
        func_80113EE0();
        D_80072F60[0] = 0x8166;
        D_80072F04 = 6;
        PLAYER.accelerationX = 0;
        PLAYER.accelerationY = 0;
        PLAYER.unkAC = 0x33;
        func_8011AAFC(g_CurrentEntity, 0, 0);
        func_8011AAFC(g_CurrentEntity, 0x58002C, 0);
        PLAYER.unk2E++;
        break;

    case 1:
        if (PLAYER.animationFrameDuration < 0) {
            PlaySfx(NA_SE_VO_AL_WHAT);
            func_8010E570(0);
        }
        break;

    default:
        break;
    }
}

void func_8011678C(void) {
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    if (D_80072EF6 != 2) {
        func_8010E570(0);
    }
}

void func_801167D0(void) {
    s32* accelerationX = &PLAYER.accelerationX;
    PLAYER.accelerationY = 0;
    *accelerationX = 0;
    if (D_80072EF6 != 2) {
        PLAYER.step = 0x28;
        PLAYER.unk2E = 0;
        PLAYER.accelerationY = 0;
        *accelerationX = 0;
        PLAYER.unkAC = 0xCF;
        PLAYER.animationFrameIndex = 0;
        PLAYER.animationFrameDuration = 0;
    }
}

bool func_80116838(void) {
    if ((g_EntityArray->unk2E != 0) &&
        ((D_8009744C != 0) || (D_80072EEC & 8) || (func_800FEEA4(0, 1) < 0))) {
        func_8010D584(9);
        func_8010DA48(0xCA);
        D_800AFDA6 = 6;
        g_EntityArray->palette = 0x810D;
        D_80072F86 = 0;
        D_80072F88 = 0;
        func_8011AAFC(g_CurrentEntity, 0x21002C, 0);
        g_EntityArray->accelerationY = g_EntityArray->accelerationY >> 1;
        return true;
    }
    return false;
}

void func_8011690C(s16 arg0) {
    s16* player_unk1E = &PLAYER.unk1E;

    if (*player_unk1E < arg0) {
        *player_unk1E += 16;
        if (arg0 < *player_unk1E) {
            *player_unk1E = arg0;
        }
    }
    if (arg0 < *player_unk1E) {
        *player_unk1E -= 16;
        if (*player_unk1E < arg0) {
            *player_unk1E = arg0;
        }
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80116994);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80116B0C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801177A0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80117AC0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80117D3C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80117DEC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801182F8);

void func_80118614(void) {
    if (PLAYER.animationFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_80118640(void) {
    if (PLAYER.animationFrameDuration < 0) {
        func_8010E470(0, 0);
    }
}

void func_80118670(void) {
    s32* animationFrameIndex = (s32*)&PLAYER.animationFrameIndex;

    if (*animationFrameIndex == 0x10007) {
        func_8011AAFC(g_CurrentEntity, 0x160028, 0);
        PlaySfx(NA_SE_PL_MP_GAUGE);
        func_8011AAFC(g_CurrentEntity, 0x70, 0);
    }
    if (PLAYER.animationFrameDuration < 0) {
        func_8010E570(0);
    }
}

void func_801186EC(void) {
    if (PLAYER.unk2E == 0) {
        if (g_EntityArray[UNK_ENTITY_10].objectId == 0) {
            D_80138008 = 0x10;
            func_8011AAFC(g_CurrentEntity, 0x15003D, 0);
            PLAYER.unk2E++;
        }
    } else if (--D_80138008 == 0) {
        PLAYER.palette = 0x8100;
        func_8010E570(0);
    }
}

Entity* GetFreeDraEntity(s16 start, s16 end) {
    Entity* entity = &g_EntityArray[start];
    s16 i;

    for (i = start; i < end; i++, entity++) {
        if (entity->objectId == ENTITY_UNALLOCATED) {
            return entity;
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118810);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118894);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118970);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118B18);

// https://decomp.me/scratch/LmXYY
// nops between assignments probably aspsx
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118C28);
#else
extern u8 D_800ACFB4[];
extern u8 D_800ACFB5[];
extern u8 D_800ACFB6[];
extern u8 D_800ACFB7[];
extern u8 D_8013803C;
extern u8 D_80138040;
extern u8 D_80138044;
extern u8 D_80138048;

void func_80118C28(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 * 4;
    D_8013803C = D_800ACFB4[temp_a0];
    D_80138040 = D_800ACFB5[temp_a0];
    D_80138044 = D_800ACFB6[temp_a0];
    D_80138048 = D_800ACFB7[temp_a0];
}
#endif

s32 func_80118C84(s16 arg0, s16 arg1) {
    Entity* entity = GetFreeDraEntity(0x38, 0x40);

    if (entity != NULL) {
        func_80106590(entity);
        entity->objectId = ENTITY_13;
        entity->posX.val = PLAYER.posX.val;
        entity->posY.val = PLAYER.posY.val;
        entity->unk80.modeS16.unk0 = arg0;
        entity->unk80.modeS16.unk2 = arg1;
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80118D0C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80119588);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80119D3C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80119E78);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80119F70);

void func_8011A290(Entity* entity) {
    Unkstruct_8011A290 sp10;

    func_800FE3C4(&sp10, entity->unkB0, 0);
    entity->unk40 = sp10.sp10;
    entity->unk42 = sp10.sp14;
    entity->unk3C = sp10.sp1C;
    entity->unk49 = sp10.sp17;
    entity->unk58 = sp10.sp18;
    entity->unk6A = sp10.sp1E;
    entity->objectRoomIndex = sp10.sp22;
    entity->unkB2 = sp10.sp20;
    func_80118894(entity);
}

void func_800FD9D4(Unkstruct_8011A328*, s32 arg1);

void func_8011A328(Entity* entity, s32 arg1) {
    Unkstruct_8011A328 sp10;

    func_800FD9D4(&sp10, arg1);
    entity->unk40 = sp10.unk18;
    entity->unk42 = sp10.unk16;
    entity->unk3C = sp10.unk10;
    entity->unk49 = sp10.unk0D;
    entity->unk58 = sp10.unk0E;
    entity->unk6A = sp10.unk12;
    entity->objectRoomIndex = sp10.unk14;
    func_80118894(entity);
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011A3AC);

void func_8011A4C8(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011A4D0);

void func_8011A870(void) {
    Entity* entity = g_CurrentEntity = &g_EntityArray[UNK_ENTITY_4];
    u16 objectId;
    s32 i = 4;

loop_1: // !FAKE: this should be a for loop
    objectId = entity->objectId;

    if (objectId != 0) {
        if (entity->step == 0) {
            if ((u32)(entity->objectId - 0xD0) < 0x10) {
                entity->pfnUpdate = (PfnEntityUpdate)D_8016FCC0[objectId];
            } else {
                goto label;
            }
        }

        if (entity->pfnUpdate != NULL) {
            entity->pfnUpdate(entity);
            entity = g_CurrentEntity;
            if (entity->objectId != 0) {
                if ((!(entity->unk34 & 0x04000000)) &&
                    (((u32)((((u16)entity->posX.i.hi) + 0x20) & 0xFFFF) >=
                      0x141) ||
                     ((u32)((((u16)entity->posY.i.hi) + 0x10) & 0xFFFF) >=
                      0x111))) {
                    func_80106590(entity);
                    goto label;
                } else if (entity->unk34 & 0x100000) {
                    func_8010DDA0(0, &D_800ACFB4);
                }
            }
        }
    }
label:
    i++;
    g_CurrentEntity++;
    entity++;

    if (i < 8)
        goto loop_1;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011A9D8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011AAFC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011AC3C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011B190);

void func_8011B334(Entity* entity) {
    Unkstruct_8011B334 temp;

    if (PLAYER.unk2E != 0x70) {
        func_80106590(entity);
        return;
    }

    entity->unk34 = 0x60000;
    entity->facing = PLAYER.facing;
    entity->posY.i.hi = PLAYER.posY.i.hi;
    entity->posX.i.hi = PLAYER.posX.i.hi;
    D_80072F60[2] &= 0xFF7F;

    if (entity->step == 0) {
        func_800FE728(0, &temp, 0);
        entity->unk40 = temp.unk8;
        entity->unk42 = temp.unkC;
        entity->unk3C = temp.unk28;
        entity->unk49 = temp.unk1A;
        entity->unk58 = temp.unk26;
        entity->unk6A = temp.unk2A;
        entity->objectRoomIndex = temp.unk30;
        func_80118894(entity);
        entity->unk10 = 9;
        entity->unk12 = 0x15;
        entity->hitboxWidth = 4;
        entity->hitboxHeight = 5;
        entity->step++;
    } else if (entity->unk48 == 1) {
        D_80072F60[2] |= 0x80;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011B480);

void func_8011B530(Entity* entity) {
    if (PLAYER.step != 0x25) {
        func_80106590(entity);
    } else if (entity->step == 0) {
        entity->unk34 = 0x60000;
        func_8011A328(entity, 5);
        entity->step++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011B5A4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011BBE0);

bool func_8011BD48(Entity* entity) {
    s32 i = 0x10;
    s16 objId = entity->objectId;
    s16 subId = entity->subId;
    Entity* e = &g_EntityArray[i];
    for (; i < 0x40; i++, e++) {
        if (objId == (s32)e->objectId && subId == (s32)e->subId &&
            e != entity) {
            return 1;
        }
    }

    return 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011BDA4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011D9F8);

void func_8011E0E4(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011E0EC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011E390);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011E4BC);

void func_8011EDA0(void) {}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011EDA8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011F074);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011F24C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8011F934);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801200AC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80120AF8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80120DD0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80121980);

extern Unkstruct_80138094 D_80138094[];

void func_80121F14(s32 arg0, s32 arg1) {
    Unkstruct_80138094* ptr = D_80138094;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->unk0 = arg0 + ptr->unk0;
        ptr->unk4 = arg1 + ptr->unk4;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80121F58);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012231C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80123788);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801238CC);

// move a0,s0 thing
// https://decomp.me/scratch/rJCCX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80123A60);
#else
void func_80123A60(Entity* entity) {
    if (D_80072F2C & 0x01000000) {

#if 1
        entity->posX.i.hi = PLAYER.posX.i.hi; //(u16) D_800733DA;
        entity->posY.i.hi = PLAYER.posY.i.hi; //(u16) D_800733DE;
#else // This one generates the  first missing move a0, s0 for some reason?
        entity->posX.i.hi = (u16)D_800733DA;
        entity->posY.i.hi = (u16)D_800733DE;
#endif
        if (entity->step == 0) {
            func_8011A328(entity, 0xB);
            entity->unk34 = 0x04060000;
            entity->step++;
        }
        if (PLAYER.animationFrame == 5) {
            entity->hitboxWidth = 12;
            entity->hitboxHeight = 32;
            entity->unk10 = 0x1C;
            entity->unk12 = -0xC;
            return;
        }
        if (PLAYER.animationFrame == 6) {
            entity->hitboxWidth = 10;
            entity->hitboxHeight = 10;
            entity->unk10 = 0x1C;
            entity->unk12 = 0x10;
            return;
        }
        goto block_7;
    }
block_7:
    func_80106590(entity);
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80123B40);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80123F78);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80124164);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801243B0);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80124A8C);
#else
void func_80124A8C(Entity* entity) {
    u32* playerStep = &PLAYER.step;

    if (*playerStep == 4) {
        s32 playerStep_temp = *playerStep; // might be !FAKE:

        switch (entity->step) {
        case 0:
            entity->animationSet = 0x11;
            entity->accelerationY = -0x6000;
            AccelerateX(0x4000);
            entity->unk5A = 0x50;
            entity->palette = 0x819F;
            entity->unk4C = &D_800AE294;
            entity->unk34 = 0x100000;
            entity->facing = 0;
            entity->posY.i.hi -= 16;
            playerStep_temp = entity->step;
            playerStep_temp++;
            entity->posX.val += entity->accelerationX << 5;
            entity->step = playerStep_temp;
            break;

        case 1:
            entity->posX.val += entity->accelerationX;
            entity->posY.val += entity->accelerationY;

            if (entity->animationFrameDuration < 0) {
                goto block_7;
            }
            break;

        default:
            break;
        }
    } else {
    block_7:
        func_80106590(entity);
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80124B88);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80125330);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80125A30);

s32 func_80125B6C(s16 arg0, s16 arg1) {
    CollisionResult collisionResult;
    s16 var_a1;

    if (g_CurrentEntity->accelerationX == 0) {
        return 0;
    }

    CheckCollision(g_CurrentEntity->posX.i.hi + arg1,
                   g_CurrentEntity->posY.i.hi + arg0, &collisionResult, 0);
    if (g_CurrentEntity->accelerationX > 0) {
        var_a1 = collisionResult.unk14;
    } else {
        var_a1 = collisionResult.unk1C;
    }

    if (collisionResult.unk0 & 2) {
        g_CurrentEntity->posX.i.lo = 0;
        g_CurrentEntity->posX.i.hi += var_a1;
        return 2;
    }

    return 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80125C2C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80125E68);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801262AC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801267B0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80126C48);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80126ECC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801274DC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012768C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80127840);

void func_801279FC(Entity* entity) {
    POLY_GT4* poly;
    s32 firstPolygonIndex;

    if (PLAYER.facing == 0) {
        entity->posX.i.hi = PLAYER.posX.i.hi - 10;
    } else {
        entity->posX.i.hi = PLAYER.posX.i.hi + 10;
    }
    entity->posY.i.hi = PLAYER.posY.i.hi + 2;

    switch (entity->step) {
    case 0:
        firstPolygonIndex = AllocPolygons(4, 1);
        entity->firstPolygonIndex = firstPolygonIndex;
        if (firstPolygonIndex != -1) {
            entity->unk7C.s = 0x16;
            entity->unk7E.modeU16 = 0x1A;
            poly = &D_80086FEC[entity->firstPolygonIndex];
            poly->u2 = 0x40;
            poly->u3 = 0x7F;
            poly->u1 = 0x7F;
            poly->v1 = 0xC0;
            poly->v0 = 0xC0;
            poly->v3 = 0xFF;
            poly->v2 = 0xFF;
            poly->r3 = 0x80;
            poly->r2 = 0x80;
            poly->r1 = 0x80;
            poly->r0 = 0x80;
            poly->g3 = 0x80;
            poly->g2 = 0x80;
            poly->g1 = 0x80;
            poly->g0 = 0x80;
            poly->u0 = 0x40;
            poly->b3 = 0x40;
            poly->b2 = 0x40;
            poly->b1 = 0x40;
            poly->b0 = 0x40;
            poly->tpage = 0x1A;
            poly->clut = 0x15F;
            poly->pad2 = PLAYER.zPriority + 1;
            poly->pad3 = 0x35;
            entity->unk34 = 0x04840000;
            entity->step++;
            break;
        }
        func_80106590(entity);
        return;

    case 1:
        entity->unk7C.s += 2;
        entity->unk7E.modeU16 += 2;
        if (entity->unk7C.s >= 0x39) {
            func_80106590(entity);
            return;
        }
        break;

    default:
        break;
    }

    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = entity->posX.i.hi - entity->unk7C.s;
    poly->y0 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x1 = entity->posX.i.hi + entity->unk7C.s;
    poly->y1 = entity->posY.i.hi - entity->unk7E.modeU16;
    poly->x2 = entity->posX.i.hi - entity->unk7C.s;
    poly->y2 = entity->posY.i.hi + entity->unk7E.modeU16;
    poly->x3 = entity->posX.i.hi + entity->unk7C.s;
    poly->y3 = entity->posY.i.hi + entity->unk7E.modeU16;

    if (entity->unk7C.s >= 0x29) {
        poly->r3 += 0xF4;
        poly->g3 += 0xF4;
        poly->b3 += 0xFA;
        poly->r0 = poly->r1 = poly->r2 = poly->r3;
        poly->g0 = poly->g1 = poly->g2 = poly->g3;
        poly->b0 = poly->b1 = poly->b2 = poly->b3;
    }
}

void func_80127CC8(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    if (PLAYER.step != 34) {
        func_80106590(entity);
        return;
    }

    entity->posX.i.hi = PLAYER.posX.i.hi;

    switch (entity->step) {
    case 0:
        ret = AllocPolygons(3, 1);
        entity->firstPolygonIndex = ret;

        if (ret == -1) {
            func_80106590(entity);
            D_80072F7C = 0xFFFF;
            return;
        }

        entity->unk34 = 0x04860000;
        poly = &D_80086FEC[entity->firstPolygonIndex];
        poly->r3 = 0xC0;
        poly->r2 = 0xC0;
        poly->r1 = 0xC0;
        poly->r0 = 0xC0;
        poly->g3 = 0x40;
        poly->g2 = 0x40;
        poly->g1 = 0x40;
        poly->g0 = 0x40;
        poly->b3 = 0x40;
        poly->b2 = 0x40;
        poly->b1 = 0x40;
        poly->b0 = 0x40;
        poly->pad3 = 0x315;
        entity->zPriority = 0x1C0;
        poly->pad2 = 0x1C0;
        entity->step++;
        break;

    case 1:
        if (entity->unk7C.s++ >= 0xE) {
            func_80106590(entity);
            return;
        }

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->x0 = poly->x2 = entity->posX.i.hi - 3;
    poly->y0 = 0;
    poly->y1 = 0;
    poly->x1 = poly->x3 = entity->posX.i.hi + 3;
    poly->y3 = 0xF0;
    poly->y2 = 0xF0;

    if (D_8003C8C4 & 1) {
        poly->pad3 = poly->pad3 | 8;
    } else {
        poly->pad3 = poly->pad3 & 0xFFF7;
    }
}

void func_80127EAC(s16 arg0) {
    g_CurrentEntity->unk7C.s = (arg0 * 2) - g_CurrentEntity->unk7C.s;
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

void func_80127EF0(s16 arg0) {
    if (g_CurrentEntity->unk80.modeS16.unk2 == 0) {
        g_CurrentEntity->unk7C.s = (arg0 * 2) - g_CurrentEntity->unk7C.s;
        g_CurrentEntity->unk80.modeS16.unk0++;
        g_CurrentEntity->unk80.modeS16.unk2++;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80127F40);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80128714);

s32 func_80128BBC(Unkstruct_80128BBC* arg0, u8 value) {
    u8 ret = 0;
    s32 i;
    s32 j;
    Unkstruct_80128BBC_Sub* temp = arg0->unk04;

    for (i = 0; i < 4; i++, temp++) {
        for (j = 0; j < 3; j++) {
            temp->unk00[j] -= value;

            if (temp->unk00[j] < 16) {
                temp->unk00[j] = 16;
            } else {
                ret |= 1;
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80128C2C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801291C4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80129864);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012A0A4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012A528);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012A89C);

void func_8012B78C(Entity* entity) {
    POLY_GT4* poly;
    s32 ret;

    switch (entity->step) {
    case 0:
        ret = AllocPolygons(4, 1);
        entity->firstPolygonIndex = ret;
        if (entity->firstPolygonIndex != -1) {
            entity->unk34 = 0x04820000;
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
            func_80106590(entity);
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
        func_80106590(entity);
        return;

    default:
        break;
    }
    poly = &D_80086FEC[entity->firstPolygonIndex];
    poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 = poly->g2 =
        poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
            entity->unk7E.modeU8.unk0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012B990);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012BEF8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012C600);

bool func_8012C88C(void) {
    if ((PLAYER.unk2E != 0) && (PLAYER.unk2E != 8)) {
        if (((D_8009744C != 0) && (func_800FE3A8(0xE) == 0)) ||
            (D_80072EEC & 2) || (func_800FEEA4(2, 1) < 0)) {
            func_8010D584(25);
            func_8010DA48(0xCA);
            D_800AFDA6 = 1;
            PLAYER.palette = 0x810D;
            D_80072F86 = 0;
            D_80072F88 = 0;
            func_8011AAFC(g_CurrentEntity, 0x24002C, 0);
            PLAYER.accelerationY >>= 1;
            return true;
        }
    }
    return false;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012C97C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012CA64);

void func_8012CB0C(void) {
    PLAYER.unkAC = 0xDE;
    PLAYER.accelerationY = 0;
    D_800B0914 = 0;
    PLAYER.animationFrameIndex = 0;
    PLAYER.animationFrameDuration = 0;
    PLAYER.unk2E = 7;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012CB4C);

void func_8012CC30(s32 arg0) {
    if (arg0 == 0) {
        D_80138444 = 1;
        if ((D_80138FC4 == 255) && (func_800FE3A8(6)) && (func_800FDC94(4))) {
            func_8010E27C();
            PLAYER.unk2E = 2;
            D_800B0914 = 4;
            AccelerateX(0x50000);
            g_CurrentEntity->accelerationY = 0;
            func_8010DA48(0xEDU);
            func_800FDCE0(4);
        }
    } else {
        D_80138444 = 1;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012CCE4);

void func_8012CED4(void) {
    if ((PLAYER.unk2E == 2) && (D_800B0914 == PLAYER.unk2E)) {
        func_8010DA48(0xE7);
        D_800B0914 = 1;
    } else {
        func_8010DA48(0xE8);
        AccelerateX(0x10000);
        D_800B0914 = 0;
        if (D_80138438 & 0x40) {
            PLAYER.animationFrameIndex = 4;
            PLAYER.accelerationX = 0;
            PLAYER.animationFrameDuration = 1;
        }
    }
    PLAYER.unk2E = 5;
    D_80072F0A = 8;
    PLAYER.accelerationY = 0;
    D_80138430 -= 0x100;
}

void func_8012CFA8(void) {
    func_8010DA48(0xEA);
    PLAYER.unk2E = 6;
    D_800B0914 = 0;
    PLAYER.accelerationX = 0;
    D_80072F0A = 8;
}

void func_8012CFF0(void) {
    PLAYER.unk2E = 3;
    func_8010DA48(0xE3);
    D_800B0914 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012D024);

void func_8012D178(void) {
    s32 var_v0;

    if (D_80072EEC & 0x40) {
        func_8012CCE4();
        return;
    } else if (!(D_80072F20 & 1)) {
        func_8012CFA8();
        return;
    } else if (PLAYER.facing != 0) {
        var_v0 = D_80072EE8 & 0x8000;
    } else {
        var_v0 = D_80072EE8 & 0x2000;
    }

    if (var_v0 != 0) {
        func_8012CB4C();
        return;
    } else if (D_80072F24 & 0x40) {
        func_8012CA64();
        return;
    } else if (D_8003C8C4 == ((D_8003C8C4 / 6) * 6)) {
        func_8011AAFC(g_CurrentEntity, 0x10045, 0);
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012D28C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012D3E8);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012DBBC);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012DF04);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012E040);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012E550);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012E7A4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012E9C0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012EAD0);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012ED30);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012EF2C);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012F178);

s32 func_8012F83C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_a0 = arg0 - arg2;
    s32 temp_a1 = arg1 - arg3;

    return ((SquareRoot12((SQ(temp_a0) + SQ(temp_a1)) << 12, temp_a1) >> 12) <
            arg4) ^
           1;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8012F894);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80130264);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80130618);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801309B4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80130E94);

// https://decomp.me/scratch/cu30D TODO: branching is wrong
#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8013136C);
#else
void func_8012C600(void); /* extern */
extern u16 D_8007412E;
extern s32 D_800741CC;
extern s32 D_800741D0;

void func_8013136C(Entity* entity) {
    if (!(D_80072F2C & 4)) {
        func_80106590(entity);
        return;
    }
    if (entity->step == 0) {
        entity->animationSet = 0xF;
        entity->unk5A = 0x7E;
        entity->palette = PLAYER.palette;
        entity->unk34 = 0x04060000;
        entity->unk19 = 4;
        entity->unk20 = -8;
        entity->step++;
    }
    entity->animationFrame = 0x50;
    entity->facing = PLAYER.facing;
    entity->posX.val = g_EntityArray[19].posX.val; // D_800741CC
    entity->posY.val = g_EntityArray[19].posY.val; // D_800741D0
    if (PLAYER.facing == 0) {
        entity->zPriority = PLAYER.zPriority - 5;
        entity->posX.i.hi += 8;
    } else {
        entity->zPriority = PLAYER.zPriority + 5;
        entity->posX.i.hi -= 8;
    }
    entity->posY.i.hi += 3;
    entity->unk1E = g_EntityArray[19].unk1E;
    switch (PLAYER.unk2E - 1) {
    case 1:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        break;

    case 0:
        if (D_800B0914 == 1) {
            entity->posY.i.hi -= 2;
            if (PLAYER.facing == 0) {
                entity->posX.i.hi -= 8;
            } else {
                entity->posX.i.hi += 8;
            }
        }
        break;

    case 2:
        switch (D_800B0914)
        {
        case 1:
            break;

        case 0:
            if (PLAYER.animationFrame == 33) {
                entity->animationFrame = 81;
                if (PLAYER.facing == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 6;
                }
            }
            if (PLAYER.animationFrame == 34) {
                if (PLAYER.facing == 0) {
                    entity->posX.i.hi += 3;
                } else {
                    entity->posX.i.hi += 13;
                }
                entity->animationFrame = 82;
            }
        case 2:
            break;
        }
        break;

    }
    entity->palette = PLAYER.palette;
    func_8012C600();
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801315F8);

void func_80131EBC(const char* str, s16 id) { D_80138784[id] = str; }

void func_80131ED8(s32 value) { D_80138F20 = value; }

void func_80131EE8(void) {
    D_80139020 = 1;
    D_8013B694 = 0;
}

void func_80131F04(void) {
    D_80139020 = 0;
    D_8013B694++;
}

s32 func_80131F28(void) { return D_80138F7C; }

u16 func_80131F38(void) {
    if (D_80139810 == 0) {
        return 0;
    }
    return D_80139810 | 0x200;
}

bool func_80131F68(void) {
    if (D_8013B61C == 0) {
        return D_8013901C != 0;
    }
    return true;
}

s16 func_80131F94(void) { return D_8013B668; }

void func_80131FA4(s16 arg0) { func_80021F6C(arg0, arg0); }

void func_80131FCC(void) {
    if (D_8013B680 == 0) {
        D_80138F7C = 0;
    } else {
        s32 temp_v1 = D_8013B680;
        s32 temp_v0 = D_8013B680;
        if (temp_v0 >= 0 && temp_v1 < 3)
            D_80138F7C++;
    }
    D_8013B680 = 0;
}

u8 func_80132028(u_char com, u_char* param, u_char* result) {
    s32 ret = CdSync(1, D_80138F2C);

    D_801396F0 = ret;

    if (com == CdlGetlocL) {
        if (ret == 2) {
            goto block_9;
        } else {
            goto block_6;
        }
    } else if ((*D_80138F2C & 0x10) || (*D_80138F2C & 4)) {
    block_6:
        CdControl(CdlNop, 0, 0);
        D_8013B680 = 2;
        return D_8013B680;
    } else if (ret == 2) {
    block_9:
        if (CdControl(com, param, result)) {
            D_8013B680 = 0;
            return D_8013B680;
        }
        goto block_12;
    }
block_12:
    D_8013B680 = 1;

    return D_8013B680;
}

void func_80132134(void) {
    g_volumeL = 127;
    g_volumeR = 127;
    SsSetMVol(g_volumeL, g_volumeR);
}

void func_8013216C(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        D_8013B620[i] = 0;
        D_8013B614[i] = 0;
        D_8013AE84[i] = 0;
        D_8013B66C[i] = 0;
        D_8013B5EC[i] = 0;
        D_8013B628[i] = 0;
        D_8013B648[i] = 0;
        D_8013AEA0[i] = 0;
    }
}

void func_801321FC(void) {
    s32 i;

    func_8013216C();
    D_8013B690 = 0;

    for (i = 0; i < 4; i++) {
        D_8013B650[i] = 0;
        D_8013AED4[i] = 0;
    }
    D_80139804 = 0;
    D_8013B664 = 0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80132264);

void func_801324B4(s8 s_num, s16 arg1, s16 arg2) {
    short voll = D_800BD07C[arg1];
    short volr = D_800BD07C[arg2];

    SsSetSerialVol(s_num, voll, volr);
}

void func_80132500(u8 soundMode) {
    CdlATV audioVolume;

    switch (soundMode) {
    case MONO:
        if (D_801390A8 != 0) { // D_801390A8 fake symbol or part of another
            func_80021174();
            audioVolume.val2 = 128; // CD (R) --> SPU (R)
            audioVolume.val0 = 128; // CD (L) --> SPU (L)
            audioVolume.val3 = 128; // CD Right sound transferred to left
            audioVolume.val1 = 128; // CD Left sound transferred to right
            CdMix(&audioVolume);
            D_8013AE7C = 108;
            D_801390A8 = 0;
        }
        break;
    case STEREO:
        if (D_801390A8 != 1) {
            func_80021188();
            audioVolume.val2 = 224; // CD (R) --> SPU (R)
            audioVolume.val0 = 224; // CD (L) --> SPU (L)
            audioVolume.val3 = 0;
            audioVolume.val1 = 0;
            CdMix(&audioVolume);
            D_8013AE7C = 127;
            D_801390A8 = 1;
        }
        break;
    }
}

/**
 * Called by entrypoint_sotn, seems to be initializing
 * various parts of the sound system
 */
void func_801325D8(void) {
    D_8013AEEC = 1;
    SsInitHot();
    SsSetTickMode(1);
    func_80132500(1);
    SsSetReservedVoice(0x10);
    SsStart();
    func_800209B4(&D_80138460, 0x10, 1);
    func_80021E38(3);
    SpuClearReverbWorkArea(3);
    func_80021EEC();
    func_80132134();
    D_8013B668 = 0x78;
    SsSetSerialAttr(0, 0, 1);
    func_801324B4(0, D_8013B668, D_8013B668);
    D_80138F24[0] = -0x38; // !FAKE: D_80138F24 part of an array / struct
    func_80132028(0xE, D_80138F24, 0);
    func_80132264();
    func_80131FA4(0xA);
    func_8002ABF4(0);
    func_80029FBC(0);
    CdReadyCallback(NULL);
    func_80028D3C(0x1010, 0x10000);
}

s32 func_801326D8(void) {
    if (D_8013901C != 0)
        return 1;
    if (D_80139810 != 0)
        return 3;
    return (D_801390D8 != 0) * 2;
}

void func_8013271C(void) {
    while (!(func_801326D8() & 0xFF) == 0) {
        VSync(0);
        func_801361F8();
    }
}

void func_80132760(void) {
    SsSetMVol(0, 0);
    SsSetSerialAttr(0, 0, 0);
    func_801324B4(0, 0, 0);
    func_80132134();
    func_80132264();
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801327B4);

// https://decomp.me/scratch/0X5YL
// Matches with gcc 2.6.0 + aspsx 2.3.4
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80132A04);
#else
void func_801327B4(s16, s16, s16, s16, s16, s16, s16, s16);
extern s16 D_800BD19C[];
extern s16 D_800BD19E[];
extern s16 D_80138FB8; // vol_l
extern s16 D_80139004; // vol_r

void func_80132A04(s16 voice, s16 vabId, s16 prog, s16 tone, u16 note,
                   s16 volume, s16 distance) {
    s16 var_a0;
    s16 var_a1;
    volatile short pad;

    if (distance == 0) {
        D_80138FB8 = volume;
        D_80139004 = volume;
    } else {
        D_80139004 = (volume * D_800BD19C[distance * 2]) >> 7;
        D_80138FB8 = (volume * D_800BD19E[distance * 2]) >> 7;
    }

    if (voice < 0x18U) {
        SsUtKeyOnV(voice, vabId, prog, tone, note, 0, D_80138FB8, D_80139004);
        SsUtKeyOnV(voice + 1, vabId, prog, 1 + tone, note, 0, D_80138FB8,
                   D_80139004);
        return;
    }
    switch (voice) {
    case 0x1E:
        var_a0 = 0;
        var_a1 = 4;
        break;
    case 0x1F:
        var_a0 = 4;
        var_a1 = 8;
        break;
    case 0x20:
        var_a0 = 8;
        var_a1 = 0xC;
        break;
    case 0x21:
        var_a0 = 0xE;
        var_a1 = 0x12;
        break;
    default:
        return;
    }
    func_801327B4(var_a0, var_a1, vabId, prog, tone, note, D_80138FB8,
                  D_80139004);
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80132C2C);

extern s16 D_80139868[];

u16 func_80132E38(void) {
    s32 i;

    for (i = 0; i < 255; i++) {
        D_80139868[i] = D_80139868[i + 1];
    }
    D_801396F4--;

    return D_801396F4;
}

void func_80132E90(u32 arg0, s8* arg1) {
    u16 temp;
    u16 temp2;

    arg1[2] = (((arg0 % 75) / 10) * 0x10) + ((arg0 % 75) % 10);
    arg1[1] = ((((arg0 / 75) % 60) / 10) * 0x10) + (((arg0 / 75) % 60) % 10);
    temp = ((arg0 / 75) / 60) % 10;
    arg1[0] = (temp2 = (((arg0 / 75) / 60) / 10) * 0x10) + temp;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80132F60);
void func_80132F60();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133290);
void func_80133290();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133488);
void func_80133488();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133604);
void func_80133604();

void func_80133780(s8 arg0) { SsSetSerialAttr(0, 1, arg0 == 1); }

void func_801337B4(void) {
    if (D_80139810 != 0) {
        func_80020F44(D_8013B658);
        SsSeqClose(D_8013B658);
        func_8013415C();
        D_80139810 = 0;
        D_801390C4 = 0;
    }
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133810);

bool func_80133940(void) { return D_801396F4 == 0; }

bool func_80133950(void) { return D_8013980C == 0; }

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133960);
void func_80133960();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133BDC);
void func_80133BDC();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80133FCC);

extern Unkstruct_80138FB4* D_80138FB4;

void func_80134104(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 0xE;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

void func_8013415C(void) {
    D_80138FB4->unk4 = 0x4000;
    D_80138FB4->unk0 = 0xFFFFFF;
    D_80138FB4->unk36 = 8;
    func_8002A09C(D_80138FB4);
    D_80138F28 = 0xFFFFFF;
    func_801321FC();
}

void func_801341B4(void) {
    s32 temp;

    switch (D_8013AE80) {
    case 0:
        D_801390A0 = 1;
        D_80139A78 = 0;
        D_8013AE80++;
        break;

    case 1:
        D_80139A78++;
        if (g_volumeL > 0) {
            temp = g_volumeR * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            g_volumeL = g_volumeR - (temp >> 9);
            if (g_volumeL >> 0x10) {
                g_volumeL = 0;
            }
        } else {
            g_volumeL = 0;
        }
        SsSetMVol(g_volumeL, g_volumeL);
        if (g_volumeL == 0) {
            D_8013AE80++;
        }
        break;

    case 2:
        func_80131FA4(0);
        func_801337B4();
        func_80132C2C(3);
        D_800BD1C4 = 3;
        D_8013AE80++;
        break;

    case 3:
        D_800BD1C4--;
        if (D_800BD1C4 == 0) {
            func_8013415C();
        default:
            D_8013AE80 = 0;
            D_801390A0 = D_8013AE80;
            D_8013B61C = 0;
            func_80132E38();
        }
        break;
    }
}

void func_80134388(void) {
    s32 temp;

    switch (D_8013AE80) {
    case 0:
        D_8013AE80++;
        D_801390A0 = 1;
        D_80139A78 = 0;
        break;

    case 1:
        D_80139A78++;
        if (D_8013B668 > 0) {
            temp = D_80139820 * D_80139A6C * D_80139A78;
            if (temp < 0) {
                temp += 0x1FF;
            }
            D_8013B668 = D_80139820 - (temp >> 9);
            if (D_8013B668 >> 0x10) {
                D_8013B668 = 0;
            }
        } else {
            D_8013B668 = 0;
        }
        func_801324B4(0, D_8013B668, D_8013B668);
        if (D_8013B668 == 0) {
            D_8013AE80++;
        }
        break;

    case 2:
        func_80132C2C(2);

    default:
        D_8013AE80 = 0;
        D_801390A0 = D_8013AE80;
        D_8013B61C = 0;
        func_80132E38();
        break;
    }
}

extern Unkstruct_80138FB4* D_801390C8;

void func_80134508(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 0xE;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_80134564(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 0xE;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

extern Unkstruct_80138FB4* D_801390C8;

void func_801345C0(void) {
    D_801390C8->unk0 = 0x300000;
    D_801390C8->unk4 = 0x4000;
    D_801390C8->unk36 = 8;
    func_8002A09C(D_801390C8);
    D_80138F28 |= 0x300000;
}

extern Unkstruct_80138FB4* D_801390CC;

void func_8013461C(void) {
    D_801390CC->unk0 = 0xC00000;
    D_801390CC->unk4 = 0x4000;
    D_801390CC->unk36 = 8;
    func_8002A09C(D_801390CC);
    D_80138F28 |= 0xC00000;
}

s32 func_80134678(s16 arg0, u16 arg1) {
    s32 ret = -2;
    u16 temp;

    if (D_80139804 != 0) {
        ret = 0;
        temp = arg1 + 8;

        if (temp >= 0x11) {
            arg1 = 0;
            ret = -1;
        }

        D_8013AE94 = arg1;
        D_8013AEE0 = arg0;
        D_8013B3E8[D_80139A70] = 1;
        D_80139A70++;

        if (D_80139A70 == 0x100) {
            D_80139A70 = 0;
        }
    }
    return ret;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134714);

void PlaySfx(s16 sfxId) {
    u16 offset;

    if (D_8013AEEC != 0) {
        offset = (u32)(sfxId - 0x601);
        if (offset < 0x2E0) {
            D_801390DC[D_80139000].unk00 = sfxId - 0x600;
            D_801390DC[D_80139000].unk02 = 0xFFFF;
            D_801390DC[D_80139000].unk04 = 0;
            D_80139000++;
            if (D_80139000 == 0x100) {
                D_80139000 = 0;
            }
        } else {
            switch (sfxId) {
            case 0x10:
            case 0x11:
                D_8013980C = 1;
                break;

            case 0x80:
            case 0x81:
            case 0x82:
            case 0x83:
            case 0x84:
            case 0x90:
            case 0x91:
            case 0x92:
            case 0x93:
            case 0x94:
                D_8013B61C = 1;
                break;

            default:
                break;
            }

            D_8013B3E8[D_80139A70] = sfxId;
            D_80139A70++;
            if (D_80139A70 == 0x100) {
                D_80139A70 = 0;
            }
        }
    }
}

void func_8013493C(s16 arg0, s16 arg1) {
    D_8013AE84[arg1] = D_8013B678[arg0];
    D_8013B620[arg1] = D_801390AC[arg0];
    D_8013B614[arg1] = D_80139058[arg0];
    D_8013B66C[arg1] = D_80139814[arg0];
    D_8013B5EC[arg1] = D_80139018[arg0];
    D_8013B628[arg1] = D_801390B4[arg0];
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801349F4);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134B48);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134C60);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134D14);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134E64);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80134F50);
void func_80134F50();

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_801353A0);
#else
void func_801353A0(void) {
    if (D_801396F4 == 0)
        return;

    switch (D_80139868[0]) {
    case 2:
        func_80133604();
        break;
    case 3:
        func_80133488();
        break;
    case 4:
        func_80132F60();
        break;
    case 6:
        func_80133290();
        break;
    case 8:
        func_80134388();
        break;
    case 10:
        func_801341B4();
        break;
    case 12:
        func_80133960();
        break;
    case 14:
        func_80133BDC();
        break;
    case 16:
        D_8013B684 = 0;
    case 0:
        func_80132E38();
        break;
    }
}
#endif

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80135484);

void func_80135624(s16 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    if (arg2 != 0) {
        D_80138F28 |= (1 << ((arg1 + 6) * 2)) + (1 << (((arg1 + 6) * 2) + 1));
    }
    func_80132A04((arg1 * 2) + 12, D_800BF554[arg0 * 7], D_800BF555[arg0 * 7],
                  D_800BF559[arg0 * 7], D_800BF556[arg0 * 7], arg3, arg4);
    do { // !FAKE:
    } while (0);
    D_8013B650[arg1] = arg0;
    D_8013AED4[arg1] = D_800BF55A[arg0 * 7];
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8013572C);

s16 func_80135C00(s16 arg0) {
    arg0++;

    if (arg0 == 0x100) {
        arg0 = 0;
    }

    return arg0;
}

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80135C2C);
void func_80135C2C();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80135D8C);
void func_80135D8C();

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80136010);

void func_801361F8(void) {
    if (D_8013AEEC != 0) {
        func_80136010();
        func_80135C2C();
        func_80135D8C();
        func_80134F50();
        func_80133FCC();
        func_801353A0();
        func_8002A024(0, D_80138F28);
        D_80138F28 = 0;
        func_80131FCC();

        if (D_80139020) {
            func_801324B4(0, 0, 0);
        } else {
            func_801324B4(0, D_8013B668, D_8013B668);
        }
    }
}

void nullsub_10(void) {}
