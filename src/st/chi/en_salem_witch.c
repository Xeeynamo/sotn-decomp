/*
 * File: en_salem_witch.c
 * Overlay: CHI
 * Description: ENTITY - Salem Witch
 */

#include "chi.h"

// [Move to same file as salem witch]
// func_801A80A8
void SalemWitchTrySpawnShadow()
{
    Entity* entity;

    if (!(g_Timer & 0xF)) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_SALEM_WITCH, g_CurrentEntity, entity);
            entity->facingLeft = g_CurrentEntity->facingLeft;
            entity->zPriority = g_CurrentEntity->zPriority - 1;
            entity->params = g_CurrentEntity->animCurFrame;
            entity->step = 0x20;    // Shadow_Init
        }
    }
}

extern EntityInit EntityInit_80180688;

// D_80181538
static u8 AnimFrames_TurnAround[] = {
    0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x03, 0x01, 0x03, 0x02,
    0x03, 0x01, 0x04, 0x02, 0x04, 0x01, 0x05, 0x02, 0x05, 0x01, 0x06, 0x02, 0x01, 0x01, 0xFF, 0x00
};

// D_80181558
static u8 AnimFrames_CurseHandMovements[] = {
    0x02, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x06, 0x0B, 0x02, 0x0C,
    0x01, 0x0D, 0x01, 0x0E, 0x01, 0x0F, 0x01, 0x10, 0x01, 0x11, 0x03, 0x12, 0x01, 0x13, 0x02, 0x14,
    0x01, 0x15, 0x01, 0x16, 0x01, 0x07, 0x02, 0x08, 0x02, 0x09, 0x07, 0x0A, 0x01, 0x09, 0x01, 0x08,
    0x01, 0x12, 0x01, 0x11, 0x01, 0x10, 0x01, 0x11, 0x01, 0x10, 0x01, 0x11, 0x01, 0x10, 0x01, 0x0F,
    0xFF, 0x00, 0x00, 0x00
};

// D_8018159C
static u8 AnimFrames_CurseKanjiFlash[] = {
    0x01, 0x0E, 0x01, 0x0D, 0x01, 0x0C, 0x06, 0x0B, 0x03, 0x0C, 0x01, 0x0D, 0x02, 0x16, 0x01, 0x15,
    0x01, 0x14, 0x01, 0x13, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x03, 0x09, 0x01, 0x21, 0x01, 0x22,
    0x0C, 0x09, 0x01, 0x23, 0x01, 0x24, 0x0C, 0x09, 0x01, 0x25, 0x01, 0x26, 0x0C, 0x09, 0x01, 0x27,
    0x01, 0x28, 0xFF, 0x00
};

// D_801815D0
static u8 AnimFrames_CurseReset[] = {
    0x01, 0x0D, 0x01, 0x15, 0x01, 0x17, 0x01, 0x18, 0x03, 0x19, 0x30, 0x18, 0x06, 0x15, 0x06, 0x0D,
    0x20, 0x01, 0xFF, 0x00
};

// D_801815E4
static u8 AnimFrames_TriboltHandsUp[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 0x1A, 0x04, 0x1B,
    0x03, 0x1C, 0x03, 0x1D, 0x03, 0x1E, 0x03, 0x1F, 0x10, 0x20, 0xFF, 0x00
};

// D_80181600
static u8 AnimFrames_TriboltReset[] = {
    0x01, 0x20, 0x03, 0x1F, 0x03, 0x1E, 0x03, 0x1D, 0x03, 0x1C, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01,
    0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x03, 0x02, 0x03, 0x01, 0x03, 0x02, 0x04, 0x01,
    0x04, 0x02, 0x05, 0x01, 0x05, 0x02, 0x06, 0x01, 0x06, 0x02, 0xFF, 0x00
};

// [Find/create/use enum/const for E_EXPLOSION spawn params?]
// E_SALEM_WITCH
// func_801A813C
// https://decomp.me/scratch/XsSqC
// PSP:func_psp_09238760:Match
// PSP:https://decomp.me/scratch/HLIBl
void EntitySalemWitch(Entity* self)
{
    // Movement
    const int IdleCircleSpeed = 32;
    const int IdleCircleSize = 8;
    const int IdleDriftSpeed = FIX(0.125);
    const int DecelerateSlow = 16;
    const int DecelerateFast = 32;
    const int VelocityAlmostStopped = FIX(0.125);
    const int KnockbackSpeed = FIX(1);
    // Attack
    const int AttackPrepYSpeed = FIX(0.5);
    const int AttackPrepXAccel = FIX(0.046875);
    const int AttackPrepXMaxSpeed = FIX(1.25);
    const int AttackPrepWallDetectThreshold = 0x18;
    // Curse
    const int CurseReevaluateThreshold = 0x60;
    const int CurseProjectileSpawnAnimFrameIdx = 5;
    const int CurseProjectileOffsetX = 0x18;
    // Tribolt
    const int TriboltReevaluateThreshold = 0x40;
    const int TriboltTargetYPos = 0x50;
    const int TriboltProjectileOffsetY = -0x20;
    // Anim Frames
    const int AnimFrameIdle = 1;
    const int AnimFrameFlyForward = 3;
    const int AnimFramePause = 4;
    const int AnimFrameFlyBack = 5;
    const int AnimFrameHurt = 6;
    // State Pause Durations
    const int TriboltChargeDuration = 0x40;     // Time from spawning projectiles until returning to Idle state
    const int HurtDuration = 0x18;              // Time from being hit until returning to Idle state
    const int DeathDuration = 0x10;             // Time from losing last HP before the fire particles explosion
    // Shadow
    const int ShadowDuration = 0x60;            // Initial value set on timer for shadow
    const int ShadowTickSpeed = 4;              // Amount removed from timer per update
    const int ShadowDestroyThreshold = 0x20;    // When timer is below this, destroy shadow

    enum Step {
        INIT            = 0x0,
        WAIT_TO_AGGRO   = 0x3,
        IDLE            = 0x5,
        TURN_AROUND     = 0x4,
        ATTACK          = 0x7,
        ATTACK_CURSE    = 0x6,
        ATTACK_TRIBOLT  = 0x8,
        HURT            = 0xA,
        DEATH           = 0x10,
        SHADOW_INIT     = 0x20,
        SHADOW_WAIT     = 0x21,
        DEBUG           = 0xFF,
    };

    enum Attack_Substep {
        ATTACK_INIT             = 0,
        ATTACK_MOVE_TO_POSITION = 1,
        ATTACK_REEVALUATE_MOVE  = 2,
        ATTACK_PERFORM          = 3,
    };

    enum Attack_Curse_Substep {
        ATTACK_CURSE_INIT                       = 0,
        ATTACK_CURSE_CAST                       = 1,
        ATTACK_CURSE_CHARGE                     = 2,
        ATTACK_CURSE_SPAWN_PROJECTILE_AND_RESET = 3,
    };

    enum Attack_Tribolt_Substep {
        ATTACK_TRIBOLT_INIT             = 0,
        ATTACK_TRIBOLT_HANDS_UP         = 1,
        ATTACK_TRIBOLT_SPAWN_PROJECTILE = 2,
        ATTACK_TRIBOLT_WAIT             = 3,
        ATTACK_TRIBOLT_RESET            = 4,
    };

    enum Hurt_Substep {
        HURT_INIT = 0,
        HURT_WAIT = 1,
    };

    enum Death_Substep {
        DEATH_INIT      = 0,
        DEATH_WAIT      = 1,
        DEATH_EXPLODE   = 2,
    };

    Entity* entity;
    Collider collider;
    s32 xPos;
    s16 idleCircleAngle;
    s32 isToRightOfPlayer;
    s32 yPos;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        SetStep(HURT);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < DEATH)) {
        SetStep(DEATH);
    }
    switch (self->step) {
        case INIT:
            InitializeEntity(&EntityInit_80180688);
            self->hitboxOffY = 0xA;
            entity = self + 1;
            CreateEntityFromCurrentEntity(E_SALEM_WITCH_GLOW, entity);
            entity->zPriority = self->zPriority - 1;
            SetStep(WAIT_TO_AGGRO);
            break;

        case WAIT_TO_AGGRO:
            if ((GetDistanceToPlayerX() < 0xA0) && (GetDistanceToPlayerY() < 0x70)) {
                SetStep(IDLE);
            }
            break;

        case IDLE:
            // Reset on entry
            if (!self->step_s) {
                self->velocityX = 0;
                self->velocityY = 0;
                self->ext.salemWitch.isDriftDirectionUp = false;
                self->animCurFrame = AnimFrameIdle;
                self->step_s += 1;
            }

            MoveEntity();
            SalemWitchTrySpawnShadow();

            // Move in circles
            idleCircleAngle = self->ext.salemWitch.idleCircleTimer += IdleCircleSpeed;
            idleCircleAngle &= 0xFFF;
            self->velocityX = rcos(idleCircleAngle) * IdleCircleSize;
            self->velocityY = rsin(idleCircleAngle) * IdleCircleSize;

            // Slowly drift up/down
            if (self->ext.salemWitch.isDriftDirectionUp) {
                self->velocityY += IdleDriftSpeed;
            } else {
                self->velocityY -= IdleDriftSpeed;
            }

            // Check for valid targeting circumstances (every 0.85s)
            if (!(self->ext.salemWitch.idleCircleTimer & 0x3FF)) {
                entity = &PLAYER;
                // Close and facing opposite (presumably, engaging)
                if (GetDistanceToPlayerX() < 0x68 && (entity->facingLeft != self->facingLeft)) {
                    self->ext.salemWitch.thinksPlayerIsEngaging = true;
                    SetStep(ATTACK);
                }
                // Far and facing same (presumably, retreating)
                if ((GetDistanceToPlayerX() > 0x58) && (entity->facingLeft == self->facingLeft)) {
                    self->ext.salemWitch.thinksPlayerIsEngaging = false;
                    SetStep(ATTACK);
                }
            }

            // Check to reverse drift direction (every 2.1s)
            if (!(self->ext.salemWitch.idleCircleTimer & 0xFFF)) {
                if (self->posY.i.hi < 0x60) {   // If too close to top of screen
                    self->ext.salemWitch.isDriftDirectionUp = true;
                } else {
                    self->ext.salemWitch.isDriftDirectionUp = false;
                }
            }

            // Turn to face player if necessary
            isToRightOfPlayer = GetSideToPlayer() & 1;
            if (self->facingLeft != isToRightOfPlayer) {
                SetStep(TURN_AROUND);
            }
            break;

        case TURN_AROUND:
            if (!self->step_s) {
                self->facingLeft ^= 1;  // Turn around
                self->step_s++;
            }

            MoveEntity();
            SalemWitchTrySpawnShadow();

            // Slow down
            self->velocityX -= self->velocityX / DecelerateSlow;
            self->velocityY -= self->velocityY / DecelerateSlow;
            if (!AnimateEntity(AnimFrames_TurnAround, self)) {
                SetStep(IDLE);
            }
            break;

        case ATTACK:
            switch (self->step_s) {
                case ATTACK_INIT:
                    self->velocityY = 0;
                    // Move to position for a random amount of time between ~0.25s and ~0.75s
                    self->ext.salemWitch.timer = (Random() & 0x1F) + 0x10;
                    self->step_s++;
                    // fallthrough
                case ATTACK_MOVE_TO_POSITION:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Detect target movement position
                    entity = &PLAYER;
                    if (self->ext.salemWitch.willCurseNextAttack) {
                        // Curse: Try to vertically align with player
                        self->ext.salemWitch.targetYPos = entity->posY.i.hi;
                        xPos = CurseReevaluateThreshold;
                    } else {
                        // Tribolt: Try to get a bit more vertically central
                        self->ext.salemWitch.targetYPos = TriboltTargetYPos;
                        xPos = TriboltReevaluateThreshold;
                    }
                    yPos = self->posY.i.hi - self->ext.salemWitch.targetYPos;

                    // Vertical movement
                    if (yPos > 0) {
                        self->velocityY = -AttackPrepYSpeed;
                    } else {
                        self->velocityY = AttackPrepYSpeed;
                    }

                    // Set up visuals to match horizontal movement
                    if (self->ext.salemWitch.thinksPlayerIsEngaging) {
                        self->animCurFrame = AnimFrameFlyBack;
                    } else {
                        self->animCurFrame = AnimFrameFlyForward;
                    }

                    // Calculate horizontal movement
                    if (self->facingLeft ^ self->ext.salemWitch.thinksPlayerIsEngaging) {
                        // Move left
                        self->velocityX -= AttackPrepXAccel;
                        if (self->velocityX <= -AttackPrepXMaxSpeed) {
                            self->velocityX = -AttackPrepXMaxSpeed;
                        }
                    } else {
                        // Move right
                        self->velocityX += AttackPrepXAccel;
                        if (self->velocityX >= AttackPrepXMaxSpeed) {
                            self->velocityX = AttackPrepXMaxSpeed;
                        }
                    }

                    // Retreating and close
                    if (!self->ext.salemWitch.thinksPlayerIsEngaging &&
                        GetDistanceToPlayerX() < xPos) {
                        SetSubStep(ATTACK_REEVALUATE_MOVE);
                    }

                    // Engaging and far
                    if (self->ext.salemWitch.thinksPlayerIsEngaging) {
                        if (xPos < GetDistanceToPlayerX()) {
                            SetSubStep(ATTACK_REEVALUATE_MOVE);
                        }
                    }

                    // Detect if movement put self near a wall
                    xPos = self->posX.i.hi;
                    yPos = self->posY.i.hi;
                    if (self->velocityX > 0) {
                        xPos += AttackPrepWallDetectThreshold;
                    }
                    if (self->velocityX < 0) {
                        xPos -= AttackPrepWallDetectThreshold;
                    }
                    g_api.CheckCollision(xPos, yPos, &collider, 0);
                    // If so, short-circuit the "random amount of time" calculated in prev substep
                    if (collider.effects & EFFECT_SOLID) {
                        self->ext.salemWitch.timer = 1;
                    }
                    if (!--self->ext.salemWitch.timer) {
                        SetSubStep(ATTACK_PERFORM);
                    }

                    // Turn to face player if necessary
                    isToRightOfPlayer = GetSideToPlayer() & 1;
                    if (self->facingLeft != isToRightOfPlayer) {
                        SetStep(TURN_AROUND);
                    }
                break;

                case ATTACK_REEVALUATE_MOVE:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateSlow;
                    self->animCurFrame = AnimFramePause;
                    if (abs(self->velocityX) < VelocityAlmostStopped) {
                        self->ext.salemWitch.thinksPlayerIsEngaging ^= 1;
                        SetSubStep(ATTACK_MOVE_TO_POSITION);
                    }
                    break;

                case ATTACK_PERFORM:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateSlow;
                    self->animCurFrame = AnimFramePause;
                    if (abs(self->velocityX) < VelocityAlmostStopped) {
                        if (self->ext.salemWitch.willCurseNextAttack) {
                            SetStep(ATTACK_CURSE);
                        } else {
                            SetStep(ATTACK_TRIBOLT);
                        }
                        self->ext.salemWitch.willCurseNextAttack ^= 1;  // Toggle between attacks
                    }
                    break;
            }
            break;

        case ATTACK_CURSE:
            self->ext.salemWitch.timer++;
            switch (self->step_s) {
                case ATTACK_CURSE_INIT:
                    PlaySfxPositional(NA_SE_EN_SALEM_WITCH_ATTACK);
                    self->step_s++;
                    // fallthrough
                case ATTACK_CURSE_CAST:
                    if (!(self->ext.salemWitch.timer & 0xF)) {  // This triggers 3x during the animation
                        PlaySfxPositional(NA_SE_EN_SALEM_WITCH_HAND_MOVEMENT);
                    }
                    if (!AnimateEntity(AnimFrames_CurseHandMovements, self)) {
                        SetSubStep(ATTACK_CURSE_CHARGE);
                    }
                    break;

                case ATTACK_CURSE_CHARGE:
                    if (!(self->ext.salemWitch.timer & 0xF)) {  // This triggers 3x during the animation
                        PlaySfxPositional(NA_SE_EN_ELECTRIC_ZAP);
                    }
                    if (!AnimateEntity(AnimFrames_CurseKanjiFlash, self)) {
                        SetSubStep(ATTACK_CURSE_SPAWN_PROJECTILE_AND_RESET);
                    }
                    break;

                case ATTACK_CURSE_SPAWN_PROJECTILE_AND_RESET:
                    if (!AnimateEntity(AnimFrames_CurseReset, self)) {
                        SetStep(IDLE);
                    }
                    if (!self->animFrameDuration &&
                        self->animFrameIdx == CurseProjectileSpawnAnimFrameIdx) {
                        PlaySfxPositional(NA_SE_EN_SALEM_WITCH_CURSE_LAUNCH);
                        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                        if (entity != NULL) {
                            CreateEntityFromEntity(E_SALEM_WITCH_CURSE, self, entity);
                            if (self->facingLeft) {
                                entity->posX.i.hi -= CurseProjectileOffsetX;
                            } else {
                                entity->posX.i.hi += CurseProjectileOffsetX;
                            }
                            entity->facingLeft = self->facingLeft;
                        }
                    }
                    break;
            }
            break;

        case ATTACK_TRIBOLT:
            switch (self->step_s) {
                case ATTACK_TRIBOLT_INIT:
                    PlaySfxPositional(NA_SE_EN_SALEM_WITCH_ATTACK);
                    self->step_s++;
                    // fallthrough
                case ATTACK_TRIBOLT_HANDS_UP:
                    if (!AnimateEntity(AnimFrames_TriboltHandsUp, self)) {
                        SetSubStep(ATTACK_TRIBOLT_SPAWN_PROJECTILE);
                    }
                    break;

                case ATTACK_TRIBOLT_SPAWN_PROJECTILE:
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_SALEM_WITCH_TRIBOLT_LAUNCH, self, entity);
                        entity->zPriority = self->zPriority + 1;
                        entity->posY.i.hi += TriboltProjectileOffsetY;
                    }
                    self->ext.salemWitch.timer = TriboltChargeDuration;
                    self->step_s++;
                    // fallthrough
                case ATTACK_TRIBOLT_WAIT:
                    if (!--self->ext.salemWitch.timer) {
                        self->step_s++;
                    }
                    break;

                case ATTACK_TRIBOLT_RESET:
                    if (!AnimateEntity(AnimFrames_TriboltReset, self)) {
                        SetStep(IDLE);
                    }
                    break;
            }
            break;

        case HURT:
            switch (self->step_s) {
                case HURT_INIT:
                    // Knockback
                    if (self->facingLeft) {
                        self->velocityX = KnockbackSpeed;
                    } else {
                        self->velocityX = -KnockbackSpeed;
                    }
                    self->velocityY = 0;

                    self->ext.salemWitch.timer = HurtDuration;
                    self->animCurFrame = AnimFrameHurt;
                    PlaySfxPositional(NA_SE_EN_SALEM_WITCH_HURT);
                    self->step_s++;
                    // fallthrough
                case HURT_WAIT:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down movement
                    self->velocityX -= self->velocityX / DecelerateFast;
                    self->velocityY -= self->velocityY / DecelerateFast;
                    if (!--self->ext.salemWitch.timer) {
                        SetStep(IDLE);
                    }
                    break;
            }
            break;

        case DEATH:
            switch (self->step_s) {
                case DEATH_INIT:
                    // Death for the shadow too
                    entity = self + 1;
                    entity->step = DEATH;

                    self->hitboxState = 0;

                    // Knockback
                    if (self->facingLeft) {
                        self->velocityX = KnockbackSpeed;
                    } else {
                        self->velocityX = -KnockbackSpeed;
                    }
                    self->velocityY = 0;

                    self->ext.salemWitch.timer = DeathDuration;
                    self->animCurFrame = AnimFrameHurt;
                    PlaySfxPositional(NA_SE_EN_SALEM_WITCH_DEATH);
                    self->step_s++;
                    // fallthrough
                case DEATH_WAIT:
                    MoveEntity();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateFast;
                    if (!--self->ext.salemWitch.timer) {
                        self->step_s++;
                    }
                    break;

                case DEATH_EXPLODE:
                    PlaySfxPositional(NA_SE_FIRE_BURST);

                    // Fire particles
                    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_EXPLOSION, self, entity);
                        entity->params = 2;
                    }
                    DestroyEntity(self);
                    return;
            }
            break;

        case SHADOW_INIT:
            InitializeEntity(&EntityInit_80180688);
            self->flags |= 0x2000;
            self->hitboxState = 0;
            self->animCurFrame = self->params;
            self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
            self->drawFlags = FLAG_DRAW_UNK8;
            self->unk6C = ShadowDuration;
            // fallthrough
        case SHADOW_WAIT:
            self->unk6C -= ShadowTickSpeed;
            if (self->unk6C < ShadowDestroyThreshold) {
                DestroyEntity(self);
            }
            return;

        case DEBUG:
            FntPrint("charal %x\n", self->animCurFrame);
            if (g_pads[1].pressed & PAD_SQUARE) {
                if (self->params) {
                    break;
                } else {
                    self->animCurFrame++;
                    self->params |= true;
                }
            } else {
                self->params = false;
            }
            if (g_pads[1].pressed & PAD_CIRCLE) {
                if (!self->step_s) {
                    self->animCurFrame--;
                    self->step_s |= true;
                }
            } else {
                self->step_s = false;
            }
            break;
    }

    // Clamp x position to always be on screen
    xPos = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    if (self->velocityX > 0) {
        if (g_Tilemap.width < xPos) {
            self->posX.i.hi = g_Tilemap.width - g_Tilemap.scrollX.i.hi;
        }
    } else if (xPos < g_Tilemap.x) {
        self->posX.i.hi = g_Tilemap.x - g_Tilemap.scrollX.i.hi;
    }
}

// D_8018162C
static u8 AnimFrames_Twinkle[] = {
    0x02, 0x29, 0x02, 0x2A, 0x02, 0x2B, 0x02, 0x2C, 0x00, 0x00, 0x00, 0x00
};

// E_SALEM_WITCH_GLOW
// func_801A8DE8
// PSP:func_psp_092399B0:Match
// PSP:https://decomp.me/scratch/Oqz9t
void EntitySalemWitchGlow(Entity* self)
{
    Entity* entity;

    if (!self->step) {
        InitializeEntity(&EntityInit_80180688);
        self->flags |= FLAG_UNK_2000;
        self->hitboxState = 0;
        self->drawMode = DRAW_TPAGE | DRAW_TPAGE2 | DRAW_UNK_40;
    }

    AnimateEntity(AnimFrames_Twinkle, self);

    entity = self - 1;
    self->facingLeft = entity->facingLeft;
    self->posX.val = entity->posX.val;
    if (self->facingLeft) {
        self->posX.val += FIX(6);
    } else {
        self->posX.val -= FIX(6);
    }
    self->posY.val = entity->posY.val + FIX(2);

    if (entity->entityId != E_SALEM_WITCH) {
        DestroyEntity(self);
    }
}

// D_80181638
static u8 AnimFrames_CurseProjectile[] = {
    0x01, 0x2D, 0x01, 0x2E, 0x01, 0x2F, 0x01, 0x30, 0x01, 0x31, 0x01, 0x32, 0x01, 0x33, 0x01, 0x34,
    0x01, 0x35, 0x01, 0x36, 0x01, 0x37, 0x01, 0x38, 0x01, 0x39, 0x01, 0x3A, 0x01, 0x3B, 0x01, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x06,
    0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E,
    0x00, 0x00, 0x00, 0x00
};

extern EntityInit EntityInit_80180694;
extern signed short* sprites_chi_4[];

// [Should sprite groups be structs, similar to EntityInit?]
// [Are sprite groups specific to a PART of the texture page? Is that why we need the 0x7F offset?]
// E_SALEM_WITCH_CURSE
// func_801A8EAC
// PSP:func_psp_09239AC8:Match
// PSP:https://decomp.me/scratch/AGNPO
void EntitySalemWitchCurse(Entity* self)
{
    const int ProjectileSpeed = FIX(3.5);
    //TODO: Should sprite groups be structs?
    const int SpriteUvOffset = 8;
    const int ProjectileSpriteMinIdx = 1;
    const int ProjectileSpriteMaxIdx = 7;
    const int TrailSpriteMinIdx = 8;
    const int TrailSpriteMaxIdx = 14;
    const int TrailStartBrightness = 0x60;
    const int TrailDarkenSpeed = 4;

    enum Step {
        INIT = 0,
        UPDATE = 1,
    };

    Primitive* prim;
    s32 primIdx;
    s16* spriteUVs;

    switch (self->step) {
        case INIT:
            InitializeEntity(&EntityInit_80180694);

            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            if (self->facingLeft) {
                self->velocityX = -ProjectileSpeed;
            } else {
                self->velocityX = ProjectileSpeed;
            }

            primIdx = g_api.AllocPrimitives(PRIM_GT4, 0x10);
            if (primIdx == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            prim = &g_PrimBuf[primIdx];
            self->ext.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = PAL_DRA(0x2EB);
                prim->p3 = 0;
                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
            // Fallthrough
        case UPDATE:
            MoveEntity();
            AnimateEntity(&AnimFrames_CurseProjectile, self);   // Animates Kanji on projectile

            // First prim is projectile itself
            prim = self->ext.prim;
            prim->x0 = prim->x2 = self->posX.i.hi - 8;
            prim->x1 = prim->x3 = self->posX.i.hi + 8;
            prim->y0 = prim->y1 = self->posY.i.hi - 8;
            prim->y2 = prim->y3 = self->posY.i.hi + 8;

            // Check if necessary to update to new sprite
            if (!prim->p2) {    // p2 == 0 means "request sprite UV update"
                prim->p1 += 1;  // p1 is sprite index
                // Loop sprites
                if (prim->p1 > ProjectileSpriteMaxIdx) {
                    prim->p1 = ProjectileSpriteMinIdx;
                }

                // Update UVs
                spriteUVs = sprites_chi_4[prim->p1];
                spriteUVs += SpriteUvOffset;
                if (self->facingLeft) {
                    prim->u2 = prim->u3 = *spriteUVs++;
                    prim->v0 = prim->v2 = *spriteUVs++ + 0x7F;
                    prim->u0 = prim->u1 = *spriteUVs++;
                    prim->v1 = prim->v3 = *spriteUVs++ + 0x7F;
                } else {
                    prim->u2 = prim->u3 = *spriteUVs++;
                    prim->v1 = prim->v3 = *spriteUVs++ + 0x7F;
                    prim->u0 = prim->u1 = *spriteUVs++;
                    prim->v0 = prim->v2 = *spriteUVs++ + 0x7F;
                }
                prim->p2 = 1;
            } else {
                prim->p2 -= 1;
            }
            prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_TPAGE | DRAW_TPAGE2;

            // 50/50 chance to try to spawn part of trail
            if (Random() & 1) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;
                    prim->p1 = TrailSpriteMinIdx;
                    prim->p2 = 0;   // "Request sprite UV update"
                    prim->r0 = prim->g0
                        = prim->b0 = prim->r1
                        = prim->g1 = prim->b1
                        = prim->r2 = prim->g2
                        = prim->b2 = prim->r3
                        = prim->g3 = prim->b3
                        = TrailStartBrightness;
                    prim->x0 = prim->x2 = self->posX.i.hi - 8;
                    prim->x1 = prim->x3 = self->posX.i.hi + 8;
                    prim->y0 = prim->y1 = self->posY.i.hi - 8;
                    prim->y2 = prim->y3 = self->posY.i.hi + 8;
                }
            }

            // Update whole trail
            prim = self->ext.prim;
            prim = prim->next;
            while (prim != NULL) {
                if (prim->p3) {
                    // Despawn if fade has run its course
                    prim->r0 -= TrailDarkenSpeed;
                    if (!prim->r0) {
                        prim->p3 = 0;
                        prim->drawMode = DRAW_HIDE;
                        prim = prim->next;
                        continue;
                    }

                    // All colors match because it's just a grayscale gradient
                    prim->g0 = prim->b0 = prim->r0;
                    prim->r1 = prim->g1
                        = prim->b1 = prim->r2
                        = prim->g2 = prim->b2
                        = prim->r3 = prim->g3
                        = prim->b3 = prim->r0;

                    if (!prim->p2) {
                        // Slowly increase size
                        prim->x0 = --prim->x2;
                        prim->x1 = ++prim->x3;
                        prim->y0 = --prim->y1;
                        prim->y2 = ++prim->y3;

                        // Next sprite
                        prim->p1++;
                        // Check for despawn
                        if (prim->p1 > TrailSpriteMaxIdx) {
                            prim->p3 = 0;
                            prim->drawMode = DRAW_HIDE;
                            prim = prim->next;
                            continue;
                        }

                        // Update UVs
                        spriteUVs = sprites_chi_4[prim->p1];
                        spriteUVs += SpriteUvOffset;
                        if (self->facingLeft) {
                            prim->u2 = prim->u3 = *spriteUVs++;
                            prim->v0 = prim->v2 = *spriteUVs++ + 0x7F;
                            prim->u0 = prim->u1 = *spriteUVs++;
                            prim->v1 = prim->v3 = *spriteUVs++ + 0x7F;
                        } else {
                            prim->u2 = prim->u3 = *spriteUVs++;
                            prim->v1 = prim->v3 = *spriteUVs++ + 0x7F;
                            prim->u0 = prim->u1 = *spriteUVs++;
                            prim->v0 = prim->v2 = *spriteUVs++ + 0x7F;
                        }
                        prim->p2 = 1;
                    } else {
                        prim->p2 -= 1;
                    }
                    prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_COLORS | DRAW_TPAGE | DRAW_TPAGE2;
                }
                prim = prim->next;
            }
            return;
    }
}

// D_8018167C
static u8 AnimFrames_TriboltCharge[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x06, 0x02, 0x07, 0x02, 0x08,
    0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x02, 0x0F, 0x02, 0x10,
    0x02, 0x11, 0x02, 0x12, 0x02, 0x13, 0x02, 0x14, 0x02, 0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x18,
    0xFF, 0x00, 0x00, 0x00
};

// D_801816B0
static u8 AnimFrames_TriboltBurst[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x06, 0xFF, 0x00, 0x00, 0x00
};

extern EntityInit g_EInitGeneric;

// E_SALEM_WITCH_TRIBOLT_LAUNCH
// func_801A93D4
void EntitySalemWitchTriboltLaunch(Entity* self)
{
    const int ProjectileCount = 3;
    const int BurstStartRotation = 0x80;
    const int BurstRotateSpeed = 0x40;

    enum Step {
        INIT = 0,
        CHARGE = 1,
        SPAWN_PROJECTILES = 2,
        BURST = 3,
        CLEANUP = 4,
    };

    Entity* entity;
    s16 rot;
    s32 i;

    switch (self->step) {
        case INIT:
            InitializeEntity(&g_EInitGeneric);
            self->animSet = 5;
            self->palette = PAL_OVL(0x2EB);
            self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
            self->unk6C = 0x60;
            self->drawFlags |= FLAG_DRAW_UNK8;

            PlaySfxPositional(NA_SE_EN_SALEM_WITCH_TRIBOLT_LAUNCH);
            // fallthrough
        case CHARGE:
            if (AnimateEntity(&AnimFrames_TriboltCharge, self) == 0) {
                SetStep(SPAWN_PROJECTILES);
            }
            return;

        case SPAWN_PROJECTILES:
            self->animSet = -0x7FFA;
            self->unk5A = 0x4B;
            self->rotY = BurstStartRotation;
            self->rotX = BurstStartRotation;
            self->unk6C = 0x80;
            self->drawFlags |= FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->step += 1;
            self->drawFlags |= FLAG_DRAW_UNK8;

            PlaySfxPositional(NA_SE_EN_DR_FIREBALL);

            for (i = 0; i < ProjectileCount; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SALEM_WITCH_TRIBOLT_PROJECTILE, self, entity);
                    entity->params = i;
                }
            }
            // fallthrough
        case BURST:
            rot = self->rotY + BurstRotateSpeed;
            self->rotY = rot;
            self->rotX = rot;
            self->unk6C -= 4;
            if (AnimateEntity(&AnimFrames_TriboltBurst, self) == 0) {
                SetStep(CLEANUP);
            }
            break;

        case CLEANUP:
            DestroyEntity(self);
            break;
    }
}

// D_801816C0
static u8 AnimFrames_TriboltProjectile[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00
};

// D_801816D0
static u8 AnimFrames_TriboltTrail[] = {
    0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x06, 0x02, 0x07, 0x02, 0x08,
    0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0xFF, 0x00
};

extern Entity D_8007D858;
extern u16 EntityInit_801806A0;

// E_SALEM_WITCH_TRIBOLT_PROJECTILE
// func_801A9588
void EntitySalemWitchTriboltProjectile(Entity* self)
{
    const int RotateSpeed = 0x10;
    const int LinearSpeed = 0x30;
    const int SpinSpeed = 0x400;

    enum Step {
        INIT = 0,
        UPDATE = 1,
        TRAIL_INIT = 8,
        TRAIL_UPDATE = 9,
    };

    Entity* entity;
    s16 rot;
    s16 timer;
    s16 rotSansSpin;
    s32 launchDir;

    switch (self->step) {
        case INIT:
            InitializeEntity(&EntityInit_801806A0);
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ;
            self->rotX = 0x80;
            launchDir = self->params - 1;
            self->rotZ = GetAngleBetweenEntities(self, &PLAYER) + (launchDir << 9) + SpinSpeed;
            self->ext.salemWitchTribolt.timer = 0x40;
            // fallthrough
        case UPDATE:
            MoveEntity();
            AnimateEntity(&AnimFrames_TriboltProjectile, self);

            // Update velocity on curve
            timer = self->ext.salemWitchTribolt.timer;
            launchDir = self->params - 1;
            if (timer != 0) {
                self->ext.salemWitchTribolt.timer = timer - 1;
                rot = self->rotZ - (launchDir * RotateSpeed);
                rotSansSpin = rot - SpinSpeed;
                self->rotZ = rot;
            } else {
                rotSansSpin = (self->rotZ + (launchDir << 9)) - SpinSpeed;
            }
            self->velocityX = rcos(rotSansSpin) * LinearSpeed;
            self->velocityY = rsin(rotSansSpin) * LinearSpeed;

            // 50/50 chance to try to spawn part of trail
            if (Random() & 1) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_SALEM_WITCH_TRIBOLT_PROJECTILE, self, entity);
                    entity->animSet = self->animSet;
                    entity->rotZ = self->rotZ;
                    entity->rotX = self->rotX;
                    entity->params = self->animCurFrame;
                    entity->zPriority = self->zPriority + 1;
                    entity->step = TRAIL_INIT;
                }
            }
            break;

        case TRAIL_INIT:
            InitializeEntity(&EntityInit_801806A0);
            self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
            self->animCurFrame = self->params;
            self->hitboxState = 0;
            self->unk6C = 0x60;
            self->animFrameIdx = self->animCurFrame;
            // fallthrough
        case TRAIL_UPDATE:
            self->unk6C += 0xFC;
            if (AnimateEntity(&AnimFrames_TriboltTrail, self) == 0) {
                DestroyEntity(self);
            }
            break;
    }
}