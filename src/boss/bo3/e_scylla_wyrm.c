// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo3.h"

AnimateEntityFrame D_us_80180FCC[] = {
    POSE(4, 0x49, 0), POSE(8, 0x4C, 0), POSE(8, 0x49, 0),
    POSE(8, 0x4D, 0), POSE(4, 0x49, 0), POSE_END};
AnimateEntityFrame D_us_80180FD8[] = {
    POSE(8, 0x49, 0), POSE(8, 0x4E, 0), POSE(8, 0x4F, 0), POSE_END};
AnimateEntityFrame D_us_80180FE0[] = {
    POSE(4, 0x4F, 0), POSE(8, 0x4E, 0), POSE(8, 0x49, 0), POSE_END};

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A4FB8);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A516C);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A51E4);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A5338);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A57A4);

INCLUDE_ASM("boss/bo3/nonmatchings/e_scylla_wyrm", func_us_801A5948);
