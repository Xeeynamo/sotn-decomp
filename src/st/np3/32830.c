// SPDX-License-Identifier: AGPL-3.0-or-later
#include "np3.h"

#include "../entrance_stage_entities.h"

void EntityTrapDoor(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        entity->animCurFrame = 0x1B;
        entity->zPriority = 0x6A;
        entity->hitboxWidth = 0x10;
        entity->hitboxHeight = 4;
        entity->hitboxState = 1;

        if (g_TrapDoorFlag == 0) {
            if (PLAYER.posY.val < entity->posY.val) {
                g_Tilemap.fg[0xA8E / 2] = 0x129;
                g_Tilemap.fg[0xA90 / 2] = 0x132;
                DestroyEntity(entity);
                return;
            }
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
        } else {
            entity->animCurFrame = 30;
            g_Tilemap.fg[0xA8E / 2] = 0x6C8;
            g_Tilemap.fg[0xA90 / 2] = 0x6C9;
            entity->step = 128;
        }

    case 1:
        if (entity->hitFlags != 0) {
            g_TrapDoorFlag = 1;
            entity->step++;
        }
        break;

    case 2:
        AnimateEntity(D_80181108, entity);
        break;
    }
}

// left side of the breakable rock, drops pot roast
void EntityMermanRockLeftSide(Entity* self) {
    const int rockBroken = (1 << 0);
    const int wolfFlag = (1 << 2);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_80181144;
        tilePos = 0x1F1;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &D_8018112C;
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_80181120[self->ext.mermanRock.unk84 * 6];
            tilePos = 0x1F1;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi += self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_8018120C[self->ext.mermanRock.unk84 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = -0x8000 - (Random() << 8);
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
            newEntity = AllocEntity(g_Entities + 160, g_Entities + 192);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
                newEntity->params = ITEM_POT_ROAST;
            }
            g_CastleFlags[JEWEL_SWORD_ROOM] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_WOLF_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= wolfFlag;
        }
        break;
    }
}

// right side of the merman room rock, breaks when hit
void EntityMermanRockRightSide(Entity* self) {
    const int rockBroken = (1 << 1);
    const int batFlag = (1 << 3);
    u16* tileLayoutPtr;
    Entity* newEntity;
    s32 tilePos;
    u8* params;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->hitboxState = 2;
        self->hitboxWidth = 16;
        self->hitboxHeight = 24;

        tileLayoutPtr = &D_80181180;
        tilePos = 0x1FD;
        for (i = 0; i < 3; i++) {
            g_BgLayers[0].layout[tilePos] = *tileLayoutPtr;
            g_BgLayers[0].layout[tilePos + 1] = *(tileLayoutPtr + 3);
            tileLayoutPtr++;
            tilePos += 0x30;
        }

        if (g_CastleFlags[JEWEL_SWORD_ROOM] & rockBroken) {
            tileLayoutPtr = &D_80181168;
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }
            self->hitboxState = 1;
            self->step = 2;
        }
        break;

    case 1:
        if (self->hitFlags != 0) {
            tileLayoutPtr = &D_8018115C[(self->ext.mermanRock.unk84 * 6)];
            tilePos = 0x1FD;
            for (i = 0; i < 3; i++) {
                g_Tilemap.fg[tilePos] = *tileLayoutPtr;
                g_Tilemap.fg[tilePos + 1] = *(tileLayoutPtr + 3);
                tileLayoutPtr++;
                tilePos += 0x30;
            }

            g_api.PlaySfx(SFX_WALL_DEBRIS_B);

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
                newEntity->zPriority = 0xA9;
                newEntity->posX.i.hi -= self->ext.mermanRock.unk84 * 16;
                newEntity->posY.i.hi += 16;
            }

            params = &D_8018120C[self->ext.mermanRock.unk84 * 3];

            for (i = 0; i < 3; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_FALLING_ROCK_2, self, newEntity);
                    newEntity->params = *params++;
                    newEntity->velocityX = (Random() << 8) + 0x8000;
                    newEntity->velocityY = -Random() * 0x100;
                    newEntity->facingLeft = 1;
                    newEntity->posY.i.hi += -16 + (i * 16);
                }
            }
            self->ext.mermanRock.unk84++;
        }

        if (self->ext.mermanRock.unk84 >= 2) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= rockBroken;
            self->hitboxState = 1;
            self->step++;
        }
        break;

    case 2:
        if ((self->hitFlags != 0) &&
            (g_Player.status & PLAYER_STATUS_BAT_FORM)) {
            g_CastleFlags[JEWEL_SWORD_ROOM] |= batFlag;
        }
        break;
    }
}

void func_801B5488(Entity* self) {
    u16* tileLayoutPtr;
    s32 tileLayoutPos;
    s32 i;
    s32 j;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        if (g_CastleFlags[CASTLE_FLAG_58] != 0) {
            self->step = 2;
        }
        break;

    case 1:
        if ((g_CastleFlags[JEWEL_SWORD_ROOM] & 12) == 12) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;

    case 2:
        for (tileLayoutPtr = &D_801811AA, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; tileLayoutPos += 0x30, j++, tileLayoutPtr++) {
                g_Tilemap.fg[tileLayoutPos] = *tileLayoutPtr;
            }
        }

        for (tileLayoutPtr = &D_801811E6, i = 0; i < 3; i++) {
            tileLayoutPos = 0x420 + i;
            for (j = 0; j < 5; j++, tileLayoutPtr++) {
                g_BgLayers[0].layout[tileLayoutPos] = *tileLayoutPtr;
                tileLayoutPos += 0x30;
            }
        }

        g_CastleFlags[CASTLE_FLAG_58] |= 1;
        g_api.func_800F1FC4(0x3A);
        self->step++;
        break;
    }
}

void EntityFallingRock2(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s32 temp_a0;
    s32 var_a1;
    s32 new_var2;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        self->animCurFrame = animFrame;
        self->animCurFrame += 31;
        self->zPriority = 0x9F;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.25);
        self->rotZ -= 0x20;
        new_var2 = self->posY.i.hi;
        new_var2 += D_80181204[animFrame];
        g_api.CheckCollision(self->posX.i.hi, new_var2, &collider, 0);

        if (collider.effects & EFFECT_SOLID) {
            if (self->velocityY > FIX(4.0)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != 0) {
                    CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                    newEntity->params = 0x11;
                    if (animFrame == 0) {
                        newEntity->params = 0x13;
                    }
                }
                DestroyEntity(self);
                return;
            }
            self->posY.i.hi = self->posY.i.hi + *(u16*)&collider.unk18;
            temp_a0 = -self->velocityY;
            self->velocityY = -self->velocityY;
            if (temp_a0 < 0) {
                var_a1 = temp_a0 + 7;
            } else {
                var_a1 = temp_a0;
            }
            self->velocityY = temp_a0 - (var_a1 >> 3);
        }
        break;
    }
}

// ID 0x4B
// Stairway piece you can break before Death encounter
void EntityStairwayPiece(Entity* self, u8 arg1, u8 arg2, u8 arg3) {
    Primitive *prim, *prim2, *prim3;
    Entity* newEntity;
    Collider collider;
    s16 primIndex;
    s32 temp;
    s16 x, y;
    u8 v1;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        self->hitboxWidth = 8;
        self->hitboxHeight = 8;
        self->posX.i.hi = 1432 - g_Tilemap.scrollX.i.hi;
        self->posY.i.hi = 200 - g_Tilemap.scrollY.i.hi;
        self->hitPoints = 16;
        if (g_CastleFlags[DEATH_STAIRWAY_BROKEN]) {
            self->hitboxState = 0;
            g_Tilemap.fg[0x4D9] = 0x3EE;
            g_Tilemap.fg[0x539] = 0x3D2;
            self->step = 32;
            break;
        }
        self->hitboxState = 2;
        g_Tilemap.fg[0x4D9] = 0x408;
        g_Tilemap.fg[0x539] = 0x40D;
        break;

    case 1:
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_STOMP_SOFT_A);
        }

        if (self->flags & FLAG_DEAD) {
            self->step++;
        }
        break;

    case 2:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        g_Tilemap.fg[0x4D9] = 0x3EE;
        g_Tilemap.fg[0x539] = 0x3D2;
        g_CastleFlags[DEATH_STAIRWAY_BROKEN] = true;

        newEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EQUIP_ITEM_DROP, self, newEntity);
            newEntity->params = ITEM_TURKEY;
        }

        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
            newEntity->params = 0x10;
            newEntity->zPriority = self->zPriority + 1;
            newEntity->posX.i.hi += 8;
            newEntity->posY.i.hi += 8;
        }

        primIndex = g_api.AllocPrimitives(PRIM_GT4, 16);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }
        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        UnkPolyFunc2(prim);
        v1 = g_Tilemap.tileDef->gfxIndex[0x409];
        arg1 = v1;
        temp = g_Tilemap.tileDef->gfxPage[0x409];
        prim->clut = g_Tilemap.tileDef->clut[0x409];
        prim->tpage = temp + 8;
        arg1 *= 16;
        arg3 = 0xF;
        arg3 = arg1 | arg3;
        prim->u0 = prim->u2 = arg1;
        arg2 = v1 & 0xF0 | 0xF;
        prim->v0 = prim->v1 = v1 & 0xF0;
        prim->u1 = prim->u3 = arg3;
        prim->v2 = prim->v3 = arg2;
        prim->next->x1 = self->posX.i.hi;
        prim->next->y0 = self->posY.i.hi;
        LOW(prim->next->u0) = 0xFFFF0000;
        LOW(prim->next->r1) = 0xFFFF0000;
        LOH(prim->next->r2) = 16;
        LOH(prim->next->b2) = 16;
        prim->priority = self->zPriority;
        prim->drawMode = DRAW_UNK02;
        self->step++;

    case 3:
        prim = self->ext.prim;
        prim2 = prim->next;
        prim2->tpage -= 0x20;
        prim2 = prim->next;
        LOW(prim2->r1) += 0x2000;
        UnkPrimHelper(prim);
        prim3 = prim->next;
        x = prim3->x1;
        y = prim3->y0;
        g_api.CheckCollision(x, (s16)(y + 8), &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            self->posX.i.hi = x;
            self->posY.i.hi = y - 4;
            self->step++;
        }
        break;

    case 4:
        g_api.PlaySfx(SFX_WALL_DEBRIS_B);
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
            newEntity->zPriority = self->zPriority + 1;
        }

        for (i = 0; i < 6; i++) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_FALLING_ROCK, self, newEntity);
                newEntity->params = Random() & 3;
                if (newEntity->params == 3) {
                    newEntity->params = 0;
                }
            }
        }
        DestroyEntity(self);
    }
}

void EntityFallingRock(Entity* self) {
    s32 animFrame = self->params & 0xF;
    Collider collider;
    Entity* newEntity;
    s16 rndAngle;
    s32 rnd;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        self->animCurFrame = animFrame + 31;
        self->rotY = 0x60;
        self->rotX = 0x60;
        self->drawFlags |= FLAG_DRAW_ROTZ | FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
        rnd = (Random() & 0x1F) + 16;
        rndAngle = (Random() * 6) + 0x900;
        self->velocityX = rnd * rcos(rndAngle);
        self->velocityY = rnd * rsin(rndAngle);
        if (self->velocityX > 0) {
            self->facingLeft = 1;
        }
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.125);
        self->rotZ -= 0x20;

        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 8, &collider, 0);
        if (collider.effects & EFFECT_SOLID) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, newEntity);
                newEntity->params = 0x10;
                if (animFrame == 0) {
                    newEntity->params = 0x13;
                }
            }
            DestroyEntity(self);
        }
        break;
    }
}

void EntityLightningThunder(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric3);
        self->zPriority = 0x2A;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        self->facingLeft = Random() & 1;
        g_api.PlaySfxVolPan(SFX_THUNDER_B, 0x40, (self->posX.i.hi >> 0x4) - 8);
    }
    if (AnimateEntity(D_80181214, self) == 0) {
        DestroyEntity(self);
    }
}

// When lightning strikes, we get a bright bolt, but it is against a cloud
// as a background. It's subtle and hard to see, but it's there.
void EntityLightningCloud(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_eInitGeneric3);
        self->zPriority = 0x29;
        self->flags &= ~FLAG_POS_CAMERA_LOCKED;
        // There are 3 shapes of cloud, this picks which one.
        self->animCurFrame = self->params + 0x22;
        self->posX.i.hi = D_80181220[self->params][0];
        self->posY.i.hi = D_80181220[self->params][1];
        self->ext.backgroundLightning.timer = 5;
    }

    if (--self->ext.backgroundLightning.timer == 0) {
        DestroyEntity(self);
    }
}

void EntitySwitch(Entity* self) {
    s32 temp_a0 = GetPlayerCollisionWith(self, 8, 4, 4);
    Entity* player = &PLAYER;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        self->animCurFrame = 9;
        self->zPriority = 0x5E;
        if (g_CastleFlags[CASTLE_FLAG_50]) {
            self->step = 2;
            self->posY.i.hi += 4;
        }
        break;

    case 1:
        if (temp_a0 != 0) {
            player->posY.i.hi++;
            self->posY.val += FIX(0.25);
            if ((g_Tilemap.scrollY.i.hi + self->posY.i.hi) > 193) {
                self->posY.i.hi = 193 - g_Tilemap.scrollY.i.hi;
                g_CastleFlags[CASTLE_FLAG_50] = true;
                g_api.PlaySfx(SFX_SWITCH_CLICK);
                self->step++;
            }
        }
        break;
    }
}

void EntityHeartRoomGoldDoor(Entity* self) {
    Entity* newEntity;
    Primitive* prim;
    s16 primIndex;
    s32 tilePos;
    s32 temp;
    s32 temp2;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_eInitGeneric3);
        self->animCurFrame = 0x25;
        self->zPriority = 0x5E;

        if (g_CastleFlags[CASTLE_FLAG_50] != 0) {
            for (
                tilePos = 0x48, i = 7, self->step = 128, self->animCurFrame = 0;
                i >= 0; tilePos += 0x10, i--) {
                g_Tilemap.fg[tilePos] = 0;
            }
            break;
        }

        primIndex = g_api.AllocPrimitives(PRIM_TILE, 64);
        if (primIndex == -1) {
            DestroyEntity(self);
            return;
        }

        prim = &g_PrimBuf[primIndex];
        self->primIndex = primIndex;
        self->ext.heartRoomGoldDoor.prim = prim;
        self->flags |= FLAG_HAS_PRIMS;
        while (prim != NULL) {
            prim->v0 = 1;
            prim->u0 = 1;
            prim->r0 = 64;
            prim->b0 = 128;
            prim->g0 = 96;
            prim->priority = self->zPriority + 0x18;
            prim->drawMode = DRAW_HIDE;
            prim->p3 = 0;
            prim = prim->next;
        }

        for (tilePos = 0x48, temp = 0x4FA, i = 7; i >= 0; tilePos += 0x10,
            i--) {
            g_Tilemap.fg[tilePos] = temp;
        }
        break;

    case 1:
        if (g_CastleFlags[CASTLE_FLAG_50]) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
            self->step++;
        }
        break;

    case 2:
        self->posY.val += FIX(0.375);
        if (++self->ext.heartRoomGoldDoor.timer & 1) {
            self->posX.i.hi++;
        } else {
            self->posX.i.hi--;
        }

        if ((self->ext.heartRoomGoldDoor.timer % 16) == 0) {
            g_api.PlaySfx(SFX_STONE_MOVE_A);
        }
        temp = temp2 = self->posY.i.hi - 112;
        if (temp2 < 0) {
            temp2 = self->posY.i.hi - 97;
        }

        temp = temp2 >> 4;
        if (temp >= 9) {
            temp = 8;
            self->step = 3;
        }

        for (tilePos = 0x48, i = 0; i < temp; tilePos += 0x10, i++) {
            g_Tilemap.fg[tilePos] = 0;
        }

        if (!(g_Timer & 1)) {
            prim = FindFirstUnkPrim(self->ext.heartRoomGoldDoor.prim);
            if (prim != NULL) {
                prim->p3 = 1;
            }
            if (!(g_Timer & 0xF)) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->posY.i.hi = 188;
                    newEntity->posX.i.hi += -8 + (Random() & 15);
                    newEntity->params = 0x10;
                    newEntity->rotX = newEntity->rotY = 192;
                    newEntity->drawFlags |= FLAG_DRAW_ROTY | FLAG_DRAW_ROTX;
                }
            }
        }
        break;
    }

    if (self->flags & FLAG_HAS_PRIMS) {
        prim = self->ext.heartRoomGoldDoor.prim;
        while (prim != NULL) {
            if (prim->p3 != 0) {
                DoorCascadePhysics(prim);
            }
            prim = prim->next;
        }
    }
}

void EntityUnkId49(Entity* self) {
    u16 temp;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitGeneric);
        break;
    case 1:
        temp = g_Tilemap.fg[0x12 / 2];
        g_Tilemap.fg[0xC / 2] = temp;
        temp = g_Tilemap.fg[0x14 / 2];
        g_Tilemap.fg[0xE / 2] = temp;
        temp = g_Tilemap.fg[0x72 / 2];
        g_Tilemap.fg[0x6C / 2] = temp;
        temp = g_Tilemap.fg[0x74 / 2];
        g_Tilemap.fg[0x6E / 2] = temp;
        temp = g_Tilemap.fg[0xD2 / 2];
        g_Tilemap.fg[0xCC / 2] = temp;
        temp = g_Tilemap.fg[0xD4 / 2];
        g_Tilemap.fg[0xCE / 2] = temp;
        self->step++;
        break;
    }
}
