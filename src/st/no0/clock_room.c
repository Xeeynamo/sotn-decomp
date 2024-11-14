// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

void func_us_801CCAAC(Entity* self) {
    s32 minute;
    s32 hour;

    if (!(self->ext.clockRoom.unk88 & 0x1F)) {
        g_api.PlaySfxVolPan(SFX_STONE_MOVE_A, 0x40, 0);
    }
    self->ext.clockRoom.unk88++;

    // Minute hand
    minute =
        (self->ext.clockRoom.unk88 * LOW((self + 5)->ext.clockRoom.bellTimer)) /
        512;
    (self + 5)->ext.clockRoom.hand =
        (s16)((self + 5)->ext.clockRoom.unk80 + minute) % 3600;

    // Hour hand
    hour =
        (self->ext.clockRoom.unk88 * LOW((self + 6)->ext.clockRoom.bellTimer)) /
        512;
    (self + 6)->ext.clockRoom.hand =
        (s16)((self + 6)->ext.clockRoom.unk80 - hour) % 3600;
}

void UpdateBirdcages(Entity* self, u32 timerMinutes) {
    // self + 7 is birdcage door 1
    self += 7;
    if (timerMinutes >= 10 && timerMinutes < 30) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }

    // self + 8 is birdcage door 2
    self += 1;
    if (timerMinutes >= 30 && timerMinutes < 50) {
        self->ext.birdcage.state = true;
    } else {
        self->ext.birdcage.state = false;
    }
}

void UpdateClockHands(Entity* self, PlayerStatus* status) {
    // self + 5 is the minute hand
    self += 5;
    self->ext.clockRoom.hand = status->timerMinutes * 60;

    // self + 6 is the hour hand
    self += 1;
    self->ext.clockRoom.hand =
        (status->timerHours * 300) + (status->timerMinutes * 5);
}

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CCC74);

#include "../clock_room_entities.h"
