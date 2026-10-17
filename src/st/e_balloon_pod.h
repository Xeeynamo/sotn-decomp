// SPDX-License-Identifier: AGPL-3.0-or-later

extern EInit g_EInitBalloonPod;
extern u8 g_RdaiUnk33Anim2[];
extern u8 g_RdaiUnk33Anim3[];
extern u8 g_RdaiUnk33Anim4[];
extern u8 g_RdaiUnk33Anim5[];
#if defined(VERSION_PSP)
extern char g_RdaiUnk33DebugText[];
#endif

#ifndef BALLOON_POD_DEATH_PARTICLE
#define BALLOON_POD_DEATH_PARTICLE E_UNK_34
#define BALLOON_POD_LOCAL_DEATH_PARTICLE
#endif
#if defined(VERSION_PSP)
#define BALLOON_POD_PAD_PRESSED g_pads[1].pressed
#else
extern u16 g_pads_1_pressed;
#define BALLOON_POD_PAD_PRESSED g_pads_1_pressed
#endif

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
        AnimateEntity(g_RdaiUnk33Anim2, self);
        break;

    case 3:
        if (!AnimateEntity(g_RdaiUnk33Anim3, self)) {
            for (i = 0; i < 16; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        BALLOON_POD_DEATH_PARTICLE, self, entity);
                }
            }
            DestroyEntity(self);
        }
        break;

    case 4:
        AnimateEntity(g_RdaiUnk33Anim4, self);
        break;

    case 5:
        if (!AnimateEntity(g_RdaiUnk33Anim5, self)) {
            for (i = 0; i < 16; i++) {
                entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
                if (entity != NULL) {
                    CreateEntityFromEntity(
                        BALLOON_POD_DEATH_PARTICLE, self, entity);
                }
            }
            DestroyEntity(self);
        }
        break;

    case 0xFF:
#if defined(VERSION_PSP)
        FntPrint(g_RdaiUnk33DebugText, self->animCurFrame);
#else
        FntPrint("charal %x\n", self->animCurFrame);
#endif
        if (BALLOON_POD_PAD_PRESSED & PAD_SQUARE) {
            if (self->params) {
                break;
            }
            self->animCurFrame++;
            self->params |= 1;
        } else {
            self->params = 0;
        }
        if (BALLOON_POD_PAD_PRESSED & PAD_CIRCLE) {
            if (self->step_s) {
                break;
            }
            self->animCurFrame--;
            self->step_s |= 1;
        } else {
            self->step_s = 0;
        }
        break;
    }
}

#undef BALLOON_POD_PAD_PRESSED
#ifdef BALLOON_POD_LOCAL_DEATH_PARTICLE
#undef BALLOON_POD_DEATH_PARTICLE
#undef BALLOON_POD_LOCAL_DEATH_PARTICLE
#endif
