// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game_psp.h>

typedef struct {
    s32 (*unk0)(void);
} unk_08935640;

void func_psp_08935640(unk_08935640* arg0, s32 arg1) {
    s32 (* volatile sp1C)(void);

    while ((u32)arg0 < arg1) {
        sp1C = arg0->unk0;
        sp1C();
        arg0++;
    }
}

void func_psp_089356A0(unk_08935640* arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_psp_08935640(arg0, arg1);
    func_psp_08937228(arg2, arg3);
}

extern s32* D_psp_090DC8E0;

s32 func_psp_089356E8(s32 arg0, s32 arg1, s32* arg2) {
    arg2[0] = (s32)D_psp_090DC8E0;
    arg2[1] = arg1;
    arg2[2] = arg0;
    D_psp_090DC8E0 = arg2;
    return arg0;
}

INCLUDE_ASM("main_psp/nonmatchings/main_psp/36D34", func_psp_0893573C);
