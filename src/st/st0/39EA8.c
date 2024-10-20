// SPDX-License-Identifier: AGPL-3.0-or-later
#include "game.h"
#include "st0.h"
#include "sfx.h"

#include "../entity_soul_steal_orb.h"

#include "../entity_enemy_blood.h"

extern ObjInit D_80181FE8[];
void EntityRoomForeground(Entity* entity) {
    ObjInit* objInit = &D_80181FE8[entity->params];

    if (entity->step == 0) {
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = objInit->animSet;
        entity->zPriority = objInit->zPriority;
        entity->unk5A = objInit->unk5A;
        entity->palette = objInit->palette;
        entity->drawFlags = objInit->drawFlags;
        entity->drawMode = objInit->drawMode;
        if (objInit->unkC != 0) {
            entity->flags = objInit->unkC;
        }
        if (entity->params >= 5) {
            entity->rotZ = 0x800;
            entity->drawFlags |= FLAG_DRAW_ROTZ;
        }
    }
    AnimateEntity(objInit->animFrames, entity);
}

#include "../popup.h"

INCLUDE_ASM("st/st0/nonmatchings/39EA8", EntityClouds);

INCLUDE_ASM("st/st0/nonmatchings/39EA8", EntityClockTower3D);

INCLUDE_ASM("st/st0/nonmatchings/39EA8", EntityCutscenePhotograph);

void EntityCutscenePhotographFire(Entity* entity) {
    switch (entity->step) {
    case 0:
        InitializeEntity(D_801805D4);
        entity->animSet = ANIMSET_OVL(7);
        entity->unk5A = 0x57;
        entity->palette = 0x8285;
        entity->drawFlags = FLAG_DRAW_UNK8;
        entity->unk6C = 0x40;
        entity->flags &= ~FLAG_POS_CAMERA_LOCKED;
        if (entity->params) {
            entity->unk6C = 0x10;
            entity->zPriority = 0x1FB;
            entity->drawMode = DRAW_UNK_40 | DRAW_TPAGE;
        } else {
            entity->zPriority = 0x1FE;
            entity->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        }
    case 1:
        entity->posY.val -= FIX(1.0);
        if (AnimateEntity(D_801824CC, entity) == 0) {
            DestroyEntity(entity);
        }
        break;
    }
}

INCLUDE_ASM("st/st0/nonmatchings/39EA8", func_801BC5C0);
