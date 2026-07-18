// SPDX-License-Identifier: AGPL-3.0-or-later
#include "top.h"

extern EInit g_EInitFleaRider;

static AnimateEntityFrame unused_anim[] = {
    {0x05, 0x01}, {0x08, 0x02}, {0x09, 0x03},
    {0x09, 0x04}, {0x0A, 0x02}, POSE_LOOP(0)};
static AnimateEntityFrame D_us_80181970[] = {
    {0x02, 0x01}, {0x03, 0x02}, {0x04, 0x03},
    {0x04, 0x04}, {0x04, 0x02}, POSE_LOOP(0),
};
static AnimateEntityFrame D_us_8018197C[] = {
    {0x07, 0x01}, {0x0A, 0x02}, {0x0B, 0x03},
    {0x0B, 0x04}, {0x0C, 0x02}, POSE_LOOP(0),
};
static AnimateEntityFrame unused_anim_2[] = {
    {0x02, 0x01},
    {0x08, 0x02},
    {0x04, 0x03},
    POSE_END,
};
static AnimateEntityFrame unused_anim_3[] = {
    {0x04, 0x03}, {0x09, 0x04}, {0x0A, 0x02}, {0x03, 0x01}, POSE_END,
};

static Point16 D_us_8018199C[] = {
    {0, -64}, {32, -32}, {64, 0},  {32, 32},
    {0, 64},  {-32, 32}, {-64, 0}, {-32, -32},
};

void EntityFleaRider(Entity* self) {
    const int FleaRiderCount = 6;
    Entity* entity;
    Entity* player;
    s16 angle;
    u8 i;

    player = &PLAYER;

    if (self->flags & FLAG_DEAD && self->step < 3) {
        PlaySfxPositional(SFX_FLEA_RIDER_EXPLODE);
        PlaySfxPositional(SFX_FLEA_RIDER_DEATH);
        self->hitboxState = 0;
        self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                       FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA;
        self->animCurFrame = 5;
        self->zPriority -= 2;
        entity = self->ext.fleaRider.entity;
        DestroyEntity(entity);
        self->step = 3;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitFleaRider);
        self->hitboxOffY = -4;
        // fallthrough
    case 1:
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromEntity(E_FLEA_RIDER, self, entity);
            self->ext.fleaRider.entity = entity;
            entity->step = 8;
            self->ext.fleaRider.unk85 = 1;
            self->step++;
        } else {
            DestroyEntity(self);
            break;
        }
        // fallthrough
    case 2:
        MoveEntity();
        if (self->ext.fleaRider.unk88) {
            if (!AnimateEntity(D_us_80181970, self)) {
                self->ext.fleaRider.unk88--;
                if (!self->ext.fleaRider.unk88) {
                    self->poseTimer = 0;
                    self->pose = 0;
                }
            }
        } else {
            AnimateEntity(D_us_8018197C, self);
        }
        if (!self->poseTimer && self->pose == 2) {
            PlaySfxPositional(SFX_WING_FLAP_A);
        }
        self->facingLeft = (GetSideToPlayer() & 1) ^ 1;

        if (!--self->ext.fleaRider.unk85) {
            self->ext.fleaRider.unk88 = 2;
            self->poseTimer = 0;
            self->pose = 0;
            self->ext.fleaRider.unk84 = Random() & 7;
            self->ext.fleaRider.unk85 = 0x80;
        }
        entity = self->ext.fleaRider.entity;
        entity->posX.i.hi = player->posX.i.hi;
        entity->posY.i.hi = player->posY.i.hi;
        i = self->ext.fleaRider.unk84;
        entity->posX.i.hi += D_us_8018199C[i].x;
        entity->posY.i.hi += D_us_8018199C[i].y;

        angle = GetAngleBetweenEntitiesShifted(self, entity);
        self->ext.fleaRider.unk7C =
            AdjustValueWithinThreshold(2, self->ext.fleaRider.unk7C, angle);
        SetEntityVelocityFromAngle(self->ext.fleaRider.unk7C, 0x20);
        break;

    case 3:
        for (i = 0; i < FleaRiderCount; i++) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_FLEA_RIDER, self, entity);
                entity->posX.i.hi += (Random() & 0x3F) - 32;
                entity->posY.i.hi += (Random() & 0x3F) - 32;
                entity->step = 5;
                entity->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
            }
        }
        self->step++;
        // fallthrough
    case 4:
        MoveEntity();
        self->velocityY += FIX(0.125);
        if (self->ext.fleaRider.unk85++ > 8) {
            entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
            if (entity != NULL) {
                DestroyEntity(entity);
                CreateEntityFromEntity(E_EXPLOSION, self, entity);
                entity->params = 1;
            }
            self->ext.fleaRider.unk85 = 0;
        }
        break;

    case 5:
        if (!self->step_s) {
            InitializeEntity(g_EInitFleaRider);
            self->hitboxState = 0;
            self->flags |= FLAG_DESTROY_IF_OUT_OF_CAMERA |
                           FLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA |
                           FLAG_UNK_00200000 | FLAG_UNK_2000;
            self->animCurFrame = 6;
            self->step = 5;
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = (Random() & 7) << 8;
            self->velocityY = FIX(-1.5);
            if (Random() & 1) {
                self->ext.fleaRider.unk7E = 0xD00;
                self->velocityX = -FIX(0.8125);
            } else {
                self->ext.fleaRider.unk7E = -0xD00;
                self->velocityX = FIX(0.8125);
            }
            self->step_s++;
        }
        MoveEntity();
        if (self->velocityY < FIX(1.5)) {
            self->velocityY += FIX(3.0 / 64.0);
        }
        self->velocityX += self->ext.fleaRider.unk7E;
        if (self->velocityX < -FIX(0.8125) || self->velocityX > FIX(0.8125)) {
            self->ext.fleaRider.unk7E = -self->ext.fleaRider.unk7E;
        }
        break;

    case 6:
    case 7:
        break;

    case 8:
        InitializeEntity(g_EInitFleaRider);
        self->flags |= FLAG_UNK_00200000 | FLAG_UNK_2000;
        self->hitboxState = 0;
        self->animCurFrame = 0;
        self->step = 9;
        break;

    case 9:
        break;
    }
}
