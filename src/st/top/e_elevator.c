// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"
#include "sfx.h"

extern EInit g_EInitTOPCommon;

static s16 y_offsets[] = {-2, -1, -1, 0, 0, 1, 1, 2};

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
        InitializeEntity(g_EInitTOPCommon);
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
        scrollY = 0xC7 - g_Tilemap.scrollY.i.hi;

        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0x30;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX - 4;
        prim->x1 = prim->x3 = offsetX + 4;
        prim->y0 = prim->y1 = scrollY - 4;
        prim->y2 = prim->y3 = scrollY + 4;
        prim->priority = 0x6C;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x47;
        prim->v0 = prim->v1 = 0x31;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX - 4;
        prim->x1 = prim->x3 = offsetX + 4;
        prim->y0 = prim->y1 = scrollY + 4;
        scrollY = 0x197 - g_Tilemap.scrollY.i.hi;
        prim->y2 = prim->y3 = scrollY - 4;
        prim->priority = 0x6C;
        prim->drawMode = DRAW_UNK02;

        prim = prim->next;
        prim->tpage = 0xE;
        prim->clut = 0xD1;
        prim->u0 = prim->u2 = 0x38;
        prim->u1 = prim->u3 = 0x3F;
        prim->v0 = prim->v1 = 0x30;
        prim->v2 = prim->v3 = 0x36;
        prim->x0 = prim->x2 = offsetX - 4;
        prim->x1 = prim->x3 = offsetX + 4;
        prim->y0 = prim->y1 = scrollY + 4;
        prim->y2 = prim->y3 = scrollY - 4;
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

        if (self->ext.topElevator.mapPos.y > 0x197) {
            self->ext.topElevator.movingUp = true;
        }
        if (self->ext.topElevator.mapPos.y < 0xC7) {
            self->ext.topElevator.movingUp = false;
        }
        if (self->ext.topElevator.movingUp) {
            self->velocityY = -FIX(0.5);
        } else {
            self->velocityY = FIX(0.5);
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
                offsetY = -y_offsets[(self->ext.topElevator.unk80 & 0xF) - 1];
            } else {
                offsetY = y_offsets[self->ext.topElevator.unk80 - 1];
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
    prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
    prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
    prim->y0 = prim->y1 = self->posY.i.hi - 4;
    prim->y2 = prim->y3 = self->posY.i.hi + 0x1C;
    self->ext.topElevator.mapPos.x = self->posX.i.hi + g_Tilemap.scrollX.i.hi;
    self->ext.topElevator.mapPos.y = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
}

static u8 clut_ids[][3] = {
    {0x99, 0x9A, 0x9B}, {0x9C, 0x9D, 0x9E}, {0x9F, 0xA0, 0xA1},
    {0xA2, 0xA3, 0xA4}, {0x92, 0x93, 0x94}, {0xA5, 0xA6, 0xA7},
    {0xAC, 0xAD, 0xAE}, {0xB4, 0xB5, 0xB6},
};
// map pos y
extern s32 D_us_801BC514;

// elevator
void func_us_801AABA4(Entity* self) {
    Primitive* prim;
    Entity* player;
    s32 collision;
    s16 offsetY;
    u8* var_s1;
    s32 i;
    s32 clutTarget;
    s32 clutSource;
    s32 primIndex;
    s32 offsetY2;
    u16 flags;

    if (self->step) {
        D_us_801BC514 = self->ext.topElevator.mapPos.y;
    } else {
        D_us_801BC514 = 0x400;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitTOPCommon);
        self->animCurFrame = 0xC;
        self->hitboxState = 1;
        self->ext.topElevator.unk88 = 0;
        self->ext.topElevator.movingUp = self->params & 1;
        self->posY.i.hi = 0x1AF - g_Tilemap.scrollY.i.hi;

        if (g_CastleFlags[TOP_LION_LIGHTS] & 1) {
            self->step = 2;
            self->step_s = 1;
            var_s1 = clut_ids[0];
            for (i = 0; i < 8; i++) {
                clutTarget = var_s1[0];
                clutSource = var_s1[2];
                g_ClutIds[clutTarget] = g_ClutIds[clutSource];
                var_s1 += 3;
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
                var_s1 = clut_ids[0];
                for (i = 0; i < 8; i++) {
                    clutTarget = var_s1[0];
                    clutSource = self->pose;
                    clutSource = var_s1[clutSource];
                    g_ClutIds[clutTarget] = g_ClutIds[clutSource];
                    var_s1 += 3;
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
                D_us_801BC514 = 0;
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
                offsetY = -y_offsets[(self->ext.topElevator.unk80 & 0xF) - 1];
            } else {
                offsetY = y_offsets[self->ext.topElevator.unk80 - 1];
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
    prim->x0 = prim->x2 = self->posX.i.hi - 0x10;
    prim->x1 = prim->x3 = self->posX.i.hi + 0x10;
    prim->y0 = prim->y1 = self->posY.i.hi + 8;
    prim->y2 = prim->y3 = self->posY.i.hi + 0x18;
}
