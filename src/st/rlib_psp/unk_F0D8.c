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

extern EInit D_us_80180670;

void func_us_801AED4C(Entity* self) {
    Entity* other;
    s16 temp_v0;
    s32 var_s1;

    other = self - 1;
    self->facingLeft = other->facingLeft;
    self->posX.val = other->posX.val;
    self->posY.val = other->posY.val;
    switch (self->step) {                              /* irregular */
    case 0:
        InitializeEntity(D_us_80180670);
        self->drawFlags = 4;
        /* fallthrough */
    case 1:
        other = self - 1;
        if ((other->ext.ILLEGAL.u8[8]) == 1) {
            self->hitboxState = 0;
            self->animCurFrame = 0;
        } else {
            self->animCurFrame = 5;
            self->rotate = other->ext.ILLEGAL.s16[3];
            self->hitboxState = 1;
            temp_v0 = self->rotate + 0x200;
            self->hitboxOffX = ((rcos(temp_v0) * 0x1C) >> 0xC);
            self->hitboxOffY = ((rsin(temp_v0) * 0x1C) >> 0xC);
            if (self->rotate >= 0xF00) {
                PlaySfxPositional(0x6C7);
            }
        }
        if ((other->ext.ILLEGAL.u8[9]) || (other->flags & 0x100)) {
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 2:
        other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
        if (other != NULL) {
            CreateEntityFromEntity(0x23, self, other);
            other->facingLeft = self->facingLeft;
            other->rotate = self->rotate;
            other->zPriority = self->zPriority;
            other->params = 5;
        }
        for(var_s1 = 0; var_s1 < 8; var_s1++) {
            other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
            if (other != NULL) {
                CreateEntityFromEntity(0x23, self, other);
                other->params = 0;
                other->zPriority = self->zPriority;
            }
        }
        PlaySfxPositional(0x645);
        other = self - 1;
        self->hitboxState = other->hitboxState;
        self->attackElement = other->attackElement;
        self->attack = other->attack;
        self->parent = self - 1;
        self->animCurFrame = 0;
        self->hitboxWidth = 0xF;
        self->hitboxHeight = 0xB;
        self->hitboxOffX = 0x17;
        self->hitboxOffY = -5;
        self->step += 1;
        return;
    case 3:
        other = self - 1;
        if ((other->entityId != 0x1F) || (other->flags & 0x100)) {
            DestroyEntity(self);
        }
        break;
    }
}
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

extern AnimateEntityFrame D_pspeu_0924C370[];
typedef struct {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    s32 unk8;
} wtf_struct;

extern wtf_struct D_pspeu_0924C398[];
extern EInit D_us_80180688;

void func_us_801AF11C(Entity* self) {
    Entity* other;
    s16 temp_v0;
    s32 temp_s2;
    u16 temp_v1;
    wtf_struct* temp_s0;

    switch (self->step) {                              /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        InitializeEntity(D_us_80180688);
        if (!self->params) {
            self->step = 1;
            temp_s2 = (Random() & 0x1F) + 0x10;
            temp_v0 = (Random() * 6) + 0x900;
            self->velocityX = temp_s2 * rcos(temp_v0);
            self->velocityY = temp_s2 * rsin(temp_v0);
            return;
        }
        self->animCurFrame = self->params;
        if (self->params > 0x3A) {
            temp_s2 = self->params - 0x3B;
            temp_s0 = &D_pspeu_0924C398[temp_s2];
            self->velocityX = temp_s0->unk4;
            if (self->facingLeft) {
                self->velocityX = -self->velocityX;
            }
            self->velocityY = temp_s0->unk8;
            self->ext.ILLEGAL.s16[2] = temp_s0->unk0;
            self->ext.ILLEGAL.u8[10] = temp_s0->unk2;
            self->step = 3;
            return;
        }
        self->drawFlags = 4;
        self->step = 2;
        return;
    case 1:                                         /* switch 1 */
        AnimateEntity(&D_pspeu_0924C370, self);
        MoveEntity();
        self->velocityY += 0x1800;
        return;
    case 2:                                         /* switch 1 */
        MoveEntity();
        self->velocityY += 0x1800;
        self->rotate += 0x80;
        return;
    case 3:                                         /* switch 1 */
        switch (self->step_s) {                        /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            if (!--self->ext.ILLEGAL.s16[2]) {
                self->ext.ILLEGAL.s16[2] = 0x20;
                self->step_s += 1;
            }
            break;
        case 1:                                     /* switch 2 */
            MoveEntity();
            if (self->ext.ILLEGAL.u8[10]) {
                self->velocityY += 0x2000;
            }
            if (!--self->ext.ILLEGAL.s16[2]) {
                PlaySfxPositional(0x655);
                other = AllocEntity(&g_Entities[0xE0], (Entity* ) &D_80097C98);
                if (other != NULL) {
                    CreateEntityFromEntity(2, self, other);
                    other->posY.i.hi += 0x10;
                    other->params = 1;
                }
                DestroyEntity(self);
            }
            break;
        }
        break;
    }
}