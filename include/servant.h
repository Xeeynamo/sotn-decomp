#include "common.h"
#include "game.h"

typedef struct {
    void (*Init)(s32 arg0);
    void (*Update)(Entity* self);
    void (*Unk08)(Entity* self);
    void (*Unk0C)(/*?*/);
    void (*Unk10)(/*?*/);
    void (*Unk14)(/*?*/);
    void (*Unk18)(/*?*/);
    void (*Unk1C)(/*?*/);
    void (*Unk20)(/*?*/);
    void (*Unk24)(/*?*/);
    void (*Unk28)(Entity* self);
    void (*Unk2C)(/*?*/);
    void (*Unk30)(/*?*/);
    void (*Unk34)(/*?*/);
    void (*Unk38)(/*?*/);
    void (*Unk3C)(Entity* self);
} ServantDesc;

typedef struct {
    u16 start, end;
} EntitySearch;

typedef struct {
    /* 0x00 */ struct ServantEvent* next; // next event in the queue
    /* 0x04 */ u32 timer;     // internal timer from 'delay' to the activation 0
    /* 0x08 */ u32 servantId; // the familiar ID that can trigger the event
    /* 0x0C */ s32 roomX;     // only activate in the specified room coords...
    /* 0x10 */ u32 roomY;     // ... where on X negative is the inverted castle
    /* 0x14 */ u32 cameraX;   // only activate on the camera coordinate...
    /* 0x18 */ u32 cameraY;   // ...within the room
    /* 0x1C */ s32 condition; // condition for the event
    /* 0x20 */ u32 delay;     // after how many frames the event is triggered
    /* 0x24 */ u32 entityId;  // ID of the entity to spawn
    /* 0x28 */ u32 params;    // parameters of the entity to spawn
    /* 0x2C */ u32 unk2C;
} ServantEvent;

#define CHECK_NONE -1

#define CHECK_RELIC_FLAG 0x40000000
#define FOR_RELIC(x) CHECK_RELIC_FLAG | x
#define FOR_MIST FOR_RELIC(RELIC_FORM_OF_MIST)

#define CHECK_CASTLE_FLAG 0x80000000
#define FOR_CASTLE_FLAG(x) CHECK_CASTLE_FLAG | x

extern SpriteParts* D_80170040[];
extern u16 D_80170448[];
extern s32 D_801704A8[];
extern s32 D_8017054C[];
extern s32 D_801705EC[];
extern s32* D_801705F4[];
extern Sprite D_80170608[];
extern s32 D_80170658[][5];
extern u16 D_80170720[];
extern s32 D_80171090;
extern EntitySearch D_80171094[];

extern ServantDesc g_ServantDesc;
