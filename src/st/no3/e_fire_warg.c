// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

static void func_801CC5A4(Entity* entity, u8 count, u8 params, s32 xDist,
                          s32 yDist, u8 arg5, s16 xOfst) {
    s32 i;
    s16 y = entity->posY.i.hi + yDist;
    s16 x = entity->posX.i.hi + xDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_ID_14;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_80182A48[i];
            newEnt->rotY = newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
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
            InitializeEntity(&D_80180B30);
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
            InitializeEntity(&D_80180B24);
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
            self->animFrameDuration = 0;
            break;
        }

        if (!(self->ext.fireWarg.unk7C)) {
            if (self->params) {
                frameIdx = AnimateEntity(&D_801827EC, self);
            } else {
                frameIdx = AnimateEntity(&D_801827DC, self);
            }
            if (!frameIdx || frameIdx & 0x80) {
                frameIdx = (self->animFrameIdx - 1);
                if (self->facingLeft) {
                    self->velocityX = D_801829EC[frameIdx];
                } else {
                    self->velocityX = -D_801829EC[frameIdx];
                }
            }
            if (var_s1 < 0x50) {
                self->ext.fireWarg.unk7C = 1;
                self->animFrameIdx = 7 - self->animFrameIdx;
                self->ext.fireWarg.unk80 = 0x10;
            }
        } else {
            if (self->params) {
                frameIdx = AnimateEntity(&D_8018280C, self);
            } else {
                frameIdx = AnimateEntity(&D_801827FC, self);
            }

            if (frameIdx != 1) {
                frameIdx = self->animFrameIdx - 1;
                if (self->facingLeft) {
                    self->velocityX = -D_80182A04[frameIdx];
                } else {
                    self->velocityX = D_80182A04[frameIdx];
                }
            }

            if (var_s1 >= 0x79) {
                self->ext.fireWarg.unk7C = 0;
                self->animFrameIdx = 7 - self->animFrameIdx;
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

            if ((frameIdx & 0x80) && (self->animFrameIdx == 7)) {
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
                        // PSP version 0x1E
                        CreateEntityFromCurrentEntity(E_ID_2E, ent_s0);
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
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->ext.fireWarg.unk80 = 0;
                SetSubStep(1);
                self->ext.fireWarg.unk80++;
                ent_s0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent_s0 != NULL) {
                    // PSP version 0x23
                    CreateEntityFromCurrentEntity(E_ID_33, ent_s0);
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
            self->unk6C -= 2;
            if (self->unk6C == 0x40) {
                PlaySfxPositional(SFX_WARG_DEATH_HOWL);
            }
            if (!self->unk6C) {
                self->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
                self->palette = 0x15F;
                self->unk6C = 0x80;
                self->step_s += 1;
            }
            break;
        case 2:
            AnimateEntity(&D_80182900, self);
            self->unk6C -= 2;
            if (!self->unk6C) {
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
            ent_s0->animFrameDuration = 0;
            ent_s0->animFrameIdx = 0;
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

            if ((var_s1 & 0x80) && (ent_s0->animFrameIdx == 5)) {
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
            frameIdx = ent_s0->animFrameIdx;
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

void EntityUnkId30(Entity* self) {
    Entity* entity;
    u16 animCurFrame;
    u16* hitboxPtr;

    entity = self - 1;
    if (self->step == 0) {
        if (self->params != 0) {
            InitializeEntity(D_80180B30);
            self->hitboxState = 0;
        } else {
            if (entity->params != 0) {
                InitializeEntity(D_80180B30);
            } else {
                InitializeEntity(D_80180B24);
            }
        }
        self->animCurFrame = 0;
        self->hitPoints = 32767;
    }
    self->posX.i.hi = entity->posX.i.hi;
    self->posY.i.hi = entity->posY.i.hi;
    self->facingLeft = entity->facingLeft;
    animCurFrame = entity->animCurFrame;

    if (animCurFrame != 0) {
        if (self->params != 0) {
            if (animCurFrame < 63) {
                animCurFrame = 0;
            } else {
                animCurFrame -= 56;
            }
            hitboxPtr = &D_80182E1C[animCurFrame * 8];
        } else {
            if (entity->params != 0) {
                if (animCurFrame >= 86 || animCurFrame >= 57) {
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
        self->hitboxHeight = *hitboxPtr++;
    }
}

void EntityUnkId31(Entity* self) {
    Entity* entity;
    u16* hitboxPtr;
    u16 animFrameIdx;
    u16 animCurFrame;
    s16 i;

    entity = self - 2;
    if (self->step == 0) {
        InitializeEntity(D_80180B24);
        self->zPriority++;
        CreateEntityFromCurrentEntity(E_ID_30, self + 1);
        (self + 1)->params = 1;
    }
    if (self->ext.fireWargHelper.unk7C) {
        animFrameIdx = (self->animFrameIdx - 1) * 2;
        if (entity->step_s == 1) {
            hitboxPtr = D_80182FC8 + animFrameIdx;
        } else {
            hitboxPtr = D_80182FE8 + animFrameIdx;
        }

        if (self->facingLeft) {
            self->posX.i.hi = entity->posX.i.hi - *hitboxPtr++;
        } else {
            self->posX.i.hi = entity->posX.i.hi + *hitboxPtr++;
        }
        self->posY.i.hi = entity->posY.i.hi + *hitboxPtr++;
    } else {
        self->posX.i.hi = entity->posX.i.hi;
        self->posY.i.hi = entity->posY.i.hi;
    }
    self->facingLeft = entity->facingLeft;
    animCurFrame = entity->animCurFrame;
    if (self->flags & FLAG_DEAD) {
        hitboxPtr = D_80182F9C;
        PlaySfxPositional(SFX_FM_THUNDER_EXPLODE);

        for (i = 0; i < 3; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity) {
                CreateEntityFromCurrentEntity(E_ID_32, entity);
                if (self->facingLeft != 0) {
                    entity->posX.i.hi -= *hitboxPtr++;
                } else {
                    entity->posX.i.hi += *hitboxPtr++;
                }
                entity->posY.i.hi += *hitboxPtr++;
                entity->params = i;
                entity->facingLeft = self->facingLeft;
            }
        }

        hitboxPtr = D_80182FA8;
        for (i = 0; i < 8; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);

            if (!entity) {
                break;
            }

            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = ((self->zPriority + 1) << 8) + 1;
            if (self->facingLeft != 0) {
                entity->posX.i.hi -= *hitboxPtr++;
            } else {
                entity->posX.i.hi += *hitboxPtr++;
            }
            entity->posY.i.hi += *hitboxPtr++;
        }

        DestroyEntity(self);
        DestroyEntity(self + 1);
        return;
    }

    if (!self->ext.fireWargHelper.unk7C) {
        if (animCurFrame >= 86) {
            animCurFrame -= 10;
        } else if (animCurFrame > 72) {
            animCurFrame -= 3;
        } else if (animCurFrame < 57) {
            animCurFrame = 49;
        } else {
            animCurFrame -= 6;
        }

        if (animCurFrame != 78) {
            if ((entity->step == 3) && ((u8)entity->ext.timer.t != 0)) {
                self->animCurFrame = animCurFrame + 58;
            } else {
                self->animCurFrame = animCurFrame;
            }
        }
    } else {
        animCurFrame = self->animCurFrame;
    }

    if (animCurFrame > 81) {
        animCurFrame -= 62;
    } else if (animCurFrame > 75) {
        animCurFrame -= 59;
    } else if (animCurFrame > 62) {
        animCurFrame -= 56;
    } else if (animCurFrame > 50) {
        animCurFrame -= 50;
    } else {
        animCurFrame -= 49;
    }
    hitboxPtr = &D_80182E1C[animCurFrame * 8];
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
}

// some sort of explosion
void EntityExplosion3(Entity* entity) {
    Entity* newEntity;
    u32* ptr32;
    u8* ptr;
    Point16* point;
    Primitive* prim;
    u16 params;
    s32 xOffset;
    s32 yOffset;
    s16 primIndex;
    u16 angle;
    s16 posX;
    s16 posY;
    u16 newX;
    u16 newY;

    params = entity->params;
    if (!entity->step) {
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 1);
        if (primIndex != -1) {
            InitializeEntity(D_80180B3C);
            entity->flags |= FLAG_UNK_2000;
            entity->hitboxState = 0;
            prim = &g_PrimBuf[primIndex];
            entity->flags |= FLAG_HAS_PRIMS;
            entity->primIndex = primIndex;
            primIndex = entity->unk5A + 3;
            prim->tpage = primIndex >> 2;
            prim->clut = entity->palette + 1;

            ptr = &D_80183028[params * 4];
            prim->u0 = prim->u2 = *ptr++ + ((primIndex & 1) << 7);
            prim->u1 = prim->u3 = *ptr++ + ((primIndex & 1) << 7);
            prim->v0 = prim->v1 = *ptr++ + ((primIndex & 2) << 6);
            prim->v2 = prim->v3 = *ptr + ((primIndex & 2) << 6);
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
        ptr32 = &D_80183034[params * 2];
        if (entity->facingLeft) {
            entity->velocityX = -*ptr32++;
        } else {
            entity->velocityX = *ptr32++;
        }
        entity->velocityY = *ptr32;
    }

    posX = entity->posX.i.hi;
    posY = entity->posY.i.hi;
    point = &D_80183054[params];
    prim = &g_PrimBuf[entity->primIndex];
    entity->ext.entityExplosion3.unk7E += D_8018304C[params];
    newX = point->x;
    newY = point->y;
    angle = newX + entity->ext.entityExplosion3.unk7E;
    xOffset = rcos(angle) * newY;
    if (xOffset < 0) {
        xOffset += 0xFFF;
    }
    xOffset = xOffset >> 12;
    if (entity->facingLeft != 0) {
        prim->x3 = posX - xOffset;
        prim->x0 = posX + xOffset;
    } else {
        prim->x0 = posX - xOffset;
        prim->x3 = posX + xOffset;
    }
    yOffset = rsin(angle) * newY;
    if (yOffset < 0) {
        yOffset += 0xFFF;
    }
    prim->y0 = posY - (yOffset >> 12);
    prim->y3 = posY + (yOffset >> 12);

    angle = entity->ext.entityExplosion3.unk7E - newX;
    xOffset = rcos(angle) * newY;
    if (xOffset < 0) {
        xOffset += 0xFFF;
    }
    xOffset = xOffset >> 12;
    if (entity->facingLeft != 0) {
        prim->x1 = posX - xOffset;
        prim->x2 = posX + xOffset;
    } else {
        prim->x1 = posX + xOffset;
        prim->x2 = posX - xOffset;
    }

    yOffset = rsin(angle) * newY;
    if (yOffset < 0) {
        yOffset += 0xFFF;
    }
    prim->y1 = posY + (yOffset >> 12);
    prim->y2 = posY - (yOffset >> 12);
    FallEntity();
    MoveEntity();
    if (entity->ext.entityExplosion3.timer & 1) {
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
            point = &D_80183060[(Random() & 7)];
            newEntity->posX.i.hi += point->x;
            newEntity->posY.i.hi += point->y;
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
    Primitive* prim = &g_PrimBuf[self->primIndex];

    if (prim == NULL) {
        return;
    }

    while (prim != NULL) {
        if (prim->p1 != 0) {
            prim->p1--;
        } else {
            if (prim->p2 < 8) {
                prim->y0 = prim->y1 = prim->y1 - 12;
                if (self->facingLeft) {
                    prim->x1 = prim->x3 = prim->x3 + 8;
                    prim->r0 = prim->r2 = prim->r2 - 8;
                    prim->g0 = prim->g2 = prim->g2 - 8;
                    prim->b0 = prim->b2 = prim->b2 - 8;
                } else {
                    prim->x0 = prim->x2 = prim->x2 - 8;
                    prim->r1 = prim->r3 = prim->r3 - 8;
                    prim->g1 = prim->g3 = prim->g3 - 8;
                    prim->b1 = prim->b3 = prim->b3 - 8;
                }
            } else if (prim->p2 < 24) {
                prim->y0 = prim->y1 = prim->y1 - 12;
                if (self->facingLeft) {
                    prim->x0 = prim->x2 = prim->x2 + 4;
                    prim->x1 = prim->x3 = prim->x3 + 1;
                } else {
                    prim->x1 = prim->x3 = prim->x3 - 4;
                    prim->x0 = prim->x2 = prim->x2 - 1;
                }
            } else if (prim->p2 < 32) {
                prim->y0 = prim->y1 = prim->y1 + 36;
                if (self->facingLeft != 0) {
                    prim->x0 = prim->x2 = prim->x2 + 2;
                    if (prim->p2 & 1) {
                        prim->x1 = prim->x3 = prim->x3 + 1;
                    }
                } else {
                    prim->x1 = prim->x3 = prim->x3 - 2;
                    if (prim->p2 & 1) {
                        prim->x0 = prim->x2 = prim->x2 - 1;
                    }
                }
            } else {
                prim->drawMode = DRAW_HIDE;
            }
            prim->p2 += 1;
        }
        prim = prim->next;
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

    // These are both !FAKE; psp matches without them. ps1 needs them. I dunno.
    // permuter found them.
    s32 twobits;
    s32 leftside;

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
        InitializeEntity(D_80180B3C);

        self->ext.timer.t = 8;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0;

        primIdx = g_api.AllocPrimBuffers(PRIM_GT4, 6);

        if (primIdx != -1) {
            prim = &g_PrimBuf[primIdx];
            self->flags |= FLAG_HAS_PRIMS;
            self->primIndex = primIdx;
            unk5APlus3 = self->unk5A + 3;
            palette = self->palette + 4;

            for (p0Offset = 0; prim != NULL; p0Offset += 4, prim = prim->next) {
                prim->tpage = unk5APlus3 >> 2;
                prim->clut = palette;
                leftside = ((unk5APlus3 & 1) << 7) + 0x21;
                prim->u1 = prim->u0 = leftside;
                prim->u3 = prim->u2 = prim->u0 + 0x2D;
                twobits = unk5APlus3 & 2;
                prim->v1 = prim->v3 = ((twobits) << 6) + 0x59;
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
                prim->drawMode = DRAW_TPAGE | DRAW_TPAGE2 | FLAG_DRAW_ROTX |
                                 FLAG_DRAW_ROTY | FLAG_DRAW_ROTZ;

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
        InitializeEntity(D_80180B3C);
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

// beams that go up when strong warg dies
void EntityFireWargDeathBeams(Entity* self) {
    Primitive* prim;
    s16 baseX;
    u16 hiddenPrimCount;
    u16 palette;
    s32 primIndex;
    s32 temp_s1;
    u16 temp_s1_u16;

    switch (self->step) {
    case 0:
        palette = self->palette + 4;
        temp_s1 = self->unk5A + 3;
        temp_s1_u16 = (u16)temp_s1;

        InitializeEntity(g_EInitCommon);
        primIndex = g_api.AllocPrimBuffers(PRIM_GT4, 4);

        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->primIndex = primIndex;
        self->flags |= FLAG_HAS_PRIMS;
        prim = &g_PrimBuf[primIndex];

        while (prim != NULL) {
            prim->tpage = temp_s1_u16 / 4;
            prim->clut = palette;
            prim->u0 = prim->u1 = ((temp_s1 & 1) << 7) + 0x21;
            prim->v1 = prim->v3 = ((temp_s1 & 2) << 6) + 0x59;
            prim->v0 = prim->v2 = ((temp_s1 & 2) << 6) + 0x7F;
            prim->u3 = prim->u2 = prim->u0 + 0x2D;
            prim->drawMode = DRAW_HIDE;
            prim = prim->next;
        }
        break;
    case 1:
        if ((self->ext.fireWargDeathBeams.unk7C == 0) &&
            (self->ext.fireWargDeathBeams.unk7E < 0x14)) {
            prim = &g_PrimBuf[self->primIndex];

            while (prim != NULL) {
                if (prim->drawMode == DRAW_HIDE) {
                    if (self->ext.fireWargDeathBeams.unk7E & 1) {
                        PlaySfxPositional(SFX_EXPLODE_B);
                    }

                    if (self->facingLeft != 0) {
                        baseX = self->posX.i.hi -
                                D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                           0xF];
                        prim->x0 = prim->x2 = baseX + 0x10;
                        prim->x1 = prim->x3 = baseX - 0x10;
                    } else {
                        baseX = self->posX.i.hi +
                                D_80183080[self->ext.fireWargDeathBeams.unk7E &
                                           0xF];
                        prim->x0 = prim->x2 = baseX - 0x10;
                        prim->x1 = prim->x3 = baseX + 0x10;
                    }

                    prim->y0 = prim->y1 = prim->y2 = prim->y3 =
                        self->posY.i.hi + 0x28;
                    prim->b1 = prim->b3 = prim->g1 = prim->g3 = prim->r1 =
                        prim->r3 = prim->b0 = prim->b2 = prim->g0 = prim->g2 =
                            prim->r0 = prim->r2 = 0x40;

                    prim->priority =
                        self->zPriority +
                        D_801830A0[self->ext.fireWargDeathBeams.unk7E & 0xF];
                    prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_COLORS |
                                     DRAW_UNK02 | DRAW_TRANSP;
                    prim->p1 = (Random() & 3) + 0x10;
                    prim->p2 = 0;
                    break;
                }

                prim = prim->next;
            }

            self->ext.fireWargDeathBeams.unk7C = 4;
            self->ext.fireWargDeathBeams.unk7E++;
        } else {
            self->ext.fireWargDeathBeams.unk7C--;
        }

        prim = &g_PrimBuf[self->primIndex];
        hiddenPrimCount = 0;

        while (prim != NULL) {
            if (prim->drawMode != DRAW_HIDE) {
                prim->p2++;
                prim->x0 = prim->x2 = prim->x2 + 1;
                prim->x1 = prim->x3 = prim->x3 - 1;

                if (prim->p2 > 8) {
                    prim->r0 = prim->r1 = prim->r1 - 0x10;
                    prim->g0 = prim->g1 = prim->g1 - 0x10;
                    prim->b0 = prim->b1 = prim->b1 - 0x10;

                    if (prim->r2) {
                        prim->r2 = prim->r3 = prim->r3 - 0x14;
                        prim->g2 = prim->g3 = prim->g3 - 0x14;
                        prim->b2 = prim->b3 = prim->b3 - 0x14;
                    }
                } else {
                    prim->r0 = prim->r2 = prim->r1 = prim->r3 = prim->r3 + 0x10;
                    prim->g0 = prim->g2 = prim->g1 = prim->g3 = prim->g3 + 0x10;
                    prim->b0 = prim->b2 = prim->b1 = prim->b3 = prim->b3 + 0x10;
                }

                prim->y0 = prim->y1 = prim->y1 - prim->p1;

                if (prim->p2 > 0x10) {
                    prim->drawMode = DRAW_HIDE;
                }
            } else {
                hiddenPrimCount++;
            }
            prim = prim->next;
        }

        if (hiddenPrimCount == 4 && self->ext.fireWargDeathBeams.unk7E > 0x13) {
            DestroyEntity(self);
            return;
        }
        break;
    }
}

void func_801CF438(Entity* entity, u8 count, u8 params, s32 xDist, s32 yDist,
                   u8 arg5, s16 xOfst) {
    s32 i;
    s16 y = entity->posY.i.hi + yDist;
    s16 x = entity->posX.i.hi + xDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_ID_14;
            newEnt->pfnUpdate = EntityExplosionVariants;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.destructAnim.index = D_801832E8[i];
            newEnt->rotY = newEnt->rotX = D_801832D8[D_801832E8[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}
