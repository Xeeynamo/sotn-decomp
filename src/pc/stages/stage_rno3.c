// SPDX-License-Identifier: AGPL-3.0-or-later
#include <game.h>
#include <string.h>
#include "overlay.h"
#include "../../st/rno3/rno3.h"

extern RoomHeader rooms[];
extern RoomDef rooms_layers[];
extern GfxBank* gfxBanks[];
extern LayoutEntity* entityLayoutHorizontal[];
extern LayoutEntity* entityLayoutVertical[];
extern GAME_IMPORT PfnEntityUpdate* PfnEntityUpdates;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutHorizontal;
extern GAME_IMPORT LayoutEntity** g_pStObjLayoutVertical;

EInit g_EInitCommon = {ANIMSET_DRA(0), 0, 0, 0, 3};
EInit g_EInitDamageNum;
EInit g_EInitParticle;
EInit g_EInitUnkId13;
AnimateEntityFrame g_bigRedFireballAnim[1];
static SpriteParts* s_SpriteBanks[] = {NULL};
static u_long s_EmptyClut[] = {(u_long)-1};
static u_long* s_Cluts[] = {s_EmptyClut};
PfnEntityUpdate EntityUpdates[UINT8_MAX + 1];

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
    for (i = 0; i < LEN(EntityUpdates); i++) {
        EntityUpdates[i] = UnsupportedEntity;
    }
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
    o->gfxBanks = gfxBanks;
    PfnEntityUpdates = EntityUpdates;
    g_pStObjLayoutHorizontal = entityLayoutHorizontal;
    g_pStObjLayoutVertical = entityLayoutVertical;
}
