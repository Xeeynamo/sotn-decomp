// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>
#include "mar.h"
#include "sfx.h"

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
            g_api.PlaySfx(SFX_CLOCK_BELL);
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
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
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

        InitializeEntity(g_EInitCommon);
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
        CreateEntityFromCurrentEntity(E_CLOCK_ROOM_SHADOW, &self[shadow]);
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
            g_api.PlaySfx(SFX_CLOCK_ROOM_TICK);
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

#include "../../st/clock_room_entities.h"
