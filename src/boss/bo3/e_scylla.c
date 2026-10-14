// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

typedef struct {
    AnimateEntityFrame* anim;
    s16 values[4];
} ScyllaPartInit;

s32 D_us_80180D48 = 0;

AnimateEntityFrame D_us_80180D4C[] = {
    POSE(18, 1, 0), POSE(18, 2, 0), POSE(18, 3, 0),
    POSE(18, 2, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180D58[] = {
    POSE(4, 1, 0), POSE(7, 5, 0), POSE(7, 6, 0),  POSE(7, 7, 0),
    POSE(7, 8, 0), POSE(7, 9, 0), POSE(7, 10, 0), POSE_END,
};

AnimateEntityFrame D_us_80180D68[] = {
    POSE(8, 7, 0), POSE(8, 8, 0), POSE(8, 9, 0), POSE(8, 10, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180D74[] = {
    POSE(4, 9, 0),  POSE(4, 10, 0), POSE(2, 7, 0),  POSE(2, 6, 0),
    POSE(1, 11, 0), POSE(1, 12, 0), POSE(1, 13, 0), POSE(48, 14, 0),
    POSE(6, 15, 0), POSE(6, 16, 0), POSE(2, 1, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180D8C[] = {
    POSE(2, 1, 0),  POSE(10, 20, 0), POSE(10, 21, 0), POSE(8, 22, 0),
    POSE(8, 23, 0), POSE(8, 24, 0),  POSE(1, 25, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180D9C[] = {
    POSE(8, 22, 0), POSE(8, 23, 0), POSE(8, 24, 0),
    POSE(8, 25, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DA8[] = {
    POSE(2, 22, 0),  POSE(8, 23, 0), POSE(10, 26, 0),
    POSE(10, 27, 0), POSE(8, 1, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180DB4[] = {
    POSE(1, 1, 0),   POSE(3, 17, 0),  POSE(3, 18, 0),
    POSE(16, 19, 0), POSE(16, 19, 0), POSE(6, 18, 0),
    POSE(6, 17, 0),  POSE(1, 1, 0),   POSE_END,
};

AnimateEntityFrame D_us_80180DC8[] = {
    POSE(1, 1, 0), POSE(4, 17, 0), POSE(4, 18, 0), POSE(64, 19, 0), POSE_END,
};

AnimateEntityFrame D_us_80180DD4[] = {
    POSE(20, 28, 0), POSE(20, 29, 0), POSE(20, 30, 0),
    POSE(20, 29, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DE0[] = {
    POSE(1, 28, 0),
    POSE(1, 31, 0),
    POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180DE8[] = {
    POSE(1, 28, 0),  POSE(10, 32, 0), POSE(16, 33, 0), POSE(10, 34, 0),
    POSE(16, 35, 0), POSE(10, 36, 0), POSE(16, 37, 0), POSE(8, 38, 0),
    POSE(8, 39, 0),  POSE(8, 40, 0),  POSE(8, 41, 0),  POSE(8, 28, 0),
    POSE_END,
};

AnimateEntityFrame D_us_80180E04[] = {
    POSE(2, 28, 0), POSE(6, 46, 0), POSE(6, 47, 0),
    POSE(6, 48, 0), POSE(6, 49, 0), POSE(22, 50, 0),
    POSE(8, 32, 0), POSE(1, 33, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E18[] = {
    POSE(4, 33, 0), POSE(6, 42, 0), POSE(6, 43, 0), POSE(6, 44, 0),
    POSE(6, 45, 0), POSE(2, 28, 0), POSE_END,
};

// unused
static AnimateEntityFrame anim_unused_0[] = {
    POSE(32, 28, 0), POSE(4, 36, 0),  POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0),  POSE(26, 54, 0), POSE(6, 53, 0),
    POSE(6, 52, 0),  POSE(4, 51, 0),  POSE(4, 34, 0),  POSE(6, 35, 0),
    POSE(6, 55, 0),  POSE(4, 56, 0),  POSE(26, 57, 0), POSE(6, 56, 0),
    POSE(6, 55, 0),  POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(26, 60, 0), POSE(6, 59, 0),  POSE(6, 58, 0),
    POSE(2, 28, 0),  POSE_END,
};

AnimateEntityFrame D_us_80180E5C[] = {
    POSE(16, 28, 0), POSE(4, 36, 0), POSE(6, 37, 0),  POSE(4, 51, 0),
    POSE(6, 52, 0),  POSE(4, 53, 0), POSE(10, 54, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E6C[] = {
    POSE(16, 54, 0), POSE(6, 53, 0), POSE(6, 52, 0), POSE(4, 51, 0),
    POSE(4, 34, 0),  POSE(6, 35, 0), POSE(6, 55, 0), POSE(4, 56, 0),
    POSE(10, 57, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E80[] = {
    POSE(16, 57, 0), POSE(6, 56, 0),  POSE(6, 55, 0),
    POSE(4, 32, 0),  POSE(6, 33, 0),  POSE(6, 58, 0),
    POSE(4, 59, 0),  POSE(10, 60, 0), POSE_END,
};

AnimateEntityFrame D_us_80180E94[] = {
    POSE(16, 60, 0), POSE(6, 59, 0), POSE(6, 58, 0), POSE(2, 28, 0), POSE_END,
};

static AnimateEntityFrame D_us_80180EA0[] = {
    POSE(20, 61, 0), POSE(20, 62, 0), POSE(20, 63, 0),
    POSE(20, 62, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EAC[] = {
    POSE(4, 62, 0),  POSE(20, 63, 0), POSE(20, 62, 0),
    POSE(20, 61, 0), POSE(16, 62, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EB8[] = {
    POSE(20, 64, 0), POSE(20, 65, 0), POSE(20, 66, 0),
    POSE(20, 65, 0), POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180EC4[] = {
    POSE(20, 67, 0),
    POSE(20, 68, 0),
    POSE(20, 69, 0),
    POSE_LOOP(0),
};

static AnimateEntityFrame D_us_80180ECC[] = {
    POSE(20, 70, 0), POSE(20, 71, 0), POSE(20, 72, 0),
    POSE(20, 71, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180ED8[] = {
    POSE(8, 80, 0), POSE(8, 81, 0), POSE(8, 82, 0),
    POSE(8, 83, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180EE4[] = {
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180EF4[] = {
    POSE(4, 91, 0), POSE(4, 92, 0), POSE(4, 93, 0), POSE(4, 94, 0),
    POSE(1, 85, 0), POSE(1, 88, 0), POSE(1, 86, 0), POSE(1, 89, 0),
    POSE(1, 87, 0), POSE(1, 90, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F0C[] = {
    POSE(7, 95, 0), POSE(7, 96, 0), POSE(7, 97, 0),
    POSE(7, 98, 0), POSE(7, 99, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F18[] = {
    POSE(8, 100, 0), POSE(8, 101, 0), POSE(8, 100, 0),
    POSE(8, 102, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180F24[] = {
    POSE(4, 100, 0), POSE(4, 101, 0), POSE(4, 100, 0),
    POSE(4, 102, 0), POSE_LOOP(0),
};

AnimateEntityFrame D_us_80180F30[] = {
    POSE(2, 100, 0), POSE(8, 103, 0), POSE(8, 104, 0),  POSE(8, 105, 0),
    POSE(8, 106, 0), POSE(8, 107, 0), POSE(16, 108, 0), POSE_END,
};

AnimateEntityFrame D_us_80180F40[] = {
    POSE(8, 109, 0), POSE(8, 108, 0), POSE(8, 110, 0),
    POSE(8, 108, 0), POSE_LOOP(0),
};

ScyllaPartInit D_us_80180F4C[] = {
    {D_us_80180EA0, {0x0086, 0x0078, 0x00B0, 0x0000}},
    {D_us_80180EAC, {0x0084, 0x0088, 0x00B0, 0x0000}},
    {D_us_80180EB8, {0x0090, 0x0050, 0x00AC, 0x0000}},
    {D_us_80180EC4, {0x0086, 0x0024, 0x0090, 0x0000}},
    {D_us_80180ECC, {0x0084, 0x0020, 0x0088, 0x0000}},
};

s16 D_us_80180F88[] = {16, 8, 8, 8};

s16 D_us_80180F90[] = {0, 8, 0, 4, 4, -4, -8, 0};

s16 D_us_80180FA0[] = {-16, -16, 0, 0};

s16 D_us_80180FA8[] = {16, -16, 0, 0};

s16 D_us_80180FB0[] = {-16, 16, 0, 0};

s16 D_us_80180FB8[] = {16, 16, 0, 0};

// unused
static AnimateEntityFrame anim_unused_1[] = {
    POSE(16, 73, 0), POSE(16, 74, 0), POSE(16, 73, 0),
    POSE(16, 75, 0), POSE_LOOP(0),
};

#ifdef VERSION_PSP
char D_pspeu_09266160[] = "charal %x\n";
char D_pspeu_09266170[] = "no WORK !!\n";
#endif

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A2A90);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A2AEC);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A365C);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A3CD8);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A3EE0);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A42A8);

#ifndef VERSION_PSP
const u32 D_us_8019CA94[3] = {0, 0, 0};
#endif

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A4680);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A4988);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A4C0C);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla", func_us_801A4E24);
