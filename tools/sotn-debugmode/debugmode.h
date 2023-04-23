#include <game.h>

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
    u32 maxCharCount;
    u32 unk20;
    u32 unk24;
    u32 unk28;
} FntStream;

extern FntStream Font[];

void SetFontCoord(int x, int y);
