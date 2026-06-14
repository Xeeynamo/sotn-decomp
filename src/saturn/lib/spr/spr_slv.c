#include "../sattypes.h"
#include "../inc_asm.h"

#define _SPR2_
#include "spr.h"

extern Uint32 SPR_SlaveParam;

// func_06023108
void SPR_InitSlaveSH(void) {}

// func_06023114
void SPR_RunSlaveSH(PARA_RTN* routine, void* parm) {
    SPR_SlaveParam = (Uint32)parm;
    routine((void*)SPR_SlaveParam);
}

// func_06023144
void SPR_WaitEndSlaveSH(void) {}

// spr_2a.src
INCLUDE_ASM("asm/saturn/zero/data", d6023150, d_06023150);
