#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

// Flags for entity->unk34
#define ENTITYFLAG_DESTROY_IF_OUT_OF_CAMERA 0x80000000
#define ENTITYFLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA 0x40000000

typedef struct {
    /* 0x00 */ const u8* gfxPage;
    /* 0x01 */ const u8* gfxIndex;
    /* 0x02 */ const u8* clut;
    /* 0x03 */ const u8* collision;
} TileDefinition; // size = 0x10

typedef struct {
    /* 0x00 */ const u32 left : 6;
    /* 0x01 */ const u32 top : 6;
    /* 0x02 */ const u32 right : 6;
    /* 0x03 */ const u32 bottom : 6;
    /* 0x04 */ const u32 flags : 8;
} LayoutRect; // size = 0x14

typedef struct {
    /* 0x00 */ const u16* layout;
    /* 0x04 */ const TileDefinition* tileDef;
    /* 0x08 */ const u32 rect;
    /* 0x0C */ const u16 unkC;
    /* 0x0E */ const u8 unkE;
    /* 0x0F */ const u8 unkF;
} LayerDef; // size = 0x10

typedef struct {
    LayerDef* foreground;
    LayerDef* background;
} LayoutMap; // size = 0x8

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
