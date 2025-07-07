// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../np3/np3.h"

// unused debug variables
static s32 D_801D3378;
static s32 D_801D337C;
static s32 D_801D3380;
static s32 D_801D3384;
static s32 D_801D3388;
STATIC_PAD_BSS(104);
// unused debug function
void func_801CD658(void) {
    g_CurrentBuffer = g_CurrentBuffer->next;
    FntPrint("a:%x\n", D_801D3378);
    FntPrint("b:%x\n", D_801D337C);
    FntPrint("c:%x\n", D_801D3380);
    FntPrint("d:%x\n", D_801D3384);
    FntPrint("e:%x\n", D_801D3388);
    DrawSync(0);
    VSync(0);
    PutDrawEnv(&g_CurrentBuffer->draw);
    PutDispEnv(&g_CurrentBuffer->disp);
    FntFlush(-1);
}
// unused debug function
void func_801CD734() {
    while (PadRead(0))
        func_801CD658();
    while (!PadRead(0))
        func_801CD658();
}

static void func_801CD78C(Point32* src, s32 speed, s16 angle, Point32* dst) {
    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    *dst = *src;

    dst->x -= speed * rsin(angle) * 16;
    dst->y += speed * rcos(angle) * 16;
}

// clang-format off

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925B558);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925B680);

// func_801CDAC8
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925B7A0);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925B990);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BA78);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BB38);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BBF8);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BC90);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BD38);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BE60);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925BEF0);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925C090);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925C0F8);

// EntityBlade
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925C350);

// EntityBladeSword
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925D890);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925DD30);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925DD78);

// Gurkha
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925DF90);

// EntityGurkhaSword
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925F370);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925F770);

// Hammer
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_0925F9D0);

// EntityGurkhaBodyParts
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09260A58);

// EntityHammerWeapon
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09260EE0);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09261108);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09261240);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09261320);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_092613B8);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09261418);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_092614A8);

INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/ham_gurk_blade", func_pspeu_09261630);

// clang-format on
