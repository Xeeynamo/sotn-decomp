#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_801353A0(void) {
    if (D_801396F4 == 0)
        return;

    switch (D_80139868[0]) {
    case 2:
        func_80133604();
        break;
    case 3:
        func_80133488();
        break;
    case 4:
        func_80132F60();
        break;
    case 6:
        func_80133290();
        break;
    case 8:
        func_80134388();
        break;
    case 10:
        func_801341B4();
        break;
    case 12:
        func_80133960();
        break;
    case 14:
        func_80133BDC();
        break;
    case 16:
        D_8013B684 = 0;
    case 0:
        func_80132E38();
        break;
    }
}

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_80135484);

void func_80135624(s16 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    if (arg2 != 0) {
        D_80138F28 |= (1 << ((arg1 + 6) * 2)) + (1 << (((arg1 + 6) * 2) + 1));
    }
    func_80132A04((arg1 * 2) + 12, D_800BF554[arg0 * 7], D_800BF555[arg0 * 7],
                  D_800BF559[arg0 * 7], D_800BF556[arg0 * 7], arg3, arg4);
    do { // TODO: !FAKE
    } while (0);
    D_8013B650[arg1] = arg0;
    D_8013AED4[arg1] = D_800BF55A[arg0 * 7];
}

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_8013572C);

s16 func_80135C00(s16 arg0) {
    arg0++;

    if (arg0 == 0x100) {
        arg0 = 0;
    }

    return arg0;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_80135C2C);
void func_80135C2C();

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_80135D8C);
void func_80135D8C();

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_80136010);

void func_801361F8(void) {
    if (D_8013AEEC != 0) {
        func_80136010();
        func_80135C2C();
        func_80135D8C();
        func_80134F50();
        func_80133FCC();
        func_801353A0();
        func_8002A024(0, D_80138F28);
        D_80138F28 = 0;
        func_80131FCC();

        if (D_80139020) {
            func_801324B4(0, 0, 0);
        } else {
            func_801324B4(0, D_8013B668, D_8013B668);
        }
    }
}

void nullsub_10(void) {}