// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/rno3/rno3.h"

extern RoomHeader rooms[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

EInit g_EInitCommon;
EInit g_EInitDamageNum;
static SpriteParts* s_SpriteBanks[] = {NULL};
static u_long s_EmptyClut[] = {(u_long)-1};
static u_long* s_Cluts[] = {s_EmptyClut};
PfnEntityUpdate EntityUpdates[UINT8_MAX + 1];
static LayoutEntity s_EmptyLayout[] = {
    {0xFFFE, 0xFFFE, E_NONE, 0, 0},
    {0xFFFF, 0xFFFF, E_NONE, 0, 0},
};
LayoutEntity* entityLayoutHorizontal[64];
LayoutEntity* entityLayoutVertical[64];

static void UnsupportedEntity(Entity* entity) { DestroyEntity(entity); }
static void Noop(void) {}
static void InitRoomEntitiesDummy(s32 layoutId) { (void)layoutId; }
void EntityExplosion(Entity* entity) { UnsupportedEntity(entity); }
void EntityPrizeDrop(Entity* entity) { UnsupportedEntity(entity); }
void EntityEquipItemDrop(Entity* entity) { UnsupportedEntity(entity); }

OVL_API void InitStage(Overlay* o) {
    s32 i;

    memset(o, 0, sizeof(*o));
    for (i = 0; i < LEN(EntityUpdates); i++) {
        EntityUpdates[i] = UnsupportedEntity;
    }
    for (i = 0; i < LEN(entityLayoutHorizontal); i++) {
        entityLayoutHorizontal[i] = s_EmptyLayout;
        entityLayoutVertical[i] = s_EmptyLayout;
    }

    o->Update = Noop;
    o->HitDetection = Noop;
    o->UpdateRoomPosition = Noop;
    o->InitRoomEntities = InitRoomEntitiesDummy;
    o->rooms = rooms;
    o->spriteBanks = s_SpriteBanks;
    o->cluts = s_Cluts;
    o->tileLayers = rooms_layers;
    o->gfxBanks = gfxBanks;
    o->UpdateStageEntities = Noop;
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}
