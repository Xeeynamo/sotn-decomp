// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dra.h"
#include "dra_bss.h"

u16 D_800AD4CC[] = {
    0x0200, 0x0600, 0x0800, 0x0800, 0x0800,
    0x0200, 0x0200, 0x0200, 0x0200, 0xFFFF,
};

u16 D_800AD4E0[] = {
    0x0200, 0x0A00, 0x0C00, 0x0C00, 0x0C00, 0x0A00, 0x0200, 0x0200, 0xFFFF,
};

u16 D_800AD4F4[] = {
    0x0E00, 0x1000, 0x1000, 0x1000, 0x0E00, 0xFFFF,
};

u16 D_800AD500[] = {
    0x1200, 0x1400, 0x1400, 0x1400, 0x1200, 0xFFFF,
};

u16 D_800AD50C[] = {
    0x0200, 0x1600, 0x0200, 0x0200, 0x0200,
    0x0200, 0x0200, 0x0200, 0x0200, 0xFFFF,
};

u16* D_800AD520[] = {
    D_800AD4CC, D_800AD4CC, D_800AD4E0, D_800AD4E0,
    D_800AD4F4, D_800AD500, D_800AD50C,
};

extern s8 D_800B0188[];
// TODO: move to 7A4D0.c
WeaponAnimation D_800AD53C[] = {
    {D_800AD520, D_800B0188, 0x0000, SFX_WEAPON_SWISH_C, 0x24, 1},
};

s16 D_800AD54C[] = {
    0, -4, -8, -12, -16, -20,
};

s32 D_800AD558[] = {
    -0x3000, -0x4000, -0x6000, -0x8000, -0xA000, -0xC000,
};

s16 D_800AD570[] = {
    0x30, 0x40, 0x50, 0x60, 0x70, 0x80,
};

AnimationFrame D_800AD57C[] = {
    {0x0001, 0x0001}, {0x0001, 0x0002}, {0x0001, 0x0003}, {0x0001, 0x0004},
    {0x0001, 0x0005}, {0x0001, 0x0006}, {0x0001, 0x0007}, {0x0001, 0x0008},
    {0x0001, 0x0009}, {0x0001, 0x000A}, {0x0001, 0x000B}, {0x0001, 0x000C},
    {0x0001, 0x000D}, {0x0001, 0x000E}, {0x0001, 0x000F}, {0x0001, 0x0010},
    {0x0001, 0x0011}, {0x0001, 0x0012}, {0x0001, 0x0013}, {0x0001, 0x0014},
    {0x0001, 0x0015}, {0x0001, 0x0016}, {0x0001, 0x0017}, {0x0001, 0x0018},
    {0xFFFF, 0x0000},
};

u8 D_800AD5E0[NUM_VERTICAL_SENSORS * 2] = {
    0x02, 0x09, 0x03, 0x0A, 0x01, 0x08, 0x04,
    0x0B, 0x00, 0x07, 0x05, 0x0C, 0x06, 0x0D,
};

u8 D_800AD5F0[] = {
    0x02, 0x09, 0x03, 0x0A, 0x04, 0x0B, 0x05, 0x0C, 0x06, 0x0D,
};

AnimationFrame D_800AD5FC[] = {
    {0x0001, 0x0009}, {0x0002, 0x000A}, {0x0002, 0x000B}, {0x0002, 0x000C},
    {0x0002, 0x000D}, {0x0002, 0x000E}, {0x0002, 0x000F}, {0x0002, 0x0010},
    {0x0002, 0x0011}, {0x0002, 0x0012}, {0x0003, 0x0013}, {0x0004, 0x0014},
    {0xFFFF, 0x0000},
};

// This is BSS on PSP.
#ifndef VERSION_PSP
s32 D_800AD630[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
#endif

s16 D_800AD670[42][10] = {
    {0, 0, 0, 351, 256, 256, 256, 96, 49, 512},
    {0, 2, 6, 351, 256, 256, 256, 16, 49, 512},
    {0, 0, 0, 351, 256, 1024, 1024, 16, 49, 512},
    {0, 0, 0, 351, 28928, 256, 28672, 16, 49, 512},
    {0, 0, 0, 351, 28928, 28672, 256, 16, 49, 512},
    {0, 0, 0, 351, 256, 28672, 512, 16, 49, 512},
    {0, 0, 0, 351, 256, 28672, 256, 28673, 49, 256},
    {0, 0, 0, 351, 256, 256, 28672, 112, 49, 512},
    {0, 0, 0, 259, 512, 512, 128, 96, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 16, 49, 512},
    {0, 2, 6, 351, 256, 256, 256, 96, 49, 512},
    {0, 0, 0, 351, 256, 28672, 256, 16, 49, 512},
    {0, 0, 0, 351, 28928, 256, 28672, 16, 49, 512},
    {0, 0, 0, 351, 28928, 28672, 256, 16, 49, 512},
    {0, 0, 0, 351, 1024, 256, 1024, 28676, 49, 512},
    {0, 0, 0, 351, 256, 28672, 512, 28678, 49, 512},
    {0, 0, 0, 351, 256, 256, 28672, 16, 49, 512},
    {0, 0, 0, 259, 29696, 128, 29696, 96, 49, 512},
    {0, 0, 0, 351, 512, 256, 1024, 28675, 49, 512},
    {0, 0, 0, 358, 256, 256, 256, 28677, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 16, 49, 512},
    {0, 0, 0, 351, 192, 192, 256, 16, 49, 512},
    {8, 0, 4, 360, 256, 256, 256, 28674, 81, 256},
    {0, 2, 9, 357, 256, 256, 256, 28672, 81, 384},
    {0, 0, 0, 351, 512, 2048, 2048, 28679, 49, 512},
    {0, 0, 0, 351, 512, 256, 512, 28677, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28677, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28680, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28681, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28682, 49, 512},
    {0, 0, 0, 351, 256, 256, 28672, 16, 49, 512},
    {0, 0, 0, 351, 1024, 256, 1024, 16, 49, 512},
    {0, 0, 0, 256, 64, 64, 64, 16, 49, 512},
    {0, 0, 0, 256, 64, 64, 64, 16, 49, 512},
    {8, 0, 8, 357, 256, 256, 256, 28679, 81, 512},
    {0, 0, 0, 256, 64, 64, 64, 16, 49, 512},
    {0, 0, 0, 256, 64, 64, 64, 16, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28683, 49, 512},
    {0, 0, 0, 259, 256, 256, 256, 16, 49, 512},
    {0, 2, 6, 259, 256, 256, 256, 16, 49, 512},
    {0, 0, 0, 360, 28928, 28928, 512, 28679, 49, 512},
    {0, 0, 0, 351, 256, 256, 256, 28684, 49, 0},
};

s16 D_800AD9B8[24][5] = {
    {0, 255, 255, 259, 49},   // Cyan, MP Refill
    {255, 127, 31, 259, 49},  // Orange, curse attacking effect
    {63, 31, 255, 259, 49},   // Light blue, Agunea
    {0, 63, 31, 259, 49},     // Forest green, no known use
    {63, 63, 63, 259, 49},    // Dark grey, no known use
    {255, 63, 63, 259, 49},   // Coral, no known use
    {31, 63, 127, 259, 49},   // Navy blue, no known use
    {127, 63, 15, 259, 49},   // Brown, no known use
    {255, 127, 31, 259, 49},  // Orange, same as entry 1, no known use
    {127, 127, 15, 259, 49},  // Olive green, no known use
    {15, 15, 127, 259, 49},   // Dark blue, no known use
    {63, 63, 63, 259, 49},    // Dark grey, same as entry 4, no known use
    {127, 15, 127, 259, 49},  // Plum, no known use
    {15, 255, 47, 259, 49},   // Chartreuse, no known use
    {47, 255, 47, 259, 49},   // Lime green, no known use
    {95, 15, 95, 259, 49},    // Eggplant, no known use
    {127, 63, 15, 259, 49},   // Brown, same as entry 7, no known use
    {255, 15, 15, 259, 49},   // Red, Dark Metamorphosis
    {127, 63, 63, 259, 49},   // Mahogany, no known use
    {0, 255, 255, 259, 49},   // Cyan, same as entry 0, no known use
    {255, 63, 63, 259, 49},   // Red, sword warp spell
    {255, 63, 63, 259, 49},   // Red, sword warp spell
    {127, 127, 127, 259, 49}, // Grey, soul steal
    {0, 255, 127, 259, 49},   // Light green, Sword Brothers
};

// clang-format off
#define UNK_FLAGS_GROUP_1 FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED
#define UNK_FLAGS_GROUP_2 FLAG_HAS_PRIMS | FLAG_KEEP_ALIVE_OFFCAMERA
#define UNK_FLAGS_GROUP_3 FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA
static unkStr_8011E4BC D_800ADAA8 = { 8, 0x7F, 0x7F, 0x7F, 2, 2, 2, 51, 0,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADAB8 = {16, 0x7F, 0x7F, 0x7F, 1, 1, 2, 51, 1,   UNK_FLAGS_GROUP_3};
static unkStr_8011E4BC D_800ADAC8 = { 8, 0x7F, 0x7F, 0x7F, 1, 1, 2, 51, 0,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADAD8 = { 8, 0x4F, 0x4F, 0x4F, 1, 1, 4, 2, 2,    UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADAE8 = {10, 0xC0, 0x60, 0x00, 1, 1, 4, 51, 3,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADAF8 = {12, 0x7F, 0x00, 0x00, 3, 3, 2, 0, 4,    UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB08 = {12, 0x3F, 0x3F, 0xFF, 3, 3, 2, 49, 4,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB18 = { 8, 0x3F, 0xF0, 0x3F, 1, 1, 4, 115, 3,  UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB28 = {30, 0x3F, 0x3F, 0x3F, 1, 1, 4, 2, 8,    UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB38 = {16, 0x7F, 0x7F, 0x7F, 1, 1, 2, 51, 9,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB48 = {10, 0xC0, 0xC0, 0x3F, 1, 1, -2, 51, 10, UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB58 = { 4, 0xC0, 0x60, 0x00, 1, 1, 4, 51, 3,   UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB68 = {20, 0xC0, 0xC0, 0x3F, 1, 1, -2, 49, 12, UNK_FLAGS_GROUP_2};
static unkStr_8011E4BC D_800ADB78 = { 6, 0xC0, 0xC0, 0xC0, 2, 2, 2, 123, 13, UNK_FLAGS_GROUP_1};
static unkStr_8011E4BC D_800ADB88 = {20, 0x7F, 0x7F, 0xC0, 1, 1, -2, 51, 12, UNK_FLAGS_GROUP_3};
// clang-format on

static unkStr_8011E4BC* D_800ADB98[] = {
    &D_800ADAA8, &D_800ADAB8, &D_800ADAC8, &D_800ADAD8, &D_800ADAE8,
    &D_800ADAF8, &D_800ADB08, &D_800ADB18, &D_800ADB28, &D_800ADB38,
    &D_800ADB48, &D_800ADB58, &D_800ADB68, &D_800ADB78, &D_800ADB88,
};

// BSS
extern s32 D_8013808C;
extern s32 D_80138090;
extern mistStruct D_80138094[16];
extern s16 D_801381D4;
extern s16 D_801381D8;
extern s16 D_801381DC;
extern s16 D_801381E0;
extern s16 D_801381E4;
extern s16 D_801381E8;
extern s16 D_801381EC;
extern s16 D_801381F0;
extern Primitive D_801381F4[8];
extern s32 D_80138394;
extern s32 D_80138398;

void func_8011E4BC(Entity* self) {
    byte stackpad[0x28];
    FakePrim* tilePrim;
    u8 thickness;
    s16 upperParams;
    s16 playerXpos;
    s16 playerYpos;
    s16 randAngleShift;
    s32 var_a2;
    s16 randVar2;
    s16 twelveShift;
    s16 randVar;
    s16 selfXPos;
    s16 selfYPos;
    unkStr_8011E4BC* temp_s5;
    s32 i;

    upperParams = self->params >> 8;
    temp_s5 = D_800ADB98[upperParams];
    selfXPos = self->posX.i.hi;
    selfYPos = self->posY.i.hi;
    playerXpos = PLAYER.posX.i.hi;
    playerYpos = PLAYER.posY.i.hi;
    switch (self->step) {
    case 0:
        self->primIndex = func_800EDB58(PRIM_TILE_ALT, temp_s5->count + 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = temp_s5->flags;
        switch (upperParams) {
        case 13:
            self->ext.et_8011E4BC.unk7C = 0x100;
            break;
        case 8:
        case 10:
        case 12:
        case 14:
            self->ext.et_8011E4BC.unk7C = 0x3F;
            break;
        case 3:
        case 5:
        case 6:
            self->ext.et_8011E4BC.unk7C = 0x2F;
            break;
        case 4:
        case 7:
        case 11:
            self->ext.et_8011E4BC.unk7C = 0x1F;
            break;
        }
        for (tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex], i = 0; true;
             i++, tilePrim = tilePrim->next) {
            tilePrim->drawMode = temp_s5->drawMode;
            tilePrim->priority = PLAYER.zPriority + temp_s5->priority;
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                break;
            }
            tilePrim->posX.i.hi = selfXPos;
            tilePrim->posY.i.hi = selfYPos;
            tilePrim->posX.i.lo = tilePrim->posY.i.lo = 0;
            switch (temp_s5->unkA) {
            case 0:
                randVar2 = rand() & PSP_RANDMASK;
                randAngleShift = (randVar2 & 1) + 2;
                tilePrim->velocityX.val = (rcos(randVar2) << randAngleShift);
                tilePrim->velocityY.val = -(rsin(randVar2) << randAngleShift);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = (((rand() & 0x1FF) - 0x100) << 8);
                tilePrim->velocityY.val = (((rand() & 0x1FF) - 0x100) << 8);
                break;
            case 2:
                tilePrim->velocityX.val =
                    ((s32)(((rand() & PSP_RANDMASK) * 2) - 0x8000)) >> 1;
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                tilePrim->posX.val += (tilePrim->velocityX.val * 19);
                tilePrim->posY.i.hi = (selfYPos + (rand() & 7)) - 3;
                tilePrim->delay = ((rand() & 0xF) + 0x10);
                break;
            case 8:
                twelveShift = -12;
                if (PLAYER.facingLeft) {
                    twelveShift = -twelveShift;
                }
                tilePrim->velocityX.val =
                    (((rand() & PSP_RANDMASK) * 4) + FIX(-1));
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                tilePrim->posX.val +=
                    ((tilePrim->velocityX.val * 35) + (twelveShift << 16));
                tilePrim->velocityX.val >>= 2;
                // Trying this line happens to fix a ton of stuff, but it's
                // obviously wrong. tilePrim->posY.i.hi = selfYPos - (rand() &
                // 0xFF & 0x1F);
                tilePrim->posY.i.hi = selfYPos - 1 + 1 - (rand() & 0x1F);
                tilePrim->delay = ((rand() & 0x1F) + 0x10);
                break;
            case 3:
                tilePrim->posX.i.hi = (selfXPos + (rand() & 0xF)) - 7;
                tilePrim->posY.i.hi = selfYPos - (rand() & 0x1F);
                tilePrim->velocityY.val = FIX(-0.75) - (rand() & 0x7FFF);
                if (self->ext.et_8011E4BC.parent != NULL) {
                    tilePrim->velocityX.val =
                        self->ext.et_8011E4BC.parent->velocityX;
                }
                tilePrim->delay = ((i * 2) + 0xF);
                break;
            case 4:
                randVar = (rand() & 0x1F);
                tilePrim->posX.i.hi = (selfXPos + randVar) - 0x10;
                randVar = (rand() & 0x1F);
                tilePrim->posY.i.hi = (selfYPos + randVar) - 0x14;
                randVar = rand() & 0x1F;
                tilePrim->velocityX.val = D_801396F8[randVar];
                tilePrim->velocityY.val = D_80139778[randVar];
                break;
            case 10:
                tilePrim->posX.i.hi = playerXpos;
                tilePrim->posY.i.hi = playerYpos;
                tilePrim->velocityY.val = -(((i * i) << 0xC) + FIX(0.25));
                tilePrim->delay = 0x3F;
                break;
            case 12:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                if (i < 10) {
                    tilePrim->velocityY.val =
                        -((i * i * 0x1800) + FIX(1.0 / 8));
                } else {
                    tilePrim->velocityY.val =
                        ((i - 10) * (i - 10) * 0x1800) + FIX(1.0 / 8);
                }
                tilePrim->delay = 0x3F;
                break;
            case 13:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                tilePrim->velocityX.val =
                    (s32)((rand() & PSP_RANDMASK) - FIX(0.25)) >> 1;
                tilePrim->velocityY.val = -((rand() & 0x1FFF) + FIX(0.375));
                tilePrim->timer = i * 4;
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim->r0 = temp_s5->r;
            tilePrim->g0 = temp_s5->g;
            tilePrim->b0 = temp_s5->b;
            tilePrim->w = temp_s5->w;
            tilePrim->h = temp_s5->h;
        }
        self->step++;
        break;
    case 1:
        switch (upperParams) {
        case 10:
            if (PLAYER.step != Player_SpellHellfire) {
                DestroyEntity(self);
                return;
            }
        case 3:
        case 4:
        case 7:
        case 8:
        case 11:
        case 12:
        case 13:
        case 14:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
        case 5:
        case 6:
            if (--self->ext.et_8011E4BC.unk7C == 0) {
                DestroyEntity(self);
                return;
            }
            thickness = 3;
            var_a2 = self->ext.et_8011E4BC.unk7C;
            if (var_a2 < 9) {
                thickness--;
            }
            if (var_a2 < 4) {
                thickness--;
            }
            break;
        }
        for (tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex], i = 0; true;
             i++, tilePrim = tilePrim->next) {
            if (tilePrim->next == NULL) {
                tilePrim->drawMode &= ~DRAW_HIDE;
                tilePrim->y0 = tilePrim->x0 = tilePrim->w = 0;
                return;
            }

            tilePrim->posX.i.hi = tilePrim->x0;
            tilePrim->posY.i.hi = tilePrim->y0;
            switch (temp_s5->unkA) {
            case 0:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->r0 -= 6;
                tilePrim->g0 -= 6;
                tilePrim->b0 -= 6;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 1:
            case 9:
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->velocityY.val += FIX(5.0 / 32.0);
                tilePrim->r0 -= 3;
                tilePrim->g0 -= 3;
                tilePrim->b0 -= 3;
                if (tilePrim->r0 < 8) {
                    DestroyEntity(self);
                    return;
                }
                break;
            case 2:
            case 8:
                if (--tilePrim->delay == 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->velocityY.val += FIX(5.0 / 64.0);
                break;
            case 3:
            case 10:
            case 12:
                tilePrim->posY.val += tilePrim->velocityY.val;
                if (--tilePrim->delay < 0) {
                    tilePrim->drawMode |= DRAW_HIDE;
                }
                break;
            case 4:
                tilePrim->posX.val += tilePrim->velocityX.val;
                tilePrim->posY.val += tilePrim->velocityY.val;
                tilePrim->velocityY.val -= (tilePrim->velocityY.val >> 5);
                if (!(var_a2 & 7)) {
                    tilePrim->velocityX.val >>= 1;
                    tilePrim->velocityY.val >>= 1;
                    if (var_a2 & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                    if (var_a2 == 0x18) {
                        tilePrim->drawMode = DRAW_UNK02;
                    }
                }

                tilePrim->w = tilePrim->h = thickness;
                break;
            case 13:
                if (tilePrim->timer == 0) {
                    tilePrim->drawMode &= ~DRAW_HIDE;
                    tilePrim->r0 -= 1;
                    tilePrim->g0 -= 1;
                    tilePrim->b0 -= 1;
                    tilePrim->posY.val += tilePrim->velocityY.val;
                    tilePrim->posX.val += tilePrim->velocityX.val;
                    if ((D_80097448[0] == 0) ||
                        tilePrim->posY.i.hi <=
                            ((PLAYER.posY.i.hi - D_80097448[0]) + 25)) {
                        tilePrim->drawMode |= DRAW_HIDE;
                    }
                } else {
                    tilePrim->timer--;
                }
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
        }
        break;
    }
}

void func_8011EDA0() {}

// RIC function is func_80161C2C
void func_8011EDA8(Entity* self) {
    s16 paramsLo = self->params & 0xFF;
    s16 paramsHi = (self->params >> 8) & 0xFF;

    switch (self->step) {
    case 0:
        if (paramsHi == 1) {
            self->scaleX = 0xC0;
            self->scaleY = 0xC0;
            self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
            self->animSet = ANIMSET_DRA(2);
            self->anim = D_800ADC10;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (paramsLo & 3) {
                self->anim = D_800ADBD4;
                self->scaleX = 0x120;
                self->scaleY = 0x120;
                self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->anim = D_800AD57C;
                self->palette = PAL_FLAG(PAL_UNK_170);
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_POS_CAMERA_LOCKED;

        if (rand() & 3) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }

        self->posY.i.hi =
            PLAYER.posY.i.hi + PLAYER.hitboxOffY + (rand() & 31) - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->scaleX -= 4;
        self->scaleY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->pose == 8) && (self->anim != D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
            if (!(paramsLo & 1) && (self->poseTimer == 1)) {
                CreateEntFactoryFromEntity(self, FACTORY(BP_4, 4), 0);
            }
        }

        if ((self->pose == 16) && (self->anim == D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
        }

        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// same as RIC/RicEntityHitByDark
void func_8011F074(Entity* self) {
    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_POS_CAMERA_LOCKED;
        self->unk5A = 0x79;
        self->animSet = ANIMSET_DRA(14);
        self->zPriority = PLAYER.zPriority + 2;
        self->palette = PAL_FLAG(PAL_UNK_19F);

        if (D_8013808C & 1) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
        } else {
            self->drawMode = DRAW_TPAGE;
        }
        D_8013808C++;
        self->opacity = 0xFF;
        self->drawFlags = FLAG_DRAW_SCALEX | FLAG_DRAW_SCALEY |
                          FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        self->scaleX = self->scaleY = 0x40;
        self->anim = D_800ADC44;

        self->posY.i.hi += ((rand() % 35) - 15);
        self->posX.i.hi += ((rand() % 20) - 10);
        self->velocityY = FIX(-0.375) - (rand() & 0x3FFF);
        self->step++;
        break;
    case 1:
        if (self->opacity > 16) {
            self->opacity -= 8;
        }
        self->posY.val += self->velocityY;
        self->scaleX += 8;
        self->scaleY += 8;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// effect when player takes lightning damage
void EntityHitByLightning(Entity* self) {
    s16 xBase;
    s16 yBase;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;
    s32 temp_s2;
    s16 temp_s1_2;
    s16 temp_s0;
    s32 i;
    Primitive* prevPrim;
    Primitive* prim;

    if ((self->params & 0xFF00) != 0) {
        if ((++self->ext.hitbylightning.unk9C) > 0xA8) {
            var_s0 = true;
        }
    } else if (PLAYER.step != 10) {
        var_s0 = true;
    }
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 6);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand() & PSP_RANDMASK;
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_800ADC7C[rand() & 1];
            prim->priority = PLAYER.zPriority - 2;
            PGREY(prim, 0) = PGREY(prim, 1) = PGREY(prim, 2) = PGREY(prim, 3) =
                0x80;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_UNK02 | DRAW_TRANSP;
            prim = prim->next;
        }
        if ((PLAYER.velocityY != 0) && (PLAYER.step != 0x10)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 0x10;
        PlaySfx(SFX_MAGIC_SWITCH);
        PlaySfx(SFX_THUNDER_B);
        self->step++;
        break;
    case 1:
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x1FF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = ((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 12;
        // This should probably be * -14 but that doesn't work.
        yOffset =
            -((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * 7 << 1;
        self->posX.val = xOffset + PLAYER.posX.val;
        self->posY.val = yOffset + PLAYER.posY.val;
        if ((self->ext.hitbylightning.unk92) &&
            (g_Player.vram_flag &
             (TOUCHING_L_WALL | TOUCHING_R_WALL | TOUCHING_CEILING))) {
            var_s0 = true;
        }
        if (var_s0) {
            self->ext.hitbylightning.unk90 = (rand() & 0xF) + 0x10;
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbylightning.unk90 == 0) {
            DestroyEntity(self);
            return;
        }
        if (self->ext.hitbylightning.unk94 > 0) {
            self->ext.hitbylightning.unk94--;
        }
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0xFF);
        temp_s2 = rsin(self->ext.hitbylightning.unk80);
        self->ext.hitbylightning.unk80 += self->ext.hitbylightning.unk82;
        xOffset = (((rcos(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 8));
        yOffset = (-((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) *
                   ((rand() % 8) + 0xA)) +
                  self->ext.hitbylightning.unk98;
        self->posX.val = PLAYER.posX.val + xOffset;
        self->posY.val = PLAYER.posY.val + yOffset;
        self->ext.hitbylightning.unk98 -= 0x8000;
        prim = &g_PrimBuf[self->primIndex];
        break;
    }
    xBase = (self->posX.i.hi + (rand() & 7)) - 4;
    yBase = (self->posY.i.hi + (rand() & 0x1F)) - 0x18;
    temp_s1_2 = self->ext.hitbylightning.unk94;
    temp_s1_2 = (temp_s1_2 * rsin(self->ext.hitbylightning.unk80)) >> 0xC;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 5; i++) {
        prevPrim = prim;
        prim = prim->next;
        *prevPrim = *prim;
        prevPrim->next = prim;
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) + 0x90;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) + 0x90;
        prevPrim->v0 = prevPrim->v1 = 0xC0;
        prevPrim->v2 = prevPrim->v3 = 0xCF;
    }
    prim->x0 = prim->x1;
    prim->y0 = prim->y1;
    prim->x2 = prim->x3;
    prim->y2 = prim->y3;
    temp_s0 = self->ext.hitbylightning.unk7C + 0x400;
    prim->x1 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y1 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);
    temp_s0 = self->ext.hitbylightning.unk7C - 0x400;
    prim->x3 = xBase + (((rcos(temp_s0) >> 4) * temp_s1_2) >> 8);
    prim->y3 = yBase - (((rsin(temp_s0) >> 4) * temp_s1_2) >> 8);

    temp_s0 = (self->ext.hitbylightning.unk80 & 0xFFF);
    if (temp_s0 < 0x400) {
        prim->priority = PLAYER.zPriority + 2;
    } else if (temp_s0 < 0xC00) {
        prim->priority = PLAYER.zPriority - 2;
    } else {
        prim->priority = PLAYER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) + 0x90;
    prim->u1 = prim->u3 = (i + 1 << 4) + 0x90;
    prim->v0 = prim->v1 = 0xC0;
    prim->v2 = prim->v3 = 0xCF;
}

// player gets frozen
void EntityHitByIce(Entity* self) {
    s32 i;
    s16 xShift;
    s16 yShift;
    s32 size;
    s16 primYshift;
    s16 selfX;
    s16 selfY;
    Point16* offset;
    bool sp18;

    s16 angle;

    Primitive* prim;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;

    sp18 = false;
    if (!(g_Player.status & PLAYER_STATUS_UNK10000)) {
        sp18 = true;
    }

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
             prim = prim->next) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = (rand() & 0x7F) + 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE2 |
                                 DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            } else {
                prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_TPAGE |
                                 DRAW_COLORS | DRAW_TRANSP;
            }
            prim->type = PRIM_G4;
            prim->priority = PLAYER.zPriority + 2;
        }
        if (PLAYER.velocityY != 0) {
            self->ext.hitbyice.unk7E = 1;
        }
        if (PLAYER.step == Player_Kill) {
            self->ext.hitbyice.unk80 = 1;
            self->ext.hitbyice.unk82 = 0x14;
            self->ext.hitbyice.unk7E = 0;
        }
        if (PLAYER.velocityY != 0) {
            if (PLAYER.facingLeft) {
                self->rotate = 0x100;
            } else {
                self->rotate = -0x100;
            }
        } else {
            if (PLAYER.velocityX > 0) {
                self->rotate = 0x80;
            } else {
                self->rotate = 0xF80;
            }
        }
        PlaySfx(SFX_MAGIC_SWITCH);
        self->step++;
        break;
    case 1:
        if (self->ext.hitbyice.unk80 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        // Could rewrite as a series of && and || but that would probably reduce
        // readability
        if (self->ext.hitbyice.unk7E) {
            if (g_Player.vram_flag & (TOUCHING_L_WALL | TOUCHING_R_WALL)) {
                sp18 = true;
            }
            if (PLAYER.step == Player_Hit && PLAYER.step_s == 5) {
                sp18 = true;
            }
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            PlaySfx(SFX_GLASS_BREAK_B);
            self->step++;
        }
        break;
    case 2:
        if (--self->ext.hitbyice.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    for (prim = &g_PrimBuf[self->primIndex], i = 0; i < 24; prim = prim->next,
        i++) {
        offset = D_800ADCC8[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift;
            prim->y0 = selfY + yShift;

            offset = D_800ADCC8[i * 3 + 1];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift;
            prim->y1 = selfY + yShift;

            offset = D_800ADCC8[i * 3 + 2];
            size = SquareRoot12(
                ((offset->x * offset->x) + (offset->y * offset->y)) << 0xC);
            angle = self->rotate + ratan2(offset->y, offset->x);
            xShift = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift;
            prim->y2 = prim->y3 = selfY + yShift;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->u0++;
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            prim->y0 += primYshift;
            prim->y1 += primYshift;
            prim->y2 += primYshift;
            prim->y3 += primYshift;
            if (prim->r3 < 4) {
                prim->r3 -= 4;
            }
            if (prim->g3 < 4) {
                prim->g3 -= 4;
            }
            if (prim->b3 < 4) {
                prim->b3 -= 4;
            }
            prim->r0 = prim->r1 = prim->r2 = prim->r3;
            prim->b0 = prim->b1 = prim->b2 = prim->b3;
            prim->g0 = prim->g1 = prim->g2 = prim->g3;
            prim->drawMode |= DRAW_UNK02;
            prim->drawMode &= ~(DRAW_UNK_200 | DRAW_UNK_100);
            self->flags |= FLAG_POS_CAMERA_LOCKED;
            self->flags &= ~(FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED);
            if (--prim->v0 == 0) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
    }
}

// Transparent white circle closes over player
// Entity ID #38. Created by blueprint 53. No known callers.
// Near-duplicate of RIC RicEntityShrinkingPowerUpRing.
void EntityTransparentWhiteCircle(Entity* self) {
    bool flag;
    s16 upperparams;
    s16* loadedParams;
    s16 selfX;
    s16 selfY;
    s16 rScale;
    s16 gScale;
    s16 bScale;
    s16 gOffset;
    s16 bOffset;
    s16 sp38;
    s16 base_angle;
    s16 angle;
    s32 i;
    Primitive* prim1;
    Primitive* prim2;

    upperparams = (self->params & 0x7F00) >> 8;
    flag = upperparams & 0x40;

    loadedParams = &D_800ADDE8[upperparams & 0x3F][0];
    rScale = loadedParams[2];
    gScale = loadedParams[3];
    bScale = loadedParams[4];
    gOffset = loadedParams[0];
    bOffset = loadedParams[1];
    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    func_8010DFF0(1, 1);
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 32);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000 | FLAG_UNK_10000;
        selfX = self->posX.i.hi;
        selfY = self->posY.i.hi;
        prim2 = prim1 = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 16; i++) {
            prim1 = prim1->next;
        }
        for (i = 0; i < 16; i++) {
            angle = i << 8;
            prim2->u0 = ((rcos(angle) >> 4 << 5) >> 8) + 0x20;
            prim2->v0 = -((rsin(angle) >> 4 << 5) >> 8) + 0xDF;
            angle = i + 1 << 8;
            prim2->u1 = ((rcos(angle) >> 4 << 5) >> 8) + 0x20;
            prim2->v1 = -((rsin(angle) >> 4 << 5) >> 8) + 0xDF;
            prim1->u2 = prim1->u3 = 0x20;
            prim1->v2 = prim1->v3 = 0xDF;
            prim2->u2 = prim1->u0 = (prim2->u0 + prim1->u2) / 2;
            prim2->v2 = prim1->v0 = (prim2->v0 + prim1->v2) / 2;
            prim2->u3 = prim1->u1 = (prim2->u1 + prim1->u3) / 2;
            prim2->v3 = prim1->v1 = (prim2->v1 + prim1->v3) / 2;
            prim1->tpage = prim2->tpage = 0x1A;
            prim1->clut = prim2->clut = PAL_FILL_WHITE;
            prim1->priority = prim2->priority = PLAYER.zPriority + 2;
            prim1->drawMode = prim2->drawMode =
                DRAW_UNK_200 | DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                DRAW_TRANSP;
            prim2 = prim2->next;
            prim1 = prim1->next;
        }

        if (flag == false) {
            self->ext.whiteCircle.unk80 = self->ext.whiteCircle.unk82 = 0x280;
            self->ext.whiteCircle.unk84 = self->ext.whiteCircle.unk86 = 0x240;
            self->ext.whiteCircle.unk8A = loadedParams[5];
            self->ext.whiteCircle.unk88 = 0xC0;
        } else {
            self->ext.whiteCircle.unk80 = self->ext.whiteCircle.unk82 = 0x40;
            self->ext.whiteCircle.unk84 = self->ext.whiteCircle.unk86 = 0;
            self->ext.whiteCircle.unk8A = loadedParams[5];
            self->ext.whiteCircle.unk88 = 0xC0;
        }
        self->step += 1;
        break;
    case 1:
        self->ext.whiteCircle.unk7E += 0x40;
        if (flag == false) {
            self->ext.whiteCircle.unk86 -= 0xA;
            if (self->ext.whiteCircle.unk86 < 0) {
                self->ext.whiteCircle.unk86 = 0;
                self->ext.whiteCircle.unk7C = 0x20;
                self->step += 1;
            }
            self->ext.whiteCircle.unk84 = self->ext.whiteCircle.unk86;
            self->ext.whiteCircle.unk82 -= 5;
            self->ext.whiteCircle.unk80 -= 5;
        } else {
            self->ext.whiteCircle.unk86 += 9;
            self->ext.whiteCircle.unk84 += 6;
            if (self->ext.whiteCircle.unk86 > 0x200) {
                self->ext.whiteCircle.unk86 = 0x200;
                self->step += 1;
            }
            self->ext.whiteCircle.unk82 += 3;
            self->ext.whiteCircle.unk80 += 2;
        }
        break;
    case 2:
        self->ext.whiteCircle.unk7E += 0x40;
        if (flag == false) {
            self->ext.whiteCircle.unk82 -= 3;
            self->ext.whiteCircle.unk80 -= 6;
            if (--self->ext.whiteCircle.unk7C == 0) {
                self->step += 1;
                break;
            }
            break;
        }
        self->ext.whiteCircle.unk88 -= 4;
        if (self->ext.whiteCircle.unk88 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        self->ext.whiteCircle.unk7E += 0x40;
        self->ext.whiteCircle.unk82 -= 3;
        self->ext.whiteCircle.unk80 -= 6;
        self->ext.whiteCircle.unk88 -= 12;
        if (self->ext.whiteCircle.unk88 < 0) {
            DestroyEntity(self);
            return;
        }
        break;
    }
    sp38 = self->ext.whiteCircle.unk8A;
    selfX = self->posX.i.hi;
    selfY = self->posY.i.hi;
    prim1 = prim2 = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 16; i++) {
        prim1 = prim1->next;
    }
    for (i = 0; i < 16; i++) {
        prim2->x0 =
            selfX + ((prim2->u0 - 0x20) * self->ext.whiteCircle.unk80) / 0x100;
        prim2->y0 =
            selfY + ((prim2->v0 - 0xE0) * self->ext.whiteCircle.unk82) / 0x100;
        prim2->x1 =
            selfX + ((prim2->u1 - 0x20) * self->ext.whiteCircle.unk80) / 0x100;
        prim2->y1 =
            selfY + ((prim2->v1 - 0xE0) * self->ext.whiteCircle.unk82) / 0x100;
        prim1->x2 = selfX + (((rcos(i + 1 << 8) >> 4 << 5) >> 8) *
                             self->ext.whiteCircle.unk84) /
                                0x100;
        prim1->y2 = selfY - (((rsin(i + 1 << 8) >> 4 << 5) >> 8) *
                             self->ext.whiteCircle.unk86) /
                                0x100;
        prim1->x3 = selfX + (((rcos(i + 2 << 8) >> 4 << 5) >> 8) *
                             self->ext.whiteCircle.unk84) /
                                0x100;
        prim1->y3 = selfY - (((rsin(i + 2 << 8) >> 4 << 5) >> 8) *
                             self->ext.whiteCircle.unk86) /
                                0x100;
        prim2->x2 = prim1->x0 = (prim2->x0 + prim1->x2) / 2;
        prim2->y2 = prim1->y0 = (prim2->y0 + prim1->y2) / 2;
        prim2->x3 = prim1->x1 = (prim2->x1 + prim1->x3) / 2;
        prim2->y3 = prim1->y1 = (prim2->y1 + prim1->y3) / 2;
        base_angle = i * sp38;
        angle = self->ext.whiteCircle.unk7E + base_angle;
        prim1->r0 = prim2->r2 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / rScale;
        angle = self->ext.whiteCircle.unk7E + gOffset + base_angle;
        prim1->g0 = prim2->g2 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / gScale;
        angle = self->ext.whiteCircle.unk7E + bOffset + base_angle;
        prim1->b0 = prim2->b2 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / bScale;
        angle = self->ext.whiteCircle.unk7E + sp38 + base_angle;
        prim1->r1 = prim2->r3 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / rScale;
        angle = self->ext.whiteCircle.unk7E + gOffset + sp38 + base_angle;
        prim1->g1 = prim2->g3 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / gScale;
        angle = self->ext.whiteCircle.unk7E + bOffset + sp38 + base_angle;
        prim1->b1 = prim2->b3 = ((rsin(angle) + 0x1000) >> 7) *
                                self->ext.whiteCircle.unk88 / bScale;
        PGREY(prim2, 0) = PGREY(prim2, 1) = 0;
        PGREY(prim1, 2) = PGREY(prim1, 3) = 0;
        prim2 = prim2->next;
        prim1 = prim1->next;
    }
}

extern Unkstruct_800ADEF0 D_800ADEF0[];

// Potion Entity. Has different effects based on a parameter.
void EntityPlayerPinkEffect(Entity* self) {
    s16 paramsHi = (self->params & 0x7F00) >> 8;
    Unkstruct_800ADEF0* data_idx = (Unkstruct_800ADEF0*)&D_800ADEF0[paramsHi];

    switch (self->step) {
    case 0:
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        self->ext.timer.t = data_idx->timers[0];
        if (data_idx->unk18 != 0x83) {
            PlaySfx(SFX_TRANSFORM);
        }
        if (data_idx->unk18 >= 128) {
            func_8010E168(true, 64);
        } else {
            GiveStatBuff(data_idx->unk18);
        }
        self->step += 1;
        break;
    case 1:
        if (--self->ext.timer.t != 0) {
            return;
        }
        if (data_idx->blueprints[self->ext.factory.unk7E]) {
            CreateEntFactoryFromEntity(
                self,
                FACTORY(data_idx->blueprints[self->ext.factory.unk7E],
                        data_idx->blueprintParams[self->ext.factory.unk7E]),
                0);
            if (data_idx->blueprints[self->ext.factory.unk7E] == 0x28) {
                PlaySfx(SFX_UI_MP_FULL);
            }
        }

        self->ext.factory.unk7E++;
        self->ext.timer.t = data_idx->timers[self->ext.factory.unk7E];
        if (self->ext.timer.t == 0xFF) {
            switch (data_idx->unk18) {
            case 0x83: // There is no un-stoning potion, perhaps related to
                       // fairy using Hammer.
                if (PLAYER.step == Player_StatusStone) {
                    g_Player.unk5E = 1;
                    D_800ACE44 = 0x40;
                }
                break;
            case 0x80:
                g_Player.timers[0] = 2;
                PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
                break;
            case 0x81:
                g_Player.timers[1] = 2;
                PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
                break;
            case 0x84: // Potion most likely.
                g_Player.unk56 = 1;
                g_Player.unk58 =
                    GetStatusAilmentTimer(STATUS_AILMENT_UNK04, 0x32);
                break;
            case 0x85: // High Potion most likely.
                g_Player.unk56 = 1;
                g_Player.unk58 =
                    GetStatusAilmentTimer(STATUS_AILMENT_UNK05, 0x64);
                break;
            case 0x86: // Elixir
                g_Player.unk56 = 1;
                g_Player.unk58 = g_Status.hpMax;
                break;
            case 0x87: // Mana Prism
                PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
                g_Status.mp = g_Status.mpMax;
                break;
            default: // Used by Resist and Stat Boosting Potions most likely.
                CreateEntFactoryFromEntity(
                    self, FACTORY(BP_47, D_800AE120[data_idx->unk18]), 0);
                PlaySfx(SFX_MAGIC_WEAPON_APPEAR_A);
            case 0x82:
                break;
            }
            self->step += 1;
        }
        break;
    case 2:
        DestroyEntity(self);
        break;
    }
}

// player dissolves into pixels
void EntityPlayerDissolves(Entity* self) {
    const int PrimCount = 36;
    const int Iterations = 40;
    u8 xMargin;
    u8 yMargin;
    u8 wSprite;
    u8 hSprite;
    s16 xPivot;
    s16 yPivot;
    s16 width;
    s16 height;
    s16 sp42;
    s32 sp3C;
    s16* sp38;
    Primitive* prim;
    s32 i;
    u8* s2;
    s16 s3;
    s16 s4;
    s16 s5;
    s16 s6;
    s16 s7;
    u_long* data;
    u8* plSprite;

    if (PLAYER.ext.player.anim != 0x38 && PLAYER.ext.player.anim != 0x39 &&
        PLAYER.ext.player.anim != 0x3A &&
        (self->step == 2 || self->step == 3)) {
        self->step = 4;
        LoadImage(&D_800AE138, D_80139A7C);
        self->ext.dissolve.unk7E = rand() & 0xFF;
        self->ext.dissolve.unk7C = 0x30;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim->drawMode &= ~DRAW_HIDE;
            prim = prim->next;
        }
    }

    s5 = self->posX.i.hi = PLAYER.posX.i.hi;
    s7 = self->posY.i.hi = PLAYER.posY.i.hi;
    self->facingLeft = PLAYER.facingLeft;
    if (!(PLAYER.animCurFrame & 0x7FFF)) {
        DestroyEntity(self);
        return;
    }

    sp38 = D_800CF324[PLAYER.animCurFrame & 0x7FFF];
    sp42 = *sp38++;
    sp42 &= 0x7FFF;
    plSprite = ((u8**)SPRITESHEET_PTR)[sp42];
    xMargin = 4;
    yMargin = 1;
    wSprite = xMargin + plSprite[0];
    hSprite = yMargin + plSprite[1];
    width = wSprite - xMargin;
    height = hSprite - yMargin;
    s3 = width / 6;
    s4 = height / 6;
    xPivot = sp38[0] + plSprite[2];
    yPivot = sp38[1] + plSprite[3];
    if (self->facingLeft) {
        s5 = s5 - xPivot;
    } else {
        s5 = s5 + xPivot;
    }
    s7 = s7 + yPivot;

    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, PrimCount);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_POS_CAMERA_LOCKED;
        self->ext.dissolve.unk7C = 0;
        self->ext.dissolve.unk80 = rand() & 7;
        self->ext.dissolve.unk7E =
            D_800AE140[self->ext.dissolve.unk80][self->ext.dissolve.unk7C];
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {

            if (self->facingLeft) {
                prim->x0 = prim->x2 = (s5 - (s3 * (i % 6))) + 1;
                prim->x1 = prim->x3 = prim->x0 - s3;
            } else {
                prim->x0 = prim->x2 = s5 + (s3 * (i % 6));
                prim->x1 = prim->x3 = prim->x0 + s3;
            }
            prim->y0 = prim->y1 = s7 + (s4 * (i / 6));
            prim->y2 = prim->y3 = prim->y0 + s4;
            prim->u0 = prim->u2 = (xMargin) + (s3 * (i % 6)) + 0x80;
            prim->u1 = prim->u3 = prim->u0 + s3;
            prim->v0 = prim->v1 = (yMargin + (s4 * (i / 6)));
            prim->v2 = prim->v3 = prim->v0 + s4;
            prim->g0 = (((i / 6) * 2) + (rand() & 3));
            prim->tpage = 0x18;
            prim->clut = PLAYER.palette & 0x7FFF;
            prim->priority = PLAYER.zPriority + 2;
            prim->drawMode = DRAW_UNK_200 | DRAW_UNK_100 | DRAW_HIDE;
            prim = prim->next;
        }
        self->step += 1;
        break;
    case 1:
        StoreImage(&D_800AE130, D_80139A7C);
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = s5 - (s3 * (i % 6)) + 1;
                prim->x1 = prim->x3 = prim->x0 - s3;
                ;
            } else {
                prim->x0 = prim->x2 = s5 + (s3 * (i % 6));
                prim->x1 = prim->x3 = prim->x0 + s3;
            }
            prim->y0 = prim->y1 = s7 + (s4 * (i / 6));
            prim->y2 = prim->y3 = prim->y0 + s4;
            prim = prim->next;
        }
        self->step += 1;
        /* fallthrough */
    case 2:
        PLAYER.animCurFrame |= 0x8000;
        if (g_Player.padTapped & (PAD_UP | PAD_RIGHT | PAD_DOWN | PAD_LEFT)) {
            self->step += 1;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (s5 - (s3 * (i % 6))) + 1;
                prim->x1 = prim->x3 = prim->x0 - s3;
            } else {
                prim->x0 = prim->x2 = s5 + (s3 * (i % 6));
                prim->x1 = prim->x3 = prim->x0 + s3;
            }
            prim->y0 = prim->y1 = s7 + (s4 * (i / 6));
            prim->y2 = prim->y3 = prim->y0 + s4;
            prim = prim->next;
        }
        break;
    case 3:
        PLAYER.animCurFrame |= 0x8000;
        self->ext.dissolve.unk7E =
            D_800AE140[self->ext.dissolve.unk80][self->ext.dissolve.unk7C];
        data = (u_long*)D_80139A7C;
        s2 = (u8*)data;
        s2 = s2 + ((self->ext.dissolve.unk7E >> 1) & 7);
        s2 = s2 + (((self->ext.dissolve.unk7E & 0xFF) >> 4) << 6);
        for (i = 0; i < Iterations; i++) {
            if (rand() & 3) {
                if (self->ext.dissolve.unk7E & 1) {
                    if (*(s2 + (i & 7) * 8 + (i >> 3) * 0x400)) {
                        *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) &= 0xF0;
                        *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) |= 1;
                    }
                } else if (*(s2 + (i & 7) * 8 + (i >> 3) * 0x400)) {
                    *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) &= 0x0F;
                    *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) |= 0x10;
                }
            }
        }
        LoadImage(&D_800AE130, data);
        if (++self->ext.dissolve.unk7C == 8) {
            self->ext.dissolve.unk7C = 0;
            self->ext.dissolve.unk80 += 1;
            self->ext.dissolve.unk80 &= 7;
            self->step = 2;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            if (self->facingLeft) {
                prim->x0 = prim->x2 = (s5 - (s3 * (i % 6))) + 1;
                prim->x1 = prim->x3 = prim->x0 - s3;
            } else {
                prim->x0 = prim->x2 = s5 + (s3 * (i % 6));
                prim->x1 = prim->x3 = prim->x0 + s3;
            }
            prim->y0 = prim->y1 = s7 + (s4 * (i / 6));
            prim->y2 = prim->y3 = prim->y0 + s4;
            prim = prim->next;
        }
        break;
    case 4:
        if (PLAYER.step == 0x10) {
            if (g_Timer % 2 == 0) {
                break;
            }
        } else if (g_Timer % 3 == 0) {
            break;
        }
        for (sp3C = 0; sp3C < 6; sp3C++) {
            data = (u_long*)D_80139A7C;
            s2 = (u8*)data;
            s2 = s2 + ((self->ext.dissolve.unk7E >> 1) & 7);
            s2 = s2 + (((self->ext.dissolve.unk7E & 0xFF) >> 4) << 6);
            for (i = 0; i < Iterations; i++) {
                if (self->ext.dissolve.unk7E & 1) {
                    *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) &= 0xF0;
                } else {
                    *(s2 + (i & 7) * 8 + (i >> 3) * 0x400) &= 0x0F;
                }
            }
            // some sort of prng state
            self->ext.dissolve.unk7E += 0x23;
            self->ext.dissolve.unk7E &= 0xFF;
        }
        LoadImage(&D_800AE138, data);
        if (--self->ext.dissolve.unk7C == 0) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < PrimCount; i++) {
            prim->drawMode &= DRAW_UNK_200;
            prim->drawMode |= DRAW_UNK02;
            if (prim->r0 == 0) {
                if (--prim->g0 == 0) {
                    prim->r0++;
                    prim->b0 = ((rand() & 3) + 0xF8);
                    prim->r1 = 0x20 - (i / 6 * 2);
                }
            } else {
                if (prim->r1) {
                    prim->r1--;
                } else {
                    prim->drawMode = DRAW_HIDE;
                }
                if (prim->b0 < 0x30 || prim->b0 > 0xD0) {
                    prim->b0 += 2;
                }
                s6 = (s8)prim->b0 >> 4;
                prim->y0 += s6;
                prim->y1 += s6;
                prim->y2 += s6;
                prim->y3 += s6;
            }
            prim = prim->next;
        }
    }
    func_8010DFF0(1, 1);
}

void EntityLevelUpAnimation(Entity* self) {
    Primitive* prim;
    Unkstruct_800AE180* unkstruct;
    s16 posX_hi, posY_hi;
    s16 angle;
    s16 prim_x0_x2;
    s16 prim_y0_y2;
    s16 prim_x1_x3;
    s16 prim_y1_y3;
    s32 i;

    s16 upperParams = (self->params >> 8) & 0xff;

    unkstruct = &D_800AE180[upperParams];
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, 14);
        if (self->primIndex == -1) {
            return;
        }
        PlaySfx(SFX_LEVEL_UP); // Max HP & MP
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_HAS_PRIMS |
                      FLAG_UNK_20000 | FLAG_UNK_10000;
        CreateEntFactoryFromEntity(self, FACTORY(BP_BLINK_WHITE, 0x4A), 0);
        self->posX.i.hi = PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi - 48;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 14; i++) {
            prim->v0 = prim->v1 = unkstruct->unk2;
            prim->v2 = prim->v3 = prim->v0 + 0x18;
            prim->u0 = ((i * 8) + 0x80);
            prim->u1 = (((i + 1) * 8) + 0x80);
            prim->u2 = (((i - 1) * 8) + 0x80);
            prim->u3 = ((i * 8) + 0x80);
            if (i == 0) {
                prim->u2 = 0x80;
            }
            if (i == 0xD) {
                prim->u1 = prim->u0;
            }
            prim->tpage = 0x1C;
            prim->clut = unkstruct->palette;
            prim->priority = 0x1FE;
            prim->drawMode =
                DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
            prim = prim->next;
        }
        self->ext.timer.t = 0;
        self->ext.factory.unk80 = 0x100;
        self->ext.factory.unk82 = 0x100;
        self->ext.factory.unk7E = 0;
        self->ext.factory.unk84 = 0x40;
        self->step++;
        D_80138090 = 0;
        break;
    case 1:
        if (++D_80138090 == 2) {
            g_unkGraphicsStruct.unk20 = 3;
        }
        self->ext.factory.unk80 -= 8;
        self->ext.factory.unk82 -= 8;
        self->ext.factory.unk7E += 6;
        if (self->ext.factory.unk7E > 0xFF) {
            self->ext.factory.unk7E = 0xFF;
        }
        if (self->ext.factory.unk82 < 0) {
            self->ext.factory.unk82 = 0;
        }
        if (self->ext.factory.unk80 < 0) {
            self->ext.factory.unk80 = 0;
            self->ext.timer.t = 0x20;
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 14; i++) {
                prim->drawMode = DRAW_DEFAULT;
                prim = prim->next;
            }
            self->step++;
        }
        break;
    case 2:
        self->ext.factory.unk80 = 8;
        self->ext.factory.unk82 = 4;
        if (--self->ext.timer.t == 0) {
            CreateEntFactoryFromEntity(self, FACTORY(BP_RIPPLE_OUTLINE, 10), 0);
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; i < 14; i++) {
                prim->drawMode =
                    DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS | DRAW_TRANSP;
                prim = prim->next;
            }
            self->step++;
        }
        break;
    case 3:
        self->ext.factory.unk80 += 0x10;
        self->ext.factory.unk82 += 2;
        self->ext.factory.unk7E -= 6;
        if (self->ext.factory.unk7E < 0) {
            self->ext.factory.unk7E = 0;
        }
        if (self->ext.factory.unk80 > 0x200) {
            g_unkGraphicsStruct.unk20 = 0;
            DestroyEntity(self);
            return;
        }
        break;
    }

    posX_hi = self->posX.i.hi - 176;
    posY_hi = self->posY.i.hi;
    for (prim = &g_PrimBuf[self->primIndex], i = 0; i < 14; prim = prim->next,
        i++) {
        angle = D_800AE190[i];
        prim_y0_y2 = -(rsin(angle) >> 5) * self->ext.factory.unk80 / 256;
        prim_x0_x2 = (rcos(angle) >> 5) * self->ext.factory.unk82 / 256;
        angle = D_800AE190[i + 1];
        prim_y1_y3 = -(rsin(angle) >> 5) * self->ext.factory.unk80 / 256;
        prim_x1_x3 = (rcos(angle) >> 5) * self->ext.factory.unk82 / 256;

        prim->x0 = prim_x0_x2 + (posX_hi + prim->u0);
        prim->x1 = prim_x1_x3 + (posX_hi + prim->u1);
        prim->x2 = prim_x0_x2 + (posX_hi + prim->u2);
        prim->x3 = prim_x1_x3 + (posX_hi + prim->u3);

        prim->y0 = posY_hi + prim_y0_y2;
        prim->y1 = posY_hi + prim_y1_y3;
        prim->y2 = posY_hi + 0x18 + prim_y0_y2;
        prim->y3 = posY_hi + 0x18 + prim_y1_y3;
        // weird RBG assign order, not RGB
        prim->r0 = prim->b0 = prim->g0 = prim->r1 = prim->b1 = prim->g1 =
            prim->r2 = prim->b2 = prim->g2 = prim->r3 = prim->b3 = prim->g3 =
                self->ext.factory.unk7E;

        D_800AE190[i] += self->ext.factory.unk84;
    }
}

void func_80121F14(s32 arg0, s32 arg1) {
    mistStruct* ptr = D_80138094;
    s32 i;

    for (i = 0; i < LEN(D_80138094); i++, ptr++) {
        ptr->posX.val += (s32)arg0;
        ptr->posY.val += (s32)arg1;
    }
}

Primitive* func_80121F58(bool arg0, s32 arg1, Primitive* arg2, s16 facingLeft) {
    s32 primU0;
    s32 tempU;
    s32 tempV;
    s32 primU1;
    s32 primV0;
    s32 primV1;
    s16 angle1;
    s16 angle2;
    Primitive* prim;
    s32 i;

    if (arg0 == false) {
        if (facingLeft) {
            prim = &D_801381F4[D_800AE230[arg1 >> 1]];
            primU0 = prim->u0;
            tempU = prim->u1;
            primV0 = prim->v0;
            tempV = prim->v1;
        } else {
            prim = &D_801381F4[D_800AE250[arg1 >> 1]];
            primU0 = prim->u1;
            tempU = prim->u0;
            primV0 = prim->v1;
            tempV = prim->v0;
        }

        primU1 = (prim->u0 + prim->u1) / 2;
        primV1 = (prim->v0 + prim->v1) / 2;

        if (arg1 & 1) {
            primU0 = primU1;
            primU1 = tempU;
            primV0 = primV1;
            primV1 = tempV;
        }
        arg2->u0 = primU0;
        arg2->v0 = primV0;
        arg2->u1 = primU1;
        arg2->v1 = primV1;
        arg2->u3 = arg2->u2 = prim->u2;
        arg2->v3 = arg2->v2 = prim->v2;
        if (PLAYER.animSet == 0xF) {
#ifdef VERSION_PSP
            arg2->tpage = 0x4118;
#else
            arg2->tpage = 0x118;
#endif
        } else {
            arg2->tpage = 0x18;
        }
        arg2->clut = 0x10F;
        arg2->priority = PLAYER.zPriority + 2;
        arg2->drawMode = DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 |
                         DRAW_TPAGE | DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        arg2 = arg2->next;
    } else {
        angle1 = D_80138094[arg1].angle1;
        angle2 = D_80138094[(arg1 + 1) % 16].angle1;

        for (i = 0; i < 4; i++) {
            // nb: the cos/sin arguments seem to be invariant, could've been
            // extracted outside the loop
            arg2->u0 = 0x60 + ((((rcos(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v0 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * (i + 1)) >> 8);
            arg2->u1 = 0x60 + ((((rcos(angle2) >> 4) * 8) * (i + 1)) >> 8);
            arg2->v1 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * (i + 1)) >> 8);

            if (i == 3) {
                if (arg2->u0 < 4) {
                    arg2->u0 = -1;
                }
                if (arg2->u1 < 4) {
                    arg2->u1 = -1;
                }
                if (arg2->v0 < 4) {
                    arg2->v0 = -1;
                }
                if (arg2->v1 < 4) {
                    arg2->v1 = -1;
                }
            }

            arg2->u2 = 0x60 + ((((rcos(angle1) >> 4) * 8) * i) >> 8);
            arg2->v2 = 0xA0 - ((((rsin(angle1) >> 4) * 8) * i) >> 8);
            arg2->u3 = 0x60 + ((((rcos(angle2) >> 4) * 8) * i) >> 8);
            arg2->v3 = 0xA0 - ((((rsin(angle2) >> 4) * 8) * i) >> 8);

            arg2->tpage = 0x18;
            arg2->clut = 0x10F;
            arg2->priority = PLAYER.zPriority + 4;
            arg2->drawMode =
                DRAW_UNK_400 | DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
            arg2 = arg2->next;
        }
    }
    return arg2;
}

// spawns mist (player transform)
void EntityMist(Entity* self) {
    Primitive* prim;
    Primitive* mistPrim;
    mistStruct* mistStruct;
    s16 xVar;
    s16 yVar;
    s16 angle;
    s16 magnitude;
    s16 angle2;
    s16 angle3;
    s16 xSize;
    s16 ySize;
    s16 baseSize;
    s16 index;
    s16 xVar2;
    s16 yVar2;
    s16 xVar3;
    s16 yVar3;
    s32 primColor1;
    s32 primColor2;
    s32 primColor3;
    s32 primColor4;
    s16 xVar4;
    s16 yVar4;
    s32 velX;
    s32 velY;
    s32 cosine;
    s32 sine;
    s32 i;
    s32 j;
    s16 xVar5;
    s16 yVar5;

    velX = PLAYER.velocityX >> 1;
    velY = PLAYER.velocityY >> 1;
    primColor1 = D_801381E4 + (rsin(D_801381D4) >> 8);
    primColor2 = D_801381E8 + (rsin(D_801381D8) >> 8);
    primColor3 = D_801381EC + (rsin(D_801381DC) >> 8);
    primColor4 = D_801381F0 + (rsin(D_801381E0) >> 8);
    D_801381D4 += 0x20;
    D_801381D8 -= 0x20;
    D_801381DC += 0x20;
    D_801381E0 -= 0x20;
    self->ext.mist.timer++;

    self->facingLeft = PLAYER.facingLeft;
    if (PLAYER.animSet == 0xF) {
        self->facingLeft = 0;
    }
    switch (self->step) {
    case 0:
        // Weird that we set FLAG_DEAD here.
        self->params = FLAG_UNK_4000 | FLAG_UNK_1000 | FLAG_UNK_800 |
                       FLAG_UNK_400 | FLAG_DEAD;
        EntityPlayerBlinkWhite(self);
        if (self->primIndex == -1) {
            goto block_147;
        }
        prim = &g_PrimBuf[self->primIndex];
        mistPrim = D_801381F4;
        for (i = 0; i < LEN(D_801381F4); i++, mistPrim++) {
            *mistPrim = *prim;
            prim = prim->next;
        }
        FreePrimitives(self->primIndex);
        self->step = 0;
        self->primIndex = AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            goto block_147;
        }

        D_801381D4 = rand() & PSP_RANDMASK;
        D_801381D8 = rand() & PSP_RANDMASK;
        D_801381DC = rand() & PSP_RANDMASK;
        D_801381E0 = rand() & PSP_RANDMASK;

        D_801381E4 = 0xEF;
        D_801381E8 = 0xEF;
        D_801381EC = 0xEF;
        D_801381F0 = 0xEF;
        mistStruct = &D_80138094[0];
        for (i = 0; i < LEN(D_80138094); i++, mistStruct++) {
            if (self->facingLeft) {
                mistPrim = &D_801381F4[D_800AE230[i >> 1]];
                xVar = mistPrim->x0;
                yVar = mistPrim->y0;
            } else {
                mistPrim = &D_801381F4[D_800AE250[i >> 1]];
                xVar = mistPrim->x1;
                yVar = mistPrim->y1;
            }
            xVar5 = (mistPrim->x0 + mistPrim->x1) / 2;
            yVar5 = (mistPrim->y0 + mistPrim->y1) / 2;
            if (!(i & 1)) {
                mistStruct->posX.i.hi = xVar;
                mistStruct->posY.i.hi = yVar;
            } else {
                mistStruct->posX.i.hi = xVar5;
                mistStruct->posY.i.hi = yVar5;
            }
            xVar2 = mistPrim->x2;
            yVar2 = mistPrim->y2;
            angle = mistStruct->angle1 = (i * 4096) / 16;
            mistStruct->angle2 = i << 9;
            xVar3 = mistStruct->posX.i.hi - xVar2;
            yVar3 = mistStruct->posY.i.hi - yVar2;
            mistStruct->size =
                (SquareRoot12(((xVar3 * xVar3) + (yVar3 * yVar3)) << 0xC) >>
                 0xC);
        }
        xVar4 = xVar2;
        yVar4 = yVar2;
        self->ext.mist.xCurrent = xVar2 - PLAYER.posX.i.hi;
        self->ext.mist.yCurrent = yVar2 - PLAYER.posY.i.hi;
        self->posX.i.hi = xVar4;
        self->posY.i.hi = yVar4;
        prim = &g_PrimBuf[self->primIndex];
        for (j = 0; j < 16; j++) {
            prim = func_80121F58(0, j, prim, self->facingLeft);
        }
        for (j = 0; j < 16; j++) {
            prim = func_80121F58(1, j, prim, self->facingLeft);
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->step++;
        self->ext.mist.timer = 0;
        D_80138394 = 0;
        break;
    case 1:
        D_801381E4 -= 1;
        D_801381E8 -= 2;
        D_801381EC -= 3;
        D_801381F0 -= 4;
        if (D_801381E4 < 0xD0) {
            D_801381E4 = 0xD0;
        }
        if (D_801381E8 < 0xA0) {
            D_801381E8 = 0xA0;
        }
        if (D_801381EC < 0x70) {
            D_801381EC = 0x70;
        }
        if (D_801381F0 < 0x30) {
            D_801381F0 = 0x30;
        }
        if (self->ext.mist.timer == 0x4F) {
            self->step++;
            func_800EA538(8);
        }
        // Fallthrough!
    case 2:
        j = 0;
        if (self->ext.mist.timer < 16) {
            j = 1;
        }
        xVar4 = PLAYER.posX.i.hi + self->ext.mist.xCurrent;
        yVar4 = PLAYER.posY.i.hi + self->ext.mist.yCurrent;
        xVar = xVar4 - self->posX.i.hi;
        yVar = yVar4 - self->posY.i.hi;
        angle = ratan2(-yVar, xVar);
        magnitude = SquareRoot12(((xVar * xVar) + (yVar * yVar)) << 0xC) >> 0xC;
        if (magnitude > 10) {
            cosine = rcos(angle) * 8;
            sine = -rsin(angle) * 8;
            if (magnitude > 35) {
                cosine *= 2;
                sine *= 2;
            }
            if (magnitude > 60) {
                cosine *= 2;
                sine *= 2;
            }
            self->posX.val += (s32)cosine;
            self->posY.val += (s32)sine;
        }
        angle3 = angle;
        xVar3 = (self->posX.i.hi + xVar4) / 2;
        yVar3 = (self->posY.i.hi + yVar4) / 2;
        xVar2 = abs(xVar) / 2;
        yVar2 = abs(yVar) / 2;
        mistStruct = &D_80138094[0];
        for (i = 0; i < LEN(D_80138094); i++, mistStruct++) {
            if ((mistStruct->size < 0x28) && (g_GameTimer & 1)) {
                mistStruct->size++;
            }
            angle2 = mistStruct->angle1;
            index = ((angle3 - angle2) & 0xFFF);
            index = (index >> 7) & 0x1F;
            baseSize = D_800AE1B0[index];
            xSize = ((mistStruct->size + xVar2) * baseSize) / 80;
            ySize = ((mistStruct->size + yVar2) * baseSize) / 80;
            xVar = xVar3 + (((rcos(angle2) >> 4) * xSize) >> 8);
            yVar = yVar3 - (((rsin(angle2) >> 4) * ySize) >> 8);
            mistStruct->angle2 += 8;
            angle = mistStruct->angle2;
            if (j) {
                xVar += (rcos(angle) >> 4) * 2 >> 8;
                yVar -= (rsin(angle) >> 4) * 2 >> 8;
            } else {
                xVar += (((rcos(angle) >> 4) * 6) >> 8);
                yVar -= (((rsin(angle) >> 4) * 6) >> 8);
            }
            xVar5 = xVar - mistStruct->posX.i.hi;
            yVar5 = yVar - mistStruct->posY.i.hi;
            angle = ratan2(-yVar5, xVar5) & 0xFFF;
            mistStruct->posX.val += rcos(angle) << 5;
            mistStruct->posY.val += -rsin(angle) << 5;
            if (D_800AE1F0[index] == -1) {
                mistStruct->posX.val += (s32)velX;
                mistStruct->posY.val += (s32)velY;
            }
        }
        D_80138394 += 8;
        if (D_80138394 >= 0xFF) {
            D_80138394 = 0xFF;
        }
        break;
    case 3:
        FreePrimitives(self->primIndex);
        self->step = 0;
        xVar = self->ext.mist.xCurrent;
        yVar = self->ext.mist.yCurrent;
        self->params = FLAG_UNK_4000 | FLAG_UNK_1000 | FLAG_UNK_800 |
                       FLAG_UNK_400 | FLAG_DEAD;
        EntityPlayerBlinkWhite(self);
        if (self->primIndex == -1) {
            self->flags = 0;
            DestroyEntity(self);
            goto block_147;
        }
        prim = &g_PrimBuf[self->primIndex];
        mistPrim = D_801381F4;
        for (i = 0; i < 8; i++, mistPrim++) {
            *mistPrim = *prim;
            prim = prim->next;
        }
        FreePrimitives(self->primIndex);
        self->ext.mist.xCurrent = xVar;
        self->ext.mist.yCurrent = yVar;
        self->ext.mist.timer = 0;
        self->step = 4;
        self->primIndex = AllocPrimitives(PRIM_GT4, 80);
        if (self->primIndex == -1) {
            DestroyEntity(self);
        } else {
            mistStruct = &D_80138094[0];
            for (i = 0; i < LEN(D_80138094); i++, mistStruct++) {
                if (self->facingLeft) {
                    mistPrim = &D_801381F4[D_800AE230[i >> 1]];
                    xVar = mistPrim->x0;
                    yVar = mistPrim->y0;
                } else {
                    mistPrim = &D_801381F4[D_800AE250[i >> 1]];
                    xVar = mistPrim->x1;
                    yVar = mistPrim->y1;
                }
                xVar5 = (mistPrim->x0 + mistPrim->x1) / 2;
                yVar5 = (mistPrim->y0 + mistPrim->y1) / 2;
                if (!(i & 1)) {
                    mistStruct->xOffset = xVar;
                    mistStruct->yOffset = yVar;
                } else {
                    mistStruct->xOffset = xVar5;
                    mistStruct->yOffset = yVar5;
                }
                mistStruct->xOffset -= PLAYER.posX.i.hi;
                mistStruct->yOffset -= PLAYER.posY.i.hi;
                xVar2 = mistPrim->x2;
                yVar2 = mistPrim->y2;
            }
            self->ext.mist.xTarget = xVar2 - PLAYER.posX.i.hi;
            self->ext.mist.yTarget = yVar2 - PLAYER.posY.i.hi;
            prim = &g_PrimBuf[self->primIndex];
            for (j = 0; j < 16; j++) {
                prim = func_80121F58(0, j, prim, self->facingLeft);
            }
            for (j = 0; j < 16; j++) {
                prim = func_80121F58(1, j, prim, self->facingLeft);
            }
            self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                          FLAG_HAS_PRIMS | FLAG_UNK_20000;
            xVar4 = PLAYER.posX.i.hi + self->ext.mist.xCurrent;
            yVar4 = PLAYER.posY.i.hi + self->ext.mist.yCurrent;
            self->posX.i.hi = PLAYER.posX.i.hi;
            self->posY.i.hi = PLAYER.posY.i.hi;
            D_80138394 = 0xFF;
            break;
        }
        goto block_147;
    case 4:
        if (self->ext.mist.timer == 0xC) {
            func_800EA538(8);
            func_800EA5E4(0x11DU);
        }
        j = 0;
        // These if-statements seem to allow for the mist to stretch and move
        // The mist's current location moves toward the target in X and Y.
        if (self->ext.mist.xCurrent > self->ext.mist.xTarget) {
            self->ext.mist.xCurrent--;
        }
        if (self->ext.mist.xCurrent < self->ext.mist.xTarget) {
            self->ext.mist.xCurrent++;
        }
        if (self->ext.mist.yCurrent > self->ext.mist.yTarget) {
            self->ext.mist.yCurrent--;
        }
        if (self->ext.mist.yCurrent < self->ext.mist.yTarget) {
            self->ext.mist.yCurrent++;
        }
        xVar4 = PLAYER.posX.i.hi + self->ext.mist.xCurrent;
        yVar4 = PLAYER.posY.i.hi + self->ext.mist.yCurrent;

        xVar = xVar4 - self->posX.i.hi;
        yVar = yVar4 - self->posY.i.hi;

        mistStruct = D_80138094;

        for (i = 0; i < LEN(D_80138094); i++, mistStruct++) {
            xVar = (mistStruct->xOffset + PLAYER.posX.i.hi) -
                   mistStruct->posX.i.hi;
            yVar = (mistStruct->yOffset + PLAYER.posY.i.hi) -
                   mistStruct->posY.i.hi;
            if (xVar | yVar) {
                angle = ratan2(-yVar, xVar);
                mistStruct->posX.val += rcos(angle) << 5;
                mistStruct->posY.val += -rsin(angle) << 5;
            }
            mistStruct->posX.val += PLAYER.velocityX;
            mistStruct->posY.val += PLAYER.velocityY;
        }
        if (self->ext.mist.timer > 0x18) {
            self->step++;
            self->ext.mist.timer = 0x10;
        }
        D_80138394 -= 0x10;
        if (D_80138394 <= 0) {
            D_80138394 = 0;
        }
        break;
    case 5:
        if (self->ext.mist.timer <= 0) {
            DestroyEntity(self);
        }
        return;
    }
    D_80138398 = 0xFF - D_80138394;

    prim = &g_PrimBuf[self->primIndex];
    for (j = 0; j < LEN(D_80138094); j++) {
        xVar5 = D_80138094[j].posX.i.hi;
        yVar5 = D_80138094[j].posY.i.hi;
        xVar2 = D_80138094[(j + 1) % 16].posX.i.hi;
        yVar2 = D_80138094[(j + 1) % 16].posY.i.hi;
        prim->x0 = xVar5;
        prim->y0 = yVar5;
        prim->x1 = xVar2;
        prim->y1 = yVar2;
        prim->x2 = xVar4;
        prim->x3 = xVar4;
        prim->y2 = yVar4;
        prim->y3 = yVar4;
        PGREY(prim, 0) = PGREY(prim, 1) = 0;
        PGREY(prim, 2) = PGREY(prim, 3) = D_80138398;
#ifndef VERSION_HD
        if (D_80138398 < 0x10) {
            prim->drawMode |= DRAW_HIDE;
        } else {
            prim->drawMode &= ~DRAW_HIDE;
        }
#endif
        prim = prim->next;
    }
    for (j = 0; j < LEN(D_80138094); j++) {
        xVar5 = D_80138094[j].posX.i.hi;
        yVar5 = D_80138094[j].posY.i.hi;
        xVar2 = D_80138094[(j + 1) % 16].posX.i.hi;
        yVar2 = D_80138094[(j + 1) % 16].posY.i.hi;
        for (i = 0; i < 4; prim = prim->next, i++) {
            prim->x0 = xVar4 + (i + 1) * (xVar5 - xVar4) / 4;
            prim->y0 = yVar4 + (i + 1) * (yVar5 - yVar4) / 4;
            prim->x1 = xVar4 + (i + 1) * (xVar2 - xVar4) / 4;
            prim->y1 = yVar4 + (i + 1) * (yVar2 - yVar4) / 4;
            prim->x2 = xVar4 + i * (xVar5 - xVar4) / 4;
            prim->y2 = yVar4 + i * (yVar5 - yVar4) / 4;
            prim->x3 = xVar4 + i * (xVar2 - xVar4) / 4;
            prim->y3 = yVar4 + i * (yVar2 - yVar4) / 4;
            switch (i) {
            case 0:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_80138394 * primColor2 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_80138394 * primColor1 / 256) & 0xFF;
                break;
            case 1:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_80138394 * primColor3 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_80138394 * primColor2 / 256) & 0xFF;
                break;
            case 2:
                PGREY(prim, 0) = PGREY(prim, 1) =
                    (D_80138394 * primColor4 / 256) & 0xFF;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_80138394 * primColor3 / 256) & 0xFF;
                break;
            case 3:
                PGREY(prim, 0) = PGREY(prim, 1) = 0;
                PGREY(prim, 2) = PGREY(prim, 3) =
                    (D_80138394 * primColor4 / 256) & 0xFF;
                break;
            }
        }
    }

block_147:
    self->facingLeft = PLAYER.facingLeft;
}

void UnknownEntId48(Entity* self) {
    u32 lowerParams;

    lowerParams = self->params & 0xFF;
    if (!(g_Player.status & PLAYER_STATUS_MIST_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (!IsRelicActive(RELIC_GAS_CLOUD)) {
        self->hitboxState = 0;
    } else {
        self->hitboxState = 2;
    }
    if (!self->step) {
        func_8011A328(self, 0xC);
        self->enemyId = 4;
        self->hitboxWidth = self->hitboxHeight = 8;
        self->flags = FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_UNK_20000;
        self->step++;
    }
    if (lowerParams == 0) {
        self->posX.i.hi = (PLAYER.posX.i.hi + g_Entities[16].posX.i.hi) / 2;
        self->posY.i.hi = (PLAYER.posY.i.hi + g_Entities[16].posY.i.hi) / 2;
        self->hitboxWidth = self->hitboxHeight = 0x1C;
    } else {
        self->posX.i.hi = D_80138094[lowerParams - 1].posX.i.hi;
        self->posY.i.hi = D_80138094[lowerParams - 1].posY.i.hi;
    }
}

void UnknownEntId49(Entity* self) {
    s16 x_offset;

    if (!(g_Player.status & PLAYER_STATUS_AXEARMOR) || (PLAYER.step != 0x2B)) {
        DestroyEntity(self);
        return;
    }
    if (!self->step) {
        self->animSet = PLAYER.animSet;
        self->animCurFrame = 7;
        self->unk5A = PLAYER.unk5A;
        self->palette = PLAYER.palette;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        self->flags =
            FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_PLAYER_LOCKED | FLAG_UNK_20000;
        self->step++;
    }
    self->drawFlags = PLAYER.drawFlags & FLAG_DRAW_OPACITY;
    self->opacity = PLAYER.opacity;

    if (abs(PLAYER.rotate) == 0x200) {
        x_offset = -0x10;
        if (PLAYER.entityRoomIndex) {
            x_offset = -x_offset;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + x_offset;
        self->posY.i.hi = PLAYER.posY.i.hi + 9 + ((g_GameTimer >> 1) & 1);
    } else {
        x_offset = -0x18;
        if (PLAYER.entityRoomIndex) {
            x_offset = -x_offset;
        }
        self->posX.i.hi = PLAYER.posX.i.hi + x_offset;
        self->posY.i.hi = PLAYER.posY.i.hi + 16 + ((g_GameTimer >> 1) & 1);
    }
}

void func_80123A60(Entity* self) {
    if (!(g_Player.status & PLAYER_STATUS_AXEARMOR)) {
        DestroyEntity(self);
        return;
    }

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    if (self->step == 0) {
        func_8011A328(self, 0xB);
        self->step++;
        self->flags =
            FLAG_UNK_20000 | FLAG_POS_PLAYER_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA;
    }

    if (PLAYER.animCurFrame == 5) {
        self->hitboxWidth = 12;
        self->hitboxHeight = 32;
        self->hitboxOffX = 0x1C;
        self->hitboxOffY = -0xC;
    } else if (PLAYER.animCurFrame == 6) {
        self->hitboxWidth = 10;
        self->hitboxHeight = 10;
        self->hitboxOffX = 0x1C;
        self->hitboxOffY = 0x10;
    } else {
        DestroyEntity(self);
    }
}

void func_80123B40(Entity* self) {
    Entity copy;
    Primitive* prim;
    s16 params;
    s32 i;

    params = self->params;
    copy = PLAYER;

    if (!self->step) {
        self->animSet = PLAYER.animSet = 1;
        self->animCurFrame = PLAYER.animCurFrame = 0x9F;
        self->palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        self->unk5A = 0xC;
        self->params = 0x2600;
        EntityPlayerBlinkWhite(self);
        self->params = params;

        PLAYER = copy;

        if (!(self->flags & FLAG_HAS_PRIMS)) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_20000 | FLAG_UNK_10000;
        self->velocityY = FIX(-3.0);
        SetSpeedX(-0x1AAAA);
        self->ext.et_80123B40.unk28 = 0x80;
        self->ext.et_80123B40.unk29 = 0x80;
    } else {
        if (g_Timer & 1) {
            self->posX.val += self->velocityX;
            self->posY.val += self->velocityY;
            self->velocityY += FIX(0.15625);
        }
        PLAYER.posX.val = self->posX.val;
        PLAYER.posY.val = self->posY.val;
        PLAYER.facingLeft = self->facingLeft;
        self->animSet = PLAYER.animSet = 1;
        self->animCurFrame = PLAYER.animCurFrame = 0x9F;
        self->params = 0x2600;
        EntityPlayerBlinkWhite(self);
        self->params = params;

        PLAYER = copy;

        if (self->ext.et_80123B40.unk29 > 4) {
            self->ext.et_80123B40.unk29 -= 1;
        }
        if (self->step == 0x10 && self->velocityY > 0) {
            self->step = 0x11;
        }
        if (self->step == 0x11 && self->ext.et_80123B40.unk28 > 4) {
            self->ext.et_80123B40.unk28 -= 1;
        }
        if (self->step == 0x12) {
            DestroyEntity(self);
            return;
        }
    }

    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 8; i++) {
        prim->u0 += 0x80;
        prim->u1 += 0x80;
        prim->u2 += 0x80;
        prim->u3 += 0x80;
        prim->v0 += 0x80;
        prim->v1 += 0x80;
        prim->v2 += 0x80;
        prim->v3 += 0x80;
        prim->priority = PLAYER.zPriority - 8;
        if (params == 0) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 =
                self->ext.et_80123B40.unk28;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = prim->b0 = prim->b1 =
                prim->b2 = prim->b3 = 0;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE2 | DRAW_TPAGE |
                             DRAW_COLORS | DRAW_UNK02 | DRAW_TRANSP;
        }
        if (params == 1) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = prim->g0 = prim->g1 =
                prim->g2 = prim->g3 = prim->b0 = prim->b1 = prim->b2 =
                    prim->b3 = self->ext.et_80123B40.unk29;
            prim->clut = PAL_ALUCARD;
            prim->drawMode = DRAW_UNK_100 | DRAW_TPAGE | DRAW_COLORS |
                             DRAW_UNK02 | DRAW_TRANSP;
        }
        prim = prim->next;
    }
}

void func_80123F78(Entity* self) {
    PlayerDraw* plDraw = &g_PlayerDraw[13];

    if (g_unkGraphicsStruct.D_800973FC == 0) {
        plDraw->enableColorBlend = 0;
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->flags = FLAG_UNK_10000 | FLAG_UNK_20000 |
                      FLAG_KEEP_ALIVE_OFFCAMERA | FLAG_POS_CAMERA_LOCKED;
        if (PLAYER.animSet != 1) {
            DestroyEntity(self);
            return;
        }
        self->animSet = ANIMSET_DRA(1);
        self->animCurFrame = PLAYER.animCurFrame;
        self->unk5A = 0xD;
        self->drawFlags = PLAYER.drawFlags;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->palette = PAL_FLAG(PAL_FILL_WHITE);
        self->zPriority = PLAYER.zPriority - 2;
        self->facingLeft = PLAYER.facingLeft;

        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = plDraw->b0 =
            plDraw->b1 = plDraw->b2 = plDraw->b3 = plDraw->g0 = plDraw->g1 =
                plDraw->g2 = plDraw->g3 = 0x80;
        plDraw->enableColorBlend = true;
        self->step++;
        break;

    case 1:
        plDraw->g3 -= 1;
        if (plDraw->g3 < 4) {
            plDraw->enableColorBlend = 0;
            DestroyEntity(self);
            return;
        }
        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = plDraw->b0 =
            plDraw->b1 = plDraw->b2 = plDraw->b3 = plDraw->g0 = plDraw->g1 =
                plDraw->g2 = plDraw->g3;
        break;
    }
}

// Corresponding RIC function is func_80165DD8
static void func_80124164(
    Primitive* prim, s32 colorMul, s32 y, s32 radius, bool arg4) {
    prim->y0 = prim->y1 = y - radius;
    prim->y2 = prim->y3 = y + radius;
    if (prim->y0 < 0) {
        prim->y0 = prim->y1 = 0;
    }
    if (prim->y0 > 240) {
        prim->y2 = prim->y3 = 240;
    }
    if (arg4 == 0) {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE27C * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE280 * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE284 * colorMul / 256;
    } else {
        prim->r1 = prim->r3 = D_800AE270 * colorMul / 256;
        prim->g1 = prim->g3 = D_800AE274 * colorMul / 256;
        prim->b1 = prim->b3 = D_800AE278 * colorMul / 256;
        prim->r0 = prim->r2 = D_800AE288 * colorMul / 256;
        prim->g0 = prim->g2 = D_800AE28C * colorMul / 256;
        prim->b0 = prim->b2 = D_800AE290 * colorMul / 256;
    }
}

// BSS
extern Point16 D_8013839C[32];
// this can probably be removed if these files get merged
s32 func_80119E78(Primitive* prim, s16 xCenter, s16 yCenter);

// teleport effect like when using library card (ID 0x42)
void EntityTeleport(Entity* self) {
    Primitive* prim;
    s32 w;
    s32 h;
    s32 yVar;
    s32 xVar;
    s32 i;
    s32 result;
    s32 upperParams;
    bool showParticles;
    bool var_s5;

    upperParams = self->params & 0xFE00;
    showParticles = false;
    var_s5 = false;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT4, LEN(D_8013839C) + 4);
        if (self->primIndex == -1) {
            return;
        }
        self->flags = FLAG_POS_CAMERA_LOCKED | FLAG_KEEP_ALIVE_OFFCAMERA |
                      FLAG_HAS_PRIMS | FLAG_UNK_10000;
        prim = &g_PrimBuf[self->primIndex];
        for (i = 0; i < 2; i++) {
            // RBG not RGB because i'm a rebel
            prim->r0 = prim->b0 = prim->g0 = 0;
            prim->x0 = 0xC0 * i;
            prim->y0 = 0;
            prim->u0 = 0xC0;
            prim->v0 = 0xF0;
            prim->type = PRIM_TILE;
            prim->priority = 0x1FD;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_HIDE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < 2; i++) {
            prim->type = PRIM_G4;
            prim->priority = 0x1F8;
            prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;
            prim = prim->next;
        }
        for (i = 0; i < LEN(D_8013839C); i++) {
            xVar = PLAYER.posX.i.hi + (rand() % 28) - 14;
            yVar = 0xE0 - (rand() & 0x3F);
            D_8013839C[i].x = xVar;
            D_8013839C[i].y = yVar;
            // SOTN please why do you do this
            prim->clut = PAL_UNK_1B2;
            prim->clut = PAL_UNK_1B5;
            prim->clut = PAL_UNK_1BA;
            prim->tpage = 0x1A;
            prim->b0 = 0;
            prim->b1 = 0;
            prim->g0 = 0;
            prim->g1 = (rand() & 0x1F) + 1;
            prim->g2 = 0;
            prim->priority = 0x1F0;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        self->ext.teleport.width = 0;
        self->ext.teleport.height = 0x10;
        self->ext.teleport.colorIntensity = 0x80;
        if ((self->params & 0x100) == 0x100) {
            self->ext.teleport.width = 0x10;
            self->ext.teleport.height = 0x100;
            self->ext.teleport.colorIntensity = 0x80;
            self->ext.teleport.unk90 = 0xFF;
            var_s5 = true;
            self->step = Player_Unk20;
#ifndef VERSION_PSP
            PlaySfx(SFX_TELEPORT_SYNTH_DOWN);
#endif
        } else {
            self->ext.teleport.unk90 = 0;
            self->ext.teleport.width = 1;
            self->ext.teleport.height = 0x10;
            self->ext.teleport.colorIntensity = 0x80;
            self->step = 1;
            PlaySfx(SFX_TELEPORT_BANG_A);
            PlaySfx(SFX_TELEPORT_SYNTH_UP);
        }
        break;
    case 1:
        self->ext.teleport.height += 0x20;
        if (self->ext.teleport.height > 0x100) {
            self->step++;
        }
        break;
    case 2:
        self->ext.teleport.width++;
        if (self->ext.teleport.width >= 0x10) {
            self->ext.teleport.width = 0x10;
            self->ext.teleport.timer = 0x80;
            self->step++;
        }
        break;
    case 3:
        showParticles = true;
        self->ext.teleport.colorIntensity += 4;
        if (self->ext.teleport.colorIntensity >= 0x100) {
            self->ext.teleport.colorIntensity = 0x100;
        }
        if (--self->ext.teleport.timer == 0) {
            PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
            self->step++;
        }
        break;
    case 4:
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        self->ext.teleport.width--;
        if (self->ext.teleport.width <= 0) {
            self->ext.teleport.width = 0;
            self->step++;
        }
        break;
    case 5:
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
        var_s5 = true;
        self->ext.teleport.unk90 += 4;
        if (self->ext.teleport.unk90 >= 0x100) {
            self->ext.teleport.unk90 = 0xFF;
            self->ext.teleport.timer = 0x20;
            self->step++;
        }
        break;
    case 6:
        PLAYER.palette = PAL_FLAG(PAL_PLAYER_HIDDEN);
#ifdef VERSION_PSP
        func_psp_0892A620(0, 1);
        func_psp_0892A620(1, 1);
#endif
        var_s5 = true;
        if (--self->ext.teleport.timer == 0) {
            self->ext.teleport.unk90 = 0;
            if (upperParams == 0) {
                D_80097C98 = 6;
            }
            if (upperParams == 0x200) {
                D_80097C98 = 4;
            }
            if (upperParams == 0x400) {
                D_80097C98 = 5;
            }
        }
        break;
    case 20:
        var_s5 = true;
        self->ext.teleport.unk90 = 0xFF;
        self->ext.teleport.timer = 0x20;
        self->step++;
        break;
    case 21:
        var_s5 = true;
        if (--self->ext.teleport.timer == 0) {
#ifdef VERSION_PSP
            PlaySfx(SFX_TELEPORT_SYNTH_DOWN);
#endif
            self->step++;
        }
        break;
    case 22:
        var_s5 = true;
        self->ext.teleport.unk90 -= 4;
        if (self->ext.teleport.unk90 <= 0) {
            self->ext.teleport.unk90 = 0;
            self->step++;
        }
        break;
    case 23:
        self->ext.teleport.width--;
        if (self->ext.teleport.width < 2) {
            self->ext.teleport.width = 0;
            self->ext.teleport.timer = 4;
            self->step++;
            g_Player.warp_flag = 1;
            PlaySfx(SFX_TELEPORT_BANG_B);
            DestroyEntity(self);
            return;
        }
        break;
    }

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    xVar = PLAYER.posX.i.hi;
    yVar = PLAYER.posY.i.hi;
    w = self->ext.teleport.width;
    h = self->ext.teleport.height;
    prim = &g_PrimBuf[self->primIndex];

    for (i = 0; i < 2; prim = prim->next, i++) {
        prim->r0 = prim->b0 = prim->g0 = self->ext.teleport.unk90;
        prim->drawMode |= DRAW_HIDE;
        if (var_s5) {
            prim->drawMode &= ~DRAW_HIDE;
        }
    }

    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar - w;
    func_80124164(
        prim, self->ext.teleport.colorIntensity, yVar, h, upperParams);
    prim = prim->next;
    prim->x1 = prim->x3 = xVar;
    prim->x0 = prim->x2 = xVar + w;
    func_80124164(
        prim, self->ext.teleport.colorIntensity, yVar, h, upperParams);
    prim = prim->next;
    if (showParticles) {
        for (i = 0; i < LEN(D_8013839C); i++) {
            switch (prim->g0) {
            case 0:
                if (--prim->g1 == 0) {
                    prim->g0++;
                }
                break;
            case 1:
                xVar = D_8013839C[i].x;
                yVar = D_8013839C[i].y;
                result = func_80119E78(prim, xVar, yVar);
                D_8013839C[i].y -= 16;
                if (result < 0) {
                    prim->drawMode |= DRAW_HIDE;
                    prim->g0++;
                } else {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                break;
            }
            prim = prim->next;
        }
    } else {
        // @bug: should probably be doing prim = prim->next
        for (i = 0; i < LEN(D_8013839C); i++) {
            prim->drawMode |= DRAW_HIDE;
        }
    }
}

// Entity #66. Made by final blueprint, #122. Created in PlayerStepStand.
void EntityPlayerSleepZ(Entity* self) {
    if (PLAYER.step != Player_Stand || PLAYER.step_s != Player_Stand_ChairSit) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        self->animSet = ANIMSET_DRA(17);
        self->velocityY = FIX(-0.375);
        SetSpeedX(FIX(0.25));
        self->unk5A = 0x50;
        self->palette = PAL_FLAG(PAL_UNK_19F);
        self->anim = D_800AE294;

        self->posY.i.hi -= 16;
        self->posX.val += self->velocityX << 5;
        self->flags = FLAG_UNK_100000;
        self->facingLeft = 0;
        self->step++;
        break;

    case 1:
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->poseTimer < 0) {
            DestroyEntity(self);
        }
        break;
    }
}
