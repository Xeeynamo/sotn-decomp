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

    if (D_80097B9C.mp < (s32)temp) {
        return false;
    } else {
        D_80097B9C.mp -= temp;
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
    if (D_80097B9C.mp >= mpCount) {
        if (subtractMp != 0) {
            D_80097B9C.mp -= mpCount;
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
    if (D_80097B9C.hearts < D_80097B9C.heartsMax) {
        D_80097B9C.hearts += value;
        if (D_80097B9C.heartsMax < D_80097B9C.hearts) {
            D_80097B9C.hearts = D_80097B9C.heartsMax;
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

    playerMP = D_80097B9C.mp - 4;

    if (playerMP > 0) {
        if (arg0 != 0) {
            D_80097B9C.mp = playerMP;
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
    return arg0 + ((u32)(arg0 * D_80097BE4[0]) >> 7);
}

s32 func_800FF494(Unkstruct_800FF494* arg0) {
    s32 temp_s2 = CheckEquipmentItemCount(0x4B, 4);
    s32 rnd = rand() & 0xFF;

    rnd -= ((rand() & 0x1F) + D_80097BE4[0]) / 20;

    if (temp_s2 != 0) {
        rnd -= arg0->unk1E * temp_s2;
    }

    if (rnd < arg0->unk1E) {
        return 0x40;
    } else {
        rnd -= arg0->unk1E;
        if (temp_s2 != 0) {
            rnd -= arg0->unk20 * temp_s2;
        }
        rnd -= ((rand() & 0x1F) + D_80097BE4[0]) / 20;

        if (rnd >= arg0->unk20) {
            rnd = rand() % 28;
            if (arg0->unk1E == 0) {
                rnd++;
            }
            if (arg0->unk20 == 0) {
                rnd++;
            }
            return rnd + temp_s2;
        } else {
            return 0x20;
        }
    }
}

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

void func_800FF708(s32 arg0, s32 arg1) {
    s32 rnd;

    do {
    loop_1:
        rnd = rand() % 90;
        if (rnd == 0x19) {
            goto loop_1;
        }
    } while (D_800A7734[rnd].unk00 != arg0);
    g_playerEquip[arg1 + 2] = rnd;
}

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
    D_8013796C = D_80097B9C.hp;

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

        poly->r0 = poly->r1 = var_v1 - 16;
        poly->r2 = poly->r3 = var_v1 + 16;
        poly->b3 = 0;
        poly->b2 = 0;
        poly->b1 = 0;
        poly->b0 = 0;
        poly->pad3 = 0x404;
    } else {
        poly->b1 = 96;
        poly->b0 = 96;
        poly->b3 = 128;
        poly->b2 = 128;
        poly->r3 = 0;
        poly->r2 = 0;
        poly->r1 = 0;
        poly->r0 = 0;
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

#ifndef NON_EQUIVALENT
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

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_80106A28);

INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010715C);

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

// Matching in gcc 2.6.0 + aspsx 2.3.4
// Matching in gcc 2.7.2 + aspsx (the one in decomp.me)
// https://decomp.me/scratch/oKHMJ
#ifndef NON_MATCHING
INCLUDE_ASM("asm/dra/nonmatchings/5D874", func_8010A3F0);
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
// matches in gcc 2.6.0 + aspsx 2.3.4
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

void func_8010E6AC(s32 arg0) {
    bool condition = false;

    condition = ((D_80072F20 & 0x20) != condition);
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

    if (D_80072F6C != 0) {
        PLAYER.unkAC = 9;
    }

    if ((PLAYER.unkAC == 7) && (condition)) {
        PLAYER.animationFrameIndex = 1;
    }

    if (D_80072F70 == 2) {
        PLAYER.animationFrameIndex = 4;
    }
}

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

void func_8010E9A4(void) {
    if (func_8010E27C() != 0) {
        AccelerateX(0x30000);
    } else {
        PLAYER.accelerationX = 0;
    }

    if (PLAYER.step == 4) {
        D_80072F60[2] |= 1;
    } else {
        D_80072F60[2] = 0;
    }

    func_8011AAFC(g_CurrentEntity, 2, 0);
    func_8010D584(8);
    PLAYER.accelerationY = -0xC0000;
    func_8010DA48(0x21);
    D_80072F6A[0] = 0;
}

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
    func_80106590(&g_EntityArray[UNK_ENTITY_10]);
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
