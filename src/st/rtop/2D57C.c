// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rtop.h"
#include <sfx.h>


// new

// tombstone
extern EInit D_us_801805CC;
extern s16 D_us_8018144C[];

void EntityTombstone(Entity* self) {
    Entity* entity;

    if (self->flags & 0x100) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(2, self, entity);
            entity->params = 2;
        }
        DestroyEntity(self);
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(D_us_801805CC);
        self->hitboxOffY = -6;
        self->drawFlags |= 4;
        self->animCurFrame = 0x15;
        break;

    case 1:
        if (UnkCollisionFunc3(D_us_8018144C) & 1) {
            self->step++;
        }
        break;

    case 2:
        if (self->ext.tombstone.timer) {
            self->ext.tombstone.timer--;
        } else if (GetDistanceToPlayerX() < 0x40) {
            self->facingLeft = (GetSideToPlayer() & 1) ^ 1;
            self->ext.tombstone.timer = 0x18;
            self->rotate = 0xFC0;
            PlaySfxPositional(SFX_EXPLODE_ECHO);
            SetStep(3);
        }
        break;

    case 3:
        if (!self->step_s) {
            if (!--self->ext.tombstone.timer) {
                if (self->facingLeft) {
                    self->velocityX = FIX(2);
                } else {
                    self->velocityX  = -FIX(2);
                }
                self->velocityY = -FIX(4);
                self->step_s++;
                return;
            } else if (self->ext.tombstone.timer & 4) {
                self->rotate += 0x20;
                return;
            } else {
                self->rotate -= 0x20;
                return;
            }
            return;
        }

        if (abs(self->velocityY) < FIX(2)) {
            self->animCurFrame = 0x17;
        } else {
            self->animCurFrame = 0x16;
        }
        if (UnkCollisionFunc3(&D_us_8018144C) & 1) {
            PlaySfxPositional(SFX_FM_EXPLODE_B);
            self->animCurFrame = 0x15;
            self->ext.tombstone.timer = 0x80;
            self->rotate = 0;
            self->step--;
        }
        break;
    }
}

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801AD800);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801ADD30);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", EntitySkeletonPieces);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801AE19C);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801AE94C);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801AEC28);

INCLUDE_ASM("st/rtop/nonmatchings/2D57C", func_us_801AEEF4);


