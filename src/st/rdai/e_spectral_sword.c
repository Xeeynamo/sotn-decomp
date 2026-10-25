// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

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

static u8 D_us_80181914[] = {0, 1, 0, 0, 1, 0};
extern EInit g_EInitSpectralSwordRDAI;

void EntitySpectralSword(Entity* self) {
    s32 primIndex;
    s32 dist;
    Entity* player;
    Entity* other;
    Primitive* prim;
    s32 yVar;
    Pos* posPtr;
    s32 miscTemp;
    s32 posOffset;
    s32 xVar;
    s32 angle;
    s32 i;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSwordRDAI);
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
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
        self->ext.spectralSwordRdai.prim = prim;
        prim->u0 = prim->v0 = 2;
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        for (other = self + 1, i = 0; i < 6; i++, other++) {
            CreateEntityFromCurrentEntity(E_SPECTRAL_SPEAR, other);
            other->params = i;
            other->params |= D_us_80181914[i] << 8;
        }
        for (i = 0; i < 4; i++, other++) {
            CreateEntityFromCurrentEntity(E_SPECTRAL_SHIELD, other);
            other->params = i;
        }
        SetStep(2);
        self->ext.spectralSwordRdai.timer2 = 0x40;
        self->ext.spectralSwordRdai.attackTimer = 0x40;
        self->ext.spectralSwordRdai.spearsAlive = 6;
        self->ext.spectralSwordRdai.shieldsAlive = 4;
        break;
    case 2:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 3:
        SetStep(6);
        self->ext.spectralSwordRdai.playerSide = GetSideToPlayer() & 1;
        break;
    case 6:
        if (!self->step_s) {
            angle = Random() * 2;
            if (self->ext.spectralSwordRdai.playerSide) {
                angle = angle + 0x100;
            } else {
                angle = angle + 0x500;
            }
            xVar = (rcos(angle) * 0x60) >> 0xC;
            yVar = (rsin(angle) * -0x60) >> 0xC;
            player = &PLAYER;
            prim = self->ext.spectralSwordRdai.prim;
            xVar = prim->x0 = player->posX.i.hi + xVar;
            yVar = prim->y0 = player->posY.i.hi + yVar;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0xC;
            self->velocityY = rsin(angle) * 0xC;
            self->ext.spectralSwordRdai.timer = 0x80;
            self->step_s++;
        }
        // NO NO NO KONAMI WHAT ARE YOU DOING, MoveEntity DOES NOT RETURN
        // ANYTHING
        other = (Entity*)MoveEntity();
        prim = self->ext.spectralSwordRdai.prim;
        xVar = prim->x0 - self->posX.i.hi;
        yVar = prim->y0 - self->posY.i.hi;
        xVar = abs(xVar);
        yVar = abs(yVar);
        if ((xVar < 8 && yVar < 8) || !--self->ext.spectralSwordRdai.timer) {
            self->step_s = 0;
        }
        player = &PLAYER;
        xVar = player->posX.i.hi - self->posX.i.hi;
        if (self->ext.spectralSwordRdai.playerSide) {
            xVar = -xVar;
        }
        if (xVar > 0x80) {
            self->velocityY = 0;
            if (self->ext.spectralSwordRdai.playerSide) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
        }
        if (xVar < 0x40) {
            self->velocityY = 0;
            if (self->ext.spectralSwordRdai.playerSide) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            if (!--self->ext.spectralSwordRdai.timer2) {
                SetStep(5);
            }
        } else {
            self->ext.spectralSwordRdai.timer2 = 0x40;
        }
        if (self->ext.spectralSwordRdai.spearsAlive) {
            if (!--self->ext.spectralSwordRdai.attackTimer) {
                miscTemp = Random() & 3;
                switch (miscTemp) {
                case 0:
                case 1:
                    self->ext.spectralSwordRdai.attackTimer = 0x100;
                    miscTemp =
                        (Random() % (self->ext.spectralSwordRdai.spearsAlive)) +
                        1;
                    other = self + 1;
                    for (i = 0; i < 6; i++, other++) {
                        if (!(other->flags & FLAG_DEAD)) {
                            miscTemp -= 1;
                        }
                        if (miscTemp == 0) {
                            break;
                        }
                    }
                    other->ext.spectralSwordRdai.modeFlags = 1;
                    break;
                case 2:
                    self->ext.spectralSwordRdai.attackTimer = 0x180;
                    player = &PLAYER;
                    angle = GetAngleBetweenEntities(self, player);
                    other = self + 1;
                    for (i = 0; i < 6; i++, other++) {
                        other->ext.spectralSwordRdai.modeFlags = 3;
                        other->ext.spectralSwordRdai.angleToPlayer = angle;
                    }
                    break;
                case 3:
                    self->ext.spectralSwordRdai.attackTimer = 0x280;
                    other = self + 1;
                    miscTemp = 0x40;
                    for (i = 0; i < 6; i++, other++) {
                        if (other->flags & FLAG_DEAD) {
                            continue;
                        }
                        other->ext.spectralSwordRdai.modeFlags = 5;
                        other->ext.spectralSwordRdai.attackTimer = miscTemp;
                        miscTemp += 0x40;
                    }
                    break;
                }
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            xVar = 0x80 - self->posX.i.hi;
            yVar = 0x40 - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = rsin(angle) * 0x30;
            self->ext.spectralSwordRdai.playerSide ^= 1;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            xVar = self->posX.i.hi;
            if (self->ext.spectralSwordRdai.playerSide) {
                if (xVar > 0x80) {
                    self->velocityX = FIX(3.0);
                    self->step_s++;
                }
            } else {
                if (xVar < 0x80) {
                    self->velocityX = FIX(-3.0);
                    self->step_s++;
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            player = &PLAYER;
            xVar = player->posX.i.hi - self->posX.i.hi;
            if (self->ext.spectralSwordRdai.playerSide) {
                xVar = -xVar;
            }
            if (xVar > 0x70) {
                SetStep(6);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            for (other = self + 1, i = 0; i < 10; i++, other++) {
                other->flags |= FLAG_DEAD;
            }
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = 0;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            self->rotate -= 4;
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 3;
                }
            }
            if (self->posY.i.hi > 0x160) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 2:
            miscTemp = 0; // Count of how many spears/shields are animframe 0
            for (other = self + 1, i = 0; i < 10; i++, other++) {
                if (!other->animCurFrame) {
                    miscTemp++;
                }
            }
            if (miscTemp == 10) {
                for (other = self, i = 0; i < 11; i++, other++) {
                    DestroyEntity(other);
                }
                return;
            }
        }
        break;
    }
    if (!(self->flags & FLAG_DEAD)) {
        player = &PLAYER;
        xVar = player->posX.i.hi - self->posX.i.hi;
        yVar = player->posY.i.hi - self->posY.i.hi;
        angle = ratan2(yVar, xVar);
        dist = (xVar * xVar) + (yVar * yVar);
        dist = SquareRoot0(dist);
        other = self + 1;
        posOffset = -0x30;
        xVar = self->posX.val;
        yVar = self->posY.val;
        for (i = 0; i < 6; i++, other++) {
            posPtr = &other->ext.spectralSwordRdai.targetPos;
            posPtr->x.val = xVar + (posOffset * rcos(angle + ROT(90)) * 0x10);
            posPtr->y.val = yVar + (posOffset * rsin(angle + ROT(90)) * 0x10);
            posOffset += 0x10;
            if (posOffset == 0) {
                posOffset += 0x10;
            }
        }
        dist /= 2;
        if (dist < 0x20) {
            dist = 0x20;
        }
        if (dist > 0x48) {
            dist = 0x48;
        }
        xVar = xVar + (dist * rcos(angle) * 0x10);
        yVar = yVar + (dist * rsin(angle) * 0x10);
        posOffset = -(self->ext.spectralSwordRdai.shieldsAlive / 2) * 24;

        for (i = 0; i < 4; i++, other++) {
            if (!(other->flags & FLAG_DEAD)) {
                other->ext.spectralSwordRdai.angleToPlayer = angle;
                posPtr = &other->ext.spectralSwordRdai.targetPos;
                posPtr->x.val =
                    xVar + (posOffset * rcos(angle + ROT(90)) * 0x10);
                posPtr->y.val =
                    yVar + (posOffset * rsin(angle + ROT(90)) * 0x10);
                posOffset += 24;
            }
        }
        if (!(self->flags & 0xF)) {
            if (g_Timer & 1) {
                self->palette = 0x215;
            } else {
                self->palette = 0x216;
            }
        }
        if (!(g_Timer & 0xF)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_SPECTRAL_SWORD_AURA, self, other);
                other->ext.et_801CEB08.parent = self;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
    }
}

void EntitySpectralSwordAura(Entity* self) {
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitSpectralSwordAura);
        self->animCurFrame = 1;
#if defined(STAGE_IS_RDAI)
        self->palette += 14;
#else
        self->palette += 2;
#endif
        self->drawFlags |= ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
    }
    parent = self->ext.et_801CEB08.parent;
    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if (self->opacity < 0x20) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitSpear;

void EntityspectralSwordSpear(Entity* self) {
    s16 hitboxDist;
    s32 otherIdx;
    Entity* other;
    s32 dist;
    Entity* player;
    Pos* posPtr;
    s32 speed;
    s32 xVar;
    s32 yVar;
    u32 playerSide;
    s16 angle;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpear);
        self->drawFlags = ENTITY_ROTATE;
        if (self->params & 0x100) {
            self->animCurFrame = 4; // Double prong spear
        } else {
            self->animCurFrame = 5; // Single prong spear
        }
        SetStep(2);
        break;
    case 2:
        MoveEntity();
        posPtr = &self->ext.spectralSwordRdai.targetPos;
        xVar = posPtr->x.i.hi - self->posX.i.hi;
        yVar = posPtr->y.i.hi - self->posY.i.hi;
        dist = (xVar * xVar) + (yVar * yVar);
        dist = SquareRoot0(dist);
        speed = dist;
        if (speed > 0x38) {
            speed = 0x38;
        }
        angle = ratan2(yVar, xVar);
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        angle -= 0x400;
        StepTowards(&self->rotate, angle, 0x10);
        if (self->ext.spectralSwordRdai.modeFlags) {
            if (!(self->ext.spectralSwordRdai.modeFlags & 4) ||
                !--self->ext.spectralSwordRdai.attackTimer) {
                SetStep(4);
            }
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!(self->ext.spectralSwordRdai.modeFlags & 2)) {
                player = &PLAYER;
                angle = GetAngleBetweenEntities(self, player);
                self->ext.spectralSwordRdai.angleToPlayer = angle;
            }
            self->velocityX =
                rcos(self->ext.spectralSwordRdai.angleToPlayer - ROT(180)) << 5;
            self->velocityY =
                rsin(self->ext.spectralSwordRdai.angleToPlayer - ROT(180)) << 5;

            // This whole little block is weird. The ifdef is probably solvable.
            // There is some possibility that otherIdx is a fake, but hard to be
            // sure.
            otherIdx = self->params & 0xFF;
            otherIdx = (otherIdx * 4) / 6;
#ifdef VERSION_US
            other = self - (self->params & 0xFF) + (otherIdx + 6);
#else
            other = self - (self->params & 0xFF) + otherIdx + 6;
#endif
            if (self->ext.spectralSwordRdai.modeFlags & 2) {
                other->ext.spectralSwordRdai.modeFlags = 2;
            } else {
                other->ext.spectralSwordRdai.modeFlags = 1;
            }
            self->step_s++;
            break;
        case 1:
            MoveEntity();

            xVar = self->velocityX -= self->velocityX / 16;
            yVar = self->velocityY -= self->velocityY / 16;
            if ((abs(xVar) < 0x2000) && (abs(yVar) < 0x2000)) {
                self->step_s++;
            }
            angle = ratan2(yVar, xVar);
            angle -= ROT(90);
            StepTowards(&self->rotate, angle, 8);
            break;
        case 2:
            angle = self->ext.spectralSwordRdai.angleToPlayer;
            if (StepTowards(&self->rotate, angle - ROT(90), 0x20) != 0) {
                self->velocityX = rcos(angle) << 7;
                self->velocityY = rsin(angle) << 7;
                self->ext.spectralSwordRdai.timer = 0x30;
                PlaySfxPositional(SFX_WEAPON_SWISH_A);
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            playerSide = GetSideToPlayer();
            if (abs(self->velocityX) > abs(self->velocityY)) {
                playerSide &= 1;
                if (self->velocityX < 0) {
                    playerSide ^= 1;
                }
            } else {
                playerSide &= 2;
                if (self->velocityY < 0) {
                    playerSide ^= 2;
                }
            }
            if (playerSide || !--self->ext.spectralSwordRdai.timer) {
                self->ext.spectralSwordRdai.modeFlags = 0;
                SetStep(2);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            other = self - 1 - (self->params & 0xFF);
            other->ext.spectralSwordRdai.spearsAlive -= 1;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
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
    angle = self->rotate + ROT(90);
    // Double prong spear is 2 pixels longer. Excessive attention to detail.
    if (self->params & 0x100) {
        hitboxDist = 24;
    } else {
        hitboxDist = 22;
    }
    self->hitboxOffX = ((hitboxDist * rcos(angle)) >> 0xC);
    self->hitboxOffY = ((hitboxDist * rsin(angle)) >> 0xC);
}

static AnimateEntityFrame anim_shield_turnToFront[] = {
    {4, 8}, {4, 7}, {16, 6}, POSE_END};
static AnimateEntityFrame anim_shield_turnToFrontSlow[] = {
    {12, 8}, {12, 7}, {32, 6}, POSE_END};
static AnimateEntityFrame anim_shield_turnToSide[] = {
    {32, 6}, {16, 7}, {16, 8}, POSE_END};
extern EInit g_EInitShield;

void EntitySpectralSwordShield(Entity* self) {
    s32 anim_running;
    s16 angle;
    s32 dist;
    s32 yVar;
    Pos* posPtr;
    s32 speed;
    s32 xVar;
    Entity* other;

    if ((self->flags & FLAG_DEAD) && ((self->step) < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShield);
        self->animCurFrame = 7;
        self->zPriority += 2;
        SetStep(3);
        break;
    case 2:
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        xVar = GetDistanceToPlayerX();
        self->animCurFrame = 8;
        if (xVar < 0x40) {
            self->animCurFrame = 7;
        }
        if (xVar < 0x20) {
            self->animCurFrame = 6;
        }
        break;
    case 3:
        MoveEntity();
        if (self->animCurFrame != 8) {
            AnimateEntity(anim_shield_turnToSide, self);
        }
        posPtr = &self->ext.spectralSwordRdai.targetPos;
        xVar = posPtr->x.i.hi - self->posX.i.hi;
        yVar = posPtr->y.i.hi - self->posY.i.hi;
        dist = (xVar * xVar) + (yVar * yVar);
        dist = SquareRoot0(dist);
        speed = dist;
        if (speed > 0x38) {
            speed = 0x38;
        }
        angle = ratan2(yVar, xVar);
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        if (self->animCurFrame != 6) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        if (self->ext.spectralSwordRdai.modeFlags) {
            SetStep(4);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->velocityX =
                rcos(self->ext.spectralSwordRdai.angleToPlayer - ROT(180)) << 5;
            self->velocityY =
                rsin(self->ext.spectralSwordRdai.angleToPlayer - ROT(180)) << 5;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (self->ext.spectralSwordRdai.modeFlags & 2) {
                anim_running = AnimateEntity(anim_shield_turnToFrontSlow, self);
            } else {
                anim_running = AnimateEntity(anim_shield_turnToFront, self);
            }
            if (anim_running == 0) {
                self->ext.spectralSwordRdai.timer = 0x20;
                self->step_s += 1;
            }
            break;
        case 2:
            if (!--self->ext.spectralSwordRdai.timer) {
                self->ext.spectralSwordRdai.modeFlags = 0;
                SetStep(3);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            other = self - 7 - self->params;
            other->ext.spectralSwordRdai.shieldsAlive -= 1;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_METAL_CLANG_C);
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->step_s += 1;
                self->animCurFrame = 0;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
}
