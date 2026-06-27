// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern u16 D_us_80180980;
extern u16 D_us_8018098C;
extern u16 D_pspeu_09259080[];

extern s32 D_pspeu_09259028;
extern s32 D_pspeu_09259038;
extern s32 D_pspeu_09259048;
extern s32 D_pspeu_09259060;
extern s32 D_pspeu_09259070;
extern u8 D_pspeu_09259090[];
extern s32 D_pspeu_09259098[];
extern s32 D_pspeu_092590B8[];
extern s16 D_pspeu_092590D8[];
extern s16 D_pspeu_092590E8[];
extern u8 D_pspeu_092590F8[][4];
extern s32 D_pspeu_09259100;
extern u16 g_EInitJackOBones;

typedef enum {
    JACKO_INIT,
    JACKO_1,
    JACKO_2,
    JACKO_3,
    JACKO_4,
    JACKO_5,
    JACKO_DEAD
} JackOBonesSteps;

extern u16 D_pspeu_09259110[];
extern u16 D_pspeu_09259118[];

void func_pspeu_0923DEB0(void) {
    s32 temp_s1;
    u16 temp_s0;

    temp_s1 = UnkCollisionFunc2(&D_pspeu_09259110);
    temp_s0 = UnkCollisionFunc(&D_pspeu_09259118, 3);
    if ((temp_s1 == 0x80) || (temp_s0 & 2)) {
        SetStep(JACKO_5);
        return;
    }
    if (!g_CurrentEntity->ext.ILLEGAL.u8[0]) {
        SetStep(JACKO_4);
        return;
    }
    g_CurrentEntity->ext.ILLEGAL.u8[0] -= 1;
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
        InitializeEntity(&g_EInitJackOBones);
        if (self->params) {
            self->palette++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->ext.ILLEGAL.u8[0] = 0x50;
        self->ext.ILLEGAL.u8[4] = 0;
        self->ext.ILLEGAL.u8[8] = 0;
        break;
    case JACKO_1:
        if (UnkCollisionFunc3(&D_pspeu_09259100) == 0) {
            break;
        }
        self->step++;
        break;
    case JACKO_2:
        if (AnimateEntity(&D_pspeu_09259028, self) == 0) {
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
        if (AnimateEntity(&D_pspeu_09259038, self) == 0) {
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
        var_s2 = AnimateEntity(&D_pspeu_09259048, self);
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
            if (!(AnimateEntity(&D_pspeu_09259060, self) & 1)) {
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
            if (UnkCollisionFunc3(&D_pspeu_09259100)) {
                self->step_s++;
            }
            CheckFieldCollision(D_pspeu_09259118, 2);
            break;
        case 2:
            if (AnimateEntity(&D_pspeu_09259070, self) == 0) {
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
    InitializeEntity(&D_us_80180980);
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
        InitializeEntity(&D_us_8018098C);
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
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 3;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->velocityX = -self->velocityX;
        } else {
            self->posY.i.hi += temp;
            self->velocityY = -self->velocityY;

            if (self->params) {
                self->velocityY = FIX(-7) / self->ext.ILLEGAL.s16[8];
            } else {
                self->velocityY -= self->velocityY / 16;
            }
        }
        xVar = self->posX.i.hi + self->velocityX;
        yVar = self->posY.i.hi;
    }
    if (self->params) {
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi - 5;
        g_api.CheckCollision(xVar, yVar, &sp10, 0);
        if (sp10.effects & EFFECT_SOLID) {
            self->posY.i.hi += sp10.unk20;
            self->velocityY = abs(self->velocityY);
        }
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
