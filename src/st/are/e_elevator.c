// SPDX-License-Identifier: AGPL-3.0-or-later
#include "are.h"

extern EInit D_us_80180AF8;

enum ElevatorPosition { TOP = 0, MIDDLE = 1, BOTTOM = 2 };

static s32 elevator_position = MIDDLE;
static s32 current_position = 385;
static s16 elevatorTiles[] = {
    0x0300, 0x0301, 0x0308, 0x031A, 0x031B, 0x031C, 0x0313, 0x0314,
    0x0303, 0x0304, 0x0305, 0x0315, 0x0316, 0x0317, 0x0318, 0x0319,
    0x003D, 0x003E, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046,
    0x003F, 0x0040, 0x0047, 0x0048, 0x0049, 0x004A, 0x004B, 0x004C};
static AnimateEntityFrame anim_elevator[] = {
    {.duration = 4, .pose = 0x10},
    {.duration = 4, .pose = 0x11},
    POSE_LOOP(0),
};

// Corresponds to each of the 3 elevator positions
static s16 target_positions[][3] = {{129, 385, 641}, {-129, 129, 385}};

void EntityElevator(Entity* self) {
    s32 playerCollision;
    s32 i;
    Primitive* prim;
    s16* tileLayoutPtr;
    s32 tileMapIndex;
    s32 targetPosition;
    s32 j;
    Entity* player;
    s32 posX;
    s32 primIndex;

    self->hitboxOffY = 0x22;
    playerCollision = GetPlayerCollisionWith(self, 0x30, 4, 4);
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AF8);
        self->animCurFrame = 0x10;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 0x20);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.areElevator.prim = prim;
        while (prim != NULL) {
            prim->type = PRIM_SPRT;
            prim->tpage = 0xE;
            prim->clut = 0xBD;
            prim->u0 = 0xE0;
            prim->v0 = 0x10;
            prim->u1 = 8;
            prim->v1 = 0x60;
            prim->priority = 0x69;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }

        tileLayoutPtr = elevatorTiles;
        if (!self->params) {
            tileMapIndex = 0x415;
        } else {
            tileMapIndex = 0x85;
            tileLayoutPtr += 8;
        }

        if (!g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            tileLayoutPtr += 0x10;
        }

        for (i = 0; i < 8; tileLayoutPtr++, i++) {
            (&g_Tilemap.fg[tileMapIndex])[i] = *tileLayoutPtr;
        }

        self->ext.areElevator.elevatorPosition = elevator_position;
        targetPosition = target_positions[self->params][elevator_position] -
                         g_Tilemap.scrollY.i.hi;
        if (!self->params) {
            self->posY.i.hi = current_position - g_Tilemap.scrollY.i.hi;
        } else {
            self->posY.i.hi = current_position - g_Tilemap.scrollY.i.hi - 0x100;
        }

        SetStep(1);
        if (targetPosition < self->posY.i.hi) {
            SetStep(3);
            if (!self->params) {
                self->posY.i.hi -= 0x18;
            }
        }

        if (self->posY.i.hi < targetPosition) {
            SetStep(4);
            if (self->params) {
                self->posY.i.hi += 0x17;
            }
        }

        if (!g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            self->step = 2;
        }
        break;
    case 1:
        if (playerCollision) {
            if (g_pads->pressed & PAD_UP) {
                elevator_position--;
                if (elevator_position < TOP) {
                    elevator_position = TOP;
                }
            }
            if (g_pads->pressed & PAD_DOWN) {
                elevator_position++;
                if (elevator_position > BOTTOM) {
                    elevator_position = BOTTOM;
                }
            }
        } else if (g_Player.vram_flag & TOUCHING_GROUND &&
                   GetDistanceToPlayerX() < 0x68) {
            if (!--self->ext.areElevator.unk80) {
                player = &PLAYER;
                targetPosition = player->posY.i.hi + g_Tilemap.scrollY.i.hi;
                if (self->params) {
                    targetPosition += 0x100;
                }
                elevator_position = targetPosition >> 8;
            }
        } else {
            self->ext.areElevator.unk80 = 0x60;
        }

        if (elevator_position != self->ext.areElevator.elevatorPosition) {
            targetPosition = target_positions[self->params][elevator_position] -
                             g_Tilemap.scrollY.i.hi;
            if (targetPosition < self->posY.i.hi) {
                SetStep(3);
            } else {
                SetStep(4);
            }
        }

        self->ext.areElevator.elevatorPosition = elevator_position;
        break;
    case 3:
        AnimateEntity(anim_elevator, self);
        self->posY.i.hi--;
        targetPosition = target_positions[self->params][elevator_position] -
                         g_Tilemap.scrollY.i.hi;
        if (self->posY.i.hi < targetPosition) {
            g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            self->posY.i.hi = targetPosition;
            SetStep(1);
        } else {
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }

            if (playerCollision) {
                g_api.func_8010DFF0(0, 1);
                player = &PLAYER;
                player->posY.i.hi--;
                D_80097488.y.i.hi--;
            }
        }
        break;
    case 4:
        AnimateEntity(anim_elevator, self);
        self->posY.i.hi++;
        targetPosition = target_positions[self->params][elevator_position] -
                         g_Tilemap.scrollY.i.hi;
        if (targetPosition < self->posY.i.hi) {
            g_api.PlaySfx(SFX_LEVER_METAL_BANG);
            self->posY.i.hi = targetPosition;
            SetStep(1);
        } else {
            if (!(g_Timer & 0xF)) {
                PlaySfxPositional(SFX_METAL_CLANG_A);
            }

            if (playerCollision) {
                g_api.func_8010DFF0(0, 1);
                player = &PLAYER;
                player->posY.i.hi++;
                D_80097488.y.i.hi++;
            }
        }
        break;
    case 2:
        if (g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            if (!self->params) {
                tileMapIndex = 0x415;
            } else {
                tileMapIndex = 0x45;
            }

            tileLayoutPtr = elevatorTiles;
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 8; tileLayoutPtr++, i++) {
                    (&g_Tilemap.fg[tileMapIndex])[i] = *tileLayoutPtr;
                }
                tileMapIndex += g_Tilemap.hSize * 0x10;
            }

            SetStep(1);
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    posX = self->posX.i.hi - 4;
    targetPosition = self->posY.i.hi - 0x8F;
    prim = self->ext.areElevator.prim;
    while (prim != NULL) {
        prim->x0 = posX;
        prim->y0 = targetPosition;
        prim->drawMode = DRAW_UNK02;
        prim = prim->next;
        targetPosition -= 0x60;
        if (targetPosition < -0x60) {
            break;
        }
    }

    while (prim != NULL) {
        prim->drawMode = DRAW_HIDE;
        prim = prim->next;
    }

    current_position = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    if (self->params) {
        current_position += 0x100;
    }
}

void EntityElevatorGates(Entity* self) {
    s32 posX;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AF8);
        self->animCurFrame = 0xF;
        self->zPriority = 0x69;
        if (self->params & 1) {
            self->facingLeft = 1;
        }

        if (self->params & 0x100) {
            self->drawFlags |= FLAG_DRAW_ROTATE;
            self->rotate = ROT(180);
        }

        // If the elevator switch is already pressed, we don't need the gates
        if (g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            DestroyEntity(self);
            return;
        }
        // Fallthrough
    case 1:
        if (g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            g_api.PlaySfx(SFX_STONE_MOVE_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.areElevator.unk80++;
        if (self->params & 1) {
            self->posX.val -= FIX(1.125);
        } else {
            self->posX.val += FIX(1.125);
        }

        if (self->ext.areElevator.unk80 & 1) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }

        // Once gates are fully opened, destroy them
        posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (posX < 0x29 || posX > 0xF7) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityElevatorSwitch(Entity* self) {
    s32 collision = GetPlayerCollisionWith(self, 8, 4, 4);
    s32 worldPos;
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180AF8);
        self->animCurFrame = 9;
        self->zPriority = 0x69;
        if (g_CastleFlags[ARE_ELEVATOR_ACTIVATED]) {
            self->posY.i.hi += 3;
            self->step = 2;
        }
        // Fallthrough
    case 1:
        if (collision != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            worldPos = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (worldPos > 0xA3) {
                self->posY.i.hi = 0xA3 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[ARE_ELEVATOR_ACTIVATED] = true;
                g_api.RevealSecretPassageAtPlayerPositionOnMap(0xB2);
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                self->step++;
            }
        }
        break;
    }
}
