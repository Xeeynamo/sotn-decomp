// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

void func_801CE04C(Entity* entity, Collider* collider) {
    s16 var_s0 = 0;

    g_api.CheckCollision(
        entity->posX.i.hi, (s16)(entity->posY.i.hi + collider->unk18), collider,
        0);
    if (collider->effects & EFFECT_SOLID) {
        var_s0 = 1;
        if (collider->effects & EFFECT_UNK_8000) {
            if (collider->effects & EFFECT_UNK_4000) {
                if (g_CurrentEntity->facingLeft != 0) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facingLeft != 0) {
                    var_s0 = 2;
                } else {
                    var_s0 = 4;
                }
            }
        }
    }
    entity->ext.GH_Props.unk88 = var_s0;
}

s32 func_801CE120(Entity* self, s32 facing) {
    Collider collider;
    s32 x = self->posX.i.hi;
    s32 y = self->posY.i.hi + 9;
    s32 ret = 0;

    if (facing != 0) {
        x += 64;
    } else {
        x -= 64;
    }

    g_api.CheckCollision(x, y - 6, &collider, 0);
    if (collider.effects & EFFECT_SOLID) {
        ret |= 2;
    }

    g_api.CheckCollision(x, y + 6, &collider, 0);
    if (!(collider.effects & EFFECT_SOLID)) {
        ret |= 4;
    }

    return ret;
}

void func_801CE1E8(s16 step) {
    s32 i;

    g_CurrentEntity->step = step;
    g_CurrentEntity->step_s = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    // BUG: See below.
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB4[i] = 0;
    }
}

void func_801CE228() {
    s32 i;
    // BUG: Array out of bounds writing. Possible explanation:
    // unkB0 was originally a 4-element array. This loop would iterate
    // through the 4 elements and write each to zero.
    // At some point, unkB0 got split to two arrays, unkB0 and unkB4.
    // Now we zero out both arrays. But since each one is only 2 elements,
    // the loop should only be `i < 2`. They forgot to change it. This means
    // that for i = 2 and i = 3, the unkB0 writes are writing into unkB4,
    // and the unkB4 is writing totally out of bounds.
    // As far as we know, this bug does not have any consequences.
    for (i = 0; i < 4; i++) {
        g_CurrentEntity->ext.GH_Props.unkB0[i] = 0;
        g_CurrentEntity->ext.GH_Props.unkB4[i] = 0;
    }
}

void func_801CE258(s16* arg0) {
    Entity* entity;

    while (*arg0 != 0) {
        entity = &g_CurrentEntity[*arg0];
        if (entity->ext.GH_Props.unkA8 == 0) {
            func_801CD83C(entity);
        }
        arg0++;
    }
}

void func_801CE2CC(s16* arg0) {
    s16* var_s0;

    func_801CD91C(&g_CurrentEntity[arg0[1]]);
    func_801CD91C(&g_CurrentEntity[arg0[0]]);
    func_801CD83C(&g_CurrentEntity[arg0[2]]);
    func_801CD83C(&g_CurrentEntity[arg0[3]]);

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

void func_801CE3FC(s16* arg0) {
    s16* var_s0;
    s16 var_v0;
    s32 i;

    for (i = 0, var_s0 = arg0; i < 4; i++) {
        func_801CD83C(&g_CurrentEntity[*var_s0]);
        var_s0++;
    }

    for (arg0 += 4; *arg0 != 0; arg0++) {
        if (*arg0 != 0xFF) {
            func_801CD83C(&g_CurrentEntity[*arg0]);
        }
    }
}

s32 func_801CE4CC(Entity* self) {
    Entity* entity;
    s32 step;
    s32 x;

    if (g_CurrentEntity->ext.GH_Props.unk8E != 0) {
        g_CurrentEntity->ext.GH_Props.unk8E--;
    }

    x = self->posX.i.hi - PLAYER.posX.i.hi;
    if (g_CurrentEntity->facingLeft != 0) {
        x = -x;
    }

    if (x < -16) {
        func_801CE1E8(10);
        return;
    }

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        entity = g_CurrentEntity + 10;
    } else {
        entity = g_CurrentEntity + 13;
    }

    if (func_801CE120(entity, g_CurrentEntity->facingLeft) != 0) {
        func_801CE1E8(7);
        return;
    }
    if (func_801CE120(entity, g_CurrentEntity->facingLeft ^ 1) != 0) {
        func_801CE1E8(5);
        return;
    }

    if (g_CurrentEntity->step == 8) {
        if (x < 80) {
            step = 5;
        } else {
            step = 8;
        }
    } else {
        if (x < 80) {
            step = 7;
        } else {
            step = 5;
        }
        if (x > 160) {
            step = 8;
        }
    }

    if ((g_CurrentEntity->ext.GH_Props.unk8E == 0) && (x < 96)) {
        g_CurrentEntity->ext.GH_Props.unk8E = 3;
        step = 6;
    }
    if (step != g_CurrentEntity->step) {
        func_801CE1E8(step);
    }
    if (g_CurrentEntity->step == 7) {
        if (step == 5) {
            g_CurrentEntity->ext.GH_Props.unkB0[0] = 1;
        }
    }
}
