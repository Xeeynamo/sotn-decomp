// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

extern u8 D_us_80181974[];
extern u8 D_us_80181980[];
extern u8 D_us_80181994[];
extern s16 D_us_801819A0[][2];
extern s32 D_pspeu_092A03E0;

void EntityKillerFish(Entity* self) {
    Entity* entity;
    s16* ptr;
    s32 i;
    u16 params;

    if (self->flags & 0x100 && self->step != 4) {
        SetStep(4);
    }

    params = self->params;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitKillerFish);
        self->facingLeft = params & 1;
        break;
    case 1:
        // nb. Interesting this is using the in-built rand() and not Random()
        if (!AnimateEntity(D_us_80181974, self) && !(rand() & 3)) {
            SetStep(2);
            self->ext.killerFish.unk7C = 0x100;
        }
        break;
    case 2:
        if (AnimateEntity(D_us_80181980, self) & 0x80 &&
            (self->pose == 3 || self->pose == 7)) {
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
        }
        if (self->velocityX != 0) {
            if (self->facingLeft) {
                self->velocityX -= 0x400;
            } else {
                self->velocityX += 0x400;
            }
        }
        MoveEntity();
        if (!--self->ext.killerFish.unk7C) {
            self->velocityX = 0;
            SetStep(3);
        }
        break;
    case 3:
        if (!AnimateEntity(D_us_80181994, self)) {
            if (self->ext.killerFish.unk80++ & 1) {
                SetStep(1);
            } else {
                self->ext.killerFish.unk7C = 0x100;
                SetStep(2);
            }
            self->animCurFrame = 1;
            self->facingLeft ^= 1;
            if (self->facingLeft) {
                self->posX.i.hi += 8;
            } else {
                self->posX.i.hi -= 8;
            }
        }
        break;
    case 4:
        PlaySfxPositional(SFX_EXPLODE_B);
        ptr = D_us_801819A0[0];

        for (i = 0; i < 5; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_ID(ID_5A), entity);
            if (self->facingLeft) {
                entity->posX.i.hi += *ptr++;
            } else {
                entity->posX.i.hi -= *ptr++;
            }
            entity->posY.i.hi += *ptr++;
        }

        DestroyEntity(self);
        return;
    }

    params = self->animCurFrame;
    if (params == 9) {
        self->hitboxWidth = 6;
        self->hitboxOffX = -0xA;
    } else {
        self->hitboxWidth = 0x14;
        self->hitboxOffX = 0;
        if (params >= 10 && params < 13) {
            self->hitboxWidth = 0x10;
            self->hitboxOffX = 4;
        }
    }
    self->hitboxOffY = 2;
    self->hitboxHeight = 8;
}

extern u8 D_us_801819B4[];

void func_us_801C9460(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = 0xE;
        self->unk5A = 0x79;
        self->palette = PAL_DRA(0x2E8);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_UNK8;
        self->unk6C = 0x60;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->velocityY += -0x8000 - 0x8000;
        return;
    }

    self->posY.val += self->velocityY;
    if (!AnimateEntity(D_us_801819B4, self)) {
        DestroyEntity(self);
    }
}
