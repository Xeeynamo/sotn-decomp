#include "common.h"
#include "dra.h"

typedef struct
{
    u8 unk0[0x32];
    u16 unk32;
} Unkstruct_mad_2;

extern s16 D_801809EC[];
extern RoomHeader g_rooms[];
extern ObjectInit* g_pStObjLayout[];
extern ObjectInit** D_801803C8[];

extern ObjectInit *D_801997D8;
extern ObjectInit* D_801997DC;

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void func_80191D3C(Unkstruct3*);
s32 func_80192914(s16 arg0, s16 arg1);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018D8C8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DC28);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DF0C);
#else
void func_8018DF0C(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 phi_v1;
    s16 phi_a2;
    s32 phi_a3;
    s16* phi_t0;
    s32 phi_a3_2;
    s16* phi_a2_2;
    s32 phi_v1_2;
    s32 phi_a3_3;
    s16* phi_a2_3;
    s32 phi_v1_3;
    s32 phi_a3_4;
    s16* phi_a2_4;
    s32 phi_v1_4;
    s32 phi_a3_5;
    s16* phi_a1;
    s32 phi_v1_5;

    for (phi_a3 = 0; phi_a3 < 0x10; phi_a3++) {
        phi_t0 = arg0;
        phi_v1_2 = 0;

        for (phi_v1 = 0; phi_v1 < 0x20; phi_v1++)
        {
            phi_a2 = -(((phi_a3 - 2) < 0xCU) ^ 1) & 3;
            if (phi_v1 - 2 >= 0x1C) {
                phi_a2 = 3;
            }

            *((phi_a3 << 5) + phi_t0) = phi_a2;
            phi_t0++;
        }
    }

    if (arg1 & 4) {
        for (phi_a3_2 = 6; phi_a3_2 < 0xA; phi_a3_2++) {
            phi_a2_2 = arg0;
loop_9:
            *((phi_a3_2 << 5) + phi_a2_2) = 0;
            phi_a2_2++;
            phi_v1_2++;
            if (phi_v1_2 < 2) {
                goto loop_9;
            }
        }
    }

    if (arg1 & 8) {
        for (phi_a3_3 = 6; phi_a3_3 < 0xA; phi_a3_3++) {
            phi_a2_3 = arg0 + 0x3C;
            phi_v1_3 = 0x1E;
loop_14:
            *((phi_a3_3 << 5) + phi_a2_3) = 0;
            phi_a2_3++;
            phi_v1_3++;
            if (phi_v1_3 < 0x20) {
                goto loop_14;
            }
        }
    }
    
    if (arg1 & 1) {
        for (phi_a3_4 = 0; phi_a3_4 < 2; phi_a3_4++) {
            phi_a2_4 = arg0 + 0xC;
            phi_v1_4 = 6;
loop_19:
            *((phi_a3_4 << 6) + ((((arg1 & 8) == 0) << 5) + phi_a2_4)) = 0;
            phi_a2_4++;
            phi_v1_4++;
            if (phi_v1_4 < 0xA) {
                goto loop_19;
            }
        }
    }
    
    if (arg1 & 2) {
        for (phi_a3_5 = 0xE; phi_a3_5 < 0x10; phi_a3_5++) {
            phi_a1 = arg0 + 0xC;
            phi_v1_5 = 6;
loop_24:
            *((phi_a3_5 << 6) + ((((arg1 & 8) == 0) << 5) + phi_a1)) = 0;
            phi_a1++;
            phi_v1_5++;
            if (phi_v1_5 < 0xA) {
                goto loop_24;
            }
        }
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E090);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E13C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E1D4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E5AC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E674);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E830);

u32 func_8018E964(void) {
    D_80097364 = (D_80097364 * 0x01010101) + 1;
    return D_80097364 >> 0x18;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E994);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EC90);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EDB8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018FEA0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190544);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190608);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190720);

void func_80190838(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997D8->unk0 == a1 || D_801997D8->unk0 < arg0) {
        D_801997D8++;
        goto loop_1;
    }
}

void func_80190884(s32 arg0) {
    s32 a2, a3;
    a3 = 0xFFFF;
    arg0 = (s16)arg0;
    a2 = 0xFFFE;
loop_1:
    if (D_801997D8->unk0 == a3 || (arg0 < D_801997D8->unk0) && (D_801997D8->unk0 != a2)) {
        D_801997D8--;
        goto loop_1;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801908DC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801909D8);

void func_80190AD8(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997DC->unk2 == a1 || D_801997DC->unk2 < arg0) {
        D_801997DC++;
        goto loop_1;
    }
}

void func_80190B24(s32 arg0) {
    while (true)
    {
        if (D_801997DC->unk2 == 0xFFFF)
            D_801997DC--;
        else if ((s16)arg0 >= D_801997DC->unk2 || D_801997DC->unk2 == 0xFFFE)
            break;
        else
            D_801997DC--;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190B7C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190C78);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", loadObjLayout);
#else
void func_801908DC(s16);
extern s8 D_801997E0;
extern s8 D_801997E4;

void loadObjLayout(s32 objLayoutId) {
    s16 temp_s0;
    s16 temp_v0_3;
    u16* pObjLayoutStart;
    ObjectInit* temp_v1;
    ObjectInit* temp_v0_2;
    s32 phi_a0;
    s16 phi_a1;
    s16 phi_a1_2;
    Unkstruct4* s1;

    pObjLayoutStart = g_pStObjLayout[objLayoutId];
    D_801997D8 = pObjLayoutStart;
    D_801997DC = D_801803C8[objLayoutId];
    s1 = &D_80072B34;
    if (*pObjLayoutStart != 0xFFFE) {
        D_801997D8 = pObjLayoutStart + 1;
        phi_a0 = func_8018E964() & 0xFF;
        
        for (phi_a1 = 0; ; phi_a1++)
        {
            s32 temp_v0 = phi_a0 - D_801997D8->unk0;
            D_801997D8 = (u16*)D_801997D8 + 1;
            phi_a0 = temp_v0;
            if (temp_v0 << 0x10 < 0)
                break;

            D_801997D8 = (u32*)D_801997D8 + 1;
        }

        D_801997D8 = (temp_v1->state << 0x10) + temp_v1->unk2;
        temp_v0_2 = (u32*)D_801997DC + (phi_a1 + 1);
        D_801997DC = temp_v0_2;
        D_801997DC = (temp_v0_2->unk2 << 0x10) + temp_v0_2->unk0;
    }

    temp_v0_3 = s1->unkA - 0x40;
    temp_s0 = s1->unkA + 0x140;
    phi_a1_2 = temp_v0_3;
    if (temp_v0_3 >> 15) {
        phi_a1_2 = 0;
    }
    
    D_801997E0 = 0;
    D_801997E4 = 0;
    func_80190838(phi_a1_2);
    func_801908DC(temp_s0);
    func_80190AD8(((u16)s1->unkE + 0x120) << 0x10 >> 0x10);
}
#endif

void func_80190F04(void) {
    Unkstruct4* s0 = &D_80072B34;
    s32 temp_v0_2;

    if (D_800973B4 != 0) {
        u16 temp_a0 = D_80072B3E;
        if (D_800973B4 > 0)
            func_801908DC(temp_a0 + 0x140);
        else
            func_801909D8(temp_a0 - 0x40);
    }
    
    temp_v0_2 = D_800973B8[0].tag;
    if (temp_v0_2 != 0) {
        u16 temp_a0_2 = s0->unkE;
        if (temp_v0_2 > 0)
            func_80190B7C(temp_a0_2 + 0x120);
        else
            func_80190C78(temp_a0_2 - 0x40);
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190FB8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019102C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801910A8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191120);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191D3C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191DA8);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191E24);
#else
void func_80191E24(Unkstruct_mad_2 *arg0) {
    if (arg0->unk32 != 0) {
        u32 temp_a0_2 = arg0->unk32 - 1;
        s32 *temp_v1 = &D_80096ED8[(temp_a0_2 >> 5) & 0xFFFF];
        *temp_v1 |= 1 << (temp_a0_2 & 0x1F);
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191E6C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191F24);

s32 func_8019203C(void) {
    s16 value = D_8006C26C->unk0.Data.unk2 - D_80072E8A;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_80192078(void) {
    s32 value = D_8006C26C->unk4.Data.unk2 - D_80072E8E;
    return value < 0 ? -value : value;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801920AC);
#else
s32 func_801920AC(void) {
    s32 flags, v1;
    flags = D_80072E8A < D_8006C26C->unk0.Data.unk2;
    v1 = D_8006C26C->unk4.Data.unk2;
    if (D_80072E8E < v1) {
        flags |= 2;
    }
    return flags;
}
#endif

void func_801920F0(void) {
    D_8006C26C->unk0.data = D_8006C26C->unk0.data + D_8006C26C->unk8;
    D_8006C26C->unk4.data = D_8006C26C->unk4.data + D_8006C26C->unkC;
}

void func_80192120(void) {
    if (D_8006C26C->unkC <= 0x5FFFF) {
        D_8006C26C->unkC = D_8006C26C->unkC + 0x4000;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019214C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192190);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192408);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192618);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192800);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192860);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019288C);
#else
s16 func_8019288C(s32 arg0) {
    return D_801809EC[arg0 & 0xFF];
}
#endif


INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801928A8);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192914);
#else
s32 func_80192914(s16 arg0, s16 arg1) {
    return ((func_800190AC(arg1, arg0) >> 4) + 0x40) & 0xFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019294C);
#else
s32 func_8019294C(Unkstruct3* a, Unkstruct3* b) {
    s32 a0 = (u16)b->unk0.Data.unk2 - (u16)a->unk0.Data.unk2;
    s32 a1 = (u16)b->unk4.Data.unk2 - (u16)a->unk4.Data.unk2;
    return func_80192914(a0, a1) & 0xFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192994);
#else
u32 func_80192994(s32 arg0, s32 arg1) {
    s32 a0 = arg0 - (u16)D_8006C26C->unk0.Data.unk2;
    s32 a1 = arg1 - (u16)D_8006C26C->unk4.Data.unk2;
    return func_80192914(a0, a1) & 0xFF;
}
#endif


INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801929DC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192A34);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AC0);
#else
s32 func_80192AC0(s16 arg0, s16 arg1) {
    return func_800190AC(arg1, arg0) & 0xFFFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AF0);
#else
s32 func_80192AF0(Unkstruct3* a, Unkstruct3* b) {
    s32 a0 = b->unk4.Data.unk2 - a->unk4.Data.unk2;
    s32 a1 = b->unk0.Data.unk2 - a->unk0.Data.unk2;
    return func_800190AC(a0, a1) & 0xFFFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192B28);
#else
u16 func_80192B28(s32 arg0, s32 arg1) {
    s16 a0 = arg1 - (u16)D_8006C26C->unk4.Data.unk2;
    s16 a1 = arg0 - (u16)D_8006C26C->unk0.Data.unk2;
    return func_800190AC(a0, a1);
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192B70);

void func_80192BD0(s32 arg0) {
    D_8006C26C->unk2C = (s16) (arg0 & 0xFF);
    D_8006C26C->unk2E = 0;
    D_8006C26C->unk50 = 0;
    D_8006C26C->unk52 = 0;
}

void func_80192BF0(s32 arg0) {
    D_8006C26C->unk2E = (s16) (arg0 & 0xFF);
    D_8006C26C->unk50 = 0;
    D_8006C26C->unk52 = 0;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192C0C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192CAC);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192DA8);
#else
void func_80192DA8(Unkstruct3* arg0) {
    if (arg0->unk2C == 0) {
        arg0->unk2C++;
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192DD0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192EF8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80193050);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80193394);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019344C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801934D0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019362C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801936E0);

void func_801937BC(void) {
}

void func_801937C4(void) {
    func_80191D3C(D_8006C26C);
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801937EC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801938FC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019394C);

void func_8019399C(void) {
    func_80191D3C(D_8006C26C);
}

Unkstruct3* func_801939C4(void) {
    D_8006C26C->unk2C = 3;
    D_8006C26C->unk30 = 4;
    return D_8006C26C;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801939E0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80194218);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80194314);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801943EC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801949C0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195520);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019563C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019572C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019583C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019596C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195A54);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195B44);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195C38);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195E68);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80195F64);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801964E4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801965E4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801966B0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019686C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80196934);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801969EC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80196BC4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801971A4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801978A4);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80197A9C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80197B94);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801982BC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198650);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198B00);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198BC8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80198FA0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199388);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801994D8);
#else
POLY_GT4* func_801994D8(POLY_GT4* arg0) {
    if (arg0 != NULL) {
loop_1:
        if (arg0->p3 != NULL) {
            arg0 = arg0->tag;
            if (arg0 != NULL) {
                goto loop_1;
            }
        }
    }
    return arg0;
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199508);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199584);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019960C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801996EC);

void func_80199740(POLY_GT4* arg0) {
    arg0->p3 = 0;
    arg0->pad3 = 8;
    ((POLY_GT4*)arg0->tag)->p3 = 0;
    ((POLY_GT4*)arg0->tag)->code = 4;
    ((POLY_GT4*)arg0->tag)->pad3 = 8;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019976C);
#else
s32 func_8019976C(s32 arg0, s32 value) {
    s32 temp_t0;
    u8* phi_v1;
    u8* phi_a0;
    int i;
    s32 phi_a2;
    s32 phi_a2_2;

    phi_v1 = arg0 + 4;
    phi_a2 = 0;
    for (i = 0, phi_a2_2 = 0; i < 4; i++)  {
        phi_v1 = phi_a0;
loop_2:
        *phi_v1 -= value;
        if ((u32) *phi_v1 >= 0xF9) {
            *phi_v1 = 0;
        } else {
            phi_a2 |= 1;
        }

        phi_v1++;
        if (phi_v1 < (phi_a0 + 3)) {
            goto loop_2;
        }

        phi_a0 += 0xC;
    }

    return phi_a2 & 0xFF;
}
#endif
