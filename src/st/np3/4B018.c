// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"
#include "sfx.h"

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
        PlaySfxPositional(SFX_WING_FLAP_A);
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
            PlaySfxPositional(0x796);
            SetStep(9);
            KNIGHT->ext.owl.unk80 |= 8;
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B2C);
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
        if (otherEnt->hitParams) {
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
            self->ext.owl.unk84 = Ratan2Shifted(xVar, yVar);
            self->step_s++;
            break;
        case 1:
            HELPER->posX.i.hi = (xVar + self->posX.i.hi);
            HELPER->posY.i.hi = (yVar + self->posY.i.hi);
            // Might be able to change types on these two functions to
            // remove the s16 cast.
            self->ext.owl.unk84 = AdjustValueWithinThreshold(
                6, self->ext.owl.unk84,
                (s16)GetAngleBetweenEntitiesShifted(self, self + 3));
            SetEntityVelocityFromAngle(self->ext.owl.unk84, 0x20);
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
            SetEntityVelocityFromAngle(
                self->ext.owl.unk84, self->ext.owl.unk88);
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
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
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
                PlaySfxPositional(SFX_WEAPON_SWISH_C);
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
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
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
                4, self->ext.owl.unk84,
                (s16)GetAngleBetweenEntitiesShifted(self, self + 3));
            self->ext.owl.unk84 = angle;
            SetEntityVelocityFromAngle(angle, 0x10);
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
            PlaySfxPositional(SFX_WEAPON_SWISH_C);
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
                if (collider.effects & EFFECT_SOLID) {
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
                PlaySfxPositional(SFX_BONE_SWORD_SWISH_B);
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
            if (UnkCollisionFunc3(D_801826CC) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
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
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
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
        FntPrint("charal %x\n", self->animCurFrame);
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

static u8 func_801CBF18(void) {
    Primitive* prim;
    s32 primIndex;
    switch (g_CurrentEntity->step_s) {
    case 0:
        g_CurrentEntity->animCurFrame = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        // yes this has to be written this way
        if (primIndex != -1) {
            g_CurrentEntity->flags |= FLAG_HAS_PRIMS;
            g_CurrentEntity->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            g_CurrentEntity->ext.prim = prim;
            for (; prim != NULL; prim = prim->next) {
                prim->tpage = 0x12;
                prim->clut = D_80180B14[3] + 1;
                prim->u0 = 72;
                prim->u1 = 72 + 40;
                prim->u2 = 72;
                prim->u3 = 72 + 40;

                if (g_CurrentEntity->facingLeft) {
                    prim->x0 = g_CurrentEntity->posX.i.hi + 13;
                    prim->x1 = prim->x0 - 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                } else {
                    prim->x0 = g_CurrentEntity->posX.i.hi - 13;
                    prim->x1 = prim->x0 + 40;
                    prim->x2 = prim->x0;
                    prim->x3 = prim->x1;
                }
                prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
                prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
                prim->b0 = prim->b1 = prim->b2 = prim->b3 = 0x80;
                prim->priority = g_CurrentEntity->zPriority;
                prim->drawMode = DRAW_UNK_400 | DRAW_COLORS | DRAW_UNK02;
                prim->p2 = 0;
            }
            prim = g_CurrentEntity->ext.prim;
            prim->v0 = 0x80;
            prim->v1 = prim->v0;
            prim->v2 = prim->v0 + 10;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 0x10;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 10;
            prim->y3 = prim->y2;
            prim->p2 = 0;
            prim->drawMode |= DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;

            prim->v0 = 138;
            prim->v1 = prim->v0;
            prim->v2 = 138 + 38;
            prim->v3 = prim->v2;
            prim->y0 = g_CurrentEntity->posY.i.hi - 6;
            prim->y1 = prim->y0;
            prim->y2 = prim->y0 + 38;
            prim->y3 = prim->y2;
        } else {
            return 1;
        }
        g_CurrentEntity->step_s++;
        break;
    case 1:
        prim = g_CurrentEntity->ext.prim;
        prim->r0 = prim->g0 = prim->b0 = 32;
        LOW(prim->r1) = LOW(prim->r0);
        prim->r2 = prim->g2 = prim->b2 = 160;
        LOW(prim->r3) = LOW(prim->r2);
        g_CurrentEntity->step_s++;
        break;
    case 2:
        prim = g_CurrentEntity->ext.prim;
        if (g_Timer % 6 == 0) {
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (g_Timer % 4 == 0) {
            prim->v0++;
            prim->v1 = prim->v0;
            prim->v2++;
            prim->v3 = prim->v2;
            prim->y3++;
            prim->y2 = prim->y3;
            prim->p2++;
            prim = prim->next;
            prim->v0++;
            prim->v1 = prim->v0;
            prim->y0++;
            prim->y1 = prim->y0;
        }
        if (prim->p2 <= 38) {
            break;
        }
        g_CurrentEntity->step_s++;
        break;
    case 3:
        prim = g_CurrentEntity->ext.prim;
        if (PrimDecreaseBrightness(prim, 6) == 0) {
            return 1;
        }
    }
    return 0;
}

// Knight's Owl is in previous slot (see KNIGHT above)
#define OWL (self - 1)

void EntityOwlKnight(Entity* self) {
    Entity* explosion;
    s16 xVar;
    u8 miscTemp;
    s8* hitboxPtr;
    s16 xVar_2;
    s32 index;

    if (self->ext.owl.unk80 & 8) {
        if (!(self->flags & FLAG_DEAD)) {
            SetStep(13);
            self->ext.owl.unk80 ^= 8;
        }
    }
    if (self->flags & FLAG_DEAD) {
        if (self->step < 17) {
            DestroyEntity(self + 1);
            OWL->ext.owl.unk80 |= 0x20;
            self->hitboxState = 0;
            self->ext.owl.unk82 = 0x60;
            PlaySfxPositional(0x795);
            SetStep(17);
        }
    }
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180B14);
        CreateEntityFromEntity(E_801CD540, self, (self + 1));
        self->hitboxOffX = -1;
        self->zPriority -= 2;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        OWL->facingLeft = self->facingLeft;
        break;
    case 1:
        if (UnkCollisionFunc3(D_80182758) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_80182770, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        OWL->facingLeft = self->facingLeft;
        switch (self->step_s) {
        case 0:
            xVar = GetDistanceToPlayerX();
            if ((xVar < 0x68) && (GetDistanceToPlayerY() < 0x80)) {
                OWL->ext.owl.unk80 |= 1;
                self->step_s++;
            }
            break;
        case 1:
            if (self->ext.owl.unk80 & 2) {
                self->ext.owl.unk80 ^= 2;
                SetStep(3);
            }
        }
        break;
    case 3:
        if (AnimateEntity(D_80182778, self) == 0) {
            SetStep(12);
        }
        if ((self->step_s == 0) && (self->animFrameIdx == 4)) {
            xVar = OWL->posX.i.hi - PLAYER.posX.i.hi;
            if (xVar < 0) {
                xVar = -xVar;
            }
            if (xVar > 0x50) {
                OWL->ext.owl.unk80 |= 2;
            } else {
                OWL->ext.owl.unk80 |= 4;
            }
            PlaySfxPositional(0x792);
            self->step_s++;
        }
        break;
    case 12:
        xVar = GetDistanceToPlayerX();
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (xVar < 0x40) {
            SetStep(4);
        } else {
            SetStep(11);
        }
        break;
    case 4:
        if (self->step_s == 0) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
            self->step_s++;
        }
        if (AnimateEntity(D_801827C8, self) == 0) {
            xVar = GetDistanceToPlayerX();
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (xVar > 0x50) {
                SetStep(10);
            } else {
                SetStep(8);
            }
        }
        break;
    case 5:
        if (self->step_s == 0) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
            self->step_s++;
        }
        if (AnimateEntity(D_80182820, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            xVar = GetDistanceToPlayerX();
            if (xVar >= 0x91) {
                OWL->ext.owl.unk80 |= 8;
                SetStep(6);
            } else {
                if (self->ext.owl.unk80 & 2) {
                    self->ext.owl.unk80 ^= 2;
                    SetStep(3);
                } else {
                    SetStep(11);
                }
            }
        }
        break;
    case 6:
        AnimateEntity(D_80182788, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.owl.unk80 & 1) {
            self->ext.owl.unk80 ^= 1;
            SetStep(2);
        }
        break;
    case 8:
        if (self->step_s == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->velocityX = 0;
            self->step_s++;
        }
        if (AnimateEntity(D_80182800, self) == 0) {
            xVar = GetDistanceToPlayerX();
            if (xVar >= 0x49) {
                SetStep(5);
            } else {
                SetStep(10);
            }
            if (self->ext.owl.unk80 & 0x10) {
                SetStep(10);
            }
        }
        UnkCollisionFunc2(D_80182768);
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (self->animFrameDuration == 0 && self->animFrameIdx == 7) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(SFX_SCRAPE_B);
            self->velocityX = FIX(-3);
            if (self->ext.owl.unk80 & 0x10) {
                self->velocityX -= FIX(2); // now it's -5
            }
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 12, 32, 0, -4);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -12, 32, 0, 4);
            }
        }
        break;
    case 7:
        if (AnimateEntity(D_80182834, self) == 0) {
            SetStep(10);
        }
        UnkCollisionFunc2(D_80182768);
        self->velocityX -= self->velocityX / 8;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (self->animFrameDuration == 0 && self->animFrameIdx == 5) {
            PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            PlaySfxPositional(0x793);
            self->velocityX = FIX(-6.0);
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 16, 32, 0, -6);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -16, 32, 0, 6);
            }
        }
        break;
    case 10:
        if (self->step_s == 0) {
            self->ext.owl.unk82 = D_8018290C[Random() & 3];
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.owl.unk8C = 1;
            if (self->ext.owl.unk80 & 0x10) {
                self->ext.owl.unk8C = 0;
                self->ext.owl.unk82 /= 4;
            }
            self->step_s++;
        }
        if (self->ext.owl.unk8C != 0) {
            miscTemp = AnimateEntity(D_801827EC, self);
        } else {
            miscTemp = AnimateEntity(D_801827D8, self);
        }
        if (!miscTemp) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        UnkCollisionFunc2(D_80182768);
        if (self->facingLeft ^ self->ext.owl.unk8C) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (self->ext.owl.unk8C != 0) {
            self->velocityX -= self->velocityX / 16;
        }
        xVar = GetDistanceToPlayerX();
        if (xVar >= 0x81) {
            if (self->ext.owl.unk8C != 0) {
                self->animFrameIdx = 9 - self->animFrameIdx;
            }
            self->ext.owl.unk8C = 0;
        }
        if (--self->ext.owl.unk82 == 0) {
            xVar = GetDistanceToPlayerX();
            if (xVar >= 0x49) {
                SetStep(5);
            } else {
                SetStep(8);
            }
            if (self->ext.owl.unk80 & 0x10) {
                if (xVar >= 0x71) {
                    SetStep(10);
                } else if (xVar < 0x48) {
                    SetStep(7);
                } else {
                    SetStep(8);
                }
            }
        }
        break;
    case 11:
        if (self->step_s == 0) {
            self->ext.owl.unk82 = D_8018290C[Random() & 3];
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.owl.unk8C = 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_80182768);
        if (self->ext.owl.unk8C != 0) {
            miscTemp = AnimateEntity(D_801827A8, self);
        } else {
            miscTemp = AnimateEntity(D_80182794, self);
        }
        if (!miscTemp) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        if (self->facingLeft ^ self->ext.owl.unk8C) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (self->ext.owl.unk8C != 0) {
            self->velocityX -= self->velocityX / 16;
        }
        xVar = GetDistanceToPlayerX();
        miscTemp = self->ext.owl.unk8C;
        if (xVar >= 0x71) {
            miscTemp = 0;
        }
        if (xVar < 0x40) {
            miscTemp = 1;
        }
        if (self->ext.owl.unk8C != miscTemp) {
            self->animFrameIdx = 9 - self->animFrameIdx;
        }
        self->ext.owl.unk8C = miscTemp;
        if (--self->ext.owl.unk82 == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            if (xVar >= 0xA1) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                OWL->ext.owl.unk80 |= 8;
                SetStep(6);
            } else if (xVar < 0x40) {
                SetStep(15);
            } else {
                if (self->ext.owl.unk80 & 2) {
                    self->ext.owl.unk80 ^= 2;
                    SetStep(3);
                } else {
                    self->ext.owl.unk82 = 0x20;
                }
            }
        }
        break;
    case 15:
        if (AnimateEntity(D_80182860, self) == 0) {
            SetStep(10);
        }
        if (self->animFrameDuration == 0 && self->animFrameIdx == 5) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
        }
        UnkCollisionFunc2(D_80182768);
        self->velocityX -= self->velocityX / 16;
        if (abs(self->velocityX) < FIX(0.5)) {
            self->velocityX = 0;
        }
        if (self->animFrameDuration == 0 && self->animFrameIdx == 0xB) {
            PlaySfxPositional(0x793);
            self->velocityX = FIX(-3.0);
            if (self->facingLeft) {
                EntityGreyPuffSpawner(self, 5, 3, 12, 32, 0, -4);
                self->velocityX = -self->velocityX;
            } else {
                EntityGreyPuffSpawner(self, 5, 3, -12, 32, 0, 4);
            }
        }
        break;
    case 13:
        switch (self->step_s) { /* switch 2 */
        case 0:                 /* switch 2 */
            if (!(self->ext.owl.unk80 & 4)) {
                self->step_s++;
            } else if (AnimateEntity(D_80182820) == 0) {
                self->flags ^= 0x4;
                self->step_s++;
            }
            break;
        case 1:
            xVar = OWL->posX.i.hi - self->posX.i.hi;
            if (xVar < 0) {
                self->velocityX = FIX(-1.5);
                self->facingLeft = 0;
            } else {
                self->velocityX = FIX(1.5);
                self->facingLeft = 1;
            }
            self->ext.owl.unk82 = 0x200;
            self->step_s++;
            break;
        case 2: /* switch 2 */
            AnimateEntity(D_801827BC, self);
            miscTemp = UnkCollisionFunc2(D_80182768);
            if (miscTemp & 0x80) {
                self->ext.owl.unk82 = 1;
            }
            miscTemp = (GetSideToPlayer() & 1) ^ 1;
            if ((self->facingLeft == miscTemp) &&
                (GetDistanceToPlayerX() < 0x28)) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->velocityX = 0;
                self->step_s++;
            }
            self->ext.owl.unk82--;
            xVar_2 = OWL->posX.i.hi - self->posX.i.hi;
            if (xVar_2 < 0) {
                xVar_2 = -xVar_2;
            }
            if ((xVar_2 < 12) || (self->ext.owl.unk82 == 0)) {
                OWL->ext.owl.unk80 |= 0x10;
                self->ext.owl.unk82 = 0x100;
                SetSubStep(4);
            }
            break;
        case 3: /* switch 2 */
            if (AnimateEntity(D_8018284C, self) == 0) {
                self->animFrameIdx = 0;
                self->animFrameDuration = 0;
                self->step_s = 1;
            }
            UnkCollisionFunc2(D_80182768);
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.5)) {
                self->velocityX = 0;
            }
            if (self->animFrameDuration == 0 && self->animFrameIdx == 5) {
                self->velocityX = FIX(-6.0);
                if (self->facingLeft) {
                    self->velocityX = FIX(6.0);
                }
            }
            break;
        case 4: /* switch 2 */
            AnimateEntity(D_801828A0, self);
            if (self->animFrameDuration == 0 && self->animFrameIdx == 2) {
                PlaySfxPositional(0x794);
            }
            if (--self->ext.owl.unk82 == 0) {
                SetSubStep(5);
            }
            break;
        case 5: /* switch 2 */
            if (AnimateEntity(D_801828AC, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
                SetStep(16);
            }
            break;
        }
        break;
    case 14:
        (self + 1)->attack *= 2;
        if (AnimateEntity(D_80182834, self) == 0) {
            (self + 1)->attack /= 2;
            SetStep(10);
        }
        break;
    case 16:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80182794, self) == 0) {
                self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            }
            if (self->facingLeft == 0) {
                self->velocityX = FIX(-0.5);
            } else {
                self->velocityX = FIX(0.5);
            }
            UnkCollisionFunc2(D_80182768);
            xVar = GetDistanceToPlayerX();
            if (xVar < 0x50) {
                SetSubStep(1);
            }
            break;
        case 1:
            if (AnimateEntity(D_80182888, self) == 0) {
                SetStep(10);
            }
            UnkCollisionFunc2(D_80182768);
            self->velocityX -= self->velocityX / 8;
            if (abs(self->velocityX) < FIX(0.5)) {
                self->velocityX = 0;
            }
            if (self->animFrameDuration == 0 && self->animFrameIdx == 5) {
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
                PlaySfxPositional(0x793);
                self->velocityX = FIX(-8.0);
                if (self->facingLeft) {
                    EntityGreyPuffSpawner(self, 5, 3, 32, 32, 0, -6);
                    self->velocityX = -self->velocityX;
                } else {
                    EntityGreyPuffSpawner(self, 5, 3, -32, 32, 0, 6);
                }
            }
            break;
        }
        break;
    case 17:
        if (!(g_Timer & 7)) {
            PlaySfxPositional(SFX_EXPLODE_SMALL);
            explosion = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (explosion != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, explosion);
                explosion->posX.i.hi += (Random() & 0x1F) - 16;
                explosion->posY.i.hi += (Random() & 0x1F) - 16;
            }
        }
        AnimateEntity(D_801828A0, self);
        if (!--self->ext.owl.unk82) {
            PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_A);
            SetStep(18);
        }
        break;
    case 18:
        if (func_801CBF18()) {
            OWL->ext.owl.unk80 |= 0x40;
            DestroyEntity(self);
            return;
        }
        break;
    case 32:
        FntPrint("charal %x\n", self->animCurFrame);
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
    hitboxPtr = D_801828B8;
    index = D_801828C8[self->animCurFrame + 1] - 7;
    if (index < 0) {
        index = 0;
    }
    hitboxPtr += index * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}
