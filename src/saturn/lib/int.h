#ifndef INT_H
#define INT_H

#include "xpt.h"
#include "sys.h"

#define INT_MSK_NULL 0
#define INT_MSK_ALL                                                            \
    (INT_MSK_ABUS | INT_MSK_SPR | INT_MSK_DMAI | INT_MSK_DMA0 | INT_MSK_DMA1 | \
     INT_MSK_DMA2 | INT_MSK_PAD | INT_MSK_SYS | INT_MSK_SND | INT_MSK_DSP |    \
     INT_MSK_TIM1 | INT_MSK_TIM0 | INT_MSK_HBLK_IN | INT_MSK_VBLK_OUT |        \
     INT_MSK_VBLK_IN)
#define INT_MSK_ABUS (1 << 15)
#define INT_MSK_SPR (1 << 13)
#define INT_MSK_DMAI (1 << 12)
#define INT_MSK_DMA0 (1 << 11)
#define INT_MSK_DMA1 (1 << 10)
#define INT_MSK_DMA2 (1 << 9)
#define INT_MSK_PAD (1 << 8)
#define INT_MSK_SYS (1 << 7)
#define INT_MSK_SND (1 << 6)
#define INT_MSK_DSP (1 << 5)
#define INT_MSK_TIM1 (1 << 4)
#define INT_MSK_TIM0 (1 << 3)
#define INT_MSK_HBLK_IN (1 << 2)
#define INT_MSK_VBLK_OUT (1 << 1)
#define INT_MSK_VBLK_IN (1 << 0)

#define INT_SCU_VBLK_IN 0x40
#define INT_SCU_VBLK_OUT 0x41
#define INT_SCU_HBLK_IN 0x42
#define INT_SCU_TIM0 0x43
#define INT_SCU_TIM1 0x44
#define INT_SCU_DSP 0x45
#define INT_SCU_SND 0x46
#define INT_SCU_SYS 0x47
#define INT_SCU_PAD 0x48
#define INT_SCU_DMA2 0x49
#define INT_SCU_DMA1 0x4a
#define INT_SCU_DMA0 0x4b
#define INT_SCU_DMAI 0x4c
#define INT_SCU_SPR 0x4d
#define INT_SCU_ABUS00 0x50
#define INT_SCU_ABUS01 0x51
#define INT_SCU_ABUS02 0x52
#define INT_SCU_ABUS03 0x53
#define INT_SCU_ABUS04 0x54
#define INT_SCU_ABUS05 0x55
#define INT_SCU_ABUS06 0x56
#define INT_SCU_ABUS07 0x57
#define INT_SCU_ABUS08 0x58
#define INT_SCU_ABUS09 0x59
#define INT_SCU_ABUS10 0x5A
#define INT_SCU_ABUS11 0x5B
#define INT_SCU_ABUS12 0x5C
#define INT_SCU_ABUS13 0x5D
#define INT_SCU_ABUS14 0x5E
#define INT_SCU_ABUS15 0x5F

#define INT_ChgMsk(ena_msk_bit, dis_msk_bit)                                   \
    SYS_CHGSCUIM(~(ena_msk_bit), dis_msk_bit)

#endif
