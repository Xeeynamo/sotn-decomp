// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

s32 D_80174F80[11];
u8 D_80174FAC;
u8 D_80174FB0;
u8 D_80174FB4;
u8 D_80174FB8;
Point16 D_80175000[32];
s32 D_80154F7C[16];
AnimationFrame g_MarEmptyAnimGroup[ZERO_LEN];
s16 g_MarSensorsCeilingCrouch[NUM_HORIZONTAL_SENSORS];
s32 mar_hit_stun_timer; // TODO move to pl_steps?
DebugInfo g_MarDebug;
u8 dead_dissolve_bmp[0x1400];
s16 D_80174F68;
s16 D_80174F6C;
s32 death_kind;
s32 mar_8015459C;
s32 mar_80175958[32];
s32 mar_801759D8[32];
ButtonComboState g_MarComboButtons[2];
s32 D_pspeu_092E5F28;
s32 D_pspeu_092E5F20;
s32 D_pspeu_092E5F18;
s32 D_pspeu_092E5D18[0x80];
Point16 D_pspeu_092E5B18[0x80];
s32 D_pspeu_092E5B10;
u8 D_pspeu_092E5B08[0x08];
s32 D_pspeu_092E5908[0x80];
s32 D_pspeu_092E5900;
