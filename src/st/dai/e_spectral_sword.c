// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

static s8 hitbox[][2] = {{0, 0},  {0, 0},  {16, 6}, {8, 4},  {18, 6},
                         {16, 3}, {0, 10}, {0, 10}, {0, 10}, {0, 0}};

static bool StepTowards(s16* val, s32 target, s32 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }

    if (*val > target) {
        *val -= step;
    }

    if (*val < target) {
        *val += step;
    }

    return false;
}

void EntitySpectralSword(Entity* self) {
    s32 primIndex;
    s32 radius;
    Primitive* prim;
    Pos* pos;
    s32 posX, posY;
    s32 tempVar;
    s32 angle;
    s32 count;
    Entity* entity;

    if ((self->flags & FLAG_DEAD) && self->step < 8) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSword);
        self->animCurFrame = 1;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->hitboxOffX = 0;
        self->hitboxOffY = 4;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.spectralSword.prim = prim;
        prim->u0 = prim->v0 = 2;
        PGREY(prim, 0) = 192;
        prim->priority = 192;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        entity = self + 1;
        for (count = 0; count < 12; count++, entity++) {
            CreateEntityFromEntity(E_SPECTRAL_SWORD_WEAPON, self, entity);
            entity->params = 0;
            entity->ext.spectralSword.unkAC = self;
        }
        for (count = 0; count < 4; count++, entity++) {
            CreateEntityFromEntity(E_SPECTRAL_SWORD_WEAPON, self, entity);
            entity->params = 1;
            entity->ext.spectralSword.unkAC = self;
        }
        self->step = 1;
        self->ext.spectralSword.unk84 = 0;
        self->ext.spectralSword.unkA2 = 48;
        self->ext.spectralSword.unk82 = 16;
        break;
    case 1:
        if (GetDistanceToPlayerX() < 64) {
            SetStep(2);
        }
        break;
    case 2:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.unk80 = 128;
            self->ext.spectralSword.unk84 = 1;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                entity->step = 2;
            }
            self->step_s++;
            // fallthrough
        case 1:
            tempVar = 0;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                if (entity->step == 4 || entity->flags & FLAG_DEAD) {
                    tempVar++;
                }
            }
            if (tempVar == 16) {
                entity = self + 1;
                for (count = 0; count < 16; count++, entity++) {
                    entity->hitboxState = 3;
                }
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.unk80 = 16;
            self->ext.spectralSword.unk9E = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (!--self->ext.spectralSword.unk80) {
                SetStep(4);
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.spectralSword.unk94 = ((Random() & 3) + 3);
            self->ext.spectralSword.unk84 = 1;
            self->step_s++;
            // fallthrough
        case 1:
            angle = (Random() * 4) + 512;
            posX = (rcos(angle) * 96) >> 12;
            posY = (rsin(angle) * -96) >> 12;
            entity = g_Entities;
            prim = self->ext.spectralSword.prim;
            prim->x0 = entity->posX.i.hi + posX;
            prim->y0 = entity->posY.i.hi + posY;
            tempVar = SQ(posX) + SQ(posY);
            tempVar = SquareRoot0(tempVar);
            if (posX < 0) {
                tempVar = -tempVar;
            }
            self->ext.spectralSword.unk9C = tempVar;
            self->ext.spectralSword.unk80 = 128;
            if (self->ext.spectralSword.unk82) {
                PlaySfxPositional(SFX_PSWORD_TWIRL);
            }
            self->step_s++;
            // fallthrough
        case 2:
            if (StepTowards(&self->ext.spectralSword.unk9E,
                            self->ext.spectralSword.unk9C, 4)) {
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            if (!--self->ext.spectralSword.unk80) {
                self->step_s = 1;
            }
            prim = self->ext.spectralSword.prim;
            posX = prim->x0 - self->posX.i.hi;
            posY = prim->y0 - self->posY.i.hi;
            tempVar = SQ(posX) + SQ(posY);
            tempVar = SquareRoot0(tempVar);
            tempVar /= 2;
            if (tempVar > 48) {
                tempVar = 48;
            }
            angle = ratan2(posY, posX);
            self->velocityX = tempVar * rcos(angle);
            self->velocityY = tempVar * rsin(angle);
            if (tempVar < 6) {
                self->step_s = 1;
                if (!--self->ext.spectralSword.unk94) {
                    SetStep(5);
                }
            }
            if (posX < 0) {
                tempVar = -tempVar;
            }
            StepTowards(&self->ext.spectralSword.unk9E, tempVar, 4);
            break;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            if (self->ext.spectralSword.unk82) {
                PlaySfxPositional(SFX_PSWORD_TWIRL_ATTACK);
            }
            self->step_s++;
            // fallthrough
        case 1:
            if (StepTowards(&self->ext.spectralSword.unk9E, 128, 2)) {
                self->step_s++;
            }
            break;
        case 2:
            if (StepTowards(&self->ext.spectralSword.unk9E, 0, 2)) {
                self->ext.spectralSword.unk80 = 32;
                self->step_s++;
            }
            break;
        case 3:
            if (!--self->ext.spectralSword.unk80) {
                if (self->ext.spectralSword.unk82) {
                    PlaySfxPositional(SFX_WEAPON_SCRAPE_ECHO);
                }
                self->step_s++;
            }
            break;
        case 4:
            self->ext.spectralSword.unkA2 += 8;
            if (self->ext.spectralSword.unkA2 > 160) {
                self->step_s++;
            }
            break;
        case 5:
            if (StepTowards(&self->ext.spectralSword.unkA2, 48, 1)) {
                SetStep(4);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->rotate = 0;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            self->rotate -= 4;
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 3;
                }
            }
            if (self->posY.i.hi > 352) {
                self->step_s++;
            }
            break;
        case 2:
            tempVar = 0;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                if (!entity->animCurFrame) {
                    tempVar++;
                }
            }
            if (tempVar == 16) {
                entity = self;
                for (count = 0; count < 17; count++, entity++) {
                    DestroyEntity(entity);
                }
                return;
            }
            break;
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
    if (!(self->flags & FLAG_DEAD)) {
        if (!self->ext.spectralSword.unk82) {
            self->ext.spectralSword.unk84 = 0;
        }
        if (self->ext.spectralSword.unk84) {
            tempVar = 16 - self->ext.spectralSword.unk82;
            self->rotate += self->ext.spectralSword.unk9E;
            if (self->ext.spectralSword.unk9E > 0) {
                self->rotate += tempVar * 2;
            } else {
                self->rotate -= tempVar * 2;
            }
            entity = self + 1;
            radius = (self->ext.spectralSword.unkA2 * 2) / 3;
            angle = self->rotate;
            for (count = 0; count < 12; count++, entity++) {
                posX = self->posX.val;
                posY = self->posY.val;
                tempVar = self->rotate + (count * angle);
                posX += radius * rcos(angle) * 16;
                posY += radius * rsin(angle) * 16;
                entity->rotate = angle - 1024;
                angle += 341;
                if (!(entity->flags & FLAG_DEAD)) {
                    pos = &entity->ext.spectralSword.unk88;
                    pos->x.val = posX;
                    pos->y.val = posY;
                }
            }
            radius = self->ext.spectralSword.unkA2;
            angle = self->rotate / 2;
            for (count = 0; count < 4; count++, entity++) {
                posX = self->posX.val;
                posY = self->posY.val;
                tempVar = self->rotate + (count * angle);
                posX += (radius * rcos(angle) * 16);
                posY += (radius * rsin(angle) * 16);
                entity->rotate = angle - 1024;
                angle += 1024;
                if (!(entity->flags & FLAG_DEAD)) {
                    pos = &entity->ext.spectralSword.unk88;
                    pos->x.val = posX;
                    pos->y.val = posY;
                }
            }
        }
        if (!(self->flags & 0xF)) {
            if (g_Timer & 1) {
                self->palette = PAL_SPECTRAL_SWORD_WEAPON_1;
            } else {
                self->palette = PAL_SPECTRAL_SWORD_WEAPON_2;
            }
        }
        if (!(g_Timer & 0xF)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_SPECTRAL_SWORD_AURA, self, entity);
                entity->ext.spectralSword.unkAC = self;
            }
        }
    }
}

void EntitySpectralSwordAura(Entity* self) {
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitSpectralSwordAura);
        self->hitboxState = 0;
        self->animCurFrame = 1;
        self->palette += 13;
        self->drawFlags |=
            FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->scaleX = self->scaleY = 256;
        self->opacity = 128;
    }
    entity = self->ext.spectralSword.unkAC;
    self->posX.val = entity->posX.val;
    self->posY.val = entity->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if ((self->opacity) < 32) {
        DestroyEntity(self);
    }
}

void EntitySpectralSwordWeapon(Entity* self) {
    Entity* entity;
    Pos* pos;
    s32 offsetX, offsetY;
    s32 vectorLength;
    s32 distance;
    s16 angle;
    s32 hitboxRadius;
    s8* hitboxPtr;

    if (self->ext.spectralSword.unkB0) {
        self->palette = PAL_SPECTRAL_SWORD_WEAPON_3;
    } else {
        self->palette = PAL_SPECTRAL_SWORD_WEAPON_1;
    }
    if ((self->flags & FLAG_DEAD) && (self->step) < 16) {
        SetStep(16);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSwordWeapon);
        self->hitboxState = 0;
        if (self->params) {
            self->animCurFrame = 2;
            self->zPriority++;
        } else {
            self->animCurFrame = 3;
            self->zPriority--;
        }
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->step = 1;
        break;
    case 1:
        break;
    case 2:
        MoveEntity();
        pos = &self->ext.spectralSword.unk88;
        offsetX = pos->x.i.hi - self->posX.i.hi;
        offsetY = pos->y.i.hi - self->posY.i.hi;

        vectorLength = SQ(offsetX) + SQ(offsetY);
        vectorLength = SquareRoot0(vectorLength);
        distance = vectorLength;
        if (distance > 56) {
            distance = 56;
        }
        if (distance < 4) {
            SetStep(4);
        }
        angle = ratan2(offsetY, offsetX);
        self->velocityX = (distance * rcos(angle));
        self->velocityY = (distance * rsin(angle));
        break;
    case 4:
        pos = &self->ext.spectralSword.unk88;
        self->posX.i.hi = pos->x.i.hi;
        self->posY.i.hi = pos->y.i.hi;
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            entity = self->ext.spectralSword.unkAC;
            entity->ext.spectralSword.unk82--;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_FAST_A);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = 1;
                }
            }
            if (self->posY.i.hi > 320) {
                self->step_s++;
                self->animCurFrame = 0;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
    if (self->rotate) {
        self->drawFlags |= FLAG_DRAW_ROTATE;
    } else {
        self->drawFlags = FLAG_DRAW_DEFAULT;
    }
    angle = self->rotate + 1024;
    hitboxPtr = hitbox[self->animCurFrame];
    hitboxRadius = *hitboxPtr++;
    self->hitboxWidth = self->hitboxHeight = *hitboxPtr;
    self->hitboxOffX = (hitboxRadius * rcos(angle)) >> 12;
    self->hitboxOffY = (hitboxRadius * rsin(angle)) >> 12;
}
