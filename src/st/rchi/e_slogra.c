// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rchi.h"

INCLUDE_ASM("st/rchi/nonmatchings/e_slogra", EntitySlogra);

extern EInit g_EInitSlograSpear;
extern EInit g_EInitSlograProjectile;
extern s8 g_SlograSpearHitboxes[];
extern u8 g_SlograSpearHitboxIdx[];
extern u8 g_AnimSlograSpearProjectileLaunch[];
extern u8 g_AnimSlograSpearProjectileFly[];

void EntitySlograSpear(Entity* self) {
    s32 animFrame;
    Entity* slogra;
    s8* hitbox;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlograSpear);

    case 1:
        slogra = self - 1;
        self->facingLeft = slogra->facingLeft;
        self->posX.i.hi = slogra->posX.i.hi;
        self->posY.i.hi = slogra->posY.i.hi;
        animFrame = slogra->animCurFrame;
        hitbox = g_SlograSpearHitboxes;
        hitbox += 4 * g_SlograSpearHitboxIdx[animFrame];
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;
        if (slogra->ext.GS_Props.nearDeath) {
            self->step++;
        }
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_ROTATE;
            self->hitboxState = 0;
            if (self->facingLeft) {
                self->velocityX = FIX(-2.25);
            } else {
                self->velocityX = FIX(2.25);
            }
            self->velocityY = FIX(-4);
            self->animCurFrame = 35;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;

        case 1:
            MoveEntity();
            self->velocityY += FIX(0.15625);
            self->rotate += ROT(11.25);
            if (!(self->rotate & 0xFFF)) {
                PlaySfxPositional(SFX_ARROW_SHOT_A);
            }
        }
    }
}

void EntitySlograSpearProjectile(Entity* self) {
    Entity* entity;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 1;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSlograProjectile);
        if (self->facingLeft) {
            self->velocityX = FIX(4);
        } else {
            self->velocityX = FIX(-4);
        }

    case 1:
        if (AnimateEntity(g_AnimSlograSpearProjectileLaunch, self) == 0) {
            SetStep(2);
        }
        break;

    case 2:
        MoveEntity();
        AnimateEntity(g_AnimSlograSpearProjectileFly, self);
        break;
    }
}
