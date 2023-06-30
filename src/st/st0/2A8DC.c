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
                CreateEntityFromEntity(0x28, self, newEntity);
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
                CreateEntityFromEntity(2, self, newEntity);
                newEntity->subId = 0x11;
            }
            DestroyEntity(self);
        }
        break;
    }
}

const u32 rodataPadding_801A7AC8 = 0;

void EntitySecretStairsEmitter(Entity* entity) {
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

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntitySecretStairsChunk);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntityStageTitleFadeout);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", EntityStageTitleCard);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", func_801ABBBC);

INCLUDE_ASM("asm/us/st/st0/nonmatchings/2A8DC", func_801AC458);
