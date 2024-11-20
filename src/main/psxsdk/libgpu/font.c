#include "common.h"
#include <libgpu.h>

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

extern s32 D_8002B810;
extern s32 D_8002B814;
extern int (*GPU_printf)(const char*, ...);

void SetDumpFnt(int id) {
    if (id >= 0 && D_8002B810 >= id) {
        D_8002B814 = id;
        GPU_printf = FntPrint;
    }
}

extern u_long D_8002B818[];
extern FntStream Font[4];
extern u16 clut;
extern u16 tpage;

void FntLoad(s32 tx, s32 ty) {
    clut = LoadClut(D_8002B818, tx, ty + 0x80);
    tpage = LoadTPage(D_8002B818 + 0x80, 0, 0, tx, ty, 0x80, 0x20);
    D_8002B810 = 0;
    memset(Font, 0, sizeof(Font));
}

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/font", FntOpen);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/font", FntFlush);

INCLUDE_ASM("main/nonmatchings/psxsdk/libgpu/font", FntPrint);
