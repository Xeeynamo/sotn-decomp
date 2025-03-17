// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

static u8 steps[] = {6, 10, 6, 10, 9, 6, 10, 6};
static u8 D_us_80182F0C[] = {0x40, 0x30, 0x60, 0x58};

static u8 D_us_80182F10[] = {0x50, 0x30, 0x60, 0x88};
static u8 D_us_80182F14[] = {0x3F, 0x3C, 0x38, 0x34, 0x30, 0x2C, 0x28, 0x24,
                             0x20, 0x1C, 0x18, 0x14, 0x10, 0x0C, 0x08, 0x04};
static s16 explosionPosXYs[][2] = {
    {-8, -4}, {8, -6},  {-12, 4},  {-1, -7}, {6, 16},   {11, -3},
    {10, 12}, {3, -2},  {-8, -8},  {10, -6}, {-12, 18}, {-8, -16},
    {6, 4},   {10, 20}, {-11, 22}, {8, -2}};

// Unknown data, stripped on PSP
static s32 unused[] = {0xFFFFC800, 0xFFFFC800, 0xFFFFB000, 0xFFFFB000};

static u16 frameIndexes[] = {2, 2, 2, 2};
static s32 xVelocities[] = {0xFFFFF000, 0xFFFFFA00, 0xFFFFE000, 0xFFFFE200};

// anims
static u8 D_us_80182F8C[] = {
    0x06, 0x01, 0x04, 0x02, 0x1C, 0x02, 0x0A, 0x03, 0x00};
static u8 D_us_80182F98[] = {0x0E, 0x04, 0x08, 0x04, 0x08, 0x05, 0x00};
static u8 D_us_80182FA0[] = {0x09, 0x05, 0x01, 0x05, 0x0A, 0x04, 0x00};
static u8 D_us_80182FA8[] = {0x0B, 0x05, 0x01, 0x05, 0x0C, 0x04, 0x00};

static u8 D_us_80182FB0[] = {
    0x08, 0x04, 0x30, 0x06, 0x25, 0x07, 0x06, 0x06, 0x00};
static u8 D_us_80182FBC[] = {
    0x06, 0x10, 0x06, 0x11, 0x06, 0x12, 0x01, 0x15, 0x01, 0x16, 0x01,
    0x15, 0x01, 0x16, 0x01, 0x15, 0x01, 0x16, 0x01, 0x15, 0x01, 0x16,
    0x01, 0x15, 0x01, 0x16, 0x06, 0x13, 0x06, 0x14, 0x00};
static u8 D_us_80182FDC[] = {
    0x06, 0x04, 0x06, 0x08, 0x06, 0x09, 0x08, 0x0A, 0x30, 0x0B, 0x02,
    0x0A, 0x02, 0x0C, 0x02, 0x0D, 0x02, 0x0E, 0x31, 0x0F, 0x00};
static u8 D_us_80182FF4[] = {
    0x06, 0x04, 0x06, 0x17, 0x06, 0x18, 0x04, 0x19, 0x04, 0x1A,
    0x30, 0x1B, 0x02, 0x1C, 0x01, 0x1D, 0x31, 0x1E, 0xFF, 0x00};
static u8 D_us_80183008[] = {0x08, 0x3E, 0x08, 0x3F, 0x08, 0x40, 0x08, 0x3F,
                             0x08, 0x40, 0x08, 0x3F, 0x08, 0x40, 0xFF, 0x00};
static u8 D_us_80183018[] = {
    0x06, 0x04, 0x06, 0x21, 0x0F, 0x22, 0x03, 0x23, 0x03,
    0x24, 0x03, 0x25, 0x16, 0x26, 0x02, 0x25, 0x02, 0x24,
    0x02, 0x23, 0x06, 0x22, 0x06, 0x21, 0x00};
static u8 D_us_80183034[] = {
    0x06, 0x04, 0x06, 0x27, 0x06, 0x28, 0x0F, 0x29, 0x03, 0x2A,
    0x03, 0x2B, 0x03, 0x2C, 0x16, 0x2D, 0x02, 0x2C, 0x02, 0x2B,
    0x02, 0x2A, 0x06, 0x29, 0x06, 0x28, 0x06, 0x27, 0x00};

static u8* animations[] = {
    D_us_80182F8C, D_us_80182F98, D_us_80182FA0, D_us_80182FA8};

// sensors
static s16 D_us_80183064[][2] = {{0, 24}, {8, 0}};
static s16 D_us_8018306C[][2] = {{0, 24}, {0, 4}, {8, -4}, {-16, 0}};

static s16 guardHitboxOffsetXYs[][2] = {
    {-28, 15},  {-24, 13},  {-24, 12},  {-23, -1},  {-29, 2},   {-29, -1},
    {-21, -24}, {1, -38},   {35, -7},   {-36, -16}, {-36, 0},   {3, 26},
    {4, 24},    {-20, 6},   {-29, -1},  {-28, -10}, {-20, 18},  {-27, 12},
    {-16, 0},   {-16, 0},   {-29, -1},  {-21, -24}, {1, -38},   {-6, -36},
    {3, -27},   {-16, -34}, {-25, -17}, {-48, -72}, {-64, -72}, {-64, -72},
    {-15, 21},  {3, 26},    {1, 38},    {1, 46},    {1, 54},    {1, 62},
    {-25, 0},   {-23, -27}, {1, -30},   {0, -47},   {0, -54},   {0, -62},
    {0, -70}};
static u16 guardHitboxWidthHeights[][2] = {
    {0, 0},  {8, 4},   {8, 4},   {16, 4},  {16, 4}, {16, 4}, {8, 8},  {4, 20},
    {8, 4},  {12, 24}, {16, 24}, {4, 12},  {4, 12}, {16, 4}, {16, 4}, {16, 4},
    {8, 8},  {8, 8},   {27, 25}, {27, 25}, {16, 4}, {8, 8},  {4, 20}, {4, 20},
    {8, 8},  {12, 4},  {0, 0},   {0, 0},   {0, 0},  {0, 0},  {4, 4},  {4, 8},
    {4, 20}, {4, 28},  {4, 36},  {4, 44},  {20, 4}, {8, 8},  {4, 8},  {4, 24},
    {4, 32}, {4, 40},  {4, 48}};

// Unknown data, stripped on PSP
static u8 unusedTwo[] = {
    0x06, 0x05, 0x06, 0x06, 0x06, 0x07, 0x06, 0x08, 0x06, 0x01};

// Spear Guard helper
void func_us_801D37A4(void) {
    Entity* player = &PLAYER;

    if (g_Player.status &
        (PLAYER_STATUS_UNK1000 | PLAYER_STATUS_UNK800 | PLAYER_STATUS_UNK400)) {
        if (GetDistanceToPlayerX() > 0x48 && Random() & 1) {
            SetStep(9);
        }
    } else {
        if (!--g_CurrentEntity->ext.spearGuard.unk7C) {
            SetStep(steps[g_CurrentEntity->ext.spearGuard.unk84++ & 7]);
            g_CurrentEntity->ext.spearGuard.unk7C = D_us_80182F0C[Random() & 3];

            if (g_CurrentEntity->params && GetDistanceToPlayerX() > 0x50 &&
                Random() & 1) {
                SetStep(11);
            }

            g_CurrentEntity->velocityX = 0;
        }
    }
}

// Spear Guard helper
void func_us_801D38E4() {
    if (GetDistanceToPlayerY() > 64) {
        SetStep(3);
    }
}

// Spear Guard helper
void func_us_801D3918(Entity* self, u8 animationIndex) {
    s32 xVelocity;
    u16 animRet = AnimateEntity(animations[animationIndex], self);
    if ((animRet & 0x80) && (self->step == 7) && (self->animFrameIdx != 3)) {
        if (self->ext.spearGuard.unk88 != self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->ext.spearGuard.unk88 = self->facingLeft;
    }
    xVelocity = self->velocityX;
    if (self->animFrameIdx >= frameIndexes[animationIndex]) {
        if (xVelocity != 0) {
            if (self->ext.spearGuard.unk88) {
                xVelocity += xVelocities[animationIndex];
            } else {
                xVelocity -= xVelocities[animationIndex];
            }
        }
    } else {
        if (self->ext.spearGuard.unk88) {
            xVelocity -= xVelocities[animationIndex];
        } else {
            xVelocity += xVelocities[animationIndex];
        }
    }
    self->velocityX = xVelocity;
    if ((UnkCollisionFunc2(D_us_80183064) & 0x60) == 0x60) {
        self->posX.val -= xVelocity;
    }
}

void EntitySpearGuard(Entity* self) {
    Entity* tempEntity;
    u8 i;
    u8 tempVar;
    u8* anim;
    s32 xDistance;

    tempEntity = self + 1;
    if (self->step) {
        if (self->ext.spearGuard.unk90 == 0) {
            tempEntity->attack = self->attack;
            tempEntity->attackElement = self->attackElement;
        }
    }
    if ((self->step < 12) && (self->flags & FLAG_DEAD)) {
        DestroyEntity(tempEntity);
        SetStep(12);
        self->hitboxState = 0;
        self->ext.spearGuard.unk7C = 0x40;
        self->drawFlags = FLAG_DRAW_UNK8;
        self->unk6C = 0x7F;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpearGuard);
        self->ext.spearGuard.unk80 = 0xB0;
        self->ext.spearGuard.unk7C = 0x40;
        self->palette += self->params & 3;
        self->hitboxOffY = 4;
        CreateEntityFromCurrentEntity(E_SPEAR_GUARD_BLOCK, tempEntity);
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_8018306C) & 1) {
            SetStep(2);
        }
        break;

    case 2:
    case 3:
        if (self->step == 2) {
            tempVar = 0;
        } else {
            tempVar = 1;
        }
        self->facingLeft = self->ext.spearGuard.unk88;
        func_us_801D3918(self, tempVar);
        if (GetDistanceToPlayerY() < 0x20) {
            SetStep(4);
            PlaySfxPositional(0x773);
            self->velocityX = 0;
        } else if (GetDistanceToPlayerX() < 0x18) {
            SetStep(7);
            self->velocityX = 0;
        } else if (!--self->ext.spearGuard.unk80) {
            self->ext.spearGuard.unk80 = 0xB0;
            self->ext.spearGuard.unk88 ^= 1;
            self->velocityX = -self->velocityX;
        }
        break;

    case 4:
    case 5:
        xDistance = GetDistanceToPlayerX();
        if (self->step == 4 && xDistance < 0x64) {
            self->step = 5;
            self->velocityX = 0;
        }
        if (self->step == 5 && xDistance > 0x78) {
            self->step = 4;
            self->velocityX = 0;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        if (self->step == 4) {
            self->ext.spearGuard.unk88 = self->facingLeft;
        } else {
            self->ext.spearGuard.unk88 = self->facingLeft ^ 1;
        }
        func_us_801D3918(self, 2);
        func_us_801D37A4();
        func_us_801D38E4();
        break;

    case 6:
        tempVar = AnimateEntity(D_us_80182FB0, self);
        if (!tempVar) {
            SetStep(4);
            PlaySfxPositional(0x773);
        } else if ((tempVar & 0x80) && (self->animCurFrame == 7)) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
            if (self->facingLeft) {
                self->velocityX = FIX(4.0);
            } else {
                self->velocityX = FIX(-4.0);
            }
        }
        if (self->velocityX != 0) {
            tempEntity->attack = g_api.enemyDefs[94].attack;
            tempEntity->attackElement = g_api.enemyDefs[94].attackElement;
            if (self->velocityX > 0) {
                self->velocityX -= FIX(0.25);
            } else {
                self->velocityX += FIX(0.25);
            }
        }
        if ((UnkCollisionFunc2(D_us_80183064) & 0x60) == 0x60) {
            self->posX.val -= self->velocityX;
        }
        break;

    case 7:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        func_us_801D3918(self, 3);
        if (!--self->ext.spearGuard.unk7C) {
            SetStep(8);
            self->ext.spearGuard.unk8C = GetSideToPlayer();
            self->velocityX = 0;
        }
        if (GetDistanceToPlayerX() > 0x48) {
            SetStep(3);
            self->velocityX = 0;
        }
        break;

    case 8:
        if (self->ext.spearGuard.unk8C & 2) {
            anim = D_us_80183034;
        } else {
            anim = D_us_80183018;
        }
        tempVar = AnimateEntity(anim, self);
        tempEntity->attack = g_api.enemyDefs[94].attack;
        tempEntity->attackElement = g_api.enemyDefs[94].attackElement;
        if (!tempVar) {
            SetStep(7);
            self->ext.spearGuard.unk7C = D_us_80182F10[Random() & 3];
        } else if ((tempVar & 0x80) && ((self->animCurFrame == 0x2D) ||
                                        (self->animCurFrame == 0x26))) {
            PlaySfxPositional(SFX_WEAPON_SWISH_B);
        }
        break;
    case 9:
        if ((g_Timer & 0x1F) == 0) {
            PlaySfxPositional(SFX_WEAPON_SWISH_A);
        }
        tempEntity->hitboxState |= 2;
        tempEntity->flags |= FLAG_UNK_8000 | FLAG_UNK_4000;
        if (!AnimateEntity(D_us_80182FBC, self)) {
            tempEntity->hitboxState &= 0xFFFD;
            tempEntity->flags &= ~(FLAG_UNK_8000 | FLAG_UNK_4000);
            SetStep(5);
        }
        break;

    case 10:
        tempVar = AnimateEntity(D_us_80182FDC, self);
        if (!tempVar) {
            SetStep(4);
            PlaySfxPositional(0x773);
        } else if (tempVar & 0x80) {
            tempVar = self->animFrameIdx - 6;
            if (tempVar == 3) {
                PlaySfxPositional(0x770);
            }
            if (!tempVar) {
                if (self->facingLeft) {
                    self->velocityX = FIX(8.0);
                } else {
                    self->velocityX = FIX(-8.0);
                }
                tempEntity->attack = g_api.enemyDefs[95].attack;
                tempEntity->attackElement = g_api.enemyDefs[95].attackElement;
                tempEntity->hitboxState |= 2;
                self->ext.spearGuard.unk90 = 1;
            }
            if (tempVar == 4) {
                self->ext.spearGuard.unk90 = 0;
                tempEntity->attack = 3;
                tempEntity->hitboxState &= 0xFFFD;
            }
        }
        if (self->velocityX != 0) {
            if (self->velocityX > 0) {
                self->velocityX -= FIX(0.5);
            } else {
                self->velocityX += FIX(0.5);
            }
        }
        if ((UnkCollisionFunc2(D_us_80183064) & 0x60) == 0x60) {
            self->posX.val -= self->velocityX;
        }
        break;

    case 11:
        tempVar = AnimateEntity(D_us_80182FF4, self);
        if (!tempVar) {
            SetStep(4);
            PlaySfxPositional(0x773);
        } else if (tempVar & 0x80) {
            tempVar = self->animFrameIdx - 7;
            if (!tempVar) {
                if (self->facingLeft) {
                    self->velocityX = FIX(8.0);
                } else {
                    self->velocityX = FIX(-8.0);
                }
                PlaySfxPositional(SFX_WEAPON_SCRAPE_ECHO);
                tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                CreateEntityFromCurrentEntity(E_ID_58, tempEntity);
                tempEntity->facingLeft = self->facingLeft;
                tempEntity->ext.spearGuardUnk.unk7C = self;
            }
        }
        if (self->velocityX != 0) {
            if (self->velocityX > 0) {
                self->velocityX -= FIX(1.0);
            } else {
                self->velocityX += FIX(1.0);
            }
        }
        if ((UnkCollisionFunc2(D_us_80183064) & 0x60) == 0x60) {
            self->posX.val -= self->velocityX;
        }
        break;

    case 12:
        AnimateEntity(D_us_80183008, self);
        if (self->unk6C) {
            self->unk6C--;
        }
        if (self->unk6C) {
            self->unk6C--;
        }
        if (!--self->ext.spearGuard.unk7C) {
            DestroyEntity(self);
        }
        for (i = 0; i < 16; i++) {
            if (self->ext.spearGuard.unk7C == D_us_80182F14[i]) {
                if (i == 14) {
                    PlaySfxPositional(0x771);
                } else if ((i & 1) == 0) {
                    PlaySfxPositional(SFX_EXPLODE_FAST_B);
                }
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromCurrentEntity(E_EXPLOSION, tempEntity);
                    tempEntity->params = 2;
                    tempEntity->zPriority = self->zPriority - 1;
                    tempEntity->posX.i.hi += explosionPosXYs[i][0];
                    tempEntity->posY.i.hi += explosionPosXYs[i][1];
                }
            }
        }
        break;
    }
}

// Produces a hitbox which blocks attacks and plays
// a deflected noise when hit
void EntitySpearGuardBlock(Entity* self) {
    Entity* parent;
    u16 animCurFrame;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitboxState = 1;
    }

    if (!(self->hitFlags & 0x80) && self->hitFlags) {
        PlaySfxPositional(SFX_METAL_CLANG_E);
    }

    parent = self - 1;
    animCurFrame = parent->animCurFrame - 3;

    if (animCurFrame > 0x2A) {
        animCurFrame = 0;
    }

    self->hitboxOffX = guardHitboxOffsetXYs[animCurFrame][0];
    self->hitboxOffY = guardHitboxOffsetXYs[animCurFrame][1];
    self->hitboxWidth = guardHitboxWidthHeights[animCurFrame][0];
    self->hitboxHeight = guardHitboxWidthHeights[animCurFrame][1];
    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;

    if (parent->entityId != E_SPEAR_GUARD) {
        DestroyEntity(self);
    }
}
