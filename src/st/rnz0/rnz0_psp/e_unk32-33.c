// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rnz0.h"

extern u8 D_pspeu_09258B10[];
extern u16 D_pspeu_092607D0;
extern Entity g_Entities_224;

void func_us_801C09E8(Entity* self) {
    Entity* other;
    s16 angle;
    s32 xVar;
    s32 yVar;
    s32 tempVar; // Used all over for various temp purposes
    s32 playerStatus;

    if ((self->hitFlags & 3) && (self->step < 0xA)) {
        SetStep(0xA);
    }
    if ((self->flags & FLAG_DEAD) && (self->step != 0xB)) {
        SetStep(0xB);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_pspeu_092607D0);
        SetStep(2);
        break;
    case 2:
        AnimateEntity(&D_pspeu_09258B10, self);
        if (GetDistanceToPlayerX() < 0x80) {
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[2] = 0xC0;
            self->step_s += 1;
        }
        AnimateEntity(&D_pspeu_09258B10, self);
        MoveEntity();
        tempVar = GetSideToPlayer() & 1;
        self->facingLeft = tempVar;
        other = &PLAYER;
        angle = self->ext.ILLEGAL.s16[7];
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
        self->ext.ILLEGAL.s16[7] += 8;
        tempVar = other->facingLeft;
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        if (tempVar != self->facingLeft) {
            playerStatus = g_Player.status;
            if (playerStatus & 0x400) {
                if ((abs(xVar) < 0x40) && (abs(yVar) < 0x20)) {
                    SetStep(8);
                }
            }
            if (playerStatus & 0x1800) {
                yVar += 12;
                if (yVar < 0x50U) {
                    SetStep(9);
                }
            }
        }

        if (!--self->ext.ILLEGAL.s16[2]) {
            if (self->facingLeft == tempVar) {
                SetStep(5);
            } else {
                SetStep(4);
            }
        }
        break;
    case 8:
    case 9:
        if (!self->step_s) {
            self->facingLeft = GetSideToPlayer() & 1;
            if (!self->facingLeft) {
                self->velocityX = FIX(-8);
            } else {
                self->velocityX = FIX(8);
            }
            if (self->step == 9) {
                self->velocityX = 0;
                self->velocityY = FIX(-4);
            }
            self->ext.ILLEGAL.s16[2] = 0x20;
            self->step_s += 1;
        }
        AnimateEntity(D_pspeu_09258B10, self);
        MoveEntity();
        self->velocityX -= self->velocityX >> 3;
        self->velocityY -= self->velocityY >> 4;
        if (!--self->ext.ILLEGAL.s16[2]) {
            SetStep(3);
            return;
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            yVar = other->posY.i.hi - 0x18 - self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) * 0x2C000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x2C000) >> 0xC;
            self->ext.ILLEGAL.s16[2] = 0x50;
            if (self->velocityX > 0) {
                self->facingLeft = 0;
            } else {
                self->facingLeft = 1;
            }
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&D_pspeu_09258B10, self);
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
            if (self->ext.ILLEGAL.s16[2]) {
                if ((xVar > 0x20) || (yVar > 0x20)) {
                    self->step_s += 1;
                    self->ext.ILLEGAL.s16[2] = 0x40;
                }
            } else {
                self->ext.ILLEGAL.s16[2]--;
            }
            if (yVar < 0) {
                yVar = -yVar;
            }
            if (xVar < 0) {
                xVar = -xVar;
            }
            if ((yVar < 6) && (xVar < 4)) {
                SetStep(6);
                return;
            }
            break;
        case 2:
            AnimateEntity(D_pspeu_09258B10, self);
            MoveEntity();
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (!--self->ext.ILLEGAL.s16[2]) {
                SetStep(3);
                return;
            }
            break;
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            xVar = other->posX.i.hi;
            yVar = (other->posY.i.hi - 0x50);
            xVar -= self->posX.i.hi;
            yVar -= self->posY.i.hi;
            angle = ratan2(yVar, xVar);
            self->velocityX = (rcos(angle) * 0x2C000) >> 0xC;
            self->velocityY = (rsin(angle) * 0x2C000) >> 0xC;
            self->ext.ILLEGAL.s16[2] = 0x200;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&D_pspeu_09258B10, self);
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (!self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0) {
                self->step_s += 1;
                return;
            }
            tempVar = --self->ext.ILLEGAL.s16[2];
            if (!(tempVar & 0xF)) {
                self->step_s -= 1;
            }
            if (tempVar == 0) {
                SetStep(3);
                return;
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
            AnimateEntity(&D_pspeu_09258B10, self);
            MoveEntity();
            other = &PLAYER;
            xVar = other->posX.i.hi - self->posX.i.hi;
            if (!self->facingLeft) {
                xVar = -xVar;
            }
            if (xVar > 0x40) {
                SetStep(5);
                return;
            }
            tempVar = --self->ext.ILLEGAL.s16[2];
            if (!(tempVar & 0xF)) {
                self->step_s -= 1;
            }
            if (tempVar == 0) {
                SetStep(3);
                return;
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            other = &PLAYER;
            if (!self->facingLeft) {
                self->ext.ILLEGAL.s16[8] = -8;
            } else {
                self->ext.ILLEGAL.s16[8] = 8;
            }
            if ((other->facingLeft) != (self->facingLeft)) {
                self->ext.ILLEGAL.s16[8] *= 2;
            }
            self->ext.ILLEGAL.s16[9] = -0x18U;
            if (g_Player.status &
                (PLAYER_STATUS_UNK80000000 | PLAYER_STATUS_AXEARMOR |
                 PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK400000 |
                 PLAYER_STATUS_DEAD | PLAYER_STATUS_STONE |
                 PLAYER_STATUS_UNK40 | PLAYER_STATUS_CROUCH |
                 PLAYER_STATUS_UNK10 | PLAYER_STATUS_WOLF_FORM |
                 PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
                SetStep(3);
            }
            self->hitboxState = 0;
            self->ext.ILLEGAL.s16[6] = 0x20;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&D_pspeu_09258B10, self);
            other = &PLAYER;
            self->posX.i.hi = other->posX.i.hi + self->ext.ILLEGAL.s16[8];
            self->posY.i.hi = other->posY.i.hi + self->ext.ILLEGAL.s16[9];
            if (!(g_Timer & 0xF)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromCurrentEntity(E_UNK_33, other);
                }
            }
            g_Player.demo_timer = 1;
            if (g_Timer & 1) {
                if (Random() & 1) {
                    g_Player.padSim = 0x8000;
                } else {
                    g_Player.padSim = 0x2000;
                }
            } else {
                g_Player.padSim = 0;
            }
            tempVar = g_pads[0].pressed & 0xF0;
            if (tempVar != self->ext.ILLEGAL.u32[2]) {
                if (!--self->ext.ILLEGAL.s16[6]) {
                    SetStep(7);
                }
            }
            self->ext.ILLEGAL.u32[2] = tempVar;
            if (g_Player.status &
                (PLAYER_STATUS_UNK80000000 | PLAYER_STATUS_AXEARMOR |
                 PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK400000 |
                 PLAYER_STATUS_DEAD | PLAYER_STATUS_STONE |
                 PLAYER_STATUS_UNK40 | PLAYER_STATUS_CROUCH |
                 PLAYER_STATUS_UNK10 | PLAYER_STATUS_WOLF_FORM |
                 PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
                SetStep(7);
                return;
            }
            break;
        }
        break;
    case 7:
    case 10:
        switch (self->step_s) {
        case 0:
            self->facingLeft = GetSideToPlayer() & 1;
            if (!self->facingLeft) {
                self->velocityX = FIX(-4);
            } else {
                self->velocityX = FIX(4);
            }
            self->velocityY = FIX(-2.5);
            self->ext.ILLEGAL.s16[2] = 0x30;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            if (self->ext.ILLEGAL.s16[2] < 0x28) {
                self->hitboxState = 3;
            }
            AnimateEntity(&D_pspeu_09258B10, self);
            MoveEntity();
            self->velocityX -= self->velocityX >> 3;
            self->velocityY -= self->velocityY >> 3;
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->step_s += 1;
                return;
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
            AnimateEntity(&D_pspeu_09258B10, self);
            MoveEntity();
            if (GetDistanceToPlayerX() > 0x60) {
                SetStep(3);
                return;
            }
            break;
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->drawFlags = ENTITY_ROTATE;
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.ILLEGAL.s16[2] = 0x30;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            AnimateEntity(&D_pspeu_09258B10, self);
            self->rotate += 0x40;
            MoveEntity();
            self->velocityY += FIX(0.03125);
            if (!--self->ext.ILLEGAL.s16[2]) {
                PlaySfxPositional(SFX_EXPLODE_E);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = EXPLOSION_FIREBALL;
                }
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}

extern u8 D_pspeu_09258B28[];
extern EInit D_pspeu_092607E0;
// The little smoke puff that shows up above and behind Alucard's head
void func_us_801C1668(Entity* self) {
    Entity* player;
    if (!self->step) {
        InitializeEntity(D_pspeu_092607E0);
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
    if (AnimateEntity(&D_pspeu_09258B28, self) == 0) {
        DestroyEntity(self);
    }
}
