// SPDX-License-Identifier: AGPL-3.0-or-later
#include <types.h>
#include <libetc.h>

typedef struct {
    u_char iq_y[64];
    u_char iq_c[64];
    short dct[64];
} DECDCTENV; /* size=0x100 */

static s32 mdec_iq[] = {
    0x40000001, 0x13101002, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B,
    0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222,
    0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A, 0x13101002,
    0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B,
    0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623,
    0x30302828, 0x38382E2E, 0x5345453A};

static s32 mdec_coef[] = {
    0x60000000, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x5A825A82, 0x6A6D7D8A,
    0x18F8471C, 0xB8E3E707, 0x82759592, 0x30FB7641, 0x89BECF04, 0xCF0489BE,
    0x764130FB, 0xE7076A6D, 0xB8E38275, 0x7D8A471C, 0x959218F8, 0xA57D5A82,
    0x5A82A57D, 0xA57D5A82, 0x5A82A57D, 0x8275471C, 0x6A6D18F8, 0xE7079592,
    0xB8E37D8A, 0x89BE30FB, 0xCF047641, 0x7641CF04, 0x30FB89BE, 0xB8E318F8,
    0x82756A6D, 0x95927D8A, 0xE707471C};

void DecDCTReset(s32 option) {
    if (option == 0) {
        ResetCallback();
    }

    MDEC_reset(option);
}

s32* DecDCTGetEnv(DECDCTENV* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;
    s32 *src3, *dst3;

    dst1 = &arg0->iq_y;
    src1 = &mdec_iq[1];
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = &arg0->iq_c;
    src2 = &mdec_iq[17];
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    dst3 = &arg0->dct;
    src3 = &mdec_coef[1];
    for (i = 31; i != -1; i--) {
        *dst3++ = *src3++;
    }

    return arg0;
}

s32* DecDCTPutEnv(DECDCTENV* arg0) {
    s32 i;
    s32 *src1, *dst1;
    s32 *src2, *dst2;

    dst1 = &mdec_iq[1];
    src1 = &arg0->iq_y;
    for (i = 15; i != -1; i--) {
        *dst1++ = *src1++;
    }

    dst2 = &mdec_iq[17];
    src2 = &arg0->iq_c;
    for (i = 15; i != -1; i--) {
        *dst2++ = *src2++;
    }

    MDEC_in(&mdec_iq, 0x20);
    MDEC_in(&mdec_coef, 0x20);

    return arg0;
}

u16 DecDCTBufSize(u16* arg0) { return *arg0; }

void DecDCTin(s32* arg0, s32 arg1) {
    s32 new_var2;
    s32 var_v0;
    s32 var_v0_2;

    if (arg1 & 1) {
        var_v0 = (*arg0) & 0xF7FFFFFF;
    } else {
        new_var2 = 0x08000000;
        var_v0 = 0x08000000;
        var_v0 = (*arg0) | var_v0;
    }

    *arg0 = var_v0;
    var_v0 = 0x02000000;
    if (arg1 & 2) {
        new_var2 = var_v0;
        var_v0_2 = (*arg0) | new_var2;
    } else {
        var_v0_2 = (*arg0) & 0xFDFFFFFF;
    }

    *arg0 = var_v0_2;
    MDEC_in(arg0, *(u16*)arg0);
}

void DecDCTout(s32 arg0, u32 arg1) { MDEC_out(arg0, arg1); }

void DecDCTinSync(void) { MDEC_in_sync(); }

void DecDCToutSync(void) { MDEC_out_sync(); }

void DecDCTinCallback(void (*func)()) { DMACallback(0, func); }

void DecDCToutCallback(void (*func)()) { DMACallback(1, func); }

static volatile u32* d0_madr = 0x1F801080;
static volatile u32* d0_bcr = 0x1F801084;
static volatile u32* d0_chcr = 0x1F801088;
static volatile u32* d1_madr = 0x1F801090;
static volatile u32* d1_bcr = 0x1F801094;
static volatile u32* d1_chcr = 0x1F801098;

static volatile u32* d2_madr = 0x1F8010A0;
static volatile u32* d2_bcr = 0x1F8010A4;
static volatile u32* b2_chcr = 0x1F8010A8;
static volatile u32* d3_madr = 0x1F8010B0;
static volatile u32* d3_bcr = 0x1F8010B4;
static volatile u32* d3_chcr = 0x1F8010B8;
static volatile u32* mdec0 = 0x1F801820;
static volatile u32* mdec1 = 0x1F801824;
static volatile u32* d_pcr = 0x1F8010F0;

static void MDEC_reset(s32 option) {
    switch (option) {
    case 0:
        *mdec1 = 0x80000000;
        *d0_chcr = 0;
        *d1_chcr = 0;
        *mdec1 = 0x60000000;
        MDEC_in(&mdec_iq, 0x20);
        MDEC_in(&mdec_coef, 0x20);
        return;
    case 1:
        *mdec1 = 0x80000000;
        *d0_chcr = 0;
        *d1_chcr = 0;
        *d1_chcr;
        *mdec1 = 0x60000000;
        return;
    default:
        printf("MDEC_rest:bad option(%d)\n", option);
        return;
    }
}

static void MDEC_in(s32* arg0, u32 arg1) {
    MDEC_in_sync();
    *d_pcr |= 0x88;
    *d0_madr = arg0 + 1;
    *d0_bcr = ((arg1 >> 5) << 0x10) | 0x20;
    *mdec0 = *arg0;
    *d0_chcr = 0x01000201;
}

static void MDEC_out(s32 arg0, u32 arg1) {
    MDEC_out_sync();
    *d_pcr |= 0x88;
    *d1_chcr = 0;
    *d1_madr = arg0;
    *d1_bcr = ((arg1 >> 5) << 0x10) | 0x20;
    *d1_chcr = 0x01000200;
}

static int MDEC_in_sync(void) {
    volatile s32 retries = 0x100000;

    if (*mdec1 & 0x20000000) {
        while (true) {
            if (--retries == -1) {
                timeout("MDEC_in_sync");
                return -1;
            }
            if (!(*mdec1 & 0x20000000)) {
                break;
            }
        }
    }

    return 0;
}

static int MDEC_out_sync(void) {
    volatile s32 retries = 0x100000;

    while (*d1_chcr & 0x01000000) {
        if (--retries == -1) {
            timeout("MDEC_out_sync");
            return -1;
        }
    }

    return 0;
}

int timeout(const char* funcName) {
    const char* errDma = "\t DMA=(%d,%d), ADDR=(0x%08x->0x%08x)\n";
    const char* errFifo =
        "\t FIFO=(%d,%d),BUSY=%d,DREQ=(%d,%d),RGB24=%d,STP=%d\n";
    u32 temp_s0;

    printf("%s timeout:\n", funcName);
    temp_s0 = *mdec1;

    printf(errDma, (*d0_chcr >> 0x18) & 1, (*d1_chcr >> 0x18) & 1, *d0_madr,
           *d1_madr);

    printf(errFifo, ~temp_s0 >> 0x1F, (temp_s0 >> 0x1E) & 1,
           (temp_s0 >> 0x1D) & 1, (temp_s0 >> 0x1C) & 1, (temp_s0 >> 0x1B) & 1,
           (temp_s0 >> 0x19) & 1, (temp_s0 >> 0x17) & 1);

    *mdec1 = 0x80000000;
    *d0_chcr = 0;
    *d1_chcr = 0;
    *d1_chcr;
    *mdec1 = 0x60000000;

    return 0;
}
