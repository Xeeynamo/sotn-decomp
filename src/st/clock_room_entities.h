// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

void EntityClockHands(Entity* self) {
    u16 params = self->params;
    Entity* handShadow = self + 5;

    if (!self->step) {
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 25;
        self->zPriority = 0x3F - params;
        self->drawFlags = ENTITY_ROTATE;

        // Create hand shadows
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, handShadow);
        handShadow->animSet = ANIMSET_OVL(1);
        handShadow->animCurFrame = params + 25;
        handShadow->zPriority = 0x3F - params;
        handShadow->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
        handShadow->blendMode = BLEND_TRANSP;
        handShadow->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                            FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        handShadow->posY.i.hi += 4;
    }

    self->rotate = (self->ext.clockRoom.hand * ROT(360)) / (60 * 60);
    if (params) {
        self->rotate += ROT(90);
    }

    self->rotate &= 0xFFF;
    handShadow->rotate = self->rotate;
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
        self->ext.birdcage.prevState = self->ext.birdcage.state;
        self->zPriority = 0x3C;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
        self->posX.i.hi = bird_cage_pos_x[params] - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = bird_cage_pos_y[params] - g_Tilemap.scrollY.i.hi;
        break;

    case 1:
        if (self->ext.birdcage.prevState != self->ext.birdcage.state) {
            self->ext.birdcage.prevState = self->ext.birdcage.state;
            self->drawFlags = ENTITY_OPACITY | ENTITY_SCALEX | ENTITY_SCALEY;
            self->ext.birdcage.timer = 64;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 2:
        self->scaleX = self->scaleY -= 2;
        self->opacity -= 1;
        if (!--self->ext.birdcage.timer) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 3:
        self->posX.val += FIX(0.125);
        if (!--self->ext.birdcage.timer) {
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
        if (!--self->ext.birdcage.timer) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0x3C;
            self->step++;
            g_api.PlaySfx(SFX_STONE_MOVE_B);
        }
        break;

    case 5:
        self->scaleX = self->scaleY += 2;
        self->opacity += 1;
        if (!--self->ext.birdcage.timer) {
            self->drawFlags = ENTITY_DEFAULT;
            self->step = 1;
        }
        break;
    }
}

void UpdateStatueTiles(s32 tilePos, u16 tile) {
    u32 i;

    for (i = 0; i < 6; i++) {
        g_Tilemap.fg[tilePos] = tile;
        tilePos++;
        g_Tilemap.fg[tilePos] = tile;
        tilePos += 15;
    }
}

extern s16 statue_pos_x_1[];
extern u32 statue_pos_x_3[];

void EntityStatue(Entity* self) {
    u16 params = self->params;
    Entity* entity = self + 2;
    Entity* statueGear = self + 11;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->zPriority = 0x40;

        if (!g_Statues[params]) {
            self->posX.i.hi += statue_pos_x_1[params];
            if (self->params) {
                UpdateStatueTiles(2, 0x597);
            } else {
                UpdateStatueTiles(12, 0x597);
            }
        } else {
            self->posX.i.hi += statue_pos_x_1[params + 2];
            if (self->params) {
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
        entity->drawFlags = ENTITY_OPACITY;
        entity->blendMode = BLEND_TRANSP;
#ifndef STAGE_IS_NO0
        entity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA;
#endif
        entity->posY.i.hi += 8;
        break;

    case 1:
        if (g_Statues[params] != self->ext.statue.step) {
            self->ext.statue.step = g_Statues[params];
            if (self->ext.statue.step) {
                statueGear->ext.statue.step = 1;
            } else {
                statueGear->ext.statue.step = 2;
            }
            self->hitboxState = 2;
            self->step++;
            PlaySfxPositional(SFX_STONE_MOVE_C);
        }
        break;

    case 2:
        GetPlayerCollisionWith(self, 16, 32, 19);
        if (!self->step_s) {
            if (self->ext.statue.step) {
                if (self->params) {
                    UpdateStatueTiles(2, 0);
                } else {
                    UpdateStatueTiles(12, 0);
                }
            }
            self->ext.statue.timer = 96;
            self->step_s++;
        }

        if (self->ext.statue.step) {
            self->posX.val += statue_pos_x_3[params];
        } else {
            self->posX.val -= statue_pos_x_3[params];
        }

        if (!--self->ext.statue.timer) {
            if (!self->ext.statue.step) {
                if (self->params) {
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
extern s16 gear_pos_x[];

// Gears that spin while the statues are moving
void EntityStatueGear(Entity* self) {
    u16 params = self->params;
    Primitive* prim;
    s32 primIndex;

    switch (self->step) {
    case 0:
        if (!self->step_s) {
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
        prim->drawMode = DRAW_DEFAULT;
        self->step++;
        break;

    case 1:
        if (self->ext.statue.step == 1) {
            self->pose = self->animCurFrame - 17;
            self->step = 2;
        }
        if (self->ext.statue.step == 2) {
            self->pose = 20 - self->animCurFrame;
            self->step = 3;
        }
        self->poseTimer = 0;
        break;

    case 2:
        AnimateEntity(anim_gear_1, self);
        if (!self->ext.statue.step) {
            self->step = 1;
        }
        break;

    case 3:
        AnimateEntity(anim_gear_2, self);
        if (!self->ext.statue.step) {
            self->step = 1;
        }
        break;
    }
}

extern u16 g_StoneDoorTiles[];

static void UpdateStoneDoorTiles(bool doorState) {
    s32 tilePos;
    s16 i, j;

    for (tilePos = 0xC4, i = 0; i < 2; i++) {
        for (j = 0; j < 8; j++) {
            if (doorState) {
                // Open stone doors
                g_Tilemap.fg[tilePos++] = 0x597;
            } else {
                // Close stone doors
                g_Tilemap.fg[tilePos++] = g_StoneDoorTiles[j];
            }
        }
        tilePos += 8;
    }
}

extern s16 stone_door_pos_x[];

// Stone doors on the floor leading to CEN Entity ID 0x1B
void EntityStoneDoor(Entity* self) {
    u16 params = self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 27;
        self->zPriority = 0x40;
        if (!g_CastleFlags[CEN_OPEN]) {
            self->posX.i.hi += stone_door_pos_x[params];
            UpdateStoneDoorTiles(true);
        } else {
            self->posX.i.hi += stone_door_pos_x[params + 2];
            UpdateStoneDoorTiles(false);
        }
        self->posY.i.hi += 88;
        self->ext.stoneDoor.flag = g_CastleFlags[CEN_OPEN];
        break;

    case 1:
        if (self->ext.stoneDoor.flag == NULL) {
            if (g_CastleFlags[CEN_OPEN]) {
                self->step++;
                self->ext.stoneDoor.unk80 = 0;
            }
        }
        self->ext.stoneDoor.flag = g_CastleFlags[CEN_OPEN];
        break;

    case 2:
        if ((self->ext.stoneDoor.unk80 & 0x1F) == 0) {
            PlaySfxPositional(SFX_STONE_MOVE_A);
        }

        ++self->ext.stoneDoor.unk80;
        if (self->ext.stoneDoor.unk80 & 1) {
            if (params) {
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
            self->step--;
            g_backbufferY = 0;
        }
        break;
    }
}

void EntityClockRoomUnused(Entity* self) {}
