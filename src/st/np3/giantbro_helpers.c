// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

// This file contains helper functions used by the "Giant Brothers"
// They are Blade, Gurkha, and Hammer.

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

// Based on the body part's angle and length, update its X and Y positions
// using the parent's position with a polar coordinate offset.
void polarPlacePart(Entity* self) {
    s16 angle = self->ext.GH_Props.rotate;
    Entity* src;

    if (g_CurrentEntity->facingLeft) {
        angle = -angle;
    }

    src = self->ext.GH_Props.parent;
    self->posX.val = src->posX.val;
    self->posY.val = src->posY.val;
    self->posX.val -= self->ext.GH_Props.length * rsin(angle) * 16;
    self->posY.val += self->ext.GH_Props.length * rcos(angle) * 16;
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
    src->posX.val -= -self->ext.GH_Props.length * rsin(angle) * 16;
    src->posY.val =
        -self->ext.GH_Props.length * rcos(angle) * 16 + src->posY.val;
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
    func_801CD78C((Point32*)temp_a0, temp_a0->ext.GH_Props.length,
                  temp_a0->ext.GH_Props.rotate, (Point32*)ent1);
    func_801CD78C((Point32*)ent1, ent2->ext.GH_Props.length,
                  ent2->ext.GH_Props.rotate, (Point32*)ent2);
}
// unused
void func_801CDA6C(Entity* self, s32 arg1) {
    Entity* temp_s0;

    temp_s0 = self->ext.GH_Props.parent;
    func_801CD78C((Point32*)self, -self->ext.GH_Props.length,
                  self->ext.GH_Props.rotate, (Point32*)temp_s0);
    func_801CD78C((Point32*)temp_s0, -temp_s0->ext.GH_Props.length,
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
    temp_s4 = ent1->ext.GH_Props.length << 8;
    temp_s3 = ent2->ext.GH_Props.length << 8;
    ratanX = ratanX >> 8;
    ratanY = ratanY >> 8;
    temp_s2 = SquareRoot0((ratanX * ratanX) + (ratanY * ratanY));
    if (((temp_s4 + temp_s3) << 8) < temp_s2) {
        temp_s2 = ((temp_s4 + temp_s3) << 8);
    }
    temp_s2 = (temp_s2 * temp_s4) / (temp_s4 + temp_s3);
    temp_s3 = (temp_s4 * temp_s4) - (temp_s2 * temp_s2);
    temp_s3 = SquareRoot0(temp_s3);
    temp_s6 += ratan2(temp_s3, temp_s2);
    ent1->ext.GH_Props.unkA4 = temp_s6;
    func_801CD78C(parentPos, ent1->ext.GH_Props.length, temp_s6, &sp10);
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

    if (*arg0 > arg1) {
        *arg0 -= arg2;
    }

    if (*arg0 < arg1) {
        *arg0 += arg2;
    }

    return false;
}

void func_801CDD00(Entity* entity, s16 arg1, s16 arg2) {
    s16 temp_t0 = arg1 - entity->ext.GH_Props.rotate;

    if (temp_t0 > 0x800) {
        temp_t0 = temp_t0 - 0x1000;
    }

    if (temp_t0 < -0x800) {
        temp_t0 = temp_t0 + 0x1000;
    }

    temp_t0 = temp_t0 / arg2;
    entity->ext.GH_Props.unkA6 = temp_t0;
    entity->ext.GH_Props.unkA4 = arg1;
}

void func_801CDD80(s16* arg0, unkStr_801CDD80* arg1) {
    Entity* var_s1;
    s16* ptr = arg1->unk4;

    while (*arg0) {
        if (*arg0 != 0xFF) {
            var_s1 = &g_CurrentEntity[*arg0];
            func_801CDD00(var_s1, *ptr, arg1->unk0);
        }
        ptr++;
        arg0++;
    }
}

void func_801CDE10(s16* arg0) {
    Entity* ent;

    while (*arg0) {
        if (*arg0 != 0xFF) {
            ent = &g_CurrentEntity[*arg0];
            ent->ext.GH_Props.rotate += ent->ext.GH_Props.unkA6;
        }
        arg0++;
    }
}

void polarPlacePartsWithAngvel(s16* entOffsets) {
    Entity* ent;

    while (*entOffsets) {
        if (*entOffsets != 0xFF) {
            ent = &g_CurrentEntity[*entOffsets];
            ent->ext.GH_Props.rotate += ent->ext.GH_Props.unkA6;
            polarPlacePart(ent);
        }
        entOffsets++;
    }
}

void func_801CDF1C(s16 entIndices[], unkStr_801CDD80* arg1, s32 arg2) {

    arg1 += (u16)g_CurrentEntity->ext.GH_Props.unkB0[arg2];

    if (!g_CurrentEntity->ext.GH_Props.unkB4[arg2]) {
        func_801CDD80(entIndices, arg1);
        g_CurrentEntity->ext.GH_Props.unkB4[arg2] = arg1->unk0;
    }
    if (!(--g_CurrentEntity->ext.GH_Props.unkB4[arg2])) {
        arg1++;
        if (!arg1->unk0) {
            g_CurrentEntity->ext.GH_Props.unkB0[arg2] = 0;
        } else {
            ++g_CurrentEntity->ext.GH_Props.unkB0[arg2];
        }
    }
}

void func_801CDFD8(Entity* self, s32 arg1) {
    if (!self->ext.GH_Props.unkB4[0]) {
        func_801CDD00(self, self->ext.GH_Props.unkA4, arg1);
        self->ext.GH_Props.unkB4[0] = arg1;
    }
    self->ext.GH_Props.unkB4[0]--;
    self->ext.GH_Props.rotate += self->ext.GH_Props.unkA6;
    polarPlacePart(self);
}
