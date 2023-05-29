#include "sotn.h"
#include <stdarg.h>

// Mocked data
Pad g_pads[2] = {0, 0};
GameApi g_api;
PlayerStatus g_Status = {0};
Entity* g_CurrentEntity;
s32 D_80097410;
s32 D_80097414;
Multi g_zEntityCenter;
RoomDimensions g_CurrentRoom = {0};
Camera g_Camera = {0};
s32 D_800973FC = 0;
u32 D_8003C8C4 = 0;
u32 g_randomNext = 0;
u8 D_8003BF9C[0x100]; // size unknown
u32 g_StageId = 0;

Primitive g_PrimBuf[MAX_PRIM_COUNT] = {0};
s32 g_entityDestroyed[0x100] = {0}; // size unknown
Entity D_8007D858[MaxEntityCount];
EnemyDef g_EnemyDefs[0x100] = {0};
Entity g_Entities[0x100];

// Entities
void PrintEntity(Entity* self);
void EntityGaibon(Entity* self);

void Dummy() {}

bool ReadFile(bool (*cb)(FILE*), const char* fmtPath, ...) {
    char path[0x100];
    va_list args;

    va_start(args, fmtPath);
    vsnprintf(path, sizeof(path), fmtPath, args);
    va_end(args);

    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "unable to read '%s'", path);
        return false;
    }

    return cb(f);
}

u8 g_Dra[0x80170000 - 0x800A0000];
bool ReadDraCb(FILE* f) {
    return !!fread(g_Dra, 0x10, sizeof(g_Dra) / 0x10, f);
}

u8 g_OvlStage[0x801E0000 - 0x80180000];
void* GetStagePtr(u32 psxPtr) { return g_OvlStage + (psxPtr - 0x80180000); }
bool ReadStageCb(FILE* f) {
    return !!fread(g_OvlStage, 0x10, sizeof(g_OvlStage) / 0x10, f);
}

bool ReadGameChrCb(FILE* f) {
    s32 i;
    char buf[0x2000];

    // Load graphics
    RECT rect = {0, 0, 32, 128};
    for (i = 0; i < 8; i++) {
        rect.x = 512 + i * 64 + 0;
        rect.y = 256;
        fread(buf, sizeof(buf), 1, f);
        LoadImage(&rect, (u_long*)buf);

        rect.x = 512 + i * 64 + 32;
        rect.y = 256;
        fread(buf, sizeof(buf), 1, f);
        LoadImage(&rect, (u_long*)buf);

        rect.x = 512 + i * 64 + 0;
        rect.y = 384;
        fread(buf, sizeof(buf), 1, f);
        LoadImage(&rect, (u_long*)buf);

        rect.x = 512 + i * 64 + 32;
        rect.y = 384;
        fread(buf, sizeof(buf), 1, f);
        LoadImage(&rect, (u_long*)buf);
    }

    // Load palette
    rect.x = 0;
    rect.y = 240;
    rect.w = 256;
    rect.h = 16;
    fread(buf, sizeof(buf), 1, f);
    LoadImage(&rect, (u_long*)buf);

    return true;
}

extern u8 vram[1024 * 1024];
bool ReadVramFromExternalFileCb(FILE* f) {
    return !!fread(vram, sizeof(vram), 1, f);
}

const char* Stages[] = {
    "NO0",  "NO1",  "LIB",  "CAT",  "NO2",  "CHI",  "DAI",  "NP3",  "CEN",
    "NO4",  "ARE",  "TOP",  "NZ0",  "NZ1",  "WRP",  "NO1",  "NO0",  "NO1",
    "DRE",  "NZ0",  "NZ1",  "LIB",  "BO7",  "MAR",  "BO6",  "BO5",  "BO4",
    "BO3",  "BO2",  "BO1",  "BO0",  "ST0",  "RNO0", "RNO1", "RLIB", "RCAT",
    "RNO2", "RCHI", "RDAI", "RNO3", "RCEN", "RNO4", "RARE", "RTOP", "RNZ0",
    "RNZ1", "RWRP", "NO1",  "NO1",  "NO1",  "NO1",  "NO1",  "NO1",  "RNZ1",
    "RBO8", "RBO7", "RBO6", "RBO5", "RBO4", "RBO3", "RBO2", "RBO1", "RBO0",
    "NO1",  "MAD",  "NO3",  "DAI",  "LIB",  "NO1",  "SEL",  "TE1",  "TE2",
    "TE3",  "TE4",  "TE5",  "TOP",  "TE2",  "TE2",  "TE2",  "TE2",
};
bool LoadStage(u32 stageId) {
    const char* stageName;

    g_StageId = stageId;
    if (g_StageId < 80) {
        stageName = Stages[g_StageId];
    } else {
        stageName = "SEL";
    }

    return ReadFile(ReadStageCb, "../../disks/us/ST/%s/%s.BIN", stageName,
                    stageName);
}

void SotnInit(void) {
    InitializePads();
    ReadFile(ReadDraCb, "../../disks/us/DRA.BIN");
    ReadFile(ReadGameChrCb, "../../disks/us/BIN/F_GAME.BIN");
    LoadStage(STAGE_NZ0);

    // obtained with PCSX Redux at http://localhost:8080/api/v1/gpu/vram/raw
    ReadFile(ReadVramFromExternalFileCb, "vram.bin");

    fflush(stdout);

    g_api.FreePrimitives = FreePrimitives;
    g_api.AllocPrimitives = AllocPrimitives;
    g_api.CheckCollision = CheckCollision;
    g_api.PlaySfx = Dummy;
    g_api.enemyDefs = g_EnemyDefs;
    g_CurrentEntity = NULL;
    D_80097410 = 0;
    D_80097414 = 0;
    g_zEntityCenter.unk = 0x80;

    g_CurrentRoom.hSize = 1;
    g_CurrentRoom.vSize = 1;
    g_CurrentRoom.width = 256;
    g_CurrentRoom.height = 240;
    g_CurrentRoom.x = 0;
    g_CurrentRoom.y = 0;

    s32 i;
    for (i = 0; i < LEN(g_PrimBuf); i++) {
        Primitive p = {0};
        g_PrimBuf[i] = p;
    }
    for (i = 0; i < LEN(g_Entities); i++) {
        DestroyEntity(&g_Entities[i]);
    }
    for (i = 0; i < LEN(D_8007D858); i++) {
        DestroyEntity(&D_8007D858[i]);
    }
    for (i = 0; i < LEN(g_entityDestroyed); i++) {
        g_entityDestroyed[i] = 0;
    }

    DestroyEntity(&PLAYER);
    PLAYER.objectId = ENTITY_BREAKABLE;
    PLAYER.pfnUpdate = EntityBreakable;
    PLAYER.posX.i.hi = 120;
    PLAYER.posY.i.hi = 140;

    g_CurrentEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                  &g_Entities[STAGE_ENTITY_START + 0x40]);
    if (g_CurrentEntity) {
        g_CurrentEntity->objectId = -1;
        g_CurrentEntity->pfnUpdate = EntityGaibon;
        g_CurrentEntity->posX.i.hi = 160;
        g_CurrentEntity->posY.i.hi = 100;
    }

    for (i = 0; i < 24; i++) {
        g_CurrentEntity = AllocEntity(&g_Entities[STAGE_ENTITY_START],
                                      &g_Entities[STAGE_ENTITY_START + 0x40]);
        if (g_CurrentEntity) {
            g_CurrentEntity->objectId = ENTITY_PRICE_DROP;
            g_CurrentEntity->subId = i | 0x8000;
            g_CurrentEntity->pfnUpdate = EntityPrizeDrop;
            g_CurrentEntity->posX.i.hi = 8 + i * 10;
            g_CurrentEntity->posY.i.hi = 64 - i * 8;
        }
    }
}

void SotnUpdate(void) {
    ReadPads();
    PrintEntity(&g_Entities[STAGE_ENTITY_START]);

    g_CurrentEntity = &PLAYER;
    g_CurrentEntity->pfnUpdate(g_CurrentEntity);

    Update();
}

SpriteParts* GetAnimFrame(u32 set, u32 frame) {
    SpriteParts* spriteAnim;
#if 0 // game data not imported yet
    SpriteParts** spriteBank;
    if (set > 0) {
        spriteBank = D_800A3B70[set];
    } else {
        spriteBank = g_api.o.spriteBanks[set & 0x7FFF];
    }
    return &spriteBank[frame];
#else
    u32 baseOvl;
    u8* ptrOvl;
    u32* psxPtrSet;
    bool isOvlSet = !!(set & 0x8000);
    if (!isOvlSet) {
        psxPtrSet = (u32*)(g_Dra + 0x3B70 + set * sizeof(u32));
        baseOvl = 0x800A0000;
        ptrOvl = g_Dra;
    } else {
        u32 psxSpriteBanks = *(u32*)(g_OvlStage + 0x14);
        u32 rawOffset = (set & 0x7FFF) * 4 + (psxSpriteBanks - 0x80180000);
        psxPtrSet = (u32*)(g_OvlStage + rawOffset);
        baseOvl = 0x80180000;
        ptrOvl = g_OvlStage;
    }

    if (*psxPtrSet == 0) {
        return NULL;
    }

    u32* ptrSet = (u32*)(ptrOvl + (*psxPtrSet - baseOvl));
    u32* psxPtrFrame = ptrSet + frame;
    if (*psxPtrFrame == 0) {
        return NULL;
    }
#endif

    return (SpriteParts*)(ptrOvl + (*psxPtrFrame - baseOvl));
}

void DrawSpriteParts(Entity* e, SpriteParts* p);
void SotnRender(void) {
    // Simulate what func_800EBBAC is doing to render the entities
    s32 i;
    for (i = 0; i < LEN(g_Entities); i++) {
        Entity* e = &g_Entities[i];
        if (e->pfnUpdate == NULL)
            continue;

        SpriteParts* spriteAnim = GetAnimFrame(e->animSet, e->animCurFrame);
        if (spriteAnim == NULL)
            continue;
        DrawSpriteParts(e, spriteAnim);
    }

    FntFlush(-1);
}

void PrintEntity(Entity* self) {
    FntPrint("pos:%d,%d", self->posX.i.hi, self->posY.i.hi);
    FntPrint("step:%d,%d", self->step, self->step_s);
    FntPrint("animFrameIdx:%d", self->animFrameIdx);
    FntPrint("animFrameDuration:%d", self->animFrameDuration);
    FntPrint("animSet:%X", (u16)self->animSet);
    FntPrint("animCurFrame:%d", self->animCurFrame);
}

void PrintSpritePart(SpritePart* p) {
    FntPrint("size %d, %d", p->width, p->height);
    FntPrint("pivot %d, %d", p->offsetx, p->offsety);
    FntPrint("flags 0x%X", p->flags);
    FntPrint("clut 0x%X", p->clut);
    FntPrint("tileset 0x%X", p->tileset);
    FntPrint("rect %d,%d,%d,%d", p->left, p->top, p->right, p->bottom);
}