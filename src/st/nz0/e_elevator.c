// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"
#include "sfx.h"

static s32 elevator_target = 0;
static s16 elevator_target_pos[] = {0x0000, 0x0060, 0x0360, 0x0660};

void func_801B6DE4(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 hitFlags;
    s32 y;

    hitFlags = self->hitFlags;
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->ext.elevator.yPos = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->hitboxWidth = 6;
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.prim = prim;

        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 72;
        prim->v0 = 200;
        prim->u1 = 16;
        prim->v1 = 16;
        prim->priority = 0x5F;
        prim->drawMode = DRAW_UNK02;
    case 1:
        if (hitFlags) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (self->ext.elevator.yPos + 4 < y) {
                self->posY.i.hi =
                    self->ext.elevator.yPos + 4 - g_Tilemap.scrollY.i.hi;
                self->step++;
                PlaySfxPositional(SFX_SWITCH_CLICK);
                elevator_target = self->params;
            }
        }
        break;
    case 2:
        if (!hitFlags) {
            self->posY.val += 0xFFFF0000;
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (y < self->ext.elevator.yPos) {
                self->posY.i.hi =
                    self->ext.elevator.yPos - g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 8;
    prim->y0 = self->posY.i.hi - 8;
}

typedef enum ElevatorSubSteps {
    /* 0 */ ELEVATOR_INIT,
    /* 1 */ ELEVATOR_IDLE,
    /* 2 */ ELEVATOR_ASCEND,
    /* 3 */ ELEVATOR_DESCEND,
} ElevatorSubSteps;

void EntityElevator(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    s32 isPlayerTouching;
    Entity* player;
    s32 x, y;

    FntPrint("elevator:%x\n", elevator_target);
    if (!(g_Player.status &
          (PLAYER_STATUS_BAT_FORM | PLAYER_STATUS_MIST_FORM))) {
        isPlayerTouching = GetPlayerCollisionWith(self, 16, 5, 4);
    } else {
        isPlayerTouching = 0;
    }

    switch (self->step) {
    case ELEVATOR_INIT:
        InitializeEntity(g_EInitInteractable);
        self->hitboxOffX = 0;
        self->hitboxOffY = 68;
        self->hitboxWidth = 16;
        self->hitboxHeight = 5;
        self->hitboxState = 1;

        if (elevator_target) {
            y = elevator_target_pos[elevator_target];
            self->posY.i.hi = y - g_Tilemap.scrollY.i.hi;
        } else {
            elevator_target = self->params;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.elevator.prim = prim;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 8;
        prim->v0 = 0x80;
        prim->u1 = 0x20;
        prim->v1 = 0x48;
        prim->priority = 0x72;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        while (prim) {
            prim->type = PRIM_SPRT;
            prim->tpage = 0xF;
            prim->clut = 9;
            prim->u0 = 0;
            prim->v0 = 0x80;
            prim->u1 = 8;
            prim->v1 = 0x40;
            prim->priority = 0x5F;
            prim->drawMode = DRAW_UNK02;
            prim = prim->next;
        }
        self->ext.elevator.elevatorTarget = elevator_target;
    case ELEVATOR_IDLE:
        if (isPlayerTouching) {
            if (g_pads[0].pressed & PAD_UP) {
                elevator_target--;
                if (elevator_target < 1) {
                    elevator_target = 1;
                }
            }
            if (g_pads[0].pressed & PAD_DOWN) {
                elevator_target++;
                if (elevator_target > 3) {
                    elevator_target = 3;
                }
            }
        }

        if (elevator_target != self->ext.elevator.elevatorTarget) {
            y = elevator_target_pos[elevator_target] - g_Tilemap.scrollY.i.hi;
            if (y < self->posY.i.hi) {
                self->step = ELEVATOR_ASCEND;
                PlaySfxPositional(SFX_LOW_SYNTH_BUBBLES);
            } else {
                self->step = ELEVATOR_DESCEND;
                PlaySfxPositional(SFX_LOW_SYNTH_BUBBLES);
            }
        }
        self->ext.elevator.elevatorTarget = elevator_target;
        break;
    case ELEVATOR_ASCEND:
        self->posY.i.hi--;
        y = elevator_target_pos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (self->posY.i.hi < y) {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
        } else {
            if (isPlayerTouching) {
                g_api.func_8010DFF0(0, 1);
                player = &PLAYER;
                player->posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        }
        break;
    case ELEVATOR_DESCEND:
        self->posY.i.hi++;
        y = elevator_target_pos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (y < self->posY.i.hi) {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
            break;
        }
        if (isPlayerTouching) {
            g_api.func_8010DFF0(0, 1);
            player = &PLAYER;
            player->posY.i.hi++;
            D_80097488.y.i.hi++;
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi;

    prim = prim->next;
    x = self->posX.i.hi - 3;
    y = self->posY.i.hi - 56;
    while (prim != NULL) {
        prim->x0 = x;
        prim->y0 = y;
        prim = prim->next;
        y -= 0x40;
    }
}
