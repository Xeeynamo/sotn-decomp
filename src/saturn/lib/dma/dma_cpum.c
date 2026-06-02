#include "sattypes.h"
#include "inc_asm.h"

// SEGA_DMA.A
#include "../xpt.h"
#include "dma.h"
#include "../int.h"

extern void* dma_cpu_dis_adr;
extern Uint32 dma_cpu_cnt;

void DMA_CpuMemCopy(void* dst, void* src, Uint32 cnt) {
    DmaCpuComPrm com_prm;
    DmaCpuPrm prm;
    DMA_CpuStop(DMA_CPU_CH0);

    com_prm.pr = DMA_CPU_FIX;
    com_prm.dme = DMA_CPU_ENA;
    com_prm.msk = DMA_CPU_M_PR | DMA_CPU_M_AE | DMA_CPU_M_NMIF | DMA_CPU_M_DME;

    DMA_CpuSetComPrm(&com_prm);

    prm.sar = (Uint32)src;
    prm.dar = (Uint32)dst;
    prm.tcr = cnt;
    prm.dm = DMA_CPU_AM_ADD;
    prm.sm = DMA_CPU_AM_ADD;
    prm.ts = DMA_CPU_2;
    prm.ar = DMA_CPU_AUTO;
    prm.ie = DMA_CPU_INT_DIS;

    prm.msk = DMA_CPU_M_SAR | DMA_CPU_M_DAR | DMA_CPU_M_TCR | DMA_CPU_M_DM |
              DMA_CPU_M_SM | DMA_CPU_M_TS | DMA_CPU_M_AR | DMA_CPU_M_IE |
              DMA_CPU_M_TE;

    DMA_CpuSetPrm(&prm, DMA_CPU_CH0);

    DMA_CpuStart(DMA_CPU_CH0);
    dma_cpu_dis_adr = dst;
    dma_cpu_cnt = cnt * 2;
}

Uint32 DMA_CpuResult(void) {
    DmaCpuComStatus com_status;
    DmaCpuStatus status;

    DMA_CpuGetComStatus(&com_status);
    if (com_status.ae == DMA_CPU_ADR_ERR) {
        return DMA_CPU_FAIL;
    }
    status = DMA_CpuGetStatus(DMA_CPU_CH0);
    if (status == DMA_CPU_TE_MV) {
        return DMA_CPU_BUSY;
    }
    CSH_Purge(dma_cpu_dis_adr, dma_cpu_cnt);
    return DMA_CPU_END;
}
