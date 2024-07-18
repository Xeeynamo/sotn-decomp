#include "wrp.h"

#if defined(VERSION_US)
#include "../e_stage_name.h"

#elif defined(VERSION_HD)
INCLUDE_ASM("st/wrp/nonmatchings/e_stage_name", func_801916C4);

INCLUDE_ASM("st/wrp/nonmatchings/e_stage_name", EntityStageNamePopup);

#endif
