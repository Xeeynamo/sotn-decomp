#include "inc_asm.h"

typedef int s32;

INCLUDE_ASM("asm/saturn/t_bat", d_00000);
INCLUDE_ASM("asm/saturn/t_bat", f_00060);
INCLUDE_ASM("asm/saturn/t_bat", f_00294);
INCLUDE_ASM("asm/saturn/t_bat", f_002E8);
INCLUDE_ASM("asm/saturn/t_bat", f_00410);
INCLUDE_ASM("asm/saturn/t_bat", f_005F4);
INCLUDE_ASM("asm/saturn/t_bat", f_006B4);
INCLUDE_ASM("asm/saturn/t_bat", f_00B00);
INCLUDE_ASM("asm/saturn/t_bat", f_00C48);
INCLUDE_ASM("asm/saturn/t_bat", f_01490);
void f_01938() {}
void f_01944() {}
void f_01950() {}
void f_0195C() {}
INCLUDE_ASM("asm/saturn/t_bat", f_01968);
void f_01A4C() {}
void f_01A58() {}
INCLUDE_ASM("asm/saturn/t_bat", f_01A64);
void f_02010() {}
void f_0201C() {}
void f_02028() {}
void f_02034() {}
INCLUDE_ASM("asm/saturn/t_bat", f_02040);
INCLUDE_ASM("asm/saturn/t_bat", f_02070);

// PSX: TT_000:func_80173E78
// SAT: T_BAT:f_021B8
s32 func_80173E78(s32 arg0, s32 arg1) {
    if (arg0 < 0) {
        arg0 += arg1;
        if (arg0 > 0) {
            arg0 = 0;
        }
    } else {
        arg0 -= arg1;
        if (arg0 < 0) {
            arg0 = 0;
        }
    }

    return arg0;
}

INCLUDE_ASM("asm/saturn/t_bat", f_021DC);
INCLUDE_ASM("asm/saturn/t_bat", f_02224);
INCLUDE_ASM("asm/saturn/t_bat", f_0225C);
INCLUDE_ASM("asm/saturn/t_bat", f_022AC);
INCLUDE_ASM("asm/saturn/t_bat", f_022DC);
INCLUDE_ASM("asm/saturn/t_bat", f_0241C);
INCLUDE_ASM("asm/saturn/t_bat", f_02640);
INCLUDE_ASM("asm/saturn/t_bat", f_026D0);
INCLUDE_ASM("asm/saturn/t_bat", f_02784);
INCLUDE_ASM("asm/saturn/t_bat", f_02808);
INCLUDE_ASM("asm/saturn/t_bat", d_02858);
