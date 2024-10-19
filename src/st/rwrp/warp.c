// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "rwrp.h"
#include "common.h"
#include "sfx.h"

extern s32 D_80097408[];
extern s16 PLAYER_posY_i_hi;
s16 GetDistanceToPlayerX();

#define ImplicitGetDistanceToPlayerX ((int (*)())GetDistanceToPlayerX)

static u32 bg_color_angle[] = {
    0x0000, 0x0200, 0x0400, 0x0600, 0x0800, 0x0A00, 0x0C00, 0x0E00,
    0x1000, 0x1200, 0x1400, 0x1600, 0x1800, 0x1A00, 0x1C00, 0x1E00,
};

static u32 D_80180648 = 0;

static u32 unused[] = {
    0x00040000,
    0x00040000,
    0xFFFC0004,
    0x0000FFF8,
};

static WarpCoord WarpRoomCoords[] = {
    {0x30, 0x19}, {0x1C, 0x13}, {0x04, 0x2E}, {0x17, 0x33}, {0x1A, 0x2A},
};

static u16 unused1[] = {
    0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000,
    0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001, 0x0101,
};

// the room the player will be warping to
s32 DestinationWarpRoom;
// the amplitude of the current background phase
s32 WarpBackgroundAmplitiude;
// the phase used to calculate the background color
s32 WarpBackgroundPhase;
// the brightness of the background layer
s32 WarpBackgroundBrightness;

// Mask for all of the statuses where the UP button will
// be ignored when in warp position or on the warp platform
//
// Value: 0xC5CF3EF7
//
// n.b.! this value is also used in src/st/wrp/warp.c
// clang-format off
#define PLAYER_STATUS_READY_MASK                                                  \
    (                                                                            \
        /* 0xC0000000 */ PLAYER_STATUS_UNK80000000 | PLAYER_STATUS_UNK40000000 | \
        /* 0x05000000 */ PLAYER_STATUS_UNK4000000 | PLAYER_STATUS_AXEARMOR |     \
        /* 0x00C00000 */ PLAYER_STATUS_UNK800000 | PLAYER_STATUS_UNK400000 |     \
        /* 0x000F0000 */ PLAYER_STATUS_UNK80000 | PLAYER_STATUS_UNK40000 | PLAYER_STATUS_UNK20000 | PLAYER_STATUS_UNK10000 | \
        /* 0x00003000 */ PLAYER_STATUS_UNK2000 | PLAYER_STATUS_UNK1000 |         \
        /* 0x00000E00 */ PLAYER_STATUS_UNK800 | PLAYER_STATUS_UNK400 | PLAYER_STATUS_UNK200 | \
        /* 0x000000F0 */ PLAYER_STATUS_STONE | PLAYER_STATUS_UNK40 | PLAYER_STATUS_UNK_20 |  PLAYER_STATUS_UNK10 | \
        /* 0x00000007 */ PLAYER_STATUS_TRANSFORM                                 \
    )
// clang-format on

// Handles everything about the reverse warp room.
// It is responsible to spawn the colourful background, the stones on the
// ground and it always listen to the UP button. When the UP
// button is pressed, it raises the platform alucard is standing on,
// brights the screen and teleport the player. when the player arrives
// at the destination the platform is lowered
//
// step 0 - initialization                      -> step 0, step 6
// step 1 - wait for up button                  -> step 1, 2
// step 2 - raise platform for alucard          -> step 2, 3
// step 3 - move alucard to backgroudn and fade -> step 3, 4
// step 4 - fade room to white                  -> step 4, 5
// step 5 - perform the warp                    -> step 5, 0x80?!
// step 6 - start new room                      -> step 7
// step 7 - finalize warp fading                -> step 7, 8
// step 8 - lower platform for alucard          -> step 8, 1
void EntityRWarpRoom(Entity* self) {
    Primitive* prim;
    s32 primIndex;
    Entity* entity;
    WarpCoord* warpCoords;
    s32 i;
    s32 angle;
    s32 temp;
    s32 moveX;
    s32 moveY;
    s32 collision;

    FntPrint("step %x\n", self->step);
    collision = GetPlayerCollisionWith(self, 16, 8, 4);

    switch (self->step) {
    case 0:
        // Initialize all the objects in the warp room
        InitializeEntity(g_EInitSmallRocks);
        self->animCurFrame = 0x66;
        self->posX.i.hi = 0x80 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 0xC0 - g_Tilemap.scrollY.i.hi;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 24);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.warpRoom.primBg = prim;
        moveY = 0x70;
        moveX = 0x80;
        for (i = 0; i <= 15; i++) {
            angle = i << 8;
            prim->x0 = moveX + (((rcos(angle) >> 4) * 0x40) >> 8);
            prim->y0 = moveY - (((rsin(angle) >> 4) * 0x40) >> 8);
            prim->u0 = 0x20 + (((rcos(angle) >> 4) * 0x1E) >> 8);
            prim->v0 = 0xE0 - (((rsin(angle) >> 4) * 0x1E) >> 8);
            angle = (i + 1) << 8;
            prim->x1 = moveX + (((rcos(angle) >> 4) * 0x40) >> 8);
            prim->y1 = moveY - (((rsin(angle) >> 4) * 0x40) >> 8);
            prim->u1 = 0x20 + (((rcos(angle) >> 4) * 0x1E) >> 8);
            prim->v1 = 0xE0 - (((rsin(angle) >> 4) * 0x1E) >> 8);
            prim->y2 = prim->y3 = moveY;
            prim->x2 = prim->x3 = moveX;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->priority = 0x40;
            prim->drawMode = DRAW_UNK02 | DRAW_COLORS | DRAW_UNK_400;
            prim = prim->next;
        }

        self->ext.warpRoom.primFade = prim;
        prim->type = PRIM_TILE;
        prim->u0 = 64;
        prim->v0 = 80;
        prim->x0 = 96;
        prim->y0 = 56;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x60;
        prim->drawMode = DRAW_HIDE | DRAW_UNK02;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 256;
        prim->y0 = prim->y1 = 16;
        prim->y2 = prim->y3 = 240;
        prim->r0 = prim->g0 = prim->b0 = 0;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->priority = 0x1F0;
        prim->drawMode = DRAW_HIDE;

        WarpBackgroundAmplitiude = 0x100;
        g_CastleFlags[CASTLE_FLAG_209] |= 1 << self->params;
        D_80180648 = 0;
        moveX = PLAYER.posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (moveX > 0x60 && moveX < 0xA0) {
            self->posY.i.hi = 0x90 - g_Tilemap.scrollY.i.hi;
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x10;
            D_8003C8B8 = 0;
            D_80180648 = 1;
            self->step = 6;
            break;
        }
        // fallthrough
    case 1:
        // Wait for player to press the UP button
        if (collision & 0x4 && g_pads[0].pressed & PAD_UP &&
            ImplicitGetDistanceToPlayerX() < 8 &&
            !(g_Player.status & PLAYER_STATUS_READY_MASK)) {
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x80;
            PLAYER.velocityY = PLAYER.velocityX = D_8003C8B8 = 0;
            self->step++;
        }
        break;
    case 2:
        // raise alucard on the platform?
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        g_api.func_8010DFF0(0, 1);
        self->posY.i.hi--;
        moveY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (moveY < 0x91) {
            self->posY.i.hi = 0x90 - g_Tilemap.scrollY.i.hi;
            self->step++;
        }
        break;
    case 3:
        // Move Alucard in the background and fade him to white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x80;
        D_8003C8B8 = 0;
        g_unkGraphicsStruct.g_zEntityCenter = PLAYER.zPriority = 0x5C;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
        prim->g0 = prim->b0 = prim->r0 += 2;
        if (prim->r0 > 96) {
            D_80180648 = 1;
            g_api.PlaySfx(SFX_TELEPORT_BANG_B);
            self->step++;
        }
        break;
    case 4:
        // Fade the entire room into white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x80;
        D_8003C8B8 = 0;
        entity = &PLAYER;
        g_unkGraphicsStruct.g_zEntityCenter = entity->zPriority = 0x5C;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
        if (prim->r0 < 0xF0) {
            prim->g0 = prim->b0 = prim->r0 += 2;
        }
        prim = prim->next;
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
        if (prim->r0 < 0xF8) {
            prim->g0 = prim->b0 = prim->r0 += 2;
        } else {
            self->step++;
        }
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 5:
        // Perform the actual warp
        temp = self->params + 1;
        for (i = 0; i < LEN(WarpRoomCoords); i++, temp++) {
            if (temp > LEN(WarpRoomCoords) - 1) {
                temp = 0;
            }
            if (g_CastleFlags[CASTLE_FLAG_209] & (1 << temp)) {
                break;
            }
        }
        DestinationWarpRoom = temp;
        warpCoords = &WarpRoomCoords[temp];
        moveX = warpCoords->x - g_Tilemap.left;
        moveY = warpCoords->y - g_Tilemap.top;
        FntPrint("move_room%x\n", DestinationWarpRoom);
        FntPrint("for_x:%x y%x\n", warpCoords->x, warpCoords->y);
        FntPrint("move_x:%x y%x\n", moveX, moveY);
        PLAYER.posX.i.hi += moveX << 8;
        PLAYER.posY.i.hi += moveY << 8;
        self->step = 0x80;
        D_80097C98 = 2;
        break;
    case 6:
        // start in new room
        g_Player.D_80072EFC = 0x10;
        PLAYER.zPriority = 0x94;
        g_Player.padSim = 0;
        D_80097408[0] = 0x94;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = DRAW_HIDE;
        prim->g0 = prim->b0 = prim->r0 = 0;
        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0xF8;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode = DRAW_TRANSP | DRAW_TPAGE | DRAW_TPAGE2;
        g_api.g_pfn_800EA5AC(0, 0, 0, 0);
        self->step++;
        // fallthrough
    case 7:
        // Finalize warp by fading in from white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim = prim->next;
        temp = prim->r0;
        temp -= 4;
        if (temp < 0) {
            temp = 0;
            prim->drawMode = DRAW_HIDE;
            D_8003C8B8 = 1;
            self->step++;
        }
        if (temp < 0x28) {
            D_80180648 = 0;
        }
        prim->g0 = prim->b0 = prim->r0 = temp;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;
    case 8:
        // lower alucard up to the room?
        self->posY.i.hi++;
        if (collision & 0x4) {
            g_api.func_8010DFF0(0, 1);

            PLAYER_posY_i_hi += 1;
            D_80097488.y.i.hi += 1;

            if (g_pads[0].pressed & PAD_UP &&
                ImplicitGetDistanceToPlayerX() < 8 &&
                !(g_Player.status & PLAYER_STATUS_READY_MASK)) {
                g_Player.padSim = 0;
                g_Player.D_80072EFC = 0x80;
                D_8003C8B8 = 0;
                self->step = 2;
            }
        }

        moveY = self->posY.i.hi + g_Tilemap.scrollY.i.hi;
        if (moveY >= 0xC0) {
            self->posY.i.hi = 0xc0 - g_Tilemap.scrollY.i.hi;
            self->step = 1;
        }
        break;
    default:
        warpCoords = &WarpRoomCoords[DestinationWarpRoom];
        moveX = warpCoords->x - g_Tilemap.left;
        moveY = warpCoords->y - g_Tilemap.top;
        FntPrint("move_room%x\n", DestinationWarpRoom);
        FntPrint("for_x:%x y%x\n", warpCoords->x, warpCoords->y);
        FntPrint("move_x:%x y%x\n", moveX, moveY);
        break;
    }

    WarpBackgroundPhase += 0x10;
    WarpBackgroundBrightness = (rsin(WarpBackgroundPhase) >> 8) + 0xD0;
    if (WarpBackgroundBrightness < 0) {
        WarpBackgroundBrightness = 0;
    }
    if (WarpBackgroundBrightness > 0xFF) {
        WarpBackgroundBrightness = 0xFF;
    }
    WarpBackgroundAmplitiude = (rcos(WarpBackgroundPhase) >> 8) + 0xD0;

    prim = self->ext.warpRoom.primBg;
    for (i = 0; i < 16; i++) {
        angle = bg_color_angle[(i + 0) % 16];
        prim->r0 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        angle = bg_color_angle[(i + 5) % 16];
        prim->g0 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        angle = bg_color_angle[(i + 10) % 16];
        prim->b0 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        angle = bg_color_angle[(i + 1) % 16];
        prim->r1 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        angle = bg_color_angle[(i + 6) % 16];
        prim->g1 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        angle = bg_color_angle[(i + 11) % 16];
        prim->b1 =
            ((rsin(angle) + 0x1000) >> 6) * WarpBackgroundAmplitiude / 256;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            WarpBackgroundBrightness;
        bg_color_angle[i] += 0x20;
        prim = prim->next;
    }
}

extern u16 g_EInitReverseSmallRocks[];

void EntityWarpSmallRocks(Entity* entity) {
    s32 x;
    s32 y;
    s32 rotation;
    s16 angle;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitReverseSmallRocks);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->rotZ = Random() * 0x10;
        entity->animCurFrame = (Random() % 5) + 1;
        if (D_80180648) {
            entity->posY.i.hi = (Random() & 0x1F) + 0x90;
            entity->step = 4;
            break;
        }
    case 1:
        if (D_80180648) {
            entity->ext.warpRoom.unk88 = Random() & 0x3F;
            entity->velocityY = FIX(-4);
            entity->step++;
        }
        break;
    case 2:
        if (entity->ext.warpRoom.unk88) {
            entity->ext.warpRoom.unk88--;
        } else {
            MoveEntity();
            entity->velocityY += FIX(0.25);
            if (entity->velocityY > FIX(-1.0f)) {
                entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                entity->rotX = entity->rotY = 0x100;
                entity->step++;
            }
        }
        break;
    case 3:
        x = 0x80 - entity->posX.i.hi;
        y = 0x80 - entity->posY.i.hi;
        angle = ratan2(y, x);
        entity->velocityX = rcos(angle) << 5;
        entity->velocityY = rsin(angle) << 5;
        MoveEntity();
        rotation = x * x + y * y;
        rotation = SquareRoot0(rotation);
        rotation *= 2;
        if (rotation > 0x100) {
            rotation = 0x100;
        }
        entity->rotX = entity->rotY = rotation;
        if (rotation < 8) {
            DestroyEntity(entity);
        }
        break;
    case 4:
        angle = entity->rotZ += 0x20;
        entity->velocityY = rsin(angle) * 4;
        if (D_80180648 == 0) {
            entity->ext.warpRoom.unk88 = 0x10;
            entity->step++;
        }
        break;
    case 5:
        if (--entity->ext.warpRoom.unk88 == 0) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
        }
        MoveEntity();
        entity->velocityY += FIX(0.1875);
        y = entity->posY.i.hi + g_Tilemap.scrollY.i.hi + 5;
        if (y > 208) {
            entity->posY.i.hi = 203 - g_Tilemap.scrollY.i.hi;
            entity->step = 1;
        }
        break;
    }
}
