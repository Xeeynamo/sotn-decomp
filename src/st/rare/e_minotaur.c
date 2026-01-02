// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rare.h"

extern EInit g_EInitMinotaur;
extern EInit D_us_8018079C;
extern EInit D_us_801807A8;
extern EInit D_us_801807B4;
extern EInit g_EInitParticle;

static s16 D_us_801815FC[] = {
    0x0000,
    0x0028,
    0x0010,
    0x0000,
};
static s16 D_us_80181604[] = {
    0x0000, 0x0028, 0x0000, 0x0004, 0x0010, 0xFFFC, 0xFFE0, 0x0000,
};

static u8 D_us_80181614[] = {
    0x06, 0x01, 0x0E, 0x30, 0x09, 0x02, 0x0A, 0x03, 0x09, 0x04,
    0x06, 0x2D, 0x06, 0x04, 0x08, 0x03, 0x07, 0x02, 0x00, 0x00,
};
static u8 D_us_80181628[] = {
    0x0A, 0x05, 0x09, 0x06, 0x07, 0x07, 0x0A, 0x08,
    0x09, 0x07, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00,
};
static u8 D_us_80181638[] = {
    0x07, 0x0A, 0x05, 0x0B, 0x06, 0x0C, 0x05, 0x2E,
    0x1A, 0x2F, 0x03, 0x34, 0x04, 0x0D, 0xFF, 0x00,
};
static u8 D_us_80181648[] = {
    0x06, 0x0E, 0x02, 0x0F, 0x02, 0x10, 0x03, 0x11,
    0x03, 0x35, 0x30, 0x11, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181658[] = {
    0x01, 0x01, 0x06, 0x13, 0x05, 0x14, 0x01, 0x31, 0x1C, 0x38,
    0x03, 0x32, 0x03, 0x15, 0x01, 0x33, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_8018166C[] = {
    0x01, 0x01, 0x06, 0x16, 0x15, 0x17, 0x04, 0x18, 0x03, 0x19, 0x0C,
    0x1A, 0x06, 0x1B, 0x04, 0x1C, 0x03, 0x1D, 0x01, 0x36, 0x16, 0x1D,
    0x06, 0x1C, 0x05, 0x1E, 0x04, 0x09, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_8018168C[] = {
    0x01, 0x01, 0x05, 0x1F, 0x16, 0x20, 0x06, 0x1F, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_80181698[] = {
    0x01, 0x01, 0x18, 0x11, 0x08, 0x35, 0x04, 0x06, 0x04, 0x05,
    0x03, 0x12, 0x03, 0x37, 0x31, 0x12, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_801816AC[] = {
    0x02, 0x21, 0x06, 0x22, 0x06, 0x21, 0x00, 0x00,
};
static u8 D_us_801816B4[] = {
    0x06, 0x39, 0x06, 0x3A, 0x06, 0x25, 0x08, 0x27, 0x08, 0x28,
    0x08, 0x29, 0x08, 0x2A, 0x08, 0x2B, 0x18, 0x2C, 0xFF, 0x00,
};
static u8 D_us_801816C8[] = {
    0x01, 0x09, 0x01, 0x0A, 0x01, 0x0B, 0x01, 0x0C, 0x01, 0x0D,
    0x01, 0x0E, 0x01, 0x0F, 0x01, 0x10, 0x01, 0x11, 0x01, 0x12,
    0x01, 0x13, 0x01, 0x14, 0xFF, 0x00, 0x00, 0x00,
};
static u8 D_us_801816E4[] = {
    0x03, 0x01, 0x03, 0x02, 0x03, 0x03, 0x03, 0x04, 0x03, 0x05,
    0x03, 0x06, 0x03, 0x07, 0x03, 0x08, 0x03, 0x09, 0x03, 0x0A,
    0x03, 0x0B, 0x03, 0x0C, 0x03, 0x0D, 0xFF, 0x00,
};

static s8 D_us_80181700[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0x00, 0x04, 0x10, 0x21},
    {0x00, 0x08, 0x10, 0x1C}, {0xFC, 0x03, 0x0F, 0x21},
    {0x01, 0x04, 0x0F, 0x21}, {0x0C, 0x08, 0x0C, 0x1C},
    {0x00, 0x00, 0x10, 0x1D}, {0xFE, 0xFC, 0x0D, 0x21},
    {0xFD, 0x03, 0x0D, 0x20}, {0x00, 0xFD, 0x10, 0x1F},
    {0xFB, 0x06, 0x0E, 0x1F}, {0x01, 0x04, 0x11, 0x21},
    {0x03, 0x01, 0x10, 0x23}, {0xFF, 0x06, 0x11, 0x1E},
    {0x00, 0x0A, 0x10, 0x19}, {0xFD, 0x0E, 0x10, 0x19},
    {0xF3, 0x0F, 0x0F, 0x15}, {0xF4, 0x0E, 0x10, 0x17},
    {0x00, 0x03, 0x10, 0x1F}, {0xFF, 0x09, 0x12, 0x1B},
    {0x00, 0xFF, 0x10, 0x21}, {0xC0, 0xA8, 0x00, 0x00},
    {0x04, 0x01, 0x10, 0x23},
};
static u8 D_us_8018175C[] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08, 0x09, 0x01, 0x0A, 0x0B, 0x0C, 0x0D, 0x01, 0x01,
    0x0E, 0x0F, 0x10, 0x11, 0x12, 0x01, 0x13, 0x01, 0x14, 0x01, 0x01, 0x01,
    0x01, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x01, 0x05, 0x05,
    0x01, 0x0C, 0x0B, 0x0D, 0x06, 0x01, 0x01, 0x0A, 0x16, 0x15, 0x15, 0x00,
};
static s8 D_us_80181798[][4] = {
    {0x00, 0x00, 0x00, 0x00}, {0xDA, 0xEE, 0x11, 0x0C},
    {0xDE, 0xF0, 0x11, 0x0C}, {0xDD, 0xF1, 0x11, 0x0A},
    {0xDB, 0xF1, 0x11, 0x0A}, {0xD9, 0xF0, 0x11, 0x0C},
    {0xDC, 0xEF, 0x11, 0x0A}, {0xF8, 0xCC, 0x0B, 0x15},
    {0x21, 0xE1, 0x0C, 0x0B}, {0x32, 0x07, 0x0A, 0x0B},
    {0x21, 0xF8, 0x0E, 0x0C}, {0x1B, 0xDC, 0x0E, 0x0C},
    {0xFB, 0xC8, 0x0A, 0x1A}, {0xD4, 0xE7, 0x18, 0x28},
    {0xDE, 0x1E, 0x11, 0x0B}, {0xD2, 0x0B, 0x1C, 0x0A},
    {0xDC, 0xFB, 0x11, 0x0B}, {0xDF, 0xF2, 0x0D, 0x0D},
    {0xD8, 0xE6, 0x0C, 0x0B}, {0xE2, 0xE2, 0x0B, 0x0B},
    {0xE9, 0xE1, 0x0C, 0x0D}, {0xF8, 0xE3, 0x0C, 0x10},
    {0xF7, 0xE7, 0x0B, 0x12}, {0xF9, 0xE5, 0x0B, 0x11},
    {0x0D, 0xEB, 0x0B, 0x0B}, {0x14, 0xEA, 0x0B, 0x0B},
    {0xEB, 0xE1, 0x0B, 0x0D}, {0xDD, 0xFA, 0x11, 0x0B},
    {0xED, 0x14, 0x0C, 0x0C}, {0xC0, 0xA8, 0x00, 0x00},
    {0xE6, 0xE2, 0x0D, 0x0D}, {0xDA, 0xEF, 0x0D, 0x0D},
    {0xE7, 0xE2, 0x0D, 0x0D},
};
static u8 D_us_8018181C[] = {
    0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1D, 0x03,
    0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D, 0x01, 0x09, 0x09,
    0x01, 0x1E, 0x1F, 0x11, 0x0A, 0x0E, 0x19, 0x0F, 0x20, 0x1D, 0x1D, 0x00,
};
static Point32 D_us_80181858[] = {
    {0x00060000, 0x00000100}, {0x00060000, 0x00000180},
    {0x00060000, 0x00000200}, {0x00060000, 0x00000280},
    {0x00060000, 0x00000300}, {0x00060000, 0x00000380},
    {0x00060000, 0x00000400}, {0x00060000, 0x00000480},
    {0x00060000, 0x00000500}, {0x00060000, 0x00000580},
};
// Present in PSX but stripped on PSP
static Point32 unused = {0x00400000, 0x00000004};

void func_us_801B1BC8(Entity* self) {
    Entity* entity;
    s32 i;
    s8* ptr;
    s32 velocityX;

    if (self->step & 1 && self->hitFlags & 3) {
        SetStep(24);
    }

    if (self->flags & FLAG_DEAD && self->step < 32) {
        SetStep(32);
    }

    FntPrint("mino_step %x\n", self->step);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitMinotaur);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_17, entity);
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_80181604) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        AnimateEntity(D_us_80181628, self);
        if (GetDistanceToPlayerX() < 0x68) {
            SetStep(3);
        }
        break;
    case 3:
        if (!self->step_s) {
            if (!self->ext.minotaur.unk82) {
                self->ext.minotaur.unk82 = 0x20;
            }
            self->step_s++;
        }

        AnimateEntity(D_us_80181628, self);
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->ext.minotaur.unk82) {
            self->ext.minotaur.unk82--;
        }

        if (!self->ext.minotaur.unk82) {
            SetStep(5);
        }

        entity = &PLAYER;
        velocityX = entity->velocityX;
        if (self->facingLeft) {
            velocityX = -velocityX;
        }

        if (self->facingLeft == entity->facingLeft &&
            GetDistanceToPlayerX() > 0x48 && GetDistanceToPlayerX() < 0x60 &&
            g_Player.status & PLAYER_STATUS_UNK400 && velocityX > 0) {
            SetStep(16);
        }

        if (self->facingLeft == entity->facingLeft &&
            g_Player.status & PLAYER_STATUS_UNK800) {
            SetStep(14);
        }

        break;
    case 5:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.minotaur.unk8C = false;
            self->ext.minotaur.unk80 = 0x20;
            self->step_s++;
        }

        if (!AnimateEntity(D_us_80181614, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }

        if (self->facingLeft ^ self->ext.minotaur.unk8C) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }

        UnkCollisionFunc2(D_us_801815FC);
        if (GetDistanceToPlayerX() > 0x70) {
            self->ext.minotaur.unk8C = false;
        }

        if (GetDistanceToPlayerX() < 0x30) {
            self->ext.minotaur.unk8C = true;
        }

        if (!--self->ext.minotaur.unk80) {
            SetStep(6);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            self->ext.minotaur.unk80 = 0x20;
            self->animCurFrame = 1;
            self->step_s++;
            break;
        case 1:
            if (!--self->ext.minotaur.unk80) {
                self->step_s++;
            }
            break;
        case 2:
            entity = &PLAYER;
            if (GetDistanceToPlayerX() < 0x48) {
                if (self->facingLeft == entity->facingLeft) {
                    if (Random() & 3) {
                        SetStep(10);
                    } else {
                        SetStep(16);
                    }
                } else if (Random() & 3) {
                    SetStep(16);
                } else {
                    SetStep(8);
                }
            } else if (Random() & 7) {
                SetStep(8);
            } else {
                SetStep(16);
            }
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80181658, self)) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.minotaur.unk80 = 0x40;
            PlaySfxPositional(SFX_MINOTAUR_BREATH_ATTACK);
            self->step_s++;
            // fallthrough
        case 2:
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_19, self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x20;
                    } else {
                        entity->posX.i.hi -= 0x20;
                    }
                    entity->posY.i.hi -= 4;
                    entity->facingLeft = self->facingLeft;
                    entity->rotate = -0x500;
                    entity->zPriority = self->zPriority + 1;
                }
            }

            if (!--self->ext.minotaur.unk80) {
                SetStep(3);
            }
        }
        break;
    case 12:
        if (!AnimateEntity(D_us_8018166C, self)) {
            SetStep(3);
        }

        if (!self->poseTimer && self->pose == 8) {
            for (i = 0; i < 8; i++) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_18, self, entity);
                    entity->posY.i.hi += 0x28;
                    entity->facingLeft = self->facingLeft;
                    entity->params = i;
                }
            }
        }

        break;
    case 14:
        if (!AnimateEntity(D_us_8018168C, self)) {
            SetStep(3);
        }
        break;
    case 16:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }

        UnkCollisionFunc2(D_us_801815FC);
        if (!AnimateEntity(D_us_80181698, self)) {
            SetStep(3);
        }

        self->velocityX -= self->velocityX / 16;
        if (!self->poseTimer && self->pose == 7) {
            PlaySfxPositional(SFX_MINOTAUR_ATTACK);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80181638, self)) {
                self->velocityY = 0;
                if (self->facingLeft) {
                    self->velocityX = FIX(4.0);
                } else {
                    self->velocityX = FIX(-4.0);
                }
                self->step_s++;
                PlaySfxPositional(SFX_BOSS_WING_FLAP);
                SetSubStep(1);
            }
            break;
        case 1:
            UnkCollisionFunc2(D_us_801815FC);
            self->velocityX -= self->velocityX / 16;
            if (!AnimateEntity(D_us_80181648, self)) {
                SetStep(3);
            }
            break;
        }
        break;
    case 24:
        if (!AnimateEntity(D_us_801816AC, self)) {
            SetStep(3);
        }
        break;
    case 18:
        switch (self->step_s) {
        case 0:
            self->animCurFrame = 0x2B;
            self->step_s++;
            break;
        case 1:
            self->facingLeft ^= 1;
            self->step_s++;
            break;
        case 2:
            self->animCurFrame = 1;
            SetStep(3);
            break;
        }
        break;
    case 32:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (UnkCollisionFunc3(D_us_80181604) & 1) {
                self->ext.minotaur.unk84 = -0x10U;
                self->ext.minotaur.unk80 = 0;
                self->step_s++;
            }
            break;
        case 2:
            if (!AnimateEntity(D_us_801816B4, self)) {
                self->step_s = 3;
            }
            self->ext.minotaur.unk80 &= 1;
            // fallthrough
        case 3:
            if (self->ext.minotaur.unk80 & 1) {
                entity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_UNK_1F, self, entity);
                    entity->posX.i.hi += self->ext.minotaur.unk84;
                    entity->posY.i.hi += 0x20;
                    entity->zPriority = self->zPriority + 1;
                    entity->params = abs(self->ext.minotaur.unk84) +
                                     (self->ext.minotaur.unk80 >> 1);
                }

                self->ext.minotaur.unk84 += 8;
                if (self->ext.minotaur.unk84 > 0x10) {
                    self->ext.minotaur.unk84 = -0x10;
                }
            }

            if (!(g_Timer & 7)) {
                PlaySfxPositional(SFX_OUIJA_TABLE_DEATH);
            }

            if (self->ext.minotaur.unk80++ > 0x20) {
                self->step_s++;
            }
            break;
        case 4:
            DestroyEntity(self);
            DestroyEntity(self + 1);
            return;
        }
        break;
    case 0xFF:
#include "../pad2_anim_debug.h"
    }

    ptr = *D_us_80181700;
    ptr += D_us_8018175C[self->animCurFrame] * 4;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
}

void func_us_801B2800(Entity* self) {
    s8* ptr;
    Entity* parent;
    s32 animCurFrame;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018079C);
        self->animCurFrame = 0;
        // fallthrough
    case 1:
        parent = self - 1;
        if (parent->entityId != 0x16) {
            DestroyEntity(self);
            return;
        }

        animCurFrame = parent->animCurFrame;
        self->facingLeft = parent->facingLeft;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        self->hitboxState = 1;

        ptr = *D_us_80181798;
        ptr += D_us_8018181C[animCurFrame] * 4;
        self->hitboxOffX = *ptr++;
        self->hitboxOffY = *ptr++;
        self->hitboxWidth = *ptr++;
        self->hitboxHeight = *ptr++;
        break;
    }
}

void func_us_801B28F4(Entity* self) {
    s32 rotation;
    s32 speed;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801807A8);
        speed = D_us_80181858[self->params].x;
        rotation = D_us_80181858[self->params].y;
        self->velocityX = (-speed * rcos(rotation)) >> 0xC;
        self->velocityY = (-speed * rsin(rotation)) >> 0xC;
        if (self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        return;
    }
}

void func_us_801B29E0(Entity* self) {
    s16 rotate;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801807B4);
        self->palette = 0x816B;
        if (self->facingLeft) {
            self->rotate = -self->rotate;
        }
        self->facingLeft = 0;
        self->rotate += 0x80 - Random();
        rotate = self->rotate;
        self->velocityX = rsin(rotate) * 0x24;
        self->velocityY = rcos(rotate) * -0x24;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY | FLAG_DRAW_ROTATE |
                          FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleX = 0x40;
        self->scaleY = 0x80;
        self->opacity = 0x80;
        break;
    case 1:
        MoveEntity();
        self->scaleX += 0x10;
        self->scaleY += 0xE;
        self->opacity -= 1;
        if (!AnimateEntity(D_us_801816C8, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

void func_us_801B2B2C(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 0xE;
        self->palette = 0x2E8;
        self->unk5A = 0x79;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags =
            FLAG_DRAW_OPACITY | FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        self->scaleY = 0x180;
        self->scaleX = 0xA0;
        self->opacity = 0x60 - (self->params * 2);
        self->velocityY = FIX(-3.0);
        self->facingLeft = Random() & 1;
        // fallthrough
    case 1:
        MoveEntity();
        self->velocityY -= FIX(0.0625);
        self->opacity -= 2;
        self->scaleX += 8;
        self->scaleY -= 4;

        if (!self->opacity) {
            DestroyEntity(self);
        } else if (!AnimateEntity(D_us_801816E4, self)) {
            DestroyEntity(self);
        }
        break;
    }
}
