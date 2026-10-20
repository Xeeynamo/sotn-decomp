// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_C8E0", func_pspeu_09243F60);

extern s16 D_pspeu_0924C2A8[];
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

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_C8E0", func_us_801AF9E8);

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_C8E0", func_us_801AFC88);
