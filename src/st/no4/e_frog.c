// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

extern u8 D_us_801826C0[];  // anim
extern s16 D_us_801826C8[]; // sensors_ground
extern Point32 D_us_801826D8[];

static s32 func_us_801D7FAC(s32 index) {
    Collider collider;
    s32 posX;
    s32 posY;

    switch (g_CurrentEntity->ext.frog.step) {
    case 0:
        if (!AnimateEntity(D_us_801826C0, g_CurrentEntity)) {
            g_CurrentEntity->velocityX = D_us_801826D8[index].x;
            if (!g_CurrentEntity->facingLeft) {
                g_CurrentEntity->velocityX = -g_CurrentEntity->velocityX;
            }
            g_CurrentEntity->velocityY = D_us_801826D8[index].y;
            g_CurrentEntity->ext.frog.step++;
            PlaySfxPositional(SFX_BLIPS_C);
            g_CurrentEntity->ext.frog.unk82 = 4;
        }
        break;
    case 1:
        posX = g_CurrentEntity->posX.i.hi;
        if (g_CurrentEntity->velocityX > 0) {
            posX += 0xC;
        }
        if (g_CurrentEntity->velocityX < 0) {
            posX -= 0xC;
        }
        posY = g_CurrentEntity->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->velocityX = 0;
        }
        if (UnkCollisionFunc3(D_us_801826C8) & 1) {
            g_CurrentEntity->poseTimer = 0;
            g_CurrentEntity->pose = 0;
            g_CurrentEntity->ext.frog.step = 2;
        }
        if (abs(g_CurrentEntity->velocityY) < FIX(2)) {
            g_CurrentEntity->animCurFrame = 0x1B;
        } else {
            g_CurrentEntity->animCurFrame = 0x1A;
        }
        if (g_CurrentEntity->ext.frog.unk82) {
            g_CurrentEntity->animCurFrame = 0x1B;
            g_CurrentEntity->ext.frog.unk82--;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_801826C0, g_CurrentEntity)) {
            return 1;
        }
        break;
    }

    return 0;
}

extern u8 D_us_80182688[];  // anim
extern u8 D_us_80182694[];  // anim
extern s16 D_us_801826C8[]; // sensors_ground
extern u8 D_us_801826F8[][2];

void EntityFrog(Entity* self) {
    Entity* entity;
    s32 index;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(0x71B);
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFrog);
        self->animCurFrame = 16;
        self->hitboxOffX = 1;
        self->hitboxOffY = 1;
        self->hitboxWidth = 8;
        self->hitboxHeight = 7;
        self->ext.frog.unk80 = 0x80;
        break;
    case 1:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (UnkCollisionFunc3(D_us_801826C8) & 1) {
            self->step++;
        }
        break;
    case 2:
        if (!AnimateEntity(&D_us_80182688, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            PlaySfxPositional(0x71B);
        }

        if (self->ext.frog.unk80) {
            self->ext.frog.unk80--;
        } else if (GetDistanceToPlayerX() < 0x40 &&
                   (GetSideToPlayer() & 1) ^ self->facingLeft) {
            SetStep(4);
        }

        if (!(Random() & 0x7F)) {
            SetStep(3);
        }

        break;
    case 4:
        if (!AnimateEntity(D_us_80182694, self)) {
            self->ext.frog.unk80 = 0x80;
            SetStep(2);
        }

        if (!self->poseTimer && self->pose == 9) {
            PlaySfxPositional(SFX_BOING);
        }

        switch (self->animCurFrame) {
        case 23:
            self->hitboxOffX = -0xF;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x14;
            self->hitboxHeight = 4;
            break;
        case 24:
            self->hitboxOffX = -0x15;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x1B;
            self->hitboxHeight = 4;
            break;
        case 25:
            self->hitboxOffX = -0x20;
            self->hitboxOffY = 0;
            self->hitboxWidth = 0x20;
            self->hitboxHeight = 4;
            break;
        default:
            self->hitboxOffX = 1;
            self->hitboxOffY = 1;
            self->hitboxWidth = 8;
            self->hitboxHeight = 7;
            break;
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            index = Random() & 3;
            self->ext.frog.step = 0;
            self->step_s = D_us_801826F8[index][0];
            self->ext.frog.unk85 = D_us_801826F8[index][1];
            break;
        case 1:
            if (func_us_801D7FAC(0) != 0) {
                self->ext.frog.step = 0;
                self->ext.frog.unk85++;
            }

            if (self->ext.frog.unk85 > 8) {
                SetStep(2);
            }
            break;
        case 2:
            if (func_us_801D7FAC(self->ext.frog.unk85) != 0) {
                self->ext.frog.step = 0;
                self->ext.frog.unk85++;
            }

            if (self->ext.frog.unk85 > 3) {
                SetStep(2);
            }
            break;
        case 3:
            if (func_us_801D7FAC(self->ext.frog.unk85) != 0) {
                self->ext.frog.step = 0;
                self->ext.frog.unk85--;
            }

            if (!self->ext.frog.unk85) {
                SetStep(2);
            }
            break;
        case 4:
            if (self->ext.frog.unk85 < 2) {
                index = 1;
            } else {
                index = 3;
            }

            if (func_us_801D7FAC(index) != 0) {
                self->ext.frog.step = 0;
                self->ext.frog.unk85++;
                if (self->ext.frog.unk85 > 2) {
                    SetStep(2);
                }
            }
            break;
        }
        break;
    }
}
