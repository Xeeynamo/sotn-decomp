// SPDX-License-Identifier: AGPL-3.0-or-later
#include "lib.h"

#define BREAKABLE_ANIMSET ANIMSET_OVL(12)

enum OVL_EXPORT(BreakableTypes) {
    HANGING_LAMP_FLAME,
    HANGING_LAMP_FLAME_,
    HANGING_LAMP_LONG,
    HANGING_LAMP_SHORT,
    CANDELABRA_TABLE,
    BRAZIER,
    CANDELABRA_WALL_TRIPLE,
    URN,
    JUG,
    BUST,
};

enum OVL_EXPORT(BreakableDebrisSteps) {
    INIT,
    UPDATE,
    DEBRIS_NOP = 256,
};

static AnimateEntityFrame anim_hanging_lamp_long[] = {
    {3, 4}, {3, 5}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hanging_lamp_short[] = {
    {3, 6}, {3, 7}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hanging_lamp_flame[] = {
    {6, 8}, {6, 9}, {6, 10}, {6, 11}, {6, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall_triple[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_hanging_lamp_flame,     // params 0x0000-0xFFF
    anim_hanging_lamp_flame,     // params 0x1000-0x1FFF
    anim_hanging_lamp_long,      // params 0x2000-0x2FFF
    anim_hanging_lamp_short,     // params 0x3000-0x3FFF
    anim_candelabra_table,       // params 0x4000-0x4FFF
    anim_brazier,                // params 0x5000-0x5FFF
    anim_candelabra_wall_triple, // params 0x6000-0x6FFF
    anim_urn,                    // params 0x7000-0x7FFF
    anim_jug,                    // params 0x8000-0x8FFF
    anim_bust,                   // params 0x9000-0x9FFF
};
static u8 hitbox_heights[] = {8, 8, 8, 8, 16, 16, 8, 8, 8, 8, 8};
static u8 explosion_types[] = {
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL,          EXPLOSION_SMALL,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE};
static u16 palettes[] = {
    PAL_NULL,      PAL_NULL,      PAL_NULL,      PAL_NULL,      PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE};
static u16 anim_sets[] = {
    ANIMSET_OVL(1),    ANIMSET_OVL(1),    ANIMSET_OVL(1),    ANIMSET_OVL(1),
    BREAKABLE_ANIMSET, BREAKABLE_ANIMSET, BREAKABLE_ANIMSET, BREAKABLE_ANIMSET,
    BREAKABLE_ANIMSET, BREAKABLE_ANIMSET};
static u8 draw_modes[] = {
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE,
    DRAW_TPAGE2 | DRAW_TPAGE, DRAW_TPAGE2 | DRAW_TPAGE};
static u16 unk_5A[] = {
    0x00, 0x00, 0x00, 0x00, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B, 0x5B};
static u16 hitbox_offsets_y[12] = {0};

extern EInit OVL_EXPORT(EInitBreakable);

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    Entity* entity;
    u16 breakableType;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        if (breakableType < 5) {
            entity = self + 1;
            CreateEntityFromEntity(E_ID_3F, self, entity);
            entity->params = breakableType;
            entity->zPriority = self->zPriority;
        }
        self->drawMode = draw_modes[breakableType];
        self->hitboxHeight = hitbox_heights[breakableType];
        self->animSet = anim_sets[breakableType];
        self->unk5A = unk_5A[breakableType];
        self->palette = palettes[breakableType];
#ifdef INVERTED_STAGE
        self->hitboxOffY = -hitbox_offsets_y[breakableType];
#else
        self->hitboxOffY = hitbox_offsets_y[breakableType];
#endif
    }
    AnimateEntity(animations[breakableType], self);
    if (self->hitParams) {
        entity = AllocEntity(&g_Entities[224], &g_Entities[256]);
        if (entity != NULL) {
            CreateEntityFromCurrentEntity(E_EXPLOSION, entity);
            entity->params = explosion_types[breakableType];
        }
        switch (breakableType) {
        case HANGING_LAMP_FLAME:
            PlaySfxPositional(SFX_GLASS_BREAK_D);
            break;
        case HANGING_LAMP_LONG:
        case HANGING_LAMP_SHORT:
            PlaySfxPositional(SFX_GLASS_BREAK_E);
            break;
        case BUST:
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromCurrentEntity(E_BREAKABLE_DEBRIS, entity);
                entity->params = 256;
            }
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case URN:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        case JUG:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = 3;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
        default:
            g_api.PlaySfx(SFX_CANDLE_HIT);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}

void EntityBreakableHelper(Entity* self) {
    Entity* entity;
    if (!self->step) {
        InitializeEntity(g_EInitInteractable);
        self->drawMode = DRAW_TPAGE2 | DRAW_TPAGE;
        self->animSet = ANIMSET_OVL(1);
    }
    if (!self->params) {
        AnimateEntity(anim_hanging_lamp_long, self);
    } else {
        AnimateEntity(anim_hanging_lamp_short, self);
    }
    entity = self - 1;
    if (entity->entityId != E_BREAKABLE) {
        if (!self->params) {
            self->animCurFrame = 13;
        } else {
            self->animCurFrame = 14;
        }
    }
}

void OVL_EXPORT(EntityBreakableDebris)(Entity* self) {
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
