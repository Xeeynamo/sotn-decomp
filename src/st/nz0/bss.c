// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <cutscene.h>

STATIC_PAD_BSS(0xC00);
u32 g_SkipCutscene;
Dialogue g_Dialogue;
u32 D_801CB6CC[26];
u16 g_CutsceneFlags;
u16 D_801CB736[3]; // used exclusively by 311C0.c
s32 g_IsCutsceneDone;
