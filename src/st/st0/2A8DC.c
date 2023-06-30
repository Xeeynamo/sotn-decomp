/*
 * Overlay: ST0
 * Entity: Secret Stairs
 */

#include "st0.h"

void EntitySecretButton(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180628);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 2;

        if (self->subId != 0) {
            self->step = 4;
            self->zPriority += 2;
            break;
        }

        if (g_isSecretStairsButtonPressed) {
            self->animCurFrame = 4;
            self->hitboxState = 0;
            self->palette += 1;
            g_CurrentRoomTileLayout.fg[0x1C4] = 0;
            self->step = 3;
            break;
        }
        g_CurrentRoomTileLayout.fg[0x1C4] = 0x32F;
        break;

    case 1:
        if (self->hitFlags != 0) {
            g_CurrentRoomTileLayout.fg[0x1C4] = 0;
            self->animCurFrame = 4;
            g_api.PlaySfx(0x644);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_SECRET_BUTTON, self, newEntity);
                newEntity->subId = 1;
            }
            self->step++;
        }
        break;

    case 2:
        if (self->hitFlags != 0) {
            g_api.PlaySfx(0x640);
            g_isSecretStairsButtonPressed = true;
            self->hitboxState = 0;
            self->palette += 1;
            self->step++;
        }
        break;

    case 3:
        break;

    case 4:
        switch (self->step_s) {
        case 0:
            self->unk19 = 0xC;
            self->unk6C = 0x60;
            self->accelerationX = 0;
            self->accelerationY = 0;
            self->step_s++;

        case 1:
            MoveEntity();
            self->rotAngle += 0x40;
            if (func_801B4D5C(D_801808F8) & 1) {
                self->step_s++;
                break;
            }
            self->accelerationY -= 0x2000;
            break;

        case 2:
            g_api.PlaySfx(0x652);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->subId = 0x11;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801A7AC8 = 0;

void EntitySecretStairsCeiling(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_80180628);
        entity->animCurFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animCurFrame = 0;
            entity->step = 3;
        }
        break;

    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(NA_SE_SECRET_STAIRS);
            entity->step++;
        }
        break;

    case 2:
        entity->posY.val -= 0x4000;
        if (entity->posY.i.hi < -16) {
            entity->step++;
        }
        break;

    case 3:
        entity->animCurFrame = 0;
        break;
    }
}

void EntitySecretStairs(Entity* self) {
    Entity* newEntity;
    u16* tilePos;
    s32 temp_s0;
    s32 temp_s1;
    s32 posX;
    s32 posY;
    s16 angle;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(D_80180628);
        self->animCurFrame = 1;
        if (self->subId == 0) {
            self->ext.generic.unk84.U8.unk0 = true;
            newEntity = &self[1];
            for (i = 0; i < 3; i++) {
                CreateEntityFromCurrentEntity(E_SECRET_STAIRS, newEntity);
                newEntity->subId = i + 1;
                newEntity++;
            }

        } else {
            self->ext.generic.unk84.U8.unk0 = false;
            if (self->subId == 3) {
                self->animCurFrame = 2;
                self->zPriority += 1;
                for (tilePos = &D_801808B0; *tilePos != 0xFFFF; tilePos += 2) {
                    if (!g_isSecretStairsButtonPressed) {
                        g_CurrentRoomTileLayout.fg[*tilePos] = 0;
                    } else {
                        g_CurrentRoomTileLayout.fg[*tilePos] = *(tilePos + 1);
                    }
                }

            } else {
                self->zPriority -= self->subId;
            }
        }

        if (g_isSecretStairsButtonPressed) {
            temp_s0 = D_801808A0[self->subId].x;
            temp_s1 = D_801808A0[self->subId].y;
            self->posX.i.hi = temp_s0 - g_Camera.posX.i.hi;
            self->posY.i.hi = temp_s1 - g_Camera.posY.i.hi;
            self->step = 15;
            break;
        }
        self->rotAngle = -0x200;
        self->unk19 |= 4;
        break;

    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(0x642);
            self->step++;
        }
        break;

    case 2:
        self->rotAngle += 0x10;
        if (self->rotAngle == 0) {
            self->unk19 = 0;
            self->step++;
        }
        break;

    case 3:
        if (!self->ext.generic.unk84.U8.unk0) {
            self->posX.i.hi = self[-1].posX.i.hi;
            self->posY.i.hi = self[-1].posY.i.hi;
            if (self->subId == 3) {
                self->posX.i.hi += 16;
                self->posY.i.hi += 16;
            }
        } else {
            g_api.PlaySfx(0x642);
            self->step++;
        }
        break;

    case 4:
        temp_s0 = D_801808A0[self->subId].x;
        temp_s1 = D_801808A0[self->subId].y;

        switch (self->step_s) {
        case 0:
            posX = g_Camera.posX.i.hi + self->posX.i.hi;
            posY = g_Camera.posY.i.hi + self->posY.i.hi;
            angle = ratan2(temp_s1 - posY, temp_s0 - posX);
            self->accelerationX = rcos(angle) * 12;
            self->accelerationY = rsin(angle) * 12;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            posX = g_Camera.posX.i.hi + self->posX.i.hi;
            if (temp_s0 == posX) {
                g_api.PlaySfx(0x64F);
                self->posX.i.hi = temp_s0 - g_Camera.posX.i.hi;
                self->posY.i.hi = temp_s1 - g_Camera.posY.i.hi;
                if (self->subId != 3) {
                    self[1].ext.stub[0x8] = 1;
                } else {
                    for (tilePos = &D_801808B0; *tilePos != 0xFFFF;
                         tilePos += 2) {
                        g_CurrentRoomTileLayout.fg[*tilePos] = *(tilePos + 1);
                    }
                }
                self->step++;
            }
            break;
        }
        break;
    }
}
