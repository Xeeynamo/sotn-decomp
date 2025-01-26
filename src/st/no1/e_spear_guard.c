// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no1.h"

// Spear Guard helper
INCLUDE_ASM("st/no1/nonmatchings/e_spear_guard", func_us_801D37A4);

// Spear Guard helper
void func_us_801D38E4() {
    if (GetDistanceToPlayerY() > 64) {
        SetStep(3);
    }
}

// Spear Guard helper
extern u16 D_us_80182F74[];
extern s32 D_us_80182F7C[];
extern u8* D_us_80183054[];
extern s16 D_us_80183064[];

void func_us_801D3918(Entity* self, u8 arg1) {
    s32 xVelocity;
    u16 animRet = AnimateEntity(D_us_80183054[arg1], self);
    if ((animRet & 0x80) && (self->step == 7) && (self->animFrameIdx != 3)) {
        if (self->ext.spearGuard.unk88 != self->facingLeft) {
            self->velocityX = -self->velocityX;
        }
        self->ext.spearGuard.unk88 = self->facingLeft;
    }
    xVelocity = self->velocityX;
    if (self->animFrameIdx >= D_us_80182F74[arg1]) {
        if (xVelocity != 0) {
            if (self->ext.spearGuard.unk88) {
                xVelocity += D_us_80182F7C[arg1];
            } else {
                xVelocity -= D_us_80182F7C[arg1];
            }
        }
    } else {
        if (self->ext.spearGuard.unk88) {
            xVelocity -= D_us_80182F7C[arg1];
        } else {
            xVelocity += D_us_80182F7C[arg1];
        }
    }
    self->velocityX = xVelocity;
    if ((UnkCollisionFunc2(D_us_80183064) & 0x60) == 0x60) {
        self->posX.val -= xVelocity;
    }
}

// Spear Guard
extern u16 D_us_80180B00[];
extern u8 D_us_80182F10[];
extern u8 D_us_80182F14[];
extern s16 D_us_80182F24[][2];
extern s16 D_us_80182F26[];
extern u8 D_us_80182FB0[];
extern u8 D_us_80182FBC[];
extern u8 D_us_80182FDC[];
extern u8 D_us_80182FF4[];
extern u8 D_us_80183008[];
extern u8 D_us_80183018;
extern u8 D_us_80183034;
extern s16 D_us_80183064[];
extern s16 D_us_8018306C[];

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
        InitializeEntity(D_us_80180B00);
        self->ext.spearGuard.unk80 = 0xB0;
        self->ext.spearGuard.unk7C = 0x40;
        self->palette += self->params & 3;
        self->hitboxOffY = 4;
        CreateEntityFromCurrentEntity(E_ID_50, tempEntity);
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
            anim = &D_us_80183034;
        } else {
            anim = &D_us_80183018;
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
                    tempEntity->posX.i.hi += D_us_80182F24[i][0];
                    tempEntity->posY.i.hi += D_us_80182F24[i][1];
                }
            }
        }
        break;
    }
}

// Spear Guard spin block
INCLUDE_ASM("st/no1/nonmatchings/e_spear_guard", func_us_801D42EC);
