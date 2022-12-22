/*
 * File: 2C048.c
 * Overlay: SEL
 * Description: Title & loading screen
 */

#include "stage.h"

#define DISP_W 512
#define DISP_H 240

typedef struct {
    u32 unk0;
    u32 unk4;
} Unkstruct_801ACBE4;

extern u8 D_8018046C[0x20 * 3];
extern u32 D_801822E4[];
extern Unkstruct_801ACBE4 D_801BAF18[];
extern s32 D_801BAFDC;
extern s32 D_801BAFE0;
extern s32 D_801BAFE4;
extern s32 D_801BAFE8;
extern s32 D_801BC3D8;
extern s32 D_801BC3DC;
extern s32 D_801BC3E0;
extern s32 D_801D6B04;
extern s32 D_801D6B08;
extern s32 D_801D6B0C;
extern s32 D_801D6B20;

extern s32 D_801BAFEC;
extern s32 D_801BAFF0;
extern s32 D_801BC650;
extern s32 D_801BC8C8;
extern s16 D_801BC35A;
extern u16 D_801BC35C;
extern s16 D_801BC35E;
extern s16 D_801BC360;
extern s16 D_801BC362;
extern s16 D_801BC366;
extern s8 D_801BC36A;
extern s8 D_801BC36B;
extern s16 D_801BC390;
extern s16 D_801BC392;
extern s32 D_801BC394;
extern s32 D_801BAFD4;
extern s32 D_801BAFD8;
extern RECT D_801825A4;

void func_801B84F0();

void func_801AC048(void) {
    D_801D6B0C = 1;
    D_801D6B08 = 0;
    D_801BC3E0 = 0;
    D_801D6B04 = 0;
    D_801BC3D8 = 0;
    D_801BC3DC = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AC084);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AC174);

void func_801ACBE4(s32 arg0, u16 arg1) {
    POLY_GT4* poly = &D_80086FEC[D_801BAF18[arg0].unk0];
    while (poly != NULL) {
        poly->pad3 = arg1;
        poly = (POLY_GT4*)poly->tag;
    }
}

void func_801ACC3C(void) {
    s32 i;
    for (i = 0; i < 21; i++) {
        func_801ACBE4(i, 8);
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACC7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACDFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACEC0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACF7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ACFBC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD134);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD1D0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD218);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD260);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD490);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD590);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD66C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD78C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AD968);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ADC3C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801ADF94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AE6D0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AE9A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEA8C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEB74);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AECA0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AED48);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEE74);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801AEED8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B17C8);

void func_801B18CC(s32 arg0) {
    D_8003C734 = arg0;
    D_80073060 = 0;
    g_backbufferX = 0;
    g_backbufferY = 0;
}

void func_801B18F4(void) { ClearImage(&D_801825A4, 0, 0, 0); }

// TODO linker error
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1924);
#else
void func_801B1924(void) {
    D_8003CB08.buf.draw.r0 = 0;
    D_8003CB08.buf.draw.g0 = 0;
    D_8003CB08.buf.draw.b0 = 0;
    D_800542FC.buf.draw.r0 = 0;
    D_800542FC.buf.draw.g0 = 0;
    D_800542FC.buf.draw.b0 = 0;
}
#endif

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B195C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B19F4);

// TODO linker error
#ifndef NON_MATCHING
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1A98);
#else
void func_801B1A98(void) {
    SetDefDrawEnv(&D_8003CB08.buf.draw, 0, 0, DISP_W, DISP_H);
    SetDefDrawEnv(&D_800542FC.buf.draw, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&D_8003CB08.buf.disp, 0, 256, DISP_W, DISP_H);
    SetDefDispEnv(&D_8005435C, 0, 0, DISP_W, DISP_H);
    D_800542FC.buf.draw.clip.y = DISP_W / 2;
    D_800542FC.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.h = DISP_H;
    D_8003CB08.buf.draw.clip.y = 0;
    D_800542FC.buf.draw.isbg = 1;
    D_8003CB08.buf.draw.isbg = 1;
    func_801B1924();
    D_800542FC.buf.disp.isrgb24 = 0;
    D_8003CB08.buf.disp.isrgb24 = 0;
}
#endif

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1B88);

void func_801B1C78(POLY_GT4* poly, u8 colorIntensity, s32 vertexIndex) {
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

void func_801B1CFC(POLY_GT4* poly, u8 colorIntensity) {
    func_801B1C78(poly, colorIntensity, 0);
    func_801B1C78(poly, colorIntensity, 1);
    func_801B1C78(poly, colorIntensity, 2);
    func_801B1C78(poly, colorIntensity, 3);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1D68);

void func_801B1D88(POLY_GT4* arg0) { func_801B1CFC(arg0, 0x80); }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1DA8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1ED0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1EF4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1F34);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1F4C);

void func_801B1FD8(u8* arg0, s32 arg1);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1FD8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2108);

void func_801B248C(s32 arg0, s32 arg1);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B248C);

void func_801B24F8(s32 arg0, s32 arg1);
INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B24F8);

void func_801B2564(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B248C(arg0, arg1);
}

void func_801B259C(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x3C0;
    D_801BAFD8 = 0x100;
    func_801B24F8(arg0, arg1);
}

void func_801B25D4(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B248C(arg0, arg1);
}

void func_801B2608(s32 arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B24F8(arg0, arg1);
}

void func_801B263C(u8* arg0, s32 arg1) {
    D_801BAFD4 = 0x180;
    D_801BAFD8 = 0;
    func_801B1FD8(arg0, arg1);
}

void func_801B2670(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height) {
    poly->x0 = x;
    poly->y0 = y;
    poly->x1 = x + width;
    poly->y1 = y;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y2 = y + height;
    poly->y3 = y + height;
}

void func_801B26A0(POLY_GT4* poly, s32 x, s32 y, s32 width, s32 height, s32 u,
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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2700);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B27A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B28D4);

s32 func_801B2984(u32 arg0) {
    s32 i;
    for (i = 0, arg0 &= 0xFF; i < 0x20; i++) {
        if (D_8018046C[i * 3] == arg0)
            return i;
    }
    return 0x20;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B29C0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2A9C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2AFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2B78);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2BD4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2C70);

void func_801B2CF8(s32* context) {
    s32 i;
    s32 n;

    for (n = 13, i = 0; i < n; i++) {
        *context++ = 0;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2D1C);

void func_801B2D6C(void) {
    func_801B84F0();
    D_801BAFDC = 0;
    D_801BAFE0 = 0;
    D_801BAFE4 = 0;
    D_801BAFE8 = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2DAC);

void func_801B2DDC(void) {}

void func_801B2DE4(void) {}

void func_801B2DEC(void) {}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2DF4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2E5C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2F50);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3120);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3164);

void func_801B367C(s32 arg0) {
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3694);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B38B4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A54);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A94);

void func_801B3E14(s32 arg0) {
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3E2C);

void func_801B3F7C(s32 arg0) {
    D_801BAFEC = 0;
    D_801BAFF0 = arg0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3F94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4048);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B410C);

void func_801B4B30(Entity* entity) {
    s32 i;
    s32 length;
    u32* ptr;

    if (entity->unk34 & 0x800000) {
        g_pfnFreePolygons(entity->firstPolygonIndex);
    }

    ptr = (u32*)entity;
    length = sizeof(Entity) / sizeof(u32);
    for (i = 0; i < length; i++)
        *ptr++ = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4B9C);

s32 AnimateEntity(const u8 frames[], Entity* entity) {
    s32 flag = 0;
    u16 currentFrameIndex = entity->animationFrameIndex * 2;
    u8* currentFrame = frames + currentFrameIndex;

    if (entity->animationFrameDuration == 0) {
        if (currentFrame[0] > 0) {
            flag = 0x80;
            if (currentFrame[0] == 0xFF) {
                return false;
            }

            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
        } else {
            currentFrame = frames;
            entity->animationFrameIndex = 0;
            entity->animationFrameDuration = 0;
            entity->animationFrameDuration = *currentFrame++;
            entity->animationFrame = *currentFrame++;
            entity->animationFrameIndex++;
            return false;
        }
    }

    entity->animationFrameDuration = entity->animationFrameDuration - 1;
    entity->animationFrame = currentFrame[-1];
    flag |= true;

    return (u8)flag;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4C68);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4D78);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4DE0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4FFC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B519C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5350);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B54C8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5548);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B55C8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B585C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B5A7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B60D4);

void func_801B642C(void) {
    D_801BC360 = 2;
    D_801BC35E = 2;
    D_801BC362 = 0;
    D_801BC366 = 0;
    D_801BC36A = 0;
    D_801BC36B = 8;
    D_801BC35A = D_801BC35C + 0x14;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B6480);

void func_801B6648(s16 yOffset) {
    RECT rect;

    rect.y = (yOffset * 12) + 384;
    rect.w = 64;
    rect.x = 0;
    rect.h = 12;
    ClearImage(&rect, 0, 0, 0);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B66A4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B675C);

void func_801B68E0(s32 arg0) {
    D_801BC394 = arg0 + 0x100000;
    D_801BC392 = 0;
    D_801BC390 = 1;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B690C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B69F8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B76F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B786C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B78BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B79D4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B80F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8298);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8338);

void func_801B83BC(void) {
    TestEvent(D_80073068);
    TestEvent(D_8007306C);
    TestEvent(D_80073070);
    TestEvent(D_80073078);
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8414);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8498);

void func_801B84F0(void) { D_801D6B20 = 0; }

void func_801B8500(void) {
    D_801BC650 = 0;
    D_801BC8C8 = 0;
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8518);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8714);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B873C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B881C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B884C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B88F4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B89C8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8A10);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8A8C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8D24);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8DB0);

void func_801B8DE8(u8* arg0, s32 arg1) {
    u8* src = (u8*)D_801822E4[arg1];
    s32 i;
    for (i = 0; i < 0x180; i++) {
        *arg0++ = *src++;
    }
}

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8E20);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B94BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9698);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9744);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B97BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B988C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9924);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B994C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B99E4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9B7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9C18);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B9C80);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA460);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA498);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA524);

u16 func_801BA5C0(u16* arg0) { return *arg0; }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA5CC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA648);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA668);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA688);

void func_801BA6A8(void (*func)()) { DMACallback(0, func); }

void func_801BA6CC(void (*func)()) { DMACallback(1, func); }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA6F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA7EC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA880);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA910);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA9A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAA40);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAB70);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BABA4);
