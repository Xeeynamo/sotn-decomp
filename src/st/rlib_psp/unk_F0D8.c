// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rlib/rlib.h"

static bool ApproachTarget(s16* val, s16 target, s16 step) {
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

extern EInit g_EInitTinman;


extern s16 D_pspeu_0924C2D8[];
extern s16 D_pspeu_0924C2E8[];
extern AnimateEntityFrame D_pspeu_0924C2F0[];
extern AnimateEntityFrame D_pspeu_0924C300[];
extern AnimateEntityFrame D_pspeu_0924C340[];
extern AnimateEntityFrame D_pspeu_0924C380[];
extern AnimationFrame D_us_80181888;
extern AnimationFrame D_us_8018189C;

void EntityTinMan(Entity* self) {
    s32 var_s2;
    s32 var_s1;
    Entity* other;

    if (self->step) {
        if ((self->hitPoints < g_api.enemyDefs[0x108].hitPoints/4 ) && (self->step < 5)) {
            SetStep(5);
        }
    }
    if (self->hitFlags & 3) {
        PlaySfxPositional(0x73D);
    }
    if ((self->flags & 0x100) && (self->step != 7)) {
        SetStep(7);
    }
    switch (self->step) {                            /* switch 1; irregular */
    case 0x0:                                       /* switch 1 */
        InitializeEntity(g_EInitTinman);
        self->hitboxOffY = 9;
        other = self + 1;
        CreateEntityFromCurrentEntity(0x20, other);
        other->zPriority = self->zPriority + 1;
        /* fallthrough */
    case 0x1:                                       /* switch 1 */
        if (UnkCollisionFunc3(&D_pspeu_0924C2D8) & 1) {
            SetStep(2);
        }
        break;
    case 0x2:                                       /* switch 1 */
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 0x3:                                       /* switch 1 */
        AnimateEntity(&D_pspeu_0924C2F0, self);
        self->ext.ILLEGAL.u8[8] = 0;
        var_s2 = 0;
        if (self->facingLeft) {
            self->velocityX += 0x800;
            if (self->velocityX > FIX(1.5)) {
                self->velocityX = FIX(1.5);
                var_s2 = 1;
            }
        } else {
            self->velocityX -= 0x800;
            if (self->velocityX < FIX(-1.5)) {
                self->velocityX = FIX(-1.5);
                var_s2 = 1;
            }
        }
        if (var_s2 != 0) {
            if (Random() & 0x1F) {
                var_s2 = 0;
            } else {
                var_s2 = 1;
            }
            if (self->poseTimer) {
                self->poseTimer -= 1;
            }
        } else if (g_Timer & 0xF) {
            var_s2 = 0;
        } else {
            var_s2 = 1;
        }
        if (var_s2 != 0) {
            other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
            if (other != NULL) {
                CreateEntityFromEntity(0x22, self, other);
                other->ext.ILLEGAL.u32[8] = (u32) self;
                other->facingLeft = self->facingLeft;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        if (UnkCollisionFunc2(&D_pspeu_0924C2E8) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        if (GetDistanceToPlayerX() < 0x50) {
            self->ext.ILLEGAL.s16[3] -= 0x100;
            self->ext.ILLEGAL.s16[3] &= 0xFFF;
        } else {
            ApproachTarget(&self->ext.ILLEGAL.s16[3], 0, 0x80);
        }
        var_s2 = GetSideToPlayer() & 1;
        if ((var_s2 == self->facingLeft) && (GetDistanceToPlayerX() > 0x30)) {
            SetStep(4);
        }
        break;
    case 0x4:                                       /* switch 1 */
        self->velocityX -= self->velocityX / 32;
        if (UnkCollisionFunc2(&D_pspeu_0924C2E8) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        switch (self->step_s) {                          /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            self->ext.ILLEGAL.u8[8] = 0;
            if (ApproachTarget(&self->ext.ILLEGAL.s16[3], 0, 0x80) != 0) {
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            self->ext.ILLEGAL.u8[8] = 1;
            if (AnimateEntity(&D_pspeu_0924C380, self) == 0) {
                self->ext.ILLEGAL.u8[8] = 0;
                self->animCurFrame = 1;
                self->facingLeft ^= 1;
                SetStep(3);
            }
            break;
        }
        break;
    case 0x5:                                       /* switch 1 */
        switch (self->step_s) {                        /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            if (GetSideToPlayer() & 1) {
                self->velocityX = 0x10000;
            } else {
                self->velocityX = -0x10000;
            }
            self->velocityY = -0x20000;
            self->drawFlags = 4;
            self->step_s += 1;
            /* fallthrough */
        case 1:                                     /* switch 3 */
            ApproachTarget(&self->rotate, 0x80, 0x10);
            if (UnkCollisionFunc3(&D_pspeu_0924C2D8) & 1) {
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 3 */
            if (ApproachTarget(&self->rotate, 0, 0x10) != 0) {
                self->ext.ILLEGAL.u8[9] = 1;
                self->drawFlags = 0;
                self->rotate = 0;
                self->step_s += 1;
            }
            break;
        case 3:                                     /* switch 3 */
            if (AnimateEntity(&D_pspeu_0924C300, self) == 0) {
                self->hitboxWidth = 0xF;
                self->hitboxHeight = 0x11;
                self->hitboxOffX = 2;
                self->hitboxOffY = 0xF;
                self->ext.ILLEGAL.s16[2] = Random() & 0xF;
                SetStep(6);
            }
            break;
        }
        break;
    case 0x6:                                       /* switch 1 */
        AnimateEntity(&D_pspeu_0924C340, self);
        if (!(self->ext.ILLEGAL.s16[2] & 7)) {
            PlaySfxPositional(0x658);
        }
        self->ext.ILLEGAL.s16[2]++;
        if (!(self->ext.ILLEGAL.s16[2] & 3)) {
            other = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (other != NULL) {
                CreateEntityFromEntity(0x21, self, other);
                other->facingLeft = self->facingLeft;
                other->posY.i.hi -= (((self->ext.ILLEGAL.s16[2] & 7) >> 1) + 7);
                if (self->facingLeft) {
                    other->posX.i.hi -= 2;
                } else {
                    other->posX.i.hi += 2;
                }
            }
        }
        break;
    case 0x7:                                       /* switch 1 */
        if(UnkCollisionFunc3(&D_pspeu_0924C2D8) & 1){
            
        }
        ApproachTarget(&self->rotate, 0, 0x20);
        switch (self->step_s) {                         /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            self->hitboxState = 0;
            if (self->ext.ILLEGAL.u8[9]) {
                self->step_s = 2;
            } else {
                self->step_s = 1;
            }
            break;
        case 1:                                     /* switch 4 */
            if (AnimateEntity(&D_pspeu_0924C300, self) == 0) {
                self->step_s += 1;
            }
            break;
        case 2:                                     /* switch 4 */
            for(var_s1 = 0; var_s1 < 11; var_s1++) {
                other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
                if (other != NULL) {
                    CreateEntityFromEntity(0x23, self, other);
                    other->facingLeft = self->facingLeft;
                    other->params = (var_s1 + 0x3B);
                }
            }
            PlaySfxPositional(0x6CA);
            DestroyEntity(self);
        }
        break;
    case 0xFF:                                      /* switch 1 */
#include "../pad2_anim_debug.h"
    }
}

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_us_801AED4C);

extern EInit D_us_80180688;

void func_us_801AEFE0(Entity* self) {
    Entity* parent;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180688);
        self->blendMode = BLEND_TRANSP;
        PlaySfxPositional(SFX_NOISE_SWEEP_DOWN_B);
        /* fall through */
    case 1:
        parent = self->ext.et_801AEFE0.parent;
        self->posX.val = parent->posX.val;
        self->posY.val = parent->posY.val;
        if (AnimateEntity(&D_us_80181888, self) == 0) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit D_us_8018067C;

void func_us_801D8D44_from_no4(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018067C);
        if (self->facingLeft) {
            self->velocityX = FIX(6);
        } else {
            self->velocityX = FIX(-6);
        }
        /* fall through */
    case 1:
        MoveEntity();
        AnimateEntity(&D_us_8018189C, self);
        if (self->flags & FLAG_DEAD) {
            DestroyEntity(self);
        }
        break;
    }
}

INCLUDE_ASM("st/rlib_psp/nonmatchings/rlib_psp/unk_F0D8", func_us_801AF11C);
