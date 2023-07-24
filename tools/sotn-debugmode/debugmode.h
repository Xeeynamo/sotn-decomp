#include <game.h>

// Decomment this to make the font readable on some more
// accurate emulators than PCSX Redux and no$psx
// #define DISABLE_FONT_COORD

void InitFont();
void SetFontCoord(int x, int y);
void BeginFont();
void EndFont();

void DbgBeginDrawMenu(void);
void DbgEndDrawMenu(void);
void DbgDrawMenuRect(int x, int y, int w, int h);
void DbgDrawCursor(int x, int y, int w, int h);
Lba* DbgGetStageLba(int stageId);
