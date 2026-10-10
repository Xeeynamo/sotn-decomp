// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern AnimateEntityFrame D_us_8018230C[];

extern s16 D_us_801822CC;
extern s32 D_us_801822E4;
extern s32 D_us_801822F8;
extern s32 D_us_80182328;
extern s16 D_us_801822DC;
extern u16 g_EInitDarkOctopus;

void func_us_801D511C(Entity* self) {
    Entity* nextEntity;
    Collider collider;

    s32 posX;
    s32 posY;

    if ((self->flags & FLAG_DEAD) && (self->step < 4)) {
        self->hitboxState = 0;
        self->drawFlags |= ENTITY_OPACITY;
        self->opacity = 0x80;
        SetStep(4);
    };

    switch (self->step) {
    case 0:
        InitializeEntity(&g_EInitDarkOctopus);
        if (self->params) {
            if (self->params == 1) {
                self->palette = PAL_FLAG(0x225);
            } else {
                self->palette = PAL_FLAG(0x224);
            }
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            self->drawFlags |= ENTITY_OPACITY;
            self->opacity = 0;
            self->step = 5;
            self->zPriority = self->ext.et_801D511C.unk8C->zPriority + 1;
            self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->hitboxState = 0;
            return;
        }
        nextEntity = self + 1;
        CreateEntityFromEntity(E_UNK_3E, self, nextEntity);
        self->hitboxOffX = 1;
        self->hitboxOffY = 0xD;
        self->nextPart = self + 1;
        self->ext.et_801D511C.unk82 = Random() & 0x3;
        break;

    case 1:
        if (UnkCollisionFunc3(&D_us_801822CC) & 0x1) {
            self->ext.et_801D511C.unk80 = 0x100;
            self->ext.et_801D511C.unk80 = Random();
            self->velocityX = FIX(-0.5);
            if (Random() & 0x1) {
                self->velocityX = -self->velocityX;
            }
            self->step += 1;
        }

        break;

    case 2:
        UnkCollisionFunc2(&D_us_801822DC);

        AnimateEntity(&D_us_801822E4, self);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi - 8;
        if (self->velocityX > 0) {
            posX += 0x18;
        } else {
            posX -= 0x18;
        }
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->ext.et_801D511C.unk80 = 0;
        }
        if (!(self->ext.et_801D511C.unk80)) {
            self->velocityX = -self->velocityX;
            self->facingLeft ^= 1;
            self->ext.et_801D511C.unk80 = 0x100;
        } else {
            self->ext.et_801D511C.unk80 -= 1;
        }
        if (!(self->ext.et_801D511C.unk82)) {
            self->ext.et_801D511C.unk84 = ((Random() & 0x7f) * 16) - 0x400;
            self->ext.et_801D511C.unk89 = Random() & 0x3;
            g_api.PlaySfx(SFX_UNK_RNO4_784);
            self->ext.et_801D511C.unk82 = 0x40;
            SetStep(3);
            break;
        }
        self->ext.et_801D511C.unk82 -= 1;
        break;

    case 3:
        AnimateEntity(&D_us_801822F8, self);

        switch (self->ext.et_801D511C.unk89) {
        case 0:
            break;

        case 1:
            self->ext.et_801D511C.unk84 += 0x10;
            break;

        case 2:
            self->ext.et_801D511C.unk84 -= 0x10;
            break;

        case 3:
            AnimateEntity(&D_us_801822F8, self);
            self->ext.et_801D511C.unk84 = ((Random() & 0x7F) * 16) - 0x400;
        }

        switch (self->step_s) {
        case 0:
            if (!(self->ext.et_801D511C.unk82 -= 0x1)) {
                self->step_s += 1;
                self->ext.et_801D511C.unk82 = 0x40;
            }

        case 1:
            AnimateEntity(&D_us_801822F8, self);
            if (((self->ext.et_801D511C.unk82) % 6) == 0) {
                nextEntity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xBC]);
                if (nextEntity) {
                    CreateEntityFromEntity(E_UNK_3F, self, nextEntity);
                    nextEntity->ext.et_801D511C.unk84 =
                        self->ext.et_801D511C.unk84;
                }
            }
            if ((self->step_s > 0) &&
                (!((self->ext.et_801D511C.unk82) & 0xf))) {
                g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            }
            if (!(self->ext.et_801D511C.unk82 -= 0x1)) {
                self->step_s += 1;
                self->ext.et_801D511C.unk82 = 0x80;
                return;
            }
            break;

        case 2: {
            if (!(self->ext.et_801D511C.unk82 -= 0x1)) {
                SetStep(2);
                self->ext.et_801D511C.unk82 = 0x80;
                return;
            }
        } break;
        } // inner switch
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            nextEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (nextEntity) {
                CreateEntityFromEntity(E_SUBWPN_IN_CONT, self, nextEntity);
                nextEntity->params = 1;
                self->ext.et_801D511C.unk8C = nextEntity;
                nextEntity->ext.et_801D511C.unk8C = self;
            } else {
                self->ext.et_801D511C.unk8C = 0;
            }
            self->step_s += 1;
            return;

        case 1:
            AnimateEntity(&D_us_801822F8, self);
            self->opacity -= 4;
            if (!self->opacity) {
                self->blendMode = BLEND_NO;
                self->palette = PAL_FLAG(0x224);
                self->opacity = 0x80;
                if (self->ext.et_801D511C.unk8C) {
                    nextEntity = self->ext.et_801D511C.unk8C;
                    DestroyEntity(nextEntity);
                }
                self->step_s += 1;
                return;
            }
            break;

        case 2:
            AnimateEntity(&D_us_801822F8, self);
            if ((self + 1)->entityId != 0x3E) {
                self->poseTimer = 0;
                self->pose = 0;
                self->ext.et_801D511C.unk82 = 0x80;
                self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
                self->scaleX = 0x100;
                self->scaleY = 0x100;
                self->step_s++;
                return;
            }
            break;

        case 3:
            if (!(g_Timer % 8)) {
                nextEntity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (nextEntity) {
                    CreateEntityFromEntity(E_EXPLOSION, self, nextEntity);
                    nextEntity->params = 0x11;
                }
            }
            AnimateEntity(&D_us_80182328, self);
            self->ext.et_801D511C.unk82 -= 1;
            if (!(self->ext.et_801D511C.unk82 & 0xf)) {
                g_api.PlaySfx(SFX_NOISE_SWEEP_DOWN_A);
            }
            if (self->ext.et_801D511C.unk82) {
                self->scaleX -= 1;
                return;
            }
            nextEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (nextEntity) {
                CreateEntityFromEntity(E_EXPLOSION, self, nextEntity);
                nextEntity->params = 1;
                nextEntity->posY.i.hi += 0xC;
            }
            PlaySfxPositional(SFX_EXPLODE_B);
            DestroyEntity(self);

            return;

        } // inner switch
        break;

    case 5:
        nextEntity = self->ext.et_801D511C.unk8C;

        self->posX.i.hi = nextEntity->posX.i.hi;
        self->posY.i.hi = nextEntity->posY.i.hi;
        self->animCurFrame = nextEntity->animCurFrame;
        self->opacity = 0x80 - nextEntity->opacity;
        return;

    case 16:
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
    }
}

extern s16 D_us_80182330[];
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
    self->posY.i.hi += D_us_80182330[prevEnt->animCurFrame];

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
        AnimateEntity(D_us_8018230C, self);

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

extern u16 D_us_80180B54;
extern s16 D_us_801822DC;

void func_us_801D5BA4(Entity* self) {
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(&D_us_80180B54);
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_ROTATE;
        self->drawFlags |= ENTITY_OPACITY;
        self->blendMode = BLEND_SUB | BLEND_TRANSP;
        self->opacity = 0x40;
        self->scaleX = 0x10;
        self->scaleY = 0x40;
        player = &PLAYER;
        self->zPriority = player->zPriority + 1;
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
