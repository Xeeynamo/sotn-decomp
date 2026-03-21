// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern EInit D_us_80180AB0;
extern EInit D_us_80180ABC;
// Imp flapping wings
static u8 anim_imp[] = {
    4, 1, 4, 2, 4, 3, 4, 4, 4, 5, 4, 6, 4, 5, 4, 4, 4, 3, 4, 2, 4, 1, 0};
// Smoke puff from Alucard when jammed by imp
static u8 anim_smoke[] = {2,  7, 2,  8, 2,  9, 2,  10, 2,  11, 2,  12,  2,
                          13, 2, 14, 2, 15, 2, 16, 2,  17, 2,  18, 255, 0};

typedef enum{
    IMP_INIT,
    IMP_IDLE = 2,
    IMP_3,
    IMP_4,
    IMP_5,
    IMP_JAM_PLAYER,
    IMP_RETREAT_ESCAPE,
    IMP_8,
    IMP_9,
    IMP_RETREAT_HIT,
    IMP_DEAD
} ImpSteps;

void EntityImp(Entity* self) {
    Entity* other;
    s16 angle;
    s32 xVar;
    s32 yVar;/*  */
    s32 tempVar; // Used all over for various temp purposes
    s32 playerStatus;
    // List of statuses where, if you have one of them, imp can not jam you
    const u32 immuneStates =
        PLAYER_STATUS_UNK40000000 | PLAYER_STATUS_AXEARMOR |
        PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK400000 | PLAYER_STATUS_DEAD |
        PLAYER_STATUS_STONE | PLAYER_STATUS_UNK40 | PLAYER_STATUS_CROUCH |
        PLAYER_STATUS_UNK10 | PLAYER_STATUS_TRANSFORM;

    if ((self->hitFlags & 3) && (self->step < IMP_RETREAT_HIT)) {
        SetStep(IMP_RETREAT_HIT);
    }
    if ((self->flags & FLAG_DEAD) && (self->step != IMP_DEAD)) {
        SetStep(IMP_DEAD);
    }
    switch (self->step) {
    case IMP_INIT:
        InitializeEntity(D_us_80180AB0);
        SetStep(IMP_IDLE);
        break;
    case IMP_IDLE:
        AnimateEntity(anim_imp, self);
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(IMP_3);
        }
        break;
    case IMP_3:
        if (!self->step_s) {
            self->ext.imp.timer = 0xC0;
            self->step_s += 1;
        }
        AnimateEntity(anim_imp, self);
        MoveEntity();
        tempVar = GetSideToPlayer() & 1;
        self->facingLeft = tempVar;
        other = &PLAYER;
        angle = self->ext.imp.angle;
        xVar = (rcos(angle) * 0x50) >> 0xC;
        yVar = (rsin(angle) * 0x50) >> 0xC;
        if (yVar > 0) {
            yVar = -yVar;
        }

        xVar += other->posX.i.hi;
        yVar += other->posY.i.hi;
        xVar -= self->posX.i.hi;
        yVar -= self->posY.i.hi;

        angle = ratan2(yVar, xVar);
        self->velocityX = (rcos(angle) << 0x10) >> 0xC;
        self->velocityY = (rsin(angle) << 0x10) >> 0xC;
        self->ext.imp.angle += 8;
        tempVar = other->facingLeft;
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        if (tempVar != self->facingLeft) {
            playerStatus = g_Player.status;
            if (playerStatus & PLAYER_STATUS_UNK400) {
                if ((abs(xVar) < 0x40) && (abs(yVar) < 0x20)) {
                    SetStep(IMP_8);
                }
            }
            if (playerStatus & (PLAYER_STATUS_UNK1000 | PLAYER_STATUS_UNK800)) {
                yVar += 12;
                if (yVar < 0x50U) {
                    SetStep(IMP_9);
                }
            }
        }

        if (!--self->ext.imp.timer) {
            if (self->facingLeft == tempVar) {
                SetStep(IMP_5);
            } else {
                SetStep(IMP_4);
            }
        }
        break;
    case IMP_8:
    case IMP_9:
        if (!self->step_s) {
            self->facingLeft = GetSideToPlayer() & 1;
            if (!self->facingLeft) {
                self->velocityX = FIX(-8);
            } else {
                self->velocityX = FIX(8);
            }
            if (self->step == IMP_9) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
            }
            self->ext.imp.timer = 0x20;
            self->step_s += 1;
        }
        AnimateEntity(anim_imp, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 3;
        self->velocityY -= self->velocityY >> 4;
        if (!--self->ext.imp.timer) {
            SetStep(IMP_3);
        }
        break;
    case IMP_5:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - 0x18 - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) * 0x2C000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x2C000) >> 0xC;
            self->ext.imp.timer = 0x50;
            if (self->velocityX > 0) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&anim_imp, self);
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = (other->posY.i.hi - 0x18) - self->posY.i.hi;
            if (self->velocityX > 0) {
                xVar -= 4;
                xVar = -xVar;
            } else {
                xVar = xVar + 4;
            }
            if (self->velocityY > 0) {
                yVar = -yVar;
            }
            if (self->ext.imp.timer) {
                if ((xVar > 0x20) || (yVar > 0x20)) {
                    self->step_s += 1;
                    self->ext.imp.timer = 0x40;
                }
            } else {
                self->ext.imp.timer--;
            }
            if (yVar < 0) {
                yVar = -yVar;
            }
            if (xVar < 0) {
                xVar = -xVar;
            }
            if ((yVar < 6) && (xVar < 4)) {
                SetStep(IMP_JAM_PLAYER);
            }
            break;
        case 2:
            AnimateEntity(anim_imp, self);
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (!--self->ext.imp.timer) {
                SetStep(IMP_3);
            }
        }
        break;
    case IMP_4:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi;
            yVar = other->posY.i.hi - 0x50;
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) * 0x2C000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x2C000) >> 0xC;
            self->ext.imp.timer = 0x200;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&anim_imp, self);
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (!self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0) {
                self->step_s += 1;
            } else {
                tempVar = --self->ext.imp.timer;
                if (!(tempVar & 0xF)) {
                    self->step_s -= 1;
                }
                if (tempVar == 0) {
                    SetStep(IMP_3);
                }
            }
            break;
        case 2:
            other = &PLAYER;
            xVar = other->posX.i.hi;
            yVar = other->posY.i.hi - 0x18;
            if (!self->facingLeft) {
                xVar += 0x40;
            } else {
                xVar -= 0x40;
            }
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) * 0x2C000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x2C000) >> 0xC;
            self->step_s += 1;
            /* fallthrough */
        case 3:
            AnimateEntity(&anim_imp, self);
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (!self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0x40) {
                SetStep(IMP_5);
            } else {
                tempVar = --self->ext.imp.timer;
                if (!(tempVar & 0xF)) {
                    self->step_s -= 1;
                }
                if (tempVar == 0) {
                    SetStep(IMP_3);
                }
            }
        }
        break;
    // Player's controls are jammed, and they spam involuntary attacks. Must
    // mash directional buttons to escape.
    case IMP_JAM_PLAYER:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            if (!self->facingLeft) {
                self->ext.imp.jamOffsetX = -8;
            } else {
                self->ext.imp.jamOffsetX = 8;
            }
            if (other->facingLeft != self->facingLeft) {
                self->ext.imp.jamOffsetX <<= 1;
            }
            self->ext.imp.jamOffsetY = -24;
            if (g_Player.status & immuneStates) {
                SetStep(IMP_3);
            }
            self->hitboxState = 0;
            self->ext.imp.playerJamTimer = 0x20;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&anim_imp, self);
            other = &PLAYER;
            self->posX.i.hi = other->posX.i.hi + self->ext.imp.jamOffsetX;
            self->posY.i.hi = other->posY.i.hi + self->ext.imp.jamOffsetY;
            if (!(g_Timer & 0xF)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(E_IMP_SMOKE, other);
                }
            }
            g_Player.demo_timer = 1;
            if (g_Timer & 1) {
                if (Random() & 1) {
                    g_Player.padSim = PAD_SQUARE;
                } else {
                    g_Player.padSim = PAD_CIRCLE;
                }
            } else {
                g_Player.padSim = 0;
            }
            // Read what directions are currently pressed.
            tempVar = g_pads[0].pressed & PAD_DIRECTION_MASK;
            // If those are different than the previous, you can count down.
            if (tempVar != self->ext.imp.prevDirsPressed) {
                // And once the jam timer runs out, you're freed in step 7.
                if (!--self->ext.imp.playerJamTimer) {
                    SetStep(IMP_RETREAT_ESCAPE);
                }
            }
            // Log current pressed buttons for the next time around.
            self->ext.imp.prevDirsPressed = tempVar;
            if (g_Player.status & immuneStates) {
                SetStep(IMP_RETREAT_ESCAPE);
            }
        }
        break;
    // 2 different ways to get here, but they behave identical.
    case IMP_RETREAT_ESCAPE:
    case IMP_RETREAT_HIT:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (!self->facingLeft) {
                self->velocityX = FIX(-4);
            } else {
                self->velocityX = FIX(4);
            }
            self->velocityY = FIX(-2.5);
            self->ext.imp.timer = 0x30;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            if (self->ext.imp.timer < 0x28) {
                self->hitboxState = 3;
            }
            AnimateEntity(anim_imp, self);
            MoveEntity();
            self->velocityX -= self->velocityX >> 3;
            self->velocityY -= self->velocityY >> 3;
            if (!--self->ext.imp.timer) {
                self->step_s += 1;
            }
            break;
        case 2:
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
            if (!self->facingLeft) {
                self->velocityX = FIX(2.5);
            } else {
                self->velocityX = FIX(-2.5);
            }
            self->step_s += 1;
            /* fallthrough */
        case 3:
            AnimateEntity(anim_imp, self);
            MoveEntity();
            if (GetDistanceToPlayerX() > 0x60) {
                SetStep(IMP_3);
            }
        }
        break;
    case IMP_DEAD:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->drawFlags = ENTITY_ROTATE;
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.imp.timer = 0x30;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&anim_imp, self);
            self->rotate += 0x40;
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!--self->ext.imp.timer) {
                PlaySfxPositional(SFX_EXPLODE_E);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = EXPLOSION_FIREBALL;
                }
                DestroyEntity(self);
            }
        }
        break;
    }
}

// The little smoke puff that shows up above and behind Alucard's head
void EntityImpSmoke(Entity* self) {
    Entity* player;
    if (!self->step) {
        InitializeEntity(D_us_80180ABC);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter + 4;
        player = &PLAYER;
        self->posX.i.hi = player->posX.i.hi;
        self->posY.i.hi = player->posY.i.hi - 0x18;
        if (player->facingLeft) {
            self->posX.i.hi -= 6;
        } else {
            self->posX.i.hi += 6;
        }
        g_api.PlaySfx(SFX_BONE_THROW);
    }
    self->posY.val -= FIX(0.5);
    if (AnimateEntity(&anim_smoke, self) == 0) {
        DestroyEntity(self);
    }
}
