#include "common.h"
#include "dra.h"

typedef struct
{
    u16 unk0;
    u16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} Unkstruct_mad_1;

extern RoomHeader g_rooms[];
extern Unkstruct_mad_1* D_801997DC;

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void func_80191D3C(Unkstruct3*);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018D8C8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DC28);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018DF0C);

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

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190838);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190884);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801908DC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801909D8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190AD8);

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
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190D8C);
#else
typedef struct
{
    u16 unk0;
    u16 unk2;
    u16 unk4;
} Unkstruct_80190D8C_1;

void func_80190838(s16, s16);
void func_801908DC(s16);
void func_80190AD8(s16);
extern s32* D_801803C8;
extern Unkstruct_80190D8C_1* D_801997D8;
extern s8 D_801997E0;
extern s8 D_801997E4;
extern u16* g_pStObjLayout[];

void func_80190D8C(s32 arg0) {
    s16 temp_s0;
    s16 temp_v0_3;
    s32 temp_a0;
    u16 temp_a0_2;
    u16* temp_a1;
    Unkstruct_80190D8C_1* temp_v1;
    Unkstruct_mad_1* temp_v0_2;
    s32 phi_a0;
    s32 phi_a1;
    s16 phi_a1_2;

    temp_a0 = arg0 * 4;
    temp_a1 = g_pStObjLayout[arg0];
    D_801997D8 = temp_a1;
    D_801997DC = *(&D_801803C8 + temp_a0);
    if (*temp_a1 != 0xFFFE) {
        D_801997D8 = temp_a1 + 1;
        phi_a0 = func_8018E964() & 0xFF;
        phi_a1 = 0;
        
        while (true)
        {
            s32 temp_v0 = phi_a0 - D_801997D8->unk0;
            phi_a0 = temp_v0;
            if ((temp_v0 << 0x10) < 0)
                break;

            D_801997D8++;
            phi_a1++;
        }

        D_801997D8 = (temp_v1->unk4 << 0x10) + temp_v1->unk2;
        temp_v0_2 = (s16)phi_a1 + 1 + D_801997DC;
        D_801997DC = temp_v0_2;
        D_801997DC = (temp_v0_2->unk2 << 0x10) + temp_v0_2->unk0;
    }

    temp_a0_2 = D_80072B34.unkA;
    temp_v0_3 = temp_a0_2 - 0x40;
    temp_s0 = temp_a0_2 + 0x140;
    phi_a1_2 = temp_v0_3;
    if (temp_v0_3 >> 15) {
        phi_a1_2 = 0;
    }
    D_801997E0 = 0;
    D_801997E4 = 0;
    func_80190838(phi_a1_2, phi_a1_2);
    func_801908DC(temp_s0);
    func_80190AD8(D_80072B34.unkE + 0x120);
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190F04);
#else
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
    
    temp_v0_2 = D_800973B8[0].next;
    if (temp_v0_2 != 0) {
        u16 temp_a0_2 = s0->unkE;
        if (temp_v0_2 > 0)
            func_80190B7C(temp_a0_2 + 0x120);
        else
            func_80190C78(temp_a0_2 - 0x40);
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190FB8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019102C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801910A8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191120);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191D3C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191DA8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191E24);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191E6C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80191F24);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019203C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192078);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801920AC);

void func_801920F0(void) {
    D_8006C26C->unk0 = D_8006C26C->unk0 + D_8006C26C->unk8;
    D_8006C26C->unk4 = D_8006C26C->unk4 + D_8006C26C->unkC;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192120);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019214C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192190);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192408);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192618);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192800);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192860);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019288C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801928A8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192914);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019294C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192994);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801929DC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192A34);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AC0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AF0);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192B28);

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

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801994D8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199508);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199584);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019960C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801996EC);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80199740);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019976C);
