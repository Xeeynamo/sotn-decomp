#include "stage.h"

void func_8019A3A8(Entity* entity);
void func_8019C63C(Entity*);
void func_8019B0B8(Entity*);
void func_8019A3A8(Entity* entity);
void func_80198F18(s16);
void func_80199014(s16);
void func_801991CC(s16);
void func_801992C8(s16);
void func_801A046C(u16);
void func_8019A490();
void func_8019BDC8(struct Entity*);
void func_8019C7DC(struct Entity*);
Entity* func_8019AC18(Entity*, Entity*);
s32 func_8019A4D8(Entity*, Entity*);

extern u16 D_80181420[];
extern Entity* D_80180470;
extern Entity* D_80181338;
extern PfnEntityUpdate D_801803C4[];
extern Entity D_801804E8;
extern Entity D_8018050C;
extern u16 D_800733FC;
extern PfnEntityUpdate D_801803C4[];
extern s16 D_801A3EDE;
extern u16 D_801A3EE0;
extern s16 D_801A3EE2;
extern s16 D_801A3EE4;
extern s16 D_801A3EE6;
extern s16 D_801A3EEA;
extern s8 D_801A3EEE;
extern s8 D_801A3EEF;
extern s16 D_801A3F14;
extern s16 D_801A3F16;
extern s32 D_801A3F18;
extern s8 D_801811AC[]; // c_HeartPrizes[]
extern s32 D_80180668;
extern Entity* D_801804AC;
extern u16 D_80180528[];

void func_80191A64(Entity* entity) {
    ObjInit2* obj = &D_80180528[entity->subId * 10];

    if (entity->initState == 0) {
        func_8019B0B8(&D_801804AC);
        entity->animationSet = obj->animationSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.data;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->unk18 = obj->unkA;

        if (obj->unkC != 0) {
            entity->unk34 = obj->unkC;
        }

        if (entity->subId == 1) {
            entity->unk1C = 0x200;
            entity->unk1A = 0x200;
        }
    }

    func_8019A4D8(obj->unk10, entity);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191B44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191D00);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80191E34);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80192104);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193B3C);

void func_80193D7C(Entity* entity) {
    if (entity->initState == 0) {
        func_8019B0B8(&D_801804E8);
    }

    entity->posX.Data.high = entity[-1].posX.Data.high;
    entity->animationFrame = 0;
    entity->posY.Data.high = entity[-1].posY.Data.high;
    entity->unk14 = entity[-1].unk14;

    if (entity[-1].animationFrame == 0x32) {
        entity->animationFrame = 0x3E;
    }

    if (entity[-1].animationFrame == 0x33) {
        entity->animationFrame = 0x3F;
    }

    entity->zPriority = D_800733FC + 4;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80193E18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194214);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194488);

void func_801946C4(Entity* entity) {
    switch (entity->initState) {
    case 0:
        func_8019B0B8(&D_8018050C);
        entity->animationFrame = 0;
        entity->unk19 = 4;
        entity->unk3C = 0;
    case 1:
        if (entity[-1].animationFrame != 0) {
            entity->unk3C = 1;
            entity->animationFrame = 0x56;
        }
        if (entity->unk48 != 0) {
            D_80180668 = 1;
        }
        if (entity[-1].objectId != 0x1E) {
            func_8019A3A8(entity);
        }
    }
}

void func_80194774(void) {
    D_801A3EE4 = 2;
    D_801A3EE2 = 2;
    D_801A3EE6 = 0;
    D_801A3EEA = 0;
    D_801A3EEE = 0;
    D_801A3EEF = 8;
    D_801A3EDE = D_801A3EE0 + 20;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801947C8);

void func_8019498C(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801949E8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194AA0);

void func_80194C24(s32 arg0) {
    D_801A3F18 = arg0 + 0x100000;
    D_801A3F16 = 0;
    D_801A3F14 = 1;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194C50);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194F14);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80194FF4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801950F8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801961DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196238);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196678);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019697C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80196CC8);

u32 func_80196F90(void) {
    g_randomNext = (g_randomNext * 0x01010101) + 1;
    return g_randomNext >> 0x18;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", UpdateStageEntities);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801972BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801973C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801984DC);

void func_80198B80(Entity* entity, ObjectInit* initDesc) { // CreateEntity
    func_8019A3A8(entity);
    entity->objectId = initDesc->flags & 0x3FF;
    do { //! FAKE https://decomp.me/scratch/zysYC
        entity->pfnUpdate = D_801803C4[entity->objectId];
    } while (0);
    entity->posX.Data.high = initDesc->posX - D_8007308E;
    entity->posY.Data.high = initDesc->posY - (u16)D_80073092;
    entity->subId = initDesc->unk8;
    entity->unk32 = initDesc->unk6 >> 8;
    entity->unk68 = (initDesc->flags >> 0xA) & 7;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198C44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198D5C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198E74);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198EC0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80198F18);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199014);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199128);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199174);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801991CC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801992C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801993DC);

void func_80199554(void) {
    Unkstruct8* currentRoomTileLayout = &g_CurrentRoomTileLayout;

    if (D_80097908 != 0) {
        s16 tmp = D_8007308E;
        if (D_80097908 > 0) {
            func_80198F18(tmp + 0x140);
        } else {
            func_80199014(tmp - 0x40);
        }
    }
    if (D_8009790C != 0) {
        s16 tmp = currentRoomTileLayout->unkE;
        if (D_8009790C > 0) {
            func_801991CC(tmp + 0x120);
        } else {
            func_801992C8(tmp - 0x40);
        }
    }
}

// https://decomp.me/scratch/FLExi
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199608);
#else
void func_80199608(u16 objectId, Entity* entity) {
    func_8019A3A8(entity);

    entity->objectId = objectId;
    entity->pfnUpdate = D_801803C4[objectId];
    entity->posX.Data.high = (s16)(u16)D_8006C3B8->posX.Data.high;
    entity->posY.Data.high = (s16)(u16)D_8006C3B8->posY.Data.high;
}
#endif

// This function matches with PSYQ4.0 GCC 2.7.2 with -02 Optimization flag
// https://decomp.me/scratch/99NPO
#ifndef NON_MATCHING
void func_8019967C(u16 objectId, Entity* arg1, Entity* arg2);
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019967C);
#else
void func_8019967C(u16 objectId, Entity* arg1, Entity* arg2) {
    func_8019A3A8(arg2);
    arg2->objectId = objectId;
    arg2->pfnUpdate = D_801803C4[objectId];
    arg2->posX.Data.high = arg1->posX.Data.high;
    arg2->posY.Data.high = arg1->posY.Data.high;
}
#endif

s32 func_801996F8(Unkstruct5* arg0) {
    s16 var_v0_2;

    var_v0_2 = D_800733DA - arg0->unk2;
    var_v0_2 = ABS_ALT(var_v0_2);

    if (var_v0_2 >= 0x11) {
        var_v0_2 = 0;
    } else {
        var_v0_2 = D_800733DE - arg0->unk6;
        var_v0_2 = ABS_ALT(var_v0_2);
        var_v0_2 = var_v0_2 < 0x21;
    }

    return var_v0_2;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_80199770);

void func_8019A3A8(Entity* item) { // DestroyEntity
    s32 i;
    s32 length;
    u32* ptr;

    if (item->unk34 & 0x800000) {
        g_pfnFreePolygons(item->firstPolygonIndex);
    }

    ptr = (u32*)item;
    length = sizeof(Entity) / sizeof(s32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

void func_8019A414(s16 index) { // DestroyEntityFromIndex
    Entity* entity = &D_800733D8[index];

    while (entity < &D_8007EF1C) {
        func_8019A3A8(entity);
        entity++;
    }
}

// https://decomp.me/scratch/oUPTM
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A490);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A4D8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A590);

s32 func_8019A6A8(void) {
    s16 value = D_8006C3B8->posX.Data.high - D_800733DA;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s32 func_8019A6E4(void) {
    s32 value = D_8006C3B8->posY.Data.high - D_800733DE;

    if (value < 0) {
        value = -value;
    }
    return value;
}

s16 func_8019A718(void) {
    s16 var_a0 = D_8006C3B8->posX.Data.high > D_800733DA;

    if (D_8006C3B8->posY.Data.high > D_800733DE) {
        var_a0 |= 2;
    }
    return var_a0;
}

void func_8019A75C(void) { // MoveEntity
    D_8006C3B8->posX.value += D_8006C3B8->accelerationX;
    D_8006C3B8->posY.value += D_8006C3B8->accelerationY;
}

void func_8019A78C(void) { // FallEntity
    if (D_8006C3B8->accelerationY < FALL_TERMINAL_VELOCITY) {
        D_8006C3B8->accelerationY += FALL_GRAVITY;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019A7B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AA30);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AC18);

// This function matches with PSYQ4.0 GCC 2.7.2 with -01 and -02 Optimization
// flags https://decomp.me/scratch/dlcph
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019AC78);
#else
extern s16 D_80180D80[];

s32 func_8019AC78(u8 arg0, s16 arg1) { return D_80180D80[arg0] * arg1; }
#endif

// This function matches with PSYQ4.0 GCC 2.7.2 with -01 and -02 Optimization
// flags https://decomp.me/scratch/reosO
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ACA4);
s32 func_8019AC78(u8, s16);
#else
extern s16 D_80180D80[];

s16 func_8019ACA4(u8 arg0) { return D_80180D80[arg0]; }
#endif

void func_8019ACC0(s32 arg0, s16 arg1) {
    D_8006C3B8->accelerationX = func_8019AC78(arg0, arg1);
    D_8006C3B8->accelerationY = func_8019AC78(arg0 - 0x40, arg1);
}

u8 func_8019AD2C(s16 x, s16 y, u16 z) { return ((ratan2(y, x) >> 4) + 0x40); }

u8 func_8019AD64(ObjInit2* arg0, ObjInit2* arg1) {
    u16 x, y, z;

    x = arg1->zPriority - arg0->zPriority;
    y = arg1->palette - arg0->palette;
    z = arg0->zPriority;

    return func_8019AD2C(x, y, z);
}

// https://decomp.me/scratch/zbNsT
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019ADAC);
#else
u8 func_8019ADAC(s16 arg0, s16 arg1, u16 arg2) {
    s16 x, y, z;

    x = arg0 - D_8006C3B8->posX.Data.high;
    y = arg1 - D_8006C3B8->posY.Data.high;
    z = arg2;

    return func_8019AD2C(x, y, z);
}
#endif

u8 func_8019ADF4(u8 arg0, u8 arg1, u8 arg2) {
    u8 var_v0;
    s8 temp_a2 = arg2 - arg1;

    if (temp_a2 < 0) {
        var_v0 = -temp_a2;
    } else {
        var_v0 = temp_a2;
    }

    if (var_v0 > arg0) {
        if (temp_a2 < 0) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_8019AE4C(u16 slope, s16 speed) {
    Entity* entity;
    s32 moveX;
    s32 moveY;

    moveX = rcos(slope) * speed;
    entity = D_8006C3B8;

    if (moveX < 0) {
        moveX += 15;
    }

    entity->accelerationX = moveX >> 4;

    moveY = rsin(slope) * speed;
    entity = D_8006C3B8;

    if (moveY < 0) {
        moveY += 15;
    }

    entity->accelerationY = moveY >> 4;
}

u16 func_8019AED8(s16 arg0, s16 arg1) { return ratan2(arg1, arg0); }

u16 func_8019AF08(Entity* a, Entity* b) {
    s32 diffX = b->posX.Data.high - a->posX.Data.high;
    s32 diffY = b->posY.Data.high - a->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_8019AF40(s32 x, s32 y) {
    s16 diffX = x - (u16)D_8006C3B8->posX.Data.high;
    s16 diffY = y - (u16)D_8006C3B8->posY.Data.high;
    return ratan2(diffY, diffX);
}

u16 func_8019AF88(u16 arg0, s16 arg1, s16 arg2) {
    u16 var_v0 = arg1;
    u16 temp_a2 = arg2 - arg1;
    u16 var_v0_2;

    if (temp_a2 & 0x800) {
        var_v0_2 = (0x800 - temp_a2) & 0x7FF;
    } else {
        var_v0_2 = temp_a2;
    }

    if (var_v0_2 > arg0) {
        if (temp_a2 & 0x800) {
            var_v0 = arg1 - arg0;
        } else {
            var_v0 = arg1 + arg0;
        }

        return var_v0;
    }

    return arg2;
}

void func_8019AFE8(u8 arg0) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->initState = arg0;
    entity->unk2E = 0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_8019B008(u8 arg0) {
    Entity* entity;

    entity = D_8006C3B8;
    entity->unk2E = arg0;
    entity->animationFrameIndex = 0;
    entity->animationFrameDuration = 0;
}

void func_8019B024(u16 arg0, u16 arg1) {
    Entity* entity;

    if (arg1 != 0) {
        func_801A046C(arg1);
    }

    if (arg0 == 0xFF) {
        func_8019A3A8(D_8006C3B8);
        return;
    }

    entity = D_8006C3B8;
    entity->unk19 = 0;
    entity->objectId = EntityExplosionID;
    entity->pfnUpdate = (PfnEntityUpdate)func_8019C63C;
    entity->subId = arg0;
    entity->animationFrame = 0;
    D_8006C3B8->initState = 0;
    D_8006C3B8->unk2E = 0;
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B0B8);

void func_8019B1B4(Entity* arg0) {
    if (arg0->initState == 0) {
        arg0->initState++;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B1DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B304);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B45C);

void func_8019B7A0(Entity* arg0) {
    u16 temp_a0;
    u16 var_v1;

    func_8019A490();
    if (!(D_8009796E & 2)) {
        func_8019A3A8(arg0);
        return;
    }

    temp_a0 = arg0->subId & 0xFFF;
    var_v1 = temp_a0;
    arg0->subId = var_v1;

    if (var_v1 < 0x80) {
        arg0->objectId = 3;
        arg0->pfnUpdate = func_8019BDC8;
        arg0->animationFrameDuration = 0;
        arg0->animationFrameIndex = 0;
    } else {
        var_v1 = temp_a0 - 0x80;
        arg0->objectId = 0xA;
        arg0->pfnUpdate = func_8019C7DC;
    }

    arg0->subId = var_v1;
    temp_a0 = 0;
    arg0->unk6D = 0x10;
    arg0->initState = temp_a0;
}

// This function matches with PSYQ4.0 GCC 2.7.2 with -02 Optimization flag
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B858);
#else
void func_8019B858(void) {
    s32 temp_v1;
    Entity* entity = D_8006C3B8;

    if (entity->accelerationY >= 0) {
        temp_v1 = entity->unk88 + entity->unk84.value;
        entity->unk84.value = temp_v1;
        entity->accelerationX = temp_v1;

        if ((temp_v1 == 0x10000) || (temp_v1 == -0x10000)) {
            entity->unk88 = -entity->unk88;
        }
        entity = D_8006C3B8;
    }

    if (entity->accelerationY < 0x00004000) {
        entity->accelerationY += 0x2000;
    }
}
#endif

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019B8DC);

// at -v0 register swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BA38);
#else
void func_8019BA38(u16 arg0) {
    s32* hearts;

    g_pfnPlaySfx(0x67A);
    hearts = &g_playerHeart;
    *hearts += D_801811AC[arg0];

    if (g_playerHeartMax < *hearts) {
        *hearts = g_playerHeartMax;
    }

    func_8019A3A8(D_8006C3B8);
}
#endif

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BAB8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BB94);

void func_8019BCAC(void) { // CollectHeartVessel
    if (g_CurrentPlayableCharacter != PLAYER_ALUCARD) {
        g_pfnPlaySfx(0x67A);
        g_playerHeart->unk0 += HEART_VESSEL_RICHTER;

        if (g_playerHeart->unk4 < g_playerHeart->unk0) {
            g_playerHeart->unk0 = g_playerHeart->unk4;
        }
    } else {
        g_pfnPlaySfx(0x67A);
        D_8003C848(HEART_VESSEL_INCREASE, 0x4000);
    }
    func_8019A3A8(D_8006C3B8);
}

void func_8019BD50(void) { // CollectLifeVessel
    g_pfnPlaySfx(0x67A);
    D_8003C848(LIFE_VESSEL_INCREASE, 0x8000);
    func_8019A3A8(D_8006C3B8);
}

void func_8019BDA0(void) { func_8019A3A8(D_8006C3B8); }

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019BDC8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019C63C);

void func_8019C738(Entity* arg0, s32 renderFlags) {
    POLY_GT4* poly;
    s16 left, top, right, bottom;

    poly = &D_80086FEC[arg0->firstPolygonIndex];

    left = arg0->posX.Data.high - 7;
    right = arg0->posX.Data.high + 7;
    poly->x2 = left;
    poly->x0 = left;
    poly->x3 = right;
    poly->x1 = right;

    top = arg0->posY.Data.high - 7;
    bottom = arg0->posY.Data.high + 7;
    poly->y1 = top;
    poly->y0 = top;
    poly->y3 = bottom;
    poly->y2 = bottom;

    if (renderFlags & RENDERFLAGS_NOSHADOW) {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                255;
    } else {
        poly->r0 = poly->r1 = poly->r2 = poly->r3 = poly->g0 = poly->g1 =
            poly->g2 = poly->g3 = poly->b0 = poly->b1 = poly->b2 = poly->b3 =
                128;
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019C7DC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019CDC4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019D074);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019DB44);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019DC6C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E1C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E2B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E3C8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E4F8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E5E0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E6D0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E7C4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019E9F4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019EAF0);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F070);

void func_8019F170(Entity* arg0) {
    if (arg0->initState == 0) {
        func_8019B0B8(&D_80180470);
        arg0->unk6C = 0xF0;
        arg0->unk1A = 0x1A0;
        arg0->unk1C = 0x1A0;
        arg0->animationSet = 8;
        arg0->animationFrame = 1;
        arg0->zPriority += 0x10;

        if (arg0->subId != 0) {
            arg0->palette = (s16)arg0->subId;
        } else {
            arg0->palette = 0x8160;
        }

        arg0->initState++;
        return;
    }

    func_8019A75C();

    if (!func_8019A4D8(&D_80181338, arg0)) {
        func_8019A3A8(arg0);
    }
}

// a0 -> v0 register swap
#ifndef NON_MATCHING
void func_8019F23C(u16 arg0, Entity* ent1, Entity* ent2);
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F23C);
#else
void func_8019F23C(u16 arg0, Entity* ent1, Entity* ent2) {
    u16 palette;

    func_8019A3A8(ent2);

    ent2->objectId = arg0;
    ent2->pfnUpdate = D_801803C4[arg0];
    ent2->posX.Data.high = ent1->posX.Data.high;
    ent2->posY.Data.high = ent1->posY.Data.high;
    ent2->unk5A = ent1->unk5A;
    ent2->zPriority = ent1->zPriority;
    ent2->animationSet = ent1->animationSet;
    ent2->unk34 = -0x32FFE000;
    palette = ent1->palette;

    if (palette & 0x8000) {
        ent2->palette = ent1->unk6A;
    } else {
        ent2->palette = palette;
    }
}
#endif

void func_8019F304(void) {
    Entity* entity;
    s8 temp_s4 = func_80196F90() & 3;
    s16 temp_s3 = ((func_80196F90() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = func_8019AC18(&D_8007D858, &D_8007D858[32]);
        if (entity != NULL) {
            func_8019967C(2, D_8006C3B8, entity);
            entity->unk84.Data1.unk1 = 6 - i;
            entity->unk80 = temp_s3;
            entity->unk84.Data1.unk0 = temp_s4;
        }
    }
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F3BC);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019F594);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_8019FB74);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0274);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A046C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0564);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A0734);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A13B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A174C);

void func_801A1BFC(Entity* entity) {
    ObjInit2* obj = &D_80181420[entity->subId * 10];    

    if (entity->initState == 0) {
        func_8019B0B8(&D_801804AC);
        entity->animationSet = obj->animationSet;
        entity->zPriority = obj->zPriority;
        entity->unk5A = obj->unk4.data;
        entity->palette = obj->palette;
        entity->unk19 = obj->unk8;
        entity->unk18 = obj->unkA;

        if (obj->unkC != 0) {
            entity->unk34 = obj->unkC;
        }

        if (entity->subId >= 5) {
            entity->unk1E = 0x800;
            entity->unk19 = entity->unk19 | 4;
        }
    }
    
    func_8019A4D8(obj->unk10, entity);
}

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A1CE8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2018);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2400);

// https://decomp.me/scratch/aRsTo
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2550);
#else
POLY_GT4* func_801A2550(POLY_GT4* arg0) {
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

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2580);

// https://decomp.me/scratch/IIvQX a0 -> v0 register swap
#ifndef NON_MATCHING
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A25FC);
#else
unkStruct3* func_801A25FC(unkStruct3* arg0, s32 arg1) {
    s32 i;
    s8 var_a2;

    if (arg0->unk2B != 0) {
        arg0->unk2B = 0;
    } else {
        arg0->unk2B = 1;
    }

    for (i = 0; i < arg1; i++) {
        if (arg0->unk2B != 0) {
            var_a2 = 0;
            arg0->unk32 &= 0xFFF7;
        } else {
            var_a2 = 1;
            arg0->unk32 |= 8;
        }

        if (arg0->unk0 != 0) {
            arg0->unk2B = var_a2;
        } else {
            return NULL;
        }
    }
    return arg0;
}
#endif

// need a weird struct for this one
INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2684);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2764);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A27B8);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A27E4);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2848);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2A58);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2C9C);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2E20);

INCLUDE_ASM("asm/st/dre/nonmatchings/11A64", func_801A2F10);
