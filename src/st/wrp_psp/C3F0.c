#include "common.h"
#include "game.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_8018C1E0);

void SetStep(u8 step) {
    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->animFrameIdx = 0;
    g_CurrentEntity->animFrameDuration = 0;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", InitializeEntity);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", EntityDummy);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_8018C55C);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", ReplaceBreakableWithItemDrop);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_psp_09244020);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", PrimResetNext);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", UnkPolyFunc2);
