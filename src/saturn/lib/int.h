#ifndef INT_H
#define INT_H

#include "xpt.h"
#include "sys.h"

#define INT_MSK_NULL 0
#define INT_MSK_DMA0 (1 << 11)

#define INT_ChgMsk(ena_msk_bit, dis_msk_bit)                                   \
    SYS_CHGSCUIM(~(ena_msk_bit), dis_msk_bit)

#endif
