// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"
#include <servant.h>

extern s32 s_ServantId;
extern u16 D_us_801722E8[];
// During cleanup, rename this.  May not actually be this familiar, unknown
// where it's set
extern Entity thisFamiliar;
extern s32 s_zPriority;
extern FamiliarStats s_FaerieStats;
extern s32 D_us_8017931C;
extern s32 D_us_80179320;

// this may actually be a multi dimensional array instead of a struct
typedef struct {
    s16 unk0;
    s16 unk2;
} UnkFaerieStruct;

extern UnkFaerieStruct D_us_80172368[];
extern AnimationFrame* D_us_80172B14[];

void func_us_80173994(Entity*, s32);
void func_us_801739D0(Entity*);
