#include "sotn.h"
#include <SDL2/SDL.h>
#include <math.h>
#include <stdarg.h>

enum { WHITE = 0xFFFFFFFFU };

void PrintText(const char* text, int x, int y, unsigned int color);

#define MAX_CHARS_PER_ROW 0x100
#define MAX_ROWS 0x20

int g_TextRow = 0;
char g_TextLines[MAX_ROWS][MAX_CHARS_PER_ROW];
int FntPrint(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    if (g_TextRow < MAX_ROWS) {
        vsnprintf(g_TextLines[g_TextRow], MAX_CHARS_PER_ROW, fmt, args);
        g_TextRow++;
    }

    va_end(args);
}

u_long* FntFlush(int) {
    s32 i;
    for (i = 0; i < g_TextRow; i++) {
        PrintText(g_TextLines[i], 0, i * 12, WHITE);
    }
    g_TextRow = 0;
}

s32 rcos(s32 x) { return cos(x) * 1024.0f; }
s32 rsin(s32 x) { return sin(x) * 1024.0f; }
s32 SquareRoot0(s32 x) { return 0; }
s32 SquareRoot12(s32 x, s32 y) { return 0; }
long ratan2(long x, long y) { return atan2(x, y) * 1024.0f; }

void CreateEntityFromCurrentEntity(u16 objectId, Entity* entity) {
    printf("CreateEntityFromCurrentEntity not implemented\n");
    DestroyEntity(entity);
}

void CreateEntityFromEntity(u16 objectId, Entity* source, Entity* entity) {
    printf("CreateEntityFromEntity not implemented\n");
    DestroyEntity(entity);
}

void FreePrimitives(s32) { printf("FreePrimitives not implemented\n"); }

void EntityEquipItemDrop(Entity*) {
    printf("EntityEquipItemDrop not implemented\n");
}

s16 AllocPrimitives(PrimitiveType type, s32 count) {
    printf("AllocPrimitives not implemented\n");
}

void CheckCollision(s32 x, s32 y, Collider* res, s32 unk) {
    Collider c = {0};
    *res = c;

    // Stop falling outside the screen
    if (y > 192) {
        res->unk0 = 9;
        res->unk18 = -(y & 15) + 1;
    }
}

extern Pad g_pads[2];
u8 D_80137460[0x10];
void func_800E8D24(void) {
    s8* ptr;
    s32 i;

    g_pads[0].repeat = 0;
    ptr = D_80137460;

    for (i = 0; i < 16; i++) {
        *ptr++ = 0x10;
    }
}

void func_800E8D54(void) {
    u16 button = 1;
    u16 repeat = 0;
    u16 unk = g_pads[0].tapped;
    u16 pressed = g_pads[0].pressed;
    u8* timers = D_80137460;
    s32 i = 0;

    do {
        NOP;
        if (pressed & button) {
            if (unk & button) {
                repeat |= button;
                timers[0] = 0x10;
            } else {
                if (--timers[0] == 0xFF) {
                    repeat |= button;
                    timers[0] = 5;
                }
            }
        }
        i++;
        timers++;
        button <<= 1;
    } while (i < 0x10);
    g_pads[0].repeat = repeat;
}

// Mocked PSY-Q SDK calls
void PadInit(int mode) {}
u_long PadRead(int id) {
    const u8* keyb = SDL_GetKeyboardState(NULL);
    u_long pressed = 0;
    if (keyb[SDL_SCANCODE_UP]) {
        pressed |= PAD_UP;
    }
    if (keyb[SDL_SCANCODE_DOWN]) {
        pressed |= PAD_DOWN;
    }
    if (keyb[SDL_SCANCODE_LEFT]) {
        pressed |= PAD_LEFT;
    }
    if (keyb[SDL_SCANCODE_RIGHT]) {
        pressed |= PAD_RIGHT;
    }
    if (keyb[SDL_SCANCODE_Q]) {
        pressed |= PAD_L1;
    }
    if (keyb[SDL_SCANCODE_R]) {
        pressed |= PAD_R1;
    }

    return pressed;
}

void InitializePads(void) {
    Pad* pad;
    s32 i;

    PadInit(0);
    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->tapped = 0;
        pad->previous = 0;
        pad->pressed = 0;
    }
    func_800E8D24();
}

void ReadPads(void) {
    Pad* pad;
    s32 i;
    u_long padd;

    for (pad = g_pads, i = 0; i < PAD_COUNT; i++, pad++) {
        pad->previous = pad->pressed;
        padd = PadRead(i >> 1);
        if (!(i & 1))
            pad->pressed = padd;
        else
            pad->pressed = padd >> 0x10;
        pad->tapped = (pad->pressed ^ pad->previous) & pad->pressed;
    }
    func_800E8D54();
}
