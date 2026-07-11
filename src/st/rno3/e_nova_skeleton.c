// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

extern EInit g_EInitNovaSkeleton;
extern EInit g_EInitNovaSkeleton2;

// sensors
static s16 sensors1[] = {0, 20, 0, 4, 8, -4, -16, 0};
static s16 sensors2[] = {0, 20, 12, 0};
// animations
static u8 anim_walk_fwd[] = {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0};
static u8 anim_walk_back[] = {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0};
// A short squatting animation. Perhaps a jump windup?
static u8 anim_unused1[] = {1, 1, 4, 27, 4, 28, 1, 1, 255, 0};
// Slightly slower squat, note that the frames are all the same, just an extra
// 4,27.
static u8 anim_unused2[] = {1, 1, 4, 27, 4, 28, 4, 27, 1, 1, 255, 0};
static u8 anim_idle[] = {4, 1, 5, 27, 15, 28, 6, 27, 6, 1, 0};
static u8 anim_laser_charge[] = {
    16, 1,  3,  2,  3,  7,  3,  8,  2,  9,  2,  10, 2,  11,  2,  10, 2,
    11, 2,  12, 2,  11, 2,  12, 2,  13, 2,  12, 2,  13, 2,   14, 2,  13,
    2,  14, 2,  13, 2,  14, 2,  15, 2,  16, 2,  15, 2,  16,  2,  15, 2,
    16, 4,  20, 4,  19, 4,  18, 4,  17, 4,  18, 4,  19, 255, 0};
// Not the laser itself - just nova skeleton standing there, holding arms up
// menacingly
static u8 anim_laser_blast[] = {
    2,  20, 96, 21, 1, 23, 1, 22, 1, 23, 1, 22, 1, 23, 2,   22,
    2,  23, 2,  22, 2, 23, 3, 22, 3, 23, 3, 22, 4, 23, 5,   22,
    26, 23, 3,  24, 3, 25, 3, 26, 4, 4,  4, 5,  4, 6,  255, 0};
// death_parts_rotspeeds
static u16 death_parts_rotspeeds[] = {256, 128, 72, 32, 64, 16, 32, -32};
// deathPartLife
static u8 death_parts_lifetimes[] = {48, 32, 20, 12, 24, 16, 64, 48};
// death part xvel
static s32 death_parts_xVels[] = {FIX(0.75), FIX(1.75), FIX(1.5),  FIX(1.0),
                                  FIX(2.0),  FIX(1.75), FIX(-0.5), FIX(0.5)};
// death part yvel
static s32 death_parts_yVels[] = {FIX(-5.0), FIX(-3.0),   FIX(-2.0), FIX(-3.0),
                                  FIX(-4.0), FIX(-0.875), FIX(-6.0), FIX(-4.5)};
// death_parts_xPos
static s16 death_parts_xPos[] = {-4, 0, 4, -4, -4, 4, -6, 6};
// death_parts_yPos
static s16 death_parts_yPos[] = {-16, -8, -4, -4, 9, 9, 2, -2};
// laser cooldown
static u8 laser_cooldowns[] = {128, 8, 8, 64, 240, 192, 160, 128};
static s8 unused[] = {-12, -1, 16, 0, 0, 0, -16, -1, 0, 0, -16, -1};
// vectors
static SVECTOR vec_negneg = {-32, -32, 0, 0};
static SVECTOR vec_posneg = {32, -32, 0, 0};
static SVECTOR vec_negpos = {-32, 32, 0, 0};
static SVECTOR vec_pospos = {32, 32, 0, 0};
// uv data
static u8 primData[] = {96, 127, 128, 128, 32, 95, 64, 128, 0, 31, 32, 64};

typedef enum {
    NOVA_INIT,
    NOVA_1,
    NOVA_IDLE,
    NOVA_WALK_FWD,
    NOVA_WALK_BACK,
    NOVA_5,
    NOVA_CHARGE,
    NOVA_SHOOT,
    NOVA_DEAD
} NovaSkeletonSteps;

static void TryShoot(void) {
    // return value not used, but function has side effects
    s32 unused = UnkCollisionFunc2(&sensors2);
    // if cooldown has expired...
    if (!g_CurrentEntity->ext.nova.cooldown) {
        if (GetDistanceToPlayerX() >= 0x80) {
            return;
        }
        if ((g_CurrentEntity->facingLeft) ^ (GetSideToPlayer() & 1)) {
            SetStep(NOVA_CHARGE);
        }
    } else {
        g_CurrentEntity->ext.nova.cooldown--;
    }
}

static void DrawLaserRing(void) {
    s32 p;
    s32 flag;
    SVECTOR sp60;
    VECTOR sp50;
    MATRIX sp30;
    SVECTOR sp28 = {0};
    s32 yVar;
    s32 xVar;
    Primitive* prim;
    // Ring state: 0 = init, 1 = ongoing/growing
    switch (g_CurrentEntity->ext.nova.ringState) {
    case 0:
        g_CurrentEntity->ext.nova.ringSize = 0;
        prim = g_CurrentEntity->ext.nova.prim;
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        g_CurrentEntity->ext.nova.ringState = 1;
        break;
    case 1:
        g_CurrentEntity->ext.nova.ringRot += 0x100;
        g_CurrentEntity->ext.nova.ringSize += 0x200;
        break;
    }
    SetGeomScreen(0x200);
    xVar = g_CurrentEntity->posX.i.hi;
    yVar = g_CurrentEntity->posY.i.hi;
    if (g_CurrentEntity->facingLeft) {
        xVar += 10;
    } else {
        xVar -= 10;
    }
    yVar -= 2;
    SetGeomOffset(xVar, yVar);
    sp60.vx = 0;
    if (g_CurrentEntity->facingLeft) {
        sp60.vy = -0x2E0;
    } else {
        sp60.vy = 0x2E0;
    }
    sp60.vz = g_CurrentEntity->ext.nova.ringRot;
    RotMatrix(&sp28, &sp30);
    RotMatrixZ(sp60.vz, &sp30);
    RotMatrixY(sp60.vy, &sp30);
    sp50.vx = 0;
    sp50.vy = 0;
    sp50.vz = 0x200;
    TransMatrix(&sp30, &sp50);
    sp50.vx = g_CurrentEntity->ext.nova.ringSize;
    sp50.vy = g_CurrentEntity->ext.nova.ringSize;
    sp50.vz = 0x1000;
    ScaleMatrix(&sp30, &sp50);
    SetRotMatrix(&sp30);
    SetTransMatrix(&sp30);
    prim = g_CurrentEntity->ext.nova.prim;
    RotTransPers4(&vec_negneg, &vec_posneg, &vec_negpos, &vec_pospos,
                  (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2,
                  (long*)&prim->x3, (long*)&p, (long*)&flag);
}

void EntityNovaSkeleton(Entity* self) {
    s32 var_s4;
    Entity* other;
    Primitive* prim;
    s32 primIndex;
    s32 i;

    if (self->flags & FLAG_DEAD) {
        SetStep(NOVA_DEAD);
    }
    switch (self->step) {
    case NOVA_INIT:
        InitializeEntity(g_EInitNovaSkeleton);
        self->ext.nova.cooldown = 0x50;
// what. why does psp need to allocate an extra prim.
#if defined(VERSION_PSP)
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
#else
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
#endif
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.nova.prim = prim;
        UnkPolyFunc2(prim);
        prim->tpage = 0x12;
        prim->clut = 0x216;
        prim->u0 = prim->u2 = 0xC0;
        prim->u1 = prim->u3 = 0xFF;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x40;
        prim->priority = self->zPriority + 1;
        prim->drawMode = DRAW_HIDE;
        break;
    case NOVA_1:
        if (UnkCollisionFunc3(sensors1) == 0) {
            break;
        }
        SetStep(NOVA_IDLE);
        break;
    case NOVA_IDLE:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(&anim_idle, self);
        if (GetDistanceToPlayerX() < 0x70) {
            SetStep(NOVA_WALK_BACK);
        }
        break;
    case NOVA_WALK_FWD:
        if (AnimateEntity(&anim_walk_fwd, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.nova.movingLeft = self->facingLeft;
        if (self->ext.nova.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 0x4C) {
            self->step = NOVA_WALK_BACK;
        }
        TryShoot();
        break;
    case NOVA_WALK_BACK:
        if (AnimateEntity(&anim_walk_back, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.nova.movingLeft = self->facingLeft ^ 1;
        if (self->ext.nova.movingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 0x5C) {
            self->step = NOVA_WALK_FWD;
        }
        TryShoot();
        break;
    // Could be related to the unsed animations. Not accessible.
    case NOVA_5:
        break;
    case NOVA_CHARGE:
        if (AnimateEntity(&anim_laser_charge, self) == 0) {
            self->ext.nova.ringState = 0;
            SetStep(NOVA_SHOOT);
        }
        if ((!self->poseTimer) && (self->pose == 2)) {
            PlaySfxPositional(SFX_ELECTRICITY);
        }
        break;
    case NOVA_SHOOT:
        switch (self->step_s) {
        case 0:
            other = self + 1;
            CreateEntityFromEntity(E_NOVA_LASER, self, other);
            if (self->facingLeft) {
                other->posX.i.hi += 0xA;
            } else {
                other->posX.i.hi -= 0xA;
            }
            other->posY.i.hi -= 4;
            other->facingLeft = self->facingLeft;
            self->step_s++;
            break;
        case 1:
            prim = self->ext.nova.prim;
            PrimDecreaseBrightness(prim, 5);
            break;
        }
        DrawLaserRing();
        if (!AnimateEntity(&anim_laser_blast, self)) {
            prim = self->ext.nova.prim;
            prim->drawMode = DRAW_HIDE;
            var_s4 = ++self->ext.nova.laserTimerIndex & 7;
            self->ext.nova.cooldown = laser_cooldowns[var_s4];
            SetStep(NOVA_WALK_BACK);
        }
        break;
    case NOVA_DEAD:
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_NOVA_DEATH_PARTS, other);
            other->facingLeft = self->facingLeft;
            other->params = i;
            other->ext.nova.deathPartLife = death_parts_lifetimes[i];
            if (self->facingLeft) {
                other->posX.i.hi -= death_parts_xPos[i];
            } else {
                other->posX.i.hi += death_parts_xPos[i];
            }
            other->posY.i.hi += death_parts_yPos[i];
            other->velocityX = death_parts_xVels[i];
            other->velocityY = death_parts_yVels[i];
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        break;
    }
}

void EntityNovaSkeletonDeathParts(Entity* self) {
    if (self->step) {
        if (--self->ext.nova.deathPartLife) {
            self->rotate += death_parts_rotspeeds[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = E_EXPLOSION;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(g_EInitNovaSkeleton);
    self->hitboxState = 0;
    self->flags |=
        FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
        FLAG_UNK_00200000 | FLAG_UNK_2000;
    self->animCurFrame = self->params + 0x1D;
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

typedef enum { LASER_INIT, LASER_1, LASER_2, LASER_3, LASER_4 } NovaLaserSteps;

void EntityNovaLaser(Entity* self) {
    s32 centerX;
    s32 primIndex;
    s32 centerY;
    Entity* other;
    s32 primX;
    s32 var_s2;
    u8* var_s1;
    Primitive* prim;

    switch (self->step) {
    case LASER_INIT:
        InitializeEntity(g_EInitNovaSkeleton2);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 3);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.nova.prim = prim;
        var_s1 = &primData[0];
        for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
            prim->tpage = 0x12;
            prim->clut = 0x216;
            prim->u0 = prim->u2 = *var_s1++ + 0x80;
            prim->u1 = prim->u3 = *var_s1++ + 0x80;
            prim->v0 = prim->v1 = 0x40;
            prim->v2 = prim->v3 = 0x5F;
            prim->r0 = prim->g0 = prim->b0 = *var_s1++;
            LOW(prim->r2) = LOW(prim->r0);
            prim->r1 = prim->g1 = prim->b1 = *var_s1++;
            LOW(prim->r3) = LOW(prim->r1);
            prim->priority = self->zPriority + 2;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        self->ext.nova.laserTimer = 0x60;
        self->ext.nova.laserLength = 0;
    case LASER_1:
        self->ext.nova.laserFadeTimer = 0x10;
        if (self->ext.nova.laserLength < 0x80) {
            self->ext.nova.laserLength += 0x10;
        } else {
            self->ext.nova.laserLength = 0x80;
            self->hitboxState = 1;
            self->step++;
        }
    case LASER_2:
        if (!(self->ext.nova.laserTimer & 3)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_NOVA_PULSE, self, other);
                other->zPriority = self->zPriority - 1;
                other->ext.nova.laserLength = self->ext.nova.laserLength;
                other->facingLeft = self->facingLeft;
            }
        }
        if (!(self->ext.nova.laserTimer & 0xF)) {
            PlaySfxPositional(SFX_BAT_ECHO_A);
        }
        if (self->ext.nova.laserTimer < 0x10) {
            PlaySfxPositional(SFX_BAT_ECHO_D);
            self->step++;
        }
    case LASER_3:
        if (OVL_EXPORT(Random)() & 1) {
            if (self->ext.nova.laserLength < 0x88) {
                self->ext.nova.laserLength++;
            } else if (self->ext.nova.laserLength > 0x78) {
                self->ext.nova.laserLength--;
            }
        }
        self->hitboxWidth = self->ext.nova.laserLength / 2 + 0x10;
        self->hitboxOffX = -self->ext.nova.laserLength / 2 - 0x10;
        self->hitboxHeight = 8;
        other = self - 1;
        if (other->entityId != E_NOVA_SKELETON) {
            self->ext.nova.laserTimer = 1;
        }
        if (!--self->ext.nova.laserTimer) {
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case LASER_4:
        self->ext.nova.laserFadeTimer--;
        if (!self->ext.nova.laserFadeTimer) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    centerX = self->posX.i.hi;
    centerY = self->posY.i.hi;
    prim = self->ext.nova.prim;
    for (var_s2 = 0; var_s2 < 3; prim = prim->next, var_s2++) {
        prim->y0 = prim->y1 = centerY - self->ext.nova.laserFadeTimer;
        prim->y2 = prim->y3 = centerY + self->ext.nova.laserFadeTimer;
        if (g_Timer & 1) {
            prim->clut = 0x216;
        } else {
            prim->clut = 0x217;
        }
    }
    prim = self->ext.nova.prim;
    primX = centerX;
    if (self->facingLeft) {
        primX -= 0x10;
    } else {
        primX += 0x10;
    }

    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }

    prim->x0 = prim->x2 = primX;
    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += self->ext.nova.laserLength;
    } else {
        primX -= self->ext.nova.laserLength;
    }

    prim->x0 = prim->x2 = primX;
    prim = prim->next;
    prim->x1 = prim->x3 = primX;
    if (self->facingLeft) {
        primX += 0x20;
    } else {
        primX -= 0x20;
    }
    prim->x0 = prim->x2 = primX;
    prim = prim->next;
}

void EntityNovaLaserPulse(Entity* self) {
    s32 temp_s0;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitNovaSkeleton2);
        self->hitboxState = 0;
        self->animCurFrame = 0x24;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x10;
        if (self->facingLeft) {
            self->velocityX = FIX(8.0);
        } else {
            self->velocityX = FIX(-8.0);
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->ext.nova.laserPulseDist += abs(self->velocityX);
        self->scaleX = self->scaleY += 0x40;
        if (self->scaleX < 0x100) {
            return;
        }
        self->step++;
        return;
    case 2:
        MoveEntity();
        self->ext.nova.laserPulseDist += abs(self->velocityX);
        temp_s0 = (self->ext.nova.laserLength + 0x20) << 0x10;
        temp_s0 -= self->ext.nova.laserPulseDist;
        if (temp_s0 < 0) {
            DestroyEntity(self);
            return;
        }
        // okay now let's just play with this number. we're not going to use
        // it but math is fun, I guess? Everyone likes some nice bit shifts.
        temp_s0 >>= 0x10;
        temp_s0 <<= 3;
        if (temp_s0 > 0x100) {
            temp_s0 = 0x100;
        }
        break;
    }
}
