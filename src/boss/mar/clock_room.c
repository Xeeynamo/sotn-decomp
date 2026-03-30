// SPDX-License-Identifier: AGPL-3.0-or-later
#include "mar.h"

extern u16 g_Statues[];

static s16 bird_cage_pos_x[] = {0x84, 0x8E};
static s16 bird_cage_pos_y[] = {0x64, 0x8E};
static s16 statue_pos_x_1[] = {0x51, -0x50, 0x81, -0x80};
static s16 gear_pos_x[] = {0x7C, -0x7C};
static s16 stone_door_pos_x[] = {-0x20, 0x20, -0x50, 0x50};
static s16 unused[] = {0x51, -0x50};
static u32 statue_pos_x_3[] = {FIX(0.5), FIX(-0.5)};
static u16 anim_bird_cage[] = {21, 22};
static s16 unused2[] = {-14, 14, -8, 8, -23, -14, -8, 8, 14, 23, -8, 8};
static u8 anim_gear_1[] = {6, 17, 6, 18, 6, 19, 6, 20, 0, 0};
static u8 anim_gear_2[] = {6, 20, 6, 19, 6, 18, 6, 17, 0, 0};
static u16 g_StoneDoorTiles[] = {
    0x597, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x597,
};

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
            g_api.PlaySfx(SFX_CLOCK_ROOM_BELL);
            if (--self->ext.clockRoom.bellTimer) {
                self->ext.clockRoom.bellDuration = 64;
            }
        } else {
            self->ext.clockRoom.bellDuration--;
        }
    }

    // Controls the statues
    if (g_unkGraphicsStruct.D_800973FC == 0) {
        if (PLAYER.posY.i.hi > 128) {
            g_Statues[RIGHT_STATUE] = false;
        }
    } else if (self->ext.clockRoom.unk8A == 0) {
        g_Statues[RIGHT_STATUE] = true;
    }

    self->ext.clockRoom.unk8A = g_unkGraphicsStruct.D_800973FC;
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
        prim->drawMode = DRAW_HIDE;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);

        InitializeEntity(g_EInitCommon);
        g_api.PlaySfx(SET_STOP_MUSIC);
        stopMusicFlag = true;
        g_Statues[RIGHT_STATUE] = false; // right statue closed
        self->animSet = ANIMSET_OVL(1);
        self->animCurFrame = 23;
        currentMusicId = 0;
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
        self[shadow].palette = PAL_FLAG(0x4B);
        self[shadow].drawFlags = ENTITY_OPACITY;
        self[shadow].blendMode = BLEND_TRANSP;
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
