/*
 * File: 394D4.c
 * Overlay: NZ0
 * Description: Alchemy Laboratory
 */

#include "nz0.h"

void func_801B0958(Entity* self) {
    ObjInit2* temp_s0 = &D_80180D64[self->params];

    if (self->step == 0) {
        InitializeEntity(D_80180C1C);
        self->animSet = temp_s0->animSet;
        self->zPriority = temp_s0->zPriority;
        self->unk5A = temp_s0->unk4.u;
        self->palette = temp_s0->palette;
        self->unk19 = temp_s0->unk8;
        self->blendMode = temp_s0->blendMode;
        if (temp_s0->unkC != 0) {
            self->flags = temp_s0->unkC;
        }
    }
    AnimateEntity(temp_s0->unk10, self);
}

bool func_801B0A20(Entity* self) {
    s16 diffX = PLAYER.posX.i.hi - self->posX.i.hi;

    diffX = ABS(diffX);
    if (self->hitboxWidth >= diffX) {
        diffX = PLAYER.posY.i.hi - self->posY.i.hi;
        diffX = ABS(diffX);
        return (self->hitboxHeight >= diffX);
    } else {
        return false;
    }
}

INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B0AA4);

void EntityBreakable(Entity* self) {
    u16 params = self->params >> 0xC;
    s16 top, bottom, left, right;
    Entity* newEntity;
    Primitive* prim;

    if (self->step != 0) {
        AnimateEntity((u8*)D_80180E04[params], self);
        if (params == 2) {
            prim = &g_PrimBuf[self->primIndex];
            if (g_blinkTimer & 2) {
                prim->clut = 0x21B;
            } else {
                prim->clut = 0x21C;
            }
        }

        if (self->unk44 != 0) {
            if (params == 2) {
                g_api.FreePrimitives(self->primIndex);
                self->flags &= ~FLAG_HAS_PRIMS;
            }
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromCurrentEntity(E_EXPLOSION, newEntity);
                newEntity->params = D_80180E2C[params];
            }
            ReplaceBreakableWithItemDrop(self);
        }
    } else {
        InitializeEntity(D_80180BC8);
        self->zPriority = g_zEntityCenter.S16.unk0 - 20;
        self->blendMode = D_80180E44[params];
        self->hitboxHeight = D_80180E24[params];
        self->animSet = D_80180E34[params];
        if (params == 2) {
            self->unk5A = 0x4B;
            self->palette = 0x219;
            self->primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
            if (self->primIndex == -1) {
                DestroyEntity(self);
                return;
            }
            self->flags |= FLAG_HAS_PRIMS;
            prim = &g_PrimBuf[self->primIndex];
            prim->tpage = 0x12;
            prim->u0 = prim->u2 = 0xC8;
            prim->u1 = prim->u3 = 0xF8;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xA0;
            left = self->posX.i.hi - 23;
            right = self->posX.i.hi + 25;
            prim->x0 = prim->x2 = left;
            prim->x1 = prim->x3 = right;
            top = self->posY.i.hi - 23;
            bottom = self->posY.i.hi + 9;
            prim->y0 = prim->y1 = top;
            prim->y2 = prim->y3 = bottom;
            prim->priority = self->zPriority;
            prim->blendMode = 0x73;
        }
    }
}

// bust with red eyes that can have a candle on it
void EntityRedEyeBust(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C34);
        self->animCurFrame = 7;
        self->zPriority = 0x70;
        break;

    case 1:
        break;

    case 2:
        FntPrint(&D_801B058C, self->animCurFrame); // "charal %x\n"
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params == 0) {
                self->animCurFrame++;
                self->params |= 1;
            } else
                break;
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

// A purplish-red brick background that scrolls behind the foreground layer
void EntityPurpleBrickScrollingBackground(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 tempPosX;
    s32 tempPosY;
    s32 x, y;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->posX.i.hi = 0;
        self->posY.i.hi = 0;
        self->unk68 = 0x80;
        // Composed of 15 primitives
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 15);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = (s32)primIndex;
        *(s32*)&self->ext.generic.unk7C = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->tpage = 0xF;
            prim->clut = 4;
            prim->u0 = prim->u2 = 0x80;
            prim->u1 = prim->u3 = 0xFF;
            prim->v0 = prim->v1 = 0x80;
            prim->v2 = prim->v3 = 0xBF;
            prim->priority = 0x20;
            prim->blendMode = 2;
            prim = prim->next;
        }

    case 1:
        // Add a scrolling effect
        tempPosX = self->posX.i.hi;
        tempPosX = tempPosX & 0x7F;
        tempPosX = tempPosX - 0x80;
        tempPosY = self->posY.i.hi;
        tempPosY = (tempPosY & 0x3F) - 0x40;
        prim = *((s32*)(&self->ext.generic.unk7C));
        // Primitives are laid out in a 5-tall by 3-wide grid
        for (y = 0; y < 5; y++) {
            for (x = 0; x < 3; x++) {
                prim->x0 = prim->x2 = tempPosX + (x * 0x80);
                prim->x1 = prim->x3 = prim->x0 + 0x80;
                prim->y0 = prim->y1 = tempPosY + (y * 0x40);
                prim->y2 = prim->y3 = prim->y0 + 0x40;
                prim->blendMode = 0;
                prim = prim->next;
            }
        }

        while (prim != NULL) {
            prim->blendMode = 8;
            prim = prim->next;
        }
    }
}

void EntityLeftSecretRoomWall(Entity* self, u16* tileLayoutPtr, s32 tilePos) {
    Entity* newEntity;
    s32 cond;
    s32 i;

    switch (self->step) {
    case LEFT_SECRET_ROOM_WALL_INIT:
        InitializeEntity(D_80180BF8);
        self->hitboxWidth = 16;
        self->hitboxHeight = 32;
        self->hitboxState = 2;

        cond = D_8003BDEC[129] != 0;
        tileLayoutPtr = &D_80180E54 + (-cond & 0xC);

        tilePos = 0x260;
        for (i = 0; i < 4; i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tilePos += 0x10;
            tileLayoutPtr += 2;
        }

        if (D_8003BDEC[129] != 0) {
            DestroyEntity(self);
            break;
        }

    case LEFT_SECRET_ROOM_WALL_IDLE:
        if (self->hitFlags != 0) {
            func_801C29B0(NA_SE_EN_ROCK_BREAK);
            self->step++;
        }
        break;

    case LEFT_SECRET_ROOM_WALL_BREAK:
        self->ext.generic.unk84.unk++;
        tileLayoutPtr = &D_80180E54 + (self->ext.generic.unk84.unk * 0x4);

        tilePos = 0x260;
        for (i = 0; i < 4; i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x13;
        }
        self->ext.generic.unk80.modeS32 = 32;
        self->step++;

        if (self->ext.generic.unk84.unk == 3) {
            D_8003BDEC[129] = 1;
            g_api.func_800F1FC4(0x81);

            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(0x22, self, newEntity);
                    newEntity->posX.i.hi += (Random() & 0xF);
                    newEntity->posY.i.hi -= 0x20 - (Random() & 0x3F);
                }
            }
            DestroyEntity(self);
        }
        break;

    case LEFT_SECRET_ROOM_WALL_CHECK:
        if (--self->ext.generic.unk80.modeS32 == 0) {
            self->step = LEFT_SECRET_ROOM_WALL_IDLE;
        }
        break;
    }
}

void EntityBottomSecretRoomFloor(
    Entity* self, u16* tileLayoutPtr, s32 tilePos) {
    Entity* newEntity;
    s32 flag;
    s32 i;

    switch (self->step) {
    case BOTTOM_SECRET_ROOM_FLOOR_INIT:
        InitializeEntity(D_80180BF8);
        self->hitboxWidth = 16;
        self->hitboxHeight = 16;
        self->hitboxState = 2;
        flag = (D_8003BDEC[130] != 0);
        tileLayoutPtr = &D_80180E94 + (-flag & 0x6);

        tilePos = 0x2E7;
        for (i = 0; i < 2; i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        if (D_8003BDEC[130] != 0) {
            DestroyEntity(self);
            break;
        }

    case BOTTOM_SECRET_ROOM_FLOOR_IDLE:
        if (self->hitFlags != 0) {
            func_801C29B0(NA_SE_EN_ROCK_BREAK);
            self->step++;
        }
        return;

    case BOTTOM_SECRET_ROOM_FLOOR_BREAK:
        self->ext.generic.unk84.unk++;
        tileLayoutPtr = &D_80180E94 + (self->ext.generic.unk84.unk * 2);

        tilePos = 0x2E7;
        for (i = 0; i < 2; i++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            g_CurrentRoomTileLayout.fg[tilePos + 1] = *(tileLayoutPtr + 1);
            tileLayoutPtr += 2;
            tilePos += 0x10;
        }

        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.generic.unk80.modeS32 = 32;
        self->step++;

        if (self->ext.generic.unk84.unk == 3) {
            D_8003BDEC[130] = 1;
            g_api.func_800F1FC4(0x82);
            DestroyEntity(self);
        }
        break;

    case BOTTOM_SECRET_ROOM_FLOOR_CHECK:
        if (--self->ext.generic.unk80.modeS32 == 0) {
            self->step = BOTTOM_SECRET_ROOM_FLOOR_IDLE;
        }
        break;
    }
}

void func_801B19A0(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 rnd;
    s16 rnd2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180C34);
        self->unk19 = 4;

        if (Random() & 1) {
            self->animCurFrame = 1;
        } else {
            self->animCurFrame = 2;
        }

        rnd = (Random() & 0x1F) + 16;
        rnd2 = ((Random() & 0x3F) * 16) | 0xC00;
        if (self->params != 0) {
            self->animCurFrame = 3;
            rnd = (Random() & 0x1F) + 16;
            rnd2 = (Random() * 6) + 0x900;
        }

        self->velocityX = rnd * rcos(rnd2);
        self->velocityY = rnd * rsin(rnd2);
        if (self->velocityX < 0) {
            self->facing = 1;
        }

    case 1:
        MoveEntity();
        self->rotAngle += 0x20;
        if (self->params != 0) {
            self->rotAngle += 0x20;
        }

        self->velocityY += 0x2000;
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posY.i.hi += collider.unk18;
            if (self->params == 0) {
                func_801C29B0(0x644);
                for (i = 0; i < 2; i++) {
                    newEntity =
                        AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
                    if (newEntity != NULL) {
                        CreateEntityFromEntity(0x22, self, newEntity);
                        newEntity->params = 0x1;
                    }
                }
                DestroyEntity(self);
                break;
            }
            if (self->velocityY < 0x8000) {
                newEntity =
                    AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 0x10;
                }
                DestroyEntity(self);
                break;
            }
            self->velocityY = -self->velocityY;
            self->velocityY *= 2;
            self->velocityY /= 3;
        }
    }
}

void func_801B1C18(Entity* self) {
    s32 temp_s1 = func_801BD9A0(self, 8, 8, 4);
    s16 primIndex;
    POLY_GT4* poly;
    Entity* player;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *((s32*)(&self->ext.generic.unk7C)) = poly;
        self->flags |= FLAG_HAS_PRIMS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->pad3 = 2;

    case 1:
        if (temp_s1 != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 468) {
                self->posY.i.hi = 468 - g_Camera.posY.i.hi;
                D_80180EB4 ^= self->params;
                self->step++;
            }
        }
        break;

    case 2:
        if (temp_s1 == 0) {
            self->step++;
        }
        break;

    case 3:
        self->posY.val += 0xFFFF0000;
        temp = g_Camera.posY.i.hi + self->posY.i.hi;
        if (temp < 464) {
            self->posY.i.hi = 464 - g_Camera.posY.i.hi;
            self->step = 1;
        }
        break;
    }
    poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
    poly->x0 = self->posX.i.hi - 8;
    poly->y0 = self->posY.i.hi - 8;
}

void func_801B1E54(Entity* self, s16 primIndex) {
    POLY_GT4* poly;
    s8 var_v1;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *((s32*)(&self->ext.generic.unk7C)) = poly;
        self->flags |= FLAG_HAS_PRIMS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 40;
        poly->v0 = 200;
        poly->u1 = 32;
        poly->v1 = 32;
        poly->pad2 = 0x5F;
        poly->pad3 = 2;

        if (self->params & D_80180EB4) {
            self->posY.i.hi = 480 - g_Camera.posY.i.hi;
            self->ext.generic.unk88.S8.unk0 = 1;
        } else {
            self->posY.i.hi = 452 - g_Camera.posY.i.hi;
            self->ext.generic.unk88.S8.unk0 = 0;
        }

    case 1:
        if (self->params & D_80180EB4) {
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 480) {
                self->posY.i.hi = 480 - g_Camera.posY.i.hi;
            }
            var_v1 = 1;
        } else {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < 452) {
                self->posY.i.hi = 452 - g_Camera.posY.i.hi;
                self->step = 1;
            }
            var_v1 = 0;
        }

        if (self->ext.generic.unk88.U8.unk0 != var_v1) {
            self->ext.generic.unk88.U8.unk0 = var_v1;
            func_801C29B0(0x69D);
        }
    }

    poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
    poly->x0 = self->posX.i.hi - 16;
    poly->y0 = self->posY.i.hi - 16;
    temp = 480 - (g_Camera.posY.i.hi + self->posY.i.hi);
    D_801CB736[self->params] = temp;
}

// moveable box for spike/switch areas
void EntityMoveableBox(Entity* self) {
    Entity* player;
    POLY_GT4* poly;
    s32 temp_s1 = func_801BD9A0(self, 0x10, 0x10, 5);
    s32 var_s1 = temp_s1;
    s16 primIndex;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v1;
    s32 new_var;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *((s32*)(&self->ext.generic.unk7C.s)) = poly;
        self->flags |= FLAG_HAS_PRIMS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 8;
        poly->v0 = 200;
        poly->u1 = 32;
        poly->v1 = 32;
        poly->pad2 = 112;
        poly->pad3 = 2;

    case 1:
        player = &PLAYER;
        self->velocityX = 0;
        self->velocityY = 0;

        if (var_s1 & 1) {
            temp_s1 = GetSideToPlayer();
            if (temp_s1 & 1 && player->velocityX > 0) {
                if (!(g_blinkTimer & 7)) {
                    g_api.PlaySfx(0x608);
                }
                self->velocityX = 0x8000;
            }
            temp_s1 = GetSideToPlayer();
            if (!(primIndex = (temp_s1 & 1)) && (player->velocityX < 0)) {
                if (!(g_blinkTimer & 7)) {
                    g_api.PlaySfx(0x608);
                }
                self->velocityX = -0x8000;
            }
        }

        func_801BCF74(&D_80180EB8);

        if (self->params == 0) {
            temp_v0_2 = self->posX.i.hi + g_Camera.posX.i.hi;
            var_v1 = temp_v0_2 - 192;
            var_v1 = ABS(var_v1);
            var_v0 = temp_v0_2 - 256;
            var_v0 = ABS(var_v0);
            var_s1 = 24 > var_v1;
            if (var_v0 < 24) {
                var_s1 = 2;
            }
            if ((self->ext.generic.unk84.unk == 0) &&
                ((s16)D_801CB736[var_s1] != 0)) {
                var_s1 = 0;
                self->posX.val -= self->velocityX;
            }
            self->ext.generic.unk84.unk = var_s1;
            if (var_s1 != 0) {
                self->posY.i.hi =
                    (448 - D_801CB736[var_s1]) - g_Camera.posY.i.hi;
            }
        }
        break;
    }
    poly = (POLY_GT4*)(*(s32*)(&self->ext.generic.unk7C.s));
    new_var = ((u16)self->posX.i.hi) - 16;
    poly->x0 = new_var;
    poly->y0 = ((u16)self->posY.i.hi) - 16;
}

// lever to operate cannon
void EntityCannonLever(Entity* self) {
    /** TODO: !FAKE
     * self->ext.generic.unk7C should be a POLY_G4*
     */
    POLY_GT4* poly;
    s16 primIndex;
    s32 temp_v0_2;
    s32 temp_v1_2;
    s32 var_v0;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->hitboxWidth = 4;
        self->hitboxHeight = 20;
        self->hitboxState = 2;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;

        self->flags |= FLAG_HAS_PRIMS;
        poly->code = 6;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 0x68;
        poly->v0 = 0x80;
        poly->u1 = 8;
        poly->v1 = 0x28;
        poly->pad2 = 0x70;
        poly->pad3 = 2;

        if (PLAYER.posX.i.hi < 128) {
            self->hitboxState = 0;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            self->velocityX = -0x40000;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        temp_v1_2 = self->velocityX;
        if (temp_v1_2 < 0) {
            var_v0 = temp_v1_2 + 0xF;
        } else {
            var_v0 = temp_v1_2;
        }
        temp_v0_2 = temp_v1_2 - (var_v0 >> 4);
        self->velocityX = temp_v0_2;
        if (temp_v0_2 < 0x2000) {
            self->step++;
        }
        break;

    case 3:
        D_80180ED0[0] = 1;
        break;
    }

    if (D_8003BE6F[0] != 0) {
        self->hitboxState = 0;
    }
    poly = (POLY_GT4*)*(s32*)&self->ext.generic.unk7C.s;
    poly->x0 = self->posX.i.hi - 4;
    poly->y0 = self->posY.i.hi - 20;
}

// cannon for shortcut
void EntityCannon(Entity* self) {
    s16 primIndex;
    Entity* newEntity;
    Primitive* prim;
    s32 var_v0;
    s32 temp;
    s32 temp2;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 2);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        self->primIndex = primIndex;
        prim = &g_PrimBuf[primIndex];
        *(s32*)&self->ext.generic.unk7C = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x28;
        prim->v0 = 0xA8;
        prim->u1 = 0x38;
        prim->v1 = 0x20;
        prim->priority = 0x70;
        prim->blendMode = 2;

        prim = prim->next;
        prim->type = PRIM_SPRT;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x28;
        prim->v0 = 0x80;
        prim->u1 = 0x40;
        prim->v1 = 0x28;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = 120 - g_Camera.posY.i.hi;
        prim->priority = 0x78;
        prim->blendMode = 2;

        if (D_8003BE6F[0] != 0) {
            self->step = 3;
        }
        break;

    case 1:
        if (D_80180ED0[0] != 0) {
            g_api.func_80102CD8(1);
            g_api.PlaySfx(0x6AC);
            self->velocityX = 0x80000;
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != 0) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            CreateEntityFromEntity(0x1E, self, &self[1]);
            self->step++;
        }
        break;

    case 2:
        prim = *(s32*)&self->ext.generic.unk7C;
        prim = prim->next;
        self->posX.i.hi = prim->x0 + 8;
        self->posX.i.lo = 0;
        MoveEntity();

        temp = self->velocityX;
        if (temp < 0) {
            var_v0 = temp + 7;
        } else {
            var_v0 = temp;
        }

        temp2 = temp - (var_v0 >> 3);
        self->velocityX = temp - (var_v0 >> 3);

        if (temp2 < 0x2000) {
            self->step++;
        }
        break;
    }

    prim = *(s32*)&self->ext.generic.unk7C;
    prim->x0 = self->posX.i.hi - 24;
    prim->y0 = self->posY.i.hi - 16;
}

// projectile shot by cannon
void EntityCannonShot(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->animSet = ANIMSET_DRA(2);
        self->animCurFrame = 1;
        self->palette = 0x81AF;
        self->zPriority = 0x6F;
        self->velocityX = -0x80000;

    case 1:
        MoveEntity();
        if ((self->posX.i.hi + g_Camera.posX.i.hi) < 112) {
            g_api.func_80102CD8(1);
            newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 3;
            }
            D_8003BE6F[0] = 1;
            DestroyEntity(self);
        }
        break;
    }
}

void EntityCannonWall(Entity* self) {
    u16* tileLayoutPtr;
    s32 tilePos;
    s32 cond;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);

        cond = D_8003BDEC[131] != 0;
        tileLayoutPtr = (-cond & 6) + &D_80180ED4[0];
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }

        if (D_8003BDEC[131] != 0) {
            DestroyEntity(self);
        }
        break;

    case 1:
        i = D_8003BDEC[131] != 0; // TODO: !FAKE:
        if (i) {
            self->step++;
        }
        break;

    case 2:
        g_api.PlaySfx(NA_SE_EN_ROCK_BREAK);

        tileLayoutPtr = &D_80180EE0;
        for (tilePos = 0x46, i = 0; i < 6; i++, tileLayoutPtr++) {
            g_CurrentRoomTileLayout.fg[tilePos] = *tileLayoutPtr;
            tilePos += 0x10;
        }
        DestroyEntity(self);
    }
}

void func_801B2AD8(Entity* self) {
    s16 primIndex;
    POLY_GT4* poly;
    s32 var_v0;
    s32 var_a0;
    s32 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->hitboxHeight = 8;
        self->hitboxOffY = -0x16;
        self->hitboxWidth = 6;
        self->hitboxState = 1;
        CreateEntityFromEntity(0x26, self, &self[-1]);
        self[-1].posY.i.hi = 344 - g_Camera.posY.i.hi;

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        poly = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *(s32*)&self->ext.generic.unk7C = poly;
        self->flags |= FLAG_HAS_PRIMS;
        poly->tpage = 0xF;
        poly->clut = 9;
        poly->u0 = 72;
        poly->v0 = 200;
        poly->u1 = 16;
        poly->v1 = 16;
        poly->pad2 = 0x5F;
        poly->code = 6;
        poly->pad3 = 2;

    case 1:
        var_a0 = self->hitFlags;
        var_v0 = self->posX.i.hi - self[-1].posX.i.hi;

        if (ABS(var_v0) < 8) {
            var_a0 |= 0x8000;
        }

        if (var_a0 != 0) {
            self->posY.val += 0x10000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp > 376) {
                self->posY.i.hi = 376 - g_Camera.posY.i.hi;
            }
            D_80180EEC = 1;
        } else {
            self->posY.val += 0xFFFF0000;
            temp = g_Camera.posY.i.hi + self->posY.i.hi;
            if (temp < 372) {
                self->posY.i.hi = 372 - g_Camera.posY.i.hi;
            }
            D_80180EEC = 0;
        }

    default:
        poly = (POLY_GT4*)(*((s32*)(&self->ext.generic.unk7C)));
        poly->x0 = self->posX.i.hi - 8;
        poly->y0 = self->posY.i.hi - 8;
    }
}

// DECOMP_ME_WIP func_801B2D08 https://decomp.me/scratch/ixW6j 93.06%
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B2D08);

void func_801B2FD8(Entity* self) {
    s32 temp = func_801BD9A0(self, 8, 8, 4);
    Primitive* prim;
    Entity* player;
    s16 primIndex;
    s32 posX, posY;
    s32 camY;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->ext.generic.unk80.modeS32 = self->posY.i.hi + g_Camera.posY.i.hi;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = 6;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x48;
        prim->v0 = 0xC8;
        prim->v1 = prim->u1 = 0x10;
        prim->priority = 0x5F;
        prim->blendMode = 2;

        posX = self->posX.i.hi;
        posX += g_Camera.posX.i.hi;
        posX >>= 4;

        // TODO: !FAKE
        camY = self->posY.i.hi;
        posY = camY += 4;
        posY = camY += g_Camera.posY.i.hi;

        camY = (camY >> 4) * g_CurrentRoom.hSize * 16;
        g_CurrentRoomTileLayout.fg[posX + camY] = 0x5AF;

    case 1:
        if (temp != 0) {
            player = &PLAYER;
            player->posY.i.hi++;
            self->posY.val += 0x10000;
            posY = g_Camera.posY.i.hi + self->posY.i.hi;
            if ((self->ext.generic.unk80.modeS32 + 4) < posY) {
                self->posY.i.hi = (self->ext.generic.unk80.modeS16.unk0 + 4) -
                                  g_Camera.posY.i.hi;
                self[1].ext.stub[0xC] = 1;
                self->step++;
                LOW(self[1].ext.stub[0x8]) ^= 1;
            }
        }

    default:
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;

    case 2:
        if (temp == 0) {
            self->posY.val += ~0xFFFF;
            posY = g_Camera.posY.i.hi + self->posY.i.hi;
            if (posY < self->ext.generic.unk80.modeS32) {
                self->posY.i.hi =
                    self->ext.generic.unk80.modeS16.unk0 - g_Camera.posY.i.hi;
                self->step = 1;
            }
        }
        prim = self->ext.prim;
        prim->x0 = self->posX.i.hi - 8;
        prim->y0 = self->posY.i.hi - 8;
        break;
    }
}

void EntityFloorSpikes(Entity* self) {
    Primitive* prim;
    s16 primIndex;
    s32 var_v1;
    s32 tilePos;
    s32 new_var;
    u8 temp; // !FAKE
    volatile int pad[3];

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180BF8);
        self->hitboxWidth = 12;
        self->hitboxHeight = 12;
        self->attackElement = 1;
        self->attack = 7;
        self->hitboxState = 1;
        self->ext.generic.unk80.modeS32 = self->posY.i.hi + g_Camera.posY.i.hi;

        temp = 4;
        new_var = self->posY.i.hi - 4;
        new_var += g_Camera.posY.i.hi;
        tilePos = ((self->posX.i.hi - temp + g_Camera.posX.i.hi) >> 4) +
                  (((new_var >> 4) * g_CurrentRoom.hSize) * 16);

        g_CurrentRoomTileLayout.fg[tilePos] = 0x102;
        g_CurrentRoomTileLayout.fg[tilePos + 1] = 0x103;
        primIndex = g_api.AllocPrimitives(PRIM_GT4, 1);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        *((s32*)(&self->ext.generic.unk7C)) = prim;
        self->flags |= FLAG_HAS_PRIMS;
        prim->type = 6;
        prim->tpage = 0xF;
        prim->clut = 9;
        prim->u0 = 0x28;
        prim->v0 = 0xC8;
        prim->v1 = prim->u1 = 0x20;
        prim->priority = 0x5F;
        prim->blendMode = 2;
        self->posY.i.hi -= 28;

    case 1:
        self->hitboxState = 1;
        if (self->ext.generic.unk84.unk != 0) {
            self->posY.val += 0x10000;
            new_var = g_Camera.posY.i.hi + self->posY.i.hi;
            var_v1 = g_Camera.posY.i.hi;
            if (new_var > self->ext.generic.unk80.modeS32) {
                self->hitboxState = 0;
                self->posY.i.hi = self->ext.generic.unk80.modeS16.unk0 - var_v1;
            }
        } else {
            self->posY.val += 0xFFFF0000;
            new_var = g_Camera.posY.i.hi + self->posY.i.hi;
            var_v1 = g_Camera.posY.i.hi;
            if (new_var < (self->ext.generic.unk80.modeS32 - 28)) {
                self->posY.i.hi =
                    self->ext.generic.unk80.modeS16.unk0 - 28 - var_v1;
            }
        }
    }
    if (self->ext.generic.unk88.U8.unk0 != 0) {
        func_801C29B0(0x69D);
        self->ext.generic.unk88.S8.unk0 = 0;
    }
    prim = *((s32*)(&self->ext.generic.unk7C));
    prim->x0 = self->posX.i.hi - 16;
    prim->y0 = self->posY.i.hi - 16;
}

// table with globe on it that can be broken
void EntityTableWithGlobe(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CC4);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180EF0, self);
        if (self->hitFlags != 0) {
            func_801C29B0(0x61D);
            self->hitboxState = 0;
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = D_80180F10[self->params];
            SetStep(2);
        }
        break;

    case 2:
        AnimateEntity(D_80180EF8, self);
        break;
    }
}

void func_801B3648(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CD0);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 12;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180F1C, self);
        if (self->hitFlags != 0) {
            func_801C29B0(0x619);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (AnimateEntity(D_80180F30, self) == 0) {
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
            self[1].params = D_80180F4C[self->params];
            newEntity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 2;
                newEntity->posY.i.hi -= 8;
            }
            self->step++;
        }
        break;

    case 3:
        newEntity = self;
        newEntity->animCurFrame = 20;
        break;
    }
}

void func_801B37C0(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CDC);
        if (self->params & 0x100) {
            self->blendMode = 0x30;
        } else {
            self->zPriority = 0x6A;
            self->hitboxWidth = 8;
            self->hitboxHeight = 12;
            self->hitboxOffY = -0xA;
            self->hitboxOffX = 0;
            self->hitboxState = 2;
            CreateEntityFromEntity(0x37, self, &self[1]);
            self[1].params = 0x100;
        }

    case 1:
        if (self->params & 0x100) {
            AnimateEntity(D_80180F74, self);
            break;
        }
        AnimateEntity(D_80180F50, self);
        if (self->hitFlags != 0) {
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        if (self->params > 0x1) {
            CreateEntityFromEntity(E_RELIC_ORB, self, &self[1]);
        } else {
            CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
        }

        self[1].params = D_80180F9C[self->params];
        do { // !FAKE
        } while (0);
        newEntity = AllocEntity(D_8007D858, &D_8007D858[32]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 2;
            newEntity->posY.i.hi -= 8;
        }
        func_801C29B0(0x61D);
        self->step++;

    case 3:
        self->animCurFrame = 4;
        break;

    case 255:
        FntPrint(&D_801B0598, self->animCurFrame); // "charal %x\n"
        if (g_pads[1].pressed & PAD_SQUARE) {
            if (self->params != 0) {
                break;
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
            newEntity = self;
            newEntity->step_s = 0;
        }
        break;
    }
}

void func_801B3A50(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(D_80180CDC);
        self->zPriority = 0x6A;
        self->hitboxWidth = 8;
        self->hitboxHeight = 16;
        self->hitboxOffY = -0xA;
        self->hitboxOffX = 0;
        self->hitboxState = 2;

    case 1:
        AnimateEntity(D_80180F88, self);
        if (self->hitFlags != 0) {
            g_api.PlaySfx(NA_SE_BREAK_CANDLE);
            self->hitboxState = 0;
            SetStep(2);
        }
        break;

    case 2:
        CreateEntityFromEntity(E_HEART_DROP, self, &self[1]);
        self[1].params = D_80180F9C[self->params];
        self->step++;

    case 3:
        self->animCurFrame = 18;
        break;
    }
}

void func_801B3B78() {
    Entity* entity;
    s8 temp_s4 = Random() & 3;
    s16 temp_s3 = ((Random() & 0xF) << 8) - 0x800;
    s32 i;

    for (i = 0; i < 6; i++) {
        entity = AllocEntity(D_8007D858, &D_8007D858[MaxEntityCount]);
        if (entity != NULL) {
            CreateEntityFromEntity(0x38, g_CurrentEntity, entity);
            entity->params = 2;
            entity->ext.generic.unk88.S8.unk1 = 6 - i;
            entity->ext.generic.unk84.S16.unk0 = temp_s3;
            entity->ext.generic.unk88.S8.unk0 = temp_s4;
        }
    }
}

// Id 0x38
INCLUDE_ASM("asm/us/st/nz0/nonmatchings/30958", func_801B3C38);
