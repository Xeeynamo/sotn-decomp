#include "stage.h"

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B18F4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1924);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B195C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B19F4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1A98);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1D88);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1DA8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1ED0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1EF4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1F34);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1F4C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B1FD8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2108);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B248C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B24F8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2564);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B259C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B25D4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2608);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B263C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2670);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B26A0);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B2CF8);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B367C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3694);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B38B4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A54);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3A94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3E14);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3E2C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3F7C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B3F94);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4048);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B410C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4B30);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4B9C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B4BB0);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B642C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B6480);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B6648);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B66A4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B675C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B68E0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B690C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B69F8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B76F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B786C);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B78BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B79D4);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B80F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8298);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8338);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B83BC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8414);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8498);

void func_801B84F0(void) { D_801D6B20 = 0; }

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801B8500);

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

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA6A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA6CC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA6F0);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA7EC);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA880);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA910);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BA9A8);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAA40);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BAB70);

INCLUDE_ASM("config/../asm/st/sel/nonmatchings/2C048", func_801BABA4);
