// SPDX-License-Identifier: AGPL-3.0-only
#include "inc_asm.h"
#include "sattypes.h"

INCLUDE_ASM("asm/saturn/t_bat/data", d60CF000, d_060CF000);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF060, func_060CF060);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF294, func_060CF294);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF2E8, func_060CF2E8);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF410, func_060CF410);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF5F4, func_060CF5F4);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CF6B4, func_060CF6B4);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFB00, func_060CFB00);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60CFC48, func_060CFC48);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0490, func_060D0490);

void f60D0938() {}
void f60D0944() {}
void f60D0950() {}
void f60D095C() {}
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0968, func_060D0968);
void f60D0A4C() {}
void f60D0A58() {}
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D0A64, func_060D0A64);
void f60D1010() {}
void f60D101C() {}
void f60D1028() {}
void f60D1034() {}

extern s32 D_80174D3C; // 0x060D1DFCh

void DestroyEntity(Entity*); // func_0600FFB8h

// PSX: func_80173C2C
// SAT: func_060D1040
void func_80173C2C(Entity* entity) {
    if (entity->params == 0xF) {
        D_80174D3C = 1;
    }
    func_0600FFB8(entity); // DestroyEntity
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1070, func_060D1070);

// PSX: TT_000:func_80173E78
// SAT: T_BAT:f_021B8 / func_060D11B8
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

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D11DC, func_060D11DC);

// PSX: func_80173F30
// SAT: func_060D1224
s32 func_80173F30(Entity* entity, s16 x, s16 y) {
    s16 diffx = x - entity->posX.i.hi;
    // not the same implementation as ratan2
    return func_0600EE88(-(s16)(y - entity->posY.i.hi), diffx) &
           0xFFF; // was entity->posY.i.hi
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D125C, func_060D125C);

s32 func_0600F914(s32, s32);

// SAT: func_060D12AC
// PSX: func_80173FE8
s32 func_80173FE8(Entity* entity, s32 x, s32 y) {
    s32 diffX = x - entity->posX.i.hi;
    s32 diffY = y - entity->posY.i.hi;

    // not shifted by 12
    return func_0600F914((diffX * diffX + diffY * diffY),
                         diffX); // SquareRoot12
}

INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D12DC, func_060D12DC);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D141C, func_060D141C);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1640, func_060D1640);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D16D0, func_060D16D0);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1784, func_060D1784);
INCLUDE_ASM("asm/saturn/t_bat/f_nonmat", f60D1808, func_060D1808);
INCLUDE_ASM("asm/saturn/t_bat/data", d60D1858, d_060D1858);
