#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", startIntrDMA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", trapIntrDMA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", setIntrDMA);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_dma", DMA_memclr);
