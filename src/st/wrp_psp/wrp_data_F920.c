#include "../wrp/wrp.h"

u8 D_801805A8[] = {4, 1, 4, 2, 0, 0, 0, 0};
u8 D_801805B0[] = {4, 0, 4, 0, 0, 0, 0, 0};

u8* g_eBreakableAnimations[] = {
    /* 5B8 */ D_801805A8,
    /* 5BC */ D_801805B0,
    /* 5C0 */ 0,
    /* 5C4 */ 0,
    /* 5C8 */ 0,
    /* 5CC */ 0,
    /* 5D0 */ 0,
    /* 5D4 */ 0,
};

u8 g_eBreakableHitboxes[] = {
    /* 5D8 */ 8,
    /* 5D9 */ 8,
    /* 5DA */ 0,
    /* 5DB */ 0,
    /* 5DC */ 0,
    /* 5DD */ 0,
    /* 5DE */ 0,
    /* 5DF */ 0,
};

// g_eBreakableExplosionTypes moved

u16 g_eBreakableanimSets[] = {
    /* 5E8 */ 3,
    /* 5EA */ 3,
    /* 5EC */ 0,
    /* 5EE */ 0,
    /* 5F0 */ 0,
    /* 5F2 */ 0,
    /* 5F4 */ 0,
    /* 5F6 */ 0,
};

// shorter than psx version
u8 g_eBreakableDrawModes[] = {
    /* 5F8 */ 0x70,
    /* 5F9 */ 0x30,
    /* 5FA */ 0x00,
    /* 5FB */ 0x00,
    /* 5FC */ 0x00,
    /* 5FD */ 0x00,
    /* 5FE */ 0x00,
    /* 5FF */ 0x00};