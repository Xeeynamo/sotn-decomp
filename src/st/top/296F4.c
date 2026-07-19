// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "sfx.h"

extern EInit g_EInitTOPCommon;
extern u16 D_us_80180CAC[];

void EntityStairSwitch(Entity* self) {
    Entity* entity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 2;
        if (self->params != 0) {
            self->step = 4;
            self->zPriority += 2;
        } else if (g_CastleFlags[TOP_SECRET_STAIRS]) {
            self->animCurFrame = 4;
            self->hitboxState = 0;
            self->palette++;
            g_Tilemap.fg[0x1AE4] = 0x328;
            self->step = 3;
        } else {
            g_Tilemap.fg[0x1AE4] = 0x327;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            g_Tilemap.fg[0x1AE4] = 0x328;
            self->animCurFrame = 4;
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_STAIR_SWITCH, self, entity);
                entity->params = 1;
            }
            self->step++;
        }
        break;

    case 2:
        if (self->hitFlags) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
            self->hitboxState = 0;
            self->palette++;
            g_CastleFlags[TOP_SECRET_STAIRS] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(TOP_SECRET_STAIRS);
            self->step++;
        }
        break;

    case 3:
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->drawFlags = ENTITY_OPACITY | ENTITY_ROTATE;
            self->opacity = 0x60;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;
            // fallthrough

        case 1:
            MoveEntity();
            self->rotate += 0x40;
            if (UnkCollisionFunc3(D_us_80180CAC) & 1) {
                self->step_s++;
            } else {
                self->velocityY -= FIX(0.125);
            }
            break;

        case 2:
            g_api.PlaySfx(SFX_EXPLODE_FAST_A);
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 0x11;
            }
            DestroyEntity(self);
            break;
        }
        break;
    }
}

void func_us_801A9CB8(Entity* self) {
    Entity* player;
    s32 i;
    s32 tilemapIndex;
    s32 offsetX;
    s32 offsetY;

    FntPrint("step %x\n", self->step);
    FntPrint("w_y %x\n", g_PlayerY);

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->animCurFrame = 3;
        self->zPriority += 2;

        if (g_CastleFlags[TOP_SECRET_STAIRS]) {
            self->animCurFrame = 0;
            self->step = 3;
            tilemapIndex = 0x18D7;
            for (i = 0; i < 5; i++, tilemapIndex++) {
                g_Tilemap.fg[tilemapIndex] = 0x32E;
            }
        } else {
            tilemapIndex = 0x18D7;
            for (i = 0; i < 5; i++, tilemapIndex++) {
                g_Tilemap.fg[tilemapIndex] = 0x1D;
            }
        }
        break;

    case 1:
        if (g_CastleFlags[TOP_SECRET_STAIRS]) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            tilemapIndex = 0x18D7;
            for (i = 0; i < 5; i++, tilemapIndex++) {
                g_Tilemap.fg[tilemapIndex] = 0x32E;
            }
            self->step++;
        }
        break;

    case 2:
        self->posY.val -= FIX(0.25);
        if (self->posY.i.hi < -0x10) {
            self->step++;
        }
        break;

    case 3:
        self->animCurFrame = 0;
        player = &PLAYER;
        offsetX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
        offsetY = player->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (offsetX > 0x550 && offsetX < 0x5D5 && offsetY < 0x380 &&
            g_PlayerY < 0x304) {
            g_Tilemap.y = 0x304;
            g_Tilemap.top += 3;
            g_PlayerY -= 0x300;
            self->step++;
        }
        break;
    }
}

extern Point16 D_us_80180C0C[];
extern u16 D_us_80180C1C;
extern u16 D_us_80180C64;

void EntitySecretStairs(Entity* self) {
    Entity* entity;
    s32 i;
    s32 posX;
    s32 posY;
    s32 offsetX;
    s32 offsetY;
    s16 angle;
    u16* var_a1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->animCurFrame = 1;
        if (!self->params) {
            self->ext.secretStairs.unk84 = 1;
            entity = self + 1;
            for (i = 0; i < 3; i++, entity++) {
                CreateEntityFromCurrentEntity(E_SECRET_STAIRS, entity);
                entity->params = i + 1;
            }
        } else {
            self->ext.secretStairs.unk84 = 0;
            if (self->params == 3) {
                self->animCurFrame = 2;
                self->zPriority++;

                if (!g_CastleFlags[TOP_SECRET_STAIRS]) {
                    var_a1 = &D_us_80180C64;
                } else {
                    var_a1 = &D_us_80180C1C;
                }

                while (*var_a1 != 0xFFFF) {
                    g_Tilemap.fg[var_a1[0]] = var_a1[1];
                    var_a1 += 2;
                }
            } else {
                self->zPriority -= self->params;
            }
        }

        if (g_CastleFlags[TOP_SECRET_STAIRS]) {
            posX = D_us_80180C0C[self->params].x;
            posY = D_us_80180C0C[self->params].y;
            self->posX.i.hi = posX - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = posY - g_Tilemap.scrollY.i.hi;
            self->step = 15;
        } else {
            self->drawFlags |= ENTITY_ROTATE;
            self->rotate = -FLT(1.0 / 8.0);
        }
        break;

    case 1:
        if (g_CastleFlags[TOP_SECRET_STAIRS]) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;

    case 2:
        self->rotate += 16;
        if (!self->rotate) {
            self->drawFlags = ENTITY_DEFAULT;
            self->step++;
        }
        break;

    case 3:
        if (self->ext.secretStairs.unk84) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        } else {
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            if (self->params == 3) {
                self->posX.i.hi += 16;
                self->posY.i.hi += 16;
            }
        }
        break;

    case 4:

        posX = D_us_80180C0C[self->params].x;
        posY = D_us_80180C0C[self->params].y;
        switch (self->step_s) {
        case 0:
            offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            posX -= offsetX;
            posY -= offsetY;

            angle = ratan2(posY, posX);
            self->velocityX = rcos(angle) * 0xC;
            self->velocityY = rsin(angle) * 0xC;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            offsetX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            offsetY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            if (posX == offsetX) {
                g_api.PlaySfx(SFX_DOOR_CLOSE_A);
                self->posX.i.hi = posX - g_Tilemap.scrollX.i.hi;
                self->posY.i.hi = posY - g_Tilemap.scrollY.i.hi;
                if (self->params != 3) {
                    entity = self + 1;
                    entity->ext.secretStairs.unk84 = 1;
                } else {
                    var_a1 = &D_us_80180C1C;
                    while (*var_a1 != 0xFFFF) {
                        g_Tilemap.fg[var_a1[0]] = var_a1[1];
                        var_a1 += 2;
                    }
                    var_a1 = &D_us_80180C1C;
                    while (*var_a1 != 0xFFFF) {
                        g_Tilemap.fg[var_a1[0]] = var_a1[1];
                        var_a1 += 2;
                    }
                }
                self->step++;
            }
            break;
        }
        break;
    }
}

// breakable wall behind leap stone or power of mist
extern s16 D_us_80180CBC[];
extern s16 D_us_80180CC2[];

void EntityBreakableWall(Entity* self) {
    s32 wallStatus;
    Entity* entity;
    s32 i;
    s16* wallTiles;
    s32 var_a1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->zPriority = 0x6A;
        self->animCurFrame = 0xF;
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x18;
        self->hitboxOffX = 8;
        self->hitboxOffY = 0;
        self->hitboxState = 2;
        if (!self->params) {
            if (g_CastleFlags[OVL_EXPORT(SECRET_WALL_1_BROKEN)]) {
                wallStatus = 3;
            } else {
                wallStatus = 0;
            }
        } else if (g_CastleFlags[OVL_EXPORT(SECRET_WALL_2_BROKEN])) {
            wallStatus = 3;
        } else {
            wallStatus = 0;
        }

        wallTiles = &D_us_80180CBC[wallStatus];
        if (!self->params) {
            var_a1 = 0x2518;
        } else {
            var_a1 = 0x3518;
        }
        for (i = 0; i < 3; i++, wallTiles++) {
            g_Tilemap.fg[var_a1] = *wallTiles;
            var_a1 += 0x80;
        }
        if (wallStatus != 0) {
            DestroyEntity(self);
            break;
        }
        // fallthrough

    case 1:
        if (self->hitFlags) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        self->ext.breakable.breakCount++;
        self->animCurFrame++;
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, entity);
            entity->params = 0x13;
            entity->zPriority = self->zPriority + 1;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step++;
        if (self->ext.breakable.breakCount == 3) {
            if (!self->params) {
                g_CastleFlags[OVL_EXPORT(SECRET_WALL_1_BROKEN)] = 1;
            } else {
                g_CastleFlags[OVL_EXPORT(SECRET_WALL_2_BROKEN)] = 1;
            }
            wallTiles = D_us_80180CC2;
            if (!self->params) {
                var_a1 = 0x2518;
            } else {
                var_a1 = 0x3518;
            }

            for (i = 0; i < 3; i++, wallTiles++) {
                g_Tilemap.fg[var_a1] = *wallTiles;
                var_a1 += 0x80;
            }

            self->entityId = 0xC;
            self->pfnUpdate = EntityHeartDrop;
            self->step = 0;
            self->step_s = 0;
            self->pose = 0;
            self->poseTimer = 0;

            if (!self->params) {
                // PrizeDrops[2] = Fire Mail
                self->params = 2;
            } else {
                // PrizeDrops[1] = Turkey
                self->params = 1;
            }
            // n.b.! odd return, but necessary for PSP
            return;
        }
        break;

    case 3:
        if (--self->ext.breakable.resetTimer == 0) {
            self->step = 1;
        }
        break;
    }
}
