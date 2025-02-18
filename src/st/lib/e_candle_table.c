// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

// This is the definition for the EInit for this function
// I've verified it for PSX, but PSP needs e_init.c
// EInit D_us_801808FC = {ANIMSET_OVL(0x08), 0x00, 0x50, 0x256, 0x005};

static u16 D_us_80181A68[] = {
    0x0103, 0x0203, 0x0303, 0x0403, 0x0503, 0x0603, 0x0703, 0x0000};

#ifdef VERSION_PSP
static u16 D_us_80181A78[] = {0x0903, 0x0A03, 0x0B03, 0x0C03, 0x0D03, 0x0E03,
                              0x0F03, 0x1003, 0x0000, 0x0000, 0x0000, 0x0000};
#else
static u16 D_us_80181A78[] = {0x0903, 0x0A03, 0x0B03, 0x0C03, 0x0D03, 0x0E03,
                              0x0F03, 0x1003, 0x0000, 0x0000, 0x0003, 0x0000};
#endif

extern u32 D_psp_092A5590;
extern s32 D_psp_08B42050;

void EntityCandleTable(Entity* self) {
    Entity* newEntity;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(D_us_801808FC);
        self->zPriority = 0x74;
        if (self->params & 0x400) {
            self->animCurFrame = 0x11;
            self->step = 4;
            break;
        }
        if (self->params & 0x200) {
            self->animCurFrame = 0x12;
            self->step = 4;
            break;
        }
        if (self->params & 0x100) {
            self->drawMode = DRAW_UNK_40 | DRAW_TPAGE2 | DRAW_TPAGE;
            self->drawFlags = FLAG_DRAW_UNK8;
            self->unk6C = 0xC0;
        } else {
            self->zPriority += 4;
            self->hitboxWidth = 8;
            self->hitboxHeight = 12;
            self->hitboxOffX = 0;
            self->hitboxOffY = -10;
            self->hitboxState = 2;
            newEntity = self + 1;
#ifdef VERSION_PSP
            CreateEntityFromEntity(D_psp_092A5590, self, newEntity);
#else
            CreateEntityFromEntity(E_CANDLE_TABLE, self, newEntity);
#endif

            newEntity->params = 0x100;
        }
    case 1:
        if (self->params & 0x100) {
            AnimateEntity(D_us_80181A78, self);
            break;
        }
        AnimateEntity(D_us_80181A68, self);
        if (self->hitFlags) {
            SetStep(2);
        }
        break;
    case 2:
        newEntity = self + 1;
        // I believe this entity to be the stone mask that drops from the candle
        // 0xC is used for other things as well, so I kept the name for now
        CreateEntityFromEntity(E_HEART_DROP, self, newEntity);
        newEntity->params = 1;
        newEntity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (newEntity != NULL) {
            CreateEntityFromEntity(E_EXPLOSION, self, newEntity);
            newEntity->posY.i.hi -= 8;
            newEntity->params = 2;
        }
        self->hitboxState = 0;
        self->step++;
        /* fallthrough */
    case 3:
        self->animCurFrame = 8;
    case 4:
        break;
    case 255:
#ifdef VERSION_PSP
#define DEBUG_REWIND_BUTTON D_psp_08B42050
#endif
#include "../pad2_anim_debug.h"
    }
}
