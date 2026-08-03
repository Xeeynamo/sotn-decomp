// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rbo8.h"

void func_801D0A00(s16* arg0) {
    Entity* ent;

    ent = g_CurrentEntity + arg0[1];
    func_801CD91C(ent);
    ent = g_CurrentEntity + arg0[0];
    func_801CD91C(ent);
    ent = g_CurrentEntity + 1;
    func_801CD91C(ent);
    ent = g_CurrentEntity + arg0[2];
    polarPlacePart(ent);
    ent = g_CurrentEntity + arg0[3];
    polarPlacePart(ent);

    for (arg0 += 4; *arg0; arg0++) {
        if (*arg0 != 0xFF) {
            ent = g_CurrentEntity + *arg0;
            polarPlacePart(ent);
        }
    }
}
