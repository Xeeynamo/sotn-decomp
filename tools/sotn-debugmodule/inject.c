#include <game.h>

typedef struct {
    u32 Init;
    u32 Update;
    u32 Unk08;
    u32 Unk0C;
    u32 Unk10;
    u32 Unk14;
    u32 Unk18;
    u32 Unk1C;
    u32 Unk20;
    u32 Unk24;
    u32 Unk28;
    u32 Unk2C;
    u32 Unk30;
    u32 Unk34;
    u32 Unk38;
    u32 Unk3C;
} ServantDesc;

// The INJECT value will change every time information is added to the .data or
// .rodata section. To get a refreshed value, compile the debug module, look for
// sotn-debugmode.map, find InjectMain and copy&paste the hex value on its left.
const u32 INJECT_MAIN_ADDR = 0x802809b4;
const u32 MODULE_ADDR = 0x80280000;
const u32 LOAD_ADDR = 0x80170000;
const u32 INJECT = INJECT_MAIN_ADDR - (MODULE_ADDR - LOAD_ADDR);

void Dummy(Entity*);
ServantDesc g_ServantDesc = {
    INJECT, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,
    Dummy,  Dummy, Dummy, Dummy, Dummy, Dummy, Dummy, Dummy,

};

#define JAL(addr) ((((u32)(addr)&0x3FFFFFFU) >> 2) | 0x0C000000U)

int MainLoop();
void InjectMain(void) {
    u32* const InjectPoint = 0x800E3D00U;
    int i;

    // Enable 8MB of ram
    *(unsigned int*)0x1F801060 |= 0xE00;

    // The game loads this overlay in 0x80170000, but as this module is compiled
    // to use 0x80280000 as a base, we copy the overlay to there.
    __builtin_memcpy((void*)0x80280000, (void*)0x80170000, 40960U);

    // Now we say to 'entrypoint_sotn' to call our main every frame
    *InjectPoint = JAL(MainLoop);
}
void Dummy(Entity*) {}

bool g_Init = false;
void Init(void);
bool Update(void);
int MainLoop() {
    if (!g_Init) {
        Init();
        g_Init = true;
    }
    return Update();
}