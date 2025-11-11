// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitElevator;

// This is similar to a small elevator in RTOP/TOP
void EntityElevator(Entity* self) {
    s16 posYOffsets[8] = {-2, -1, -1, 0, 0, 1, 1, 2};

    u8 isPlayerTouching;
    u16 flags;
    Entity* player;
    s16 posY;

    if (self->step) {
        player = &PLAYER;
        if (self->ext.topElevator.movingUp) {
            self->velocityY = FIX(-0.5);
        } else {
            self->velocityY = FIX(0.5);
        }
        if (self->ext.topElevator.mapPos.y > 0x148) {
            self->ext.topElevator.movingUp = true;
        }

        if (self->ext.topElevator.mapPos.y < 0x98) {
            self->ext.topElevator.movingUp = false;
        }

        if (!self->params) {
            self->velocityY = 0;
        }
        self->velocityX = 0;
        self->ext.topElevator.unk88++;
        MoveEntity();
        if (self->ext.topElevator.playerCollision & 4) {
            posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi -
                   self->ext.topElevator.mapPos.y;
            if (posY > 0 ||
                (posY < 0 && ((g_Player.vram_flag ^ TOUCHING_CEILING) &
                              TOUCHING_CEILING))) {
                player->posY.i.hi += posY;
                D_80097488.y.i.hi += posY;
            }
        }

        flags = 4;
        if (self->ext.topElevator.unk8A) {
            self->ext.topElevator.unk8A--;
            flags ^= 4;
        }

        if (self->ext.topElevator.unk80 & 0xF &&
            self->ext.topElevator.unk80 & 0xF0) {
            flags |= 0x10;
        }

        isPlayerTouching = GetPlayerCollisionWith(self, 16, 7, flags);
        if (self->ext.topElevator.unk80 & 0xF) {
            // Applies a small up/down jitter to the elevator
            // when the player lands on it
            if (self->ext.topElevator.unk80 & 0xF0) {
                posY = -posYOffsets[(self->ext.topElevator.unk80 & 0xF) - 1];
            } else {
                posY = posYOffsets[self->ext.topElevator.unk80 - 1];
            }
            self->posY.i.hi += posY;

            if (isPlayerTouching & 4) {
                player->posY.i.hi += posY;
                D_80097488.y.i.hi += posY;
            }
            self->ext.topElevator.unk80--;
        }

        if (isPlayerTouching & 4) {
            g_api.func_8010DFF0(0, 1);
            if (self->ext.topElevator.playerCollision ^ 4 &&
                !(self->ext.topElevator.unk80 & 0xF) &&
                F(player->velocityY).i.hi > 0) {
                self->ext.topElevator.unk80 = 8;
            }
        } else if (self->ext.topElevator.playerCollision & 4) {
            self->ext.topElevator.unk8A = 8;
        }

        if (isPlayerTouching & 2 && !(self->ext.topElevator.unk80 & 0xF)) {
            self->ext.topElevator.unk80 = 0x18;
        }
        self->ext.topElevator.playerCollision = isPlayerTouching;
    } else {
        InitializeEntity(g_EInitElevator);
        self->hitboxState = 1;
        self->ext.topElevator.unk88 = 0;
        self->ext.topElevator.movingUp = false;
    }
    self->ext.topElevator.mapPos.x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.topElevator.mapPos.y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}
