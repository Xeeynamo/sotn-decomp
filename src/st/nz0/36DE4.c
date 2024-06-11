#include "nz0.h"

void func_801B6DE4(Entity* self) {
    s32 temp_s1 = self->hitFlags;
    s16 primIndex;
    POLY_GT4* poly;
    s32 y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->ext.generic.unk80.modeS32 =
            self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        self->hitboxHeight = 8;
        self->hitboxOffY = -22;
        self->hitboxWidth = 6;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = poly;

        self->flags |= FLAG_HAS_PRIMS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            self->posY.val += FIX(1.0);
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if ((self->ext.generic.unk80.modeS32 + 4) < y) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0 -
                                        (g_Tilemap.scrollY.i.hi - 4));
                self->step++;
                func_801C29B0(NA_SE_EV_SWITCH_CLICK);
                g_ElevatorTarget = self->params;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->posY.val += 0xFFFF0000;
            y = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (y < self->ext.generic.unk80.modeS32) {
                self->posY.i.hi = (u16)(self->ext.generic.unk80.modeS16.unk0) -
                                  g_Tilemap.scrollY.i.hi;
                self->step = 1;
            }
        }
        break;
    }

    poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi;
    poly->y0 = poly->y0 - 8;
}

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
            func_801C29B0(0x6E6);
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
