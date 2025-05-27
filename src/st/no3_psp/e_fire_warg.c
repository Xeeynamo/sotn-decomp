// SPDX-License-Identifier: AGPL-3.0-or-later

#include "../no3/no3.h"

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
            newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->rotY = newEnt->rotX;
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
            InitializeEntity(D_80180B30);
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
            InitializeEntity(D_80180B24);
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
                        // PSP version 0x1E
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
                self->drawFlags = FLAG_DRAW_UNK8;
                self->unk6C = 0x80;
                self->ext.fireWarg.unk80 = 0;
                SetSubStep(1);
                self->ext.fireWarg.unk80++;
                ent_s0 = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (ent_s0 != NULL) {
                    // PSP version 0x23
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

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId30);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId31);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityExplosion3);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", func_pspeu_0924C7A8);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargWaveAttack);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityUnkId2F);

INCLUDE_ASM("st/no3_psp/psp/no3_psp/e_fire_warg", EntityFireWargDeathBeams);
