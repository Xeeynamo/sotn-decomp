#include "sattypes.h"
#include "inc_asm.h"

// SEGA_DMA.A
#include "../xpt.h"
#include "../sys.h"
#include "dma.h"

#define REG_DXR ((volatile Uint32*)0x25FE0000)
#define REG_DXW ((volatile Uint32*)0x25FE0004)
#define REG_DXC ((volatile Uint32*)0x25FE0008)
#define REG_DXAD ((volatile Uint32*)0x25FE000C)
#define REG_DXEN ((volatile Uint32*)0x25FE0010)
#define REG_DXMD ((volatile Uint32*)0x25FE0014)

#define OFSET0_REG 0x00000008

#define R_DXEN_DXGO (1 << DMA_DXEN_DXGO)
#define R_DXEN_DXEN (1 << DMA_DXEN_DXEN)

#define STOP_COM(ch, vector_num)                                               \
    do {                                                                       \
        SYS_SETUINT_NO_MACSAVE((vector_num), dma_scu_vector[(ch)]);            \
        SYS_SETSINT((vector_num), dma_vector[(ch)]);                           \
        dma_int_status[(ch)] = DMA_SCU_NO_MV;                                  \
    } while (0)

#define INTR_FUNC(ch, vector_num)                                              \
    do {                                                                       \
        Uint32 msk;                                                            \
        msk = get_imask();                                                     \
        set_imask(15);                                                         \
        dma_int_status[(ch)] = DMA_SCU_NO_MV;                                  \
        STOP_COM((ch), (vector_num));                                          \
        set_imask(msk);                                                        \
    } while (0)

extern void (*dma_scu_vector[3])(void);
extern void (*dma_vector[3])(void);
extern Uint8 dma_int_status[3];

void DMA_ScuIntFunc0(void);
void DMA_ScuIntFunc1(void);
void DMA_ScuIntFunc2(void);

static inline void set_sr(register Uint32 sr) {
    __asm__ volatile("ldc	%0, sr" : : "r"(sr));
}

static inline Uint32 get_sr(void) {
    Uint32 sr;
    __asm__ volatile("stc	sr, %0" : "=r"(sr));
    return sr;
}

static inline Uint32 get_imask(void) {
    Uint32 imask = (get_sr() & 0x000000F0) >> 4;
    return imask;
}

static inline void set_imask(register Uint32 imask) {
    Uint32 sr = get_sr();

    sr &= ~0x000000F0;
    sr |= imask << 4;
    set_sr(sr);
}

void DMA_ScuSetPrm(DmaScuPrm* prm, Uint32 ch) {
    if ((prm->msk & DMA_SCU_M_DXR) == DMA_SCU_M_DXR) {
        DMA_POKE_L((REG_DXR + OFSET0_REG * ch), prm->dxr);
    }

    if ((prm->msk & DMA_SCU_M_DXW) == DMA_SCU_M_DXW) {
        DMA_POKE_L((REG_DXW + OFSET0_REG * ch), prm->dxw);
    }

    DMA_POKE_L((REG_DXC + OFSET0_REG * ch), prm->dxc);

    DMA_POKE_L((REG_DXAD + OFSET0_REG * ch), (prm->dxad_r | prm->dxad_w));
    DMA_POKE_L((REG_DXMD + OFSET0_REG * ch),
               (prm->dxmod | (prm->dxrup << DMA_DXMD_DXRUP) |
                (prm->dxwup << DMA_DXMD_DXWUP) | prm->dxft));
}

void DMA_ScuStart(Uint32 ch) {
    Uint32 msk;
    Uint32 now_vector_num;
    void (*intr_func)(void);

    msk = get_imask();
    set_imask(15);
    switch (ch) {
    case 0:
        now_vector_num = 0x4B;
        intr_func = DMA_ScuIntFunc0;
        break;
    case 1:
        now_vector_num = 0x4A;
        intr_func = DMA_ScuIntFunc1;
        break;
    case 2:
        now_vector_num = 0x49;
        intr_func = DMA_ScuIntFunc2;
        break;
    }
    dma_scu_vector[ch] = SYS_GETUINT_NO_MACSAVE(now_vector_num);
    dma_vector[ch] = SYS_GETSINT(now_vector_num);
    dma_int_status[ch] = DMA_SCU_MV;
    SYS_SETUINT_NO_MACSAVE(now_vector_num, intr_func);
    SYS_SETSINT(now_vector_num, 0);
    DMA_POKE_L((REG_DXEN + OFSET0_REG * ch), (R_DXEN_DXGO | R_DXEN_DXEN));
    set_imask(msk);
}

void DMA_ScuGetStatus(DmaScuStatus* status, Uint32 ch) {
    Uint32 msk;
    msk = get_imask();
    set_imask(15);

    status->dxmv = (Uint32)dma_int_status[ch];

    set_imask(msk);
}

void DMA_ScuIntFunc0(void) {
    Uint32 DMA_Scu0_Mac[2];

    SYS_GetMac(DMA_Scu0_Mac);
    INTR_FUNC(DMA_SCU_CH0, 0x4B);
    SYS_SetMac(DMA_Scu0_Mac);
}

void DMA_ScuIntFunc1(void) {
    Uint32 DMA_Scu1_Mac[2];

    SYS_GetMac(DMA_Scu1_Mac);
    INTR_FUNC(DMA_SCU_CH1, 0x4A);
    SYS_SetMac(DMA_Scu1_Mac);
}

void DMA_ScuIntFunc2(void) {
    Uint32 DMA_Scu2_Mac[2];

    SYS_GetMac(DMA_Scu2_Mac);
    INTR_FUNC(DMA_SCU_CH2, 0x49);
    SYS_SetMac(DMA_Scu2_Mac);
}
