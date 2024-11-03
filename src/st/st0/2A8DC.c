// SPDX-License-Identifier: AGPL-3.0-or-later
#include "st0.h"
#include "sfx.h"

void EntitySecretButton(Entity* self) {
    Entity* newEntity;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitSecretStairs);
        self->animCurFrame = 5;
        self->hitboxWidth = 6;
        self->hitboxHeight = 6;
        self->hitboxState = 2;

        if (self->params != 0) {
            self->step = 4;
            self->zPriority += 2;
            break;
        }

        if (g_isSecretStairsButtonPressed) {
            self->animCurFrame = 4;
            self->hitboxState = 0;
            self->palette += 1;
            g_Tilemap.fg[0x1C4] = 0;
            self->step = 3;
            break;
        }
        g_Tilemap.fg[0x1C4] = 0x32F;
        break;

    case 1:
        if (self->hitFlags != 0) {
            g_Tilemap.fg[0x1C4] = 0;
            self->animCurFrame = 4;
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_SECRET_BUTTON, self, newEntity);
                newEntity->params = 1;
            }
            self->step++;
        }
        break;

    case 2:
        if (self->hitFlags != 0) {
            g_api.PlaySfx(SFX_ANIME_SWORD_B);
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
            self->drawFlags = FLAG_DRAW_ROTZ | FLAG_DRAW_UNK8;
            self->unk6C = 0x60;
            self->velocityX = 0;
            self->velocityY = 0;
            self->step_s++;

        case 1:
            MoveEntity();
            self->rotZ += 0x40;
            if (UnkCollisionFunc3(D_801808F8) & 1) {
                self->step_s++;
                break;
            }
            self->velocityY -= FIX(0.125);
            break;

        case 2:
            g_api.PlaySfx(SFX_EXPLODE_FAST_A);
            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = 0x11;
            }
            DestroyEntity(self);
        }
        break;
    }
}

void EntitySecretStairsCeiling(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(g_EInitSecretStairs);
        entity->animCurFrame = 3;
        entity->zPriority += 2;
        if (g_isSecretStairsButtonPressed) {
            entity->animCurFrame = 0;
            entity->step = 3;
        }
        break;

    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            entity->step++;
        }
        break;

    case 2:
        entity->posY.val -= FIX(0.25);
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
        InitializeEntity(g_EInitSecretStairs);
        self->animCurFrame = 1;
        if (self->params == 0) {
            self->ext.secretStairs.unk84 = true;
            newEntity = self + 1;
            for (i = 0; i < 3; i++) {
                CreateEntityFromCurrentEntity(E_SECRET_STAIRS, newEntity);
                newEntity->params = i + 1;
                newEntity++;
            }

        } else {
            self->ext.secretStairs.unk84 = false;
            if (self->params == 3) {
                self->animCurFrame = 2;
                self->zPriority += 1;
                for (tilePos = &D_801808B0; *tilePos != 0xFFFF; tilePos += 2) {
                    if (!g_isSecretStairsButtonPressed) {
                        g_Tilemap.fg[*tilePos] = 0;
                    } else {
                        g_Tilemap.fg[*tilePos] = *(tilePos + 1);
                    }
                }

            } else {
                self->zPriority -= self->params;
            }
        }

        if (g_isSecretStairsButtonPressed) {
            temp_s0 = D_801808A0[self->params].x;
            temp_s1 = D_801808A0[self->params].y;
            self->posX.i.hi = temp_s0 - g_Tilemap.scrollX.i.hi;
            self->posY.i.hi = temp_s1 - g_Tilemap.scrollY.i.hi;
            self->step = 15;
            break;
        }
        self->rotZ = -0x200;
        self->drawFlags |= FLAG_DRAW_ROTZ;
        break;

    case 1:
        if (g_isSecretStairsButtonPressed) {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;

    case 2:
        self->rotZ += 0x10;
        if (self->rotZ == 0) {
            self->drawFlags = FLAG_DRAW_DEFAULT;
            self->step++;
        }
        break;

    case 3:
        if (!self->ext.secretStairs.unk84) {
            // TODO: What is self - 1? In case 0 we create self + 1, but
            // it's not clear what entity comes before us.
            self->posX.i.hi = (self - 1)->posX.i.hi;
            self->posY.i.hi = (self - 1)->posY.i.hi;
            if (self->params == 3) {
                self->posX.i.hi += 16;
                self->posY.i.hi += 16;
            }
        } else {
            g_api.PlaySfx(SFX_DOOR_OPEN);
            self->step++;
        }
        break;

    case 4:
        temp_s0 = D_801808A0[self->params].x;
        temp_s1 = D_801808A0[self->params].y;

        switch (self->step_s) {
        case 0:
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            posY = g_Tilemap.scrollY.i.hi + self->posY.i.hi;
            angle = ratan2(temp_s1 - posY, temp_s0 - posX);
            self->velocityX = rcos(angle) * 12;
            self->velocityY = rsin(angle) * 12;
            self->step_s++;
            break;

        case 1:
            MoveEntity();
            posX = g_Tilemap.scrollX.i.hi + self->posX.i.hi;
            if (temp_s0 == posX) {
                g_api.PlaySfx(SFX_DOOR_CLOSE_A);
                self->posX.i.hi = temp_s0 - g_Tilemap.scrollX.i.hi;
                self->posY.i.hi = temp_s1 - g_Tilemap.scrollY.i.hi;
                if (self->params != 3) {
                    (self + 1)->ext.secretStairs.unk84 = 1;
                } else {
                    tilePos = &D_801808B0;
                    while (*tilePos != 0xFFFF) {
                        g_Tilemap.fg[*tilePos] = *(tilePos + 1);
                        tilePos += 2;
                    }
                }
                self->step++;
            }
            break;
        }
        break;
    }
}
