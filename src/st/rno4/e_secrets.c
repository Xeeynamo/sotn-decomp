// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

void EntityBreakableCrystalFloor(Entity* self) {
    extern s16 g_BreakableCrystalFloorTiles[];
    Entity* newEntity;
    s16* tileLayoutPtr;
    s32 tilePos;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->hitboxWidth = 0x10;
        self->hitboxHeight = 0x10;
        self->hitboxState = 2;
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            i = 0x12;
        } else {
            i = 0;
        }
        tileLayoutPtr = &g_BreakableCrystalFloorTiles[i];
        tilePos = 0x2C;
        tilePos = 0x2C;
        (&g_BgLayers[0].layout[tilePos])[-1] = 0x3FE;
        (&g_BgLayers[0].layout[tilePos])[-2] = 0x3FF;
        (&g_BgLayers[0].layout[tilePos])[-17] = 0x401;
        (&g_BgLayers[0].layout[tilePos])[-18] = 0x402;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        if (g_CastleFlags[RNO4_SECRET_CEILING_OPEN]) {
            DestroyEntity(self);
            return;
        }
        /* fallthrough */
    case 1:
        if (self->hitFlags) {
            PlaySfxPositional(SFX_WALL_DEBRIS_B);
            self->step++;
        }
        break;
    case 2:
        self->ext.breakable.breakCount++;
        tileLayoutPtr =
            &g_BreakableCrystalFloorTiles[self->ext.breakable.breakCount * 6];
        tilePos = 0x2C;
        for (i = 0; i < 2; i++, tileLayoutPtr += 3) {
            (&g_Tilemap.fg[tilePos])[0] = tileLayoutPtr[0];
            (&g_Tilemap.fg[tilePos])[-1] = tileLayoutPtr[1];
            (&g_Tilemap.fg[tilePos])[-2] = tileLayoutPtr[2];
            tilePos -= 0x10;
        }
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->params = 0x11;
        }
        self->ext.breakable.resetTimer = 0x20;
        self->step += 1;
        if (self->ext.breakable.breakCount == 3) {
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x13;
            }
            g_CastleFlags[RNO4_SECRET_CEILING_OPEN] = 1;
            g_api.RevealSecretPassageAtPlayerPositionOnMap(0xCA);
            DestroyEntity(self);
            return;
        }
        break;
    case 3:
        if (!--self->ext.breakable.resetTimer) {
            self->step = 1;
            return;
        }
        break;
    }
}

INCLUDE_ASM("st/rno4/nonmatchings/e_secrets", EntityBreakableWall);

extern Entity g_Entities_224;

void EntityBreakableWallDebris(Entity* self) {
    Collider collider;
    Entity* debris;
#ifdef VERSION_PSP
    s32 collX;
    s32 collY;
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitParticle);
        self->drawFlags = ENTITY_ROTATE;
        self->animSet = ANIMSET_OVL(1);
        if (Random() & 1) {
            self->animCurFrame = 0x26;
        } else {
            self->animCurFrame = 0x27;
        }
        if (self->velocityX < 0) {
            self->facingLeft = 1;
        }
        /* fall through */
    case 1:
        MoveEntity();
#ifdef VERSION_PSP
        self->rotate += ROT(2.8125);
        if (self->params) {
            self->rotate += ROT(2.8125);
        }
#else
        {
            u16 rotation = self->rotate;
            self->rotate = rotation + 0x20;
            if (self->params != 0) {
                self->rotate = rotation + 0x40;
            }
        }
#endif
        self->velocityY += FIX(0.125);
#ifdef VERSION_PSP
        collX = self->posX.i.hi;
        collY = self->posY.i.hi + 6;
        g_api.CheckCollision(collX, collY, &collider, 0);
#else
        g_api.CheckCollision(
            self->posX.i.hi, self->posY.i.hi + 6, &collider, 0);
#endif
        if (collider.effects & EFFECT_SOLID) {
#ifdef VERSION_PSP
            self->posY.i.hi += collider.unk18;
            if (self->velocityY < FIX(0.5)) {
                debris = AllocEntity(&g_Entities[224], &g_Entities[256]);
#else
            self->posY.i.hi = (u16)self->posY.i.hi + (u16)collider.unk18;
            if (self->velocityY <= 0x7FFF) {
                debris = AllocEntity(&g_Entities[224], &g_Entities[256]);
#endif
                if (debris != 0) {
                    CreateEntityFromEntity(E_INTENSE_EXPLOSION, self, debris);
                    debris->params = 0x10;
                }
                DestroyEntity(self);
                return;
            }
            self->velocityY = (-self->velocityY * 2) / 3;
        }
        break;
    }
}
