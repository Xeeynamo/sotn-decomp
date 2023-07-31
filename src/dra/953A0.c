#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"
#if defined(VERSION_US)

void func_801353A0(void) {
    if (*(u16*)&D_801396F4 == 0)
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

void func_80135484(s16 arg0, s32 arg1, s32 arg2, s32 volume, u16 arg4) {
    u16 volumeMod;
    u16 calcVolume;
    s32 progId;

    if (arg2 != 0) {
        D_80138F28 |= (1 << (arg1 * 4 + 0)) + (1 << (arg1 * 4 + 1)) +
                      (1 << (arg1 * 4 + 2)) + (1 << (arg1 * 4 + 3));
    }

    volumeMod = volume;
    if (volumeMod == 0xFFFF) {
        D_8013B620[arg1] = (D_8013AE7C * D_800BF554[arg0].volume) >> 7;
        D_8013B614[arg1] = 0;
    } else {
        calcVolume = (D_8013AE7C * D_800BF554[arg0].volume) >> 7;
        D_8013B620[arg1] = (calcVolume * volumeMod) >> 7;
        D_8013B614[arg1] = arg4;
    }
    D_8013AE84[arg1] = arg0;
    D_8013B5EC[arg1] = D_800BF554[arg0].unk4;
    progId = D_800BF554[arg0].prog + 1;
    D_8013B628[arg1] = D_800C1ECC[progId];
    D_8013B66C[arg1] = 0;
    D_8013B648[arg1] = arg0;
    D_8013AEA0[arg1] = D_800BF554[arg0].unk6;
}

void func_80135624(s16 arg0, s32 arg1, s32 arg2, s16 volume, s16 distance) {
    if (arg2 != 0) {
        D_80138F28 |= (1 << ((arg1 + 6) * 2)) + (1 << (((arg1 + 6) * 2) + 1));
    }
    func_80132A04(
        (arg1 * 2) + 12, D_800BF554[arg0].vabid, D_800BF554[arg0].prog,
        D_800BF554[arg0].tone, D_800BF554[arg0].note, volume, distance);
    D_8013B650[arg1] = arg0;
    D_8013AED4[arg1] = D_800BF554[arg0].unk6;
}

INCLUDE_ASM("asm/us/dra/nonmatchings/953A0", func_8013572C);

s16 IncrementRingBufferPos(s16 arg0) {
    arg0++;

    if (arg0 == MAX_SND_COUNT) {
        arg0 = 0;
    }

    return arg0;
}

void func_80135C2C(void) {
    s16 sfxBufPos;
    s32 isFound;
    s16 sndId;

    if (g_sfxRingBufferPos1 == D_80138FAC)
        return;
    while (D_80138FAC != g_sfxRingBufferPos1) {
        sndId = g_sfxRingBuffer1[D_80138FAC].sndId;
        g_sfxRingBuffer1[D_80138FAC].sndId = 0;
        isFound = 0;
        for (sfxBufPos = IncrementRingBufferPos(D_80138FAC);
             sfxBufPos != g_sfxRingBufferPos1;
             sfxBufPos = IncrementRingBufferPos(sfxBufPos)) {
            if (sndId == g_sfxRingBuffer1[sfxBufPos].sndId) {
                isFound = 1;
                break;
            }
        }
        if (isFound == 0) {
            func_8013572C(sndId, g_sfxRingBuffer1[D_80138FAC].unk02,
                          g_sfxRingBuffer1[D_80138FAC].unk04);
        }

        D_80138FAC = IncrementRingBufferPos(D_80138FAC);
    }
}

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
#endif
