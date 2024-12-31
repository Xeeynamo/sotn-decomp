// SPDX-License-Identifier: AGPL-3.0-or-later
#include "sfx.h"

#ifndef MAGICALLY_SEALED_DOOR_PALETTE
#define MAGICALLY_SEALED_DOOR_PALETTE 0x233
#endif

#ifndef MAGICALLY_SEALED_DOOR_CLUT
#define MAGICALLY_SEALED_DOOR_CLUT MAGICALLY_SEALED_DOOR_PALETTE - 1
#endif

static u8 g_eBlueDoorUV[][8] = {
    {0x03, 0x0D, 0x03, 0x0D, 0x03, 0x03, 0x45, 0x45},
    {0x13, 0x3D, 0x13, 0x3D, 0x03, 0x03, 0x45, 0x45},
    {0x3D, 0x13, 0x3D, 0x13, 0x03, 0x03, 0x45, 0x45}};

static u16 g_eBlueDoorTiles[][8] = {
    {0x597, 0x597, 0x597, 0x597, 0x000, 0x000, 0x000, 0x000},
    {0x130, 0x138, 0x1C0, 0x1C5, 0x130, 0x138, 0x1C0, 0x1C5},
    {0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000},
    {0x597, 0x597, 0x597, 0x597, 0x000, 0x000, 0x000, 0x000}};

// NZ0 has an extra .word in data vs NO0
static char D_80182710[] = {
    0x7C, 0x0E, 'M', 'a', 'g', 'i',  'c',  'a',  'l',  'l',  'y', ' ', 's',
    'e',  'a',  'l', 'e', 'd', 0x81, 0x44, 0x00, 0x00, 0x00, 0x00
#if defined(STAGE_IS_NO0)
};
#else
    , 0x00, 0x00, 0x00, 0x00 };
#endif

static s32 MagicallySealedDoorIsNearPlayer(Entity* e) {
    s16 diff = PLAYER.posX.i.hi - e->posX.i.hi;

    diff = abs(diff);

    if (diff >= 25) {
        return 0;
    } else {
        diff = PLAYER.posY.i.hi - e->posY.i.hi;
        diff = abs(diff);
        if (diff < 33) {
            return 1;
        } else {
            return 0;
        }
    }
    return diff;
}

// sealed door that displays "Magically Sealed" prompt
void EntityMagicallySealedDoor(Entity* self) {
    Entity* messageBox;
    Primitive* prim;
    s32 i;
    s16 angle;
    u8* uv;
    s16 x;
    s16 y;
    u8 sp3F;
    s16 endX;
    s16 scrollX;
    s16 scrollY;
    s32 tileIdx;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCommon);
        self->animSet = 0;
        self->animCurFrame = 1;
        self->zPriority = PLAYER.zPriority - 0x20;
        self->palette = MAGICALLY_SEALED_DOOR_PALETTE;
        self->facingLeft = 0;
        self->posY.i.hi += 0x1F;

        if (self->params & 0x100) {
            self->ext.magicallySealedDoor.unk86 = -4;
        } else {
            self->ext.magicallySealedDoor.unk86 = 4;
        }
        self->posX.i.hi += self->ext.magicallySealedDoor.unk86;
        self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 4);
        if (self->primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        uv = g_eBlueDoorUV;
        prim = &g_PrimBuf[self->primIndex];
        y = self->posY.i.hi - 0x1F;
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim->next != NULL; i++,
            prim = prim->next, uv += 8) {
            prim->u0 = uv[0];
            prim->u1 = uv[1];
            prim->u2 = uv[2];
            prim->u3 = uv[3];
            prim->v0 = uv[4];
            prim->v1 = uv[5];
            prim->v2 = uv[6];
            prim->v3 = uv[7];
            prim->tpage = 0x15;
            prim->clut = MAGICALLY_SEALED_DOOR_CLUT;
            prim->priority = PLAYER.zPriority - 0x20;
            prim->y0 = prim->y1 = y;
            prim->y2 = prim->y3 = y + 62;
            if (i == 0) {
                prim->y0 = prim->y1 = y;
                prim->y2 = prim->y3 = y + 62;
            }
            prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            prim->r0 = prim->b0 = prim->g0 = 0x7F;
            LOW(prim->r1) = LOW(prim->r0);
            LOW(prim->r2) = LOW(prim->r0);
            LOW(prim->r3) = LOW(prim->r0);
            if (i == 2 && !(self->params & 0x100)) {
                prim->drawMode |= DRAW_HIDE;
            }
            if (i == 1 && (self->params & 0x100)) {
                prim->drawMode |= DRAW_HIDE;
            }
        }
        prim->tpage = 0x15;
        prim->clut = self->palette;
        prim->u0 = prim->u2 = 0x40;
        prim->u1 = prim->u3 = 0x50;
        prim->v0 = prim->v1 = 0;
        prim->v2 = prim->v3 = 0x48;
        prim->x0 = prim->x2 = self->posX.i.hi - 8;
        prim->x1 = prim->x3 = self->posX.i.hi + 8;
        prim->y0 = prim->y1 = self->posY.i.hi - 0x24;
        prim->y2 = prim->y3 = self->posY.i.hi + 0x24;
        prim->priority = 0xAA;
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
        if (MagicallySealedDoorIsNearPlayer(self)) {
            if (!(self->params & 0x100)) {
                self->ext.magicallySealedDoor.angle = 0x1000;
            }
            if (self->params & 0x100) {
                self->ext.magicallySealedDoor.angle = 0x800;
            }
            g_Player.D_80072EFC = 0x18;
            PLAYER.velocityY = 0;
            g_Player.padSim = 0;
            self->animCurFrame = 0;
            self->step = 4;
            break;
        }
    case 1:
        GetPlayerCollisionWith(self, 8, 32, 5);
        self->ext.magicallySealedDoor.angle = 0xC00;
        for (prim = &g_PrimBuf[self->primIndex], i = 0; prim->next != NULL; i++,
            prim = prim->next) {
            if (i != 0) {
                prim->drawMode |= DRAW_HIDE;
            } else {
                prim->drawMode = DRAW_COLORS | DRAW_UNK02;
            }
        }
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;

        if (!(((PLAYER.facingLeft != GetSideToPlayer()) & 1) ^ 1) &&
            ((PLAYER.step == 0x19 && g_PlayableCharacter) ||
             PLAYER.step == 1) &&
            MagicallySealedDoorIsNearPlayer(self)) {
            // If player does not have the jewel, show the box.
            if (!(g_Status.relics[RELIC_JEWEL_OF_OPEN] & RELIC_FLAG_ACTIVE)) {
                if (self->ext.magicallySealedDoor.showedMessage) {
                    break;
                }
                messageBox = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (messageBox == NULL) {
                    break;
                }
                self->ext.magicallySealedDoor.showedMessage = 1;
                CreateEntityFromCurrentEntity(E_SAVE_GAME_POPUP, messageBox);
                messageBox->posX.i.hi = 0x80;
                messageBox->posY.i.hi = 0xB0;
                messageBox->ext.messageBox.label = D_80182710;
                break;
            }

            for (prim = &g_PrimBuf[self->primIndex], i = 0; prim != NULL; i++,
                prim = prim->next) {
                if (i == 1 && !(self->params & 0x100)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 2 && (self->params & 0x100)) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
                if (i == 0) {
                    prim->drawMode &= ~DRAW_HIDE;
                }
            }
            self->animCurFrame = 0;
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 2;
            self->ext.magicallySealedDoor.sideToPlayer =
                (GetSideToPlayer() & 1) ^ 1;
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;
    case 2:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x18;
        if (!(self->params & 0x100)) {
            self->ext.magicallySealedDoor.angle += 0x20;
            if (self->ext.magicallySealedDoor.angle >= 0x1000) {
                self->ext.magicallySealedDoor.angle = 0x1000;
            }
            if (self->ext.magicallySealedDoor.angle == 0x1000) {
                self->step++;
            }
        } else {
            self->ext.magicallySealedDoor.angle -= 0x20;
            if (self->ext.magicallySealedDoor.angle <= 0x800) {
                self->ext.magicallySealedDoor.angle = 0x800;
            }
            if (self->ext.magicallySealedDoor.angle == 0x800) {
                self->step++;
            }
        }
        break;
    case 3:
        if (g_Player.D_80072EFC >= 4) {
            return;
        }
        if (self->ext.magicallySealedDoor.sideToPlayer != 0) {
            g_Player.padSim = PAD_LEFT;
        } else {
            g_Player.padSim = PAD_RIGHT;
        }
        g_Player.D_80072EFC = 3;
        self->step++;
        break;
    case 4:
        if (self->ext.magicallySealedDoor.sideToPlayer == 0) {
            g_Player.padSim = PAD_RIGHT;
        } else {
            g_Player.padSim = PAD_LEFT;
        }
        g_Player.D_80072EFC = 4;
        if (MagicallySealedDoorIsNearPlayer(self) == 0) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
            g_Player.D_80072EFC = 0;
        }
        break;
    case 5:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 4;
        if (!(self->params & 0x100)) {
            self->ext.magicallySealedDoor.angle -= 0x20;
            if (self->ext.magicallySealedDoor.angle < 0xC01) {
                self->ext.magicallySealedDoor.angle = 0xC00;
            }
        } else {
            self->ext.magicallySealedDoor.angle += 0x20;
            if (self->ext.magicallySealedDoor.angle >= 0xC00) {
                self->ext.magicallySealedDoor.angle = 0xC00;
            }
        }
        if (self->ext.magicallySealedDoor.angle == 0xC00) {
            prim = &g_PrimBuf[self->primIndex];
            for (i = 0; prim != NULL; i++, prim = prim->next) {
                if (!(self->params & 0x1000) || (i != 0)) {
                    prim->drawMode |= DRAW_HIDE;
                }
            }
            self->animCurFrame = 1;
            self->step = 1;
        }
        break;
    }

    if (self->step != 1) {
        g_api.func_8010E168(1, 0x20);
        g_api.func_8010DFF0(1, 1);
    }

    x = self->posX.i.hi - self->ext.magicallySealedDoor.unk86;
    if (self->params & 0x100) {
        x--;
    } else {
        x++;
    }

    angle = self->ext.magicallySealedDoor.angle;
    prim = &g_PrimBuf[self->primIndex];
    for (i = 0; prim->next != NULL; i++, prim = prim->next) {
        if (!(prim->drawMode & DRAW_HIDE)) {
            if (!(self->params & 0x100)) {
                if (i == 0) {
                    endX = prim->x0 = prim->x2 =
                        x + ((rcos(angle) >> 8) * 32 >> 4);
                    prim->x1 = prim->x3 =
                        prim->x0 - ((rsin(angle) >> 4) * 6 >> 8);
                    if (angle > 0xF80) {
                        prim->x1 = prim->x3 = prim->x0 + 1;
                    }
                    if (angle > 0xE00) {
                        prim->u0 = prim->u2 = 4;
                        prim->u1 = prim->u3 = 12;
                    }
                    if (angle <= 0xE00) {
                        prim->u0 = prim->u2 = 3;
                        prim->u1 = prim->u3 = 13;
                    }
                    if (angle == 0x1000) {
                        prim->r1 = prim->b1 = prim->g1 = 63;
                        prim->r3 = prim->b3 = prim->g3 = 63;
                    } else {
                        prim->r1 = prim->b1 = prim->g1 =
                            0x7F - ((angle & 0x3FF) >> 4);
                        prim->r3 = prim->b3 = prim->g3 =
                            0x7F - ((angle & 0x3FF) >> 4);
                    }
                } else {
                    prim->x0 = prim->x2 = x;
                    prim->x1 = prim->x3 = endX;
                    if (angle == 0x1000) {
                        prim->r0 = prim->b0 = prim->g0 = 63;
                        prim->r2 = prim->b2 = prim->g2 = 63;
                    } else {
                        prim->r0 = prim->b0 = prim->g0 = (angle & 0x3FF) >> 4;
                        prim->r2 = prim->b2 = prim->g2 = (angle & 0x3FF) >> 4;
                    }
                }
            } else {
                if (i == 0) {
                    endX = prim->x1 = prim->x3 =
                        x + ((rcos(angle) >> 8) * 32 >> 4);
                    prim->x0 = prim->x2 =
                        prim->x1 + (((rsin(angle) >> 4) * 6) >> 8);
                    if (angle < 0x880) {
                        prim->x0 = prim->x2 = prim->x1 - 1;
                    }
                    if (angle < 0xA00) {
                        prim->u0 = prim->u2 = 4;
                        prim->u1 = prim->u3 = 12;
                    }
                    if (angle > 0xA00) {
                        prim->u0 = prim->u2 = 3;
                        prim->u1 = prim->u3 = 13;
                    }
                    if (angle == 0x800) {
                        prim->r0 = prim->b0 = prim->g0 = 127;
                        prim->r2 = prim->b2 = prim->g2 = 127;
                    } else {
                        prim->r0 = prim->b0 = prim->g0 =
                            63 + ((angle & 0x3FF) >> 4);
                        prim->r2 = prim->b2 = prim->g2 =
                            63 + ((angle & 0x3FF) >> 4);
                    }
                } else {
                    prim->x0 = prim->x2 = endX - 1;
                    prim->x1 = prim->x3 = x;
                    if (angle == 0x800) {
                        prim->r1 = prim->b1 = prim->g1 = 63;
                        prim->r3 = prim->b3 = prim->g3 = 63;
                    } else {
                        prim->r1 = prim->b1 = prim->g1 =
                            63 - ((angle & 0x3FF) >> 4);
                        prim->r3 = prim->b3 = prim->g3 =
                            63 - ((angle & 0x3FF) >> 4);
                    }
                }
            }
        }
    }

    if (self->animCurFrame == 0) {
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
    } else {
        prim->drawMode = DRAW_TPAGE2 | DRAW_TPAGE | DRAW_UNK02 | DRAW_TRANSP;
    }
    prim->clut = self->palette;
    self->ext.magicallySealedDoor.unk82 += 0x20;
    if (self->ext.magicallySealedDoor.unk82 >= 0x381) {
        self->ext.magicallySealedDoor.unk82 =
            -self->ext.magicallySealedDoor.unk82;
    }

    self->palette = (abs(self->ext.magicallySealedDoor.unk82) >> 8) +
                    MAGICALLY_SEALED_DOOR_PALETTE;

    sp3F = self->params & 0xFF;
    if (self->animCurFrame) {
        for (i = 0; i < 4; i++) {
            x = self->posX.i.hi;
            y = self->posY.i.hi - 24 + i * 0x10;
            scrollX = x + g_Tilemap.scrollX.i.hi;
            scrollY = y + g_Tilemap.scrollY.i.hi;
            tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
            g_Tilemap.fg[tileIdx] = g_eBlueDoorTiles[sp3F][i];
        }
    } else {
        for (i = 0; i < 4; i++) {
            x = self->posX.i.hi;
            y = self->posY.i.hi - 24 + i * 0x10;
            scrollX = x + g_Tilemap.scrollX.i.hi;
            scrollY = y + g_Tilemap.scrollY.i.hi;
            tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
            g_Tilemap.fg[tileIdx] = g_eBlueDoorTiles[sp3F][i + 4];
        }
    }
}
