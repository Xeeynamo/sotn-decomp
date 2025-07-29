// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

void func_801CE04C(Entity* self, Collider* col) {
    u16 var_s0 = 0;
    s16 x = self->posX.i.hi;
    s16 y = self->posY.i.hi + col->unk18;

    g_api.CheckCollision(x, y, col, 0);
    if (col->effects & EFFECT_SOLID) {
        var_s0 = 1;
        if (col->effects & EFFECT_UNK_8000) {
            if (col->effects & EFFECT_UNK_4000) {
                if (g_CurrentEntity->facingLeft) {
                    var_s0 = 4;
                } else {
                    var_s0 = 2;
                }
            } else {
                if (g_CurrentEntity->facingLeft) {
                    var_s0 = 2;
                } else {
                    var_s0 = 4;
                }
            }
        }
    }
    self->ext.GH_Props.unk88 = var_s0;
}

s32 func_801CE120(Entity* self, s32 facing) {
    Collider col;

    s32 ret = 0;
    s32 x = self->posX.i.hi;
    s32 y = self->posY.i.hi + 9;

    if (facing) {
        x += 64;
    } else {
        x -= 64;
    }

    g_api.CheckCollision(x, y - 6, &col, 0);
    if (col.effects & EFFECT_SOLID) {
        ret |= 2;
    }

    g_api.CheckCollision(x, y + 6, &col, 0);
    if ((col.effects & EFFECT_SOLID) == 0) {
        ret |= 4;
    }

    return ret;
}

void func_801CE1E8(s32 step) {
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

void polarPlacePartsList(s16* offsets) {
    Entity* entity;

    while (*offsets) {
        entity = g_CurrentEntity + *offsets;
        if (!entity->ext.GH_Props.unkA8) {
            polarPlacePart(entity);
        }
        offsets++;
    }
}

void func_801CE2CC(s16* offsets) {
    Entity* entity;

    entity = g_CurrentEntity + offsets[1];
    func_801CD91C(entity);
    entity = g_CurrentEntity + offsets[0];
    func_801CD91C(entity);
    entity = g_CurrentEntity + offsets[2];
    polarPlacePart(entity);
    entity = g_CurrentEntity + offsets[3];
    polarPlacePart(entity);
    offsets += 4;

    while (*offsets) {
        if (*offsets != 0xFF) {
            entity = g_CurrentEntity + *offsets;
            polarPlacePart(entity);
        }
        offsets++;
    }
}

void func_801CE3FC(s16* offsets) {
    Entity* entity;
    s32 i;

    for (i = 0; i < 4; i++) {
        entity = g_CurrentEntity + offsets[i];
        polarPlacePart(entity);
    }
    offsets += 4;

    while (*offsets) {
        if (*offsets != 0xFF) {
            entity = g_CurrentEntity + *offsets;
            polarPlacePart(entity);
        }
        offsets++;
    }
}
