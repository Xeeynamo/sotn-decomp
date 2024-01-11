#include "common.h"

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_vb", startIntrVSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_vb", trapIntrVSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_vb", setIntrVSync);

INCLUDE_ASM("main/nonmatchings/psxsdk/libetc/intr_vb", VSync_memclr);
