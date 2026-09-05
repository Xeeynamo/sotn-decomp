// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rbo8/rbo8.h"

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

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80195938);

static void func_801D0B40(void) {
    Entity* ent;
    Entity* parent;

    ent = g_CurrentEntity + 7;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x100;

    ent = g_CurrentEntity + 11;
    parent = ent->ext.GH_Props.parent;
    ent->ext.GH_Props.rotate = parent->ext.GH_Props.rotate + 0x180;
}

extern s32 abs(s32 value);

#include "../rbo8/func_us_80195ad8.h"

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80195D80);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80197B1C);

extern EInit g_EInitGalamothLvl50;
extern s32 D_us_80180C0C;

void func_us_801980E4(Entity* self) {
    Entity* source;

    if (D_us_80180C0C != 0) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->hitboxState = 0;
        self->animCurFrame = 0x10;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x100;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0xC0;
        self->drawFlags |= ENTITY_ROTATE;
        /* fall through */
    case 1:
        if (g_Timer & 1) {
            self->palette = PAL_FLAG(0x206);
        } else {
            self->palette = PAL_FLAG(0x207);
        }
        source = self->ext.et_801980E4.source;
        self->facingLeft = source->facingLeft;
        self->rotate = source->rotate;
        self->posX.i.hi = source->posX.i.hi;
        self->posY.i.hi = source->posY.i.hi;
        self->scaleX = self->scaleY += 0x20;
        self->opacity -= 8;
        if (!self->opacity) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180A8C;
extern u8 D_us_80180C20[];

void func_us_80198210(Entity* self) {
    Entity* entities;
    s16 angle;

    if ((self->flags & FLAG_DEAD) || D_us_80180C0C != 0) {
        self->velocityX = 0;
        self->velocityY = 0;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180A8C);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        entities = g_Entities;
        angle = GetAngleBetweenEntities(self, entities);
        self->velocityX = rcos(angle) * 0x140;
        self->velocityY = rsin(angle) * 0x140;
        /* fall through */

    case 1:
        AnimateEntity(D_us_80180C20, self);
        MoveEntity();
        self->velocityX -= self->velocityX / 0x10;
        self->velocityY -= self->velocityY / 0x10;
        if (abs(self->velocityX) < FIX(0.25) &&
            abs(self->velocityY) < FIX(0.25)) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->hitboxState = 0;
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(D_us_80180C20, self);
        self->scaleX = self->scaleY -= 0x10;
        if (!self->scaleX) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_801983EC);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_80198964);

INCLUDE_ASM("boss/rbo8_psp/nonmatchings/rbo8_psp/unk_EF80", func_us_8019C7B8_from_rcen);

extern EInit D_us_80180A98;

void func_us_801991D4(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_us_80180A98);
        return;
    }
    DestroyEntity(self);
}

void func_us_8019921C(Entity* self) {
    s32 args[9];

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGalamothLvl50);
        self->animCurFrame = self->params;
        self->drawFlags = ENTITY_ROTATE;
        /* fall through */
    case 1:
        MoveEntity();
        self->rotate -= 0x20;
        self->velocityY += FIX(0.125);
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        args[6] = 0x20;
        func_us_801955A0(self, args);
        if (self->ext.et_8019921C.hitFloor) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->zPriority = 0x5F;
        }
        break;
    }
}

extern EInit D_us_80180AA4;
extern AnimationFrame D_us_80180C4C[];

void EntityMinotaurSpitLiquid(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AA4);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += ROT(22.5) - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x28;
        self->velocityY = rcos(angle) * -0x28;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->drawFlags =
            ENTITY_OPACITY | ENTITY_ROTATE | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x20;
        self->scaleY = 0x100;
        self->opacity = 0x80;
        /* fall through */

    case 1:
        MoveEntity();
        self->scaleX += 0xC;
        self->scaleY += 2;
        self->opacity -= 1;
        if (!AnimateEntity(D_us_80180C4C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_80180AB0;
extern u8 D_us_80180C68[];

void func_us_8019943C(Entity* self) {
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AB0);
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += ROT(22.5) - Random() * 2;

        angle = self->rotate;
        self->velocityX = rsin(angle) * 0x20;
        self->velocityY = rcos(angle) * -0x20;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        /* fall through */
    case 1:
        MoveEntity();
        self->posY.i.hi--;
        if (AnimateEntity(D_us_80180C68, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

#include "../../st/e_room_bg.h"
