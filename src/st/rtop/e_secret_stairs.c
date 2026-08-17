// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"

extern EInit g_EInitRTOPCommon;
#ifdef VERSION_PSP
extern s32 E_ID(STAIR_SEGMENT);
#endif

static Point16 D_us_8018080C[] = {
    {0x0580, 0x0330},
    {0x0598, 0x0348},
    {0x05B0, 0x0360},
    {0x05C0, 0x0370},
};

// g_Tilemap.fg[i0] = i1
static u16 D_us_8018081C[][2] = {
    {0x1956, 0x0645}, {0x1957, 0x0646}, {0x19D6, 0x0644}, {0x19D7, 0x0643},
    {0x19D8, 0x0641}, {0x1A57, 0x0642}, {0x1A58, 0x0640}, {0x1A59, 0x063B},
    {0x1AD8, 0x063F}, {0x1AD9, 0x063C}, {0x1ADA, 0x0639}, {0x1B59, 0x063E},
    {0x1B5A, 0x063A}, {0x1B5B, 0x0638}, {0x1BDA, 0x063D}, {0x1BDB, 0x0637},
    {0x1BDC, 0x0636}, {0xFFFF, 0xFFFF},
};

// These are remnants from TOP's closed stairs and switch collider
// but go unused here. Stripped on PSP.
static u16 unused_1[][2] = {
    {0x1956, 0x0119}, {0x1957, 0x0118}, {0x19D6, 0x0002}, {0x19D7, 0x0002},
    {0x19D8, 0x017F}, {0x1A57, 0x0166}, {0x1A58, 0x0187}, {0x1A59, 0x0188},
    {0x1AD8, 0x018F}, {0x1AD9, 0x0190}, {0x1ADA, 0x0191}, {0x1B59, 0x0198},
    {0x1B5A, 0x0199}, {0x1B5B, 0x019A}, {0x1BDA, 0x01A1}, {0x1BDB, 0x01A2},
    {0x1BDC, 0x01A3}, {0xFFFF, 0xFFFF},
};

static s16 unused_2[] = {
    0, 8, 0, 4, 4, -4, -8, 0,
};

// Simplified version of TOP's. This version doesn't support being manipulated
void EntityStairSwitch(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 0;
        if (self->params) {
            self->step = 4;
            self->zPriority += 2;
        } else {
            self->animCurFrame = 4;
            self->palette++;
            self->hitboxState = 0;
            g_Tilemap.fg[0x251B] = 0x328;
            self->step = 3;
        }
        break;
    case 3:
        break;
    }
}

void func_us_801A0BF4(Entity* self) {
    s32 i;
    s32 tilemapIndex;
    s32 offsetX;
    s32 offsetY;
    Entity* player;

    FntPrint("step %x\n", self->step);
    FntPrint("w_y %x\n", g_PlayerY);
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitRTOPCommon);

        self->animCurFrame = 3;
        self->zPriority += 2;
        self->animCurFrame = 0;
        self->step = 3;

        for (tilemapIndex = 0x2724, i = 0; i < 5; i++, tilemapIndex++) {
            g_Tilemap.fg[tilemapIndex] = 0x32E;
        }
        break;

    case 3:
        self->animCurFrame = 0;
        player = &PLAYER;
        offsetX = LOH(player->posX.i.hi) + g_Tilemap.scrollX.i.hi;
        offsetY = LOH(player->posY.i.hi) + g_Tilemap.scrollY.i.hi;

        if (offsetX > 0x220 && offsetX < 0x2C0 && offsetY > 0x460 &&
            g_PlayerY > 0x4DD) {
            g_Tilemap.height = 0x4FB;
            g_Tilemap.bottom = g_Tilemap.bottom - 3;
            self->step++;
        }
        break;
    }
}

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
                CreateEntityFromCurrentEntity(E_ID(STAIR_SEGMENT), entity);
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
        if (self->ext.secretStairs.unk84) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        } else {
            entity = self - 1;
            self->posX.i.hi = entity->posX.i.hi;
            self->posY.i.hi = entity->posY.i.hi;
            if (self->params == 3) {
                self->posX.i.hi += 0x10;
                self->posY.i.hi += 0x10;
            }
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
                    var_a1 = *D_us_8018081C;
                    while (*var_a1 != 0xFFFF) {
                        g_Tilemap.fg[var_a1[0]] = var_a1[1];
                        var_a1 += 2;
                    }
                    var_a1 = *D_us_8018081C;
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
