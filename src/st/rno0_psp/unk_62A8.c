// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"

// Very similar to a giantbro helper function
static void func_pspeu_0923D928(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x += -(speed * rsin(angle) * 16);
    dst->y += speed * rcos(angle) * 16;
}

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2424);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923DD78);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923DF88);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E1A0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E300);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", StepTowards);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E6D0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923E920);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923EBE8);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923EE78);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F088);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F198);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_pspeu_0923F300);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", EntityGorgon);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D068C);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D0CFC);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D136C);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D15C0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D1BF0);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2038);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D21C8);

INCLUDE_ASM("st/rno0_psp/nonmatchings/rno0_psp/unk_62A8", func_us_801D2264);
