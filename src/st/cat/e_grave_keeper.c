// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit D_us_8018126C;
static s16 D_us_801826BC[] = {0, 23, 0, 4, 8, -4, -16, 0};
static s16 D_us_801826CC[] = {0, 23, 8, 0};
static s16 D_us_801826D4[] = {-12, 16, 0, -16};
static u8 D_us_801826DC[] = {
    0x0C, 0x01, 0x06, 0x02, 0x0C, 0x03, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00};
static u8 D_us_801826E8[] = {
    0x01, 0x01, 0x02, 0x06, 0x03, 0x07, 0x01, 0x08, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_801826F4[] = {
    0x04, 0x01, 0x04, 0x04, 0x16, 0x05, 0x08, 0x04, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182700[] = {
    0x08, 0x01, 0x02, 0x02, 0x03, 0x03, 0x02, 0x01, 0x02, 0x08, 0xFF, 0x00};
static u8 D_us_8018270C[] = {
    0x08, 0x0B, 0x08, 0x0C, 0x08, 0x0D, 0x08, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182718[] = {
    0x01, 0x01, 0x04, 0x0D, 0x04, 0x0C, 0x04, 0x0B, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182724[] = {
    0x03, 0x06, 0x03, 0x07, 0x03, 0x06, 0x04, 0x01, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182730[] = {0x02, 0x01, 0x02, 0x02, 0x03, 0x03, 0x02, 0x02,
                             0x08, 0x08, 0x18, 0x09, 0xFF, 0x00, 0x00, 0x00};
static u8 D_us_80182740[] = {0x06, 0x01, 0x08, 0x0E, 0x06, 0x0F, 0x06, 0x10,
                             0x06, 0x11, 0x06, 0x12, 0x16, 0x13, 0xFF, 0x00};

extern EInit D_us_80181278;

// { hitboxOffX, hitboxOffY, hitboxWidth, hitboxHeight}
static s16 D_us_80182750[][4] = {
    // all other anim frames
    {0, 0, 0, 0},
    // anim frame 5
    {-17, -5, 8, 4},
    // anim frame 9
    {-16, 0, 8, 4},
    // anim frame 10
    {-18, 16, 8, 4}};

void func_us_801D121C(void) {
    Entity* newEntity;

    newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEntity != NULL) {
        CreateEntityFromEntity(E_INTENSE_EXPLOSION, g_CurrentEntity, newEntity);
        newEntity->posY.i.hi += 0x18;
        if (g_CurrentEntity->facingLeft) {
            newEntity->posX.i.hi -= 8;
        } else {
            newEntity->posX.i.hi += 8;
        }

        newEntity->drawFlags |= FLAG_DRAW_SCALEY | FLAG_DRAW_SCALEX;
        newEntity->scaleX = newEntity->scaleY = 0xA0;
        newEntity->zPriority = g_CurrentEntity->zPriority + 2;
        newEntity->params = 0x10;
    }
}

void func_us_801D12E0(u32 resetColliderEffects) {
    Collider collider;
    s32 posX;
    s32 posY;

    posX = g_CurrentEntity->posX.i.hi;
    posY = g_CurrentEntity->posY.i.hi;
    if (g_CurrentEntity->velocityX > 0) {
        posX += 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (resetColliderEffects) {
            collider.effects = EFFECT_NONE;
        }
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posX.i.hi += collider.unk14;
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.unk85 = 1;
            SetStep(10);
            return;
        }

        posX += g_Tilemap.scrollX.i.hi;
        if (g_Tilemap.width < posX) {
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.unk85 = 1;
            SetStep(10);
        }
    } else {
        posX -= 0x10;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (resetColliderEffects) {
            collider.effects = EFFECT_NONE;
        }
        if (collider.effects & EFFECT_SOLID) {
            g_CurrentEntity->posX.i.hi += collider.unk1C;
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.unk85 = 1;
            SetStep(10);
            return;
        }

        posX += g_Tilemap.scrollX.i.hi;
        if (posX < g_Tilemap.x) {
            g_CurrentEntity->facingLeft ^= 1;
            g_CurrentEntity->ext.graveKeeper.unk82 = 0;
            g_CurrentEntity->ext.graveKeeper.unk85 = 1;
            SetStep(10);
        }
    }
}

void func_us_801D1474(Entity* self) {
    Entity* entity;
    Entity* player;
    s32 var_s2;
    s32 var_s1;
    s32 var_s3;
    s32 var_s5;
    s32 pad[9];

    if (self->flags & 0x100 && self->step != 0xC) {
        entity = self + 1;
        DestroyEntity(entity);
        self->hitboxState = 0;
        SetStep(0xC);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_8018126C);
        self->animCurFrame = 0xB;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_UNK_45, entity);
        // fallthrough
    case 1:
        if (UnkCollisionFunc3(D_us_801826BC) & 1) {
            SetStep(2);
            return;
        }
        break;
    case 2:
        self->animCurFrame = 0xB;
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        self->hitboxHeight = 8;
        self->hitboxOffY = 8;
        if (GetDistanceToPlayerX() < 0x60) {
            SetStep(3);
            return;
        }
        break;
    case 3:
        if (!self->step_s) {
            func_us_801D121C();
            self->step_s++;
        }
        if (!AnimateEntity(&D_us_8018270C, self)) {
            self->hitboxHeight = 0x14;
            self->hitboxOffY = 0;
            SetStep(4);
            return;
        }
        break;
    case 4:
    case 5:
        if (!self->step_s) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->step_s++;
        }
        UnkCollisionFunc2(D_us_801826CC);
        if (!AnimateEntity(D_us_801826DC, self)) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.graveKeeper.unk82 = 1;
        }

        if (self->facingLeft) {
            self->velocityX = FIX(0.75);
        } else {
            self->velocityX = FIX(-0.75);
        }

        if (self->step == 5) {
            self->velocityX = -self->velocityX;
        }

        switch (self->step) {
        case 4:
            if (GetDistanceToPlayerX() < 0x40) {
                SetStep(5);
            }

            // BUG: This may be uninitialised!
            if (var_s2 & 0x80) {
                var_s2 = UnkCollisionFunc(D_us_801826D4, 2);
                if (var_s2 & 2) {
                    SetStep(7);
                }
            }
            break;
        case 5:
            if (GetDistanceToPlayerX() > 0x80) {
                SetStep(4);
            }
            break;
        }

        if (self->facingLeft != (GetSideToPlayer() & 1)) {
            player = &PLAYER;
            var_s3 = GetDistanceToPlayerX();
            // BUG: this goes unused
            var_s5 = PLAYER.posY.i.hi - self->posY.i.hi;
            if ((PLAYER.step_s & 0x40) && var_s3 < 0x30) {
                if (PLAYER.step == 2) {
                    self->ext.graveKeeper.unk82 = 2;
                    SetStep(7);
                    return;
                }
                SetStep(0xD);
                return;
            }
            if (self->ext.graveKeeper.unk82) {
                var_s1 = 0;
                self->ext.graveKeeper.unk82 = 0;
                if (self->facingLeft) {
                    if (player->velocityX <= 0) {
                        var_s1 |= 1;
                    }
                } else if (player->velocityX >= 0) {
                    var_s1 |= 1;
                }

                if (PLAYER.step == 4 && var_s3 > 0x40) {
                    if (var_s1 & 1) {
                        self->ext.graveKeeper.unk82 = 0;
                    } else {
                        self->ext.graveKeeper.unk82 = 1;
                    }
                    SetStep(10);
                    return;
                }

                if (var_s3 < 0x40) {
                    if (((var_s1 != 0) ^ 1) & 1) {
                        SetStep(0xB);
                        return;
                    }
                    SetStep(8);
                    return;
                }

                if (var_s3 < 0x100) {
                    if (((var_s1 != 0) ^ 1) & 1) {
                        SetStep(10);
                        return;
                    }
                    SetStep(9);
                    return;
                }
            }
        }
        break;
    case 13:
        if (!self->step_s) {
            func_us_801D121C();
            self->step_s++;
        }
        self->hitboxHeight = 8;
        self->hitboxOffY = 8;
        if (!AnimateEntity(&D_us_80182718, self) && !(PLAYER.step_s & 0x40)) {
            SetStep(3);
            return;
        }
        break;
    case 7:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(&D_us_801826E8, self)) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->velocityY = FIX(-4.0);
                if (self->ext.graveKeeper.unk82 & 2) {
                    self->velocityX = -self->velocityX;
                }
                SetSubStep(1);
                return;
            }
            break;
        case 1:
            if (UnkCollisionFunc3(D_us_801826BC) & 1) {
                PlaySfxPositional(SFX_STOMP_HARD_B);
                SetStep(4);
                return;
            }
            func_us_801D12E0(self->ext.graveKeeper.unk85);
            return;
        }
        break;
    case 8:
        if (!AnimateEntity(D_us_801826F4, self)) {
            if (Random() & 1) {
                SetStep(4);
            } else {
                SetStep(0xB);
            }
        }

        if (self->pose == 2 && !self->poseTimer) {
            PlaySfxPositional(0x755);
            return;
        }
        break;
    case 9:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_80182700, self)) {
                PlaySfxPositional(0x755);
                if (self->facingLeft) {
                    self->velocityX = FIX(2.0);
                } else {
                    self->velocityX = FIX(-2.0);
                }
                self->ext.graveKeeper.unk80 = 0x40;
                self->poseTimer = 0;
                self->pose = 0;
                self->step_s++;
                return;
            }
            break;
        case 2:
            self->velocityX -= self->velocityX / 0x20;
            if (!AnimateEntity(&D_us_801826F4, self)) {
                SetStep(4);
                return;
            }
            if (self->pose == 2 && !self->poseTimer) {
                PlaySfxPositional(SFX_WEAPON_SWISH_C);
            }
            if (self->pose == 4) {
                self->velocityX = 0;
            }
            // fallthrough
        case 1:
            var_s2 = UnkCollisionFunc2(D_us_801826CC);
            if (var_s2 & 0x80) {
                self->ext.graveKeeper.unk82 = 0;
                SetStep(10);
            }

            if (!--self->ext.graveKeeper.unk80) {
                SetStep(4);
                return;
            }

            if (GetDistanceToPlayerX() < 0x30) {
                self->step_s = 2;
            }

            if (self->step_s == 1 && !(g_Timer & 7)) {
                func_us_801D121C();
                return;
            }
        }
        break;
    case 10:
        switch (self->step_s) {
        case 0:
            if (!AnimateEntity(D_us_801826E8, self)) {
                PlaySfxPositional(0x754);
                if (self->ext.graveKeeper.unk82 & 1) {
                    self->velocityX = FIX(3.0);
                    self->velocityY = FIX(-6.0);
                } else {
                    self->velocityX = FIX(2.5);
                    self->velocityY = FIX(-4.0);
                }

                if (!self->facingLeft) {
                    self->velocityX = -self->velocityX;
                }
                self->ext.graveKeeper.unk84 = 0;
                self->step_s++;
                return;
            }
            break;
        case 1:
            entity = self + 1;
            if (entity->hitFlags & 0x80) {
                PlaySfxPositional(SFX_WEAPON_HIT_A);
                self->velocityX = -self->velocityX / 2;
                self->velocityY = FIX(-3.0);
                self->ext.graveKeeper.unk84 = 1;
                self->step_s++;
            }
            // fallthrough
        case 2:
            if (self->velocityY > FIX(65535.0)) {
                self->velocityY -= FIX(0.0625);
                self->animCurFrame = 0xA;
            }

            if (self->velocityY > FIX(1.0)) {
                var_s2 = UnkCollisionFunc3(D_us_801826BC);
                if (var_s2 & 1) {
                    self->ext.graveKeeper.unk85 = 0;
                    PlaySfxPositional(SFX_STOMP_HARD_B);
                    SetStep(6);
                    return;
                }
            } else {
                MoveEntity();
                self->velocityY += FIX(0.25);
            }

            if (!self->ext.graveKeeper.unk84) {
                func_us_801D12E0(self->ext.graveKeeper.unk85);
                return;
            }
            break;
        }
        break;
    case 6:
        if (!self->step_s) {
            func_us_801D121C();
            self->step_s++;
        }
        if (!AnimateEntity(D_us_80182724, self)) {
            SetStep(4);
            return;
        }
        break;
    case 11:
        if (!self->step_s) {
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
        }
        if (self->pose == 4 && !self->poseTimer) {
            PlaySfxPositional(0x755);
            if (self->facingLeft) {
                self->velocityX = FIX(2.0);
            } else {
                self->velocityX = FIX(-2.0);
            }
        }

        UnkCollisionFunc2(D_us_801826CC);
        self->velocityX -= self->velocityX / 0x20;
        if (self->velocityX != 0 && !(g_Timer & 7)) {
            func_us_801D121C();
        }

        if (!AnimateEntity(D_us_80182730, self)) {
            SetStep(4);
            return;
        }
        break;
    case 12:
        switch (self->step_s) {
        case 0:
            self->velocityX = FIX(2.0);
            if ((GetSideToPlayer() & 1) ^ 1) {
                self->velocityX = -self->velocityX;
            }
            PlaySfxPositional(0x756);
            self->step_s++;
            break;
        case 1:
            UnkCollisionFunc2(D_us_801826CC);
            self->velocityX -= self->velocityX / 0x20;
            if (!AnimateEntity(&D_us_80182740, self)) {
                self->step_s++;
            }
            break;
        case 2:
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 3;
            }
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            DestroyEntity(self);
            break;
        }
        break;
    }
}

void func_us_801D1F68(Entity* self) {
    Entity* parent;
    s32 idx;
    s16* ptr;

    if (!self->step_s) {
        InitializeEntity(D_us_80181278);
    }

    parent = self - 1;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    self->facingLeft = parent->facingLeft;

    switch (parent->animCurFrame) {
    case 5:
        idx = 1 * LEN(D_us_80182750);
        break;
    case 9:
        idx = 2 * LEN(D_us_80182750);
        break;
    case 10:
        idx = 3 * LEN(D_us_80182750);
        break;
    default:
        idx = 0 * LEN(D_us_80182750);
        break;
    }

    ptr = D_us_80182750[0] + idx;
    self->hitboxOffX = *ptr++;
    self->hitboxOffY = *ptr++;
    self->hitboxWidth = *ptr++;
    self->hitboxHeight = *ptr++;
    if (parent->entityId != 0x44) {
        DestroyEntity(self);
    }
}
