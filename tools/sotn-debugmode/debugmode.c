#include <game.h>

void Init();
void Update();
void Dummy();

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

ServantDesc g_ServantDesc = {
    Init,  Update, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,
    Dummy, Dummy,  Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,

};

int g_DebugMode;

void InitEntitySpawn(void);
void InitSfxPlayer(void);
void InitDraTest800FD874(void);
void DestroyEntity(Entity* item);
void Init() {
    Entity* e;

    g_DebugMode = 0;
    InitEntitySpawn();
    InitSfxPlayer();
    InitDraTest800FD874();

    // forces to make the game think that the Familiar is actually active
    DestroyEntity(e);
    e = &g_EntityArray[4];
    e->posX.val = PLAYER.posX.val;
    e->posY.val = PLAYER.posY.val;
    e->objectId = 0xD1;
    e->subId = 0;
    e->unk34 = 0x10000;
    e->pfnUpdate = Update;
}

void UpdateEntitySpawn(int variant);
void UpdateSfxPlayer(void);
void UpdateDraTest800FD874(void);
void CollisionDebug(void);

void Update(Entity* e) {
    if (g_pads->tapped & PAD_R2) {
        g_DebugMode++;
    }

    switch (g_DebugMode) {
    case 0:
        FntFlush(-1);
        break;
    case 1:
        UpdateEntitySpawn(0);
        break;
    case 2:
        UpdateEntitySpawn(1);
        break;
    case 3:
        UpdateSfxPlayer();
        break;
    case 4:
        UpdateDraTest800FD874();
        break;
    case 5:
        CollisionDebug();
        break;
    default:
        g_DebugMode = 0;
        break;
    }
}

void Dummy() {}
