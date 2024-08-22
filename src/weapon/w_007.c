// SPDX-License-Identifier: AGPL-3.0-or-later
// Weapon ID #7. Used by weapons:
// Shield rod, Unknown#173
#define FUNC_04_VOID
#include "weapon_private.h"
#include "w_007_1.h"
#include "w_007_2.h"
#define g_Animset w_007_1
#define g_Animset2 w_007_2

static u16 D_35000_8017A884[] = {
    COLOR16(0, 0, 0, 0),    COLOR16(4, 4, 5, 0),    COLOR16(0, 0, 0, 1),
    COLOR16(9, 2, 1, 0),    COLOR16(16, 11, 9, 0),  COLOR16(19, 17, 14, 0),
    COLOR16(15, 4, 5, 0),   COLOR16(19, 6, 12, 0),  COLOR16(26, 11, 8, 0),
    COLOR16(26, 21, 7, 0),  COLOR16(2, 2, 2, 0),    COLOR16(6, 6, 6, 0),
    COLOR16(10, 10, 10, 0), COLOR16(15, 15, 16, 0), COLOR16(20, 20, 21, 0),
    COLOR16(25, 26, 27, 0), COLOR16(0, 0, 0, 0),    COLOR16(0, 2, 29, 0),
    COLOR16(0, 11, 31, 0),  COLOR16(0, 21, 31, 0),  COLOR16(3, 28, 31, 0),
    COLOR16(9, 11, 14, 0),  COLOR16(16, 13, 22, 0), COLOR16(16, 0, 7, 0),
    COLOR16(26, 11, 7, 0),  COLOR16(31, 26, 7, 0),  COLOR16(2, 2, 2, 0),
    COLOR16(6, 6, 6, 0),    COLOR16(10, 10, 10, 0), COLOR16(15, 15, 16, 0),
    COLOR16(20, 20, 21, 0), COLOR16(25, 28, 27, 0), COLOR16(0, 0, 0, 0),
    COLOR16(4, 10, 13, 1),  COLOR16(8, 13, 17, 1),  COLOR16(9, 5, 5, 0),
    COLOR16(13, 10, 8, 0),  COLOR16(23, 16, 8, 0),  COLOR16(28, 22, 13, 0),
    COLOR16(4, 5, 7, 0),    COLOR16(5, 7, 12, 0),   COLOR16(8, 12, 18, 0),
    COLOR16(21, 19, 11, 0), COLOR16(14, 15, 7, 0),  COLOR16(7, 8, 9, 0),
    COLOR16(10, 12, 13, 0), COLOR16(14, 16, 18, 0), COLOR16(20, 22, 22, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(0, 18, 11, 0),  COLOR16(0, 26, 12, 0),
    COLOR16(16, 31, 18, 0), COLOR16(27, 31, 14, 0), COLOR16(9, 11, 14, 0),
    COLOR16(16, 13, 22, 0), COLOR16(2, 9, 11, 0),   COLOR16(5, 15, 15, 0),
    COLOR16(23, 30, 20, 0), COLOR16(2, 2, 2, 0),    COLOR16(6, 6, 6, 0),
    COLOR16(10, 10, 10, 0), COLOR16(15, 15, 16, 0), COLOR16(20, 20, 21, 0),
    COLOR16(25, 28, 27, 0), COLOR16(0, 0, 0, 0),    COLOR16(0, 18, 11, 0),
    COLOR16(0, 26, 12, 0),  COLOR16(16, 31, 18, 0), COLOR16(27, 31, 14, 0),
    COLOR16(9, 11, 14, 0),  COLOR16(16, 13, 22, 0), COLOR16(2, 9, 11, 0),
    COLOR16(5, 15, 15, 0),  COLOR16(23, 30, 20, 0), COLOR16(2, 2, 2, 0),
    COLOR16(6, 6, 6, 0),    COLOR16(10, 10, 10, 0), COLOR16(15, 15, 16, 0),
    COLOR16(20, 20, 21, 0), COLOR16(25, 28, 27, 0), COLOR16(0, 0, 0, 0),
    COLOR16(4, 4, 5, 0),    COLOR16(0, 0, 0, 1),    COLOR16(6, 2, 1, 0),
    COLOR16(9, 7, 14, 0),   COLOR16(11, 10, 17, 0), COLOR16(15, 4, 5, 0),
    COLOR16(0, 31, 1, 0),   COLOR16(0, 31, 0, 0),   COLOR16(0, 31, 0, 0),
    COLOR16(2, 2, 2, 0),    COLOR16(3, 5, 8, 0),    COLOR16(7, 9, 11, 0),
    COLOR16(13, 14, 16, 0), COLOR16(20, 20, 21, 0), COLOR16(25, 28, 30, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(31, 12, 1, 0),  COLOR16(31, 17, 10, 0),
    COLOR16(31, 28, 14, 0), COLOR16(31, 31, 23, 0), COLOR16(17, 11, 4, 0),
    COLOR16(23, 15, 8, 0),  COLOR16(16, 0, 7, 0),   COLOR16(26, 11, 7, 0),
    COLOR16(31, 26, 7, 0),  COLOR16(2, 2, 2, 0),    COLOR16(6, 6, 6, 0),
    COLOR16(10, 10, 10, 0), COLOR16(15, 15, 16, 0), COLOR16(20, 20, 21, 0),
    COLOR16(25, 28, 27, 0), COLOR16(0, 0, 0, 0),    COLOR16(1, 2, 4, 0),
    COLOR16(6, 5, 31, 0),   COLOR16(6, 1, 27, 0),   COLOR16(6, 12, 22, 0),
    COLOR16(6, 2, 22, 0),   COLOR16(8, 5, 22, 0),   COLOR16(10, 8, 22, 0),
    COLOR16(12, 12, 22, 0), COLOR16(14, 15, 22, 0), COLOR16(16, 18, 22, 0),
    COLOR16(18, 22, 22, 0), COLOR16(11, 19, 27, 0), COLOR16(9, 26, 23, 0),
    COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0), COLOR16(0, 0, 0, 0),
    COLOR16(1, 3, 8, 0),    COLOR16(5, 4, 28, 0),   COLOR16(4, 1, 23, 0),
    COLOR16(18, 22, 22, 0), COLOR16(6, 12, 22, 0),  COLOR16(6, 2, 22, 0),
    COLOR16(8, 5, 22, 0),   COLOR16(10, 8, 22, 0),  COLOR16(12, 12, 22, 0),
    COLOR16(14, 15, 22, 0), COLOR16(16, 18, 22, 0), COLOR16(9, 26, 23, 0),
    COLOR16(26, 27, 29, 0), COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(1, 2, 4, 0),    COLOR16(4, 3, 25, 0),
    COLOR16(3, 1, 19, 0),   COLOR16(16, 18, 22, 0), COLOR16(18, 22, 22, 0),
    COLOR16(6, 12, 22, 0),  COLOR16(6, 2, 22, 0),   COLOR16(8, 5, 22, 0),
    COLOR16(10, 8, 22, 0),  COLOR16(12, 12, 22, 0), COLOR16(14, 15, 22, 0),
    COLOR16(11, 19, 27, 0), COLOR16(9, 26, 23, 0),  COLOR16(7, 5, 16, 0),
    COLOR16(10, 12, 22, 0), COLOR16(0, 0, 0, 0),    COLOR16(1, 3, 8, 0),
    COLOR16(3, 2, 22, 0),   COLOR16(2, 1, 15, 0),   COLOR16(14, 15, 22, 0),
    COLOR16(16, 18, 22, 0), COLOR16(18, 22, 22, 0), COLOR16(6, 12, 22, 0),
    COLOR16(6, 2, 22, 0),   COLOR16(8, 5, 22, 0),   COLOR16(10, 8, 22, 0),
    COLOR16(12, 12, 22, 0), COLOR16(9, 26, 23, 0),  COLOR16(26, 27, 29, 0),
    COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0), COLOR16(0, 0, 0, 0),
    COLOR16(1, 2, 4, 0),    COLOR16(3, 1, 19, 0),   COLOR16(1, 2, 12, 0),
    COLOR16(12, 12, 22, 0), COLOR16(14, 15, 22, 0), COLOR16(16, 18, 22, 0),
    COLOR16(18, 22, 22, 0), COLOR16(6, 12, 22, 0),  COLOR16(6, 2, 22, 0),
    COLOR16(8, 5, 22, 0),   COLOR16(10, 8, 22, 0),  COLOR16(11, 19, 27, 0),
    COLOR16(9, 26, 23, 0),  COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(1, 3, 8, 0),    COLOR16(3, 2, 22, 0),
    COLOR16(2, 1, 15, 0),   COLOR16(10, 8, 22, 0),  COLOR16(12, 12, 22, 0),
    COLOR16(14, 15, 22, 0), COLOR16(16, 18, 22, 0), COLOR16(18, 22, 22, 0),
    COLOR16(6, 12, 22, 0),  COLOR16(6, 2, 22, 0),   COLOR16(8, 5, 22, 0),
    COLOR16(9, 26, 23, 0),  COLOR16(26, 27, 29, 0), COLOR16(7, 5, 16, 0),
    COLOR16(10, 12, 22, 0), COLOR16(0, 0, 0, 0),    COLOR16(1, 2, 4, 0),
    COLOR16(4, 3, 25, 0),   COLOR16(3, 1, 19, 0),   COLOR16(8, 5, 22, 0),
    COLOR16(10, 8, 22, 0),  COLOR16(12, 12, 22, 0), COLOR16(14, 15, 22, 0),
    COLOR16(16, 18, 22, 0), COLOR16(18, 22, 22, 0), COLOR16(6, 12, 22, 0),
    COLOR16(6, 2, 22, 0),   COLOR16(11, 19, 27, 0), COLOR16(9, 26, 23, 0),
    COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0), COLOR16(0, 0, 0, 0),
    COLOR16(1, 3, 8, 0),    COLOR16(5, 4, 28, 0),   COLOR16(4, 1, 23, 0),
    COLOR16(6, 2, 22, 0),   COLOR16(8, 5, 22, 0),   COLOR16(10, 8, 22, 0),
    COLOR16(12, 12, 22, 0), COLOR16(14, 15, 22, 0), COLOR16(16, 18, 22, 0),
    COLOR16(18, 22, 22, 0), COLOR16(6, 12, 22, 0),  COLOR16(9, 26, 23, 0),
    COLOR16(26, 27, 29, 0), COLOR16(7, 5, 16, 0),   COLOR16(10, 12, 22, 0),
    COLOR16(0, 0, 0, 0),    COLOR16(1, 2, 3, 0),    COLOR16(3, 31, 6, 0),
    COLOR16(10, 12, 15, 0), COLOR16(1, 5, 11, 0),   COLOR16(3, 8, 17, 0),
    COLOR16(7, 13, 22, 0),  COLOR16(11, 17, 23, 0), COLOR16(15, 21, 24, 0),
    COLOR16(4, 4, 4, 0),    COLOR16(8, 8, 7, 0),    COLOR16(12, 11, 10, 0),
    COLOR16(16, 15, 14, 0), COLOR16(20, 18, 17, 0), COLOR16(24, 22, 20, 0),
    COLOR16(28, 26, 24, 0), COLOR16(0, 0, 0, 0),    COLOR16(0, 0, 15, 0),
    COLOR16(0, 0, 18, 0),   COLOR16(3, 9, 22, 0),   COLOR16(8, 14, 27, 0),
    COLOR16(17, 22, 31, 0), COLOR16(19, 27, 31, 0), COLOR16(31, 31, 31, 0),
    COLOR16(0, 0, 1, 0),    COLOR16(13, 13, 15, 0), COLOR16(16, 16, 19, 0),
    COLOR16(22, 22, 25, 0), COLOR16(26, 26, 28, 0), COLOR16(0, 0, 0, 1),
    COLOR16(21, 29, 31, 0), COLOR16(0, 0, 1, 0)};

static u16 D_35000_8017AAA4[] = {
    0x2A01, 0x2C02, 0x0403, 0x2E04, 0x3005, 0x3206, 0x0807,
    0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF,
};

static u16 D_35000_8017AAC0[] = {
    0x360E, 0x380F, 0x0E10, 0x3A11, 0x3C12, 0x3E13, 0x1214,
    0x1215, 0x1216, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF,
};

static u16 D_35000_8017AADC[] = {
    0x360E, 0x380F, 0x4217, 0x4418, 0x4419, 0x461A, 0x1A1B,
    0x1A1C, 0x1A1D, 0x401E, 0x401F, 0x4020, 0x4021, 0xFFFF,
};

static u16 D_35000_8017AAF8[] = {
    0x2A01, 0x2C02, 0x0403, 0x2E04, 0x3005, 0x3206, 0x0807,
    0x0808, 0x0809, 0x340A, 0x340B, 0x340C, 0x340D, 0xFFFF,
};

static u16 D_35000_8017AB14[] = {
    0x482C, 0x4A2D, 0x042E, 0x4C2F, 0x4E30, 0x5031,
    0x0832, 0x0833, 0x0834, 0x523C, 0xFFFF, 0x0000,
};

static u16 D_35000_8017AB2C[] = {
    0x482C, 0x4A2D, 0x5435, 0x5636, 0x5637, 0x5838,
    0x2239, 0x223A, 0x223B, 0x523C, 0xFFFF, 0x0000,
};

static AnimationFrame D_35000_8017AB44[] = {
    {4, FRAME(0x3D, 0x24)},
    {4, FRAME(0x3E, 0x24)},
    {4, FRAME(0x3F, 0x24)},
    {4, FRAME(0x40, 0x24)},
    A_LOOP_AT(0)};

static s8 D_35000_8017AB58[] = {
    0x00, 0x00, 0x00, 0x00, 0xFD, 0xE6, 0x0C, 0x04, 0x1A, 0xE5, 0x10, 0x06,
    0x28, 0xEE, 0x08, 0x08, 0x11, 0xF7, 0x0C, 0x08, 0xF1, 0xFC, 0x04, 0x04,
    0xF6, 0xF8, 0x0C, 0x04, 0x13, 0xF5, 0x10, 0x08, 0x20, 0xFF, 0x08, 0x08,
    0x0F, 0x08, 0x0C, 0x08, 0x16, 0x03, 0x12, 0x04, 0x11, 0x02, 0x0C, 0x0C,
    0x1D, 0x13, 0x08, 0x08, 0x0B, 0x12, 0x0C, 0x08, 0xE9, 0x0E, 0x04, 0x04,
    0xF2, 0xE4, 0x0C, 0x04, 0x18, 0x04, 0x14, 0x0C, 0x06, 0xFD, 0x10, 0x08,
    0x01, 0x00, 0x08, 0x08, 0x00, 0x00, 0x0F, 0x0F, 0x01, 0x02, 0x1C, 0x1C,
    0xF5, 0xE6, 0x08, 0x08, 0x09, 0xE0, 0x0A, 0x0A, 0x28, 0xEB, 0x08, 0x08,
    0x28, 0xF1, 0x0F, 0x06, 0x1D, 0xF7, 0x0C, 0x08, 0xEE, 0xFC, 0x06, 0x04,
    0xEE, 0xF9, 0x08, 0x08, 0x00, 0xF2, 0x08, 0x08, 0x20, 0xFB, 0x08, 0x08,
    0x20, 0x02, 0x0F, 0x06, 0x17, 0x08, 0x0C, 0x08, 0xE6, 0x0E, 0x06, 0x04,
    0x15, 0x02, 0x10, 0x0C, 0x1D, 0x13, 0x0D, 0x08, 0x0B, 0x12, 0x0F, 0x08,
    0xED, 0xE4, 0x08, 0x08, 0xFC, 0xDE, 0x08, 0x08, 0x1E, 0xEE, 0x0A, 0x0A,
    0x21, 0xF1, 0x0F, 0x06, 0x15, 0xF7, 0x0C, 0x08, 0xEB, 0xFC, 0x06, 0x04,
    0x1A, 0xFC, 0x14, 0x16, 0x26, 0x08, 0x0A, 0x08, 0x0A, 0xFD, 0x10, 0x08,
};

static u16* D_35000_8017AC0C[] = {
    D_35000_8017AAA4, D_35000_8017AAA4, D_35000_8017AAC0, D_35000_8017AADC,
    D_35000_8017AAF8, D_35000_8017AB14, D_35000_8017AB2C,
};

static WeaponAnimation D_35000_8017AC28[] = {
    {D_35000_8017AC0C, D_35000_8017AB58, 0x000F, SFX_UNK_689, 0x48, 0x03,
     0x0000},
    {D_35000_8017AC0C, D_35000_8017AB58, 0x000F, SFX_UNK_689, 0x48, 0x03,
     0x0000}};

static u16 D_35000_8017AC48[] = {
    0x0028, 0xFFF2, 0x0028, 0xFFF2, 0x0028, 0x0004, 0x0024,
    0x0014, 0x0028, 0xFFF2, 0x0028, 0xFFF3, 0x0028, 0x0010,
};

static u8 D_35000_8017AC64[6][8] = {
    {0x00, 0x50, 0x10, 0x50, 0x00, 0x60, 0x10, 0x60},
    {0x10, 0x50, 0x20, 0x50, 0x10, 0x60, 0x20, 0x60},
    {0x70, 0x40, 0x80, 0x40, 0x70, 0x50, 0x80, 0x50},
    {0x70, 0x30, 0x78, 0x30, 0x70, 0x38, 0x78, 0x38},
    {0x78, 0x30, 0x80, 0x30, 0x78, 0x38, 0x80, 0x38},
    {0x70, 0x38, 0x78, 0x38, 0x77, 0x40, 0x78, 0x40}};

static u16* g_WeaponCluts[] = {D_35000_8017A884, D_35000_8017A884};
static s32 g_HandId = HAND_ID;

#include "shared.h"

void EntityWeaponAttack(Entity* self) {
    s8 animIndex = (self->params & 0x7FFF) >> 8;
    WeaponAnimation* anim = &D_35000_8017AC28[animIndex];
    s32 hand;
    s32 temp;

    self->posX.val = PLAYER.posX.val;
    self->posY.val = PLAYER.posY.val;
    self->facingLeft = PLAYER.facingLeft;

    if ((PLAYER.ext.player.anim < anim->frameStart) ||
        (PLAYER.ext.player.anim >= anim->frameStart + 7) ||
        g_Player.unk46 == 0) {
        DestroyEntity(self);
        return;
    }

    if (self->step == 0) {
        SetSpriteBank1(g_Animset);
        self->animSet = ANIMSET_OVL(0x10);
        self->palette = 0x110;
        self->unk5A = 0x64;
        if (g_HandId != 0) {
            self->animSet += 2;
            self->palette += 0x18;
            self->unk5A += 2;
        }

        self->palette += anim->palette;
        self->flags = FLAG_UNK_40000 | FLAG_UNK_20000;
        self->zPriority = PLAYER.zPriority - 2;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        SetWeaponProperties(self, 0);
        self->step++;
    }
    self->ext.weapon.anim = PLAYER.ext.player.anim - anim->frameStart;
    if ((PLAYER.animFrameDuration == 1) &&
        (PLAYER.animFrameIdx == anim->soundFrame)) {
        g_api.PlaySfx(anim->soundId);
    }
    if (g_api.UpdateUnarmedAnim(anim->frameProps, anim->frames) < 0) {
        DestroyEntity(self);
        return;
    }
    if (animIndex && PLAYER.animFrameDuration == 7 &&
        PLAYER.animFrameIdx == 4) {
        hand = (g_HandId + 1) << 0xC;
        temp = (self->ext.weapon.anim << 0x10) + 0x4A;
        g_api.CreateEntFactoryFromEntity(self, hand + temp, 0);
    }
    self->drawFlags = PLAYER.drawFlags;
    self->rotY = PLAYER.rotY;
    self->rotPivotY = PLAYER.rotPivotY;
}

static void func_ptr_80170004(Entity* self) {
    Entity* parent;
    s32 index;
    u16 offsetX, offsetY;

    switch (self->step) {
    case 0:
        parent = self->ext.weapon.parent;
        if (parent->entityId != 0) {
            index = (self->params >> 7);
            self->facingLeft = parent->facingLeft;
            offsetX = D_35000_8017AC48[index];
            offsetY = D_35000_8017AC48[index + 1];
            if (self->facingLeft) {
                offsetX = -offsetX;
            }
            self->posX.i.hi += offsetX;
            self->posY.i.hi += offsetY;

            self->animSet = self->ext.weapon.parent->animSet;
            self->anim = D_35000_8017AB44;
            self->zPriority = 0xA8;
            self->unk5A = self->ext.weapon.parent->unk5A;
            self->palette = self->ext.weapon.parent->palette;

            SetSpeedX(FIX(4.75));
            if ((self->params & 0xFF00) == 0x300 ||
                (self->params & 0xFF00) == 0x600) {
                self->velocityY = FIX(2.75);
                SetSpeedX(FIX(3.75));
            }
            self->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            self->rotX = self->rotY = 0x10;
            self->flags = FLAG_UNK_08000000 | FLAG_UNK_100000;
            self->hitboxWidth = self->hitboxHeight = 9;
            self->attack = 1;
            self->attackElement = 0;
            self->hitboxState = 4;
            self->nFramesInvincibility = 4;
            self->stunFrames = 4;
            self->hitEffect = 1;
            self->entityRoomIndex = 0;
            g_api.func_80118894(self);
            g_api.PlaySfx(SFX_UNK_6AD);
            self->step++;
            return;
        }
        DestroyEntity(self);
        return;
    case 1:
        if (self->hitFlags) {
            self->step = 3;
        }
        DecelerateX(FIX(7.0 / 32));
        DecelerateY(FIX(7.0 / 32));
        self->posX.val += self->velocityX;
        self->posY.val += self->velocityY;
        if (self->rotX < 0x100) {
            self->rotX += 0x10;
            self->rotY += 0x10;
        }
        if ((self->velocityX == 0) && (self->rotX >= 0x100)) {
            self->ext.weapon.unk7E = 0x200;
            self->step++;
        }
        break;
    case 3:
        self->rotX -= 0xC;
        self->rotY -= 0xC;
        if (self->rotX < 0x10) {
            DestroyEntity(self);
            return;
        }
        // fallthrough
    case 2:
        self->velocityY = rsin(self->ext.weapon.lifetime);
        self->posY.val += self->velocityY;
        self->ext.weapon.lifetime += 0x20;
        self->posY.val += self->velocityY; // ???
        if (!(self->ext.weapon.unk7E & 7)) {
            g_api.CreateEntFactoryFromEntity(
                self, ((g_HandId + 1) << 0xC) | 0x40, 0);
        }
        if (((--self->ext.weapon.unk7E << 0x10) == 0) ||
            (self->hitFlags != 0)) {
            self->step = 3;
        }
        break;
    }
}

static s32 func_35000_8017B604(Primitive* prim, s32 x, s32 y) {
    s32 size;
    s32 left;
    s32 right;
    s32 top;
    s32 bottom;
    u8* uvPtr;

    // Should be able to do this as an array access but nope
    uvPtr = &D_35000_8017AC64;
    uvPtr += prim->b0 * 8;

    if (prim->b0 >= 3) {
        size = 2;
    } else {
        size = 3;
    }
    if (prim->b0 == 6) {
        return -1;
    }
    left = x - size;
    top = y - size;
    right = x + size;
    bottom = y + size;

    prim->x0 = left;
    prim->y0 = top;
    prim->x1 = right;
    prim->y1 = top;
    prim->x2 = left;
    prim->y2 = bottom;
    prim->x3 = right;
    prim->y3 = bottom;

    prim->u0 = *uvPtr++;
    prim->v0 = *uvPtr++;
    prim->u1 = *uvPtr++;
    prim->v1 = *uvPtr++;
    prim->u2 = *uvPtr++;
    prim->v2 = *uvPtr++;
    prim->u3 = *uvPtr++;
    prim->v3 = *uvPtr++;
    if (!(++prim->b1 & 1)) {
        prim->b0++;
    }
    return 0;
}

static void func_ptr_80170008(Entity* self) {
    Primitive* prim;
    s32 velocityX;
    s32 range;

    if (self->step == 0) {
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags = FLAG_UNK_08000000 | FLAG_HAS_PRIMS;
        self->velocityY = FIX(3.0 / 4.0);

        range = 16;
        velocityX = (rand() % range) - 8;

        self->posX.i.hi += velocityX;
        self->posY.i.hi += rand() % range;

        prim = &g_PrimBuf[self->primIndex];
        prim->clut = 0x1B0;
        prim->tpage = 0x1A;
        prim->b0 = 0;
        prim->b1 = 0;
        prim->priority = self->zPriority + 4;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_TRANSP;

        func_35000_8017B604(prim, self->posX.i.hi, self->posY.i.hi);
        self->step++;
        return;
    }

    self->posY.val += self->velocityY;

    prim = &g_PrimBuf[self->primIndex];
    if (func_35000_8017B604(prim, self->posX.i.hi, self->posY.i.hi)) {
        DestroyEntity(self);
    }
}
static void func_ptr_8017000C(Entity* self) {}

static s32 func_ptr_80170010(Entity* self) {}

static s32 func_ptr_80170014(Entity* self) {}

static int GetWeaponId(void) { return 7; }

static void EntityWeaponShieldSpell(Entity* self) {}

static void func_ptr_80170024(Entity* self) {}

static void func_ptr_80170028(Entity* self) {}

static void WeaponUnused2C(void) {}

static void WeaponUnused30(void) {}

static void WeaponUnused34(void) {}

static void WeaponUnused38(void) {}

static void WeaponUnused3C(void) {}
