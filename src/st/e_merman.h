// SPDX-License-Identifier: AGPL-3.0-or-later
typedef enum {
    MERMAN_INIT,
    MERMAN_SWIMMING_UP,
    MERMAN_SWIMMING = 3,
    MERMAN_JUMPING,
    MERMAN_WALKING_TOWARDS_PLAYER,
    MERMAN_SPIT_FIRE,
    MERMAN_LUNGE,
    MERMAN_FALLING,
    MERMAN_DYING,
} MermanSteps;

typedef enum {
    MERMAN_JUMPING_SETUP,
    MERMAN_JUMPING_UNDERWATER,
    MERMAN_JUMPING_IN_AIR,
    MERMAN_JUMPING_LANDING,
} MermanJumpingSubSteps;

typedef enum {
    MERMAN_WALKING_TOWARDS_START,
    MERMAN_WALKING_TOWARDS_PLAYER_WALKING,
} MermanWalkingTowardsPlayerSubSteps;

typedef enum {
    MERMAN_SPIT_FIRE_FACE_PLAYER,
    MERMAN_SPIT_FIRE_ATTACK,
} MermanSpitFireSubSteps;

typedef enum {
    MERMAN_LUNGE_START,
    MERMAN_LUNGE_SETUP,
    MERMAN_LUNGE_TOWARDS_PLAYER,
    MERMAN_LUNGE_STANDING,
} MermanLungeSubSteps;

typedef enum {
    MERMAN_DYING_SETUP,
    MERMAN_DYING_KNOCKEDBACK,
    MERMAN_DYING_END,
} MermanDyingSubSteps;

#define XY(x, y) x, y
static Point32 swimVelocities[] = {
    XY(FIX(0.5), FIX(-0.5)), XY(FIX(-0.5), FIX(-0.5)), XY(FIX(0.5), FIX(0.5)),
    XY(FIX(-0.5), FIX(0.5))};
static u8 walkDurations[] = {0x40, 0x30, 0x50, 0x40};
static s16 sensors1[] = {XY(0, 21), XY(0, 4), XY(4, -4), XY(-8, 0)};
static s16 sensors2[] = {XY(0, 11), XY(0, 4), XY(8, -4), XY(-16, 0)};
static s16 sensors3[] = {XY(0, 24), XY(0, 4), XY(8, -4), XY(-16, 0)};
static s16 sensors4[] = {XY(0, 21), XY(8, 0)};
static u8 anim1[] = {8, 1, 8, 2, 8, 3, 8, 2, 0};
static u8 unused_anim[] = {15, 8, 5, 9, 15, 10, 5, 9, 0};
static u8 anim2[] = {16, 1, 8, 4, 8, 5, 8, 6, 15, 7, 8, 4, 255, 0};
static u8 anim3[] = {3, 13, 3, 14, 3, 15, 3, 16, 3, 17, 3, 18, 3, 19, 3, 20, 0};
static u8 anim4[] = {11, 21, 14, 13, 11, 11, 14, 13, 0};
static u8 anim5[] = {1, 25, 1, 23, 9, 22, 4, 23, 3, 24, 8, 25, 255, 0};
static u8 anim6[] = {1, 15, 1, 16, 1, 17, 1, 18, 1, 19, 1, 20, 1, 13, 1, 14, 0};
static u8 anim7[] = {1, 26, 1, 27, 1, 28, 1, 29, 1, 30, 1, 31, 1, 32, 1, 33, 0};
static u8 anim8[] = {7, 34, 7, 35, 7, 36, 255, 0};
static s32 jumpAirXVels[] = {
    0,         FIX(-5.0 / 8), FIX(-1.25), FIX(-5.0 / 8), 0, FIX(5.0 / 8),
    FIX(1.25), FIX(5.0 / 8),  0x0};

void EntityMerman(Entity* self) {
    Entity* newEntity;
    Collider collider;
    s16 posX, posY;
    s32 colRet;
    s16* pos;
    u8 rnd;

    if (self->ext.merman.isUnderwater) {
        self->palette = self->ext.merman.palette;
    }
    if (self->ext.merman.ignoreCol && (self->step < MERMAN_FALLING)) {
        SetStep(MERMAN_FALLING);
    }

    if ((self->flags & FLAG_DEAD) && (self->step < MERMAN_DYING)) {
        PlaySfxPositional(SFX_MERMAN_DEATH);
        self->hitboxState = 0;
        if (self->step == MERMAN_LUNGE) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
            }
            DestroyEntity(self);
            return;
        }
        SetStep(MERMAN_DYING);
    }

    switch (self->step) {
    case MERMAN_INIT:
        InitializeEntity(g_EInitMerman);
        self->ext.merman.palette = 0x2B9;
        self->zPriority = 0xA9;
        self->velocityY = FIX(-1);
        self->palette = self->ext.merman.palette;
        self->hitboxWidth = 5;
        self->hitboxHeight = 17;
        break;

    case MERMAN_SWIMMING_UP:
        if (!self->step_s) {
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
        }
        AnimateEntity(anim4, self);
        MoveEntity();

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY -= 24;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_WATER)) {
            SetStep(MERMAN_SWIMMING);
        }
        break;

    case MERMAN_SWIMMING:
        if (!self->step_s) {
            self->hitboxWidth = 5;
            self->hitboxHeight = 17;
            rnd = Random() & 3;
            self->velocityX = swimVelocities[rnd].x;
            self->velocityY = swimVelocities[rnd].y;
            self->step_s++;
        }
        if (AnimateEntity(anim4, self) == 0) {
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
        if (self->ext.merman.timer2++ > 32) {
            self->ext.merman.timer2 = 0;
            self->step_s = 0;
            if ((GetDistanceToPlayerX() >= 48) && !(Random() & 1)) {
                SetStep(MERMAN_JUMPING);
            }
        }
        break;

    case MERMAN_JUMPING:
        switch (self->step_s) {
        case MERMAN_JUMPING_SETUP:
            self->velocityX = 0;
            self->velocityY = FIX(-8.5);
            self->step_s++;
            break;

        case MERMAN_JUMPING_UNDERWATER:
            MoveEntity();
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            posY -= 20;
            posY += g_Tilemap.scrollY.i.hi;
            pos = g_WaterXTbl;
            pos += (self->params & 0x100) >> 8;
            if (posY < pos[3]) {
                g_api.PlaySfx(NA_SE_EV_WATER_SPLASH);
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_MERMAN_WATER_SPLASH, self, newEntity);
                    newEntity->posY.i.hi -= 20;
                    newEntity->zPriority = self->zPriority;
                }
                self->step_s++;
            }
            break;

        case MERMAN_JUMPING_IN_AIR:
            AnimateEntity(anim3, self);
            if (!self->ext.merman.isUnderwater) {
                if (UnkCollisionFunc3(&sensors1) & 1) {
                    self->poseTimer = 0;
                    self->pose = 0;
                    self->step_s++;
                }
            } else {
                self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                               FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                MoveEntity();
                self->velocityY += FIX(0.25);
            }

            self->ext.merman.timer++;
            if (self->velocityY < 0) {
                if ((self->ext.merman.palette > 0x2B2) &&
                    !(self->ext.merman.timer % 4)) {
                    self->ext.merman.palette--;
                }
                self->palette = self->ext.merman.palette;
                newEntity = AllocEntity(&g_Entities[232], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_JUMP_AIR, self, newEntity);
                    newEntity->posX.i.hi += ((Random() & 3) * 4) - 6;
                    newEntity->velocityX = jumpAirXVels[self->pose - 1];
                }
            } else {
                self->palette = 0x2B2;
                if (self->velocityY > 0) {
                    CheckMermanEnteringWater(0x15);
                }
            }
            break;

        case MERMAN_JUMPING_LANDING:
            if (AnimateEntity(anim5, self) != 0) {
                break;
            }
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_WALKING_TOWARDS_PLAYER:
        switch (self->step_s) {
        case MERMAN_WALKING_TOWARDS_START:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }
            rnd = Random() & 3;
            self->ext.merman.timer2 = walkDurations[rnd];
            self->step_s++;
            break;

        case MERMAN_WALKING_TOWARDS_PLAYER_WALKING:
            AnimateEntity(anim1, self);
            colRet = UnkCollisionFunc2(&sensors4);
            if (colRet == 0xFF) {
                self->facingLeft ^= 1;
            }
            if (self->facingLeft) {
                self->velocityX = FIX(0.375);
            } else {
                self->velocityX = FIX(-0.375);
            }
            if (colRet & 0x80) {
                self->posX.val += self->velocityX;
            }
            if (!--self->ext.merman.timer2) {
                if (Random() & 1) {
                    SetStep(MERMAN_SPIT_FIRE);
                } else {
                    SetStep(MERMAN_LUNGE);
                }
            }
            if (CheckMermanEnteringWater(0x15)) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_SPIT_FIRE:
        switch (self->step_s) {
        case MERMAN_SPIT_FIRE_FACE_PLAYER:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
            break;

        case MERMAN_SPIT_FIRE_ATTACK:
            if (AnimateEntity(anim2, self) == 0) {
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            if (self->pose == 4 && !self->poseTimer) {
                PlaySfxPositional(SFX_FIREBALL_SHOT_C);
                newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_MERMAN_SPIT_FIRE, self, newEntity);
                    if (self->facingLeft) {
                        newEntity->posX.i.hi += 12;
                    } else {
                        newEntity->posX.i.hi -= 12;
                    }
                    newEntity->posY.i.hi -= 10;
                    newEntity->facingLeft = self->facingLeft;
                }
            }
        }
        break;

    case MERMAN_LUNGE:
        switch (self->step_s) {
        case MERMAN_LUNGE_START:
            if (AnimateEntity(anim5, self) == 0) {
                self->step_s++;
            }
            break;

        case MERMAN_LUNGE_SETUP:
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }

            self->velocityY = FIX(-2);
            self->ext.merman.timer2 = 64;
            self->animCurFrame = 12;
            self->hitboxWidth = 18;
            self->hitboxHeight = 4;
            self->step_s++;
            break;

        case MERMAN_LUNGE_TOWARDS_PLAYER:
            posX = self->posX.i.hi;
            posY = self->posY.i.hi + 8;
            if (self->facingLeft) {
                posX += 24;
            } else {
                posX -= 24;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                self->velocityX = 0;
            }
            UnkCollisionFunc5(&sensors2);
            if (self->facingLeft) {
                self->velocityX -= FIX(0.03125);
            } else {
                self->velocityX += FIX(0.03125);
            }
            if (!--self->ext.merman.timer2) {
                self->velocityX = 0;
                self->velocityY = FIX(2);
                self->posY.i.hi -= 9;
                UnkCollisionFunc3(&sensors1);
                self->pose = 2;
                self->poseTimer = 0;
                self->hitboxWidth = 5;
                self->hitboxHeight = 17;
                self->step_s++;
            }
            CheckMermanEnteringWater(11);
            if (self->ext.merman.isUnderwater) {
                self->ext.merman.ignoreCol = 1;
            }
            break;

        case MERMAN_LUNGE_STANDING:
            UnkCollisionFunc3(&sensors1);
            if (AnimateEntity(anim5, self) == 0) {
                self->velocityY = 0;
                SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
            }
            CheckMermanEnteringWater(11);
            if (self->ext.merman.isUnderwater) {
                self->ext.merman.ignoreCol = 1;
            }
        }
        break;

    case MERMAN_FALLING:
        if (!self->step_s) {
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.25);
        if (!(CheckMermanEnteringWater(21)) &&
            !(self->ext.merman.isUnderwater)) {
            self->ext.merman.ignoreCol = 0;
            SetStep(MERMAN_WALKING_TOWARDS_PLAYER);
        }
        break;

    case MERMAN_DYING:
        switch (self->step_s) {
        case MERMAN_DYING_SETUP:
            self->ext.merman.palette = 0x2BC;
            self->velocityY = 0;
            self->step_s++;

        case MERMAN_DYING_KNOCKEDBACK:
            if (UnkCollisionFunc3(&sensors3) & 1) {
                if (GetSideToPlayer() & 1) {
                    self->velocityX = FIX(0.5);
                } else {
                    self->velocityX = FIX(-0.5);
                }
                self->step_s++;
            }
            // fallthrough

        case MERMAN_DYING_END:
            AnimateEntity(anim6, self); // spinning
            MoveEntity();
            self->palette = self->ext.merman.palette;
            if (!(g_Timer % 8)) {
                self->ext.merman.palette++;
                if (self->ext.merman.palette == 0x2C0) {
                    PlaySfxPositional(SFX_FM_EXPLODE_B);
                    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(E_MERMAN_DYING, self, newEntity);
                        newEntity->params = 2;
                    }
                }
            }
            if (self->ext.merman.palette > 0x2C4) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

// fireball shot by merman
void EntityMermanFireball(Entity* self) {
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitMermanFireball);
        self->animCurFrame = 0;
        self->hitboxWidth = 6;
        self->hitboxHeight = 3;

        if (self->facingLeft) {
            self->velocityX = FIX(1.5);
        } else {
            self->velocityX = FIX(-1.5);
        }

        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
        self->scaleX = 0x80;
        self->scaleY = 0x80;

        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_GREY_PUFF, self, entity);
            entity->ext.destructAnim.index = 4;
            entity->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
            entity->zPriority = self->zPriority + 8;
            entity->scaleX = 192;
            entity->scaleY = 192;
        }
    } else {
        AnimateEntity(anim7, self);
        MoveEntity();

        if (self->scaleX < 0x100) {
            self->scaleX += 8;
            self->scaleY = self->scaleX;
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
}

void EntityMermanJumpAir(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitMerman);
        self->zPriority += 4;
        self->animCurFrame = 0;
        self->hitboxState = 0;
        self->flags |= FLAG_UNK_2000;
    }
    MoveEntity();
    self->velocityY += FIX(5.0 / 32.0);
    if (AnimateEntity(anim8, self) == 0) {
        DestroyEntity(self);
    }
}

static s32 explosionYVels[] = {
    FIX(-1), FIX(-1.5), FIX(-1.5), FIX(-1.5), FIX(-3)};
static u8 explosionFrames[] = {1, 9, 21, 43};
static u16 explosionDurations[] = {16, 24, 42, 47};

// part of explosion when merman dies
void EntityMermanExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->palette = PAL_FLAG(0x2BB);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = explosionFrames[self->params];
        self->velocityY = explosionYVels[self->params];
        self->step++;
        return;
    } else {
        self->posY.val += self->velocityY;
        self->poseTimer++;
    }

    if (!(self->poseTimer % 2)) {
        self->animCurFrame++;
    }

    if (self->poseTimer > explosionDurations[self->params]) {
        DestroyEntity(self);
    }
}
