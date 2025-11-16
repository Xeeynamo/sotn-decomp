// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

extern EInit g_EInitCoffin;
#ifdef VERSION_PSP
extern s32 E_ID(COFFIN);
extern s32 E_ID(BLOOD_SKELETON);
#endif

static AnimateEntityFrame D_us_80181684[] = {
    {.duration = 2, .pose = 0x13},
    {.duration = 2, .pose = 0x14},
    {.duration = 1, .pose = 0x1B},
    {.duration = 1, .pose = 0x1C},
    POSE_END};
static Point16 D_us_80181690[] = {
    {-16, -26}, {1, -16}, {-12, 1}, {14, -13}, {-2, 0}, {1, -17}};
static Point32 D_us_801816A8[] = {
    {-0xC000, -0x28000},  {-0xA000, -0x28000},  {-0x6000, -0x18000},
    {-0x18000, -0x20000}, {-0x12000, -0x20000}, {-0x10000, -0x20000},
};
static s16 D_us_801816D8[] = {10, 10, 8, 4, 0, 4};
static s16 D_us_801816E4[] = {
    FIX(7.0 / 32.0), FIX(17.0 / 128.0), FIX(5.0 / 32.0),
    FIX(3.0 / 32.0), FIX(3.0 / 32.0),   FIX(1.0 / 8.0)};
static s16 D_us_801816F0[] = {16, -64, -32, -64, -128, -48};

void EntityCoffin(Entity* self) {
    Collider collider;
    Entity* newEntity;
    s32 i;
    u8 params;
    Entity* coffinSpawnEntity;
    s16 posX;
    s16 posY;

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitCoffin);
        self->hitboxWidth = 8;
        self->hitboxHeight = 0x14;
        self->hitboxState = 2;
        self->hitPoints = 2;
        self->facingLeft = self->params >> 8;
        self->params &= 0xFF;
        self->zPriority = 0x70;
        break;
    case 1:
        if (self->flags & FLAG_DEAD) {
            g_api.PlaySfx(SFX_WALL_DEBRIS_B);
            self->hitboxState = 0;
            self->step++;
        }
        break;
    case 2:
        if (!AnimateEntity(D_us_80181684, self)) {
            g_api.PlaySfx(SFX_FM_EXPLODE_B);

            for (i = 0; i < 6; i++) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(E_ID(COFFIN), self, newEntity);
                    newEntity->step = 3;
                    newEntity->params = i;
                    newEntity->facingLeft = self->facingLeft;
                    newEntity->ext.coffin.unk80 = GetSideToPlayer() & 1;
                    newEntity->flags |= FLAG_UNK_2000;
                }
            }

            newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
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
            self->step = 0x20;
        }
        break;
    case 3:
        InitializeEntity(g_EInitCoffin);
        self->flags |= FLAG_UNK_2000;
        self->drawFlags |= FLAG_DRAW_ROTATE;
        self->hitboxState = 0;

        params = self->params;
        self->animCurFrame = params + 0x15;
        self->posY.i.hi += D_us_80181690[params].y;
        self->posY.i.hi += 0xE;
        if (self->facingLeft) {
            self->posX.i.hi -= D_us_80181690[params].x;
            self->posX.i.hi -= 8;
        } else {
            self->posX.i.hi += D_us_80181690[params].x;
            self->posX.i.hi += 8;
        }

        if (self->ext.coffin.unk80) {
            self->velocityX = -D_us_801816A8[params].x;
        } else {
            self->velocityX = D_us_801816A8[params].x;
        }

        self->velocityY = D_us_801816A8[params].y;
        break;
    case 4:
        params = self->params;
        MoveEntity();
        self->velocityY += D_us_801816E4[params];
        if (self->ext.coffin.unk80 ^ self->facingLeft) {
            self->rotate -= D_us_801816F0[params];
        } else {
            self->rotate += D_us_801816F0[params];
        }

        posX = self->posX.i.hi;
        posY = self->posY.i.hi;
        posY += D_us_801816D8[params];
        g_api.CheckCollision(posX, posY, &collider, 0);
        if (collider.effects != EFFECT_NONE) {
            self->posY.i.hi += collider.unk18;
            self->velocityY = -self->velocityY / 2;
            if (-self->velocityY < D_us_801816E4[self->params] * 2) {
                newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
                if (newEntity != NULL) {
                    CreateEntityFromEntity(
                        E_INTENSE_EXPLOSION, self, newEntity);
                    newEntity->params = 0x10;
                }
                DestroyEntity(self);
            }
        }
        break;
    case 16:
#include "../pad2_anim_debug.h"
    }
}
