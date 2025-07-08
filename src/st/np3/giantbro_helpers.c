// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

static s32 D_801D3378;
static s32 D_801D337C;
static s32 D_801D3380;
static s32 D_801D3384;
static s32 D_801D3388;
STATIC_PAD_BSS(104);

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

    if (g_CurrentEntity->facingLeft != 0) {
        angle = -angle;
    }

    src = self->ext.GH_Props.parent;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.GH_Props.unk9E * rsin(angle) * 16;
    self->posY.val += self->ext.GH_Props.unk9E * rcos(angle) * 16;
    if (self->ext.GH_Props.unkA8 != 0) {
        FntPrint("CAUTION!! WARNING_A AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

void func_801CD91C(Entity* self) {
    s16 angle = self->ext.GH_Props.rotate;
    Entity* src;

    if (g_CurrentEntity->facingLeft != 0) {
        angle = -angle;
    }
    src = self->ext.GH_Props.parent;
    src->posX.val = self->posX.val;
    src->posY.val = self->posY.val;
    src->posX.val -= -self->ext.GH_Props.unk9E * rsin(angle) * 16;
    src->posY.val =
        -self->ext.GH_Props.unk9E * rcos(angle) * 16 + src->posY.val;
    if (self->ext.GH_Props.unkA8 != 0) {
        FntPrint("CAUTION!! WARNING_B AT %x\n", self->animCurFrame);
    }
    self->ext.GH_Props.unkA8 |= 1;
}

// unused
void func_801CDA14(Entity* ent1, Entity* ent2) {
    Entity* temp_a0;

    temp_a0 = ent1->ext.GH_Props.parent;
    func_801CD78C(temp_a0, temp_a0->ext.GH_Props.unk9E,
                  temp_a0->ext.GH_Props.rotate, ent1);
    func_801CD78C(
        ent1, ent2->ext.GH_Props.unk9E, ent2->ext.GH_Props.rotate, ent2);
}
// unused
void func_801CDA6C(Entity* self, s32 arg1) {
    Entity* temp_s0;

    temp_s0 = self->ext.GH_Props.parent;
    func_801CD78C(
        self, -self->ext.GH_Props.unk9E, self->ext.GH_Props.rotate, temp_s0);
    func_801CD78C(temp_s0, -temp_s0->ext.GH_Props.unk9E,
                  temp_s0->ext.GH_Props.rotate, arg1);
}

void func_801CDAC8(Entity* ent1, Entity* ent2) {
    Point32 sp10;
    s32 ratanX;
    s32 ratanY;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    Point32* parentPos;
    s16 temp_s6;

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

bool func_801CDC80(s16* arg0, s16 arg1, s16 arg2) {
    if (abs(*arg0 - arg1) < arg2) {
        *arg0 = arg1;
        return true;
    }

    if (arg1 < *arg0) {
        *arg0 = *arg0 - arg2;
    }

    if (*arg0 < arg1) {
        *arg0 = arg2 + *arg0;
    }

    return false;
}

void func_801CDD00(Entity* entity, s16 arg1, s16 arg2) {
    s16 temp_t0 = arg1 - entity->ext.GH_Props.rotate;

    if (temp_t0 > 0x800) {
        temp_t0 -= 0x1000;
    }

    if (temp_t0 < -0x800) {
        temp_t0 += 0x1000;
    }

    do {
        entity->ext.GH_Props.unkA4 = arg1;
        entity->ext.GH_Props.unkA6 = temp_t0 / arg2;
    } while (0);
}

void func_801CDD80(s16* arg0, Entity* arg1) {
    s16* posY = arg1->posY.val;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            func_801CDD00(&g_CurrentEntity[*arg0], *posY, arg1->posX.val);
        }
        arg0++;
        posY++;
    }
}

void func_801CDE10(s16* arg0) {
    Entity* temp_a0;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            temp_a0 = &g_CurrentEntity[*arg0];
            temp_a0->ext.GH_Props.rotate =
                temp_a0->ext.GH_Props.rotate + temp_a0->ext.GH_Props.unkA6;
        }
        arg0++;
    }
}

void func_801CDE88(s16* arg0) {
    Entity* temp_a0;

    while (*arg0 != 0) {
        if (*arg0 != 0xFF) {
            temp_a0 = &g_CurrentEntity[*arg0];
            temp_a0->ext.GH_Props.rotate =
                temp_a0->ext.GH_Props.rotate + temp_a0->ext.GH_Props.unkA6;
            func_801CD83C(temp_a0);
        }
        arg0++;
    }
}

void func_801CDF1C(s16 entIndices[], s16 arg1[][4], s32 arg2) {

    arg1 += (u16)g_CurrentEntity->ext.GH_Props.unkB0[arg2];

    if (g_CurrentEntity->ext.GH_Props.unkB4[arg2] == 0) {
        func_801CDD80(entIndices, arg1);
        g_CurrentEntity->ext.GH_Props.unkB4[arg2] = arg1[0][0];
    }
    if (!(--g_CurrentEntity->ext.GH_Props.unkB4[arg2])) {
        if (arg1[1][0] == 0) {
            g_CurrentEntity->ext.GH_Props.unkB0[arg2] = 0;
        } else {
            ++g_CurrentEntity->ext.GH_Props.unkB0[arg2];
        }
    }
}

void func_801CDFD8(Entity* self, s32 arg1) {
    if (self->ext.GH_Props.unkB4[0] == 0) {
        func_801CDD00(self, self->ext.GH_Props.unkA4, arg1);
        self->ext.GH_Props.unkB4[0] = arg1;
    }
    self->ext.GH_Props.unkB4[0]--;
    self->ext.GH_Props.rotate += self->ext.GH_Props.unkA6;
    func_801CD83C(self);
}
