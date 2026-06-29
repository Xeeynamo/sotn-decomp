// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rno3/rno3.h"

extern EInit D_us_801809C8;
extern EInit g_EInitOrobourous;
extern EInit g_EInitOruburos;
extern EInit g_EInitOruburosRider;


extern u8 D_pspeu_0925A6B0[] = {32, 4, 6, 5, 6, 6, 14, 7, 6, 6, 6, 5, 0};
extern u8 D_pspeu_0925A6C0[] = {8, 16, 8, 15, 255, 0};
extern s16 D_pspeu_0925A6C8[] = {0, 12, 0, 4, 8, -4, -16, 0};
typedef struct{
    u32 velX;
    u32 velY;
    s16 rotate;
} adhoc_vels_rot;
extern adhoc_vels_rot D_pspeu_0925A6D8[] = {{FIX(0.0625), FIX(0.0), -8}, 
                                           {FIX(0.25), FIX(-1.5), 40}, 
                                           {FIX(0.5), FIX(-0.5), 16}, 
                                           {FIX(0.125), FIX(-0.375), 8}};
extern s16 D_pspeu_0925A708[] = {-7, 2, 13, 10, 4, 0, 7, 13, -5, 0, 7, 13};
extern s8 D_pspeu_0925A720;
void func_us_801C4334(Entity* self);

void func_us_801C35F8(Entity* self) {
    Collider sp3C;
    Entity* other;
    s32 var_s7;
    s32 var_s6;
    s16* var_s5;
    s16 var_s4;
    s32 xVar;
    s32 yVar;
    s32 i;

    if (self->flags & 0x100) {
        SetStep(8U);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOrobourous);
        self->animCurFrame = 0xE;
        self->drawFlags |= 4;
        other = self + 1;
        for(i = 0; i < 0x18; i++, other++){
            CreateEntityFromEntity(0x2C, self, other);
            other->params = (i + 1);
            other->nextPart = other - 1;
        }
        self->parent = NULL;
        self->nextPart = self + 24;
        CreateEntityFromEntity(0x2E, self, other);
        self->ext.ILLEGAL.u8[9] = 2;
        break;
    case 1:
        if (UnkCollisionFunc3(&D_pspeu_0925A6C8) & 1) {
            SetStep(2U);
        }
        break;
    case 2:
        SetStep(3U);
        break;
    case 3:
        MoveEntity();
        self->velocityY += self->ext.ILLEGAL.u32[3];
        self->ext.ILLEGAL.u32[3] += 0x100;
        if (self->velocityY < 0) {
            self->animCurFrame = 1;
        } else {
            self->animCurFrame = 0xE;
        }
        if (((self->ext.ILLEGAL.u8[8]) != self->facingLeft) && (AnimateEntity(D_pspeu_0925A6C0, self) == 0)) {
            self->animCurFrame = 0xE;
            self->facingLeft = self->ext.ILLEGAL.u8[8];
        }
        if (self->rotate) {
            self->rotate -= 0x10;
        }
        xVar = self->posX.i.hi;
        yVar = self->posY.i.hi + 12;
        g_api.CheckCollision(xVar, yVar, &sp3C, 0);
        if (sp3C.effects & 1) {
            PlaySfxPositional(0x63D);
            self->posY.i.hi += sp3C.unk18;
            self->velocityY = -0x30000;
            self->ext.ILLEGAL.u32[3] = 0;
            var_s7 = self->ext.ILLEGAL.u8[8];
            if (var_s7 == (GetSideToPlayer() & 1)) {
                self->ext.ILLEGAL.u8[9] -= 1;
            } else {
                self->ext.ILLEGAL.u8[9] = 2;
            }
            xVar = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (self->ext.ILLEGAL.u8[8]) {
                if (((g_Tilemap.hSize << 8) - 0x80) < xVar) {
                    self->ext.ILLEGAL.u8[9] = 0;
                }
            } else if (xVar < 0x80) {
                self->ext.ILLEGAL.u8[9] = 0;
            }
            if (!self->ext.ILLEGAL.u8[9]) {
                self->ext.ILLEGAL.u8[9] = 2;
                self->ext.ILLEGAL.u8[8] ^= 1;
                self->poseTimer = 0;
                self->pose = 0;
            } else {
                self->rotate = 0x200;
            }
            if (self->ext.ILLEGAL.u8[8]) {
                self->velocityX = 0x18000;
                EntityGreyPuffSpawner(self, 5, 3, 4, 12, 0, -4);
            } else {
                self->velocityX = -0x18000;
                EntityGreyPuffSpawner(self, 5, 3, -4, 12, 0, 4);
            }
        }
        if (self->ext.ILLEGAL.u8[0xA]) {
            self->animCurFrame = 0xE;
            SetStep(4U);
        }
        break;
    case 4:
        other = self + 1;
        for(i = 0; i < 0x18; i++, other++){
            other->ext.ILLEGAL.u8[0xA] = 1;
        }
        self->drawFlags = 0;
        self->ext.ILLEGAL.u8[9] = 0;
        self->hitboxState = 0;
        self->ext.ILLEGAL.s16[0xC] = 0x800;
        self->ext.ILLEGAL.s16[2] = 0x10;
        other = AllocEntity(&g_Entities[32], &g_Entities[47]);
        if (other != NULL) {
            DestroyEntity(other);
            other->entityId = 0x43;
            other->step = 1;
            other->pfnUpdate = func_us_801C4334;
            other->ext.prim = (Primitive* ) self;
        } else {
            self->ext.ILLEGAL.s16[0xC] = -1U;
        }
        SetStep(5U);
        /* fallthrough */
    case 5:
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->ext.ILLEGAL.s16[2] = 4;
            other = self + self->ext.ILLEGAL.u8[9];
            other->palette += 2;
            if (self->ext.ILLEGAL.u8[9]++ > 0x18) {
                SetStep(6U);
            }
        }
        /* fallthrough */
    case 6:
        FntPrint("rest_time:%x\n", self->ext.ILLEGAL.s16[0xC]);
        if (!self->step_s) {
            self->ext.ILLEGAL.s16[0xA] = 0x40;
            var_s4 = Random() * 8;
            xVar = (rcos(var_s4) * 0x60) >> 0xC;
            yVar = (rsin(var_s4) * -0x60) >> 0xC;
            if (!self->ext.ILLEGAL.s16[0xC]) {
                xVar = 0;
                yVar = 0;
                self->ext.ILLEGAL.s16[0xC]--;
                self->ext.ILLEGAL.s16[0xA] = 0x100;
            }
            if (self->ext.ILLEGAL.s16[0xC] < 0) {
                xVar = 0x200;
                yVar = -0x300;
                self->ext.ILLEGAL.s16[0xA] = 0x400;
            }
            other = &PLAYER;
            self->ext.ILLEGAL.s16[0xE] = other->posX.i.hi + xVar;
            self->ext.ILLEGAL.s16[0xF] = other->posY.i.hi + yVar;
            self->step_s += 1;
        }
        if (self->ext.ILLEGAL.u8[8] != self->facingLeft && (AnimateEntity(D_pspeu_0925A6C0, self) == 0)) {
            self->animCurFrame = 0xE;
            self->facingLeft = self->ext.ILLEGAL.u8[8];
            self->pose = 0;
            self->poseTimer = 0;
        }
        MoveEntity();
        if (self->velocityX > 0) {
            self->ext.ILLEGAL.u8[8] = 1;
        } else {
            self->ext.ILLEGAL.u8[8] = 0;
        }
        xVar = self->ext.ILLEGAL.s16[0xE] - self->posX.i.hi;
        yVar = self->ext.ILLEGAL.s16[0xF] - self->posY.i.hi;
        var_s4 = ratan2(yVar, xVar);
        var_s4 = GetNormalizedAngle(0x20, self->ext.ILLEGAL.s16[0xB], var_s4);
        self->velocityX = rcos(var_s4) * 0x24;
        self->velocityY = rsin(var_s4) * 0x24;
        self->ext.ILLEGAL.s16[0xB] = var_s4;
        if ((!--self->ext.ILLEGAL.s16[0xA]) || ((abs(xVar) < 8) && (abs(yVar) < 8))) {
            self->step_s = 0;
        }
        if (self->ext.ILLEGAL.s16[0xC] > 0) {
            self->ext.ILLEGAL.s16[0xC]--;
            break;
        }
        if (self->posY.i.hi < -0x200) {
            other = self + 1;
            for(i = 0; i < 24; i++, other++){
                DestroyEntity(other);
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        }
        break;
    case 8:
        PlaySfxPositional(0x629);
        other = self + 1;
        for(i = 0; i < 25; i++, other++) {
            other->flags |= 0x100;
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 3;
        }
        for(i = 0;i < 4; i++){
            if (i != 1) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(0x2D, self, other);
                    other->facingLeft = self->facingLeft;
                    other->velocityX = self->velocityX;
                    other->velocityY = -0x18000;
                    other->params = i;
                }
            }
        }
        DestroyEntity(self);
        return;
    }
    var_s5 = &D_pspeu_0925A708[0];
    var_s6 = self->animCurFrame - 0xE;
    if (var_s6 < 0) {
        var_s6 = 0;
    }
    var_s5 += var_s6 * 4;
    self->hitboxOffX = *var_s5++;
    self->hitboxOffY = *var_s5++;
    self->hitboxWidth = *var_s5++;
    self->hitboxHeight = *var_s5++;
}

void func_us_801C3DE0(Entity* self) {
    s32 speed;
    s16 angle;
    s32 xVar;
    s32 yVar;
    Entity* other;
    s32 miscTemp;

    if ((self->flags & 0x100) && ((self->step) < 8)) {
        self->hitboxState = 0;
        self->flags |= 0xC0000000;
        SetStep(8U);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOruburos);
        self->hitboxOffY = 1;
        self->pose = self->params % 6;
        self->drawFlags |= 8;
        miscTemp = self->params;
        self->opacity = (0x80 - miscTemp);
        miscTemp -= 10;
        if (miscTemp > 0) {
            self->drawFlags = 3;
            self->scaleX = self->scaleY = 0x100 - (miscTemp * 6);
        }
        if ((self->params) == 4) {
            self->animCurFrame = 0x11;
        }
        if ((self->params) == 0xC) {
            self->animCurFrame = 0x12;
        }
        break;
    case 1:
        MoveEntity();
        other = self - 1;
        xVar = other->posX.i.hi - self->posX.i.hi;
        yVar = other->posY.i.hi - self->posY.i.hi;
        miscTemp = (xVar * xVar) + (yVar * yVar);
        miscTemp =  SquareRoot0(miscTemp);
        speed = miscTemp * 3;
        angle = ratan2(yVar, xVar);
        miscTemp = speed * rcos(angle);
        self->velocityX = miscTemp;
        self->velocityY = speed * rsin(angle);
        if (miscTemp > 0) {
            self->facingLeft = 1;
        } else {
            self->facingLeft = 0;
        }
        break;
    case 8:
        MoveEntity();
        self->velocityY += 0x1400;
        return;
    }
    if (((self->params) != 4) && ((self->params) != 0xC)) {
        AnimateEntity(D_pspeu_0925A6B0, self);
    }
    miscTemp = (self->params & 3);
    if ((g_Timer & 3) == miscTemp) {
        self->hitboxState = 3;
    } else {
        self->hitboxState = 0;
    }
    if (self->ext.ILLEGAL.u8[0xA]) {
        self->hitboxState = 0;
    }
}

void func_us_801C406C(Entity* self) {
    adhoc_vels_rot* temp_s0;

    if (!self->step) {
        InitializeEntity(D_us_801809C8);
        self->drawFlags = 4;
        self->hitboxState = 0;
        self->animCurFrame = self->params + 8;
        self->zPriority += self->params;
        temp_s0 = &D_pspeu_0925A6D8[self->params];
        if (self->facingLeft) {
            self->velocityX += temp_s0->velX;
        } else {
            self->velocityX += -temp_s0->velX;
        }
        self->velocityY += temp_s0->velY;
    }
    MoveEntity();
    self->velocityY += 0x1800;
    temp_s0 = &D_pspeu_0925A6D8[self->params];
    self->rotate += temp_s0->rotate;
}

void func_us_801C4178(Entity* self) {
    Entity* other;

    if (self->flags & 0x100) {
        PlaySfxPositional(0x655);
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 1;
        }
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(0x2D, self, other);
            other->facingLeft = self->facingLeft;
            other->params = 1;
        }
        other = self - 25;
        other->ext.ILLEGAL.u8[0xA] = 1;
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitOruburosRider);
        self->animCurFrame = 0xD;
        self->hitboxOffX = 5;
        self->hitboxOffY = -2;
        self->drawFlags = 4;
        break;
    case 1:
        other = self - 25;
        self->facingLeft = other->facingLeft;
        // Note! This is a useless if statement, with useless shifts!
        // There was probably some kind of OFFSET defined but set
        // to zero at final release.
        if (self->facingLeft) {
            self->posX.i.hi = other->posX.i.hi - 0;
        } else {
            self->posX.i.hi = other->posX.i.hi + 0;
        }
        self->posY.i.hi = other->posY.i.hi - 0xA;
        if (other->animCurFrame == 0xE) {
            self->zPriority = other->zPriority + 1;
        } else {
            self->zPriority = other->zPriority - 1;
        }
        if (other->velocityY > 0) {
            self->animCurFrame = 0xD;
            if (self->rotate > -0x240) {
                self->rotate -= 0x18;
            }
        } else {
            self->animCurFrame = 0;
            self->rotate = 0;
        }
        break;
    }
}

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_1A748", func_us_801C4334);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_1A748", func_us_801C4468);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_1A748", func_us_801C48D8);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_1A748", func_us_801C4B44);

INCLUDE_ASM("st/rno3_psp/nonmatchings/rno3_psp/unk_1A748", func_us_801C4C50);
