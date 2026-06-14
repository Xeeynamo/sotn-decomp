// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

// Tail animations
static u8 animTail0[] = {
    6,  31, 6,  36, 6,  37, 6,  38, 6,  39, 6,  50, 6,  51, 6,
    52, 6,  51, 6,  50, 6,  39, 6,  38, 6,  37, 6,  36, 0,  0,
};
static u8 animTail1[] = {
    8, 30, 8, 46, 8, 47, 8, 48, 40, 49, 8, 30, 16, 24, -1, 0,
};
static u8 animTail2[] = {
    8, 30, 8, 46, 2, 32, 2, 33, 2, 34, 2, 33, 2,  32, 2,  33,
    3, 34, 3, 33, 3, 32, 3, 33, 4, 34, 5, 33, 32, 32, -1, 0,
};
static u8 animTail3[] = {
    4,  25, 4,  24, 4,  23, 8,  40, 8,  41, 20, 42, 1,  23, 1,  24, 1,
    25, 1,  26, 2,  43, 2,  44, 2,  45, 5,  27, 5,  28, 22, 29, 0,  0,
};
static u8 animTail4[] = {6, 19, 6, 20, 6, 21, 6, 20, 0, 0};

// Fireball animations
static u8 animFire0[] = {
    2, 2, 2, 3, 2, 4, 2, 5, 2, 6, 2, 7, 2, 6, 2, 5, 2, 4, 2, 3, 0, 0,
};
static u8 animFire1[] = {
    2, 2, 2, 3,  2, 4,  2, 5,  2, 6,  2, 7,  2,  8,
    2, 9, 2, 10, 2, 11, 2, 12, 2, 13, 2, 14, -1, 0,
};
static u8 animFire2[] = {
    1,  0,  0, 31, 31, 2,  32, 0, 31, 31, 2,  64, 0, 31, 31, 2,  96, 0,
    31, 31, 2, 0,  32, 31, 31, 2, 32, 32, 31, 15, 2, 32, 48, 31, 15, 0,
};

void EntityDiplocephalusFireball(Entity* self) {
    Entity* player;
    Primitive* prim;
    s16 angle;
    s32 primIndex;
    s32 speed;

    FntPrint("tama_step %x\n", self->step);
    if ((self->flags & FLAG_DEAD) && self->step < 4) {
        PlaySfxPositional(SFX_EXPLODE_FAST_A);
        self->hitboxState = 0;
        SetStep(4);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalusFireball);
        self->drawFlags |= ENTITY_ROTATE | ENTITY_SCALEX | ENTITY_SCALEY;
        self->scaleX = self->scaleY = 0x60;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.diploFireball.unk90 = prim;

        while (prim != NULL) {
            prim->tpage = 26;
            prim->clut = PAL_UNK_170;
            PGREY(prim, 0) = 64;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            prim->p3 = 0;
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        self->velocityY = 0;
        self->ext.diploFireball.unk9C = 2;
        /* Fallthrough */
    case 1:
        MoveEntity();
        AnimateEntity(animFire0, self);
        self->rotate += ROT(5.625);
        self->scaleX += 16;
        if (self->scaleX > 256) {
            self->scaleX = 256;
        }
        self->scaleY = self->scaleX;
        MoveEntity();
        self->velocityX -= self->velocityX / 8;
        if (abs(self->velocityX) < FIX(0.25)) {
            if (self->facingLeft) {
                self->ext.diploFireball.angle = ROT(0);
            } else {
                self->ext.diploFireball.angle = ROT(180);
            }
            self->ext.diploFireball.speed = 0;
            self->step++;
        }
        break;

    case 2:
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        angle = GetNormalizedAngle(16, self->ext.diploFireball.angle, angle);
        speed = self->ext.diploFireball.speed;
        speed += FLT(0.75);
        if (speed > FLT(48)) {
            speed = FLT(48);
            self->step++;
        }
        self->velocityX = FLT_TO_I(speed * rcos(angle));
        self->velocityY = FLT_TO_I(speed * rsin(angle));
        self->ext.diploFireball.speed = speed;
        self->ext.diploFireball.angle = angle;
        AnimateEntity(animFire0, self);
        MoveEntity();
        break;

    case 3:
        AnimateEntity(animFire0, self);
        MoveEntity();
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            prim = self->ext.diploFireball.unk90;
            while (prim != NULL) {
                prim->p3 = 0;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->velocityX >>= 1;
            self->velocityY >>= 1;
            self->drawFlags = ENTITY_DEFAULT;
            self->step_s++;
            self->flags = ~0xF;
            self->palette = 0x2C0;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->posY.val -= FIX(1.0);
            if (!AnimateEntity(animFire1, self)) {
                DestroyEntity(self);
                return;
            }
            break;
        }
        break;
    }

    if ((g_Timer & 1) && !(self->flags & FLAG_DEAD)) {
        prim = self->ext.diploFireball.unk90;
        prim = FindFirstUnkPrim(prim);
        if (prim != NULL) {
            prim->p3 = 3;
            prim->x0 = prim->x2 = self->posX.i.hi - 12;
            prim->x1 = prim->x3 = prim->x0 + 28;
            prim->y0 = prim->y1 = self->posY.i.hi - 12;
            prim->y2 = prim->y3 = prim->y0 + 28;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim->p1 = 0;
            prim->p2 = 0;
        }
    }

    prim = self->ext.diploFireball.unk90;
    while (prim != NULL) {
        if (prim->p3 && !UpdateAnimation(animFire2, prim)) {
            prim->p3 = 0;
            prim->drawMode = DRAW_HIDE;
        }
        prim = prim->next;
    }
}

void EntityDiplocephalusTail(Entity* self) {
    s16 unused;
    s16 temp_s5;
    u8 three;
    s16 temp_a2;
    s16 temp_s6;
    s32 dVel;
    s32 dx, dy;
    s32 i;
    Entity* prevPart;
    Entity* part;

#define tailTip self->ext.diploTail.tip
#define prevTailPart ext.diploTail.prevPart
#define nextTailPart ext.diploTail.nextPart

    if (self->prevTailPart == NULL) {
        FntPrint("stail_step %x\n", self->step);
    }
    if (self->nextTailPart == NULL) {
        FntPrint("tail_step %x\n", self->step);
    }
    if (self->nextTailPart == NULL) {
        self->ext.diploTail.diplo->ext.diplo.hitParams = self->hitParams;
    } else if (self->hitboxState) {
        self->hitboxState = 0;
        if (self->prevTailPart != NULL) {
            (self - 1)->hitboxState = 1;
        } else {
            (self + 5)->hitboxState = 1;
        }
    }
    if ((self->ext.diploTail.diplo->entityId != E_DIPLOCEPHALUS) &&
        self->prevTailPart == NULL && self->step < 8) {
        self->step = 8;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitDiplocephalusTail);
        self->hitboxState = 1;
        self->drawFlags = ENTITY_ROTATE;
        self->ext.diploTail.angle = ROT(0);
        self->ext.diploTail.unk9C = 0;
        self->ext.diploTail.unk9D = 0;
        self->prevTailPart = NULL;
        prevPart = self;
        part = self;
        for (i = 0; i < 6; i++) {
            part++;
            CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_TAIL, part);
            part->prevTailPart = part - 1;
            (part - 1)->nextTailPart = part;
            part->step = 3;
            part->animSet = self->animSet;
            part->animCurFrame = 19;
            part->facingLeft = self->ext.diploTail.diplo->facingLeft ^ 1;
            part->zPriority = self->ext.diploTail.diplo->zPriority - i - 1;
            part->attackElement = self->attackElement;
            part->attack = self->attack;
            part->hitPoints = self->hitPoints;
            part->enemyId = self->enemyId;
            part->hitboxState = 0;
            part->hitboxWidth = self->hitboxWidth;
            part->hitboxHeight = self->hitboxHeight;
            part->flags = self->flags;
            part->unk5A = self->unk5A;
            part->palette = self->palette;
            part->ext.diploTail.diplo = self->ext.diploTail.diplo;
            part->drawFlags = ENTITY_ROTATE;
            prevPart = part;
            part->nextPart = part + 1;
        }
        part->nextPart = NULL;
        (part - 1)->ext.diploTail.unk9F = 1;
        part->hitboxState = 3;
        part->hitboxWidth = 8;
        part->hitboxHeight = 13;
        part->hitboxOffY = -8;
        part->nextTailPart = NULL;
        part->flags |= FLAG_UNK_20000000;
        tailTip = part;
        tailTip->animCurFrame = 23;
        tailTip->zPriority = self->zPriority;
        tailTip->step = 5;
        tailTip->drawFlags = ENTITY_DEFAULT;
        tailTip->ext.diploTail.angle = ROT(112.5);
        tailTip->prevTailPart->animCurFrame = 22;
        /* fallthrough */
    case 1:
        if (self->facingLeft) {
            self->posX.val = self->ext.diploTail.diplo->posX.val - FIX(29);
        } else {
            self->posX.val = self->ext.diploTail.diplo->posX.val + FIX(29);
        }
        self->posY.val = self->ext.diploTail.diplo->posY.val;
        dVel = self->velocityY - self->ext.diploTail.velocityY;

        if (dVel > 0) {
            self->ext.diploTail.angle += 0x10;
        }
        if (dVel < 0) {
            self->ext.diploTail.angle -= 0x10;
        }
        if (self->ext.diploTail.angle > ROT(0)) {
            self->ext.diploTail.angle -= 8;
        }
        if (self->ext.diploTail.angle < ROT(0)) {
            self->ext.diploTail.angle += 8;
        }
        if (self->ext.diploTail.angle > ROT(22.5)) {
            self->ext.diploTail.angle = ROT(22.5);
        }
        if (self->ext.diploTail.angle < ROT(-22.5)) {
            self->ext.diploTail.angle = ROT(-22.5);
        }
        dVel = self->velocityX - self->ext.diploTail.velocityX;
        if (self->facingLeft ^ 1) {
            dVel = -dVel;
        }
        if (dVel > 0) {
            tailTip->ext.diploTail.angle += 0x10;
        }
        if (dVel < 0) {
            tailTip->ext.diploTail.angle -= 0x10;
        }
        if (tailTip->ext.diploTail.angle > ROT(112.5)) {
            tailTip->ext.diploTail.angle -= 8;
        }
        if (tailTip->ext.diploTail.angle < ROT(112.5)) {
            tailTip->ext.diploTail.angle += 8;
        }
        if (tailTip->ext.diploTail.angle > ROT(157.5)) {
            tailTip->ext.diploTail.angle = ROT(157.5);
        }
        if (tailTip->ext.diploTail.angle < ROT(67.5)) {
            tailTip->ext.diploTail.angle = ROT(67.5);
        }
        three = 3;
        temp_a2 = tailTip->ext.diploTail.angle - self->ext.diploTail.angle;
        temp_s5 = (temp_a2 - self->ext.diploTail.angle) / three;
        temp_s6 = (tailTip->ext.diploTail.angle - temp_a2) / (6 - three);
        unused = (tailTip->ext.diploTail.angle - self->ext.diploTail.angle) / 6;

        part = self;
        i = 0;
        while (!(three < i)) {
            part->ext.diploTail.angle = self->ext.diploTail.angle + temp_s5 * i;
            dx = (rcos(part->ext.diploTail.angle) << 3) << 4;
            dy = (rsin(part->ext.diploTail.angle) << 3) << 4;
            if (self->facingLeft) {
                part->nextTailPart->posX.val = part->posX.val - dx;
            } else {
                part->nextTailPart->posX.val = part->posX.val + dx;
            }
            part->nextTailPart->posY.val = part->posY.val - dy;
            i++;
            part->rotate = -part->ext.diploTail.angle;
            part = part->nextTailPart;
        }
        i = 0;
        while (part->nextTailPart != NULL) {
            part->ext.diploTail.angle = temp_a2 + temp_s6 * i;
            dx = (rcos(part->ext.diploTail.angle) << 3) << 4;
            dy = (rsin(part->ext.diploTail.angle) << 3) << 4;
            if (self->facingLeft) {
                part->nextTailPart->posX.val = part->posX.val - dx;
            } else {
                part->nextTailPart->posX.val = part->posX.val + dx;
            }
            part->nextTailPart->posY.val = part->posY.val - dy;
            i++;
            part->rotate = -part->ext.diploTail.angle;
            part = part->nextTailPart;
        }
        tailTip->posX.i.hi += 1;
        tailTip->posY.i.hi -= 2;
        self->ext.diploTail.velocityY = self->ext.diploTail.diplo->velocityY;
        self->ext.diploTail.velocityX = self->ext.diploTail.diplo->velocityX;
        self->ext.diploTail.unk9C++;
        if (self->ext.diploTail.unk9C > 0x20) {
            part = self->nextTailPart;
            for (i = 0; i < self->ext.diploTail.unk9D; i++) {
                part = part->nextTailPart;
            }
            part->poseTimer = 0;
            part->pose = 0;
            part->step = 4;
            self->ext.diploTail.unk9C = 0;
            self->ext.diploTail.unk9D++;
        }
        if (self->ext.diploTail.unk9D > 3) {
            self->ext.diploTail.unk9D = 0;
        }
        break;

    case 4:
        if (!AnimateEntity(animTail4, self)) {
            self->poseTimer = 0;
            self->pose = 0;
            self->step = 3;
        }
        break;

    case 5:
        AnimateEntity(animTail0, self);
        if (self->ext.diploTail.diplo->ext.diplo.hitParams2 != 0) {
            PlaySfxPositional(SFX_DIPLOCEPHALUS_PAIN);
            self->poseTimer = 0;
            self->pose = 0;
            self->step = 6;
        } else if ((Random() & 0x7F) == 0) {
            self->poseTimer = 0;
            self->pose = 0;
            self->params = 1;
            self->step = 11;
        }
        break;

    case 6:
        if (!AnimateEntity(animTail1, self)) {
            self->poseTimer = 0;
            self->pose = 0;
            self->step--;
        }
        break;

    case 7:
        if (!AnimateEntity(animTail2, self)) {
            part = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (part != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, part);
                part->params = 3;
                part->zPriority = self->zPriority + 9;
            }
            g_api.func_80102CD8(1);
            EntityExplosionSpawn(0, 0);
        }
        break;

    case 8:
        self->ext.diploTail.unk9D = 1;
        self->ext.diploTail.unk9C = 0;
        tailTip->step = 7;
        tailTip->flags &= ~FLAG_UNK_20000000;
        PlaySfxPositional(SFX_DIPLOCEPHALUS_DEATH);
        part = self;
        while (part->nextTailPart != NULL) {
            part->hitboxState = 0;
            part++;
        }
        tailTip->hitboxState = 0;
        PlaySfxPositional(SFX_STUTTER_EXPLODE_B);
        self->step++;
        break;

    case 9:
        if (tailTip->nextTailPart != NULL ||
            tailTip->entityId != E_DIPLOCEPHALUS_TAIL) {
            if (self->ext.diploTail.unk9C++ > 6) {
                self->ext.diploTail.unk9D++;
                self->ext.diploTail.unk9C = 0;
                tailTip--;
                part = tailTip;
                part->step = 10;
            }
        }
        break;

    case 10:
        self->posY.val += FIX(0.25);
        PlaySfxPositional(SFX_EXPLODE_FAST_A);
        EntityExplosionSpawn(0, 0);
        break;

    case 11:
        if (!AnimateEntity(animTail3, self)) {
            self->poseTimer = 0;
            self->pose = 0;
            self->step = 5;
            return;
        }
        if (self->pose == 8 && self->params) {
            PlaySfxPositional(SFX_DIPLOCEPHALUS_ATTACK);
            part = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (part != NULL) {
                PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
                CreateEntityFromCurrentEntity(E_DIPLOCEPHALUS_FIREBALL, part);
                part->facingLeft = self->facingLeft;
                if (self->facingLeft) {
                    part->posX.i.hi += 12;
                } else {
                    part->posX.i.hi -= 12;
                }
                part->posY.i.hi -= 16;
                self->params = 0;
            }
        }
        break;
    }
}
