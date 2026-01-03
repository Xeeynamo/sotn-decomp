// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

// Animations
static u8 D_801830BC[] = {14, 1, 14, 2, 14, 3, 14, 4, 14, 5, 14, 6, 0};
static u8 anim_unused1[] = {14, 57, 14, 58, 14, 59, 14, 60, 14, 61, 14, 62, 0};
static u8 D_801830DC[] = {14, 6, 14, 5, 14, 4, 14, 3, 14, 2, 14, 1, 0};
static u8 anim_unused2[] = {14, 62, 14, 61, 14, 60, 14, 59, 14, 58, 14, 57, 0};
static u8 D_801830FC[] = {26, 7, 26, 8, 2, 9, 0};
static u8 anim_unused3[] = {
    26, 73, 26, 74, 2, 75, 0, 0, 8, 30, 8, 31, 8, 32, 255, 0};
static u8 anim_unused4[] = {
    2, 33, 3, 34, 4, 35, 20, 36, 6, 37, 4, 38, 2, 39, 255, 0};
static u8 anim_unused5[] = {4, 32, 4, 31, 32, 30, 8, 14, 255, 0};
static u8 D_80183130[] = {8,  14, 8,  40, 8,  41, 8,  42, 8,  43,  6,
                          44, 8,  45, 8,  46, 8,  47, 8,  48, 255, 0};
static u8 D_80183148[] = {2, 14, 2, 15, 2, 16, 12, 17, 8, 18, 8,   19,
                          8, 26, 8, 27, 8, 28, 8,  29, 8, 14, 255, 0};
static u8 anim_unused6[] = {4, 96, 4, 97, 4, 98, 4, 99, 4, 100, 4,   101,
                            8, 26, 8, 27, 8, 28, 8, 29, 8, 14,  255, 0};
static u8 D_80183178[] = {1, 10, 1, 11, 0};
static u8 D_80183180[] = {1, 12, 1, 13, 0};
static u8 anim_unused7[] = {4,  15, 4,  16, 16, 17, 8,  14, 8,  18,  8,
                            19, 16, 20, 8,  19, 8,  18, 12, 14, 255, 0};
static u8 D_801831A0[] = {
    8, 102, 8, 103, 8, 104, 16, 105, 8, 106, 8,   107, 8, 108,
    8, 107, 8, 106, 8, 105, 8,  106, 8, 107, 56,  108, 8, 107,
    8, 106, 8, 105, 8, 104, 8,  103, 8, 102, 255, 0};
static u8 anim_unused8[] = {
    4, 102, 4, 103, 4, 104, 4, 105, 4, 106, 4, 107, 16,  108,
    4, 107, 4, 106, 4, 105, 4, 104, 4, 103, 4, 102, 255, 0};
static u8 anim_unused9[] = {4,  15, 4,  16, 16, 17, 8,  14, 8,  18,  8,
                            19, 64, 20, 8,  19, 8,  18, 12, 14, 255, 0};
static u8 D_801831FC[] = {4, 40, 20, 42, 255, 0};
static u8 D_80183204[] = {4, 40, 1, 14, 255, 0};
static u8 anim_unused10[] = {
    8, 63, 8, 64, 8, 65, 32, 66, 6, 67, 6, 68, 42, 69, 8, 64, 255, 0};
static u8 anim_unused11[] = {
    24, 50, 32, 88, 4, 87, 46, 86, 4, 87, 8, 88, 255, 0};
static u8 anim_unused12[] = {
    8,  63, 8,  64, 8,  65, 32, 66, 6,  67, 6,  68, 16, 69, 12, 66,  6,
    67, 6,  68, 16, 69, 12, 66, 6,  67, 6,  68, 64, 69, 8,  64, 255, 0};
static u8 anim_unused13[] = {
    24, 50, 32, 88, 4,  87, 20, 86, 4,  87, 12, 88, 4,  87,  20,
    86, 4,  87, 12, 88, 4,  87, 52, 86, 4,  87, 8,  88, 255, 0};
// For UnkCollisionFunc functions
static s16 D_80183274[] = {0, 40, 48, 0};
static u16 D_8018327C[] = {0, 40, 0, 4, 24, -4, -48, 0};
// Lookup tables
static u32 D_8018328C[] = {FIX(6.0 / 7), FIX(3.0 / 7), FIX(2.0 / 7),
                           FIX(6.0 / 7), FIX(3.0 / 7), FIX(2.0 / 7)};
static u32 D_801832A4[] = {FIX(2.0 / 7), FIX(3.0 / 7), FIX(6.0 / 7),
                           FIX(2.0 / 7), FIX(3.0 / 7), FIX(6.0 / 7)};
// These are very close to 12/7, 6/7, 4/7, 12/7, 6/7, 4/7 but not quite.
static s32 unused_morefixes[] = {
    0x1B6DA, 0xDBC6, 0x9248, 0x1B6DA, 0xDBC6, 0x9248, FIX(4)};

static s16 D_801832D8[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70};
static u8 D_801832E8[] = {2, 0, 1, 3};

// Unused.
void func_801CF438(Entity* entity, u8 count, u8 params, s32 xDist, s32 yDist,
                   u8 arg5, s16 xOfst) {
    s32 i;
    s16 y = entity->posY.i.hi + yDist;
    s16 x = entity->posX.i.hi + xDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_EXPLOSION_VARIANTS;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_801832E8[i];
            newEnt->scaleY = newEnt->scaleX = D_801832D8[D_801832E8[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

static void func_801CF58C(Entity* self) {
    self->velocityX = 0;
    self->ext.warg.attackTimer = 0x100;
    SetStep(6);
    g_api.PlaySfx(SFX_WARG_GROWL);
    self->ext.warg.timer = 0x20;
}

static void func_801CF5E0(Entity* self) {
    Tilemap* tilemap = &g_Tilemap;
    s16 temp_v0;

    // I think this could be a mistake. The == gets
    // evaluated before the & 1. In other places they use
    // GetSideToPlayer() & 1 but I think if they wanted to
    // do that here they should have put it in parentheses.
    // Makes no difference to ultimate behavior, but does mean
    // we get some weird bonus insructions (xor, sltiu) on PSP.
    if (self->facingLeft == GetSideToPlayer() & 1) {
        SetStep(5);
        return;
    }

    if (!self->ext.warg.attackTimer) {
        func_801CF58C(self);
        return;
    }

    temp_v0 = self->ext.warg.anchorX - self->posX.i.hi - tilemap->scrollX.i.hi;

    if (temp_v0 > 16) {
        SetStep(3);
        if (self->facingLeft) {
            self->ext.warg.movingBackward = false;
        } else {
            self->ext.warg.movingBackward = true;
        }
    } else if (temp_v0 < -16) {
        SetStep(3);
        if (self->facingLeft) {
            self->ext.warg.movingBackward = true;
        } else {
            self->ext.warg.movingBackward = false;
        }
    } else {
        SetStep(7);
    }

    self->ext.warg.timer = 0;
    self->ext.warg.decisionDelay = 32;
}

static void func_801CF6D8(Entity* self) {
    u16 xDist = GetDistanceToPlayerX();

    if (self->ext.warg.attackTimer) {
        if (xDist < 0x60) {
            self->ext.warg.attackTimer -= 2;
            if (self->ext.warg.attackTimer < 0) {
                self->ext.warg.attackTimer = 0;
            }
        } else {
            self->ext.warg.attackTimer--;
        }
    }
}

static s16 D_801832EC[] = {
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -6,  12, 8,
    8,  12, 28, 28, -31, -6,  12, 8,  8,  12, 28, 28, -31, -1,  10, 10,
    8,  12, 28, 28, -30, -1,  10, 10, 8,  12, 28, 28, -33, -5,  12, 9,
    8,  12, 28, 28, -33, -10, 12, 8,  8,  12, 28, 28, -32, -11, 12, 8,
    8,  12, 28, 28, -16, -15, 28, 8,  8,  12, 28, 28, -33, -5,  12, 9,
    8,  12, 28, 28, -33, -1,  12, 10, 8,  12, 28, 28, -33, 0,   12, 10,
    8,  12, 28, 28, -33, -1,  12, 10, 8,  12, 28, 28, -33, -1,  12, 10,
    8,  12, 28, 28, -33, -1,  12, 10, 8,  12, 28, 28, -33, 0,   12, 9,
    8,  12, 28, 28, -33, -1,  12, 8,  0,  16, 28, 24, -38, 11,  9,  9,
    0,  16, 28, 24, -38, 11,  9,  9,  0,  16, 28, 24, -38, 5,   10, 7,
    0,  16, 28, 24, -40, 2,   11, 7,  0,  16, 28, 24, -39, 4,   10, 7,
    0,  16, 28, 24, -39, 1,   11, 7,  0,  12, 28, 28, -39, -5,  10, 8,
    0,  12, 28, 28, -38, -8,  9,  7,  8,  12, 28, 28, -30, -14, 9,  7,
    8,  8,  28, 24, -29, -16, 9,  7,  8,  0,  28, 24, -30, -10, 10, 8,
    8,  0,  28, 24, -31, -10, 10, 8,  8,  12, 28, 28, -32, -4,  11, 8,
    8,  12, 28, 28, -31, -6,  10, 8,  8,  12, 28, 28, -31, -5,  10, 9,
    8,  12, 28, 28, -29, -4,  9,  10, 8,  12, 28, 28, -27, -3,  7,  10,
    -3, 12, 17, 28, 0,   0,   0,  0,  -8, 12, 12, 28, 0,   0,   0,  0,
    0,  12, 28, 28, 32,  -1,  4,  8,  0,  12, 28, 28, 35,  -1,  7,  8,
    -8, 12, 28, 28, 31,  -5,  11, 8,  -8, 12, 28, 28, 32,  -4,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -6,  12, 9,
    8,  12, 28, 28, -33, -5,  12, 8,  8,  12, 28, 28, -33, -5,  12, 8,
    8,  12, 28, 28, -16, -10, 28, 7,  8,  12, 28, 28, -16, -17, 26, 6,
    8,  12, 28, 28, -28, -22, 22, 8,  8,  12, 28, 28, -20, -24, 8,  13,
    8,  12, 28, 28, -19, -24, 8,  13, 8,  12, 28, 28, -18, -24, 8,  13,
    8,  12, 28, 28, -18, -25, 8,  13};

void EntityWarg(Entity* self) {
    DR_ENV* dr_env;
    Tilemap* gTilemap;
    Entity* otherEnt;
    Primitive* prim;
    s16* hitboxPtr;
    u16 switchTemp;
    u8 animResult;
    s16 xVar;
    EnemyDef* enemy;
    s32 primIndex;
    DRAWENV drawEnv;
    RECT rect = {0, 0x100, 0x80, 0x80};

    gTilemap = &g_Tilemap;
    switchTemp = self->step;
    if (self->flags & FLAG_DEAD) {
        if (switchTemp != 11) {
            if (!(self->animCurFrame < 0x2B || self->animCurFrame > 0x30)) {
                self->facingLeft ^= 1;
            }
            self->velocityX = 0;
            self->velocityY = 0;
            self->ext.warg.deathPosX = self->posX.i.hi + gTilemap->scrollX.i.hi;
            self->ext.warg.deathPosY = self->posY.i.hi + gTilemap->scrollY.i.hi;
            g_api.PlaySfx(SFX_STUTTER_EXPLODE_A);
            SetStep(11);
        }
    } else if (self->hitFlags & 0xF) {
        if (self->ext.warg.attackTimer >= 0x10) {
            self->ext.warg.attackTimer /= 2;
        }
        if (switchTemp == 2 || switchTemp == 3 || switchTemp == 7) {
            SetStep(10);
        }
    }
    switchTemp = self->step;
    switch (switchTemp) {
    case 0:
        otherEnt = self + 1;
        self->unk60 = otherEnt;
        CreateEntityFromCurrentEntity(E_ID_4B, otherEnt);
        otherEnt->unk5C = self;
        InitializeEntity(g_EInitWarg);
        otherEnt->unk60 = self;
        self->facingLeft = (GetSideToPlayer() ^ 1) & 1;
        if (self->facingLeft) {
            self->posX.i.hi -= 0x20;
        } else {
            self->posX.i.hi += 0x20;
        }
        self->ext.warg.attackTimer = 0x40;
        break;
    case 1:
        AnimateEntity(D_801830FC, self);
        if (UnkCollisionFunc3(D_8018327C) & 1) {
            SetStep(2);
            self->ext.warg.anchorX = self->posX.i.hi + gTilemap->scrollX.i.hi;
        }
        break;
    case 2:
        AnimateEntity(D_801830FC, self);
        if (GetDistanceToPlayerX() < 0x80 || self->hitFlags) {
            SetStep(7);
        }
        break;
    case 3:
        func_801CF6D8(self);
        xVar =
            self->ext.warg.anchorX - self->posX.i.hi - gTilemap->scrollX.i.hi;
        if (self->ext.warg.timer) {
            self->ext.warg.timer -= 1;
            self->poseTimer = 0;
            break;
        }
        if (!self->ext.warg.movingBackward) {
            animResult = AnimateEntity(D_801830BC, self);
            if (!animResult || (animResult & 0x80)) {
                animResult = self->pose - 1;
                if (self->facingLeft) {
                    self->velocityX = D_8018328C[animResult];
                    if (xVar < -0x10) {
                        self->ext.warg.movingBackward = true;
                        self->pose = 7 - self->pose;
                        self->ext.warg.timer = 0x10;
                    }
                } else {
                    self->velocityX = -D_8018328C[animResult];
                    if (xVar > 0x10) {
                        self->ext.warg.movingBackward = true;
                        self->pose = 7 - self->pose;
                        self->ext.warg.timer = 0x10;
                    }
                }
            }
        } else {
            animResult = AnimateEntity(D_801830DC, self);
            if (animResult != 1) {
                animResult = self->pose - 1;
                if (self->facingLeft) {
                    self->velocityX = -D_801832A4[animResult];
                    if (xVar > 0x10) {
                        self->ext.warg.movingBackward = false;
                        self->pose = 7 - self->pose;
                        self->ext.warg.timer = 0x10;
                    }
                } else {
                    self->velocityX = D_801832A4[animResult];
                    if (xVar < -0x10) {
                        self->ext.warg.movingBackward = false;
                        self->pose = 7 - self->pose;
                        self->ext.warg.timer = 0x10;
                    }
                }
            }
        }
        UnkCollisionFunc2(D_80183274);
        if (self->ext.warg.decisionDelay) {
            --self->ext.warg.decisionDelay;
            break;
        }
        if ((self->facingLeft == GetSideToPlayer()) & 1) {
            SetStep(5);
            break;
        }
        if (!self->ext.warg.attackTimer) {
            func_801CF58C(self);
            break;
        }
        if (xVar < 0x10 && xVar > -0x10) {
            self->velocityX = 0;
            SetStep(7);
            break;
        }
        break;
    case 5:
        func_801CF6D8(self);
        if (!AnimateEntity(D_80183130, self)) {
            self->facingLeft ^= 1;
            self->animCurFrame = 0xE;
            func_801CF5E0(self);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            AnimateEntity(D_80183178, self);
            if (!--self->ext.warg.timer) {
                SetSubStep(1);
            }
            break;
        case 1:
            otherEnt = self + 1;
            animResult = AnimateEntity(D_80183148, self);
            if (self->velocityX) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.375);
                } else {
                    self->velocityX -= FIX(0.375);
                }
            } else {
                otherEnt->attackElement = self->attackElement;
                otherEnt->attack = self->attack;
            }

            if (animResult & 0x80 && self->pose == 7) {
                if (self->facingLeft) {
                    self->velocityX = FIX(6.0);
                } else {
                    self->velocityX = FIX(-6.0);
                }
                g_api.PlaySfx(SFX_WARG_ATTACK);
                enemy = &g_api.enemyDefs[176];
                otherEnt->attackElement = enemy->attackElement;
                otherEnt->attack = enemy->attack;
            }
            UnkCollisionFunc2(D_80183274);
            if (!animResult) {
                func_801CF5E0(self);
            }
        }
        break;
    case 7:
        self->ext.warg.timer += 1;
        func_801CF6D8(self);
        AnimateEntity(D_80183180, self);
        if (self->ext.warg.decisionDelay) {
            self->ext.warg.decisionDelay -= 1;
            break;
        }
        // Same weird issue with GetSideToPlayer in func_801CF5E0
        if (self->facingLeft == GetSideToPlayer() & 1) {
            SetStep(5);
            break;
        }
        if (!self->ext.warg.attackTimer) {
            func_801CF58C(self);
        }
        break;
    case 8:
        if (!AnimateEntity(D_801831A0, self)) {
            func_801CF5E0(self);
        }
        break;
    case 10:
        func_801CF6D8(self);
        switch (self->step_s) {
        case 0:
            SetSubStep(1);
            g_api.PlaySfx(SFX_WARG_PAIN);
            if (self->facingLeft) {
                self->velocityX = FIX(-2.0);
            } else {
                self->velocityX = FIX(2.0);
            }
            break;
        case 1:
            UnkCollisionFunc2(D_80183274);
            if (self->velocityX) {
                if (self->facingLeft) {
                    self->velocityX += FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -0x20, 0x26, (Random() & 3) + 1, -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 2, 0x26, (Random() & 3) + 1, -4);
                } else {
                    self->velocityX -= FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -2, 0x26, (Random() & 3) + 1, 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0x20, 0x26, (Random() & 3) + 1, 4);
                }
            }
            if (!AnimateEntity(D_801831FC, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(D_80183204, self)) {
                func_801CF5E0(self);
            }
        }
        break;
    case 11:
        if (++self->ext.warg.timer & 1) {
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLODE_PUFF_TRANS, otherEnt);
// These are the same code, but compiler instruction reordering is messing it
// up. There's almost certainly a single solution, but I can't find it.
#ifdef VERSION_PSP
                otherEnt->params =
                    ((g_unkGraphicsStruct.g_zEntityCenter - 8 - (Random() & 7))
                     << 8) +
                    1;
#else
                otherEnt->params =
                    ((g_unkGraphicsStruct.g_zEntityCenter - (Random() & 7) - 8)
                     << 8) +
                    1;
#endif
                otherEnt->posX.i.hi =
                    self->ext.warg.deathPosX - gTilemap->scrollX.i.hi;
                otherEnt->posY.i.hi =
                    self->ext.warg.deathPosY - gTilemap->scrollY.i.hi;
                if (self->facingLeft) {
                    otherEnt->posX.i.hi += (((Random() & 0xF) - 8) * 8);
                } else {
                    otherEnt->posX.i.hi += (((Random() & 0xF) - 7) * 8);
                }
                otherEnt->posY.i.hi += (((Random() & 7) - 2) * 8);
            }
        }
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(D_8018327C) & 1) {
                self->drawFlags = FLAG_DRAW_OPACITY;
                self->opacity = 0x80;
                SetSubStep(1);
            }
            break;
        case 1:
            AnimateEntity(D_801831A0, self);
            self->opacity -= 2;
            if (self->opacity == 0x40) {
                g_api.PlaySfx(SFX_WARG_DEATH_HOWL);
            }
            if (self->opacity) {
                break;
            }

            self->palette = PAL_FILL_WHITE;
            self->opacity = 0x80;
            primIndex = g_api.AllocPrimitives(4, 3);
            // That's weird, it should do == -1, right?
            if (!primIndex) {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }

            self->primIndex = primIndex;
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[primIndex];
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);

            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x3F;
                prim->drawMode = DRAW_DEFAULT;

                // The bgtz here is due to loading everything from the draw
                drawEnv = g_CurrentBuffer->draw;
                drawEnv.isbg = 1;
                drawEnv.r0 = drawEnv.g0 = drawEnv.b0 = 0;
                drawEnv.clip = rect;
                drawEnv.ofs[0] = 0;
                drawEnv.ofs[1] = 0x100;
#ifdef VERSION_PSP
                drawEnv.dtd = 0;
#endif
                SetDrawEnv(dr_env, &drawEnv);
            } else {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            prim = prim->next;
            dr_env = g_api.func_800EDB08((POLY_GT4*)prim);
            if (dr_env != NULL) {
                prim->type = PRIM_ENV;
                prim->priority = 0x41;
                prim->drawMode = DRAW_UNK_800;

            } else {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            prim = prim->next;
#ifdef VERSION_PSP
            prim->tpage = 0x1110;
#endif
#ifdef VERSION_US
            prim->tpage = 0x110;
#endif
            prim->u0 = prim->u2 = 0;
            prim->u1 = prim->u3 = 0x80;
            prim->v0 = prim->v1 = 0x10;
            prim->v2 = prim->v3 = 0x70;
            prim->x0 = prim->x2 = self->posX.i.hi - 0x40;
            prim->x1 = prim->x3 = prim->x0 + 0x80;
            prim->y0 = prim->y1 = self->posY.i.hi - 0x30;
            prim->y2 = prim->y3 = prim->y0 + 0x60;
            prim->priority = self->zPriority;
            prim->drawMode =
                DRAW_UNK_40 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
            self->posX.i.hi = 0x40;
            self->posY.i.hi = 0x40;
            self->zPriority = 0x40;
            self->step_s += 1;
            break;
        case 2:
            AnimateEntity(D_801831A0, self);
            self->posX.i.hi = 0x40;
            self->posY.i.hi = 0x40;
            self->zPriority = 0x40;
            self->opacity -= 2;
            if (!self->opacity) {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            break;
        }
        break;
    // The switch statement expects a 12th case, but there's nothing there
    case 12:
        break;
    }

    switchTemp = self->animCurFrame;
    if (switchTemp) {
        if (self->params) {
            if (switchTemp >= 0x56) {
                switchTemp -= 0x39;
            } else if (switchTemp >= 0x39) {
                switchTemp -= 0x39;
            } else {
                switchTemp = 0xD;
            }
        } else {
            if (switchTemp >= 0x60) {
                switchTemp -= 0x30;
            } else {
                --switchTemp;
            }
        }

        hitboxPtr = &(D_801832EC)[switchTemp * 8];
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

static s16 D_801836BC[] = {
    6,  -24, 4, 24, -37, 2,  10, 4, 2,  -23, 4, 24, -38, 2,   10, 4,
    3,  -23, 4, 24, -38, 3,  10, 4, 3,  -22, 4, 24, -38, 4,   10, 4,
    2,  -23, 4, 24, -39, 2,  10, 4, 3,  -23, 4, 24, -39, 3,   10, 4,
    3,  -22, 4, 24, -39, 4,  10, 4, 6,  -24, 4, 24, -36, 2,   10, 4,
    3,  -26, 4, 24, -39, 0,  10, 4, 2,  -29, 4, 24, -38, 0,   10, 4,
    2,  -28, 4, 24, -25, -9, 10, 4, -3, -21, 4, 24, -47, 0,   17, 4,
    -2, -21, 4, 24, -46, 0,  18, 4, -2, -21, 4, 24, -45, 0,   19, 4,
    5,  -25, 4, 24, -36, 0,  10, 4, 5,  -25, 4, 24, -37, 0,   10, 4,
    5,  -25, 4, 24, -36, 2,  10, 4, -1, -21, 4, 24, -44, 5,   10, 4,
    -3, -24, 4, 24, -46, 2,  10, 4, -2, -20, 4, 24, -44, 5,   10, 4,
    5,  -33, 4, 24, -37, -7, 10, 4, 3,  -38, 4, 24, -40, -12, 10, 4,
    1,  -28, 4, 24, -38, 0,  10, 4, 5,  -23, 4, 24, -37, 2,   10, 4};

void EntityUnkId4B(Entity* self) {
    u16 lastAnimFrame;
    Entity* previous;
    s16* hitboxPtr;

    previous = self - 1;

    if (!self->step) {
        InitializeEntity(g_EInitWarg);
        self->animCurFrame = 0;
        self->hitPoints = 0x7FFF;
    }

    self->posX.i.hi = previous->posX.i.hi;
    self->posY.i.hi = previous->posY.i.hi;
    self->facingLeft = previous->facingLeft;
    lastAnimFrame = previous->animCurFrame;

    if (lastAnimFrame) {

        if (self->params) {

            if (lastAnimFrame >= 109) {
                lastAnimFrame -= 108;
            } else if (lastAnimFrame >= 82) {
                lastAnimFrame -= 62;
            } else if (lastAnimFrame >= 76) {
                lastAnimFrame -= 59;
            } else if (lastAnimFrame >= 63) {
                lastAnimFrame -= 56;
            } else if (lastAnimFrame >= 51) {
                lastAnimFrame -= 50;
            } else {
                lastAnimFrame -= 49;
            }
            hitboxPtr = &D_801836BC[lastAnimFrame * 8];

        } else {
            if (previous->params) {
                if (lastAnimFrame >= 86) {
                    lastAnimFrame -= 57;
                } else if (lastAnimFrame >= 57) {
                    lastAnimFrame -= 57;
                } else {
                    lastAnimFrame = 13;
                }
            } else if (lastAnimFrame >= 96) {
                lastAnimFrame -= 48;
            } else {
                lastAnimFrame -= 1;
            }
            hitboxPtr = &D_801832EC[lastAnimFrame * 8];
        }

        hitboxPtr = hitboxPtr + 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

static u8 D_8018383C[] = {3, 1, 3, 2, 3, 3,  3, 4,  3, 5,  3, 6,  3,   7,
                          3, 8, 3, 9, 3, 10, 3, 11, 3, 12, 3, 13, 255, 0};
// A single "puff" of the warg explosion animation, transparent
void EntityWargExplosionPuffTransparent(Entity* self) {

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->pose = 0;
        self->poseTimer = 0;
        self->animSet = ANIMSET_DRA(14);
        self->unk5A = 0x79;
        self->palette = 0xD0;
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->drawFlags = FLAG_DRAW_OPACITY;
        self->opacity = 0x60;
        if (self->params & 0xFF00) {
            self->zPriority = (self->params & 0xFF00) >> 8;
        }
        self->velocityY += FIX(-1);
        return;
    }
    self->posY.val += self->velocityY;
    if (AnimateEntity(D_8018383C, self) == 0) {
        DestroyEntity(self);
    }
}
