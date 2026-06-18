// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cen.h"
#include "game.h"
#include "sfx.h"

static u8 D_80180768[] = {
    0x08, 0x03, 0x04, 0x04, 0x04, 0x05, 0x04, 0x06, 0x04, 0x07, 0x04,
    0x08, 0x04, 0x09, 0x02, 0x0A, 0x01, 0x0B, 0x10, 0x0A, 0xFF, 0x00,
};

static u8 D_80180780[] = {
    0x04, 0x0A, 0x04, 0x09, 0x04, 0x08, 0x04, 0x07, 0x04, 0x06, 0x04,
    0x05, 0x04, 0x04, 0x04, 0x03, 0x02, 0x0C, 0x04, 0x03, 0xFF, 0x00,
};

void EntityMaria(Entity* self) {
    if (self->step == 0) {
#if !defined(VERSION_HD)
        /* Has player seen Maria Holy Glasses Cutscene? */
        if (g_CastleFlags[MET_MARIA_IN_CEN] != 0) {
            DestroyEntity(self);
            return;
        }
#endif
        InitializeEntity(g_EInitSpawner);
        self->flags = FLAG_POS_CAMERA_LOCKED;
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 10;
        self->unk5A = 0x48;
        self->palette = 0x210;
        self->zPriority = 0x80;
    }
}

s16 func_8019040C(Primitive* prim, s16 arg1) {
    s16 ret = arg1;
    s16 temp_v0;

    prim->x2 = arg1;
    prim->x0 = arg1;
    ret += 0x20;
    prim->drawMode = DRAW_UNK02;
    prim->v0 = prim->v1 = 0x50;
    prim->v2 = prim->v3 = 0x60;
    prim->y0 = prim->y1 = 0x2C;
    prim->y2 = prim->y3 = 0x3C;
    prim->u0 = prim->u2 = 2;

    if (ret > 0xB0) {
        temp_v0 = 0xB2 - arg1;
        prim->u1 = prim->u3 = temp_v0;
        ret = 0;
        prim->x1 = prim->x3 = 0xB0;
    } else {
        prim->u1 = prim->u3 = 0x22;
        prim->x1 = prim->x3 = ret;
    }
    return ret;
}

s16 func_801904B8(Primitive* prim, s16 arg1) {
    prim->u0 = prim->u2 = 0x50;
    prim->u1 = prim->u3 = 0x60;
    prim->drawMode = DRAW_UNK02;
    prim->x0 = prim->x2 = g_CurrentEntity->posX.i.hi - 8;
    prim->x1 = prim->x3 = g_CurrentEntity->posX.i.hi + 8;
    prim->y2 = prim->y3 = arg1;
    arg1 -= 32;
    prim->v2 = prim->v3 = 38;
    prim->v0 = prim->v1 = 6;
    prim->y0 = prim->y1 = arg1;
    return arg1;
}

// Elevator when not moving (ID 1A)
void EntityElevatorStationary(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s16 posX, posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        CreateEntityFromCurrentEntity(E_ELEVATOR_STATIONARY, &self[-1]);
        (self - 1)->params = 1;
        CreateEntityFromCurrentEntity(E_ELEVATOR_STATIONARY, &self[-2]);
        (self - 2)->params = 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.cenElevator.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->tpage = 0x12;
        prim->clut = 0x223;
        temp = prim->v1 = prim->u0 = prim->u2 = 0x28;
        prim->v2 = prim->v3 = prim->u1 = prim->u3 = 0x38;
        prim->v0 = temp;
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

        if ((s16)(player->posY.i.hi + g_Tilemap.scrollY.i.hi) < 80) {
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
            self->animCurFrame = 10;
            g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
            SetStep(3);
        }
        break;

    case 1:
        if ((self - 1)->ext.cenElevator.unk80) {
            posX = self->posX.i.hi - player->posX.i.hi;
            if (g_pads[0].pressed & PAD_UP) {
                if (abs(posX) < 8) {
                    g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
                    g_Player.demo_timer = 2;
                    g_Player.padSim = 0;
#if !defined(VERSION_HD)
                    PLAYER.velocityX = 0;
                    PLAYER.velocityY = 0;
#endif
                    self->step = 2;
                }
            }
        }
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        switch (self->step_s) {
        case 0:
            self->posY.val += FIX(0.5);
            player->posY.i.hi++;
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            if (posY == 0x74) {
                self->step_s++;
            }
            break;

        case 1:
            if (AnimateEntity(D_80180780, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 0;
                self->step_s = 0;
                self->step = 1;
            }
            if (self->pose == 4 && self->poseTimer == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
        }
        break;

    case 2:
        g_Player.demo_timer = self->step;
        g_Player.padSim = 0;

        switch (self->step_s) {
        case 0:
            if (AnimateEntity(D_80180768, self) == 0) {
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            if (self->pose == 4 && self->poseTimer == 0) {
                g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            }
            break;

        case 1:
            self->posY.val -= FIX(0.5);
            if ((g_Timer % 16) == 0) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }
            break;

        case 2:
            if (AnimateEntity(D_80180780, self) == 0) {
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
    temp = self->posY.i.hi;
    prim->drawMode = DRAW_UNK02;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
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
    Entity* entity = &self[self->params];
    s32 step = self->step;

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
            self->ext.cenElevator.unk80 =
                GetPlayerCollisionWith(self, 12, 8, 4);
        } else {
            self->posY.i.hi = entity->posY.i.hi - 24;
            self->ext.cenElevator.unk80 =
                GetPlayerCollisionWith(self, 12, 8, 6);
        }
        break;
    }
}

// Elevator when moving, fixes player into position (ID 1C)
void EntityMovingElevator(Entity* self) {
    Entity* player = &PLAYER;
    Primitive* prim;
    s16 primIndex;
    s32 step;
    s16 posY;
    s16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitElevator);
        self->animCurFrame = 3;
        self->zPriority = player->zPriority + 2;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 12);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.cenElevator.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
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

        if (player->posY.i.hi > 192) {
            step = 2;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        } else {
            step = 3;
            self->posY.i.hi = player->posY.i.hi;
            player->posX.i.hi = self->posX.i.hi;
        }

        self->animCurFrame = 10;
        g_Entities[E_AFTERIMAGE_1].ext.afterImage.disableFlag = 1;
        SetStep(step);
        break;

    case 3:
        g_Player.demo_timer = 2;
        g_Player.padSim = 0;
        self->posY.val += FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;

    case 2:
        g_Player.demo_timer = self->step;
        g_Player.padSim = 0;
        self->posY.val -= FIX(0.5);
        player->posY.i.hi = self->posY.i.hi + 4;
        g_Player.vram_flag = VRAM_FLAG_UNK40 | TOUCHING_GROUND;
        break;
    }
    prim = self->ext.cenElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 8;
    prim->x1 = prim->x3 = self->posX.i.hi + 8;
    temp = self->posY.i.hi;
    prim->drawMode = DRAW_UNK02;
    prim->y2 = prim->y3 = temp - 0x1F;
    prim->y0 = prim->y1 = temp - 0x2F;
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
