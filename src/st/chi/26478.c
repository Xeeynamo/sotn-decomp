/*
 * File: en_heart_drop.c
 * Overlay: CHI
 * Description: ENTITY - Heart prize
 */

#include "chi.h"

// D_801813EC
static u16 g_UnkRecursPrimVecOrder[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6478: UnkRecursivePrimFunc1
#include "../unk_recursive_primfunc_1.h"

// D_8018140C
static u16 g_UnkRecursPrim2Inds[] = {
    0x0000, 0x0001, 0x0003, 0x0004, 0x0001, 0x0002, 0x0004, 0x0005,
    0x0003, 0x0004, 0x0006, 0x0007, 0x0004, 0x0005, 0x0007, 0x0008
};

// [Duplicate]
// func_801A6A58: UnkRecursivePrimFunc2
#include "../unk_recursive_primfunc_2.h"

// func_801A7158: ClutLerp
#include "../clut_lerp.h"

// func_801A7350: PlaySfxWithPosArgs
#include "../play_sfx_with_pos_args.h"