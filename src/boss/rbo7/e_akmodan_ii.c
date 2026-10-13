// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo7.h"

extern EInit g_EInitInteractable;

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_801940B4);

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_801957C0);

extern EInit D_us_80180444;
extern s8 D_us_8018074C[];
extern u8 D_us_80180764[];

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitbox;
    Entity* harpy;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180444);
        /* fall through */
    case 1:
        harpy = self - 1;
        self->facingLeft = harpy->facingLeft;
        self->posX.val = harpy->posX.val;
        self->posY.val = harpy->posY.val;

        animFrame = harpy->animCurFrame;
        animFrame -= 0x23;
        if (animFrame < 0) {
            animFrame = 0;
        }

        hitbox = D_us_8018074C;
        animFrame = D_us_80180764[animFrame];
        hitbox += animFrame * 4;
        self->hitboxOffX = *hitbox++;
        self->hitboxOffY = *hitbox++;
        self->hitboxWidth = *hitbox++;
        self->hitboxHeight = *hitbox++;

        if (harpy->entityId != E_ID(UNK_19)) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_80195A8C);

INCLUDE_ASM("boss/rbo7/nonmatchings/e_akmodan_ii", func_us_80195D04);

extern u8 D_us_8018076C[];

void EntityCtulhuDeath(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 14;
        self->unk5A = 121;
        self->drawFlags = ENTITY_OPACITY;
        if (self->params) {
            self->palette = 0x2EE;
            self->opacity = 8;
            self->blendMode = BLEND_TRANSP | BLEND_SUB;
            self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        } else {
            self->palette = 0x2E4;
            self->zPriority += 2;
            self->opacity = 0x14;
            self->blendMode = BLEND_TRANSP | BLEND_ADD;
        }
        /* fall through */
    case 1:
        self->posY.val -= FIX(1);
        if (!AnimateEntity(D_us_8018076C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
