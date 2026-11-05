// SPDX-License-Identifier: AGPL-3.0-or-later
static unsigned int seed = 1;

int sotn_rand(void) {
    seed = seed * 0x41C64E6D + 0x3039;
    return (seed >> 16) & 0x7FFF;
}

void func_06032E88(unsigned int value) { seed = value; }
