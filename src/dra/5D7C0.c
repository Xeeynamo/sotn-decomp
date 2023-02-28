#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

u32 CheckEquipmentItemCount(u32 itemId, u32 equipType) {
    if (equipType < 5) {
        switch (equipType) {
        case 0:
            return (g_playerEquip[0] == itemId) + (g_playerEquip[1] == itemId);
        case 1:
            return g_playerEquip[2] == itemId;
        case 2:
            return g_playerEquip[3] == itemId;
        case 3:
            return g_playerEquip[4] == itemId;
        case 4:
            return (g_playerEquip[5] == itemId) + (g_playerEquip[6] == itemId);
        }
    }
    // seems to require missing return
}

// fix missing padding at end of jump table.
// this probably indicates the end of a C file
const u32 rodataPadding_800DCBD8 = 0;

#ifndef NON_EQUIVALENT
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FD874);
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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FD9D4);

// TODO get rid of the asm volatile
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDB18);
#else
s16 func_800FDB18(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s32 ret;
    s32 var_v1;

    switch (arg0) {
    case 0:
        temp_v0 = arg1 - (D_80097BDC * 0x10);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x100) {
            ret = 0x100;
        }
        break;
    case 1:
        temp_v0 = arg1 - (D_80097BDC * 4);
        // asm volatile("move $16, $2");
        if (temp_v0 < 0x40) {
            ret = 0x40;
        }
        break;
    case 2:
        ret = arg1;
        var_v1 = (((rand() % 12) + D_80097BDC) - 9) / 10;
        if (var_v1 < 0) {
            var_v1 = 0;
        }
        if (var_v1 > 4) {
            var_v1 = 4;
        }
        ret = ret - var_v1;
        break;
    case 3:
        ret = arg1 + (D_80097BE0 * 4);
        break;
    case 4:
    case 5:
        ret = arg1;
        if (CheckEquipmentItemCount(80, 4)) {
            ret += ((s32)(((s16)ret) + (((u32)(ret << 0x10)) >> 0x1F))) >> 1;
        }
        break;
    }

    return ret;
}
#endif

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
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDCE0);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FDE20);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE044);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE3C4);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE728);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FE97C);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FEEA4);

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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FF128);

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
    if ((g_StageId != 0x1F) && (g_CurrentPlayableCharacter == PLAYER_ALUCARD)) {
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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_800FF7B8);

// matches with ASPSX
#ifndef NON_MATCHING
INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", DrawHudRichter);
#else
void DrawHudRichter(void) {
    POLY_GT4* poly;

    D_80137978 = 400;
    D_8013797C = 400;
    D_801397FC = 0;
    D_80139008 = 0;
    D_80137994 = 0;
    D_8003C744 = 0;
    D_80137980 = 48;
    D_80137984 = 0;
    D_80137990.unk0 = 0;
    D_8013798C = 40000 / D_80137978;
    D_80137988 = 40000 / D_8013797C;
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
            phi_s1 += 2;
            phi_s0 += 2;
        } while (poly != 0);
    }
}
#endif

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_80100B50);

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

    if ((g_StageId == STAGE_ST0) ||
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

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_80101A80);

INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_801024DC);

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
    } else if (!(g_StageId & 0x20)) {
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

// INCLUDE_ASM("asm/us/dra/nonmatchings/5D7C0", func_801027C4);

extern s32 D_801379A4;
extern s32 D_801379A8;

// typedef struct {
//     /* 0x00 */ u_long tag;
//     /* 0x04 */ u_char r0;
//     /* 0x05 */ u_char g0;
//     /* 0x06 */ u_char b0;
//     /* 0x07 */ u_char code;
//     /* 0x08 */ short x0;
//     /* 0x0A */ short y0;
//     /* 0x0C */ u_char u0;
//     /* 0x0D */ u_char v0;
//     /* 0x0E */ u_short clut;
//     /* 0x10 */ u_char r1;
//     /* 0x11 */ u_char g1;
//     /* 0x12 */ u_char b1;
//     /* 0x13 */ u_char p1;
//     /* 0x14 */ short x1;
//     /* 0x16 */ short y1;
//     /* 0x18 */ u_char u1;
//     /* 0x19 */ u_char v1;
//     /* 0x1A */ u_short tpage;
//     /* 0x1C */ u_char r2;
//     /* 0x1D */ u_char g2;
//     /* 0x1E */ u_char b2;
//     /* 0x1F */ u_char p2;
//     /* 0x20 */ short x2;
//     /* 0x22 */ short y2;
//     /* 0x24 */ u_char u2;
//     /* 0x25 */ u_char v2;
//     /* 0x26 */ u_short pad2;
//     /* 0x28 */ u_char r3;
//     /* 0x29 */ u_char g3;
//     /* 0x2A */ u_char b3;
//     /* 0x2B */ u_char p3;
//     /* 0x2C */ short x3;
//     /* 0x2E */ short y3;
//     /* 0x30 */ u_char u3;
//     /* 0x31 */ u_char v3;
//     /* 0x32 */ u_short pad3;
// } POLY_GT4; /* Gouraud Textured Quadrangle, size = 0x34*/

// glabel jpt_80102810
// /* 3CC0C 800DCC0C 18281080 */ .word .L80102818
// /* 3CC10 800DCC10 40281080 */ .word .L80102840
// /* 3CC14 800DCC14 40281080 */ .word .L80102840
// /* 3CC18 800DCC18 18281080 */ .word .L80102818
// /* 3CC1C 800DCC1C 5C281080 */ .word .L8010285C
// /* 3CC20 800DCC20 40281080 */ .word .L80102840
// /* 3CC24 800DCC24 40281080 */ .word .L80102840
// /* 3CC28 800DCC28 40281080 */ .word .L80102840

// glabel jpt_80102810
// /* 3CC0C 800DCC0C 18281080 */ .word .L80102818
// /* 3CC10 800DCC10 40281080 */ .word .L80102840
// /* 3CC14 800DCC14 40281080 */ .word .L80102840
// /* 3CC18 800DCC18 18281080 */ .word .L80102818
// /* 3CC1C 800DCC1C 5C281080 */ .word .L8010285C
// /* 3CC20 800DCC20 40281080 */ .word .L80102840
// /* 3CC24 800DCC24 40281080 */ .word .L80102840
// /* 3CC28 800DCC28 40281080 */ .word .L80102840

// glabel jpt_80102918
// /* 3CC2C 800DCC2C 20291080 */ .word .L80102920


// void func_801027C4(u32 arg0) {
//     POLY_GT4 *temp_v1;
//     POLY_GT4* temp_a1;
//     u8 temp_v0;
//     POLY_GT4 *temp_v1_2;

//     temp_v1 = &D_80086FEC[D_8013799C];
//     temp_a1 = temp_v1->tag;
//     switch (arg0) {
//     case 0:
//     case 3:
//         temp_v1_2->x1 = 0;
//         temp_v1_2->clut = 0;
//         temp_v1_2 = (POLY_GT4*)temp_v1->tag;//->tag;
//         D_801379A8 = arg0 + 1;
//         return;
//     case 1:
//     case 2:
//     case 5:
//     case 6:
//     case 7:
//         temp_v1->x1 = 0;
//         temp_v1->clut = 0;
//         D_801379A4 = arg0 + 1;
//         return;
//     case 4:
//         temp_v1->x1 = 0xFF;
//         temp_v1->clut = 1;
//         D_801379A4 = 2;
//         temp_v0 = (u8) temp_v1->x1;
//         temp_a1->b0 = temp_v0;
//         temp_a1->g0 = temp_v0;
//         temp_a1->r0 = temp_v0;
//         temp_v1->b0 = temp_v0;
//         temp_v1->g0 = temp_v0;
//         temp_v1->r0 = temp_v0;
//         temp_a1->pad3 = 0xD1U;
//         temp_v1->pad3 = 0xD1;
//         /* fallthrough */
//     default:
//         return;
//     }
// }

// void func_801027C4(u32 arg0) {
//     u8 new_var;
//     POLY_GT4* poly1;
//     POLY_GT4* poly2;
//     u8 temp_v0;
//     poly1 = &D_80086FEC[D_8013799C];
//     poly2 = poly1->tag;
//     switch (arg0) {
//     case 0:
//     case 3:
//         poly1 = (POLY_GT4*)poly1->tag;
//         poly1 = (POLY_GT4*)poly1->tag;
//         poly1->x1 = 0;
//         poly1->clut = 0;
//         D_801379A8 = arg0 + 1;
//         return;
//     case 1:
//     case 2:
//     case 5:
//     case 6:
//     case 7:
//         poly1->x1 = 0;
//         poly1->clut = 0;
//         D_801379A4 = arg0 + 1;
//         return;
//     case 4:
//         poly1->x1 = 0xFF;
//         poly1->clut = 1;
//         do {
//             D_801379A4 = 2;
//             temp_v0 = (*(u8**)&poly1->g1);
//             new_var = temp_v0;
//             poly2->b0 = new_var;
//             poly2->g0 = new_var;
//         } while (0);
//         poly2->r0 = new_var;
//         poly1->b0 = temp_v0;
//         poly1->g0 = new_var;
//         poly1->r0 = temp_v0;
//         poly2->pad3 = 0xD1U;
//         poly1->pad3 = 0xD1;

//     default:
//         return;
//     }
// }
