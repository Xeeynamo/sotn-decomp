// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

// NOTE: Compare this to e_dragon_rider. Lots of similarities.

extern EInit D_us_801809C8;
extern EInit g_EInitOrobourous;
extern EInit g_EInitOruburos;
extern EInit g_EInitOruburosRider;

static u8 anim_bone_twisting[] = {32, 4, 6, 5, 6, 6, 14, 7, 6, 6, 6, 5, 0};
// 8 frames each of the head facing left vs right. happens when bouncing
static u8 anim_head_flipdirs[] = {8, 16, 8, 15, 255, 0};
static s16 sensors1[] = {0, 12, 0, 4, 8, -4, -16, 0};
typedef struct {
    u32 velX;
    u32 velY;
    s16 rotate;
} adhoc_vels_rot;
static adhoc_vels_rot headPartsParams[] = {
    {FIX(0.0625), FIX(0.0), -8},
    {FIX(0.25), FIX(-1.5), 40},
    {FIX(0.5), FIX(-0.5), 16},
    {FIX(0.125), FIX(-0.375), 8}};
static s16 headHitboxXYWH[] = {-7, 2, 13, 10, 4, 0, 7, 13, -5, 0, 7, 13};

// forward declare, exists later in this file
void EntityOrobHolyAttacker(Entity* self);

typedef enum{
    OROB_INIT,
    OROB_WAIT,
    OROB_2,
    OROB_BOUNCING,
    OROB_SET_FREE,
    OROB_INIT_FLY,
    OROB_FLYAROUND,
    OROB_7, // unused
    OROB_DEAD
} OrobourousSteps;

// This seems to be the entity for just the head.
// It creates 24 segments, and then the rider.
void EntityOrobourous(Entity* self) {
    Collider sp3C;
    Entity* other;
    s32 var_s7;
    s32 var_s6;
    s16* var_s5;
    s16 var_s4;
    s32 xVar;
    s32 yVar;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        SetStep(OROB_DEAD);
    }

    switch (self->step) {
    case OROB_INIT:
        InitializeEntity(g_EInitOrobourous);
        self->animCurFrame = 14;
        self->drawFlags |= ENTITY_ROTATE;
        other = self + 1;
        for (i = 0; i < 24; i++, other++) {
            CreateEntityFromEntity(E_OROB_SEGMENT, self, other);
            other->params = (i + 1);
            other->nextPart = other - 1;
        }
        self->parent = NULL;
        self->nextPart = self + 24;
        CreateEntityFromEntity(E_OROB_RIDER, self, other);
        self->ext.orob.unk9 = 2;
        break;
    case OROB_WAIT:
        if (UnkCollisionFunc3(sensors1) & 1) {
            SetStep(OROB_2);
        }
        break;
    case OROB_2:
        SetStep(OROB_BOUNCING);
        break;
    case OROB_BOUNCING:
        MoveEntity();
        self->velocityY += self->ext.orob.gravity;
        self->ext.orob.gravity += 0x100;
        if (self->velocityY < 0) {
            self->animCurFrame = 1;
        } else {
            self->animCurFrame = 14;
        }
        if (((self->ext.orob.movingLeft) != self->facingLeft) &&
            (AnimateEntity(anim_head_flipdirs, self) == 0)) {
            self->animCurFrame = 14;
            self->facingLeft = self->ext.orob.movingLeft;
        }
        if (self->rotate) {
            self->rotate -= 0x10;
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 12;
        g_api.CheckCollision(xVar, yVar, &sp3C, 0);
        if (sp3C.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_START_SLAM_B);
            self->posY.i.hi += sp3C.unk18;
            self->velocityY = FIX(-3.0);
            self->ext.orob.gravity = 0;
            var_s7 = self->ext.orob.movingLeft;
            if (var_s7 == (GetSideToPlayer() & 1)) {
                self->ext.orob.unk9 --;
            } else {
                self->ext.orob.unk9 = 2;
            }
            xVar = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (self->ext.orob.movingLeft) {
                if (((g_Tilemap.hSize << 8) - 0x80) < xVar) {
                    self->ext.orob.unk9 = 0;
                }
            } else if (xVar < 0x80) {
                self->ext.orob.unk9 = 0;
            }
            if (!self->ext.orob.unk9) {
                self->ext.orob.unk9 = 2;
                self->ext.orob.movingLeft ^= 1;
                self->poseTimer = 0;
                self->pose = 0;
            } else {
                self->rotate = 0x200;
            }
            if (self->ext.orob.movingLeft) {
                self->velocityX = FIX(1.5);
                EntityGreyPuffSpawner(self, 5, 3, 4, 12, 0, -4);
            } else {
                self->velocityX = FIX(-1.5);
                EntityGreyPuffSpawner(self, 5, 3, -4, 12, 0, 4);
            }
        }
        if (self->ext.orob.riderDead) {
            self->animCurFrame = 14;
            SetStep(OROB_SET_FREE);
        }
        break;
    case OROB_SET_FREE:
        other = self + 1;
        // Iterate through all the body segments
        for (i = 0; i < 24; i++, other++) {
            other->ext.orob.riderDead = true;
        }
        self->drawFlags = ENTITY_DEFAULT;
        self->ext.orob.unk9 = 0;
        self->hitboxState = 0;
        self->ext.orob.rest_time = 0x800;
        self->ext.orob.stepTimer = 0x10;
        other = AllocEntity(&g_Entities[32], &g_Entities[47]);
        if (other != NULL) {
            DestroyEntity(other);
            // Normally we would put in an E_WHATEVER for this, but
            // in RNO3 0x43 is the jewel sword door which makes no sense
            other->entityId = 0x43;
            other->step = 1;
            other->pfnUpdate = EntityOrobHolyAttacker;
            other->ext.orob.parent = self;
        } else {
            self->ext.orob.rest_time = -1;
        }
        SetStep(OROB_INIT_FLY);
        /* fallthrough */
    case OROB_INIT_FLY:
        if (!--self->ext.orob.stepTimer) {
            self->ext.orob.stepTimer = 4;
            other = self + self->ext.orob.unk9;
            other->palette += 2;
            if (self->ext.orob.unk9++ > 24) {
                SetStep(OROB_FLYAROUND);
            }
        }
        /* fallthrough */
    case OROB_FLYAROUND:
        FntPrint("rest_time:%x\n", self->ext.orob.rest_time);
        // This routine sets a target for the flying orob to navigate toward
        // Gets re-called periodically.
        if (!self->step_s) {
            self->ext.orob.targetTimer = 0x40;
            var_s4 = Random() * 8;
            xVar = (rcos(var_s4) * 0x60) >> 0xC;
            yVar = (rsin(var_s4) * -0x60) >> 0xC;
            if (!self->ext.orob.rest_time) {
                xVar = 0;
                yVar = 0;
                self->ext.orob.rest_time--;
                self->ext.orob.targetTimer = 0x100;
            }
            if (self->ext.orob.rest_time < 0) {
                xVar = 0x200;
                yVar = -0x300;
                self->ext.orob.targetTimer = 0x400;
            }
            other = &PLAYER;
            self->ext.orob.targetX = other->posX.i.hi + xVar;
            self->ext.orob.targetY = other->posY.i.hi + yVar;
            self->step_s += 1;
        }

        if (self->ext.orob.movingLeft != self->facingLeft &&
            (AnimateEntity(anim_head_flipdirs, self) == 0)) {
            self->animCurFrame = 14;
            self->facingLeft = self->ext.orob.movingLeft;
            self->pose = 0;
            self->poseTimer = 0;
        }
        MoveEntity();
        if (self->velocityX > 0) {
            self->ext.orob.movingLeft = 1;
        } else {
            self->ext.orob.movingLeft = 0;
        }
        xVar = self->ext.orob.targetX - self->posX.i.hi;
        yVar = self->ext.orob.targetY - self->posY.i.hi;
        var_s4 = ratan2(yVar, xVar);
        var_s4 = LimitAngleChange(0x20, self->ext.orob.vel_angle, var_s4);
        self->velocityX = rcos(var_s4) * 36;
        self->velocityY = rsin(var_s4) * 36;
        self->ext.orob.vel_angle = var_s4;
        // If the targetTimer has run out, or we have reached the target
        // (to a tolerance of 8 on each axis), reset to get a new target
        if ((!--self->ext.orob.targetTimer) ||
            ((abs(xVar) < 8) && (abs(yVar) < 8))) {
            self->step_s = 0;
        }
        if (self->ext.orob.rest_time > 0) {
            self->ext.orob.rest_time--;
            break;
        }
        if (self->posY.i.hi < -0x200) {
            other = self + 1;
            for (i = 0; i < 24; i++, other++) {
                DestroyEntity(other);
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        }
        break;
    case OROB_DEAD:
        PlaySfxPositional(SFX_SKELETON_DEATH_A);
        other = self + 1;
        for (i = 0; i < 25; i++, other++) {
            other->flags |= FLAG_DEAD;
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 3;
        }
        for (i = 0; i < 4; i++) {
            // i = 1 would make params 1 so anim frame 9, which is
            // the rider dude. Skip making him, he already fell off.
            if (i != 1) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_OROB_HEAD_PARTS, self, other);
                    other->facingLeft = self->facingLeft;
                    other->velocityX = self->velocityX;
                    other->velocityY = -0x18000;
                    other->params = i;
                }
            }
        }
        DestroyEntity(self);
        return;
    }
    var_s5 = &headHitboxXYWH[0];
    var_s6 = self->animCurFrame - 14;
    if (var_s6 < 0) {
        var_s6 = 0;
    }
    var_s5 += var_s6 * 4;
    self->hitboxOffX = *var_s5++;
    self->hitboxOffY = *var_s5++;
    self->hitboxWidth = *var_s5++;
    self->hitboxHeight = *var_s5++;
}

void EntityOrobSegment(Entity* self) {
    s32 speed;
    s16 angle;
    s32 xVar;
    s32 yVar;
    Entity* other;
    s32 miscTemp;

    if ((self->flags & FLAG_DEAD) && ((self->step) < 8)) {
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        SetStep(OROB_DEAD);
    }
    switch (self->step) {
    case OROB_INIT:
        InitializeEntity(g_EInitOruburos);
        self->hitboxOffY = 1;
        self->pose = self->params % 6;
        self->drawFlags |= ENTITY_OPACITY;
        miscTemp = self->params;
        self->opacity = (0x80 - miscTemp);
        miscTemp -= 10;
        if (miscTemp > 0) {
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100 - (miscTemp * 6);
        }
        // The 4th segment is the arms
        if ((self->params) == 4) {
            self->animCurFrame = 17;
        }
        // The 12th segment is the legs
        if ((self->params) == 12) {
            self->animCurFrame = 18;
        }
        break;
    case OROB_WAIT:
        MoveEntity();
        other = self - 1;
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        miscTemp = (xVar * xVar) + (yVar * yVar);
        miscTemp = SquareRoot0(miscTemp);
        speed = miscTemp * 3;
        angle = ratan2(yVar, xVar);
        miscTemp = (self->velocityX = speed * rcos(angle));
        self->velocityY = speed * rsin(angle);
        if (miscTemp > 0) {
            self->facingLeft = 1;
        } else {
            self->facingLeft = 0;
        }
        break;
    case OROB_DEAD:
        MoveEntity();
        self->velocityY += FIX(10.0/128);
        return;
    }
    if (((self->params) != 4) && ((self->params) != 12)) {
        AnimateEntity(anim_bone_twisting, self);
    }
    miscTemp = (self->params & 3);
    if ((g_Timer & 3) == miscTemp) {
        self->hitboxState = 3;
    } else {
        self->hitboxState = 0;
    }
    if (self->ext.orob.riderDead) {
        self->hitboxState = 0;
    }
}

void EntityOrobHeadParts(Entity* self) {
    adhoc_vels_rot* temp_s0;

    if (!self->step) {
        InitializeEntity(D_us_801809C8);
        self->drawFlags = ENTITY_ROTATE;
        self->hitboxState = 0;
        // We create 4 of this entity, with params 0 to 3.
        self->animCurFrame = self->params + 8;
        self->zPriority += self->params;
        temp_s0 = &headPartsParams[self->params];
        if (self->facingLeft) {
            self->velocityX += temp_s0->velX;
        } else {
            self->velocityX += -temp_s0->velX;
        }
        self->velocityY += temp_s0->velY;
    }
    MoveEntity();
    self->velocityY += FIX(0.09375);
    temp_s0 = &headPartsParams[self->params];
    self->rotate += temp_s0->rotate;
}

void EntityOrobRider(Entity* self) {
    Entity* other;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_EXPLODE_B);
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, other);
            other->params = 1;
        }
        // This creates the entity for the rider dude falling off.
        // params of 1 is what triggers this.
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_OROB_HEAD_PARTS, self, other);
            other->facingLeft = self->facingLeft;
            other->params = 1;
        }
        // The head is made, then 24 segments, then the rider.
        // so self - 25 is going back to the head.
        other = self - 25;
        other->ext.orob.riderDead = true;
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOruburosRider);
        self->animCurFrame = 13;
        self->hitboxOffX = 5;
        self->hitboxOffY = -2;
        self->drawFlags = ENTITY_ROTATE;
        break;
    case 1:
        other = self - 25;
        self->facingLeft = other->facingLeft;
        // Note! This is a useless if statement, with useless shifts!
        // There was probably some kind of OFFSET defined but set
        // to zero at final release.
        if (self->facingLeft) {
            self->posX.i.hi = other->posX.i.hi - 0;
        } else {
            self->posX.i.hi = other->posX.i.hi + 0;
        }
        self->posY.i.hi = other->posY.i.hi - 0xA;
        if (other->animCurFrame == 0xE) {
            self->zPriority = other->zPriority + 1;
        } else {
            self->zPriority = other->zPriority - 1;
        }
        if (other->velocityY > 0) {
            self->animCurFrame = 13;
            if (self->rotate > -0x240) {
                self->rotate -= 0x18;
            }
        } else {
            self->animCurFrame = 0;
            self->rotate = 0;
        }
        break;
    }
}

// Once the Orobourous has been freed (the rider killed), it converts over and
// can damage enemies (effectively, it has turned good). This entity, in case
// 2, constantly positions itself at different locations. It places itself at
// different offsets along the length of the snake, effectively meaning that
// the snake has a "killer orb" racing along itself. It moves quite fast.
// It can be seen if you turn on hitboxes in the SOTN Debug Module.
void EntityOrobHolyAttacker(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
    case 1:
        self->hitboxState = 2;
        self->attack = 48;
        self->attackElement = ELEMENT_HOLY;
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->nFramesInvincibility = 16;
        self->stunFrames = 4;
        self->hitEffect = 1;
        self->ext.orob.unused_zero = 0;
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        g_api.func_80118894(self);
        self->step += 1;
        break;
    case 2:
        parent = self->ext.orob.parent;
        parent += self->ext.orob.unk9;
        
        self->ext.orob.unk9 += 2;
        if (self->ext.orob.unk9 > 24) {
            self->ext.orob.unk9 = 0;
        }
        self->posX.i.hi = parent->posX.i.hi;
        self->posY.i.hi = parent->posY.i.hi;
        if ((parent->entityId != E_OROBOUROUS) && 
        (parent->entityId != E_OROB_SEGMENT)) {
            DestroyEntity(self);
        }
        break;
    }
}
