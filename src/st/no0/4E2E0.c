// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no0.h"

static u8 anim_unk[] = {
    1, 1, 1,  2, 1,  3, 1,  4, 1,  5, 1,  6, 1,  7, 1,  8, 1,
    9, 1, 10, 1, 11, 1, 12, 1, 13, 1, 14, 1, 15, 1, 16, 0, 0};

// Does not appear in the entity list and appears to be unused
void func_us_801CE2E0(Entity* self) {
    s16 yOffsets[8] = {-2, -1, -1, 0, 0, 1, 1, 2};
    Entity* player;
    s32 collision;
    s16 offset;
    u16 flags;

    if (self->step != 0) {
        UnkAnimFunc(anim_unk, self, 5);
        self->rotate += 0x80;
        player = &PLAYER;
        if (self->ext.et_801CE2E0.unk88 & 0x40) {
            self->velocityY = FIX(-0.5);
        } else {
            self->velocityY = FIX(0.5);
        }

        self->velocityX = 0;
        self->ext.et_801CE2E0.unk88++;
        MoveEntity();
        if (self->ext.et_801CE2E0.unk7C & 0x4) {
            offset = (self->posY.i.hi + g_Tilemap.scrollY.i.hi) -
                     self->ext.et_801CE2E0.posY;
            if (offset > 0 ||
                (offset < 0 && (g_Player.vram_flag ^ TOUCHING_CEILING) & 2)) {
                player->posY.i.hi += offset;
            }
        }
        flags = 15;
        if (self->ext.et_801CE2E0.unk8A != 0) {
            self->ext.et_801CE2E0.unk8A--;
            flags = 11;
        }

        if (self->ext.et_801CE2E0.unk80 & 0xF &&
            (self->ext.et_801CE2E0.unk80 & 0xF0)) {
            flags |= 0x10;
        }

        collision = GetPlayerCollisionWith(self, 24, 8, flags);
        if (self->ext.et_801CE2E0.unk80 & 0xF) {
            if (self->ext.et_801CE2E0.unk80 & 0xF0) {
                offset = -yOffsets[(self->ext.et_801CE2E0.unk80 & 0xF) - 1];
            } else {
                offset = yOffsets[self->ext.et_801CE2E0.unk80 - 1];
            }
            self->posY.i.hi += offset;
            if (collision & 4) {
                player->posY.i.hi += offset;
            }
            self->ext.et_801CE2E0.unk80--;
        }

        if (collision & 4) {
            if (self->ext.et_801CE2E0.unk7C != 4 &&
                !(self->ext.et_801CE2E0.unk80 & 0xF) &&
                F(player->velocityY).i.hi > 0) {
                self->ext.et_801CE2E0.unk80 = 8;
            }
            offset = self->posX.i.hi + g_Tilemap.scrollX.i.hi -
                     self->ext.et_801CE2E0.posX;
            if ((offset > 0 && g_Player.vram_flag != TOUCHING_R_WALL) ||
                (offset < 0 && g_Player.vram_flag != TOUCHING_L_WALL)) {
                player->posX.i.hi += offset;
            }
        } else if (self->ext.et_801CE2E0.unk7C & 4) {
            self->ext.et_801CE2E0.unk8A = 8;
        }

        if ((collision & 0x2) && !(self->ext.et_801CE2E0.unk80 & 0xF)) {
            self->ext.et_801CE2E0.unk80 = 24;
        }
        self->ext.et_801CE2E0.unk7C = collision;
    } else {
        InitializeEntity(D_us_80180AAC);
        self->animCurFrame = 1;
        self->hitboxWidth = 24;
        self->hitboxHeight = 8;
        self->hitboxState = 2;
        self->ext.et_801CE2E0.unk88 = 0;
    }
    self->ext.et_801CE2E0.posX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.et_801CE2E0.posY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}
