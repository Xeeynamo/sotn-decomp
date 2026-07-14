// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rcat.h"

extern EInit g_EInitSalome;
extern EInit g_EInitSalomeEffects;
extern EInit g_EInitSalomeMagicOrb;
extern EInit g_EInitSalomeSkull;
extern EInit g_EInitSalomeCat;

static s16 sensors_wall[] = {0, 7, 8, 0};
static AnimateEntityFrame anim_turn_to_player[] = {
    {.duration = 2, .pose = 0x01},
    {.duration = 6, .pose = 0x02},
    {.duration = 6, .pose = 0x03},
    POSE_END,
};
static AnimateEntityFrame anim_return_to_stationary[] = {
    {.duration = 4, .pose = 0x03},
    {.duration = 4, .pose = 0x02},
    {.duration = 4, .pose = 0x01},
    POSE_END,
};
static AnimateEntityFrame anim_fly[] = {
    {.duration = 3, .pose = 0x04}, {.duration = 3, .pose = 0x05},
    {.duration = 3, .pose = 0x06}, {.duration = 3, .pose = 0x07},
    {.duration = 3, .pose = 0x08}, POSE_LOOP(0),
};
static AnimateEntityFrame anim_turn_with_sparkles[] = {
    {.duration = 6, .pose = 0x09}, {.duration = 6, .pose = 0x0A},
    {.duration = 6, .pose = 0x0B}, {.duration = 3, .pose = 0x0C},
    {.duration = 2, .pose = 0x0D}, {.duration = 2, .pose = 0x0E},
    {.duration = 1, .pose = 0x0F}, POSE_END,
};
static AnimateEntityFrame anim_throw[] = {
    {.duration = 4, .pose = 0x01}, {.duration = 8, .pose = 0x10},
    {.duration = 3, .pose = 0x11}, {.duration = 3, .pose = 0x12},
    {.duration = 3, .pose = 0x13}, {.duration = 28, .pose = 0x14},
    {.duration = 2, .pose = 0x15}, {.duration = 2, .pose = 0x16},
    {.duration = 2, .pose = 0x17}, {.duration = 2, .pose = 0x18},
    {.duration = 2, .pose = 0x19}, {.duration = 6, .pose = 0x1A},
    {.duration = 4, .pose = 0x01}, POSE_END,
};
static AnimateEntityFrame anim_shield[] = {
    {.duration = 2, .pose = 0x1B},
    {.duration = 2, .pose = 0x1C},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_magic_orb[] = {
    {.duration = 2, .pose = 0x1E},
    {.duration = 2, .pose = 0x1F},
    {.duration = 2, .pose = 0x20},
    {.duration = 2, .pose = 0x21},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_skull_rotate[] = {
    {.duration = 2, .pose = 0x22},
    {.duration = 2, .pose = 0x23},
    {.duration = 2, .pose = 0x24},
    {.duration = 2, .pose = 0x25},
    {.duration = 2, .pose = 0x26},
    {.duration = 2, .pose = 0x27},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_skull_rotate_decel[] = {
    {.duration = 1, .pose = 0x22},
    {.duration = 1, .pose = 0x23},
    {.duration = 1, .pose = 0x24},
    {.duration = 1, .pose = 0x25},
    {.duration = 1, .pose = 0x26},
    {.duration = 1, .pose = 0x27},
    {.duration = 2, .pose = 0x28},
    {.duration = 2, .pose = 0x29},
    {.duration = 2, .pose = 0x22},
    {.duration = 2, .pose = 0x23},
    {.duration = 3, .pose = 0x24},
    {.duration = 3, .pose = 0x25},
    {.duration = 3, .pose = 0x26},
    {.duration = 4, .pose = 0x27},
    {.duration = 4, .pose = 0x28},
    {.duration = 4, .pose = 0x29},
    {.duration = 4, .pose = 0x22},
    {.duration = 5, .pose = 0x23},
    {.duration = 5, .pose = 0x24},
    {.duration = 5, .pose = 0x25},
    {.duration = 5, .pose = 0x26},
    {.duration = 5, .pose = 0x27},
    {.duration = 5, .pose = 0x28},
    {.duration = 5, .pose = 0x29},
    {.duration = 5, .pose = 0x22},
    {.duration = 5, .pose = 0x23},
    {.duration = 5, .pose = 0x24},
    {.duration = 5, .pose = 0x25},
    {.duration = 5, .pose = 0x26},
    {.duration = 5, .pose = 0x27},
    {.duration = 5, .pose = 0x28},
    {.duration = 5, .pose = 0x29},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_cat_move[] = {
    {.duration = 2, .pose = 0x2A},
    {.duration = 1, .pose = 0x2B},
    {.duration = 3, .pose = 0x2C},
    {.duration = 3, .pose = 0x2D},
    {.duration = 3, .pose = 0x2E},
    {.duration = 3, .pose = 0x2F},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_death_cat_move[] = {
    {.duration = 2, .pose = 0x33},
    {.duration = 1, .pose = 0x34},
    {.duration = 3, .pose = 0x35},
    {.duration = 3, .pose = 0x36},
    {.duration = 3, .pose = 0x37},
    {.duration = 3, .pose = 0x38},
    POSE_LOOP(0),
};
static AnimateEntityFrame anim_lantern_flicker[] = {
    {.duration = 2, .pose = 0x31},
    {.duration = 2, .pose = 0x32},
    POSE_LOOP(0),
};
// Indexed off animCurFrame
static Point16 lantern_light_positions[] = {
    {.x = 22, .y = 3},   {.x = 22, .y = -1}, {.x = -19, .y = -2},
    {.x = -24, .y = 9},  {.x = -24, .y = 9}, {.x = -24, .y = 9},
    {.x = -24, .y = 9},  {.x = -24, .y = 9}, {.x = -15, .y = 3},
    {.x = -20, .y = -2}, {.x = 20, .y = -2}, {.x = 26, .y = 9},
    {.x = 26, .y = 9},   {.x = 26, .y = 9},  {.x = 26, .y = 9},
    {.x = 25, .y = -2},  {.x = 25, .y = -3}, {.x = 25, .y = -4},
    {.x = 25, .y = -5},  {.x = 25, .y = -5}, {.x = 25, .y = -4},
    {.x = 25, .y = -3},  {.x = 25, .y = -2}, {.x = 25, .y = -2},
    {.x = 24, .y = -1},  {.x = 23, .y = 0},
};

void EntitySalomeCat(Entity*);
void EntitySalome(Entity* self) {
    Entity* entity;
    s32 posY;
    s16 angle;
    s32 facingDirection;

    enum Step {
        INIT = 0,
        IDLE = 2,
        FLY = 4,
        CHANGE_DIRECTION = 5,
        THROW_OBJECT = 6,
        DEATH = 8,
        DEBUG = 255,
    };

    if ((GetDistanceToPlayerX() < 0x50) && (GetDistanceToPlayerY() < 0x40)) {
        self->ext.salome.playerWithinProximity = true;
    } else {
        self->ext.salome.playerWithinProximity = false;
    }

    self->hitboxState = 3;
    entity = &PLAYER;
    if (((GetSideToPlayer() & 1) ^ 1) == self->facingLeft &&
        self->ext.salome.playerWithinProximity) {
        self->hitboxState = 1;
    }

    if (self->hitFlags & 3) {
        PlaySfxPositional(SFX_SALOME_PAIN);
    }

    if (self->flags & FLAG_DEAD && self->step < DEATH) {
        SetStep(DEATH);
    }

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitSalome);
        // Start out looking in the player's direction
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        // Pick a starting thrown object randomly
        // 0 = skull, 1 = cat
        self->ext.salome.thrownObject = Random() & 1;
        self->ext.salome.attackTimer = 0x30;
        self->zPriority = 0xAA;

        // Spawn the magical shield entity
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_SALOME_EFFECTS, entity);
        entity->zPriority = self->zPriority + 1;
        entity->params = 0;

        // Spawn the lantern flicker entity
        entity = self + 2;
        CreateEntityFromCurrentEntity(E_SALOME_EFFECTS, entity);
        entity->zPriority = self->zPriority - 1;
        entity->params = 1;

        SetStep(IDLE);
        // fallthrough
    case IDLE:
        switch (self->step_s) {
        case 0:
            // Rise and fall on broomstick while idling
            self->animCurFrame = 1;
            MoveEntity();
            angle = self->ext.salome.bobPhase += 0x20;
            angle &= 0xFFF;
            self->velocityX = 0;
            self->velocityY = rsin(angle) * 8;

            // When the player is close enough, we aggro
            if (GetDistanceToPlayerX() < 0x60) {
                self->step_s++;
            }
            break;
        case 1:
            if (!AnimateEntity(anim_turn_to_player, self)) {
                SetStep(FLY);
            }
            break;
        }
        break;
    case FLY:
        if (!self->step_s) {
            self->step_s++;
        }
        AnimateEntity(anim_fly, self);
        MoveEntity();
        if (self->facingLeft ^ self->ext.salome.moveLeft) {
            // Fly right
            self->velocityX += FIX(3.0 / 64.0);
            if (self->velocityX >= FIX(1.25)) {
                self->velocityX = FIX(1.25);
            }
        } else {
            // Fly left
            self->velocityX -= FIX(3.0 / 64.0);
            if (self->velocityX <= FIX(-1.25)) {
                self->velocityX = FIX(-1.25);
            }
        }

        // Track the player's height and aim roughly above them at a fixed
        // distance
        entity = &PLAYER;
        posY = entity->posY.i.hi;
        posY = posY - 0x48 - self->posY.i.hi;
        if (posY < -8) {
            self->velocityY -= FIX(3.0 / 128.0);
            if (self->velocityY <= FIX(-0.625)) {
                self->velocityY = FIX(-0.625);
            }
        }

        if (posY > 8) {
            self->velocityY += FIX(3.0 / 64.0);
            if (self->velocityY >= FIX(0.625)) {
                self->velocityY = FIX(0.625);
            }
        }

        if (!self->ext.salome.attackTimer) {
            // If the player is underneath us, spawn a magic orb at them,
            // otherwise move into Throw Object step
            if (GetDistanceToPlayerX() > 0x40) {
                SetStep(THROW_OBJECT);
            } else {
                PlaySfxPositional(SFX_SALOME_MAGIC_ATTACK);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SALOME_MAGIC_ORB, self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x1C;
                    } else {
                        entity->posX.i.hi -= 0x1C;
                    }
                    entity->posY.i.hi += 4;
                    entity->zPriority = self->zPriority + 1;
                }
            }
            self->ext.salome.attackTimer = 0x30;
        } else {
            self->ext.salome.attackTimer--;
        }

        facingDirection = ((GetSideToPlayer() & 1) ^ 1);
        if (self->facingLeft != facingDirection) {
            SetStep(CHANGE_DIRECTION);
        }
        break;
    case CHANGE_DIRECTION:
        if (!AnimateEntity(anim_turn_with_sparkles, self)) {
            self->animCurFrame = 4;
            self->facingLeft ^= 1;
            SetStep(FLY);
        }
        MoveEntity();
        self->velocityX -= self->velocityX / 32;
        self->velocityY -= self->velocityY / 32;
        break;
    case THROW_OBJECT:
        switch (self->step_s) {
        case 0:
            MoveEntity();
            self->velocityX -= self->velocityX / 4;
            self->velocityY -= self->velocityY / 4;
            if (!AnimateEntity(anim_return_to_stationary, self)) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (!AnimateEntity(anim_throw, self)) {
                SetSubStep(2);
            }

            if (!self->poseTimer && self->pose == 5) {
                self->ext.salome.thrownObject ^= 1;
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    if (self->ext.salome.thrownObject) {
                        PlaySfxPositional(SFX_SALOME_MEOW_SHORT);
                        CreateEntityFromEntity(E_SALOME_CAT, self, entity);
                    } else {
                        PlaySfxPositional(SFX_SALOME_ATTACK);
                        CreateEntityFromEntity(E_SALOME_SKULL, self, entity);
                    }

                    entity->zPriority = self->zPriority + 1;
                    entity->facingLeft = self->facingLeft;
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x14;
                    } else {
                        entity->posX.i.hi -= 0x14;
                    }
                    entity->posY.i.hi -= 4;
                }
            }
            break;
        case 2:
            if (!AnimateEntity(anim_turn_to_player, self)) {
                SetStep(FLY);
            }
            break;
        }
        break;
    case DEATH:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;

            entity = self + 1;
            DestroyEntity(entity);

            entity = self + 2;
            entity->step = DEATH;

            self->blendMode = BLEND_NO;
            self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
            self->scaleX = self->scaleY = 0x100;
            self->opacity = 0x80;
            self->step_s++;
            // fallthrough
        case 1:
            // Shrink down into cat form and scamper away
            self->scaleX = self->scaleY -= 8;
            if (self->opacity) {
                self->opacity -= 4;
            }

            if (self->scaleX < 0x40) {
                self->blendMode = BLEND_ADD | BLEND_TRANSP;
            }

            if (!self->scaleX) {
                PlaySfxPositional(SFX_SALOME_MEOW);
                entity = self + 2;
                entity->step = 0;
                entity->step_s = 0;
                entity->entityId = E_SALOME_CAT;
                entity->pfnUpdate = EntitySalomeCat;
                entity->ext.salome.isDeathCat = true;

                entity = self;
                DestroyEntity(entity);
            }
            break;
        }
        break;

    case DEBUG:
#include "../pad2_anim_debug.h"
    }
}

// Params 0: magic shield
// Params 1: lantern light
void EntitySalomeEffects(Entity* self) {
    Entity* entity;
    s32 animCurFrame;

    enum Step { INIT = 0, SHIELD = 1, LANTERN_LIGHT = 2, DEATH = 8 };

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitSalomeEffects);
        self->hitboxState = 2;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        if (!self->params) {
            // Magical shield
            self->drawFlags = ENTITY_OPACITY;
            self->hitboxWidth = 0x14;
            self->hitboxHeight = 0x30;
            self->hitboxOffX = -0x11;
            // fallthrough
        } else {
            // Lantern light effect
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            self->hitboxState = 0;
            self->step = LANTERN_LIGHT;
            break;
        }
    case SHIELD:
        AnimateEntity(anim_shield, self);
        entity = self - 1;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;

        if (entity->ext.salome.playerWithinProximity) {
            if (!self->ext.salome.shieldActivated) {
                PlaySfxPositional(SFX_MAGIC_NOISE_SWEEP);
                self->ext.salome.shieldActivated = true;
            }
            self->hitboxState = 2;
            self->opacity += 16;
            if (self->opacity > 0x80) {
                self->opacity = 0x80;
            }
            break;
        }

        self->ext.salome.shieldActivated = false;
        self->hitboxState = 0;
        if (self->opacity) {
            self->opacity -= 16;
            break;
        }

        self->animCurFrame = 0;
        break;
    case LANTERN_LIGHT:
        AnimateEntity(anim_lantern_flicker, self);
        entity = self - 2;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        animCurFrame = entity->animCurFrame;
        if (self->facingLeft) {
            self->posX.i.hi -= lantern_light_positions[animCurFrame].x;
        } else {
            self->posX.i.hi += lantern_light_positions[animCurFrame].x;
        }
        self->posY.i.hi += lantern_light_positions[animCurFrame].y;
        break;
    case DEATH:
        self->drawFlags = ENTITY_DEFAULT;
        self->blendMode = BLEND_NO;

        entity = self - 2;
        self->facingLeft = entity->facingLeft;
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
        self->animCurFrame = 0x38;
        break;
    }
}

void EntitySalomeMagicOrb(Entity* self) {
    Entity* player;
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitSalomeMagicOrb);
        player = &PLAYER;
        angle = GetAngleBetweenEntities(player, self);
        self->velocityX = (rcos(angle) * FIX(-1.0)) >> 0xC;
        self->velocityY = (rsin(angle) * FIX(-1.0)) >> 0xC;
    }
    AnimateEntity(anim_magic_orb, self);
    MoveEntity();

    if (self->hitFlags || self->flags & FLAG_DEAD) {
        DestroyEntity(self);
    }
}

void EntitySalomeSkull(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 posX;
    s32 posY;

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = EXPLOSION_FIREBALL;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSalomeSkull);
        if (self->facingLeft) {
            self->velocityX = FIX(1.25);
        } else {
            self->velocityX = FIX(-1.25);
        }
        self->velocityY = FIX(-1.0);
        // fallthrough
    case 1:
        AnimateEntity(anim_skull_rotate, self);
        MoveEntity();
        self->velocityY += FIX(3.0 / 32.0);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 2;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (!(collider.effects & EFFECT_SOLID)) {
            self->step++;
        }
        break;
    case 2:
        if (self->ext.salome.touchedGround) {
            AnimateEntity(anim_skull_rotate_decel, self);
        } else {
            AnimateEntity(anim_skull_rotate, self);
        }
        MoveEntity();
        self->velocityY += FIX(3.0 / 32.0);
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->velocityX > 0) {
            posX += 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->posX.i.hi += collider.unk14;
                self->velocityX = -self->velocityX;
            }
        } else {
            posX -= 8;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->posX.i.hi += collider.unk1C;
                self->velocityX = -self->velocityX;
            }
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            PlaySfxPositional(SFX_SKULL_KNOCK_B);
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY;
            // Lose a little bit of height every bounce
            self->velocityY -= self->velocityY / 8;

            if (!self->ext.salome.touchedGround) {
                self->pose = 0;
                self->poseTimer = 0;
            }

            self->ext.salome.touchedGround |= 1;
            // Once the skull has reached a minimum bounce velocity, kill it
            if (abs(self->velocityY) < 0x4000) {
                self->flags |= FLAG_DEAD;
            }
        }

        if (self->velocityY < 0) {
            posY -= 0x10;
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                PlaySfxPositional(SFX_SKULL_KNOCK_B);
                self->posY.i.hi += collider.unk20;
                self->velocityY = 0;
            }
        }
        break;
    }
}

void EntitySalomeCat(Entity* self) {
    Collider collider;
    Entity* entity;
    s32 collisionTest;
    s32 hitFlags;
    s32 posX;
    s32 posY;

    hitFlags = self->hitFlags;
    if (self->flags & FLAG_DEAD) {
        hitFlags |= 3;
    }

    if (hitFlags && !(hitFlags & 0x80)) {
        self->ext.salome.unk9D = 1;
        if (self->step != 1) {
            self->velocityY = FIX(-2.0);
            SetStep(1);
        }
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSalomeCat);
        self->attackElement = 7;
        self->drawFlags |= ENTITY_ROTATE;
        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        self->velocityY = 0;
        self->ext.salome.touchedGround = 0;
        if (self->ext.salome.isDeathCat) {
            self->hitPoints <<= 2;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->rotate = 0;
        if (self->ext.salome.isDeathCat) {
            self->animCurFrame = 0x38;
        } else {
            self->animCurFrame = 0x2F;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        self->velocityY += FIX(3.0 / 32.0);

        if (self->ext.salome.unk9D) {
            self->velocityX = -self->velocityX;
            self->animCurFrame = 0x30;
            if (self->ext.salome.isDeathCat) {
                self->animCurFrame = 0x39;
            }
        }
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        if (self->velocityX > 0) {
            if (!self->ext.salome.touchedGround) {
                posX += 2;
            } else {
                posX += 8;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                if (self->ext.salome.touchedGround & 1) {
                    self->posX.i.hi += collider.unk14;
                    self->velocityX = -self->velocityX;
                }
            } else {
                self->ext.salome.touchedGround |= 1;
            }
        } else {
            if (!self->ext.salome.touchedGround) {
                posX -= 2;
            } else {
                posX -= 8;
            }
            g_api.CheckCollision(posX, posY, &collider, 0);
            if (collider.effects & EFFECT_SOLID) {
                if (self->ext.salome.touchedGround & 1) {
                    self->posX.i.hi += collider.unk1C;
                    self->velocityX = -self->velocityX;
                }
            } else {
                self->ext.salome.touchedGround |= 1;
            }
        }

        posX = self->posX.i.hi;
        if (self->ext.salome.touchedGround & 2) {
            posY = self->posY.i.hi + 8;
        } else {
            posY = self->posY.i.hi + 2;
        }

        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            if (self->ext.salome.touchedGround & 2) {
                self->posY.i.hi += collider.unk18;
                self->velocityY = 0;
                if (self->ext.salome.unk9D) {
                    self->ext.salome.unk9D = 0;
                    if (self->flags & FLAG_DEAD) {
                        PlaySfxPositional(SFX_STUTTER_EXPLODE_LOW);
                        entity = AllocEntity(
                            &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                        if (entity != NULL) {
                            CreateEntityFromEntity(E_EXPLOSION, self, entity);
                            entity->params = EXPLOSION_FIREBALL;
                        }
                        DestroyEntity(self);
                        break;
                    }
                }
                PlaySfxPositional(SFX_STOMP_SOFT_B);
                SetStep(2);
            }
        } else {
            self->ext.salome.touchedGround |= 2;
        }
        break;
    case 2:
        if (self->facingLeft) {
            self->velocityX = FIX(2.0);
        } else {
            self->velocityX = FIX(-2.0);
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi + 8;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            collisionTest = 1;
            if (collider.effects & EFFECT_UNK_8000) {
                if (collider.effects & EFFECT_UNK_4000) {
                    if (self->facingLeft) {
                        collisionTest = 4;
                    } else {
                        collisionTest = 2;
                    }
                } else {
                    if (self->facingLeft) {
                        collisionTest = 2;
                    } else {
                        collisionTest = 4;
                    }
                }
            }
        }

        self->rotate = 0;
        if (collisionTest == 2) {
            self->velocityX -= self->velocityX / 2;
            self->rotate = ROT(45);
            if (collider.effects & EFFECT_UNK_1000) {
                self->rotate = ROT(22.5);
            }
            if (collider.effects & EFFECT_UNK_2000) {
                self->rotate = ROT(11.25);
            }
        }

        if (collisionTest == 4) {
            self->velocityX += self->velocityX / 8;
            self->rotate = ROT(-45);
            if (collider.effects & EFFECT_UNK_1000) {
                self->rotate = ROT(-22.5);
            }
            if (collider.effects & EFFECT_UNK_2000) {
                self->rotate = ROT(-11.25);
            }
        }

        if (self->ext.salome.isDeathCat) {
            hitFlags = AnimateEntity(anim_death_cat_move, self);
        } else {
            hitFlags = AnimateEntity(anim_cat_move, self);
        }

        if (!hitFlags) {
            PlaySfxPositional(SFX_QUIET_STEPS);
        }

        collisionTest = UnkCollisionFunc2(sensors_wall);
        if (collisionTest == 0xFF) {
            self->facingLeft ^= 1;
        }

        if (collisionTest == 0x80) {
            self->velocityY = FIX(-2.0);
            SetStep(1);
        }

        break;
    }
}
