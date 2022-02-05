#include "common.h"
#include "dra.h"

typedef struct
{
    u8 unk0[0x32];
    u16 unk32;
} Unkstruct_mad_2;

typedef struct
{
    u_long	tag;
    s8 unk4, unk5, unk6, unk7;
    s16 unk8, unkA;
    s16 unkC, unkE;
    s16 unk10;
    s8 unk12;
    s8 unk13;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s8 unk1E;
    s8 unk1F;
    s16 unk20;
    s16 unk22;
    s8 unk24;
    s8 unk25;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} Unkstruct_mad_3;

typedef struct
{
    u_long	tag;
    s8 unk4, unk5, unk6, unk7;
    s16 unk8, unkA;
    s16 unkC, unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s8 unk24;
    s8 unk25;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} Unkstruct_mad_4;

extern s16 D_801809EC[];
extern RoomHeader g_rooms[];
extern ObjectInit* g_pStObjLayout[];
extern ObjectInit** D_801803C8[];
extern PfnEntityUpdate PfnEntityUpdates[];

extern ObjectInit *D_801997D8;
extern ObjectInit* D_801997DC;
extern u8 D_801997E0;
extern s8 D_801997E4;

void func_801908DC(s16);
void func_801909D8(s16);
void func_80190B7C(s16);
void func_80190C78(s16);
void DestroyEntity(Entity*);
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

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", EntityCandle);

u32 func_8018E964(void) {
    D_80097364 = (D_80097364 * 0x01010101) + 1;
    return D_80097364 >> 0x18;
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018E994);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EC90);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018EDB8);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8018FEA0);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", InitializeEntity);
#else
void InitializeEntity(Entity* entity, ObjectInit* initDesc) {
    DestroyEntity(entity);
    entity->objectId = initDesc->unk4 & 0x3FF;
    entity->pfnUpdate = PfnEntityUpdates[entity->objectId];
    entity->posX.Data.high = initDesc->posX - D_80072B3E;
    entity->posY.Data.high = initDesc->posY - D_80072B42;
    entity->unk30 = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = initDesc->unk4 >> 0xA & 7;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190608);
#else
void func_80190608(ObjectInit* initDesc) {
    s16 temp_a2;
    s16 temp_v1_2;
    s16 phi_a0;
    Entity* entity;

    temp_a2 = D_80072B42 + 0x120;
    phi_a0 = D_80072B42 - 0x40;
    if (phi_a0 < 0) {
        phi_a0 = 0;
    }
    
    temp_v1_2 = initDesc->posY;
    if (temp_v1_2 >= phi_a0 && temp_a2 >= temp_v1_2 && (initDesc->unk4 & 0xE000) != 0x8000) {
        switch (initDesc->unk4 & 0xE000) {
        case 0x0:
            entity = &D_80075D88[*(u8*)&initDesc->unk6];
            if (entity->objectId != 0) {
                break;
            }
            InitializeEntity(entity, initDesc);
            break;
        case 0xA000:
            InitializeEntity(&D_80075D88[initDesc->unk6], initDesc);
            break;
        }
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190720);

void func_80190838(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997D8->posX == a1 || D_801997D8->posX < arg0) {
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
    if (D_801997D8->posX == a3 || (arg0 < D_801997D8->posX) && (D_801997D8->posX != a2)) {
        D_801997D8--;
        goto loop_1;
    }
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801908DC);
#else
void func_801908DC(s16 arg0) {
    u32 temp_a0, temp_v1_2;
    if (D_801997E0 != 0) {
        func_80190838((s16) (arg0 - D_800973B4));
        D_801997E0 = 0;
    }

    while (true) {
        if (D_801997D8->posX == 0xFFFF || arg0 < D_801997D8->posX)
            break;

        temp_a0 = ((u32) D_801997D8->unk6 >> 8) + 0xFF;
        temp_v1_2 = temp_a0 & 0xFF;
        if (temp_v1_2 == 0xFF || (((1 << (temp_a0 & 0x1F)) & D_80096ED8[temp_v1_2 >> 5]) == 0)) {
            func_80190608(D_801997D8);
        }
        D_801997D8++;
    }
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801909D8);

void func_80190AD8(s32 arg0) {
    s32 a1 = 0xFFFE;
    arg0 = (s16)arg0;
loop_1:
    if (D_801997DC->posY == a1 || D_801997DC->posY < arg0) {
        D_801997DC++;
        goto loop_1;
    }
}

void func_80190B24(s32 arg0) {
    while (true)
    {
        if (D_801997DC->posY == 0xFFFF)
            D_801997DC--;
        else if ((s16)arg0 >= D_801997DC->posY || D_801997DC->posY == 0xFFFE)
            break;
        else
            D_801997DC--;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190B7C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80190C78);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", LoadObjLayout);
#else
void LoadObjLayout(s32 objLayoutId) {
    s16 temp_s0;
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
            s32 temp_v0 = phi_a0 - D_801997D8->posX;
            D_801997D8 = (u16*)D_801997D8 + 1;
            phi_a0 = temp_v0;
            if (temp_v0 << 0x10 < 0)
                break;

            D_801997D8 = (u32*)D_801997D8 + 1;
        }

        D_801997D8 = (temp_v1->unk4 << 0x10) + temp_v1->posY;
        temp_v0_2 = (u32*)D_801997DC + (phi_a1 + 1);
        D_801997DC = temp_v0_2;
        D_801997DC = (temp_v0_2->posY << 0x10) + temp_v0_2->posX;
    }

    temp_s0 = s1->unkA + 0x140;
    phi_a1_2 = s1->unkA - 0x40;
    if (phi_a1_2 < 0) {
        phi_a1_2 = 0;
    }
    
    D_801997E0 = 0;
    D_801997E4 = 0;
    func_80190838(phi_a1_2);
    func_801908DC(temp_s0);
    func_80190AD8((s16)(s1->unkE + 0x120));
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

void DestroyEntity(Entity* item) {
    int i, length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        D_8003C6B0(item->unk64);
    }

    ptr = item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

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
    s16 value = D_8006C26C->posX.Data.high - D_80072E8A;
    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_80192078(void) {
    s32 value = D_8006C26C->posY.Data.high - D_80072E8E;
    return value < 0 ? -value : value;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801920AC);
#else
s32 func_801920AC(void) {
    s32 unk, v1;
    unk = D_80072E8A < D_8006C26C->posX.Data.high;
    v1 = D_8006C26C->posY.Data.high;
    if (D_80072E8E < v1) {
        unk |= 2;
    }
    return unk;
}
#endif

void func_801920F0(void) {
    D_8006C26C->posX.value = D_8006C26C->posX.value + D_8006C26C->accelerationX;
    D_8006C26C->posY.value = D_8006C26C->posY.value + D_8006C26C->accelerationY;
}

void func_80192120(void) {
    if (D_8006C26C->accelerationY <= 0x5FFFF) {
        D_8006C26C->accelerationY = D_8006C26C->accelerationY + 0x4000;
    }
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019214C);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192190);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192408);

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192618);

Entity* func_80192800(Entity* arg0, Entity* arg1) {
    while (arg0 < arg1)
    {
        if (arg0->objectId == 0)
        {
            DestroyEntity(arg0);
            return arg0;
        }

        arg0++;
    }
    return NULL;
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192860);
#else
s32 func_80192860(s32 arg0, s16 arg1) {
    return D_801809EC[arg0 & 0xFF] * arg1;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019288C);
#else
s16 func_8019288C(s32 arg0) {
    return D_801809EC[arg0 & 0xFF];
}
#endif

void func_801928A8(s32 arg0, s16 arg1) {
    D_8006C26C->accelerationX = func_80192860(arg0 & 0xFF, arg1);
    D_8006C26C->accelerationY = func_80192860((arg0 - 0x40) & 0xFF, arg1);
}

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192914);
#else
s32 func_80192914(s16 x, s16 y) {
    return ((func_800190AC(y, x) >> 4) + 0x40) & 0xFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_8019294C);
#else
s32 func_8019294C(Entity* a, Entity* b) {
    s32 diffX = (u16)b->posX.Data.high - (u16)a->posX.Data.high;
    s32 diffY = (u16)b->posY.Data.high - (u16)a->posY.Data.high;
    return func_80192914(diffX, diffY) & 0xFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192994);
#else
u32 func_80192994(s32 x, s32 y) {
    s32 diffX = x - (u16)D_8006C26C->unk0.Data.high;
    s32 diffY = y - (u16)D_8006C26C->unk4.Data.high;
    return func_80192914(diffX, diffY) & 0xFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801929DC);
#else
u8 func_801929DC(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_a2 = (arg2 - arg1) << 0x18;
    u8 phi_v0 = temp_a2 ? -temp_a2 : temp_a2;

    if ((u8)arg0 < phi_v0) {
        s32 phi_v0_2 = temp_a2 << 0x18 ? (arg1 - arg0) : (arg1 + arg0);
        return phi_v0_2;
    }
    
    return arg2;
}
#endif

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192A34);

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AC0);
#else
s32 func_80192AC0(s16 x, s16 y) {
    return func_800190AC(y, x) & 0xFFFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192AF0);
#else
s32 func_80192AF0(Entity* a, Entity* b) {
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    return func_800190AC(diffY, diffX) & 0xFFFF;
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192B28);
#else
u16 func_80192B28(s32 x, s32 y) {
    s16 diffY = y - (u16)D_8006C26C->posY.Data.high;
    s16 diffX = x - (u16)D_8006C26C->posX.Data.high;
    return func_800190AC(diffY, diffX);
}
#endif

#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_80192B70);
#else
u16 func_80192B70(s32 arg0, s32 arg1, s32 arg2) {
    u32 temp_a2 = arg2 - arg1;
    u16 phi_v0 = temp_a2 & 0x800 ? (0x800 - temp_a2) & 0x7FF : temp_a2;
    
    if ((u16)arg0 < phi_v0) {
        u16 ret = temp_a2 & 0x800 ? (arg1 - arg0) : (arg1 + arg0);
        return ret;
    }

    return arg2;
}
#endif

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
void func_80192DA8(Entity* arg0) {
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
    DestroyEntity(D_8006C26C);
}

INCLUDE_ASM("asm/st/mad/nonmatchings/D8C8", func_801937EC);

void func_801938FC(void) {
    D_8003C6D8(0x670);
    D_8003C744(5, 0x4000);
    DestroyEntity(D_8006C26C);
}

void func_8019394C(void) {
    D_8003C6D8(0x670);
    D_8003C744(5, 0x8000);
    DestroyEntity(D_8006C26C);
}

void func_8019399C(void) {
    DestroyEntity(D_8006C26C);
}

Entity* func_801939C4(void) {
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

void func_8019960C(Unkstruct_mad_3* arg0) {
    arg0->unk13 = 0;
    arg0->unk1F = 0;
    arg0->unk2B = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk14 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk16 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unkA = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk8 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unkE = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unkC = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk12 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk10 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk18 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk1A = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk1C = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk1E = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk24 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk25 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk28 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk2A = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk20 = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk22 = 0;
}

void func_801996EC(Unkstruct_mad_3* arg0) {
    func_8019960C(arg0);
    arg0->unk2B = 8;
    ((Unkstruct_mad_4*)arg0->tag)->unk2B = 1;
    ((Unkstruct_mad_4*)arg0->tag)->unk7 = 2;
    ((Unkstruct_mad_4*)arg0->tag)->unk32 = 0xA;
}

void func_80199740(Unkstruct_mad_4* arg0) {
    arg0->unk2B = 0;
    arg0->unk32 = 8;
    ((Unkstruct_mad_4*)arg0->tag)->unk2B = 0;
    ((Unkstruct_mad_4*)arg0->tag)->unk7 = 4;
    ((Unkstruct_mad_4*)arg0->tag)->unk32 = 8;
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
