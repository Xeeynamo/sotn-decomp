// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

extern EInit g_EInitRTOPCommon;

// Simplified version of TOP's. This version doesn't support being manipulated
void EntityStairSwitch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 0;
        if (self->params != 0) {
            self->step = 4;
            self->zPriority += 2;
        } else {
            self->animCurFrame = 4;
            self->hitboxState = 0;
            self->palette++;
            g_Tilemap.fg[0x251B] = 0x328;
            self->step = 3;
        }
        break;
    }
}

void func_us_801A0BF4(Entity* self) {
    s32 i;
    s32 tilemapIndex;
    s32 offsetX;
    s32 offsetY;

    FntPrint("step %x\n", self->step);
    FntPrint("w_y %x\n", g_PlayerY);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);

        // cursed!
        *((volatile s16*)&self->animCurFrame) = 3;
        *((volatile s16*)&self->animCurFrame) = 0;
        self->zPriority += 2;
        self->step = 3;

        for (i = 0, tilemapIndex = 0x2724; i < 5; i++, tilemapIndex++) {
            g_Tilemap.fg[tilemapIndex] = 0x32E;
        }
        break;

    case 3:
        self->animCurFrame = 0;
        offsetX = LOH(PLAYER.posX.i.hi) + g_Tilemap.scrollX.i.hi;
        offsetY = LOH(PLAYER.posY.i.hi) + g_Tilemap.scrollY.i.hi;

        if (offsetX > 0x220 && offsetX < 0x2C0 && offsetY > 0x460 &&
            g_PlayerY >= 0x4DE) {
            g_Tilemap.height = 0x4FB;
            g_Tilemap.bottom = g_Tilemap.bottom - 3;
            self->step++;
        }
        break;
    }
}

static Point16 D_us_8018080C[] = {
    {0x0580, 0x0330},
    {0x0598, 0x0348},
    {0x05B0, 0x0360},
    {0x05C0, 0x0370}};
// This probably has some extra stuff at the end, but going with this for now
static u16 D_us_8018081C[] = {
    0x1956, 0x0645, 0x1957, 0x0646, 0x19D6, 0x0644, 0x19D7, 0x0643, 0x19D8, 0x0641, 0x1A57, 0x0642, 0x1A58, 0x0640, 0x1A59, 0x063B, 0x1AD8, 0x063F, 0x1AD9, 0x063C, 0x1ADA, 0x0639, 0x1B59, 0x063E, 0x1B5A, 0x063A, 0x1B5B, 0x0638, 0x1BDA, 0x063D, 0x1BDB, 0x0637, 0x1BDC, 0x0636, 0xFFFF, 0xFFFF, 0x1956, 0x0119, 0x1957, 0x0118, 0x19D6, 0x0002, 0x19D7, 0x0002, 0x19D8, 0x017F, 0x1A57, 0x0166, 0x1A58, 0x0187, 0x1A59, 0x0188, 0x1AD8, 0x018F, 0x1AD9, 0x0190, 0x1ADA, 0x0191, 0x1B59, 0x0198, 0x1B5A, 0x0199, 0x1B5B, 0x019A, 0x1BDA, 0x01A1, 0x1BDB, 0x01A2, 0x1BDC, 0x01A3, 0xFFFF, 0xFFFF, 0, 0x0008, 0, 0x0004, 0x0004, 0xFFFC, 0xFFF8, 0, 
};

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
        InitializeEntity(g_EInitRTOPCommon);
        self->animCurFrame = 1;
        if (!self->params) {
            self->ext.secretStairs.unk84 = 1;
            entity = self + 1;
            for (i = 0; i < 3; i++, entity++) {
                CreateEntityFromCurrentEntity(E_STAIR_SEGMENT, entity);
                entity->params = i + 1;
            }
        }
        if (self->params == 3) {
            self->animCurFrame = 2;
            self->zPriority++;
        }
        g_api.RevealSecretPassageAtPlayerPositionOnMap(RTOP_SECRET_STAIRS);
        posX = D_us_8018080C[self->params].x;
        posY = D_us_8018080C[self->params].y;
        self->posX.i.hi = 0x800 - posX - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0x800 - posY - g_Tilemap.scrollY.i.hi;
        self->step = 15;
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
        if (self->ext.secretStairs.unk84 == 0) {
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            if (self->params == 3) {
                self->posX.i.hi += 0x10;
                self->posY.i.hi += 0x10;
            }
        } else {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;
    case 4:

        posX = D_us_8018080C[self->params].x;
        posY = D_us_8018080C[self->params].y;
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
                    var_a1 = D_us_8018081C;
                    while (*var_a1 != 0xFFFF) {
                        g_Tilemap.fg[var_a1[0]] = var_a1[1];
                        var_a1 += 2;
                    }
                    var_a1 = D_us_8018081C;
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
static u16 D_us_801808BC[] = {0x0019, 0x001A, 0x001B, 0x0386, 0x0389, 0x001C};

void EntityBreakableWall(Entity* self) {
    s32 wallStatus;
    Entity* entity;
    s32 i;
    s16* wallTiles;
    s32 var_a1;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
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

        wallTiles = &D_us_801808BC[wallStatus];
        if (!self->params) {
            var_a1 = 0x1AE7;
        } else {
            var_a1 = 0xAE7;
        }
        for (i = 0; i < 3; i++, wallTiles++) {
            g_Tilemap.fg[var_a1] = *wallTiles;
            var_a1 -= 0x80;
        }
        if (wallStatus != 0) {
            DestroyEntity(self);
            break;
        }
        // fallthrough

    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
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
            wallTiles = &D_us_801808BC[3];
            if (!self->params) {
                var_a1 = 0x1AE7;
            } else {
                var_a1 = 0xAE7;
            }

            for (i = 0; i < 3; i++, wallTiles++) {
                g_Tilemap.fg[var_a1] = *wallTiles;
                var_a1 -= 0x80;
            }

            self->entityId = 0xC;
            self->pfnUpdate = EntityHeartDrop;
            self->step = 0;
            self->step_s = 0;
            self->pose = 0;
            self->poseTimer = 0;

            if (!self->params) {
                self->params = 1;
            } else {
                self->params = 0;
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

// odd +1 reference to D_us_80180CC6
static s16 D_us_801808C8[] = {-2, -1, -1, 0, 0, 1, 1, 2};

void EntityTriangleElevator(Entity* self) {
    Primitive* prim;
    s16 offsetY;
    s32 offsetX;
    s32 scrollY;
    s32 primIndex;
    s32 collision;
    u16 flags;
    Entity* player;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->animCurFrame = 0xD;
        self->hitboxState = 1;
        self->ext.topElevator.unk88 = 0;
        self->ext.topElevator.movingUp = self->params & 1;
        self->ext.topElevator.playerCollision = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;

        prim = &g_PrimBuf[primIndex];
        offsetX = self->posX.i.hi;
        scrollY = 0x139 - g_Tilemap.scrollY.i.hi;

        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0x30;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX + 4;
        prim->x1 = prim->x3 = offsetX - 4;
        prim->y0 = prim->y1 = scrollY + 4;
        prim->y2 = prim->y3 = scrollY - 4;
        prim->priority = 0x6C;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x47;
        prim->v0 = prim->v1 = 0x31;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX + 4;
        prim->x1 = prim->x3 = offsetX - 4;
        prim->y0 = prim->y1 = scrollY - 4;
        scrollY = 0x69 - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = scrollY + 4;
        prim->priority = 0x6C;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0x30;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX + 4;
        prim->x1 = prim->x3 = offsetX - 4;
        prim->y0 = prim->y1 = scrollY - 4;
        prim->y2 = prim->y3 = scrollY + 4;
        prim->priority = 0x6C;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        self->ext.topElevator.prim = prim;
        prim->tpage = 0xE;
        prim->clut = 0xD2;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x5F;
        prim->v0 = prim->v1 = 0x70;
        prim->v2 = prim->v3 = 0x7F;
        prim->priority = 0x6D;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;

        prim = prim->next;
        break;

    case 1:
        player = &PLAYER;

        if (self->ext.topElevator.mapPos.y < 0x69) {
            self->ext.topElevator.movingUp = true;
        }
        if (self->ext.topElevator.mapPos.y > 0x139) {
            self->ext.topElevator.movingUp = false;
        }
        if (self->ext.topElevator.movingUp) {
            self->velocityY = FIX(0.5);
        } else {
            self->velocityY = -FIX(0.5);
        }
        self->velocityX = 0;
        MoveEntity();
        self->ext.topElevator.unk88++;

        if (self->ext.topElevator.playerCollision & 4) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi -
                      self->ext.topElevator.mapPos.y;
            if ((offsetY > 0) ||
                ((offsetY < 0) &&
                 ((g_Player.vram_flag ^ TOUCHING_CEILING) & 2))) {
                player->posY.i.hi += offsetY;
                g_unkGraphicsStruct.shoveY.i.hi += offsetY;
            }
        }

        flags = 4;
        if (self->ext.topElevator.unk8A) {
            self->ext.topElevator.unk8A--;
            flags ^= 4;
        }

        if (self->ext.topElevator.unk80 & 0xF &&
            self->ext.topElevator.unk80 & 0xF0) {
            flags |= 0x10;
        }
        collision = GetPlayerCollisionWith(self, 0x10, 7, flags);

        if (self->ext.topElevator.unk80 & 0xF) {
            if (self->ext.topElevator.unk80 & 0xF0) {
                offsetY =
                    -D_us_801808C8[(self->ext.topElevator.unk80 & 0xF) - 1];
            } else {
                offsetY = D_us_801808C8[self->ext.topElevator.unk80 - 1];
            }
            self->posY.i.hi += offsetY;
            if (collision & 4) {
                player->posY.i.hi += offsetY;
                g_unkGraphicsStruct.shoveY.i.hi += offsetY;
            }
            self->ext.topElevator.unk80--;
        }

        if (collision & 4) {
            g_api.func_8010DFF0(0, 1);
            if (self->ext.topElevator.playerCollision ^ 4) {
                if (!(self->ext.topElevator.unk80 & 0xF)) {
                    if (HIH(player->velocityY) > 0) {
                        self->ext.topElevator.unk80 = 8;
                    }
                }
            }
        } else {
            if (self->ext.topElevator.playerCollision & 4) {
                self->ext.topElevator.unk8A = 8;
            }
        }
        if ((collision & 2) && !(self->ext.topElevator.unk80 & 0xF)) {
            self->ext.topElevator.unk80 = 0x18;
        }
        self->ext.topElevator.playerCollision = collision;
        break;
    }

    prim = self->ext.topElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi + 0x10;
    prim->x1 = prim->x3 = self->posX.i.hi - 0x10;
    prim->y0 = prim->y1 = self->posY.i.hi + 4;
    prim->y2 = prim->y3 = self->posY.i.hi - 0x1C;
    self->ext.topElevator.mapPos.x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.topElevator.mapPos.y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}

static u8 D_us_801808D8[][3] = {
    {153, 154, 155}, {156, 157, 158}, {159, 160, 161}, {162, 163, 164}, 
    {146, 147, 148}, {165, 166, 167}, {172, 173, 174}, {180, 181, 182}
};
// map pos y
extern s32 D_us_801B10D8;

// elevator
void func_us_801A1940(Entity* self) {
    Primitive* prim;
    Entity* player;
    s32 collision;
    s16 offsetY;
    s32 clutTarget;
    u8* var_a0;
    s32 i;
    s32 clutSource;
    s32 primIndex;
    s32 offsetY2;
    u16 flags;

    if (self->step) {
        D_us_801B10D8 = self->ext.topElevator.mapPos.y;
    } else {
        D_us_801B10D8 = 0x400;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->animCurFrame = 0xC;
        self->hitboxState = 1;
        self->ext.topElevator.unk88 = 0;
        self->ext.topElevator.movingUp = self->params & 1;
        self->posY.i.hi = 0x1AF - g_Tilemap.scrollY.i.hi;

        if (g_CastleFlags[TOP_LION_LIGHTS] & 1) {
            self->step = 2;
            self->step_s = 1;
            var_a0 = D_us_801808D8;
            for (i = 0; i < 8; i++) {
                clutTarget = var_a0[0];
                clutSource = var_a0[2];
                g_ClutIds[clutTarget] = g_ClutIds[clutSource];
                var_a0 += 3;
            }
        } else {
            self->step = 1;
        }
        self->ext.topElevator.playerCollision = 0;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.topElevator.prim = prim;
        prim->tpage = 0xE;
        prim->clut = 0xD2;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x5F;
        prim->v0 = prim->v1 = 0x70;
        prim->v2 = prim->v3 = 0x7F;
        prim->priority = 0x6D;
        prim->drawMode = DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        prim = prim->next;
        break;

    case 1:
        collision = GetPlayerCollisionWith(self, 0x10, 7, 4);
        switch (self->step_s) {
        case 0:
            if (collision & 4) {
                self->poseTimer = 1;
                self->pose = 0;
                self->step_s++;
            } else {
                self->pose = 0;
                self->poseTimer = 1;
            }
            // fallthrough

        case 1:
            if (!--self->poseTimer) {
                self->poseTimer = 6;
                var_a0 = (u8*)D_us_801808D8;
                for (i = 0; i < 8; i++) {
                    clutTarget = var_a0[0];
                    clutSource = var_a0[self->pose];
                    g_ClutIds[clutTarget] = g_ClutIds[clutSource];
                    var_a0 += 3;
                }
                self->pose++;
                if (self->pose > 2) {
                    self->step_s++;
                }
            }
            break;
        case 2:
            g_CastleFlags[TOP_LION_LIGHTS] = 1;
            self->velocityY = FIX(-0.5);
            self->ext.topElevator.unk8C = 0x28;
            SetStep(2);
            break;
        }
        break;

    case 2:
        player = &PLAYER;

        switch (self->step_s) {
        case 0:
            if (self->ext.topElevator.mapPos.y > 0x1AF) {
                self->ext.topElevator.movingUp = true;
                self->velocityY = 0;
                self->step_s++;
            }
            if (self->ext.topElevator.mapPos.y < 0xAF) {
                self->ext.topElevator.movingUp = false;
                self->velocityY = 0;
                D_us_801B10D8 = 0;
                self->step_s = 1;
            }
            break;

        case 1:
            offsetY2 = player->posY.i.hi + g_Tilemap.scrollY.i.hi;

            if (offsetY2 < 0x100) {
                offsetY = 0;
            } else {
                offsetY = 1;
            }

            if (g_Player.vram_flag == TOUCHING_GROUND &&
                ((offsetY) ^ self->ext.topElevator.movingUp)) {
                self->ext.topElevator.unk8C--;
            } else {
                self->ext.topElevator.unk8C = 0x40;
            }

            if (self->ext.topElevator.unk8C == 0 ||
                (self->ext.topElevator.playerCollision & 4)) {
                if (self->ext.topElevator.movingUp) {
                    self->velocityY = FIX(-0.5);
                } else {
                    self->velocityY = FIX(0.5);
                }
                self->step_s = 0;
            }
            break;
        }

        self->velocityX = 0;
        MoveEntity();
        self->ext.topElevator.unk88++;
        if (self->ext.topElevator.playerCollision & 4) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi -
                      self->ext.topElevator.mapPos.y;

            if ((offsetY > 0) ||
                ((offsetY < 0) &&
                 ((g_Player.vram_flag ^ TOUCHING_CEILING) & 2))) {
                player->posY.i.hi += offsetY;
                g_unkGraphicsStruct.shoveY.i.hi += offsetY;
            }
        }

        flags = 4;
        if (self->ext.topElevator.unk8A) {
            self->ext.topElevator.unk8A--;
            flags ^= 4;
        }

        if ((self->ext.topElevator.unk80 & 0xF) &&
            (self->ext.topElevator.unk80 & 0xF0)) {
            flags |= 0x10;
        }

        collision = GetPlayerCollisionWith(self, 0x10, 7, flags);
        if (self->ext.topElevator.unk80 & 0xF) {
            if (self->ext.topElevator.unk80 & 0xF0) {
                offsetY =
                    -D_us_801808C8[(self->ext.topElevator.unk80 & 0xF) - 1];
            } else {
                offsetY = D_us_801808C8[self->ext.topElevator.unk80 - 1];
            }
            self->posY.i.hi += offsetY;
            if (collision & 4) {
                player->posY.i.hi += offsetY;
                g_unkGraphicsStruct.shoveY.i.hi += offsetY;
            }
            self->ext.topElevator.unk80--;
        }

        if (collision & 4) {
            g_api.func_8010DFF0(0, 1);
            if (self->ext.topElevator.playerCollision ^ 4) {
                if (!(self->ext.topElevator.unk80 & 0xF)) {
                    if (HIH(player->velocityY) > 0) {
                        self->ext.topElevator.unk80 = 8;
                    }
                }
            }
        } else {
            if (self->ext.topElevator.playerCollision & 4) {
                self->ext.topElevator.unk8A = 8;
            }
        }
        if (collision & 2 && !(self->ext.topElevator.unk80 & 0xF)) {
            self->ext.topElevator.unk80 = 0x18;
        }
        self->ext.topElevator.playerCollision = collision;
        break;
    }

    if (collision) {
        if ((g_Timer % 6) == 0) {
            self->palette++;
        }
    } else if ((g_Timer % 8) == 0) {
        self->palette++;
    }
    if (self->palette > 8) {
        self->palette = 0;
    }

    self->ext.topElevator.mapPos.x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.topElevator.mapPos.y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
    prim = self->ext.topElevator.prim;
    prim->x0 = prim->x2 = self->posX.i.hi - 16;
    prim->x1 = prim->x3 = self->posX.i.hi + 16;
    prim->y0 = prim->y1 = self->posY.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi + 24;
}

static u8 LionLampAnim[] = {3, 6, 3, 7, 3, 8, 3, 9, 3, 10, 0};

void EntityLionLamp(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->zPriority = 0x58;
        // fallthrough

    case 1:
        AnimateEntity(LionLampAnim, self);
        if (g_Timer & 1) {
            self->palette = 0;
        } else {
            self->palette = 1;
        }
        break;

    case 0xFF:
        FntPrint("charal %x\n", self->animCurFrame);
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params) {
                return;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }

        if (g_pads[1].pressed & PAD_CIRCLE) {
            if (self->step_s == 0) {
                self->animCurFrame--;
                self->step_s |= 1;
            }
        } else {
            self->step_s = 0;
        }
        break;
    }
}

static u8 D_us_801808FC[] = {146, 149, 150, 151, 152, 165, 168, 169, 170, 171, 172, 175, 176, 177, 178, 180, 183, 184, 185, 186};

void func_us_801A21F8(Entity* self) {
    u8* lookup;
    s32 writeIndex;
    s32 readIndex;
    s32 offsetY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->animSet = 7;
        self->animCurFrame = 3;
        self->zPriority = 0x5C;
        self->palette = PAL_FLAG(PAL_FILL_BLACK);
        if (g_CastleFlags[TOP_LION_LIGHTS] & (1 << (self->params + 2))) {
            self->step = 3;
        }
        break;

    case 1:
        if (g_CastleFlags[TOP_LION_LIGHTS]) {
            offsetY = self->posY.i.hi + g_Tilemap.scrollY.i.hi + 0x20;
            if (offsetY > D_us_801B10D8) {
                g_CastleFlags[TOP_LION_LIGHTS] |= 1 << (self->params + 2);
                SetStep(3);
            }
        }
        break;

    case 3:
        self->animSet = PAL_FLAG(1);
        self->animCurFrame = 0xB;
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->palette = 0;
        self->zPriority = 0x70;
        self->step++;
        // fallthrough

    case 4:
        if (g_Timer & 2) {
            self->palette = 0;
        } else {
            self->palette = 1;
        }

        if (!self->poseTimer) {
            self->poseTimer = 4;
            lookup = D_us_801808FC;
            lookup += self->params * 5;

            writeIndex = lookup[0];
            // cursed composition!
            readIndex = self->pose;
            readIndex = lookup[readIndex];
            g_ClutIds[writeIndex] = g_ClutIds[readIndex];
            self->pose++;
            if (self->pose > 3) {
                self->pose = 0;
            }
        } else {
            self->poseTimer--;
        }
        break;
    }
}

// n.b.! unused
#include "../e_trigger_before_castle_warp.h"
