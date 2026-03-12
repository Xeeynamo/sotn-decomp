// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rnz0.h"

extern EInit g_EInitFloorTrap;

static u8 anim[] = {1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 0, 0};
// This could be anything (and might not be u16). Stripped on PSP.
static u16 unused[] = {0, 40, 8, 0};

// Sliding spikes on the floor throughout the second castle
void EntityFloorTrap(Entity* self) {
    Entity* other;
    s32 player_dY;
    s32 collision;
    s32 launchSpeed;
    s32 dX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFloorTrap);
        if (self->params & 0x100) {
            self->animCurFrame = 3;
            self->step = 8;
        } else {
            if (self->params) {
                self->animCurFrame = 2;
                self->zPriority -= 1;
                self->hitboxOffX = 5;
                self->hitboxOffY = 2;
            } else {
                self->animCurFrame = 1;
                self->hitboxOffX = -5;
                self->hitboxOffY = 2;
            }
            self->hitboxWidth = 6;
            self->hitboxHeight = 5;
            self->attackElement = ELEMENT_CUT | ELEMENT_UNK_10;
            self->attack = 15;
            self->hitboxState = 1;
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_FLOORTRAP, self, other);
                other->params = 0x100;
                other->ext.floorTrap.unkEnt = self;
                other->zPriority = self->zPriority + 1;
            }
        }
        break;
    case 1:
        self->ext.floorTrap.unk84 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (self->params) {
            other = self - 1;
        } else {
            other = self + 1;
        }
        if (other->entityId == E_FLOORTRAP) {
            dX = other->posX.i.hi + g_Tilemap.scrollX.i.hi;
            self->ext.floorTrap.unk86 = (self->ext.floorTrap.unk84 + dX) / 2;
            if (self->params) {
                self->ext.floorTrap.unk86 -= 12;
            } else {
                self->ext.floorTrap.unk86 += 12;
            }
            dX -= self->ext.floorTrap.unk84;
            self->ext.floorTrap.unk88 = abs(dX);
            self->step++;
        }
        break;
    case 2:
        other = &PLAYER;
        player_dY = self->posY.i.hi - other->posY.i.hi;
        if ((g_Player.vram_flag & TOUCHING_GROUND) && (abs(player_dY) < 0x21)) {
            dX = other->posX.i.hi - self->posX.i.hi;
            if (!self->params) {
                dX = -dX;
            }
            if ((dX < self->ext.floorTrap.unk88) && (dX > 0)) {
                SetStep(3);
            }
        }
        break;
    case 3:
        switch (self->step_s) {
        case 0:
            if (self->params) {
                self->velocityX = FIX(4);
            } else {
                self->velocityX = FIX(-4);
            }
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            dX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            dX = self->ext.floorTrap.unk86 - dX;
            if (!self->params) {
                dX = -dX;
            }
            if (dX < 0) {
                self->posX.i.hi =
                    self->ext.floorTrap.unk86 - g_Tilemap.scrollX.i.hi;
                self->ext.floorTrap.timer = 0x20;
                PlaySfxPositional(SFX_LEVER_METAL_BANG);
                self->step_s++;
            }
            break;
        case 2:
            self->velocityX = 0;
            if (!--self->ext.floorTrap.timer) {
                if (self->params) {
                    self->velocityX = FIX(-1);
                } else {
                    self->velocityX = FIX(1);
                }
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            dX = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
            dX = self->ext.floorTrap.unk84 - dX;
            if (self->params) {
                dX = -dX;
            }
            if (dX < 0) {
                self->posX.i.hi =
                    self->ext.floorTrap.unk84 - g_Tilemap.scrollX.i.hi;
                self->velocityX = 0;
                SetStep(2);
            }
            break;
        }
        break;
    case 8:
        other = self->ext.floorTrap.unkEnt;
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        if (other->velocityX != 0) {
            AnimateEntity(anim, self);
        }
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
    collision = GetPlayerCollisionWith(self, 7, 6, 4);
    if (!(self->params & 0x100) && (collision & 4)) {
        // Launch the player proportional to self's speed
        launchSpeed = self->velocityX;
        other = &PLAYER;
        other->posY.i.hi += launchSpeed;
        D_80097488.x.i.hi += launchSpeed;
    }
    if (self->hitFlags) {
        self->ext.floorTrap.paletteTimer = 63;
    }
    if (self->ext.floorTrap.paletteTimer) {
        self->ext.floorTrap.paletteTimer--;
    }
    self->palette =
        g_EInitFloorTrap[3] + (self->ext.floorTrap.paletteTimer >> 3);
    self->ext.floorTrap.unk90 = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
}
