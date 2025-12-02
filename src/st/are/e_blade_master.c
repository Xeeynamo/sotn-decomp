// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit g_EInitBladeMaster;
extern EInit g_EInitBladeMasterAttackHitbox;
extern EInit g_EInitParticle;
// This comes from e_collect
extern u8 g_explosionBigAnim[];

static s16 sensors_ground[] = {0, 24, 0, 4, 8, -4, -16, 0};
static s16 sensors_wall[] = {0, 24, 12, 0};
static AnimateEntityFrame anim_walk_toward[] = {
    {.duration = 10, .pose = 0x01},
    {.duration = 7, .pose = 0x02},
    {.duration = 10, .pose = 0x03},
    {.duration = 6, .pose = 0x04},
    {.duration = 7, .pose = 0x05},
    {.duration = 8, .pose = 0x04},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_walk_away[] = {
    {.duration = 10, .pose = 0x03},
    {.duration = 5, .pose = 0x02},
    {.duration = 7, .pose = 0x01},
    {.duration = 4, .pose = 0x04},
    {.duration = 5, .pose = 0x05},
    {.duration = 6, .pose = 0x04},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_short_slash[] = {
    {.duration = 2, .pose = 0x09},  {.duration = 2, .pose = 0x0A},
    {.duration = 2, .pose = 0x0B},  {.duration = 2, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},  {.duration = 8, .pose = 0x0E},
    {.duration = 1, .pose = 0x0F},  {.duration = 1, .pose = 0x10},
    {.duration = 1, .pose = 0x11},  {.duration = 1, .pose = 0x12},
    {.duration = 1, .pose = 0x13},  {.duration = 1, .pose = 0x14},
    {.duration = 2, .pose = 0x15},  {.duration = 8, .pose = 0x14},
    {.duration = 48, .pose = 0x15}, {.duration = 8, .pose = 0x13},
    {.duration = 8, .pose = 0x12},  POSE_END};
static AnimateEntityFrame anim_charge_slash[] = {
    {.duration = 3, .pose = 0x09},
    {.duration = 3, .pose = 0x0A},
    {.duration = 2, .pose = 0x0B},
    {.duration = 2, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D},
    {.duration = 9, .pose = 0x0E},
    {.duration = 2, .pose = 0x16},
    {.duration = 2, .pose = 0x17},
    {.duration = 2, .pose = 0x18},
    {.duration = 4, .pose = 0x19},
    {.duration = 2, .pose = 0x1A},
    {.duration = 5, .pose = 0x0E},
    {.duration = 1, .pose = 0x1B},
    {.duration = 1, .pose = 0x1C},
    {.duration = 1, .pose = 0x1D},
    {.duration = 1, .pose = 0x1E},
    {.duration = 1, .pose = 0x1F},
    {.duration = 1, .pose = 0x20},
    {.duration = 1, .pose = 0x21},
    {.duration = 2, .pose = 0x22},
    {.duration = 5, .pose = 0x14},
    {.duration = 28, .pose = 0x15},
    {.duration = 8, .pose = 0x13},
    {.duration = 8, .pose = 0x12},
    POSE_END};
static AnimateEntityFrame anim_slide_kick[] = {
    {.duration = 1, .pose = 0x0A},  {.duration = 1, .pose = 0x24},
    {.duration = 1, .pose = 0x25},  {.duration = 1, .pose = 0x26},
    {.duration = 1, .pose = 0x27},  {.duration = 1, .pose = 0x28},
    {.duration = 1, .pose = 0x29},  {.duration = 1, .pose = 0x2A},
    {.duration = 3, .pose = 0x37},  {.duration = 3, .pose = 0x38},
    {.duration = 3, .pose = 0x39},  {.duration = 31, .pose = 0x2B},
    {.duration = 1, .pose = 0x2A},  {.duration = 1, .pose = 0x29},
    {.duration = 1, .pose = 0x28},  {.duration = 1, .pose = 0x27},
    {.duration = 12, .pose = 0x26}, {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x24},  POSE_END};
static AnimateEntityFrame anim_flip[] = {
    {.duration = 1, .pose = 0x2D},
    {.duration = 2, .pose = 0x2E},
    {.duration = 8, .pose = 0x2F},
    {.duration = 8, .pose = 0x30},
    {.duration = 8, .pose = 0x31},
    {.duration = 1, .pose = 0x2D},
    POSE_END};

// These do not look like obvious animation data
static u8 unused_1[] = {0x08, 0x00, 0x00, 0x00};
static u8 unused_2[] = {0x32, 0x00, 0x00, 0x00};
static u8 unused_3[] = {0x08, 0x00, 0x00, 0x00};
static u8 unused_4[] = {0x33, 0x00, 0x00, 0x00};
static u8 unused_5[] = {0x30, 0x00, 0x00, 0x00};
static u8 unused_6[] = {0x2D, 0x00, 0x00, 0x00};
static u8 unused_7[] = {0xFF, 0x00, 0x00, 0x00};

static AnimateEntityFrame anim_land[] = {
    {.duration = 1, .pose = 0x0A},
    {.duration = 2, .pose = 0x25},
    {.duration = 8, .pose = 0x26},
    {.duration = 6, .pose = 0x25},
    {.duration = 6, .pose = 0x24},
    {.duration = 6, .pose = 0x0A},
    POSE_END};
static AnimateEntityFrame anim_short_hop[] = {
    {.duration = 6, .pose = 0x2D},  {.duration = 2, .pose = 0x2E},
    {.duration = 3, .pose = 0x35},  {.duration = 8, .pose = 0x36},
    {.duration = 3, .pose = 0x35},  {.duration = 2, .pose = 0x2E},
    {.duration = 64, .pose = 0x2D}, POSE_END};
static AnimateEntityFrame anim_dash[] = {
    {.duration = 5, .pose = 0x06},
    {.duration = 5, .pose = 0x07},
    {.duration = 5, .pose = 0x08},
    POSE_LOOP(0)};
static AnimateEntityFrame anim_skid_stop[] = {
    {.duration = 1, .pose = 0x09},
    {.duration = 2, .pose = 0x0A},
    {.duration = 3, .pose = 0x0B},
    {.duration = 3, .pose = 0x0C},
    {.duration = 3, .pose = 0x0D},
    {.duration = 3, .pose = 0x0F},
    {.duration = 8, .pose = 0x05},
    {.duration = 8, .pose = 0x04},
    POSE_END};
static AnimateEntityFrame anim_idle[] = {
    {.duration = 6, .pose = 0x04}, {.duration = 6, .pose = 0x05}, POSE_LOOP(0)};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
static s8 hitbox_dimensions[][4] = {
    {0, 0, 0, 0},     {-1, 2, 4, 23}, {3, 3, 8, 21},    {1, -5, 6, 17},
    {4, 3, 8, 21},    {1, 7, 8, 16},  {3, 6, 15, 8},    {-1, 15, 22, 6},
    {-56, -40, 0, 0}, {2, 2, 4, 21},  {-1, -3, 9, 9},   {-1, -13, 5, 20},
    {-3, -7, 14, 7},  {0, -3, 9, 9},  {-60, -32, 0, 0}, {0, -1, 8, 15}};

// This is indexed off the current animation frame
static u8 hitbox_indices[] = {
    0, 1, 1, 1, 2, 2, 3, 3,  3,  2,  2,  2,  2,  2, 2,  2, 2, 2, 4, 2,
    2, 2, 2, 2, 2, 2, 2, 2,  2,  2,  2,  2,  2,  2, 2,  2, 2, 5, 5, 5,
    6, 6, 7, 7, 8, 9, 9, 10, 11, 12, 13, 13, 14, 2, 15, 7, 7, 7};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
// This is indexed off the current animation frame
static s16 attack_hitbox_dimensions[][4] = {
    {0, 0, 0, 0},
    {-4, 16, 22, 6},
    {-20, -1, 17, 18},
    {-20, -1, 17, 18},
};

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight }
// This is indexed off the current animation frame
static s16 slash_hitbox_dimensions[][4] = {
    {0, 0, 0, 0},
    {-5, -4, 8, 11},
    {-5, -4, 8, 11},
    {-7, -9, 12, 18},
};

static Point32 death_parts_velocities[] = {
    {.x = FIX(2.0), .y = FIX(-4.5)}, {.x = FIX(1.0), .y = FIX(-4)}};

enum BladeMasterSteps {
    INIT = 0,
    FALL_TO_GROUND = 1,
    WAKE = 2,
    WALK_TOWARDS = 3,
    WALK_AWAY = 4,
    JUMP_OVER = 5,
    SHORT_HOP = 6,
    SLIDE_KICK = 7,
    DASH = 8,
    CHARGE_SLASH = 9,
    SHORT_SLASH = 10,
    LAND = 11,
    SKID_STOP = 12,
    GUARD = 13,
    DEATH = 15,
    DEBUG = 255
};

static void CheckPlayerApproaching(void) {
    Entity* player;
    s32 posX;

    g_CurrentEntity->facingLeft = (GetSideToPlayer() & 1) ^ 1;
    player = &PLAYER;
    posX = g_CurrentEntity->posX.i.hi - player->posX.i.hi;
    if (g_CurrentEntity->facingLeft) {
        posX = -posX;
    }

    if (posX < 0x71) {
        if (player->facingLeft == g_CurrentEntity->facingLeft) {
            // Keep track of the number of steps the player has taken towards us
            //
            // There is a minor BUG! here in that if the player moves into
            // alternate form like bat, they can fly or jump right over and the
            // step counter never increments leaving Blade Master stuck in the
            // guard state.
            if (player->step == Player_Walk) {
                g_CurrentEntity->ext.bladeMaster.playerStepTowards++;
            } else {
                g_CurrentEntity->ext.bladeMaster.playerStepTowards = 0;
            }
        } else {
            g_CurrentEntity->ext.bladeMaster.playerStepTowards = 0;
        }

        // If player is starting to walk towards us, put us into a guard state.
        if (g_CurrentEntity->ext.bladeMaster.playerStepTowards > 2) {
            SetStep(GUARD);
            g_CurrentEntity->ext.bladeMaster.playerStepTowards = 0;
            return;
        }

        if (posX < 0x2C) {
            SetStep(CHARGE_SLASH);
        }
    }
}

void EntityBladeMaster(Entity* self) {
    Entity* entity;
    s32 i;
    Entity* player;
    s8* ptr;
    s32 posX;
    s32 animResult;

    FntPrint("BLADES_STEP %x\n", self->step);
    FntPrint("check %x\n", self->ext.bladeMaster.playerStepTowards);

    if (self->flags & FLAG_DEAD) {
        self->hitboxState = 0;
        entity = self + 1;
        DestroyEntity(entity);
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitBladeMaster);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_BLADE_MASTER_ATTACK_HITBOX, entity);
        break;
    case FALL_TO_GROUND:
        if (UnkCollisionFunc3(sensors_ground) & 1) {
            SetStep(WAKE);
        }
        break;
    case WAKE:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(anim_idle, self);
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(WALK_TOWARDS);
        }
        break;
    case WALK_TOWARDS:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeMaster.walkCounter = 2;
            self->step_s++;

            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
        }
        animResult = AnimateEntity(anim_walk_toward, self);
        if (self->pose < 4) {
            UnkCollisionFunc2(sensors_wall);
        }

        if (!animResult) {
            self->ext.bladeMaster.walkCounter--;
        }

        if (!self->ext.bladeMaster.walkCounter) {
            SetStep(WALK_AWAY);
        }

        CheckPlayerApproaching();
        break;
    case WALK_AWAY:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.bladeMaster.walkCounter = 1;
            self->step_s++;

            if (self->facingLeft) {
                self->velocityX = FIX(-1.5);
            } else {
                self->velocityX = FIX(1.5);
            }
        }
        if (!AnimateEntity(anim_walk_away, self)) {
            self->ext.bladeMaster.walkCounter--;
        }

        if (self->pose < 4) {
            UnkCollisionFunc2(sensors_wall);
        }

        if (!self->ext.bladeMaster.walkCounter) {
            SetStep(WALK_TOWARDS);
        }

        CheckPlayerApproaching();
        break;
    case CHARGE_SLASH:
        if (!AnimateEntity(anim_charge_slash, self)) {
            SetStep(WALK_AWAY);
        }

        // On the third frame of anim_charge_slash
        if (!self->poseTimer && self->pose == 0x0B) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
        }

        break;
    case GUARD:
        self->animCurFrame = 0x0A;
        player = &PLAYER;
        // If player is walking towards us, keep track of how many steps
        if (player->facingLeft == self->facingLeft) {
            if (player->step == Player_Walk) {
                self->ext.bladeMaster.playerStepTowards++;
            }
        } else {
            // If player looks away, we're back to attacking
            self->ext.bladeMaster.playerStepTowards = 0;
            SetStep(DASH);
            break;
        }

        // Once player has walked 24 steps towards, flip jump over them
        if (self->ext.bladeMaster.playerStepTowards > 0x18) {
            self->ext.bladeMaster.playerStepTowards = 0;
            SetStep(JUMP_OVER);
        }

        // Player is attacking
        if (PLAYER.step_s & 0x40) {
            if (PLAYER.step == Player_Crouch) {
                SetStep(SHORT_HOP);
            } else {
                SetStep(SLIDE_KICK);
            }
        }
        break;
    case JUMP_OVER:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
            self->velocityY = FIX(-7.0);
            self->animCurFrame = 0x2D;
            self->step_s++;
            break;
        case 1:
            if (self->velocityY > FIX(-1.0)) {
                AnimateEntity(anim_flip, self);
            }

            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetStep(LAND);
            }
            break;
        }
        break;
    case LAND:
        if (!AnimateEntity(anim_land, self)) {
            SetStep(WALK_AWAY);
        }
        break;
    case SLIDE_KICK:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }

            PlaySfxPositional(SFX_SCRAPE_B);
            self->step_s++;
            // fallthrough
        case 1:
            AnimateEntity(anim_slide_kick, self);
            UnkCollisionFunc2(sensors_wall);
            self->velocityX -= self->velocityX / 32;
            if (abs(self->velocityX) < 0x6000) {
                SetStep(WALK_AWAY);
            }
            break;
        }
        break;
    case SHORT_HOP:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-5.0);
            self->step_s++;
            break;
        case 1:
            AnimateEntity(anim_short_hop, self);
            if (UnkCollisionFunc3(sensors_ground) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_C);
                SetStep(LAND);
            }
            break;
        }
        break;
    case DASH:
        switch (self->step_s) {
        case 0:
            if (self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->velocityY = 0;
            PlaySfxPositional(SFX_QUIET_STEPS);
            self->step_s++;
            // fallthrough
        case 1:
            UnkCollisionFunc2(sensors_wall);
            AnimateEntity(anim_dash, self);
            player = &PLAYER;
            // If player turns back to face us while dashing, flip over them
            if (self->facingLeft == player->facingLeft) {
                SetStep(JUMP_OVER);
            } else {
                posX = self->posX.i.hi - player->posX.i.hi;
                if (self->facingLeft) {
                    posX = -posX;
                }

                if (posX < 0) {
                    SetStep(SKID_STOP);
                } else if (posX < 0x30) {
                    SetStep(SHORT_SLASH);
                }
            }
            break;
        }
        break;
    case SKID_STOP:
        if (!AnimateEntity(anim_skid_stop, self)) {
            SetStep(WALK_AWAY);
        }

        UnkCollisionFunc2(sensors_wall);
        self->velocityX -= self->velocityX / 8;
        break;
    case SHORT_SLASH:
        if (!self->step_s) {
            entity = self + 1;
            entity->ext.bladeMaster.slashInProgress = true;
            self->step_s++;
        }

        if (!AnimateEntity(anim_short_slash, self)) {
            SetStep(WALK_AWAY);
        }

        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_BONE_THROW);
        }

        if (self->animCurFrame == 0x15) {
            entity = self + 1;
            entity->ext.bladeMaster.slashInProgress = false;
        }

        UnkCollisionFunc2(sensors_wall);
        self->velocityX -= self->velocityX / 16;
        break;
    case DEATH:
        for (i = 0; i < 2; i++) {
            entity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (entity != NULL) {
                CreateEntityFromEntity(
                    E_BLADE_MASTER_DEATH_PARTS, self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = i;
            }
        }
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        DestroyEntity(self);
        // NOTE: This skips the final hitbox code outside the switch!
        return;
    case DEBUG:
#include "../pad2_anim_debug.h"
    }

    i = hitbox_indices[self->animCurFrame];
    ptr = hitbox_dimensions[i];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void EntityBladeMasterAttackHitbox(Entity* self) {
    s32 bladeMasterAnimFrame;
    s16* ptr;
    Entity* bladeMaster;

    if (!self->step) {
        InitializeEntity(g_EInitBladeMasterAttackHitbox);
    }

    bladeMaster = self - 1;
    self->posX.val = bladeMaster->posX.val;
    self->posY.val = bladeMaster->posY.val;
    self->facingLeft = bladeMaster->facingLeft;
    bladeMasterAnimFrame = bladeMaster->animCurFrame;
    if (self->ext.bladeMaster.slashInProgress) {
        bladeMasterAnimFrame -= 0x10;
        if (bladeMasterAnimFrame < 0) {
            bladeMasterAnimFrame = 0;
        }
        if (bladeMasterAnimFrame > 3) {
            bladeMasterAnimFrame = 0;
        }
        ptr = *slash_hitbox_dimensions;
    } else {
        bladeMasterAnimFrame -= 0x1D;
        if (bladeMasterAnimFrame < 0) {
            bladeMasterAnimFrame = 0;
        }

        if (bladeMasterAnimFrame > 3) {
            bladeMasterAnimFrame = 0;
        }
        ptr = *attack_hitbox_dimensions;
    }

    ptr = &ptr[bladeMasterAnimFrame * 4];
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;

    if (bladeMaster->entityId != E_BLADE_MASTER) {
        DestroyEntity(self);
    }
}

// Params 1 = skull
// Params 2 = body parts
void EntityBladeMasterDeathParts(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 posX;
    s32 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBladeMaster);
        self->hitboxState = 0;
        self->flags |=
            FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_UNK_00200000 | FLAG_UNK_2000;
        if (self->params) {
            self->animCurFrame = 0x2C;
        } else {
            self->animCurFrame = 0x34;
        }
        self->velocityX = death_parts_velocities[self->params].x;
        self->velocityY = death_parts_velocities[self->params].y;
        if ((GetSideToPlayer() & 1) ^ 1) {
            self->velocityX = -self->velocityX;
        }
        self->step += self->params;
        break;
    case 1:
        // Skull goes flying slightly upwards and then explodes in a small
        // fireball
        if (!self->step_s) {
            self->ext.bladeMaster.deathTimer = 0x18;
            self->step_s++;
        }
        MoveEntity();
        self->velocityY += FIX(0.1875);
        if (!--self->ext.bladeMaster.deathTimer) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = EXPLOSION_FIREBALL;
            }
            DestroyEntity(self);
        }
        break;
    case 2:
        // Body parts fly and fall until they hit the ground
        MoveEntity();
        self->velocityY += FIX(0.21875);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->animCurFrame = 0;
            self->posY.i.hi += 0x10;
            self->ext.bladeMaster.deathTimer = 0x60;
            self->step++;
        }
        break;
    case 3:
        // Once body parts have hit the ground spawn the death fireworks
        if (!(self->ext.bladeMaster.deathTimer & 0xF)) {
            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(
                    E_BLADE_MASTER_DEATH_EXPLOSION, self, newEntity);
                newEntity->zPriority = self->zPriority + 1;
            }
        }

        if (!(self->ext.bladeMaster.deathTimer & 7)) {
            if (Random() & 1) {
                PlaySfxPositional(SFX_EXPLODE_E);
            } else {
                PlaySfxPositional(SFX_EXPLODE_F);
            }
        }

        if (!--self->ext.bladeMaster.deathTimer) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityBladeMasterDeathExplosion(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->velocityY = FIX(-3.0);
        return;
    }

    self->posY.val += self->velocityY;
    if (!AnimateEntity(g_explosionBigAnim, self)) {
        DestroyEntity(self);
    }
}
