// SPDX-License-Identifier: AGPL-3.0-or-later
#include "no3.h"
#include "sfx.h"

// intro owl and leaves
void EntityFlyingOwlAndLeaves(Entity* entity) {
    Tilemap* tilemap = &g_Tilemap;
    Entity* newEntity;
    u16 animFlag = true;
    u16 i;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = 56;
        if (entity->params != 0) {
            entity->drawFlags =
                FLAG_DRAW_ROTX | FLAG_DRAW_ROTY | FLAG_DRAW_UNK8;
            entity->rotX = 0x180;
            entity->rotY = 0x180;
            entity->unk6C = 0x60;
            entity->posY.i.hi = -16;
            entity->zPriority = 0xC1;
        } else {
            entity->drawFlags = FLAG_DRAW_UNK8;
            entity->unk6C = 0x20;
            entity->zPriority = 0xBF;
        }
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->posX.i.hi < 224) {
            entity->ext.generic.unk7C.s = 0;
            entity->step++;
        }
        break;

    case 2:
        if (!(entity->ext.generic.unk7C.s++ & 7)) {
            g_api.PlaySfx(SE_TREE_BRANCH);
        }
        if (entity->posX.i.hi < 192) {
            SetStep(3);
            if (entity->params != 0) {
                entity->velocityX = FIX(8);
                entity->velocityY = FIX(3);
                break;
            }
            entity->velocityX = FIX(10);
            entity->velocityY = FIX(1.625);
            for (i = 0; i < 8; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromCurrentEntity(
                        E_FLYING_OWL_UNK60, newEntity);
                    newEntity->params = i;
                }
            }
        }
        break;

    case 3:
        if (entity->params != 0) {
            animFlag = AnimateEntity(D_801819DC, entity);
            entity->velocityY -= 0xA00;
        } else {
            animFlag = AnimateEntity(D_801819D0, entity);
            if (entity->velocityY > (s32)0xFFFE0000) {
                entity->velocityY -= FIX(0.03125);
            }
        }
        MoveEntity();
        if ((entity->params == 0) && (tilemap->scrollX.i.hi > 0xD80)) {
            entity->step++;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
        break;

    case 4:
        if (entity->velocityY > (s32)0xFFFE0000) {
            entity->velocityY -= FIX(0.03125);
        }
        animFlag = AnimateEntity(D_801819D0, entity);
        MoveEntity();
        if (entity->unk6C < 0x78) {
            entity->unk6C += 2;
        }
        if (entity->posX.i.hi > 288) {
            DestroyEntity(entity);
        } else if (entity->posY.i.hi < -16) {
            DestroyEntity(entity);
        }
    }

    if (!animFlag) {
        PlaySfxPositional(SFX_WING_FLAP_A);
    }
}

// a single leaf from when the owl comes out in the intro
void EntityFallingLeaf(Entity* entity) {
    volatile int pad;

    switch (entity->step) {
    case 0:
        InitializeEntity(g_eInitGeneric2);
        entity->animSet = ANIMSET_OVL(1);
        entity->animCurFrame = (entity->params & 1) + 63;
        entity->zPriority = 0xC1;
        entity->velocityX = D_801819E8[entity->params * 2];
        entity->velocityY = D_801819EC[entity->params * 2];
        entity->unk68 = 0x1C0;
        break;

    case 1:
        if (entity->velocityX > 0) {
            entity->velocityX -= FIX(0.0625);
        }
        if (entity->velocityY < FIX(1.0)) {
            entity->velocityY += 0x400;
        }
        if (entity->velocityY > FIX(1.0)) {
            entity->velocityY -= 0x400;
        }
        MoveEntity();
        break;
    }
}
