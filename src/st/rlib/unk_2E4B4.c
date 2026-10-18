// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

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


static s16 sensors1[] = {0, 34, 0, 4, 24, -4, -48, 0};
static s16 sensors2[] = {0, 34, 24, 0};
static AnimateEntityFrame D_pspeu_0924C2F0[] = {{3, 1}, {3, 2}, {3, 3}, {3, 4}, POSE_LOOP(0)};
static AnimateEntityFrame D_pspeu_0924C300[] = {{32, 1}, {4, 6}, {3, 7}, {2, 8}, {2, 9}, {8, 10}, {2, 11}, {2, 12}, {2, 13}, {2, 14}, {2, 15}, {2, 16}, {2, 17}, {2, 18}, {8, 17}, {2, 19}, {2, 21}, {2, 20}, {8, 21}, {3, 22}, {3, 23}, {3, 24}, {3, 25}, {3, 26}, {3, 27}, {3, 28}, {3, 29}, {3, 30}, {32, 21}, POSE_END};
extern AnimateEntityFrame D_pspeu_0924C340[] = {{2, 21}, {2, 31}, POSE_LOOP(0)};
extern AnimateEntityFrame D_us_80181888[] = {{3, 32}, {3, 33}, {3, 34}, {3, 35}, {3, 36}, {3, 37}, {3, 38}, {3, 39}, {3, 40}, POSE_END};
extern AnimateEntityFrame D_us_8018189C[] = {{2, 42}, {2, 43}, {2, 44}, {2, 45}, {2, 46}, POSE_LOOP(0)};
extern AnimateEntityFrame D_pspeu_0924C370[] = {{2, 47}, {2, 48}, {2, 49}, {2, 50}, {2, 51}, {2, 52}, POSE_LOOP(0)};
extern AnimateEntityFrame D_pspeu_0924C380[] = {{17, 53}, {3, 54}, {3, 55}, {3, 56}, {3, 57}, {17, 58}, {3, 57}, {3, 56}, {3, 55}, {3, 54}, POSE_END};

typedef struct {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    s32 unk8;
} wtf_struct;

static wtf_struct D_pspeu_0924C398[] = {
    {52, 0, -0x18000, 0x0000},
    {28, 1, 0xC000, -0x14000},
    {16, 1, 0x10000, -0x40000},
    {24, 1, 0x8000, -0x18000},
    {48, 1, 0x6000, -0x10000},
    {32, 1, 0xE000, -0x10000},
    {40, 0, 0x30000, 0x0000},
    {40, 1, 0x0000, -0x30000},
    {52, 0, -0xC000, 0x0000},
    {8, 1, 0x8000, -0x20000},
    {4, 1, -0x4000, -0x10000},
};

extern EInit g_EInitTinman;

void EntityTinMan(Entity* self) {
    s32 var_s2;
    s32 var_s1;
    Entity* other;

    if (self->step) {
        if ((self->hitPoints < g_api.enemyDefs[ENEMY_TIN_MAN].hitPoints / 4) &&
            (self->step < 5)) {
            SetStep(5);
        }
    }
    if (self->hitFlags & 3) {
        PlaySfxPositional(SFX_UNK_RLIB_73D);
    }
    if ((self->flags & FLAG_DEAD) && (self->step != 7)) {
        SetStep(7);
    }
    switch (self->step) {
    case 0x0:
        InitializeEntity(g_EInitTinman);
        self->hitboxOffY = 9;
        other = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_20, other);
        other->zPriority = self->zPriority + 1;
        /* fallthrough */
    case 0x1:
        if (UnkCollisionFunc3(&sensors1) & 1) {
            SetStep(2);
        }
        break;
    case 0x2:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 0x3:
        AnimateEntity(&D_pspeu_0924C2F0, self);
        self->ext.tinman.unk84 = 0;
        var_s2 = 0;
        if (self->facingLeft) {
            self->velocityX += FIX(0.03125);
            if (self->velocityX > FIX(1.5)) {
                self->velocityX = FIX(1.5);
                var_s2 = 1;
            }
        } else {
            self->velocityX -= FIX(0.03125);
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
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_22, self, other);
                other->ext.tinman.parent = self;
                other->facingLeft = self->facingLeft;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
        if (UnkCollisionFunc2(sensors2) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        if (GetDistanceToPlayerX() < 0x50) {
            self->ext.tinman.unk82 -= 0x100;
            self->ext.tinman.unk82 &= 0xFFF;
        } else {
            ApproachTarget(&self->ext.tinman.unk82, 0, 0x80);
        }
        var_s2 = GetSideToPlayer() & 1;
        if ((var_s2 == self->facingLeft) && (GetDistanceToPlayerX() > 0x30)) {
            SetStep(4);
        }
        break;
    case 0x4:
        self->velocityX -= self->velocityX / 32;
        if (UnkCollisionFunc2(sensors2) & 0x60) {
            self->posX.val -= self->velocityX;
            self->velocityX = -self->velocityX;
        }
        switch (self->step_s) {
        case 0:
            self->ext.tinman.unk84 = 0;
            if (ApproachTarget(&self->ext.tinman.unk82, 0, 0x80) != 0) {
                self->step_s++;
            }
            break;
        case 1:
            self->ext.tinman.unk84 = 1;
            if (AnimateEntity(&D_pspeu_0924C380, self) == 0) {
                self->ext.tinman.unk84 = 0;
                self->animCurFrame = 1;
                self->facingLeft ^= 1;
                SetStep(3);
            }
            break;
        }
        break;
    case 0x5:
        switch (self->step_s) {
        case 0:
            if (GetSideToPlayer() & 1) {
                self->velocityX = FIX(1.0);
            } else {
                self->velocityX = FIX(-1.0);
            }
            self->velocityY = FIX(-2.0);
            self->drawFlags = ENTITY_ROTATE;
            self->step_s++;
            /* fallthrough */
        case 1:
            ApproachTarget(&self->rotate, 0x80, 0x10);
            if (UnkCollisionFunc3(&sensors1) & 1) {
                self->step_s++;
            }
            break;
        case 2:
            if (ApproachTarget(&self->rotate, 0, 0x10) != 0) {
                self->ext.tinman.unk85 = 1;
                self->drawFlags = ENTITY_DEFAULT;
                self->rotate = 0;
                self->step_s++;
            }
            break;
        case 3:
            if (AnimateEntity(&D_pspeu_0924C300, self) == 0) {
                self->hitboxWidth = 0xF;
                self->hitboxHeight = 0x11;
                self->hitboxOffX = 2;
                self->hitboxOffY = 0xF;
                self->ext.tinman.unk80 = Random() & 0xF;
                SetStep(6);
            }
            break;
        }
        break;
    case 0x6:
        AnimateEntity(&D_pspeu_0924C340, self);
        if (!(self->ext.tinman.unk80 & 7)) {
            PlaySfxPositional(SFX_EXPLODE_E);
        }
        self->ext.tinman.unk80++;
        if (!(self->ext.tinman.unk80 & 3)) {
            other = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_21, self, other);
                other->facingLeft = self->facingLeft;
                other->posY.i.hi -= (((self->ext.tinman.unk80 & 7) >> 1) + 7);
                if (self->facingLeft) {
                    other->posX.i.hi -= 2;
                } else {
                    other->posX.i.hi += 2;
                }
            }
        }
        break;
    case 0x7:
        if (UnkCollisionFunc3(&sensors1) & 1) {
        }
        ApproachTarget(&self->rotate, 0, 0x20);
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            if (self->ext.tinman.unk85) {
                self->step_s = 2;
            } else {
                self->step_s = 1;
            }
            break;
        case 1:
            if (AnimateEntity(&D_pspeu_0924C300, self) == 0) {
                self->step_s++;
            }
            break;
        case 2:
            for (var_s1 = 0; var_s1 < 11; var_s1++) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_UNK_23, self, other);
                    other->facingLeft = self->facingLeft;
                    other->params = (var_s1 + 0x3B);
                }
            }
            PlaySfxPositional(SFX_FLEA_ARMOR_EXPLODE);
            DestroyEntity(self);
        }
        break;
    case 0xFF:
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
    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_80180670);
        self->drawFlags = ENTITY_ROTATE;
        /* fallthrough */
    case 1:
        other = self - 1;
        if ((other->ext.tinman.unk84) == 1) {
            self->hitboxState = 0;
            self->animCurFrame = 0;
        } else {
            self->animCurFrame = 5;
            self->rotate = other->ext.tinman.unk82;
            self->hitboxState = 1;
            temp_v0 = self->rotate + 0x200;
            self->hitboxOffX = ((rcos(temp_v0) * 0x1C) >> 0xC);
            self->hitboxOffY = ((rsin(temp_v0) * 0x1C) >> 0xC);
            if (self->rotate >= ROT(337.5)) {
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
            }
        }
        if ((other->ext.tinman.unk85) || (other->flags & FLAG_DEAD)) {
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 2:
        other = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (other != NULL) {
            CreateEntityFromEntity(E_UNK_23, self, other);
            other->facingLeft = self->facingLeft;
            other->rotate = self->rotate;
            other->zPriority = self->zPriority;
            other->params = 5;
        }
        for (var_s1 = 0; var_s1 < 8; var_s1++) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_23, self, other);
                other->params = 0;
                other->zPriority = self->zPriority;
            }
        }
        PlaySfxPositional(SFX_WALL_DEBRIS_C);
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
        self->step++;
        break;
    case 3:
        other = self - 1;
        if ((other->entityId != 0x1F) || (other->flags & FLAG_DEAD)) {
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
        parent = self->ext.tinman.parent;
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

extern EInit D_us_80180688;

void func_us_801AF11C(Entity* self) {
    Entity* other;
    s16 temp_v0;
    s32 temp_s2;
    u16 temp_v1;
    wtf_struct* temp_s0;

    switch (self->step) {
    case 0:
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
            self->ext.tinman.unk80 = temp_s0->unk0;
            self->ext.tinman.unk86 = temp_s0->unk2;
            self->step = 3;
            return;
        }
        self->drawFlags = ENTITY_ROTATE;
        self->step = 2;
        return;
    case 1:
        AnimateEntity(&D_pspeu_0924C370, self);
        MoveEntity();
        self->velocityY += FIX(0.09375);
        return;
    case 2:
        MoveEntity();
        self->velocityY += FIX(0.09375);
        self->rotate += ROT(11.25);
        return;
    case 3:
        switch (self->step_s) {
        case 0:
            if (!--self->ext.tinman.unk80) {
                self->ext.tinman.unk80 = 0x20;
                self->step_s++;
            }
            break;
        case 1:
            MoveEntity();
            if (self->ext.tinman.unk86) {
                self->velocityY += FIX(0.125);
            }
            if (!--self->ext.tinman.unk80) {
                PlaySfxPositional(SFX_EXPLODE_B);
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
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
