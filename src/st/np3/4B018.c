#include "np3.h"

// Owl's Owl Knight shows up one slot above it, so define this for
// ease of readability.
#define KNIGHT (self + 1)
// an unknown helper entity is also spawned.
#define HELPER (self + 3)
void EntityOwl(Entity* self) {
    Collider collider;
    Entity* otherEnt;
    s16 xVar;
    s16 yVar;
    s16 angle;

    if (1 < self->step && self->step < 9 && !(g_Timer & 0xF)) {
        func_801C2598(0x68C);
    }
    if (self->ext.owl.unk80 & 0x20) {
        if (!(self->flags & FLAG_DEAD)) {
            SetStep(8);
            self->ext.owl.unk80 ^= 0x20;
        }
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 9) {
            self->hitboxState = 0;
            self->animCurFrame = 12;
            self->velocityX = 0;
            self->velocityY = 0;
            func_801C2598(0x796);
            SetStep(9);
            KNIGHT->ext.owl.unk80 |= 8;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(&D_80180B2C);
        // Turns out the knight is spawned from the owl. Neat!
        CreateEntityFromEntity(E_OWL_KNIGHT, self, KNIGHT);
        CreateEntityFromEntity(E_801CD620, self, self + 3);
        break;
    case 1:
        AnimateEntity(D_801826EC, self);
        otherEnt = KNIGHT;
        self->posX.i.hi = KNIGHT->posX.i.hi;
        if (self->facingLeft) {
            self->posX.i.hi -= 10;
        } else {
            self->posX.i.hi += 10;
        }
        if (otherEnt->animCurFrame == 0x10) {
            self->posY.i.hi = otherEnt->posY.i.hi - 0x21;
        } else {
            self->posY.i.hi = otherEnt->posY.i.hi - 0x20;
        }
        if (otherEnt->unk44) {
            SetStep(2);
        }
        if (self->ext.owl.unk80 & 1) {
            self->ext.owl.unk80 ^= 1;
            SetStep(3);
        }
        break;
    case 2:
        if (AnimateEntity(D_801826F8, self) == 0) {
            SetStep(1);
            break;
        }
        break;
    case 3:
        if (AnimateEntity(D_80182720, self) == 0) {
            KNIGHT->ext.owl.unk80 |= 2;
            SetStep(4);
        }
        MoveEntity();
        if (self->animFrameIdx == 6) {
            self->velocityY -= FIX(12.0 / 128);
        }
        if (self->animFrameIdx >= 7) {
            self->velocityY += FIX(8.0 / 128);
        }
        break;
    case 4:
        MoveEntity();
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_80182734, self);
        xVar = KNIGHT->posX.i.hi - self->posX.i.hi;
        yVar = (KNIGHT->posY.i.hi - self->posY.i.hi);
        if (KNIGHT->facingLeft) {
            xVar -= 0x20;
        } else {
            xVar += 0x20;
        }
        yVar -= 0x40;
        switch (self->step_s) {
        case 0:
            xVar = self->velocityX / 16;
            yVar = self->velocityY / 16;
            self->ext.owl.unk84 = func_801BCE58(xVar, yVar);
            self->step_s++;
            break;
        case 1:
            HELPER->posX.i.hi = (xVar + self->posX.i.hi);
            HELPER->posY.i.hi = (yVar + self->posY.i.hi);
            // Might be able to change types on these two functions to
            // remove the s16 cast.
            self->ext.owl.unk84 = AdjustValueWithinThreshold(
                6, self->ext.owl.unk84, (s16)func_801BCE90(self, self + 3));
            func_801BCDEC(self->ext.owl.unk84, 0x20);
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            xVar = abs(xVar);
            yVar = abs(yVar);
            if ((xVar < 0x10) && (yVar < 0x10)) {
                self->ext.owl.unk88 = 0x20;
                self->step_s++;
            }
            break;
        case 2:
            xVar = abs(xVar);
            yVar = abs(yVar);
            func_801BCDEC(self->ext.owl.unk84, self->ext.owl.unk88);
            self->ext.owl.unk88--;
            if (self->ext.owl.unk88 < 0) {
                self->ext.owl.unk88 = 0;
            }
            if ((xVar >= 0x29) || (yVar >= 0x29)) {
                self->step_s--;
            }
            break;
        }
        if (self->ext.owl.unk80 & 8) {
            SetStep(6);
        }
        if (self->ext.owl.unk80 & 2) {
            SetStep(5);
            self->ext.owl.unk80 ^= 2;
        }
        if (self->ext.owl.unk80 & 4) {
            SetStep(7);
            self->ext.owl.unk80 ^= 4;
        }
        break;
    case 5:
        AnimateEntity(D_8018274C, self);
        MoveEntity();
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            xVar = PLAYER.posX.i.hi - self->posX.i.hi;
            yVar = PLAYER.posY.i.hi - self->posY.i.hi;
            yVar -= 0x10;
            angle = ratan2(-yVar, xVar);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = -rsin(angle) * 0x30;
            self->ext.owl.unk82 = 0x60;
            func_801C2598(0x60C);
            self->step_s++;
            break;
        case 1:
            if (self->ext.owl.unk82 < 0x30) {
                self->velocityY -= FIX(0.09375);
            }
            if (!--self->ext.owl.unk82) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->ext.owl.unk80 & 8) {
                SetStep(6);
            } else {
                KNIGHT->ext.owl.unk80 |= 2;
                SetStep(4);
            }
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80182734, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }
            MoveEntity();
            self->velocityY = FIX(-1.5);
            if (self->facingLeft) {
                self->velocityX = FIX(16.0 / 128);
            } else {
                self->velocityX = FIX(-16.0 / 128);
            }
            if (self->posY.i.hi < 0x30) {
                func_801C2598(0x60C);
                self->step_s++;
            }
            break;
        case 1:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            xVar = PLAYER.posX.i.hi - self->posX.i.hi;
            yVar = PLAYER.posY.i.hi - self->posY.i.hi;
            angle = ratan2(-yVar, xVar);
            self->velocityX = rcos(angle) << 6;
            self->velocityY = -rsin(angle) * 0x40;
            self->animCurFrame = 4;
            self->animFrameIdx = 0;
            self->animFrameDuration = 0;
            func_801C2598(0x60C);
            self->step_s++;
            break;
        case 2:
            MoveEntity();
            if (self->posY.i.hi > 0x90) {
                self->step_s++;
            }
            break;
        case 3:
            AnimateEntity(D_80182740, self);
            MoveEntity();
            self->velocityY -= FIX(28.0 / 128);
            if (self->velocityY < FIX(-2)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s++;
            }
            break;
        case 4:
            AnimateEntity(D_80182734, self);
            MoveEntity();
            if (self->posY.i.hi < 0x60) {
                if (self->ext.owl.unk80 & 8) {
                    SetStep(6);
                } else {
                    KNIGHT->ext.owl.unk80 |= 2;
                    SetStep(4);
                }
                if (self->ext.owl.unk80 & 0x40) {
                    SetStep(7);
                }
            }
            break;
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            yVar = KNIGHT->posY.i.hi - self->posY.i.hi - 0x40;
            xVar = KNIGHT->posX.i.hi - self->posX.i.hi;
            angle = ratan2(-yVar, xVar);
            self->velocityX = rcos(angle) * 0x28;
            self->velocityY = -rsin(angle) * 0x28;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            self->step_s++;
            break;
        case 1:
            AnimateEntity(D_8018274C, self);
            MoveEntity();
            xVar = KNIGHT->posX.i.hi - self->posX.i.hi;
            if (abs(xVar) < 8) {
                self->ext.owl.unk84 = 0x400;
                self->step_s++;
            }
            break;
        case 2:
            AnimateEntity(D_80182734, self);
            MoveEntity();
            if (KNIGHT->facingLeft) {
                HELPER->posX.i.hi = KNIGHT->posX.i.hi - 10;
            } else {
                HELPER->posX.i.hi = KNIGHT->posX.i.hi + 10;
            }
            HELPER->posY.i.hi = (KNIGHT->posY.i.hi - 0x20);
            // probably not an angle here but reusing variable.
            angle = AdjustValueWithinThreshold(
                4, self->ext.owl.unk84, (s16)func_801BCE90(self, self + 3));
            self->ext.owl.unk84 = angle;
            func_801BCDEC(angle, 0x10);
            xVar = HELPER->posX.i.hi - self->posX.i.hi;
            yVar = HELPER->posY.i.hi - self->posY.i.hi;
            if (xVar > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            xVar = abs(xVar);
            yVar = abs(yVar);
            if ((xVar < 6) && (yVar < 6)) {
                SetStep(1);
                self->velocityX = 0;
                self->velocityY = 0;
                self->ext.owl.unk80 = 0;
                KNIGHT->ext.owl.unk80 = 1;
                self->facingLeft = KNIGHT->facingLeft;
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            yVar = KNIGHT->posY.i.hi - self->posY.i.hi;
            xVar = KNIGHT->posX.i.hi - self->posX.i.hi;
            if (KNIGHT->facingLeft) {
                xVar += 0x20;
            } else {
                xVar -= 0x20;
            }
            yVar += 26;
            angle = ratan2(-yVar, xVar);
            self->velocityX = rcos(angle) * 0x30;
            self->velocityY = -rsin(angle) * 0x30;
            if (self->velocityX > 0) {
                self->facingLeft = 1;
            } else {
                self->facingLeft = 0;
            }
            func_801C2598(0x60C);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            AnimateEntity(D_80182734, self);
            yVar = KNIGHT->posY.i.hi - self->posY.i.hi;
            if (yVar < 0x41) {
                xVar = self->posX.i.hi;
                yVar = self->posY.i.hi + 0x10;
                g_api.CheckCollision(xVar, yVar, &collider, 0);
                if (collider.effects & 1) {
                    self->posY.i.hi = self->posY.i.hi + collider.unk18;
                    self->step_s++;
                    if (KNIGHT->posX.i.hi > self->posX.i.hi) {
                        self->facingLeft = 1;
                    } else {
                        self->facingLeft = 0;
                    }
                }
            }
            break;
        case 2:
            AnimateEntity(D_80182710, self);
            if ((g_Timer & 7) == 7) {
                func_801C2598(0x66D);
            }
            if (self->ext.owl.unk80 & 0x40) {
                SetStep(7);
                break;
            }
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (func_801BC8E4(D_801826CC) & 1) {
                func_801C2598(0x647);
                self->animCurFrame = 0xD;
                if (self->posX.i.hi > KNIGHT->posX.i.hi) {
                    self->facingLeft = 1;
                } else {
                    self->facingLeft = 0;
                }
                self->step_s++;
                break;
            }
            self->velocityY -= FIX(0.125);
            break;
        case 1:
            if (self->ext.generic.unk80.modeS32 & 0x50) {
                self->ext.owl.unk82 = 0x80;
                self->step++;
            }
            break;
        }
        break;
    case 10:
        if (!(--self->ext.owl.unk82) || (KNIGHT->entityId == 0)) {
            func_801C2598(0x683);
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, otherEnt);
                otherEnt->params = 2;
            }
            self->animCurFrame = 0;
            self->step = 24;
            KNIGHT->ext.owl.unk80 |= 0x10;
            DestroyEntity(self);
        }
        break;
    case 16:
        FntPrint(&D_801B20DC, self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params != 0) {
                break;
            }
            self->animCurFrame = self->animCurFrame + 1;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame = self->animCurFrame - 1;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

const s32 rodata_pad_32148 = 0;
