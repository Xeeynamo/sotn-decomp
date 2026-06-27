// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno3.h"

extern EInit D_us_80180980;
extern EInit D_us_8018098C;
extern EInit g_EInitJackOBones;

static u8 D_pspeu_09259028[] = {6, 1, 4, 2, 4, 3, 6, 4, 5, 5, 5, 6, 0};
static u8 D_pspeu_09259038[] = {6, 1, 5, 6, 5, 5, 6, 4, 4, 3, 4, 2, 0};
static u8 D_pspeu_09259048[] = {5, 1, 5, 2, 5, 7, 6, 8, 5, 9, 5, 10, 5, 11, 31, 12, 4, 4, 4, 5, 4, 6, 255, 0};
static u8 D_pspeu_09259060[] = {1, 1, 4, 13, 4, 14, 1, 1, 255, 0};
static u8 D_pspeu_09259070[] = {1, 1, 4, 13, 6, 14, 4, 13, 1, 1, 255, 0};
static u16 D_pspeu_09259080[] = {0x100, 0x80, 0x48, 0x20, 0x40, 0x10, 0x18, 0};
static u8 D_pspeu_09259090[] = {48, 32, 20, 12, 24, 16, 20, 0}; // good to 25b0
static s32 D_pspeu_09259098[] = {0xc000, 0x1c000, 0x18000, 0x10000, 0x20000, 0x1c000, 0xc000};
static s32 D_pspeu_092590B8[] = {-0x50000, -0x30000, -0x20000, -0x30000, -0x40000, -0xe000, -0x40000};
static s16 D_pspeu_092590D8[] = {-4, 0, 4, -4, -4, 4, 0, 0,};
static s16 D_pspeu_092590E8[] = {-16, -8, -4, -4, 9, 9, 0, 0};
static u8 D_pspeu_092590F8[][4] = {{96, 8, 8, 64}, {128, 64, 32, 48}};
static s16 D_pspeu_09259100[] = {0, 20, 0, 4, 8, -4, -16, 0};
static u16 D_pspeu_09259110[] = {0, 20, 12, 0};
static s16 D_pspeu_09259118[] = {-12, 16, 0, -16, 0, -16};

typedef enum {
    JACKO_INIT,
    JACKO_1,
    JACKO_2,
    JACKO_3,
    JACKO_4,
    JACKO_5,
    JACKO_DEAD
} JackOBonesSteps;

<<<<<<< HEAD
INCLUDE_ASM("st/rno3/nonmatchings/e_jack_o_bones", func_us_801C247C);
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 583c2b199 (pull out jackobones)
=======
>>>>>>> f04056fbe (finish splits for now)
=======
static void func_pspeu_0923DEB0(void) {
    s32 temp_s1;
    u16 temp_s0;

    temp_s1 = UnkCollisionFunc2(D_pspeu_09259110);
    temp_s0 = UnkCollisionFunc(D_pspeu_09259118, 3);
    if ((temp_s1 == 0x80) || (temp_s0 & 2)) {
        SetStep(JACKO_5);
        return;
    }
    if (!g_CurrentEntity->ext.ILLEGAL.u8[0]) {
        SetStep(JACKO_4);
        return;
    }
    g_CurrentEntity->ext.ILLEGAL.u8[0]--;
}

void EntityJackOBones(Entity* self) {
    s32 xShift;
    u8 var_s2;
    s32 i;
    Entity* other;

    if (self->flags & FLAG_DEAD) {
        self->step = JACKO_DEAD;
    }
    switch (self->step) {
    case JACKO_INIT:
        InitializeEntity(g_EInitJackOBones);
        if (self->params) {
            self->palette++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.ILLEGAL.u8[0] = 0x50;
        self->ext.ILLEGAL.u8[4] = 0;
        self->ext.ILLEGAL.u8[8] = 0;
        break;
    case JACKO_1:
        if (UnkCollisionFunc3(D_pspeu_09259100) == 0) {
            break;
        }
        self->step++;
        break;
    case JACKO_2:
        if (AnimateEntity(D_pspeu_09259028, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() < 76) {
            self->step = JACKO_3;
        }
        func_pspeu_0923DEB0();
        break;
    case JACKO_3:
        if (AnimateEntity(D_pspeu_09259038, self) == 0) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        }
        self->ext.ILLEGAL.u8[4] = self->facingLeft ^ 1;
        if (self->ext.ILLEGAL.u8[4]) {
            self->velocityX = FIX(0.5);
        } else {
            self->velocityX = FIX(-0.5);
        }
        if (GetDistanceToPlayerX() > 92) {
            self->step = JACKO_2;
        }
        func_pspeu_0923DEB0();
        break;
    case JACKO_4:
        var_s2 = AnimateEntity(D_pspeu_09259048, self);
        // We set a value here but it is never used.
        if (self->params) {
            i = 11;
        } else {
            i = 10;
        }
        if (!var_s2) {
            SetStep(JACKO_3);
            var_s2 = ++self->ext.ILLEGAL.u8[8] & 3;
            self->ext.ILLEGAL.u8[0] =
                D_pspeu_092590F8[self->params & 1][var_s2];
            break;
        }
        if ((var_s2 & 0x80) && (self->animCurFrame == 0xB)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                PlaySfxPositional(SFX_BONE_THROW);
                CreateEntityFromCurrentEntity(E_UNK_26, other);
                if (self->params) {
                    xShift = -0x10;
                } else {
                    xShift = 8;
                }
                if (self->facingLeft) {
                    other->posX.i.hi -= xShift;
                } else {
                    other->posX.i.hi += xShift;
                }
                other->posY.i.hi -= 0x10;
                other->params = self->params;
                other->facingLeft = self->facingLeft;
            }
        }
        break;
    case JACKO_5:
        switch (self->step_s) {
        case 0:
            if (!(AnimateEntity(D_pspeu_09259060, self) & 1)) {
                var_s2 = self->ext.ILLEGAL.u8[4];
                if (!(Random() & 3)) {
                    var_s2 ^= 1;
                }
                if (var_s2) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX = FIX(-2);
                }
                self->velocityY = FIX(-3);
                self->pose = 0;
                self->poseTimer = 0;
                self->step_s++;
            }
            break;
        case 1:
            if (UnkCollisionFunc3(D_pspeu_09259100)) {
                self->step_s++;
            }
            CheckFieldCollision(D_pspeu_09259118, 2);
            break;
        case 2:
            if (AnimateEntity(D_pspeu_09259070, self) == 0) {
                SetStep(JACKO_3);
            }
        }
        break;
    case 6:
        PlaySfxPositional(SFX_SKELETON_DEATH_B);
        for (i = 0; i < 6; i++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other == NULL) {
                break;
            }
            CreateEntityFromCurrentEntity(E_UNK_25, other);
            other->facingLeft = self->facingLeft;
            other->params = i;
            other->params |= (self->params << 8);
            other->ext.ILLEGAL.u8[0xC] = D_pspeu_09259090[i];
            if (self->facingLeft) {
                other->posX.i.hi -= D_pspeu_092590D8[i];
            } else {
                other->posX.i.hi += D_pspeu_092590D8[i];
            }
            other->posY.i.hi += D_pspeu_092590E8[i];
            other->velocityX = D_pspeu_09259098[i];
            other->velocityY = D_pspeu_092590B8[i];
        }
        DestroyEntity(self);
        break;
    }
}

void func_us_801C2380(Entity* self) {
    if (self->step) {
        if (--self->ext.ILLEGAL.u8[0xC]) {
            self->rotate += D_pspeu_09259080[self->params];
            FallEntity();
            MoveEntity();
            return;
        }
        self->entityId = 2;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
        return;
    }
    InitializeEntity(D_us_80180980);
    self->animCurFrame = (self->params & 0xFF) + 0xF;
    if (self->params & 0x100) {
        self->palette += 1;
    }
    self->drawFlags = ENTITY_ROTATE;
    if (self->facingLeft) {
        self->velocityX = -self->velocityX;
    }
}

void func_us_801C247C(Entity* self) {
    Collider sp10;
    s32 temp;
    s32 yVar;
    s32 xVar;

    if (!self->step) {
        InitializeEntity(D_us_8018098C);
        if (self->params) {
            self->palette += 1;
        }
        self->animCurFrame = 0x15;
        self->drawFlags |= ENTITY_ROTATE;
        if (self->params) {
            yVar = 0x40000;
            xVar = 0x10000;
        } else {
            yVar = -0x10000;
            xVar = 0x28000;
        }
        if (self->facingLeft) {
            self->velocityX = xVar;
        } else {
            self->velocityX = -xVar;
        }
        self->velocityY = yVar;
    }
    MoveEntity();
    self->velocityY += FIX(0.1875);
    self->rotate -= 0x40;
    xVar = self->posX.i.hi;
    yVar = self->posY.i.hi + 5;
    g_api.CheckCollision(xVar, yVar, &sp10, 0);
    if (sp10.effects & EFFECT_SOLID) {
        PlaySfxPositional(SFX_SKULL_KNOCK_A);
        self->ext.ILLEGAL.s16[8] += 1;
        temp = sp10.unk18;
        #if defined(VERSION_PSP)
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 3;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->velocityX = -self->velocityX;
        } else {
        #else
        if(1){
        #endif
            self->posY.i.hi += temp;
            #if defined(VERSION_PSP)
            self->velocityY = -self->velocityY;
            #else
            self->velocityY = -((self->velocityY < 0) ? -self->velocityY : self->velocityY);
            #endif
            if (self->params) {
                self->velocityY = FIX(-7) / self->ext.ILLEGAL.s16[8];
            } else {
                self->velocityY -= self->velocityY / 16;
            }
        }
        xVar = self->posX.i.hi + self->velocityX;
        yVar = self->posY.i.hi;
    }
    #if defined(VERSION_PSP)
    if (self->params) {
    #else
    if(1) {
    #endif
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 5;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk20;
            self->velocityY = abs(self->velocityY);
        }
        #if !defined(VERSION_PSP)
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi;
        if(self->velocityX > 0){
            xVar += 5;
        } else {
            xVar -= 5;
        }
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->velocityX = -self->velocityX;
        }
        if (self->params)
        #endif
        if (self->ext.ILLEGAL.s16[8] > 8) {
            self->flags |= FLAG_DEAD;
        }
    }

    if (self->flags & FLAG_DEAD) {
        self->drawFlags = ENTITY_DEFAULT;
        self->entityId = 2;
        self->pfnUpdate = EntityExplosion;
        self->params = 0;
        self->step = 0;
    }
}
>>>>>>> 092e0b5c6 (migrating to US)
