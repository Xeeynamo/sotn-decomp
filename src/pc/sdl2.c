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
static SDL_Texture* g_VramTex = NULL;
static int g_LastVramTexTpage = -1;
static int g_LastVramTexClut = -1;

void ResetPlatform(void);
bool InitPlatform() {
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

    return true;
}

void ResetPlatform(void) {
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

int MyResetGraph(int arg0) { return 0; }

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
int MyDrawSync(int mode) {
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
DISPENV* MyPutDispEnv(DISPENV* env) {
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

// On PSX, color blending at 0x80 retains the original color, while on PC
// that is half brightness. A value of 0xFF on PSX is double the brightness.
// Higher values than 0x80 on PC are for now ignored without a GPU shader.
// NOTE: For some reason it only works well on sprite primitives?
#define PSX_COL(x) MIN(0xFF, ((unsigned int)(x)*2 - 1))

#define PSX_TEX_U(x) ((float)(x) / 256.0f)
#define PSX_TEX_V(x) ((float)(x) / 256.0f)
void SetSdlVertexSprite(SDL_Vertex* v, SPRT* sprt, bool isSemiTransp) {
    u8 a = isSemiTransp ? 0x80 : 0xFF;
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
    v[0].color.a = a;
    v[1].position.x = sprt->x0 + sprt->w;
    v[1].position.y = sprt->y0;
    v[1].tex_coord.x = PSX_TEX_U(sprt->u0 + sprt->w);
    v[1].tex_coord.y = PSX_TEX_V(sprt->v0);
    v[1].color.r = sprt->r0;
    v[1].color.g = sprt->g0;
    v[1].color.b = sprt->b0;
    v[1].color.a = a;
    v[2].position.x = sprt->x0;
    v[2].position.y = sprt->y0 + sprt->h;
    v[2].tex_coord.x = PSX_TEX_U(sprt->u0);
    v[2].tex_coord.y = PSX_TEX_V(sprt->v0 + sprt->h);
    v[2].color.r = sprt->r0;
    v[2].color.g = sprt->g0;
    v[2].color.b = sprt->b0;
    v[2].color.a = a;
    v[4].position.x = sprt->x0 + sprt->w;
    v[4].position.y = sprt->y0 + sprt->h;
    v[4].tex_coord.x = PSX_TEX_U(sprt->u0 + sprt->w);
    v[4].tex_coord.y = PSX_TEX_V(sprt->v0 + sprt->h);
    v[4].color.r = sprt->r0;
    v[4].color.g = sprt->g0;
    v[4].color.b = sprt->b0;
    v[4].color.a = a;
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

void SetSdlVertexG4(SDL_Vertex* v, POLY_G4* poly, bool isSemiTransp) {
    u8 a = isSemiTransp ? 0x80 : 0xFF;
    v[0].position.x = poly->x0;
    v[0].position.y = poly->y0;
    v[0].color.r = poly->r0;
    v[0].color.g = poly->g0;
    v[0].color.b = poly->b0;
    v[0].color.a = a;
    v[1].position.x = poly->x1;
    v[1].position.y = poly->y1;
    v[1].color.r = poly->r1;
    v[1].color.g = poly->g1;
    v[1].color.b = poly->b1;
    v[1].color.a = a;
    v[2].position.x = poly->x2;
    v[2].position.y = poly->y2;
    v[2].color.r = poly->r2;
    v[2].color.g = poly->g2;
    v[2].color.b = poly->b2;
    v[2].color.a = a;
    v[4].position.x = poly->x3;
    v[4].position.y = poly->y3;
    v[4].color.r = poly->r3;
    v[4].color.g = poly->g3;
    v[4].color.b = poly->b3;
    v[4].color.a = a;
    v[3] = v[1];
    v[5] = v[2];
}

void SetSdlVertexGT4(SDL_Vertex* v, POLY_GT4* poly, bool isSemiTransp) {
    u8 blend = poly->code & 1 ? 0xFF : 0x00;
    u8 a = isSemiTransp ? 0x80 : 0xFF;
    v[0].position.x = poly->x0;
    v[0].position.y = poly->y0;
    v[0].tex_coord.x = PSX_TEX_U(poly->u0);
    v[0].tex_coord.y = PSX_TEX_V(poly->v0);
    v[0].color.r = poly->r0 | blend;
    v[0].color.g = poly->g0 | blend;
    v[0].color.b = poly->b0 | blend;
    v[0].color.a = a;
    v[1].position.x = poly->x1;
    v[1].position.y = poly->y1;
    v[1].tex_coord.x = PSX_TEX_U(poly->u1);
    v[1].tex_coord.y = PSX_TEX_V(poly->v1);
    v[1].color.r = poly->r1 | blend;
    v[1].color.g = poly->g1 | blend;
    v[1].color.b = poly->b1 | blend;
    v[1].color.a = a;
    v[2].position.x = poly->x2;
    v[2].position.y = poly->y2;
    v[2].tex_coord.x = PSX_TEX_U(poly->u2);
    v[2].tex_coord.y = PSX_TEX_V(poly->v2);
    v[2].color.r = poly->r2 | blend;
    v[2].color.g = poly->g2 | blend;
    v[2].color.b = poly->b2 | blend;
    v[2].color.a = a;
    v[4].position.x = poly->x3;
    v[4].position.y = poly->y3;
    v[4].tex_coord.x = PSX_TEX_U(poly->u3);
    v[4].tex_coord.y = PSX_TEX_V(poly->v3);
    v[4].color.r = poly->r3 | blend;
    v[4].color.g = poly->g3 | blend;
    v[4].color.b = poly->b3 | blend;
    v[4].color.a = a;
    v[3] = v[1];
    v[5] = v[2];
}

void MyRenderPrimitives(void) {
    POLY_G4* g4;
    POLY_GT4* gt4;
    LINE_G2* lg2;
    SPRT* sp;
    SPRT_16* sp16;
    DR_MODE* dr;

    bool prevDtd = false;
    bool prevDfe = false;
    bool dtd;
    bool dfe;
    u8 colorBlend;
    RECT r = {0, 0, 0, 0};
    for (int i = 0; i < LEN(g_PrimBuf); i++) {
        Primitive* prim = &g_PrimBuf[i];
        if (prim->drawMode & DRAW_HIDE) {
            continue;
        }
        if (D_800973EC && !(prim->drawMode & DRAW_MENU)) {
            continue;
        }

        switch (prim->type) {
        case PRIM_NONE:
            break;
        case PRIM_G4:
            g4 = &g_CurrentBuffer->polyG4[g_GpuUsage.g4++];
            g4->r0 = prim->r0;
            g4->g0 = prim->g0;
            g4->b0 = prim->b0;
            g4->x0 = prim->x0;
            g4->y0 = prim->y0;
            g4->r1 = prim->r1;
            g4->g1 = prim->g1;
            g4->b1 = prim->b1;
            g4->x1 = prim->x1;
            g4->y1 = prim->y1;
            g4->r2 = prim->r2;
            g4->g2 = prim->g2;
            g4->b2 = prim->b2;
            g4->x2 = prim->x2;
            g4->y2 = prim->y2;
            g4->r3 = prim->r3;
            g4->g3 = prim->g3;
            g4->b3 = prim->b3;
            g4->x3 = prim->x3;
            g4->y3 = prim->y3;
            dtd = false;
            dfe = false;

            SetPolyG4(g4);
            SetSemiTrans(g4, !!(prim->drawMode & DRAW_TRANSP));
            AddPrim(&g_CurrentBuffer->ot[prim->priority], g4);
            break;
        case PRIM_GT4:
            gt4 = &g_CurrentBuffer->polyGT4[g_GpuUsage.gt4++];
            gt4->r0 = prim->r0 | 0xFF;
            gt4->g0 = prim->g0 | 0xFF;
            gt4->b0 = prim->b0 | 0xFF;
            gt4->x0 = prim->x0;
            gt4->y0 = prim->y0;
            gt4->u0 = prim->u0;
            gt4->v0 = prim->v0;
            gt4->clut = D_8003C104[prim->clut];
            gt4->r1 = prim->r1 | 0xFF;
            gt4->g1 = prim->g1 | 0xFF;
            gt4->b1 = prim->b1 | 0xFF;
            gt4->p1 = prim->p1;
            gt4->x1 = prim->x1;
            gt4->y1 = prim->y1;
            gt4->u1 = prim->u1;
            gt4->v1 = prim->v1;
            gt4->tpage = prim->tpage;
            gt4->r2 = prim->r2 | 0xFF;
            gt4->g2 = prim->g2 | 0xFF;
            gt4->b2 = prim->b2 | 0xFF;
            gt4->p2 = prim->p2;
            gt4->x2 = prim->x2;
            gt4->y2 = prim->y2;
            gt4->u2 = prim->u2;
            gt4->v2 = prim->v2;
            gt4->r3 = prim->r3 | 0xFF;
            gt4->g3 = prim->g3 | 0xFF;
            gt4->b3 = prim->b3 | 0xFF;
            gt4->p3 = prim->p3;
            gt4->x3 = prim->x3;
            gt4->y3 = prim->y3;
            gt4->u3 = prim->u3;
            gt4->v3 = prim->v3;
            dtd = false;
            dfe = false;

            SetPolyGT4(gt4);
            SetSemiTrans(gt4, !!(prim->drawMode & DRAW_TRANSP));
            AddPrim(&g_CurrentBuffer->ot[prim->priority], gt4);

            if (prevDtd != dtd || prevDfe != dfe) {
                if (g_GpuUsage.drawModes < MAX_DRAW_MODES) {
                    dr = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes++];
                    SetDrawMode(dr, dtd, dfe, 0, &r);
                    AddPrim(&g_CurrentBuffer->ot[prim->priority], dr);
                } else {
                    WARNF("draw mode buffer out of limit");
                }
            }
            break;
        case PRIM_SPRT:
            colorBlend = prim->drawMode & DRAW_COLORS ? 0x00 : 0xFF;
            sp = &g_CurrentBuffer->sprite[g_GpuUsage.sp++];
            sp->r0 = PSX_COL(prim->r0) | colorBlend;
            sp->g0 = PSX_COL(prim->g0) | colorBlend;
            sp->b0 = PSX_COL(prim->b0) | colorBlend;
            sp->x0 = prim->x0;
            sp->y0 = prim->y0;
            sp->u0 = prim->u0;
            sp->v0 = prim->v0;
            sp->clut = D_8003C104[prim->clut];
            sp->w = prim->u1;
            sp->h = prim->v1;

            SetSprt(sp);
            SetSemiTrans(sp, !!(prim->drawMode & DRAW_TRANSP));
            AddPrim(&g_CurrentBuffer->ot[prim->priority], sp);

            dr = &g_CurrentBuffer->drawModes[g_GpuUsage.drawModes++];
            SetDrawMode(dr, dtd, dfe, prim->tpage, &r);
            AddPrim(&g_CurrentBuffer->ot[prim->priority], dr);
            break;
        default:
            WARNF("unhandled prim type %d", prim->type);
            break;
        }
    }
}

u_short g_DrawEnvTpage;
DRAWENV* MyPutDrawEnv(DRAWENV* env) {
    if (env->isbg) {
        SDL_SetRenderDrawColor(g_Renderer, env->r0, env->g0, env->b0, 255);
    }
    g_DrawEnvTpage = env->tpage;

    return env;
}

void MyDrawOTag(OT_TYPE* p) {
    POLY_G4* g4;
    POLY_GT4* gt4;
    LINE_G2* lg2;
    SPRT* sp;
    SPRT_16* sp16;
    DR_MODE* drMode;

    SDL_Vertex v[6];
    SDL_Texture* t = NULL;
    u_short tpage = g_DrawEnvTpage;
    bool dfe = false;
    bool dtd = false;
    size_t n = 0;

    for (size_t n = 0; (u_long)p != 0xffffff; n++, p = (OT_TYPE*)p->tag) {
        P_TAG* tag = (P_TAG*)p;
        if (tag->len == 0) {
            continue;
        }

        u8 code = tag->code & ~3;
        u8 isSemiTrans = tag->code & 2;
        u8 isShadeTex = tag->code & 1;
        u8 isUnk = tag->code & 0x80;
        switch (code) {
        case 0x00:
            break;
        case 0x38:
            g4 = (POLY_G4*)tag;
            SetSdlVertexG4(v, g4, isSemiTrans);
            SDL_RenderGeometry(g_Renderer, NULL, v, 6, NULL, 0);
            break;
        case 0x3C:
            gt4 = (POLY_GT4*)tag;
            SetSdlVertexGT4(v, gt4, isSemiTrans);
            t = GetVramTexture(gt4->tpage, gt4->clut);
            SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
            break;
        case 0x50:
            lg2 = (LINE_G2*)tag;
            SDL_SetRenderDrawColor(g_Renderer, lg2->r0, lg2->g0, lg2->b0, 255);
            SDL_RenderDrawLine(g_Renderer, lg2->x0, lg2->y0, lg2->x1, lg2->y1);
            break;
        case 0x64:
            sp = (SPRT*)tag;
            SetSdlVertexSprite(v, sp, isSemiTrans);
            t = GetVramTexture(tpage, sp->clut);
            SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
            break;
        case 0x7C:
            sp16 = (SPRT_16*)tag;
            SetSdlVertexSprite16(v, sp16);
            t = GetVramTexture(tpage, sp16->clut);
            SDL_RenderGeometry(g_Renderer, t, v, 6, NULL, 0);
            break;
        case 0xE0:
            drMode = (DR_MODE*)tag;
            tpage = drMode->code[0] & 0x1FF;
            dtd = !!(drMode->code[0] & 0x200);
            dfe = !!(drMode->code[0] & 0x400);
            break;
        default:
            WARNF("code %02X not supported", code);
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    const char* filename;

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
