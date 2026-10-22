// SPDX-License-Identifier: AGPL-3.0-or-later
#include "bo5.h"

void func_us_801A19CC(u8 arg0) {
    g_CurrentEntity->poseTimer = 0;
    g_CurrentEntity->pose = 0;
    g_CurrentEntity->ext.et_801A19CC.unk7D = 0;
    g_CurrentEntity->step = arg0;
    g_CurrentEntity->step_s = 0;
}

void func_us_801A19FC(u8 count, s16 posY) {
    Entity* entity;
    s32 i;

    for (i = 0; i < count; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            DestroyEntity(entity);
            MakeEntityFromId(E_ID(UNK_22), g_CurrentEntity, entity);
            entity->flags =
                FLAG_DESTROY_IF_OUT_OF_CAMERA |
                FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA | FLAG_POS_CAMERA_LOCKED |
                FLAG_UNK_00200000 | FLAG_UNK_2000;
            entity->posX.i.hi += (Random() & 0x3F) - 0x20;
            entity->posY.i.hi += (Random() & 0x3F) - 0x20 + posY;
            entity->velocityY = -FIX(0.25);
            if (Random() & 1) {
                entity->zPriority++;
            }
            entity->step = 0x30;
            entity->params = Random() & 1;
            if (entity->params) {
                entity->step = 0x32;
                if (Random() & 1) {
                    entity->ext.et_801A19CC.unk8C = 0xD00;
                    entity->velocityX = -FIX(0.8125);
                } else {
                    entity->ext.et_801A19CC.unk8C = -0xD00;
                    entity->velocityX = FIX(0.8125);
                }
            }
            if (g_CurrentEntity->step == 0x16) {
                if (g_CurrentEntity->facingLeft) {
                    g_CurrentEntity->velocityX += FIX(0.25);
                } else {
                    g_CurrentEntity->velocityX -= FIX(0.25);
                }
            }
        }
    }
}

bool CheckHippogryphFloorCollision(s16* sensors) {
    s32 posY;

    if (UnkCollisionFunc3(sensors) & 1) {
        return true;
    } else {
        posY = g_CurrentEntity->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (posY > 183) {
            g_CurrentEntity->posY.i.hi = 183 - g_Tilemap.scrollY.i.hi;
            g_CurrentEntity->velocityX = 0;
            g_CurrentEntity->velocityY = 0;
            return true;
        }
        return false;
    }
}

INCLUDE_ASM("boss/bo5/nonmatchings/e_hippogryph", func_us_801A1C14);

extern s32 D_us_801806E0;
extern EInit D_us_801804F0;
extern AnimateEntityFrame D_us_80180A00[];
extern AnimateEntityFrame D_us_80180A0C[];

void func_us_801A3B88(Entity* self) {
    Entity* entity;

    if (D_us_801806E0 & 2) {
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804F0);
        self->hitboxState = 0;
        self->animSet = 2;
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        self->rotate = 0xE00;
        self->scaleX = self->scaleY = 0x20;
        if (self->facingLeft) {
            self->velocityX = FIX(4.40625);
        } else {
            self->velocityX = -FIX(4.40625);
        }
        if (self->params) {
            self->velocityY = FIX(0.1875);
        } else {
            self->velocityY = -FIX(0.375);
        }
        if (self->params >= 2) {
            self->opacity = 0x7C;
            self->velocityY = 0;
            if (self->params == 3) {
                self->hitboxState = 1;
            }
        }
        break;

    case 1:
        AnimateEntity(D_us_80180A00, self);
        MoveEntity();
        self->velocityY -= FIX(0.078125);
        self->opacity -= 5;
        self->scaleX += 0x18;
        self->scaleY = self->scaleX;
        if (self->scaleX > 0xF0) {
            self->velocityX = self->velocityX / 4;
            self->pose = 0;
            self->poseTimer = 0;
            self->step++;
        }
        if (self->params == 3 && (Random() & 1)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_ID(UNK_26), self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        if (!self->params && (Random() & 7)) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_ID(UNK_26), self, entity);
                entity->facingLeft = self->facingLeft;
                entity->params = self->params;
                entity->scaleX = self->scaleX;
                entity->scaleY = self->scaleY;
            }
        }
        break;

    case 2:
        MoveEntity();
        if (!AnimateEntity(D_us_80180A0C, self)) {
            DestroyEntity(self);
        }
        break;
    }
}

extern EInit g_EInitParticle;
extern AnimateEntityFrame D_us_80180A18[];

void func_us_801A3E78(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->animSet = 2;
        self->animCurFrame = 1;
        self->drawFlags |= ENTITY_SCALEX | ENTITY_SCALEY | ENTITY_OPACITY;
        self->drawFlags |= ENTITY_ROTATE;
        self->blendMode |= BLEND_TRANSP | BLEND_ADD;
        self->opacity = 0x80;
        if (self->facingLeft) {
            self->velocityX = FIX(1);
        } else {
            self->velocityX = -FIX(1);
        }
        if (self->params) {
            self->velocityY = FIX(0.5);
            return;
        }
        self->velocityY = -FIX(1);
        return;

    case 1:
        MoveEntity();
        if (self->facingLeft) {
            self->velocityX -= FIX(0.125);
        } else {
            self->velocityX += FIX(0.125);
        }
        self->velocityY -= FIX(0.0625);
        if (self->params) {
            self->rotate -= ROT(5.625);
        } else {
            self->rotate += ROT(5.625);
        }
        self->scaleX -= 0xA;
        self->opacity -= 6;
        if (!AnimateEntity(D_us_80180A18, self)) {
            DestroyEntity(self);
        }
        return;
    }
}

extern EInit D_us_801804E4;
extern s16 D_us_80180ABC[];
extern AnimateEntityFrame D_us_801809F0[];
extern AnimateEntityFrame D_us_801809F8[];

void func_us_801A3FD4(Entity* self) {
    Entity* entity;

    if (D_us_801806E0 & 2) {
        self->flags |= FLAG_DEAD;
    }

    if (self->flags & FLAG_DEAD) {
        entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (entity != NULL) {
            DestroyEntity(entity);
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801804E4);
        self->hitboxState = 2;
        self->drawFlags |= ENTITY_ROTATE;
        self->rotate = ((Random() & 3) << 9) - 0x300;
        self->ext.et_801A3FD4.rotateDir = 1;
        return;

    case 1:
        if (UnkCollisionFunc3(D_us_80180ABC) & 1) {
            self->step++;
        }

    case 2:
        if (!self->ext.et_801A3FD4.timer) {
            if (AnimateEntity(D_us_801809F0, self)) {
                return;
            }
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0;
            }
            self->facingLeft = GetSideToPlayer() & 1;
            self->drawFlags = ENTITY_DEFAULT;
            if (self->facingLeft) {
                self->velocityX = -FIX(2.5);
            } else {
                self->velocityX = FIX(2.5);
            }
            self->velocityY = -FIX(0.25);
            self->pose = 0;
            self->poseTimer = 0;
            self->hitboxState = 3;
            PlaySfxPositional(SFX_NO1_BIRD_CYCLE);
            self->step++;
            return;
        } else if (self->ext.et_801A3FD4.timer-- < 8) {
            self->rotate += self->ext.et_801A3FD4.rotateDir << 9;
            self->ext.et_801A3FD4.rotateDir = -self->ext.et_801A3FD4.rotateDir;
            return;
        }
        break;

    case 3:
        AnimateEntity(D_us_801809F8, self);
        MoveEntity();
        self->velocityY -= FIX(0.0390625);
        break;
    }
}

extern EInit g_EInitInteractable;
extern u8 D_us_80180B0C[];

void EntityHippogryphHitbox(Entity* self) {
    Entity* parent;
    u8 frame;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->hitPoints = 0x7FFE;
        self->hitboxState = 2;
        self->flags |= FLAG_SUPPRESS_STUN;
        self->attack = 0;
        self->attackElement = 0;
        self->parent = self - 1;
        self->nextPart = self - 1;
    }

    parent = self - 1;
    frame = parent->animCurFrame;
    if (frame > 0x67) {
        frame = 0;
    }

    frame = D_us_80180B0C[frame];
    switch (frame) {
    case 0:
        self->hitboxOffX = 0;
        self->hitboxOffY = 0;
        self->hitboxWidth = 0;
        self->hitboxHeight = 0;
        break;
    case 1:
        self->hitboxOffX = 8;
        self->hitboxOffY = -24;
        self->hitboxWidth = 20;
        self->hitboxHeight = 18;
        break;
    case 2:
        self->hitboxOffX = 12;
        self->hitboxOffY = -8;
        self->hitboxWidth = 18;
        self->hitboxHeight = 8;
        break;
    case 3:
        self->hitboxOffX = -2;
        self->hitboxOffY = 24;
        self->hitboxWidth = 8;
        self->hitboxHeight = 18;
        break;
    case 4:
        self->hitboxOffX = 6;
        self->hitboxOffY = 10;
        self->hitboxWidth = 16;
        self->hitboxHeight = 10;
        break;
    case 5:
        self->hitboxOffX = 16;
        self->hitboxOffY = -32;
        self->hitboxWidth = 22;
        self->hitboxHeight = 22;
        break;
    case 6:
        self->hitboxOffX = 2;
        self->hitboxOffY = -32;
        self->hitboxWidth = 12;
        self->hitboxHeight = 24;
        break;
    }

    self->facingLeft = parent->facingLeft;
    self->posX.i.hi = parent->posX.i.hi;
    self->posY.i.hi = parent->posY.i.hi;
    if (parent->entityId != E_ID(UNK_22)) {
        DestroyEntity(self);
    }
}

void EntityFireDamageHitbox(Entity* self) {
    if (!self->step) {
        InitializeEntity(D_us_801804F0);
        self->hitboxWidth = 24;
        self->hitboxHeight = 4;
        self->hitboxOffX = -48;
        self->hitboxOffY = -2;
    }
}
