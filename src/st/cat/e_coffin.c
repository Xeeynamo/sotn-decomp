// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitCoffin;
#ifdef VERSION_PSP
extern s32 E_ID(COFFIN);
extern s32 E_ID(BLOOD_SKELETON);
#endif

static AnimateEntityFrame anim_coffin_explode[] = {
    {.duration = 2, .pose = 0x13},
    {.duration = 2, .pose = 0x14},
    {.duration = 1, .pose = 0x1B},
    {.duration = 1, .pose = 0x1C},
    POSE_END};

static Point16 broken_coffin_parts_pos[] = {
    {-16, -26}, {1, -16}, {-12, 1}, {14, -13}, {-2, 0}, {1, -17}};
static Point32 broken_coffin_parts_velocity[] = {
    {FIX(-0.75), FIX(-2.5)}, {FIX(-0.625), FIX(-2.5)}, {FIX(-0.375), FIX(-1.5)},
    {FIX(-1.5), FIX(-2.0)},  {FIX(-1.125), FIX(-2.0)}, {FIX(-1.0), FIX(-2.0)},
};
static s16 coffin_parts_bounce_posY[] = {10, 10, 8, 4, 0, 4};
static s16 coffin_parts_bounce_velocity[] = {
    FIX(7.0 / 32.0), FIX(17.0 / 128.0), FIX(5.0 / 32.0),
    FIX(3.0 / 32.0), FIX(3.0 / 32.0),   FIX(1.0 / 8.0)};
static s16 coffin_parts_rotation[] = {ROT(1.40625), ROT(-5.625), ROT(-2.8125),
                                      ROT(-5.625),  ROT(-11.25), ROT(-4.21875)};

// Params = 0 - spawns a blood skeleton
// Params != 0 - spawns an item drop
void EntityCoffin(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 i;
    u8 params;
    Entity* coffinSpawnEntity;
    s16 posX;
    s16 posY;

    enum Step {
        INIT = 0,
        DESTROYED = 1,
        SPAWN_SUB_ENTITIES = 2,
        BROKEN_COFFIN_PARTS = 3,
        COFFIN_PARTS_BOUNCE = 4,
        DONE = 32
    };

    switch (self->step) {
    case INIT:
        InitializeEntity(g_EInitCoffin);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x14;
        self->hitboxState = 2;
        self->hitPoints = 2;
        self->facingLeft = self->params >> 8;
        self->params &= 0xFF;
        self->zPriority = 0x70;
        break;
    case DESTROYED:
        if (self->flags & FLAG_DEAD) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case SPAWN_SUB_ENTITIES:
        if (!AnimateEntity(anim_coffin_explode, self)) {
            g_api.PlaySfx(SFX_FM_EXPLODE_B);

            // Spawn the broken coffin parts
            for (i = 0; i < 6; i++) {
                newEntity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(COFFIN), self, newEntity);
                    newEntity->step = BROKEN_COFFIN_PARTS;
                    newEntity->params = i;
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->ext.coffin.playerOnLeft = GetSideToPlayer() & 1;
                    newEntity->flags |= FLAG_UNK_2000;
                }
            }

            newEntity =
                AllocEntity(&g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
            if (newEntity != NULL) {
                CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
                newEntity->params = ((self->zPriority + 2) << 8) + 0x11;
            }

            coffinSpawnEntity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (coffinSpawnEntity != NULL) {
                if (!self->params) {
                    CreateEntityFromCurrentEntity(
                        E_ID(BLOOD_SKELETON), coffinSpawnEntity);
                } else {
                    CreateEntityFromCurrentEntity(
                        E_HEART_DROP, coffinSpawnEntity);
                    coffinSpawnEntity->params = self->params;
                }
            }

            self->animCurFrame = 0;
            MakeExplosions();
            self->step = DONE;
        }
        break;
    case BROKEN_COFFIN_PARTS:
        InitializeEntity(g_EInitCoffin);
        self->flags |= FLAG_UNK_2000;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxState = 0;

        params = self->params;
        self->animCurFrame = params + 0x15;
        self->posY.i.hi += broken_coffin_parts_pos[params].y;
        self->posY.i.hi += 0xE;
        if (self->facingLeft) {
            self->posX.i.hi -= broken_coffin_parts_pos[params].x;
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += broken_coffin_parts_pos[params].x;
            self->posX.i.hi += 8;
        }

        if (self->ext.coffin.playerOnLeft) {
            self->velocityX = -broken_coffin_parts_velocity[params].x;
        } else {
            self->velocityX = broken_coffin_parts_velocity[params].x;
        }

        self->velocityY = broken_coffin_parts_velocity[params].y;
        break;
    case COFFIN_PARTS_BOUNCE:
        params = self->params;
        MoveEntity();
        self->velocityY += coffin_parts_bounce_velocity[params];
        if (self->ext.coffin.playerOnLeft ^ self->facingLeft) {
            self->rotate -= coffin_parts_rotation[params];
        } else {
            self->rotate += coffin_parts_rotation[params];
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += coffin_parts_bounce_posY[params];

        // When parts hit the ground they bounce and roll
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;

            // When they hit a minimum valocity despawn the parts
            // in a cloud of dust
            if (-self->velocityY <
                coffin_parts_bounce_velocity[self->params] * 2) {
                newEntity = AllocEntity(
                    &g_Entities[224], &g_Entities[TOTAL_ENTITY_COUNT]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    // params & 0xF0 to EntityIntenseExplosion uses the dust
                    // cloud palette
                    newEntity->params = 16;
                }
                DestroyEntity(self);
            }
        }
        break;
    case 16:
#include "../pad2_anim_debug.h"
    }
}
