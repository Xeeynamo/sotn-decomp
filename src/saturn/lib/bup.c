#include "sattypes.h"
#include "inc_asm.h"

// SEGA_BUP.A
const char* bup_version = "BUP Version 1.25 1997-06-20";
const u32 pad_06030400 = 0x00000000;
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030404, func_06030404); // BUP_Init
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030478, func_06030478); // preProc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60304CC, func_060304CC); // postProc

// change_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030518, func_06030518);
// return_dfunc
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030554, func_06030554);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030580, func_06030580); // dummy_func
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603058C, func_0603058C); // isConSeri

// _BUP_SelPart
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60305CC, func_060305CC);

// _BUP_Format
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030640, func_06030640);

// _BUP_Stat
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030690, func_06030690);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60306EC, func_060306EC); // BUP_Write
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030768, func_06030768); // BUP_Read
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60307C4, func_060307C4); // BUP_Delete
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603081C, func_0603081C); // BUP_Dir

// _BUP_Verify
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030898, func_06030898);

// _BUP_GetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60308F4, func_060308F4);
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030968, func_06030968); // BUP_SetDate
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f603099C, func_0603099C); // get_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f60309D4, func_060309D4); // set_imask
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A20, func_06030A20); // set_sr
INCLUDE_ASM("asm/saturn/zero/f_nonmat", f6030A30, func_06030A30); // get_sr

INCLUDE_ASM_NO_ALIGN("asm/saturn/zero/data", d6030A4A, d_6030A4A);
