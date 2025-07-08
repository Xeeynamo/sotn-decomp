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

void func_801CD83C(Entity* self) {
    s16 angle = self->ext.GH_Props.rotate;
    Entity* src;

    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }

    src = self->ext.GH_Props.parent;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.GH_Props.unk9E * rsin(angle) * 16;
    self->posY.val += self->ext.GH_Props.unk9E * rcos(angle) * 16;
    if (self->ext.GH_Props.unkA8) {
        FntPrint("CAUTION!! WARNING_A AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

void func_801CD91C(Entity* self) {
    s16 angle = self->ext.GH_Props.rotate;
    Entity* src;

    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }
    src = self->ext.GH_Props.parent;
    src->posX.val = self->posX.val;
    src->posY.val = self->posY.val;
    src->posX.val -= -self->ext.GH_Props.unk9E * rsin(angle) * 16;
    src->posY.val =
        -self->ext.GH_Props.unk9E * rcos(angle) * 16 + src->posY.val;
    if (self->ext.GH_Props.unkA8) {
        FntPrint("CAUTION!! WARNING_B AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

// unused
void func_801CDA14(Entity* ent1, Entity* ent2) {
    Entity* temp_a0;

    temp_a0 = ent1->ext.GH_Props.parent;
    // Need to cast the entities to Point32 to account for PosX/PosY actually
    // being a Point of two F32 values.
    func_801CD78C((Point32*)temp_a0, temp_a0->ext.GH_Props.unk9E,
                  temp_a0->ext.GH_Props.rotate, (Point32*)ent1);
    func_801CD78C(
        (Point32*)ent1, ent2->ext.GH_Props.unk9E, ent2->ext.GH_Props.rotate, (Point32*)ent2);
}
// unused
void func_801CDA6C(Entity* self, s32 arg1) {
    Entity* temp_s0;

    temp_s0 = self->ext.GH_Props.parent;
    func_801CD78C(
        (Point32*)self, -self->ext.GH_Props.unk9E, self->ext.GH_Props.rotate, (Point32*)temp_s0);
    func_801CD78C((Point32*)temp_s0, -temp_s0->ext.GH_Props.unk9E,
                  temp_s0->ext.GH_Props.rotate, (Point32*)arg1);
}

void func_801CDAC8(Entity* ent1, Entity* ent2) {
    Point32 sp10;
    s16 temp_s6;
    Point32* parentPos;
    s32 temp_s4;
    s32 temp_s3;
    s32 temp_s2;
    s32 ratanX;
    s32 ratanY;

    parentPos = (Point32*)ent1->ext.GH_Props.parent;
    ratanX = ent2->posX.val - parentPos->x;
    if (g_CurrentEntity->facingLeft) {
        ratanX = -ratanX;
    }
    ratanY = ent2->posY.val - parentPos->y;
    temp_s6 = ratan2(-ratanX, ratanY);
    temp_s4 = ent1->ext.GH_Props.unk9E << 8;
    temp_s3 = ent2->ext.GH_Props.unk9E << 8;
    ratanX >>= 8;
    ratanY >>= 8;
    temp_s2 = SquareRoot0((ratanX * ratanX) + (ratanY * ratanY));
    if (((temp_s4 + temp_s3) << 8) < temp_s2) {
        temp_s2 = ((temp_s4 + temp_s3) << 8);
    }
    temp_s2 = (temp_s2 * temp_s4) / (temp_s4 + temp_s3);
    temp_s3 = (temp_s4 * temp_s4) - (temp_s2 * temp_s2);
    temp_s3 = SquareRoot0(temp_s3);
    temp_s6 += ratan2(temp_s3, temp_s2);
    ent1->ext.GH_Props.unkA4 = temp_s6;
    func_801CD78C(parentPos, ent1->ext.GH_Props.unk9E, temp_s6, &sp10);
    ratanX = ent2->posX.val - sp10.x;
    if (g_CurrentEntity->facingLeft) {
        ratanX = -ratanX;
    }
    ratanY = ent2->posY.val - sp10.y;
    ent2->ext.GH_Props.unkA4 = ratan2(-ratanX, ratanY);
}

// clang-format off

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
