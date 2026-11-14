// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo2.h"
#include "sfx.h"

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", EntityBreakable);

s16 _LimitAngleChange(s16 delta, s16 base, s16 target) {
    s16 diff;
    s16 ret;

    base &= 0xFFF;
    diff = target - base;
    ret = diff;

    if (diff > ROT(180)) {
        ret = diff - ROT(360);
    }

    if (diff < ROT(-180)) {
        ret = diff + ROT(360);
    }

    if (abs(ret) > delta) {
        if (diff < 0) {
            ret = base - delta;
        } else {
            ret = base + delta;
        }
        return ret;
    }

    return target;
}

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019B430);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_801CDC80);

extern u8 D_us_8018066C[];
extern u8 D_us_8018067C[];
extern u8 D_us_80180694[];
extern u8 D_us_801806A8[];
extern u8 D_us_801806B0[];
extern u8 D_us_801806B8[];
extern u8 D_us_801806D0[];
extern EInit g_EInitDeath1;
extern s32 g_BossMgrState;
void func_us_8019B430(void);

void func_us_8019B52C(Entity* self) {
    Entity* entity;
    Primitive* prim;
    s32 primIndex;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 count;
    s32 dist;

    if (self->flags & FLAG_DEAD) {
        if (self->step != 9) {
            SetStep(9);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDeath1);
        self->hitboxOffY = -5;
        self->hitboxState = 2;
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 3);
        if (primIndex == -1) {
            self->step = 0;
            break;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.deathBoss.prim = prim;
        while (prim != NULL) {
            prim->u0 = prim->v0 = 0;
            prim->priority = self->zPriority;
            prim->drawMode = DRAW_HIDE | DRAW_UNK02;
            prim = prim->next;
        }
        SetStep(1);
    case 1:
        AnimateEntity(D_us_8018066C, self, entity);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxState = 0;
        if (g_BossMgrState & BOSS_MGR_DEATH_FIGHT_ON) {
            self->hitboxState = 2;
            SetStep(2);
        }
        break;

    case 2:
        if (self->hitFlags & 3) {
            SetStep(8);
            break;
        }
        switch (self->step_s) {
        case 0:
            self->ext.deathBoss.timer = ((Random() & 3) << 5) + 0x20;
            entity = &PLAYER;
            posX = entity->posX.i.hi;
            posY = entity->posY.i.hi;
            if (self->posX.i.hi > entity->posX.i.hi) {
                posX -= 0x60;
            } else {
                posX += 0x60;
            }
            posY -= Random() & 0x3F;
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            prim = self->ext.deathBoss.prim;
            prim->x0 = posX;
            prim->y0 = posY;
            self->ext.deathBoss.angle = rand() & 0xFFF;
            self->ext.deathBoss.speed = FIX(1.75);
            self->step_s++;
        case 1:
            AnimateEntity(D_us_8018066C, self, entity);
            MoveEntity();
            prim = self->ext.deathBoss.prim;
            posX = prim->x0;
            posY = prim->y0;
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            angle = _LimitAngleChange(0x30, self->ext.deathBoss.angle, angle);
            self->velocityX = (self->ext.deathBoss.speed * rcos(angle)) >> 12;
            self->velocityY = (self->ext.deathBoss.speed * rsin(angle)) >> 12;
            self->ext.deathBoss.angle = angle;
            if (self->ext.deathBoss.speed > FIX(0.875)) {
                self->ext.deathBoss.speed -= self->ext.deathBoss.speed >> 4;
            }
            func_us_8019B430();
            if (!--self->ext.deathBoss.timer) {
                self->step_s--;
            }
            if (!self->ext.deathBoss.unk88) {
                if (self->hitPoints <
                    g_api.enemyDefs[ENEMY_DEATH].hitPoints -
                        g_api.enemyDefs[ENEMY_DEATH].hitPoints / 4) {
                    SetStep(3);
                }
            } else if (
                self->hitPoints < g_api.enemyDefs[ENEMY_DEATH].hitPoints / 2) {
                SetStep(4);
            }
            break;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_8018067C, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            entity = self + 1;
            CreateEntityFromEntity(E_ID(UNK_18), self, entity);
            entity->posX.i.hi -= 0x28;
            entity->posY.i.hi -= 0x1C;
            entity->params = 0;
            entity->zPriority = self->zPriority + 1;
            entity->ext.rbo2Ball.parent = self;
            entity = self + 2;
            CreateEntityFromEntity(E_ID(UNK_18), self, entity);
            entity->posX.i.hi += 0x28;
            entity->posY.i.hi -= 0x1C;
            entity->params = 1;
            entity->zPriority = self->zPriority + 1;
            entity->ext.rbo2Ball.parent = self;
            self->ext.deathBoss.timer = 0x80;
            self->step_s++;
        case 2:
            if (!(self->ext.deathBoss.timer & 0xF)) {
                PlaySfxPositional(SFX_RIC_SUC_REVIVE);
            }
            AnimateEntity(D_us_801806A8, self);
            if (!--self->ext.deathBoss.timer) {
                SetSubStep(3);
            }
            break;
        case 3:
            if (!AnimateEntity(D_us_80180694, self)) {
                PlaySfxPositional(SFX_DEATH_BALL_ATTACK);
                self->ext.deathBoss.unk88 = 1;
                self->step_s++;
            }
            break;
        case 4:
            if (!AnimateEntity(D_us_801806B0, self)) {
                SetStep(2);
            }
            break;
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->ext.deathBoss.unk89 = 1;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        case 1:
            if (!AnimateEntity(D_us_8018067C, self)) {
                PlaySfxPositional(SFX_DEATH_PAIN_A);
                SetSubStep(2);
            }
            break;
        case 2:
            AnimateEntity(D_us_801806A8, self);
            entity = self + 1;
            if (entity->ext.rbo2Ball.unk8A) {
                entity = self + 2;
                if (entity->ext.rbo2Ball.unk8A) {
                    self->ext.deathBoss.unk8B = 1;
                    SetStep(5);
                }
            }
            break;
        }
        break;

    case 5:
        AnimateEntity(D_us_801806A8, self);
        MoveEntity();
        self->ext.deathBoss.unk94 += ROT(5.625);
        self->velocityY = (rsin(self->ext.deathBoss.unk94) * FIX(0.75)) >> 12;
        if (self->posY.i.hi < 0x68) {
            self->velocityY += FIX(0.0625);
        } else {
            self->velocityY -= FIX(0.0625);
        }
        if (self->posX.i.hi < 0x80) {
            if (self->velocityX < FIX(0.875)) {
                self->velocityX += FIX(0.03125);
            }
        } else if (self->velocityX > FIX(-0.875)) {
            self->velocityX -= FIX(0.03125);
        }
        if (self->hitPoints < g_api.enemyDefs[ENEMY_DEATH].hitPoints / 3) {
            SetStep(6);
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            g_BossMgrState |= 4;
            self->step_s++;
        case 1:
            AnimateEntity(D_us_801806A8, self);
            entity = self + 1;
            if (entity->ext.rbo2Ball.unk8A) {
                entity = self + 2;
                if (entity->ext.rbo2Ball.unk8A) {
                    self->ext.deathBoss.unk8C = 1;
                    self->ext.deathBoss.timer = 0x40;
                    PlaySfxPositional(SFX_DEATH_SCYTHE_ATTACK);
                    self->step_s++;
                }
            }
            break;
        case 2:
            AnimateEntity(D_us_801806A8, self);
            if (!--self->ext.deathBoss.timer) {
                self->ext.deathBoss.unk94 = ROT(45);
                SetStep(7);
            }
            break;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_us_8018066C, self);
            entity = self + 1;
            if (entity->ext.rbo2Ball.unk8A) {
                entity = self + 2;
                if (entity->ext.rbo2Ball.unk8A) {
                    SetSubStep(1);
                }
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_801806B8, self)) {
                self->ext.deathBoss.unk8D = 1;
                self->ext.deathBoss.timer = 0x10;
                SetSubStep(2);
            }
            if (!self->poseTimer && self->pose == 4) {
                PlaySfxPositional(SFX_DEATH_ATTACK);
            }
            break;
        case 2:
            self->ext.deathBoss.unk8D = 0;
            if (!--self->ext.deathBoss.timer) {
                SetSubStep(0);
            }
            break;
        }
        MoveEntity();
        entity = &PLAYER;
        angle = self->ext.deathBoss.unk94;
        posX = entity->posX.i.hi + ((rcos(angle) * 0x60) >> 12);
        posY = entity->posY.i.hi - ((rsin(angle) * 0x60) >> 12);
        posX -= self->posX.i.hi;
        posY -= self->posY.i.hi;
        angle = ratan2(posY, posX);
        self->ext.deathBoss.speed = FIX(1.75);
        angle = _LimitAngleChange(0x30, self->ext.deathBoss.angle, angle);
        self->velocityX = (self->ext.deathBoss.speed * rcos(angle)) >> 12;
        self->velocityY = (self->ext.deathBoss.speed * rsin(angle)) >> 12;
        self->ext.deathBoss.angle = angle;
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX > 0x180) {
            self->ext.deathBoss.unk94 = ROT(135);
        }
        if (posX < 0x80) {
            self->ext.deathBoss.unk94 = ROT(45);
        }
        break;

    case 8:
        if (!self->step_s) {
            self->ext.deathBoss.timer = 0x40;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(4);
            } else {
                self->velocityX = FIX(-4);
            }
            self->velocityY = FIX(-4);
            if (Random() & 1) {
                PlaySfxPositional(SFX_DEATH_PAIN_B);
            } else {
                PlaySfxPositional(SFX_DEATH_PAIN_C);
            }
            posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            if (posX > 0x180) {
                self->velocityX = FIX(-7);
            }
            if (posX < 0x80) {
                self->velocityX = FIX(7);
            }
            self->step_s++;
        }
        AnimateEntity(D_us_801806D0, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 5;
        self->velocityY -= self->velocityY >> 5;
        self->velocityY += FIX(0.0625);
        if (!--self->ext.deathBoss.timer) {
            SetStep(2);
        }
        break;

    case 9:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            g_BossMgrState |= 8;
            prim = self->ext.deathBoss.prim;
            prim->x0 = 0x90;
            prim->y0 = 0x68;
            PlaySfxPositional(SFX_DEATH_YOURE_STRONG_INDEED);
            self->step_s++;
        case 1:
            AnimateEntity(D_us_8018066C, self);
            MoveEntity();
            prim = self->ext.deathBoss.prim;
            posX = prim->x0 - self->posX.i.hi;
            posY = prim->y0 - self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = rcos(angle) * 16;
            self->velocityY = rsin(angle) * 16;
            dist = SquareRoot0(posX * posX + posY * posY);
            if (dist < 8) {
                self->step_s++;
            }
            break;
        case 2:
            self->ext.deathBoss.unk90 = 0x40;
            self->ext.deathBoss.unk98 = 0;
            self->opacity = 0x80;
            self->drawFlags |= ENTITY_OPACITY;
            prim = self->ext.deathBoss.prim;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.deathBoss.unk90;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.deathBoss.unk90;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            prim->type = PRIM_G4;
            prim->x0 = prim->x2 = self->posX.i.hi;
            prim->x1 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = 0;
            prim->y2 = prim->y3 = 0x100;
            prim->r0 = prim->g0 = prim->b0 = self->ext.deathBoss.unk90;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = 0xC0;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            self->ext.deathBoss.timer = 0x20;
            PlaySfxPositional(SFX_TELEPORT_BANG_B);
            self->step_s++;
        case 3:
            prim = self->ext.deathBoss.prim;
            prim = prim->next;
            prim->x0 = prim->x2 -= 2;
            prim = prim->next;
            prim->x1 = prim->x3 += 2;
            posX = prim->x1 - self->posX.i.hi;
            if (posX == 0x30) {
                PlaySfxPositional(SFX_DEATH_BUT_NOW_YOU_WILL_DIE);
                self->step_s++;
            }
            break;
        case 4:
            count = 0;
            self->ext.deathBoss.unk98 += 4;
            posX = self->posX.i.hi - self->ext.deathBoss.unk98;
            if (posX < 0) {
                count++;
                posX = 0;
            }
            prim = self->ext.deathBoss.prim;
            prim->x0 = prim->x2 = posX;
            prim = prim->next;
            prim->x0 = prim->x2 = posX - 0x30;
            prim->x1 = prim->x3 = posX;
            posX = self->posX.i.hi + self->ext.deathBoss.unk98;
            if (posX > 0x100) {
                count++;
                posX = 0x100;
            }
            prim = self->ext.deathBoss.prim;
            prim->x1 = prim->x3 = posX;
            prim = prim->next;
            prim = prim->next;
            prim->x0 = prim->x2 = posX;
            prim->x1 = prim->x3 = posX + 0x30;
            if (self->opacity) {
                self->opacity -= 8;
            }
            if (self->ext.deathBoss.unk90 < 0xF0) {
                self->ext.deathBoss.unk90 += 8;
            }
            prim = self->ext.deathBoss.prim;
            prim->r0 = prim->g0 = prim->b0 = self->ext.deathBoss.unk90;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = 0;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = self->ext.deathBoss.unk90;
            LOW(prim->r3) = LOW(prim->r1);
            prim = prim->next;
            prim->r0 = prim->g0 = prim->b0 = self->ext.deathBoss.unk90;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = 0;
            LOW(prim->r3) = LOW(prim->r1);
            if (count == 2) {
                self->step_s++;
            }
            break;
        case 5:
            prim = self->ext.deathBoss.prim;
            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            entity = &g_Entities[96];
            CreateEntityFromEntity(E_ID(UNK_1B), self, entity);
            self->step_s++;
            break;
        case 6:
            self->animCurFrame = 0;
            break;
        }
        break;

    case 0xFF:
#include "../../st/pad2_anim_debug.h"
    }

    posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->velocityX < 0) {
        if (posX < 0x20) {
            self->posX.i.hi = 0x20 - g_Tilemap.scrollX.i.hi;
        }
    } else if (posX > 0x1E0) {
        self->posX.i.hi = 0x1E0 - g_Tilemap.scrollX.i.hi;
    }
    if (self->velocityY < 0) {
        if (posY < 0x50) {
            self->posY.i.hi = 0x50 - g_Tilemap.scrollY.i.hi;
        }
    } else if (posY > 0xE0) {
        self->posY.i.hi = 0xE0 - g_Tilemap.scrollY.i.hi;
    }
}

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019C718);

extern EInit D_us_801804AC;
extern u8 D_us_80180708[];
extern u8 D_us_80180718[];
extern u8 D_us_8018072C[];
extern u8 D_us_80180744[];
extern u8 D_us_8018075C[];
extern s32 g_BossMgrState;

void func_us_8019C924(Entity* self) {
    Entity* entity;
    s32 dx;
    s32 dy;
    s16 angle;
    s32 animDone;
    s32 dist;
    EnemyDef* enemyDef;

    FntPrint("ball_step %x\n", self->step);
    if (g_BossMgrState & 8) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_BIG;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804AC);
        self->hitboxState = 0;
        self->drawFlags = ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0x80;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        PlaySfxPositional(SFX_RAPID_SYNTH_BUBBLE_SHORT);
        // fallthrough
    case 1:
        if (!AnimateEntity(D_us_80180708, self)) {
            self->step++;
        }
        // fallthrough
    case 2:
        self->scaleX += 4;
        if (self->scaleX > 0x100) {
            self->hitboxState = 1;
            self->drawFlags = ENTITY_DEFAULT;
            SetStep(3);
        }
        self->scaleY = self->scaleX;
        break;

    case 3:
        AnimateEntity(D_us_80180718, self);
        entity = self->ext.rbo2Ball.parent;
        if (entity->ext.rbo2Ball.unk88) {
            self->ext.rbo2Ball.angle = ROT(90);
            SetStep(4);
        }
        break;

    case 4:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        entity = &PLAYER;
        dx = entity->posX.i.hi;
        dy = entity->posY.i.hi;
        dx += (Random() & 0x3F) - 0x20;
        dy += (Random() & 0x3F) - 0x20;
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        angle = LimitAngleChange(0x40, self->ext.rbo2Ball.angle, angle);
        self->velocityX = (rcos(angle) * FIX(0.4375)) >> 12;
        self->velocityY = (rsin(angle) * FIX(0.4375)) >> 12;
        self->ext.rbo2Ball.angle = angle;
        entity = self->ext.rbo2Ball.parent;
        if (entity->ext.rbo2Ball.unk89) {
            SetStep(5);
        }
        break;

    case 5:
        AnimateEntity(D_us_80180718, self);
        MoveEntity();
        entity = self->ext.rbo2Ball.parent;
        if (!self->params) {
            dx = entity->posX.i.hi - 0x20;
        } else {
            dx = entity->posX.i.hi + 0x20;
        }
        dy = entity->posY.i.hi - 0x1C;
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
        self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
        dist = SquareRoot0(dx * dx + dy * dy);
        if (dist < 4) {
            self->ext.rbo2Ball.unk8A = 1;
            self->step++;
        }
        break;

    case 6:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8B) {
                self->ext.rbo2Ball.unk8A = 0;
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(D_us_8018072C, self)) {
                SetStep(7);
            }
            break;
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[176], &g_Entities[184]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_ID(UNK_19), self, entity);
                entity->ext.rbo2Ball.parent = self;
                if (!self->params) {
                    entity->ext.rbo2Ball.unkA0 = self + 1;
                } else {
                    entity->ext.rbo2Ball.unkA0 = self - 1;
                }
                entity->facingLeft = self->params;
                entity->zPriority = self->zPriority + 1;
                self->ext.rbo2Ball.unk8C = 0;
                PlaySfxPositional(SFX_LOW_SYNTH_BUBBLES);
                self->step_s++;
            }
            break;
        case 1:
            self->ext.rbo2Ball.timer = 0x60;
            self->step_s++;
            break;
        case 2:
            if (!--self->ext.rbo2Ball.timer) {
                self->step_s = 0;
            }
            break;
        }
        if (g_Timer & 1) {
            self->animCurFrame = 0x39;
        } else {
            self->animCurFrame = 0;
        }
        MoveEntity();
        entity = self->ext.rbo2Ball.parent;
        dy = entity->posY.i.hi - 0x1C;
        if (!self->params) {
            dx = entity->posX.i.hi - 0x50;
        } else {
            dx = entity->posX.i.hi + 0x50;
        }
        dx -= self->posX.i.hi;
        dy -= self->posY.i.hi;
        angle = ratan2(dy, dx);
        self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
        self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
        dist = SquareRoot0(dx * dx + dy * dy);
        if (dist < 3) {
            self->velocityX = 0;
            self->velocityY = 0;
        }
        if (g_BossMgrState & 4) {
            SetStep(8);
        }
        break;

    case 8:
        switch (self->step_s) {
        case 0:
            animDone = AnimateEntity(D_us_80180744, self);
            MoveEntity();
            entity = self->ext.rbo2Ball.parent;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dy = entity->posY.i.hi - 0x1C;
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->velocityX = (rcos(angle) * FIX(1.75)) >> 12;
            self->velocityY = (rsin(angle) * FIX(1.75)) >> 12;
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist < 4 && !animDone) {
                self->ext.rbo2Ball.unk8A = 1;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(D_us_80180718, self);
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8C) {
                self->facingLeft = self->params;
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_8018075C, self)) {
                enemyDef = &g_api.enemyDefs[ENEMY_DEATH_UNK_168];
                self->attackElement = enemyDef->attackElement;
                self->attack = enemyDef->attack;
                self->hitboxWidth = enemyDef->hitboxWidth;
                self->hitboxHeight = enemyDef->hitboxHeight;
                self->hitboxState = 1;
                self->blendMode = BLEND_NO;
                self->drawFlags = ENTITY_ROTATE;
                SetStep(9);
            }
            break;
        }
        break;

    case 9:
        switch (self->step_s) {
        case 0:
            self->ext.rbo2Ball.unk8A = 1;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.rbo2Ball.parent;
            dy = entity->posY.i.hi - 0x10;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->velocityX = (rcos(angle) * FIX(0.875)) >> 12;
            self->velocityY = (rsin(angle) * FIX(0.875)) >> 12;
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist < 3) {
                self->velocityX = 0;
                self->velocityY = 0;
            }
            entity = self->ext.rbo2Ball.parent;
            if (entity->ext.rbo2Ball.unk8D) {
                self->ext.rbo2Ball.unk8A = 0;
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            dx = entity->posX.i.hi - self->posX.i.hi;
            dy = entity->posY.i.hi - self->posY.i.hi;
            angle = ratan2(dy, dx);
            self->ext.rbo2Ball.angle = angle;
            self->ext.rbo2Ball.speed = FIX(6);
            self->step_s++;
            // fallthrough
        case 3:
            MoveEntity();
            self->rotate -= ROT(22.5);
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            angle = self->ext.rbo2Ball.angle;
            self->velocityX = (self->ext.rbo2Ball.speed * rcos(angle)) >> 12;
            self->velocityY = (self->ext.rbo2Ball.speed * rsin(angle)) >> 12;
            self->ext.rbo2Ball.speed -= self->ext.rbo2Ball.speed >> 4;
            if (self->ext.rbo2Ball.speed < FIX(0.25)) {
                self->ext.rbo2Ball.timer = 0x20;
                self->step_s++;
            }
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[208], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_ID(UNK_1A), self, entity);
                    entity->params = self->animCurFrame;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = self->rotate;
                }
            }
            break;
        case 4:
            self->rotate -= ROT(45);
            self->rotate &= 0xFFF;
            if (!(self->rotate & 0xF00)) {
                PlaySfxPositional(SFX_DEATH_SCYTHE_SWISH);
            }
            if (!--self->ext.rbo2Ball.timer) {
                self->step_s++;
            }
            break;
        case 5:
            MoveEntity();
            func_801CDC80(&self->rotate, 0, 0x40);
            entity = self->ext.rbo2Ball.parent;
            dy = entity->posY.i.hi - 0x10;
            if (!self->params) {
                dx = entity->posX.i.hi - 0x20;
            } else {
                dx = entity->posX.i.hi + 0x20;
            }
            dx -= self->posX.i.hi;
            dy -= self->posY.i.hi;
            angle = ratan2(dy, dx);
            dist = SquareRoot0(dx * dx + dy * dy);
            if (dist > 0x20) {
                angle = LimitAngleChange(0x60, self->ext.rbo2Ball.angle, angle);
            }
            self->velocityX = (rcos(angle) * FIX(3)) >> 12;
            self->velocityY = (rsin(angle) * FIX(3)) >> 12;
            self->ext.rbo2Ball.angle = angle;
            if (dist < 8) {
                self->step_s = 0;
            }
            break;
        }
        break;
    }
}

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019D4CC);

INCLUDE_ASM("boss/rbo2/nonmatchings/unk_1B284", func_us_8019D950);
