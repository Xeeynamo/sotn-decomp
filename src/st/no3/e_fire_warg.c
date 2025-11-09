// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"

// Note: Two functions in this file have weird temp variables for PSX.
// Look for the "VERSION_PSP" defines in this file to see. The PSP version
// of both functions is simple and reasonable, but PSX has odd temps.
// You will be the lord of this castle if you can work out the match :)

static u8 D_801827DC[] = {14, 1, 14, 2, 14, 3, 14, 4, 14, 5, 14, 6, 0};
static u8 D_801827EC[] = {14, 57, 14, 58, 14, 59, 14, 60, 14, 61, 14, 62, 0};
static u8 D_801827FC[] = {14, 6, 14, 5, 14, 4, 14, 3, 14, 2, 14, 1, 0};
static u8 D_8018280C[] = {14, 62, 14, 61, 14, 60, 14, 59, 14, 58, 14, 57, 0};
static u8 D_8018281C[] = {26, 7, 26, 8, 2, 9, 0};
static u8 D_80182824[] = {26, 73, 26, 74, 2, 75, 0};
static u8 unused[] = {134, 14, 8,  30, 8,  31, 8,  32, 8,  33, 10, 34, 12,
                      35,  14, 36, 12, 37, 10, 38, 8,  39, 8,  30, 0};
static u8 D_80182848[] = {8, 30, 8, 31, 8, 32, 255, 0};
static u8 D_80182850[] = {8, 86, 8, 87, 8, 88, 255, 0};
static u8 D_80182858[] = {
    2, 33, 3, 34, 4, 35, 20, 36, 6, 37, 4, 38, 2, 39, 255, 0};
static u8 D_80182868[] = {
    2, 89, 3, 90, 4, 91, 20, 92, 6, 93, 4, 94, 2, 95, 255, 0};
static u8 D_80182878[] = {4, 32, 4, 31, 32, 30, 8, 14, 255, 0};
static u8 D_80182884[] = {4, 88, 4, 87, 32, 86, 8, 50, 255, 0};
static u8 D_80182890[] = {8,  14, 8,  40, 8,  41, 8,  42, 8,  43,  6,
                          44, 8,  45, 8,  46, 8,  47, 8,  48, 255, 0};
static u8 D_801828A8[] = {2, 14, 2, 15, 2, 16, 12, 17, 8, 18, 8,   19,
                          8, 26, 8, 27, 8, 28, 8,  29, 8, 14, 255, 0};
static u8 unused2[] = {4, 96, 4, 97, 4, 98, 4, 99, 4, 100, 4,   101,
                       8, 26, 8, 27, 8, 28, 8, 29, 8, 14,  255, 0};
static u8 D_801828D8[] = {1, 10, 1, 11, 0};
static u8 unused3[] = {1, 12, 1, 13, 0};
static u8 unused4[] = {4,  15, 4,  16, 16, 17, 8,  14, 8,  18,  8,
                       19, 16, 20, 8,  19, 8,  18, 12, 14, 255, 0};
static u8 D_80182900[] = {
    8, 102, 8, 103, 8, 104, 16, 105, 8, 106, 8,   107, 8, 108,
    8, 107, 8, 106, 8, 105, 8,  106, 8, 107, 56,  108, 8, 107,
    8, 106, 8, 105, 8, 104, 8,  103, 8, 102, 255, 0};
static u8 D_80182928[] = {
    4, 102, 4, 103, 4, 104, 4, 105, 4, 106, 4, 107, 16,  108,
    4, 107, 4, 106, 4, 105, 4, 104, 4, 103, 4, 102, 255, 0};
static u8 D_80182944[] = {4,  15, 4,  16, 16, 17, 8,  14, 8,  18,  8,
                          19, 64, 20, 8,  19, 8,  18, 12, 14, 255, 0};
static u8 D_8018295C[] = {4, 40, 20, 42, 255, 0};
static u8 D_80182964[] = {4, 40, 1, 14, 255, 0};
static u8 D_8018296C[] = {
    8, 63, 8, 64, 8, 65, 32, 66, 6, 67, 6, 68, 42, 69, 8, 64, 255, 0};
static u8 D_80182980[] = {24, 50, 32, 88, 4, 87, 46, 86, 4, 87, 8, 88, 255, 0};
static u8 D_80182990[] = {
    8,  63, 8,  64, 8,  65, 32, 66, 6,  67, 6,  68, 16, 69, 12, 66,  6,
    67, 6,  68, 16, 69, 12, 66, 6,  67, 6,  68, 64, 69, 8,  64, 255, 0};
static u8 D_801829B4[] = {
    24, 50, 32, 88, 4,  87, 20, 86, 4,  87, 12, 88, 4,  87,  20,
    86, 4,  87, 12, 88, 4,  87, 52, 86, 4,  87, 8,  88, 255, 0};
// End of animations
static s16 D_801829D4[] = {0, 40, 48, 0};
static s16 D_801829DC[] = {0, 40, 0, 4, 24, -4, -48, 0};
static s32 D_801829EC[] = {FIX(6.0 / 7), FIX(3.0 / 7), FIX(2.0 / 7),
                           FIX(6.0 / 7), FIX(3.0 / 7), FIX(2.0 / 7)};
static s32 D_80182A04[] = {FIX(2.0 / 7), FIX(3.0 / 7), FIX(6.0 / 7),
                           FIX(2.0 / 7), FIX(3.0 / 7), FIX(6.0 / 7)};
// These are very close to 12/7, 6/7, 4/7, 12/7, 6/7, 4/7 but not quite.
static s32 unused_morefixes[] = {
    0x1B6DA, 0xDBC6, 0x9248, 0x1B6DA, 0xDBC6, 0x9248, FIX(4)};
static s16 D_80182A38[] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70};
static u8 D_80182A48[] = {2, 0, 1, 3};

static void func_801CC5A4(Entity* entity, u8 count, u8 params, s16 xDist,
                          s16 yDist, u8 arg5, s16 xOfst) {
    s32 i;
    s16 x = entity->posX.i.hi + xDist;
    s16 y = entity->posY.i.hi + yDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_EXPLOSION_VARIANTS;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_80182A48[i];
            newEnt->scaleX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->scaleY = newEnt->scaleX;
            newEnt->drawFlags = FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

static void func_801CC6F8(Entity* self) {
    u16 distance = GetDistanceToPlayerX();
    bool buttNearScreenEdge;

    self->velocityX = 0;
    self->ext.fireWarg.unk86 = 0x100;

    if (self->params) {
        SetStep(12);
        return;
    }

    // This will test if we're facing left, with high X, or facing right with
    // low X.
    buttNearScreenEdge = false;
    if (self->facingLeft) {
        if (self->posX.i.hi > 0x70) {
            buttNearScreenEdge = true;
        }
    } else {
        if (self->posX.i.hi < 0x90) {
            buttNearScreenEdge = true;
        }
    }

    if (distance < 0x70) {
        if (!(Random() & 3) && !buttNearScreenEdge) {
            SetStep(9);
        } else {
            SetStep(6);
            PlaySfxPositional(SFX_WARG_GROWL);
            self->ext.fireWarg.unk80 = 0x20;
        }
    } else {
        if ((Random() & 3) && !buttNearScreenEdge) {
            SetStep(9);
            if (!(Random() & 3)) {
                self->ext.fireWarg.unk86 = 0;
            }
        } else {
            SetStep(6);
            PlaySfxPositional(SFX_WARG_GROWL);
            self->ext.fireWarg.unk80 = 0x20;
        }
    }
}

// Only called by the EntityFireWarg
static void func_801CC820(Entity* self) {
    u16 distance;

    if ((self->facingLeft == GetSideToPlayer()) & 1) {
        if (self->params) {
            SetStep(4);
        } else {
            SetStep(5);
        }
        return;
    }
    if (!self->ext.fireWarg.unk86) {
        func_801CC6F8(self);
        return;
    }
    distance = GetDistanceToPlayerX();
    if ((distance < 0x48) && (self->step != 4)) {
        SetStep(4);
        return;
    }
    SetStep(3);
    if (distance < 0x60) {
        self->ext.fireWarg.unk7C = 1;
    } else {
        self->ext.fireWarg.unk7C = 0;
    }
    self->ext.fireWarg.unk80 = 0;
    self->ext.fireWarg.unk82 = 0x20;
}

// duplicate of func_801CF6D8
static void func_801CC90C(Entity* self) {
    u16 xDist = GetDistanceToPlayerX();

    if (self->ext.fireWarg.unk86) {
        if (xDist < 0x60) {
            self->ext.fireWarg.unk86 -= 2;
            if (self->ext.fireWarg.unk86 < 0) {
                self->ext.fireWarg.unk86 = 0;
            }
        } else {
            self->ext.fireWarg.unk86--;
        }
    }
}

static s16 D_80182A4C[] = {
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

void EntityFireWarg(Entity* self) {
    Entity* ent_s0;
    Entity* ent_s4;
    EnemyDef* enemyDefPtr;
    s16* hitboxPtr;
    Collider collider;
    u16 var_s1;
    s32 var_s2;
    u8 frameIdx;

    var_s1 = self->step;
    if (self->flags & FLAG_DEAD) {
        if (!self->params) {
            if (var_s1 != 11) {
                self->velocityX = 0;
                self->velocityY = 0;
                SetStep(11);
            }
        } else {
            ent_s0 = (self + 1);
            self->params = 0;
            self->flags &= ~(FLAG_NOT_AN_ENEMY | FLAG_DEAD);
            ent_s0->flags &= ~(FLAG_NOT_AN_ENEMY | FLAG_DEAD);
            self->flags |= FLAG_UNK_400000 | FLAG_UNK_400;
            ent_s0->flags |= FLAG_UNK_400000;
            self->enemyId = ent_s0->enemyId = 0x94;
            ent_s0->flags = self->flags;
            enemyDefPtr = &g_api.enemyDefs[148];
            self->hitPoints = enemyDefPtr->hitPoints;
            ent_s0->attack = self->attack;
            ent_s0->attack = self->attack;
            ent_s0->unk60 = self;

            for (var_s2 = 0; var_s2 < 11; var_s2++) {
                self->unk6D[var_s2] = 0x10;
                ent_s0->unk6D[var_s2] = 0x10;
            }

            if (var_s1 != 4) {
                SetStep(4);
                SetSubStep(1);
                self->velocityY = FIX(-5.0);
                if (self->facingLeft) {
                    self->velocityX = FIX(-1.5);
                } else {
                    self->velocityX = FIX(1.5);
                }
            }
        }
    } else if (self->hitFlags & 0xF) {
        if (self->ext.fireWarg.unk86 >= 0x10) {
            self->ext.fireWarg.unk86 /= 2;
        }
        if ((var_s1 == 2 || var_s1 == 3) && !self->params) {
            SetStep(10);
        }
    }

    var_s1 = self->step;
    switch (var_s1) {
    case 0:
        // The self + 1 entity is an E_ID_30, or EntityUnkId30
        ent_s0 = self + 1;
        self->unk60 = ent_s0;
        // PSP version: 0x20
        CreateEntityFromCurrentEntity(E_ID_30, ent_s0);
        ent_s0->unk5C = self;
        if (self->params) {
            InitializeEntity(g_EInitFireWarg2);
            self->animCurFrame = 0x32;
            // The self + 2 entity is an E_ID_31, or EntityUnkId31
            ent_s4 = self + 2;
            ent_s0->unk60 = ent_s4;
            ent_s0 = ent_s4;
            // PSP version: 0x21
            CreateEntityFromCurrentEntity(E_ID_31, ent_s0);
            ent_s0->unk5C = self;
            ent_s0->unk60 = self;
        } else {
            InitializeEntity(g_EInitFireWarg1);
        }
        ent_s0->unk60 = self;
        self->facingLeft = (GetSideToPlayer() ^ 1) & 1;
        if (self->facingLeft) {
            self->posX.i.hi -= 0x20;
        } else {
            self->posX.i.hi += 0x20;
        }
        self->ext.fireWarg.unk86 = 0x80;
        break;

    case 1:
        if (UnkCollisionFunc3(&D_801829DC) & 1) {
            SetStep(2);
        }
        break;
    case 2:
        if (self->params) {
            AnimateEntity(&D_80182824, self);
        } else {
            AnimateEntity(&D_8018281C, self);
        }
        if ((GetDistanceToPlayerX() < 0x80) || (self->hitFlags)) {
            SetStep(3);
        }
        break;
    case 3:
        func_801CC90C(self);
        var_s1 = GetDistanceToPlayerX();
        if (self->ext.fireWarg.unk80) {
            --self->ext.fireWarg.unk80;
            self->poseTimer = 0;
            break;
        }

        if (!(self->ext.fireWarg.unk7C)) {
            if (self->params) {
                frameIdx = AnimateEntity(&D_801827EC, self);
            } else {
                frameIdx = AnimateEntity(&D_801827DC, self);
            }
            if (!frameIdx || frameIdx & 0x80) {
                frameIdx = (self->pose - 1);
                if (self->facingLeft) {
                    self->velocityX = D_801829EC[frameIdx];
                } else {
                    self->velocityX = -D_801829EC[frameIdx];
                }
            }
            if (var_s1 < 0x50) {
                self->ext.fireWarg.unk7C = 1;
                self->pose = 7 - self->pose;
                self->ext.fireWarg.unk80 = 0x10;
            }
        } else {
            if (self->params) {
                frameIdx = AnimateEntity(&D_8018280C, self);
            } else {
                frameIdx = AnimateEntity(&D_801827FC, self);
            }

            if (frameIdx != 1) {
                frameIdx = self->pose - 1;
                if (self->facingLeft) {
                    self->velocityX = -D_80182A04[frameIdx];
                } else {
                    self->velocityX = D_80182A04[frameIdx];
                }
            }

            if (var_s1 > 0x78) {
                self->ext.fireWarg.unk7C = 0;
                self->pose = 7 - self->pose;
                self->ext.fireWarg.unk80 = 0x10;
            }
        }

        UnkCollisionFunc2(&D_801829D4);
        if (self->ext.fireWarg.unk82) {
            --self->ext.fireWarg.unk82;
            break;
        }

        if ((self->facingLeft == GetSideToPlayer()) & 1) {
            if (self->params) {
                SetStep(4);
            } else {
                SetStep(5);
            }
        } else if (var_s1 < 0x48) {
            SetStep(4);
        } else {
            if (self->facingLeft) {
                g_api.CheckCollision(
                    self->posX.i.hi - 0x38, self->posY.i.hi, &collider, 0);
            } else {
                g_api.CheckCollision(
                    self->posX.i.hi + 0x38, self->posY.i.hi, &collider, 0);
            }

            if ((!self->ext.fireWarg.unk86) ||
                (collider.effects & EFFECT_SOLID &&
                 collider.effects & EFFECT_UNK_0002)) {
                func_801CC6F8(self);
            }
        }

        break;
    case 4:
        func_801CC90C(self);
        switch (self->step_s) {
        case 0:
            if (self->params) {
                frameIdx = AnimateEntity(&D_80182850, self);
            } else {
                frameIdx = AnimateEntity(&D_80182848, self);
            }
            if (!frameIdx) {
                SetSubStep(1);
                self->velocityY = FIX(-5.0);
                if (self->facingLeft) {
                    self->velocityX = FIX(-3.0);
                } else {
                    self->velocityX = FIX(3.0);
                }
            }
            break;
        case 1:
            if (self->params) {
                AnimateEntity(&D_80182868, self);
            } else {
                AnimateEntity(&D_80182858, self);
            }
            if (self->velocityX) {
                if (self->velocityX < 0) {
                    var_s1 = (self->posX.i.hi - 0x30);
                    if (var_s1 + g_Tilemap.scrollX.i.hi < 0x30) {
                        self->posX.val -= self->velocityX;
                        self->velocityX = 0;
                    }
                } else {
                    var_s1 = (self->posX.i.hi + 0x30);
                    if (var_s1 + g_Tilemap.scrollX.i.hi >
                        g_Tilemap.width - 0x30) {
                        self->posX.val -= self->velocityX;
                        self->velocityX = 0;
                    }
                }

                if (self->velocityX) {
                    g_api.CheckCollision(var_s1, self->posY.i.hi, &collider, 0);
                    if ((collider.effects & EFFECT_SOLID) &&
                        (collider.effects & EFFECT_UNK_0002)) {
                        self->posX.val -= self->velocityX;
                        self->velocityX = 0;
                    }
                }
            }
            var_s2 = self->velocityX;

            if (UnkCollisionFunc3(&D_801829DC) & 1) {
                self->velocityX = var_s2;

                if (!var_s2) {
                    if (self->facingLeft) {
                        func_801CC5A4(self, 4, 1, -16, 38, 1, -4);
                        func_801CC5A4(self, 4, 1, 2, 38, 1, 4);
                    } else {
                        func_801CC5A4(self, 4, 1, -2, 38, 1, -4);
                        func_801CC5A4(self, 4, 1, 16, 38, 1, 4);
                    }
                }

                SetSubStep(2);
            }
            break;
        case 2:
            var_s2 = self->velocityX;
            if (var_s2) {
                if (var_s2 < 0) {
                    var_s2 += 0x3000;
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -16, 38, ((Random() & 3) + 1), -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 10, 38, ((Random() & 3) + 1), -4);
                } else {
                    var_s2 -= 0x3000;
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -10, 38, ((Random() & 3) + 1), 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 16, 38, ((Random() & 3) + 1), 4);
                }
                self->velocityX = var_s2;
            }
            UnkCollisionFunc2(&D_801829D4);

            if (self->params) {
                frameIdx = AnimateEntity(&D_80182884, self);
            } else {
                frameIdx = AnimateEntity(&D_80182878, self);
            }

            if (!frameIdx) {
                func_801CC820(self);
            }
        }
        break;
    case 5:
        func_801CC90C(self);
        if (!AnimateEntity(&D_80182890, self)) {
            self->facingLeft ^= 1;
            self->animCurFrame = 0xE;
            func_801CC820(self);
        }
        break;
    case 6:
        switch (self->step_s) {
        case 0:
            AnimateEntity(&D_801828D8, self);
            if (!--self->ext.fireWarg.unk80) {
                SetSubStep(1);
            }
            break;
        case 1:
            ent_s0 = self + 1;
            frameIdx = AnimateEntity(&D_801828A8, self);

            if (self->velocityX) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.5);
                } else {
                    self->velocityX -= FIX(0.5);
                }
            } else {
                ent_s0->attackElement = self->attackElement;
                ent_s0->attack = self->attack;
            }

            if ((frameIdx & 0x80) && (self->pose == 7)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(8.0);
                } else {
                    self->velocityX = FIX(-8.0);
                }
                PlaySfxPositional(SFX_WARG_GROWL);
                enemyDefPtr = &g_api.enemyDefs[149];
                ent_s0->attackElement = enemyDefPtr->attackElement;
                ent_s0->attack = enemyDefPtr->attack;
            }

            UnkCollisionFunc2(&D_801829D4);

            if (!frameIdx) {
                func_801CC820(self);
            }
        }
        break;
    case 7:
        func_801CC90C(self);
        AnimateEntity(&D_801828D8, self);
        break;
    case 8:
        if (!AnimateEntity(&D_80182900, self)) {
            func_801CC820(self);
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(&D_80182928, self)) {
                SetSubStep(1);
                self->ext.fireWarg.unk80 = 0;
            }
            break;
        case 1:
            if (!AnimateEntity(&D_80182944, self)) {
                func_801CC820(self);
                break;
            }

            if (self->animCurFrame == 0x14) {
                if (self->ext.fireWarg.unk80 == 0) {
                    ent_s0 = AllocEntity(&g_Entities[160], &g_Entities[192]);
                    if (ent_s0 != NULL) {
                        CreateEntityFromCurrentEntity(
                            E_FIRE_WARG_ATTACK, ent_s0);
                        ent_s0->facingLeft = self->facingLeft;
                        ent_s0->posY.i.hi += 0x28;
                        if (self->facingLeft) {
                            ent_s0->posX.i.hi += 0x40;
                        } else {
                            ent_s0->posX.i.hi -= 0x40;
                        }
                    }
                }

                self->ext.fireWarg.unk80 += 1;
            }
        }
        break;
    case 10:
        func_801CC90C(self);
        switch (self->step_s) {
        case 0:
            SetSubStep(1);
            PlaySfxPositional(SFX_WARG_PAIN);
            if (self->facingLeft) {
                self->velocityX = FIX(-2.0);
            } else {
                self->velocityX = FIX(2.0);
            }
            break;
        case 1:
            UnkCollisionFunc2(&D_801829D4);
            if (self->velocityX != 0) {
                if (self->facingLeft) {
                    self->velocityX += FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -32, 38, ((Random() & 3) + 1), -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 2, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.125);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -2, 38, ((Random() & 3) + 1), 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 32, 38, ((Random() & 3) + 1), 4);
                }
            }
            if (!AnimateEntity(&D_8018295C, self)) {
                SetSubStep(2);
            }
            break;
        case 2:
            if (!AnimateEntity(&D_80182964, self)) {
                func_801CC820(self);
            }
            break;
        }
        break;
    case 11:
        switch (self->step_s) {
        case 0:
            if (UnkCollisionFunc3(&D_801829DC) & 1) {
                self->drawFlags = FLAG_DRAW_OPACITY;
                self->opacity = 0x80;
                self->ext.fireWarg.unk80 = 0;
                SetSubStep(1);
                self->ext.fireWarg.unk80++;
                ent_s0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent_s0 != NULL) {
                    CreateEntityFromCurrentEntity(E_FIRE_WARG_DEATH, ent_s0);
                    ent_s0->unk5A = self->unk5A;
                    if (self->hitEffect) {
                        ent_s0->palette = self->hitEffect;
                    } else {
                        ent_s0->palette = self->palette;
                    }
                }
            }
            break;
        case 1:
            AnimateEntity(&D_80182900, self);
            self->ext.fireWarg.unk80 += 1;
            self->opacity -= 2;
            if (self->opacity == 0x40) {
                PlaySfxPositional(SFX_WARG_DEATH_HOWL);
            }
            if (!self->opacity) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
                self->palette = PAL_FILL_WHITE;
                self->opacity = 0x80;
                self->step_s += 1;
            }
            break;
        case 2:
            AnimateEntity(&D_80182900, self);
            self->opacity -= 2;
            if (!self->opacity) {
                DestroyEntity(self);
                DestroyEntity(self + 1);
                return;
            }
            break;
        }
        break;
    case 12:
        ent_s0 = self + 2;
        ent_s4 = self + 3;
        switch (self->step_s) {
        case 0:
            ent_s0->poseTimer = 0;
            ent_s0->pose = 0;
            ent_s0->ext.fireWargHelper.unk7C = true;

            if (!(Random() & 7)) {
                AnimateEntity(&D_8018296C, ent_s0);
                AnimateEntity(&D_80182980, self);
                self->step_s += 1;
            } else {
                AnimateEntity(&D_80182990, ent_s0);
                AnimateEntity(&D_801829B4, self);
                self->step_s += 2;
            }
            self->animCurFrame = 0x32;
            break;
        case 1:
            var_s1 = AnimateEntity(&D_8018296C, ent_s0);
            AnimateEntity(&D_80182980, self);
            if (self->velocityX != 0) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.5);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 26, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.5);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -26, 38, ((Random() & 3) + 1), 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), 4);
                }
            } else {
                ent_s4->hitboxState = 0;
                ent_s4->attackElement = self->attackElement;
                ent_s4->attack = self->attack;
            }

            if ((var_s1 & 0x80) && (ent_s0->pose == 5)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(4.0);
                } else {
                    self->velocityX = FIX(-4.0);
                }

                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
                enemyDefPtr = &g_api.enemyDefs[152];
                ent_s4->hitboxState = enemyDefPtr->hitboxState;
                ent_s4->attackElement = enemyDefPtr->attackElement;
                ent_s4->attack = (enemyDefPtr->attack * 3) / 2;
            }

            UnkCollisionFunc2(&D_801829D4);
            if (!var_s1) {
                func_801CC820(self);
                ent_s0->ext.fireWargHelper.unk7C = false;
            }
            break;
        case 2:
            var_s1 = AnimateEntity(&D_80182990, ent_s0);
            AnimateEntity(&D_801829B4, self);
            if (self->velocityX != 0) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.5);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), -4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 26, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.5);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, -26, 38, ((Random() & 3) + 1), 4);
                    EntityExplosionVariantsSpawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), 4);
                }
            } else {
                ent_s4->hitboxState = 0;
                ent_s4->attackElement = self->attackElement;
                ent_s4->attack = self->attack;
            }
            frameIdx = ent_s0->pose;
            if ((var_s1 & 0x80) &&
                ((frameIdx == 5) || (frameIdx == 9) || (frameIdx == 0xD))) {
                if (self->facingLeft) {
                    self->velocityX = FIX(4.0);
                } else {
                    self->velocityX = FIX(-4.0);
                }
                PlaySfxPositional(SFX_WHIP_TWIRL_SWISH);
                enemyDefPtr = &g_api.enemyDefs[152];
                ent_s4->hitboxState = enemyDefPtr->hitboxState;
                ent_s4->attackElement = enemyDefPtr->attackElement;
                ent_s4->attack = enemyDefPtr->attack;
            }

            UnkCollisionFunc2(&D_801829D4);
            if (!var_s1) {
                func_801CC820(self);
                ent_s0->ext.fireWargHelper.unk7C = false;
            }
        }
        break;
    }

    var_s1 = self->animCurFrame;
    if (var_s1) {
        if (self->params) {
            if (var_s1 >= 0x56) {
                var_s1 -= 0x39;
            } else if (var_s1 >= 0x39) {
                var_s1 -= 0x39;
            } else {
                var_s1 = 0xD;
            }
        } else {
            if (var_s1 >= 0x60) {
                var_s1 -= 0x30;
            } else {
                --var_s1;
            }
        }

        hitboxPtr = &(D_80182A4C)[var_s1 * 0x8];
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

static s16 D_80182E1C[] = {
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

void EntityUnkId30(Entity* self) {
    Entity* entity;
    u16 animCurFrame;
    s16* hitboxPtr;

    entity = self - 1;
    if (!self->step) {
        if (self->params) {
            InitializeEntity(g_EInitFireWarg2);
            self->hitboxState = 0;
        } else {
            if (entity->params) {
                InitializeEntity(g_EInitFireWarg2);
            } else {
                InitializeEntity(g_EInitFireWarg1);
            }
        }
        self->animCurFrame = 0;
        self->hitPoints = 32767;
    }
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->facingLeft = entity->facingLeft;
    animCurFrame = entity->animCurFrame;

    if (animCurFrame) {
        if (self->params) {
            if (animCurFrame >= 63) {
                animCurFrame -= 56;
            } else {
                animCurFrame = 0;
            }
            hitboxPtr = &D_80182E1C[animCurFrame * 8];
        } else {
            if (entity->params) {
                // this chain of comparisons is stupid
                if (animCurFrame >= 86) {
                    animCurFrame -= 57;
                } else if (animCurFrame >= 57) {
                    animCurFrame -= 57;
                } else {
                    animCurFrame = 13;
                }
            } else {
                if (animCurFrame >= 96) {
                    animCurFrame -= 48;
                } else {
                    animCurFrame -= 1;
                }
            }
            hitboxPtr = &D_80182A4C[animCurFrame * 8];
        }
        hitboxPtr += 4;
        self->hitboxOffX = *hitboxPtr++;
        self->hitboxOffY = *hitboxPtr++;
        self->hitboxWidth = *hitboxPtr++;
        self->hitboxHeight = *hitboxPtr;
    }
}

static s16 D_80182F9C[] = {-44, 0, -20, 12, 8, -4};
static s16 D_80182FA8[] = {
    16, -16, 28, -24, -16, -20, 8, -32, -24, -48, -40, -8, 24, -56, -6, -40};
static s16 D_80182FC8[] = {
    0, 0, 0, 0, 0, 0, -8, 4, -8, 4, -8, 4, -8, 4, -12, 4};
static s16 D_80182FE8[] = {
    0,  0, 0,  0, 0,  0, -8, 4, -8, 4, -8, 4, -8, 4, -8, 4,
    -8, 4, -8, 4, -8, 4, -8, 4, -8, 4, -8, 4, -8, 4, -8, 8};

void EntityUnkId31(Entity* self) {
    Entity* otherEnt;
    s16* hitboxPtr;
    u16 animCurFrame;
    s16 i;

    if (!self->step) {
        InitializeEntity(g_EInitFireWarg1);
        self->zPriority++;
        otherEnt = self + 1;
        CreateEntityFromCurrentEntity(E_ID_30, otherEnt);
        otherEnt->params = 1;
    }
    otherEnt = self - 2;
    if (self->ext.fireWargHelper.unk7C) {
        animCurFrame = (self->pose - 1) * 2;
        if (otherEnt->step_s == 1) {
            hitboxPtr = D_80182FC8 + animCurFrame;
        } else {
            hitboxPtr = D_80182FE8 + animCurFrame;
        }

        if (self->facingLeft) {
            self->posX.i.hi = otherEnt->posX.i.hi - *hitboxPtr++;
        } else {
            self->posX.i.hi = otherEnt->posX.i.hi + *hitboxPtr++;
        }
        self->posY.i.hi = otherEnt->posY.i.hi + *hitboxPtr;
    } else {
        self->posX.i.hi = otherEnt->posX.i.hi;
        self->posY.i.hi = otherEnt->posY.i.hi;
    }
    self->facingLeft = otherEnt->facingLeft;
    animCurFrame = otherEnt->animCurFrame;
    if (self->flags & FLAG_DEAD) {
        hitboxPtr = D_80182F9C;
        PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);

        for (i = 0; i < 3; i++) {
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (otherEnt != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION_3, otherEnt);
                if (self->facingLeft) {
                    otherEnt->posX.i.hi -= *hitboxPtr++;
                } else {
                    otherEnt->posX.i.hi += *hitboxPtr++;
                }
                otherEnt->posY.i.hi += *hitboxPtr++;
                otherEnt->params = i;
                otherEnt->facingLeft = self->facingLeft;
            }
        }

        hitboxPtr = D_80182FA8;
        for (i = 0; i < 8; i++) {
            otherEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);

            if (otherEnt == NULL) {
                break;
            }

            CreateEntityFromCurrentEntity(E_EXPLOSION, otherEnt);
            otherEnt->params = ((self->zPriority + 1) << 8) + 1;
            if (self->facingLeft) {
                otherEnt->posX.i.hi -= *hitboxPtr++;
            } else {
                otherEnt->posX.i.hi += *hitboxPtr++;
            }
            otherEnt->posY.i.hi += *hitboxPtr++;
        }

        DestroyEntity(self);
        DestroyEntity(self + 1);
        return;
    }

    if (!self->ext.fireWargHelper.unk7C) {
        if (animCurFrame >= 86) {
            animCurFrame -= 10;
        } else if (animCurFrame >= 73) {
            animCurFrame -= 3;
        } else if (animCurFrame >= 57) {
            animCurFrame -= 6;
        } else {
            animCurFrame = 49;
        }

        if (animCurFrame != 78) {
            // Identifying ext here is non-trivial.
            // If we made it here, we didn't return at the end of the FLAG_DEAD
            // block above. So otherEnt is still set to self - 2.
            // E_ID_31 is created by the fire warg as self + 2.
            // So here we're pointing to the fire warg.
            if ((otherEnt->step == 3) && (otherEnt->ext.fireWarg.unk7C)) {
                self->animCurFrame = animCurFrame + 58;
            } else {
                self->animCurFrame = animCurFrame;
            }
        }
    } else {
        animCurFrame = self->animCurFrame;
    }

    if (animCurFrame >= 82) {
        animCurFrame -= 62;
    } else if (animCurFrame >= 76) {
        animCurFrame -= 59;
    } else if (animCurFrame >= 63) {
        animCurFrame -= 56;
    } else if (animCurFrame >= 51) {
        animCurFrame -= 50;
    } else {
        animCurFrame -= 49;
    }
    hitboxPtr = &D_80182E1C[animCurFrame * 8];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr;
}

static u8 D_80183028[] = {24, 55, 56, 87, 88, 127, 56, 87, 56, 87, 56, 87};
static s32 D_80183034[] = {FIX(-3), FIX(-5), FIX(-1), FIX(-7), FIX(4), FIX(-4)};
static s16 D_8018304C[] = {-32, -128, 24, 0};
static s16 D_80183054[] = {512, 22, 440, 25, 512, 22};
static s16 D_80183060[] = {
    0, 8, 6, 6, 8, 0, 6, -6, 0, -8, -6, -6, -8, 0, -6, 6};

// some sort of explosion
void EntityExplosion3(Entity* entity) {
    Entity* newEntity;
    s32* var_s7;
    u8* ptr;
    s16* point;
    Primitive* prim;
    u16 params;
    u16 angle;
    u16 newX;
    u16 newY;
    s32 primIndex;
    s16 posX;
    s16 posY;
    s16 offset_var;

    params = entity->params;
    if (!entity->step) {
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(g_EInitFireWarg3);
            entity->flags |= FLAG_UNK_2000;
            entity->hitboxState = 0;
            prim = &g_PrimBuf[primIndex];
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = primIndex;
            offset_var = entity->unk5A + 3;
            prim->tpage = offset_var >> 2;
            prim->clut = entity->palette + 1;

            ptr = &D_80183028[params * 4];
            prim->u0 = prim->u2 = *ptr++ + ((offset_var & 1) << 7);
            prim->u1 = prim->u3 = *ptr++ + ((offset_var & 1) << 7);
            prim->v0 = prim->v1 = *ptr++ + ((offset_var & 2) << 6);
            prim->v2 = prim->v3 = *ptr + ((offset_var & 2) << 6);
            prim->r0 = prim->r1 = prim->r2 = prim->r3 = 0x80;
            prim->g0 = prim->g1 = prim->g2 = prim->g3 = 0x80;
            prim->b0 = prim->b2 = prim->b1 = prim->b3 = 0x80;

            prim->priority = entity->zPriority + 1;
            prim->drawMode = DRAW_UNK02;
        } else {
            DestroyEntity(entity);
            return;
        }

        entity->ext.entityExplosion3.timer = 0;
        var_s7 = &D_80183034[params * 2];
        if (entity->facingLeft) {
            entity->velocityX = -*var_s7++;
        } else {
            entity->velocityX = *var_s7++;
        }
        entity->velocityY = *var_s7;
    }

    posX = entity->posX.i.hi;
    posY = entity->posY.i.hi;
    prim = &g_PrimBuf[entity->primIndex];
    entity->ext.entityExplosion3.unk7E += D_8018304C[params];
    point = &D_80183054[params * 2];
    newX = *point++;
    newY = *point;
    angle = entity->ext.entityExplosion3.unk7E + newX;
    offset_var = rcos(angle) * newY / 0x1000;

    if (entity->facingLeft) {
        prim->x3 = posX - offset_var;
        prim->x0 = posX + offset_var;
    } else {
        prim->x0 = posX - offset_var;
        prim->x3 = posX + offset_var;
    }
    offset_var = rsin(angle) * newY / 0x1000;
    prim->y0 = posY - offset_var;
    prim->y3 = posY + offset_var;

    angle = entity->ext.entityExplosion3.unk7E - newX;
    offset_var = rcos(angle) * newY / 0x1000;

    if (entity->facingLeft) {
        prim->x1 = posX - offset_var;
        prim->x2 = posX + offset_var;
    } else {
        prim->x1 = posX + offset_var;
        prim->x2 = posX - offset_var;
    }

    offset_var = rsin(angle) * newY / 0x1000;
    prim->y1 = posY + offset_var;
    prim->y2 = posY - offset_var;
    FallEntity();
    MoveEntity();
    if (entity->ext.entityExplosion3.timer & 1) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            point = &D_80183060[(Random() & 7) * 2];
            newEntity->posX.i.hi += *point++;
            newEntity->posY.i.hi += *point;
            newEntity->params = 1;
        }
    }
    entity->ext.entityExplosion3.timer++;
    if (entity->ext.entityExplosion3.timer >= 32) {
        CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
        entity->params = 1;
    }
}

void func_801CE740(Entity* self) {
    Primitive* prim;

    for (prim = &g_PrimBuf[self->primIndex]; prim != NULL; prim = prim->next) {
        if (prim->p1) {
            prim->p1--;
            continue;
        }
        if (prim->p2 < 8) {
            prim->y0 = prim->y1 -= 12;
            if (self->facingLeft) {
                prim->x1 = prim->x3 += 8;
                prim->r0 = prim->r2 -= 8;
                prim->g0 = prim->g2 -= 8;
                prim->b0 = prim->b2 -= 8;
            } else {
                prim->x0 = prim->x2 -= 8;
                prim->r1 = prim->r3 -= 8;
                prim->g1 = prim->g3 -= 8;
                prim->b1 = prim->b3 -= 8;
            }
        } else if (prim->p2 < 24) {
            prim->y0 = prim->y1 -= 12;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 4;
                prim->x1 = prim->x3 += 1;
            } else {
                prim->x1 = prim->x3 -= 4;
                prim->x0 = prim->x2 -= 1;
            }
        } else if (prim->p2 < 32) {
            prim->y0 = prim->y1 += 36;
            if (self->facingLeft) {
                prim->x0 = prim->x2 += 2;
                if (prim->p2 & 1) {
                    prim->x1 = prim->x3 += 1;
                }
            } else {
                prim->x1 = prim->x3 -= 2;
                if (prim->p2 & 1) {
                    prim->x0 = prim->x2 -= 1;
                }
            }
        } else {
            prim->drawMode = DRAW_HIDE;
        }
        prim->p2 += 1;
    }
}

// flame-like attack on ground from Fire Warg
void EntityFireWargWaveAttack(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    u32 primIdx;
    s32 unk5A;
    u16 unk5APlus3;
    u16 palette;
    u8 p0Offset;

    switch (self->step) {
    case 0:
        newEntity = AllocEntity(self, &g_Entities[192]);

        if (newEntity == NULL) {
            DestroyEntity(self);
            break;
        }

        PlaySfxPositional(SFX_FIREBALL_SHOT_A);
        CreateEntityFromCurrentEntity(E_ID_2F, newEntity);
        newEntity->facingLeft = self->facingLeft;
        InitializeEntity(g_EInitFireWarg3);

        self->ext.timer.t = 8;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0;

        primIdx = g_api.AllocPrimitives(PRIM_GT4, 6);

        if (primIdx != -1) {
            prim = &g_PrimBuf[primIdx];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            unk5APlus3 = self->unk5A + 3;
            palette = self->palette + 4;

            for (p0Offset = 0; prim != NULL; p0Offset += 4, prim = prim->next) {
#if !defined(VERSION_PSP)
                // These are both !FAKE; psp matches without them. ps1 needs
                // them. I dunno. permuter found them.
                s32 twobits;
                s32 leftside;
                prim->tpage = unk5APlus3 >> 2;
                prim->clut = palette;
                leftside = ((unk5APlus3 & 1) << 7) + 0x21;
                prim->u1 = prim->u0 = leftside;
                prim->u3 = prim->u2 = prim->u0 + 0x2D;
                twobits = unk5APlus3 & 2;
                prim->v1 = prim->v3 = ((twobits) << 6) + 0x59;
#else
                prim->tpage = unk5APlus3 >> 2;
                prim->clut = palette;
                prim->u1 = prim->u0 = ((unk5APlus3 & 1) << 7) + 0x21;
                prim->u3 = prim->u2 = prim->u0 + 0x2D;
                prim->v1 = prim->v3 = ((unk5APlus3 & 2) << 6) + 0x59;
#endif

                prim->v0 = prim->v2 = prim->v1 + 0x26;

                prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
                prim->x1 = prim->x3 = prim->x0 + 0x20;

                prim->y0 = prim->y1 = prim->y2 = prim->y3 = self->posY.i.hi;

                prim->r0 = prim->r2 = 0x40;
                prim->g0 = prim->g2 = 0x40;
                prim->b0 = prim->b2 = 0x40;
                prim->r1 = prim->r3 = 0x40;
                prim->g1 = prim->g3 = 0x40;
                prim->b1 = prim->b3 = 0x40;

                prim->priority = self->zPriority;
                prim->drawMode = DRAW_TPAGE | DRAW_TPAGE2 | FLAG_DRAW_SCALEX |
                                 FLAG_DRAW_SCALEY | FLAG_DRAW_ROTATE;

                prim->p1 = p0Offset;
                prim->p2 = 0;
            }
        } else {
            DestroyEntity(self);
        }
        break;
    case 1:
        func_801CE740(self);

        self->posY.i.hi -= 1;
        self->hitboxHeight += 1;

        if (self->facingLeft) {
            self->posX.i.hi += 4;
        } else {
            self->posX.i.hi -= 4;
        }

        self->hitboxWidth += 4;

        if (!--self->ext.timer.t) {
            self->ext.timer.t = 0x14;
            self->step += 1;
        }
        break;
    case 2:
        func_801CE740(self);

        if (self->hitboxHeight < 0xC0) {
            self->posY.i.hi -= 1;
            self->hitboxHeight += 1;
        }

        if (self->facingLeft) {
            self->posX.i.hi += 2;
        } else {
            self->posX.i.hi -= 2;
        }

        self->hitboxWidth -= 1;

        if (!--self->ext.timer.t) {
            self->ext.timer.t = 0x10;
            self->step += 1;
        }
        break;
    case 3:
        func_801CE740(self);

        self->posY.i.hi += 1;
        self->hitboxHeight -= 1;

        if (self->facingLeft) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }

        self->hitboxWidth -= 1;

        if (!--self->ext.timer.t) {
            self->ext.timer.t = 0x20;
            self->hitboxState = 0;
            self->step += 1;
        }
        break;
    case 4:
        func_801CE740(self);
        if (!--self->ext.timer.t) {
            DestroyEntity(self);
        }
        break;
    }
}

// func_psp_0924D030
void EntityUnkId2F(Entity* self) {

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFireWarg3);
        self->attack /= 2;
        self->ext.timer.t = 8;
        self->hitboxWidth = 4;
        self->hitboxHeight = 0;

        break;
    case 1:
        self->posY.i.hi -= 4;
        self->hitboxHeight += 2;
        if (self->facingLeft) {
            self->posX.i.hi += 6;
        } else {
            self->posX.i.hi -= 6;
        }
        self->hitboxWidth += 2;
        if (!--self->ext.timer.t) {
            self->ext.timer.t = 20;
            self->step++;
        }
        break;
    case 2:
        if (self->hitboxHeight < 192) {
            self->posY.i.hi -= 4;
            self->hitboxHeight += 2;
        }
        if (self->facingLeft) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }

        if (!--self->ext.timer.t) {
            self->ext.timer.t = 16;
            self->step++;
        }
        break;
    case 3:
        self->posY.i.hi += 4;
        self->hitboxHeight -= 2;
        if (self->facingLeft) {
            self->posX.i.hi += 1;
        } else {
            self->posX.i.hi -= 1;
        }
        self->hitboxWidth -= 1;
        if (!--self->ext.timer.t) {
            self->ext.timer.t = 32;
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 4:
        if (!--self->ext.timer.t) {
            DestroyEntity(self);
        }
        break;
    }
}

static s16 D_80183080[] = {
    16, -32, 0, 24, -12, 8, -20, 32, -2, 12, -29, 18, 0, -20, 2, -14};
static s16 D_801830A0[] = {2, -2, -2, 4, -2, 2, 0, -2, 2, 0, -2, 2, -2, 0};

// beams that go up when strong warg dies
void EntityFireWargDeathBeams(Entity* self) {
    Primitive* prim;
    u16 hiddenPrimCount;
    u16 palette;
    s32 primIndex;

#if !defined(VERSION_PSP)
    s32 temp_s1;
    u16 temp_s1_u16;
#else
    u16 temp_s1;
#endif

    switch (self->step) {
    case 0:
        temp_s1 = self->unk5A + 3;
        palette = self->palette + 4;
#if !defined(VERSION_PSP)
        temp_s1_u16 = (u16)temp_s1;
#endif

        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);

        if (primIndex != -1) {
            prim = &g_PrimBuf[primIndex];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIndex;

            while (prim != NULL) {
#if !defined(VERSION_PSP)
                prim->tpage = temp_s1_u16 >> 2;
#else
                prim->tpage = temp_s1 >> 2;
#endif
                prim->clut = palette;
                prim->u1 = prim->u0 = ((temp_s1 & 1) << 7) + 0x21;
                prim->u3 = prim->u2 = prim->u0 + 0x2D;
                prim->v1 = prim->v3 = ((temp_s1 & 2) << 6) + 0x59;
                prim->v0 = prim->v2 = prim->v1 + 0x26;
                prim->drawMode = DRAW_HIDE;
                prim = prim->next;
            }
        } else {
            DestroyEntity(self);
            return;
        }
        break;
    case 1:
        if ((!self->ext.fireWargDeathBeams.unk7C) &&
            (self->ext.fireWargDeathBeams.unk7E < 0x14)) {
            for (prim = &g_PrimBuf[self->primIndex]; prim != NULL;
                 prim = prim->next) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (self->ext.fireWargDeathBeams.unk7E & 1) {
                        PlaySfxPositional(SFX_EXPLODE_B);
                    }

                    if (self->facingLeft) {
                        prim->x0 = prim->x2 =
                            self->posX.i.hi -
                            D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                       0xF] +
                            0x10;
                        prim->x1 = prim->x3 = prim->x0 - 0x20;
                    } else {
                        prim->x0 = prim->x2 =
                            self->posX.i.hi +
                            D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                       0xF] -
                            0x10;
                        prim->x1 = prim->x3 = prim->x0 + 0x20;
                    }

                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + 0x28;
                    prim->r0 = prim->r2 = 0x40;
                    prim->g0 = prim->g2 = 0x40;
                    prim->b0 = prim->b2 = 0x40;
                    prim->r1 = prim->r3 = 0x40;
                    prim->g1 = prim->g3 = 0x40;
                    prim->b1 = prim->b3 = 0x40;

                    prim->priority =
                        self->zPriority +
                        D_801830A0[self->ext.fireWargDeathBeams.unk7E & 0xF];
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->p1 = (Random() & 3) + 0x10;
                    prim->p2 = 0;
                    break;
                }
            }

            self->ext.fireWargDeathBeams.unk7E++;
            self->ext.fireWargDeathBeams.unk7C = 4;
        } else {
            self->ext.fireWargDeathBeams.unk7C--;
        }

        for (hiddenPrimCount = 0, prim = &g_PrimBuf[self->primIndex];
             prim != NULL; prim = prim->next) {
            if (prim->drawMode != DRAW_HIDE) {
                prim->p2++;
                prim->x0 = prim->x2 += 1;
                prim->x1 = prim->x3 -= 1;

                if (prim->p2 > 8) {
                    prim->r0 = prim->r1 -= 0x10;
                    prim->g0 = prim->g1 -= 0x10;
                    prim->b0 = prim->b1 -= 0x10;

                    if (prim->r2) {
                        prim->r2 = prim->r3 -= 0x14;
                        prim->g2 = prim->g3 -= 0x14;
                        prim->b2 = prim->b3 -= 0x14;
                    }
                } else {
                    prim->r0 = prim->r2 = prim->r1 = prim->r3 += 0x10;
                    prim->g0 = prim->g2 = prim->g1 = prim->g3 += 0x10;
                    prim->b0 = prim->b2 = prim->b1 = prim->b3 += 0x10;
                }

                prim->y0 = prim->y1 -= prim->p1;

                if (prim->p2 > 0x10) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else {
                hiddenPrimCount++;
            }
        }

        if (hiddenPrimCount == 4 &&
            self->ext.fireWargDeathBeams.unk7E >= 0x14) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}
