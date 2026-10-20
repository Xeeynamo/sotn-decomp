// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

static AnimateEntityFrame D_us_80180824[] = {{3, 4}, {3, 5}, POSE_LOOP(0)};
extern AnimateEntityFrame D_us_8018082C[] = {{3, 6}, {3, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim3[] = {{6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim4[] = {{5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim5[] = {{5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim6[] = {{5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim7[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim8[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim9[] = {{5, 20}, {255, 255}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* g_RlibBreakableAnimations[] = {
    anim3,
    anim3,
    D_us_80180824,
    D_us_8018082C,
    anim4,
    anim5,
    anim6,
    anim7,
    anim8,
    anim9
};


extern u8 g_RlibBreakableHitboxHeights[];
extern u8 g_RlibBreakableExplosionTypes[];
extern u16 g_RlibBreakablePalettes[];
extern u16 g_RlibBreakableAnimSets[];
extern u8 g_RlibBreakableBlendModes[];
extern u16 g_RlibBreakableUnk5A[];
extern u16 g_RlibBreakableHitboxOffsetsY[];

#ifdef VERSION_PSP
extern s32 E_ID(UNK_1B);
extern s32 E_ID(BREAKABLE_DEBRIS);
#endif

extern EInit g_EInitBreakable;

void EntityBreakable(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        if (breakableType < 5) {
            entity = self + 1;
            CreateEntityFromEntity(E_ID(UNK_1B), self, entity);
            entity->params = breakableType;
            entity->zPriority = self->zPriority;
        }
        self->blendMode = g_RlibBreakableBlendModes[breakableType];
        self->hitboxHeight = g_RlibBreakableHitboxHeights[breakableType];
        self->animSet = g_RlibBreakableAnimSets[breakableType];
        self->unk5A = g_RlibBreakableUnk5A[breakableType];
        self->palette = g_RlibBreakablePalettes[breakableType];
        self->hitboxOffY = g_RlibBreakableHitboxOffsetsY[breakableType];
    }
    AnimateEntity(g_RlibBreakableAnimations[breakableType], self);
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = g_RlibBreakableExplosionTypes[breakableType];
        }
        switch (breakableType) {
        case 2:
        case 3:
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            break;
        case 9:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_ID(BREAKABLE_DEBRIS), entity);
                entity->params = 0x100;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = 3;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        default:
            g_api.PlaySfx(SFX_GLASS_BREAK_C);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}

extern EInit g_EInitInteractable;

void func_us_801AE7AC_from_lib(Entity* self) {
    Entity* breakable;

    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->blendMode = BLEND_TRANSP | BLEND_ADD;
        self->animSet = ANIMSET_OVL(2);
    }

    if (!self->params) {
        AnimateEntity(D_us_80180824, self);
    } else {
        AnimateEntity(D_us_8018082C, self);
    }

    breakable = self - 1;
    if (breakable->entityId != E_BREAKABLE) {
        if (!self->params) {
            self->animCurFrame = 0xD;
        } else {
            self->animCurFrame = 0xE;
        }
    }
}

#define BREAKABLE_ANIMSET ANIMSET_OVL(7)
extern EInit g_EInitParticle;

enum BreakableDebrisSteps {
    INIT,
    UPDATE,
    DEBRIS_NOP = 256,
};

void EntityBreakableDebris(Entity* self) {
    u32 pad[10];

    switch (self->step) {
    case INIT:
        if (self->params & 256) {
            InitializeEntity(g_EInitInteractable);
            self->animSet = BREAKABLE_ANIMSET;
            self->unk5A = 91;
            self->palette = PAL_BREAKABLE;
            self->animCurFrame = 21;
            self->zPriority = 106;
            self->step = DEBRIS_NOP; // No case defined, resulting in nop
        } else {
            InitializeEntity(g_EInitParticle);
        }
        break;
    case UPDATE:
        break;
    }
}
