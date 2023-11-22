#include <SDL2/SDL.h>
#include <common.h>
#include <psxsdk/libetc.h>
#include <game.h>
#include <log.h>

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

int VSyncCallback(void (*f)()) { NOT_IMPLEMENTED; }

int VSyncCallbacks(int ch, void (*f)()) { NOT_IMPLEMENTED; }

long SetVideoMode(long mode) { NOT_IMPLEMENTED; }
