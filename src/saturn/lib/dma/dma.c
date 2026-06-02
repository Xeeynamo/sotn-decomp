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

extern void (*dma_scu_vector[3])(void);
extern void (*dma_vector[3])(void);
extern Uint8 dma_int_status[3];

void DMA_ScuIntFunc0(void);
void DMA_ScuIntFunc1(void);
void DMA_ScuIntFunc2(void);

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

// _DMA_ScuIntFunc0
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023AB0, func_06023AB0);

// _DMA_ScuIntFunc1
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6023B54, func_06023B54);

// _DMA_ScuIntFunc2 - splitter bug
INCLUDE_ASM("asm/saturn/zero/data", d6023C00, d_06023C00);

#define REG_SAR ((volatile Uint32*)0xFFFFFF80)
#define REG_DAR ((volatile Uint32*)0xFFFFFF84)
#define REG_TCR ((volatile Uint32*)0xFFFFFF88)
#define REG_CHCR ((volatile Uint32*)0xFFFFFF8C)
#define REG_DRCR ((volatile Uint8*)0xFFFFFE71)

#define OFSET0_REG 0x00000004
#define OFSET1_REG 0x00000001

#define REG_DMAOR ((Uint32*)0xFFFFFFB0)

#define R_CHCR_DE (1 << DMA_CHCR_DE)
#define R_CHCR_TE (1 << DMA_CHCR_TE)
#define R_CHCR_IE (1 << DMA_CHCR_IE)
#define R_CHCR_TA (1 << DMA_CHCR_TA)
#define R_CHCR_TB (1 << DMA_CHCR_TB)
#define R_CHCR_DL (1 << DMA_CHCR_DL)
#define R_CHCR_DS (1 << DMA_CHCR_DS)
#define R_CHCR_AL (1 << DMA_CHCR_AL)
#define R_CHCR_AM (1 << DMA_CHCR_AM)
#define R_CHCR_AR (1 << DMA_CHCR_AR)
#define R_CHCR_TS (3 << DMA_CHCR_TS)
#define R_CHCR_SM (3 << DMA_CHCR_SM)
#define R_CHCR_DM (3 << DMA_CHCR_DM)
#define R_DMAOR_DME (1 << DMA_DMAOR_DME)
#define R_DMAOR_NMIF (1 << DMA_DMAOR_NMIF)
#define R_DMAOR_AE (1 << DMA_DMAOR_AE)
#define R_DMAOR_PR (1 << DMA_DMAOR_PR)

void DMA_CpuSetComPrm(DmaCpuComPrm* com_prm) {
    Uint32 work_reg;
    work_reg = DMA_PEEK_L(REG_DMAOR);

    if ((com_prm->msk & DMA_CPU_M_PR) == DMA_CPU_M_PR) {
        work_reg &= ~R_DMAOR_PR;
        work_reg |= com_prm->pr;
    }
    if ((com_prm->msk & DMA_CPU_M_DME) == DMA_CPU_M_DME) {
        work_reg &= ~R_DMAOR_DME;
        work_reg |= com_prm->dme;
    }
    if ((com_prm->msk & DMA_CPU_M_AE) == DMA_CPU_M_AE) {
        work_reg &= ~R_DMAOR_AE;
    }
    if ((com_prm->msk & DMA_CPU_M_NMIF) == DMA_CPU_M_NMIF) {
        work_reg &= ~R_DMAOR_NMIF;
    }
    DMA_POKE_L(REG_DMAOR, work_reg);
}

void DMA_CpuSetPrm(DmaCpuPrm* prm, Uint32 ch) {
    Uint32 work_reg;

    if ((prm->msk & DMA_CPU_M_SAR) == DMA_CPU_M_SAR) {
        DMA_POKE_L((REG_SAR + OFSET0_REG * ch), prm->sar);
    }
    if ((prm->msk & DMA_CPU_M_DAR) == DMA_CPU_M_DAR) {
        DMA_POKE_L((REG_DAR + OFSET0_REG * ch), prm->dar);
    }
    if ((prm->msk & DMA_CPU_M_TCR) == DMA_CPU_M_TCR) {
        DMA_POKE_L((REG_TCR + OFSET0_REG * ch), prm->tcr);
    }
    work_reg = DMA_PEEK_L(REG_CHCR + OFSET0_REG * ch);

    if ((prm->msk & DMA_CPU_M_DM) == DMA_CPU_M_DM) {
        work_reg &= ~R_CHCR_DM;
        work_reg |= prm->dm << DMA_CHCR_DM;
    }
    if ((prm->msk & DMA_CPU_M_SM) == DMA_CPU_M_SM) {
        work_reg &= ~R_CHCR_SM;
        work_reg |= prm->sm << DMA_CHCR_SM;
    }
    if ((prm->msk & DMA_CPU_M_TS) == DMA_CPU_M_TS) {
        work_reg &= ~R_CHCR_TS;
        work_reg |= prm->ts;
    }
    if ((prm->msk & DMA_CPU_M_AR) == DMA_CPU_M_AR) {
        work_reg &= ~R_CHCR_AR;
        work_reg |= prm->ar;
    }

    work_reg &= ~R_CHCR_TB;
    work_reg &= ~R_CHCR_TA;

    if ((prm->msk & DMA_CPU_M_IE) == DMA_CPU_M_IE) {
        work_reg &= ~R_CHCR_IE;
        work_reg |= prm->ie;
    }
    if ((prm->msk & DMA_CPU_M_TE) == DMA_CPU_M_TE) {
        work_reg &= ~R_CHCR_TE;
    }

    DMA_POKE_L((REG_CHCR + OFSET0_REG * ch), work_reg);

    if ((prm->msk & DMA_CPU_M_DRCR) == DMA_CPU_M_DRCR) {
        if ((prm->drcr == DMA_CPU_RXI) || (prm->drcr == DMA_CPU_TXI)) {
            DMA_POKE_B((REG_DRCR + OFSET1_REG * ch), prm->drcr);
        }
    }
}

void DMA_CpuStart(Uint32 ch) {
    Uint32 work_reg;

    work_reg = DMA_PEEK_L(REG_CHCR + OFSET0_REG * ch);
    work_reg |= R_CHCR_DE;
    DMA_POKE_L((REG_CHCR + OFSET0_REG * ch), work_reg);
}

void DMA_CpuStop(Uint32 ch) {
    Uint32 work_reg;

    work_reg = DMA_PEEK_L(REG_CHCR + OFSET0_REG * ch);
    work_reg &= ~R_CHCR_DE;
    DMA_POKE_L((REG_CHCR + OFSET0_REG * ch), work_reg);
}

void DMA_CpuAllStop(void) {
    Uint32 work_reg;
    work_reg = DMA_PEEK_L(REG_DMAOR);
    work_reg &= ~R_DMAOR_DME;
    DMA_POKE_L(REG_DMAOR, work_reg);
}

void DMA_CpuGetComStatus(DmaCpuComStatus* status) {
    Uint32 work_reg;

    work_reg = DMA_PEEK_L(REG_DMAOR);
    status->ae = work_reg & R_DMAOR_AE;
    status->nmif = work_reg & R_DMAOR_NMIF;
}

DmaCpuStatus DMA_CpuGetStatus(Uint32 ch) {
    Uint32 work_reg;

    work_reg = DMA_PEEK_L(REG_CHCR + OFSET0_REG * ch);
    return work_reg & R_CHCR_TE;
}

INCLUDE_ASM("asm/saturn/zero/data", d6024088, d_6024088);
