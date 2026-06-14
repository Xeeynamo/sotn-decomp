#include "sattypes.h"
#include "inc_asm.h"

// SEGA_DMA.A
#include "../xpt.h"
#include "dma.h"
#include "../int.h"

#define CADR_B_BUS_START ((Uint32)0x5A00000)
#define CADR_B_BUS_END ((Uint32)0x5FE0000)
#define ADR_B_BUS_START ((Uint32)0x25A00000)
#define ADR_B_BUS_END ((Uint32)0x25FE0000)

#define CADR_WORKRAM_L_START ((volatile void*)0x200000)
#define CADR_WORKRAM_L_END ((volatile void*)0x300000)
#define ADR_WORKRAM_L_START ((volatile void*)0x20200000)
#define ADR_WORKRAM_L_END ((volatile void*)0x20300000)

extern void* dma_scu_dis_adr;
extern Uint32 dma_scu_cnt;
extern Uint8 dma_flg;
extern Uint8 dma_start_flg;

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

void DMA_ScuInit(void) {
    Uint32 msk;

    msk = get_imask();
    set_imask(15);
    INT_ChgMsk(INT_MSK_DMA0, INT_MSK_NULL);
    dma_start_flg = 0;
    set_imask(msk);
}

void DMA_ScuMemCopy(void* dst, void* src, Uint32 cnt) {
    DmaScuPrm prm;
    Uint32 msk;

    msk = get_imask();
    set_imask(15);
    if (((dst >= ADR_WORKRAM_L_START) && (dst < ADR_WORKRAM_L_END)) ||
        ((dst >= CADR_WORKRAM_L_START) && (dst < CADR_WORKRAM_L_END)) ||
        ((src >= ADR_WORKRAM_L_START) && (src < ADR_WORKRAM_L_END)) ||
        ((src >= CADR_WORKRAM_L_START) && (src < CADR_WORKRAM_L_END))) {
        dma_flg = 0;
        memcpy(dst, src, cnt);
    } else {
        dma_flg = 1;

        dma_scu_dis_adr = dst;
        dma_scu_cnt = (Uint32)cnt;

        prm.dxr = (Uint32)src;
        prm.dxw = (Uint32)dst;
        prm.dxc = cnt;
        prm.dxad_r = DMA_SCU_R4;

        if (((prm.dxw >= ADR_B_BUS_START) & (prm.dxw < ADR_B_BUS_END)) ||
            ((prm.dxw >= CADR_B_BUS_START) & (prm.dxw < CADR_B_BUS_END))) {
            prm.dxad_w = DMA_SCU_W2;
        } else {
            prm.dxad_w = DMA_SCU_W4;
        }

        prm.dxmod = DMA_SCU_DIR;
        prm.dxrup = DMA_SCU_KEEP;
        prm.dxwup = DMA_SCU_KEEP;
        prm.dxft = DMA_SCU_F_DMA;
        prm.msk = DMA_SCU_M_DXR | DMA_SCU_M_DXW;

        DMA_ScuSetPrm(&prm, DMA_SCU_CH0);
        DMA_ScuStart(DMA_SCU_CH0);
    }
    dma_start_flg = 1;
    set_imask(msk);
}

Uint32 DMA_ScuResult(void) {
    DmaScuStatus status;
    Uint32 msk;

    msk = get_imask();
    set_imask(15);

    if (dma_start_flg == 1) {
        if (dma_flg == 0) {
            set_imask(msk);
            return DMA_SCU_END;
        } else {
            DMA_ScuGetStatus(&status, 0);
            if (status.dxmv == 1) {
                set_imask(msk);
                return DMA_SCU_BUSY;
            }
            CSH_Purge(dma_scu_dis_adr, dma_scu_cnt);
            set_imask(msk);
            return DMA_SCU_END;
        }
    } else {
        set_imask(msk);
        return DMA_SCU_END;
    }
}
