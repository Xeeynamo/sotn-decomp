// SPDX-License-Identifier: AGPL-3.0-or-later
#include "inc_asm.h"
#include "sattypes.h"

#include "warp.h"

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC040, func_060DC040);

// inlined in case 0 of EntityWarpRoom on PSX
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC4D4, func_060DC4D4);

// inlined in the final chunk of code from EntityWarpRoom on PSX
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC7D8, func_060DC7D8);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCAFC, func_060DCAFC);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCE50, func_060DCE50);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCF5C, func_060DCF5C);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD038, func_060DD038);

INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD894, func_060DD894);
