// SPDX-License-Identifier: AGPL-3.0-or-later
#include "rlib.h"

// Main entity which shows a table, a candle, and the flickering flame
static AnimateEntityFrame anim_table_candle_flame[] = {
    {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, POSE_LOOP(0)};
// A dark shadow of a flame behind the main candle. Easy to miss it!
static AnimateEntityFrame anim_flame_shadow[] = {
    {3, 9},  {3, 10}, {3, 11}, {3, 12},     {3, 13},
    {3, 14}, {3, 15}, {3, 16}, POSE_LOOP(0)};

#ifdef VERSION_PSP
static s32 D_us_80181A8C = 0;
extern s32 E_ID(CANDLE_TABLE);
#else
static s32 D_us_80181A8C = 3;
#endif

extern EInit g_EInitCandleTable;

// There are actually two flames overlaid. When one is created, it spawns one
// with params 0x100 which tells it to be a faint "shadow" flame.
void EntityCandleTable(Entity* self) {
    Entity* newEntity;

    switch (self->step) { /* irregular */
    case 0:
        InitializeEntity(g_EInitCandleTable);
        self->zPriority = 0x74;

        // This entity also controls the chairs in the same room.
        // Params 0x400 and 0x200 are the chairs on the right and left.
        if (self->params & 0x400) {
            self->animCurFrame = 17;
            self->step = 4;
            break;
        }
        if (self->params & 0x200) {
            self->animCurFrame = 18;
            self->step = 4;
            break;
        }
        if (self->params & 0x100) {
            self->blendMode = BLEND_TRANSP | BLEND_QUARTER;
            self->drawFlags = ENTITY_OPACITY;
            self->opacity = 0xC0;
        } else {
            self->zPriority += 4;
            self->hitboxWidth = 8;
            self->hitboxHeight = 12;
            self->hitboxOffX = 0;
            self->hitboxOffY = 10;
            self->hitboxState = 2;
            // Create the shadow version
            newEntity = self + 1;
            CreateEntityFromEntity(E_ID(CANDLE_TABLE), self, newEntity);
            newEntity->params = 0x100;
        }
    case 1:
        // Test for shadow
        if (self->params & 0x100) {
            AnimateEntity(anim_flame_shadow, self);
            break;
        }
        AnimateEntity(anim_table_candle_flame, self);
        if (self->hitFlags) {
            SetStep(2);
        }
        break;
    case 2:
        // Catch the shadow flame and swap it out for the item
        newEntity = self + 1;
        CreateEntityFromEntity(E_PERSISTENT_ITEM_DROP, self, newEntity);
        newEntity->params = 6; // somehow this encodes what item gets dropped
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
        // Set ourself to just display a table with no candle
        self->animCurFrame = 8;
    case 4:
        break;
    case 255:
#include "../pad2_anim_debug.h"
    }
}
