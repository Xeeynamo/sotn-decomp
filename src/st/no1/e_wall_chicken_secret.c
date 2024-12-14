// SPDX-License-Identifier: AGPL-3.0-or-later
#include "common.h"

// Breakable wall with chicken
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BE880);

// Hit spawner?
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BEB54);

// Wall particles on hit
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BEE00);

// More particles / stones
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BF074);

// Secret elevator inside chicken wall
// Stand still for ~20 seconds to activate
INCLUDE_ASM("st/no1/nonmatchings/e_wall_chicken_secret", func_us_801BF3F4);
