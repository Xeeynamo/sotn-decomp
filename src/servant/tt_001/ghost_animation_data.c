// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

AnimationFrame g_DefaultGhostAnimationFrame[] = {
    /* 801704A8 */ {2, 0x0201},
    /* 801704AC */ {2, 0x0202},
    /* 801704B0 */ {2, 0x0203},
    /* 801704B4 */ {2, 0x0204},
    /* 801704B8 */ {2, 0x0205},
    /* 801704BC */ {2, 0x0206},
    /* 801704C0 */ {2, 0x0207},
    /* 801704C4 */ {2, 0x0208},
    /* 801704C8 */ {0, 0x0000}};

AnimationFrame D_us_801704CC[] = {
    /* 801704CC */ {2, 0x0209},
    /* 801704D0 */ {2, 0x020A},
    /* 801704D4 */ {2, 0x020B},
    /* 801704D8 */ {2, 0x020C},
    /* 801704DC */ {2, 0x020D},
    /* 801704E0 */ {2, 0x020E},
    /* 801704E4 */ {2, 0x020F},
    /* 801704E8 */ {2, 0x0210},
    /* 801704EC */ {2, 0x0211},
    /* 801704F0 */ {2, 0x0212},
    /* 801704F4 */ {2, 0x0213},
    /* 801704F8 */ {2, 0x0214},
    /* 801704FC */ {0, 0x0000}};

AnimationFrame* g_GhostAnimationFrames[] = {
    /* 801705F4 */ g_DefaultGhostAnimationFrame,
    /* 801705F8 */ D_us_801704CC};
