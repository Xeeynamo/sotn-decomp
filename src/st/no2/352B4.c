// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

#ifdef VERSION_PSP
extern s32 E_ID(ID_22);
extern s32 E_ID(ID_23);
extern s32 E_ID(ID_31);
#endif

static u8 D_us_80180D38[] = {2, 1, 2, 2, 2, 3, 2, 4, 2, 5, 4, 6, -1, 0};

void func_us_801B52B4(Entity* self) {
    s16 angle;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority = 0xA0;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = PAL_OVL(0x161);
        angle = GetAngleBetweenEntitiesShifted(self, &PLAYER);
        SetEntityVelocityFromAngle(angle, 0x28);
        return;
    }
    MoveEntity();
    if (!AnimateEntity(D_us_80180D38, self)) {
        DestroyEntity(self);
    }
}

void func_us_801B5368(Entity* self) {
    Collider collider;
    s16 posX, posY;
    u8 params;

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801808A4);
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->zPriority = 0xA0;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.spikes.rotate = 0;
        params = self->params;

        if (params & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += 0x10;
            self->ext.spikes.rotate += 8;
        }

        if (params & 2) {
            self->velocityX = FIX(-0.5);
            self->rotate -= 0x10;
            self->ext.spikes.rotate -= 8;
        }

        self->velocityY += FIX(0.75);
        self->velocityX += ((Random() & 3) << 0xD) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 0xD) - FIX(0.1875);
        self->ext.spikes.rotate += ((Random() & 3) * 0x10) - 0x18;
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.spikes.rotate;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);

        if (collider.effects) {
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = -self->velocityY / 2;
                self->ext.spikes.rotate *= 4;
            }
            if (collider.effects & EFFECT_UNK_0002) {
                self->velocityX = -self->velocityX;
            }
            if (abs(self->velocityY) < FIX(0.1875)) {
                DestroyEntity(self);
            }
        }
        break;
    }
}

/*
    Function that generates 3 spike chunks that fall when a spike tile is
   destroyed
*/
void func_us_801B5578(u32 tileIdx) {
    s16 posX, posY;
    s32 i;
    Entity* newEnt;

    posX = tileIdx % 0x60 * 16 + 8;
    posY = tileIdx / 0x60 * 16 + 8;

    posX -= g_Tilemap.scrollX.i.hi;
    posY -= g_Tilemap.scrollY.i.hi;

    for (i = 0; i < 3; i++) {
        newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEnt != NULL) {
            CreateEntityFromCurrentEntity(E_ID(ID_22), newEnt);
            newEnt->posX.i.hi = posX;
            newEnt->posY.i.hi = posY;
            newEnt->params = i;
        }
    }

    newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, newEnt);
        newEnt->posX.i.hi = posX;
        newEnt->posY.i.hi = posY;
        newEnt->params = 16;
    }

    newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_ID(ID_23), newEnt);
        newEnt->posX.i.hi = posX;
        newEnt->posY.i.hi = posY;
    }
}

void func_us_801B56A4(u32 tileIdx) {
    s16 posX, posY;
    Entity* newEnt;

    posX = tileIdx % 0x60 * 16 + 8;
    posY = tileIdx / 0x60 * 16 + 8;

    posX -= g_Tilemap.scrollX.i.hi;
    posY -= g_Tilemap.scrollY.i.hi;

    newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_ID(ID_31), newEnt);
        newEnt->posX.i.hi = posX;
        newEnt->posY.i.hi = posY;
    }
}

/*
    Function that checks if the player can destroy the spikes in Olrox's
    quarters
*/
void func_us_801B5750(Entity* self) {
    Entity* player;
    u32 tileIdx;
    u32 newTileType;
    u32 tileType;
    u8 colType;
    s32 i;
    s16 x, y;
    s16 scrollX, scrollY;

    player = &PLAYER;
    switch (self->step) {
    case 0:
        InitializeEntity(D_us_80180844);
        g_GpuBuffers[0].draw.r0 = 0x10;
        g_GpuBuffers[0].draw.g0 = 0x10;
        g_GpuBuffers[0].draw.b0 = 0x10;
        g_GpuBuffers[1].draw.r0 = 0x10;
        g_GpuBuffers[1].draw.g0 = 0x10;
        g_GpuBuffers[1].draw.b0 = 0x10;
        /* fallthrough */
    case 1:
        x = player->posX.i.hi;
        y = player->posY.i.hi;
        scrollX = x + g_Tilemap.scrollX.i.hi;
        scrollY = y + g_Tilemap.scrollY.i.hi;
        tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 0x10;
        tileIdx -= 0x60;

        for (i = 0; i < 3; i++) {
            tileType = g_Tilemap.fg[tileIdx];
            colType = g_Tilemap.tileDef->collision[tileType];
            if (colType > 0xF3 && colType < 0xF8) {
                if (g_api.CheckEquipmentItemCount(
                        ITEM_SPIKE_BREAKER, EQUIP_ARMOR)) {
                    switch (tileType) {
                    case 0x6AE:
                        newTileType = 0x6B1;
                        break;

                    case 0x6AF:
                        newTileType = 0x6B2;
                        break;

                    case 0x6B0:
                        newTileType = 0x6B3;
                        break;
                    }
                    g_Tilemap.fg[tileIdx] = newTileType;
                    func_us_801B5578(tileIdx);
                    g_api.PlaySfx(SFX_EXPLODE_FAST_A);
                } else {
                    func_us_801B56A4(tileIdx);
                }
            }
            tileIdx += 0x60;
        }
        break;
    }
}

void func_us_801B5948(Entity* self) {
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->attackElement = 0x50;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
    } else {
        DestroyEntity(self);
    }
}
