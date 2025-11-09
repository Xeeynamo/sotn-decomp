// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

enum SpectralSwordSteps {
    SPECTRAL_SWORD_INIT,
    SPECTRAL_SWORD_READY,
    SPECTRAL_SWORD_WEAPONS,
    SPECTRAL_SWORD_HOLD,
    SPECTRAL_SWORD_MOVE,
    SPECTRAL_SWORD_ATTACK,
    SPECTRAL_SWORD_DEATH = 8,
    SPECTRAL_SWORD_DEBUG = 255,
};

enum SpectralSwordWeaponsSubsteps {
    SPECTRAL_SWORD_WEAPONS_INIT,
    SPECTRAL_SWORD_WEAPONS_SPAWN,
};

enum SpectralSwordReadySubsteps {
    SPECTRAL_SWORD_HOLD_INIT,
    SPECTRAL_SWORD_HOLD_WAIT,
};

enum SpectralSwordMoveSubsteps {
    SPECTRAL_SWORD_MOVE_INIT,
    SPECTRAL_SWORD_MOVE_LOOP,
    SPECTRAL_SWORD_MOVE_SPIN,
    SPECTRAL_SWORD_MOVE_TOWARD,
};

enum SpectralSwordAttackSubsteps {
    SPECTRAL_SWORD_ATTACK_INIT,
    SPECTRAL_SWORD_ATTACK_SPIN,
    SPECTRAL_SWORD_ATTACK_FACE_RIGHT,
    SPECTRAL_SWORD_ATTACK_DELAY,
    SPECTRAL_SWORD_ATTACK_EXPAND,
    SPECTRAL_SWORD_ATTACK_RETRACT,
};

enum SpectralSwordDeathSubsteps {
    SPECTRAL_SWORD_DEATH_INIT,
    SPECTRAL_SWORD_DEATH_MOVE,
    SPECTRAL_SWORD_DEATH_DESPAWN,
};

enum SpectralWeaponSteps {
    SPECTRAL_WEAPON_INIT,
    SPECTRAL_WEAPON_WAIT,
    SPECTRAL_WEAPON_MAKE_READY,
    SPECTRAL_WEAPON_READY = 4,
    SPECTRAL_WEAPON_DEATH = 16,
};

enum SpectralWeaponSubsteps {
    SPECTRAL_WEAPON_DEATH_INIT,
    SPECTRAL_WEAPON_DEATH_MOVE,
    SPECTRAL_WEAPON_DEATH_HIDE,
};

extern EInit g_EInitSpectralSword;
extern EInit g_EInitSpectralSwordAura;
extern EInit g_EInitSpectralSwordWeapon;

static s8 hitbox[][2] = {{0, 0},  {0, 0},  {16, 6}, {8, 4},  {18, 6},
                         {16, 3}, {0, 10}, {0, 10}, {0, 10}, {0, 0}};

// EntitySpectralSword primarily uses this as a method to smoothly rotate, but
// also to retract it's outer ring after an attack by decreasing the radius.
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

    if ((self->flags & FLAG_DEAD) && self->step < SPECTRAL_SWORD_DEATH) {
        SetStep(SPECTRAL_SWORD_DEATH);
    }
    switch (self->step) {
    case SPECTRAL_SWORD_INIT:
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
        // Small swords
        for (count = 0; count < 12; count++, entity++) {
            CreateEntityFromEntity(E_SPECTRAL_SWORD_WEAPON, self, entity);
            entity->params = 0;
            entity->ext.spectralSword.poltergeist = self;
        }
        // Large swords
        for (count = 0; count < 4; count++, entity++) {
            CreateEntityFromEntity(E_SPECTRAL_SWORD_WEAPON, self, entity);
            entity->params = 1;
            entity->ext.spectralSword.poltergeist = self;
        }
        self->step = SPECTRAL_SWORD_READY;
        self->ext.spectralSword.hasWeapons = false;
        self->ext.spectralSword.radius = 48;
        self->ext.spectralSword.weaponCount = 16;
        break;
    case SPECTRAL_SWORD_READY:
        if (GetDistanceToPlayerX() < 64) {
            SetStep(SPECTRAL_SWORD_WEAPONS);
        }
        break;
    case SPECTRAL_SWORD_WEAPONS:
        switch (self->step_s) {
        case SPECTRAL_SWORD_WEAPONS_INIT:
            self->ext.spectralSword.timer = 128;
            self->ext.spectralSword.hasWeapons = true;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                entity->step = SPECTRAL_WEAPON_MAKE_READY;
            }
            self->step_s++;
            // fallthrough
        case SPECTRAL_SWORD_WEAPONS_SPAWN:
            tempVar = 0;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                if (entity->step == SPECTRAL_WEAPON_READY ||
                    entity->flags & FLAG_DEAD) {
                    tempVar++;
                }
            }
            if (tempVar == 16) {
                entity = self + 1;
                for (count = 0; count < 16; count++, entity++) {
                    entity->hitboxState = 3;
                }
                SetStep(SPECTRAL_SWORD_HOLD);
            }
            break;
        }
        break;
    case SPECTRAL_SWORD_HOLD:
        switch (self->step_s) {
        case SPECTRAL_SWORD_HOLD_INIT:
            self->ext.spectralSword.timer = 16;
            self->ext.spectralSword.rotate = 0;
            self->step_s++;
            // fallthrough
        case SPECTRAL_SWORD_HOLD_WAIT:
            if (!--self->ext.spectralSword.timer) {
                SetStep(SPECTRAL_SWORD_MOVE);
            }
            break;
        }
        break;
    case SPECTRAL_SWORD_MOVE:
        switch (self->step_s) {
        case SPECTRAL_SWORD_MOVE_INIT:
            self->ext.spectralSword.moveTimer = ((Random() & 3) + 3);
            self->ext.spectralSword.hasWeapons = true;
            self->step_s++;
            // fallthrough
        case SPECTRAL_SWORD_MOVE_LOOP:
            angle = (Random() * 4) + 512;
            posX = (rcos(angle) * 96) >> 12;
            posY = (rsin(angle) * -96) >> 12;
            entity = &PLAYER;
            prim = self->ext.spectralSword.prim;
            prim->x0 = entity->posX.i.hi + posX;
            prim->y0 = entity->posY.i.hi + posY;
            // tempVar is used here to calculate the rotational value (unk9C)
            tempVar = SQ(posX) + SQ(posY);
            tempVar = SquareRoot0(tempVar);
            if (posX < 0) {
                tempVar = -tempVar;
            }
            self->ext.spectralSword.rotateTarget = tempVar;
            // Attack timer
            self->ext.spectralSword.timer = 128;
            if (self->ext.spectralSword.weaponCount) {
                PlaySfxPositional(SFX_PSWORD_TWIRL);
            }
            self->step_s++;
            // fallthrough
        case SPECTRAL_SWORD_MOVE_SPIN:
            if (StepTowards(&self->ext.spectralSword.rotate,
                            self->ext.spectralSword.rotateTarget, 4)) {
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_MOVE_TOWARD:
            MoveEntity();
            if (!--self->ext.spectralSword.timer) {
                self->step_s = SPECTRAL_SWORD_MOVE_LOOP;
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
                self->step_s = SPECTRAL_SWORD_MOVE_LOOP;
                if (!--self->ext.spectralSword.moveTimer) {
                    SetStep(SPECTRAL_SWORD_ATTACK);
                }
            }
            if (posX < 0) {
                tempVar = -tempVar;
            }
            StepTowards(&self->ext.spectralSword.rotate, tempVar, 4);
            break;
        }
        break;
    case SPECTRAL_SWORD_ATTACK:
        switch (self->step_s) {
        case SPECTRAL_SWORD_ATTACK_INIT:
            if (self->ext.spectralSword.weaponCount) {
                PlaySfxPositional(SFX_PSWORD_TWIRL_ATTACK);
            }
            self->step_s++;
            // fallthrough
        case SPECTRAL_SWORD_ATTACK_SPIN:
            if (StepTowards(&self->ext.spectralSword.rotate, ROT(11.25), 2)) {
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_ATTACK_FACE_RIGHT:
            if (StepTowards(&self->ext.spectralSword.rotate, ROT(0), 2)) {
                self->ext.spectralSword.timer = 32;
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_ATTACK_DELAY:
            if (!--self->ext.spectralSword.timer) {
                if (self->ext.spectralSword.weaponCount) {
                    PlaySfxPositional(SFX_WEAPON_SCRAPE_ECHO);
                }
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_ATTACK_EXPAND:
            self->ext.spectralSword.radius += 8;
            if (self->ext.spectralSword.radius > 160) {
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_ATTACK_RETRACT:
            if (StepTowards(&self->ext.spectralSword.radius, 48, 1)) {
                SetStep(SPECTRAL_SWORD_MOVE);
            }
            break;
        }
        break;
    case SPECTRAL_SWORD_DEATH:
        switch (self->step_s) {
        case SPECTRAL_SWORD_DEATH_INIT:
            self->hitboxState = 0;
            entity = self + 1;
            for (count = 0; count < 16; count++, entity++) {
                entity->flags |= FLAG_DEAD;
            }
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->rotate = 0;
            self->step_s++;
            break;
        case SPECTRAL_SWORD_DEATH_MOVE:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            self->rotate -= 4;
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_B);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = EXPLOSION_BIG;
                }
            }
            if (self->posY.i.hi > 352) {
                self->step_s++;
            }
            break;
        case SPECTRAL_SWORD_DEATH_DESPAWN:
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
    case SPECTRAL_SWORD_DEBUG:
#include "../pad2_anim_debug.h"
    }
    if (!(self->flags & FLAG_DEAD)) {
        if (!self->ext.spectralSword.weaponCount) {
            self->ext.spectralSword.hasWeapons = false;
        }
        if (self->ext.spectralSword.hasWeapons) {
            tempVar = 16 - self->ext.spectralSword.weaponCount;
            self->rotate += self->ext.spectralSword.rotate;
            if (self->ext.spectralSword.rotate > 0) {
                self->rotate += tempVar * 2;
            } else {
                self->rotate -= tempVar * 2;
            }
            entity = self + 1;
            radius = (self->ext.spectralSword.radius * 2) / 3;
            angle = self->rotate;
            // Small swords
            for (count = 0; count < 12; count++, entity++) {
                posX = self->posX.val;
                posY = self->posY.val;
                tempVar = self->rotate + (count * angle);
                posX += radius * rcos(angle) * 16;
                posY += radius * rsin(angle) * 16;
                entity->rotate = angle - ROT(90);
                angle += 341;
                if (!(entity->flags & FLAG_DEAD)) {
                    pos = &entity->ext.spectralSword.weaponPos;
                    pos->x.val = posX;
                    pos->y.val = posY;
                }
            }
            radius = self->ext.spectralSword.radius;
            angle = self->rotate / 2;
            // Large swords
            for (count = 0; count < 4; count++, entity++) {
                posX = self->posX.val;
                posY = self->posY.val;
                tempVar = self->rotate + (count * angle);
                posX += (radius * rcos(angle) * 16);
                posY += (radius * rsin(angle) * 16);
                entity->rotate = angle - ROT(90);
                angle += ROT(90);
                if (!(entity->flags & FLAG_DEAD)) {
                    pos = &entity->ext.spectralSword.weaponPos;
                    pos->x.val = posX;
                    pos->y.val = posY;
                }
            }
        }
        if (!(self->flags & 0xF)) {
            // This creates the flickering of the poltergeist sprite (not the
            // growing aura), adding a green border and slighting changing the
            // blade color every other frame.
            if (g_Timer & 1) {
                self->palette = PAL_SPECTRAL_SWORD_WEAPON;
            } else {
                self->palette = PAL_SPECTRAL_SWORD_POLTERGEIST;
            }
        }
        if (!(g_Timer & 0xF)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_SPECTRAL_SWORD_AURA, self, entity);
                entity->ext.spectralSword.poltergeist = self;
            }
        }
    }
}

void EntitySpectralSwordAura(Entity* self) {
    Entity* poltergeist;

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
    poltergeist = self->ext.spectralSword.poltergeist;
    self->posX.val = poltergeist->posX.val;
    self->posY.val = poltergeist->posY.val;
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

    // Unknown why this is here, it does not appear that unkB0 is set at any
    // point.  Perhaps this is something that came from the Spectral Sword in
    // RDAI, but isn't relevant for DAI.
    if (self->ext.spectralSword.unkB0) {
        self->palette = PAL_CC_TURQUOISE_EFFECT;
    } else {
        self->palette = PAL_SPECTRAL_SWORD_WEAPON;
    }
    if ((self->flags & FLAG_DEAD) && (self->step) < SPECTRAL_WEAPON_DEATH) {
        SetStep(SPECTRAL_WEAPON_DEATH);
    }
    switch (self->step) {
    case SPECTRAL_WEAPON_INIT:
        InitializeEntity(g_EInitSpectralSwordWeapon);
        self->hitboxState = 0;
        // Large sword
        if (self->params) {
            self->animCurFrame = 2;
            self->zPriority++;
            // Small sword
        } else {
            self->animCurFrame = 3;
            self->zPriority--;
        }
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->step = SPECTRAL_WEAPON_WAIT;
        break;
    // Wait for EntitySpectralSword to set step to SPECTRAL_WEAPON_MAKE_READY
    case SPECTRAL_WEAPON_WAIT:
        break;
    case SPECTRAL_WEAPON_MAKE_READY:
        MoveEntity();
        pos = &self->ext.spectralSword.weaponPos;
        offsetX = pos->x.i.hi - self->posX.i.hi;
        offsetY = pos->y.i.hi - self->posY.i.hi;

        vectorLength = SQ(offsetX) + SQ(offsetY);
        vectorLength = SquareRoot0(vectorLength);
        distance = vectorLength;
        if (distance > 56) {
            distance = 56;
        }
        if (distance < 4) {
            SetStep(SPECTRAL_WEAPON_READY);
        }
        angle = ratan2(offsetY, offsetX);
        self->velocityX = (distance * rcos(angle));
        self->velocityY = (distance * rsin(angle));
        break;
    case SPECTRAL_WEAPON_READY:
        pos = &self->ext.spectralSword.weaponPos;
        self->posX.i.hi = pos->x.i.hi;
        self->posY.i.hi = pos->y.i.hi;
        break;
    case SPECTRAL_WEAPON_DEATH:
        switch (self->step_s) {
        case SPECTRAL_WEAPON_DEATH_INIT:
            self->hitboxState = 0;
            entity = self->ext.spectralSword.poltergeist;
            // decrement child count
            entity->ext.spectralSword.weaponCount--;
            self->step_s++;
            // fallthrough
        case SPECTRAL_WEAPON_DEATH_MOVE:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_EXPLODE_FAST_A);
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = EXPLOSION_FIREBALL;
                }
            }
            if (self->posY.i.hi > 320) {
                self->step_s++;
                self->animCurFrame = 0;
            }
            break;
        case SPECTRAL_WEAPON_DEATH_HIDE:
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
    angle = self->rotate + ROT(90);
    hitboxPtr = hitbox[self->animCurFrame];
    hitboxRadius = *hitboxPtr++;
    self->hitboxWidth = self->hitboxHeight = *hitboxPtr;
    self->hitboxOffX = (hitboxRadius * rcos(angle)) >> 12;
    self->hitboxOffY = (hitboxRadius * rsin(angle)) >> 12;
}
