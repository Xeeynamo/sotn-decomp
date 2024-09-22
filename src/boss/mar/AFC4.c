// SPDX-License-Identifier: AGPL-3.0-or-later
#include <stage.h>

#include "mar.h"

extern Dialogue g_Dialogue;

#include "../../st/cutscene_unk1.h"

#include "../../st/cutscene_unk2.h"

#include "../../st/cutscene_unk3.h"

#include "../../st/cutscene_unk4.h"

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B2F0);

#include "../../st/cutscene_unk6.h"

#include "../../st/cutscene.h"

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", func_us_8018B74C);

INCLUDE_ASM("boss/mar/nonmatchings/AFC4", EntityMariaCutscene);

// func_psp_092467F8
void func_us_8018C90C(Entity* self) {
    Entity* player;
    Tilemap* tilemap; // unused but shows up in the psp code.

    tilemap = &g_Tilemap;
    player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180A60);
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.unk0 = 1;
        g_Player.padSim = PAD_RIGHT;
        g_Player.D_80072EFC = 1;
        break;
    case 1:
        if ((player->posX.i.hi >= 0x21) && !(g_CutsceneFlags & 1)) {
            g_CutsceneFlags |= 1;
        }
        if (player->posX.i.hi >= 0xB1) {
            g_Player.padSim = PAD_LEFT;
            self->step++;
        } else {
            g_Player.padSim = PAD_RIGHT;
        }
        g_Player.D_80072EFC = 1;
        break;
    case 2:
        if (g_CutsceneFlags & 2) {
            D_8003C8B8 = 1;

            if (g_unkGraphicsStruct.unk0) {
                g_unkGraphicsStruct.unk0 = 0;
            }

            DestroyEntity(self);
            g_Statues[LEFT_STATUE] ^= 1; // suspicious, everywhere else we're
                                         // treating this like a boolean.
        }

        g_Player.padSim = 0;
        g_Player.D_80072EFC = 1;
        break;
    }
}
