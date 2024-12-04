// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../dra/dra.h"

void func_8010E168(s32 arg0, s16 arg1) {
    if (arg0 == 0) {
        // Create factory with unkA0 = 0x1500, blueprint #44.
        // Blueprint 44 is to make child entity #11, or EntityPlayerBlinkWhite
        CreateEntFactoryFromEntity(g_CurrentEntity, FACTORY(44, 0x15), 0);
        if (g_Player.timers[13] <= arg1) {
            g_Player.timers[13] = arg1;
        }
    } else if (g_Player.timers[14] <= arg1) {
        g_Player.timers[14] = arg1;
    }
}

INCLUDE_ASM("dra_psp/psp/dra_psp/3AE30", func_psp_09117858);

INCLUDE_ASM("dra_psp/psp/dra_psp/3AE30", func_psp_091178F8);

INCLUDE_ASM("dra_psp/psp/dra_psp/3AE30", func_psp_09117998);
