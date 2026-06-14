// SPDX-License-Identifier: AGPL-3.0-or-later
#include "nz1.h"

extern EInit g_EInitInteractable;
extern EInit g_EInitEnvironment;

static s16 D_us_80180FF8[] = {
    0x30C, 0x30D, 0x30E, 0x30F, 0x30E, 0x30F, 0x316, 0x317, 0x30C, 0x545, 0x54C,
    0x54D, 0x554, 0x555, 0x55C, 0x55D, 0x546, 0x547, 0x54E, 0x54F, 0x556, 0x557,
    0x55E, 0x55F, 0x561, 0x562, 0x000, 0x000, 0x000, 0x000, 0x563, 0x56C,
};

static s16 D_us_80181038[] = {
    0x53E, 0x53F, 0x53E, 0x53F, 0x53E, 0x53F, 0x53E, 0x53F, 0x540, 0x541, 0x548,
    0x549, 0x550, 0x551, 0x558, 0x559, 0x542, 0x543, 0x54A, 0x54B, 0x552, 0x553,
    0x55A, 0x55B, 0x564, 0x565, 0x000, 0x56D, 0x000, 0x575, 0x57C, 0x57D,
};

static u16 D_us_80181078[] = {0x560, 0x560, 0x560, 0x568, 0x569, 0x544};

static s32 D_us_80181084[] = {0x43, 0x4B, 0x50, 0x4F};

void EntityBreakableWall(Entity* self) {
    Entity* tempEntity;
    s32 tileIdx;
    s32 i;
    s32 castleFlag;
    s16* ptr;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x20;
        self->hitboxState = 2;
        if (!self->params) {
            castleFlag = NZ1_LOWER_WALL_OPEN;
        } else {
            castleFlag = NZ1_UPPER_WALL_OPEN;
        }
        if (g_CastleFlags[castleFlag]) {
            i = 0x18;
        } else {
            i = 0;
        }
        if (!self->params) {
            ptr = &D_us_80180FF8[i];
            tileIdx = 0x9A0;
        } else {
            ptr = &D_us_80181038[i];
            tileIdx = 0x6E;
        }
        for (i = 0; i < 4; i++, ptr += 2) {
            *(&g_Tilemap.fg[tileIdx] + 0) = ptr[0];
            *(&g_Tilemap.fg[tileIdx] + 1) = ptr[1];
            if (!self->params) {
                tileIdx += 0x70;
            } else {
                tileIdx += 0x10;
            }
        }
        if (g_CastleFlags[castleFlag]) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        self->ext.breakable.breakCount++;
        if (!self->params) {
            ptr = &D_us_80180FF8[self->ext.breakable.breakCount * 8];
            tileIdx = 0x9A0;
        } else {
            ptr = &D_us_80181038[self->ext.breakable.breakCount * 8];
            tileIdx = 0x6E;
        }
        for (i = 0; i < 4; i++, ptr += 2) {
            *(&g_Tilemap.fg[tileIdx] + 0) = ptr[0];
            *(&g_Tilemap.fg[tileIdx] + 1) = ptr[1];
            if (!self->params) {
                tileIdx += 0x70;
            } else {
                tileIdx += 0x10;
            }
        }
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 0x13;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step++;
        if (self->ext.breakable.breakCount == 3) {
            if (!self->params) {
                g_CastleFlags[NZ1_LOWER_WALL_OPEN] = 1;
                g_api.RevealSecretPassageAtPlayerPositionOnMap(
                    NZ1_LOWER_WALL_OPEN);
            } else {
                g_CastleFlags[NZ1_UPPER_WALL_OPEN] = 1;
                g_api.RevealSecretPassageAtPlayerPositionOnMap(
                    NZ1_UPPER_WALL_OPEN);
            }
            for (i = 0; i < 8; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SECRET_WALL_DEBRIS), self, tempEntity);
                    tempEntity->posX.i.hi += (Random() & 0xF);
                    tempEntity->posY.i.hi += (Random() & 0x3F) - 0x20;
                    tempEntity->params = self->params;
                }
            }
            DestroyEntity(self);
        }
        break;

    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
        }
        break;
    }
}

void EntityBreakableWallPartial(Entity* self) {
    Entity* tempEntity;
    s32 i;
    s32 tileX, tileY;
    s32 tileIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        if (g_CastleFlags[NZ1_STATUE_ROOM_BREAKABLE_WALLS] &
            (1 << self->params)) {
            tileX = self->posX.i.hi;
            tileY = self->posY.i.hi - 0x10;
            tileX += g_Tilemap.scrollX.i.hi;
            tileY += g_Tilemap.scrollY.i.hi;
            for (i = 0; i < 3; i++) {
                tileIdx =
                    (tileX >> 4) + ((tileY >> 4) * g_Tilemap.hSize * 0x10);
                g_Tilemap.fg[tileIdx] = D_us_80181078[i + 3];
                tileY += 0x10;
            }
            self->step = 0x10;
            return;
        }
        self->hitboxState = 2;
        self->hitPoints = 0x7FFF;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x18;
        /* fallthrough */
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        tileX = self->posX.i.hi;
        tileY = self->posY.i.hi - 0x10;
        tileX += g_Tilemap.scrollX.i.hi;
        tileY += g_Tilemap.scrollY.i.hi;
        for (i = 0; i < 3; i++) {
            tileIdx = (tileX >> 4) + ((tileY >> 4) * g_Tilemap.hSize * 0x10);
            g_Tilemap.fg[tileIdx] = D_us_80181078[i + 3];
            tileY += 0x10;
        }
        self->hitboxState = 0;
        tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, tempEntity);
            tempEntity->params = 0x13;
        }
        for (i = 0; i < 3; i++) {
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(
                    E_ID(SECRET_WALL_DEBRIS), self, tempEntity);
                tempEntity->posY.i.hi += (Random() & 0x1F) - 0x10;
                tempEntity->params = 1;
            }
        }
        g_CastleFlags[NZ1_STATUE_ROOM_BREAKABLE_WALLS] |= (1 << self->params);
        tempEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (tempEntity != NULL) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, tempEntity);
            tempEntity->params = D_us_80181084[self->params];
        }
        self->step++;
        break;
    }
}

void EntitySecretWallDebris(Entity* self) {
    Collider collider;
    Entity* tempEntity;
    s16 angle;
    s32 i;
    s32 speed;
    s32 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitEnvironment);
        self->drawFlags = ENTITY_ROTATE;
        self->animCurFrame = 8;
        speed = (Random() & 0x1F) + 0x10;
        if (self->params) {
            angle = ((Random() & 0x3F) * 0x10) + ROT(90);
        } else {
            angle = ((Random() & 0x3F) * 0x10) + ROT(270);
        }
        if (self->params & 0x10) {
            self->animCurFrame = 9;
            speed = (Random() & 0x1F) + 0x10;
            angle = (Random() * 6) + ROT(202.5);
        }
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }
        /* fallthrough */
    case 1:
        MoveEntity();
        self->rotate += 0x20;
        if (self->params) {
            self->rotate += 0x20;
        }
        self->velocityY += FIX(0.125);
        x = self->posX.i.hi;
        y = self->posY.i.hi + 6;
        g_api.CheckCollision(x, y, &collider, 0);
        if ((collider.effects & EFFECT_SOLID) == 0) {
            return;
        }
        self->posY.i.hi += collider.unk18;
        if (!(self->params & 0x10)) {
            for (i = 0; i < 2; i++) {
                tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (tempEntity != NULL) {
                    CreateEntityFromEntity(
                        E_ID(SECRET_WALL_DEBRIS), self, tempEntity);
                    tempEntity->params = 0x10;
                }
            }
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            DestroyEntity(self);
            return;
        }
        if (self->velocityY < FIX(0.5)) {
            PlaySfxPositional(SFX_EXPLODE_FAST_B);
            tempEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (tempEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, tempEntity);
                tempEntity->params = 0x10;
            }
            DestroyEntity(self);
            return;
        }
        self->velocityY = -self->velocityY * 2 / 3;
        break;
    }
}
