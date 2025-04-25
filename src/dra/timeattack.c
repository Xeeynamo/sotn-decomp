// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"

s32 TimeAttackController(TimeAttackEvents eventId, TimeAttackActions action) {
    switch (action) {
    case TIMEATTACK_GET_RECORD:
        // get the time attack for a specific defeated boss. this is
        // also responsible to check if the player should teleport into
        // a boss room
        return g_Settings.timeAttackRecords[eventId];

    case TIMEATTACK_SET_RECORD:
        // set new time attack record if the boss was not previously
        // defeated
        if (g_Settings.timeAttackRecords[eventId] == 0) {
            g_Settings.timeAttackRecords[eventId] = g_Status.timerSeconds;
            g_Settings.timeAttackRecords[eventId] += g_Status.timerMinutes * 100;
            g_Settings.timeAttackRecords[eventId] += g_Status.timerHours * 10000;
        }
        break;

    case TIMEATTACK_SET_VISITED:
        // not exactly sure yet why this flag is needed
        g_Settings.D_8003CB00 |= 1 << eventId;
        break;
    }
}
