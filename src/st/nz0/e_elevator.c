// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz0.h"

typedef enum ElevatorSubSteps {
    /* 0 */ ELEVATOR_INIT,
    /* 1 */ ELEVATOR_IDLE,
    /* 2 */ ELEVATOR_ASCEND,
    /* 3 */ ELEVATOR_DESCEND,
} ElevatorSubSteps;

void EntityElevator(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 player;
    s32 x, y;
    s32 temp;

    FntPrint("elevator:%x\n", g_ElevatorTarget);

    if (g_Player.unk0C & 3) {
        temp = 0;
    } else {
        temp = GetPlayerCollisionWith(self, 16, 5, 4);
    }

    //! FAKE:
    player = PLAYER_CHARACTER;

    switch (self->step) {
    case ELEVATOR_INIT:
        InitializeEntity(g_EInitGeneric);
        self->hitboxOffX = 0;
        self->hitboxOffY = 68;
        self->hitboxWidth = 16;
        self->hitboxHeight = 5;
        self->hitboxState = 1;

        if (g_ElevatorTarget != 0) {
            y = g_ElevatorTargetPos[g_ElevatorTarget];
            self->posY.i.hi = y - g_Tilemap.scrollY.i.hi;
        } else {
            g_ElevatorTarget = self->params;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 32);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.elevator.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 8;
        prim->v0 = 0x80;
        prim->u1 = 0x20;
        prim->v1 = 0x48;
        prim->priority = 0x72;
        prim->drawMode = 2;
        prim = prim->next;
        while (prim != NULL) {
            prim->type = PRIM_SPRT;
            prim->tpage = 0xF;
            prim->clut = 9;
            prim->u0 = 0;
            prim->v0 = 0x80;
            prim->u1 = 8;
            prim->v1 = 0x40;
            prim->priority = 0x5F;
            prim->drawMode = 2;
            prim = prim->next;
        }
        self->ext.elevator.elevatorTarget = g_ElevatorTarget;

    case ELEVATOR_IDLE:
        if (temp != 0) {
            if (g_pads[0].pressed & PAD_UP) {
                if (--g_ElevatorTarget < 1) {
                    g_ElevatorTarget = 1;
                }
            }
            if (g_pads[0].pressed & PAD_DOWN) {
                if (++g_ElevatorTarget > 3) {
                    g_ElevatorTarget = 3;
                }
            }
        }

        if (g_ElevatorTarget != self->ext.elevator.elevatorTarget) {
            y = g_ElevatorTargetPos[g_ElevatorTarget];
            y -= g_Tilemap.scrollY.i.hi;
            if (y >= self->posY.i.hi) {
                self->step = ELEVATOR_DESCEND;
            } else {
                self->step = ELEVATOR_ASCEND;
            }
            PlaySfxPositional(0x6E6);
        }
        self->ext.elevator.elevatorTarget = g_ElevatorTarget;
        break;

    case ELEVATOR_ASCEND:
        self->posY.i.hi--;
        y = g_ElevatorTargetPos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (self->posY.i.hi >= y) {
            if (temp != 0) {
                g_api.func_8010DFF0(0, 1);
                g_Entities[player].posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        } else {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
        }
        break;

    case ELEVATOR_DESCEND:
        self->posY.i.hi++;
        y = g_ElevatorTargetPos[self->ext.elevator.elevatorTarget] -
            g_Tilemap.scrollY.i.hi;
        if (y < self->posY.i.hi) {
            self->posY.i.hi = y;
            self->step = ELEVATOR_IDLE;
            break;
        }
        if (temp != 0) {
            g_api.func_8010DFF0(0, 1);
            g_Entities[player].posY.i.hi++;
            D_80097488.y.i.hi++;
        }
        break;
    }
    prim = self->ext.prim;
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi;

    prim = prim->next;
    x = self->posX.i.hi;
    y = self->posY.i.hi - 56;
    x -= 3;
    while (prim != NULL) {
        prim->x0 = x;
        prim->y0 = y;
        prim = prim->next;
        y -= 0x40;
    }
}
