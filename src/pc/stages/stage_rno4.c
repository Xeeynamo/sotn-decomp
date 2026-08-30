// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/rno4/rno4.h"

extern RoomHeader rooms[];
extern RoomDef rooms_layers[];
#ifdef ENABLE_SATURN_STAGES
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
#endif
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 3};
EInit g_EInitDamageNum;
static SpriteParts* s_SpriteBanks[] = {NULL};
static u_long s_EmptyClut[] = {(u_long)-1};
static u_long* s_Cluts[] = {s_EmptyClut};
static GfxBank s_EmptyGfxBank = {.kind = GFX_BANK_NONE};
static GfxBank* s_GfxBanks[UINT8_MAX + 1];
PfnEntityUpdate EntityUpdates[NUM_ENTITIES];
#ifndef ENABLE_SATURN_STAGES
static LayoutEntity s_EmptyLayout[] = {
    {0xFFFE, 0xFFFE, E_NONE, 0, 0},
    {0xFFFF, 0xFFFF, E_NONE, 0, 0},
};
LayoutEntity* entityLayoutHorizontal[64];
LayoutEntity* entityLayoutVertical[64];
#endif

static void UnsupportedEntity(Entity* entity) { DestroyEntity(entity); }
static void Noop(void) {}
void EntityExplosion(Entity* entity) { UnsupportedEntity(entity); }
void EntityPrizeDrop(Entity* entity) { UnsupportedEntity(entity); }
void EntityEquipItemDrop(Entity* entity) { UnsupportedEntity(entity); }
void EntityRedDoor(Entity* entity);
void EntityRoomForeground(Entity* entity);

OVL_API void InitStage(Overlay* o) {
    s32 i;

    memset(o, 0, sizeof(*o));
    for (i = 0; i < LEN(s_GfxBanks); i++) {
        s_GfxBanks[i] = &s_EmptyGfxBank;
    }
    for (i = 0; i < LEN(EntityUpdates); i++) {
        EntityUpdates[i] = UnsupportedEntity;
    }
#ifndef ENABLE_SATURN_STAGES
    for (i = 0; i < LEN(entityLayoutHorizontal); i++) {
        entityLayoutHorizontal[i] = s_EmptyLayout;
        entityLayoutVertical[i] = s_EmptyLayout;
    }
#endif
    EntityUpdates[E_RED_DOOR - 1] = EntityRedDoor;
    EntityUpdates[E_ROOM_FOREGROUND - 1] = EntityRoomForeground;
    o->Update = Update;
    o->HitDetection = Noop;
    o->UpdateRoomPosition = UpdateRoomPosition;
    o->InitRoomEntities = InitRoomEntities;
    o->UpdateStageEntities = UpdateStageEntities;
    o->rooms = rooms;
    o->spriteBanks = s_SpriteBanks;
    o->cluts = s_Cluts;
    o->tileLayers = rooms_layers;
    o->gfxBanks = s_GfxBanks;
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}
