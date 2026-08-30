// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno4/rno4.h"

static Primitive* SetupPrimsForEntitySpriteParts(
    Entity* entity, Primitive* prim) {
    s16 y;
    s32 spritePartCount;
    s16 x;
    u8 spriteU0;
    u8 spriteV0;
    s16* spriteData;
    s32 i;
    u8 spriteU1;
    s16 spriteDestX;
    s16 spriteDestY;
    s16 spriteDestW;
    s16 spriteDestH;
    s16 spriteFlags;
    u8 spriteV1;
    s32 xFlip;

    spriteData = g_VenusWeedSpriteParts[entity->animCurFrame];
    spritePartCount = *spriteData;
    spriteData++;

    for (i = 0; i < spritePartCount; i++, spriteData += 11) {
        spriteFlags = spriteData[0];
        spriteDestX = spriteData[1];
        spriteDestY = spriteData[2];
        spriteDestW = spriteData[3];
        spriteDestH = spriteData[4];

        if (spriteFlags & 4) {
            spriteDestW -= 1;
            if (spriteFlags & 2) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 8) {
            spriteDestH -= 1;
            if (spriteFlags & 1) {
                spriteDestY += 1;
            }
        }
        if (spriteFlags & 0x10) {
            spriteDestW -= 1;
            if (!(spriteFlags & 2)) {
                spriteDestX += 1;
            }
        }
        if (spriteFlags & 0x20) {
            spriteDestH -= 1;
            if (!(spriteFlags & 1)) {
                spriteDestY += 1;
            }
        }

        x = entity->posX.i.hi;
        y = entity->posY.i.hi;
        if (entity->facingLeft) {
            x -= spriteDestX;
        } else {
            x += spriteDestX;
        }
        y += spriteDestY;

        if (entity->facingLeft) {
            LOH(prim->x0) = x - spriteDestW + 1;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + 1;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x - spriteDestW + 1;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + 1;
            LOH(prim->y3) = y + spriteDestH;
        } else {
            LOH(prim->x0) = x;
            LOH(prim->y0) = y;
            LOH(prim->x1) = x + spriteDestW;
            LOH(prim->y1) = y;
            LOH(prim->x2) = x;
            LOH(prim->y2) = y + spriteDestH;
            LOH(prim->x3) = x + spriteDestW;
            LOH(prim->y3) = y + spriteDestH;
        }

        prim->clut = entity->palette + spriteData[5];
        spriteU0 = spriteData[7];
        spriteV0 = spriteData[8];
        spriteU1 = spriteData[9];
        spriteV1 = spriteData[10];

        if (spriteFlags & 4) {
            spriteU1--;
        }
        if (spriteFlags & 8) {
            spriteV1--;
        }
        if (spriteFlags & 0x10) {
            spriteU0++;
        }
        if (spriteFlags & 0x20) {
            spriteV0++;
        }

        xFlip = (spriteFlags & 2) ^ entity->facingLeft;
        if (!xFlip) {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU0;
                prim->v0 = spriteV0;
                prim->u1 = spriteU1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU0;
                prim->v2 = spriteV1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU0;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU0;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU1;
                prim->v3 = spriteV0 - 1;
            }
        } else {
            if (!(spriteFlags & 1)) {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV0;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV0;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV1;
            } else {
                prim->u0 = spriteU1 - 1;
                prim->v0 = spriteV1 - 1;
                prim->u1 = spriteU0 - 1;
                prim->v1 = spriteV1 - 1;
                prim->u2 = spriteU1 - 1;
                prim->v2 = spriteV0 - 1;
                prim->u3 = spriteU0 - 1;
                prim->v3 = spriteV0 - 1;
            }
        }

        prim->tpage = 0x14;
        prim->priority = entity->zPriority + 1;
        prim = prim->next;
    }
    return prim;
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/e_blue_venus_weed", EntityVenusWeed);

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/e_blue_venus_weed", EntityVenusWeedFlower);

void EntityVenusWeedTendril(Entity* self) {
    extern s8 g_VenusWeedTendrilHitboxData[];

    const int InitDistMinX = 0x18;
    const int InitDistRandRangeX = 0x1F;
    const int SpikeSfxpose = 0xA;
    s32 x;
    Entity* entity;
    s8* hitboxData;
    u32 hitboxIndex;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBlueVenusWeedTendril);
        self->animCurFrame = 0;
        break;

    case 1:
        if (UnkCollisionFunc3(g_VenusWeedTendrilPhysicsSensors) & 1) {
            SetStep(2);
        }
        break;

    case 2:
        if (!self->step_s) {
            x = self->params * 0x20 - 0x70;
            if (x > 0) {
                x += InitDistMinX;
            } else {
                x -= InitDistMinX;
            }
            x += (Random() & (InitDistRandRangeX * 2 + 1)) - InitDistRandRangeX;
            self->ext.venusWeedTendril.targetX = x;
            self->step_s++;
        }

        AnimateEntity(g_VenusWeedTendrilBounceAnim, self);
        UnkCollisionFunc2(g_VenusWeedTendrilWalkSensors);
        entity = &PLAYER;
        x = entity->posX.i.hi - self->posX.i.hi;
        if (abs(x) > 24) {
            entity = self - 1 - self->params;
            x = entity->posX.i.hi + self->ext.venusWeedTendril.targetX;
            x -= self->posX.i.hi;
        }

        if (abs(x) < 2) {
            SetStep(5);
        } else if (x > 0) {
            self->velocityX = abs(x) << 0xC;
        } else {
            self->velocityX = -(abs(x) << 0xC);
        }

        if (self->ext.venusWeedTendril.unk93) {
            self->ext.venusWeedTendril.unk93 = 0;
            entity = self - 1 - self->params;
            entity->ext.venusWeedTendril.unk93++;
            SetStep(3);
        }
        break;

    case 5:
        if (AnimateEntity(g_VenusWeedTendrilRecoverAnim, self) == 0) {
            SetStep(3);
            self->step_s = 1;
            self->pose = 8;
        }
        break;

    case 3:
        switch (self->step_s) {
        case 0:
            AnimateEntity(g_VenusWeedTendrilBounceAnim, self);
            if (self->ext.venusWeedTendril.spikeStartTimeOffsetIndex) {
                self->ext.venusWeedTendril.spikeStartTimeOffsetIndex = 0;
                SetSubStep(1);
            }
            break;

        case 1:
            if (AnimateEntity(g_VenusWeedTendrilChargeAnim, self) == 0) {
                SetSubStep(2);
            }
            if (!self->poseTimer && self->pose == SpikeSfxpose) {
                PlaySfxPositional(SFX_VENUS_WEED_CHARGE_ATTACK);
            }
            break;

        case 2:
            if (AnimateEntity(g_VenusWeedTendrilLaunchAnim, self) == 0) {
                SetStep(2);
            }
            break;
        }

        if (self->hitFlags & 0x80) {
            entity = self - 1 - self->params;
            entity->ext.venusWeedFlower.clutOffset++;
        }
        break;

    case 8:
        if (!self->step_s) {
            self->ext.venusWeedTendril.timer = self->params * 8 + 1;
            self->step_s++;
        }
        if (!--self->ext.venusWeedTendril.timer) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 2;
                entity->posY.i.hi -= 0xC;
            }
            PlaySfxPositional(SFX_EXPLODE_B);
            DestroyEntity(self);
            return;
        }
        break;
    }

    hitboxData = g_VenusWeedTendrilHitboxData;
    hitboxIndex = g_VenusWeedTendrilHitboxIndices[self->animCurFrame - 0x22];
    hitboxData += hitboxIndex * 4;
    self->hitboxOffX = (s8)*hitboxData++;
    self->hitboxOffY = (s8)*hitboxData++;
    self->hitboxWidth = *hitboxData++;
    self->hitboxHeight = *hitboxData++;
}

void EntityVenusWeedDart(Entity* self) {
    const int AnimFrameIndexInit = 0x37;
    const int StartSpeed = 0x8000;
    const int SpeedMax = 0x60000;
    const int AccelInc = 0x800;
    const int AccelMax = 0x10000;
    const int ClutIdxWallHit = 0x20;
    const int ClutIdxPlayerHit = 0;
    const int ClutIdxMax = 0x30;
    const int DartClutStart = 0x234;
    const int PlantClutMax = 0x243;

    typedef enum Step {
        INIT = 0,
        FLY = 1,
        DECAY = 2,
        DEATH = 3,
    } Step;

    Collider collider;
    Entity* entity;
    s16 rot;
    s32 x;
    s32 speed;
    s32 y;

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBlueVenusWeedDart);
        self->animCurFrame = AnimFrameIndexInit;
        self->drawFlags = ENTITY_ROTATE;
        rot = self->rotate;
        self->hitboxOffX = (rcos(rot) * 6) >> 0xC;
        self->hitboxOffY = (rsin(rot) * 6) >> 0xC;
        self->ext.venusWeedDart.nextPosDeltaX = rcos(rot) << 3 >> 0xC;
        self->ext.venusWeedDart.nextPosDeltaY = rsin(rot) << 3 >> 0xC;
        self->ext.venusWeedDart.speed = StartSpeed;
        /* fall through */

    case FLY:
        MoveEntity();

        rot = self->rotate;
        speed = self->ext.venusWeedDart.speed;
        self->velocityX = (speed * rcos(rot)) >> 0xC;
        self->velocityY = (speed * rsin(rot)) >> 0xC;
        self->ext.venusWeedDart.speed += self->ext.venusWeedDart.accel;
        self->ext.venusWeedDart.accel += (self->params + 1) * AccelInc;
        if (self->ext.venusWeedDart.accel > AccelMax) {
            self->ext.venusWeedDart.accel = AccelMax;
        }
        if (self->ext.venusWeedDart.speed > SpeedMax) {
            self->ext.venusWeedDart.speed = SpeedMax;
        }

        x = self->posX.i.hi + self->ext.venusWeedDart.nextPosDeltaX;
        y = self->posY.i.hi + self->ext.venusWeedDart.nextPosDeltaY;
        g_api.CheckCollision(x, y, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_STOMP_HARD_E);
            if (self->velocityY > 0) {
                self->posY.i.hi += collider.unk18;
            }
            if (self->velocityY < 0) {
                self->posY.i.hi += collider.unk20;
            }
            self->hitboxState = 0;
            self->ext.venusWeedDart.clutIndex = ClutIdxWallHit;
            SetStep(DEATH);
        }

        if (self->hitFlags & 0x80) {
            entity = &PLAYER;
            self->ext.venusWeedDart.nextPosDeltaX =
                entity->posX.i.hi - self->posX.i.hi;
            self->ext.venusWeedDart.nextPosDeltaY =
                entity->posY.i.hi - self->posY.i.hi;
            self->ext.venusWeedDart.clutIndex = ClutIdxPlayerHit;
            self->hitboxState = 0;
            SetStep(DECAY);
            break;
        }
        if (self->hitParams) {
            self->flags & FLAG_DEAD;
        }
        break;

    case DECAY:
        if (!(self->palette & 0x8000)) {
            self->ext.venusWeedDart.clutIndex++;
            self->palette = self->ext.venusWeedDart.clutIndex + DartClutStart;
            if (self->palette > PlantClutMax) {
                self->palette = PlantClutMax;
            }
        }
        if (self->ext.venusWeedDart.clutIndex > ClutIdxMax) {
            self->flags |= FLAG_DEAD;
        }

        entity = &PLAYER;
        self->posX.i.hi =
            entity->posX.i.hi - self->ext.venusWeedDart.nextPosDeltaX;
        self->posY.i.hi =
            entity->posY.i.hi - self->ext.venusWeedDart.nextPosDeltaY;
        break;

    case DEATH:
        if (!--self->ext.venusWeedDart.clutIndex) {
            self->flags |= FLAG_DEAD;
        }
        break;
    }

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
    }
}

INCLUDE_ASM("st/rno4_psp/nonmatchings/rno4_psp/e_blue_venus_weed", EntityVenusWeedSpike);
