// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"

static bool func_pspeu_09243F60(s16* val, s16 target, s16 step) {
    if (abs(*val - target) < step) {
        *val = target;
        return true;
    }
    if (*val > target) {
        *val -= step;
    }
    if (*val < target) {
        *val += step;
    }
    return false;
}
typedef struct {
    s16 animFrame;
    s16 zOffset;
    s16 xPos;
    s16 yPos;
    s16 minRot;
    s16 maxRot;
} unkParams;

static unkParams D_pspeu_0924C278[] = {
    {3, -1, 5, -11, -1024, 384}, 
    {4, -1, -9, -6, -4095, 4095},
    {5, 1, -9, -6, -4095, 4095},
    {6, 1, 5, -11, -1024, 256}
};
static s16 D_pspeu_0924C2A8[] = {0, 48, 1, 0,};
static AnimateEntityFrame D_us_8018198C[] = {{5, 8}, {5, 9}, {5, 10}, {5, 11}, POSE_LOOP(0)};
static AnimateEntityFrame D_us_80181998[] = {{8, 12}, {8, 13}, {8, 12}, POSE_END};

extern EInit g_EInitScarecrow;

void func_us_801AF448(Entity* self) {
    Collider sp2C;
    Entity* other;
    s16 var_s5;
    s32 yVar;
    s32 xVar;
    s32 var_s2;
    s32 i;

    if ((self->flags & 0x100) && ((self->step) != 3)) {
        SetStep(3);
    }
    switch (self->step) {                              
    case 0x0:                                       
        InitializeEntity(g_EInitScarecrow);
        self->drawFlags = 4;
        self->animCurFrame = 2;
        self->hitboxWidth = 0xC;
        self->hitboxHeight = 8;
        self->hitboxOffY = -6;
        if (!(Random() & 0xF)) {
            self->params |= 1;
        }
        if (self->params) {
            self->palette -= 1;
            self->animCurFrame = 7;
            self->hitboxWidth = 9;
            self->hitboxHeight = 0xC;
            self->hitboxOffY = -6;
            return;
        }
        for(other = self + 1, i = 0; i < 4; i++, other++){
            CreateEntityFromEntity(0x25, self, other);
            other->params = i;
            other->nextPart = other - 1;
            other->parent = self;
        }
        self->nextPart = self + 4;
    case 0x1:                                       
        switch (self->step_s) {                        
        case 0:                                     
            self->velocityY = -0x28000;
            if (self->facingLeft) {
                self->velocityX = 0x18000;
            } else {
                self->velocityX = -0x18000;
            }
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     
            MoveEntity();
            self->velocityY += 0x2000;
            if (self->velocityY > 0) {
                func_pspeu_09243F60(&self->rotate, 0x100, 8);
            } else {
                func_pspeu_09243F60(&self->rotate, -0x100, 0x10);
            }
            xVar = self->posX.i.hi;
            yVar = self->posY.i.hi + 0x30;
            g_api.CheckCollision(xVar, yVar, &sp2C, 0);
            if (sp2C.effects & 1) {
                self->step_s = 0;
                PlaySfxPositional(0x649);
                var_s2 = sp2C.unk18;
                xVar = self->posX.i.hi;
                yVar = self->posY.i.hi + 0x28;
                g_api.CheckCollision(xVar, yVar, &sp2C, 0);                
                if (sp2C.effects & 1) {
                    self->facingLeft ^= 1;
                    return;
                }
                self->posY.i.hi += var_s2;
                var_s2 = (GetSideToPlayer() & 1) ^ 1;
                xVar = GetDistanceToPlayerX();
                if ((var_s2 != self->facingLeft) && (xVar > 0x40)) {
                    self->facingLeft ^= 1;
                    if (!(Random() & 3)) {
                        SetStep(2);
                        return;
                    }
                }
            }
            break;
        }
        break;
    case 0x2:                                       
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.ILLEGAL.s16[2] = (Random() & 0x1F) + 0x20;
            self->step_s += 1;
        }
        var_s2 = UnkCollisionFunc2(&D_pspeu_0924C2A8);
        if (self->facingLeft) {
            self->velocityX += 0x1000;
        } else {
            self->velocityX -= 0x1000;
        }
        if (var_s2 == 0xFF) {
            self->ext.ILLEGAL.s16[2] = 1;
        }
        if (!--self->ext.ILLEGAL.s16[2]) {
            self->facingLeft = GetSideToPlayer() & 1;
            SetStep(1);
        }
        break;
    case 0x3:                                       
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 3;
        }
        var_s2 = 0x30;
        var_s5 = self->rotate + 0x400;
        if (self->facingLeft) {
            var_s5 = 0x800 - var_s5;
        }
        for(i = 0; i < 8; i++){
            xVar = (var_s2 * rcos(var_s5)) >> 0xC;
            yVar = (var_s2 * rsin(var_s5)) >> 0xC;
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(0x26, self, other);
                other->params = 3;
                other->rotate = self->rotate;
                other->posX.i.hi += xVar;
                other->posY.i.hi += yVar;
            }
            var_s2 -= 8;
        }
        PlaySfxPositional(0x62C);
        DestroyEntity(self);
        return;
    case 0xFF:                                      
#include "../pad2_anim_debug.h"
    }
}

extern EInit D_us_801806A0;

void func_us_801AF9E8(Entity* self) {
    s32 yOffset;
    s32 xOffset;
    s32 sine;
    s32 cosine;
    s16 angle;
    s16 angleChange;
    s32 yVar;
    s32 xVar;
    Entity* other;
    unkParams* temp_s1;

    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_801806A0);
        self->drawFlags |= 4;
        other = (self - 1) - (self->params);
        temp_s1 = &D_pspeu_0924C278[self->params];
        self->animCurFrame = temp_s1->animFrame;
        self->zPriority = other->zPriority + temp_s1->zOffset;
        self->ext.ILLEGAL.u32[2] = other->velocityX;
        self->ext.ILLEGAL.u32[3] = other->velocityY;
        /* fallthrough */
    case 1:
        other = (self - 1) - (self->params);
        temp_s1 = &D_pspeu_0924C278[self->params];
        self->posX.i.hi = other->posX.i.hi;
        self->posY.i.hi = other->posY.i.hi;
        self->facingLeft = other->facingLeft;
        self->palette = other->palette;
        angle = other->rotate;
        xVar = temp_s1->xPos;
        yVar = temp_s1->yPos;
        sine = rsin(angle);
        cosine = rcos(angle);
        // This is doing a 2D rotation matrix!
        xOffset = ((xVar * cosine) - (yVar * sine)) >> 0xC;
        yOffset = ((xVar * sine) + (yVar * cosine)) >> 0xC;
        if (self->facingLeft) {
            self->posX.i.hi -= xOffset;
        } else {
            self->posX.i.hi += xOffset;
        }
        self->posY.i.hi += yOffset;
        xVar = other->velocityX - self->ext.ILLEGAL.u32[2];
        if (self->facingLeft) {
            xVar = -xVar;
        }
        yVar = -(other->velocityY - self->ext.ILLEGAL.u32[3]);
        angleChange = xVar >> 8;
        angleChange += yVar >> 8;
        self->rotate += angleChange;
        func_pspeu_09243F60(&self->rotate, 0, 0x10);
        if (self->rotate > temp_s1->maxRot) {
            self->rotate = temp_s1->maxRot;
        }
        if (self->rotate < temp_s1->minRot) {
            self->rotate = temp_s1->minRot;
        }
        self->ext.ILLEGAL.u32[2] = other->velocityX;
        self->ext.ILLEGAL.u32[3] = other->velocityY;
        if (other->entityId != 0x24) {
            DestroyEntity(self);
        }
    }
}

extern EInit g_EInitSchmoo;

void func_us_801AFC88(Entity* self) {
    Entity* other;
    s32 side;
    s32 xDist;

    if (self->flags & 0x100) {
        PlaySfxPositional(0x655);
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(2, self, other);
            other->params = 1;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(g_EInitSchmoo);
        self->drawFlags = 4;
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        /* fallthrough */
    case 1:                                         /* switch 1 */
        AnimateEntity(&D_us_8018198C, self);
        MoveEntity();
        side = GetSideToPlayer();
        if (self->facingLeft) {
            self->velocityX += 0xC00;
            if (self->velocityX > FIX(3)) {
                self->velocityX = FIX(3);
            }
        } else {
            self->velocityX -= 0xC00;
            if (self->velocityX < FIX(-3)) {
                self->velocityX = FIX(-3);
            }
        }
        if (side & 2) {
            self->velocityY -= 0xC00;
            if (self->velocityY < FIX(-1.5)) {
                self->velocityY = FIX(-1.5);
            }
        } else {
            self->velocityY += 0xC00;
            if (self->velocityY > FIX(1.5)) {
                self->velocityY = FIX(1.5);
            }
        }
        side = (side & 1) ^ 1;
        xDist = GetDistanceToPlayerX();
        if ((side != self->facingLeft) && (xDist > 0x58)) {
            SetStep(2);
        }
        break;
    case 2:                                         /* switch 1 */
        MoveEntity();
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            self->velocityX -= self->velocityX >> 4;
            self->velocityY -= self->velocityY >> 4;
            if (abs(self->velocityX) < 0x4000) {
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            self->velocityX -= self->velocityX >> 8;
            self->velocityY -= self->velocityY >> 8;
            if (AnimateEntity(&D_us_80181998, self) == 0) {
                SetStep(1);
            }
            if (!self->poseTimer && self->pose == 2) {
                self->facingLeft ^= 1;
            }
            break;
        }
        break;
    }
    self->rotate = -abs(self->velocityX >> 8);
}