// SPDX-License-Identifier: AGPL-3.0-only
#include "sattypes.h"
#include "inc_asm.h"

// SEGA_SYS.A
const char* sys_version = "SYS Version 2.50 1997-06-10";
const u32 pad_06030af8 = 0x00000000;

// _SYS_SetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030AFC, func_06030AFC);

// _SYS_GetUintMacSave
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030B88, func_06030B88);

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d6030BF4, d_6030BF4);
