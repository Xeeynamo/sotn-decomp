// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no4.h"

void func_us_801C8248(Entity* self) {
    s32 posX, posY;

#ifdef VERSION_PSP
    if (g_CastleFlags[SUCCUBUS_CS]) {
#else
    if (g_api.TimeAttackController(
            TIMEATTACK_EVENT_SUCCUBUS_DEFEAT, TIMEATTACK_GET_RECORD)) {
#endif
        posX = self->posX.val;
        posY = self->posY.val;
        CreateEntityFromCurrentEntity(E_HEART_DROP, self);
        self->params = 10;
        self->posX.val = posX;
        self->posY.val = posY;
    }
}
