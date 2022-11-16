#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "dra.h"

// Those entity IDs are common across all stages
#define ENTITY_BREAKABLE 1
#define ENTITY_EXPLOSION 2
#define ENTITY_ITEM_DROP 3
#define ENTITY_NUMERIC_DAMAGE 4
#define ENTITY_RED_DOOR 5
#define ENTITY_INTENSE_EXPLOSION 6
#define ENTITY_ABSORB_ORB 7
#define ENTITY_ROOM_FOREGROUND 8
#define ENTITY_STAGE_NAME_POPUP 9
#define ENTITY_HEART_DROP 10
#define ENTITY_RELIC 11
#define ENTITY_COLLECTABLE 12
#define ENTITY_ENEMY_BLOOD 13
#define ENTITY_UNKNOWN_0D 14

// Flags for entity->unk34
#define ENTITYFLAG_DESTROY_IF_OUT_OF_CAMERA 0x80000000
#define ENTITYFLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA 0x40000000

typedef struct {
    const u8* gfxPage;
    const u8* gfxIndex;
    const u8* clut;
    const u8* collision;
} TileDefinition;

typedef struct {
    const u32 left : 6;
    const u32 top : 6;
    const u32 right : 6;
    const u32 bottom : 6;
    const u32 flags : 8;
} LayoutRect;

typedef struct {
    /* 00 */ const u16* layout;
    /* 04 */ const TileDefinition* tileDef;
    /* 08 */ const u32 rect;
    /* 0C */ const u16 unkC;
    /* 0E */ const u8 unkE;
    /* 0F */ const u8 unkF;
} LayerDef;

typedef struct {
    LayerDef* foreground;
    LayerDef* background;
} LayoutMap;

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 objectId;
    /* 0x6 */ u16 objectRoomIndex;
    /* 0x8 */ u16 subId;
} LayoutObject; // size = 0xA

typedef struct {
    /* 00 */ s16 unk0;
    /* 02 */ s16 unk2;
    /* 04 */ s16 unk4;
    /* 06 */ s16 unk6;
    /* 08 */ s16 unk8;
    /* 0A */ s16 unkA;
    /* 0C */ s16 unkC;
    /* 0E */ s16 unkE;
    /* 10 */ s16 unk10;
    /* 12 */ s16 unk12;
    /* 14 */ s16 unk14;
    /* 16 */ s16 unk16;
    /* 18 */ s16 unk18;
    /* 1A */ s16 unk1A;
} UnkOvelrayStruct; // size = 0xC

typedef void (*PfnOverlayEntry)(void);
typedef void (*PfnLoadObjectLayout)(s32 layoutId);

s32 Random();
void UpdateStageEntities(void);
void CreateEntity(Entity* entity, LayoutObject* initDesc);
void DestroyEntity(Entity*);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(const u8 frames[], Entity* entity);
void MoveEntity(void);
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(const u16 arg0[]);

#endif
