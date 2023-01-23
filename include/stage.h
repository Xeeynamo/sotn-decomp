#ifndef STAGE_H
#define STAGE_H

#include "common.h"
#include "game.h"
#include "objects.h"
#include "sfx.h"

// Flags for entity->unk34
#define ENTITYFLAG_DESTROY_IF_OUT_OF_CAMERA 0x80000000
#define ENTITYFLAG_DESTROY_IF_BARELY_OUT_OF_CAMERA 0x40000000

typedef struct {
    /* 0x00 */ const u8* gfxPage;
    /* 0x04 */ const u8* gfxIndex;
    /* 0x08 */ const u8* clut;
    /* 0x0C */ const u8* collision;
} TileDefinition; // size = 0x10

typedef struct {
    /* 0x00 */ const u32 left : 6;
    /* 0x04 */ const u32 top : 6;
    /* 0x08 */ const u32 right : 6;
    /* 0x0C */ const u32 bottom : 6;
    /* 0x10 */ const u32 flags : 8;
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
    /* 0x00 */ LayerDef* foreground;
    /* 0x04 */ LayerDef* background;
} LayoutMap; // size = 0x8

typedef struct {
    /* 0x0 */ u16 posX;
    /* 0x2 */ u16 posY;
    /* 0x4 */ u16 objectId;
    /* 0x6 */ u16 objectRoomIndex;
    /* 0x8 */ u16 subId;
} LayoutObject; // size = 0xA

typedef struct {
    /* 00 */ s16 flags;
    /* 02 */ s16 offsetx;
    /* 04 */ s16 offsety;
    /* 06 */ s16 width;
    /* 08 */ s16 height;
    /* 0A */ s16 clut;
    /* 0C */ s16 tileset;
    /* 0E */ s16 left;
    /* 10 */ s16 top;
    /* 12 */ s16 right;
    /* 14 */ s16 bottom;
    /* 16 */ s16 padding;
} SpritePart;

typedef struct {
    /* 00 */ u16 count;
    /* 02 */ SpritePart parts[0];
} SpriteParts; // size = 4 + count*sizeof(SpritePart)

s32 Random();
void Update(void);
void CreateEntity(Entity* entity, LayoutObject* initDesc);
void DestroyEntity(Entity*);
void DestroyEntityFromIndex(s16 index);
s32 AnimateEntity(const u8 frames[], Entity* entity);
void MoveEntity(void);
void FallEntity(void);
Entity* AllocEntity(Entity* start, Entity* end);
void InitializeEntity(u16 arg0[]);

#endif
