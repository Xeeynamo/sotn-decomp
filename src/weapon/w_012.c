// Weapon ID #12. Used by weapons:
// Chakram, Vorpal blade, Crissaegrim
#include "weapon_private.h"
#include "w_012_1.h"
#include "w_012_2.h"
#define g_Animset w_012_1
#define g_Animset2 w_012_2

extern s32 D_58000_8017BB28;

static u16 D_58000_8017A2B0[] = {
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xE670,
    0xDDEE, 0xD58C, 0xC54A, 0xB508, 0xA8C6, 0x9884, 0x8C42, 0x0000, 0xAD54,
    0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xCD2B, 0xD58C, 0xDE0E,
    0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF, 0x0000, 0xAD54, 0xB5D6, 0xBE58,
    0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8C42, 0x9884, 0xA8C6, 0xB508, 0xC54A,
    0xD58C, 0xDDEE, 0xE670, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D,
    0xD7DF, 0xFFFF, 0x8000, 0x8C42, 0x9884, 0xA8C6, 0xB508, 0xC54A, 0xD58C,
    0xDDEE, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF,
    0x8000, 0x8000, 0x8C42, 0x9884, 0xA8C6, 0xB508, 0xC54A, 0xD58C, 0x0000,
    0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8000, 0x8000,
    0x8000, 0x8C42, 0x9884, 0xA8C6, 0xB508, 0xC54A, 0x0000, 0xAD54, 0xB5D6,
    0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8C42, 0x9884, 0xA8C6, 0xB508, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB,
    0xCF5D, 0xD7DF, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8C42,
    0x9884, 0xA8C6, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF,
    0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8C42, 0x9884,
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8C42,
};

static u16 D_58000_8017A3F0[] = {
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xA1C8, 0xC290, 0xD7DF, 0xFFFF, 0xA1C8,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0xAD54,
    0xB5D6, 0xBE58, 0xA5A8, 0xC270, 0xD7DF, 0xFFFF, 0x90C4, 0xA5A8, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58,
    0xA988, 0xC650, 0xD7DF, 0xFFFF, 0x8000, 0x94C4, 0xA988, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xAD68, 0xCA50,
    0xD7DF, 0xFFFF, 0x8000, 0x8000, 0x94A4, 0xAD68, 0x8000, 0x8000, 0x8000,
    0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xB148, 0xCA30, 0xD7DF, 0xFFFF,
    0x8000, 0x8000, 0x8000, 0x98A4, 0xB148, 0x8000, 0x8000, 0x8000, 0x0000,
    0xAD54, 0xB5D6, 0xBE58, 0xB528, 0xCE10, 0xD7DF, 0xFFFF, 0x8000, 0x8000,
    0x8000, 0x8000, 0x9884, 0xB528, 0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6,
    0xBE58, 0xB908, 0xD210, 0xD7DF, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x9C84, 0xB908, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xBCE8,
    0xD1F0, 0xD7DF, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x9C64, 0xBCE8, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xACA6, 0xC9CE, 0xD7DF,
    0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0xACA6,
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
};

static u16 D_58000_8017A530[] = {
    0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x8087,
    0x84A7, 0x88C7, 0x94E7, 0x9CE7, 0x9CE7, 0x9CE7, 0x9CE7, 0x0000, 0x99A6,
    0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x810F, 0x8D6F, 0x91AF,
    0xA9CF, 0xBDEF, 0xBDEF, 0xBDEF, 0xBDEF, 0x0000, 0x99A6, 0xAA0A, 0xBA6E,
    0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x8000, 0x8087, 0x84A7, 0x88C7, 0x94E7,
    0x9CE7, 0x9CE7, 0x9CE7, 0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37,
    0xEF9B, 0xFFFF, 0x8000, 0x8000, 0x810F, 0x8D6F, 0x91AF, 0xA9CF, 0xBDEF,
    0xBDEF, 0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF,
    0x8000, 0x8000, 0x8000, 0x8087, 0x84A7, 0x88C7, 0x94E7, 0x9CE7, 0x0000,
    0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x8000, 0x8000,
    0x8000, 0x8000, 0x810F, 0x8D6F, 0x91AF, 0xA9CF, 0x0000, 0x99A6, 0xAA0A,
    0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8087, 0x84A7, 0x88C7, 0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3,
    0xDF37, 0xEF9B, 0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x810F, 0x8D6F, 0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B,
    0xFFFF, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8087,
    0x0000, 0x99A6, 0xAA0A, 0xBA6E, 0xCED3, 0xDF37, 0xEF9B, 0xFFFF, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
};

static u16 D_58000_8017A670[] = {
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xCD2B,
    0xD58C, 0xDE0E, 0xE670, 0xEEF1, 0xF753, 0xFFD5, 0xFFFF, 0x0000, 0xAD54,
    0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xD6B5, 0xD68E, 0xCA0C,
    0xC18A, 0xB928, 0xB0C7, 0xA886, 0xA085, 0x0000, 0xAD54, 0xB5D6, 0xBE58,
    0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xD28F, 0xC60D, 0xBD8B, 0xB529, 0xACC8,
    0xA487, 0xA086, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D,
    0xD7DF, 0xFFFF, 0xC20E, 0xBDAD, 0xB54B, 0xACEA, 0xA4A9, 0xA088, 0x8000,
    0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF,
    0xB9CE, 0xB56D, 0xAD0B, 0xA4AA, 0xA089, 0x8000, 0x8000, 0x8000, 0x0000,
    0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xB18E, 0xAD2D,
    0xA4CC, 0xA08B, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6,
    0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0xAD4E, 0xA4CD, 0xA08C, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB,
    0xCF5D, 0xD7DF, 0xFFFF, 0xA4EF, 0xA08E, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF,
    0xFFFF, 0xA0B0, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x0000, 0xAD54, 0xB5D6, 0xBE58, 0xC6DB, 0xCF5D, 0xD7DF, 0xFFFF, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
};

static u16 D_58000_8017A7B0[] = {
    0x0000, 0x8821, 0x9484, 0x84C6, 0x814C, 0x9E36, 0x9EDB, 0x8C8D, 0xA174,
    0xAC85, 0xC0CC, 0xC96E, 0xD610, 0xDA93, 0xDF37, 0xEF59, 0x0000, 0xE040,
    0xE080, 0xE0C0, 0xE100, 0xE140, 0xE180, 0xE1C0, 0xE200, 0xE240, 0xE280,
    0xE2C0, 0xE300, 0xE340, 0xE380, 0xE3C0, 0x0000, 0xE044, 0xE084, 0xE0C4,
    0xE104, 0xE144, 0xE184, 0xE1C4, 0xE204, 0xE244, 0xE284, 0xE2C4, 0xE304,
    0xE344, 0xE384, 0xE3C4, 0x0000, 0xE048, 0xE088, 0xE0C8, 0xE108, 0xE148,
    0xE188, 0xE1C8, 0xE208, 0xE248, 0xE288, 0xE2C8, 0xE308, 0xE348, 0xE388,
    0xE3C8, 0x0000, 0xE04C, 0xE08C, 0xE0CC, 0xE10C, 0xE14C, 0xE18C, 0xE1CC,
    0xE20C, 0xE24C, 0xE28C, 0xE2CC, 0xE30C, 0xE34C, 0xE38C, 0xE3CC, 0x0000,
    0xE050, 0xE090, 0xE0D0, 0xE110, 0xE150, 0xE190, 0xE1D0, 0xE210, 0xE250,
    0xE290, 0xE2D0, 0xE310, 0xE350, 0xE390, 0xE3D0, 0x0000, 0xE054, 0xE094,
    0xE0D4, 0xE114, 0xE154, 0xE194, 0xE1D4, 0xE214, 0xE254, 0xE294, 0xE2D4,
    0xE314, 0xE354, 0xE394, 0xE3D4, 0x0000, 0xE058, 0xE098, 0xE0D8, 0xE118,
    0xE158, 0xE198, 0xE1D8, 0xE218, 0xE258, 0xE298, 0xE2D8, 0xE318, 0xE358,
    0xE398, 0xE3D8, 0x0000, 0xE05C, 0xE09C, 0xE0DC, 0xE11C, 0xE15C, 0xE19C,
    0xE1DC, 0xE21C, 0xE25C, 0xE29C, 0xE2DC, 0xE31C, 0xE35C, 0xE39C, 0xE3DC,
    0x0000, 0x8821, 0xB5AD, 0xD6B5, 0x8148, 0x9E31, 0x801F, 0xA08C, 0xC192,
    0xA4A7, 0xB0C7, 0xBD28, 0xC98A, 0xD1CC, 0xDA4D, 0xE2D0, 0x0000, 0x8C25,
    0x9C68, 0xA0CD, 0xAD30, 0xAD93, 0xADF6, 0xC699, 0xE800, 0x8000, 0xA507,
    0xB149, 0xBDAC, 0xCA0F, 0xD672, 0xE2D5, 0x0000, 0x9444, 0xC255, 0xA94B,
    0xA5AD, 0x9189, 0xA316, 0xA087, 0xB509, 0xBDAC, 0x9CE7, 0xB18C, 0xC631,
    0xD6B5, 0xEB5A, 0xFFFF, 0x0000, 0x0421, 0x0C60, 0x08A7, 0x090B, 0x1DF4,
    0x4AF9, 0x5100, 0x69E6, 0x2316, 0x1884, 0x2D27, 0x3DAC, 0x5251, 0x5EB4,
    0x6F38, 0x0000, 0x8000, 0x8820, 0x9041, 0x9C81, 0xA4A2, 0xB0E2, 0xB903,
    0xC544, 0xC986, 0xCDC9, 0xD60C, 0xDA4F, 0xE292, 0xE6D5, 0xEF38, 0x0000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x0000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x0000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
    0x8000, 0x8000, 0x8000, 0x8000, 0x8000, 0x8000,
};

static u16* g_WeaponCluts[] = {
    D_58000_8017A2B0, D_58000_8017A3F0, D_58000_8017A530,
    D_58000_8017A670, D_58000_8017A7B0, D_58000_8017A2B0,
};

static s32 g_HandId = HAND_ID;

#include "shared.h"

static void EntityWeaponAttack(Entity* self) {
    Primitive* prim;
    u16 maskedParams;
    s32 clut;
    s32 var_v0;
    u8 width;

    maskedParams = self->params & 0x7F00;
    if (g_HandId != 0) {
        width = 0x80;
        clut = 0x18;
    } else {
        clut = 0;
        width = 0;
    }

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[self->primIndex];

        self->posX.val = PLAYER.posX.val;
        self->posY.val = PLAYER.posY.val;
        self->facingLeft = PLAYER.facingLeft;

        self->ext.sword.unk90 = 0xB;
        self->ext.sword.unk94 = 0xB;
        self->ext.sword.unk92 = 0x4B;
        self->ext.sword.unk96 = 0x4B;
        self->ext.sword.unk88 = -0x27;
        self->ext.sword.unk98 = -0x27;
        self->ext.sword.unk8A = 0x19;
        self->ext.sword.unk9A = 0x19;
        self->ext.sword.unkA0 = 0;

        if (PLAYER.step == 2) {
            if (PLAYER.step_s != PLAYER.step) {
                self->ext.sword.unkA0 = 0x18;
            }
        }

        self->ext.sword.unk86 = D_58000_8017BB28 % 3;
        if (self->ext.sword.unk86 == 1) {
            self->ext.sword.unk82 = -2;
            self->ext.sword.unk84 = -1;
            self->ext.sword.unk9C = self->ext.sword.unk9E = 0;
            self->ext.sword.unk98 = -self->ext.sword.unk98;
            self->ext.sword.unk9A = -self->ext.sword.unk9A;
            self->ext.sword.unk88 = -self->ext.sword.unk88;
            self->ext.sword.unk8A = -self->ext.sword.unk8A;
            self->ext.sword.unk94 = self->ext.sword.unk94 - 0x10;
            if (self->ext.sword.unkA0 != 0) {
                self->ext.sword.unk9C = -0x10;
            }
        }
        if (self->ext.sword.unk86 == 0) {
            self->ext.sword.unk82 = 2;
            self->ext.sword.unk84 = 1;
            self->ext.sword.unk9C = self->ext.sword.unk9E = 0;
            self->ext.sword.unk90 = self->ext.sword.unk90 - 0x10;
            if (self->ext.sword.unkA0 != 0) {
                self->ext.sword.unk9E = 0x10;
            }
        }
        if (self->ext.sword.unk86 == 2) {
            self->ext.sword.unk82 = self->ext.sword.unk84 = 1;
            self->ext.sword.unk9E = self->ext.sword.unk9C = 0x10;
        }
        if (self->facingLeft) {
            self->ext.sword.unk90 = -self->ext.sword.unk90;
            self->ext.sword.unk92 = -self->ext.sword.unk92;
            self->ext.sword.unk94 = -self->ext.sword.unk94;
            self->ext.sword.unk96 = -self->ext.sword.unk96;
        }

        if (maskedParams == 0x100 || maskedParams == 0x200) {
            SetSpeedX(FIX(4));
            self->posX.val -= self->velocityX * 4;
        }

        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (maskedParams == 0x200) {
            prim->g0 = prim->b0 = prim->r0 = prim->g1 = prim->b1 = prim->r1 =
                prim->g2 = prim->b2 = prim->r2 = prim->g3 = prim->b3 =
                    prim->r3 = 0x80;
            prim->drawMode |= DRAW_COLORS;
        }
        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        SetWeaponProperties(self, 0);
        self->hitboxOffX = 0x2B;
        self->hitboxWidth = 0x1E;
        self->hitboxOffY = self->ext.sword.unkA0 - 6;
        self->hitboxHeight = 0x1C - (self->ext.sword.unkA0 / 2);
        DestroyEntityWeapon(true);

        prim->u0 = 0;
        prim->v0 = width;
        prim->u1 = 0x40;
        prim->v1 = width;
        prim->v2 = width + 0x40;
        prim->v3 = width + 0x40;
        prim->u2 = 0;
        prim->u3 = 0x40;
        prim->tpage = 0x19;
        prim->clut = clut + 0x110;
        prim->priority = PLAYER.zPriority + 2;

        D_58000_8017BB28++;
        g_api.PlaySfx(SFX_WEAPON_SWISH_B);
        g_Player.D_80072F00[9] = 4;
        self->step++;
    } else {
        if (maskedParams == 0x100) {
            DecelerateX(FIX(0.1875));
        }
        if (maskedParams == 0x200) {
            DecelerateX(FIX(0.0625));
        }
        self->posX.val += self->velocityX;

        prim = &g_PrimBuf[self->primIndex];
        prim->clut++;
    }

    if (self->params & 0x8000) {
        var_v0 = prim->clut < 0x132;
    } else {
        var_v0 = prim->clut < 0x11A;
    }
    if (var_v0 == 0) {
        DestroyEntity(self);
        return;
    }

    if (maskedParams == 0x100 || maskedParams == 0x200) {
        self->ext.sword.unk9C += self->ext.sword.unk82;
        self->ext.sword.unk9E += self->ext.sword.unk84;
        if (maskedParams == 0x200) {
            if (self->velocityX < 0) {
                self->ext.sword.unk90 -= 7;
                self->ext.sword.unk94 -= 7;
            } else {
                self->ext.sword.unk90 += 7;
                self->ext.sword.unk94 += 7;
            }
        }
    }
    prim->x0 = self->posX.i.hi + self->ext.sword.unk90;
    prim->x1 = self->posX.i.hi + self->ext.sword.unk92;
    prim->x2 = self->posX.i.hi + self->ext.sword.unk94;
    prim->x3 = self->posX.i.hi + self->ext.sword.unk96;
    prim->y0 = self->posY.i.hi + self->ext.sword.unk98 + self->ext.sword.unkA0 +
               self->ext.sword.unk9C;
    prim->y1 = self->posY.i.hi + self->ext.sword.unk88 + self->ext.sword.unkA0 +
               self->ext.sword.unk9C;
    prim->y2 = self->posY.i.hi + self->ext.sword.unk9A + self->ext.sword.unkA0 -
               self->ext.sword.unk9E;
    prim->y3 = self->posY.i.hi + self->ext.sword.unk8A + self->ext.sword.unkA0 -
               self->ext.sword.unk9E;
}

/* similar to func_ptr_80170004_w_034 */
static s32 func_ptr_80170004(Entity* self) {
    s16 xDiff;
    s16 yDiff;
    s16 offsetY;
    s16 var_s1;
    s16 xVar;
    s16 yVar;
    s16 angleTarget;
    s16 angleDiff;
    s16 angle;

    switch (self->step) {
    case 0:
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->unk5A = 0x66;
            self->animSet += 2;
        }
        self->animCurFrame = 3;
        self->facingLeft = PLAYER.facingLeft;
        self->zPriority = PLAYER.zPriority - 2;
        self->palette = 0x100;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        SetSpeedX(((rand() & FIX(0.25) - 1) * 2) | FIX(4.5));
        self->ext.weapon_012.unk7E = 0x1C;
        offsetY = PLAYER.posY.i.hi + PLAYER.hitboxOffY;
        self->posY.i.hi = offsetY - 8;
        if (PLAYER.step != 2) {
            self->posY.i.hi = offsetY - 0x10;
        }
        if (self->facingLeft != 0) {
            self->posX.i.hi = PLAYER.posX.i.hi - PLAYER.hitboxOffX;
            self->ext.weapon_012.unk7C = FIX(0.15625);
        } else {
            self->posX.i.hi = PLAYER.posX.i.hi + PLAYER.hitboxOffX;
            self->ext.weapon_012.unk7C = FIX(-0.15625);
        }
        self->velocityX += PLAYER.velocityX;
        self->ext.weapon_012.unk84 = 0x80;
        self->velocityY = ((rand() & FIX(0.5) - 1) * 2) + FIX(2);
        self->ext.weapon_012.unk86 = FIX(-0.125);
        SetWeaponProperties(self, 0);
        DestroyEntityWeapon(true);
        self->hitboxHeight = 4;
        self->hitboxWidth = 4;
        g_Player.D_80072F00[10] = 4;
        self->ext.weapon_012.vol = 0x60;
        self->step++;
        break;
    case 1:
        if (!(self->ext.weapon_012.unk9C & 7)) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_A, self->ext.weapon_012.vol, 0);
        }
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        self->velocityX += self->ext.weapon_012.unk7C;
        self->velocityY += self->ext.weapon_012.unk86;
        self->ext.weapon_012.unk86 -= FIX(7.0 / 1024);
        if (self->ext.weapon_012.unk7E == 4) {
            self->animCurFrame++;
        }
        if (--self->ext.weapon_012.unk7E == 0) {
            self->ext.weapon_012.unk82 =
                ratan2(-self->velocityY, self->velocityX) & 0xFFF;
            self->animCurFrame++;
            self->step++;
        }
        break;
    case 2:
        var_s1 = self->ext.weapon_012.unk84;
        self->ext.weapon_012.unk84 += 0x10;
        xDiff = abs((PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi);
        if (xDiff < (PLAYER.hitboxWidth + self->hitboxWidth) >> 1) {
            yDiff =
                abs((PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi);
            if (yDiff < (PLAYER.hitboxHeight + self->hitboxHeight) >> 1) {
                DestroyEntity(self);
                return;
            }
        }

        xVar = (PLAYER.posX.i.hi + PLAYER.hitboxOffX) - self->posX.i.hi;
        yVar = (PLAYER.posY.i.hi + PLAYER.hitboxOffY) - self->posY.i.hi;
        angleTarget = ratan2(-yVar, xVar) & 0xFFF;
        angle = self->ext.weapon_012.unk82 & 0xFFF;
        angleDiff = abs(angle - angleTarget);
        if (var_s1 > angleDiff) {
            var_s1 = angleDiff;
        }
        if (angle < angleTarget) {
            if (angleDiff < 0x800) {
                angle += var_s1;
            } else {
                angle -= var_s1;
            }
        } else {
            if (angleDiff < 0x800) {
                angle -= var_s1;
            } else {
                angle += var_s1;
            }
        }
        self->ext.weapon_012.unk82 = angle & 0xFFF;
        self->facingLeft = 0;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        self->rotZ = 0x800 - self->ext.weapon_012.unk82;
        self->posX.val += rcos(self->ext.weapon_012.unk82) << 6;
        self->posY.val -= rsin(self->ext.weapon_012.unk82) << 6;
        if (!(self->ext.weapon_012.unk9C & 7)) {
            g_api.PlaySfxVolPan(
                SFX_WEAPON_SWISH_A, self->ext.weapon_012.vol, 0);
            self->ext.weapon_012.vol -= 0xC;
            if (self->ext.weapon_012.vol < 0) {
                self->ext.weapon_012.vol = 0;
            }
        }
        break;
    }

    if (!(g_GameTimer & 3)) {
        g_api.CreateEntFactoryFromEntity(self, WFACTORY(0x40, 0), 0);
    }
    self->ext.weapon_012.unk9C++;
}

static void func_ptr_80170008(Entity* self) {
    if (self->step == 0) {
        if (self->ext.weapon.parent->entityId == 0) {
            DestroyEntity(self);
            return;
        }
        self->animCurFrame = self->ext.weapon.parent->animCurFrame;
        self->animSet = self->ext.weapon.parent->animSet;
        self->facingLeft = self->ext.weapon.parent->facingLeft;
        self->unk5A = self->ext.weapon.parent->unk5A;
        self->zPriority = PLAYER.zPriority - 4;
        self->flags = FLAG_UNK_08000000 | FLAG_UNK_04000000 | FLAG_UNK_20000;
        self->palette = self->ext.weapon.parent->palette;
        self->drawFlags = self->ext.weapon.parent->drawFlags + FLAG_DRAW_UNK8;
        self->rotZ = self->ext.weapon.parent->rotZ;
        self->unk6C = 0x80;
        self->step++;
    }
    if (self->unk6C >= 48) {
        self->unk6C -= 8;
        return;
    }
    DestroyEntity(self);
}

static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 12; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
