// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno0/rno0.h"

// These first two are copied from the Plate Lord?
static void func_pspeu_0923D928(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x += -(speed * rsin(angle) * 16);
    dst->y += speed * rcos(angle) * 16;
}

static void func_us_801D2424(Pos* arg0, s16 arg1, Point16* arg2, Pos* arg3, s16 arg4,
                             Point16* arg5, Primitive* prim) {
    prim->x0 = prim->x1 = arg0->x.i.hi;
    prim->y0 = prim->y1 = arg0->y.i.hi;
    prim->x2 = prim->x3 = arg3->x.i.hi;
    prim->y2 = prim->y3 = arg3->y.i.hi;
    if (g_CurrentEntity->facingLeft) {
        prim->x0 += FLT_TO_I(arg2->x * rcos(arg1));
        prim->x1 -= FLT_TO_I(arg2->y * rcos(arg1));
        prim->x2 += FLT_TO_I(arg5->x * rcos(arg4));
        prim->x3 -= FLT_TO_I(arg5->y * rcos(arg4));
    } else {
        prim->x0 -= FLT_TO_I(arg2->x * rcos(arg1));
        prim->x1 += FLT_TO_I(arg2->y * rcos(arg1));
        prim->x2 -= FLT_TO_I(arg5->x * rcos(arg4));
        prim->x3 += FLT_TO_I(arg5->y * rcos(arg4));
    }
    prim->y0 -= FLT_TO_I(arg2->x * rsin(arg1));
    prim->y1 += FLT_TO_I(arg2->y * rsin(arg1));
    prim->y2 -= FLT_TO_I(arg5->x * rsin(arg4));
    prim->y3 += FLT_TO_I(arg5->y * rsin(arg4));
}

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
