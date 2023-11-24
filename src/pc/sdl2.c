#include <common.h>
#include <log.h>
#include <game.h>
#include <SDL2/SDL.h>
#include "pc.h"

extern bool g_IsQuitRequested;
SDL_Window* g_Window = NULL;
SDL_Renderer* g_Renderer = NULL;
SDL_AudioSpec g_SdlAudioSpecs = {0};
SDL_AudioDeviceID g_SdlAudioDevice = {0};

bool InitPlatform() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        ERRORF("SDL_Init: %s", SDL_GetError());
        return false;
    }

    g_Window = SDL_CreateWindow(
        "SOTN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DISP_WIDTH * SCREEN_SCALE, DISP_HEIGHT * SCREEN_SCALE,
        SDL_WINDOW_SHOWN);
    if (!g_Window) {
        ERRORF("SDL_CreateWindow: %s", SDL_GetError());
        return false;
    }

    g_Renderer = SDL_CreateRenderer(
        g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g_Renderer) {
        ERRORF("SDL_CreateRenderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void ResetPlatform() {
    if (g_Renderer) {
        SDL_DestroyRenderer(g_Renderer);
        g_Renderer = NULL;
    }

    if (g_Window) {
        SDL_DestroyWindow(g_Window);
        g_Window = NULL;
    }

    SDL_Quit();
}

int MyResetGraph(int) { return 0; }

void MyAudioCallback(void* data, Uint8* buffer, int length);
void SDLAudioCallback(void* data, Uint8* buffer, int length) {
    MyAudioCallback(data, buffer, length);
}

void MySsInitHot(void) {
    SDL_AudioSpec specs = {0};
    specs.freq = 44100;
    specs.format = AUDIO_S16;
    specs.channels = 2;
    specs.samples = 2048;
    specs.callback = SDLAudioCallback;

    g_SdlAudioDevice =
        SDL_OpenAudioDevice(NULL, false, &specs, &g_SdlAudioSpecs, false);
    if (g_SdlAudioDevice == 0) {
        WARNF("SDL_OpenAudioDevice failed: %s", SDL_GetError());
        return;
    }
    INFOF("SDL audio device opened: %d", g_SdlAudioDevice);

    SDL_PauseAudioDevice(g_SdlAudioDevice, 0);
}

void MyPadInit(int mode) { INFOF("use keyboard"); }

u_long MyPadRead(int id) {
    const u8* keyb = SDL_GetKeyboardState(NULL);
    u_long pressed = 0;

    switch (id) {
    case 0:
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
        break;
    }

    return pressed;
}

void MyDrawSyncCallback();
int MyDrawSync(int mode) {
    SDL_RenderPresent(g_Renderer);
    SDL_RenderSetScale(g_Renderer, SCREEN_SCALE, SCREEN_SCALE);

    // SDL event handling
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            g_IsQuitRequested = 1;
            break;
        }
    }

    // TODO maybe move this to ClearImage?
    SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
    SDL_RenderClear(g_Renderer);

    MyDrawSyncCallback(mode);

    return 0;
}