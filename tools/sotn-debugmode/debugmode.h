#include <game.h>

#define MENU_END                                                               \
    { -1, -1, -1, NULL }

typedef enum {
    DbgMenu_ActionOnInput,
    DbgMenu_ActionOnChange,
    DbgMenu_ActionOnFrame,
} DbgMenuKind;

typedef struct {
    int param;
    int min;
    int max;
    void (*action)(int param);
    DbgMenuKind kind;
} DbgMenuItem;

typedef struct {
    DbgMenuItem* items;
    int menuWidth;
    int pageScroll;
    int isInit;

    // no need to set all these values
    int nItems;
    int option;
} DbgMenuCtrl;

#define PLAY_MENU_SOUND() g_api.PlaySfx(0x67B)

void InitFont();
void SetFontCoord(int x, int y);
void BeginFont();
void EndFont();
void PrintDefaultFont();
void PauseDebugMode();

extern bool g_ShowDebugMessages;
extern bool g_ShowCollisionLayer;
extern bool g_FrameByFrame;
extern int g_ShowDrawCalls;
extern bool g_ShowHBlankInfo;

void SetHook(int (*hook)(void));

void DbgBeginDrawMenu(void);
void DbgEndDrawMenu(void);
void DbgDrawMenuRect(int x, int y, int w, int h);
void DbgDrawCursor(int x, int y, int w, int h);
Lba* DbgGetStageLba(int stageId);

// High level menu navigator that takes care of all the boilerplate
void DbgMenuNavigate(DbgMenuCtrl* ctrl);
