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

s32 func_800EDB58(u8 primType, s32 count) {
    s32 primStartIdx;
    s32 i;
    s32 var_v1;
    Primitive* prim;
    
    var_v1 = count;
    primStartIdx = 0;
    for(i = 0, prim = g_PrimBuf; i < 0x400; prim++, i++){
        if (prim->type != PRIM_NONE) {
            primStartIdx = i + 1;
            var_v1 = count;
        } else if (--var_v1 == 0) {
            break;
        }
    }
    if (var_v1 != 0) {
        return -1;
    }
    
    for (i = 0, prim = &g_PrimBuf[primStartIdx]; i < count; i++, prim++) {
        DestroyPrimitive(prim);
        prim->type = primType;
        prim->next = &g_PrimBuf[primStartIdx] + i + 1;    
    }
    prim[-1].type &= 0xEF;
    prim[-1].next = NULL;
    // Casted return value as mentioned above
    return (s16)primStartIdx;
}

s32 AllocPrimitives(u8 primType, s32 count) {
    s32 i;
    Primitive* prim;
    s16 index;

    for(i = 0, prim = &g_PrimBuf[0]; i < MAX_PRIM_ALLOC_COUNT; i++, prim++){
        if (prim->type == 0) {
            DestroyPrimitive(prim);
            if (count == 1) {
                prim->type = primType;
                prim->next = NULL;
                if (D_800A2438 < i) {
                    D_800A2438 = i;
                }
            } else {
                prim->type = primType;
                index = AllocPrimitives(primType, count - 1);
                if (index == -1) {
                    prim->type = 0;
                    return -1;
                }
                prim->next = &g_PrimBuf[index];
            }
            return (s16)i;
        }
    }
    return -1;
}

s32 func_800EDD9C(u8 type, s32 count) {
    s32 i;
    Primitive* prim;
    s16 foundPolyIndex;

    for(prim = &g_PrimBuf[LEN(g_PrimBuf) - 1],i = LEN(g_PrimBuf) - 1; i >= 0; i--, prim--) {
        if (prim->type == PRIM_NONE) {
            DestroyPrimitive(prim);
            if (count == 1) {
                prim->type = type;
                prim->next = NULL;
            } else {
                prim->type = type;
                foundPolyIndex = func_800EDD9C(type, count - 1);
                prim->next = &g_PrimBuf[foundPolyIndex];
            }
            foundPolyIndex = i;
            return foundPolyIndex;
        }
    }
    return 0;
}

void FreePrimitives(s32 primitiveIndex) {
    Primitive* prim; 

    for (prim = &g_PrimBuf[primitiveIndex]; prim != NULL; prim = prim->next) {
        if (prim->type == PRIM_ENV) {
            **(DR_ENV***)&prim->r1 = NULL;
            prim->type = PRIM_NONE;
        } else {
            prim->type = PRIM_NONE;
        }
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/42B0", RenderPrimitives);
