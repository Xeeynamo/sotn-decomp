// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../np3/np3.h"

// clang-format off

void func_801CF778(void) {
    Entity* currEnt15;
    Entity* ent15Parent;
    currEnt15 = g_CurrentEntity + 15;
    ent15Parent = currEnt15->ext.GH_Props.parent;
    currEnt15->ext.GH_Props.rotate = ent15Parent->ext.GH_Props.rotate + 0x300;
}

int func_801CF7A0(Entity* ent) {
    Entity* otherEnt;
    s32 xDistance;
    s32 step;

    if (g_CurrentEntity->ext.GH_Props.unk8E) {
        --g_CurrentEntity->ext.GH_Props.unk8E;
    }
    otherEnt = &PLAYER;
    xDistance = ent->posX.i.hi - otherEnt->posX.i.hi;

    if (g_CurrentEntity->facingLeft) {
        xDistance = -xDistance;
    }

    if (xDistance < -16) {
        func_801CE1E8(10);
        return;
    }

    if (g_CurrentEntity->ext.GH_Props.unk84 == 1) {
        otherEnt = g_CurrentEntity + 10;
    } else {
        otherEnt = g_CurrentEntity + 13;
    }

    step = func_801CE120(otherEnt, g_CurrentEntity->facingLeft);
    if (step) {
        func_801CE1E8(7);
        return;
    }

    step = 5;

    if (xDistance < 48) {
        step = 7;
    }

    if (xDistance < 80) {
        step = 5;
    }

    if (xDistance > 128) {
        step = 8;
    }

    if (!g_CurrentEntity->ext.GH_Props.unk8E) {
        if (xDistance < 160) {
            g_CurrentEntity->ext.GH_Props.unk8E = 3;
            step = 6;
            g_CurrentEntity->ext.GH_Props.unk8C = 1;
        }
        if (xDistance < 64) {
            g_CurrentEntity->ext.GH_Props.unk8C = 0;
        }
    }

    if (step != g_CurrentEntity->step) {
        do {
            func_801CE1E8(step);
        } while (0); // no idea why, found by permuter
    }

    if ((g_CurrentEntity->step == 7) && (step == 5)) {
        g_CurrentEntity->ext.GH_Props.unkB0[0] = 1;
    }
}

// EntityGurkha
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/gurkha", func_pspeu_0925DF90);

// EntityGurkhaSword
INCLUDE_ASM("st/np3_psp/nonmatchings/np3_psp/gurkha", func_pspeu_0925F370);

// clang-format on
