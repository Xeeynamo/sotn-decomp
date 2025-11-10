// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitHarpy;
extern AnimationFrame D_us_80181F04[];
extern AnimationFrame D_us_80181F10[];
extern AnimationFrame D_us_80181F1C[];
extern AnimationFrame D_us_80181F28[];
extern AnimationFrame D_us_80181F3C[];
extern AnimationFrame D_us_80181F48[];
extern AnimationFrame D_us_80181F5C[];
extern AnimationFrame D_us_80181F68[];
extern s16 D_us_80181FA8[];

void EntityHarpy(Entity* self) {
    Entity* entity;
    Entity* player;
    s32 i;
    s16 angle;
    s32 posX;
    s32 posY;
    s32 velocity;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        SetStep(0xC);
    }

    if (self->flags & FLAG_DEAD && self->step != 14) {
        PlaySfxPositional(SFX_HARPY_DEATH);
        SetStep(14);
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHarpy);
        self->zPriority = 0x9C;
        self->ext.harpy.timer = 0x80;
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_HARPY_KICK, entity);
        SetStep(2);
        // fallthrough

    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_80181F1C, self);
        if (self->pose == 1 && !self->poseTimer) {
            PlaySfxPositional(SFX_HARPY_WING_FLAP);
        }
        MoveEntity();
        angle = self->ext.harpy.angle += ROT(2.8125);
        angle &= 0xFFF;

        self->velocityX = rcos(angle) * 2;
        self->velocityY = rsin(angle) * 8;
        if (GetDistanceToPlayerX() < 0x70 && GetDistanceToPlayerY() < 0x40) {
            SetStep(4);
        }
        break;

    case 5:
        if (!self->step_s) {
            self->ext.harpy.unk8C = 0;
            self->ext.harpy.unk80 = 0;
            self->step_s++;
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(D_us_80181F04, self);
        if (self->pose == 1 && !self->poseTimer) {
            PlaySfxPositional(SFX_HARPY_WING_FLAP);
        }
        MoveEntity();

        if (!self->ext.harpy.unk80) {
            self->ext.harpy.unk80 = 64;
            self->ext.harpy.unk8C = 0;
            self->ext.harpy.unk88 = (Random() & 0x3F) * 0x10;
        } else {
            self->ext.harpy.unk80--;
        }

        angle = self->ext.harpy.unk88 + 0x200;

        player = &PLAYER;
        posX = player->posX.i.hi - self->posX.i.hi;
        posX += (FLT_TO_I(rcos(angle) * 0x60));

        posY = player->posY.i.hi - self->posY.i.hi;
        posY -= FLT_TO_I(rsin(angle) * 0x60);

        if (abs(posX) < 6) {
            self->ext.harpy.unk80 = 0;
        }
        angle = ratan2(posY, posX);
        velocity = self->ext.harpy.unk8C;
        self->velocityX = FLT_TO_I(velocity * rcos(angle));
        self->velocityY = FLT_TO_I(velocity * rsin(angle));

        angle = self->ext.harpy.angle += ROT(2.8125);
        self->velocityY += (rsin(angle) * 8);

        velocity += FIX(3.0 / 64.0);
        if (velocity > FIX(1.25)) {
            velocity = FIX(1.25);
        }
        self->ext.harpy.unk8C = velocity;
        if (!--self->ext.harpy.timer) {
            self->ext.harpy.timer = D_us_80181FA8[(Random() & 3)];
            posX = GetDistanceToPlayerX();
            posY = GetDistanceToPlayerY();
            if (posX < posY) {
                SetStep(11);
            } else {
                SetStep(7);
            }
        }
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            if (AnimateEntity(&D_us_80181F28, self) == 0) {
                self->animCurFrame = 8;
                self->drawFlags = FLAG_DRAW_ROTATE;
                self->rotate = ROT(0);
                self->step_s += 1;
            }
            if (self->pose == 1 && !self->poseTimer) {
                PlaySfxPositional(SFX_HARPY_WING_FLAP);
                return;
            }
            break;
        case 1:
            self->rotate += ROT(22.5);
            if (self->rotate > ROT(360)) {
                self->drawFlags = FLAG_DRAW_DEFAULT;
                self->animCurFrame = 10;
                SetSubStep(2);
                return;
            }
            break;
        case 2:
            if (AnimateEntity(&D_us_80181F3C, self) == 0) {
                SetStep(5);
            }
            if (!self->poseTimer && self->pose == 3) {
                PlaySfxPositional(SFX_GUARD_TINK);
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_HARPY_DAGGER, self, entity);
                    if (self->facingLeft) {
                        entity->posX.i.hi += 0x10;
                    } else {
                        entity->posX.i.hi -= 0x10;
                    }
                    entity->posY.i.hi += 0x20;
                    entity->facingLeft = self->facingLeft;
                    player = &PLAYER;
                    posX = player->posX.i.hi - entity->posX.i.hi;
                    posY = player->posY.i.hi - entity->posY.i.hi;
                    if (!self->facingLeft) {
                        posX = -posX;
                    }
                    angle = ratan2(-posY, posX);
                    if (angle > FLT(1.0 / 16.0)) {
                        angle = FLT(1.0 / 16.0);
                    }
                    if (angle < FLT(-3.0 / 16.0)) {
                        angle = FLT(-3.0 / 16.0);
                    }
                    entity->rotate = angle;
                    entity->zPriority = self->zPriority;
                }
            }
        }
        break;

    case 11:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.harpy.unk84 = 0;
            self->step_s++;
            // fallthrough
        case 1:
            if (self->facingLeft) {
                self->velocityX = FIX(-1.25);
            } else {
                self->velocityX = FIX(1.25);
            }
            MoveEntity();
            if (self->pose == 1 && !self->poseTimer) {
                PlaySfxPositional(SFX_HARPY_WING_FLAP);
            }
            if (AnimateEntity(&D_us_80181F10, self) == 0) {
                self->ext.harpy.unk84++;
            }
            if (self->ext.harpy.unk84 > 2) {
                self->step_s++;
            }
            break;

        case 2:
            PlaySfxPositional(SFX_FM_EXPLODE_SWISHES);
            for (i = 0; i < 3; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_HARPY_FLAME, self, entity);
                    entity->params = i;
                    entity->zPriority = self->zPriority - 1;
                    entity->facingLeft = self->facingLeft;
                }
            };
            SetStep(5);
        }
        break;

    case 7:
        switch (self->step_s) {
        case 0:
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            player = &PLAYER;
            posX = player->posX.i.hi;
            posY = player->posY.i.hi;
            if (self->facingLeft) {
                posX -= 0x20;
            } else {
                posX += 0x20;
            }
            self->ext.harpy.unk90 = posX + g_Tilemap.scrollX.i.hi;
            self->ext.harpy.unk92 = posY + g_Tilemap.scrollY.i.hi;
            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;
            angle = ratan2(posY, posX);
            self->velocityX = FLT_TO_I(rcos(angle) * FLT(48));
            self->velocityY = FLT_TO_I(rsin(angle) * FLT(48));
            self->animCurFrame = 1;
            self->step_s++;
            // fallthrough

        case 1:
            MoveEntity();
            posX = self->ext.harpy.unk90 - g_Tilemap.scrollX.i.hi;
            posY = self->ext.harpy.unk92 - g_Tilemap.scrollY.i.hi;

            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;

            if (abs(posX) < 0x18) {
                if (abs(posY) < 0x18) {
                    SetSubStep(2);
                }
            }
            break;

        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;

            if (self->pose == 3 && !self->poseTimer) {
                PlaySfxPositional(SFX_AXE_KNIGHT_WEAPON_BREAK);
            }

            if (AnimateEntity(&D_us_80181F48, self) == 0) {
                SetStep(5);
            }
        }
        break;

    case 12:
        if (!self->step_s) {
            if ((GetSideToPlayer() & 1) ^ 1) {
                self->velocityX = FIX(-2);
            } else {
                self->velocityX = FIX(2);
            }
            PlaySfxPositional(SFX_HARPY_ATTACK);
            self->step_s++;
        }

        MoveEntity();

        self->velocityX -= self->velocityX / 32;
        self->velocityY -= self->velocityY / 32;
        if ((self->pose < 4) && (g_Timer & 1)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HARPY_FEATHER, self, entity);
                if (self->facingLeft) {
                    entity->posX.i.hi -= 0x10;
                } else {
                    entity->posX.i.hi += 0x10;
                }
                entity->posY.i.hi -= 8;
                entity->zPriority = self->zPriority + 1;
            }
        }
        if (AnimateEntity(&D_us_80181F5C, self) == 0) {
            SetStep(5);
        }
        break;
    case 14:
        switch (self->step_s) {
        case 0:
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->hitboxState = 0;
            entity = self + 1;
            DestroyEntity(entity);
            self->drawFlags = FLAG_DRAW_ROTATE;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            // fallthrough
        case 1:
            if (AnimateEntity(&D_us_80181F68, self) == 0) {
                self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
                self->step_s++;
            }
            self->rotate += ROT(1.40625);
            if (g_Timer & 1) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_HARPY_FEATHER, self, entity);
                    entity->zPriority = self->zPriority + 1;
                }
            }
            break;
        case 2:
            MoveEntity();
            self->velocityY += FIX(0.0625);
            self->rotate += ROT(2.8125);
            if (!(g_Timer & 3)) {
                entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (entity != NULL) {
                    CreateEntityFromEntity(E_EXPLOSION, self, entity);
                    entity->params = EXPLOSION_FIREBALL;
                    entity->zPriority = self->zPriority + 1;
                    entity->posX.i.hi += -0x10 + (Random() & 0x1F);
                    entity->posY.i.hi += -0x10 + (Random() & 0x1F);
                }
            }
        }
        break;

    case 0xFF:
#include "pad2_anim_debug.h"
        break;
    }
}
