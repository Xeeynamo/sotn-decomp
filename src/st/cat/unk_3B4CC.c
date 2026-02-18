// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

typedef struct {
    u16 unk0;
    u16 unk2;
} unk801BB4CC;

static unk801BB4CC D_us_80181744[] = {{0, 0}, {E_LOSSOTH, 0x8003}};

void func_us_801BB4CC(Entity* self) {
    unk801BB4CC* ptr;
    Entity* tempEntity;

    ptr = D_us_80181744;
    ptr += self->params;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->palette = 0x815E;
        self->drawFlags |= ENTITY_OPACITY | ENTITY_SCALEY | ENTITY_SCALEX;
        self->scaleX = 0x120;
        self->scaleY = 0x200;
        self->opacity = 0;
        self->zPriority = 0x24;
        if (!self->params) {
            self->step = 2;
            self->flags |= FLAG_UNK_10000;
            break;
        }
    case 1:
        tempEntity = self->ext.lossoth.unk9C;
        self->facingLeft = tempEntity->facingLeft;
        self->unk5A = tempEntity->unk5A;
        self->animSet = tempEntity->animSet;
        self->animCurFrame = tempEntity->animCurFrame;
        self->posX.i.hi = tempEntity->posX.i.hi;
        self->posY.i.hi = tempEntity->posY.i.hi - 0x14;
        if (tempEntity->entityId != ptr->unk0) {
            DestroyEntity(self);
        }
        break;

    case 2:
        tempEntity = &PLAYER;
        self->facingLeft = tempEntity->facingLeft;
        self->unk5A = tempEntity->unk5A;
        self->animSet = tempEntity->animSet;
        self->animCurFrame = tempEntity->animCurFrame;
        self->posX.i.hi = tempEntity->posX.i.hi;
        self->posY.i.hi = tempEntity->posY.i.hi - 0x14;
        if (g_Player.status &
            (
#ifdef VERSION_US
                PLAYER_STATUS_UNK40000000 | PLAYER_STATUS_UNK800000 |
                PLAYER_STATUS_UNK400000 | PLAYER_STATUS_WOLF_FORM |
#endif
                PLAYER_STATUS_MIST_FORM | PLAYER_STATUS_BAT_FORM)) {
            self->animCurFrame = 0;
        }
        break;
    }
}
