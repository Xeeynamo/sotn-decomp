#ifndef DMA_H
#define DMA_H

#define DMA_POKE_B(adr, data) (*((volatile Uint8*)(adr))) = (Uint8)(data)
#define DMA_POKE_L(adr, data) (*((volatile Uint32*)(adr))) = (Uint32)(data)
#define DMA_PEEK_L(adr) (*(volatile Uint32*)(adr))

#define DMA_CHCR_DE 0
#define DMA_CHCR_TE 1
#define DMA_CHCR_IE 2
#define DMA_CHCR_TA 3
#define DMA_CHCR_TB 4
#define DMA_CHCR_DL 5
#define DMA_CHCR_DS 6
#define DMA_CHCR_AL 7
#define DMA_CHCR_AM 8
#define DMA_CHCR_AR 9
#define DMA_CHCR_TS 10
#define DMA_CHCR_SM 12
#define DMA_CHCR_DM 14

#define DMA_CPU_M_PR (1 << 0)
#define DMA_CPU_M_AE (1 << 1)
#define DMA_CPU_M_NMIF (1 << 2)
#define DMA_CPU_M_DME (1 << 3)

#define DMA_DMAOR_DME 0
#define DMA_DMAOR_NMIF 1
#define DMA_DMAOR_AE 2
#define DMA_DMAOR_PR 3

#define DMA_CPU_RXI 0x1
#define DMA_CPU_TXI 0x2

#define DMA_CPU_M_SAR (1 << 0)
#define DMA_CPU_M_DAR (1 << 1)
#define DMA_CPU_M_TCR (1 << 2)
#define DMA_CPU_M_DM (1 << 3)
#define DMA_CPU_M_SM (1 << 4)
#define DMA_CPU_M_TS (1 << 5)
#define DMA_CPU_M_AR (1 << 6)
#define DMA_CPU_M_IE (1 << 7)
#define DMA_CPU_M_DRCR (1 << 8)
#define DMA_CPU_M_TE (1 << 9)

typedef struct {
    Uint32 pr;
    Uint32 dme;
    Uint32 msk;
} DmaCpuComPrm;

typedef struct {
    Uint32 sar;
    Uint32 dar;
    Uint32 tcr;
    Uint32 dm;
    Uint32 sm;
    Uint32 ts;
    Uint32 ar;
    Uint32 ie;
    Uint32 drcr;
    Uint32 msk;
} DmaCpuPrm;

typedef struct {
    Uint32 ae;
    Uint32 nmif;
} DmaCpuComStatus;

typedef Uint32 DmaCpuStatus;

#define DMA_SCU_CH0 0x0
#define DMA_SCU_CH1 0x1
#define DMA_SCU_CH2 0x2

#define DMA_DXAD_DXRAD 8
#define DMA_DXAD_DXWAD 0

#define DMA_DXEN_DXGO 0
#define DMA_DXEN_DXEN 8

#define DMA_DXMD_DXMOD 24
#define DMA_DXMD_DXRUP 16
#define DMA_DXMD_DXWUP 8
#define DMA_DXMD_DXFT 0

#define DMA_SCU_R0 (0x0 << DMA_DXAD_DXRAD)
#define DMA_SCU_R4 (0x1 << DMA_DXAD_DXRAD)

#define DMA_SCU_W0 (0x0 << DMA_DXAD_DXWAD)
#define DMA_SCU_W2 (0x1 << DMA_DXAD_DXWAD)
#define DMA_SCU_W4 (0x2 << DMA_DXAD_DXWAD)
#define DMA_SCU_W8 (0x3 << DMA_DXAD_DXWAD)
#define DMA_SCU_W16 (0x4 << DMA_DXAD_DXWAD)
#define DMA_SCU_W32 (0x5 << DMA_DXAD_DXWAD)
#define DMA_SCU_W64 (0x6 << DMA_DXAD_DXWAD)
#define DMA_SCU_W128 (0x7 << DMA_DXAD_DXWAD)

#define DMA_SCU_DIR (0x0 << DMA_DXMD_DXMOD)
#define DMA_SCU_IN_DIR (0x1 << DMA_DXMD_DXMOD)

#define DMA_SCU_KEEP 0x0
#define DMA_SCU_REN 0x1

#define DMA_SCU_F_VBLK_IN (0x0 << DMA_DXMD_DXFT)
#define DMA_SCU_F_VBLK_OUT (0x1 << DMA_DXMD_DXFT)
#define DMA_SCU_F_HBLK_IN (0x2 << DMA_DXMD_DXFT)
#define DMA_SCU_F_TIM0 (0x3 << DMA_DXMD_DXFT)
#define DMA_SCU_F_TIM1 (0x4 << DMA_DXMD_DXFT)
#define DMA_SCU_F_SND (0x5 << DMA_DXMD_DXFT)
#define DMA_SCU_F_SPR (0x6 << DMA_DXMD_DXFT)
#define DMA_SCU_F_DMA (0x7 << DMA_DXMD_DXFT)

#define DMA_SCU_M_DXR (1 << 0)
#define DMA_SCU_M_DXW (1 << 1)

#define DMA_SCU_MV 0x1
#define DMA_SCU_NO_MV 0x0

typedef struct {
    Uint32 dxr;
    Uint32 dxw;
    Uint32 dxc;
    Uint32 dxad_r;
    Uint32 dxad_w;
    Uint32 dxmod;
    Uint32 dxrup;
    Uint32 dxwup;
    Uint32 dxft;
    Uint32 msk;
} DmaScuPrm;

typedef struct {
    Uint32 dxmv;
} DmaScuStatus;

#define DMA_SCU_END 0
#define DMA_SCU_FAIL 1
#define DMA_SCU_BUSY 2

#endif
