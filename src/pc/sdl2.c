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
        if (keyb[SDL_SCANCODE_X]) {
            pressed |= PAD_CROSS;
        }
        if (keyb[SDL_SCANCODE_S]) {
            pressed |= PAD_TRIANGLE;
        }
        if (keyb[SDL_SCANCODE_Z]) {
            pressed |= PAD_SQUARE;
        }
        if (keyb[SDL_SCANCODE_D]) {
            pressed |= PAD_CIRCLE;
        }
        if (keyb[SDL_SCANCODE_BACKSPACE]) {
            pressed |= PAD_SELECT;
        }
        if (keyb[SDL_SCANCODE_RETURN]) {
            pressed |= PAD_START;
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

void SetSdlVertexG4(SDL_Vertex* v, POLY_G4* poly) {
    v[0].position.x = poly->x0;
    v[0].position.y = poly->y0;
    v[0].color.r = poly->r0;
    v[0].color.g = poly->g0;
    v[0].color.b = poly->b0;
    v[0].color.a = 0xFF;
    v[1].position.x = poly->x1;
    v[1].position.y = poly->y1;
    v[1].color.r = poly->r1;
    v[1].color.g = poly->g1;
    v[1].color.b = poly->b1;
    v[1].color.a = 0xFF;
    v[2].position.x = poly->x2;
    v[2].position.y = poly->y2;
    v[2].color.r = poly->r2;
    v[2].color.g = poly->g2;
    v[2].color.b = poly->b2;
    v[2].color.a = 0xFF;
    v[4].position.x = poly->x3;
    v[4].position.y = poly->y3;
    v[4].color.r = poly->r3;
    v[4].color.g = poly->g3;
    v[4].color.b = poly->b3;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}

void SetSdlVertexPrim(SDL_Vertex* v, Primitive* prim) {
    v[0].position.x = prim->x0;
    v[0].position.y = prim->y0;
    v[0].color.r = prim->r0;
    v[0].color.g = prim->g0;
    v[0].color.b = prim->b0;
    v[0].color.a = 0xFF;
    v[1].position.x = prim->x1;
    v[1].position.y = prim->y1;
    v[1].color.r = prim->r1;
    v[1].color.g = prim->g1;
    v[1].color.b = prim->b1;
    v[1].color.a = 0xFF;
    v[2].position.x = prim->x2;
    v[2].position.y = prim->y2;
    v[2].color.r = prim->r2;
    v[2].color.g = prim->g2;
    v[2].color.b = prim->b2;
    v[2].color.a = 0xFF;
    v[4].position.x = prim->x3;
    v[4].position.y = prim->y3;
    v[4].color.r = prim->r3;
    v[4].color.g = prim->g3;
    v[4].color.b = prim->b3;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}

void MyRenderPrimitives(void) {
    SDL_Vertex v[6];

    for (int i = 0; i < LEN(g_PrimBuf); i++) {
        Primitive* prim = &g_PrimBuf[i];
        switch (prim->type) {
        case PRIM_GT4:
            SetSdlVertexPrim(v, prim);
            SDL_RenderGeometry(g_Renderer, NULL, v, 6, NULL, 0);
            break;
        }
    }
    for (int i = 0; i < g_GpuUsage.g4; i++) {
        SetSdlVertexG4(v, &g_CurrentBuffer->polyG4[i]);
        SDL_RenderGeometry(g_Renderer, NULL, v, 6, NULL, 0);
    }
    for (int i = 0; i < g_GpuUsage.line; i++) {
        LINE_G2* poly = &g_CurrentBuffer->lineG2[i];
        SDL_SetRenderDrawColor(g_Renderer, poly->r0, poly->g0, poly->b0, 255);
        SDL_RenderDrawLine(g_Renderer, poly->x0, poly->y0, poly->x1, poly->y1);
    }
}
