// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include "dialogue2.h"

// As g_Dialogue can be either structs, we only care of the bigger one
union DiagCombo {
    Dialogue diag1;
    Dialogue2 diag2;
};

u16 msgBoxTpage[768];
u32 D_801C06B0[4];
u32 D_801C06C0[1346];
u16 D_801C1BC8;
u16 D_801C1BCA;
u16 D_801C1BCC[1022];
u32 D_801C23C8[64];
u32 g_SkipCutscene;
union DiagCombo g_Dialogue;
u32 D_801C2510[26];
u32 D_801C2578;
u32 g_CutsceneFlags;
s32 g_IsCutsceneDone;
