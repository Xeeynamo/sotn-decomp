#include "dra.h"
#include "objects.h"
#include "sfx.h"

u8 D_800AD4B8[] = {
    // TODO: move to 7A4D0.c
    0x20, 0x3F, 0x11, 0x2F, 0x20, 0x2F, 0x10, 0x10, 0x1C, 0x1F,
    0x19, 0x1F, 0x11, 0x1F, 0x11, 0x3F, 0x11, 0x3F, 0x2F, 0x2F,
};

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

extern u8 D_800B0188[];
AnimSoundEvent D_800AD53C = {
    // TODO: move to 7A4D0.c
    D_800AD520, D_800B0188, 0x0000, 0x060C, 0x24, 1,
};

u16 D_800AD54C[] = {
    0x0000, 0xFFFC, 0xFFF8, 0xFFF4, 0xFFF0, 0xFFEC,
};

s32 D_800AD558[] = {
    0xFFFFD000, 0xFFFFC000, 0xFFFFA000, 0xFFFF8000, 0xFFFF6000, 0xFFFF4000,
};

u16 D_800AD570[] = {
    0x0030, 0x0040, 0x0050, 0x0060, 0x0070, 0x0080,
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

u8 D_800AD5E0[] = {
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

s32 D_800AD630[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};

s32 D_800AD670[] = {
    0x00000000, 0x015F0000, 0x01000100, 0x00600100, 0x02000031, 0x00020000,
    0x015F0006, 0x01000100, 0x00100100, 0x02000031, 0x00000000, 0x015F0000,
    0x04000100, 0x00100400, 0x02000031, 0x00000000, 0x015F0000, 0x01007100,
    0x00107000, 0x02000031, 0x00000000, 0x015F0000, 0x70007100, 0x00100100,
    0x02000031, 0x00000000, 0x015F0000, 0x70000100, 0x00100200, 0x02000031,
    0x00000000, 0x015F0000, 0x70000100, 0x70010100, 0x01000031, 0x00000000,
    0x015F0000, 0x01000100, 0x00707000, 0x02000031, 0x00000000, 0x01030000,
    0x02000200, 0x00600080, 0x02000031, 0x00000000, 0x015F0000, 0x01000100,
    0x00100100, 0x02000031, 0x00020000, 0x015F0006, 0x01000100, 0x00600100,
    0x02000031, 0x00000000, 0x015F0000, 0x70000100, 0x00100100, 0x02000031,
    0x00000000, 0x015F0000, 0x01007100, 0x00107000, 0x02000031, 0x00000000,
    0x015F0000, 0x70007100, 0x00100100, 0x02000031, 0x00000000, 0x015F0000,
    0x01000400, 0x70040400, 0x02000031, 0x00000000, 0x015F0000, 0x70000100,
    0x70060200, 0x02000031, 0x00000000, 0x015F0000, 0x01000100, 0x00107000,
    0x02000031, 0x00000000, 0x01030000, 0x00807400, 0x00607400, 0x02000031,
    0x00000000, 0x015F0000, 0x01000200, 0x70030400, 0x02000031, 0x00000000,
    0x01660000, 0x01000100, 0x70050100, 0x02000031, 0x00000000, 0x015F0000,
    0x01000100, 0x00100100, 0x02000031, 0x00000000, 0x015F0000, 0x00C000C0,
    0x00100100, 0x02000031, 0x00000008, 0x01680004, 0x01000100, 0x70020100,
    0x01000051, 0x00020000, 0x01650009, 0x01000100, 0x70000100, 0x01800051,
    0x00000000, 0x015F0000, 0x08000200, 0x70070800, 0x02000031, 0x00000000,
    0x015F0000, 0x01000200, 0x70050200, 0x02000031, 0x00000000, 0x015F0000,
    0x01000100, 0x70050100, 0x02000031, 0x00000000, 0x015F0000, 0x01000100,
    0x70080100, 0x02000031, 0x00000000, 0x015F0000, 0x01000100, 0x70090100,
    0x02000031, 0x00000000, 0x015F0000, 0x01000100, 0x700A0100, 0x02000031,
    0x00000000, 0x015F0000, 0x01000100, 0x00107000, 0x02000031, 0x00000000,
    0x015F0000, 0x01000400, 0x00100400, 0x02000031, 0x00000000, 0x01000000,
    0x00400040, 0x00100040, 0x02000031, 0x00000000, 0x01000000, 0x00400040,
    0x00100040, 0x02000031, 0x00000008, 0x01650008, 0x01000100, 0x70070100,
    0x02000051, 0x00000000, 0x01000000, 0x00400040, 0x00100040, 0x02000031,
    0x00000000, 0x01000000, 0x00400040, 0x00100040, 0x02000031, 0x00000000,
    0x015F0000, 0x01000100, 0x700B0100, 0x02000031, 0x00000000, 0x01030000,
    0x01000100, 0x00100100, 0x02000031, 0x00020000, 0x01030006, 0x01000100,
    0x00100100, 0x02000031, 0x00000000, 0x01680000, 0x71007100, 0x70070200,
    0x02000031, 0x00000000, 0x015F0000, 0x01000100, 0x700C0100, 0x00000031,
};

s32 D_800AD9B8[] = {
    0x00FF0000, 0x010300FF, 0x00FF0031, 0x001F007F, 0x00310103, 0x001F003F,
    0x010300FF, 0x00000031, 0x001F003F, 0x00310103, 0x003F003F, 0x0103003F,
    0x00FF0031, 0x003F003F, 0x00310103, 0x003F001F, 0x0103007F, 0x007F0031,
    0x000F003F, 0x00310103, 0x007F00FF, 0x0103001F, 0x007F0031, 0x000F007F,
    0x00310103, 0x000F000F, 0x0103007F, 0x003F0031, 0x003F003F, 0x00310103,
    0x000F007F, 0x0103007F, 0x000F0031, 0x002F00FF, 0x00310103, 0x00FF002F,
    0x0103002F, 0x005F0031, 0x005F000F, 0x00310103, 0x003F007F, 0x0103000F,
    0x00FF0031, 0x000F000F, 0x00310103, 0x003F007F, 0x0103003F, 0x00000031,
    0x00FF00FF, 0x00310103, 0x003F00FF, 0x0103003F, 0x00FF0031, 0x003F003F,
    0x00310103, 0x007F007F, 0x0103007F, 0x00000031, 0x007F00FF, 0x00310103,
};

// clang-format off
#define UNK_FLAGS_GROUP_1 FLAG_HAS_PRIMS | FLAG_UNK_08000000
#define UNK_FLAGS_GROUP_2 FLAG_HAS_PRIMS | FLAG_UNK_04000000
#define UNK_FLAGS_GROUP_3 FLAG_HAS_PRIMS | FLAG_UNK_08000000 | FLAG_UNK_04000000
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

void func_8011E4BC(Entity* self) {
    byte stackpad[0x28];
    FakePrim* tilePrim;
    s16 randVar;
    s32 randAngleShift;
    s32 twelveShift;
    s32 i;
    u16 playerXpos;
    u16 playerYpos;
    u16 selfYPos;
    u16 selfXPos;
    u32 upperParams;
    unkStr_8011E4BC* temp_s5;
    s32 thickness;
    s32 var_a2;

    selfXPos = self->posX.i.hi;
    selfYPos = self->posY.i.hi;
    upperParams = self->params >> 8;
    temp_s5 = D_800ADB98[upperParams];
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
        i = 0;
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        while (1) {
            tilePrim->drawMode = temp_s5->drawMode;
            tilePrim->priority = PLAYER.zPriority + temp_s5->priority;
            if (tilePrim->next == NULL) {
                tilePrim->w = 0;
                tilePrim->x0 = 0;
                tilePrim->y0 = 0;
                tilePrim->drawMode &= ~DRAW_HIDE;
                break;
            }
            tilePrim->posX.i.hi = selfXPos;
            tilePrim->posY.i.hi = selfYPos;
            tilePrim->posY.i.lo = 0;
            tilePrim->posX.i.lo = 0;
            switch (temp_s5->unkA) {
            case 0:
                randVar = rand();
                randAngleShift = (randVar & 1) + 2;
                tilePrim->velocityX.val = (rcos(randVar) << randAngleShift);
                tilePrim->velocityY.val = -(rsin(randVar) << randAngleShift);
                break;
            case 1:
            case 9:
                tilePrim->velocityX.val = (((rand() & 0x1FF) - 0x100) << 8);
                tilePrim->velocityY.val = (((rand() & 0x1FF) - 0x100) << 8);
                break;
            case 2:
                tilePrim->velocityX.val = (((rand() * 2) - 0x8000) >> 1);
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                tilePrim->posX.val += (tilePrim->velocityX.val * 0x13);
                tilePrim->posY.i.hi = (selfYPos + (rand() & 7)) - 3;
                randVar = rand() & 0xF;
                tilePrim->delay = (randVar + 0x10);
                break;
            case 8:
                if (PLAYER.facingLeft) {
                    twelveShift = 12;
                } else {
                    twelveShift = -12;
                }
                tilePrim->velocityX.val = ((rand() * 4) + 0xFFFF0000);
                tilePrim->velocityY.val = -(rand() & 0x3FFF);
                // This ends up adding the unk18 to unk18.lo and twelveShift to
                // unk10.hi
                tilePrim->posX.val +=
                    ((tilePrim->velocityX.val * 0x23) + (twelveShift << 16));
                tilePrim->velocityX.val = (tilePrim->velocityX.val >> 2);
                tilePrim->posY.i.hi = selfYPos - (rand() & 0x1F);
                randVar = rand() & 0x1F;
                tilePrim->delay = (randVar + 0x10);
                break;
            case 3:
                tilePrim->posX.i.hi = (selfXPos + (rand() & 0xF)) - 7;
                tilePrim->posY.i.hi = selfYPos - (rand() & 0x1F);
                tilePrim->velocityY.val = 0xFFFF4000 - (rand() & 0x7FFF);
                if (self->ext.et_8011E4BC.unk8C != NULL) {
                    tilePrim->velocityX.val = self->ext.et_8011E4BC.unk8C->unk8;
                }
                tilePrim->delay = ((i * 2) + 0xF);
                break;
            case 4:
                tilePrim->posX.i.hi = (selfXPos + (rand() & 0x1F)) - 0x10;
                tilePrim->posY.i.hi = (selfYPos + (rand() & 0x1F)) - 0x14;
                randVar = rand() & 0x1F;
                tilePrim->velocityX.val = D_801396F8[randVar];
                tilePrim->velocityY.val = D_80139778[randVar];
                break;
            case 10:
                tilePrim->posX.i.hi = playerXpos;
                tilePrim->posY.i.hi = playerYpos;
                tilePrim->delay = 0x3F;
                tilePrim->velocityY.val = -(((i * i) << 0xC) + 0x4000);
                break;
            case 12:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                if (i < 10) {
                    tilePrim->velocityY.val = -((i * i * 0x1800) + 0x2000);
                } else {
                    tilePrim->velocityY.val =
                        ((i - 10) * (i - 10) * 0x1800) + 0x2000;
                }
                tilePrim->delay = 0x3F;
                break;
            case 13:
                tilePrim->posX.i.hi = selfXPos;
                tilePrim->posY.i.hi = selfYPos;
                tilePrim->velocityX.val = (rand() - 0x4000) >> 1;
                tilePrim->velocityY.val = -((rand() & 0x1FFF) + 0x6000);
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
            tilePrim = tilePrim->next;
            i++;
        }
        self->step++;
        break;
    case 1:
        switch (upperParams) {
        case 10:
            if (PLAYER.step != 0x22) {
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
            var_a2 = self->ext.et_8011E4BC.unk7C;
            if (var_a2 < 9) {
                thickness = 2;
            } else {
                thickness = 3;
            }
            if (var_a2 < 4) {
                thickness--;
            }
            break;
        }
        tilePrim = (FakePrim*)&g_PrimBuf[self->primIndex];
        while (1) {
            if (tilePrim->next == NULL) {
                tilePrim->w = 0;
                tilePrim->x0 = 0;
                tilePrim->y0 = 0;
                tilePrim->drawMode &= ~DRAW_HIDE;
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
                tilePrim->velocityY.val = (tilePrim->velocityY.val + 0x2800);
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
                tilePrim->velocityY.val = (tilePrim->velocityY.val + 0x1400);
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
                // There is probably a clever way to write this
                tilePrim->velocityY.val =
                    (tilePrim->velocityY.val - (tilePrim->velocityY.val >> 5));
                if (!(var_a2 & 7)) {
                    tilePrim->velocityX.val = (tilePrim->velocityX.val >> 1);
                    tilePrim->velocityY.val >>= 1;
                    if (var_a2 & 0x20) {
                        tilePrim->velocityY.val >>= 1;
                    }
                    if (var_a2 == 0x18) {
                        tilePrim->drawMode = 2;
                    }
                }
                tilePrim->h = thickness;
                tilePrim->w = thickness;
                break;
            case 13:
                if (tilePrim->timer == 0) {
                    tilePrim->drawMode &= ~DRAW_HIDE;
                    tilePrim->r0 -= 1;
                    tilePrim->g0 -= 1;
                    tilePrim->b0 -= 1;
                    tilePrim->posY.val += tilePrim->velocityY.val;
                    tilePrim->posX.val += tilePrim->velocityX.val;
                    if ((*D_80097448 == 0) ||
                        (((PLAYER.posY.i.hi - *D_80097448) + 0x19) >=
                         tilePrim->posY.i.hi)) {
                        tilePrim->drawMode |= DRAW_HIDE;
                    }
                } else {
                    tilePrim->timer--;
                }
                break;
            }
            tilePrim->x0 = tilePrim->posX.i.hi;
            tilePrim->y0 = tilePrim->posY.i.hi;
            tilePrim = tilePrim->next;
        }
        break;
    }
}

void func_8011EDA0(Entity* entity) {}

void func_8011EDA8(Entity* self) {
    u16 params = self->params;
    s16 paramsHi = self->params >> 8;
    s32 step = self->step;
    s32 rnd;

    switch (step) {
    case 0:
        if (paramsHi == 1) {
            self->rotX = 0xC0;
            self->rotY = 0xC0;
            self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
            self->animSet = ANIMSET_DRA(2);
            self->unk4C = D_800ADC10;
        }

        if ((paramsHi == 0) || (paramsHi == 2)) {
            if (params & 3) {
                self->unk4C = D_800ADBD4;
                self->rotX = 0x120;
                self->rotY = 0x120;
                self->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                self->animSet = ANIMSET_DRA(2);
            } else {
                self->animSet = ANIMSET_DRA(5);
                self->unk4C = D_800AD57C;
                self->palette = 0x8170;
            }
        }
        self->flags = FLAG_UNK_20000 | FLAG_UNK_100000 | FLAG_UNK_08000000;

        if (rand() % 4) {
            self->zPriority = PLAYER.zPriority + 2;
        } else {
            self->zPriority = PLAYER.zPriority - 2;
        }

        if (paramsHi == 2) {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() % 44) - 22;
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + (rand() & 15) - 8;
        }

        rnd = rand() & 31;
        self->posY.i.hi = PLAYER.posY.i.hi + PLAYER.hitboxOffY + rnd - 16;
        self->velocityY = FIX(-0.5);
        self->velocityX = PLAYER.velocityX >> 2;
        self->step++;
        break;

    case 1:
        self->rotX -= 4;
        self->rotY -= 4;
        self->posY.val += self->velocityY;
        self->posX.val += self->velocityX;
        if ((self->animFrameIdx == 8) && (self->unk4C != D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
            if (!(params & 1) && (self->animFrameDuration == step)) {
                CreateEntFactoryFromEntity(self, FACTORY(0x400, 4), 0);
            }
        }

        if ((self->animFrameIdx == 16) && (self->unk4C == D_800AD57C)) {
            self->drawMode = DRAW_TPAGE;
        }

        if (self->animFrameDuration < 0) {
            DestroyEntity(self);
        }
        break;
    }
}

// same as RIC/func_801601DC
void func_8011F074(Entity* entity) {
    s16 posX;
    s16 posY;

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_100000 | FLAG_UNK_20000 | FLAG_UNK_08000000;
        entity->unk5A = 0x79;
        entity->animSet = ANIMSET_DRA(14);
        entity->zPriority = PLAYER.zPriority + 2;
        entity->palette = 0x819F;

        if (D_8013808C & 1) {
            entity->drawMode = 0x70;
        } else {
            entity->drawMode = DRAW_TPAGE;
        }
        entity->rotY = 0x40;
        entity->rotX = 0x40;
        entity->unk4C = &D_800ADC44;
        D_8013808C++;
        entity->unk6C = 0xFF;
        entity->drawFlags =
            FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK10 | FLAG_DRAW_UNK20;
        posX = 10;
        posY = 15;
        entity->posY.i.hi = entity->posY.i.hi - posY + (rand() % 35);
        entity->posX.i.hi = entity->posX.i.hi - posX + (rand() % 20);
        entity->velocityY = -0x6000 - (rand() & 0x3FFF);
        entity->step++;
        break;

    case 1:
        if (entity->unk6C >= 17) {
            entity->unk6C += 248;
        }
        entity->posY.val += entity->velocityY;
        entity->rotX += 8;
        entity->rotY += 8;
        if (entity->animFrameDuration < 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

// effect when player takes lightning damage

void EntityHitByLightning(Entity* self) {
    Primitive* prevPrim;
    Primitive* prim;
    s16 temp_s0;
    s32 temp_s2;
    s16 xBase;
    s16 yBase;

    s16 tempAngle;
    s32 i;
    s16 temp_s1_2;
    s32 xOffset;
    s32 yOffset;
    bool var_s0 = false;

    if ((self->params & 0xFF00) != 0) {
        var_s0 = (++self->ext.hitbylightning.unk9C) > 0xA8;
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

        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS | FLAG_UNK_20000;
        self->ext.hitbylightning.unk7C =
            ((self->params & 0xF) << 9) + (rand() & 0x3F);
        self->ext.hitbylightning.unk80 = rand();
        self->ext.hitbylightning.unk82 = (rand() & 0x1FF) + 0x100;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->x0 = prim->x1 = prim->x2 = prim->x3 = self->posX.i.hi;
            prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;
            prim->tpage = 0x1A;
            prim->clut = D_800ADC7C[rand() & 1];
            prim->priority = PLAYER.zPriority - 2;
            prim->r0 = prim->g0 = prim->b0 = prim->r1 = prim->g1 = prim->b1 =
                prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 =
                    prim->b3 = 0x80;
            prim->drawMode = 0x133;
            prim = prim->next;
        }
        if ((PLAYER.velocityY != 0) && (PLAYER.step != 0x10)) {
            self->ext.hitbylightning.unk92 = 1;
        }
        self->ext.hitbylightning.unk94 = 0x10;
        PlaySfx(0x69D);
        PlaySfx(0x665);
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
            ((rsin(self->ext.hitbylightning.unk7C) * temp_s2) >> 7) * -7 << 1;
        self->posX.val = xOffset + PLAYER.posX.val;
        self->posY.val = yOffset + PLAYER.posY.val;
        if ((self->ext.hitbylightning.unk92 != 0) &&
            (g_Player.pl_vram_flag & 0xE)) {
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
                  self->ext.generic.unk98;
        self->posX.val = xOffset + PLAYER.posX.val;
        self->posY.val = yOffset + PLAYER.posY.val;
        self->ext.generic.unk98 -= 0x8000;
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
        prevPrim->u0 = prevPrim->u2 = (i * 0x10) - 0x70;
        prevPrim->u1 = prevPrim->u3 = ((i + 1) * 0x10) - 0x70;
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

    // FAKE: Annoying repeat of the access and bitmask
    tempAngle = self->ext.hitbylightning.unk80 & 0xFFF;
    if (((tempAngle) >= 0x400) &&
        ((self->ext.hitbylightning.unk80 & 0xFFF) < 0xC00)) {
        prim->priority = PLAYER.zPriority - 2;
    } else {
        prim->priority = PLAYER.zPriority + 2;
    }
    prim->u0 = prim->u2 = (i << 4) - 0x70;
    prim->v0 = prim->v1 = 0xC0;
    // FAKE but needed to duplicate the sll 4 instruction
    tempAngle = i;
    prim->u1 = prim->u3 = (tempAngle << 4) - 0x60;
    prim->v2 = prim->v3 = 0xCF;
}

// player gets frozen
void EntityHitByIce(Entity* self) {
    s32 i;
    Primitive* prim;
    s16 angle;
    s32 xShift1;
    s32 xShift2;
    s32 xShift3;
    s32 yShift1;
    s32 yShift2;
    s32 yShift3;
    s32 size;
    u32 primYshift;
    u16 selfX;
    u16 selfY;
    s16_pair* offset;
    bool sp18 = false;

    self->posX.i.hi = PLAYER.posX.i.hi;
    self->posY.i.hi = PLAYER.posY.i.hi;
    sp18 = (g_Player.unk0C & 0x10000) == sp18;
    switch (self->step) {
    case 0:
        self->primIndex = AllocPrimitives(PRIM_GT3, 24);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags = FLAG_HAS_PRIMS | FLAG_UNK_40000 | FLAG_UNK_20000;
        prim = &g_PrimBuf[self->primIndex];
        while (prim != NULL) {
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = (rand() & 0xF) + 0x30;
            prim->b0 = prim->b1 = prim->b2 = prim->b3 = rand() | 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = (rand() & 0x1F) + 0x30;
            if (rand() & 1) {
                prim->drawMode = 0x335;
            } else {
                prim->drawMode = 0x315;
            }
            prim->type = 3;
            prim->priority = PLAYER.zPriority + 2;
            prim = prim->next;
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
            if (PLAYER.facingLeft == 0) {
                self->rotZ = -0x100;
            } else {
                self->rotZ = 0x100;
            }
        } else {
            if (PLAYER.velocityX <= 0) {
                self->rotZ = 0xF80;
            } else {
                self->rotZ = 0x80;
            }
        }
        PlaySfx(0x69D);
        self->step++;
        break;
    case 1:
        if (self->ext.hitbyice.unk80 != 0 && --self->ext.hitbyice.unk82 == 0) {
            sp18 = true;
        }
        // Could rewrite as a series of && and || but that would probably reduce
        // readability
        if (self->ext.hitbyice.unk7E != 0) {
            if (g_Player.pl_vram_flag & 0xC) {
                sp18 = true;
            }
            if (PLAYER.step == Player_Hit && PLAYER.step_s == 5) {
                sp18 = true;
            }
        }
        if (sp18) {
            self->ext.hitbyice.unk7C = 0x40;
            PlaySfx(0x61A);
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
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; i < 24; i++) {
        offset = D_800ADCC8[i * 3];
        if (prim->u0 < 2) {
            size = SquareRoot12(
                ((offset->unk0 * offset->unk0) + (offset->unk2 * offset->unk2))
                << 0xC);
            angle = self->rotZ + ratan2(offset->unk2, offset->unk0);
            xShift1 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift1 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x0 = selfX + xShift1;
            prim->y0 = selfY + yShift1;

            offset = D_800ADCC8[i * 3 + 1];
            size = SquareRoot12(
                ((offset->unk0 * offset->unk0) + (offset->unk2 * offset->unk2))
                << 0xC);
            angle = self->rotZ + ratan2(offset->unk2, offset->unk0);
            xShift2 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift2 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x1 = selfX + xShift2;
            prim->y1 = selfY + yShift2;

            offset = D_800ADCC8[i * 3 + 2];
            size = SquareRoot12(
                ((offset->unk0 * offset->unk0) + (offset->unk2 * offset->unk2))
                << 0xC);
            angle = self->rotZ + ratan2(offset->unk2, offset->unk0);
            xShift3 = (((rcos(angle) >> 4) * size) + 0x80000) >> 0x14;
            yShift3 = (((rsin(angle) >> 4) * size) + 0x80000) >> 0x14;
            prim->x2 = prim->x3 = selfX + xShift3;
            prim->y2 = prim->y3 = selfY + yShift3;
        }
        if ((prim->u0 == 0) && (sp18 != 0)) {
            prim->u0++;
            prim->v0 = (rand() & 15) + 1;
        }
        if (prim->u0 == 1) {
            if (--prim->v0 == 0) {
                prim->v0 = 0x20;
                prim->u2 = 0xF0;
                prim->u0++;
            }
        }
        if (prim->u0 == 2) {
            if ((prim->u2 < 0x70) || (prim->u2 > 0xD0)) {
                prim->u2 += 4;
            }
            primYshift = (s8)prim->u2 >> 4;
            prim->y0 = primYshift + prim->y0;
            prim->y1 = primYshift + prim->y1;
            prim->y2 = primYshift + prim->y2;
            prim->y3 = primYshift + prim->y3;
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
            prim->drawMode |= 2;
            prim->drawMode &= ~0x300;
            self->flags |= FLAG_UNK_08000000;
            self->flags &= ~(FLAG_UNK_20000 | FLAG_UNK_40000);
            if (--prim->v0 == 0) {
                prim->drawMode |= 8;
            }
        }
        prim = prim->next;
    }
}

// Transparent white circle closes over player
// Entity ID #38. Created by blueprint 53. No known callers.
INCLUDE_ASM("dra/nonmatchings/7E4BC", EntityTransparentWhiteCircle);

// pink effect on player
INCLUDE_ASM("dra/nonmatchings/7E4BC", EntityPlayerPinkEffect);

// player dissolves into pixels
INCLUDE_ASM("dra/nonmatchings/7E4BC", EntityPlayerDissolves);

// level up animation
INCLUDE_ASM("dra/nonmatchings/7E4BC", EntityLevelUpAnimation);

void func_80121F14(s32 arg0, s32 arg1) {
    Unkstruct_80138094* ptr = D_80138094;
    s32 i;

    for (i = 0; i < 16; i++, ptr++) {
        ptr->posX.val = arg0 + ptr->posX.val;
        ptr->posY.val = arg1 + ptr->posY.val;
    }
}

INCLUDE_ASM("dra/nonmatchings/7E4BC", func_80121F58);

// spawns mist (player transform)
INCLUDE_ASM("dra/nonmatchings/7E4BC", EntityMist);

// Appears as D_800AD0C4[48].
void UnknownEntId48(Entity* self) {
    s32 params;

    params = (u8)self->params;
    if (!(g_Player.unk0C & PLAYER_STATUS_MIST_FORM)) {
        DestroyEntity(self);
        return;
    }
    if (!IsRelicActive(RELIC_GAS_CLOUD)) {
        self->hitboxState = 0;
    } else {
        self->hitboxState = 2;
    }
    if (self->step == 0) {
        func_8011A328(self, 0xC);
        self->enemyId = 4;
        self->hitboxHeight = 8;
        self->hitboxWidth = 8;
        self->flags = FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->step++;
    }
    if (params == 0) {
        self->posX.i.hi = (PLAYER.posX.i.hi + g_Entities[16].posX.i.hi) / 2;
        self->posY.i.hi = (PLAYER.posY.i.hi + g_Entities[16].posY.i.hi) / 2;
        self->hitboxWidth = self->hitboxHeight = 0x1C;
    } else {
        self->posX.i.hi = D_80138094[params - 1].posX.i.hi;
        self->posY.i.hi = D_80138094[params - 1].posY.i.hi;
    }
}

// Appears as D_800AD0C4[49].
void UnknownEntId49(Entity* self) {
    s32 x_offset;

    if (!(g_Player.unk0C & 0x01000000) || (PLAYER.step != 0x2B)) {
        DestroyEntity(self);
        return;
    }
    if (self->step == 0) {
        self->animSet = PLAYER.animSet;
        self->animCurFrame = 7;
        self->unk5A = PLAYER.unk5A;
        self->palette = PLAYER.palette;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority;
        self->flags = 0x04060000;
        self->step++;
    }
    self->drawFlags = PLAYER.drawFlags & FLAG_DRAW_UNK8;
    self->unk6C = PLAYER.unk6C;

    if (ABS(PLAYER.rotZ) == 0x200) {
        x_offset = PLAYER.entityRoomIndex != 0 ? 0x10 : -0x10;
        self->posX.i.hi = x_offset + PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 9 + ((g_GameTimer >> 1) & 1);
    } else {
        x_offset = PLAYER.entityRoomIndex != 0 ? 0x18 : -0x18;
        self->posX.i.hi = x_offset + PLAYER.posX.i.hi;
        self->posY.i.hi = PLAYER.posY.i.hi + 16 + ((g_GameTimer >> 1) & 1);
    }
}

void func_80123A60(Entity* entity) {
    Entity* player = &PLAYER;

    if (!(g_Player.unk0C & 0x01000000)) {
        DestroyEntity(entity);
        return;
    }

    entity->posX.i.hi = player->posX.i.hi;
    entity->posY.i.hi = player->posY.i.hi;
    if (entity->step == 0) {
        func_8011A328(entity, 0xB);
        entity->flags = FLAG_UNK_20000 | FLAG_UNK_40000 | FLAG_UNK_04000000;
        entity->step++;
    }

    if (player->animCurFrame == 5) {
        entity->hitboxWidth = 12;
        entity->hitboxHeight = 32;
        entity->hitboxOffX = 0x1C;
        entity->hitboxOffY = -0xC;
        return;
    }

    if (player->animCurFrame == 6) {
        entity->hitboxWidth = 10;
        entity->hitboxHeight = 10;
        entity->hitboxOffX = 0x1C;
        entity->hitboxOffY = 0x10;
        return;
    }

    DestroyEntity(entity);
}

INCLUDE_ASM("dra/nonmatchings/7E4BC", func_80123B40);

void func_80123F78(Entity* entity) {
    PlayerDraw* plDraw = &g_PlayerDraw[13];

    if (D_800973FC == 0) {
        plDraw->enableColorBlend = 0;
        DestroyEntity(entity);
        return;
    }

    switch (entity->step) {
    case 0:
        entity->flags = FLAG_UNK_10000 | FLAG_UNK_20000 | FLAG_UNK_04000000 |
                        FLAG_UNK_08000000;
        if (PLAYER.animSet != 1) {
            DestroyEntity(entity);
            break;
        }
        entity->animSet = ANIMSET_DRA(1);
        entity->animCurFrame = PLAYER.animCurFrame;
        entity->unk5A = 0xD;
        entity->drawFlags = PLAYER.drawFlags;
        entity->drawMode = 0x30;
        entity->palette = 0x815F;
        entity->zPriority = PLAYER.zPriority - 2;
        entity->facingLeft = PLAYER.facingLeft;

        plDraw->b0 = plDraw->b1 = plDraw->b2 = plDraw->b3 = 128;
        plDraw->g0 = plDraw->g1 = plDraw->g2 = plDraw->g3 = 128;
        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = 128;
        plDraw->enableColorBlend = true;
        entity->step++;
        break;

    case 1:
        plDraw->b3 += 255;
        if (plDraw->b3 < 4) {
            plDraw->enableColorBlend = 0;
            DestroyEntity(entity);
            break;
        }
        plDraw->r0 = plDraw->r1 = plDraw->r2 = plDraw->r3 = plDraw->g0 =
            plDraw->g1 = plDraw->g2 = plDraw->g3 = plDraw->b0 = plDraw->b1 =
                plDraw->b2 = plDraw->b3;
        break;
    }
}

// Corresponding RIC function is func_80165DD8
void func_80124164(
    POLY_GT4* poly, s32 colorIntensity, s32 y, s32 radius, bool arg4) {
    s16 top = y - radius;
    s16 bottom = y + radius;
    s32 colorChannel;

    poly->y1 = top;
    poly->y0 = top;

    poly->y3 = bottom;
    poly->y2 = bottom;

    if (poly->y0 < 0) {
        poly->y1 = 0;
        poly->y0 = 0;
    }

    if (poly->y0 > 240) {
        poly->y3 = 240;
        poly->y2 = 240;
    }

    if (arg4 == 0) {
        colorChannel = colorIntensity * D_800AE270[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[3];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[4];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[5];
    } else {
        colorChannel = colorIntensity * D_800AE270[0];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r3 = (u32)colorChannel >> 8;
        poly->r1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[1];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g3 = (u32)colorChannel >> 8;
        poly->g1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[2];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->b3 = (u32)colorChannel >> 8;
        poly->b1 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[6];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->r2 = (u32)colorChannel >> 8;
        poly->r0 = (u32)colorChannel >> 8;

        colorChannel = colorIntensity * D_800AE270[7];
        if (colorChannel < 0) {
            colorChannel += 255;
        }
        poly->g2 = (u32)colorChannel >> 8;
        poly->g0 = (u32)colorChannel >> 8;
        colorChannel = colorIntensity * D_800AE270[8];
    }
    if (colorChannel < 0) {
        colorChannel += 255;
    }
    poly->b2 = (u32)colorChannel >> 8;
    poly->b0 = (u32)colorChannel >> 8;
}
