// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/unk_18CC0", func_us_801D511C);

extern s32 D_us_8018230C;
extern s16 D_us_80182330;
extern u16 g_EInitDarkOctopus;

void func_us_801D58FC(Entity* self) {
    Entity* prevEnt;

    if ((self->flags & FLAG_DEAD) && (self->step < 2)) {
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x80;
        self->ext.et_801D58FC.unk82 = 0x80;
        SetStep(2);
    }

    prevEnt = self - 1;
    self->posX.i.hi = prevEnt->posX.i.hi;
    self->posY.i.hi = prevEnt->posY.i.hi;
    self->posY.i.hi += *((&D_us_80182330) + prevEnt->animCurFrame);

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitDarkOctopus);
        self->hitboxWidth = 6;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 1;
        self->hitboxOffY = -5;
        self->nextPart = self - 1;

#if defined(VERSION_PSP)
        break;
#endif

    case 1:
        AnimateEntity(&D_us_8018230C, self);

        break;

    case 2:
        if (!(g_Timer % 8)) {
            prevEnt =
                AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (prevEnt) {
                CreateEntityFromEntity(E_EXPLOSION, self, prevEnt);
                prevEnt->params = 0x11;
            }
        }
        switch (self->step_s) {
        case 0:
            prevEnt =
                AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (prevEnt) {
                CreateEntityFromEntity(E_SUBWPN_IN_CONT, self, prevEnt);
                prevEnt->params = 2;
                self->ext.et_801D58FC.entity = prevEnt;
                prevEnt->ext.et_801D58FC.entity = self;
            } else {
                self->ext.et_801D58FC.entity = 0;
            }
            self->step_s += 1;

            break;

        case 1:
            self->opacity -= 4;

            if (!self->opacity) {
                self->blendMode = BLEND_NO;
                self->opacity = 0x80;
                self->poseTimer = 0;
                self->pose = 0;
                self->palette = PAL_FLAG(0x224);
                self->drawFlags |= ENTITY_SCALEY;
                self->scaleY = 0x100;

                if (self->ext.et_801D58FC.entity != 0) {
                    prevEnt = self->ext.et_801D58FC.entity;
                    DestroyEntity(prevEnt);
                }

                self->step_s += 1;
            }
            break;

        case 2:
            self->scaleY -= 4;
            self->posY.val += FIX(0.1875);

            if (self->scaleY < 0x20) {
                self->step_s += 1;
            }

            break;

        case 3:
            DestroyEntity(self);
        }
    }
}

// https://www.decomp.me/scratch/85Slq

extern u16 D_us_80180B54;
extern s16 D_us_801822DC;

void func_us_801D5BA4(Entity* self) {
    Entity* ent;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B54);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_SUB | BLEND_TRANSP;
        self->opacity = 0x40;
        self->scaleX = 0x10;
        self->scaleY = 0x40;
        ent = g_Entities;
        self->zPriority = ent->zPriority + 1;
        self->rotate = self->ext.et_801D5BA4.unk84;
        self->ext.et_801D5BA4.unk88 = 0x30;
        self->step_s = 0;
        return;

    case 1:
        UnkCollisionFunc2(&D_us_801822DC);
        self->velocityX =
            rsin(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        self->velocityY =
            -rcos(self->ext.et_801D5BA4.unk84) * self->ext.et_801D5BA4.unk88;
        if (self->ext.et_801D5BA4.unk88 > 12) {
            self->ext.et_801D5BA4.unk88 -= 2;
        }
        switch (self->step_s) {
        case 0:
            self->scaleX += 8;
            self->scaleY += 0x10;
            if (self->scaleX == 0x100) {
                self->scaleY = 0x100;
                self->ext.et_801D5BA4.unk88 = 4;
                self->hitboxState = 0;
                self->step_s += 1;
                return;
            }
            break;

        case 1:
            self->scaleX += 8;
            self->scaleY += 8;
            self->opacity -= 2;
            if (!self->opacity) {
                DestroyEntity(self);
            }
        }
    }
}
