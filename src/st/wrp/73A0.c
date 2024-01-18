#include "wrp.h"
#include "sfx.h"

extern u16 D_80180470[];
extern u16 D_801804C4[];
extern u32 D_80180648;

#ifndef NON_MATCHING
INCLUDE_ASM("st/wrp/nonmatchings/73A0", EntityWarpRoom);
#else
extern u8 D_8003BEBC[];
extern s32 D_8003C8B8;
extern s32 D_80193AA0; // rename into move_room
extern s32 D_80193AA4;
extern s32 D_80193AA8;
extern s32 D_80193AAC;

// Handles everything about the warp room.
// It is responsible to spawn the colourful background, the stones on the
// ground and it always listen to the UP button. When the UP
// button is pressed, it brights the screen and teleport the player.
void EntityWarpRoom(Entity* self) {
    Primitive* prim;
    Entity* newEntity;
    WarpCoord* warpCoords;
    s32 i;
    s32 i3;
    s16 primIndex;
    s32 moveX;
    s32 moveY;
    s32 move_room;

    FntPrint(D_80186E30, self->step);
    switch (self->step) {
    case 0:
        // Initialize all the objects in the warp room
        InitializeEntity(D_80180470);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 24);
        if (primIndex == -1) {
            self->step = 0;
            return;
        }
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.warpRoom.primBg = prim;
        self->flags |= FLAG_HAS_PRIMS;
        moveY = self->posY.i.hi;
        moveX = self->posX.i.hi;
        for (i = 0; i < 0x10; i++) {
            prim->x0 = moveX + ((rcos(i * 256) * 4) >> 8);
            prim->y0 = moveY - ((rsin(i * 256) * 4) >> 8);
            prim->u0 = 0x20 + (((rcos(i * 256) >> 4) * 0x1E) >> 8);
            prim->v0 = -0x20 - (((rsin(i * 256) >> 4) * 0x1E) >> 8);
            prim->x1 = moveX + ((rcos((i + 1) * 256) * 4) >> 8);
            prim->y1 = moveY - ((rsin((i + 1) * 256) * 4) >> 8);
            prim->u1 = 0x20 + (((rcos((i + 1) * 256) >> 4) * 0x1E) >> 8);
            prim->v1 = -0x20 - (((rsin((i + 1) * 256) >> 4) * 0x1E) >> 8);
            prim->y2 = prim->y3 = moveY;
            prim->x2 = prim->x3 = moveX;
            prim->u2 = prim->u3 = 0x20;
            prim->v2 = prim->v3 = 0xE0;
            prim->tpage = 0x1A;
            prim->clut = 0x15F;
            prim->priority = 0x40;
            prim->blendMode = 0x406;
            prim = prim->next;
        }

        self->ext.warpRoom.primFade = prim;
        prim->type = PRIM_TILE;
        prim->u0 = 64;
        prim->v0 = 80;
        prim->x0 = 96;
        prim->y0 = 112;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->priority = 0x60;
        prim->blendMode = 0xA;
        prim = prim->next;
        prim->type = PRIM_G4;
        prim->r0 = prim->g0 = prim->b0 = 0;
        prim->x0 = prim->x2 = 0;
        prim->x1 = prim->x3 = 256;
        prim->y0 = prim->y1 = 16;
        prim->y2 = prim->y3 = 240;
        prim->priority = 0x1F0;
        prim->blendMode = BLEND_VISIBLE;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        D_80193AA4 = 0x100;
        for (i = 0; i < 32; i++) {
            newEntity = AllocEntity(&g_Entities[0xA0], &g_Entities[0x100]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(0x17, newEntity);
                newEntity->posY.i.hi = 0xCC - g_Tilemap.cameraY.i.hi;
                newEntity->posX.i.hi = (Random() & 0x7F) + 0x40;
            }
        }

        self->unk3C = 1;
        self->hitboxWidth = 2;
        self->hitboxHeight = 16;
        self->unk12 += 16;
        D_80180648 = 0;
        *D_8003BEBC |= 1;
        *D_8003BEBC |= 1 << self->params;
        moveX = g_Tilemap.cameraX.i.hi + (&PLAYER)->posX.i.hi;
        if (moveX > 0x60 && moveX < 0xA0) {
            g_Player.D_80072EFC = 0x10;
            g_Player.D_80072EF4 = 0;
            D_8003C8B8 = 0;
            self->step = 5;
            D_80180648 = 1;
        }
        break;

    case 1:
        // Wait for player to press the UP button
        if (self->unk48 != 0 && g_pads->pressed & 0x1000 &&
            !(g_Player.unk0C & 0xC5CF3EF7)) {
            D_8003C8B8 = 0;
            g_Player.D_80072EF4 = 0;
            g_Player.D_80072EFC = 0x80;
            PLAYER.velocityX = 0;
            PLAYER.velocityY = 0;
            self->step++;
        }
        break;

    case 2:
        // Move Alucard in the background and fade him to white
        g_Player.D_80072EFC = 0x80;
        g_Player.D_80072EF4 = 0;
        PLAYER.zPriority = 0x5C;
        g_unkGraphicsStruct.g_zEntityCenter.unk = 0x5C;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim->g0 = prim->b0 = prim->r0 = prim->r0 + 2;
        prim->blendMode = 0x31;
        if (prim->r0 > 96) {
            D_80180648 = 1;
            g_api.PlaySfx(SE_WARP_ENTER);
            self->step++;
        }
        break;

    case 3:
        // Fade the entire room into white
        g_Player.D_80072EFC = 0x80;
        g_Player.D_80072EF4 = 0;
        PLAYER.zPriority = 0x5C;
        g_unkGraphicsStruct.g_zEntityCenter.unk = 0x5C;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim->blendMode = 0x31;
        if (prim->r0 < 0xF0) {
            prim->g0 = prim->b0 = prim->r0 = prim->r0 + 2;
        }
        prim = prim->next;
        prim->blendMode = 0x31;
        if (prim->r0 < 0xF8) {
            prim->g0 = prim->b0 = prim->r0 = prim->r0 + 2;
        } else {
            self->step++;
        }
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    case 4:
        // Perform the actual warp
        move_room = self->params + 1;
        for (i3 = 0; i3 < 5; i3++) {
            if (move_room >= 5) {
                move_room = 0;
            }
            if (*D_8003BEBC >> move_room & 1) {
                break;
            }
            move_room++;
        }

        warpCoords = &D_8018065C[move_room];
        moveX = warpCoords->x - g_Tilemap.left;
        moveY = warpCoords->y - g_Tilemap.top;
        D_80193AA0 = move_room;
        FntPrint(D_80186E3C, move_room);
        FntPrint(D_80186E4C, warpCoords->x, warpCoords->y);
        FntPrint(D_80186E5C, moveX, moveY);
        PLAYER.posX.i.hi += moveX << 8;
        PLAYER.posY.i.hi += moveY << 8;
        D_80097C98 = 2;
        self->step = 0x80;
        break;

    case 5:
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim->blendMode = BLEND_VISIBLE;
        prim->r0 = 0;
        prim->b0 = 0;
        prim->g0 = 0;
        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0xF8;
        prim->blendMode = 0x31;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        g_api.g_pfn_800EA5AC(0, 0, 0, 0);
        self->step++;

    case 6:
        // Finalize warp by fading in from white
        g_Player.D_80072EF4 = 0;
        g_Player.D_80072EFC = 0x10;
        prim = self->ext.warpRoom.primFade;
        prim = prim->next;
        D_8003C8B8 = 0;
        move_room = prim->r0;
        move_room -= 4;
        if (move_room < 0) {
            move_room = 0;
            prim->blendMode = BLEND_VISIBLE;
            D_8003C8B8 = 1;
            self->step = 1;
        }
        if (move_room < 0x28) {
            D_80180648 = 0;
        }
        prim->g0 = prim->b0 = prim->r0 = move_room;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        break;

    default:
        warpCoords = &D_8018065C[D_80193AA0];
        moveX = warpCoords->x - g_Tilemap.left;
        moveY = warpCoords->y - g_Tilemap.top;
        FntPrint(D_80186E3C, D_80193AA0);
        FntPrint(D_80186E4C, warpCoords->x, warpCoords->y);
        FntPrint(D_80186E5C, moveX, moveY);
        break;
    }

    D_80193AA8 += 0x10;
    D_80193AAC = (rsin(D_80193AA8) >> 8) + 0xD0;
    if (D_80193AAC < 0) {
        D_80193AAC = 0;
    }
    if (D_80193AAC > 0xFF) {
        D_80193AAC = 0xFF;
    }
    D_80193AA4 = (rcos(D_80193AA8) >> 8) + 0xD0;

    prim = self->ext.warpRoom.primBg;
    for (i3 = 0; i3 < 0x10; i3++) {
        prim->r0 = ((rsin(D_80180608[(i3 + 0) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->g0 = ((rsin(D_80180608[(i3 + 5) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->b0 = ((rsin(D_80180608[(i3 + 10) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->r1 = ((rsin(D_80180608[(i3 + 1) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->g1 = ((rsin(D_80180608[(i3 + 6) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->b1 = ((rsin(D_80180608[(i3 + 11) % 16]) + 0x1000) >> 6) *
                   D_80193AA4 / 256;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            D_80193AAC;
        D_80180608[i3] += 0x20;
        prim = prim->next;
    }
}
#endif

void EntityWarpSmallRocks(Entity* entity) {
    s32 x;
    s32 y;
    s16* y_unk;
    s32 distance;
    s16 radians;
    u32* unk;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801804C4);
        entity->drawFlags = FLAG_DRAW_ROTZ;
        entity->rotZ = Random() * 0x10;
        entity->animCurFrame = (Random() % 5) + 1;
        if (D_80180648 != 0) {
            entity->posY.i.hi = (Random() & 0x1F) + 0x90;
            entity->step = 4;
        }
        break;
    case 1:
        if (D_80180648 != 0) {
            *(u32*)(&entity->ext.generic.unk88) = Random() & 0x3F;
            entity->velocityY = FIX(-4);
            entity->step++;
        }
        break;
    case 2:
        if (*(u32*)&entity->ext.generic.unk88 != 0) {
            *(u32*)&entity->ext.generic.unk88 =
                *(u32*)&entity->ext.generic.unk88 - 1;
        } else {
            MoveEntity();
            entity->velocityY += FIX(0.25);
            if (entity->velocityY > ((s32)0xFFFF0000)) {
                entity->drawFlags = FLAG_DRAW_ROTX | FLAG_DRAW_ROTY;
                entity->rotY = 0x100;
                distance = 0x100;
                entity->rotX = distance;
                entity->step++;
            }
        }
        break;
    case 3:
        x = 0x80 - entity->posX.i.hi;
        y = 0x80 - entity->posY.i.hi;
        radians = ratan2(y, x);
        entity->velocityX = rcos(radians) << 5;
        entity->velocityY = rsin(radians) << 5;
        MoveEntity();
        distance = SquareRoot0(x * x + y * y) * 2;
        if (distance >= 0x101) {
            distance = 0x100;
        }
        entity->rotX = entity->rotY = distance;
        if (distance < 8) {
            DestroyEntity(entity);
        }
        break;
    case 4:
        entity->rotZ += 0x20;
        entity->velocityY = rsin(entity->rotZ) * 4;
        if (D_80180648 == 0) {
            *(u32*)&entity->ext.generic.unk88 = 0x10;
            entity->step++;
        }
        break;
    case 5:
        y_unk = &g_Tilemap.cameraY.i.hi;
        *(u32*)&entity->ext.generic.unk88 =
            *(u32*)&entity->ext.generic.unk88 - 1;
        if (*(u32*)&entity->ext.generic.unk88 == 0) {
            func_801916C4(SE_WARP_DEBRIS);
        }
        MoveEntity();
        entity->velocityY += FIX(0.1875);
        y = entity->posY.i.hi + *y_unk + 5;
        if (y >= 209) {
            entity->posY.i.hi = 203 - (*y_unk);
            entity->step = 1;
        }
        break;
    }
}
