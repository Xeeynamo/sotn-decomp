// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no2.h"

u8 D_us_80180D38[] = {
    0x2, 0x1, 0x2, 0x2, 0x2,  0x3, 0x2, 0x4,
    0x2, 0x5, 0x4, 0x6, 0xFF, 0x0, 0x0, 0x0,
};

void func_us_801B52B4(Entity* self) {
    s16 angle;
    if (!self->step) {
        InitializeEntity(g_EInitParticle);
        self->zPriority = 0xA0;
        self->animSet = 8;
        self->animCurFrame = 1;
        self->palette = 0x8161;
        angle = GetAngleBetweenEntitiesShifted(self, g_Entities); // & 0xFF;
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
        self->zPriority = 160;
        self->velocityX = 0;
        self->velocityY = 0;
        self->rotate = 0;
        self->ext.et_801B5368.unk80 = 0;
        params = self->params;

        if (params & 1) {
            self->velocityX = FIX(0.5);
            self->rotate += 0x10;
            self->ext.et_801B5368.unk80 += 8;
        }

        if (params & 2) {
            self->velocityX = FIX(-0.5);
            self->rotate -= 0x10;
            self->ext.et_801B5368.unk80 -= 8;
        }

        self->velocityY += FIX(0.75);
        self->velocityX += ((Random() & 3) << 0xD) - FIX(0.1875);
        self->velocityY += ((Random() & 3) << 0xD) - FIX(0.1875);
        self->ext.et_801B5368.unk80 += (((Random() & 3) * 0x10) - 0x18);
        break;

    case 1:
        MoveEntity();
        self->velocityY += FIX(0.15625);
        self->rotate += self->ext.et_801B5368.unk80;
        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        g_api.CheckCollision(posX, posY, &collider, 0);

        if (collider.effects) {
            if (collider.effects & EFFECT_SOLID) {
                self->velocityY = -self->velocityY / 2;
                self->ext.et_801B5368.unk80 *= 4;
            }
            if (collider.effects & EFFECT_UNK_0002) {
                self->velocityX = -self->velocityX;
            }
            if (abs(self->velocityY) < FIX(0.1875)) {
                DestroyEntity(self);
            }
        }
        return;
    }
}

/*
    Function that generates 3 spike chunks that fall when a spike tile is
   destroyed
*/
void func_us_801B5578(u32 tileIdx) {
    s16 screenX, screenY;
    s32 entityIdx;
    Entity* newEnt;

    screenX = tileIdx % 96 * 16 + 8;
    screenY = tileIdx / 96 * 16 + 8;

    screenX -= g_Tilemap.scrollX.i.hi;
    screenY -= g_Tilemap.scrollY.i.hi;

    for (entityIdx = 0; entityIdx < 3; entityIdx++) {
        newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEnt != NULL) {
            CreateEntityFromCurrentEntity(E_UNK_22, newEnt);
            newEnt->posX.i.hi = screenX;
            newEnt->posY.i.hi = screenY;
            newEnt->params = entityIdx;
        }
    }

    newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_INTENSE_EXPLOSION, newEnt);
        newEnt->posX.i.hi = screenX;
        newEnt->posY.i.hi = screenY;
        newEnt->params = 16;
    }

    newEnt = AllocEntity(&g_Entities[224], &g_Entities[256]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_UNK_23, newEnt);
        newEnt->posX.i.hi = screenX;
        newEnt->posY.i.hi = screenY;
    }
}

void func_us_801B56A4(u32 tileIndex) {
    s16 screenX, screenY;
    Entity* newEnt;

    screenX = tileIndex % 96 * 16 + 8;
    screenY = tileIndex / 96 * 16 + 8;

    screenX -= g_Tilemap.scrollX.i.hi;
    screenY -= g_Tilemap.scrollY.i.hi;

    newEnt = AllocEntity(&g_Entities[160], &g_Entities[192]);
    if (newEnt != NULL) {
        CreateEntityFromCurrentEntity(E_UNK_31, newEnt);
        newEnt->posX.i.hi = screenX;
        newEnt->posY.i.hi = screenY;
    }
}

/*
    Function that checks if the player can destroy the spikes in Olrox's
    quarters
*/
void func_us_801B5750(Entity* self) {
    Entity* player;
    s16 scrollX, scrollY;
    u32 tileType, newTileType, colType, tileIdx;
    s32 i;

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
    case 1:
        scrollX = player->posX.i.hi + g_Tilemap.scrollX.i.hi;
        scrollY = player->posY.i.hi + g_Tilemap.scrollY.i.hi;
        tileIdx = (scrollX >> 4) + (scrollY >> 4) * g_Tilemap.hSize * 16;
        tileIdx -= 0x60;

        for (i = 0; i < 3; i++) {
            tileType = g_Tilemap.fg[tileIdx];
            colType = g_Tilemap.tileDef->collision[tileType];
            if (((colType + 12) & 0xFF) < 4) {
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
        return;
    }
}

void func_us_801B5948(Entity* self) {
    if (self->step == 0) {
        InitializeEntity(g_EInitInteractable);
        self->attackElement = 0x50;
        self->attack = 15;
        self->hitboxState = 1;
        self->hitboxWidth = 4;
        self->hitboxHeight = 4;
        self->poseTimer = 4;
        return;
    }
    DestroyEntity(self);
}
