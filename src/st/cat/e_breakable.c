// SPDX-License-Identifier: AGPL-3.0-or-later
#include "cat.h"

enum OVL_EXPORT(BreakableTypes) {
    WALL_LAMP_LEFT,
    WALL_LAMP_RIGHT,
    HANGING_LAMP,
    CANDELABRA_SHORT,
    CANDELABRA_TABLE,
    BRAZIER,
    CANDELABRA_WALL_TRIPLE,
    URN,
    JUG,
    BUST,
};

static AnimateEntityFrame anim_wall_lamp_left[] = {
    {6, 4}, {6, 5}, {6, 6}, {6, 7}, {6, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_wall_lamp_right[] = {
    {6, 9}, {6, 10}, {6, 11}, {6, 12}, {6, 13}, POSE_LOOP(0)};
static AnimateEntityFrame anim_hanging_lamp[] = {
    {4, 14}, {4, 15}, {4, 14}, {4, 15}, {6, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_short[] = {
    {5, 5}, {5, 6}, {5, 7}, {5, 8}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_table[] = {
    {5, 9}, {5, 10}, {5, 11}, {5, 12}, POSE_LOOP(0)};
static AnimateEntityFrame anim_brazier[] = {
    {5, 13}, {5, 14}, {5, 15}, {5, 16}, POSE_LOOP(0)};
static AnimateEntityFrame anim_candelabra_wall[] = {
    {5, 17}, {5, 18}, {5, 19}, POSE_LOOP(0)};
static AnimateEntityFrame anim_urn[] = {{5, 23}, POSE_LOOP(0)};
static AnimateEntityFrame anim_jug[] = {{5, 22}, POSE_LOOP(0)};
static AnimateEntityFrame anim_bust[] = {
    {5, 20}, {-1, -1}, {5, 21}, {5, 21}, POSE_END};
static AnimateEntityFrame* animations[] = {
    anim_wall_lamp_left,   // params 0x0000-0x0FFF
    anim_wall_lamp_right,  // params 0x1000-0x1FFF
    anim_hanging_lamp,     // params 0x2000-0x2FFF
    anim_candelabra_short, // params 0x3000-0x3FFF
    anim_candelabra_table, // params 0x4000-0x4FFF
    anim_brazier,          // params 0x5000-0x5FFF
    anim_candelabra_wall,  // params 0x6000-0x6FFF
    anim_urn,              // params 0x7000-0x7FFF
    anim_jug,              // params 0x8000-0x8FFF
    anim_bust,             // params 0x9000-0x9FFF
};

static u8 hitbox_heights[] = {8, 8, 8, 24, 16, 16, 8, 8, 8, 8, 8, 8};
static u8 explosion_types[] = {
    EXPLOSION_SMALL,          EXPLOSION_SMALL,
    EXPLOSION_SMALL,          EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE,
    EXPLOSION_SMALL_MULTIPLE, EXPLOSION_SMALL_MULTIPLE};
static u16 palettes[] = {
    PAL_NONE,      PAL_NONE,      PAL_NONE,      PAL_BREAKABLE, PAL_BREAKABLE,
    PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE, PAL_BREAKABLE};
static u16 anim_sets[] = {
    ANIMSET_OVL(2),  ANIMSET_OVL(2),  ANIMSET_OVL(2),  ANIMSET_OVL(12),
    ANIMSET_OVL(12), ANIMSET_OVL(12), ANIMSET_OVL(12), ANIMSET_OVL(12),
    ANIMSET_OVL(12), ANIMSET_OVL(12), ANIMSET_OVL(12), ANIMSET_OVL(2)};
static u16 unk_5A[] = {0, 0, 0, 91, 91, 91, 91, 91, 91, 91};
static u8 draw_modes[] = {
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_TPAGE | DRAW_TPAGE2,
    DRAW_TPAGE | DRAW_TPAGE2, DRAW_DEFAULT};
static u16 z_priorities[] = {168, 168, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 hitbox_offsets_y[12] = {0};

extern EInit OVL_EXPORT(EInitBreakable);

void OVL_EXPORT(EntityBreakable)(Entity* self) {
    Entity* entity;
    s16* debrisOffsetsY;
    u16 breakableType;
    s32 debrisIndex;
    s32 debrisCount;
    s16 posY;

    breakableType = self->params >> 12;
    if (!self->step) {
        InitializeEntity(OVL_EXPORT(EInitBreakable));
        self->zPriority = g_unkGraphicsStruct.g_zEntityCenter - 20;
        if (z_priorities[breakableType]) {
            self->zPriority = z_priorities[breakableType];
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
        case BUST:
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            entity = AllocEntity(&g_Entities[160], &g_Entities[192]);
            if (entity != NULL) {
                CreateEntityFromEntity(E_HEART_DROP, self, entity);
                entity->params = self->params & 0x1FF;
            }
            PreventEntityFromRespawning(self);
            DestroyEntity(self);
            return;
            g_api.PlaySfx(SFX_GLASS_BREAK_E);
            break;
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
            g_api.PlaySfx(SFX_GLASS_BREAK_B);
            break;
        }
        ReplaceBreakableWithItemDrop(self);
    }
}
