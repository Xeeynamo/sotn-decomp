// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"
#include "sfx.h"

extern EInit g_EInitElevator;
#ifdef VERSION_PSP
extern s32 E_ID(ELEVATOR_STATIONARY);
#endif

static u8 D_80180768[] = {
    0x08, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x04, 0x07, 0x04,
    0x08, 0x04, 0x09, 0x02, 0x0A, 0x01, 0x0B, 0x10, 0x0A, 0xFF, 0x00,
};

static u8 D_80180780[] = {
    0x04, 0x0A, 0x04, 0x09, 0x04, 0x08, 0x04, 0x07, 0x04, 0x06, 0x04,
    0x05, 0x04, 0x04, 0x04, 0x03, 0x02, 0x0C, 0x04, 0x03, 0xFF, 0x00,
};

// This is unused and stripped on PSP
// The equivalent function here is used on NO0 side but not in the CEN elevator
static s16 UnusedPrimFunction(Primitive* prim, s16 dx) {
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;
    prim->x0 = prim->x2 = dx;
    dx += 0x20;

    if (dx > 0xB0) {
        dx = dx - 0xB0;
        prim->u1 = prim->u3 = 0x22 - dx;
        prim->x1 = prim->x3 = 0xB0;
        dx = 0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = dx;
    }
    return dx;
}

static s16 func_801904B8(Primitive* prim, s16 dy) {
    prim->drawMode = DRAW_UNK02;
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->v2 = prim->v3 = 38;
    prim->y2 = prim->y3 = dy;
    dy -= 32;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = dy;
    return dy;
}

// Elevator when not moving (ID 1A)
void EntityElevatorStationary(Entity* self) {
    Primitive* prim;
    Entity* player = &PLAYER;
    Entity* entity;
    s32 primIndex;
    u8 playerIsTouching;
    s16 posX, posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;

        entity = self - 1;
        OVL_EXPORT(CreateEntityFromCurrentEntity)
        (E_ID(ELEVATOR_STATIONARY), entity);
        entity->params = 1;

        entity = self - 2;
        OVL_EXPORT(CreateEntityFromCurrentEntity)
        (E_ID(ELEVATOR_STATIONARY), entity);
        entity->params = 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cenElevator.prim = prim;
            prim->tpage = 0x12;
            prim->clut = 0x223;
            prim->u0 = prim->u2 = 0x28;
            prim->u1 = prim->u3 = 0x38;
            prim->v0 = prim->v1 = 0x28;
            prim->v2 = prim->v3 = 0x38;
            prim->priority = 0x6B;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;

            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->clut = 0x223;
                prim->priority = 0x6A;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        posY = player->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY < 80) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(3);
        }

        break;

    case 1:
        playerIsTouching = (self - 1)->ext.cenElevator.playerCollision;
        if (playerIsTouching) {
            posX = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_UP && abs(posX) < 8) {
#ifdef VERSION_PSP
                if (F(player->velocityX).i.hi != 0) {
                    break;
                }
#endif
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
                g_Player.demo_timer = 2;
                g_Player.padSim = PAD_NONE;
#ifdef VERSION_US
                PLAYER.velocityX = 0;
                PLAYER.velocityY = 0;
#endif
                self->step = 2;
            }
        }
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = PAD_NONE;
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (!(g_Timer & 15)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            if (posY == 0x74) {
                self->step_s++;
            }
            break;

        case 1:
            if (!AnimateEntity(D_80180780, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
                self->step_s = 0;
                self->step = 1;
            }

            if (!self->poseTimer && self->pose == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;

    case 2:
        g_Player.demo_timer = 2;
        g_Player.padSim = PAD_NONE;

        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_80180768, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            if (!self->poseTimer && self->pose == 4) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            // nb. this goes unused?
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (!(g_Timer & 15)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;

        case 2:
            if (!AnimateEntity(D_80180780, self)) {
                self->pose = 0;
                self->poseTimer = 0;
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
                self->step_s = 0;
                self->step = 1;
            }
            break;
        }
    }

    prim = self->ext.cenElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi - 0x1F;
    prim->y0 = prim->y1 = prim->y2 - 0x10;
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;

    posY = self->posY.i.hi - 40;
    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}

void EntityUnkId1B(Entity* self) {
    Entity* entity = self + self->params;
    u8 isTouchingPlayer;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        if (self->params & 16) {
            self->animCurFrame = self->params & 15;
            self->zPriority = 0x6A;
            self->step = 2;
            return;
        }
        self->animCurFrame = 0;
        break;

    case 1:
        self->posX.i.hi = entity->posX.i.hi;
        if (self->params == 1) {
            self->posY.i.hi = entity->posY.i.hi + 35;
            isTouchingPlayer = GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            isTouchingPlayer = GetPlayerCollisionWith(self, 12, 8, 6);
        }
        self->ext.cenElevator.playerCollision = isTouchingPlayer;
        break;
    }
}

// Elevator when moving, fixes player into position (ID 1C)
void EntityMovingElevator(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s32 primIndex;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex != -1) {
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;
            prim = &g_PrimBuf[primIndex];
            self->ext.cenElevator.prim = prim;
            while (prim != NULL) {
                prim->tpage = 0x12;
                prim->u0 = prim->u2 = 0x50;
                prim->u1 = prim->u3 = 0x60;
                prim->v0 = prim->v1 = 6;
                prim->v2 = prim->v3 = 0x26;
                prim->clut = 0x223;
                prim->priority = 0x6A;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }

        if (player->posY.i.hi > 192) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 0xA;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(2);
        } else {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 0xA;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(3);
        }
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = PAD_NONE;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;

    case 2:
        g_Player.demo_timer = 2;
        g_Player.padSim = PAD_NONE;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;
    }
    prim = self->ext.cenElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi - 0x1F;
    prim->y0 = prim->y1 = prim->y2 - 0x10;
    prim->drawMode = DRAW_UNK02;
    prim = prim->next;

    posY = self->posY.i.hi - 40;

    while (prim != NULL) {
        posY = func_801904B8(prim, posY);
        prim = prim->next;
        if (posY <= 0) {
            break;
        }
        prim = prim->next;
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    if (abs(self->posY.i.hi) > 384) {
        DestroyEntity(self);
    }
}
