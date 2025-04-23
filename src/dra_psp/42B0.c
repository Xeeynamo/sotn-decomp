// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"
#include "../dra/dra_bss.h"

static void DestroyPrimitive(Primitive* prim) {
    s32 i;
    s32 n;
    u32* primData = (u32*)prim;

    for (n = sizeof(Primitive) / sizeof(*primData), i = 0; i < n; i++) {
        *primData++ = 0;
    }
}

void DestroyAllPrimitives(void) {
    s32 i;
    Primitive* prim;

    for (i = 0, prim = g_PrimBuf; i < MAX_PRIM_COUNT; i++) {
        DestroyPrimitive(prim);
        prim->type = PRIM_NONE;
        prim++;
    }
}

s32 func_800EDAE4(void) {
    s32 i;
    DR_ENV* ptr = &D_800974AC[0];

    for (i = 0; i < 16; i++, ptr++) {
        ptr->tag = 0;
    }
#ifdef VERSION_PSP
    return 0;
#endif
}

DR_ENV* func_800EDB08(Primitive* prim) {
    s32 i;
    DR_ENV* dr = &D_800974AC[0];

    for (i = 0; i < LEN(D_800974AC); i++, dr++) {
        if (dr->tag == 0) {
#ifdef VERSION_PSP
            SetDrawEnv(dr, 0);
#endif
            dr->tag = 1;
            setcode(prim, 7);
            *(DR_ENV**)&prim->r1 = dr;
            return dr;
        }
    }

    return NULL;
}

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", func_800EDB58);

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", AllocPrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", func_800EDD9C);

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", FreePrimitives);

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", RenderPrimitives);
