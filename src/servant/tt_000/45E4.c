// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>
#include <sfx.h>
#include <psxsdk/libc.h>

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

s32 func_80174864(void) {
    if (g_StageId >= STAGE_RNO0 && g_StageId < STAGE_RNZ1_DEMO) {
        if (D_8003C708.flags == 0x22) {
            return 1;
        }
        if (D_8003C708.flags == 0x20) {
            return 0;
        }
        return 2;
    } else {
        if (D_8003C708.flags == 0x22) {
            return 0;
        }

        if (D_8003C708.flags == 0x20) {
            return 1;
        }
        return 2;
    }
}

#ifdef VERSION_PSP
void func_092EC220(void) {
    memcpy((u8*)&D_8D1DC40, (u8*)&g_ServantDesc, sizeof(ServantDesc));
}
#endif
