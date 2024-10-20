// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include "no0.h"

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CCAAC);

INCLUDE_ASM("st/no0/nonmatchings/clock_room", func_us_801CCBE4);

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
