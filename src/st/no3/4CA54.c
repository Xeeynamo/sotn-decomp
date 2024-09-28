// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

void func_801CC5A4(Entity* entity, u8 count, u8 params, s32 xDist, s32 yDist,
                   u8 arg5, s16 xOfst) {
    s32 i;
    s16 y = entity->posY.i.hi + yDist;
    s16 x = entity->posX.i.hi + xDist;

    for (i = 0; i < count; ++i) {
        Entity* newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEnt != NULL) {
            newEnt->entityId = E_ID_14;
            newEnt->pfnUpdate = EntityUnkId14;
            newEnt->params = params;
            newEnt->posX.i.hi = x + i * xOfst;
            newEnt->posY.i.hi = y;
            newEnt->ext.generic.unk94 = D_80182A48[i];
            newEnt->rotY = newEnt->rotX = D_80182A38[D_80182A48[i] + arg5];
            newEnt->drawFlags = FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
            newEnt->zPriority = entity->zPriority + 1;
        }
    }
}

void func_801CC6F8(Entity* entity) {
    u16 distance = GetDistanceToPlayerX();
    bool var_s1;

    entity->ext.et_801CC820.unk86 = 0x100;
    entity->velocityX = 0;

    if (entity->params != 0) {
        SetStep(0xC);
        return;
    }

    var_s1 = 0;

    if (entity->facingLeft != 0) {
        var_s1 = entity->posX.i.hi >= 0x71;
    } else if (entity->posX.i.hi < 0x90) {
        var_s1 = 1;
    }

    if (distance < 0x70) {
        if (!(Random() & 3) && !var_s1) {
            SetStep(9);
            return;
        }
    } else if ((Random() & 3) && !var_s1) {
        SetStep(9);
        if (!(Random() & 3)) {
            entity->ext.et_801CC820.unk86 = 0;
        }
        return;
    }

    SetStep(6);
    PlaySfxPositional(0x783);
    entity->ext.et_801CC820.unk80 = 0x20;
}

void func_801CC820(Entity* entity) {
    u16 distance;

    if (entity->facingLeft == GetSideToPlayer()) {
        if (entity->params == 0) {
            SetStep(5);
        } else {
            SetStep(4);
        }
        return;
    }
    if (entity->ext.et_801CC820.unk86 == 0) {
        func_801CC6F8(entity);
        return;
    }
    distance = GetDistanceToPlayerX();
    if ((distance < 0x48) && (entity->step != 4)) {
        SetStep(4);
        return;
    }
    SetStep(3);
    if (distance < 0x60) {
        entity->ext.et_801CC820.unk7C = 1;
    } else {
        entity->ext.et_801CC820.unk7C = 0;
    }
    entity->ext.et_801CC820.unk80 = 0;
    entity->ext.et_801CC820.unk82 = 0x20;
}

void func_801CC90C(Entity* arg0) {
    s16 temp_v0_2;
    s16 temp_v1;
    s16 temp_v0;

    temp_v0 = GetDistanceToPlayerX();
    temp_v1 = arg0->ext.generic.unk84.S16.unk2;
    if (temp_v1 != 0) {

        if ((u32)(temp_v0) < 0x60) {
            temp_v0_2 = temp_v1 - 2;
            arg0->ext.generic.unk84.S16.unk2 = temp_v0_2;
            if (temp_v0_2 < 0) {
                arg0->ext.generic.unk84.S16.unk2 = 0;
            }
        } else {
            arg0->ext.generic.unk84.S16.unk2 = (temp_v1 - 1);
        }
    }
}

void EntityStrongWarg(Entity* self) {
    Entity* ent_s0;
    Entity* ent_s4;
    EnemyDef* enemyDefPtr;
    s16* hitboxPtr;
    Collider collider;
    u16 var_s1;
    s32 var_s2;
    u8 frameIdx;

    var_s1 = self->step;
    if (self->flags & 0x100) {
        if (!self->params) {
            if (var_s1 != 0xB) {
                self->velocityX = 0;
                self->velocityY = 0;
                SetStep(0xB);
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
        if (self->ext.strongWarg.unk86 >= 0x10) {
            self->ext.strongWarg.unk86 /= 2;
        }
        if ((var_s1 == 2 || var_s1 == 3) && !self->params) {
            SetStep(0xA);
        }
    }

    var_s1 = self->step;
    switch (var_s1) {
    case 0:
        ent_s0 = self + 1;
        self->unk60 = ent_s0;
        // PSP version: 0x20
        CreateEntityFromCurrentEntity(E_ID_30, ent_s0);
        ent_s0->unk5C = self;
        if (self->params) {
            InitializeEntity(&D_80180B30);
            self->animCurFrame = 0x32;
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
        self->ext.strongWarg.unk86 = 0x80;
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
        if (self->ext.strongWarg.unk80) {
            --self->ext.strongWarg.unk80;
            self->animFrameDuration = 0;
            break;
        }

        if (!(self->ext.strongWarg.unk7C.unk & 0xFF)) {
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
                self->ext.strongWarg.unk7C.U8.unk0 = 1;
                self->animFrameIdx = 7 - self->animFrameIdx;
                self->ext.strongWarg.unk80 = 0x10;
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
                self->ext.strongWarg.unk7C.U8.unk0 = 0;
                self->animFrameIdx = 7 - self->animFrameIdx;
                self->ext.strongWarg.unk80 = 0x10;
            }
        }

        UnkCollisionFunc2(&D_801829D4);
        if (self->ext.strongWarg.unk82) {
            --self->ext.strongWarg.unk82;
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

            if ((!self->ext.strongWarg.unk86) ||
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
                    EntityUnkId14Spawner(
                        self, 1, 1, -16, 38, ((Random() & 3) + 1), -4);
                    EntityUnkId14Spawner(
                        self, 1, 1, 10, 38, ((Random() & 3) + 1), -4);
                } else {
                    var_s2 -= 0x3000;
                    EntityUnkId14Spawner(
                        self, 1, 1, -10, 38, ((Random() & 3) + 1), 4);
                    EntityUnkId14Spawner(
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
            if (!--self->ext.strongWarg.unk80) {
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
                PlaySfxPositional(0x783);
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
                self->ext.strongWarg.unk80 = 0;
            }
            break;
        case 1:
            if (!AnimateEntity(&D_80182944, self)) {
                func_801CC820(self);
                break;
            }

            if (self->animCurFrame == 0x14) {
                if (self->ext.strongWarg.unk80 == 0) {
                    ent_s0 = AllocEntity(&D_8007A958, &D_8007A958 + 0x20);
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

                self->ext.strongWarg.unk80 += 1;
            }
        }
        break;
    case 10:
        func_801CC90C(self);
        switch (self->step_s) {
        case 0:
            SetSubStep(1);
            PlaySfxPositional(0x781);
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
                    EntityUnkId14Spawner(
                        self, 1, 1, -32, 38, ((Random() & 3) + 1), -4);
                    EntityUnkId14Spawner(
                        self, 1, 1, 2, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.125);
                    EntityUnkId14Spawner(
                        self, 1, 1, -2, 38, ((Random() & 3) + 1), 4);
                    EntityUnkId14Spawner(
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
                self->ext.strongWarg.unk80 = 0;
                SetSubStep(1);
                self->ext.strongWarg.unk80++;
                ent_s0 = AllocEntity(&D_8007D858, (&D_8007D858 + 0x20));
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
            self->ext.strongWarg.unk80 += 1;
            self->unk6C -= 2;
            if (self->unk6C == 0x40) {
                PlaySfxPositional(0x780);
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
            ent_s0->ext.strongWarg.unk7C.unk = 1;

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
                    EntityUnkId14Spawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), -4);
                    EntityUnkId14Spawner(
                        self, 1, 1, 26, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.5);
                    EntityUnkId14Spawner(
                        self, 1, 1, -26, 38, ((Random() & 3) + 1), 4);
                    EntityUnkId14Spawner(
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
                ent_s0->ext.strongWarg.unk7C.unk = 0;
            }
            break;
        case 2:
            var_s1 = AnimateEntity(&D_80182990, ent_s0);
            AnimateEntity(&D_801829B4, self);
            if (self->velocityX != 0) {
                if (self->velocityX < 0) {
                    self->velocityX += FIX(0.5);
                    EntityUnkId14Spawner(
                        self, 1, 1, 0, 38, ((Random() & 3) + 1), -4);
                    EntityUnkId14Spawner(
                        self, 1, 1, 26, 38, ((Random() & 3) + 1), -4);
                } else {
                    self->velocityX -= FIX(0.5);
                    EntityUnkId14Spawner(
                        self, 1, 1, -26, 38, ((Random() & 3) + 1), 4);
                    EntityUnkId14Spawner(
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
                ent_s0->ext.strongWarg.unk7C.unk = 0;
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

const u32 padding = 0;

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
    if (self->ext.prim) {
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

    if (!self->ext.prim) {
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
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
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
        CreateEntityFromCurrentEntity(2, entity);
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

// flame-like attack on ground from strong warg
INCLUDE_ASM("st/no3/nonmatchings/4CA54", EntityStrongWargWaveAttack);
