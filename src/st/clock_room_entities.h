// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

void EntityClockHands(Entity* self) {
    Entity* handShadow = &self[5];
    u16 params = self->params;

    if (self->step == 0) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 25;
        self->zPriority = 0x3F - params;
        self->drawFlags = FLAG_DRAW_ROTZ;

        // Create hand shadows
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, handShadow);
        handShadow->drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_ROTZ;
        handShadow->blendMode = 0x10;
        handShadow->animSet = ANIMSET_OVL(1);
        handShadow->animCurFrame = params + 25;
        handShadow->zPriority = 0x3F - params;
        handShadow->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        handShadow->posY.i.hi += 4;
    }

    self->rotZ = (self->ext.clockRoom.hand * 0x1000) / 3600;
    if (params != 0) {
        self->rotZ += 0x400;
    }

    handShadow->rotZ = self->rotZ &= 0xFFF;
}

extern u16 anim_bird_cage[];
// todo: overlapping arrays
extern s16 bird_cage_pos_x[];
extern s16 bird_cage_pos_y[];

// Birdcage doors on the clock
void EntityBirdcageDoor(Entity* self) {
    u16 params = self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = anim_bird_cage[self->ext.birdcage.state & 1];
        self->zPriority = 0x3C;
        self->rotX = self->rotY = 0x100;
        self->ext.birdcage.prevState = self->ext.birdcage.state;
        self->unk6C = 0x80;
        self->posX.i.hi = bird_cage_pos_x[params] - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = bird_cage_pos_y[params] - g_Tilemap.scrollY.i.hi;
        break;

    case 1:
        if (self->ext.birdcage.prevState != self->ext.birdcage.state) {
            self->drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->ext.birdcage.timer = 64;
            self->ext.birdcage.prevState = self->ext.birdcage.state;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 2:
        self->rotX = self->rotY -= 2;
        self->unk6C += 0xFF;
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 3:
        self->posX.val += FIX(0.125);
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->animCurFrame = anim_bird_cage[self->ext.birdcage.state & 1];
            self->posX.i.hi -= 8;
            self->posY.i.hi += 8;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 4:
        self->posY.val -= FIX(0.125);
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0x3C;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 5:
        self->rotX = self->rotY += 2;
        self->unk6C += 1;
        if (--self->ext.birdcage.timer == 0) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->step = 1;
        }
        break;
    }
}

void UpdateStatueTiles(s32 tilePos, s32 tile) {
    u32 i;

    for (i = 0; i < 6; i++) {
        g_Tilemap.fg[tilePos] = tile;
        tilePos++;
        g_Tilemap.fg[tilePos] = tile;
        tilePos += 15;
    }
}

extern u16 statue_pos_x_1[];
extern u16 statue_pos_x_2[];
extern s32 statue_pos_x_3[];

void EntityStatue(Entity* self) {
    Entity* entity = &self[2];
    Entity* statueGear = &self[11];
    u16 params = self->params;
    u16* temp_a0;
    u16* fakeVar;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->zPriority = 0x40;

        if (g_Statues[params] == 0) {
            self->posX.i.hi += statue_pos_x_1[params];
            if (self->params != 0) {
                UpdateStatueTiles(2, 0x597);
            } else {
                UpdateStatueTiles(12, 0x597);
            }
        } else {
            self->posX.i.hi += statue_pos_x_2[params];
            if (self->params != 0) {
                UpdateStatueTiles(2, 0);
            } else {
                UpdateStatueTiles(12, 0);
            }
        }

        self->ext.statue.step = g_Statues[params];
        self->posY.i.hi -= 58;

        // Create shadow for the statue
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = params + 10;
        entity->zPriority = 0x3F;
        entity->drawFlags = FLAG_DRAW_UNK8;
#ifdef STAGE_IS_NO0
        entity->drawMode = DRAW_TPAGE;
#else
        entity->blendMode = 0x10;
        entity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA;
#endif
        entity->posY.i.hi += 8;
        break;

    case 1:
        //! FAKE
        fakeVar = g_Statues;
        temp_a0 = fakeVar;
        temp_a0 += params;
        if (*temp_a0 != self->ext.statue.step) {
            self->ext.statue.step = *temp_a0;
            if (self->ext.statue.step == 0) {
                statueGear->ext.statue.step = 2;
            } else {
                statueGear->ext.statue.step = 1;
            }
            self->hitboxState = 2;
            self->step++;
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }
        break;

    case 2:
        GetPlayerCollisionWith(self, 0x10, 0x20, 0x13);
        if (self->step_s == 0) {
            if (self->ext.statue.step != 0) {
                if (self->params != 0) {
                    UpdateStatueTiles(2, 0);
                } else {
                    UpdateStatueTiles(12, 0);
                }
            }
            self->ext.statue.timer = 96;
            self->step_s++;
        }

        if (self->ext.statue.step != 0) {
            self->posX.val += statue_pos_x_3[params];
        } else {
            self->posX.val -= statue_pos_x_3[params];
        }

        if (--self->ext.statue.timer == 0) {
            if (self->ext.statue.step == 0) {
                if (self->params != 0) {
                    UpdateStatueTiles(2, 0x597);
                } else {
                    UpdateStatueTiles(12, 0x597);
                }
            }
            statueGear->ext.statue.step = 0;
            self->hitboxState = 0;
            self->step_s = 0;
            self->step--;
        }
        break;
    }
    entity->posX.i.hi = self->posX.i.hi;
}

extern u8 anim_gear_1[];
extern u8 anim_gear_2[];
extern u16 gear_pos_x[];

// Gears that spin while the statues are moving
void EntityStatueGear(Entity* self) {
    u16 params = self->params;
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        if (self->step_s == 0) {
            InitializeEntity(g_EInitCommon);
            self->animSet = ANIMSET_OVL(1);
            self->animCurFrame = 17;
            self->zPriority = 0x80;
            self->posX.i.hi += gear_pos_x[params];
            self->posY.i.hi -= 44;
            self->step = 0;
            self->step_s++;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (primIndex == -1) {
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->x0 = self->posX.i.hi - 6;
        prim->y0 = self->posY.i.hi - 16;
        prim->u0 = 12;
        prim->v0 = 32;
        prim->priority = 0x7F;
        prim->blendMode = 0;
        self->step++;
        break;

    case 1:
        if (self->ext.statue.step == self->step) {
            self->step = 2;
            self->animFrameIdx = self->animCurFrame - 17;
        }
        if (self->ext.statue.step == 2) {
            self->step = 3;
            self->animFrameIdx = 20 - self->animCurFrame;
        }
        self->animFrameDuration = 0;
        break;

    case 2:
        AnimateEntity(anim_gear_1, self);
        if (self->ext.statue.step == 0) {
            self->step = 1;
        }
        break;

    case 3:
        AnimateEntity(anim_gear_2, self);
        if (self->ext.statue.step == 0) {
            self->step = 1;
        }
        break;
    }
}

extern s16 g_StoneDoorTiles[];

void UpdateStoneDoorTiles(bool doorState) {
    s32 tilePos;
    s16 i, j;

    for (tilePos = 0xC4, i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            if (doorState) {
                // Open stone doors
                g_Tilemap.fg[tilePos] = 0x597;
                tilePos++;
            } else {
                // Close stone doors
                g_Tilemap.fg[tilePos] = g_StoneDoorTiles[j];
                tilePos++;
            }
        }
        tilePos += 8;
    }
}

// todo overlapping?
extern s16 stone_door_pos_x_1[];
extern s16 stone_door_pos_x_2[];

// Stone doors on the floor leading to CEN Entity ID 0x1B
void EntityStoneDoor(Entity* self) {
    u16 params = self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 27;
        self->zPriority = 0x40;
        if (g_CastleFlags[CLOCK_ROOM_DOORS] == 0) {
            self->posX.i.hi += stone_door_pos_x_1[params];
            UpdateStoneDoorTiles(true);
        } else {
            self->posX.i.hi += stone_door_pos_x_2[params];
            UpdateStoneDoorTiles(false);
        }
        self->posY.i.hi += 88;
        self->ext.stoneDoor.flag = g_CastleFlags[CLOCK_ROOM_DOORS];
        break;

    case 1:
        if (self->ext.stoneDoor.flag == NULL) {
            if (g_CastleFlags[CLOCK_ROOM_DOORS]) {
                self->ext.stoneDoor.unk80 = 0;
                self->step++;
            }
        }
        self->ext.stoneDoor.flag = g_CastleFlags[CLOCK_ROOM_DOORS];
        break;

    case 2:
        if ((self->ext.stoneDoor.unk80 % 32) == 0) {
            PlaySfxPositional(SFX_STONE_MOVE_A);
        }

        if (++self->ext.stoneDoor.unk80 % 2) {
            if (params != 0) {
                self->posX.i.hi++;
            } else {
                self->posX.i.hi--;
            }
#ifdef STAGE_IS_NO0
            g_backbufferY = 1;
#else
            if (self->ext.stoneDoor.unk80 % 2) {
                g_backbufferY = 1;
            } else {
                g_backbufferY = 0;
            }
#endif
        } else {
            g_backbufferY = 0;
        }

        if (self->ext.stoneDoor.unk80 > 96) {
            UpdateStoneDoorTiles(false);
            g_backbufferY = 0;
            self->step--;
        }
        break;
    }
}

void EntityClockRoomUnused(void) {}
