// SPDX-License-Identifier: AGPL-3.0-or-later
#include "../rdai/rdai.h"

// EntitySpectralSword primarily uses this as a method to smoothly rotate, but
// also to retract it's outer ring after an attack by decreasing the radius.
static bool StepTowards(s16* val, s32 target, s32 step) {
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

static u8 D_us_80181914[] = {0, 1, 0, 0, 1, 0};
extern EInit g_EInitSpectralSwordRDAI;

void func_us_801C0C44(Entity* self) {
    s32 sp3C;
    s32 sp38;
    Entity* player;
    Entity* other;
    Primitive* prim;
    s32 var_s7;
    Point32* var_s6;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    s32 var_s2;
    s32 var_s1;

    if ((self->flags & FLAG_DEAD) && ((self->step) < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpectralSwordRDAI);
        self->animCurFrame = 1;
        self->blendMode = BLEND_ADD | BLEND_TRANSP;
        self->hitboxOffX = 0;
        self->hitboxOffY = 4;
        sp3C = g_api.AllocPrimitives(PRIM_TILE, 1);
        if (sp3C == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = sp3C;
        prim = &g_PrimBuf[sp3C];
        self->ext.spectralSwordRdai.prim = prim;
        prim->u0 = prim->v0 = 2;
        prim->r0 = prim->g0 = prim->b0 = 0xC0;
        prim->priority = 0xC0;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        for (other = self + 1, var_s1 = 0; var_s1 < 6; var_s1++, other++) {
            CreateEntityFromCurrentEntity(E_UNK_24, other);
            other->params = var_s1;
            other->params |= D_us_80181914[var_s1] << 8;
        }
        for (var_s1 = 0; var_s1 < 4; var_s1++, other++) {
            CreateEntityFromCurrentEntity(E_UNK_25, other);
            other->params = var_s1;
        }
        SetStep(2);
        self->ext.spectralSwordRdai.unk82 = 0x40;
        self->ext.spectralSwordRdai.unk96 = 0x40;
        self->ext.spectralSwordRdai.unk86 = 6;
        self->ext.spectralSwordRdai.unk87 = 4;
        break;
    case 2:
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
        }
        break;
    case 3:
        SetStep(6);
        self->ext.spectralSwordRdai.unk84 = GetSideToPlayer() & 1;
        break;
    case 6:
        if (!self->step_s) {
            var_s2 = Random() * 2;
            if (self->ext.spectralSwordRdai.unk84) {
                var_s2 = var_s2 + 0x100;
            } else {
                var_s2 = var_s2 + 0x500;
            }
            var_s3 = (rcos(var_s2) * 0x60) >> 0xC;
            var_s7 = (rsin(var_s2) * -0x60) >> 0xC;
            player = &PLAYER;
            prim = self->ext.spectralSwordRdai.prim;
            var_s3 = prim->x0 = player->posX.i.hi + var_s3;
            var_s7 = prim->y0 = player->posY.i.hi + var_s7;
            var_s3 -= self->posX.i.hi;
            var_s7 -= self->posY.i.hi;
            var_s2 = ratan2(var_s7, var_s3);
            self->velocityX = rcos(var_s2) * 0xC;
            self->velocityY = rsin(var_s2) * 0xC;
            self->ext.spectralSwordRdai.unk80 = 0x80;
            self->step_s++;
        }
        // NO NO NO KONAMI WHAT ARE YOU DOING, MoveEntity DOES NOT RETURN
        // ANYTHING
        other = (Entity*)MoveEntity();
        prim = self->ext.spectralSwordRdai.prim;
        var_s3 = prim->x0 - self->posX.i.hi;
        var_s7 = prim->y0 - self->posY.i.hi;
        var_s3 = abs(var_s3);
        var_s7 = abs(var_s7);
        if ((var_s3 < 8 && var_s7 < 8) ||
            !--self->ext.spectralSwordRdai.unk80) {
            self->step_s = 0;
        }
        player = &PLAYER;
        var_s3 = player->posX.i.hi - self->posX.i.hi;
        if (self->ext.spectralSwordRdai.unk84) {
            var_s3 = -var_s3;
        }
        if (var_s3 > 0x80) {
            self->velocityY = 0;
            if (self->ext.spectralSwordRdai.unk84) {
                self->velocityX = FIX(-0.75);
            } else {
                self->velocityX = FIX(0.75);
            }
        }
        if (var_s3 < 0x40) {
            self->velocityY = 0;
            if (self->ext.spectralSwordRdai.unk84) {
                self->velocityX = FIX(0.75);
            } else {
                self->velocityX = FIX(-0.75);
            }
            if (!--self->ext.spectralSwordRdai.unk82) {
                SetStep(5);
            }
        } else {
            self->ext.spectralSwordRdai.unk82 = 0x40;
        }
        if (self->ext.spectralSwordRdai.unk86) {
            if (!--self->ext.spectralSwordRdai.unk96) {
                var_s5 = Random() & 3;
                switch (var_s5) {
                case 0:
                case 1:
                    self->ext.spectralSwordRdai.unk96 = 0x100;
                    var_s5 =
                        (Random() % (self->ext.spectralSwordRdai.unk86)) + 1;
                    other = self + 1;
                    for (var_s1 = 0; var_s1 < 6; var_s1++, other++) {
                        if (!(other->flags & FLAG_DEAD)) {
                            var_s5 -= 1;
                        }
                        if (var_s5 == 0) {
                            break;
                        }
                    }
                    other->ext.spectralSwordRdai.unk94 = 1;
                    break;
                case 2:
                    self->ext.spectralSwordRdai.unk96 = 0x180;
                    player = &PLAYER;
                    var_s2 = GetAngleBetweenEntities(self, player);
                    other = self + 1;
                    for (var_s1 = 0; var_s1 < 6; var_s1++, other++) {
                        other->ext.spectralSwordRdai.unk94 = 3;
                        other->ext.spectralSwordRdai.unk90 = var_s2;
                    }
                    break;
                case 3:
                    self->ext.spectralSwordRdai.unk96 = 0x280;
                    other = self + 1;
                    var_s5 = 0x40;
                    for (var_s1 = 0; var_s1 < 6; var_s1++, other++) {
                        if (other->flags & FLAG_DEAD) {
                            continue;
                        }
                        other->ext.spectralSwordRdai.unk94 = 5;
                        other->ext.spectralSwordRdai.unk96 = var_s5;
                        var_s5 += 0x40;
                    }
                    break;
                }
            }
        }
        break;
    case 5:
        switch (self->step_s) {
        case 0:
            var_s3 = 0x80 - self->posX.i.hi;
            var_s7 = 0x40 - self->posY.i.hi;
            var_s2 = ratan2(var_s7, var_s3);
            self->velocityX = rcos(var_s2) * 0x30;
            self->velocityY = rsin(var_s2) * 0x30;
            self->ext.spectralSwordRdai.unk84 ^= 1;
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            var_s3 = self->posX.i.hi;
            if (self->ext.spectralSwordRdai.unk84) {
                if (var_s3 > 0x80) {
                    self->velocityX = FIX(3.0);
                    self->step_s++;
                }
            } else {
                if (var_s3 < 0x80) {
                    self->velocityX = FIX(-3.0);
                    self->step_s++;
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.125);
            player = &PLAYER;
            var_s3 = player->posX.i.hi - self->posX.i.hi;
            if (self->ext.spectralSwordRdai.unk84) {
                var_s3 = -var_s3;
            }
            if (var_s3 > 0x70) {
                SetStep(6);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            self->hitboxState = 0;
            for (other = self + 1, var_s1 = 0; var_s1 < 10; var_s1++, other++) {
                other->flags |= FLAG_DEAD;
            }
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = 0;
            PlaySfxPositional(SFX_STUTTER_EXPLODE_A);
            self->step_s++;
            break;
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.09375);
            self->rotate -= 4;
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 3;
                }
            }
            if (self->posY.i.hi > 0x160) {
                self->animCurFrame = 0;
                self->step_s++;
            }
            break;
        case 2:
            var_s5 = 0;
            for (other = self + 1, var_s1 = 0; var_s1 < 10; var_s1++, other++) {
                if (!other->animCurFrame) {
                    var_s5++;
                }
            }
            if (var_s5 == 0xA) {
                for (other = self, var_s1 = 0; var_s1 < 11; var_s1++, other++) {
                    DestroyEntity(other);
                }
                return;
            }
        }
        break;
    }
    if (!(self->flags & FLAG_DEAD)) {
        player = &PLAYER;
        var_s3 = player->posX.i.hi - self->posX.i.hi;
        var_s7 = player->posY.i.hi - self->posY.i.hi;
        var_s2 = ratan2(var_s7, var_s3);
        sp38 = (var_s3 * var_s3) + (var_s7 * var_s7);
        sp38 = SquareRoot0(sp38);
        other = self + 1;
        var_s4 = -0x30;
        var_s3 = self->posX.val;
        var_s7 = self->posY.val;
        for (var_s1 = 0; var_s1 < 6; var_s1++, other++) {
            var_s6 = (Point32*)&other->ext.spectralSwordRdai.unk88;
            var_s6->x = var_s3 + (var_s4 * rcos(var_s2 + 0x400) * 0x10);
            var_s6->y = var_s7 + (var_s4 * rsin(var_s2 + 0x400) * 0x10);
            var_s4 += 0x10;
            if (var_s4 == 0) {
                var_s4 += 0x10;
            }
        }
        sp38 /= 2;
        if (sp38 < 0x20) {
            sp38 = 0x20;
        }
        if (sp38 > 0x48) {
            sp38 = 0x48;
        }
        var_s3 = var_s3 + (sp38 * rcos(var_s2) * 0x10);
        var_s7 = var_s7 + (sp38 * rsin(var_s2) * 0x10);
        var_s4 = -(self->ext.spectralSwordRdai.unk87 / 2) * 24;

        for (var_s1 = 0; var_s1 < 4; var_s1++, other++) {
            if (!(other->flags & FLAG_DEAD)) {
                other->ext.spectralSwordRdai.unk90 = var_s2;
                var_s6 = (Point32*)&other->ext.spectralSwordRdai.unk88;
                var_s6->x = var_s3 + (var_s4 * rcos(var_s2 + 0x400) * 0x10);
                var_s6->y = var_s7 + (var_s4 * rsin(var_s2 + 0x400) * 0x10);
                var_s4 += 24;
            }
        }
        if (!(self->flags & 0xF)) {
            if (g_Timer & 1) {
                self->palette = 0x215;
            } else {
                self->palette = 0x216;
            }
        }
        if (!(g_Timer & 0xF)) {
            other = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (other != NULL) {
                CreateEntityFromEntity(E_UNK_23, self, other);
                other->ext.et_801CEB08.unk80 = self;
                other->zPriority = ((self->zPriority) + 1);
            }
        }
    }
}

void EntitySpectralSwordAura(Entity* self) {
    Entity* parent;

    if (!self->step) {
        InitializeEntity(g_EInitSpectralSwordAura);
        self->animCurFrame = 1;
#if defined(STAGE_IS_RDAI)
        self->palette += 14;
#else
        self->palette += 2;
#endif
        self->drawFlags |= ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->scaleX = self->scaleY = 0x100;
        self->opacity = 0x80;
    }
    parent = self->ext.et_801CEB08.unk80;
    self->posX.val = parent->posX.val;
    self->posY.val = parent->posY.val;
    self->scaleX += 6;
    self->scaleY += 6;
    self->opacity -= 4;
    if (self->opacity < 0x20) {
        DestroyEntity(self);
    }
}

extern EInit g_EInitSpear;

void func_us_801C17E8(Entity* self) {
    s16 sp3C;
    s32 sp38;
    Entity* other;
    s32 var_s8;
    Entity* player;
    Pos* var_s6;
    s32 var_s5;
    s32 var_s4;
    s32 var_s3;
    u32 var_s2;
    s16 var_s0;

    if ((self->flags & FLAG_DEAD) && (self->step < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpear);
        self->drawFlags = ENTITY_ROTATE;
        if (self->params & 0x100) {
            self->animCurFrame = 4;
        } else {
            self->animCurFrame = 5;
        }
        SetStep(2);
        break;
    case 2:
        MoveEntity();
        var_s6 = (Pos*)&self->ext.spectralSwordRdai.unk88;
        var_s4 = var_s6->x.i.hi - self->posX.i.hi;
        var_s3 = var_s6->y.i.hi - self->posY.i.hi;
        var_s8 = (var_s4 * var_s4) + (var_s3 * var_s3);
        var_s8 = SquareRoot0(var_s8);
        var_s5 = var_s8;
        if (var_s5 > 0x38) {
            var_s5 = 0x38;
        }
        var_s0 = ratan2(var_s3, var_s4);
        self->velocityX = var_s5 * rcos(var_s0);
        self->velocityY = var_s5 * rsin(var_s0);
        player = &PLAYER;
        var_s0 = GetAngleBetweenEntities(self, player);
        var_s0 -= 0x400;
        StepTowards(&self->rotate, var_s0, 0x10);
        if (self->ext.spectralSwordRdai.unk94) {
            if (!(self->ext.spectralSwordRdai.unk94 & 4) ||
                !--self->ext.spectralSwordRdai.unk96) {
                SetStep(4);
            }
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            if (!(self->ext.spectralSwordRdai.unk94 & 2)) {
                player = &PLAYER;
                var_s0 = GetAngleBetweenEntities(self, player);
                self->ext.spectralSwordRdai.unk90 = var_s0;
            }
            self->velocityX =
                rcos(self->ext.spectralSwordRdai.unk90 - 0x800) << 5;
            self->velocityY =
                rsin(self->ext.spectralSwordRdai.unk90 - 0x800) << 5;

            // This whole little block is weird. The ifdef is probably solvable.
            // There is some possibility that sp38 is a fake, but hard to be
            // sure.
            sp38 = self->params & 0xFF;
            sp38 = (sp38 * 4) / 6;
#ifdef VERSION_US
            other = self - (self->params & 0xFF) + (sp38 + 6);
#else
            other = self - (self->params & 0xFF) + sp38 + 6;
#endif
            if (self->ext.spectralSwordRdai.unk94 & 2) {
                other->ext.spectralSwordRdai.unk94 = 2;
            } else {
                other->ext.spectralSwordRdai.unk94 = 1;
            }
            self->step_s++;
            break;
        case 1:
            MoveEntity();

            var_s4 = self->velocityX -= self->velocityX / 16;
            var_s3 = self->velocityY -= self->velocityY / 16;
            if ((abs(var_s4) < 0x2000) && (abs(var_s3) < 0x2000)) {
                self->step_s++;
            }
            var_s0 = ratan2(var_s3, var_s4);
            var_s0 -= 0x400;
            StepTowards(&self->rotate, var_s0, 8);
            break;
        case 2:
            var_s0 = self->ext.spectralSwordRdai.unk90;
            if (StepTowards(&self->rotate, var_s0 - 0x400, 0x20) != 0) {
                self->velocityX = rcos(var_s0) << 7;
                self->velocityY = rsin(var_s0) << 7;
                self->ext.spectralSwordRdai.unk80 = 0x30;
                PlaySfxPositional(SFX_WEAPON_SWISH_A);
                self->step_s++;
            }
            break;
        case 3:
            MoveEntity();
            var_s2 = GetSideToPlayer();
            if (abs(self->velocityX) > abs(self->velocityY)) {
                var_s2 &= 1;
                if (self->velocityX < 0) {
                    var_s2 ^= 1;
                }
            } else {
                var_s2 &= 2;
                if (self->velocityY < 0) {
                    var_s2 ^= 2;
                }
            }
            if ((var_s2) || !--self->ext.spectralSwordRdai.unk80) {
                self->ext.spectralSwordRdai.unk94 = 0;
                SetStep(2);
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            other = self - 1 - (self->params & 0xFF);
            other->ext.spectralSwordRdai.unk86 -= 1;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->step_s++;
                self->animCurFrame = 0;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
    var_s0 = self->rotate + 0x400;
    if (self->params & 0x100) {
        sp3C = 0x18;
    } else {
        sp3C = 0x16;
    }
    self->hitboxOffX = ((sp3C * rcos(var_s0)) >> 0xC);
    self->hitboxOffY = ((sp3C * rsin(var_s0)) >> 0xC);
}

static AnimateEntityFrame D_pspeu_09254C98[] = {
    {4, 8}, {4, 7}, {16, 6}, POSE_END};
static AnimateEntityFrame D_pspeu_09254CA0[] = {
    {12, 8}, {12, 7}, {32, 6}, POSE_END};
static AnimateEntityFrame D_pspeu_09254CA8[] = {
    {32, 6}, {16, 7}, {16, 8}, POSE_END};
extern EInit g_EInitShield;

void func_us_801C1DE8(Entity* self) {
    s32 var_s7;
    s16 var_s6;
    s32 var_s5;
    s32 var_s4;
    Pos* var_s3;
    s32 var_s2;
    s32 var_s1;
    Entity* other;

    if ((self->flags & FLAG_DEAD) && ((self->step) < 8)) {
        SetStep(8);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitShield);
        self->animCurFrame = 7;
        self->zPriority += 2;
        SetStep(3);
        break;
    case 2:
        self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        var_s1 = GetDistanceToPlayerX();
        self->animCurFrame = 8;
        if (var_s1 < 0x40) {
            self->animCurFrame = 7;
        }
        if (var_s1 < 0x20) {
            self->animCurFrame = 6;
        }
        break;
    case 3:
        MoveEntity();
        if (self->animCurFrame != 8) {
            AnimateEntity(D_pspeu_09254CA8, self);
        }
        var_s3 = (Pos*)&self->ext.spectralSwordRdai.unk88;
        var_s1 = var_s3->x.i.hi - self->posX.i.hi;
        var_s4 = var_s3->y.i.hi - self->posY.i.hi;
        var_s5 = (var_s1 * var_s1) + (var_s4 * var_s4);
        var_s5 = SquareRoot0(var_s5);
        var_s2 = var_s5;
        if (var_s2 > 0x38) {
            var_s2 = 0x38;
        }
        var_s6 = ratan2(var_s4, var_s1);
        self->velocityX = var_s2 * rcos(var_s6);
        self->velocityY = var_s2 * rsin(var_s6);
        if (self->animCurFrame != 6) {
            self->facingLeft = ((GetSideToPlayer() & 1) ^ 1);
        }
        if (self->ext.spectralSwordRdai.unk94) {
            SetStep(4);
        }
        break;
    case 4:
        switch (self->step_s) {
        case 0:
            self->velocityX =
                rcos(self->ext.spectralSwordRdai.unk90 - 0x800) << 5;
            self->velocityY =
                rsin(self->ext.spectralSwordRdai.unk90 - 0x800) << 5;
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            if (self->ext.spectralSwordRdai.unk94 & 2) {
                var_s7 = AnimateEntity(D_pspeu_09254CA0, self);
            } else {
                var_s7 = AnimateEntity(D_pspeu_09254C98, self);
            }
            if (var_s7 == 0) {
                self->ext.spectralSwordRdai.unk80 = 0x20;
                self->step_s += 1;
                return;
            }
            break;
        case 2:
            if (!--self->ext.spectralSwordRdai.unk80) {
                self->ext.spectralSwordRdai.unk94 = 0;
                SetStep(3);
                return;
            }
            break;
        }
        break;
    case 8:
        switch (self->step_s) {
        case 0:
            other = self - 7 - self->params;
            other->ext.spectralSwordRdai.unk87 -= 1;
            self->hitboxState = 0;
            PlaySfxPositional(SFX_METAL_CLANG_C);
            PlaySfxPositional(SFX_QUICK_STUTTER_EXPLODE_B);
            self->step_s += 1;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(0.125);
            if (!(g_Timer & 7)) {
                other = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (other != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, other);
                    other->params = 1;
                }
            }
            if (self->posY.i.hi > 0x140) {
                self->step_s += 1;
                self->animCurFrame = 0;
                return;
            }
            break;
        case 2:
            self->animCurFrame = 0;
            break;
        }
        break;
    }
}
