// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"
#include <scratchpad.h>

extern EInit g_EInitFrozenHalf;
extern EInit g_EInitFrozenHalfOrbitIcicle;
extern EInit g_EInitFrozenHalfThrownChunk;
extern EInit g_EInitFrozenHalfBlizzard;
extern EInit g_EInitFrozenHalfFallingIce;
extern EInit g_EInitParticle;

static AnimateEntityFrame anim_hair_flick[] = {
    {0x07, 0x02}, {0x07, 0x03}, {0x07, 0x04}, {0x07, 0x05}, {0x07, 0x06},
    {0x07, 0x07}, {0x07, 0x08}, {0x30, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_move_towards_stop[] = {
    {0x0A, 0x0A}, {0x04, 0x06}, {0x04, 0x07},
    {0x04, 0x08}, {0x01, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_move_toward[] = {
    {0x05, 0x0A}, {0x02, 0x06}, {0x02, 0x07},
    {0x02, 0x08}, {0x01, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_move_away_stop[] = {
    {0x06, 0x02}, {0x05, 0x04}, {0x04, 0x05}, {0x04, 0x06},
    {0x04, 0x07}, {0x04, 0x08}, {0x01, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_move_away[] = {
    {0x03, 0x02}, {0x03, 0x04}, {0x02, 0x05}, {0x02, 0x06},
    {0x02, 0x07}, {0x02, 0x08}, {0x01, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_cast_blizzard[] = {
    {0x06, 0x0F}, {0x08, 0x10}, {0x07, 0x11}, {0x04, 0x12},
    {0x04, 0x13}, {0x04, 0x14}, {0x01, 0x15}, POSE_END,
};

// This basically plays the end of the cast animation in reverse to lower hands
static AnimateEntityFrame anim_end_blizzard[] = {
    {0x01, 0x15}, {0x03, 0x14}, {0x03, 0x13}, {0x03, 0x12},
    {0x03, 0x11}, {0x01, 0x01}, POSE_END,
};

static AnimateEntityFrame anim_orbit_icicle[] = {
    {0x01, 0x18}, {0x01, 0x19}, {0x01, 0x1A}, {0x01, 0x1B}, POSE_LOOP(0),
};

static AnimateEntityFrame anim_orbit_icicle_death[] = {
    {0x03, 0x1A},
    {0x01, 0x19},
    {0x01, 0x18},
    POSE_END,
};

static AnimateEntityFrame anim_falling_ice[] = {
    {0x01, 0x1C},
    {0x01, 0x1D},
    POSE_LOOP(0),
};

static AnimateEntityFrame anim_thrown_chunk[] = {
    {0x01, 0x1E},
    {0x01, 0x1F},
    POSE_LOOP(0),
};

// X positions for icicles which fall from above during Blizzard attack
static s16 falling_icicle_posX[] = {
    0x0020, 0x00A0, 0x0030, 0x00C0, 0x0050, 0x0068, 0x00D0, 0x0040,
};

static SVECTOR blizzard_vec_a = {.vx = 0xFFC0, .vy = 0x0000, .vz = 0xFFC0};
static SVECTOR blizzard_vec_b = {.vx = 0x0040, .vy = 0x0000, .vz = 0xFFC0};
static SVECTOR blizzard_vec_c = {.vx = 0xFFC0, .vy = 0x0000, .vz = 0x0040};
static SVECTOR blizzard_vec_d = {.vx = 0x0040, .vy = 0x0000, .vz = 0x0040};

void EntityFrozenHalf(Entity* self) {
    Primitive* prim;
    s32 i;
    s32 j;
    s32 posX;
    s32 posY;
    Entity* entity;
    s32 animResult;
    s16 angle;
    s32 primIndex;

    enum Step {
        INIT = 0,
        IDLE = 3,
        PLAYER_AGGRO = 5,
        ATTACK_THROW_CHUNK = 6,
        MOVE = 7,
        ATTACK_BLIZZARD = 8,
        HURT = 10,
        DEATH = 16,
        DEBUG = 255,
    };

    if (g_Timer & 1) {
        self->palette = 0x200;
    } else {
        self->palette = 0x201;
    }

    FntPrint("step %x\n", self->step);
    FntPrint("step_s %x\n", self->step_s);
    if (self->step & 1 && self->hitFlags & 3) {
        SetStep(HURT);
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        PlaySfxPositional(SFX_FROZEN_HALF_DEATH);
        if (self->ext.frozenHalf.entity != NULL) {
            entity = self->ext.frozenHalf.entity;
            DestroyEntity(entity);
        }
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitFrozenHalf);
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        entity = self + 1;
        CreateEntityFromEntity(E_FROZEN_HALF_ORBIT_ICICLE, self, entity);
        SetStep(IDLE);
        break;
    case IDLE:
        self->facingLeft = GetSideToPlayer() & 1;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(PLAYER_AGGRO);
        }
        break;
    case PLAYER_AGGRO:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }

        MoveEntity();
        self->facingLeft = GetSideToPlayer() & 1;
        angle = self->ext.frozenHalf.angle += 0x20;
        angle &= 0xFFF;
        self->velocityY = rsin(angle) * 0x10;
        if (self->ext.frozenHalf.moveUpwards) {
            self->velocityY += FIX(0.125);
        } else {
            self->velocityY -= FIX(0.125);
        }

        AnimateEntity(anim_hair_flick, self);
        if (angle > 0x600) {
            self->pose = 0;
            self->poseTimer = 0;
            self->animCurFrame = 1;
        }

        if (!(self->ext.frozenHalf.angle & 0x3FF)) {
            entity = &PLAYER;
            if (GetDistanceToPlayerX() < 0x68 &&
                entity->facingLeft != self->facingLeft) {
                self->ext.frozenHalf.moveAwayFromPlayer = true;
                SetStep(MOVE);
            }

            if (GetDistanceToPlayerX() > 0x50 &&
                entity->facingLeft == self->facingLeft) {
                self->ext.frozenHalf.moveAwayFromPlayer = false;
                SetStep(MOVE);
            }
        }

        if (!(self->ext.frozenHalf.angle & 0xFFF)) {
            if (self->posY.i.hi < 0x60) {
                self->ext.frozenHalf.moveUpwards = true;
            } else {
                self->ext.frozenHalf.moveUpwards = false;
            }
        }
        break;
    case MOVE:
        switch (self->step_s) {
        case 0:
            self->velocityY = 0;
            self->ext.frozenHalf.timer = 0x40;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->ext.frozenHalf.moveAwayFromPlayer) {
                self->animCurFrame = 0xB;
            } else {
                self->animCurFrame = 9;
            }

            if (self->facingLeft ^ self->ext.frozenHalf.moveAwayFromPlayer) {
                self->velocityX -= FIX(0.0625);
                if (self->velocityX <= FIX(-1.0)) {
                    self->velocityX = FIX(-1.0);
                }
            } else {
                self->velocityX += FIX(0.0625);
                if (self->velocityX >= FIX(1.0)) {
                    self->velocityX = FIX(1.0);
                }
            }

            if (!self->ext.frozenHalf.moveAwayFromPlayer) {
                if (GetDistanceToPlayerX() < 0x48) {
                    SetSubStep(2);
                }
            }

            if (self->ext.frozenHalf.moveAwayFromPlayer &&
                GetDistanceToPlayerX() > 0x70) {
                SetSubStep(2);
            }

            if (!--self->ext.frozenHalf.timer) {
                SetSubStep(3);
            }
            break;
        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 8;

            if (self->ext.frozenHalf.moveAwayFromPlayer) {
                animResult = AnimateEntity(anim_move_away, self);
            } else {
                animResult = AnimateEntity(anim_move_toward, self);
            }

            if (!animResult) {
                self->ext.frozenHalf.moveAwayFromPlayer ^= 1;
                SetSubStep(1);
            }

            break;
        case 3:
            MoveEntity();
            self->velocityX -= self->velocityX / 16;

            if (self->ext.frozenHalf.moveAwayFromPlayer) {
                animResult = AnimateEntity(anim_move_away_stop, self);
            } else {
                animResult = AnimateEntity(anim_move_towards_stop, self);
            }

            if (!animResult) {
                // Alternate between throwing ice chunk and casting blizzard
                if (self->ext.frozenHalf.castBlizzard) {
                    if (self->posX.i.hi & 0xFF00) {
                        SetStep(MOVE);
                    } else {
                        SetStep(ATTACK_BLIZZARD);
                    }
                } else {
                    SetStep(ATTACK_THROW_CHUNK);
                }
                self->ext.frozenHalf.castBlizzard ^= 1;
            }
            break;
        }
        break;
    case ATTACK_THROW_CHUNK:
        switch (self->step_s) {
        case 0:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                PlaySfxPositional(SFX_GLASS_SHARDS);
                CreateEntityFromEntity(
                    E_FROZEN_HALF_THROWN_CHUNK, self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi += 0x10;
                } else {
                    entity->posX.i.hi -= 0x10;
                }
                entity->posY.i.hi -= 0x10;
                entity->facingLeft = self->facingLeft;
                self->ext.frozenHalf.entity = entity;
            } else {
                self->ext.frozenHalf.entity = NULL;
                SetStep(PLAYER_AGGRO);
                break;
            }

            self->animCurFrame = 0xD;
            self->step_s++;
            break;
        case 1:
            entity = self->ext.frozenHalf.entity;
            if (entity->flags & FLAG_DEAD) {
                self->ext.frozenHalf.entity = NULL;
                SetStep(PLAYER_AGGRO);
            } else if (!(entity->drawFlags & ENTITY_SCALEX)) {
                PlaySfxPositional(SFX_FROZEN_HALF_ATTACK);
                PlaySfxPositional(SFX_GLASS_SHARDS);
                self->ext.frozenHalf.entity = NULL;
                self->ext.frozenHalf.timer = 0x20;
                self->step_s++;
            }

            break;
        case 2:
            self->animCurFrame = 0xE;
            if (!--self->ext.frozenHalf.timer) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case ATTACK_BLIZZARD:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 1;
            if (self->posY.i.hi < 0x60) {
                self->step_s++;
            } else {
                self->posY.i.hi--;
            }
            break;
        case 1:
            if (!AnimateEntity(anim_cast_blizzard, self)) {
                PlaySfxPositional(SFX_FROZEN_HALF_MAXIMUM_POWER);
                PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                self->ext.frozenHalf.timer = 0x40;
                self->step_s++;
            }
            break;
        case 2:
            if (g_Timer & 2) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_FROZEN_HALF_FROST_MIST, self, entity);
                    entity->posY.i.hi -= 0x20;
                    entity->params = g_Timer & 1;
                    if (!entity->params) {
                        entity->velocityX =
                            ((rand() & PSP_RANDMASK) * 2) - 0x8000;
                    } else {
                        entity->velocityX = (rand() & PSP_RANDMASK) - 0x4000;
                    }
                }
            }

            if (!--self->ext.frozenHalf.timer) {
                self->step_s++;
            }

            break;
        case 3:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_FROZEN_HALF_BLIZZARD, self, entity);
                entity->posY.i.hi -= 0x28;
                entity->facingLeft = self->facingLeft;
                entity->zPriority = self->zPriority - 1;
                self->ext.frozenHalf.entity = entity;
                self->step_s++;
                PlaySfxPositional(SFX_TRANSFORM_3X);
            } else {
                self->ext.frozenHalf.entity = NULL;
                SetSubStep(5);
                break;
            }
            // fallthrough
        case 4:
            entity = self->ext.frozenHalf.entity;
            if (entity->entityId != E_FROZEN_HALF_BLIZZARD) {
                self->ext.frozenHalf.entity = NULL;
                SetSubStep(5);
            }
            break;
        case 5:
            if (!AnimateEntity(anim_end_blizzard, self)) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case HURT:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = 0;
            self->ext.frozenHalf.timer = 0x10;
            self->animCurFrame = 0xC;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 0x20;
            if (!--self->ext.frozenHalf.timer) {
                SetStep(PLAYER_AGGRO);
            }
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            // Kill off the orbiting icicle
            entity = self + 1;
            entity->step = DEATH;
            entity->flags |= FLAG_UNK_2000;

            self->hitboxState = 0;
            if (self->facingLeft) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = 0;
            self->ext.frozenHalf.timer = 0x10;
            self->animCurFrame = 0xC;
            self->step_s++;
            // fallthrough
        case 1:
            MoveEntity();
            self->velocityX -= self->velocityX / 0x20;
            if (!--self->ext.frozenHalf.timer) {
                self->step_s++;
            }
            break;
        case 2:
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x200);
            if (primIndex == -1) {
                DestroyEntity(self);
                return;
            }

            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            self->ext.frozenHalf.prim = prim = &g_PrimBuf[primIndex];
            posX = self->posX.i.hi;
            posY = self->posY.i.hi;
            // BUG! This is a reassignment of above line and only required for
            // PSP match
            prim = self->ext.frozenHalf.prim;
            prim->tpage = 0x12;
            prim->clut = 0x200;

            if (self->facingLeft) {
                prim->u0 = prim->u2 = 0xA0;
                prim->u1 = prim->u3 = 0x80;
            } else {
                prim->u0 = prim->u2 = 0x80;
                prim->u1 = prim->u3 = 0xA0;
            }

            prim->v0 = prim->v1 = 0;
            prim->v2 = prim->v3 = 0x30;
            prim->x0 = prim->x2 = posX - 0xF;
            prim->x1 = prim->x3 = posX + 0x11;
            prim->y0 = prim->y1 = posY - 0x15;
            prim->y2 = prim->y3 = posY + 0x1B;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
            for (i = 0; i < 0x18; i++) {
                for (j = 0; j < 0x10; j++) {
                    prim->tpage = 0x12;
                    prim->clut = 0x200;
                    if (self->facingLeft) {
                        prim->u0 = prim->u2 = 0xA0 - (j * 2);
                        prim->u1 = prim->u3 = 0x9E - (j * 2);
                    } else {
                        prim->u0 = prim->u2 = 0x80 + (j * 2);
                        prim->u1 = prim->u3 = 0x82 + (j * 2);
                    }

                    prim->v0 = prim->v1 = 0x2E - (i * 2);
                    prim->v2 = prim->v3 = 0x30 - (i * 2);
                    prim->x0 = prim->x2 = posX - 0xF + (j * 2);
                    prim->x1 = prim->x3 = posX - 0xF + (j * 2) + 2;
                    prim->y0 = prim->y1 = posY + 0x1B - (i * 2) - 2;
                    prim->y2 = prim->y3 = posY + 0x1B - (i * 2);

                    PGREY(prim, 0) = 0x60;
                    LOW(prim->r1) = LOW(prim->r0);
                    LOW(prim->r2) = LOW(prim->r0);
                    LOW(prim->r3) = LOW(prim->r0);
                    prim->p3 = 0x50;
                    prim->priority = self->zPriority;
                    prim->priority++;
                    prim->drawMode = DRAW_HIDE | DRAW_UNK02;
                    prim = prim->next;
                }
            }

            while (prim != NULL) {
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }

            self->animCurFrame = 0;
            self->ext.frozenHalf.timer = 1;
            self->ext.frozenHalf.deathPrimCount = 0;
            PlaySfxPositional(SFX_GLASS_SHARDS);
            self->step_s++;
            break;
        case 3:
            if (!--self->ext.frozenHalf.timer) {
                self->ext.frozenHalf.timer = 6;
                prim = self->ext.frozenHalf.prim;
                prim->v2 = prim->v3 -= 2;
                prim->y2 = prim->y3 -= 2;

                self->ext.frozenHalf.deathPrimCount++;
                if (self->ext.frozenHalf.deathPrimCount >= 0x17) {
                    self->step_s++;
                }
            }
            // fallthrough
        case 4:
            prim = self->ext.frozenHalf.prim;
            prim = prim->next;
            animResult = 1;
            for (i = 0; i < self->ext.frozenHalf.deathPrimCount * 0x10; i++) {
                if (!prim->r0) {
                    prim->drawMode = DRAW_HIDE;
                    prim = prim->next;
                } else {
                    animResult = 0;
                    posX = prim->x0 << 8;
                    posY = prim->y0 << 8;
                    posX += prim->p2;
                    posY += (prim->p3 * 0x10) - 0x400;
                    if (self->facingLeft) {
                        posX -= ((prim->u0 - 0x90) * 0x18);
                    } else {
                        posX += ((prim->u0 - 0x90) * 0x18);
                    }
                    prim->x0 = posX >> 8;
                    prim->p2 = posX & 0xFF;
                    prim->y0 = posY >> 8;
                    if (prim->p3) {
                        prim->p3 -= 2;
                    }
                    prim->x2 = prim->x0;
                    prim->x1 = prim->x3 = prim->x0 + 2;
                    prim->y1 = prim->y0;
                    prim->y2 = prim->y3 = prim->y0 + 2;

                    prim->r0 -= 2;
                    PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                        prim->g0 = prim->b0 = prim->r0;

                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim = prim->next;
                }
            }

            if (animResult) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    case DEBUG:
#include "../pad2_anim_debug.h"
    }
}

// Magical orbiting icicle object
void EntityFrozenHalfOrbitIcicle(Entity* self) {
    Entity* parent;
    s32 posX;
    s32 posY;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalfOrbitIcicle);
        // fallthrough
    case 1:
        // Standard routine
        MoveEntity();
        AnimateEntity(anim_orbit_icicle, self);
        self->ext.frozenHalf.angle += 0x40;
        parent = self - 1;
        if (parent->entityId != E_FROZEN_HALF) {
            DestroyEntity(self);
            return;
        }

        posX = parent->posX.val;
        posY = parent->posY.val;
        angle = self->ext.frozenHalf.angle;

        posX += rcos(angle) << 9;
        posY += (rsin(angle / 2)) << 7;
        self->posX.val = posX;
        self->posY.val = posY;
        break;
    case 16:
        // Death routine
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->pose = 0;
            self->poseTimer = 0;
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(anim_orbit_icicle_death, self);
            self->scaleX = self->scaleY -= 0x10;
            if (!self->scaleX) {
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

// A large chunk of ice that is thrown by the Frozen Half
void EntityFrozenHalfThrownChunk(Entity* self) {
    Entity* player;
    s16 angle;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalfThrownChunk);
        self->drawFlags = ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0;
        self->drawFlags |= ENTITY_ROTATE;
        // fallthrough
    case 1:
        AnimateEntity(anim_thrown_chunk, self);
        self->rotate += ROT(360 / 256.0);
        self->scaleY = self->scaleX += 8;
        if (self->scaleX >= 0x100) {
            self->drawFlags = ENTITY_ROTATE;
            self->palette = PAL_FLAG(PAL_FILL_WHITE);
            self->step++;
        }
        break;
    case 2:
        self->palette = 0x200;
        player = &PLAYER;
        angle = GetAngleBetweenEntities(self, player);
        self->velocityX = rcos(angle) * 0x28;
        self->velocityY = rsin(angle) * 0x28;
        if (self->facingLeft) {
            if (self->velocityX > 0) {
                self->velocityX = FIX(-0.625);
            }
        } else {
            if (self->velocityX < 0) {
                self->velocityX = FIX(0.625);
            }
        }
        self->step++;
        break;
    case 3:
        AnimateEntity(anim_thrown_chunk, self);
        MoveEntity();
        self->rotate += ROT(360 / 64.0);
        break;
    }
}

Primitive* UnkRecursivePrimFunc1(
    SVECTOR* p0, SVECTOR* p1, SVECTOR* p2, SVECTOR* p3, Primitive* srcPrim,
    s32 iterations, Primitive* dstPrim, u8* dataPtr);

// Manages the blizzard storm and spawns falling ice
void EntityFrozenHalfBlizzard(Entity* self) {
#ifdef VERSION_PC
    u8 sp[SP_LEN];
#endif
    SVECTOR rot;
    VECTOR trans;
    MATRIX matrix;
    Primitive* prim;
    Primitive* nextPrim;
    Entity* entity;
    s32 posXOffset;
    s32 primIndex;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalfBlizzard);
        self->scaleX = self->scaleY = 0;
        self->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x41);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.frozenHalf.prim = prim;
        prim->tpage = 0x12;
        prim->clut = 0x202;
        prim->u0 = prim->u2 = 0;
        prim->u1 = prim->u3 = 0x40;
        prim->v0 = prim->v1 = 0x80;
        prim->v2 = prim->v3 = 0xC0;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        // fallthrough
    case 1:
        switch (self->step_s) {
        case 0:
            self->rotate += ROT(360 / 64.0);
            self->scaleX += 0x80;
            self->scaleY = self->scaleX;
            if (self->scaleX >= 0x2000) {
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            self->velocityY -= FIX(0.25);
            self->rotate += ROT(360 / 32.0);
            self->scaleX += 0x200;
            if (self->posY.i.hi < -0x60) {
                SetStep(2);
            }
            break;
        }

        SetGeomScreen(0x100);
        SetGeomOffset(self->posX.i.hi, 0x80);

        rot.vx = 0;
        rot.vy = self->rotate;
        rot.vz = 0;
        RotMatrixYXZ(&rot, &matrix);

        trans.vx = 0;
        trans.vy = -(0x80 - self->posY.i.hi);
        trans.vz = 0x100;
        TransMatrix(&matrix, &trans);

        trans.vx = self->scaleX;
        trans.vy = self->scaleX;
        trans.vz = self->scaleX;
        ScaleMatrix(&matrix, &trans);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);

        prim = self->ext.frozenHalf.prim;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        nextPrim = prim->next;
        nextPrim = UnkRecursivePrimFunc1(
            &blizzard_vec_a, &blizzard_vec_b, &blizzard_vec_c, &blizzard_vec_d,
            prim, 2, nextPrim, (u8*)SPAD(0));
        prim->drawMode = DRAW_HIDE;
        while (nextPrim != NULL) {
            nextPrim->drawMode = DRAW_HIDE;
            nextPrim = nextPrim->next;
        }
        break;
    case 2:
        prim = self->ext.frozenHalf.prim;
        while (prim != NULL) {
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.frozenHalf.timer = 0x200;
        self->step++;
        break;
    case 3:
        entity = &PLAYER;
        posXOffset = -0x80;
        if (entity->velocityX > 0) {
            posXOffset += 0x40;
        }

        if (entity->velocityX < 0) {
            posXOffset -= 0x40;
        }

        if (!(self->ext.frozenHalf.timer & 0xF)) {
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(
                    E_FROZEN_HALF_FALLING_ICE, entity);
                entity->posY.i.hi = -0x20;
                entity->posX.i.hi =
                    falling_icicle_posX[self->ext.frozenHalf.iciclePositionIdx];
                entity->params = 0;
            }
            self->ext.frozenHalf.iciclePositionIdx += 1;
            self->ext.frozenHalf.iciclePositionIdx &= 7;
        }

        entity = AllocEntity(&g_Entities[64], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_FROZEN_HALF_FALLING_ICE, entity);
            entity->posY.i.hi = -0x10;
            entity->posX.i.hi = (Random() * 2) + posXOffset;
            entity->params = 1;
        }

        if (!(self->ext.frozenHalf.timer & 0x1F)) {
            g_api.PlaySfx(SFX_FROZEN_HALF_BLIZZARD);
        }

        if (!--self->ext.frozenHalf.timer) {
            DestroyEntity(self);
        }
        break;
    }
}

// Spawned by the Blizzard entity above, these fall from top of screen
void EntityFrozenHalfFallingIce(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrozenHalfFallingIce);
        if (self->params) {
            self->hitboxState = 0;
            self->animCurFrame = 0x16;
            self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
            self->step = 2;
            self->velocityX = FIX(0.75);
            self->velocityY = FIX(5.0);
            return;
        }

        self->drawFlags = ENTITY_ROTATE;
        self->velocityX = FIX(0.5);
        self->velocityY = FIX(4.0);
        // fallthrough
    case 1:
        MoveEntity();
        AnimateEntity(anim_falling_ice, self);
        self->velocityY += FIX(0.0625);
        self->rotate += ROT(360 / 128.0);

        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }

        break;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.0625);

        if (self->posY.i.hi > 0x100) {
            DestroyEntity(self);
            return;
        }

        break;
    }
}

static AnimateEntityFrame anim_mist_a[] = {
    {0x02, 0x01}, {0x02, 0x02}, {0x02, 0x03}, {0x02, 0x04}, {0x02, 0x05},
    {0x02, 0x06}, {0x02, 0x07}, {0x02, 0x08}, {0x02, 0x09}, {0x02, 0x0A},
    {0x02, 0x0B}, {0x02, 0x0C}, {0x02, 0x0D}, {0x02, 0x0E}, {0x02, 0x0F},
    {0x02, 0x10}, {0x02, 0x11}, {0x02, 0x12}, {0x02, 0x13}, {0x02, 0x14},
    {0x02, 0x15}, {0x02, 0x16}, {0x02, 0x17}, {0x02, 0x18}, POSE_END,
};
static AnimateEntityFrame anim_mist_b[] = {
    {0x03, 0x01}, {0x03, 0x02}, {0x03, 0x03}, {0x03, 0x04}, {0x03, 0x05},
    {0x03, 0x06}, {0x03, 0x07}, {0x03, 0x08}, {0x03, 0x09}, {0x03, 0x0A},
    {0x03, 0x0B}, {0x03, 0x0C}, {0x03, 0x0D}, POSE_END,
};

// Summoned above Frozen Half just before the Blizzard attack commences
void EntityFrozenHalfFrostMist(Entity* self) {
    s32 animResult;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        if (!self->params) {
            self->animSet = 0xE;
            self->unk5A = 0x5C;
            self->velocityY = FIX(1.0);
        } else {
            self->animSet = 5;
            self->velocityY = FIX(1.25);
        }

        self->blendMode = BLEND_QUARTER | BLEND_TRANSP;
        self->palette = PAL_FLAG(0x202);
        self->drawFlags = ENTITY_OPACITY;
        self->opacity = 0x80;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= self->velocityY / 0x40;
        self->velocityX += self->velocityX / 0x20;

        if (!self->params) {
            animResult = AnimateEntity(anim_mist_b, self);
        } else {
            animResult = AnimateEntity(anim_mist_a, self);
        }

        self->opacity -= 1;
        if (!self->opacity) {
            animResult = 0;
        }

        if (!animResult) {
            DestroyEntity(self);
        }

        break;
    }
}
