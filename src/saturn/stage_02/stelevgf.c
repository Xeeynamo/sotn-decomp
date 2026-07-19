// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sattypes.h"
#include <saturn_sprite.h>

SaturnSpritePalette1 g_Stage02ElevatorMainPalette = {
    1,
    {{
        0x8160, 0xFBFF, 0xD2D6, 0xCA94, 0xC252, 0xBA10, 0xB1CE, 0xA58C,
        0x9D4A, 0x9508, 0x8CC6, 0x8484, 0xFFE0, 0xD280, 0xB9C0, 0xA100,
    }},
};

SaturnSpritePalette1 g_Stage02ElevatorAlternatePalette = {
    0x4001,
    {{
        0, 0xA100, 0xB9C0, 0xD280, 0xFFE0, 0xD280, 0xB9C0, 0xA100,
        0, 0xA100, 0xB9C0, 0xD280, 0xFFE0, 0xD280, 0xB9C0, 0xA100,
    }},
};

SaturnSpriteImage g_Stage02ElevatorImages[4] = {
    {8, 33, 0},
    {28, 33, 0x44},
    {8, 35, 0x12C},
    {0, 0, 0x174},
};

SaturnSpriteResource g_Stage02ElevatorResource = {
    g_Stage02ElevatorImages,
    (u16*)&g_Stage02ElevatorMainPalette,
    -1,
    0xFFFF,
};

SaturnSpriteResource g_Stage02ElevatorPaletteResource = {
    NULL,
    (u16*)&g_Stage02ElevatorAlternatePalette,
    -1,
    0xFFFF,
};
