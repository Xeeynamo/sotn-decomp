#include "debugmode.h"

typedef struct {
    u32 unk00;
    u32 unk04;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    u32 unk10;
    u32 unk14;
    u32 unk18;
    u32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
} FntStream;

const s16 DefaultFontX = 8;
const s16 DefaultFontY = 48;

int g_FontStreamId;
int g_PrevFontStreamId;
s16 g_FontCoordX;
s16 g_FontCoordY;
FntStream Font[];

void InitFont() {
    g_FontStreamId = 0;
    g_FontCoordX = DefaultFontX;
    g_FontCoordY = DefaultFontY;
}

void SetFontCoord(int x, int y) {
    if (g_FontCoordX == x && g_FontCoordY == y) {
        return;
    }

#ifndef DISABLE_FONT_COORD
    FntFlush(g_FontStreamId);
    Font[g_FontStreamId].x = g_FontCoordX = LOH(x);
    Font[g_FontStreamId].y = g_FontCoordY = LOH(y);
#endif
}

void BeginFont() {
    Font[g_FontStreamId].x = -255;
    Font[g_FontStreamId].y = -255;
    FntFlush(-1);
    Font[g_FontStreamId].x = g_FontCoordX = DefaultFontX;
    Font[g_FontStreamId].y = g_FontCoordY = DefaultFontY;
    SetDumpFnt(0);
}

void EndFont() {
    FntFlush(g_FontStreamId);
    SetDumpFnt(0);
}

void PrintDefaultFont() {
    Font[g_FontStreamId].x = DefaultFontX;
    Font[g_FontStreamId].y = DefaultFontY;
    FntFlush(-1);
}
