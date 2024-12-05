#ifndef SERVANT_H
#define SERVANT_H
#define SERVANT
#include <common.h>
#include <game.h>

// Unsure if these values are shared or are specific to SERVANT
// May need to move if these init values are used for more entities
typedef enum {
    ENGINE_INIT_SERVANT_0 = 0,
    MENU_SWITCH_SERVANT,
    ENGINE_INIT_SERVANT_2,
    MENU_SAME_SERVANT
} InitializeMode;

#define SERVANT_ENTITY_START 0xD0
#define SERVANT_ID(id) (SERVANT_ENTITY_START + (id))
#define ENTITY_ID_SERVANT SERVANT_ID(1)

/* These are mostly update functions.
 * Update function is called in the engine and is
 * calculated by index = Entity->entityId - 0xD0.
 * "Default" update function is Update as most servants
 * are set to entityId = 0xD1 (index 1)
 * Sub entities tend to use lower pointers
 * Some servants change thier entityId to switch "modes" */
typedef struct {
    void (*Init)(InitializeMode mode);
    PfnEntityUpdate Update;
    void (*Unk08)(Entity* self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
    void (*Unk28)(Entity* self);
    void (*Unk2C)(Entity* self);
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity* self);
} ServantDesc;

typedef struct {
    u16 start, end;
} EntitySearch;

typedef struct ServantEvent {
    /* 0x00 */ struct ServantEvent* next; // next event in the queue
    /* 0x04 */ u32 timer;     // internal timer from 'delay' to the activation 0
    /* 0x08 */ s32 servantId; // the familiar ID that can trigger the event
    /* 0x0C */ s32 roomX;     // only activate in the specified room coords...
    /* 0x10 */ s32 roomY;     // ... where on X negative is the inverted castle
    /* 0x14 */ s32 cameraX;   // only activate on the camera coordinate...
    /* 0x18 */ s32 cameraY;   // ...within the room
    /* 0x1C */ s32 condition; // condition for the event
    /* 0x20 */ u32 delay;     // after how many frames the event is triggered
    /* 0x24 */ s32 entityId;  // ID of the entity to spawn
    /* 0x28 */ s32 params;    // parameters of the entity to spawn
    /* 0x2C */ u32 unk2C;
} ServantEvent;

#define CHECK_NONE -1
#define SERVANT_ENTITY_INDEX 4

#define CHECK_RELIC_FLAG 0x40000000
#define FOR_RELIC(x) CHECK_RELIC_FLAG | x
#define FOR_MIST FOR_RELIC(RELIC_FORM_OF_MIST)

#define CHECK_CASTLE_FLAG 0x80000000
#define FOR_CASTLE_FLAG(x) CHECK_CASTLE_FLAG | x

extern SpriteParts* g_ServantSpriteParts[];
extern u16 g_ServantClut[48];

extern s32 g_PlaySfxStep;
extern EntitySearch g_EntityRanges[];

#ifdef VERSION_PSP
extern ServantDesc D_8D1DC40;
#endif
void DestroyEntity(Entity* entity);

#endif
