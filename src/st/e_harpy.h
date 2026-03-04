// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitHarpy;
extern EInit g_EInitHarpyDagger;
extern EInit g_EInitHarpyFlame;
extern EInit g_EInitHarpyKick;
extern EInit g_EInitHarpyFeather;

static u8 anim0[] = {10, 1, 7, 2, 8, 3, 9, 4, 10, 5, 0, 0};
static u8 anim1[] = {5, 1, 4, 2, 4, 3, 5, 4, 5, 5, 0, 0};
static u8 anim2[] = {10, 6, 7, 7, 8, 8, 9, 9, 10, 10, 0, 0};
static u8 anim3[] = {5, 6, 4, 7, 4, 8, 5, 9, 5, 10, 5, 6, 4, 7, 4, 8, -1, 0};
static u8 anim4[] = {4, 10, 3, 11, 4, 23, 9, 12, 6, 13, -1, 0};
static u8 anim5[] = {1, 1, 2, 13, 2, 23, 16, 12, 6,  14,
                     3, 2, 3, 3,  3, 4,  3,  5,  -1, 0};
static u8 anim6[] = {4, 1, 8, 15, 12, 16, 4, 4, 4, 5, -1, 0};
static u8 anim7[] = {8, 1, 8, 15, 8, 16, 24, 17, -1, 0};
static u8 anim8[] = {1, 19, 1, 20, 1, 21, 1, 22, 0, 0};

static s8 hitboxes[][4] = {
    {0, 0, 0, 0},   {-58, -52, 0, 0}, {26, 30, 5, 5},
    {27, 29, 5, 5}, {11, 37, 5, 5},   {-27, 6, 5, 5},
};
static u8 hitboxOffsets[] = {0, 1, 1, 1, 1, 1, 1, 2, 3, 2, 2, 4, 5, 1, 0, 0};

static s16 delays[] = {0x40, 0x20, 0x80, 0xC0};

void EntityHarpy(Entity* self) {
    Entity* entity;
    Entity* player;
    s32 i;
    s16 angle;
    s32 posX, posY;
    s32 velocity;

    if ((self->step & 1) && (self->hitFlags & 3)) {
        SetStep(12);
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
        /* fallthrough */
    case 2:
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
        AnimateEntity(anim2, self);
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
        AnimateEntity(anim0, self);
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
        posX += FLT_TO_I(rcos(angle) * 0x60);

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
            self->ext.harpy.timer = delays[Random() & 3];
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
            if (AnimateEntity(anim3, self) == 0) {
                self->animCurFrame = 8;
                self->drawFlags = ENTITY_ROTATE;
                self->rotate = ROT(0);
                self->step_s++;
            }
            if (self->pose == 1 && !self->poseTimer) {
                PlaySfxPositional(SFX_HARPY_WING_FLAP);
            }
            break;

        case 1:
            self->rotate += ROT(22.5);
            if (self->rotate > ROT(360)) {
                self->drawFlags = ENTITY_DEFAULT;
                self->animCurFrame = 10;
                SetSubStep(2);
            }
            break;

        case 2:
            if (AnimateEntity(anim4, self) == 0) {
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
                    if (angle > ROT(22.5)) {
                        angle = ROT(22.5);
                    }
                    if (angle < ROT(-67.5)) {
                        angle = ROT(-67.5);
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
            /* fallthrough */
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
            if (AnimateEntity(anim1, self) == 0) {
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
            /* fallthrough */
        case 1:
            MoveEntity();
            posX = self->ext.harpy.unk90 - g_Tilemap.scrollX.i.hi;
            posY = self->ext.harpy.unk92 - g_Tilemap.scrollY.i.hi;

            posX -= self->posX.i.hi;
            posY -= self->posY.i.hi;

            if (abs(posX) < 24 && abs(posY) < 24) {
                SetSubStep(2);
            }
            break;

        case 2:
            MoveEntity();
            self->velocityX -= self->velocityX / 32;
            self->velocityY -= self->velocityY / 32;

            if (self->pose == 3 && !self->poseTimer) {
                PlaySfxPositional(SFX_AXE_KNIGHT_WEAPON_BREAK);
            }

            if (AnimateEntity(anim5, self) == 0) {
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
        if (self->pose < 4 && (g_Timer & 1)) {
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
        if (AnimateEntity(anim6, self) == 0) {
            SetStep(5);
        }
        break;

    case 14:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_DEFAULT;
            self->hitboxState = 0;
            entity = self + 1;
            DestroyEntity(entity);
            self->drawFlags = ENTITY_ROTATE;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA;
            self->step_s++;
            /* fallthrough */
        case 1:
            if (AnimateEntity(anim7, self) == 0) {
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
                    entity->posX.i.hi += (Random() & 0x1F) - 0x10;
                    entity->posY.i.hi += (Random() & 0x1F) - 0x10;
                }
            }
        }
        break;

    case 0xFF:
#include "pad2_anim_debug.h"
        break;
    }
}

void EntityHarpyDagger(Entity* self) {
    s16 angle;

    if (self->flags & FLAG_DEAD && self->step != 2) {
        SetStep(2);
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHarpyDagger);
        self->animCurFrame = 18;
        self->drawFlags = ENTITY_ROTATE;
        angle = self->rotate;
        if (self->facingLeft) {
            angle = -angle;
        } else {
            angle = ROT(180) + angle;
        }
        self->facingLeft = false;
        self->velocityX = FLT_TO_I(rcos(angle) * FLT(48));
        self->velocityY = FLT_TO_I(rsin(angle) * FLT(48));
        /* fallthrough */
    case 1:
        MoveEntity();
        self->rotate += ROT(11.25);
        break;

    case 2:
        switch (self->step_s) {
        case 0:
            self->velocityX = -self->velocityX;
            self->velocityY = FIX(-4);
            self->flags |= FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
            self->step_s++;
            /* fallthrough */
        case 1:
            MoveEntity();
            self->velocityY += FIX(3.0 / 16);
            self->rotate -= ROT(16.875);
        }
        break;
    }
}

void EntityHarpyFlame(Entity* self) {
    Entity* tempEntity;
    s16 angle;

    if (self->flags & FLAG_DEAD) {
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 0;
        }
        DestroyEntity(self);
        return;
    }
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHarpyFlame);
        self->drawFlags = ENTITY_ROTATE;
        self->drawFlags |= ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = self->scaleY = 0x200;
        if (self->params & 0xFF00) {
            self->animCurFrame = self->params >> 8;
            self->hitboxState = 0;
            self->opacity = 0x40;
            self->step = 2;
            self->drawFlags |= ENTITY_OPACITY;
            self->blendMode = BLEND_ADD | BLEND_TRANSP;
            return;
        }
        angle = (self->params * 0x180) - 0x180;
        if (self->facingLeft) {
            angle = -angle;
        } else {
            angle = angle + ROT(180);
        }
        self->rotate = angle + ROT(180);
        self->facingLeft = false;
        /* fallthrough */
    case 1:
        angle = self->rotate - ROT(180);
        self->velocityX = FLT_TO_I(rcos(angle) * FLT(56));
        self->velocityY = FLT_TO_I(rsin(angle) * FLT(56));
        MoveEntity();
        AnimateEntity(anim8, self);
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_HARPY_FLAME, self, tempEntity);
            tempEntity->params = self->animCurFrame << 8;
            tempEntity->rotate = self->rotate;
            tempEntity->facingLeft = self->facingLeft;
        }
        break;

    case 2:
        self->opacity -= 8;
        if (!self->opacity) {
            DestroyEntity(self);
        }
        break;
    }
}

void EntityHarpyKick(Entity* self) {
    s32 animFrame;
    s8* hitboxPtr;
    Entity* tempEntity;

    if (!self->step) {
        InitializeEntity(g_EInitHarpyKick);
    }
    tempEntity = self - 1;
    self->facingLeft = tempEntity->facingLeft;
    self->posX.val = tempEntity->posX.val;
    self->posY.val = tempEntity->posY.val;
    animFrame = tempEntity->animCurFrame;
    if (animFrame > 13) {
        animFrame = 0;
    }
    hitboxPtr = hitboxes[0];
    hitboxPtr += hitboxOffsets[animFrame] * 4;
    self->hitboxOffX = *hitboxPtr++;
    self->hitboxOffY = *hitboxPtr++;
    self->hitboxWidth = *hitboxPtr++;
    self->hitboxHeight = *hitboxPtr++;
    if (tempEntity->entityId != E_HARPY) {
        DestroyEntity(self);
    }
}

void EntityHarpyFeather(Entity* self) {
    s32 scale;
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitHarpyFeather);
        self->facingLeft = Random() & 1;
        self->drawFlags = ENTITY_ROTATE;
        scale = (Random() & 0x1F) + 0x10;
        angle = (Random() * 6) + ROT(202.5);
        self->velocityX = scale * rcos(angle);
        self->velocityY = scale * rsin(angle);
    }
    MoveEntity();
    self->rotate += 0x20;
    self->velocityY += FIX(1.0 / 8);
}
