#include "sattypes.h"
#include "inc_asm.h"

#include "mth.h"

// mth_fixd.src
INCLUDE_ASM("asm/saturn/zero/data", d602F550, d_0602F550);

// mth_mtrx.src
INCLUDE_ASM("asm/saturn/zero/data", d602F5F4, d_0602F5F4);

// mth_ps2d.src
INCLUDE_ASM("asm/saturn/zero/data", d602FAEC, d_0602FAEC);

// mth_tri.src
INCLUDE_ASM("asm/saturn/zero/data", d602FB84, d_0602FB84);

Fixed32 MTH_Sqrt(Fixed32 x) {
    Fixed32 s, last;
    Sint32 count = 0;

    if (x > MTH_FIXED(0.0)) {
        s = (x > MTH_FIXED(1.0)) ? x : MTH_FIXED(1.0);
        do {
            last = s;
            s = (MTH_Div(x, s) + s) / 2;
            count++;
        } while (s < last);
        return last;
    } else if (x != MTH_FIXED(0.0)) {
        return MTH_FIXED(-1.0);
    } else {
        return MTH_FIXED(0.0);
    }
}

Fixed32 MTH_Hypot(Fixed32 x, Fixed32 y) {
    Sint32 bai;
    Fixed32 bun;

    x = ABS(x);
    y = ABS(y);
    if ((x > MTH_FIXED(1.0)) || (y > MTH_FIXED(1.0))) {
        bai = (x > y) ? MTH_FixedToInt(x) : MTH_FixedToInt(y);
        x = x / bai;
        y = y / bai;
        return MTH_Sqrt(MTH_Mul(x, x) + MTH_Mul(y, y)) * bai;
    } else {
        bun = (x > y) ? MTH_Div(MTH_FIXED(1.0), x) : MTH_Div(MTH_FIXED(1.0), y);
        x = MTH_Mul(x, bun);
        y = MTH_Mul(y, bun);
        return MTH_Div(MTH_Sqrt(MTH_Mul(x, x) + MTH_Mul(y, y)), bun);
    }
}
