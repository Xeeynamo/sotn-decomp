// SPDX-License-Identifier: AGPL-3.0-or-later
#include "stage.h"

#define STAGE_IS_NO4

#define OVL_EXPORT(x) NO4_##x
#define STAGE_FLAG OVL_EXPORT(STAGE_FLAG)

extern s16 D_us_801DF788;
extern s16 D_us_801DF78A;
extern s8 D_us_801DF78E;
extern s8 D_us_801DF78F;
