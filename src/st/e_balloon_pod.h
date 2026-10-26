// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitBalloonPod;
static AnimateEntityFrame anim_tentacles_waving[] = {{4, 19}, {4, 20}, {4, 21}, {4, 22}, {4, 23}, {4, 24}, {4, 25}, {4, 26}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bursting_open[] = {{4, 21}, {4, 27}, {4, 28}, {4, 29}, {4, 30}, {4, 31}, POSE_END};
static AnimateEntityFrame anim_floor_pulsating[] = {{4, 32}, {4, 33}, {4, 34}, {4, 35}, {4, 36}, {4, 35}, {4, 34}, {4, 33}, POSE_LOOP(0)};
static AnimateEntityFrame anim_floor_bursting[] = {{4, 34}, {4, 37}, {4, 38}, {4, 39}, {4, 40}, {4, 41}, POSE_END};
static AnimateEntityFrame anim_seed_flapping[] = {{4, 42}, {4, 43}, {4, 44}, {4, 43}, POSE_LOOP(0)};

void EntityBalloonPod(Entity* self) {
    Entity* entity;
    s32 i;

    if ((self->flags & FLAG_DEAD) && !self->ext.rdaiUnk33.deathStarted) {
        PlaySfxPositional(SFX_EXPLODE_B);
        if (self->params) {
            SetStep(5);
        } else {
            SetStep(3);
        }
        self->ext.rdaiUnk33.deathStarted = 1;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBalloonPod);
        if (self->params) {
            SetStep(4);
            break;
        }
        self->hitboxOffY = -4;
        SetStep(2);
        break;

    case 2:
        AnimateEntity(anim_tentacles_waving, self);
        break;

    case 3:
        if (!AnimateEntity(anim_bursting_open, self)) {
            for (i = 0; i < 16; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_BALLOON_POD_SEED, self, entity);
                }
            }
            DestroyEntity(self);
        }
        break;

    case 4:
        AnimateEntity(anim_floor_pulsating, self);
        break;

    case 5:
        if (!AnimateEntity(anim_floor_bursting, self)) {
            for (i = 0; i < 16; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        E_BALLOON_POD_SEED, self, entity);
                }
            }
            DestroyEntity(self);
        }
        break;

    case 0xFF:
    #include "pad2_anim_debug.h"
    }
}

extern EInit g_EInitBalloonPodSeed;

void EntityBalloonPodSeed(Entity* self) {
    s32 speed;
    s16 angle;

    if (self->flags & FLAG_DEAD) {
        PlaySfxPositional(SFX_SMALL_FLAME_IGNITE);
        self->pfnUpdate = EntityExplosion;
        self->step = 0;
        self->params = 0;
        return;
    }

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitBalloonPodSeed);
        self->facingLeft = Random() & 1;
        speed = (Random() & 0x1F) + 0x10;
        angle = Random() * 6 + 0x900;
        self->velocityX = speed * rcos(angle);
        self->velocityY = speed * rsin(angle);
        self->posX.val += self->velocityX * 4;
        self->posY.val += self->velocityY * 4;
        self->ext.imp.timer = (Random() & 0x1F) + 0x10;
        self->rotate = angle;
        // fallthrough
    case 1:
        AnimateEntity(anim_seed_flapping, self);
        MoveEntity();
        self->velocityX -= self->velocityX / 16;
        self->velocityY -= self->velocityY / 16;
        if (!--self->ext.imp.timer) {
            self->velocityX = 0;
            self->step++;
        }
        break;

    case 2:
        MoveEntity();
        if (self->velocityY < FIX(0.5)) {
            self->velocityY += FIX(0.03125);
        }
#if defined(VERSION_PSP)
        angle = self->rotate += ROT(11.25);
        self->velocityX = (rcos(angle) << 15) >> 12;
#else
        self->rotate += ROT(11.25);
        self->velocityX = (rcos(self->rotate) << 15) >> 12;
#endif
        break;
    }
}

