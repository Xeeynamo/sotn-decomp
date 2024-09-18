// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include "mar.h"

void EntityClockRoomController(Entity* self) {
    PlayerStatus* status = &g_Status;
    const int birdcageDoor1 = 7;
    const int birdcageDoor2 = 8;
    const int stoneDoors = 14;
    const int minuteHand = 5;
    const int hourHand = 6;
    const int statues = 1;
    const int shadow = 9;
    const int gears = 12;
    Entity* newEntity;
    Primitive* prim;
    s16 primIndex;
    u16 i, j;

    // Plays the clock bell
    if (self->ext.clockRoom.bellTimer != 0) {
        if (self->ext.clockRoom.bellDuration == 0) {
            g_api.PlaySfx(0x7A6); // Clock bell
            if (--self->ext.clockRoom.bellTimer) {
                self->ext.clockRoom.bellDuration = 64;
            }
        } else {
            self->ext.clockRoom.bellDuration--;
        }
    }

    // Controls the statues
    if (D_800973FC == 0) {
        if (PLAYER.posY.i.hi > 128) {
            g_Statues[RIGHT_STATUE] = false;
        }
    } else if (self->ext.clockRoom.unk8A == 0) {
        g_Statues[RIGHT_STATUE] = true;
    }

    self->ext.clockRoom.unk8A = D_800973FC;
    if (self->step != 0) {
        if ((status->timerFrames == 0) && (status->timerSeconds == 0)) {
            if (status->timerMinutes & 1) {
                g_Statues[LEFT_STATUE] = false;
            } else {
                g_Statues[LEFT_STATUE] = true;
            }
        }
    } else if (status->timerMinutes & 1) {
        g_Statues[LEFT_STATUE] = false;
    } else {
        g_Statues[LEFT_STATUE] = true;
    }

    switch (self->step) {
    case 0:
        if (g_Timer == ((g_Timer / 60) * 0x3C)) {
            g_api.PlaySfx(0x7A9); // Clock tick
        }

        primIndex = g_api.AllocPrimitives(PRIM_G4, 1);
        if (primIndex == -1) {
            return;
        }
        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->y2 = prim->y3 = prim->x1 = prim->x3 = 0x100;
        prim->priority = 0x1F0;
        prim->y0 = prim->y1 = prim->x0 = prim->x2 = 0;
        prim->blendMode = 8;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        InitializeEntity(g_eInitGeneric2);
        g_api.PlaySfx(SET_STOP_MUSIC);
        D_80097928 = 1;
        g_Statues[RIGHT_STATUE] = false; // right statue closed
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 23;
        D_80097910 = 0;
        self->zPriority = 0x40;

        // Create clock hands
        newEntity = &self[5];
        for (i = 0; i < 2; i++) {
            CreateEntityFromCurrentEntity(E_CLOCK_HANDS, newEntity);
            newEntity->params = i;
            newEntity++;
        }

        // Clock set
        self[minuteHand].ext.clockRoom.hand = status->timerMinutes * 0x3C;
        self[hourHand].ext.clockRoom.hand =
            (status->timerHours * 0x12C) + (status->timerMinutes * 5);

        // Create Birdcage doors
        newEntity = &self[birdcageDoor1];
        for (i = 0; i < 2; i++) {
            CreateEntityFromCurrentEntity(E_BIRDCAGE_DOOR, newEntity);
            newEntity->params = i;
            newEntity++;
        }

        if ((status->timerMinutes >= 10) && (status->timerMinutes < 30)) {
            self[birdcageDoor1].ext.birdcage.state = true;
        } else {
            self[birdcageDoor1].ext.birdcage.state = false;
        }

        if ((status->timerMinutes >= 30) && (status->timerMinutes < 50)) {
            self[birdcageDoor2].ext.birdcage.state = true;
        } else {
            self[birdcageDoor2].ext.birdcage.state = false;
        }

        // Shadow for the Bighorn sheep head on the center
        CreateEntityFromCurrentEntity(E_DUMMY_1D, &self[shadow]);
        self[shadow].animSet = ANIMSET_OVL(1);
        self[shadow].animCurFrame = 23;
        self[shadow].zPriority = 0x40;
        self[shadow].palette = 0x804B;
        self[shadow].drawFlags = FLAG_DRAW_UNK8;
        self[shadow].blendMode = 0x10;
        self[shadow].flags = FLAG_DESTROY_IF_OUT_OF_CAMERA |
                             FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
        self[shadow].posY.i.hi += 4;

        // Create path blocking statues
        newEntity = &self[statues];
        for (i = 0; i < 2; i++) {
            CreateEntityFromCurrentEntity(E_STATUE, newEntity);
            newEntity->params = i;
            newEntity++;
        }

        // Create the gears that drive the statues
        newEntity = &self[gears];
        for (j = 0; j < 2; j++) {
            CreateEntityFromCurrentEntity(E_STATUE_GEAR, newEntity);
            newEntity->params = j;
            newEntity++;
        }

        // Create the stones on the floor
        newEntity = &self[stoneDoors];
        for (j = 0; j < 2; j++) {
            CreateEntityFromCurrentEntity(E_STONE_DOOR, newEntity);
            newEntity->params = j;
            newEntity++;
        }
        break;

    case 1:
        if (status->timerFrames == 0) {
            g_api.PlaySfx(0x7A9); // clock tick
        }

        // Update clock hands
        self[minuteHand].ext.clockRoom.hand = status->timerMinutes * 0x3C;
        self[hourHand].ext.clockRoom.hand =
            (status->timerHours * 0x12C) + (status->timerMinutes * 5);
        if ((status->timerSeconds == 0) && (status->timerFrames == 0) &&
            (status->timerMinutes == 0)) {
            self->ext.clockRoom.bellTimer =
                ((status->timerHours + 11) % 12) + 1;
            if (self->ext.clockRoom.bellTimer == 0) {
                self->ext.clockRoom.bellTimer = 12;
            }
        }
        break;
    }
}

// Entity ID 0x17
void EntityClockHands(Entity* self) {
    Entity* handShadow = &self[5];
    u16 params = self->params;

    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 25;
        self->zPriority = 0x3F - params;
        self->drawFlags = FLAG_DRAW_ROTZ;

        // Create hand shadows
        CreateEntityFromCurrentEntity(E_DUMMY_1D, handShadow);
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

extern u16 D_us_801812A8[];
// todo: overlapping arrays
extern s16 D_us_80181280[];
extern s16 D_us_80181284[];

// Birdcage doors on the clock Entity ID 0x18
void EntityBirdcageDoor(Entity* self) {
    u16 params = self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = D_us_801812A8[self->ext.birdcage.state & 1];
        self->zPriority = 0x3C;
        self->rotX = self->rotY = 0x100;
        self->ext.birdcage.prevState = self->ext.birdcage.state;
        self->unk6C = 0x80;
        self->posX.i.hi = D_us_80181280[params] - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = D_us_80181284[params] - g_Tilemap.scrollY.i.hi;
        break;

    case 1:
        if (self->ext.birdcage.prevState != self->ext.birdcage.state) {
            self->drawFlags = FLAG_DRAW_UNK8 | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->ext.birdcage.timer = 64;
            self->ext.birdcage.prevState = self->ext.birdcage.state;
            self->step++;
            g_api.PlaySfx(0x608);
        }
        break;

    case 2:
        self->rotX = self->rotY -= 2;
        self->unk6C += 0xFF;
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0;
            self->step++;
            g_api.PlaySfx(0x608);
        }
        break;

    case 3:
        self->posX.val += FIX(0.125);
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->animCurFrame = D_us_801812A8[self->ext.birdcage.state & 1];
            self->posX.i.hi -= 8;
            self->posY.i.hi += 8;
            self->step++;
            g_api.PlaySfx(0x608);
        }
        break;

    case 4:
        self->posY.val -= FIX(0.125);
        if (--self->ext.birdcage.timer == 0) {
            self->ext.birdcage.timer = 64;
            self->zPriority = 0x3C;
            self->step++;
            g_api.PlaySfx(0x608);
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

extern u16 D_us_80181288[];
extern u16 D_us_8018128C[];
extern s32 D_us_801812A0[];

// Entity ID 0x19
void EntityStatue(Entity* self) {
    Entity* entity = &self[2];
    Entity* statueGear = &self[11];
    u16 params = self->params;
    u16* temp_a0;
    u16* fakeVar;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->zPriority = 0x40;

        if (g_Statues[params] == 0) {
            self->posX.i.hi += D_us_80181288[params];
            if (self->params != 0) {
                UpdateStatueTiles(2, 0x597);
            } else {
                UpdateStatueTiles(12, 0x597);
            }
        } else {
            self->posX.i.hi += D_us_8018128C[params];
            if (self->params != 0) {
                UpdateStatueTiles(2, 0);
            } else {
                UpdateStatueTiles(12, 0);
            }
        }

        self->ext.statue.step = g_Statues[params];
        self->posY.i.hi -= 58;

        // Create shadow for the statue
        CreateEntityFromCurrentEntity(E_DUMMY_1D, entity);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = params + 10;
        entity->zPriority = 0x3F;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->blendMode = 0x10;
        entity->flags = FLAG_DESTROY_IF_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                        FLAG_KEEP_ALIVE_OFFCAMERA;
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
            PlaySfxPositional(0x609);
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
            self->posX.val += D_us_801812A0[params];
        } else {
            self->posX.val -= D_us_801812A0[params];
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

extern u8 D_us_801812C4[];
extern u8 D_us_801812D0[];
extern u16 D_us_80181290[];

// Gears that spin while the statues are moving Entity ID 0x1A
void EntityStatueGear(Entity* self) {
    u16 params = self->params;
    Primitive* prim;
    s16 primIndex;

    switch (self->step) {
    case 0:
        if (self->step_s == 0) {
            InitializeEntity(g_eInitGeneric2);
            self->animSet = ANIMSET_OVL(1);
            self->animCurFrame = 17;
            self->zPriority = 0x80;
            self->posX.i.hi += D_us_80181290[params];
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
        AnimateEntity(D_us_801812C4, self);
        if (self->ext.statue.step == 0) {
            self->step = 1;
        }
        break;

    case 3:
        AnimateEntity(D_us_801812D0, self);
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
extern s16 D_us_80181294[];
extern s16 D_us_80181298[];

// Stone doors on the floor leading to CEN Entity ID 0x1B
void EntityStoneDoor(Entity* self) {
    u16 params = self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = params + 27;
        self->zPriority = 0x40;
        if (g_CastleFlags[CLOCK_ROOM_DOORS] == 0) {
            self->posX.i.hi += D_us_80181294[params];
            UpdateStoneDoorTiles(true);
        } else {
            self->posX.i.hi += D_us_80181298[params];
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
            PlaySfxPositional(0x607);
        }

        if (++self->ext.stoneDoor.unk80 % 2) {
            if (params != 0) {
                self->posX.i.hi++;
            } else {
                self->posX.i.hi--;
            }
            if (self->ext.stoneDoor.unk80 % 2) {
                g_backbufferY = 1;
            } else {
                g_backbufferY = 0;
            }
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

void func_us_80199114(void) {}
