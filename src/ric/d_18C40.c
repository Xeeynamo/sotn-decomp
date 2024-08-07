#include "ric.h"

u8 D_80154C40[] = {0x30, 0x3F, 0x20, 0x2F, 0x10, 0x1E, 0x10, 0x3F,
                   0x1F, 0x1F, 0x30, 0x30, 0x10, 0x2F, 0x00, 0x00};

u16 D_80154C50[] = {0x0000, 0xFFFC, 0xFFF8, 0xFFF4, 0xFFF0, 0xFFEC};

s32 D_80154C5C[] = {0xFFFFD000, 0xFFFFC000, 0xFFFFA000,
                    0xFFFF8000, 0xFFFF6000, 0xFFFF4000};

u16 D_80154C74[] = {0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080};

AnimationFrame D_80154C80[] = {
    0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0003, 0x0001, 0x0004, 0x0001,
    0x0005, 0x0001, 0x0006, 0x0001, 0x0007, 0x0001, 0x0008, 0x0001, 0x0009,
    0x0001, 0x000A, 0x0001, 0x000B, 0x0001, 0x000C, 0x0001, 0x000D, 0x0001,
    0x000E, 0x0001, 0x000F, 0x0001, 0x0010, 0x0001, 0x0011, 0x0001, 0x0012,
    0x0001, 0x0013, 0x0001, 0x0014, 0x0001, 0x0015, 0x0001, 0x0016, 0x0001,
    0x0017, 0x0001, 0x0018, 0xFFFF, 0x0000,
};

u8 D_80154CE4[] = {0x02, 0x09, 0x03, 0x0A, 0x01, 0x08, 0x04, 0x0B,
                   0x00, 0x07, 0x05, 0x0C, 0x06, 0x0D, 0x00, 0x00};

u8 D_80154CF4[] = {0x02, 0x09, 0x03, 0x0A, 0x04, 0x0B,
                   0x05, 0x0C, 0x06, 0x0D, 0x00, 0x00};

unkStr_8011E4BC D_80154D00 = {
    0x08, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};

unkStr_8011E4BC D_80154D10 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0001, 0x0C800000};

unkStr_8011E4BC D_80154D20 = {
    0x08, 0x7F, 0x7F, 0x7F, 0x02, 0x02, 0x0002, 0x0033, 0x0000, 0x08800000};

unkStr_8011E4BC D_80154D30 = {
    0x06, 0x7F, 0xFF, 0xFF, 0x01, 0x01, 0x0004, 0x0073, 0x0003, 0x08800000};

unkStr_8011E4BC D_80154D40 = {
    0x0C, 0xC0, 0x60, 0x00, 0x01, 0x01, 0x0004, 0x0033, 0x0003, 0x08800000};

unkStr_8011E4BC D_80154D50 = {
    0x0C, 0x7F, 0x00, 0x00, 0x03, 0x03, 0x0002, 0x0002, 0x0004, 0x0C800000};

unkStr_8011E4BC D_80154D60 = {
    0x08, 0x1F, 0x1F, 0x7F, 0x01, 0x01, 0x0004, 0x0033, 0x0006, 0x0C800000};

unkStr_8011E4BC D_80154D70 = {
    0x14, 0x7F, 0x7F, 0xC0, 0x01, 0x01, 0xFFFE, 0x0033, 0x0007, 0x0C800000};

unkStr_8011E4BC D_80154D80 = {
    0x06, 0xC0, 0xC0, 0xC0, 0x02, 0x02, 0x0002, 0x007B, 0x0008, 0x08800000};

unkStr_8011E4BC D_80154D90 = {
    0x10, 0x7F, 0x7F, 0x7F, 0x01, 0x01, 0x0002, 0x0033, 0x0009, 0x08800000};

unkStr_8011E4BC* D_80154DA0[] = {
    &D_80154D00, &D_80154D10, &D_80154D20, &D_80154D30, &D_80154D40,
    &D_80154D50, &D_80154D60, &D_80154D70, &D_80154D80, &D_80154D90};

AnimationFrame D_80154DC8[] = {
    0x0002, 0x0001, 0x0002, 0x0002, 0x0002, 0x0003, 0x0002, 0x0004,
    0x0002, 0x0005, 0x0002, 0x0004, 0x0002, 0x0003, 0x0002, 0x0004,
    0x0002, 0x0003, 0x0002, 0x0004, 0x0002, 0x0005, 0x0001, 0x0006,
    0x0001, 0x0007, 0x0001, 0x0008, 0xFFFF, 0x0000,
};

AnimationFrame D_80154E04[] = {
    0x0001, 0x0009, 0x0002, 0x000A, 0x0002, 0x000B, 0x0002, 0x000C, 0x0002,
    0x000D, 0x0002, 0x000E, 0x0002, 0x000F, 0x0002, 0x0010, 0x0002, 0x0011,
    0x0002, 0x0012, 0x0003, 0x0013, 0x0004, 0x0014, 0xFFFF, 0x0000,
};

AnimationFrame D_80154E38[] = {
    0x0002, 0x0001, 0x0002, 0x0002, 0x0002, 0x0003, 0x0002, 0x0004, 0x0002,
    0x0005, 0x0002, 0x0006, 0x0002, 0x0007, 0x0002, 0x0008, 0xFFFF, 0x0000,
};

unkStr80154E5C D_80154E5C[] = {
    {
        0xFFC0,
        0x0000,
        0x00028000,
        0x00000000,
        0x0060,
        0x001B,
        0x0118,
        0x80,
        0x00,
    },
    {
        0x0040,
        0x0000,
        0xFFFD8000,
        0x00000000,
        0x0048,
        0x001B,
        0x0119,
        0x00,
        0x80,
    },
    {
        0x0000,
        0xFFC0,
        0x00000000,
        0x00028000,
        0x0030,
        0x0019,
        0x011A,
        0x00,
        0x00,
    },
    {
        0x0000,
        0x0040,
        0x00000000,
        0xFFFD8000,
        0x0018,
        0x0019,
        0x011B,
        0x80,
        0x00,
    },
};

s16 D_80154EAC[] = {
    0x016E,
    0x0161,
    0x0160,
    0x0162,
};

s32 D_80154EB4[] = {
    0x0001AAAA,
    0xFFFE5556,
    0x00005555,
    0xFFFF2AAB,
};

s32 D_80154EC4[] = {
    0xFFFE0000,
    0xFFFE5556,
    0xFFFD0000,
    0xFFFDAAAB,
};

s32 D_80154ED4[] = {
    0x00010004, 0x00020004, 0x00030004, 0x00040004, 0x00050004,
    0x00060004, 0x00070004, 0x00080004, 0x00000000,
};

AnimationFrame D_80154EF8[] = {
    0x0008, 0x0009, 0x0008, 0x000D, 0x0040, 0x000A, 0x0002, 0x000B, 0x0002,
    0x000C, 0x0006, 0x000D, 0x0007, 0x000E, 0x0006, 0x000F, 0x0005, 0x000E,
    0x0004, 0x000D, 0x0003, 0x000F, 0x0003, 0x000E, 0x0003, 0x000D, 0x0003,
    0x000E, 0x0003, 0x000F, 0x0003, 0x000E, 0x0003, 0x000D, 0x0004, 0x000E,
    0x0005, 0x000F, 0x0006, 0x000E, 0x0007, 0x000D, 0x0030, 0x000E, 0x000C,
    0x0009, 0x000D, 0x0010, 0x0008, 0x0011, 0x000C, 0x0012, 0x00B0, 0x0013,
    0x000A, 0x0014, 0x000A, 0x0015, 0x000A, 0x0016, 0x0030, 0x0017, 0x00D0,
    0x0018, 0xFFFF, 0x0000,
};

s32 D_80154F7C[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

s16 D_80154FBC[][10] = {
    0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x0100, 0x0100, 0x0060, 0x0031,
    0x0200, 0x0000, 0x0002, 0x0006, 0x015F, 0x0100, 0x0100, 0x0100, 0x0040,
    0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x7000, 0x7000,
    0x0040, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x7000,
    0x0200, 0x0010, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0100,
    0x7000, 0x7000, 0x0010, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F,
    0x0100, 0x7000, 0x0200, 0x7000, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000,
    0x015F, 0x0100, 0x7000, 0x0100, 0x7002, 0x0031, 0x0100, 0x0000, 0x0000,
    0x0000, 0x015F, 0x0100, 0x0100, 0x7000, 0x0070, 0x0031, 0x0200, 0x0000,
    0x0000, 0x0000, 0x015F, 0x0100, 0x7000, 0x0200, 0x7006, 0x0031, 0x0200,
    0x0000, 0x0000, 0x0000, 0x015F, 0x0200, 0x0200, 0x0400, 0x7001, 0x0031,
    0x0200, 0x0000, 0x0000, 0x0000, 0x0166, 0x0100, 0x0100, 0x0100, 0x7005,
    0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x0102, 0x0100, 0x7000, 0x7000,
    0x0040, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x7100,
    0x0100, 0x7005, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0100,
    0x0100, 0x0100, 0x7005, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x0102,
    0x0100, 0x7000, 0x0200, 0x0040, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000,
    0x0102, 0x0100, 0x7000, 0x0100, 0x0040, 0x0031, 0x0200, 0x0000, 0x0000,
    0x0000, 0x0102, 0x0100, 0x0100, 0x7000, 0x0000, 0x0031, 0x0200, 0x0000,
    0x0000, 0x0000, 0x0102, 0x0400, 0x0100, 0x0400, 0x0000, 0x0031, 0x0200,
    0x0000, 0x0000, 0x0000, 0x015F, 0x0100, 0x0100, 0x7000, 0x0000, 0x0031,
    0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x0200, 0x0800, 0x0800, 0x7007,
    0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x0102, 0x0100, 0x0100, 0x0100,
    0x0000, 0x0031, 0x0200, 0x0000, 0x0000, 0x0000, 0x015F, 0x00C0, 0x00C0,
    0x0100, 0x0010, 0x0031, 0x0200, 0x0008, 0x0000, 0x0008, 0x0165, 0x0100,
    0x0100, 0x0100, 0x7007, 0x0051, 0x0200, 0x0000, 0x0000, 0x0000, 0x0168,
    0x7100, 0x7100, 0x0200, 0x7007, 0x0031, 0x0200,
};

Point16 D_8015519C[] = {
    {0, 0},         {256, 256},   {256, 256},   {1280, 2560}, {256, 256},
    {256, 0},       {0, 0},       {256, 28672}, {28672, 512}, {0, 0},
    {28928, 28928}, {256, 4096},  {0, 0},       {28928, 256}, {28672, 2048},
    {0, 0},         {256, 28928}, {256, 1024},  {1280, 2560}, {256, 256},
    {256, 256},     {1280, 2560}, {256, 512},   {28928, 256}, {-2, -24},
    {0, -8},        {2, 8},       {0, 24},      {6, -12},     {8, 0},
    {7, 12},        {-8, -12},    {-9, 0},      {-7, 12},     {-14, -6},
    {-15, 7},       {13, -7},     {16, 8},      {-7, -22},    {6, -21},
    {-8, 21},       {7, 22}};

Point16* D_80155244[] = {
    &D_8015519C[0x18], // + 0x60
    &D_8015519C[0x1C], // + 0x70
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x1C], // + 0x70
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x1E], // + 0x78
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x1E], // + 0x78
    &D_8015519C[0x1B], // + 0x6C
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x1B], // + 0x6C
    &D_8015519C[0x21], // + 0x84
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x21], // + 0x84
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x1A], // + 0x68
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x1F], // + 0x7C
    &D_8015519C[0x19], // + 0x64
    &D_8015519C[0x1F], // + 0x7C
    &D_8015519C[0x18], // + 0x60
    &D_8015519C[0x1C], // + 0x70
    &D_8015519C[0x24], // + 0x90
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x24], // + 0x90
    &D_8015519C[0x25], // + 0x94
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x25], // + 0x94
    &D_8015519C[0x1E], // + 0x78
    &D_8015519C[0x1D], // + 0x74
    &D_8015519C[0x1F], // + 0x7C
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x22], // + 0x88
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x23], // + 0x8C
    &D_8015519C[0x22], // + 0x88
    &D_8015519C[0x20], // + 0x80
    &D_8015519C[0x21], // + 0x84
    &D_8015519C[0x23], // + 0x8C
    &D_8015519C[0x18], // + 0x60
    &D_8015519C[0x1F], // + 0x7C
    &D_8015519C[0x26], // + 0x98
    &D_8015519C[0x18], // + 0x60
    &D_8015519C[0x27], // + 0x9C
    &D_8015519C[0x1C], // + 0x70
    &D_8015519C[0x1B], // + 0x6C
    &D_8015519C[0x28], // + 0xA0
    &D_8015519C[0x21], // + 0x84
    &D_8015519C[0x1E], // + 0x78
    &D_8015519C[0x29], // + 0xA4
    &D_8015519C[0x1B], // + 0x6C
    &D_8015519C[0x26], // + 0x98
    &D_8015519C[0x1F], // + 0x7C
    &D_8015519C[0x22], // + 0x88
    &D_8015519C[0x27], // + 0x9C
    &D_8015519C[0x24], // + 0x90
    &D_8015519C[0x1C], // + 0x70
    &D_8015519C[0x23], // + 0x8C
    &D_8015519C[0x21], // + 0x84
    &D_8015519C[0x28], // + 0xA0
    &D_8015519C[0x25], // + 0x94
    &D_8015519C[0x29], // + 0xA4
    &D_8015519C[0x1E], // + 0x78
};

s16 D_80155364[] = {
    0x0194,
    0x0199,
};

s32 D_80155368[] = {255, 255, 255, 127, 127, 63, 127, 63, 127};

AnimationFrame* D_8015538C[] = {
    D_801553BC,
    D_801553BC,
};

AnimationFrame D_80155394[2] = {
    0x0040,
    0x0226,
};

AnimationFrame D_8015539C[] = {
    0x0002, 0x0237, 0x0001, 0x0290, 0x0002, 0x0291, 0x0003, 0x0290,
    0x0004, 0x0291, 0x000C, 0x0290, 0x0004, 0x0210, 0xFFFE, 0x0001,
};

AnimationFrame D_801553BC[] = {
    0x0007, 0x0201, 0x0007, 0x0202, 0x0007, 0x0203, 0x0007, 0x0202, 0x0007,
    0x0201, 0x0007, 0x0202, 0x0007, 0x0203, 0x0007, 0x0202, 0x0007, 0x0201,
    0x0007, 0x0202, 0x0007, 0x0203, 0x0007, 0x0202, 0x0007, 0x0201, 0x0007,
    0x0202, 0x0007, 0x0203, 0x0007, 0x0202, 0x0007, 0x0201, 0x0007, 0x0202,
    0x0007, 0x0203, 0x0007, 0x0202, 0x0008, 0x0201, 0x0008, 0x0202, 0x0008,
    0x0203, 0x0008, 0x0202, 0x0009, 0x0201, 0x0009, 0x0202, 0x0009, 0x0203,
    0x0009, 0x0202, 0x000A, 0x0201, 0x000A, 0x0202, 0x000A, 0x0203, 0x000A,
    0x0202, 0x000B, 0x0201, 0x000B, 0x0202, 0x000B, 0x0203, 0x000B, 0x0202,
    0x000C, 0x0201, 0x000C, 0x0202, 0x000D, 0x0203, 0x000D, 0x0202, 0x000F,
    0x0201, 0x000F, 0x0202, 0x000F, 0x0203, 0x0080, 0x0202, 0x0004, 0x0204,
    0x0004, 0x0205, 0x0004, 0x0206, 0x0040, 0x0207, 0xFFFF, 0x0000,
};

AnimationFrame D_80155480[2] = {
    0x0040,
    0x0207,
};

AnimationFrame D_80155488[] = {
    0x0003, 0x0208, 0x0006, 0x0209, 0x0005, 0x020A, 0x0006,
    0x020B, 0x0007, 0x020C, 0x0006, 0x020D, 0x0005, 0x020E,
    0x0006, 0x020F, 0x0004, 0x0208, 0x0000, 0x0000,
};
