#include <game.h>
#include <stdio.h>

typedef enum {
    ENTITY_BREAKABLE = 1,
    ENTITY_EXPLOSION,
    ENTITY_PRICE_DROP,
    ENTITY_INVENTORY_DROP = 10,
} STAGE_ENTITIES;

// OVL stuff
extern u16 D_80194728[0x20];

// Simulation
void* GetStagePtr(u32 psxPtr);
void DrawInit();
void DrawSprite(int x, int y, u8 w, u8 h, u8 u, u8 v, u8 tpage, u8 clut,
                u16 flags);
void DrawSpritePart(Entity* e, SpritePart* p);
void DrawSpriteParts(Entity* e, SpriteParts* p);

// Real functions
s32 Random(void);
void Update(void);
void InitializeEntity(u16 arg0[]);
void DestroyEntity(Entity* item);
Entity* AllocEntity(Entity* start, Entity* end);
s32 AnimateEntity(const u8 frames[], Entity* entity);
void MoveEntity(void);
void FallEntity(void);
void SetStep(u8 step);
void SetSubStep(u8 step);
s16 GetPlayerSide(void);

// Mocked functions
void InitializePads(void);
void ReadPads(void);
void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity);
void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity);
void ReplaceBreakableWithItemDrop(Entity* self);
void FreePrimitives(s32);
s16 AllocPrimitives(PrimitiveType type, s32 count);
void CheckCollision(s32 x, s32 y, Collider* res, s32 unk);
void PreventEntityFromRespawning(Entity* entity);

// Entities
void EntityBreakable(Entity*);
void EntityPrizeDrop(Entity*);
void EntityEquipItemDrop(Entity*);
