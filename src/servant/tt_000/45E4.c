// SPDX-License-Identifier: AGPL-3.0-or-later
#include <servant.h>
#include <sfx.h>
#include <psxsdk/libc.h>

#include "../create_event_entity.h"

#include "../is_movement_allowed.h"

#ifndef VERSION_PSP
#include "../check_all_entities_valid.h"
#endif

#include "../servant_unk0.h"

#ifdef VERSION_PSP
extern ServantDesc bat_ServantDesc;
void func_092EC220(void) {
    memcpy((u8*)&D_8D1DC40, (u8*)&bat_ServantDesc, sizeof(ServantDesc));
}
#endif
