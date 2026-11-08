// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../zero.h"
#include "../zero/sound.h"

void PlaySfx(s32 sfxId) {}

void func_06010400(void) {}

void satz_idle(void);

void func_060139C4(void) {
    for (;;) {
        satz_idle();
    }
}
