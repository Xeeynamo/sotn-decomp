// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"

typedef struct {
    u8 walk[14];
    u8 walkBackward[14];
    u8 swing[26];
    u8 jump[10];
    u8 land[12];
    u8* animations[5];
} BoneScimitarSpriteAnimationData;

BoneScimitarSpriteAnimationData g_Stage02BoneScimitarSpriteAnimations = {
    {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, -1, -1},
    {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, -1, -1},
    {5,  1, 5,  2,  5,  7, 6, 8, 5, 9, 5, 10, 5,
     11, 1, 12, 30, 13, 4, 4, 4, 5, 4, 6, -1, -1},
    {1, 1, 4, 14, 4, 15, 1, 1, -1, -1},
    {1, 1, 4, 14, 6, 15, 4, 14, 1, 1, -1, -1},
    {g_Stage02BoneScimitarSpriteAnimations.walk,
     g_Stage02BoneScimitarSpriteAnimations.walkBackward,
     g_Stage02BoneScimitarSpriteAnimations.swing,
     g_Stage02BoneScimitarSpriteAnimations.jump,
     g_Stage02BoneScimitarSpriteAnimations.land},
};
