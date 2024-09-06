// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../wrp/wrp.h"

void func_8928694(s32, void*);
void func_89286CC(s8[], void*);
void func_8928624(s32, void*);
void func_892865C(s32, void*);
void func_892880C(void*, s32[]);
void func_892752C(void*, s32[]);
void func_8928094(int);
void func_89280A0(s32, s32);
void func_892887C(s16[]);
void func_8928ABC();

void func_psp_09244020(Primitive* arg0) {
    s16 sp78[4];
    s16 sp70[4];
    s32 sp60[4];
    s16 sp58[4];
    s16 sp50[4];
    s16 sp48[4];
    s16 sp40[0x14];

    s8 sp18[8] = {0};
    u8 temp_s0;
    u16 temp_s1;

    if (arg0->p3 & 8) {
        sp78[1] = arg0->next->x1;
        sp78[0] = arg0->next->y1;
        LOW(sp78[0]) += LOWU(arg0->next->u0);
        arg0->next->x1 = sp78[1];
        arg0->next->y1 = sp78[0];
        LOW(arg0->next->x0) += LOW(arg0->next->r1);
    }
    temp_s0 = arg0->next->b3;
    temp_s1 = ((temp_s0) + ((temp_s0) << 8));
    LOH(arg0->r0) = LOH(arg0->r1) = LOH(arg0->r2) = LOH(arg0->r3) = temp_s1;
    arg0->b0 = arg0->b1 = arg0->b2 = arg0->b3 = temp_s0;

    sp60[0] = 0;
    sp60[1] = 0;
    sp60[2] = 0x400 - (s16)LOH(arg0->next->u1);
    func_89286CC(sp18, &sp18[8]);
    if (arg0->p3 & 0x20) {
        sp70[0] = arg0->next->x3;
        sp70[1] = arg0->next->y3;
        func_8928624(sp70[0], &sp18[8]);
        func_892865C(sp70[1], &sp18[8]);
    }
    sp70[2] = LOH(arg0->next->tpage);
    func_8928694(sp70[2], &sp18[8]);
    func_892880C(&sp18[8], sp60);
    if (arg0->p3 & 0x10) {
        sp60[0] = (s32)(s16)arg0->next->x2;
        sp60[1] = (s32)(s16)arg0->next->y2;
        sp60[2] = 0x1000;
        func_892752C(&sp18[8], sp60);
    }
    func_892879C(&sp18[8]);
    func_892882C(&sp18[8]);
    func_8928094(0x400);
    func_89280A0((s16)arg0->next->x1, (s16)arg0->next->y0);
    sp58[0] = -LOH(arg0->next->r2) / 2;
    sp58[1] = -LOH(arg0->next->b2) / 2;
    sp58[2] = 0;
    sp50[0] = (s16)LOH(arg0->next->r2) / 2;
    sp50[1] = -LOH(arg0->next->b2) / 2;
    sp50[2] = 0;
    sp48[0] = -LOH(arg0->next->r2) / 2;
    sp48[1] = (s16)LOH(arg0->next->b2) / 2;
    sp48[2] = 0;
    sp40[0 + 16] = (s16)LOH(arg0->next->r2) / 2;
    sp40[1 + 16] = (s16)LOH(arg0->next->b2) / 2;
    sp40[2 + 16] = 0;
    func_892887C(sp58);
    func_8928ABC();
    func_8929430(&arg0->x0);
    func_892887C(sp50);
    func_8928ABC();
    func_8929430(&arg0->x1);
    func_892887C(sp48);
    func_8928ABC();
    func_8929430(&arg0->x2);
    func_892887C(sp40 + 16);
    func_8928ABC();
    func_8929430(&arg0->x3);
}
