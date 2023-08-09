#include "sattypes.h"
#include "inc_asm.h"

// SEGA_CSH.A
#include "xpt.h"
#include "csh.h"

// func_0602B9B4
void CSH_Init(Uint16 sw) {
    Uint32 way;
    Uint32 i;
    Uint32* adrs;

    CSH_SET_ENABLE(CSH_DISABLE);
    for (way = 0; way < 4; way++) {
        CSH_SET_ACS_WAY(way);
        adrs = (Uint32*)0x60000000;
        for (i = 0; i < 64; i++) {
            *adrs = 0;
            adrs += 4;
        }
    }
    CSH_SET_WAY_MODE(sw);
    CSH_SET_CODE_FILL(CSH_CODE_ENABLE);
    CSH_SET_DATA_FILL(CSH_DATA_ENABLE);
    CSH_SET_ENABLE(CSH_ENABLE);
}

// func_0602BA94
void CSH_AllClr(void) {
    Uint32 way;
    Uint32 i;
    Uint32* adrs;

    CSH_SET_ENABLE(CSH_DISABLE);
    for (way = 0; way < 4; way++) {
        CSH_SET_ACS_WAY(way);
        adrs = (Uint32*)0x60000000;
        for (i = 0; i < 64; i++) {
            *adrs = 0;
            adrs += 4;
        }
    }
    CSH_SET_ENABLE(CSH_ENABLE);
}

// func_0602BB3C
void CSH_Purge(void* adrs, Uint32 P_size) {
    typedef Uint32 Line[0x10 / sizeof(Uint32)];
    Line *ptr, *end;
    Uint32 zero = 0;

    ptr = (void*)(((Uint32)adrs & 0x1fffffff) | 0x40000000);
    end = (void*)((Uint32)ptr + P_size - 0x10);
    ptr = (void*)((Uint32)ptr & -sizeof(Line));
    do {
        (*ptr)[0] = zero;
    } while (ptr++ < end);
}

// more funcs here
INCLUDE_ASM("asm/saturn/zero/data", d602bb98, d_0602bb98);
