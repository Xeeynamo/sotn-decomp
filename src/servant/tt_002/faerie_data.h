// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>

static ItemPrimitiveParams g_ItemPrimitiveParams[] = {
    {0x80, 0x01, 1, 0, 1, 1, 0x7F, 0x7F, 0x7F, 1,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 1, 2, 2, 0x7F, 0x7F, 0x7F, 2, DRAW_UNK02, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x2F, 0xFF, 0x2F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x5F, 0x0F, 0x5F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x7F, 0x3F, 0x0F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0xFF, 0x7F, 0x1F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x7F, 0x7F, 0x0F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x0F, 0x0F, 0x7F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x0F, 0xFF, 0x2F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x7F, 0x3F, 0x3F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
    {0x20, 0x20, 0, 2, 1, 1, 0x3F, 0x3F, 0x3F, 2,
     DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP, 0,
     FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS},
};

AnimationFrame D_us_80172600[] = {{1, 1}, {0, 0}};
AnimationFrame D_us_80172608[] = {{1, 112}, {0, 0}};
AnimationFrame D_us_80172610[] = {{1, 113}, {0, 0}};
AnimationFrame D_us_80172618[] = {{1, 114}, {1, 1}, {1, 115}, {1, 1}, {0, 0}};
AnimationFrame D_us_8017262C[] = {{1, 112}, {1, 1}, {1, 113}, {1, 1}, {0, 0}};
AnimationFrame D_us_80172640[] = {{1, 116}, {1, 1}, {1, 117}, {1, 1}, {0, 0}};
AnimationFrame D_us_80172654[] = {{2, 19}, {2, 20}, {0, 0}};
AnimationFrame D_us_80172660[] = {
    {2, 14},  {2, 118}, {2, 14},  {2, 118}, {2, 21},
    {2, 119}, {2, 21},  {2, 119}, {6, 18},  {0, 0}};
AnimationFrame D_us_80172688[] = {
    {9, 18}, {2, 21},  {2, 119}, {2, 21},  {2, 119},
    {2, 14}, {2, 118}, {2, 14},  {2, 118}, {-2, 43}};
AnimationFrame D_us_801726B0[] = {
    {2, 21}, {2, 119}, {2, 120}, {2, 22}, {2, 121},
    {2, 23}, {2, 122}, {2, 24},  {0, 0}};
AnimationFrame D_us_801726D4[] = {{1, 62}, {1, 22}, {1, 63}, {1, 24}, {0, 0}};
AnimationFrame D_us_801726E8[] = {
    {2, 52}, {2, 53}, {2, 54}, {2, 55}, {2, 56}, {2, 57}, {0, 0}};
AnimationFrame D_us_80172704[] = {{3, 92}, {3, 93}, {3, 94}, {3, 95}, {0, 0}};
AnimationFrame D_us_80172718[] = {
    {4, 97}, {4, 96}, {4, 75}, {4, 100}, {4, 99}, {4, 98}, {0, 0}};
AnimationFrame D_us_80172734[] = {{6, 2}, {6, 3}, {6, 4}, {6, 5}, {0, 0}};
AnimationFrame D_us_80172748[] = {{6, 6},  {6, 7},  {5, 8},  {5, 9},  {4, 10},
                                  {4, 11}, {4, 12}, {4, 13}, {-2, 16}};
AnimationFrame D_us_8017276C[] = {{4, 14}, {4, 15}, {4, 16}, {4, 17}, {0, 0}};
AnimationFrame D_us_80172780[] = {{10, 77}, {6, 78}, {8, 79}, {0, 0}};
AnimationFrame D_us_80172790[] = {
    {4, 18},  {2, 21},  {1, 119}, {2, 22},  {1, 120}, {2, 23},
    {1, 121}, {2, 24},  {1, 122}, {2, 63},  {2, 25},  {1, 123},
    {1, 26},  {1, 124}, {2, 27},  {2, 125}, {-2, 44}};
AnimationFrame D_us_801727D4[] = {
    {6, 18},  {5, 21}, {2, 119}, {2, 22}, {2, 120}, {2, 23},
    {2, 121}, {2, 24}, {2, 122}, {2, 25}, {2, 123}, {2, 26},
    {2, 124}, {2, 27}, {2, 125}, {-2, 45}};
AnimationFrame D_us_80172814[] = {
    {6, 18}, {5, 21}, {5, 22}, {5, 23}, {5, 24}, {4, 21}, {4, 62},
    {4, 23}, {4, 24}, {3, 21}, {3, 22}, {3, 23}, {3, 24}, {2, 63},
    {2, 22}, {2, 62}, {2, 24}, {2, 62}, {2, 63}, {2, 62}, {2, 63},
    {2, 62}, {2, 63}, {2, 62}, {2, 63}, {2, 62}, {2, 63}, {4, 34},
    {4, 35}, {4, 34}, {4, 35}, {4, 34}, {4, 35}, {-2, 21}};
AnimationFrame D_us_8017289C[] = {
    {6, 25}, {6, 26}, {6, 36}, {8, 37}, {32, 38}, {-1, 0}};
AnimationFrame D_us_801728B4[] = {
    {10, 84}, {1, 102}, {6, 103}, {1, 105}, {1, 104}, {1, 105}, {1, 104},
    {1, 105}, {1, 104}, {1, 105}, {6, 103}, {1, 102}, {0, 0}};
AnimationFrame D_us_801728E8[] = {{4, 34}, {4, 23}, {17, 39}, {7, 40}, {6, 41},
                                  {4, 42}, {6, 43}, {6, 101}, {-2, 14}};
AnimationFrame D_us_8017290C[] = {{1, 46}, {0, 0}};
AnimationFrame D_us_80172914[] = {
    {18, 45}, {11, 46}, {18, 47}, {11, 46}, {0, 0}};
AnimationFrame D_us_80172928[] = {
    {35, 47}, {27, 48}, {35, 49}, {27, 48}, {0, 0}};
AnimationFrame D_us_8017293C[] = {
    {1, 44}, {2, 50}, {2, 51}, {2, 50}, {2, 51}, {2, 50},
    {3, 52}, {3, 53}, {3, 54}, {3, 55}, {3, 56}, {3, 57},
    {6, 59}, {6, 60}, {6, 61}, {6, 58}, {-1, 0}};
AnimationFrame D_us_80172980[] = {{5, 59}, {5, 60}, {5, 61}, {0, 0}};
AnimationFrame D_us_80172990[] = {{1, 74}, {0, 0}};
AnimationFrame D_us_80172998[] = {{4, 96}, {0, 0}};
AnimationFrame D_us_801729A0[] = {{6, 80}, {6, 85}, {6, 90}, {6, 91}, {0, 0}};
AnimationFrame D_us_801729B4[] = {
    {3, 88},  {2, 89},  {1, 90}, {1, 106}, {1, 107}, {3, 108},
    {2, 107}, {1, 106}, {1, 90}, {1, 89},  {0, 0}};
AnimationFrame D_us_801729E0[] = {{6, 80}, {6, 81}, {6, 82}, {6, 83}, {0, 0}};
AnimationFrame D_us_801729F4[] = {{6, 84}, {6, 85}, {6, 86}, {6, 87}, {0, 0}};
AnimationFrame D_us_80172A08[] = {{8, 88}, {8, 89}, {8, 90}, {8, 91}, {0, 0}};
AnimationFrame D_us_80172A1C[] = {
    {6, 26}, {6, 27}, {6, 28}, {6, 29}, {24, 30}, {-1, 0}};
AnimationFrame D_us_80172A34[] = {
    {6, 26}, {6, 80}, {6, 109}, {6, 110}, {24, 111}, {-1, 0}};
AnimationFrame D_us_80172A4C[] = {
    {6, 64}, {6, 65}, {6, 66}, {6, 67}, {7, 68}, {8, 69},
    {8, 70}, {7, 71}, {7, 72}, {7, 73}, {-2, 14}};
AnimationFrame D_us_80172A78[] = {
    {2, 52}, {2, 53}, {2, 54}, {2, 55}, {2, 56}, {2, 57}, {0, 0}};
AnimationFrame D_us_80172A94[] = {{5, 59}, {5, 60}, {5, 61}, {0, 0}};
AnimationFrame D_us_80172AA4[] = {{4, 13}, {4, 12}, {4, 11}, {4, 10}, {5, 9},
                                  {5, 8},  {6, 7},  {6, 6},  {-2, 14}};
AnimationFrame D_us_80172AC8[] = {{5, 4}, {6, 3}, {6, 2}, {9, 6}, {0, 0}};
AnimationFrame D_us_80172ADC[] = {{7, 6}, {6, 2}, {7, 3}, {9, 4}, {0, 0}};
AnimationFrame D_us_80172AF0[] = {{6, 28}, {6, 29}, {38, 30}, {-1, 0}};
AnimationFrame D_us_80172B00[] = {{7, 31}, {7, 32}, {37, 33}, {-1, 0}};

STATIC_PAD_DATA(4);

AnimationFrame* g_FaerieAnimationFrames[] = {
    D_us_80172600, D_us_80172608, D_us_80172610, D_us_80172618, D_us_8017262C,
    D_us_80172640, D_us_80172654, D_us_80172660, D_us_80172688, D_us_801726B0,
    D_us_801726D4, D_us_801726E8, D_us_80172704, D_us_80172718, D_us_80172734,
    D_us_80172748, D_us_8017276C, D_us_80172780, D_us_80172790, D_us_801727D4,
    D_us_80172814, D_us_8017289C, D_us_801728B4, D_us_801728E8, D_us_8017290C,
    D_us_80172914, D_us_80172928, D_us_8017293C, D_us_80172980, D_us_80172990,
    D_us_80172998, D_us_801729A0, D_us_801729B4, D_us_801729E0, D_us_801729F4,
    D_us_80172A08, D_us_80172A1C, D_us_80172A34, D_us_80172A4C, D_us_80172A78,
    D_us_80172A94, D_us_80172AA4, D_us_80172AC8, D_us_80172ADC, D_us_80172AF0,
    D_us_80172B00,
};

FaerieSfx g_FaerieSfx = {
    SFX_FAERIE_HEALING,     SFX_FAERIE_POTION, SFX_FAERIE_REGENERATION,
    SFX_FAERIE_NO_MEDICINE, SFX_FAERIE_OH_NO,  SFX_FAERIE_ARE_YOU_OK};

s32 g_SfxRandomizerHammerResist[] = {
    0x3F, SFX_FAERIE_HAMMER_A, 0x7F, SFX_FAERIE_HAMMER_B,
    0xBF, SFX_FAERIE_HAMMER_C, 0xFF, SFX_FAERIE_HAMMER_D};

static s32 g_SfxRandomizerGrunt[] = {
    0x3F, SFX_FAERIE_FALL_OFF_A, 0x7F, SFX_FAERIE_FALL_OFF_B,
    0xBF, SFX_FAERIE_FALL_OFF_C, 0xFF, SFX_FAERIE_FALL_OFF_D};

static ServantSfxEventDesc s_IntroEventLifeVO[] = {
    {0, 34, FAERIE_INTRO_LIFE}, {-1, 14, 0}};
static ServantSfxEventDesc s_IntroEventCommandVO[] = {
    {0, 34, FAERIE_INTRO_COMMAND}, {-1, 14, 0}};
s32* g_FaerieIntroRandomizer[] = {(s32*)0x7F, (s32*)s_IntroEventLifeVO,
                                  (s32*)0xFF, (s32*)s_IntroEventCommandVO};

static ServantSfxEventDesc s_SfxEventLetsGo[] = {
    {0, 38, FAERIE_LETS_GO}, {-1, 14, 0}};
static ServantSfxEventDesc s_SfxEventFollow[] = {
    {0, 38, FAERIE_FOLLOW}, {-1, 14, 0}};
s32* g_SfxEventRandomizer[] = {
    (s32*)0x7F, (s32*)s_SfxEventLetsGo, (s32*)0xFF, (s32*)s_SfxEventFollow};

static ServantSfxEventDesc s_DarknessHint[] = {
    {0, 14, FAERIE_DARKNESS_HINT}, {-1, 14, 0}};
static ServantSfxEventDesc s_MistHint[] = {
    {0, 14, FAERIE_MIST_HINT}, {-1, 14, 0}};
static ServantSfxEventDesc s_WallHint1[] = {
    {0, 37, FAERIE_WALL_HINT}, {-1, 14, 0}};
static ServantSfxEventDesc s_SuspiciousHint[] = {
    {0, 36, FAERIE_SUSPICIOUS_HINT}, {-1, 14, 0}};
static ServantSfxEventDesc s_WallHint2[] = {
    {0, 36, FAERIE_WALL_HINT}, {-1, 14, 0}};
static s32* g_FaerieHints[] = {
    (s32*)-1,  (s32*)-1,  (s32*)s_DarknessHint,
    (s32*)-1,  (s32*)-1,  (s32*)s_MistHint,
    (s32*)88,  (s32*)184, (s32*)s_WallHint1,
    (s32*)32,  (s32*)128, (s32*)s_SuspiciousHint,
    (s32*)56,  (s32*)128, (s32*)s_WallHint2,
    (s32*)128, (s32*)208, (s32*)s_WallHint1,
    (s32*)208, (s32*)112, (s32*)s_WallHint2,
    (s32*)160, (s32*)128, (s32*)s_SuspiciousHint,
    (s32*)208, (s32*)120, (s32*)s_WallHint2,
    (s32*)48,  (s32*)128, (s32*)s_SuspiciousHint,
};
