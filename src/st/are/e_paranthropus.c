// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitParanthropus;
extern EInit g_EInitParanthropusThrownBone;
extern EInit g_EInitParanthropusBoneHitbox;
extern EInit g_EInitInteractable;

static s16 sensors_ground[] = {0, 27, 0, 4, 16, -4, -32, 0};
static s16 skull_sensors_ground[] = {0, 8, 0, 4, 16, -4, -32, 0};

static AnimateEntityFrame anim_walk[] = {
    {.duration = 25, .pose = 0x01},
    {.duration = 9, .pose = 0x02},
    {.duration = 9, .pose = 0x03},
    {.duration = 25, .pose = 0x04},
    {.duration = 9, .pose = 0x03},
    {.duration = 9, .pose = 0x02},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_swing_bone[] = {
    {.duration = 9, .pose = 0x07},  {.duration = 9, .pose = 0x08},
    {.duration = 9, .pose = 0x09},  {.duration = 31, .pose = 0x0A},
    {.duration = 4, .pose = 0x0B},  {.duration = 4, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},  {.duration = 2, .pose = 0x0E},
    {.duration = 2, .pose = 0x0F},  {.duration = 2, .pose = 0x10},
    {.duration = 2, .pose = 0x0F},  {.duration = 2, .pose = 0x10},
    {.duration = 31, .pose = 0x0F}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_throw_bone[] = {
    {.duration = 6, .pose = 0x11},
    {.duration = 7, .pose = 0x12},
    {.duration = 8, .pose = 0x13},
    {.duration = 9, .pose = 0x14},
    {.duration = 6, .pose = 0x15},
    {.duration = 6, .pose = 0x16},
    {.duration = 6, .pose = 0x17},
    {.duration = 32, .pose = 0x18},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_dive[] = {
    {.duration = 6, .pose = 0x01},  {.duration = 4, .pose = 0x19},
    {.duration = 5, .pose = 0x1A},  {.duration = 5, .pose = 0x1B},
    {.duration = 8, .pose = 0x1C},  {.duration = 6, .pose = 0x1D},
    {.duration = 6, .pose = 0x1E},  {.duration = 6, .pose = 0x1F},
    {.duration = 1, .pose = 0x20},  {.duration = 1, .pose = 0x1F},
    {.duration = 1, .pose = 0x20},  {.duration = 1, .pose = 0x1F},
    {.duration = 33, .pose = 0x20}, {.duration = 6, .pose = 0x1E},
    {.duration = 6, .pose = 0x1D},  {.duration = 6, .pose = 0x1C},
    {.duration = 6, .pose = 0x1B},  {.duration = 6, .pose = 0x1A},
    {.duration = 6, .pose = 0x19},  POSE_END,
};
static AnimateEntityFrame anim_unused_idle[] = {
    {.duration = 6, .pose = 0x05},
    {.duration = 20, .pose = 0x06},
    {.duration = 6, .pose = 0x01},
    POSE_END,
};
static AnimateEntityFrame anim_belly_ground_recovery[] = {
    {.duration = 16, .pose = 0x21},
    {.duration = 6, .pose = 0x20},
    {.duration = 16, .pose = 0x21},
    {.duration = 6, .pose = 0x20},
    {.duration = 16, .pose = 0x21},
    {.duration = 6, .pose = 0x20},
    {.duration = 6, .pose = 0x1F},
    {.duration = 6, .pose = 0x1E},
    {.duration = 6, .pose = 0x1D},
    {.duration = 6, .pose = 0x1C},
    {.duration = 6, .pose = 0x1B},
    {.duration = 6, .pose = 0x1A},
    {.duration = 6, .pose = 0x19},
    {.duration = 33, .pose = 0x01},
    POSE_END,
};
static AnimateEntityFrame anim_death[] = {
    {.duration = 5, .pose = 0x22},
    {.duration = 5, .pose = 0x23},
    {.duration = 5, .pose = 0x24},
    {.duration = 5, .pose = 0x25},
    {.duration = 5, .pose = 0x26},
    {.duration = 5, .pose = 0x27},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 2, .pose = 0x28},
    {.duration = 34, .pose = 0x29},
    POSE_END,
};

// This is some sort of unused rotating bone animation
// Unclear what it would have been for, maybe the bone
// was originally going to be thrown horizontally like the Slinger
static AnimateEntityFrame anim_unused_bone_rotate[] = {
    {.duration = 2, .pose = 0x2B},
    {.duration = 2, .pose = 0x2C},
    {.duration = 2, .pose = 0x2D},
    {.duration = 2, .pose = 0x2E},
    {.duration = 2, .pose = 0x2F},
    {.duration = 2, .pose = 0x30},
    {.duration = 2, .pose = 0x31},
    {.duration = 2, .pose = 0x32},
    {.duration = 2, .pose = 0x33},
    {.duration = 2, .pose = 0x34},
    {.duration = 2, .pose = 0x35},
    {.duration = 2, .pose = 0x36},
    POSE_LOOP(0),
};

static u8 unusedData[] = {4, 5, 6};

static Point16 death_flames_positions[] = {
    {.x = -32, .y = 27}, {.x = 32, .y = 24}, {.x = 8, .y = 29},
    {.x = -16, .y = 29}, {.x = 0, .y = 31},  {.x = -4, .y = 23},
};

// Used for animation frames 29 (0x1D) - 33 (0x21)
static Point16 dive_hitbox_offsets[] = {
    {.x = -9, .y = -1},  {.x = -9, .y = 4},   {.x = -10, .y = 10},
    {.x = -10, .y = 13}, {.x = -10, .y = 13},
};
static Point16 dive_hitbox_dimensions[] = {
    {.x = 18, .y = 24}, {.x = 26, .y = 11}, {.x = 26, .y = 11},
    {.x = 27, .y = 11}, {.x = 27, .y = 11},
};

static s16 walk_posX_offsets[] = {0, 6, 5, 2, 0};
static s16 swing_bone_posX_offsets[] = {0, 6, 5, 2, 0, 0, 0, 4, 0, 0};
static s16 thrown_bone_posX_offsets[] = {0, 6, 5, 2, 0, 0, 4, 0, 0};

// Indexed off Paranthropus animCurFrame
static Point16 bone_hitbox_offsets[] = {
    {.x = 0, .y = 0},    {.x = -34, .y = 16},  {.x = -34, .y = 16},
    {.x = -36, .y = 16}, {.x = -37, .y = 16},  {.x = -34, .y = 16},
    {.x = -34, .y = 16}, {.x = -33, .y = 16},  {.x = 0, .y = 0},
    {.x = 0, .y = 0},    {.x = 31, .y = -9},   {.x = 28, .y = -33},
    {.x = 8, .y = -36},  {.x = -30, .y = -38}, {.x = -40, .y = -15},
    {.x = -43, .y = 22}, {.x = -43, .y = 25},  {.x = -30, .y = 16},
    {.x = 0, .y = 0},    {.x = 4, .y = -31},   {.x = 14, .y = -38},
    {.x = 9, .y = -37},  {.x = -32, .y = -39}, {.x = 0, .y = 0},
    {.x = 0, .y = 0},    {.x = -30, .y = 16},  {.x = -30, .y = 15},
    {.x = -30, .y = 14}, {.x = -30, .y = 13},  {.x = -38, .y = 14},
    {.x = -47, .y = 20}, {.x = -50, .y = 21},  {.x = -53, .y = 24},
};
// Indexed off Paranthropus animCurFrame
static Size16 bone_hitbox_dimensions[] = {
    {.width = 0, .height = 0},  {.width = 8, .height = 4},
    {.width = 8, .height = 4},  {.width = 8, .height = 4},
    {.width = 8, .height = 4},  {.width = 8, .height = 4},
    {.width = 8, .height = 4},  {.width = 8, .height = 4},
    {.width = 0, .height = 0},  {.width = 0, .height = 0},
    {.width = 8, .height = 4},  {.width = 4, .height = 8},
    {.width = 4, .height = 12}, {.width = 4, .height = 12},
    {.width = 4, .height = 12}, {.width = 12, .height = 4},
    {.width = 12, .height = 4}, {.width = 12, .height = 4},
    {.width = 0, .height = 0},  {.width = 4, .height = 4},
    {.width = 4, .height = 12}, {.width = 4, .height = 12},
    {.width = 4, .height = 12}, {.width = 0, .height = 0},
    {.width = 0, .height = 0},  {.width = 12, .height = 4},
    {.width = 12, .height = 4}, {.width = 12, .height = 4},
    {.width = 12, .height = 4}, {.width = 12, .height = 4},
    {.width = 12, .height = 4}, {.width = 12, .height = 4},
    {.width = 12, .height = 4},
};
// Indexed off Paranthropus animCurFrame
static Point16 skull_positions[] = {
    {.x = 0, .y = 0},     {.x = -13, .y = -19}, {.x = -13, .y = -20},
    {.x = -13, .y = -20}, {.x = -13, .y = -19}, {.x = -14, .y = -17},
    {.x = -13, .y = -16}, {.x = -13, .y = -19}, {.x = -11, .y = -24},
    {.x = -10, .y = -25}, {.x = -7, .y = -29},  {.x = -7, .y = -29},
    {.x = -10, .y = -25}, {.x = -11, .y = -24}, {.x = -13, .y = -19},
    {.x = -15, .y = -17}, {.x = -15, .y = -15}, {.x = -13, .y = -19},
    {.x = -11, .y = -24}, {.x = -9, .y = -25},  {.x = -4, .y = -31},
    {.x = -9, .y = -26},  {.x = -11, .y = -24}, {.x = -13, .y = -19},
    {.x = -15, .y = -17}, {.x = -14, .y = -19}, {.x = -14, .y = -20},
    {.x = -14, .y = -21}, {.x = -14, .y = -22}, {.x = -22, .y = -19},
    {.x = -29, .y = -11}, {.x = -32, .y = -2},  {.x = -33, .y = 5},
    {.x = -33, .y = 5},
};

enum ParanthropusStep {
    INIT = 0,
    FALL_TO_GROUND = 1,
    DIVE_RECOVERY = 2,
    WALK = 3,
    THROW_BONE = 4,
    SWING_BONE = 5,
    DIVE = 6,
    DEATH = 7,
    DEATH_EFFECTS = 8,
    DEATH_PARTS_VACUUM = 9,
    DEATH_SKULL_REMAINS = 11
};

void ParanthropusSetStep(u16 step) {
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->ext.paranthropus.unk7C = 0;
    g_CurrentEntity->ext.paranthropus.unk7E = false;
    g_CurrentEntity->step = step;
}

// Params = 11 - skull that remains after death
void EntityParanthropus(Entity* self) {
    Collider collider;
    Primitive* deathVortex;
    Entity* entity;
    s32 i;
    s16 xOffset;
    u8 var_s4;
    s16 primX;
    s16 primY;
    s32 primIndex;
    s16 posX;
    s16 posY;

    enum Attacks { BONE_THROW = 0, BONE_SWING = 1, BELLY_DIVE = 2 };

    self->ext.paranthropus.lastFacingDirection = self->facingLeft;
    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        ParanthropusSetStep(DEATH);
        self->hitboxState = 0;
        (self + 1)->hitboxState = 0;

        // Spawn the skull entity which remains after death
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(E_PARANTHROPUS, self, entity);
            entity->facingLeft = self->facingLeft;
            entity->posY.i.hi -= 0x18;
            if (self->facingLeft) {
                entity->posX.i.hi += 0x10;
            } else {
                entity->posX.i.hi -= 0x10;
            }
            entity->params = 11;
        }
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitParanthropus);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->params == 11) {
            self->zPriority++;
            self->animCurFrame = 0x2A;
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->step = DEATH_SKULL_REMAINS;
        } else {
            self->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            self->scaleX = self->scaleY = 0x100;

            entity = self + 1;
            CreateEntityFromEntity(E_PARANTHROPUS_BONE_HITBOX, self, entity);

            entity = self + 2;
            CreateEntityFromEntity(E_PARANTHROPUS_SKULL, self, entity);
        }
        break;
    case FALL_TO_GROUND:
        UnkCollisionFunc3(sensors_ground);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (GetDistanceToPlayerX() < 0x60) {
            self->step_s = 0;
            self->ext.paranthropus.nextAttack = BONE_THROW;
            ParanthropusSetStep(WALK);
        }
        break;
    case DIVE_RECOVERY:
        if (!AnimateEntity(anim_belly_ground_recovery, self)) {
            self->step_s = 0;
            self->ext.paranthropus.nextAttack = BONE_THROW;
            ParanthropusSetStep(WALK);
        }
        break;
    case WALK:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi += walk_posX_offsets[self->animCurFrame];
                } else {
                    self->posX.i.hi -= walk_posX_offsets[self->animCurFrame];
                }

                if (self->pose == 3 || self->pose == 6) {
                    PlaySfxPositional(SFX_STOMP_HARD_B);
                }

                self->posY.i.hi += 4;
                posX = self->posX.i.hi;
                posY = self->posY.i.hi + 0x1B;
                g_api.CheckCollision(posX, posY, &collider, 0);
                if (collider.effects & EFFECT_SOLID) {
                    self->posY.i.hi += collider.unk18;
                }
            }
        } else {
            self->ext.paranthropus.unk7E = true;
        }

        if (!AnimateEntity(anim_walk, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.paranthropus.unk7C++;
        }

        // Once player is close enough we can commence attack routine
        if (self->ext.paranthropus.unk7C > 1 && GetDistanceToPlayerX() < 0x60) {
            self->step_s = 0;

            // Attacks rotate depending on the previous one used
            switch (self->ext.paranthropus.nextAttack) {
            case BONE_THROW:
                ParanthropusSetStep(THROW_BONE);
                break;
            case BONE_SWING:
                ParanthropusSetStep(SWING_BONE);
                break;
            case BELLY_DIVE:
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->velocityY = FIX(-6.25);
                ParanthropusSetStep(DIVE);
                break;
            }
        }
        break;
    case THROW_BONE:
        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi +=
                        thrown_bone_posX_offsets[self->animCurFrame - 0x10];
                } else {
                    self->posX.i.hi -=
                        thrown_bone_posX_offsets[self->animCurFrame - 0x10];
                }
            }
        } else {
            self->ext.paranthropus.unk7E = true;
        }

        if (!AnimateEntity(anim_throw_bone, self)) {
            self->ext.paranthropus.nextAttack = BONE_SWING;
            ParanthropusSetStep(WALK);
        }

        if (self->animCurFrame == 0x17) {
            if (!self->ext.paranthropus.unk7C) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    PlaySfxPositional(SFX_BONE_THROW);
                    CreateEntityFromEntity(
                        E_PARANTHROPUS_THROWN_BONE, self, entity);
                    entity->facingLeft = self->facingLeft;
                    entity->posY.i.hi -= 0x20;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x18;
                    } else {
                        entity->posX.i.hi -= 0x18;
                    }
                }
                self->ext.paranthropus.unk7C = 1;
            }
        } else {
            self->ext.paranthropus.unk7C = 0;
        }
        break;
    case SWING_BONE:
        if (self->ext.paranthropus.unk7E) {
            if (self->poseTimer == 0) {
                if (self->facingLeft) {
                    self->posX.i.hi +=
                        swing_bone_posX_offsets[self->animCurFrame - 6];
                } else {
                    self->posX.i.hi -=
                        swing_bone_posX_offsets[self->animCurFrame - 6];
                }
            }
        } else {
            self->ext.paranthropus.unk7E = true;
        }

        if (self->pose == 7 && !self->poseTimer) {
            PlaySfxPositional(SFX_EXPLODE_B);
        }

        if (!AnimateEntity(anim_swing_bone, self)) {
            self->ext.paranthropus.nextAttack = BELLY_DIVE;
            ParanthropusSetStep(WALK);
        }
        break;
    case DIVE:
        // When we hit the ground spawn the dust particles all around
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            if (self->facingLeft) {
                EntityExplosionVariantsSpawner(self, 5, 3, 0x20, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 4, 3, 0x18, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 3, 3, 0x10, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 8, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 5, 3, -8, 0x1B, 0, -4);
            } else {
                EntityExplosionVariantsSpawner(self, 5, 3, 8, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, 4);
                EntityExplosionVariantsSpawner(self, 2, 3, 0, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 2, 3, -8, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 3, 3, -0x10, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 4, 3, -0x18, 0x1B, 0, -4);
                EntityExplosionVariantsSpawner(self, 5, 3, -0x20, 0x1B, 0, -4);
            }
            g_api.func_80102CD8(1);
            PlaySfxPositional(SFX_EXPLODE_D);
            ParanthropusSetStep(DIVE_RECOVERY);
        } else {
            AnimateEntity(anim_dive, self);
        }
        break;
    case DEATH:
#ifdef VERSION_PSP
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            PlaySfxPositional(SFX_SKELETON_DEATH_A);
            ParanthropusSetStep(DEATH_EFFECTS);
        }
#else
        MoveEntity();
        self->velocityY += FIX(0.25);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY + 0x1B, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            PlaySfxPositional(SFX_SKELETON_DEATH_A);
            ParanthropusSetStep(DEATH_EFFECTS);
        }
#endif
        break;
    case DEATH_EFFECTS:
        if (self->facingLeft) {
            xOffset = 0x1B;
        } else {
            xOffset = -0x1B;
        }

        if (!AnimateEntity(anim_death, self)) {
            primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (primIndex != -1) {
                // Displays a circular black vortex that sucks up the bones
                self->flags |= FLAG_HAS_PRIMS;
                self->primIndex = primIndex;
                deathVortex = &g_PrimBuf[primIndex];
                self->ext.paranthropus.deathVortexPrim = deathVortex;
                deathVortex->tpage = 0x1A;
                deathVortex->clut = 0x170;
                deathVortex->u0 = 0;
                deathVortex->u1 = 0x1F;
                deathVortex->u2 = 0;
                deathVortex->u3 = 0x1F;
                deathVortex->v0 = 0;
                deathVortex->v1 = 0;
                deathVortex->v2 = 0x1F;
                deathVortex->v3 = 0x1F;
                deathVortex->x0 = self->posX.i.hi + xOffset;
                deathVortex->y0 = self->posY.i.hi + 0x18;
                LOW(deathVortex->x1) = LOW(deathVortex->x0);
                LOW(deathVortex->x2) = LOW(deathVortex->x0);
                LOW(deathVortex->x3) = LOW(deathVortex->x0);
                PRED(deathVortex) = 0;
                PGRN(deathVortex) = 0;
                PBLU(deathVortex) = 0;
                deathVortex->priority = self->zPriority + 2;
                deathVortex->drawMode |= DRAW_UNK02;
                deathVortex->drawMode |= DRAW_COLORS;
                deathVortex->drawMode |= DRAW_UNK_40 | DRAW_TPAGE | DRAW_TRANSP;
                ParanthropusSetStep(DEATH_PARTS_VACUUM);
                self->ext.paranthropus.unk7C = 0;
                self->ext.paranthropus.deathVortexColor = 1;
                self->ext.paranthropus.unk84 = 0;
            } else {
                // If we can't spawn the vortex, just burst the parts into
                // flames instead
                self->zPriority -= 2;
                if (self->facingLeft) {
                    xOffset = 0x10;
                } else {
                    xOffset = -0x10;
                }

                for (i = 0; i < 6; i++) {
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entity);
                        entity->params = EXPLOSION_SMALL_MULTIPLE;
                        entity->posX.i.hi +=
                            xOffset + death_flames_positions[i].x;
                        entity->posY.i.hi += death_flames_positions[i].y;
                    }
                }

                DestroyEntity(self);
            }
        }
        break;
    case DEATH_PARTS_VACUUM:
        // The bones shrink and get sucked into the vortex before disappearing
        self->ext.paranthropus.unk7C ^= 1;
        if (!self->ext.paranthropus.unk7C) {
            if (self->ext.paranthropus.unk7E) {
                self->ext.paranthropus.deathVortexColor--;
                if (self->scaleX > 8) {
                    self->scaleX -= 8;
                    self->posY.val += FIX(0.8125);
                    if (self->facingLeft) {
                        self->posX.val += FIX(0.8125);
                    } else {
                        self->posX.val -= FIX(0.8125);
                    }
                }
                self->scaleY = self->scaleX;
            } else {
                if (self->ext.paranthropus.deathVortexColor++ > 0x38) {
                    PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
                    self->ext.paranthropus.unk7E = true;
                }
            }
            if (self->ext.paranthropus.unk7E) {
                primX = -1;
                primY = -(self->ext.paranthropus.deathVortexColor % 2);
            } else {
                primX = 1;
                primY = self->ext.paranthropus.deathVortexColor % 2;
            }

            // BUG! This looks like a copy paste mistake as this goes unused
            if (self->facingLeft) {
                xOffset = 0x1B;
            } else {
                xOffset = -0x1B;
            }

            deathVortex = self->ext.paranthropus.deathVortexPrim;
            deathVortex->x0 -= primX;
            deathVortex->x1 += primX;
            deathVortex->x2 -= primX;
            deathVortex->x3 += primX;
            deathVortex->y0 -= primY;
            deathVortex->y1 -= primY;
            deathVortex->y2 += primY;
            deathVortex->y3 += primY;

            PRED(deathVortex) = self->ext.paranthropus.deathVortexColor;
            PGRN(deathVortex) = self->ext.paranthropus.deathVortexColor;
            PBLU(deathVortex) = self->ext.paranthropus.deathVortexColor;

            if (self->ext.paranthropus.deathVortexColor == 0) {
                DestroyEntity(self);
            }
        }
        break;
    case 10:
        deathVortex = self->ext.paranthropus.deathVortexPrim;
        var_s4 = self->ext.paranthropus.deathVortexColor;
        PRED(deathVortex) = var_s4;
        PGRN(deathVortex) = var_s4;
        PBLU(deathVortex) = var_s4;
        break;
    case DEATH_SKULL_REMAINS:
        if ((!UnkCollisionFunc3(skull_sensors_ground)) & 1) {
            self->rotate += ROT(1.40625);
        }
        break;
    }

    if (self->facingLeft ^ self->ext.paranthropus.lastFacingDirection) {
        if (self->facingLeft) {
            self->posX.i.hi -= 0x10;
        } else {
            self->posX.i.hi += 0x10;
        }
    }

    // If we're in the dive attack, update the hitboxes accordingly
    if (self->animCurFrame >= 0x1D && self->animCurFrame < 0x22) {
        var_s4 = self->animCurFrame - 0x1D;
        self->hitboxWidth = dive_hitbox_dimensions[var_s4].x;
        self->hitboxHeight = dive_hitbox_dimensions[var_s4].y;
        self->hitboxOffX = dive_hitbox_offsets[var_s4].x;
        self->hitboxOffY = dive_hitbox_offsets[var_s4].y;
        return;
    }

    self->hitboxWidth = 0x12;
    self->hitboxHeight = 0x18;
    self->hitboxOffX = 0;
    self->hitboxOffY = 0;
}

void EntityParanthropusThrownBone(Entity* self) {
    if (self->flags & FLAG_DEAD) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParanthropusThrownBone);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }
        self->velocityY = FIX(-6.0);
        break;
    case 1:
        MoveEntity();
        self->rotate -= ROT(22.5);
        self->velocityY += FIX(0.25);
        break;
    }
}

void EntityParanthropusBoneHitbox(Entity* self) {
    Entity* paranthropus;
    u8 paranthropusAnimCurFrame;

    if (!self->step) {
        InitializeEntity(g_EInitParanthropusBoneHitbox);
    }

    paranthropus = self - 1;

    paranthropusAnimCurFrame = paranthropus->animCurFrame;
    if (paranthropusAnimCurFrame > 0x1D) {
        paranthropusAnimCurFrame = 0;
    }

    self->hitboxOffX = bone_hitbox_offsets[paranthropusAnimCurFrame].x;
    self->hitboxOffY = bone_hitbox_offsets[paranthropusAnimCurFrame].y;
    self->hitboxWidth =
        bone_hitbox_dimensions[paranthropusAnimCurFrame].width / 2;
    self->hitboxHeight =
        bone_hitbox_dimensions[paranthropusAnimCurFrame].height / 2;
    self->facingLeft = paranthropus->facingLeft;
    self->hitboxState = paranthropus->hitboxState;
    self->posX.i.hi = paranthropus->posX.i.hi;
    self->posY.i.hi = paranthropus->posY.i.hi;

    if (paranthropus->entityId != E_PARANTHROPUS) {
        DestroyEntity(self);
    }
}

void EntityParanthropusSkull(Entity* self) {
    u8 i;
    Entity* entity;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->attack = 0;
        self->attackElement = ELEMENT_NONE;
    }

    // Main Paranthropus entity
    entity = self - 2;
    i = entity->animCurFrame;
    if (i >= 0x21) {
        i = 0;
    }

    if (entity->facingLeft) {
        self->posX.i.hi = (self - 2)->posX.i.hi - skull_positions[i].x;
    } else {
        self->posX.i.hi = (self - 2)->posX.i.hi + skull_positions[i].x;
    }
    self->posY.i.hi = (self - 2)->posY.i.hi + skull_positions[i].y;

    // Player can stand on top of the skull as a platform
#ifdef VERSION_US
    i = 0;
#endif
    if (entity->step < DEATH) {
        i = GetPlayerCollisionWith(self, 8, 10, 4);
    }

    entity = &PLAYER;
    if (i) {
        entity->posY.val += FIX(2.0);
    }

    if ((self - 2)->entityId != E_PARANTHROPUS) {
        DestroyEntity(self);
    }
}
