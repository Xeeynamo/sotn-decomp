#include "../wrp/wrp.h"

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/prim_helpers", PrimResetNext);

void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}

INCLUDE_ASM("st/wrp_psp/psp/wrp_psp/prim_helpers", PrimDecreaseBrightness);
