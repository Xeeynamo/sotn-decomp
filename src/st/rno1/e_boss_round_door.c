// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno1.h"

#ifdef VERSION_PSP
extern s32 E_ID(BOSS_ROUND_HALF);
#endif

extern EInit g_EInitInteractable;
void EntityBossRoundDoor(Entity* self) {
    Entity* child;
    s32 i;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = 0;
        self->animCurFrame = 0;
        child = self + 1;
        for (i = 1; i < 2; i++) {
            CreateEntityFromEntity(E_ID(BOSS_ROUND_HALF), self, child);
            child->params = i + 0x100;
            child++;
            CreateEntityFromEntity(E_ID(BOSS_ROUND_HALF), self, child);
            child->params = i;
            child++;
        }
    case 1:
    default:
        break;
    }
}

extern EInit g_EInitHalfRound;

void EntityBossRoundDoorHalf(Entity* self) {
    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitHalfRound);
        self->drawFlags |= ENTITY_ROTATE;
        if ((self->params & 0xF) % 2) {
            self->rotate = ROT(-90);
        } else {
            self->rotate = 0;
        }
        self->zPriority = (0x40 - self->params) & 0xF;
        if (self->params & 0x100) {
            // Lower half
            self->animCurFrame = 0x64;
        } else {
            // Upper half
            self->animCurFrame = 0x62;
        }
        self->ext.et_801BDA0C.unk84 = 0;
        self->ext.et_801BDA0C.unk80 = 0;
        return;

    case 1:
        self->palette = PAL_FLAG(0x4F);
        return;
    }
}
