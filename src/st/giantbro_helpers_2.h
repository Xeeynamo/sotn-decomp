// SPDX-License-Identifier: AGPL-3.0-or-later
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

#include "func_801CE1E8.h"

#include "func_801CE228.h"

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
