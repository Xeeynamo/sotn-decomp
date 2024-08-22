// SPDX-License-Identifier: AGPL-3.0-only
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/warp/data", d60DC000, d_060DC000);

void EntityWarpRoom(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC040, func_060DC040);

// inlined in case 0 of EntityWarpRoom on PSX
void WarpRoomInit(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC4D4, func_060DC4D4);

// inlined in the final chunk of code from EntityWarpRoom on PSX
void WarpRoomAnimateBg(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DC7D8, func_060DC7D8);

void EntityWarpSmallRocks(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCAFC, func_060DCAFC);

void func_060DCE50(s16 arg0);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCE50, func_060DCE50);

void func_060DCF5C(u32 arg0);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DCF5C, func_060DCF5C);

void func_060DD038(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD038, func_060DD038);

void func_060DD894(Entity* self);
INCLUDE_ASM("asm/saturn/warp/f_nonmat", f60DD894, func_060DD894);

INCLUDE_ASM("asm/saturn/warp/data", d60DDD74, d_060DDD74);
