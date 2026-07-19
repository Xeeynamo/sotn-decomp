// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u8 animIdle[18];
    u8 animAttack[26];
    u8 animAttackReturn[28];
    u8* animations[3];
} Entity38AnimationData;

Entity38AnimationData g_Stage02Entity38AnimationData = {
    {6, 1, 6, 2, 6, 3, 6, 4, 6, 5, 6, 6, 6, 7, 6, 8, -1, -1},
    {8, 9,  8, 10, 8, 11, 8, 12, 8, 13, 8, 14, 8,
     15, 8, 16, 8, 17, 8, 18, 8, 19, 16, 20, -1, -1},
    {8, 20, 8, 19, 8, 18, 8, 17, 8, 16, 8, 15, 8, 14,
     8, 13, 8, 12, 8, 11, 8, 10, 8, 9,  16, 2,  -1, -1},
    {g_Stage02Entity38AnimationData.animIdle,
     g_Stage02Entity38AnimationData.animAttack,
     g_Stage02Entity38AnimationData.animAttackReturn},
};
