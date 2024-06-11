#include <game.h>
#include "../wrp/wrp.h"

extern s32 D_80193AA0;
extern WarpCoord D_8018065C[];
extern u8 D_8003BEBC[];
#define SE_WARP_ENTER 0x636

extern u16 D_80180470[];
extern u32 D_80180608_wrp[];
extern u32 D_80180648;
extern s32 D_80193AA4;
extern s32 D_80193AAC;
extern s32 D_80193AA8;
extern const char D_80186E30[];
extern const char D_80186E3C[];
extern const char D_80186E4C[];
extern const char D_80186E5C[];
void func_80186FD0(Entity* arg0);
#define NEW_ENTITY pl
extern s32 D_psp_0924BC90;
extern s32 D_psp_0924BC90;

void EntityWarpRoom(Entity* self) {
    Primitive* prim;
    s32 angle;
    s32 i;
    Entity* pl;
    s32 move_room;
    s32 moveX;
    s32 moveY;
    WarpCoord* warpCoords;
    s32 primIndex;

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
        self->flags |= FLAG_HAS_PRIMS;
        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        self->ext.warpRoom.primBg = prim;
        moveY = self->posY.i.hi;
        moveX = self->posX.i.hi;
        for (i = 0; i < 0x10; i++) {
            angle = i * 256;
            prim->x0 = moveX + (((rcos(angle) >> 4) * 0x40) >> 8);
            prim->y0 = moveY - (((rsin(angle) >> 4) * 0x40) >> 8);
            prim->u0 = 0x20 + (((rcos(angle) >> 4) * 0x1E) >> 8);
            prim->v0 = 0xE0 - (((rsin(angle) >> 4) * 0x1E) >> 8);
            angle = (i + 1) * 256;
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
            prim->drawMode = 0x406;
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
        prim->drawMode = 0xA;
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
        D_80193AA4 = 0x100;
        for (i = 0; i < 32; i++) {
            NEW_ENTITY =
                (Entity*)AllocEntity(&g_Entities[0xA0], &g_Entities[0x100]);
            if (NEW_ENTITY != NULL) {
                CreateEntityFromCurrentEntity(D_psp_0924BC90, NEW_ENTITY);
                NEW_ENTITY->posY.i.hi = 0xCC - g_Tilemap.scrollY.i.hi;
                NEW_ENTITY->posX.i.hi = (Random() & 0x7F) + 0x40;
            }
        }
        self->hitboxState = 1;
        self->hitboxOffY += 16;
        self->hitboxWidth = 2;
        self->hitboxHeight = 16;
        *D_8003BEBC |= 1;
        *D_8003BEBC |= 1 << self->params;
        D_80180648 = 0;
        pl = &PLAYER;
        moveX = pl->posX.i.hi + g_Tilemap.scrollX.i.hi;
        if (moveX > 0x60 && moveX < 0xA0) {
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x10;
            D_8003C8B8 = 0;
            self->step = 5;
            D_80180648 = 1;
            break;
        }
    case 1:
        // Wait for player to press the UP button
        if (self->hitFlags && g_pads->pressed & 0x10 &&
            !(g_Player.unk0C & 0xC5CF3EF7)) { //
            g_Player.padSim = 0;
            g_Player.D_80072EFC = 0x80;
            D_8003C8B8 = 0;
#ifdef VERSION_US
            PLAYER.velocityX = 0;
            PLAYER.velocityY = 0;
#endif
            self->step++;
        }
        break;
    case 2:
        // Move Alucard in the background and fade him to white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x80;
        D_8003C8B8 = 0;
        pl = &g_Entities[0];
        g_unkGraphicsStruct.g_zEntityCenter.unk = pl->zPriority = 0x5C;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = 0x31;
        prim->g0 = prim->b0 = prim->r0 += 2;
        if (prim->r0 > 96) {
            D_80180648 = 1;
            g_api.PlaySfx(SE_WARP_ENTER);
            self->step++;
        }
        break;
    case 3:
        // Fade the entire room into white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x80;
        D_8003C8B8 = 0;
        pl = &g_Entities[0];
        g_unkGraphicsStruct.g_zEntityCenter.unk = pl->zPriority = 0x5C;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = 0x31;
        if (prim->r0 < 0xF0) {
            prim->g0 = prim->b0 = prim->r0 += 2;
        }
        prim = prim->next;
        prim->drawMode = 0x31;
        if (prim->r0 < 0xF8) {
            prim->g0 = prim->b0 = prim->r0 += 2;
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
        for (i = 0; i < 5;) {
            if (move_room > 4) {
                move_room = 0;
            }
            if (*D_8003BEBC & (1 << move_room)) {
                break;
            }
            i++;
            move_room++;
        }
        D_80193AA0 = move_room;
        warpCoords = &D_8018065C[move_room];
        moveX = warpCoords->x - g_Tilemap.left;
        moveY = warpCoords->y - g_Tilemap.top;
        FntPrint(D_80186E3C, D_80193AA0);
        FntPrint(D_80186E4C, warpCoords->x, warpCoords->y);
        FntPrint(D_80186E5C, moveX, moveY);
        PLAYER.posX.i.hi += moveX << 8;
        PLAYER.posY.i.hi += moveY << 8;
        self->step = 0x80;
        D_80097C98 = 2;
        break;
    case 5:
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim->drawMode = DRAW_HIDE;
        prim->g0 = prim->b0 = prim->r0 = 0;
        prim = prim->next;
        prim->r0 = prim->g0 = prim->b0 = 0xF8;
        LOW(prim->r1) = LOW(prim->r0);
        LOW(prim->r2) = LOW(prim->r0);
        LOW(prim->r3) = LOW(prim->r0);
        prim->drawMode = 0x31;
        g_api.g_pfn_800EA5AC(0, 0, 0, 0);
        self->step++;
    case 6:
        // Finalize warp by fading in from white
        g_Player.padSim = 0;
        g_Player.D_80072EFC = 0x10;
        D_8003C8B8 = 0;
        prim = self->ext.warpRoom.primFade;
        prim = prim->next;
        move_room = prim->r0;
        move_room -= 4;
        if (move_room < 0) {
            move_room = 0;
            prim->drawMode = DRAW_HIDE;
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
    for (i = 0; i < 0x10; i++) {
        angle = D_80180608_wrp[(i + 0) % 16];
        prim->r0 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        angle = D_80180608_wrp[(i + 5) % 16];
        prim->g0 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        angle = D_80180608_wrp[(i + 10) % 16];
        prim->b0 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        angle = D_80180608_wrp[(i + 1) % 16];
        prim->r1 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        angle = D_80180608_wrp[(i + 6) % 16];
        prim->g1 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        angle = D_80180608_wrp[(i + 11) % 16];
        prim->b1 = ((rsin(angle) + 0x1000) >> 6) * D_80193AA4 / 256;
        prim->r2 = prim->g2 = prim->b2 = prim->r3 = prim->g3 = prim->b3 =
            D_80193AAC;
        D_80180608_wrp[i] += 0x20;
        prim = prim->next;
    }
}

extern u16 D_801804C4[];
extern u32 D_80180648;
#define SE_WARP_DEBRIS 0x644

void EntityWarpSmallRocks(Entity* entity) {
    s32 x;
    s32 y;
    s32 rotation;
    s16 angle;

    switch (entity->step) {
    case 0:
        InitializeEntity(D_801804C4);
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
            func_801916C4(SE_WARP_DEBRIS);
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
