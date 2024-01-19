#include <common.h>
#include <log.h>
#include <game.h>
#include <stdlib.h>
#ifdef _MSC_VER
#define SDL_MAIN_HANDLED
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include "pc.h"

typedef enum {
    DEBUG_SDL_NONE,
    DEBUG_SDL_SHOW_VRAM_16bpp,
    DEBUG_SDL_SHOW_VRAM_8bpp,
    DEBUG_SDL_SHOW_VRAM_4bpp,
} DebugSdl;

extern bool g_IsQuitRequested;
extern u16 g_RawVram[VRAM_W * VRAM_H];
SDL_Window* g_Window = NULL;
SDL_Renderer* g_Renderer = NULL;
SDL_AudioSpec g_SdlAudioSpecs = {0};
SDL_AudioDeviceID g_SdlAudioDevice = {0};
DebugSdl g_DebugSdl = DEBUG_SDL_NONE;
unsigned int g_Tpage = 0;
static SDL_Texture* g_VramTex = NULL;
static int g_LastVramTexTpage = -1;
static int g_LastVramTexClut = -1;

extern bool (*InitPlatform)();
extern void (*ResetPlatform)(void);
extern void (*MyRenderPrimitives)(void);
extern void (*MyPadInit)(int mode);
extern u_long (*MyPadRead)(int id);
extern int (*MyDrawSync)(int mode);
extern DISPENV* (*MyPutDispEnv)(DISPENV* env);
extern void (*MySetDrawMode)(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw);
extern int (*MyResetGraph)(int mode);
extern void (*MySsInitHot)();

bool SdlInitPlatform() {
    atexit(ResetPlatform);

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
    SDL_SetRenderDrawBlendMode(g_Renderer, SDL_BLENDMODE_BLEND);

    g_VramTex = SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_ABGR1555,
                                  SDL_TEXTUREACCESS_STREAMING, 256, 256);
    if (!g_VramTex) {
        ERRORF("unable to create VRAM texture: %s", SDL_GetError());
        return false;
    }
    SDL_SetTextureBlendMode(g_VramTex, SDL_BLENDMODE_BLEND);

    g_Tpage = 0;
    return true;
}

void SdlResetPlatform(void) {
    g_Tpage = 0;
    g_LastVramTexTpage = -1;
    g_LastVramTexClut = -1;
    if (g_VramTex) {
        SDL_DestroyTexture(g_VramTex);
        g_VramTex = NULL;
    }

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

int SdlMyResetGraph(int arg0) { return 0; }

void MyAudioCallback(void* data, Uint8* buffer, int length);
void SDLAudioCallback(void* data, Uint8* buffer, int length) {
    MyAudioCallback(data, buffer, length);
}

void SdlMySsInitHot(void) {
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

void SdlMyPadInit(int mode) { INFOF("use keyboard"); }

u_long SdlMyPadRead(int id) {
    const u8* keyb = SDL_GetKeyboardState(NULL);
    u_long pressed = 0;

    switch (id) {
    case 0:
        if (keyb[SDL_SCANCODE_ESCAPE]) {
            g_IsQuitRequested = 1;
        }
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

        g_DebugSdl = DEBUG_SDL_NONE;
        if (keyb[SDL_SCANCODE_F5]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_16bpp;
        }
        if (keyb[SDL_SCANCODE_F6]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_8bpp;
        }
        if (keyb[SDL_SCANCODE_F7]) {
            g_DebugSdl = DEBUG_SDL_SHOW_VRAM_4bpp;
        }
        break;
    }

    return pressed;
}

void ShowVram16bpp(void) {
    SDL_Texture* t =
        SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_ABGR1555,
                          SDL_TEXTUREACCESS_STREAMING, VRAM_W, VRAM_H);

    u16* pixels;
    int pitch = VRAM_STRIDE;
    SDL_LockTexture(t, NULL, (void**)&pixels, &pitch);
    if (pitch == VRAM_STRIDE) {
        memcpy(pixels, g_RawVram, sizeof(g_RawVram));
    } else {
        u16* dst = pixels;
        u16* src = g_RawVram;
        for (int i = 0; i < VRAM_H; i++) {
            memcpy(dst, src, VRAM_STRIDE);
            dst += pitch >> 1;
            src += VRAM_STRIDE >> 1;
        }
    }
    SDL_UnlockTexture(t);

    SDL_Rect rsrc = {0, 0, 512, 256};
    SDL_Rect rdst = {0, 0, 256, 128};
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    rsrc.y += 256;
    rdst.y += 128;
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    SDL_DestroyTexture(t);
}

void ShowVram8bpp(void) {
    SDL_Texture* t =
        SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_RGBA32,
                          SDL_TEXTUREACCESS_STREAMING, VRAM_W, VRAM_H);

    u8* pixels;
    int pitch = VRAM_STRIDE;
    SDL_LockTexture(t, NULL, (void**)&pixels, &pitch);

    u16* src = g_RawVram;
    for (int i = 0; i < VRAM_H; i++) {
        for (int j = 0; j < VRAM_W; j++) {
            u8 ch = src[j];
            pixels[j * 4 + 0] = ch;
            pixels[j * 4 + 1] = ch;
            pixels[j * 4 + 2] = ch;
            pixels[j * 4 + 3] = 0xFF;
        }
        src += VRAM_W;
        pixels += pitch;
    }
    SDL_UnlockTexture(t);

    SDL_Rect rsrc = {512, 0, 512, 256};
    SDL_Rect rdst = {0, 0, 256, 128};
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    rsrc.y += 256;
    rdst.y += 128;
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    SDL_DestroyTexture(t);
}

void ShowVram4bpp(void) {
    SDL_Texture* t =
        SDL_CreateTexture(g_Renderer, SDL_PIXELFORMAT_RGBA32,
                          SDL_TEXTUREACCESS_STREAMING, VRAM_W * 2, VRAM_H);

    u8* pixels;
    int pitch = VRAM_STRIDE;
    SDL_LockTexture(t, NULL, (void**)&pixels, &pitch);

    u16* src = g_RawVram;
    for (int i = 0; i < VRAM_H; i++) {
        for (int j = 0; j < VRAM_W; j++) {
            u8 ch = src[j];
            pixels[j * 8 + 0] = (ch & 0xF) << 4;
            pixels[j * 8 + 1] = (ch & 0xF) << 4;
            pixels[j * 8 + 2] = (ch & 0xF) << 4;
            pixels[j * 8 + 3] = 0xFF;
            pixels[j * 8 + 4] = ch & 0xF0;
            pixels[j * 8 + 5] = ch & 0xF0;
            pixels[j * 8 + 6] = ch & 0xF0;
            pixels[j * 8 + 7] = 0xFF;
        }
        src += VRAM_W;
        pixels += pitch;
    }
    SDL_UnlockTexture(t);

    SDL_Rect rsrc = {1024, 0, 1024, 256};
    SDL_Rect rdst = {0, 0, 256, 128};
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    rsrc.y += 256;
    rdst.y += 128;
    SDL_RenderCopy(g_Renderer, t, &rsrc, &rdst);

    SDL_DestroyTexture(t);
}

void MyDrawSyncCallback();
int SdlMyDrawSync(int mode) {
    switch (g_DebugSdl) {
    case DEBUG_SDL_SHOW_VRAM_16bpp:
        ShowVram16bpp();
        break;
    case DEBUG_SDL_SHOW_VRAM_8bpp:
        ShowVram8bpp();
        break;
    case DEBUG_SDL_SHOW_VRAM_4bpp:
        ShowVram4bpp();
        break;
    }

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

int g_WndWidth = -1;
int g_WndHeight = -1;
DISPENV* SdlMyPutDispEnv(DISPENV* env) {
    int w = env->disp.w * SCREEN_SCALE;
    int h = env->disp.h * SCREEN_SCALE;
    if (g_WndWidth == w && g_WndHeight == h) {
        return env;
    }

    g_WndWidth = w;
    g_WndHeight = h;
    SDL_SetWindowSize(g_Window, w, h);
    return env;
}

void SdlMySetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT* tw) {
    g_Tpage = tpage;
}

SDL_Texture* GetVramTexture(int tpage, int clut) {
    u16 pal[256];
    if (g_LastVramTexTpage != tpage || g_LastVramTexClut != clut) {
        g_LastVramTexTpage = tpage;
        g_LastVramTexClut = clut;

        u8* src = g_RawVram;
        src += (tpage & 0xF) * 128;
        src += ((tpage >> 4) & 1) * VRAM_STRIDE * 256;

        u16* sourcepal = g_RawVram;
        sourcepal += clut * 0x10;

        u16* pixels;
        int pitch;
        SDL_LockTexture(g_VramTex, NULL, (void**)&pixels, &pitch);

        int bpp = tpage >> 7;
        switch (bpp) {
        case 0: // 4bpp
            // Hack that rewrites the VRAM to adjust transparent palette colors
            memcpy(pal, sourcepal, 0x20);
            pal[0] &= ~0x8000; // first color always transparent?
            for (int i = 1; i < 16; i++) {
                pal[i] |= 0x8000;
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 128; j++) {
                    u8 ch = src[j];
                    pixels[j * 2 + 0] = pal[ch & 0xF];
                    pixels[j * 2 + 1] = pal[ch >> 4];
                }
                pixels += pitch >> 1;
                src += VRAM_STRIDE;
            }
            break;
        case 1: // 8 bpp
            // Hack that rewrites the VRAM to adjust transparent palette colors
            memcpy(pal, sourcepal, 0x200);
            pal[0] &= ~0x8000; // first color always transparent?
            for (int i = 1; i < 256; i++) {
                pal[i] |= 0x8000;
            }
            for (int i = 0; i < 256; i++) {
                for (int j = 0; j < 256; j++) {
                    pixels[j] = pal[src[j]];
                }
                pixels += pitch >> 1;
                src += VRAM_STRIDE;
            }
            break;
        default:
            WARNF("bpp %d not supported", bpp);
            break;
        }
        SDL_UnlockTexture(g_VramTex);
    }

    return g_VramTex;
}

#define PSX_TEX_U(x) ((float)(x) / 256.0f)
#define PSX_TEX_V(x) ((float)(x) / 256.0f)
void SetSdlVertexSprite(SDL_Vertex* v, SPRT* sprt) {
    // u8 blend = sprt->code & 1 ? 0xFF : 0x00;
    sprt->r0 |= 255;
    sprt->g0 |= 255;
    sprt->b0 |= 255;
    v[0].position.x = sprt->x0;
    v[0].position.y = sprt->y0;
    v[0].tex_coord.x = PSX_TEX_U(sprt->u0);
    v[0].tex_coord.y = PSX_TEX_V(sprt->v0);
    v[0].color.r = sprt->r0;
    v[0].color.g = sprt->g0;
    v[0].color.b = sprt->b0;
    v[0].color.a = 0xFF;
    v[1].position.x = sprt->x0 + sprt->w;
    v[1].position.y = sprt->y0;
    v[1].tex_coord.x = PSX_TEX_U(sprt->u0 + sprt->w);
    v[1].tex_coord.y = PSX_TEX_V(sprt->v0);
    v[1].color.r = sprt->r0;
    v[1].color.g = sprt->g0;
    v[1].color.b = sprt->b0;
    v[1].color.a = 0xFF;
    v[2].position.x = sprt->x0;
    v[2].position.y = sprt->y0 + sprt->h;
    v[2].tex_coord.x = PSX_TEX_U(sprt->u0);
    v[2].tex_coord.y = PSX_TEX_V(sprt->v0 + sprt->h);
    v[2].color.r = sprt->r0;
    v[2].color.g = sprt->g0;
    v[2].color.b = sprt->b0;
    v[2].color.a = 0xFF;
    v[4].position.x = sprt->x0 + sprt->w;
    v[4].position.y = sprt->y0 + sprt->h;
    v[4].tex_coord.x = PSX_TEX_U(sprt->u0 + sprt->w);
    v[4].tex_coord.y = PSX_TEX_V(sprt->v0 + sprt->h);
    v[4].color.r = sprt->r0;
    v[4].color.g = sprt->g0;
    v[4].color.b = sprt->b0;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}

void SetSdlVertexSprite16(SDL_Vertex* v, SPRT_16* sprt) {
    sprt->r0 |= 255;
    sprt->g0 |= 255;
    sprt->b0 |= 255;
    v[0].position.x = sprt->x0;
    v[0].position.y = sprt->y0;
    v[0].tex_coord.x = PSX_TEX_U(sprt->u0);
    v[0].tex_coord.y = PSX_TEX_V(sprt->v0);
    v[0].color.r = sprt->r0;
    v[0].color.g = sprt->g0;
    v[0].color.b = sprt->b0;
    v[0].color.a = 0xFF;
    v[1].position.x = sprt->x0 + 16;
    v[1].position.y = sprt->y0;
    v[1].tex_coord.x = PSX_TEX_U(sprt->u0 + 16);
    v[1].tex_coord.y = PSX_TEX_V(sprt->v0);
    v[1].color.r = sprt->r0;
    v[1].color.g = sprt->g0;
    v[1].color.b = sprt->b0;
    v[1].color.a = 0xFF;
    v[2].position.x = sprt->x0;
    v[2].position.y = sprt->y0 + 16;
    v[2].tex_coord.x = PSX_TEX_U(sprt->u0);
    v[2].tex_coord.y = PSX_TEX_V(sprt->v0 + 16);
    v[2].color.r = sprt->r0;
    v[2].color.g = sprt->g0;
    v[2].color.b = sprt->b0;
    v[2].color.a = 0xFF;
    v[4].position.x = sprt->x0 + 16;
    v[4].position.y = sprt->y0 + 16;
    v[4].tex_coord.x = PSX_TEX_U(sprt->u0 + 16);
    v[4].tex_coord.y = PSX_TEX_V(sprt->v0 + 16);
    v[4].color.r = sprt->r0;
    v[4].color.g = sprt->g0;
    v[4].color.b = sprt->b0;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
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

void SetSdlVertexGT4(SDL_Vertex* v, POLY_GT4* poly) {
    u8 blend = poly->code & 1 ? 0xFF : 0x00;
    v[0].position.x = poly->x0;
    v[0].position.y = poly->y0;
    v[0].tex_coord.x = PSX_TEX_U(poly->u0);
    v[0].tex_coord.y = PSX_TEX_V(poly->v0);
    v[0].color.r = poly->r0 | blend;
    v[0].color.g = poly->g0 | blend;
    v[0].color.b = poly->b0 | blend;
    v[0].color.a = 0xFF;
    v[1].position.x = poly->x1;
    v[1].position.y = poly->y1;
    v[1].tex_coord.x = PSX_TEX_U(poly->u1);
    v[1].tex_coord.y = PSX_TEX_V(poly->v1);
    v[1].color.r = poly->r1 | blend;
    v[1].color.g = poly->g1 | blend;
    v[1].color.b = poly->b1 | blend;
    v[1].color.a = 0xFF;
    v[2].position.x = poly->x2;
    v[2].position.y = poly->y2;
    v[2].tex_coord.x = PSX_TEX_U(poly->u2);
    v[2].tex_coord.y = PSX_TEX_V(poly->v2);
    v[2].color.r = poly->r2 | blend;
    v[2].color.g = poly->g2 | blend;
    v[2].color.b = poly->b2 | blend;
    v[2].color.a = 0xFF;
    v[4].position.x = poly->x3;
    v[4].position.y = poly->y3;
    v[4].tex_coord.x = PSX_TEX_U(poly->u3);
    v[4].tex_coord.y = PSX_TEX_V(poly->v3);
    v[4].color.r = poly->r3 | blend;
    v[4].color.g = poly->g3 | blend;
    v[4].color.b = poly->b3 | blend;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}

void SetSdlVertexPrim(SDL_Vertex* v, Primitive* prim) {
    v[0].position.x = prim->x0;
    v[0].position.y = prim->y0;
    v[0].tex_coord.x = PSX_TEX_U(prim->u0);
    v[0].tex_coord.y = PSX_TEX_V(prim->v0);
    v[0].color.r = prim->r0;
    v[0].color.g = prim->g0;
    v[0].color.b = prim->b0;
    v[0].color.a = 0xFF;
    v[1].position.x = prim->x1;
    v[1].position.y = prim->y1;
    v[1].tex_coord.x = PSX_TEX_U(prim->u1);
    v[1].tex_coord.y = PSX_TEX_V(prim->v1);
    v[1].color.r = prim->r1;
    v[1].color.g = prim->g1;
    v[1].color.b = prim->b1;
    v[1].color.a = 0xFF;
    v[2].position.x = prim->x2;
    v[2].position.y = prim->y2;
    v[2].tex_coord.x = PSX_TEX_U(prim->u2);
    v[2].tex_coord.y = PSX_TEX_V(prim->v2);
    v[2].color.r = prim->r2;
    v[2].color.g = prim->g2;
    v[2].color.b = prim->b2;
    v[2].color.a = 0xFF;
    v[4].position.x = prim->x3;
    v[4].position.y = prim->y3;
    v[4].tex_coord.x = PSX_TEX_U(prim->u3);
    v[4].tex_coord.y = PSX_TEX_V(prim->v3);
    v[4].color.r = prim->r3;
    v[4].color.g = prim->g3;
    v[4].color.b = prim->b3;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}
void SetSdlVertexPrimSprt(SDL_Vertex* v, Primitive* prim) {
    v[0].position.x = prim->x0;
    v[0].position.y = prim->y0;
    v[0].tex_coord.x = PSX_TEX_U(prim->u0);
    v[0].tex_coord.y = PSX_TEX_V(prim->v0);
    v[0].color.r = 0xFF;
    v[0].color.g = 0xFF;
    v[0].color.b = 0xFF;
    v[0].color.a = 0xFF;
    v[1].position.x = prim->x0 + prim->u1;
    v[1].position.y = prim->y0;
    v[1].tex_coord.x = PSX_TEX_U(prim->u0 + prim->u1);
    v[1].tex_coord.y = PSX_TEX_V(prim->v0);
    v[1].color.r = 0xFF;
    v[1].color.g = 0xFF;
    v[1].color.b = 0xFF;
    v[1].color.a = 0xFF;
    v[2].position.x = prim->x0;
    v[2].position.y = prim->y0 + prim->v1;
    v[2].tex_coord.x = PSX_TEX_U(prim->u0);
    v[2].tex_coord.y = PSX_TEX_V(prim->v0 + prim->v1);
    v[2].color.r = 0xFF;
    v[2].color.g = 0xFF;
    v[2].color.b = 0xFF;
    v[2].color.a = 0xFF;
    v[4].position.x = prim->x0 + prim->u1;
    v[4].position.y = prim->y0 + prim->v1;
    v[4].tex_coord.x = PSX_TEX_U(prim->u0 + prim->u1);
    v[4].tex_coord.y = PSX_TEX_V(prim->v0 + prim->v1);
    v[4].color.r = 0xFF;
    v[4].color.g = 0xFF;
    v[4].color.b = 0xFF;
    v[4].color.a = 0xFF;
    v[3] = v[1];
    v[5] = v[2];
}

void SdlMyRenderPrimitives(void) {
    SDL_Vertex v[6];
    SDL_Texture* t = NULL;

    int pg4 = 0;
    int pgt4 = 0;
    int plg2 = 0;
    int ptile = 0;
    int psprt = 0;
    for (int i = 0; i < LEN(g_PrimBuf); i++) {
        Primitive* prim = &g_PrimBuf[i];
        if (prim->blendMode & 8) {
            continue;
        }

        switch (prim->type) {
        case PRIM_NONE:
            break;
        case PRIM_G4:
            SetSdlVertexPrim(v, prim);
            SDL_RenderGeometry(g_Renderer, NULL, v, 6, NULL, 0);
            pg4++;
            break;
        case PRIM_GT4:
            SetSdlVertexPrim(v, prim);
            t = GetVramTexture(prim->tpage, D_8003C104[prim->clut]);
            SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
            pgt4++;
            break;
        case PRIM_LINE_G2:
            SDL_SetRenderDrawColor(
                g_Renderer, prim->r0, prim->g0, prim->b0, 255);
            SDL_RenderDrawLine(
                g_Renderer, prim->x0, prim->y0, prim->x1, prim->y1);
            plg2++;
            break;
        case PRIM_SPRT:
            SetSdlVertexPrimSprt(v, prim);
            t = GetVramTexture(prim->tpage, D_8003C104[prim->clut]);
            SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
            psprt++;
            break;
        default:
            WARNF("unhandled prim type %d", prim->type);
            break;
        }
    }

    DEBUGF("PG4   %03X, PGT4  %03X", pg4, pgt4);
    DEBUGF("PLG2  %03X, PSPRT %03X", plg2, psprt);
    DEBUGF("PTILE %03X            ", plg2, ptile);

    for (int i = 0; i < g_GpuUsage.g4; i++) {
        SetSdlVertexG4(v, &g_CurrentBuffer->polyG4[i]);
        SDL_RenderGeometry(g_Renderer, NULL, v, 6, NULL, 0);
    }
    for (int i = 0; i < g_GpuUsage.gt4; i++) {
        POLY_GT4* poly = &g_CurrentBuffer->polyGT4[i];
        SetSdlVertexGT4(v, poly);
        t = GetVramTexture(poly->tpage, poly->clut);
        SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
    }
    for (int i = 0; i < g_GpuUsage.sp; i++) {
        SPRT* sp = &g_CurrentBuffer->sprite[i];
        SetSdlVertexSprite(v, sp);
        t = GetVramTexture(g_Tpage, sp->clut);
        SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
    }
    for (int i = 0; i < g_GpuUsage.line; i++) {
        LINE_G2* poly = &g_CurrentBuffer->lineG2[i];
        SDL_SetRenderDrawColor(g_Renderer, poly->r0, poly->g0, poly->b0, 255);
        SDL_RenderDrawLine(g_Renderer, poly->x0, poly->y0, poly->x1, poly->y1);
    }
    for (int i = 0; i < g_GpuUsage.sp16; i++) {
        SPRT_16* sp = &g_CurrentBuffer->sprite16[i];
        SetSdlVertexSprite16(v, sp);
        t = GetVramTexture(sp->code, sp->clut); // TODO sp->code is a bad hack
        SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
    }
}

int main(int argc, char* argv[]) {
    const char* filename;

    InitPlatform = SdlInitPlatform;
    ResetPlatform = SdlResetPlatform;
    MyRenderPrimitives = SdlMyRenderPrimitives;
    MyPadInit = SdlMyPadInit;
    MyPadRead = SdlMyPadRead;
    MyDrawSync = SdlMyDrawSync;
    MyPutDispEnv = SdlMyPutDispEnv;
    MyResetGraph = SdlMyResetGraph;
    MySsInitHot = SdlMySsInitHot;

    if (argc < 2) {
        filename = "disks/sotn.us.bin";
    } else {
        filename = argv[1];
    }
    OpenCd(filename);

    if (InitGame()) {
        MainGame();
    }
    ResetGame();
}
