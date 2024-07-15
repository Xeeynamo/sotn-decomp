#include "../wrp/wrp.h"

u32 c_GoldPrizes[] = {
    1, 25, 50, 100, 250, 400, 700, 1000, 2000, 5000,
};

s16 D_80180EB8[] = {0xFFFA, 0x0004, 0x0000, 0xFFF8};

s8 c_HeartPrizes[] = {1, 5};

s32 g_ExplosionYVelocities[] = {
    /* EC4 */ 0xFFFF0000,
    /* EC8 */ 0xFFFE8000,
    /* ECC */ 0xFFFE8000,
    /* ED0 */ 0xFFFE8000,
    /* ED4 */ 0xFFFD0000,
};
