#include "common.h"
#include "game.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_8018C1E0);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", SetStep);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", InitializeEntity);

void EntityDummy(Entity* arg0) {
    if (!arg0->step) {
        arg0->step++;
    }
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_8018C55C);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", ReplaceBreakableWithItemDrop);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", func_psp_09244020);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", PrimResetNext);

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/C3F0", UnkPolyFunc2);
