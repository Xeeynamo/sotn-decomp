// SPDX-License-Identifier: AGPL-3.0-or-later
#include "dai.h"

#ifdef VERSION_PSP
extern s32 E_ID(UNK_2F);
extern s32 E_ID(UNK_30);
extern s32 E_ID(UNK_31);
#endif

static u8 anim[] = {2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1, 0, 0, 0};
static u8 D_us_80180EB4[][3] = {{5, 4, 6}, {1, 0, 2}, {9, 8, 10}, {0, 0, 0}};

void func_us_801C379C(Entity* self) {
    s16 angle;

    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority = 160;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_OVL(PAL_UNK_161);
        angle = GetAngleBetweenEntitiesShifted(self, g_Entities);
        SetEntityVelocityFromAngle(angle, 40);
        return;
    }
    MoveEntity();
    if (!AnimateEntity(anim, self)) {
        DestroyEntity(self);
    }
}

void func_us_801C3850(Entity* self) {
    Collider collider;
    s16 posX, posY;
    u8 params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitStatueBlock);
        self->animCurFrame = 15;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.unk4379C.rotate = 0;
        params = (self->params & 0xFF00) >> 8;
        if ((params) & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += ROT(1.40625);
            self->ext.unk4379C.rotate += 8;
        }
        if ((params) & 2) {
            self->velocityX = FIX(-0.5);
            self->rotate -= ROT(1.40625);
            self->ext.unk4379C.rotate -= 8;
        }
        params = self->params & 0xFF;
        if (params & 2) {
            self->velocityX += FIX(-0.75);
            self->rotate -= ROT(90);
            self->ext.unk4379C.rotate += 64;
        }
        if (params & 1) {
            self->velocityX += FIX(0.75);
            self->rotate += ROT(90);
            self->ext.unk4379C.rotate -= 64;
        }
        if (params & 4) {
            self->velocityY += FIX(0.75);
            self->rotate -= ROT(180);
        }
        if (params & 8) {
            self->velocityY += FIX(-2.5);
        }
        self->velocityX += FIX(-0.1875) + ((Random() & 3) << 13);
        self->velocityY += FIX(-0.1875) + ((Random() & 3) << 13);
        self->ext.unk4379C.rotate += (-24 + (Random() & 3) * 16);
        break;
    case 1:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.unk4379C.rotate;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects) {
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = -self->velocityY / 2;
                self->ext.unk4379C.rotate *= 4;
            }
            if (collider.effects & EFFECT_UNK_0002) {
                self->velocityX = -self->velocityX;
            }
            if (abs(self->velocityY) < FIX(0.1875)) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

void func_us_801C3B10(u32 tileIdx) {
    u8 accumulator;
    Entity* entity;
    s16 posX, posY;
    s32 count;
    s32 i, j;
    u8 collision;
    u32 collisionIdx;

    posX = ((tileIdx % 80) * 16) + 8;
    posY = ((tileIdx / 80) * 16) + 8;
    accumulator = 0;
    tileIdx -= 81;
    for (i = 0; i < 3; tileIdx += 80, i++) {
        for (j = 0; j < 3; j++) {
            collisionIdx = (&g_Tilemap.fg[tileIdx])[j];
            collision = g_Tilemap.tileDef->collision[collisionIdx];
            if (collision == 3) {
                accumulator |= D_us_80180EB4[i][j];
            }
        }
    }
    posX -= g_Tilemap.scrollX.i.hi;
    posY -= g_Tilemap.scrollY.i.hi;
    for (i = 0; i < 3; i++) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_ID(UNK_2F), entity);
            entity->posX.i.hi = posX;
            entity->posY.i.hi = posY;
            entity->params = accumulator + (i << 8);
        }
    }
    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, entity);
        entity->posX.i.hi = posX;
        entity->posY.i.hi = posY;
        entity->params = 16;
    }
    entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (entity != NULL) {
        CreateEntityFromCurrentEntity(E_ID(UNK_30), entity);
        entity->posX.i.hi = posX;
        entity->posY.i.hi = posY;
    }
}

void func_us_801C3CE4(u32 arg0) {
    Tilemap* gTilemap;
    Entity* gCurrentEntity;
    s16 scrollX, scrollY;

    scrollX = arg0 % 80 * 16 + 8;
    scrollY = arg0 / 80 * 16 + 8;
    scrollX -= g_Tilemap.scrollX.i.hi;
    scrollY -= g_Tilemap.scrollY.i.hi;

    gCurrentEntity = g_CurrentEntity + 1;
    gCurrentEntity->posX.i.hi = scrollX;
    gCurrentEntity->posY.i.hi = scrollY;
}

void func_us_801C3D44(Entity* self) {
    u8 colType;
    u32 tileIdx;
    s32 count;
    Entity* entity;
    u32 colTile;
    Entity* playerPtr = &PLAYER;
    s16 posY;
    s16 scrollX, scrollY;
    u16 posX;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSpawner);
        entity = self + 1;
        CreateEntityFromCurrentEntity(E_ID(UNK_31), entity);
        break;
    case 1:
        entity = self + 1;
        entity->posX.i.hi = -16;
        entity->posY.i.hi = -16;
#ifdef VERSION_PSP
        posX = playerPtr->posX.i.hi;
        posY = playerPtr->posY.i.hi;
        scrollX = LOH(posX) + g_Tilemap.scrollX.i.hi;
#else
        posY = playerPtr->posY.i.hi;
        scrollX = LOH(playerPtr->posX.i.hi) + g_Tilemap.scrollX.i.hi;
#endif
        scrollY = posY + g_Tilemap.scrollY.i.hi;
        tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 16;
        tileIdx -= 80;
        for (count = 0; count < 3; tileIdx += 80, count++) {
            colTile = g_Tilemap.fg[tileIdx];
            colType = g_Tilemap.tileDef->collision[colTile];
            if (colType > 243 && colType < 248) {
                // Is there an enum for this?
                if (g_api.CheckEquipmentItemCount(0xE, 2)) {
                    g_Tilemap.fg[tileIdx] = 0;
                    func_us_801C3B10(tileIdx);
                    g_api.PlaySfx(SFX_EXPLODE_FAST_A);
                } else {
                    func_us_801C3CE4(tileIdx);
                }
            }
        }
        break;
    }
}

void func_us_801C3ED8(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        // The elements needed have not yet been defined in the enum
        self->attackElement = 0x51;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
    }
}
