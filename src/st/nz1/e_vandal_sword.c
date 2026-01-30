// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

typedef struct AlastorData {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
} AlastorData;

static AlastorData D_us_80182114[] = {
    {0xB8, 0xC0, 0x37, 0x3F, -0xB, -0xB},
    {0x80, 0xB8, 0x37, 0x47, -0x14, -0xE},
    {0xA8, 0x80, 0x37, 0x3F, -0x18, -0x10},
};

static s32 VandalSwordDrawAlastor(s32 arg0, s32 arg1) {
    AlastorData* temp_s1;
    Primitive* prim;
    s16 temp_v0;
    s16 temp_v0_11;
    s16 temp_v0_12;
    s16 temp_v0_13;
    s16 temp_v0_14;
    s16 temp_v0_15;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    u8 temp_s2;
    u8 temp_v0_10;
    u8 temp_v0_7;
    u8 temp_v0_8;
    u8 temp_v0_9;

    prim = g_CurrentEntity->ext.prim;
    temp_s1 = &D_us_80182114[arg0];
    if (g_CurrentEntity->facingLeft) {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - temp_s1->unk6;
        prim->x1 = prim->x3 = prim->x0 - temp_s1->unk2;
    } else {
        prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi + temp_s1->unk6;
        prim->x1 = prim->x3 = prim->x0 + temp_s1->unk2;
    }
    prim->y0 = prim->y1 = g_CurrentEntity->posY.i.hi + temp_s1->unk8;
    prim->y2 = prim->y3 = prim->y0 + temp_s1->unk4;

    if (!(g_Timer & 3)) {
        if (g_CurrentEntity->ext.ILLEGAL.u16[9] & 0x4000) {
            g_CurrentEntity->ext.ILLEGAL.u16[9]--;
            if ((g_CurrentEntity->ext.ILLEGAL.u16[9]) < 0x4000) {
                g_CurrentEntity->ext.ILLEGAL.u16[9] = 0;
            }
        } else {
            g_CurrentEntity->ext.ILLEGAL.u16[9]++;
            if ((g_CurrentEntity->ext.ILLEGAL.u16[9]) > 15) {
                g_CurrentEntity->ext.ILLEGAL.u16[9] = 0x400F;
            }
        }
    }

    switch (arg1) {
    case 0:
        prim->clut = 0x210;
        prim->u0 = prim->u2 = temp_s1->unk0;
        prim->u1 = prim->u3 = temp_s1->unk0 + temp_s1->unk2;
        prim->v0 = prim->v1 = temp_s1->unk1;
        prim->v2 = prim->v3 = temp_s1->unk1 + temp_s1->unk4;
        prim->priority = ((g_CurrentEntity->zPriority) + 1);
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        g_CurrentEntity->ext.ILLEGAL.u8[8] = 0x80;
        break;

    case 1:
        temp_s2 = ((g_CurrentEntity->ext.ILLEGAL.u8[8]) *
                       abs(rsin(g_CurrentEntity->ext.ILLEGAL.s16[3])) >>
                   0xC);
        prim->clut = ((g_CurrentEntity->ext.ILLEGAL.u16[9] & 0xF) + 0x210);
        prim->r0 = prim->g0 = prim->b0 = temp_s2;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode =
            DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        if ((g_CurrentEntity->ext.ILLEGAL.u8[8]) < 0x80) {
            g_CurrentEntity->ext.ILLEGAL.u8[8] += 0x10;
        }
        prim->y0 = prim->y1 +=
            FLT_TO_I(rsin(g_CurrentEntity->ext.ILLEGAL.s16[3]) * 4);
        if (g_CurrentEntity->facingLeft) {
            prim->x0 = prim->x2 +=
                FLT_TO_I(rcos(g_CurrentEntity->ext.ILLEGAL.s16[3]) * 2);
            prim->x1 = prim->x3 -=
                FLT_TO_I(rcos(g_CurrentEntity->ext.ILLEGAL.s16[3]) * 2);
        } else {
            prim->x0 = prim->x2 +=
                FLT_TO_I(rcos(g_CurrentEntity->ext.ILLEGAL.s16[3]) * 2);
            prim->x1 = prim->x3 -=
                FLT_TO_I(rcos(g_CurrentEntity->ext.ILLEGAL.s16[3]) * 2);
        }
        g_CurrentEntity->ext.ILLEGAL.s16[3] += 0x30;
        break;

    case 2:
        if (PrimDecreaseBrightness(prim, 7) == 0) {
            prim->drawMode = DRAW_HIDE;
            return 1;
        }
        break;
    }

    return 0;
}

static void VandalSwordTriggerDeath(void) {
    Entity* entity;

    if (!(g_Timer & 7)) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(
                E_VANDAL_SWORD_DEATH, g_CurrentEntity, entity);
            entity->rotate = g_CurrentEntity->rotate;
            entity->facingLeft = g_CurrentEntity->facingLeft;
        }
    }
}

static bool ApproachTarget(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}

extern EInit g_EInitVandalSword;

void EntityVandalSword(Entity* self) {
    Primitive* prim;
    Entity* entity;
    s32 primIndex;
    s32 negativeVelocity;
    s32 posX;
    s32 posY;
    s16 angle;

    if ((self->flags & FLAG_DEAD) && !self->ext.vandalSword.flag) {
        self->ext.vandalSword.flag = true;
        entity = self + 1;
        DestroyEntity(entity);
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        SetStep(8);
    } else if (self->hitFlags & 3 && self->step != 8) {
        SetStep(8);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitVandalSword);
        self->drawFlags = FLAG_DRAW_ROTATE;
        self->rotate = 0;
        self->hitboxState = 2;
        self->hitboxWidth = self->hitboxHeight = 0xE;
        self->hitPoints = 0x20;

        entity = self + 1;
        CreateEntityFromCurrentEntity(E_VANDAL_SWORD_HITBOX, entity);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;
        prim->tpage = 0x14;
        prim->clut = 0x210;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
        self->ext.vandalSword.prim = prim;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
        // fallthrough

    case 1:
        switch (self->step_s) {
        case 0:
            VandalSwordDrawAlastor(0, 0);
            self->ext.vandalSword.timer = 0x60;
            self->step_s++;
            // fallthrough

        case 1:
            VandalSwordDrawAlastor(0, 1);
            if (!--self->ext.vandalSword.timer) {
                self->step_s++;
            }
            break;
        case 2:
            if (self->facingLeft) {
                self->ext.vandalSword.angle = 0x800;
            } else {
                self->ext.vandalSword.angle = 0;
            }
            self->ext.vandalSword.timer2 = 0x40;
            if (VandalSwordDrawAlastor(0, 2)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            prim = self->ext.vandalSword.prim;
            entity = &PLAYER;
            prim->x0 = entity->posX.i.hi;
            prim->y0 = entity->posY.i.hi;
            angle = rand() & PSP_RANDMASK;
            prim->x0 += FLT_TO_I(rcos(angle) * 0x30);
            prim->y0 += FLT_TO_I(rcos(angle) * 0x30);
            self->ext.vandalSword.timer = 0x60;
            // fallthrough

        case 1:
            MoveEntity();
            VandalSwordTriggerDeath();
            prim = self->ext.vandalSword.prim;
            posX = prim->x0 - self->posX.i.hi;
            posY = prim->y0 - self->posY.i.hi;
            angle = ratan2(posY, posX);
            angle =
                GetNormalizedAngle(0x18, self->ext.vandalSword.angle, angle);
            self->velocityX = FLT_TO_I(rcos(angle) * FLT(0x18));
            self->velocityY = FLT_TO_I(rsin(angle) * FLT(0x18));
            self->ext.vandalSword.angle = angle;
            if (self->facingLeft) {
                angle = -angle;
            }
            ApproachTarget(&self->rotate, angle, 8);
            if (!--self->ext.vandalSword.timer) {
                self->step_s--;
            }
            break;
        }

        if (!--self->ext.vandalSword.timer2) {
            self->ext.vandalSword.timer2 = 0x60;
            SetStep(5);
        }
        break;

    case 5:
        switch (self->step_s) {
        case 0:
            entity = &PLAYER;
            posX = entity->posX.i.hi - self->posX.i.hi;
            posY = entity->posY.i.hi - self->posY.i.hi;
            self->ext.vandalSword.angle = ratan2(posY, posX);
            self->step_s++;
            break;

        case 1:
            angle = self->ext.vandalSword.angle;
            angle += 0x400;
            if (self->facingLeft) {
                angle = -angle;
            }
            if (ApproachTarget(&self->rotate, angle, 0x60)) {
                angle = self->ext.vandalSword.angle;
                self->velocityX = FLT_TO_I(rcos(angle) * FLT(0x50));
                self->velocityY = FLT_TO_I(rsin(angle) * FLT(0x50));
                self->step_s++;
            }
            break;

        case 2:
            if (self->velocityX > 0) {
                negativeVelocity = false;
            } else {
                negativeVelocity = true;
            }
            if (self->facingLeft != negativeVelocity) {
                self->facingLeft = negativeVelocity;
                self->rotate = -self->rotate;
            }
            VandalSwordDrawAlastor(1, 0);
            self->ext.vandalSword.timer = 0x30;
            self->step_s++;
            // fallthrough

        case 3:
            VandalSwordDrawAlastor(1, 1);
            if (!--self->ext.vandalSword.timer) {
                self->step_s++;
            }
            break;

        case 4:
            if (VandalSwordDrawAlastor(1, 2)) {
                self->ext.vandalSword.timer = 0x18;
                PlaySfxPositional(SFX_VANDAL_SWORD_ATTACK);
                self->step_s++;
            }
            break;

        case 5:
            VandalSwordTriggerDeath();
            MoveEntity();
            if (!--self->ext.vandalSword.timer) {
                SetStep(3);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            VandalSwordDrawAlastor(2, 0);
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(1.5);
            } else {
                self->velocityX = FIX(-1.5);
            }
            self->velocityY = FIX(-3.0);
            PlaySfxPositional(SFX_VANDAL_SWORD_PAIN);
            self->step_s++;
            // fallthrough

        case 1:
            VandalSwordDrawAlastor(2, 1);
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY += FIX(0.125);
            if (self->velocityY > FIX(2)) {
                self->step_s++;
            }
            break;
        case 2:
            if (VandalSwordDrawAlastor(2, 2)) {
                SetStep(3);
                if (self->flags & FLAG_DEAD) {
                    PlaySfxPositional(SFX_VANDAL_SWORD_DEATH);
                    SetStep(9);
                }
            }
            break;
        }
        break;
    case 9:
        MoveEntity();
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
        self->velocityY += FIX(0.125);
        if (g_Timer & 1) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
        }
        break;

    case 0xFF:
        // SPDX-License-Identifier: AGPL-3.0-or-later

        // Common code dropped into many Entity functions using a special case
        // in the self->step field. Allows using the Player 2 controller to move
        // the entity's frame one step forward or back. This code is impossible
        // to reach when playing the game, but can be triggered by poking the
        // proper location in RAM to trigger the entity's state machine.

#ifndef BUTTON_SYMBOL
#define BUTTON_SYMBOL PAD_CIRCLE
#endif

        /**
         * Debug: Press SQUARE / CIRCLE on the second controller
         * to advance/rewind current animation frame
         */
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (g_pads[1].pressed & BUTTON_SYMBOL) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;

        break;
    }
}

void EntityVandalSwordHitbox(Entity* self) {
    Entity* parent;
    s16 rotate;
    s32 posX;
    s32 posY;

    if (!self->step) {
        InitializeEntity(g_EInitVandalSword);
        self->animCurFrame = 0;
        self->hitboxState = 1;
        self->hitboxWidth = self->hitboxHeight = 6;
        self->flags |= FLAG_NOT_AN_ENEMY;
    }
    parent = self - 1;
    rotate = parent->rotate;
    if (parent->facingLeft) {
        rotate = -rotate;
    }
    posX = parent->posX.i.hi + FLT_TO_I(rsin(rotate) * 0x18);
    posY = parent->posY.i.hi - FLT_TO_I(rcos(rotate) * 0x18);
    self->posX.i.hi = posX;
    self->posY.i.hi = posY;
    if (parent->entityId != E_VANDAL_SWORD) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitVandSwordDeath;

void EntityVandalSwordDeath(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitVandSwordDeath);
        self->hitboxState = 0;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE;
        self->opacity = 0x80;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->palette++;
    }
    self->opacity -= 4;
    if (!(self->opacity & 7)) {
        self->palette++;
    }
    if (self->palette > 0x21E) {
        DestroyEntity(self);
    }
}
