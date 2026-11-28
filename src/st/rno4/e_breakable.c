// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rno4.h"

extern EInit g_EInitBreakable;

#if TARGET == TARGET_PSP
extern s32 E_ID(UNK_3C);
#endif

static AnimateEntityFrame D_us_80180D50[] = {{4, 1}, {4, 2}, {0, 0}, {0, 0}};

static AnimateEntityFrame D_us_80180D58[] = {{4, 0}, {4, 0}, {0, 0}, {0, 0}};

static AnimateEntityFrame D_us_80180D60[] = {
    {5, 1}, {5, 2}, {5, 3}, {5, 4}, {0, 0}, {0, 0}};

static AnimateEntityFrame D_us_80180D6C[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, {0, 0}, {0, 0}};

// TODO: What to do with this? It's part of .bss
#if TARGET == TARGET_PSP
extern AnimateEntityFrame D_pspeu_0929BEB0[];
#else
static AnimateEntityFrame D_us_80180D78[] = {{0, 0}};
#endif

static AnimateEntityFrame D_us_80180D7C[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, {0, 0}, {0, 0}};

static AnimateEntityFrame D_us_80180D88[] = {{5, 17}, {5, 18}, {5, 19}, {0, 0}};

static AnimateEntityFrame D_us_80180D90[] = {{5, 23}, {0, 0}};

static AnimateEntityFrame D_us_80180D94[] = {{5, 22}, {0, 0}};

static AnimateEntityFrame D_us_80180D98[] = {
    {5, 20}, {255, 255}, {5, 21}, {5, 21}, {255, 0}, {0, 0}};

static AnimateEntityFrame* D_us_80180DA4[] = {
    D_us_80180D50,    D_us_80180D58, D_us_80180D60, D_us_80180D6C,

#if TARGET == TARGET_PSP
    D_pspeu_0929BEB0,
#else
    D_us_80180D78,
#endif

    D_us_80180D7C,    D_us_80180D88, D_us_80180D90, D_us_80180D94,
    D_us_80180D98,
};

static u8 D_us_80180DCC[] = {
    0x08, 0x08, 0x28, 0x18, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00};

static u8 D_us_80180DD8[] = {
    0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00};

static u16 D_us_80180DE4[] = {0x0000, 0x0000, 0x025D, 0x025D, 0x025D,
                              0x025D, 0x025D, 0x025D, 0x025D, 0x025D};

static u16 D_us_80180DF8[] = {0x0003, 0x0003, 0x8009, 0x8009, 0x8009,
                              0x8009, 0x8009, 0x8009, 0x8009, 0x8009};

static u16 D_us_80180E0C[] = {0x0000, 0x007C, 0x005B, 0x005B, 0x005B,
                              0x005B, 0x005B, 0x005B, 0x005B, 0x005B};

static u8 D_us_80180E20[] = {
    0x70, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00};

// static u16 D_us_80180E2C[] = {
//  0x0000, 0x0000, 0xFFE8, 0xFFF0,
//  0x0000, 0x0000, 0x0000, 0x0000,
//  0x0000, 0x0000, 0x0000, 0x0000
// };
static u16 D_us_80180E2C[] = {
    0x0000, 0x0000, 0xFFE8, 0xFFF0, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
#if TARGET != TARGET_PSP
    0x0000, 0x0001, 0x0002, 0x0002, 0x0003, 0x0000,
    0x0001, 0x0002, 0x0003
#endif
};

void EntityBreakable(Entity* self) {
    Entity* entity;
#if TARGET == TARGET_PSP
    s32 breakableType;
#else
    u16 breakableType;
#endif

    breakableType = ((self->params >> 0xC) & 0xFFFF) & 0xFFFF;

    if (!self->step) {
        InitializeEntity(g_EInitBreakable);
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 0x14;
        self->blendMode = D_us_80180E20[breakableType & 0xFFFF];
        self->hitboxHeight = D_us_80180DCC[breakableType & 0xFFFF];
        self->animSet = D_us_80180DF8[breakableType & 0xFFFF];
        self->unk5A = D_us_80180E0C[breakableType & 0xFFFF];
        self->palette = D_us_80180DE4[breakableType & 0xFFFF];
        self->hitboxOffY = D_us_80180E2C[breakableType & 0xFFFF];
        if (!breakableType) {
            self->drawFlags = ENTITY_ROTATE;
            self->rotate = ROT(180);
        }
    }
    AnimateEntity(D_us_80180DA4[breakableType & 0xFFFF], self);
    if (self->hitParams) {
        entity =
            AllocEntity(&g_Entities[0xE0], &g_Entities[TOTAL_ENTITY_COUNT]);
        if (entity) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = D_us_80180DD8[breakableType & 0xFFFF];
        }
        switch (breakableType & 0xFFFF) {
        case 0:
            self->drawFlags = ENTITY_DEFAULT;
            self->rotate = 0;
            g_api.PlaySfx(SFX_CANDLE_HIT);

        case 2:
            break;

        case 3:
            break;

        case 9:
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromCurrentEntity(E_ID(UNK_3C), entity);
                entity->params = 0x100;
            }

            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;

        case 7:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }

            PreventEntityFromRespawning(self);
            DestroyEntity(self);

            return;

        case 8:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[0xA0], &g_Entities[0xC0]);
            if (entity) {
                CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, entity);
                entity->params = ((self->params) & 0x1FF);
            }

            PreventEntityFromRespawning(self);
            DestroyEntity(self);

            return;

        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
        }

        ReplaceBreakableWithItemDrop(self);
    }
}

void func_us_801C123C_from_no4(Entity* self) {
// TODO: what???
#if TARGET != TARGET_PSP
    volatile u8 padding[0x28];
#endif

    switch (self->step) {
    case 0:
        InitializeEntity(g_EInitInteractable);
        self->animSet = -0x7FF7;
        self->unk5A = 0x5B;
        self->palette = 0x25D;
        self->animCurFrame = 0x15;
        self->zPriority = 0x6A;
        self->step = 0x100;
    default:
        return;
    }
}
