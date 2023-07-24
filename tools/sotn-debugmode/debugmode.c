#include "debugmode.h"

#define DRAW_RESET()                                                           \
    do {                                                                       \
        g_PrimCur = g_PrimFirst;                                               \
    } while (0)
#define FILL_RECT(x, y, w, h, r, g, b, blend)                                  \
    do {                                                                       \
        g_PrimCur->r0 = r;                                                     \
        g_PrimCur->g0 = g;                                                     \
        g_PrimCur->b0 = b;                                                     \
        g_PrimCur->blendMode = blend;                                          \
        g_PrimCur->x0 = x;                                                     \
        g_PrimCur->y0 = y;                                                     \
        g_PrimCur->u0 = w;                                                     \
        g_PrimCur->v0 = h;                                                     \
        g_PrimCur->priority = 0x80;                                            \
        g_PrimCur = g_PrimCur->next;                                           \
    } while (0)

#define DRAW_RECT(x, y, w, h, r, g, b, blend, th)                              \
    do {                                                                       \
        FILL_RECT(x - th, y - th, th, h + th * 2, r, g, b, blend);             \
        FILL_RECT(x, y - th, w, th, r, g, b, blend);                           \
        FILL_RECT(x + w, y - th, th, h + th * 2, r, g, b, blend);              \
        FILL_RECT(x, y + h, w, th, r, g, b, blend);                            \
    } while (0)

#define HIDE_PRIMS(s, c)                                                       \
    do {                                                                       \
        int i;                                                                 \
        Primitive* prim = g_PrimFirst;                                         \
        for (i = 0; i < s; i++) {                                              \
            prim = prim->next;                                                 \
        }                                                                      \
        for (i = 0; i < c; i++) {                                              \
            prim->type |= 0x80;                                                \
            prim = prim->next;                                                 \
        }                                                                      \
    } while (0)

#define SHOW_PRIMS(s, c)                                                       \
    do {                                                                       \
        int i;                                                                 \
        Primitive* prim = g_PrimFirst;                                         \
        for (i = 0; i < s; i++) {                                              \
            prim = prim->next;                                                 \
        }                                                                      \
        for (i = 0; i < c; i++) {                                              \
            prim->type &= ~0x80;                                               \
            prim = prim->next;                                                 \
        }                                                                      \
    } while (0)

typedef struct {
    void (*Init)();
    void (*Update)();
    bool showMenu;
    bool pauseGame;
    const char* name;
} DebugMenu;

void DummyDummyDummy() {}
void InitEntitySpawn(void);
void InitSfxPlayer(void);
void InitDraTest800FD874(void);
void InitCollisionViewer(void);
void InitFlagChecker(void);
void InitStageSelect(void);
void UpdateDraEntitySpawn();
void UpdateStageEntitySpawn();
void UpdateSfxPlayer(void);
void UpdateDraTest800FD874(void);
void UpdateCollisionViewer(void);
void UpdateFlagChecker(void);
void UpdateStageSelect(void);

void Foo() {}

DebugMenu g_DebugMenus[] = {
    DummyDummyDummy,     DummyDummyDummy,        true,  false, "Debug mode",
    InitEntitySpawn,     UpdateDraEntitySpawn,   true,  true,  "DRA spawn",
    InitEntitySpawn,     UpdateStageEntitySpawn, true,  true,  "Stage spawn",
    InitSfxPlayer,       UpdateSfxPlayer,        true,  true,  "Snd player",
    InitDraTest800FD874, UpdateDraTest800FD874,  true,  true,  "Inventory",
    InitCollisionViewer, UpdateCollisionViewer,  false, false, "Collision map",
    InitFlagChecker,     UpdateFlagChecker,      true,  true,  "Castleflags",
    InitStageSelect,     UpdateStageSelect,      true,  true,  "Stages",
};

int g_DebugMode;
bool g_EntitiesPaused;
int g_PrimIndex;
Primitive* g_PrimFirst;
Primitive* g_PrimCur;

void DestroyEntity(Entity* item);
void Init(void) {
    int i;

    g_PrimIndex = g_api.AllocPrimitives(PRIM_TILE, 5);
    if (g_PrimIndex == -1) {
        g_PrimFirst = NULL;
        return;
    }

    g_PrimFirst = &g_PrimBuf[g_PrimIndex];
    DRAW_RESET();
    DRAW_RECT(159, 22, 90, 14, 0xFF, 0xFF, 0xFF, 0x00, 1);
    FILL_RECT(159, 22, 90, 14, 0x50, 0x50, 0x30, 0x41);

    g_EntitiesPaused = false;
    g_DebugMode = 0;
    for (i = 0; i < LEN(g_DebugMenus); i++) {
        g_DebugMenus[i].Init();
    }
}
bool Update(void) {
    BeginFont();
    if (g_pads->tapped & PAD_R2) {
        g_DebugMode++;
        if (g_DebugMode >= LEN(g_DebugMenus)) {
            g_DebugMode = 0;
        }
    }

    if (g_DebugMenus[g_DebugMode].pauseGame != g_EntitiesPaused) {
        g_EntitiesPaused ^= 1;
    }

    if (g_DebugMenus[g_DebugMode].showMenu) {
        SHOW_PRIMS(0, 5);
        SetFontCoord(160, 26);
        FntPrint("%s\n", g_DebugMenus[g_DebugMode].name);
    } else {
        HIDE_PRIMS(0, 5);
    }
    SetFontCoord(8, 48);
    g_DebugMenus[g_DebugMode].Update();

    EndFont();

    return !g_EntitiesPaused;
}