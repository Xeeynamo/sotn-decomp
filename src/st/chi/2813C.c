#include "chi.h"

/*
 * File: 2813C.c
 * Overlay: CHI
 * Description: Abandoned Mine
 */

extern EntityInit EntityInit_80180688;

// D_80181538
u8 AnimFrames_TurnAround[] = {
    0x01, 0x01, 0x01, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x03, 0x01, 0x03, 0x02,
    0x03, 0x01, 0x04, 0x02, 0x04, 0x01, 0x05, 0x02, 0x05, 0x01, 0x06, 0x02, 0x01, 0x01, 0xFF, 0x00
};

// D_80181558
u8 AnimFrames_CurseHandMovements[] = {
    0x02, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x06, 0x0B, 0x02, 0x0C,
    0x01, 0x0D, 0x01, 0x0E, 0x01, 0x0F, 0x01, 0x10, 0x01, 0x11, 0x03, 0x12, 0x01, 0x13, 0x02, 0x14,
    0x01, 0x15, 0x01, 0x16, 0x01, 0x07, 0x02, 0x08, 0x02, 0x09, 0x07, 0x0A, 0x01, 0x09, 0x01, 0x08,
    0x01, 0x12, 0x01, 0x11, 0x01, 0x10, 0x01, 0x11, 0x01, 0x10, 0x01, 0x11, 0x01, 0x10, 0x01, 0x0F,
    0xFF, 0x00, 0x00, 0x00
};

// D_8018159C
u8 AnimFrames_CurseKanjiFlash[] = {
    0x01, 0x0E, 0x01, 0x0D, 0x01, 0x0C, 0x06, 0x0B, 0x03, 0x0C, 0x01, 0x0D, 0x02, 0x16, 0x01, 0x15,
    0x01, 0x14, 0x01, 0x13, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x03, 0x09, 0x01, 0x21, 0x01, 0x22,
    0x0C, 0x09, 0x01, 0x23, 0x01, 0x24, 0x0C, 0x09, 0x01, 0x25, 0x01, 0x26, 0x0C, 0x09, 0x01, 0x27,
    0x01, 0x28, 0xFF, 0x00
};

// D_801815D0
u8 AnimFrames_CurseReset[] = {
    0x01, 0x0D, 0x01, 0x15, 0x01, 0x17, 0x01, 0x18, 0x03, 0x19, 0x30, 0x18, 0x06, 0x15, 0x06, 0x0D,
    0x20, 0x01, 0xFF, 0x00
};

// D_801815E4
u8 AnimFrames_TriboltHandsUp[] = {
    0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 0x1A, 0x04, 0x1B,
    0x03, 0x1C, 0x03, 0x1D, 0x03, 0x1E, 0x03, 0x1F, 0x10, 0x20, 0xFF, 0x00
};

// D_80181600
u8 AnimFrames_TriboltReset[] = {
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
        Init            = 0x0,
        WaitToAggro     = 0x3,
        Idle            = 0x5,
        TurnAround      = 0x4,
        Attack          = 0x7,
        Attack_Curse    = 0x6,
        Attack_Tribolt  = 0x8,
        Hurt            = 0xA,
        Death           = 0x10,
        Shadow_Init     = 0x20,
        Shadow_Wait     = 0x21,
        Debug           = 0xFF,
    };

    enum Attack_Substep {
        Attack_Init             = 0,
        Attack_MoveToPosition   = 1,
        Attack_ReevaluateMove   = 2,
        Attack_Perform          = 3,
    };

    enum Attack_Curse_Substep {
        Attack_Curse_Init                       = 0,
        Attack_Curse_Cast                       = 1,
        Attack_Curse_Charge                     = 2,
        Attack_Curse_SpawnProjectileAndReset    = 3,
    };

    enum Attack_Tribolt_Substep {
        Attack_Tribolt_Init             = 0,
        Attack_Tribolt_HandsUp          = 1,
        Attack_Tribolt_SpawnProjectile  = 2,
        Attack_Tribolt_Wait             = 3,
        Attack_Tribolt_Reset            = 4,
    };

    enum Hurt_Substep {
        Hurt_Init = 0,
        Hurt_Wait = 1,
    };

    enum Death_Substep {
        Death_Init = 0,
        Death_Wait = 1,
        Death_Explode = 2,
    };

    Entity* entity;
    Collider collider;
    s32 xPos;
    s16 idleCircleAngle;
    s32 isToRightOfPlayer;
    s32 yPos;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        SetStep(Hurt);
    }
    if ((self->flags & FLAG_DEAD) && (self->step < Death)) {
        SetStep(Death);
    }
    switch (self->step) {
        case Init:
            InitializeEntity(&EntityInit_80180688);
            self->hitboxOffY = 0xA;
            entity = self + 1;
            CreateEntityFromCurrentEntity(E_SALEM_WITCH_GLOW, entity);
            entity->zPriority = self->zPriority - 1;
            SetStep(WaitToAggro);
            break;

        case WaitToAggro:
            if ((GetDistanceToPlayerX() < 0xA0) && (GetDistanceToPlayerY() < 0x70)) {
                SetStep(Idle);
            }
            break;

        case Idle:
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
                    SetStep(Attack);
                }
                // Far and facing same (presumably, retreating)
                if ((GetDistanceToPlayerX() > 0x58) && (entity->facingLeft == self->facingLeft)) {
                    self->ext.salemWitch.thinksPlayerIsEngaging = false;
                    SetStep(Attack);
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
                SetStep(TurnAround);
            }
            break;

        case TurnAround:
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
                SetStep(Idle);
            }
            break;

        case Attack:
            switch (self->step_s) {
                case Attack_Init:
                    self->velocityY = 0;
                    // Move to position for a random amount of time between ~0.25s and ~0.75s
                    self->ext.salemWitch.timer = (Random() & 0x1F) + 0x10;
                    self->step_s++;
                    // fallthrough
                case Attack_MoveToPosition:
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
                        SetSubStep(Attack_ReevaluateMove);
                    }

                    // Engaging and far
                    if (self->ext.salemWitch.thinksPlayerIsEngaging) {
                        if (xPos < GetDistanceToPlayerX()) {
                            SetSubStep(Attack_ReevaluateMove);
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
                        SetSubStep(Attack_Perform);
                    }

                    // Turn to face player if necessary
                    isToRightOfPlayer = GetSideToPlayer() & 1;
                    if (self->facingLeft != isToRightOfPlayer) {
                        SetStep(TurnAround);
                    }
                break;

                case Attack_ReevaluateMove:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateSlow;
                    self->animCurFrame = AnimFramePause;
                    if (abs(self->velocityX) < VelocityAlmostStopped) {
                        self->ext.salemWitch.thinksPlayerIsEngaging ^= 1;
                        SetSubStep(Attack_MoveToPosition);
                    }
                    break;

                case Attack_Perform:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateSlow;
                    self->animCurFrame = AnimFramePause;
                    if (abs(self->velocityX) < VelocityAlmostStopped) {
                        if (self->ext.salemWitch.willCurseNextAttack) {
                            SetStep(Attack_Curse);
                        } else {
                            SetStep(Attack_Tribolt);
                        }
                        self->ext.salemWitch.willCurseNextAttack ^= 1;  // Toggle between attacks
                    }
                    break;
            }
            break;

        case Attack_Curse:
            self->ext.salemWitch.timer++;
            switch (self->step_s) {
                case Attack_Curse_Init:
                    PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_ATTACK);
                    self->step_s++;
                    // fallthrough
                case Attack_Curse_Cast:
                    if (!(self->ext.salemWitch.timer & 0xF)) {  // This triggers 3x during the animation
                        PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_HAND_MOVEMENT);
                    }
                    if (!AnimateEntity(AnimFrames_CurseHandMovements, self)) {
                        SetSubStep(Attack_Curse_Charge);
                    }
                    break;

                case Attack_Curse_Charge:
                    if (!(self->ext.salemWitch.timer & 0xF)) {  // This triggers 3x during the animation
                        PlaySfxWithPosArgs(NA_SE_EN_ELECTRIC_ZAP);
                    }
                    if (!AnimateEntity(AnimFrames_CurseKanjiFlash, self)) {
                        SetSubStep(Attack_Curse_SpawnProjectileAndReset);
                    }
                    break;

                case Attack_Curse_SpawnProjectileAndReset:
                    if (!AnimateEntity(AnimFrames_CurseReset, self)) {
                        SetStep(Idle);
                    }
                    if (!self->animFrameDuration &&
                        self->animFrameIdx == CurseProjectileSpawnAnimFrameIdx) {
                        PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_CURSE_LAUNCH);
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

        case Attack_Tribolt:
            switch (self->step_s) {
                case Attack_Tribolt_Init:
                    PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_ATTACK);
                    self->step_s++;
                    // fallthrough
                case Attack_Tribolt_HandsUp:
                    if (!AnimateEntity(AnimFrames_TriboltHandsUp, self)) {
                        SetSubStep(Attack_Tribolt_SpawnProjectile);
                    }
                    break;

                case Attack_Tribolt_SpawnProjectile:
                    entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (entity != NULL) {
                        CreateEntityFromEntity(E_ID_24, self, entity);
                        entity->zPriority = self->zPriority + 1;
                        entity->posY.i.hi += TriboltProjectileOffsetY;
                    }
                    self->ext.salemWitch.timer = TriboltChargeDuration;
                    self->step_s++;
                    // fallthrough
                case Attack_Tribolt_Wait:
                    if (!--self->ext.salemWitch.timer) {
                        self->step_s++;
                    }
                    break;

                case Attack_Tribolt_Reset:
                    if (!AnimateEntity(AnimFrames_TriboltReset, self)) {
                        SetStep(Idle);
                    }
                    break;
            }
            break;

        case Hurt:
            switch (self->step_s) {
                case Hurt_Init:
                    // Knockback
                    if (self->facingLeft) {
                        self->velocityX = KnockbackSpeed;
                    } else {
                        self->velocityX = -KnockbackSpeed;
                    }
                    self->velocityY = 0;

                    self->ext.salemWitch.timer = HurtDuration;
                    self->animCurFrame = AnimFrameHurt;
                    PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_HURT);
                    self->step_s++;
                    // fallthrough
                case Hurt_Wait:
                    MoveEntity();
                    SalemWitchTrySpawnShadow();

                    // Slow down movement
                    self->velocityX -= self->velocityX / DecelerateFast;
                    self->velocityY -= self->velocityY / DecelerateFast;
                    if (!--self->ext.salemWitch.timer) {
                        SetStep(Idle);
                    }
                    break;
            }
            break;

        case Death:
            switch (self->step_s) {
                case Death_Init:
                    // Death for the shadow too
                    entity = self + 1;
                    entity->step = Death;

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
                    PlaySfxWithPosArgs(NA_SE_EN_SALEM_WITCH_DEATH);
                    self->step_s++;
                    // fallthrough
                case Death_Wait:
                    MoveEntity();

                    // Slow down x movement
                    self->velocityX -= self->velocityX / DecelerateFast;
                    if (!--self->ext.salemWitch.timer) {
                        self->step_s++;
                    }
                    break;

                case Death_Explode:
                    PlaySfxWithPosArgs(NA_SE_FIRE_BURST);

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

        case Shadow_Init:
            InitializeEntity(&EntityInit_80180688);
            self->flags |= 0x2000;
            self->hitboxState = 0;
            self->animCurFrame = self->params;
            self->drawMode = DRAW_TPAGE | DRAW_TPAGE2;
            self->drawFlags = FLAG_DRAW_UNK8;
            self->unk6C = ShadowDuration;
            // fallthrough
        case Shadow_Wait:
            self->unk6C -= ShadowTickSpeed;
            if (self->unk6C < ShadowDestroyThreshold) {
                DestroyEntity(self);
            }
            return;

        case Debug:
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
u8 AnimFrames_Twinkle[] = {
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

u8 D_80181638[] = {
    0x01, 0x2D, 0x01, 0x2E, 0x01, 0x2F, 0x01, 0x30, 0x01, 0x31, 0x01, 0x32, 0x01, 0x33, 0x01, 0x34,
    0x01, 0x35, 0x01, 0x36, 0x01, 0x37, 0x01, 0x38, 0x01, 0x39, 0x01, 0x3A, 0x01, 0x3B, 0x01, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03, 0x02, 0x04, 0x02, 0x05, 0x02, 0x06,
    0x02, 0x07, 0x02, 0x08, 0x02, 0x09, 0x02, 0x0A, 0x02, 0x0B, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E,
    0x00, 0x00, 0x00, 0x00 
};

extern EntityInit EntityInit_80180694;
extern signed short* sprites_chi_4[];

// E_SALEM_WITCH_CURSE
// func_801A8EAC
// PSP:func_psp_09239AC8:Match
// PSP:https://decomp.me/scratch/AGNPO
void EntitySalemWitchCurse(Entity* self)
{
    Primitive* prim;    // s0
    s32 primIdx;        // s2
    s16* temp_v1_10;    // s1

    switch (self->step) {
        case 0:
            InitializeEntity(&EntityInit_80180694);
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            if (self->facingLeft) {
                self->velocityX = 0xFFFC0000 | 0x8000;
            } else {
                self->velocityX = 0x30000 | 0x8000;
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
                prim->clut = 0x2EB;
                prim->p3 = 0;
                prim->priority = self->zPriority + 1;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        case 1:
            MoveEntity();
            AnimateEntity(&D_80181638, self);
            
            prim = self->ext.prim;
            prim->x0 = prim->x2 = self->posX.i.hi - 8;
            prim->x1 = prim->x3 = self->posX.i.hi + 8;
            prim->y0 = prim->y1 = self->posY.i.hi - 8;
            prim->y2 = prim->y3 = self->posY.i.hi + 8;
            if (!prim->p2) {
                prim->p1 += 1;
                if (prim->p1 > 7) {
                    prim->p1 = 1;
                }
                temp_v1_10 = sprites_chi_4[prim->p1];
                temp_v1_10 += 0x8;
                if (self->facingLeft) {
                    prim->u2 = prim->u3 = *temp_v1_10++;
                    prim->v0 = prim->v2 = *temp_v1_10++ + 0x7F;
                    prim->u0 = prim->u1 = *temp_v1_10++;
                    prim->v1 = prim->v3 = *temp_v1_10++ + 0x7F;
                } else {
                    prim->u2 = prim->u3 = *temp_v1_10++;
                    prim->v1 = prim->v3 = *temp_v1_10++ + 0x7F;
                    prim->u0 = prim->u1 = *temp_v1_10++;
                    prim->v0 = prim->v2 = *temp_v1_10++ + 0x7F;
                }
                prim->p2 = 1;
            } else {
                prim->p2 -= 1;
            }
            prim->drawMode = DRAW_TRANSP | DRAW_UNK02 | DRAW_TPAGE | DRAW_TPAGE2;
            if (Random() & 1) {
                prim = self->ext.prim;
                prim = prim->next;
                prim = FindFirstUnkPrim(prim);
                if (prim != NULL) {
                    prim->p3 = 1;
                    prim->p1 = 8;
                    prim->p2 = 0;
                    prim->r0 = prim->g0
                        = prim->b0 = prim->r1
                        = prim->g1 = prim->b1
                        = prim->r2 = prim->g2
                        = prim->b2 = prim->r3
                        = prim->g3 = prim->b3
                        = 0x60;
                    prim->x0 = prim->x2 = self->posX.i.hi - 8;
                    prim->x1 = prim->x3 = self->posX.i.hi + 8;
                    prim->y0 = prim->y1 = self->posY.i.hi - 8;
                    prim->y2 = prim->y3 = self->posY.i.hi + 8;
                }
            }
            prim = self->ext.prim;
            prim = prim->next;
            while (prim != NULL) {
                if (prim->p3) {
                    prim->r0 -= 4;
                    if (!prim->r0) {
                        prim->p3 = 0;
                        prim->drawMode = 8;
                        prim = prim->next;
                        continue;
                    }
                    
                    prim->g0 = prim->b0 = prim->r0;
                    prim->r1 = prim->g1
                        = prim->b1 = prim->r2
                        = prim->g2 = prim->b2
                        = prim->r3 = prim->g3
                        = prim->b3 = prim->r0;
                    if (!prim->p2) {
                        prim->x0 = --prim->x2;
                        prim->x1 = ++prim->x3;
                        prim->y0 = --prim->y1;
                        prim->y2 = ++prim->y3;
                        prim->p1++;
                        if (prim->p1 > 0xE) {
                            prim->p3 = 0;
                            prim->drawMode = 8;
                            prim = prim->next;
                            continue;
                        }
                        
                        temp_v1_10 = sprites_chi_4[prim->p1];
                        temp_v1_10 += 0x8;
                        if (self->facingLeft) {
                            prim->u2 = prim->u3 = *temp_v1_10++;
                            prim->v0 = prim->v2 = *temp_v1_10++ + 0x7F;
                            prim->u0 = prim->u1 = *temp_v1_10++;
                            prim->v1 = prim->v3 = *temp_v1_10++ + 0x7F;
                        } else {
                            prim->u2 = prim->u3 = *temp_v1_10++;
                            prim->v1 = prim->v3 = *temp_v1_10++ + 0x7F;
                            prim->u0 = prim->u1 = *temp_v1_10++;
                            prim->v0 = prim->v2 = *temp_v1_10++ + 0x7F;
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

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801A93D4);    // [Entity] Salem Witch Tribolt

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801A9588);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801A97C8);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801A9D40);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801A9E94);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AA020);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AA390);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AB0C0);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AB548);

// POSSIBLE FILE BREAK

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AB7CC);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AC074);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AC730);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801ACB6C);    // [Entity]

INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801ACEF4);    // [Entity]

s32 func_801AE70C(Primitive* prim, u8 arg1);
void StageNamePopupHelper(Primitive* prim)  // [Duplicate]
{
    u8 xPos;
    s32 i;
    s32 j;

    switch (prim->p3) {
    case 0:
        if (prim->p1 < 0x80) {
            if (--prim->p1 == 0) {
                prim->p3 = 1;
            }
        } else {
            if (++prim->p1 == 0) {
                prim->p3 = 2;
            }
        }

        if (prim->p3 != 0) {
            u8* dst = prim->p3 == 1 ? &prim->r1 : &prim->r0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    dst[j] = 0x50;
                }
                dst += 0x18;
            }
            prim->p2 = 0;
        }
        break;
    case 1:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 + xPos;
        prim->x1 = prim->x1 + xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    case 2:
        if (prim->p2 < 0x14) {
            prim->p2++;
        }
        xPos = prim->p2 / 5;
        prim->x2 = prim->x0 = prim->x0 - xPos;
        prim->x1 = prim->x1 - xPos;
        prim->x3 = prim->x0;
        func_801AE70C(prim, 4);
        break;
    }
}

// POSSIBLE FILE BREAK

//#ifndef NON_MATCHING
INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AD2BC);    // EntityStageNamePopup()
//#else
// /*?*/ void func_801AD0EC(?*);                                // extern
// extern u8 D_8003BE40;
// extern s8 D_8019B3C0;
// extern s8 D_8019B3D0;
// extern u16 EntityInit_80180640;

// void func_801AD2BC(Entity* arg0)
// {
//     Primitive* temp_s0;
//     Primitive* temp_s0_2;
//     Primitive* temp_s0_3;
//     Primitive* temp_s0_6;
//     Primitive* var_s0;
//     Primitive* var_s0_10;
//     Primitive* var_s0_11;
//     Primitive* var_s0_2;
//     Primitive* var_s0_3;
//     Primitive* var_s0_6;
//     Primitive* var_s0_7;
//     Primitive* var_s0_8;
//     Primitive* var_s0_9;
//     s16 temp_a0_2;
//     s16 temp_a0_3;
//     s16 temp_v0;
//     s16 temp_v0_10;
//     s16 temp_v0_12;
//     s16 temp_v0_17;
//     s16 temp_v0_18;
//     s16 temp_v0_19;
//     s16 temp_v0_4;
//     s16 temp_v0_5;
//     s16 temp_v0_6;
//     s16 temp_v0_7;
//     s16 temp_v0_8;
//     s16 temp_v1_2;
//     s16 temp_v1_3;
//     s16 var_v0_2;
//     s16 var_v1;
//     s16 var_v1_2;
//     s32 temp_s0_4;
//     s32 temp_s0_5;
//     s32 temp_v0_15;
//     s32 temp_v0_20;
//     s32 temp_v0_21;
//     s32 temp_v0_22;
//     s32 temp_v0_3;
//     s32 var_a0;
//     s32 var_s0_4;
//     s32 var_s0_5;
//     s32 var_s1;
//     s32 var_s1_10;
//     s32 var_s1_11;
//     s32 var_s1_12;
//     s32 var_s1_13;
//     s32 var_s1_3;
//     s32 var_s1_4;
//     s32 var_s1_5;
//     s32 var_s1_6;
//     s32 var_s1_7;
//     s32 var_s1_8;
//     s32 var_s1_9;
//     s32 var_v0;
//     u16 temp_a0;
//     u16 temp_v0_2;
//     u16 temp_v1;
//     u16 temp_v1_4;
//     u8 temp_a1;
//     u8 temp_a1_2;
//     u8 temp_a2;
//     u8 temp_v0_11;
//     u8 temp_v0_13;
//     u8 temp_v0_14;
//     u8 temp_v0_16;
//     u8 temp_v0_9;
//     u8 var_a1;
//     u8 var_a1_2;
//     u8 var_s1_2;

//     temp_a0 = arg0->step;
//     switch (temp_a0) {                              // switch 1; irregular
//         case 0:                                     // switch 1
//             if ((g_DemoMode == Demo_None) && (D_8003BE40 == 0)) {
//                 InitializeEntity(&EntityInit_80180640);
//                 temp_v0 = g_api_AllocPrimitives(PRIM_GT4, 0x57);
//                 if (temp_v0 != -1) {
//                     var_s0 = &g_PrimBuf[temp_v0];
//                     arg0->primIndex = (s32) temp_v0;
//                     arg0->ext.prim = var_s0;
//                     arg0->flags |= 0x800000;
//                     if (var_s0 != NULL) {
//                         do {
//                             var_s0->drawMode = 8;
//                             var_s0 = var_s0->next;
//                         } while (var_s0 != NULL);
//                     }
//                     var_s0_2 = arg0->ext.prim;
//                     var_s1 = 0;
//                     do {
//                         temp_v0_2 = 0xC0 - var_s1;
//                         var_s1 += 1;
//                         var_s0_2->tpage = 0x11;
//                         var_s0_2->clut = 0x19F;
//                         var_s0_2->u2 = 4;
//                         var_s0_2->u0 = 4;
//                         var_s0_2->u3 = 0x78;
//                         var_s0_2->u1 = 0x78;
//                         var_s0_2->v1 = 0;
//                         var_s0_2->v0 = 0;
//                         var_s0_2->v3 = 0x28;
//                         var_s0_2->v2 = 0x28;
//                         var_s0_2->x0 = 0xC;
//                         var_s0_2->x2 = 0xC;
//                         var_s0_2->y0 = 0x9D;
//                         var_s0_2->y1 = 0x9D;
//                         var_s0_2->x1 = 0x80;
//                         var_s0_2->x3 = 0x80;
//                         var_s0_2->y2 = 0xC5;
//                         var_s0_2->y3 = 0xC5;
//                         var_s0_2->priority = temp_v0_2;
//                         var_s0_2->drawMode = 8;
//                         temp_s0 = var_s0_2->next;
//                         temp_s0->tpage = 0x11;
//                         temp_s0->clut = 0x19F;
//                         temp_s0->u2 = 8;
//                         temp_s0->u0 = 8;
//                         temp_s0->u3 = 0x7C;
//                         temp_s0->u1 = 0x7C;
//                         temp_s0->v1 = 0x40;
//                         temp_s0->v0 = 0x40;
//                         temp_s0->v3 = 0x68;
//                         temp_s0->v2 = 0x68;
//                         temp_s0->x0 = 0x80;
//                         temp_s0->x2 = 0x80;
//                         temp_s0->y0 = 0x9D;
//                         temp_s0->priority = temp_v0_2;
//                         temp_s0->y1 = 0x9D;
//                         temp_s0->x1 = 0xF4;
//                         temp_s0->x3 = 0xF4;
//                         temp_s0->y2 = 0xC5;
//                         temp_s0->y3 = 0xC5;
//                         temp_s0->drawMode = 8;
//                         var_s0_2 = temp_s0->next;
//                     } while (var_s1 < 2);
//                     var_s1_2 = 0;
//                     arg0->ext.generic.unk88.unk = var_s0_2;
//                     var_s0_2->u2 = 4;
//                     var_s0_2->u0 = 4;
//                     var_s0_2->u3 = 0x78;
//                     var_s0_2->u1 = 0x78;
//                     var_s0_2->tpage = 0x11;
//                     var_s0_2->clut = 0x19D;
//                     var_s0_2->v1 = 0;
//                     var_s0_2->v0 = 0;
//                     var_s0_2->v3 = 0x28;
//                     var_s0_2->v2 = 0x28;
//                     var_s0_2->x0 = 0xC;
//                     var_s0_2->x2 = 0xC;
//                     var_s0_2->y0 = 0x9D;
//                     var_s0_2->y1 = 0x9D;
//                     var_s0_2->x1 = 0x80;
//                     var_s0_2->x3 = 0x80;
//                     var_s0_2->y2 = 0xC5;
//                     var_s0_2->y3 = 0xC5;
//                     var_s0_2->priority = 0xBF;
//                     var_s0_2->drawMode = 8;
//                     temp_s0_2 = var_s0_2->next;
//                     temp_s0_2->clut = 0x19D;
//                     temp_s0_2->tpage = 0x11;
//                     temp_s0_2->u2 = 8;
//                     temp_s0_2->u0 = 8;
//                     temp_s0_2->u3 = 0x7C;
//                     temp_s0_2->u1 = 0x7C;
//                     temp_s0_2->v1 = 0x40;
//                     temp_s0_2->v0 = 0x40;
//                     temp_s0_2->v3 = 0x68;
//                     temp_s0_2->v2 = 0x68;
//                     temp_s0_2->x0 = 0x80;
//                     temp_s0_2->x2 = 0x80;
//                     temp_s0_2->y0 = 0x9D;
//                     temp_s0_2->y1 = 0x9D;
//                     temp_s0_2->x1 = 0xF4;
//                     temp_s0_2->x3 = 0xF4;
//                     temp_s0_2->y2 = 0xC5;
//                     temp_s0_2->y3 = 0xC5;
//                     temp_s0_2->priority = 0xBF;
//                     temp_s0_2->drawMode = 8;
//                     temp_s0_3 = temp_s0_2->next;
//                     arg0->ext.generic.unk84.unk = temp_s0_3;
//                     temp_s0_3->u0 = 0;
//                     temp_s0_3->u1 = 0x40;
//                     temp_s0_3->type = 3;
//                     temp_s0_3->tpage = 0x1A;
//                     temp_s0_3->clut = 0x15F;
//                     temp_s0_3->v0 = 0xC0;
//                     temp_s0_3->v1 = 0xC0;
//                     temp_s0_3->v2 = 0xFF;
//                     temp_s0_3->v3 = 0xFF;
//                     temp_s0_3->y0 = 0x9B;
//                     temp_s0_3->y1 = 0x9B;
//                     temp_s0_3->y2 = 0xC7;
//                     temp_s0_3->y3 = 0xC7;
//                     temp_s0_3->x0 = 0xC;
//                     temp_s0_3->x2 = 0xC;
//                     temp_s0_3->x1 = 0xF4;
//                     temp_s0_3->x3 = 0xF4;
//                     temp_s0_3->r0 = 0x10;
//                     temp_s0_3->g0 = 0x28;
//                     temp_s0_3->u2 = temp_s0_3->u0;
//                     temp_s0_3->u3 = temp_s0_3->u1;
//                     temp_s0_3->b0 = 0;
//                     temp_s0_3->r2 = 8;
//                     temp_s0_3->g2 = 0;
//                     temp_s0_3->b2 = 0x38;
//                     temp_s0_3->priority = 0xB0;
//                     temp_s0_3->drawMode = 0x1D;
//                     temp_s0_3->unk10 = (s32) temp_s0_3->unk4;
//                     temp_s0_3->unk28 = (s32) temp_s0_3->unk1C;
//                     var_s0_3 = temp_s0_3->next;
//                     arg0->ext.factory.parent = var_s0_3;
//                     var_v1 = 0x9D;
//                     do {
//                         temp_a0_2 = var_s1_2 + 0x9E;
//                         temp_a1 = var_s1_2;
//                         var_s1_2 += 1;
//                         var_s0_3->v3 = var_s1_2;
//                         var_s0_3->v2 = var_s1_2;
//                         var_s0_3->y0 = var_v1;
//                         var_s0_3->y1 = var_v1;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         var_s0_3->y2 = temp_a0_2;
//                         var_s0_3->y3 = temp_a0_2;
//                         var_s0_3->v1 = temp_a1;
//                         var_s0_3->v0 = temp_a1;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->x0 = 0xC;
//                         var_s0_3->x2 = 0xC;
//                         var_s0_3->x1 = 0x80;
//                         var_s0_3->x3 = 0x80;
//                         var_s0_3->u0 = 4;
//                         var_s0_3->u2 = 4;
//                         var_s0_3->u3 = 0x78;
//                         var_s0_3->u1 = 0x78;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1 = var_s1_2 + 0x9D;
//                     } while ((s32) var_s1_2 < 0x28);
//                     var_s1_3 = 0;
//                     var_v1_2 = 0x9D;
//                     do {
//                         temp_a0_3 = var_s1_3 + 0x9E;
//                         temp_a1_2 = var_s1_3 + 0x40;
//                         var_s0_3->clut = 0x19F;
//                         var_s0_3->y0 = var_v1_2;
//                         var_s0_3->y1 = var_v1_2;
//                         var_s0_3->r0 = 0x78;
//                         var_s0_3->g0 = 0x78;
//                         var_s0_3->b0 = 0xA8;
//                         temp_a2 = var_s1_3 + 0x41;
//                         var_s0_3->y2 = temp_a0_3;
//                         var_s0_3->y3 = temp_a0_3;
//                         var_s1_3 += 1;
//                         var_s0_3->v1 = temp_a1_2;
//                         var_s0_3->v0 = temp_a1_2;
//                         var_s0_3->priority = 0xC0;
//                         var_s0_3->drawMode = 0xC;
//                         var_s0_3->tpage = 0x11;
//                         var_s0_3->x0 = 0x80;
//                         var_s0_3->x2 = 0x80;
//                         var_s0_3->x1 = 0xF4;
//                         var_s0_3->x3 = 0xF4;
//                         var_s0_3->u0 = 8;
//                         var_s0_3->u2 = 8;
//                         var_s0_3->u3 = 0x7C;
//                         var_s0_3->u1 = 0x7C;
//                         var_s0_3->v3 = temp_a2;
//                         var_s0_3->v2 = temp_a2;
//                         var_s0_3->unk10 = (s32) var_s0_3->unk4;
//                         var_s0_3->unk1C = (s32) var_s0_3->unk4;
//                         var_s0_3->unk28 = (s32) var_s0_3->unk4;
//                         var_s0_3 = var_s0_3->next;
//                         var_v1_2 = var_s1_3 + 0x9D;
//                     } while (var_s1_3 < 0x28);
//                     arg0->ext.generic.unk80.modeS32 = 0x20;
//                 case 1:                             // switch 1
//                     temp_v1 = arg0->step_s;
//                     switch (temp_v1) {
//                         case 0:
//                             temp_v0_3 = arg0->ext.generic.unk80.modeS32;
//                             if (temp_v0_3 != 0) {
//                                 arg0->ext.generic.unk80.modeS32 = temp_v0_3 - 1;
//                             } else {
//                                 temp_s0_4 = arg0->ext.generic.unk84.unk;
//                                 temp_s0_4->unk20 = 0x80;
//                                 temp_s0_4->unk8 = 0x80;
//                                 temp_s0_4->unk2C = 0x80;
//                                 temp_s0_4->unk14 = 0x80;
//                                 temp_s0_4->unk16 = 0xB1;
//                                 temp_s0_4->unkA = 0xB1;
//                                 temp_s0_4->unk2E = 0xB1;
//                                 temp_s0_4->unk22 = 0xB1;
//                                 temp_s0_4->unk32 = 0x15;
// block_78:
// block_79:
//                                 arg0->step_s += 1;
//                             }
//                             break;
//                         case 1:
//                             temp_s0_5 = arg0->ext.generic.unk84.unk;
//                             temp_v0_4 = temp_s0_5->unkA;
//                             var_a0 = 0;
//                             if (temp_v0_4 >= 0x9C) {
//                                 var_a0 = 1;
//                                 temp_v1_2 = temp_v0_4 - 4;
//                                 temp_s0_5->unkA = temp_v1_2;
//                                 temp_s0_5->unk16 = temp_v1_2;
//                                 temp_v0_5 = (u16) temp_s0_5->unk22 + 4;
//                                 temp_s0_5->unk22 = temp_v0_5;
//                                 temp_s0_5->unk2E = temp_v0_5;
//                             }
//                             temp_v0_6 = temp_s0_5->unk8;
//                             var_v0 = var_a0 & 0xFF;
//                             if (temp_v0_6 >= 0xD) {
//                                 temp_v1_3 = temp_v0_6 - 8;
//                                 temp_s0_5->unk8 = temp_v1_3;
//                                 temp_s0_5->unk20 = temp_v1_3;
//                                 temp_v0_7 = (u16) temp_s0_5->unk14 + 8;
//                                 temp_s0_5->unk14 = temp_v0_7;
//                                 temp_s0_5->unk2C = temp_v0_7;
//                                 var_v0 = (var_a0 | 1) & 0xFF;
//                             }
//                             if (var_v0 == 0) {
//                                 arg0->ext.generic.unk80.modeS32 = 0;
//                                 arg0->ext.factory.childId = 0;
//                                 arg0->ext.factory.unk92 = 0;
//                                 goto block_79;
//                             }
//                             break;
//                         case 2:
//                             temp_v0_8 = (u16) arg0->ext.factory.childId + 3;
//                             arg0->ext.factory.childId = temp_v0_8;
//                             var_s1_4 = 0;
//                             if (temp_v0_8 >= 0x80) {
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_4 = arg0->ext.generic.unk88.unk;
//                             var_s0_4->unk32 = 0x75;
// loop_34:
//                             temp_v0_9 = (u8) arg0->ext.stub[0x14];
//                             var_s1_4 += 1;
//                             var_s0_4->unk2A = temp_v0_9;
//                             var_s0_4->unk29 = temp_v0_9;
//                             var_s0_4->unk28 = temp_v0_9;
//                             var_s0_4->unk1E = temp_v0_9;
//                             var_s0_4->unk1D = temp_v0_9;
//                             var_s0_4->unk1C = temp_v0_9;
//                             var_s0_4->unk12 = temp_v0_9;
//                             var_s0_4->unk11 = temp_v0_9;
//                             var_s0_4->unk10 = temp_v0_9;
//                             var_s0_4->unk6 = temp_v0_9;
//                             var_s0_4->unk5 = temp_v0_9;
//                             var_s0_4->unk4 = temp_v0_9;
//                             var_s0_4 = var_s0_4->unk0;
//                             if (var_s1_4 < 2) {
//                                 var_s0_4->unk32 = 0x75;
//                                 goto loop_34;
//                             }
//                             break;
//                         case 3:
//                             temp_v0_10 = (u16) arg0->ext.factory.childId - 2;
//                             arg0->ext.factory.childId = temp_v0_10;
//                             var_s1_5 = 0;
//                             if (temp_v0_10 & 0x8000) {
//                                 arg0->ext.factory.childId = 0;
//                             }
//                             var_s0_5 = arg0->ext.generic.unk88.unk;
//                             do {
//                                 var_s0_5->unk32 = 0x35;
//                                 temp_v0_11 = (u8) arg0->ext.stub[0x14];
//                                 var_s1_5 += 1;
//                                 var_s0_5->unk2A = temp_v0_11;
//                                 var_s0_5->unk29 = temp_v0_11;
//                                 var_s0_5->unk28 = temp_v0_11;
//                                 var_s0_5->unk1E = temp_v0_11;
//                                 var_s0_5->unk1D = temp_v0_11;
//                                 var_s0_5->unk1C = temp_v0_11;
//                                 var_s0_5->unk12 = temp_v0_11;
//                                 var_s0_5->unk11 = temp_v0_11;
//                                 var_s0_5->unk10 = temp_v0_11;
//                                 var_s0_5->unk6 = temp_v0_11;
//                                 var_s0_5->unk5 = temp_v0_11;
//                                 var_s0_5->unk4 = temp_v0_11;
//                                 var_s0_5 = var_s0_5->unk0;
//                             } while (var_s1_5 < 2);
//                             temp_v0_12 = arg0->ext.factory.childId;
//                             if (temp_v0_12 != 0) {
//                                 var_v0_2 = 0x80 - temp_v0_12;
//                             } else {
//                                 var_v0_2 = (u16) arg0->ext.factory.unk92 + 4;
//                             }
//                             arg0->ext.factory.unk92 = var_v0_2;
//                             var_s1_6 = 0;
//                             if (arg0->ext.factory.unk92 >= 0x80) {
//                                 arg0->ext.factory.unk92 = 0x80;
//                                 arg0->step_s += 1;
//                             }
//                             var_s0_6 = arg0->ext.prim;
//                             do {
//                                 var_s0_6->drawMode = 0x35;
//                                 temp_v0_13 = (u8) arg0->ext.stub[0x16];
//                                 var_s1_6 += 1;
//                                 var_s0_6->b3 = temp_v0_13;
//                                 var_s0_6->g3 = temp_v0_13;
//                                 var_s0_6->r3 = temp_v0_13;
//                                 var_s0_6->b2 = temp_v0_13;
//                                 var_s0_6->g2 = temp_v0_13;
//                                 var_s0_6->r2 = temp_v0_13;
//                                 var_s0_6->b1 = temp_v0_13;
//                                 var_s0_6->g1 = temp_v0_13;
//                                 var_s0_6->r1 = temp_v0_13;
//                                 var_s0_6->b0 = temp_v0_13;
//                                 var_s0_6->g0 = temp_v0_13;
//                                 var_s0_6->r0 = temp_v0_13;
//                                 var_s0_6 = var_s0_6->next;
//                             } while (var_s1_6 < 2);
//                             var_s1_7 = 0;
//                             var_s0_6->drawMode = 0x15;
// loop_48:
//                             temp_v0_14 = (u8) arg0->ext.stub[0x16];
//                             var_s1_7 += 1;
//                             var_s0_6->b3 = temp_v0_14;
//                             var_s0_6->g3 = temp_v0_14;
//                             var_s0_6->r3 = temp_v0_14;
//                             var_s0_6->b2 = temp_v0_14;
//                             var_s0_6->g2 = temp_v0_14;
//                             var_s0_6->r2 = temp_v0_14;
//                             var_s0_6->b1 = temp_v0_14;
//                             var_s0_6->g1 = temp_v0_14;
//                             var_s0_6->r1 = temp_v0_14;
//                             var_s0_6->b0 = temp_v0_14;
//                             var_s0_6->g0 = temp_v0_14;
//                             var_s0_6->r0 = temp_v0_14;
//                             var_s0_6 = var_s0_6->next;
//                             if (var_s1_7 < 2) {
//                                 var_s0_6->drawMode = 0x15;
//                                 goto loop_48;
//                             }
//                             break;
//                         case 4:
//                             arg0->ext.generic.unk88.unk->unk32 = 8;
//                             arg0->ext.generic.unk80.modeS32 = 0x40;
//                             arg0->step = 2;
//                             arg0->step_s = 0;
//                             D_8003BE40 = 1;
//                             break;
//                     }
//                 default:                            // switch 1
// block_84:
//                     FntPrint(&D_8019B3C0, arg0->step);
//                     FntPrint(&D_8019B3D0, arg0->step_s);
//                     return;
//                 }
//             }
// block_83:
//             DestroyEntity(arg0);
//             return;
//         case 2:                                     // switch 1
//             temp_v0_15 = arg0->ext.generic.unk80.modeS32 - 1;
//             arg0->ext.generic.unk80.modeS32 = temp_v0_15;
//             if (temp_v0_15 == 0) {
//                 arg0->step_s = 0;
//                 arg0->step = 3;
//             }
//             goto block_84;
//         case 3:                                     // switch 1
//             temp_v1_4 = arg0->step_s;
//             if (temp_v1_4 != 1) {
//                 if ((s32) temp_v1_4 < 2) {
//                     var_s1_8 = 0;
//                     if (temp_v1_4 != 0) {

//                     } else {
//                         var_s0_7 = arg0->ext.prim->next->next;
//                         do {
//                             var_s0_7->drawMode = 0x15;
//                             temp_v0_16 = arg0->ext.stub[0x16];
//                             var_s1_8 += 1;
//                             var_s0_7->b3 = temp_v0_16;
//                             var_s0_7->g3 = temp_v0_16;
//                             var_s0_7->r3 = temp_v0_16;
//                             var_s0_7->b2 = temp_v0_16;
//                             var_s0_7->g2 = temp_v0_16;
//                             var_s0_7->r2 = temp_v0_16;
//                             var_s0_7->b1 = temp_v0_16;
//                             var_s0_7->g1 = temp_v0_16;
//                             var_s0_7->r1 = temp_v0_16;
//                             var_s0_7->b0 = temp_v0_16;
//                             var_s0_7->g0 = temp_v0_16;
//                             var_s0_7->r0 = temp_v0_16;
//                             var_s0_7 = var_s0_7->next;
//                         } while (var_s1_8 < 2);
//                         temp_v0_17 = (u16) arg0->ext.factory.unk92 - 4;
//                         arg0->ext.factory.unk92 = temp_v0_17;
//                         if (temp_v0_17 & 0x8000) {
//                             arg0->ext.factory.unk92 = 0;
//                             goto block_79;
//                         }
//                     }
//                     goto block_84;
//                 }
//                 if (temp_v1_4 != 2) {
//                     if (temp_v1_4 != temp_a0) {
//                         goto block_84;
//                     }
//                     var_s0_8 = arg0->ext.factory.parent;
//                     if (var_s0_8 != NULL) {
//                         do {
//                             func_801AD0EC((?* ) var_s0_8);
//                             var_s0_8 = var_s0_8->next;
//                         } while (var_s0_8 != NULL);
//                     }
//                     temp_s0_6 = arg0->ext.generic.unk84.unk;
//                     temp_v0_18 = (u16) temp_s0_6->y0 + 2;
//                     temp_s0_6->y0 = temp_v0_18;
//                     temp_s0_6->y1 = temp_v0_18;
//                     temp_s0_6->x0 = (u16) temp_s0_6->x0 - 2;
//                     temp_v0_19 = (u16) temp_s0_6->y2 - 2;
//                     temp_s0_6->y2 = temp_v0_19;
//                     temp_s0_6->y3 = temp_v0_19;
//                     temp_s0_6->x2 = (u16) temp_s0_6->x2 - 2;
//                     temp_s0_6->x1 = (u16) temp_s0_6->x1 + 2;
//                     temp_s0_6->x3 = (u16) temp_s0_6->x3 + 2;
//                     if (temp_s0_6->y2 < temp_s0_6->y0) {
//                         goto block_83;
//                     }
//                     goto block_84;
//                 }
//                 var_s0_9 = arg0->ext.factory.parent;
//                 if (var_s0_9 != NULL) {
//                     do {
//                         func_801AD0EC((?* ) var_s0_9);
//                         var_s0_9 = var_s0_9->next;
//                     } while (var_s0_9 != NULL);
//                 }
//                 temp_v0_20 = arg0->ext.generic.unk80.modeS32 - 1;
//                 arg0->ext.generic.unk80.modeS32 = temp_v0_20;
//                 if (temp_v0_20 == 0) {
//                     goto block_78;
//                 }
//                 goto block_84;
//             }
//             var_s0_10 = arg0->ext.prim;
//             var_s1_9 = 1;
//             do {
//                 var_s0_10->drawMode = 8;
//                 var_s0_10 = var_s0_10->next;
//                 var_s1_9 += 1;
//             } while (var_s1_9 < 4);
//             var_s0_11 = arg0->ext.factory.parent;
//             var_s1_10 = 0;
//             var_a1 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_10 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1 = var_s1_10 * 4;
//             } while (var_s1_10 < 0x14);
//             var_s1_11 = 0;
//             do {
//                 temp_v0_21 = 0x14 - var_s1_11;
//                 var_s1_11 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_21 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_11 < 0x14);
//             var_s1_12 = 0;
//             var_a1_2 = 0 * 4;
//             do {
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s1_12 += 1;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = var_a1_2;
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->p3 = 0;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11 = var_s0_11->next;
//                 var_a1_2 = var_s1_12 * 4;
//             } while (var_s1_12 < 0x14);
//             var_s1_13 = 0;
//             do {
//                 temp_v0_22 = 0x14 - var_s1_13;
//                 var_s1_13 += 1;
//                 var_s0_11->r0 = 0x80;
//                 var_s0_11->g0 = 0x80;
//                 var_s0_11->b0 = 0x80;
//                 var_s0_11->unk10 = (s32) var_s0_11->unk4;
//                 var_s0_11->unk1C = (s32) var_s0_11->unk4;
//                 var_s0_11->unk28 = (s32) var_s0_11->unk4;
//                 var_s0_11->p1 = (u8) -(temp_v0_22 * 4);
//                 var_s0_11->p2 = Random() & 3;
//                 var_s0_11->drawMode = 0x35;
//                 var_s0_11->p3 = 0;
//                 var_s0_11 = var_s0_11->next;
//             } while (var_s1_13 < 0x14);
//             arg0->ext.generic.unk80.modeS32 = 0x70;
//             goto block_79;
//     }
// }
// Warning: struct draculaPrimitive is not defined (only forward-declared)
//#endif
//#include "../e_stage_name.h"

//NOTE: The remaining functions are all contained in "../prim_helpers.h" but
//      UnkPrimHelper and PrimDecreaseBrightness don't match.
INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801ADF40);    // UnkPrimHelper()
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE328);    // UpdateAnimation()
s32 UpdateAnimation(u8* texAnimations, Primitive* prim) {
    s16 sp0;
    s16 tempUv;
    u8 new_var;
    u8* nextAnimation = texAnimations + ((prim->p1 * 5) & 0xFF);
    u8 new_var2;
    s32 retVal = 0;

    if (prim->p2 == 0) {
        if (*nextAnimation) {
            if (*nextAnimation == 0xFF) {
                return 0;
            }
            retVal = 0x80;
            prim->p2 = nextAnimation[0];
            ++nextAnimation;
            tempUv = nextAnimation[0] + (nextAnimation[1] << 8);
            nextAnimation += 2;
            sp0 = nextAnimation[0] + (nextAnimation[1] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + *((u8*)(&sp0));
            new_var = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var << 8);
            ++prim->p1;
        } else {
            prim->p1 = 0;
            prim->p2 = 0;
            prim->p2 = texAnimations[0];
            tempUv = texAnimations[1] + (texAnimations[2] << 8);
            sp0 = texAnimations[3] + (texAnimations[4] << 8);
            LOH(prim->u0) = tempUv;
            LOH(prim->u1) = tempUv + (*(u8*)&sp0);
            new_var2 = *((u8*)&sp0 + 1);
            LOH(prim->u3) = tempUv + sp0;
            LOH(prim->u2) = tempUv + (new_var2 << 8);
            ++prim->p1;
            return 0;
        }
    }

    retVal |= 1;
    --prim->p2;
    return (retVal | 1) & 0xFF;
}
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE478);    // FindFirstUnkPrim()
Primitive* FindFirstUnkPrim(Primitive* poly) {
    while (poly != NULL) {
        if (poly->p3 != 0) {
            poly = poly->next;
        } else {
            return poly;
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE4A8);    // FindFirstUnkPrim2()
Primitive* FindFirstUnkPrim2(Primitive* prim, u8 index) {

    Primitive* ret;
    int i;

    for (; prim; prim = prim->next) {
        if (!prim->p3) {
            ret = prim;
            for (i = 1; i < index; ++i) {
                prim = prim->next;
                if (!prim) {
                    return NULL;
                }
                if (prim->p3) {
                    break;
                }
            }
            if (i == index) {
                return ret;
            }
        }
    }
    return NULL;
}
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE524);    // PrimToggleVisibility()
Primitive* PrimToggleVisibility(Primitive* firstPrim, s32 count) {
    Primitive* prim;
    s8 isVisible;
    s32 i;

    if (firstPrim->p3) {
        firstPrim->p3 = 0;
    } else {
        firstPrim->p3 = 1;
    }

    prim = firstPrim;
    for (i = 0; i < count; i++) {
        if (prim->p3) {
            prim->drawMode &= ~DRAW_HIDE;
            isVisible = false;
        } else {
            prim->drawMode |= DRAW_HIDE;
            isVisible = true;
        }

        prim = prim->next;
        if (prim == NULL)
            return 0;
        prim->p3 = isVisible;
    }

    return prim;
}
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE5AC);    // PrimResetNext()
void PrimResetNext(Primitive* prim) {
    prim->p1 = 0;
    prim->p2 = 0;
    prim->p3 = 0;
    prim->next->x1 = 0;
    prim->next->y1 = 0;
    prim->next->y0 = 0;
    prim->next->x0 = 0;
    prim->next->clut = 0;
    LOHU(prim->next->u0) = 0;
    LOHU(prim->next->b1) = 0;
    LOHU(prim->next->r1) = 0;
    LOHU(prim->next->u1) = 0;
    prim->next->tpage = 0;
    LOHU(prim->next->r2) = 0;
    LOHU(prim->next->b2) = 0;
    prim->next->u2 = 0;
    prim->next->v2 = 0;
    prim->next->r3 = 0;
    prim->next->b3 = 0;
    prim->next->x2 = 0;
    prim->next->y2 = 0;
}
//TODO: Find first "init not started" prim?
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE68C);    // UnkPolyFunc2()
void UnkPolyFunc2(Primitive* prim) {
    PrimResetNext(prim);
    prim->p3 = 8;
    prim->next->p3 = 1;
    prim->next->type = PRIM_LINE_G2;
    prim->next->drawMode = 0xA;
}
//INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE6E0);    // UnkPolyFunc0()
void UnkPolyFunc0(Primitive* prim) {
    prim->p3 = 0;
    prim->drawMode = DRAW_HIDE;
    prim->next->p3 = 0;
    prim->next->type = PRIM_GT4;
    prim->next->drawMode = DRAW_HIDE;
}
INCLUDE_ASM("st/chi/nonmatchings/2813C", func_801AE70C);    // PrimDecreaseBrightness()
//#include "../prim_helpers.h"
