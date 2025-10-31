// SPDX-License-Identifier: AGPL-3.0-or-later

// Detects if the merman is splashing into water.
// If so, creates a splash effect, and sets merman underwater to true.
bool CheckMermanEnteringWater(s16 yOffset) {
    Collider collider;
    Entity* newEntity;
    s32 res = false;

    s16 x = g_CurrentEntity->posX.i.hi;
    s16 y = g_CurrentEntity->posY.i.hi + yOffset;
    g_api.CheckCollision(x, y, &collider, 0);

    if (!(collider.effects & EFFECT_SOLID)) {
        res = true;
    }

    if (collider.effects & EFFECT_WATER) {
        if (!g_CurrentEntity->ext.merman.isUnderwater) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_MERMAN_WATER_SPLASH, g_CurrentEntity, newEntity);
                newEntity->posY.i.hi += yOffset;
                newEntity->zPriority = g_CurrentEntity->zPriority;
            }
            g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
            g_CurrentEntity->ext.merman.isUnderwater = true;
        }
    }
    return res;
}

typedef enum {
    MERMAN2_INIT,
    MERMAN2_SWIMMING_UP,
    MERMAN2_SWIMMING = 3,
    MERMAN2_JUMPING,
    MERMAN2_WALKING_TO_PLAYER,
    MERMAN2_SPIT_FIRE,
    MERMAN2_7,
    MERMAN2_DYING,
} Merman2Steps;

typedef enum {
    MERMAN2_JUMPING_SETUP,
    MERMAN2_JUMPING_UNDERWATER,
    MERMAN2_JUMPING_IN_AIR,
} Merman2JumpingSubSteps;

typedef enum {
    MERMAN2_WALKING_TO_PLAYER_SETUP,
    MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER,
    MERMAN2_WALKING_TO_PLAYER_WALKING,
} Merman2WalkingToPlayerSubSteps;

typedef enum {
    MERMAN2_SPIT_FIRE_FACE_PLAYER,
    MERMAN2_SPIT_FIRE_ATTACK,
} Merman2SpitFireSubSteps;

#define XY(x, y) x, y
static Point32 g_merman2Swimvels[] = {
    XY(FIX(0.5), FIX(-0.5)), XY(FIX(-0.5), FIX(-0.5)), XY(FIX(0.5), FIX(0.5)),
    XY(FIX(-0.5), FIX(0.5))};
static u8 g_merman2_walktimers[] = {0x40, 0x30, 0x50, 0x40};
static s16 g_merman_coll1[] = {XY(0, 27), XY(0, 4), XY(4, -4), XY(-8, 0)};
static s16 g_merman2_coll3[] = {XY(0, 22), XY(0, 4), XY(8, -4), XY(-16, 0)};
static s16 g_merman_coll2[] = {XY(0, 27), XY(8, 0)};
static u8 g_merman2_walkanim[] = {9, 1, 9, 2, 9, 3, 9, 4, 0};
static u8 g_merman2_spitfire[] = {
    24, 5, 2, 8, 2, 9, 5, 10, 11, 11, 5, 10, 2, 9, 2, 8, 8, 12, 1, 13, 255, 0};
static u8 g_merman_walkanim_init[] = {24, 7, 7, 6, 16, 5, 255, 0};
static u8 g_merman2_swim_anim[] = {11, 15, 11, 16, 0};

void EntityMerman2(Entity* self) {
    u8 colorOffset;
    u8 rnd;
    s16* pos;
    s32 primIndex;
    s32 colRes;
    Collider collider;
    Entity* newEntity;
    Primitive* prim;
    s16 posX, posY;
    s32 i;

    if (self->ext.merman2.ignoreCol && (self->step < MERMAN2_7)) {
        SetStep(MERMAN2_7);
    }

    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN2_DYING)) {
        PlaySfxPositional(SFX_MERMAN_DEATH);
        self->drawFlags = FLAG_DRAW_DEFAULT;
        if (self->flags & FLAG_HAS_PRIMS) {
            primIndex = self->primIndex;
            g_api.FreePrimitives(primIndex);
            self->flags &= ~FLAG_HAS_PRIMS;
        }
        self->flags &= ~FLAG_UNK_20000000;
        self->hitboxState = 0;
        SetStep(MERMAN2_DYING);
    }

    switch (self->step) {
    case MERMAN2_INIT:
        InitializeEntity(g_EInitWaterObject);
        self->hitboxOffY = 8;
        self->zPriority = 0xA9;
        if (self->params) {
            self->palette++;
        }
        self->velocityY = FIX(-1);
        break;

    case MERMAN2_SWIMMING_UP:
        AnimateEntity(g_merman2_swim_anim, self);
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN2_SWIMMING);
        }
        break;

    case MERMAN2_SWIMMING:
        if (!self->step_s) {
            rnd = Random() & 3;
            self->velocityX = g_merman2Swimvels[rnd].x;
            self->velocityY = g_merman2Swimvels[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(g_merman2_swim_anim, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        MoveEntity();
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            self->velocityY = FIX(0.5);
        }
        posY += g_Tilemap.scrollY.i.hi;
        pos = g_WaterXTbl;
        pos += (self->params & 0x100) >> 8;
        if (posY > pos[4]) {
            self->posY.i.hi = pos[4] - g_Tilemap.scrollY.i.hi - 24;
        }

        if (self->ext.merman2.timer++ > 32) {
            self->ext.merman2.timer = 0;
            self->step_s = 0;
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN2_JUMPING);
            }
        }
        break;

    case MERMAN2_JUMPING:
        switch (self->step_s) {
        case MERMAN2_JUMPING_SETUP:
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                self->animCurFrame = 0;
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.merman2.prim = prim;
                prim->tpage = 0x12;
                prim->clut = 0x28C;
                if (self->params & 1) {
                    prim->clut++;
                }
                prim->u0 = 0;
                prim->u1 = prim->u0 + 0x20;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0x38;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0x38;
                prim->v3 = prim->v2;

                // These should probably be written some other way
                if (self->facingLeft) {
                    prim->x0 = (self->posX.i.hi - 0x8000) - 0x7FF1;
                    prim->x1 = prim->x0 - 0x20;
                } else {
                    prim->x0 = (self->posX.i.hi + 0x7FFF) + 0x7FF2;
                    prim->x1 = prim->x0 + 0x20;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = (self->posY.i.hi + 0x7FFF) + 0x7FF0;
                prim->y1 = prim->y0;
                prim->y2 = prim->y0 + 0x38;
                prim->y3 = prim->y2;
                setRGB0(prim, 64, 64, 160);
                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);

                prim->priority = self->zPriority;
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                self->animCurFrame = 17;
                DestroyEntity(self);
            }
            break;

        case MERMAN2_JUMPING_UNDERWATER:
            MoveEntity();
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            posY -= 24;
            posY += g_Tilemap.scrollY.i.hi;
            pos = g_WaterXTbl;
            pos += (self->params & 0x100) >> 8;

            if (posY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MERMAN_WATER_SPLASH, self, newEntity);
                    newEntity->posY.i.hi -= 24;
                    newEntity->zPriority = self->zPriority;
                }
                self->drawFlags |= FLAG_DRAW_ROTATE;
                self->rotate = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_JUMPING_IN_AIR:
            prim = self->ext.merman2.prim;
            if (self->velocityY > ~0xBFFF) {
                prim->drawMode = DRAW_HIDE;
                self->animCurFrame = 18;
                self->rotate -= 0x80;
                self->hitboxHeight = 8;
            } else {
                // These should probably be written some other way
                if (self->facingLeft) {
                    prim->x0 = (self->posX.i.hi - 0x8000) - 0x7FF1;
                    prim->x1 = prim->x0 - 0x20;
                } else {
                    prim->x0 = (self->posX.i.hi + 0x7FFF) + 0x7FF2;
                    prim->x1 = prim->x0 + 0x20;
                }
                prim->x2 = prim->x0;
                prim->x3 = prim->x1;
                prim->y0 = (self->posY.i.hi + 0x7FFF) + 0x7FF0;
                prim->y1 = prim->y0;
                prim->y2 = prim->y0 + 0x38;
                prim->y3 = prim->y2;

                colorOffset = (abs(self->velocityY) >> 0xC) - 10;

                setRGB0(prim, 128 - colorOffset / 2, 128 - colorOffset / 2,
                        colorOffset / 2 + 192);

                LOW(prim->r1) = LOW(prim->r0);
                LOW(prim->r2) = LOW(prim->r0);
                LOW(prim->r3) = LOW(prim->r0);
            }
            if (self->velocityY < 0) {
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN2_JUMP_AIR, self, newEntity);
                    newEntity->posX.i.hi += ((Random() & 3) * 4) - 6;
                    newEntity->zPriority = self->zPriority + 1;
                }
            }
            if (self->velocityY > 0) {
                CheckMermanEnteringWater(0x1B);
            }
            if (!self->ext.merman2.isUnderwater) {
                if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                    primIndex = self->primIndex;
                    g_api.FreePrimitives(primIndex);
                    self->flags &= ~FLAG_HAS_PRIMS;
                    self->drawFlags &=
                        FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                        FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                        FLAG_DRAW_SCALEX;
                    self->hitboxHeight = 21;
                    SetStep(MERMAN2_WALKING_TO_PLAYER);
                }
            } else {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                MoveEntity();
                self->velocityY += FIX(0.25);
            }
        }
        break;

    case MERMAN2_WALKING_TO_PLAYER:
        switch (self->step_s) {
        case MERMAN2_WALKING_TO_PLAYER_SETUP:
            if (AnimateEntity(g_merman_walkanim_init, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;

        case MERMAN2_WALKING_TO_PLAYER_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            rnd = Random() & 3;
            self->ext.merman2.timer = g_merman2_walktimers[rnd];
            self->step_s++;
            break;

        case MERMAN2_WALKING_TO_PLAYER_WALKING:
            AnimateEntity(g_merman2_walkanim, self);
            colRes = UnkCollisionFunc2(&g_merman_coll2);
            if (colRes == 0xFF) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }

            if (colRes & 0x80) {
                self->posX.val += self->velocityX;
            }

            if (self->params & 1) {
                self->velocityX *= 2;
            }
            if (!(self->params & 1)) {
                if (self->posX.i.hi & 0xFF00) {
                    break;
                }
                if (!--self->ext.merman2.timer) {
                    if (Random() & 1) {
                        SetStep(MERMAN2_SPIT_FIRE);
                    } else {
                        self->step_s--;
                    }
                }
            }
            if (CheckMermanEnteringWater(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN2_SPIT_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN2_SPIT_FIRE_ATTACK:
            if (AnimateEntity(g_merman2_spitfire, self) == 0) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MEDIUM_WATER_SPLASH, self, newEntity);
                    newEntity->posY.i.hi -= 12;
                    newEntity->facingLeft = self->facingLeft;
                }
                for (i = 0; i < 3; i++) {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(
                            E_MERMAN2_SPIT_FIRE, self, newEntity);
                        if (self->facingLeft) {
                            newEntity->posX.i.hi += (8 + i * 8);
                        } else {
                            newEntity->posX.i.hi -= (8 + i * 8);
                        }
                        newEntity->posY.i.hi -= 12;
                        newEntity->facingLeft = self->facingLeft;
                        if (i == 0) {
                            newEntity->params = 1;
                        }
                    }
                }
                self->drawFlags |= FLAG_DRAW_ROTATE;
                self->rotate = 0;
                self->ext.merman2.rotation = 1;
                if (self->facingLeft) {
                    self->velocityX = FIX(-6);
                } else {
                    self->velocityX = FIX(6);
                }
                self->velocityY = FIX(-0.0625);
                self->posY.i.hi -= 1;
                self->step_s++;
            }
            break;

        case 2:
            if ((self->ext.merman2.rotation < 0x100) && (g_Timer % 2)) {
                self->ext.merman2.rotation *= 2;
            }
            if (self->velocityX != 0) {
                if (self->facingLeft) {
                    self->velocityX += FIX(0.1875);
                } else {
                    self->velocityX -= FIX(0.1875);
                }
            }
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            self->rotate += self->ext.merman2.rotation;
            self->velocityY -= FIX(0.125);

            if (UnkCollisionFunc3(&g_merman_coll1) & 1) {
                if (self->facingLeft) {
                    self->velocityX = FIX(-2.5);
                } else {
                    self->velocityX = FIX(2.5);
                }
                self->ext.merman2.rotation = 4;
                self->posY.i.hi += 10;
                self->step_s++;
            }
            CheckMermanEnteringWater(0x1B);
            if (self->ext.merman2.isUnderwater) {
                self->ext.merman2.ignoreCol = 1;
            }
            break;

        case 3:
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft) {
                posX -= 20;
            } else {
                posX += 20;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            MoveEntity();
            self->rotate += 0xC0;
            if (self->rotate > 0x1000) {
                self->posY.i.hi -= 10;
                self->drawFlags &=
                    FLAG_BLINK | FLAG_DRAW_UNK40 | FLAG_DRAW_UNK20 |
                    FLAG_DRAW_UNK10 | FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY |
                    FLAG_DRAW_SCALEX;
                SetStep(MERMAN2_WALKING_TO_PLAYER);
            }
            if (CheckMermanEnteringWater(0x1B)) {
                self->ext.merman2.ignoreCol = 1;
            }
        }
        break;

    case MERMAN2_7:
        if (!self->step_s) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(CheckMermanEnteringWater(0x1B)) &&
            !(self->ext.merman2.isUnderwater)) {
            self->ext.merman2.ignoreCol = 0;
            SetStep(MERMAN2_WALKING_TO_PLAYER);
        }
        break;

    case MERMAN2_DYING:
        switch (self->step_s) {
        case 0:
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->animCurFrame = 14;
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(2);
            } else {
                self->velocityX = FIX(-2);
            }
            self->velocityY = FIX(-1);
            self->step_s++;
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.merman2.prim = prim;
                UnkPolyFunc2(prim);
                prim->tpage = 0x12;
                prim->clut = 0x292;
                if (self->params & 1) {
                    prim->clut++;
                }
                if (self->facingLeft) {
                    prim->u0 = 0xF0;
                    prim->u1 = prim->u0 - 0x28;
                } else {
                    prim->u0 = 0xC8;
                    prim->u1 = prim->u0 + 0x28;
                }
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = prim->v0 + 0x30;
                prim->v3 = prim->v2;

                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_UNK02;
                LOH(prim->next->r2) = 0x28;
                LOH(prim->next->b2) = 0x30;
                prim->next->b3 = 0x80;
                if (self->facingLeft) {
                    prim->next->x1 = self->posX.i.hi - 3;
                } else {
                    prim->next->x1 = self->posX.i.hi + 3;
                }
                prim->next->y0 = self->posY.i.hi + 2;
            }
            UnkPrimHelper(prim);
            break;

        case 1:
            UnkCollisionFunc3(&g_merman2_coll3);
            self->velocityY -= FIX(0.1875);
            prim = self->ext.merman2.prim;
            if (self->facingLeft) {
                prim->next->x1 = self->posX.i.hi - 3;
            } else {
                prim->next->x1 = self->posX.i.hi + 3;
            }
            prim->next->y0 = self->posY.i.hi + 2;
            UnkPrimHelper(prim);
            if (!(g_Timer % 10)) {
                prim->clut += 2;
                if (prim->clut > 0x29F) {
                    prim->drawMode = DRAW_HIDE;
                    self->step_s++;
                } else {
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(
                            E_MERMAN2_DYING, self, newEntity);
                        newEntity->facingLeft = self->facingLeft;
                        newEntity->params = prim->clut;
                        newEntity->zPriority = self->zPriority;
                    }
                }
            }
            CheckMermanEnteringWater(0x1B);
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            CreateExplosionPuff();
            DestroyEntity(self);
        }
        break;
    }
}

static u8 g_MediumWaterSplashAnim[] = {2, 19, 2, 20, 2, 21, 2, 22, 0};
static u8 g_explosion2anim[] = {7, 23, 7, 24, 7, 25, 255, 0};
static u8 g_FallingObject2Anim[] = {9, 26, 9, 27, 9, 28, 255, 0};
static u8 g_HighWaterSplashAnim[] = {
    4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 255, 0};
static Point32 g_Merman2XY[] = {
    {-0x3000, -0x54000},
    {-0x1000, -0x58000},
    {0x4000, -0x50000},
    {0x4000, -0x5c000},
    {0x4000, -0x5c000}};
static s16 g_MermanSplashXOffset[] = {-12, -8, 10, 13, 14, 0};
static u8 g_HighWaterSplashParams[] = {1, 3, 6, 8, 11, 13, 16};
static s16 g_Merman2posPtr[] = {-3, 3, -3, 3, -2, 2, -2, 0};
static s32 g_Merman2velPtr[] = {
    -0x3000, 0x3000, -0x2000, 0x2000, -0x1000, 0x1000, 0x0};

void EntityMermanFireSpit(Entity* self) {
    Primitive* prim;
    s32 primIndex;

    if (!self->step) {
        InitializeEntity(g_EInitWaterObject);
        self->zPriority += 4;
        self->animCurFrame = 0;
        self->hitboxState = 0;
        if (self->params) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
            if (primIndex != -1) {
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                prim = &g_PrimBuf[primIndex];
                self->ext.EntityMermanFireSpit.prim = prim;
                UnkPolyFunc2(prim);
                prim->tpage = 0x1A;
                prim->clut = 0x1FF;
                prim->u0 = 0;
                prim->u1 = 0x20;
                prim->u2 = prim->u0;
                prim->u3 = prim->u1;
                prim->v0 = 0;
                prim->v1 = prim->v0;
                prim->v2 = 0x20;
                prim->v3 = prim->v2;

                LOH(prim->next->r2) = 0x40;
                LOH(prim->next->b2) = 0x40;
                LOH(prim->next->u1) = 0;
                prim->next->b3 = 0x60;
                prim->next->x1 = self->posX.i.hi;
                prim->next->y0 = self->posY.i.hi;
                prim->priority = self->zPriority - 4;
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            } else {
                DestroyEntity(self);
                return;
            }
        }
    }

    if (self->params) {
        prim = self->ext.EntityMermanFireSpit.prim;
        UnkPrimHelper(prim);
        prim->next->b3 -= 4;
        LOH(prim->next->u1) -= 128;
        if (prim->next->b3 < 16) {
            prim->drawMode = DRAW_HIDE;
        }
    }

    self->ext.EntityMermanFireSpit.unk84++;
    if (!(self->ext.EntityMermanFireSpit.unk84 % 4)) {
        self->posY.i.hi++;
    }

    if (AnimateEntity(g_explosion2anim, self) == 0) {
        DestroyEntity(self);
    }
}

// medium sized water splash used with merman
void EntityMediumWaterSplash(Entity* self) {
    Entity* newEntity;

    if (!self->step) {
        InitializeEntity(g_EInitWaterSplash);
        self->animCurFrame = 0;
        if (self->facingLeft) {
            self->velocityX = FIX(2);
            return;
        }
        self->velocityX = FIX(-2);
        return;
    }
    AnimateEntity(g_MediumWaterSplashAnim, self);
    MoveEntity();
    if (self->flags & FLAG_DEAD) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0;
        }
        DestroyEntity(self);
    }
}

// Honestly probably some deep misunderstandings about the data types.
// Way too many LOW and such.
void EntityMermanWaterSplash(Entity* self) {
    // Could just be 8 s16's
    Point16 bro[2];
    Point16 dude[2];

    Entity* newEntity;
    Primitive* prim;
    s32 primIndex;
    u8 temp;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        break;

    case 1:
        primIndex = g_api.AllocPrimitives(PRIM_TILE, 4);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.mermanWaterSplash.prim = prim;

            for (i = 0; prim != NULL; i++, prim = prim->next) {
                prim->r0 = 64;
                prim->g0 = 64;
                prim->b0 = 160;
                prim->u0 = 2;
                prim->v0 = 2;
                prim->x0 = self->posX.i.hi + g_MermanSplashXOffset[i];
                prim->y0 = self->posY.i.hi - 12;
                LOW(dude[0]) = g_Merman2XY[i].x;
                prim->y1 = dude[0].y;
                prim->y3 = dude[0].x;
                LOW(dude[1]) = g_Merman2XY[i].y;
                prim->x2 = dude[1].y;
                prim->x3 = dude[1].x;
                prim->p1 = 0;
                prim->p3 = 1;
                prim->p2 = i % 2;
                prim->priority = self->zPriority + 2;
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        for (i = 0; i < 7; i++) {
            newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_HIGH_WATER_SPLASH, self, newEntity);
                newEntity->params = g_HighWaterSplashParams[i];
                newEntity->posX.i.hi += g_Merman2posPtr[i];
                newEntity->velocityX = g_Merman2velPtr[i];
                newEntity->zPriority = self->zPriority + 1;
            }
        }
        self->ext.mermanWaterSplash.unk84 = 0;
        self->ext.mermanWaterSplash.unk86 = 0;
        self->step++;
        break;

    case 2:
        temp = false;
        for (prim = self->ext.mermanWaterSplash.prim; prim != NULL;) {
            if (prim->p1) {
                prim = prim->next;
                continue;
            }
            temp |= true;
            bro[0].y = prim->x0;
            bro[0].x = prim->x1;
            bro[1].y = prim->y0;
            bro[1].x = prim->y2;
            dude[0].y = prim->y1;
            dude[0].x = prim->y3;
            dude[1].y = prim->x2;
            dude[1].x = prim->x3;
            LOW(bro[0]) += LOW(dude[0]);
            LOW(bro[1]) += LOW(dude[1]);
            LOW(dude[1]) += 0x2000;
            if ((LOW(dude[1]) > 0) && (prim->p2) && (prim->p3)) {
                if (bro[0].y > self->posX.i.hi) {
                    LOW(dude[0]) += 0x4000;
                } else {
                    LOW(dude[0]) -= 0x4000;
                }
                prim->p3 = 0;
            }
            if (prim->y0 & 0xFF00) {
                prim->drawMode |= DRAW_HIDE;
                prim->p1 = 1;
            }
            prim->x0 = bro[0].y;
            prim->x1 = bro[0].x;
            prim->y0 = bro[1].y;
            prim->y2 = bro[1].x;
            prim->x2 = dude[1].y;
            prim->x3 = dude[1].x;
            prim->y1 = dude[0].y;
            prim->y3 = dude[0].x;
            prim = prim->next;
        }
        if (!temp) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void EntityMerman2JumpAir(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitWaterObject);
        self->flags |= FLAG_UNK_2000;
        self->zPriority += 4;
        self->animCurFrame = 0;
        self->hitboxState = 0;
    }
    MoveEntity();
    self->velocityY += FIX(0.15625);
    if (AnimateEntity(g_FallingObject2Anim, self) == 0) {
        DestroyEntity(self);
    }
}

void EntityHighWaterSplash(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = ANIMSET_DRA(2);
        self->velocityY = FIX(-5);
        self->palette = PAL_FLAG(PAL_CC_MAGIC_HUD_EFFECT);
        self->drawMode = DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->palette = PAL_FLAG(0x18);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags |= FLAG_DRAW_OPACITY;
        self->opacity = 0xA0;
        self->scaleX = 0x100;
        self->scaleY = 0x1A0;
        self->ext.mermanWaterSplash.unk84 = self->params;
        self->ext.mermanWaterSplash.unk85 = 0x11;
        break;

    case 1:
        self->ext.mermanWaterSplash.unk85--;
        if (!--self->ext.mermanWaterSplash.unk84) {
            self->step++;
        }
        break;

    case 2:
        AnimateEntity(g_HighWaterSplashAnim, self);
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->scaleX += 6;
        self->scaleY -= 4;
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        if (!--self->ext.mermanWaterSplash.unk85) {
            self->velocityY = 0;
            self->step++;
        }
        break;

    case 3:
        if (AnimateEntity(g_HighWaterSplashAnim, self) == 0) {
            MoveEntity();
            self->velocityY += FIX(0.25);
            self->scaleX += 6;
            self->scaleY -= 4;
        }
        if (self->posY.i.hi > 256) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityDeadMerman(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitWaterObject);
        self->palette = self->params + 0xE;
        self->animCurFrame = 13;
        self->ext.merman.timer = 0x20;
        self->velocityY = FIX(0.0625);
        self->hitboxState = 0;
        self->drawFlags |= FLAG_DRAW_OPACITY;
        self->opacity = 0x80;
        self->flags |= FLAG_UNK_2000;
        return;
    }
    MoveEntity();
    self->velocityY += FIX(0.0625);
    self->opacity -= 2;
    if (!--self->ext.merman.timer) {
        DestroyEntity(self);
    }
}

void EntityMermanSpawner(Entity* self) {
    Entity* newEntity;
    s16 xVar;
    s16 yVar;

    if (!self->step) {
        InitializeEntity(g_EInitSpawner);
        self->flags |= FLAG_UNK_2000;
    }

    if (!(g_Timer % 0x40)) {
        Entity* player = &PLAYER;
        yVar = g_Tilemap.scrollY.i.hi + player->posY.i.hi;
        if (yVar >= 256) {
            xVar = g_Tilemap.scrollX.i.hi + player->posX.i.hi;
            xVar += Random() - 0x80;
            if (xVar < 0x40 || xVar > 0x2C0) {
                return;
            }
            yVar = 496;
            newEntity = AllocEntity(&g_Entities[160], &g_Entities[170]);
            if (newEntity != 0) {
                if (Random() & 1) {
                    CreateEntityFromCurrentEntity(E_MERMAN2, newEntity);
                    newEntity->params = Random() & 1;
                } else {
                    CreateEntityFromCurrentEntity(E_MERMAN, newEntity);
                }
                newEntity->posX.i.hi = xVar - g_Tilemap.scrollX.i.hi;
                newEntity->posY.i.hi = yVar - g_Tilemap.scrollY.i.hi;
            }
        }
    }
}
